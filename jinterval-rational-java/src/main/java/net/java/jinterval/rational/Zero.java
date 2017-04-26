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

import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.math.RoundingMode;

/**
 * Singleton class that represets Zero.
 */
class Zero extends BinaryDouble {

    static final Zero INSTANCE = new Zero();

    private Zero() {
        super(0);
    }

    @Override
    public int intCeilLog2() {
        return Integer.MIN_VALUE;
    }

    @Override
    public int intFloorLog2() {
        throw new ArithmeticException();
    }

    @Override
    public int intExp2() {
        return 0;
    }

    @Override
    public BigInteger getNumeratorWithout2s() {
        return BigInteger.ZERO;
    }

    @Override
    public BigInteger getNumeratorWithout2sAbs() {
        return BigInteger.ZERO;
    }

    @Override
    public BigInteger getDenominatorWithout2s() {
        return BigInteger.ONE;
    }

    @Override
    public int signum() {
        return 0;
    }

    @Override
    public int compareTotalTo(ExtendedRational that) {
        if (that instanceof Zero) {
            return 0;
        }
        return -that.signum();
    }

    @Override
    public int compareTo(ExtendedRational that) {
        return -that.signum();
    }

    @Override
    int compareTo(BinaryImpl that) {
        return -that.signum();
    }

    @Override
    int compareTo(BinaryDoubleImpl that) {
        return -that.signum();
    }

    @Override
    public float floatValue(RoundingMode roundingMode) {
        return floatValue();
    }

    @Override
    public BigInteger toBigInteger() {
        return BigInteger.ZERO;
    }

    @Override
    public int intValue() {
        return 0;
    }

    @Override
    public long longValue() {
        return 0;
    }

    @Override
    public BigDecimal bigDecimalValue(MathContext mc) {
        return BigDecimal.ZERO;
    }

    @Override
    public String toString() {
        return "0";
    }

    @Override
    public String toHexString(BinaryValueSet valueSet) {
        return "0x0p0";
    }

    @Override
    int precision() {
        return 1;
    }

    @Override
    public int hashCode() {
        long bits = Double.doubleToRawLongBits(value);
        return (int) (bits ^ (bits >>> 32));
    }

    @Override
    public boolean equals(Object o) {
        return this == o;
    }
}
