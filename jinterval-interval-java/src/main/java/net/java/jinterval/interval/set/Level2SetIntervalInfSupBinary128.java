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
package net.java.jinterval.interval.set;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public class Level2SetIntervalInfSupBinary128 extends AbstractLevel2SetInterval<Level2SetIntervalInfSupBinary128> {

    public static final BinaryValueSet numberFormat = BinaryValueSet.BINARY128;
    private static final SetIntervalContext ctx = SetIntervalContexts.getTightest(numberFormat);

    private Level2SetIntervalInfSupBinary128(SetInterval impl) {
        super(impl);
    }

    SetIntervalContext ctx() {
        return ctx;
    }

    Level2SetIntervalInfSupBinary128 valueOf(SetInterval impl) {
        return valueOfImpl(impl);
    }

    private static Level2SetIntervalInfSupBinary128 valueOfImpl(SetInterval impl) {
        return impl.isCommonInterval() ? new Level2SetIntervalInfSupBinary128.Classic((ClassicInterval) impl) : new Level2SetIntervalInfSupBinary128(impl);
    }

    boolean canEqual(AbstractLevel2SetInterval that) {
        return that instanceof Level2SetIntervalInfSupBinary128;
    }

    String getDatatypeName() {
        return "InfSupBinary128";
    }

    public static Level2SetIntervalInfSupBinary128 hull(SetInterval x) {
        return valueOfImpl(ctx.hull(x));
    }

    public static Level2SetIntervalInfSupBinary128 empty() {
        return valueOfImpl(ctx.empty());
    }

    public static Level2SetIntervalInfSupBinary128 entire() {
        return valueOfImpl(ctx.entire());
    }

    public static Level2SetIntervalInfSupBinary128 numsToInterval(ExtendedRational l, ExtendedRational u) {
        return valueOfImpl(ctx.numsToInterval(l, u));
    }

    public static Level2SetIntervalInfSupBinary128 numsToInterval(double l, double u) {
        return valueOfImpl(ctx.numsToInterval(l, u));
    }

    public static Level2SetIntervalInfSupBinary128 numsToInterval(float l, float u) {
        return valueOfImpl(ctx.numsToInterval(l, u));
    }

    public static Level2SetIntervalInfSupBinary128 numsDecToInterval(ExtendedRational l, ExtendedRational u, Decoration decoration) {
        return valueOfImpl(ctx.numsDecToInterval(l, u, decoration));
    }

    public static Level2SetIntervalInfSupBinary128 numsDecToInterval(double l, double u, Decoration decoration) {
        return valueOfImpl(ctx.numsDecToInterval(l, u, decoration));
    }

    public static Level2SetIntervalInfSupBinary128 numsDecToInterval(float l, float u, Decoration decoration) {
        return valueOfImpl(ctx.numsDecToInterval(l, u, decoration));
    }

    private static class Classic extends Level2SetIntervalInfSupBinary128 {

        Classic(SetInterval impl) {
            super(impl);
        }

        @Override
        public Rational inf() {
            return ((ClassicInterval) impl).inf();
        }

        @Override
        public Rational sup() {
            return ((ClassicInterval) impl).sup();
        }

        @Override
        public Rational wid() {
            return ((ClassicInterval) impl).wid();
        }

        @Override
        public Rational rad() {
            return ((ClassicInterval) impl).rad();
        }

        @Override
        public Rational mag() {
            return ((ClassicInterval) impl).mag();
        }

        @Override
        public Rational mig() {
            return ((ClassicInterval) impl).mig();
        }
    }
}
