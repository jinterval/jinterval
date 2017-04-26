/*
 * Copyright (c) 2012, JInterval Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.p1788.bridj;

import org.bridj.Pointer;
import org.bridj.StructObject;
import org.bridj.ann.Field;

/**
 * BridJ wrapper of DECORATED_INFSUP_B64 structure
 */
public class DECORATED_INFSUP_B64 extends StructObject {

    public DECORATED_INFSUP_B64() {
        super();
    }

    public DECORATED_INFSUP_B64(Pointer pointer) {
        super(pointer);
    }

    @Field(0)
    public double inf() {
        return io.getDoubleField(this, 0);
    }

    @Field(0)
    public DECORATED_INFSUP_B64 inf(double inf) {
        io.setDoubleField(this, 0, inf);
        return this;
    }

    @Field(1)
    public double sup() {
        return io.getDoubleField(this, 1);
    }

    @Field(1)
    public DECORATED_INFSUP_B64 sup(double sup) {
        io.setDoubleField(this, 1, sup);
        return this;
    }

    @Field(2)
    public byte decoration() {
        return io.getByteField(this, 2);
    }

    @Field(2)
    public DECORATED_INFSUP_B64 decoration(byte decoration) {
        io.setByteField(this, 2, decoration);
        return this;
    }
}
