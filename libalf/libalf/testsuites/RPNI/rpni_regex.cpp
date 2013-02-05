/* $Id: rpni_regex.cpp 1344 2010-07-18 15:34:43Z davidpiegdon $
 * vim: fdm=marker
 *
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
 * (c) 2008,2009 Lehrstuhl Softwaremodellierung und Verifikation (I2), RWTH Aachen University
 *           and Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 * Author: David R. Piegdon <david-i2@piegdon.de>
 *
 */

#include <iostream>
#include <ostream>
#include <iterator>
#include <fstream>
#include <algorithm>

#include <libalf/alf.h>
#include <libalf/algorithm_RPNI.h>

#include <amore++/deterministic_finite_automaton.h>
#include <amore++/nondeterministic_finite_automaton.h>

#include <liblangen/prng.h>

#include "amore_alf_glue.h"

using namespace std;
using namespace libalf;



// add knowledge about epsilon?
bool add_epsilon = true;
// how many runs should be used to generate knowledge from regex-generated automaton?
int runs = 100;
// how long should these runs be?
int run_length = 8;




int main(int argc, char**argv)
{
	amore::finite_automaton *nfa = NULL;
	amore::finite_automaton *dfa = NULL;

	ostream_logger log(&cout, LOGGER_DEBUG);

	knowledgebase<bool> knowledge;

	ofstream file;
	char filename[128];

	int alphabet_size;

	bool regex_ok;
	if(argc == 3) {
		nfa = new amore::nondeterministic_finite_automaton(atoi(argv[1]), argv[2], regex_ok);
	} else /* find alphabet size or show some example regex */ {{{
		if(argc == 2) {
			nfa = new amore::nondeterministic_finite_automaton(argv[1], regex_ok);
		} else {
			cout << "either give a sole regex as parameter, or give <alphabet size> <regex>.\n\n";
			cout << "example regular expressions:\n";
			cout << "alphabet size, \"regex\":\n";
			cout << "2 '((a((aa)a))U(((bb))*((((bU(ab))U(bUa)))*)*))'\n";
			cout << "2 '(((bb)|a)(b(((bb)b)(((aa)a)|a))))'\n";
			cout << "2 '(((aa)(a)*)(((a((b(b)*)(aUb)))((ba))*))*)'\n";
			cout << "3 '(cbb(ab(c)*))* U (a((cbb*) U a+b+bc)+)'\n";
			return 1;
		}
	}}}

	if(regex_ok) {
		log(LOGGER_INFO, "REGEX ok.\n");
	} else {
		log(LOGGER_ERROR, "REGEX failed.\n");
		return 1;
	}

	file.open("original-nfa.dot"); file << nfa->visualize(); file.close();

	dfa = nfa->determinize();
	delete nfa;
	dfa->minimize();
	file.open("original-dfa.dot"); file << dfa->visualize(); file.close();

	alphabet_size = dfa->get_alphabet_size();

	list<int> w;
	if(add_epsilon)
		knowledge.add_knowledge(w, dfa->contains(w));

	// create sample set in knowledgebase
	for(int i = 0; i < runs; i++) {
		w.clear();
		for(int j = 0; j < run_length; j++) {
			int r = liblangen::prng::random_int(alphabet_size);
			w.push_back(r);
			knowledge.add_knowledge(w, dfa->contains(w));
		}
	}

	cout << "\n";
	knowledge.print(cout);
	cout << "\n";

	RPNI<bool> rumps(&knowledge, &log, alphabet_size);
	amore::finite_automaton * hypothesis = NULL;
	conjecture *cj;
	libalf::finite_automaton *ba;

	if(!rumps.conjecture_ready()) {
		log(LOGGER_WARN, "RPNI says that no conjecture is ready! trying anyway...\n");
	}

	if( NULL == (cj = rumps.advance()) ) {
		log(LOGGER_ERROR, "advance() returned false!\n");
	} else {
		ba = dynamic_cast<libalf::finite_automaton*>(cj);
		set<int> final_states;
		ba->get_final_states(final_states);
//		rumps.print(cout);
		hypothesis = amore::construct_amore_automaton(ba->is_deterministic, ba->input_alphabet_size, ba->state_count, ba->initial_states, final_states, ba->transitions);

		snprintf(filename, 128, "hypothesis.dot");
		file.open(filename); file << hypothesis->visualize(); file.close();

		amore::finite_automaton * ndifference, * difference;
		ndifference = dfa->lang_symmetric_difference( *hypothesis );
		difference = ndifference->determinize();
		delete ndifference;
		difference->minimize();

		snprintf(filename, 128, "difference.dot");
		file.open(filename); file << difference->visualize(); file.close();

		delete difference;

		printf("\n\nhypothesis/difference saved.\n\n");

		delete hypothesis;
		delete cj;
	}

	return 0;
}

