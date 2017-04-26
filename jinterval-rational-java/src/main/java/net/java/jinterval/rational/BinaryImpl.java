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

/**
 *
 * @author nadezhin
 */
class BinaryImpl extends Binary {

    private final int exp;
    private final BigInteger numeratorWithout2s;
    private final BigInteger numeratorWithout2sAbs;
    private final int signum;

    BinaryImpl(int signum, BigInteger numeratorWithout2sAbs, int exp) {
        assert numeratorWithout2sAbs.signum() > 0;
        assert signum == 1 || signum == -1;
        int precision = numeratorWithout2sAbs.bitLength();
        assert exp >= -EXP_LIMIT + 1 && exp <= EXP_LIMIT - precision;
//        assert exp >= -Integer.MAX_VALUE + 1 && exp <= Integer.MAX_VALUE + 1 - precision;
        assert precision > BinaryValueSet64.SIGNIFICAND_WIDTH
                || exp < BinaryValueSet64.MINEXP + 1 - BinaryValueSet64.SIGNIFICAND_WIDTH
                || exp > BinaryValueSet64.MAXEXP + 1 - precision;
        this.signum = signum;
        this.numeratorWithout2sAbs = numeratorWithout2sAbs;
        this.exp = exp;
        numeratorWithout2s = signum >= 0 ? numeratorWithout2sAbs : numeratorWithout2sAbs.negate();
    }

    @Override
    public int intCeilLog2() {
        int bitLength = numeratorWithout2sAbs.bitLength();
        return bitLength > 1 ? exp + bitLength : exp;
    }

    @Override
    public int intFloorLog2() {
        int bitLength = numeratorWithout2sAbs.bitLength();
        return exp + bitLength - 1;
    }

    @Override
    public int intExp2() {
        return exp;
    }

    @Override
    public BigInteger getNumeratorWithout2s() {
        return numeratorWithout2s;
    }

    @Override
    public BigInteger getNumeratorWithout2sAbs() {
        return numeratorWithout2sAbs;
    }

    @Override
    public int signum() {
        return signum;
    }

    @Override
    public int compareTo(ExtendedRational that) {
        return -that.compareTo(this);
    }

    @Override
    int compareTo(BinaryImpl that) {
        if (signum > 0) {
            if (that.signum < 0) {
                return +1;
            }
            return compareAbsTo(that.numeratorWithout2sAbs, that.exp);
        } else {
            if (that.signum > 0) {
                return -1;
            }
            return -compareAbsTo(that.numeratorWithout2sAbs, that.exp);
        }
    }

    @Override
    int compareTo(BinaryDoubleImpl that) {
        if (signum > 0) {
            if (that.value < 0) {
                return +1;
            }
            return compareAbsTo(that.getNumeratorWithout2sAbs(), that.intExp2());
        } else {
            if (that.value > 0) {
                return -1;
            }
            return -compareAbsTo(that.getNumeratorWithout2sAbs(), that.intExp2());
        }
    }

    private int compareAbsTo(BigInteger ya, int yExp) {
        BigInteger xa = numeratorWithout2sAbs;
        int xPrec = xa.bitLength();
        int yPrec = ya.bitLength();
        int xDot1 = xPrec + exp;
        int yDot1 = yPrec + yExp;
        if (xDot1 != yDot1) {
            return xDot1 > yDot1 ? +1 : -1;
        }
        if (xPrec > yPrec) {
            ya = ya.shiftLeft(xPrec - yPrec);
        } else if (xPrec < yPrec) {
            xa = xa.shiftLeft(yPrec - xPrec);
        }
        return xa.compareTo(ya);
    }

    @Override
    public int hashCode() {
        return 31 * numeratorWithout2s.hashCode() - exp;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof BinaryImpl) {
            BinaryImpl that = (BinaryImpl) o;
            return this.numeratorWithout2s.equals(that.numeratorWithout2s) && this.exp == that.exp;
        }
        return false;
    }

    @Override
    public double doubleValueUp() {
        return BinaryValueSet64.doubleValueUp(this);
    }

    @Override
    public double doubleValueDown() {
        return BinaryValueSet64.doubleValueDown(this);
    }

    @Override
    public double doubleValueHalfUp() {
        return BinaryValueSet64.doubleValueHalfUp(this);
    }

    @Override
    public double doubleValueHalfDown() {
        return BinaryValueSet64.doubleValueHalfDown(this);
    }

    @Override
    public double doubleValueHalfEven() {
        return BinaryValueSet64.doubleValueHalfEven(this);
    }

    @Override
    int precision() {
        return numeratorWithout2sAbs.bitLength();
    }
}
