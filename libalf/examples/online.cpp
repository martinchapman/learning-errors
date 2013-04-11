#include <iostream> 
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// Used to define the libalf name space.
#include <libalf/alf.h>
// Angluin's L* algorithm
#include <libalf/algorithm_angluin.h>
#include <vector>
#include <map>
#include "../../file_names.h" // ofer
#include "../../scc/dominators.hpp"

using namespace std;
using namespace libalf;
int alphabet_size; 
int min_func_idx; // index of first function
bool instrument_branches = false, instrument_functions = false;

bool **matrix; // represents the call graph
bool **instrumented_matrix; // represents the call graph for instrumented functions
bool *first_functions; // the list of first functions - to be updated based on main

// functions for computing dfs
void project_matrix_to_relevant_vertices(int n, int m);
void project_matrix_to_relevant_vertices_source(int n, int m, int current, int source);
int cnt;
void predecessors(int m, int current, int *predecessors_list);

struct myEdge {char s[100]; char t[100];};
map<string, int> 
	node_index_cg, // indices for all functions in the cfg (superset of node_index)
	node_index; // indices for functions we care about.


string input_file_name, 
	input_file_name_full; // with extension (e.g. file.c)
int word_length; 
ostringstream word_length_s;
FILE *convert;	

/*********************** building 'matrix' (the allowed consecutive function calls) based on the call-graph  ******************/

void rewrite_function_enter(char *name, int num) // rewriting the instrumented calls: either erase or change to reporting an int.
{
	stringstream st; 
	if (num == -1) // remove statement
		st << "-e s/\"_Learn_function_enter((signed char \\*)\\\"c::" << string(name) << "\\\");\"// ";
	else
		st << "-e s/\"_Learn_function_enter((signed char \\*)\\\"c::" << string(name) << "\\\");\"/\"_Learn_function_enter(" << num << ");\"/ ";	
	fprintf(convert, "%s", st.str().c_str());
}

void rewrite_branch(char *name, int num) 
{
	stringstream st; 
	if (num == -1) // remove statement
		st << "-e s/\"_Learn_branch((signed char \\*)\\\"" << string(name) << "\\\");\"// ";
	else
		st << "-e s/\"_Learn_branch((signed char \\*)\\\"" << string(name) << "\\\");\"/\"_Learn_branch(" << num << ");\"/ ";	
	fprintf(convert, "%s", st.str().c_str());
}

int generate_func_names(int letter) {
// reads func names from FUNC_NAMES and 
// 1) fills the global list node_index (to be used later in compute_allowed_pairs())
// 2) populates AUTO_LABELS_FUNCTIONS with function labels, 
// 3) prepares the CONVERT (convert.bat) file, which removes calls to _Learn_func_enter that we are not interested in (e.g. 'main, check_conjectiure, etc), 
//    and replaces the (char *) <func_name> with (int index) in the file a.c (the result of goto-instrument). Using int rather than strings avoids
//    strcmp() instructions which turn into loops by cbmc. 
	char name[100];
	map<string, int> user_func_set;
	stringstream st;
	st << input_file_name << ".f";
	FILE *func_names = fopen(FUNC_NAMES, "r"),
		 *Labels = fopen(AUTO_LABELS_FUNCTIONS, "w"),
		 *user_func_names = fopen(st.str().c_str() , "r");
	if (func_names == NULL) {fprintf(stderr, "cannot open %s. ", FUNC_NAMES); exit(1);}
	if (user_func_names != NULL) {
		cout << "found " << st.str() << endl;
		while (!feof(user_func_names)) {
			if (fscanf(user_func_names, "%s", name) != 1) continue;
			user_func_set.insert(pair<string, int>(name, 0));
		}
	}
	else cout << "Using all function names (other than 'main'). A restricted list can be given in a file " << input_file_name << ".f" << endl;
	bool first = true;
	while (!feof(func_names)) {
		if (fscanf(func_names, "%s", name) != 1) continue;
		
		if (!strcmp(name, "main") || ((user_func_names != NULL) && user_func_set.find(name) == user_func_set.end())) // here we can add other functions we wish to ignore
		{
			cout << "skipping " << name << endl; 
			rewrite_function_enter(name, -1); // -1 = remove statement
			continue; 
		}		
		first = false;
		node_index.insert(pair<string, int>(string(name), letter));
		fprintf(Labels, "%d %s\n", letter, name);
		rewrite_function_enter(name, letter++);		
	}
// what's special about assert is that it is not instrumented, being a library function. Inside Learn_assert we invoke Learn(alphabet-1)

	fprintf(Labels, "%d %s\n", letter, "assert");
	node_index.insert(pair<string, int>(string("assert"), letter++));	
	node_index.insert(pair<string, int>(string("main"), letter++));	// we force main to be at index m + 1 for conviniance when building matrix later on. It will not be part of the alphabet (see line).
	
	fclose(func_names);
	fclose(Labels);	
	return letter - 1; // '-1' because this number is fed into alphabet_size, and we do not want main to be part of the alphabet. 
}

void print_matrix(int numOfVertices) {
	cout << " -------------------------------------------------" << endl;
	for (int t = 0; t < numOfVertices; ++t){
		for (int j = 0; j < numOfVertices; ++j)
			cout << matrix[t][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void populate(dominators::myGraph_t *myGraph, bool **instrumented_matrix, int m) {
	typedef dominators::myGraph_t::edge edge;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			if (instrumented_matrix[i][j]) myGraph->edges.push_back(edge(i, j));
	myGraph->numOfVertices = m;
}; 

void project_matrix_to_relevant_vertices(int n, int m){
	// performs dfs contracting edges of the non-instrumented nodes	 
	// the matrix size is n x n. Only the first m x m sub-matrix (m <= n) relates to the vertices which we follow (i.e. nodes like 'main', 
	// 'assume', '_Learn_...' are not followed). This function updates the m x m sub-matrix such that matrix[i][j] = 1 (i,j <= m)
	// if there is a path from i to j in the n x n matrix.    
	
	// initializing the instrumented matrix
	instrumented_matrix = (bool **)malloc(m*sizeof(bool));
	for(int i = 0; i < m; ++i) {
	      instrumented_matrix[i] = new bool[m];
	}

	for( int i=0; i < m; i++){
		for( int j = m; j < n; j++) {
			if( matrix[i][j] == 1 ) {
				project_matrix_to_relevant_vertices_source( n, m, j, i );
			}
		}
	}
		
	// updating instrumented matrix 	
	for (int t = 0; t < m; ++t) {		
		for (int j = 0; j < m; ++j) {
			instrumented_matrix[j][t] = matrix[j][t];			
		}
	} 	

	int *predecessors_list;
	predecessors_list = new int[m];

	dominators::myGraph_t myGraph;		

	/* see '****' below why this is turned off. 
	populate(&myGraph, instrumented_matrix, m); // create myGraph from instrumented_matrix
	dominators dom;
	dom.find_dominators(myGraph, m - 1); // m - 1 is 'main', and it is the root. 		
	*/

	for (int i = 0; i < m - 2; i++) {  // -2 because we are not looking for predecessors of assert + main
		for(int j = 0; j < m; j++){
			predecessors_list[j]=-1;			
		}
		
		cnt = 0;
		predecessors(m, i, predecessors_list); // fill list of predecessors of i
		
		
		int tmp;
		for(int t = 0; (tmp = predecessors_list[t]) > -1; t++){  // for each predecessor tmp
			for (int r = 0; r < m; r++){ // looking for tmp's children					
				if (instrumented_matrix[i][r] || i == r) continue; // already marked				
				if (!matrix[tmp][r])  continue;
				// ***** currently turning-off domination check. The reason is that e.g.: f -> g -> h: g can be called after h although it dominates it, because g can be called twice from f.
				// The call graph does not include this information. 
				//if (dom.isDom(r, i)) {cout << r << " dominates " << i << endl; continue;} // if r dominates i, then it cannot follow i. 
				instrumented_matrix[i][r] = 1;
			}			
		}
	}
	delete(predecessors_list);

	// updating the first mXm of the original matrix 
	// with the instrumented matrix
	for (int t = 0; t < m; ++t)
		for (int j = 0; j < m; ++j)
			matrix[j][t] = instrumented_matrix[j][t];		
}

void project_matrix_to_relevant_vertices_source(int n, int m, int current, int source ){
 
	// performs dfs for a given source node contracting non-instrumented edges
    int v;
    
	for(v = 0; v < n; v++)
    {
        if(matrix[current][v] == 1) {
			if (v < m) {
				matrix[source][v] = 1;
				return;
			}
			if( v != current){
				project_matrix_to_relevant_vertices_source( n, m, v, source );
			}
		}
	}
}

void predecessors(int m, int current, int *predecessors_list) {
	
	int flag = 0;

	for (int i = 0; i < m; i++) {
		flag = 0;
		for (int tt = 0; predecessors_list[tt] > -1; tt++) {
			if (i == predecessors_list[tt]){
				flag = 1;
				break;
			}
		}
		if( (matrix[i][current] == 1) && !flag ) {
			predecessors_list[cnt++] = i;
			predecessors(m, i, predecessors_list);
		}
	}
}
	
void compute_allowed_pairs() { 
// creates the initial matrix according to the call graph. The indices are shifted by min_func_idx which is 2 if '--auto b' (branch instrumentation) is activated, and 0 otherwise.
	stringstream st;	
	vector<myEdge> edge_list;
	myEdge tmp_edge;	
	st << "echo \"#define membership\" > " << MODE;
	system(st.str().c_str()); // we analyze the call graph under membership query
	st.str("");
	st << "cmd /C \"" << GENERATE_CALL_GRAPH << " " << input_file_name_full << " " << CG << "\"";
	system(st.str().c_str());
	FILE *cg = fopen(CG, "r");
	if (!cg) {fprintf(stderr, "cannot open %s", CG); exit(1);}
	
	node_index_cg.insert(node_index.begin(), node_index.end());
	cout << "# of vertices = " << node_index_cg.size() << " " << node_index.size() << "(including 'main')" << endl;
	while (!feof(cg)) {
		if (fscanf(cg, "%s %s\n", tmp_edge.s, tmp_edge.t) != 2) continue;
		edge_list.push_back(tmp_edge);				
		node_index_cg.insert(pair<string, int>(string(tmp_edge.s), node_index_cg.size() + min_func_idx ));
		node_index_cg.insert(pair<string, int>(string(tmp_edge.t), node_index_cg.size() + min_func_idx ));
	}
	int numOfVertices = node_index_cg.size();
	cout << "# of vertices = " << numOfVertices << endl;

	// allocating matrix
	matrix = new bool*[numOfVertices];
	for(int i = 0; i < numOfVertices; ++i) {
	    matrix[i] = new bool[numOfVertices];
	}

	// initializing matrix
	for (int t = 0; t < numOfVertices; ++t)
		for (int j = 0; j < numOfVertices; ++j)
			matrix[t][j] = false;

	// filling matrix
	vector<myEdge>::iterator it;
	for (it = edge_list.begin(); it != edge_list.end(); ++it) {
		int src = node_index_cg[(*it).s] - min_func_idx;
		int target = node_index_cg[(*it).t] - min_func_idx;
		cout << "min_func_idx = " << min_func_idx << ": " << src << (*it).s << " " << target << (*it).t << endl;
		matrix[src][target] = true;
	}
	
	print_matrix(numOfVertices); 
	print_matrix(node_index.size()); 
	project_matrix_to_relevant_vertices(numOfVertices, node_index.size());  // note that we send node_index.size(), which is equal to m + 1, since it includes main.
	//print_matrix(node_index.size());	
	print_matrix(numOfVertices);	
}


/****************************** before learn *************************/

void parse_options(int argc, char**argv) {		
	if (argc < 3) {fprintf(stderr, "usage: online <file_name> <word-length> [--auto {b,f}]* [<user (manualy inserted) alphabet-size>]" "\n-- auto\tautomatic instrumentation of (f)unction entries or (b)ranch.\n\tif (f) is chosen, each function becomes a letter in the alphabet. Ignores alphabet-size if given. \n Default 'manual' alphabet-size is 0.\n"); exit(1);}
	input_file_name_full = argv[1];	
	unsigned int pos = input_file_name_full.find('.');
	if (pos != std::string::npos) input_file_name = input_file_name_full.substr(0,pos);
	word_length = atoi(argv[2]);
	for (int i = 3; i < argc ; ++i) {
		if (!strcmp(argv[i], "--auto")) {
			if (argc == i + 1) {fprintf(stderr, "missing argument {'b','f'}  for --auto\n"); exit(1);}
			if (!strcmp(argv[i+1], "b")) instrument_branches = true;
			else if (!strcmp(argv[i+1], "f")) instrument_functions = true;
			else {fprintf(stderr, "argument after --auto must be in {'b','f'} \n"); exit(1);}
			++i;
		}
		else if (isdigit(argv[i][0])) alphabet_size = atoi(argv[3]); 
		else {fprintf(stderr, "wrong argument: %s\n", argv[i]); exit(1);}
	}	
	
	if (alphabet_size == 0 && !instrument_branches && !instrument_functions) {fprintf(stderr, "alphabet size must be > 0, or --auto should be used."); exit(1);}
}

void remove_files() {
	ostringstream tmp;
	tmp << "rm -f " << AUTO_LABELS << " " << POSITIVE_QUERIES_FILE << "; echo > " << POSITIVE_QUERIES_FILE;	// we need a positives_query file because it is included from other files. 
	system(tmp.str().c_str());
}

void init_auto_instrumentation()
{
	stringstream tmp;
	
	// we need to do the following conversions even if --auto is not activated, because the definition of _Learn_branch/_Learn_function_enter in learn.c won't compile otherwise.
	convert = fopen(CONVERT, "w");
	fprintf(convert, "@echo off\n");
	fprintf(convert, "sed -e s/\"signed int _Learn_letter;\"// " );
	fprintf(convert, "-e s/\"void _Learn_branch(signed char \\*)\"/\"void _Learn_branch(int _Learn_letter) \"/ ");	
	fprintf(convert, "-e s/\"void _Learn_function_enter(signed char \\*)\"/\"void _Learn_function_enter(int _Learn_letter) \"/ ");	

		
	if (instrument_branches) {
		alphabet_size += 2;		
		rewrite_branch("not-taken", 0);
		rewrite_branch("taken", 1);
	}
	if (instrument_functions) {		
		tmp << "cmd /C \"" << GET_FUNC_NAMES  << " " << input_file_name << " " << FUNC_NAMES << "\""; // populates FUNC_NAMES with function names, according to the instrumented file generated by goto-instrument
		cout << "running " << tmp.str() << endl;
		system(tmp.str().c_str());
		min_func_idx = alphabet_size;
	
		alphabet_size = generate_func_names(alphabet_size); // this one also updates AUTO_LABELS_FUNCTIONS
		compute_allowed_pairs();
	}	
	else {
		alphabet_size++; // because of the assert function.	If instrument_function is true, it updates it anyway.
		min_func_idx = alphabet_size; // we need to define it because it is used in answer_query
	}	

	if (instrument_branches || instrument_functions) {
		tmp.str("");
		tmp << "cat " << (instrument_branches ? AUTO_LABELS_BRANCHES : " ") << " " << (instrument_functions ? AUTO_LABELS_FUNCTIONS : " ") << " > " << AUTO_LABELS;
		system(tmp.str().c_str());
	}
	fprintf(convert, " a.c > tmp.c\ncp tmp.c a.c\n");
	fclose(convert);		
}

void init_word_length_file() {
	printf("reading from %s; word_length = %d, alphabet-size = %d\n", input_file_name_full.c_str(), word_length, alphabet_size);
	FILE *file = fopen(WORD_LENGTH, "w");
	fprintf(file, "#define word_length_bound %d\n", word_length);
	fprintf(file, "#define AlphaBetSize %d", alphabet_size);
	fclose(file);	
	word_length_s << (word_length + 1); // we need to unroll one more than the word_length
}

/******************************* after learn *************************/

void post_process() {
	
	system("cmd /C \"dominators.exe\"");
	system("cmd /C \"dfs.exe\"");
}

void show_result(conjecture *result) {	
	finite_automaton * a = dynamic_cast<finite_automaton*> (result);
	streambuf* strm_buffer = cout.rdbuf();		// redirecting cout to a.out. We need this because visualize() returns an ostream.
	ofstream dot("a.dot");
	cout.rdbuf (dot.rdbuf());	
	cout << a->visualize();
	dot.close();
	cout.rdbuf (strm_buffer); 

	system("dotty a.dot");	
}

/*******************************  Learn  ****************************/

list<int> get_CounterExample(int alphabetsize) {
	list<int> ce;
	int  i;
	int length;
	ifstream read(MODEL);
	cout << "Counterexample ";
	read >> length;
	cout << "(length = " << length << ")";
	while(read>>i && (length--)) 
	{
		cout << " read: " << i;
		ce.push_back(i);
	}
	cout << endl;
	return ce;
}

int run_cbmc(bool membership) {
	stringstream tmp;	
	tmp << "echo \"#define " << (membership ? "membership" : "conjecture") << "\" > " << MODE;
	system(tmp.str().c_str());
	//if (membership) system("echo \"#define membership\" > " + MODE);
	//else system("echo \"#define conjecture\" > " + MODE);
	string goto_instrument_argument("");
	if (instrument_branches) goto_instrument_argument += string("--branch _Learn_branch ");
	if (instrument_functions) goto_instrument_argument += string("--function-enter _Learn_function_enter ");
	tmp.str("");
	string tmp_file("tmpfile");
	if (!goto_instrument_argument.empty()) {
		tmp << "cmd /c \"goto-cl " << input_file_name_full <<"\"";
		system(tmp.str().c_str());
		
		tmp.str("");
		tmp << "cmd /c \"goto-instrument " << goto_instrument_argument << "  --dump-c " << input_file_name << ".exe a.c \"";
		system(tmp.str().c_str());
		
		tmp.str("");
		tmp << "cmd /c " << CONVERT;
		system(tmp.str().c_str());
		
		tmp.str("");
		tmp << "cmd /c \"cbmc -Iansi-c-lib --unwind " << word_length_s.str() << " --no-unwinding-assertions --xml-ui a.c learn_code.c " << " > " << tmp_file << "\"";
		system(tmp.str().c_str());
	}
	else {
			tmp << "cmd /c \"cbmc -Iansi-c-lib --unwind " << word_length_s.str() << " --no-unwinding-assertions --xml-ui " << input_file_name_full << " learn_code.c > " << tmp_file << "\"";
			system(tmp.str().c_str());
	}

	tmp.str("");
	tmp << "grep ERROR " << tmp_file;
	if (!system(tmp.str().c_str())) {
		cout << "ERROR in output of CBMC" << endl;
		exit(1);
	}

	string m = membership ? " m\"" : "\"";
	string cmd = string("cmd /C \"") + CE + string(" ") + tmp_file + m;
	system(cmd.c_str());
	tmp.str("");
	tmp <<  "grep -q FAILURE " << tmp_file;
	
	return system(tmp.str().c_str());
}

bool answer_Conjecture(conjecture * cj) {

	assert(cj != NULL);

	finite_automaton * a = dynamic_cast<finite_automaton*> (cj);
	cout << endl << "Conjecture:" << endl << endl;
	cout << a->visualize();
	streambuf* strm_buffer = cout.rdbuf();		// redirecting cout to a.out. We need this because visualize() returns an ostream.
	//ofstream dot("a.dot");
	//cout.rdbuf (dot.rdbuf());
	//cout << a->visualize();
	//dot.close();

	ofstream candidate(CONJECTURE_DATA);    // same thing for write()
	cout.rdbuf (candidate.rdbuf());
	cout << a->write(); // write() is a rewrite of the original lib function. 
	candidate.close();
	cout.rdbuf (strm_buffer); // reverting cout to its normal behavior. 			
	int res = run_cbmc(false);	
	cout << " " << (res != 0 ? "(yes - equivalent)" : "(no - not equivalent)") << endl;		
	//exit(1);
	return (res != 0);	
}

bool answer_Membership(list<int> query) {

	if (query.size() == 0) return false;

	cout << "Please classify the word: ";	
	stringstream st;		
	st << "#include \"" << MEMBERSHIP_DATA_H << "\"\n"	<< "\nint _Learn_mq[mq_length] = {";
	list<int>::iterator it;
	list<int>::reverse_iterator rit;
	
	// last letter must be 'assert' (== alphabet_size - 1)
	rit = query.rbegin();
	if (*rit != alphabet_size - 1) {
		for (it = query.begin(); it != query.end(); ++it ) cout << *it;
		cout << "E!" << endl;
		return false;
	}

	it = query.begin();
	if (!matrix[alphabet_size][*it]) {
		for (it = query.begin(); it != query.end(); ++it ) cout << *it;
		cout << "B!" << endl;
		return false;
	}
	
	bool saw_assert_test_letter = false;
	bool last_is_assert_letter;
	int last_func_call = -1;
	for (it = query.begin(); it != query.end(); )
	{
		last_is_assert_letter = false;
		if (instrument_functions) {
			// consecutive letters in the word must be compatible with the call-graph, as represented in 'matrix'.
			if (*it >= min_func_idx) // TODO: screen also first letter: only those that can be accessed through main without one of the good functions can be first. 
			{		
				if (last_func_call >=0 && !matrix[last_func_call - min_func_idx][*it - min_func_idx]) { cout << *it << " @! \n"; return false;}
				last_func_call = *it;
			}
		}
		else
		{	// cannot have two 'asserts' in the word
			if (*it == alphabet_size - 1) {
				if (saw_assert_test_letter) {cout << *it << " ! \n"; return false;}
				saw_assert_test_letter = true;
				last_is_assert_letter = true;
			}
		}
		cout << *it;
		st << *it;
		it++;
		if (it != query.end()) st << ", ";
	}
	st << "};";
	
	FILE *file = fopen(MEMBERSHIP_DATA, "w");
	fprintf(file, "%s", st.str().c_str());
	fclose(file);

	st.str("");
	file = fopen(MEMBERSHIP_DATA_H, "w");
	st << "#define mq_length " << query.size() << "\nextern int _Learn_mq[mq_length];";
	fprintf(file, "%s", st.str().c_str());
	fclose(file);
	

	cout << endl;

	fflush(stdout);
	
	int res = run_cbmc(true);

	//string cmd = string("cmd /C \"") + CE + " " + input_file_name + " " + word_length_s.str() + " "  + string(" m ") + (instrument_functions ? string("f") : instrument_branches ? string("b") : string("")) + string("\"");	
	//int res = system(cmd.c_str());		// invoking the script. The 'm' tells the script that it is a membership query.
	
	cout << " " << (res == 0 ? "(yes)" : "(no)") << endl;
	
	// updating the positive_queries_file: this will block paths that correspond to membership that we already answered positively.
	if (res == 0)
	{		
		int size = query.size();		
		ostringstream ist;		
		ist << "echo \"if (_Learn_idx == " << size << " && ";
		int i = 0;
		for (it = query.begin(); it != query.end(); ++i)			
		{
			ist << "_Learn_b[" << i  << "] == " << *it;			
			it++;
			if (it != query.end()) ist << " && "; else ist << ") __CPROVER_assume (0); \" >> " << POSITIVE_QUERIES_FILE;			
		}
		system (ist.str().c_str());
	}

	return (res == 0);		
}

void learn() {
	// Create new knowledge-base. In this case, we choose bool as type for the knowledge-base.
	knowledgebase<bool> base;
	conjecture *result = NULL;	

	// Create learning algorithm (Angluin L*) without a logger (2nd argument is NULL) and alphabet size alphabet_size
	angluin_simple_table<bool> algorithm(&base, NULL, alphabet_size);


	bool conjectured = false;
	int counter = 0;
	do {	
		// Advance the learning algorithm
		conjecture *cj = algorithm.advance();		
		// Resolve membership queries
		if (cj == NULL) {			
			counter++;
			// retrieve queries
			list<list<int> > queries = base.get_queries();

			// iterate through all queries
			list<list<int> >::iterator li;
			for (li = queries.begin(); li != queries.end(); li++) {

				// Answer query				
				bool a = answer_Membership(*li);				
				//if (counter == 2) exit(1);
				// Add answer to knowledge-base
				base.add_knowledge(*li, a);
			}
						
		//	if (counter > 1 && conjectured) exit(1);
			conjectured = false;
		}
		// Resolve equivalence queries
		else {			
			//counter++;
			if (conjectured) {
				cout << "last counterexample corresponds to a nondeterministic path: it can either belong or not belong to the language. " << endl;
				exit(1);
			}
			conjectured = true;
			bool is_equivalent = answer_Conjecture(cj);			
			//if (counter == 1) exit(1);
			if (is_equivalent) {
				result = cj;
			} else {
				// Get a counter-example
				list<int> ce = get_CounterExample(alphabet_size);			
				// Add counter-example to algorithm
				algorithm.add_counterexample(ce);
				
				// Delete old conjecture
				delete cj;
			}
		}
		

	} while (result == NULL);
	
	post_process();
	
	show_result(result);	// we do it inside learn because result is a pointer to a local object. 
	
	delete result;	
}


/*******************************  main  ****************************/
int main(int argc, char**argv) {		
	parse_options(argc, argv);
	remove_files();
	init_auto_instrumentation();
    init_word_length_file();
		
	learn();		

	return 0;
}
