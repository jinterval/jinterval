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
class RationalContextExact implements ExtendedRationalContext {

    @Override
    public ExtendedRational rnd(CReal x) {
        ExtendedRational r = x.peekExactValue();
        if (r == null) {
            throw new IrrationalException();
        }
        return r;
    }

    @Override
    public ExtendedRational rnd(Number x) {
        return rnd(ExtendedRational.valueOf(x));
    }

    @Override
    public ExtendedRational rnd(ExtendedRational x) {
        return x;
    }

//        @Override
//        ExtendedRational rnd(Binary x) {
//            return x;
//        }
    @Override
    public ExtendedRational pi() {
        throw new IrrationalException();
    }

    @Override
    public ExtendedRational euler() {
        throw new IrrationalException();
    }

    @Override
    public ExtendedRational neg(ExtendedRational x) {
        return ExtendedRationalOps.neg(x);
    }

    @Override
    public ExtendedRational add(ExtendedRational x, ExtendedRational y) {
        return ExtendedRationalOps.add(x, y);
    }

    @Override
    public ExtendedRational sub(ExtendedRational x, ExtendedRational y) {
        return ExtendedRationalOps.sub(x, y);
    }

    @Override
    public ExtendedRational mul(ExtendedRational x, ExtendedRational y) {
        return ExtendedRationalOps.mul(x, y);
    }

    @Override
    public ExtendedRational div(ExtendedRational x, ExtendedRational y) {
        return ExtendedRationalOps.div(x, y);
    }

    @Override
    public ExtendedRational recip(ExtendedRational x) {
        return ExtendedRationalOps.recip(x);
    }

    @Override
    public ExtendedRational sqrt(ExtendedRational x) {
        return ExtendedRationalOps.sqrt(x);
    }

    @Override
    public ExtendedRational sqr(ExtendedRational x) {
        return ExtendedRationalOps.sqr(x);
    }

    @Override
    public ExtendedRational fma(ExtendedRational x, ExtendedRational y, ExtendedRational z) {
        return ExtendedRationalOps.fma(x, y, z);
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, BigInteger p) {
        return ExtendedRationalOps.pown(x, p);
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, long p) {
        return ExtendedRationalOps.pown(x, p);
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, int p) {
        return ExtendedRationalOps.pown(x, p);
    }

    @Override
    public ExtendedRational pow(ExtendedRational x, ExtendedRational y) {
        return ExtendedRationalOps.pow(x, y);
    }

    @Override
    public ExtendedRational exp(ExtendedRational x) {
        return ExtendedRationalOps.exp(x);
    }

    @Override
    public ExtendedRational exp2(ExtendedRational x) {
        return ExtendedRationalOps.exp2(x);
    }

    @Override
    public ExtendedRational exp10(ExtendedRational x) {
        return ExtendedRationalOps.exp10(x);
    }

    @Override
    public ExtendedRational log(ExtendedRational x) {
        return ExtendedRationalOps.log(x);
    }

    @Override
    public ExtendedRational log2(ExtendedRational x) {
        return ExtendedRationalOps.log2(x);
    }

    @Override
    public ExtendedRational log10(ExtendedRational x) {
        return ExtendedRationalOps.log10(x);
    }

    @Override
    public ExtendedRational sin(ExtendedRational x) {
        return ExtendedRationalOps.sin(x);
    }

    @Override
    public ExtendedRational cos(ExtendedRational x) {
        return ExtendedRationalOps.cos(x);
    }

    @Override
    public ExtendedRational tan(ExtendedRational x) {
        return ExtendedRationalOps.tan(x);
    }

    @Override
    public ExtendedRational asin(ExtendedRational x) {
        return ExtendedRationalOps.asin(x);
    }

    @Override
    public ExtendedRational acos(ExtendedRational x) {
        return ExtendedRationalOps.acos(x);
    }

    @Override
    public ExtendedRational atan(ExtendedRational x) {
        return ExtendedRationalOps.atan(x);
    }

    @Override
    public ExtendedRational atan2(ExtendedRational y, ExtendedRational x) {
        return ExtendedRationalOps.atan2(y, x);
    }

    @Override
    public ExtendedRational sinh(ExtendedRational x) {
        return ExtendedRationalOps.sinh(x);
    }

    @Override
    public ExtendedRational cosh(ExtendedRational x) {
        return ExtendedRationalOps.cosh(x);
    }

    @Override
    public ExtendedRational tanh(ExtendedRational x) {
        return ExtendedRationalOps.tanh(x);
    }

    @Override
    public ExtendedRational asinh(ExtendedRational x) {
        return ExtendedRationalOps.asinh(x);
    }

    @Override
    public ExtendedRational acosh(ExtendedRational x) {
        return ExtendedRationalOps.acosh(x);
    }

    @Override
    public ExtendedRational atanh(ExtendedRational x) {
        return ExtendedRationalOps.atanh(x);
    }

    @Override
    public ExtendedRational sign(ExtendedRational x) {
        return ExtendedRationalOps.sign(x);
    }

    @Override
    public ExtendedRational ceil(ExtendedRational x) {
        return ExtendedRationalOps.ceil(x);
    }

    @Override
    public ExtendedRational floor(ExtendedRational x) {
        return ExtendedRationalOps.floor(x);
    }

    @Override
    public ExtendedRational trunc(ExtendedRational x) {
        return ExtendedRationalOps.trunc(x);
    }

    @Override
    public ExtendedRational roundTiesToEven(ExtendedRational x) {
        return ExtendedRationalOps.roundTiesToEven(x);
    }

    @Override
    public ExtendedRational roundTiesToAway(ExtendedRational x) {
        return ExtendedRationalOps.roundTiesToAway(x);
    }

    @Override
    public ExtendedRational abs(ExtendedRational x) {
        return ExtendedRationalOps.abs(x);
    }

    @Override
    public ExtendedRational min(ExtendedRational x1, ExtendedRational x2) {
        return ExtendedRationalOps.min(x1, x2);
    }

    @Override
    public ExtendedRational min(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn) {
        return ExtendedRationalOps.min(x1, x2, xn);
    }

    @Override
    public ExtendedRational max(ExtendedRational x1, ExtendedRational x2) {
        return ExtendedRationalOps.max(x1, x2);
    }

    @Override
    public ExtendedRational max(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn) {
        return ExtendedRationalOps.max(x1, x2, xn);
    }

    @Override
    public ExtendedRational rootn(ExtendedRational x, BigInteger q) {
        return ExtendedRationalOps.rootn(x, q);
    }

    @Override
    public ExtendedRational rootn(ExtendedRational x, long q) {
        return ExtendedRationalOps.rootn(x, q);
    }

    @Override
    public ExtendedRational rootn(ExtendedRational x, int q) {
        return ExtendedRationalOps.rootn(x, q);
    }

    @Override
    public ExtendedRational hypot(ExtendedRational x, ExtendedRational y) {
        return ExtendedRationalOps.hypot(x, y);
    }

}
