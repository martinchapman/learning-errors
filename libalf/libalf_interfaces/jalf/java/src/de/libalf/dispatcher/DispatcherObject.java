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

import de.libalf.AlfException;
import de.libalf.LibALFObject;

/**
 * TODO: check the following text
 * <p>
 * Root of all classes representing the JNI LibALF C++ objects.
 * </p>
 * <p>
 * Each <code>JNIObject</code> stores a 64 bit variable (a <em>pointer</em>)
 * that points to memory location of the C++ object. Each <code>native</code>
 * method call on C++ objects via the JNI interface has to provide a pointer to
 * locate the object.<br>
 * The 64 bit variable allows the memory access on both 32 bit and 64 bit
 * systems.
 * </p>
 * <p>
 * This class is only the root class and should not be initialized. Each
 * subclass has to provide an <code>init</code> method that initializes a C++
 * object via the JNI interface and returns the memory address of the object.
 * This initialization can be performed in the constructor of the subclass.
 * </p>
 * 
 * @author Daniel Neider (<a
 *         href="mailto:neider@automata.rwth-aachen.de">neider@automata.
 *         rwth-aachen.de</a>), Chair of Computer Science 7, RWTH Aachen
 *         University
 * @author Stefan Schulz
 * @version 1.0
 */
public abstract class DispatcherObject implements LibALFObject, Sendable {
	private static final long serialVersionUID = 1L;

	/**
	 * Stores the reference of the dispatcher object id.
	 */
	transient private int id;

	/**
	 * Object's factory.
	 */
	protected final DispatcherFactory factory;

	private final DispatcherConstants objType;

	protected DispatcherObject(DispatcherFactory factory, DispatcherConstants objType) throws DispatcherProtocolException {
		this.factory = factory;
		this.objType = objType;
	}

	protected void useID(int id) throws DispatcherProtocolException {
		this.id = id;
		if (id < 0)
			throw new DispatcherProtocolException("Negative object identifier!");
	}

	protected void create(int[] data) throws DispatcherProtocolException {
		synchronized (this.factory) {
			this.factory.writeCommandThrowing(DispatcherConstants.CLCMD_CREATE_OBJECT, this.objType, data);
			useID(this.factory.readInt());
		}
	}

	protected void create() throws DispatcherProtocolException {
		create(new int[0]);
	}

	@Override
	public int getInt() {
		return this.id;
	}

	@Override
	public String getVersion() {
		checkDestroyed();
		return this.factory.getVersion();
	}

	@Override
	protected void finalize() throws Throwable {
		destroy();
		super.finalize();
	}

	@Override
	public void destroy() throws AlfException {
		synchronized (this.factory) {
			if (isDestroyed())
				return;

			this.factory.writeCommandThrowing(DispatcherConstants.CLCMD_DELETE_OBJECT, this);
			this.id = -1;
		}
	}

	@Override
	public boolean isDestroyed() {
		return this.id < 0 || this.factory.isDestroyed();
	}

	protected void checkDestroyed() throws DispatcherObjectDestroyedException {
		if (isDestroyed())
			throw new DispatcherObjectDestroyedException("Object has been destroyed.");
	}

	protected void checkFactory(LibALFObject obj) {
		if (!obj.isDestroyed() && obj instanceof DispatcherObject && ((DispatcherObject) obj).factory == this.factory)
			return;
		throw new IllegalArgumentException("object has to be from the same factory!");
	}

	public DispatcherConstants getObjType() {
		return this.objType;
	}

	void checkObjType() {
		synchronized (this.factory) {
			this.factory.writeCommandThrowing(DispatcherConstants.CLCMD_GET_OBJECTTYPE, this);
			if (this.objType.getInt() != this.factory.readInt())
				throw new DispatcherProtocolException("object type mismatch");
		}
	}

	@Override
	public String toString() {
		return super.toString() + "[type=" + this.objType + ", id=" + this.id + "]";
	}

	@Override
	public DispatcherFactory getFactory() {
		return this.factory;
	}
}
