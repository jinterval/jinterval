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

import java.math.BigInteger;
import java.math.RoundingMode;

/**
 *
 * @author nadezhin
 */
class BinaryValueSet64 extends BinaryValueSet {

    static final int SIGNIFICAND_WIDTH = 53;
    static final int MINEXP = -1022;
    static final int MAXEXP = 1023;
    static final long SIGN_MASK = 0x8000000000000000L;
    static final long EXP_BIT_MASK = 0x7FF0000000000000L;
    static final long SIGNIF_BIT_MASK = 0x000FFFFFFFFFFFFFL;

    BinaryValueSet64() {
        super(SIGNIFICAND_WIDTH, MINEXP, MAXEXP);
    }

    @Override
    MathContext makeMathContext(RoundingMode rm) {
        switch (rm) {
            case UP:
                return new MathContextUp64();
            case DOWN:
                return new MathContextDown64();
            case CEILING:
                return new MathContextCeiling64();
            case FLOOR:
                return new MathContextFloor64();
            case HALF_UP:
                return new MathContextHalfUp64();
            case HALF_DOWN:
                return new MathContextHalfDown64();
            case HALF_EVEN:
                return new MathContextHalfEven64();
            case UNNECESSARY:
                return new MathContextUnnecessary64();
            default:
                throw new AssertionError();
        }
    }

    class MathContext64 extends MathContext {

        private MathContext64(RoundingMode rm) {
            super(BinaryValueSet64.this, rm);
        }

        @Override
        BinaryDouble round(BinaryDoubleImpl v) {
            return v;
        }
    }

    private class MathContextUp64 extends MathContext64 {

        private MathContextUp64() {
            super(RoundingMode.UP);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            return fromBits(bitsUp(v));
        }
    }

    private class MathContextDown64 extends MathContext64 {

        private MathContextDown64() {
            super(RoundingMode.DOWN);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            return fromBits(bitsDown(v));
        }
    }

    private class MathContextCeiling64 extends MathContext64 {

        private MathContextCeiling64() {
            super(RoundingMode.CEILING);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            return fromBits(bitsCeiling(v));
        }
    }

    private class MathContextFloor64 extends MathContext64 {

        private MathContextFloor64() {
            super(RoundingMode.FLOOR);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            return fromBits(bitsFloor(v));
        }
    }

    private class MathContextHalfUp64 extends MathContext64 {

        private MathContextHalfUp64() {
            super(RoundingMode.HALF_UP);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            return fromBits(bitsHalfUp(v));
        }
    }

    private class MathContextHalfDown64 extends MathContext64 {

        private MathContextHalfDown64() {
            super(RoundingMode.HALF_DOWN);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            return fromBits(bitsHalfDown(v));
        }
    }

    private class MathContextHalfEven64 extends MathContext64 {

        private MathContextHalfEven64() {
            super(RoundingMode.HALF_EVEN);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            return fromBits(bitsHalfEven(v));
        }
    }

    private class MathContextUnnecessary64 extends MathContext64 {

        private MathContextUnnecessary64() {
            super(RoundingMode.UNNECESSARY);
        }

        @Override
        ExtendedRational round(BinaryImpl v) {
            throw new ArithmeticException("Rounding necessary");
        }
    }

    static double doubleValueUp(BinaryImpl v) {
        return Double.longBitsToDouble(bitsUp(v));
    }

    static double doubleValueDown(BinaryImpl v) {
        return Double.longBitsToDouble(bitsDown(v));
    }

    static double doubleValueHalfUp(BinaryImpl v) {
        return Double.longBitsToDouble(bitsHalfUp(v));
    }

    static double doubleValueHalfDown(BinaryImpl v) {
        return Double.longBitsToDouble(bitsHalfDown(v));
    }

    static double doubleValueHalfEven(BinaryImpl v) {
        return Double.longBitsToDouble(bitsHalfEven(v));
    }

    private static ExtendedRational fromBits(long bits) {
        long maskedBits = bits & 0x7FFFFFFFFFFFFFFFL;
        if (maskedBits <= 0) {
            assert maskedBits == 0;
            return Rational.zero();
        }
        if (maskedBits >= 0x7FF0000000000000L) {
            assert maskedBits == 0x7FF0000000000000L;
            return bits >= 0 ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.NEGATIVE_INFINITY;
        }
        return new BinaryDoubleImpl(Double.longBitsToDouble(bits));
    }

    private static long bitsUp(BinaryImpl v) {
        return bitsDown(v) + 1;
    }

    private static long bitsDown(BinaryImpl v) {
        int signum = v.signum();
        int precision = v.precision();
        int exp = v.intExp2();
        BigInteger unscaledValueAbs = v.getNumeratorWithout2sAbs();
        int dotExp = exp + precision - 1;
        long bits;
        if (dotExp >= MINEXP) {
            if (dotExp <= MAXEXP) {
                bits = unscaledValueAbs.shiftRight(precision - SIGNIFICAND_WIDTH).longValue()
                        + (((long) (dotExp - MINEXP)) << 52);
            } else {
                bits = 0x7FEFFFFFFFFFFFFFL;
            }
        } else {
            bits = unscaledValueAbs.shiftRight(MINEXP - SIGNIFICAND_WIDTH + 1 - exp).longValue();
        }
        if (signum < 0) {
            bits |= SIGN_MASK;
        }
        return bits;
    }

    private static long bitsCeiling(BinaryImpl v) {
        long bits = bitsDown(v);
        return v.signum() > 0 ? bits + 1 : bits;
    }

    private static long bitsFloor(BinaryImpl v) {
        long bits = bitsDown(v);
        return v.signum() < 0 ? bits + 1 : bits;
    }

    static long bitsHalfUp(BinaryImpl v) {
        int signum = v.signum();
        int precision = v.precision();
        int exp = v.intExp2();
        BigInteger unscaledValueAbs = v.getNumeratorWithout2sAbs();
        int dotExp = exp + precision - 1;
        long bits;
        if (dotExp >= MINEXP) {
            if (dotExp <= MAXEXP) {
                bits = unscaledValueAbs.shiftRight(precision - (SIGNIFICAND_WIDTH + 1)).longValue()
                        + (((long) (dotExp - MINEXP)) << 53);
            } else {
                bits = 0xFFDFFFFFFFFFFFFFL;
            }
        } else {
            bits = unscaledValueAbs.shiftRight(MINEXP - SIGNIFICAND_WIDTH - exp).longValue();
        }
        bits++;
        bits >>>= 1;
        if (signum < 0) {
            bits |= SIGN_MASK;
        }
        return bits;
    }

    static long bitsHalfDown(BinaryImpl v) {
        int signum = v.signum();
        int precision = v.precision();
        int exp = v.intExp2();
        BigInteger unscaledValueAbs = v.getNumeratorWithout2sAbs();
        int dotExp = exp + precision - 1;
        long bits = 0;
        int shift;
        if (dotExp >= MINEXP) {
            if (dotExp <= MAXEXP) {
                shift = precision - (SIGNIFICAND_WIDTH + 1);
                bits = unscaledValueAbs.shiftRight(shift).longValue()
                        + (((long) (dotExp - MINEXP)) << 53);
            } else {
                bits = 0xFFDFFFFFFFFFFFFFL;
                shift = Integer.MAX_VALUE;
            }
        } else {
            shift = MINEXP - SIGNIFICAND_WIDTH - exp;
            bits = unscaledValueAbs.shiftRight(shift).longValue();
        }
        if (shift > 1) {
            bits++;
        }
        bits >>>= 1;
        if (signum < 0) {
            bits |= SIGN_MASK;
        }
        return bits;
    }

    static long bitsHalfEven(BinaryImpl v) {
        int signum = v.signum();
        int precision = v.precision();
        int exp = v.intExp2();
        BigInteger unscaledValueAbs = v.getNumeratorWithout2sAbs();
        int dotExp = exp + precision - 1;
        long bits = 0;
        int shift;
        if (dotExp >= MINEXP) {
            if (dotExp <= MAXEXP) {
                shift = precision - (SIGNIFICAND_WIDTH + 1);
                bits = unscaledValueAbs.shiftRight(shift).longValue()
                        + (((long) (dotExp - MINEXP)) << 53);
            } else {
                bits = 0xFFDFFFFFFFFFFFFFL;
                shift = Integer.MAX_VALUE;
            }
        } else {
            shift = MINEXP - SIGNIFICAND_WIDTH - exp;
            bits = unscaledValueAbs.shiftRight(shift).longValue();
        }
        if (shift > 0 || (bits & 2) != 0) {
            bits++;
        }
        bits >>>= 1;
        if (signum < 0) {
            bits |= SIGN_MASK;
        }
        return bits;
    }
}
