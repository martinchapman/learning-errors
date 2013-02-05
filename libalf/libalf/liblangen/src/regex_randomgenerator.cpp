/* $Id: regex_randomgenerator.cpp 1001 2009-10-13 10:09:48Z davidpiegdon $
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
 * RegEx Random Generator, similar to the one described in section 4.3 of
 * [1] "F. Denis, A. Lemay and A. Terlutte - Learning regular languages using RFSAs"
 */

#include <liblangen/regex_randomgenerator.h>
#include <liblangen/prng.h>

#include <stdio.h>

namespace liblangen {

using namespace std;
using namespace prng;

regex_randomgenerator::regex_randomgenerator()
{{{
	seed_prng();
}}}

string regex_randomgenerator::normalized_generate(int & alphabet_size, int num_op, float & p_concat, float & p_union, float & p_star)
{{{
	if(num_op <= 0) {
		// just return a terminal, i.e. an element from the alphabet
		string s;
		s += (char)('a'+random_int(alphabet_size));
		return s;
	}

	float x, p_sum;

	// choose random operator
	x = random_float();
	p_sum = 0.;

	p_sum += p_concat;
	if(x < p_sum) {
		string s1,s2;
		s1 = normalized_generate(alphabet_size, num_op/2, p_concat, p_union, p_star);
		s2 = normalized_generate(alphabet_size, num_op/2, p_concat, p_union, p_star);
		return s1 + s2;
	}

	p_sum += p_union;
	if(x < p_sum) {
		string s1,s2;
		s1 = normalized_generate(alphabet_size, num_op/2, p_concat, p_union, p_star);
		s2 = normalized_generate(alphabet_size, num_op/2, p_concat, p_union, p_star);

		return "(" + s1 + ")|(" + s2 + ")";
	}

	// p_star in any case (normed to 1)
	string s;
	s = normalized_generate(alphabet_size, num_op-1, p_concat, p_union, p_star);

	return "(" + s + ")*";
}}}

string regex_randomgenerator::generate(int alphabet_size, int num_op, float p_concat, float p_union, float p_star)
{{{
	float p_concat_norm;
	float p_union_norm;
	float p_star_norm;
	float p_sum;

	if(p_concat < 0 || p_union < 0 || p_star < 0)
		return "";

	p_sum = p_concat + p_union + p_star;

	p_concat_norm = p_concat / p_sum;
	p_union_norm = p_union / p_sum;
	p_star_norm = p_star / p_sum;

	return normalized_generate(alphabet_size, num_op, p_concat_norm, p_union_norm, p_star_norm);
}}}

}; // end of namespace liblangen

