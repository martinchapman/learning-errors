/*
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
 * (c) 2009 Lehrstuhl Softwaremodellierung und Verifikation (I2), RWTH Aachen University
 *           and Lehrstuhl Logik und Theorie diskreter Systeme (I7), RWTH Aachen University
 * Author: Stefan Schulz
 *
 */

package de.libalf.dispatcher;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.LinkedList;

import de.libalf.AlfException;
import de.libalf.Knowledgebase;

public class DispatcherKnowledgebase extends DispatcherObject implements Knowledgebase {
	private static final long serialVersionUID = 1L;

	public DispatcherKnowledgebase(DispatcherFactory factory) throws AlfException {
		super(factory, DispatcherConstants.OBJ_KNOWLEDGEBASE);
		create();
	}

	@Override
	public boolean add_knowledge(int[] word, boolean acceptance) throws AlfException {
		return add_knowledge(word, acceptance ? Acceptance.ACCEPT : Acceptance.REJECT);
	}

	public boolean add_knowledge(int[] word, Acceptance acceptance) throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_ADD_KNOWLEDGE, word, DispatcherConstants.convertAcceptance(acceptance));
			return this.factory.readBool();
		}
	}

	@Override
	public void clear() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_CLEAR);
		}
	}

	@Override
	public void clear_queries() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_CLEAR_QUERIES);
		}
	}

	@Override
	public int count_answers() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_COUNT_ANSWERS);
			return this.factory.readInt();
		}
	}

	@Override
	public int count_queries() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_COUNT_QUERIES);
			return this.factory.readInt();
		}
	}

	@Override
	public boolean deserialize(int[] serialization) throws AlfException {
		synchronized (this.factory) {
			try {
				this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_DESERIALIZE, serialization);
				return true;
			} catch (DispatcherCommandError e) {
				return false;
			}
		}
	}

	@Override
	public String generate_dotfile() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_TO_DOTFILE);
			return this.factory.readString();
		}
	}

	@Override
	public int get_memory_usage() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_GET_MEMORY_USAGE);
			return this.factory.readInt();
		}
	}

	@SuppressWarnings("serial")
	private static class DispatcherKnowledgebaseIterator extends DispatcherObject {
		DispatcherKnowledgebaseIterator(DispatcherFactory factory, int id) {
			super(factory, DispatcherConstants.OBJ_KNOWLEDGEBASE_ITERATOR);
			useID(id);
		}
	}

	@Deprecated
	public LinkedList<int[]> get_knowledge_old() throws AlfException {
		synchronized (this.factory) {
			return iterateToList(dispatchBegin(this), dispatchEnd(this));
		}
	}

	@Override
	public LinkedList<int[]> get_knowledge() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_SERIALIZE_KNOWLEDGE);

			LinkedList<int[]> list = new LinkedList<int[]>();
			try {
				while (true)
					list.add(this.factory.readInts());
			} catch (NegativeArraySizeException e) {}

			return list;
		}
	}

	@Override
	public void deserialize_query_acceptance(boolean[] acceptances) throws AlfException {
		synchronized (this.factory) {
			int i = acceptances.length;
			int[] is = new int[i];
			while (i-- > 0)
				is[i] = DispatcherConstants.convertAcceptance(acceptances[i] ? Acceptance.ACCEPT : Acceptance.REJECT).id;
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_DESERIALIZE_QUERY_ACCEPTANCES, is);
		}
	}

	@Deprecated
	public LinkedList<int[]> get_queries_old() throws AlfException {
		synchronized (this.factory) {
			return iterateToList(dispatchQBegin(this), dispatchQEnd(this));
		}
	}

	@Override
	public LinkedList<int[]> get_queries() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_SERIALIZE_QUERIES);

			LinkedList<int[]> list = new LinkedList<int[]>();
			try {
				while (true)
					list.add(this.factory.readInts());
			} catch (NegativeArraySizeException e) {}

			return list;
		}
	}

	private LinkedList<int[]> iterateToList(DispatcherKnowledgebaseIterator begin, DispatcherKnowledgebaseIterator end) {
		LinkedList<int[]> list = new LinkedList<int[]>();
		while (!dispatchIteratorCompare(begin, end)) {
			list.add(dispatchIteratorGetWord(begin));
			dispatchIteratorNext(begin);
		}
		begin.destroy();
		end.destroy();
		return list;
	}

	private boolean dispatchIteratorCompare(DispatcherKnowledgebaseIterator obj1, DispatcherKnowledgebaseIterator obj2) {
		this.factory.writeObjectCommandThrowing(obj1, DispatcherConstants.KITERATOR_COMPARE, obj2);
		return this.factory.readBool();
	}

	private void dispatchIteratorNext(DispatcherKnowledgebaseIterator obj) {
		this.factory.writeObjectCommandThrowing(obj, DispatcherConstants.KITERATOR_NEXT);
	}

	private int[] dispatchIteratorGetWord(DispatcherKnowledgebaseIterator obj) {
		this.factory.writeObjectCommandThrowing(obj, DispatcherConstants.KITERATOR_GET_WORD);
		return this.factory.readInts();
	}

	private DispatcherKnowledgebaseIterator dispatchBegin(DispatcherKnowledgebase obj) {
		this.factory.writeObjectCommandThrowing(obj, DispatcherConstants.KNOWLEDGEBASE_BEGIN);
		return new DispatcherKnowledgebaseIterator(this.factory, this.factory.readInt());
	}

	private DispatcherKnowledgebaseIterator dispatchEnd(DispatcherKnowledgebase obj) {
		this.factory.writeObjectCommandThrowing(obj, DispatcherConstants.KNOWLEDGEBASE_END);
		return new DispatcherKnowledgebaseIterator(this.factory, this.factory.readInt());
	}

	private DispatcherKnowledgebaseIterator dispatchQBegin(DispatcherKnowledgebase obj) {
		this.factory.writeObjectCommandThrowing(obj, DispatcherConstants.KNOWLEDGEBASE_QBEGIN);
		return new DispatcherKnowledgebaseIterator(this.factory, this.factory.readInt());
	}

	private DispatcherKnowledgebaseIterator dispatchQEnd(DispatcherKnowledgebase obj) {
		this.factory.writeObjectCommandThrowing(obj, DispatcherConstants.KNOWLEDGEBASE_QEND);
		return new DispatcherKnowledgebaseIterator(this.factory, this.factory.readInt());
	}

	@Override
	public boolean is_answered() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_IS_ANSWERED);
			return this.factory.readBool();
		}
	}

	@Override
	public boolean is_empty() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_IS_EMPTY);
			return this.factory.readBool();
		}
	}

	@Override
	public Acceptance resolve_or_add_query(int[] word) throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_RESOLVE_OR_ADD_QUERY, word);
			return this.factory.readAcceptance();
		}
	}

	@Override
	public Acceptance resolve_query(int[] word) throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_RESOLVE_QUERY, word);
			return this.factory.readAcceptance();
		}
	}

	@Override
	public int[] serialize() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_SERIALIZE);
			return this.factory.readInts();
		}
	}

	@Override
	public boolean undo(int count) throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_UNDO, count);
			return this.factory.readBool();
		}
	}

	@Override
	public String toString() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_TO_STRING);
			return this.factory.readString();
		}
	}

	public String toDot() throws AlfException {
		synchronized (this.factory) {
			this.factory.writeObjectCommandThrowing(this, DispatcherConstants.KNOWLEDGEBASE_TO_DOTFILE);
			return this.factory.readString();
		}
	}

	/**
	 * @see Serializable
	 */
	private void writeObject(ObjectOutputStream out) throws IOException {
		out.defaultWriteObject();
		out.writeObject(serialize());
	}

	/**
	 * @see Serializable
	 */
	private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		in.defaultReadObject();
		create();
		deserialize((int[]) in.readObject());
	}
}
