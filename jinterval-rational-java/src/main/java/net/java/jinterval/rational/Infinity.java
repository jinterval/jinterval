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

/**
 * Class that represent infinities.
 * There only two singleton subclasses - <code>NegativeInfinity</code> and <code>PositiveInfinity</code>.
 */
abstract class Infinity extends ExtendedRational {

    private final BigInteger unscaledValue;

    Infinity(int signum) {
        assert Math.abs(signum) == 1;
        unscaledValue = BigInteger.valueOf(signum);
    }

    @Override
    public int intCeilLog2() {
        throw new ArithmeticException();
    }

    @Override
    public int intFloorLog2() {
        return Integer.MAX_VALUE;
    }

    @Override
    public int intExp2() {
        return 0;
    }

    @Override
    public BigInteger getNumeratorWithout2s() {
        return unscaledValue;
    }

    @Override
    public BigInteger getNumeratorWithout2sAbs() {
        return BigInteger.ONE;
    }

    @Override
    public BigInteger getDenominatorWithout2s() {
        return BigInteger.ZERO;
    }

    @Override
    public double doubleValueUp() {
        return doubleValueExact();
    }

    @Override
    public double doubleValueDown() {
        return doubleValueExact();
    }

    @Override
    public double doubleValueHalfUp() {
        return doubleValueExact();
    }

    @Override
    public double doubleValueHalfDown() {
        return doubleValueExact();
    }

    @Override
    public double doubleValueHalfEven() {
        return doubleValueExact();
    }

    @Override
    public double doubleValueExact() {
        return unscaledValue.signum() > 0 ? Double.POSITIVE_INFINITY : Double.NEGATIVE_INFINITY;
    }
    
    @Override
    public BigInteger toBigInteger() {
        throw new ArithmeticException();
    }

    @Override
    public BigDecimal bigDecimalValue(MathContext mc) {
        throw new ArithmeticException();
    }
}
