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
 */
public interface ExtendedRationalContext {

    public ExtendedRational rnd(CReal x);

    public ExtendedRational rnd(Number x);

    public ExtendedRational rnd(ExtendedRational x);

    public ExtendedRational pi();

    public ExtendedRational euler();

//    ExtendedRational rnd(Binary x);
    public ExtendedRational neg(ExtendedRational x);

    public ExtendedRational add(ExtendedRational x, ExtendedRational y);

    public ExtendedRational sub(ExtendedRational x, ExtendedRational y);

    public ExtendedRational mul(ExtendedRational x, ExtendedRational y);

    public ExtendedRational div(ExtendedRational x, ExtendedRational y);

    public ExtendedRational recip(ExtendedRational x);

    public ExtendedRational sqr(ExtendedRational x);

    public ExtendedRational sqrt(ExtendedRational x);

    public ExtendedRational fma(ExtendedRational x, ExtendedRational y, ExtendedRational z);

    public ExtendedRational pown(ExtendedRational x, BigInteger p);

    public ExtendedRational pown(ExtendedRational x, long p);

    public ExtendedRational pown(ExtendedRational x, int p);

    public ExtendedRational pow(ExtendedRational x, ExtendedRational y);

    public ExtendedRational exp(ExtendedRational x);

    public ExtendedRational exp2(ExtendedRational x);

    public ExtendedRational exp10(ExtendedRational x);

    public ExtendedRational log(ExtendedRational x);

    public ExtendedRational log2(ExtendedRational x);

    public ExtendedRational log10(ExtendedRational x);

    public ExtendedRational sin(ExtendedRational x);

    public ExtendedRational cos(ExtendedRational x);

    public ExtendedRational tan(ExtendedRational x);

    public ExtendedRational asin(ExtendedRational x);

    public ExtendedRational acos(ExtendedRational x);

    public ExtendedRational atan(ExtendedRational x);

    public ExtendedRational atan2(ExtendedRational y, ExtendedRational x);

    public ExtendedRational sinh(ExtendedRational x);

    public ExtendedRational cosh(ExtendedRational x);

    public ExtendedRational tanh(ExtendedRational x);

    public ExtendedRational asinh(ExtendedRational x);

    public ExtendedRational acosh(ExtendedRational x);

    public ExtendedRational atanh(ExtendedRational x);

    public ExtendedRational sign(ExtendedRational x);

    public ExtendedRational ceil(ExtendedRational x);

    public ExtendedRational floor(ExtendedRational x);

    public ExtendedRational trunc(ExtendedRational x);

    public ExtendedRational roundTiesToEven(ExtendedRational x);

    public ExtendedRational roundTiesToAway(ExtendedRational x);

    public ExtendedRational abs(ExtendedRational x);

    public ExtendedRational min(ExtendedRational x1, ExtendedRational x2);

    public ExtendedRational min(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn);

    public ExtendedRational max(ExtendedRational x1, ExtendedRational x2);

    public ExtendedRational max(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn);

    public ExtendedRational rootn(ExtendedRational x, BigInteger q);

    public ExtendedRational rootn(ExtendedRational x, long q);

    public ExtendedRational rootn(ExtendedRational x, int q);

    public ExtendedRational hypot(ExtendedRational x, ExtendedRational y);
}
