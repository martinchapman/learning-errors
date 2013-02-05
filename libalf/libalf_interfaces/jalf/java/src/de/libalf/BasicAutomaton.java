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
 * Author: Daniel Neider <neider@automata.rwth-aachen.de>
 *
 */

package de.libalf;

import java.util.HashSet;
import java.util.LinkedList;

/**
 * <p>
 * Represents a deterministic or nondeterministic finite automaton as it is
 * generated by the LibALF library.
 * </p>
 * <p>
 * A LibALF automaton consists of:
 * <ul>
 * <li>A set of <em>states</em>, represented by the <code>integers</code>
 * between <code>0</code> and <code>numberOfStates</code>.</li>
 * <li>An <em>alphabet</em> over which the automaton works. An alphabet is the
 * set of all <code>integers</code> between <code>0</code> and
 * <code>alphabetSize</code> .</li>
 * <li>A set of <em>initial states</em>.</li>
 * <li>A set of <em>final states</em>.</li>
 * </ul>
 * Make sure that both <code>numberOfStates</code> and <code>alphabetSize</code>
 * are <code>integers</code> greater than 0.
 * </p>
 * 
 * <p>
 * Note that this class does only store the automaton, but provides no
 * functionality. <code>BasicAutomaton</code> objects are created by the LibALF
 * C++ library via the JNI interface. To work with this automaton, one has to
 * implement the required operations (e.g. simulating runs on words, Boolean
 * operations etc.) or needs to convert it into an existing automaton library
 * (e.g. the <a href="http://www.brics.dk/automaton/">brics library</a>).
 * </p>
 * 
 * @author Daniel Neider (<a
 *         href="mailto:neider@automata.rwth-aachen.de">neider@automata.
 *         rwth-aachen.de</a>), Chair of Computer Science 7, RWTH Aachen
 *         University
 * @version 0.1
 * 
 */
public class BasicAutomaton implements Conjecture {
	private static final long serialVersionUID = 1L;

	/**
	 * Is this object representing a deterministic finite automaton?
	 */
	private boolean isDFA;

	/**
	 * The number of states of the automaton.
	 */
	private int numberOfStates;

	/**
	 * The size of the alphabet used by this automaton.
	 */
	private int alphabetSize;

	/**
	 * The set of initial states.
	 */
	private HashSet<Integer> initialStates;

	/**
	 * The set of final states.
	 */
	private HashSet<Integer> finalStates;

	/**
	 * The transitions of the automaton.
	 */
	private LinkedList<BasicTransition> transitions;

	/**
	 * Creates a new nondeterministic finite automaton with the given number of
	 * states and alphabet.
	 * 
	 * @param numberOfStates
	 *            the number of states
	 * @param alphabetSize
	 *            the size of the alphabet
	 */
	public BasicAutomaton(int numberOfStates, int alphabetSize) {
		this(false, numberOfStates, alphabetSize);
	}

	/**
	 * Creates a new finite automaton with the given number of states and
	 * alphabet. The automaton is deterministic or nondeterministic depending on
	 * the <code>isDFA</code> parameter.
	 * 
	 * @param isDFA
	 *            determines if the automaton is deterministic or
	 *            nondeterministic
	 * @param numberOfStates
	 *            the number of states
	 * @param alphabetSize
	 *            the size of the alphabet
	 */
	public BasicAutomaton(boolean isDFA, int numberOfStates, int alphabetSize) {
		this.isDFA = isDFA;
		this.numberOfStates = numberOfStates;
		this.alphabetSize = alphabetSize;
		this.initialStates = new HashSet<Integer>(numberOfStates);
		this.finalStates = new HashSet<Integer>(numberOfStates);
		this.transitions = new LinkedList<BasicTransition>();
	}

	/**
	 * Returns whether the automaton is deterministic or nondeterministic.
	 * 
	 * @return whether the automaton is deterministic or nondeterministic.
	 */
	public boolean isDFA() {
		return this.isDFA;
	}

	/**
	 * Returns the number of states of the automaton.
	 * 
	 * @return the number of states of the automaton.
	 */
	public int getNumberOfStates() {
		return this.numberOfStates;
	}

	/**
	 * Returns the size of the alphabet (i.e. the greatest symbol in the
	 * alphabet).
	 * 
	 * @return the size of the alphabet.
	 */
	public int getAlphabetSize() {
		return this.alphabetSize;
	}

	/**
	 * Returns the set of initial states.
	 * 
	 * @return the set of initial states.
	 */
	public HashSet<Integer> getInitialStates() {
		return this.initialStates;
	}

	/**
	 * Adds the given state to the set of initial states. This method does only
	 * allow to add states that are states of the automaton.
	 * 
	 * @param stateToAdd
	 *            the state to add to the set of initial states
	 */
	public void addInitialState(int stateToAdd) {
		if (stateToAdd >= 0 && stateToAdd < this.numberOfStates)
			this.initialStates.add(stateToAdd);
	}

	/**
	 * Removes the given state from the set of initial states.
	 * 
	 * @param stateToRemove
	 *            the state to remove from the set of initial states
	 */
	public void removeInitialState(int stateToRemove) {
		this.initialStates.remove(stateToRemove);
	}

	/**
	 * Returns the automaton's set of final states.
	 * 
	 * @return the automaton's set of final states.
	 */
	public HashSet<Integer> getFinalStates() {
		return this.finalStates;
	}

	/**
	 * Adds the given state to the set of final states. This method does only
	 * allow to add states that are states of the automaton.
	 * 
	 * @param stateToAdd
	 *            the state to add
	 */
	public void addFinalState(int stateToAdd) {
		if (stateToAdd >= 0 && stateToAdd < this.numberOfStates)
			this.finalStates.add(stateToAdd);
	}

	/**
	 * Checks whether the given state is a final state.
	 * 
	 * @param state
	 *            the state to check
	 * @return true if the state is a final state and false otherwise.
	 */
	public boolean isFinalState(int state) {
		return this.finalStates.contains(state);
	}

	/**
	 * Removes a state from the set of final states.
	 * 
	 * @param stateToRemove
	 *            the state to remove
	 */
	public void removeFinalState(int stateToRemove) {
		this.finalStates.remove(stateToRemove);
	}

	/**
	 * Returns the transitions of this automaton.
	 * 
	 * @return the transitions of this automaton.
	 */
	public LinkedList<BasicTransition> getTransitions() {
		return this.transitions;
	}

	/**
	 * Adds a new transition to the automaton. This method does only allow to
	 * add valid transitions, i.e. transitions that are labeled correctly and
	 * where the source and the destination state are states of the automaton.
	 * 
	 * @param transitionToAdd
	 *            the transition to add
	 */
	public void addTransition(BasicTransition transitionToAdd) {
		if ((transitionToAdd.source >= 0 && transitionToAdd.source < this.numberOfStates)
				&& (transitionToAdd.destination >= 0 && transitionToAdd.destination < this.numberOfStates)
				&& (transitionToAdd.label >= 0 && transitionToAdd.label <= this.alphabetSize))
			this.transitions.add(transitionToAdd);
	}

	/**
	 * Removes the given transition from the automaton.
	 * 
	 * @param transitionToRemove
	 *            the transition to remove.
	 */
	public void removeTransition(BasicTransition transitionToRemove) {
		this.transitions.remove(transitionToRemove);
	}

	public String toDot() {
		String lineSeparator = System.getProperty("line.separator");
		String dot = "digraph Automaton {" + lineSeparator;
		dot += "  rankdir = LR;" + lineSeparator;
		for (int i = 0; i < this.numberOfStates; i++)
			dot += "  " + i + " ["
					+ (this.initialStates.contains(i) ? "style=filled," : "")
					+ "shape="
					+ (this.finalStates.contains(i) ? "double" : "")
					+ "circle, label=\"" + i + "\"];" + lineSeparator;
		for (BasicTransition t : this.transitions)
			dot += "  " + t.source + " -> " + t.destination + " [label=\""
					+ t.label + "\"];" + lineSeparator;
		dot += "}";
		return dot;
	}

	@Override
	public String toString() {
		String output = "LibALF automaton Java impementation\nNumber of States: "
				+ this.numberOfStates + "\n";
		output += "Alphabet size: " + this.alphabetSize + "\n";
		output += "Automaton is deterministic: " + this.isDFA + "\n";
		output += "Initial states: " + this.initialStates + "\n";
		output += "Final states: " + this.finalStates + "\n";
		output += "Transitions:" + this.transitions;
		return output;
	}
}
