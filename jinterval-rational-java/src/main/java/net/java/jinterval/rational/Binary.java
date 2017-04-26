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

/**
 *
 * @author nadezhin
 */
abstract class Binary extends Rational {

    @Override
    public abstract int intExp2();

    @Override
    public abstract BigInteger getNumeratorWithout2s();

    @Override
    public abstract int signum();

    public ExtendedRational min(Binary y) {
        return compareTotalTo(y) <= 0 ? this : y;
    }

    public ExtendedRational max(Binary y) {
        return compareTotalTo(y) >= 0 ? this : y;
    }

    @Override
    public BigInteger getDenominatorWithout2s() {
        return BigInteger.ONE;
    }

    @Override
    public String toString() {
        return toString(null);
    }

    @Override
    public String toHexString(BinaryValueSet valueSet) {
        if (valueSet == null) {
            throw new NullPointerException();
        }
        return toString(valueSet);
    }

    private String toString(BinaryValueSet valueSet) {
        StringBuilder sb = new StringBuilder();
        sb.append(signum() > 0 ? "0x" : "-0x");
        BigInteger n = getNumeratorWithout2sAbs();
        int exp = intFloorLog2();
        if (valueSet != null && exp < valueSet.getMinExp()) {
            exp = valueSet.getMinExp();
        }
        int fracBits = exp - intExp2();
        if (fracBits % 4 != 0) {
            n = n.shiftLeft(4 - fracBits % 4);
            fracBits += 4 - fracBits % 4;
        }
        assert fracBits % 4 == 0;
        int hexDigits = fracBits / 4;
        String ms = n.toString(16);
        while (ms.length() <= hexDigits) {
            ms = '0' + ms;
        }
        assert ms.length() == hexDigits + 1;
        sb.append(ms.charAt(0));
        if (ms.length() > 1) {
            sb.append(".").append(ms.substring(1));
        }
        sb.append("p");
        sb.append(exp);
        String s = sb.toString();
        if (valueSet == null) {
            if (intExp2() >= 0) {
                if (intFloorLog2() / 10 * 3 <= s.length()) {
                    String s1 = toBigInteger().toString();
                    if (s1.length() <= s.length()) {
                        s = s1;
                    }
                }
                BigDecimal bd = bigDecimalValue(mathContextExact);
                String s1 = bd.toString();
                int numTrailingZeros = 0;
                while (s1.charAt(s1.length() - numTrailingZeros - 1) == '0') {
                    numTrailingZeros += 1;
                }
                if (numTrailingZeros > 0) {
                    bd = bd.setScale(-numTrailingZeros);
                    s1 = bd.toString();
                }
                if (s1.length() <= s.length()) {
                    s = s1;
                }
            } else if (intExp2() >= -s.length()) {
                String s1 = bigDecimalValue(mathContextExact).toString();
                if (s1.length() <= s.length()) {
                    s = s1;
                }
            }
        }
        return s;
    }

    abstract int precision();
}
