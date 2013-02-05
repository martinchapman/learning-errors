/* $Id: co_learning_algorithm.cpp 1444 2011-02-28 16:29:41Z davidpiegdon $
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
 * (c) 2008,2009,2010,2011
 *		Lehrstuhl Softwaremodellierung und Verifikation (I2), RWTH Aachen University
 *	    and Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 * Author: David R. Piegdon <david-i2@piegdon.de>
 *
 */

#include <libalf/answer.h>
#include <libalf/serialize.h>
#include <libalf/learning_algorithm.h>

#include <libalf/algorithm_angluin.h>
#include <libalf/algorithm_biermann_minisat.h>
//#include BIERMANN_ANGLUIN
#include <libalf/algorithm_NLstar.h>
#include <libalf/algorithm_RPNI.h>
#include <libalf/algorithm_DeLeTe2.h>
#include <libalf/algorithm_biermann_original.h>
#include <libalf/algorithm_DeLeTe2.h>
#include <libalf/algorithm_kearns_vazirani.h>
#include <libalf/algorithm_rivest_schapire.h>

#include "co_learning_algorithm.h"
#include "co_logger.h"
#include "co_normalizer.h"
#include "co_knowledgebase.h"
#include "co_knowledgebase_iterator.h"

using namespace std;
using namespace libalf;

co_learning_algorithm::co_learning_algorithm(enum libalf::learning_algorithm_type alg, int alphabet_size)
{{{
	referenced_knowledgebase = -1;
	referenced_logger = -1;
	referenced_normalizer = -1;

	switch(alg) {
		default:
			// we can't use this->sv->clog here, as sv is not initialized yet.
			fprintf(stderr, "bad request reached co_learning_algorithm constructor\n"
					"(bad type of learning algorithm: %d (%s). maybe not implemented yet?).\n"
					"killing client.\n",
				(int)alg, learning_algorithm_name(alg));
			exit(-1);

		case ALG_ANGLUIN:
			o = new angluin_simple_table<bool>(NULL, NULL, alphabet_size);
			break;
		case ALG_ANGLUIN_COLUMN:
			o = new angluin_col_table<bool>(NULL, NULL, alphabet_size);
			break;
		case ALG_NL_STAR:
			o = new NLstar_table<bool>(NULL, NULL, alphabet_size);
			break;
		case ALG_BIERMANN:
			o = new MiniSat_biermann<bool>(NULL, NULL, alphabet_size);
			break;
		case ALG_RPNI:
			o = new RPNI<bool>(NULL, NULL, alphabet_size);
			break;
		case ALG_DELETE2:
			o = new DeLeTe2<bool>(NULL, NULL, alphabet_size);
			break;
		case ALG_BIERMANN_ORIGINAL:
			o = new original_biermann<bool>(NULL, NULL, alphabet_size, 1);
			break;
		case ALG_KEARNS_VAZIRANI:
			o = new kearns_vazirani<bool>(NULL, NULL, alphabet_size);
			break;
		case ALG_RIVEST_SCHAPIRE:
			o = new rivest_schapire_table<bool>(NULL, NULL, alphabet_size);
			break;
	}
}}};

co_learning_algorithm::~co_learning_algorithm()
{{{
	if(referenced_knowledgebase != -1)
		this->sv->objects[referenced_knowledgebase]->deref_learning_algorithm(this->id);
	if(referenced_logger != -1)
		this->sv->objects[referenced_logger]->deref_learning_algorithm(this->id);
	if(referenced_normalizer != -1)
		this->sv->objects[referenced_normalizer]->deref_learning_algorithm(this->id);

	if(o) {
		delete o;
	}
}}};

bool co_learning_algorithm::handle_command(int command, basic_string<int32_t> & command_data)
{{{
	conjecture * cj;
	basic_string<int32_t> serial;
	serial_stretch cd(command_data);
	string s;
	list<int> word;
	int i;

	switch(command) {
		case LEARNING_ALGORITHM_SERIALIZE:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			serial = o->serialize();
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_raw_blob(serial);
		case LEARNING_ALGORITHM_DESERIALIZE:
			if(!o->deserialize(cd))
				return this->sv->send_errno(ERR_BAD_PARAMETERS);
			if(!cd.empty())
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_TO_STRING:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			s = o->to_string();
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_string(s.c_str());
		case LEARNING_ALGORITHM_DESERIALIZE_MAGIC:
			if(cd.empty()) // at least expect size
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			++cd; // eat superfluous size.
			if(!o->deserialize_magic(cd, serial))
				return this->sv->send_errno(ERR_BAD_PARAMETERS);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			if(!this->sv->client->stream_send_int(serial.size()))
				return false;
			return this->sv->client->stream_send_raw_blob(serial);
		case LEARNING_ALGORITHM_GET_NAME:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_string(o->get_name());
		case LEARNING_ALGORITHM_ASSOCIATE_LOGGER:
			// Checked.
			if(command_data.size() != 1)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			i = ntohl(command_data[0]);
			if(i < 0 || i >= (int)sv->objects.size())
				return this->sv->send_errno(ERR_NO_OBJECT);
			if(this->sv->objects[i]->get_type() != OBJ_LOGGER)
				return this->sv->send_errno(ERR_BAD_OBJECT);

			this->ref_logger(i);
			this->sv->objects[i]->ref_learning_algorithm(this->id);

			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_REMOVE_LOGGER:
			// Checked.
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);

			this->sv->objects[referenced_logger]->deref_learning_algorithm(this->id);
			this->deref_logger(referenced_logger);

			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_SET_KNOWLEDGE_SOURCE:
			if(command_data.size() != 1)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			i = ntohl(command_data[0]);
			if(i < 0 || i >= (int)sv->objects.size())
				return this->sv->send_errno(ERR_NO_OBJECT);
			if(this->sv->objects[i]->get_type() != OBJ_KNOWLEDGEBASE)
				return this->sv->send_errno(ERR_BAD_OBJECT);

			this->ref_knowledgebase(i);
			this->sv->objects[i]->ref_learning_algorithm(this->id);

			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_GET_KNOWLEDGE_SOURCE:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_int(referenced_knowledgebase);
		case LEARNING_ALGORITHM_SET_NORMALIZER:
			if(command_data.size() != 1)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			i = ntohl(command_data[0]);
			if(i < 0 || i >= (int)sv->objects.size())
				return this->sv->send_errno(ERR_NO_OBJECT);
			if(this->sv->objects[i]->get_type() != OBJ_NORMALIZER)
				return this->sv->send_errno(ERR_BAD_OBJECT);

			this->sv->objects[i]->ref_learning_algorithm(this->id);
			this->ref_normalizer(i);

			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_GET_NORMALIZER:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_int(referenced_normalizer);
		case LEARNING_ALGORITHM_UNSET_NORMALIZER:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			this->sv->objects[referenced_normalizer]->deref_learning_algorithm(this->id);
			this->deref_normalizer(referenced_normalizer);
			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_GET_MEMORY_STATISTICS:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			serial = this->o->get_memory_statistics().serialize();
			return this->sv->client->stream_send_raw_blob(serial);
		case LEARNING_ALGORITHM_GET_TIMING_STATISTICS:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			serial = this->o->get_timing_statistics().serialize();
			return this->sv->client->stream_send_raw_blob(serial);
		case LEARNING_ALGORITHM_ENABLE_TIMING:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			o->enable_timing();
			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_DISABLE_TIMING:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			o->disable_timing();
			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_RESET_TIMING:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			o->reset_timing();
			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_GET_ALPHABET_SIZE:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_int(o->get_alphabet_size());
		case LEARNING_ALGORITHM_INCREASE_ALPHABET_SIZE:
			if(command_data.size() != 1)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			i = ntohl(command_data[0]);
			if(i < 1)
				return this->sv->send_errno(ERR_BAD_PARAMETERS);
			o->increase_alphabet_size(i);
			return this->sv->send_errno(ERR_SUCCESS);
		case LEARNING_ALGORITHM_CONJECTURE_READY:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_int(o->conjecture_ready() ? 1 : 0);
		case LEARNING_ALGORITHM_ADVANCE:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;

			cj = o->advance();

			if(cj == NULL) {
				return this->sv->client->stream_send_int(0);
			} else {
				if(!this->sv->client->stream_send_int(1))
					return false;
				if(!this->sv->client->stream_send_int( (int) cj->get_type() ))
					return false;

				serial = cj->serialize();
				delete cj;
				return this->sv->client->stream_send_raw_blob(serial);
			}
		case LEARNING_ALGORITHM_ADD_COUNTEREXAMPLE:
			if(!::deserialize(word, cd))
				return this->sv->send_errno(ERR_BAD_PARAMETERS);
			if(!cd.empty())
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(o->add_counterexample(word))
				return this->sv->send_errno(ERR_SUCCESS);
			else
				return this->sv->send_errno(ERR_COMMAND_FAILED);
		case LEARNING_ALGORITHM_SUPPORTS_SYNC:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(!this->sv->send_errno(ERR_SUCCESS))
				return false;
			return this->sv->client->stream_send_int(o->supports_sync() ? 1 : 0);
		case LEARNING_ALGORITHM_SYNC_TO_KNOWLEDGEBASE:
			if(command_data.size() != 0)
				return this->sv->send_errno(ERR_BAD_PARAMETER_COUNT);
			if(o->sync_to_knowledgebase())
				return this->sv->send_errno(ERR_SUCCESS);
			else
				return this->sv->send_errno(ERR_COMMAND_FAILED);
		default:
			return this->sv->send_errno(ERR_BAD_COMMAND);
	}

	return false;
}}};

void co_learning_algorithm::ref_knowledgebase(int oid)
{{{
	if(referenced_knowledgebase != -1) {
		// deref former knowledgebase
		this->sv->objects[referenced_knowledgebase]->deref_learning_algorithm(this->id);
		this->deref_learning_algorithm(referenced_knowledgebase);
	}

	referenced_knowledgebase = oid;
	this->o->set_knowledge_source( ( dynamic_cast<co_knowledgebase*>(this->sv->objects[oid]) )->o );
}}};

void co_learning_algorithm::deref_knowledgebase(int __attribute__ ((__unused__)) oid)
{{{
	referenced_knowledgebase = -1;
	if(o)
		o->set_knowledge_source(NULL);
}}};

void co_learning_algorithm::ref_logger(int oid)
{{{
	if(referenced_logger != -1) {
		// deref former logger
		this->sv->objects[referenced_logger]->deref_learning_algorithm(this->id);
		this->deref_logger(referenced_logger);
	}

	referenced_logger = oid;
	this->o->set_logger( ( dynamic_cast<co_logger*>(this->sv->objects[oid]) )->o );
}}};

void co_learning_algorithm::deref_logger(int __attribute__ ((__unused__)) oid)
{{{
	referenced_logger = -1;
	if(o)
		o->set_logger(NULL);
}}};

void co_learning_algorithm::ref_normalizer(int oid)
{{{
	if(referenced_normalizer != -1) {
		// deref former normalizer
		this->sv->objects[referenced_normalizer]->deref_learning_algorithm(this->id);
		this->deref_normalizer(referenced_normalizer);
	}

	referenced_normalizer = oid;
	this->o->set_normalizer( ( dynamic_cast<co_normalizer*>(this->sv->objects[oid]) )->o );
}}};

void co_learning_algorithm::deref_normalizer(int __attribute__ ((__unused__)) oid)
{{{
	referenced_normalizer = -1;
	if(o)
		o->unset_normalizer();
}}};

