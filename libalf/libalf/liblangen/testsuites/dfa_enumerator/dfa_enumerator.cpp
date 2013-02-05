/* $Id: dfa_enumerator.cpp 1344 2010-07-18 15:34:43Z davidpiegdon $
 * vim: fdm=marker
 *
 * This file is part of liblangen (LANguageGENerator)
 *
 * liblangen is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liblangen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with liblangen.  If not, see <http://www.gnu.org/licenses/>.
 *
 * (c) 2008,2009 Lehrstuhl Softwaremodellierung und Verifikation (I2), RWTH Aachen University
 *           and Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 * Author: David R. Piegdon <david-i2@piegdon.de>
 *
 */

/*
 * dfa_enumerator: testsuite for DFA enumerator.
 */

#include <stdlib.h>

#include <iostream>
#include <fstream>

#include <liblangen/dfa_enumerator.h>
#include <libalf/conjecture.h>

using namespace liblangen;
using namespace std;

int main(int argc, char**argv)
{
	int alphabet_size;
	int state_count;

	if(argc != 3) {
		cout << "please give <alphabet size> and <state count> as parameters\n";
		return 1;
	}

	alphabet_size = atoi(argv[1]);
	state_count = atoi(argv[2]);

	dfa_enumerator denum(state_count, alphabet_size);

	libalf::finite_automaton automaton;

	int id = 0;

	while(!denum.generation_completed()) {
		set<int> final_states;
		denum.derive(automaton.is_deterministic, automaton.input_alphabet_size, automaton.state_count, automaton.initial_states, final_states, automaton.transitions);
		automaton.valid = true;
		automaton.set_final_states(final_states);
		ofstream file;
		char filename[64];
		snprintf(filename, 64, "dfa_%010d.dot", id);
		file.open(filename);
		file << automaton.visualize();
		file.close();

		denum.next(true);

		id++;
	}

	return 0;
}

