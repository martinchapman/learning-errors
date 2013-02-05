/*
 * This file is part of libalf. libalf is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version. libalf is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details. You should have received a
 * copy of the GNU Lesser General Public License along with libalf. If not, see
 * <http://www.gnu.org/licenses/>. (c) 2009 Lehrstuhl Softwaremodellierung und
 * Verifikation (I2), RWTH Aachen University and Lehrstuhl Logik und Theorie
 * diskreter Systeme (I7), RWTH Aachen University Author: Stefan Schulz
 */

package de.libalf.dispatcher;

import de.libalf.Knowledgebase.Acceptance;
import de.libalf.Logger.LoggerLevel;

enum DispatcherConstants implements Sendable {
	// enum command_error_code
	ERR_SUCCESS(0),
	ERR_NO_OBJECT(1),
	ERR_BAD_OBJECT(2),
	ERR_BAD_OBJECT_STATE(3),

	ERR_BAD_COMMAND(10),
	ERR_NOT_IMPLEMENTED(11),

	ERR_BAD_PARAMETER_COUNT(15),
	ERR_BAD_PARAMETERS(16),

	ERR_COMMAND_FAILED(20),

	ERR_UNRESOLVED_REFERENCES_REMOVED(40),
	ERR_REMAINING_OBJECTS(41),

	ERR_AUTHENTICATION_REQUIRED(100),
	ERR_AUTHENTICATION_FAILED(101),

	ERR_TLS_REQUIRED(110),

	ERR_OUT_OF_MEM(1000),
	ERR_INTERNAL_ERROR(1001),

	// enum client_command
	CLCMD_REQ_CAPA(0),
	CLCMD_REQ_VERSION(1),

	CLCMD_DISCONNECT(10),
	CLCMD_STARTTLS(11),
	CLCMD_AUTH(12),

	CLCMD_CREATE_OBJECT(20),
	CLCMD_DELETE_OBJECT(21),
	CLCMD_GET_OBJECTTYPE(22),
	CLCMD_OBJECT_COMMAND(23),
	CLCMD_COUNT_DISPATCHER_REFERENCES(30),
	/*
	 * CLCMD_ENABLE_CLIENT_REFERENCING(35),
	 * CLCMD_DISABLE_CLIENT_REFERENCING(36), CLCMD_COUNT_CLIENT_REFERENCES(37),
	 * CLCMD_INCREASE_CLIENT_REFERENCES(38),
	 * CLCMD_DECREASE_CLIENT_REFERENCES(39),
	 */

	CLCMD_HELLO_CARSTEN(99),

	// reserved for extensions: >= 1000

	// enum object_type
	OBJ_NONE(-1),
	OBJ_LOGGER(0),
	OBJ_KNOWLEDGEBASE(10),
	OBJ_KNOWLEDGEBASE_ITERATOR(11),
	OBJ_LEARNING_ALGORITHM(20),
	OBJ_NORMALIZER(30),

	// enum logger_command
	LOGGER_RECEIVE_AND_FLUSH(0),
	LOGGER_SET_MIN_LOGLEVEL(1),
	LOGGER_LOG_ALGORITHM(2),
	LOGGER_NOT_LOG_ALGORITHM(3),

	// enum knowledgebase_command
	KNOWLEDGEBASE_SERIALIZE(0),
	KNOWLEDGEBASE_DESERIALIZE(1),
	KNOWLEDGEBASE_ASSIGN(2),

	KNOWLEDGEBASE_TO_DOTFILE(5),
	KNOWLEDGEBASE_TO_STRING(6),

	KNOWLEDGEBASE_IS_ANSWERED(10),
	KNOWLEDGEBASE_IS_EMPTY(11),
	KNOWLEDGEBASE_GET_ALPHABET_SIZE(12),
	KNOWLEDGEBASE_COUNT_QUERIES(13),
	KNOWLEDGEBASE_COUNT_ANSWERS(14),
	KNOWLEDGEBASE_COUNT_RESOLVED_QUERIES(15),
	KNOWLEDGEBASE_GET_MEMORY_USAGE(16),

	KNOWLEDGEBASE_RESOLVE_QUERY(20),
	KNOWLEDGEBASE_RESOLVE_OR_ADD_QUERY(21),
	KNOWLEDGEBASE_ADD_KNOWLEDGE(22),

	KNOWLEDGEBASE_GET_QUERY_TREE(25),
	KNOWLEDGEBASE_MERGE_TREE(26),
	KNOWLEDGEBASE_DESERIALIZE_QUERY_ACCEPTANCES(27),
	KNOWLEDGEBASE_SERIALIZE_QUERIES(28),
	KNOWLEDGEBASE_SERIALIZE_KNOWLEDGE(29),

	// iterator:
	KNOWLEDGEBASE_BEGIN(30),
	KNOWLEDGEBASE_END(31),
	KNOWLEDGEBASE_QBEGIN(32),
	KNOWLEDGEBASE_QEND(33),

	KNOWLEDGEBASE_CLEAR(40),
	KNOWLEDGEBASE_CLEAR_QUERIES(41),

	KNOWLEDGEBASE_UNDO(50),

	// enum knowledgebase_iterator_command
	KITERATOR_IS_VALID(0),
	KITERATOR_ASSIGN(1),
	KITERATOR_COMPARE(2),

	KITERATOR_IS_ANSWERED(10),
	KITERATOR_IS_REQUIRED(11),

	KITERATOR_GET_WORD(20),
	KITERATOR_GET_ANSWER(21),

	KITERATOR_NEXT(30),
	KITERATOR_ANSWER(31),

	// enum algorithm_command
	LEARNING_ALGORITHM_SERIALIZE(0),
	LEARNING_ALGORITHM_DESERIALIZE(1),
	LEARNING_ALGORITHM_TO_STRING(2),
	LEARNING_ALGORITHM_DESERIALIZE_MAGIC(3),
	LEARNING_ALGORITHM_GET_NAME(4),

	LEARNING_ALGORITHM_ASSOCIATE_LOGGER(10),
	LEARNING_ALGORITHM_REMOVE_LOGGER(11),
	LEARNING_ALGORITHM_SET_KNOWLEDGE_SOURCE(12),
	LEARNING_ALGORITHM_GET_KNOWLEDGE_SOURCE(13),
	LEARNING_ALGORITHM_SET_NORMALIZER(14),
	LEARNING_ALGORITHM_GET_NORMALIZER(15),
	LEARNING_ALGORITHM_UNSET_NORMALIZER(16),

	LEARNING_ALGORITHM_GET_MEMORY_STATISTICS(20),
	LEARNING_ALGORITHM_GET_TIMING_STATISTICS(21),
	LEARNING_ALGORITHM_ENABLE_TIMING(22),
	LEARNING_ALGORITHM_DISABLE_TIMING(23),
	LEARNING_ALGORITHM_RESET_TIMING(24),

	LEARNING_ALGORITHM_GET_ALPHABET_SIZE(30),
	LEARNING_ALGORITHM_INCREASE_ALPHABET_SIZE(31),

	LEARNING_ALGORITHM_CONJECTURE_READY(40),
	LEARNING_ALGORITHM_ADVANCE(41),
	LEARNING_ALGORITHM_ADD_COUNTEREXAMPLE(42),

	LEARNING_ALGORITHM_SUPPORTS_SYNC(50),
	LEARNING_ALGORITHM_SYNC_TO_KNOWLEDGEBASE(51),

	// enum normalizer_command
	NORMALIZER_SERIALIZE(0),
	NORMALIZER_DESERIALIZE(1),
	NORMALIZER_DESERIALIZE_EXTENSION(2),

	NORMALIZER_GET_TYPE(10),

	NORMALIZER_NORMALIZE_A_WORD_PNF(20),
	NORMALIZER_NORMALIZE_A_WORD_SNF(21),

	// enum algorithm
	ALG_ANGLUIN(1),
	ALG_ANGLUIN_COLUMN(2),
	ALG_RIVEST_SCHAPIRE(3),
	ALG_NL_STAR(4),

	ALG_BIERMANN(6),
	ALG_RPNI(7),
	ALG_DELETE2(8),
	ALG_BIERMANN_ORIGINAL(9),
	ALG_KEARNS_VAZIRANI(10),

	// enum acceptance
	ACCEPTANCE_REJECT(0),
	ACCEPTANCE_UNKNOWN(1),
	ACCEPTANCE_ACCEPT(2),

	// enum conjecture_type
	CONJECTURE_FINITE_AUTOMATON(4),

	// enum normalizer_type
	NORMALIZER_MSC(1),

	// enum logger_loglevel
	LOGGER_ERROR(1),
	LOGGER_WARN(2),
	LOGGER_INFO(3),
	LOGGER_DEBUG(4),

	;

	@SuppressWarnings("deprecation")
	static DispatcherConstants convertAcceptance(Acceptance a) {
		switch (a) {
		case REJECT:
			return ACCEPTANCE_REJECT;
		case DONTCARE:
			return ACCEPTANCE_UNKNOWN;
		case ACCEPT:
			return ACCEPTANCE_ACCEPT;
		default:
			return null;
		}
	}

	static DispatcherConstants convertLoggerLevel(LoggerLevel level) {
		switch (level) {
		case LOGGER_ERROR:
			return LOGGER_ERROR;
		case LOGGER_WARN:
			return LOGGER_WARN;
		case LOGGER_INFO:
			return LOGGER_INFO;
		case LOGGER_DEBUG:
			return LOGGER_DEBUG;
		default:
			return null;
		}
	}

	static final int DISPATCHER_PROTOCOL_VERSION = 1;

	static final int DISPATCHER_DEFAULT_PORT = 24940;

	final int id;

	private DispatcherConstants(int id) {
		this.id = id;
	}

	@Override
	public int getInt() {
		return this.id;
	}

	static DispatcherConstants getConjectureType(int conType) {
		for (DispatcherConstants c : DispatcherConstants.values())
			if (c.id == conType && c.name().startsWith("CONJECTURE_"))
				return c;
		return null;
	}
}
