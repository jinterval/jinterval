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
package net.java.jinterval.field;

import java.math.RoundingMode;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.ExtendedRationalContext;
import org.apache.commons.math3.Field;

/**
 *
 */
public class RationalField implements Field<RationalFieldElement> {

    private ExtendedRationalContext context;
    private final RationalFieldElement zero;
    private final RationalFieldElement one;

    public RationalField(RoundingMode rm) {
        this(BinaryValueSet.BINARY64, rm);
    }

    public RationalField(BinaryValueSet valueSet, RoundingMode rm) {
        this(ExtendedRationalContexts.valueOf(valueSet, rm));
    }

    public RationalField(ExtendedRationalContext context) {
        this.context = context;
        zero = get(ExtendedRational.zero());
        one = get(ExtendedRational.one());
    }

    public RationalFieldElement getZero() {
        return zero;
    }

    public RationalFieldElement getOne() {
        return one;
    }

    public RationalFieldElement get(Number value) {
        return new RationalFieldElement(this, context.rnd(value));
    }

    public RationalFieldElement get(ExtendedRational value) {
        return new RationalFieldElement(this, context.rnd(value));
    }

    public Class<RationalFieldElement> getRuntimeClass() {
        return RationalFieldElement.class;
    }

    ExtendedRationalContext getContext() {
        return context;
    }
}
