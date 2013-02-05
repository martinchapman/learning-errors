/* $Id: learn_regex.cpp 1386 2010-10-12 16:59:18Z davidpiegdon $
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
#include <libalf/algorithm_angluin.h>

#include <amore++/nondeterministic_finite_automaton.h>

#include "amore_alf_glue.h"

using namespace std;
using namespace libalf;

int main(int argc, char**argv)
{
	statistics stats;

	amore::finite_automaton *nfa;
	ostream_logger log(&cout, LOGGER_DEBUG);

	knowledgebase<bool> knowledge;

	char filename[128];
	ofstream file;

	int iteration;
	bool success = false;

	int alphabet_size;
	unsigned int hypothesis_state_count = 0;

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

	alphabet_size = nfa->get_alphabet_size();

	{{{ /* dump original automata */
		file.open("original-nfa.dot"); file << nfa->visualize(); file.close();

		amore::finite_automaton * dfa;
		dfa = nfa->determinize();
		dfa->minimize();
		file.open("original-dfa.dot"); file << dfa->visualize(); file.close();
		delete dfa;
	}}}


	// create angluin_col_table and teach it the automaton
	angluin_col_table<bool> ot(&knowledge, &log, alphabet_size);
	amore::finite_automaton * hypothesis = NULL;

	for(iteration = 1; iteration <= 100; iteration++) {
		int c = 'a';
		conjecture * cj;

		while( NULL == (cj = ot.advance()) ) {
			// resolve missing knowledge:

			snprintf(filename, 128, "knowledgebase%02d%c.dot", iteration, c);
			file.open(filename); file << knowledge.visualize(); file.close();

			// create query-tree
			knowledgebase<bool> * query;
			query = knowledge.create_query_tree();

			snprintf(filename, 128, "knowledgebase%02d%c-q.dot", iteration, c);
			file.open(filename); file << query->visualize(); file.close();

			// answer queries
			stats.queries.uniq_membership += amore_alf_glue::automaton_answer_knowledgebase(*nfa, *query);

			snprintf(filename, 128, "knowledgebase%02d%c-r.dot", iteration, c);
			file.open(filename); file << query->visualize(); file.close();

			// merge answers into knowledgebase
			knowledge.merge_knowledgebase(*query);
			delete query;
			c++;
		}

		libalf::finite_automaton * ba = dynamic_cast<libalf::finite_automaton*>(cj);
		if(hypothesis)
			delete hypothesis;
		hypothesis = amore_alf_glue::automaton_libalf2amore(*ba);
		delete cj;
		if(!hypothesis) {
			printf("generation of hypothesis failed!\n");
			return -1;
		}

		{{{ /* dump/serialize table */
			basic_string<int32_t> serialized;
			basic_string<int32_t>::iterator it;

			snprintf(filename, 128, "table%02d.text.angluin", iteration);
			file.open(filename); ot.print(file); file.close();

			/*
			serialized = ot.serialize();

			snprintf(filename, 128, "table%02d.serialized.angluin", iteration);
			file.open(filename);

			for(it = serialized.begin(); it != serialized.end(); it++) {
				file << ntohl(*it);
				file << ";";
			}

			file.close();
			*/
		}}}

		snprintf(filename, 128, "hypothesis%02d.dot", iteration);
		file.open(filename); file << hypothesis->visualize(); file.close();

		printf("hypothesis %02d state count %02d\n", iteration, hypothesis->get_state_count());
		if(hypothesis_state_count >= hypothesis->get_state_count()) {
			log(LOGGER_ERROR, "STATE COUNT DID NOT INCREASE\n");
			getchar();
		}
		hypothesis_state_count = hypothesis->get_state_count();

		// once an automaton is generated, test for equivalence with oracle_automaton
		// if this test is ok, all worked well

		list<int> counterexample;
		stats.queries.equivalence++;
		if(amore_alf_glue::automaton_equivalence_query(*nfa, *hypothesis, counterexample)) {
			// equivalent
			cout << "success.\n";
			success = true;
			break;
		}

		snprintf(filename, 128, "counterexample%02d.angluin", iteration);
		file.open(filename);
		print_word(file, counterexample);
		ot.add_counterexample(counterexample);
		file.close();
	}

	iteration++;
	snprintf(filename, 128, "knowledgebase%02d-final.dot", iteration);
	file.open(filename);
	file << knowledge.visualize();
	file.close();

	stats.memory = ot.get_memory_statistics();
	stats.queries.membership = knowledge.count_resolved_queries();

	delete nfa;

	cout << "\nrequired membership queries: " << stats.queries.membership << "\n";
	cout << "required uniq membership queries: " << stats.queries.uniq_membership << "\n";
	cout << "required equivalence queries: " << stats.queries.equivalence << "\n";
	cout << "sizes: bytes: " << stats.memory.bytes
	     << ", members: " << stats.memory.members
	     << ", words: " << stats.memory.words << "\n";
	cout << "upper table rows: " << stats.memory.upper_table
	     << ", lower table rows: " << stats.memory.lower_table
	     << ", columns: " << stats.memory.columns << "\n";
	cout << "minimal state count: " << hypothesis->get_state_count() << "\n";

	delete hypothesis;

	if(success)
		return 0;
	else
		return 2;
}

