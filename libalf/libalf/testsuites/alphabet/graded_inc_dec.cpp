/* $Id: graded_inc_dec.cpp 1000 2009-10-13 10:09:11Z davidpiegdon $
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

#include <libalf/alphabet.h>

using namespace std;
using namespace libalf;

int main()
{
	list<int> word;

	for(int i = 0; i < 20; i++) {
		cout << "(" << word2string(word) << ")++\n";
		inc_graded_lex(word, 3);
	}

	for(int i = 0; i < 20; i++) {
		dec_graded_lex(word, 3);
		cout << "--(" << word2string(word) << ")\n";
	}

	return 0;
}

