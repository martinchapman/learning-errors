/* $Id: co_knowledgebase.h 1427 2010-12-07 14:51:42Z davidpiegdon $
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

#ifndef __libalf_dispatcher_co_knowledgebase_h__
# define __libalf_dispatcher_co_knowledgebase_h__

#include <libalf/answer.h>
#include <libalf/serialize.h>
#include <libalf/knowledgebase.h>

#include "client_object.h"

class co_knowledgebase;

#include "co_learning_algorithm.h"

using namespace libalf;

class co_knowledgebase : public client_object {
	private:
		co_knowledgebase(knowledgebase<bool> * o);

	public:
		knowledgebase<bool> * o;

		set<int> referring_learning_algorithms;
		set<int> referring_iterators;
	public:
		co_knowledgebase();

		virtual ~co_knowledgebase();

		virtual enum object_type get_type()
		{ return OBJ_KNOWLEDGEBASE; };

		virtual bool handle_command(int command, basic_string<int32_t> & command_data);

		virtual void ref_learning_algorithm(int oid);
		virtual void deref_learning_algorithm(int oid);

		virtual void ref_knowledgebase_iterator(int oid);
		virtual void deref_knowledgebase_iterator(int oid);

		virtual int get_reference_count()
		{
			int refs = 0;
			refs += referring_learning_algorithms.size();
			refs += referring_iterators.size();
			return refs;
		}
		virtual int get_depending_reference_count()
		{ return get_reference_count(); };
};

#endif // __libalf_dispatcher_co_knowledgebase_h__

