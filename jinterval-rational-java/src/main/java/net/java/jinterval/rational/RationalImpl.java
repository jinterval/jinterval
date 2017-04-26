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
 * @author nadezhin
 */
class RationalImpl extends Rational {

    private final int exp;
    private final BigInteger numeratorWithout2s;
    private final BigInteger denominatorWithout2s;

    RationalImpl(int exp, BigInteger numeratorWithout2s, BigInteger denominatorWithout2s) {
        this.exp = exp;
        this.numeratorWithout2s = numeratorWithout2s;
        this.denominatorWithout2s = denominatorWithout2s;
        assert denominatorWithout2s.signum() > 0;
        if (exp >= 0) {
            assert exp <= EXP_LIMIT - numeratorWithout2s.abs().bitLength();
            assert denominatorWithout2s.bitLength() <= EXP_LIMIT;
        } else {
            assert numeratorWithout2s.abs().bitLength() <= EXP_LIMIT;
            assert exp >= -EXP_LIMIT + denominatorWithout2s.bitLength();
        }
    }

    @Override
    public int intCeilLog2() {
        BigInteger na = getNumeratorWithout2sAbs();
        BigInteger d = denominatorWithout2s;
        int diffLength = na.bitLength() - d.bitLength();
        int log2 = exp + diffLength;
        if (diffLength > 0) {
            d = d.shiftLeft(diffLength);
        } else if (diffLength < 0) {
            na = na.shiftLeft(-diffLength);
        }
        if (na.compareTo(d) > 0) {
            log2++;
        }
        return log2;
    }

    @Override
    public int intFloorLog2() {
        BigInteger na = getNumeratorWithout2sAbs();
        BigInteger d = denominatorWithout2s;
        int diffLength = na.bitLength() - d.bitLength();
        int log2 = exp + diffLength;
        if (diffLength > 0) {
            d = d.shiftLeft(diffLength);
        } else if (diffLength < 0) {
            na = na.shiftLeft(-diffLength);
        }
        if (na.compareTo(d) < 0) {
            log2--;
        }
        return log2;
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
    BigInteger getNumeratorWithout2sAbs() {
        return numeratorWithout2s.abs();
    }

    @Override
    public BigInteger getDenominatorWithout2s() {
        return denominatorWithout2s;
    }

    public int signum() {
        return numeratorWithout2s.signum();
    }

    @Override
    public int compareTo(ExtendedRational that) {
        BigInteger xp = this.getNumeratorWithout2s();
        BigInteger xq = this.getDenominatorWithout2s();
        assert xp.signum() != 0 && xq.signum() > 0;
        BigInteger yp = that.getNumeratorWithout2s();
        BigInteger yq = that.getDenominatorWithout2s();
        if (xp.signum() != yp.signum()) {
            return xp.signum() > yp.signum() ? +1 : -1;
        }
        BigInteger x = xp.multiply(yq);
        BigInteger y = yp.multiply(xq);
        int e = this.intExp2() - that.intExp2();
        if (e > 0) {
            x = x.shiftLeft(e);
        } else if (e < 0) {
            y = y.shiftLeft(-e);
        }
        return x.compareTo(y);
    }

    @Override
    int compareTo(BinaryImpl that) {
        return compareTo((ExtendedRational) that);
    }

    @Override
    int compareTo(BinaryDoubleImpl that) {
        return compareTo((ExtendedRational) that);
    }

    @Override
    public double doubleValueUp() {
        return BinaryValueSet.BINARY64.getMathContext(RoundingMode.UP).round(this).doubleValueExact();
    }

    @Override
    public double doubleValueDown() {
        return BinaryValueSet.BINARY64.getMathContext(RoundingMode.DOWN).round(this).doubleValueExact();
    }

    @Override
    public double doubleValueHalfUp() {
        return BinaryValueSet.BINARY64.getMathContext(RoundingMode.HALF_UP).round(this).doubleValueExact();
    }

    @Override
    public double doubleValueHalfDown() {
        return BinaryValueSet.BINARY64.getMathContext(RoundingMode.HALF_DOWN).round(this).doubleValueExact();
    }

    @Override
    public double doubleValueHalfEven() {
        return BinaryValueSet.BINARY64.getMathContext(RoundingMode.HALF_EVEN).round(this).doubleValueExact();
    }

    @Override
    public int hashCode() {
        return exp + numeratorWithout2s.hashCode() + denominatorWithout2s.hashCode();
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof RationalImpl) {
            RationalImpl that = (RationalImpl) o;
            return this.exp == that.exp
                    && this.numeratorWithout2s.equals(that.numeratorWithout2s)
                    && this.denominatorWithout2s.equals(that.denominatorWithout2s);
        }
        return false;
    }

    @Override
    public String toString() {
        String decimal = null;
        try {
            decimal = bigDecimalValue(mathContextExact).toString();
        } catch (ArithmeticException e) {
        }
        String fractional = biNumerator() + "/" + biDenominator();
        return decimal == null || decimal.length() > fractional.length() ? fractional : decimal;
    }

    @Override
    public String toHexString(BinaryValueSet valueSet) {
        throw new UnsupportedOperationException();
    }
}
