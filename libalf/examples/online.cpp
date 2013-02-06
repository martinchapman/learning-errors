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
// Used to define the libalf name space.
#include <libalf/alf.h>
// Angluin's L* algorithm
#include <libalf/algorithm_angluin.h>

using namespace std;
using namespace libalf;


/*
 * Reading the counterexample from model.txt.
 */
list<int> get_CounterExample(int alphabetsize) {
	list<int> ce;
	char i;
	ifstream read("model.txt");
	cout << "Counterexamle: ";  
	while(read>>i) 
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
	ofstream dot("a.dot");
	cout.rdbuf (dot.rdbuf());
	cout << a->visualize();
	dot.close();

	ofstream candidate("conjecture_data.c");    // same thing for write()
	cout.rdbuf (candidate.rdbuf());
	cout << a->write(); // write() is a rewrite of the original lib function. 
	candidate.close();
	cout.rdbuf (strm_buffer); // reverting cout to its normal behavior. 

	int res = system("cmd /C \"ce.bat\"");		// invoking the script for a conjecture query. 
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
	file = fopen("membership_data.c", "w");
	fprintf(file, "#define mq_length %d\nint _Learn_mq[mq_length] = {", query.size());
	list<int>::iterator it;
	for (it = query.begin(); it != query.end(); )
	{
		cout << *it;
		fprintf(file, "%d", *it);
		it++;
		if (it != query.end()) fprintf(file, ", ");
	}
	fprintf(file, "};");
	fclose(file);

	fflush(stdout);
	int res = system("cmd /C \"ce.bat m\"");		// invoking the script. The 'm' tells the scrpt that it is a membership query. 
	cout << " " << (res == 0 ? "(yes)" : "(no)") << endl;		

	return (res == 0);		
}

/*
 * The main method
 */
int main(int argc, char**argv) {
	
	int alphabet_size = 2; 

	// Create new knowledgebase. In this case, we choose bool as type for the knowledgebase.
	knowledgebase<bool> base;

	// Create learning algorithm (Angluin L*) without a logger (2nd argument is NULL) and alphabet size alphabet_size
	angluin_simple_table<bool> algorithm(&base, NULL, alphabet_size);

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
	do {
	
		// Advance the learning algorithm
		conjecture * cj = algorithm.advance();

		// Resolve membership queries
		if (cj == NULL) {

			// retrieve queries
			list<list<int> > queries = base.get_queries();

			// iterate through all queries
			list<list<int> >::iterator li;
			for (li = queries.begin(); li != queries.end(); li++) {

				// Answer query
				bool a = answer_Membership(*li);

				// Add answer to knowledgebase
				base.add_knowledge(*li, a);
			}
		}
		// Resolve equivalence queries
		else {
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
	system("dotty a.dot");
	// Delete result
	delete result;
	
	return 0;
}
