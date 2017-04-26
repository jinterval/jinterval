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
package net.java.jinterval.rational;

import java.math.RoundingMode;
import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;

/**
 *
 */
public class ExtendedRationalContexts {

    public static ExtendedRationalContext valueOf(BinaryValueSet valueSet, RoundingMode rm) {
        return new RationalContextBinary(valueSet.getMathContext(rm));
    }

    public static ExtendedRationalContext mkFloor(BinaryValueSet valueSet) {
        return new RationalContextBinary(valueSet.roundFloor());
    }

    public static ExtendedRationalContext mkCeiling(BinaryValueSet valueSet) {
        return new RationalContextBinary(valueSet.roundCeiling());
    }

    public static ExtendedRationalContext mkNearest(BinaryValueSet valueSet) {
        return new RationalContextBinary(valueSet.roundNearest());
    }

    public static ExtendedRationalContext exact() {
        return new RationalContextExact();
    }

    public static ExtendedRational[] evaluateRational(ExtendedRationalContext rc, CodeList cl, ExtendedRational[] args, Expression... results) {
        if (args.length != cl.getNumInps()) {
            throw new IllegalArgumentException();
        }
        RationalEvaluator ev = new RationalEvaluator(rc, cl);
        System.arraycopy(args, 0, ev.values, 0, cl.getNumInps());
        cl.acceptConstants(ev);
        cl.acceptForward(ev);
        ExtendedRational[] ret = new ExtendedRational[results.length];
        for (int i = 0; i < results.length; i++) {
            ret[i] = ev.values[results[i].getIndex()];
        }
        return ret;
    }
}
