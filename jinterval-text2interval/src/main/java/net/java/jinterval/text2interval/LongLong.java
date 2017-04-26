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
package net.java.jinterval.text2interval;

import java.math.BigInteger;

/**
 *
 */
public class LongLong {

    /**
     * This mask is used to obtain the value of an int as if it were unsigned.
     */
    final static long LONG_MASK = 0xffffffffL;
    long hi, lo;

    void mult(long x, long y) {
        long pll = (x & LONG_MASK) * (y & LONG_MASK);
        long phl = (x >>> 32) * (y & LONG_MASK);
        long plh = (x & LONG_MASK) * (y >>> 32);
        long phh = (x >>> 32) * (y >>> 32);
        long s1 = (pll >>> 32) + (phl & LONG_MASK) + (plh & LONG_MASK);
        lo = (pll & LONG_MASK) | (s1 << 32);
        hi = phh + (phl >>> 32) + (plh >>> 32) + (s1 >>> 32);
//        assert longArrayToBigInteger(new long[]{x}, 1, false).multiply(longArrayToBigInteger(new long[]{y}, 1, false)).
//                equals(longArrayToBigInteger(new long[]{hi, lo}, 2, false));
    }

    void addLo(long l) {
        long oldLo = lo;
        lo += l;
        if (lo >= 0 ? lo < oldLo || oldLo < 0 : lo < oldLo && oldLo < 0) {
            hi++;
        }
    }
    
    void subHi(long h) {
        hi -= h;
    }

    void addMult(long x, long y) {
//        BigInteger oldV = longArrayToBigInteger(new long[]{high, hi, lo}, 3, true);
        long pll = (x & LONG_MASK) * (y & LONG_MASK);
        long phl = (x >>> 32) * (y & LONG_MASK);
        long plh = (x & LONG_MASK) * (y >>> 32);
        long phh = (x >>> 32) * (y >>> 32);
        long s0 = (lo & LONG_MASK) + (pll & LONG_MASK);
        long s1 = (s0 >> 32) + (lo >>> 32) + (pll >>> 32) + (phl & LONG_MASK) + (plh & LONG_MASK);
        lo = (s0 & LONG_MASK) | (s1 << 32);
        long s2 = (s1 >> 32) + (hi & LONG_MASK) + (phl >>> 32) + (plh >>> 32) + (phh & LONG_MASK);
        long s3 = (s2 >> 32) + (hi >> 32) + (phh >>> 32);
        hi = (s2 & LONG_MASK) | (s3 << 32);
//        BigInteger newV = longArrayToBigInteger(new long[]{high, hi, lo}, 3, true);
//        assert oldV.add(longArrayToBigInteger(new long[]{x}, 1, false).multiply(longArrayToBigInteger(new long[]{y}, 1, false))).
//                equals(newV);
    }
    
    void subMult(long x, long y) {
//        BigInteger oldV = toBigInteger();
        long pll = (x & LONG_MASK) * (y & LONG_MASK);
        long phl = (x >>> 32) * (y & LONG_MASK);
        long plh = (x & LONG_MASK) * (y >>> 32);
        long phh = (x >>> 32) * (y >>> 32);
        long s0 = (lo & LONG_MASK) - (pll & LONG_MASK);
        long s1 = (s0 >> 32) + (lo >>> 32) - (pll >>> 32) - (phl & LONG_MASK) - (plh & LONG_MASK);
        lo = (s0 & LONG_MASK) | (s1 << 32);
        long s2 = (s1 >> 32) + (hi & LONG_MASK) - (phl >>> 32) - (plh >>> 32) - (phh & LONG_MASK);
        long s3 = (s2 >> 32) + (hi >> 32) - (phh >>> 32);
        hi = (s2 & LONG_MASK) | (s3 << 32);
//        BigInteger newV = toBigInteger();
//        assert oldV.subtract(DoubleParseHard64.longArrayToBigInteger(new long[]{x}, 1, false).multiply(DoubleParseHard64.longArrayToBigInteger(new long[]{y}, 1, false))).
//                equals(newV);
    }
    
    public BigInteger toBigInteger() {
        return longArrayToBigInteger(new long[] {hi, lo}, 2, true);
    }
    
    static BigInteger longArrayToBigInteger(long[] la, int len, boolean signed) {
        byte[] bytes = new byte[len * 8 + 1];
        if (signed && la[0] < 0) {
            bytes[0] = -1;
        }
        for (int i = 0; i < len; i++) {
            long l = la[i];
            bytes[i * 8 + 1] = (byte) (l >> 56);
            bytes[i * 8 + 2] = (byte) (l >> 48);
            bytes[i * 8 + 3] = (byte) (l >> 40);
            bytes[i * 8 + 4] = (byte) (l >> 32);
            bytes[i * 8 + 5] = (byte) (l >> 24);
            bytes[i * 8 + 6] = (byte) (l >> 16);
            bytes[i * 8 + 7] = (byte) (l >> 8);
            bytes[i * 8 + 8] = (byte) l;
        }
        return new BigInteger(bytes);
    }
}
