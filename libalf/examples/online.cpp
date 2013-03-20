
// TODO: 
// 1. check issue of max unrolling due to the number of states + length of path. 
// 2. what should be done about illegal paths that seem to be accepted in the automaton ? 



/* 
 * This file is part of libalf.
 *
 * libalf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libalf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libalf.  If not, see <http://www.gnu.org/licenses/>.
 *
 * (c) 2009 Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 *
 * Author: Daniel Neider <neider@automata.rwth-aachen.de>
 *
 */

/*
 * This class demonstrates how to use online algorithms in libalf. In this
 * example, the user is queried for classified examples that are then used to
 * compute the final result.
 *
 * This program takes the alphabet size as the input and produces the conjecture
 * as the output by requesting the user to classify the queries/words computed
 * in the knowledgebase. As the first step, a knowledgebase is created.
 * The user is then required to provide information about the
 * alphabet size of the automaton. Once this information is obtained, a learning
 * algorithm is created by passing the type of algorithm, empty knowledgebase,
 * and the alphabet size as the parameters. The learning algorithm advances
 * iteratively, checking at every step, if enough information exists in the
 * knowledgebase to construct a conjecture. If there was no enough information
 * to compute a conjecture, a list of words (called queries) that are to be
 * classifed by the user is produced. The words are presented to the user for
 * classification and this information is added to the knowledgebase. When
 * during an advance, if a conjecture was computed, then it is presented to the
 * user to check its equivalence. If the conjecture was correct, the file
 * "output_online.dot" containing the code for the automaton is created.
 * However, if the conjecture is incorrect, then the user is prompted to provide
 * a counter example which is used in furthur construction of the conjecture. In
 * this demo, the ANGLUIN algorithm is used.
 */

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

using namespace std;
using namespace libalf;
int alphabet_size; 
int **matrix;

string input_file;
int word_length; 
ostringstream word_length_s;   
	
/*
 * Reading the counterexample from model.txt.
 */
list<int> get_CounterExample(int alphabetsize) {
	list<int> ce;
	char i;
	int length;
	ifstream read(MODEL);
	cout << "Counterexamle ";
	read >> length;
	cout << "(length = " << length << ")";
	while(read>>i && (length--)) 
	{
		cout << " " << i;
		ce.push_back(i - '0');
	}
	cout << endl;
	return ce;
}

/*
 * getting the candidate data and writing it to conjecture_data.c; invoking the script for a conjecture query. Returning the result.  
 */
bool check_Equivalence(conjecture * cj) {

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
	string cmd = string("cmd /C \"") + CE + " " + input_file + " " + word_length_s.str() + string(" \"");
	int res = system(cmd.c_str());		// invoking the script for a conjecture query. 
	//cout << " " << (res != 0 ? "(yes - equivalent)" : "(no - not equivalent)") << endl;		
	res = system("grep -q FAILURE tmp");
	cout << " " << (res != 0 ? "(yes - equivalent)" : "(no - not equivalent)") << endl;		
	return (res != 0);	
}

/*
 * Function used to obtain information about the classification of a word. 
 */
bool answer_Membership(list<int> query) {

	if (query.size() == 0) return false;

	cout << "Please classify the word: ";		
	FILE *file;
	file = fopen(MEMBERSHIP_DATA, "w");
	fprintf(file, "#define mq_length %d\nint _Learn_mq[mq_length] = {", query.size());
	list<int>::iterator it;
	bool saw_assert_test_letter = false;
	for (it = query.begin(); it != query.end(); )
	{
		if (*it == alphabet_size - 1) {
			if (saw_assert_test_letter) {cout << *it << " ! \n"; fprintf(file, "[answering 'no' trvially. This file will not be used]"); fclose(file); fflush(stdout); return false;}
			saw_assert_test_letter = true;
		}
		cout << *it;
		fprintf(file, "%d", *it);
		it++;
		if (it != query.end()) fprintf(file, ", ");
	}
	fprintf(file, "};");
	fclose(file);
	cout << endl;

	fflush(stdout);
	
	string cmd = string("cmd /C \"") + CE + " " + input_file + " " + word_length_s.str() + " "  + string(" m\"");
	int res = system(cmd.c_str());		// invoking the script. The 'm' tells the scrpt that it is a membership query. 	
	res = system("grep -q FAILURE tmp");
	cout << " " << (res == 0 ? "(yes)" : "(no)") << endl;		
	

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

int generate_func_names(int letter) {
	char name[100];
	FILE *func_names = fopen(FUNC_NAMES, "r"),
		 *ToLearn = fopen(FUNCNAMETONUM, "w"),
		 *Labels = fopen(AUTO_LABELS_FUNCTIONS, "w");
	if (func_names == NULL) {fprintf(stderr, "cannot open %s. ", FUNC_NAMES); exit(1);}	
	bool first = true;
	while (!feof(func_names)) {
		if (fscanf(func_names, "%s", name) != 1) continue;
		if (!strcmp(name, "main") || !strcmp(name, "_Learn_branch") || !strcmp(name,"check_conjecture") || !strcmp(name,"check_conjecture_at_trap")) continue; // TODO: change function names so they all start with _Learn
		if (!first) fprintf(ToLearn, "else ");
		first = false;
		fprintf(Labels, "%d %s\n", letter, name);
		fprintf(ToLearn, "if (!strcmp(\"c::%s\", st)) {_Learn(%d);}\n", name, letter++); // the c:: is necessary because goto-instrument reports the function name with this prefix.
		
	}
	fclose(func_names);
	fclose(ToLearn);
	fclose(Labels);
	return letter;
}


struct edge {char s[100]; char t[100];};
void compute_allowed_pairs() {  // call before removing the ".c" from input_file
	stringstream s;	
	vector<edge> edge_list;
	edge tmp_edge;
	map<char *, int> edge_index;

	s << GENERATE_CALL_GRAPH << " " << input_file << " " << CG;
	system(s.str().c_str());
	FILE *cg = fopen(CG, "r");
	
	while (!feof(cg)) {
		if (fscanf(cg, "%s %s", tmp_edge.s, tmp_edge.t) != 2) continue;
		edge_list.push_back(tmp_edge);		
		edge_index.insert(pair<char *, int>(tmp_edge.s, edge_index.size() + 1));
		edge_index.insert(pair<char *, int>(tmp_edge.t, edge_index.size() + 1));
	}
	int numOfVertices = edge_index.size();
	cout << "# of vertices = " << numOfVertices;
	// initializing matrix
	matrix = new int*[numOfVertices];
	for(int i = 0; i < numOfVertices; ++i) {
	    matrix[i] = new int[numOfVertices];
	}
	// resetting matrix
	for (int t = 0; t < numOfVertices; ++t)
		for (int j = 0; j < numOfVertices; ++j)
			matrix[t][j] = 0;

	// filling matrix
	vector<edge>::iterator it;	
	for (it = edge_list.begin(); it != edge_list.end(); ++it) {
		int src = edge_index[(*it).s];
		int target = edge_index[(*it).t];
		matrix[src][target] = 1;
	}
}



/*
 * The main method
 */
int main(int argc, char**argv) {
	
	bool instrument_branches = false, instrument_functions = false;

	// Create new knowledgebase. In this case, we choose bool as type for the knowledgebase.
	knowledgebase<bool> base;

	
	conjecture * result = NULL;

	/*
	 * The method "advance" is iterated in a loop which checks if there is
	 * enough information to formulate a conjecture. If there was no enough
	 * information for the same, the method creates a list of words that are
	 * to be classified by the user. This is referred to as "queries". The
	 * user answers the query and the answer is added to the knowledgebase.
	 * This information may either give enough knowledge to the algorithm to
	 * produce a conjecture or may produce more queries to be resolved. This
	 * is identified when "advance" is invoked in the next iteration.
	 *
	 * On the otherhand, If a conjecture was computed, it is displayed on the
	 * screen and the user classifies it as correct or incorrect.
	 * If marked correct, the conjecture is stored in a variable
	 * named "automaton" which is later used to construct the ".dot" file.
	 * If the conjecture is rejected, the algorithm requires a counter
	 * example from the user and iteration is continued.
	 */

	if (argc < 3) {fprintf(stderr, "usage: online <file_name> <word-length> [--auto {b,f}]* [<alphabet-size>]" "\n-- auto\tautomatic instrumentation of (f)unction entries or (b)ranch.\n\tif (f) is chosen, each function becomes a letter in the alphabet. Ignores alphabet-size if given. \n Default alphabet-size is 2.\n"); exit(1);}
	input_file = argv[1];	
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
	
	
	compute_allowed_pairs();
	
	ostringstream tmp;
	tmp << "rm -f " << AUTO_LABELS;
	system(tmp.str().c_str());
	if (instrument_branches || instrument_functions) alphabet_size = 0; // if --auto, then we override user-input regarding the alphabetsize.

	if (instrument_branches) {
		alphabet_size = 2;		
	}
	tmp.str("");
	if (instrument_functions) {
		unsigned int pos = input_file.find('.');
		if (pos != std::string::npos) input_file = input_file.substr(0,pos);
		tmp << "cmd /C \"" << GET_FUNC_NAMES  << "\" " << input_file;
		cout << "running " << tmp.str() << endl;
		system(tmp.str().c_str());
		alphabet_size = generate_func_names(alphabet_size) + 1;
	}

	tmp.str("");
	tmp << "cat " << (instrument_branches ? AUTO_LABELS_BRANCHES : " ") << " " << (instrument_functions ? AUTO_LABELS_FUNCTIONS : " ") << " > " << AUTO_LABELS;
	if (instrument_branches || instrument_functions) system(tmp.str().c_str());
	
	

	tmp.str("");
	printf("reading from %s; word_length = %d, alphabet-size = %d\n", input_file.c_str(), word_length, alphabet_size);
	FILE *file;
	file = fopen(WORD_LENGTH, "w");
	fprintf(file, "#define word_length_bound %d\n", word_length);
	fprintf(file, "#define AlphaBetSize %d", alphabet_size);
	
	tmp << "rm -f " << POSITIVE_QUERIES_FILE << "; echo > " << POSITIVE_QUERIES_FILE;
	system(tmp.str().c_str());
	word_length_s << (word_length + 1); // we need to unroll one more than the word_length
	cout << word_length_s.str() << endl;
	fclose(file);
	
	
	

	// Create learning algorithm (Angluin L*) without a logger (2nd argument is NULL) and alphabet size alphabet_size
	angluin_simple_table<bool> algorithm(&base, NULL, alphabet_size);


	bool conjectured = false;
	//int counter = 0;
	do {
	
		// Advance the learning algorithm
		conjecture * cj = algorithm.advance();

		// Resolve membership queries
		if (cj == NULL) {

			conjectured = false;
			// retrieve queries
			list<list<int> > queries = base.get_queries();

			// iterate through all queries
			list<list<int> >::iterator li;
			for (li = queries.begin(); li != queries.end(); li++) {

				// Answer query
				bool a = answer_Membership(*li);
				//if (counter == 1) exit(1);
				//counter ++;
				
				// Add answer to knowledgebase
				base.add_knowledge(*li, a);
			}
		}
		// Resolve equivalence queries
		else {
			if (conjectured) {
				cout << "last counterexample corresponds to a nondeterministic path: it can either belong or not belong to the language. " << endl;
				exit(1);
			}
			conjectured = true;
			bool is_equivalent = check_Equivalence(cj);			
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

	//Display the result on the screen.
	//	cout << endl << "Result:" << endl << result->visualize() << endl;

	system("cmd /C \"dominators.exe\"");
	system("cmd /C \"dfs.exe\"");

	finite_automaton * a = dynamic_cast<finite_automaton*> (result);
	streambuf* strm_buffer = cout.rdbuf();		// redirecting cout to a.out. We need this because visualize() returns an ostream.
	ofstream dot("a.dot");
	cout.rdbuf (dot.rdbuf());
	cout << a->visualize();
	dot.close();


	system("dotty a.dot");
	
	delete result;
	
	return 0;
}
