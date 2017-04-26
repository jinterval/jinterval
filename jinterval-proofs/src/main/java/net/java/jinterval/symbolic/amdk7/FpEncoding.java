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
package net.java.jinterval.symbolic.amdk7;

import java.math.BigInteger;
import net.java.jinterval.rational.Rational;

/**
 * Encoding of floating point number, according to D. Russinoff's paper:
 * http://www.russinoff.com/papers/k7-div-sqrt.html
 */
public class FpEncoding {

    public static final int EXP_MASK = (1 << 18) - 1;
    public static final int BIAS = (1 << 17) - 1;
    public final int M;
    public final boolean sgn;
    public final BigInteger sig;
    public final int expo;

    FpEncoding(int M, boolean sgn, BigInteger sig, int expo) {
        this.M = M;
        this.sgn = sgn;
        this.sig = sig;
        this.expo = expo;
    }

    public Rational rationalValue() {
        return Rational.valueOf(sgn ? sig.negate() : sig, expo - BIAS - (M - 1));
    }

    @Override
    public String toString() {
        return rationalValue().toString();
    }
}
