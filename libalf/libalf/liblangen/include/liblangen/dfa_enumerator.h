/* $Id: dfa_enumerator.h 1414 2010-11-02 15:51:48Z davidpiegdon $
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
 * dfa_enumerator: enumerate over all accessible n-state automata with specific alphabet size
 */

#include <map>
#include <vector>
#include <set>

#ifndef __liblangen_dfa_enumerator_h__
# define __liblangen_dfa_enumerator_h__

namespace liblangen {

// for alphabet_size >= 2, dfa_enumerator will construct all possible DFAs
// with a given alphabet size and exact state count (i.e. all states reachable)
//
// use derive() to obtain the current DFA,
// use next() to move to the next automaton.

class dfa_enumerator {
	private:
		typedef struct transition_t {
			int source;
			int label;
			int destination;
		} transition;
	private:
		bool completed;

		int alphabet_size;
		int state_count;
		std::set<int> initial;
		std::vector<bool> final;
		std::vector<transition> transitions;

	public:
		dfa_enumerator(int state_count, int alphabet_size);

		// returns true if next automaton is valid
		// (all states are reachable)
		// false, if next automaton may be skipped or
		// if all automata have been generated (check generation_completed() ).
		bool next(bool exact_state_count);

		bool derive(bool &t_is_dfa, int &t_alphabet_size, int &t_state_count, std::set<int> &t_initial, std::set<int> &t_final, std::map<int, std::map<int, std::set<int> > > &t_transitions);

		bool generation_completed()
		{ return completed; };
};

}; // end of namespace liblangen

#endif

