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
class BinaryDoubleImpl extends BinaryDouble {

    BinaryDoubleImpl(double value) {
        super(value);
    }

    @Override
    public int intCeilLog2() {
        long bits = Double.doubleToRawLongBits(value);
        int p = ((int) (bits >> 52)) & 0x7FF;
        assert p != 0x7FF;
        if (p != 0) {
            return (bits & BinaryValueSet64.SIGNIF_BIT_MASK) != 0 ? p + Double.MIN_EXPONENT : p + (Double.MIN_EXPONENT - 1);
        } else {
            int leadingZeros = Long.numberOfLeadingZeros((bits & BinaryValueSet64.SIGNIF_BIT_MASK) - 1);
            return (Double.MIN_EXPONENT - 52 + 64) - leadingZeros;
        }
    }

    @Override
    public int intFloorLog2() {
        long bits = Double.doubleToRawLongBits(value);
        int p = ((int) (bits >> 52)) & 0x7FF;
        assert p != 0x7FF;
        if (p != 0) {
            return p + (Double.MIN_EXPONENT - 1);
        } else {
            int leadingZeros = Long.numberOfLeadingZeros((bits & BinaryValueSet64.SIGNIF_BIT_MASK));
            return (Double.MIN_EXPONENT - 52 + 64 - 1) - leadingZeros;
        }
    }

    @Override
    public int intExp2() {
        long bits = Double.doubleToRawLongBits(value);
        int p = ((int) (bits >> 52)) & 0x7FF;
        assert p != 0x7FF;
        int trailingZeros = Long.numberOfTrailingZeros(bits);
        if (p != 0) {
            return p + Math.min(trailingZeros, 52) + (Double.MIN_EXPONENT - 1 - 52);
        } else {
            assert trailingZeros < 52;
            return trailingZeros + (Double.MIN_EXPONENT - 52);
        }
    }

    @Override
    public BigInteger getNumeratorWithout2s() {
        long bits = Double.doubleToRawLongBits(value);
        int p = ((int) (bits >> 52)) & 0x7FF;
        assert p != 0x7FF;
        long m = bits & 0xFFFFFFFFFFFFFL;
        int trailingZeros = Long.numberOfTrailingZeros(bits);
        if (p != 0) {
            m |= 0x10000000000000L;
        }
        m >>>= Math.min(trailingZeros, 52);
        if (bits < 0) {
            m = -m;
        }
        return BigInteger.valueOf(m);
    }

    @Override
    public BigInteger getNumeratorWithout2sAbs() {
        long bits = Double.doubleToRawLongBits(value);
        int p = ((int) (bits >> 52)) & 0x7FF;
        assert p != 0x7FF;
        long m = bits & 0xFFFFFFFFFFFFFL;
        int trailingZeros = Long.numberOfTrailingZeros(bits);
        if (p != 0) {
            m |= 0x10000000000000L;
        }
        m >>>= Math.min(trailingZeros, 52);
        return BigInteger.valueOf(m);
    }

    @Override
    public int signum() {
        return value > 0 ? +1 : -1;
    }

    @Override
    public int compareTo(ExtendedRational that) {
        return -that.compareTo(this);
    }

    @Override
    int compareTo(BinaryImpl that) {
        return -that.compareTo(this);
    }

    @Override
    int compareTo(BinaryDoubleImpl that) {
        return value > that.value ? +1 : value < that.value ? -1 : 0;
    }

    @Override
    public int intValue() {
        return (int) value;
    }

    @Override
    public long longValue() {
        return (long) value;
    }

    @Override
    int precision() {
        long bits = Double.doubleToRawLongBits(value);
        int p = (int) ((bits & BinaryValueSet64.EXP_BIT_MASK) >> (BinaryValueSet64.SIGNIFICAND_WIDTH - 1));
        assert p != 0x7FF;
        int trailingZeros = Long.numberOfTrailingZeros(bits);
        if (p != 0) {
            return Math.max(1, BinaryValueSet64.SIGNIFICAND_WIDTH - trailingZeros);
        }
        assert trailingZeros < (BinaryValueSet64.SIGNIFICAND_WIDTH - 1);
        return Long.SIZE - Long.numberOfLeadingZeros(bits & BinaryValueSet64.SIGNIF_BIT_MASK) - trailingZeros;
    }
}
