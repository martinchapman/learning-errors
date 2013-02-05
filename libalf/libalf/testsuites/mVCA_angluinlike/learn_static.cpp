/* $Id: learn_static.cpp 1418 2010-11-02 17:08:31Z davidpiegdon $
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
 * (c) 2010 Lehrstuhl Softwaremodellierung und Verifikation (I2), RWTH Aachen University
 *      and Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 * Author: David R. Piegdon <david-i2@piegdon.de>
 *
 */

#include <iostream>
#include <ostream>
#include <iterator>
#include <fstream>
#include <algorithm>

#include <libmVCA/mVCA.h>
#include <libmVCA/deterministic_mVCA.h>
#include <libmVCA/pushdown.h>

#include <libalf/alf.h>
#include <libalf/knowledgebase.h>
#include <libalf/algorithm_mVCA_angluinlike.h>

#include <mVCA_alf_glue.h>

using namespace std;
using namespace libalf;
using namespace libmVCA;

ostream_logger my_logger(&cout, LOGGER_DEBUG);

pushdown_alphabet get_alphabet()
{{{
	pushdown_alphabet ret(3);
	ret.set_direction(0, DIR_UP);
	ret.set_direction(1, DIR_STAY);
	ret.set_direction(2, DIR_DOWN);
	return ret;
}}}

libmVCA::mVCA * get_aNbcN3()
{{{
	map<int, map<int, map<int, set<int> > > > transitions;

	pushdown_alphabet al = get_alphabet();

	set<int> final;
	final.insert(1);

	transitions[0][0][0].insert(0);

	transitions[1][0][0].insert(0);
	transitions[1][1][2].insert(1);

	transitions[2][0][0].insert(0);
	transitions[2][1][2].insert(1);

	transitions[3][0][0].insert(0);
	transitions[3][1][2].insert(1);
	transitions[3][0][1].insert(1);

	return construct_mVCA(/*state-count*/ 2, al, /*initial state*/ 0, final, /*m_bound*/ 3, transitions);
}}};

libmVCA::mVCA * get_aNbcN3_or_b()
{{{
	map<int, map<int, map<int, set<int> > > > transitions;
	// m->state->sigma->states

	pushdown_alphabet al = get_alphabet();

	set<int> final;
	final.insert(1);
	final.insert(2);

	transitions[0][0][0].insert(0);
	transitions[0][0][1].insert(2);

	transitions[1][0][0].insert(0);
	transitions[1][1][2].insert(1);

	transitions[2][0][0].insert(0);
	transitions[2][1][2].insert(1);

	transitions[3][0][0].insert(0);
	transitions[3][1][2].insert(1);
	transitions[3][0][1].insert(1);

	return construct_mVCA(/*state-count*/ 3, al, /*initial state*/ 0, final, /*m_bound*/ 3, transitions);
}}};


int main()
{
	knowledgebase<bool> kb;
	mVCA_angluinlike<bool> table(&kb, &my_logger, 3);
	vector<int> alphabet_pushdown_directions;
	alphabet_pushdown_directions.resize(3);
	alphabet_pushdown_directions[0] = 1;
	alphabet_pushdown_directions[1] = 0;
	alphabet_pushdown_directions[2] = -1;
	table.indicate_pushdown_alphabet_directions(alphabet_pushdown_directions);

	libmVCA::mVCA * teacher;
	teacher = get_aNbcN3_or_b();

	// real work with algorithm:
	while(1) {
		conjecture * cj = NULL;

		int count = 0;
		int delta;
		my_logger(LOGGER_DEBUG, "membership-query cycle\n");
		while(NULL == (cj = table.advance())) {
			delta = mVCA_alf_glue::automaton_answer_knowledgebase(*teacher, kb);
			count += delta;
			if(delta == 0) break;
		}
		my_logger(LOGGER_DEBUG, "answered %d membership queries for next conjecture.\n", count);
		if(delta == 0) break;

		if(NULL != dynamic_cast<bounded_simple_mVCA*>(cj)) {
			// partial equivalence query
			int bound = ( dynamic_cast<bounded_simple_mVCA*>(cj) )->m_bound;
			my_logger(LOGGER_INFO, "partial equivalence query for bound %d.\n", bound);
//			cout << cj->visualize();
			list<int> counterexample;
			if(mVCA_alf_glue::automaton_partial_equivalence_query(*teacher, cj, bound, counterexample)) {
				my_logger(LOGGER_INFO, "is equivalent.\n");
				table.indicate_partial_equivalence();
			} else {
				my_logger(LOGGER_INFO, "results in counterexample %s .\n", word2string(counterexample).c_str());
				table.add_counterexample(counterexample);
			}
		} else if(NULL != dynamic_cast<simple_mVCA*>(cj)) {
			// full equivalence query
			my_logger(LOGGER_INFO, "full equivalence query.\n");
//			cout << cj->visualize();
			list<int> counterexample;
			if(mVCA_alf_glue::automaton_equivalence_query(*teacher, cj, counterexample)) {
				my_logger(LOGGER_INFO, "is equivalent.\n");
				break;
			} else {
				my_logger(LOGGER_INFO, "results in counterexample %s .\n", word2string(counterexample).c_str());
				table.add_counterexample(counterexample);
			}
		} else {
			// bad query!
			my_logger(LOGGER_ERROR, "bad conjecture from mVCA_angluinlike:\n\n%s\n\n%s\n\n", cj->write().c_str(), cj->visualize().c_str());
			delete cj;
			return -1;
		}

		delete cj;
	}


	// debugging of table:
	table.print(cout);

	basic_string<int32_t> ser;
	ser = table.serialize();
//	cout << "\n\n{ ";
//	print_basic_string_2hl(ser, cout);
//	cout << " }\n";

	mVCA_angluinlike<bool> table2(&kb, &my_logger, 1);
	serial_stretch s(ser);
	if(!table2.deserialize(s))
		cerr << "failed to deser!\n";

//	ser = table2.serialize();
//	cout << "\n{ ";
//	print_basic_string_2hl(ser, cout);
//	cout << " }\n\n";

	generic_statistics stat;
	table.receive_generic_statistics(stat);
	cout << "statistics:\n\t";
	stat.print(cout);
	cout << "\n";

	return 0;
}

