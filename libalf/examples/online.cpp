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
#include <ctime>
#include "../../file_names.h" // ofer
#include "../../scc/dominators.hpp"

using namespace std;
using namespace libalf;
int alphabet_size; 
int min_func_idx; // index of first function
bool instrument_branches = false, instrument_functions = false;
int mem_queries, cbmc_mem_queries;

bool **matrix; // represents the call graph
bool **instrumented_matrix; // represents the call graph for instrumented functions
bool *first_functions; // the list of first functions - to be updated based on main

// functions for computing dfs
void project_matrix_to_relevant_vertices(int n, int m);
void project_matrix_to_relevant_vertices_source(int n, int m, int current, int source);
int cnt;
void predecessors(int m, int current, int *predecessors_list);
void instrument();
void Abort(string msg);
int run(const char* cmd);

struct myEdge {char s[100]; char t[100];};
map<string, int> 	
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
		st << "-e s/\"_Learn_function_enter((const char \\*)\\\"c::" << string(name) << "\\\");\"// ";
	else
		st << "-e s/\"_Learn_function_enter((const char \\*)\\\"c::" << string(name) << "\\\");\"/\"_Learn_function_enter(" << num << ");\"/ ";	
	fprintf(convert, "%s", st.str().c_str());
}

void rewrite_branch(char *name, int num) 
{
	stringstream st; 
	if (num == -1) // remove statement
		st << "-e s/\"_Learn_branch((const char \\*)\\\"" << string(name) << "\\\");\"// ";
	else
		st << "-e s/\"_Learn_branch((const char \\*)\\\"" << string(name) << "\\\");\"/\"_Learn_branch(" << num << ");\"/ ";	
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
	st << input_file_name.substr(1,string::npos) << ".f";
	FILE *func_names = fopen(FUNC_NAMES, "r"),
		 *Labels = fopen(AUTO_LABELS_FUNCTIONS, "w"),
		 *user_func_names = fopen(st.str().c_str() , "r");
	if (func_names == NULL) Abort(string("cannot open ") + string(FUNC_NAMES));
	if (user_func_names != NULL) {
		cout << "found " << st.str() << endl;
		while (!feof(user_func_names)) {
			if (fscanf(user_func_names, "%s", name) != 1) continue;
			user_func_set.insert(pair<string, int>(name, 0));
		}
	}
	else cout << "Using all function names (other than 'main'). A restricted list can be given in a file " << input_file_name << ".f" << endl;
	
	while (!feof(func_names)) {
		if (fscanf(func_names, "%s", name) != 1) continue;
		
		if (!strcmp(name, "main") || ((user_func_names != NULL) && user_func_set.find(name) == user_func_set.end())) // here we can add other functions we wish to ignore
		{
			cout << "skipping " << name << endl; 
			rewrite_function_enter(name, -1); // -1 = remove statement
			continue; 
		}			
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



void project_matrix_to_relevant_vertices_cfg(int n, int m){
	// performs dfs contracting edges of the non-instrumented nodes	 
	// the matrix size is n x n. Only the first m x m sub-matrix (m <= n) relates to the vertices which we follow (i.e. nodes like 'main', 
	// 'assume', '_Learn_...' are not followed). This function updates the m x m sub-matrix such that matrix[i][j] = 1 (i,j <= m)
	// if there is a path from i to j in the n x n matrix.    

	for( int i=0; i < m; i++){
		for( int j = m; j < n; j++) {
			if( matrix[i][j] == 1 ) {
				project_matrix_to_relevant_vertices_source( n, m, j, i );
			}
		}
	}
}


void project_matrix_to_relevant_vertices(int n, int m){
	// performs dfs contracting edges of the non-instrumented nodes	 
	// the matrix size is n x n. Only the first m x m sub-matrix (m <= n) relates to the vertices which we follow (i.e. nodes like 'main', 
	// 'assume', '_Learn_...' are not followed). This function updates the m x m sub-matrix such that matrix[i][j] = 1 (i,j <= m)
	// if there is a path from i to j in the n x n matrix.    
	
	// initializing the instrumented matrix
	instrumented_matrix = (bool **)malloc(m*sizeof(bool *));
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
				if (instrumented_matrix[i][r] /*|| i == r*/) continue; // already marked				
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
				continue;
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
	map<string, int> node_index_cg; // indices for all functions in the cfg (superset of node_index)
	st << "echo \"#define membership\" > " << MODE;
	run(st.str().c_str()); // we analyze the call graph under membership query
	st.str("");
	st << "cmd /C \"" << GENERATE_CALL_GRAPH << " " << input_file_name_full << " " << CG << "\"";
	run(st.str().c_str());
	FILE *cg = fopen(CG, "r");
	if (!cg) Abort(string("cannot open ") + string(CG));
	
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



void import_allowed_pairs() { // based on goto-instrument's list of pairs.
	// creates the initial matrix according to the call graph. The indices are shifted by min_func_idx which is 2 if '--auto b' (branch instrumentation) is activated, and 0 otherwise.
	cout << "import_allowed_pairs " << endl;
	stringstream tmp;		

	

	tmp << "cmd /c \"goto-cl " << input_file_name_full << " " << "learn_code.c" << "\"";
	run(tmp.str().c_str());
	tmp.str("");
	tmp << "cmd /c \"goto-instrument --show-call-sequences " << input_file_name << ".exe \"" << " | grep - | sed -e s/" << "\"->\"" << "// -e s/" 
		<< "c:://  -e s/" << "c::" << "// -e s/\" Assert\"/\"assert\"/" << " > " << FUNC_PAIRS ;
	
	cout << "running " << tmp.str() << endl; fflush(stdout);
	run(tmp.str().c_str());

	FILE *pairs = fopen(FUNC_PAIRS, "r");
	vector<myEdge> edge_list;
	myEdge tmp_edge;	
	map<string, int> node_index_cfg; // indices for all functions in the cfg (superset of node_index)
	node_index_cfg.insert(node_index.begin(), node_index.end());
	while (!feof(pairs)) {
		if (fscanf(pairs, "%s %s\n", tmp_edge.s, tmp_edge.t) != 2) continue;
		edge_list.push_back(tmp_edge);				
		node_index_cfg.insert(pair<string, int>(string(tmp_edge.s), node_index_cfg.size() + min_func_idx ));
		node_index_cfg.insert(pair<string, int>(string(tmp_edge.t), node_index_cfg.size() + min_func_idx ));
	}
	int numOfVertices = node_index_cfg.size();
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
		int src = node_index_cfg[(*it).s] - min_func_idx;
		int target = node_index_cfg[(*it).t] - min_func_idx;
		cout << "min_func_idx = " << min_func_idx << ": " << src << " " <<  (*it).s << " " << target << " " << (*it).t << endl;
		matrix[src][target] = true;
	}

	print_matrix(numOfVertices); 
	print_matrix(node_index.size()); 
	
	//project_matrix_to_relevant_vertices_cfg(numOfVertices, node_index.size());  // note that we send node_index.size(), which is equal to m + 1, since it includes main.
		
	
	// %%%%%%%%%%%%%%%%%%%%   for experiment only. Use the _cfg version when goto-instrument bug is fixed.  %%%%%%%%%%%%%%%%%%%/
	project_matrix_to_relevant_vertices(numOfVertices, node_index.size());  // note that we send node_index.size(), which is equal to m + 1, since it includes main.
		  
	print_matrix(numOfVertices);	
	
	}



/****************************** before learn *************************/


void Abort(string msg) {
	cerr << msg << endl;
	exit(1);
}

void parse_options(int argc, char**argv) {		
	FILE *in;

	if (argc < 3) Abort(string("usage: online <file_name> <word-length> [--auto {b,f}]* [<user (manualy inserted) alphabet-size>]" "\n-- auto\tautomatic instrumentation of (f)unction entries or (b)ranch.\n\tif (f) is chosen, each function becomes a letter in the alphabet. Ignores alphabet-size if given. \n Default 'manual' alphabet-size is 0."));
	input_file_name_full = argv[1];
	if ((in = fopen(input_file_name_full.c_str(),"r")) == NULL) Abort(string("file ") + input_file_name_full + string("cannot be opened"));
	fclose(in);
	input_file_name = input_file_name_full.substr(0,input_file_name_full.size() - 2);
	assert(input_file_name_full[input_file_name_full.size() - 2]=='.');
	word_length = atoi(argv[2]);
	for (int i = 3; i < argc ; ++i) {
		if (!strcmp(argv[i], "--auto")) {
			if (argc == i + 1) Abort("missing argument {'b','f'}  for --auto\n"); 
			if (!strcmp(argv[i+1], "b")) instrument_branches = true;
			else if (!strcmp(argv[i+1], "f")) instrument_functions = true;
			else Abort("argument after --auto must be in {'b','f'}");
			++i;
		}
		else if (isdigit(argv[i][0])) alphabet_size = atoi(argv[3]); 
		else Abort(string("wrong argument: ") + string(argv[i]));
	}	
	
	if (alphabet_size == 0 && !instrument_branches && !instrument_functions) Abort("alphabet size must be > 0, or --auto should be used.");
}

void remove_files() {
	ostringstream tmp;
	tmp << "rm -f " << AUTO_LABELS << " " << POSITIVE_QUERIES_FILE << "; echo > " << POSITIVE_QUERIES_FILE;	// we need a positives_query file because it is included from other files. 
	run(tmp.str().c_str());
}

void init_auto_instrumentation()
{
	stringstream tmp;
	

	// the convert file will be activated only after goto-instrument.
	// we need to do the following conversions even if --auto is not activated, because the definition of _Learn_branch/_Learn_function_enter in learn.c won't compile otherwise.
	convert = fopen(CONVERT, "w");
	fprintf(convert, "@echo off\nsed ");
	
	fprintf(convert, "-e s/\"_Learn_function_exit((const char \\*)\\\"c::main\\\");\"/@@/ -e s/\"_Learn_function_exit((const char \\*)\\\"c::[a-zA-Z0-9_]*\\\");\"// -e s/\"@@\"/\"Learn_trap();\"/ ");

	fprintf(convert, "-e s/\"signed int _Learn_letter;\"// " );
	fprintf(convert, "-e s/\"void _Learn_branch(const char \\*)\"/\"void _Learn_branch(int _Learn_letter) \"/ ");	
	fprintf(convert, "-e s/\"void _Learn_function_enter(const char \\*)\"/\"void _Learn_function_enter(int _Learn_letter) \"/ ");	
	
		
	if (instrument_branches) {
		alphabet_size += 2;		
		rewrite_branch("not-taken", 0);
		rewrite_branch("taken", 1);
	}
	if (instrument_functions) {
		tmp.str("");
		tmp << "cmd /C \"" << GET_FUNC_NAMES  << " " << input_file_name << " " << FUNC_NAMES << "\""; // populates FUNC_NAMES with function names, according to the instrumented file generated by goto-instrument
		cout << "running " << tmp.str() << endl;
		run(tmp.str().c_str());
		min_func_idx = alphabet_size;
	
		alphabet_size = generate_func_names(alphabet_size); // this one also updates AUTO_LABELS_FUNCTIONS
		compute_allowed_pairs();
		// import_allowed_pairs();  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%  this is the one after cfg bug is fixed. 
	}	
	else {
		alphabet_size++; // because of the assert function.	If instrument_function is true, it updates it anyway.
		min_func_idx = alphabet_size; // we need to define it because it is used in answer_query
	}	

	fprintf(convert, " a.c > tmp.c\ncp tmp.c a.c\n");
	fclose(convert);		

	if (instrument_branches || instrument_functions) {
		tmp.str("");
		tmp << "cat " << (instrument_branches ? AUTO_LABELS_BRANCHES : " ") << " " << (instrument_functions ? AUTO_LABELS_FUNCTIONS : " ") << " > " << AUTO_LABELS;
		run(tmp.str().c_str());
				
		instrument();
	}
	
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
	
	run("cmd /C \"dominators.exe\"");
	run("cmd /C \"dfs.exe\"");
}

void show_result(conjecture *result) {	
	finite_automaton * a = dynamic_cast<finite_automaton*> (result);
	streambuf* strm_buffer = cout.rdbuf();		// redirecting cout to a.out. We need this because visualize() returns an ostream.
	ofstream dot("a.dot");
	cout.rdbuf (dot.rdbuf());	
	cout << a->visualize();
	dot.close();
	cout.rdbuf (strm_buffer); 

	run("dotty a.dot");	
}

/*******************************  Learn  ****************************/

list<int> get_CounterExample(int alphabetsize, bool *feedback) {
	list<int> ce;
	int  i;
	int length;
	ifstream read(MODEL);

	read >> *feedback;
	cout << ((*feedback) ? "Positive " : "Negative ") << "feedback" << endl;
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



void instrument() {
	// precondition: we get here only if (instrument_branches || instrument_functions)
	// auto-instrumentation via goto-instrument	
	stringstream tmp;		
	string goto_instrument_argument("");
	if (instrument_branches) goto_instrument_argument += string("--branch _Learn_branch ");
	if (instrument_functions) goto_instrument_argument += string("--function-enter _Learn_function_enter ");	
	
	assert(!goto_instrument_argument.empty());
	
	goto_instrument_argument += string("--function-exit _Learn_function_exit ");
	
	tmp.str("");
	tmp << "cmd /c \"goto-cl " << input_file_name_full <<"\"";
	run(tmp.str().c_str());

	tmp.str("");
	if (instrument_branches)
		tmp << "cmd /c \"goto-instrument " << goto_instrument_argument << "  --dump-c " << input_file_name << ".exe a.c \"";
	if (instrument_functions)
		tmp << "cmd /c \"goto-instrument " << goto_instrument_argument << "  --dump-c " << input_file_name << ".exe a.c \""; 		
	cout << "running: " << tmp.str() << endl;
	 run(tmp.str().c_str());

	 


	tmp.str("");
	tmp << "cmd /c " << CONVERT;
	run(tmp.str().c_str());	
}


int run(const char* cmd) {
	bool verbose = false; // to be made a command-line argument
	if (verbose) cout << cmd << endl;
	return system(cmd);
}


int run_cbmc(bool membership) {
	stringstream tmp;	
	string tmp_file("tmpfile");
	tmp << "echo \"#define " << (membership ? "membership" : "conjecture") << "\" > " << MODE;
	run(tmp.str().c_str());
	string filename = (instrument_branches || instrument_functions) ? "a.c" : input_file_name_full;
	tmp.str("");
	tmp << "cmd /c \"cbmc -Iansi-c-lib --unwind " << word_length_s.str() << " --no-unwinding-assertions --xml-ui " << filename << " learn_code.c " << " > " << tmp_file << "\"";
	run(tmp.str().c_str());	
	
	tmp.str("");
	tmp << "grep ERROR " << tmp_file;
	if (!run(tmp.str().c_str())) Abort(string("ERROR in output of CBMC (see " + tmp_file = ")"));
		
	if (!membership) { // in case of conjecture query, we extract the counterexample
		string cmd = string("cmd /C \"") + CE + string(" ") + tmp_file + "\"";
		run(cmd.c_str());		
	}
	tmp.str("");
	tmp <<  "grep -q FAILURE " << tmp_file;
	
	return run(tmp.str().c_str()); // 0 if there is CE, > 0 otherwise.  
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
	return (res != 0);	
}

bool answer_Membership(list<int> query) {
	list<int>::iterator it;
	list<int>::reverse_iterator rit;

	mem_queries++;
	if (query.size() == 0) return false;

	cout << "Please classify the word: ";	
	for (it = query.begin(); it != query.end(); ++it ) cout << *it;
	stringstream st;		
	
	// query longer than word_length. It will be rejected anyway. 
	if (query.size() > word_length) 
	{
		cout << "L!" << endl;
		return false;
	}

	// last letter must be 'assert' (== alphabet_size - 1)
	rit = query.rbegin();
	if (*rit != alphabet_size - 1) {		
		cout << "E!" << endl;
		return false;
	}
	// first letter must be accessible from 'main'
	it = query.begin();
	if (!matrix[alphabet_size][*it]) {	
		cout << "B!" << endl;
		return false;
	}
	
	bool saw_assert_test_letter = false;
	bool last_is_assert_letter;
	int last_func_call = -1;
	cout << " | ";
	st << "#include \"" << MEMBERSHIP_DATA_H << "\"\n"	<< "\nint _Learn_mq[mq_length] = {";
	for (it = query.begin(); it != query.end(); )
	{
		last_is_assert_letter = false;
		if (instrument_functions) {
			// consecutive letters in the word must be compatible with the call-graph, as represented in 'matrix'.
			if (*it >= min_func_idx) 
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
	cbmc_mem_queries++;
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
	//int res = run(cmd.c_str());		// invoking the script. The 'm' tells the script that it is a membership query.
	
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
		run (ist.str().c_str());
	}

	return (res == 0);		
}

void learn() {
	// Create new knowledge-base. In this case, we choose bool as type for the knowledge-base.
	knowledgebase<bool> base;
	conjecture *result = NULL;	

	// Create learning algorithm (Angluin L*) without a logger (2nd argument is NULL) and alphabet size alphabet_size
	angluin_simple_table<bool> algorithm(&base, NULL, alphabet_size);

	bool feedback;
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
			//	if (conjectured) exit(1);
				// Add answer to knowledge-base
				base.add_knowledge(*li, a);
			}
						
		//	if (counter > 1 && conjectured) exit(1);
			conjectured = false;
		}
		// Resolve equivalence queries
		else {			
			//counter++;
			if (conjectured) Abort(string("last counterexample corresponds to a nondeterministic path: it can either belong or not belong to the language. "));
			conjectured = true;
			bool is_equivalent = answer_Conjecture(cj);			
			//if (counter == 1) exit(1);
			if (is_equivalent) {
				result = cj;
			} else {
				// Get a counter-example
				list<int> ce = get_CounterExample(alphabet_size, &feedback);			
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

void preprocess_source() {	
	// adding 'include "learn.c" ' in the first line of the source file. It is necessary for goto-cl because of the Learn_Assert command. 
	stringstream tmp;

	tmp << "cmd /c sed -e '1i\\#include \\\"learn.c\\\" ' " << input_file_name_full << " > tmp "; 
	run(tmp.str().c_str());
	cout << tmp.str().c_str() << endl;
	tmp.str("");
	input_file_name_full = "_" + input_file_name_full;
	input_file_name = "_" + input_file_name;
	tmp << "cp tmp " << input_file_name_full;
	run(tmp.str().c_str());	
}



/*******************************  main  ****************************/
int main(int argc, char**argv) {		
	clock_t begin = clock();
	parse_options(argc, argv);
	remove_files();
	preprocess_source();
	init_auto_instrumentation();
    init_word_length_file();
		
	learn();		

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "membership queries: " << mem_queries << " (" << cbmc_mem_queries << " cbmc calls - " << (float)cbmc_mem_queries * 100/(float)mem_queries << "\%)" << endl;
	cout << "Time: " << elapsed_secs << endl;

	return 0;
		
	}