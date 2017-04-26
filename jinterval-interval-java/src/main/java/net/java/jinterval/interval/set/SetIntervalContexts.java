/*
 * Copyright (c) 2012, JInterval Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. * Redistributions in
 * binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
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
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.interval.set;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;

/**
 *
 */
public class SetIntervalContexts {

    public static SetIntervalContext getDefault() {
        return getAccur64();
    }

    public static SetIntervalContext getExact() {
        ExtendedRationalContext mc = ExtendedRationalContexts.exact();
        return new SetIntervalContextInfSup(mc, mc) {
            @Override
            public SetInterval hull(SetInterval x) {
                return x;
            }
        };
    }

    public static SetIntervalContext getTightestSlow(BinaryValueSet valueSet) {
        final ExtendedRationalContext mcInf = ExtendedRationalContexts.mkFloor(valueSet);
        final ExtendedRationalContext mcSup = ExtendedRationalContexts.mkCeiling(valueSet);
        return new SetIntervalContextInfSupBase(mcInf, mcSup);
    }

    public static SetIntervalContext getTightest(BinaryValueSet valueSet) {
        final ExtendedRationalContext mcInf = ExtendedRationalContexts.mkFloor(valueSet);
        final ExtendedRationalContext mcSup = ExtendedRationalContexts.mkCeiling(valueSet);
        return new SetIntervalContextInfSup(mcInf, mcSup);
    }

    public static SetIntervalContext getTightest64() {
        return getTightest(BinaryValueSet.BINARY64);
    }

    public static SetIntervalContext getAccur64() {
        return new SetIntervalContextAccur64();
    }

    public static SetIntervalContext getDoubleNearest() {
        return new SetIntervalContextNearest();
    }

    public static SetIntervalContext getPlain() {
        return new SetIntervalContextPlain();
    }

    public static SetIntervalContext forceCommon(SetIntervalContext ic) {
        return new SetIntervalContextForceCommon(ic);
    }

    public static SetIntervalContext decorate(SetIntervalContext ic) {
        return new SetIntervalContextDecorated(ic);
    }

    public static SetInterval[] evaluateSetInterval(SetIntervalContext ic, CodeList cl, SetInterval[] args, Expression... results) {
        SetIntervalEvaluator ev = SetIntervalEvaluator.create(ic, cl, results);
        return ev.evaluate(args);
    }

    @Deprecated
    public static SetIntervalContext getInfSupBase(BinaryValueSet valueSet) {
        return getTightestSlow(valueSet);
    }

    @Deprecated
    public static SetIntervalContext getInfSup(BinaryValueSet valueSet) {
        return getTightest(valueSet);
    }

    @Deprecated
    public static SetIntervalContext getFast() {
        return getPlain();
    }

}
