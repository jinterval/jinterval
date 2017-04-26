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
package net.java.jinterval.interval.classic;

import java.math.BigInteger;
import net.java.jinterval.interval.IntervalContext;
import net.java.jinterval.rational.ExtendedRational;

/**
 *
 */
public interface ClassicIntervalContext extends IntervalContext<ClassicInterval> {

    @Override
    public ClassicInterval hull(ClassicInterval x);

    @Override
    public ClassicInterval newDec(ClassicInterval x);

    @Override
    public ClassicInterval numsToInterval(ExtendedRational l, ExtendedRational u);

    @Override
    public ClassicInterval numsToInterval(double l, double u);

    @Override
    public ClassicInterval numsToInterval(float l, float u);

    @Override
    public ClassicInterval textToInterval(String s);

    @Override
    public ClassicInterval textToDecoratedInterval(String s);

    @Override
    public ClassicInterval pi();

    @Override
    public ClassicInterval euler();

    @Override
    public ClassicInterval neg(ClassicInterval x);

    @Override
    public ClassicInterval add(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval sub(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval mul(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval div(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval recip(ClassicInterval x);

    @Override
    public ClassicInterval sqr(ClassicInterval x);

    @Override
    public ClassicInterval sqrt(ClassicInterval x);

    @Override
    public ClassicInterval fma(ClassicInterval x, ClassicInterval y, ClassicInterval z);

    @Override
    public ClassicInterval pown(ClassicInterval x, BigInteger p);

    @Override
    public ClassicInterval pown(ClassicInterval x, long p);

    @Override
    public ClassicInterval pown(ClassicInterval x, int p);

    @Override
    public ClassicInterval pow(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval exp(ClassicInterval x);

    @Override
    public ClassicInterval exp2(ClassicInterval x);

    @Override
    public ClassicInterval exp10(ClassicInterval x);

    @Override
    public ClassicInterval log(ClassicInterval x);

    @Override
    public ClassicInterval log2(ClassicInterval x);

    @Override
    public ClassicInterval log10(ClassicInterval x);

    @Override
    public ClassicInterval sin(ClassicInterval x);

    @Override
    public ClassicInterval cos(ClassicInterval x);

    @Override
    public ClassicInterval tan(ClassicInterval x);

    @Override
    public ClassicInterval asin(ClassicInterval x);

    @Override
    public ClassicInterval acos(ClassicInterval x);

    @Override
    public ClassicInterval atan(ClassicInterval x);

    @Override
    public ClassicInterval atan2(ClassicInterval y, ClassicInterval x);

    @Override
    public ClassicInterval sinh(ClassicInterval x);

    @Override
    public ClassicInterval cosh(ClassicInterval x);

    @Override
    public ClassicInterval tanh(ClassicInterval x);

    @Override
    public ClassicInterval asinh(ClassicInterval x);

    @Override
    public ClassicInterval acosh(ClassicInterval x);

    @Override
    public ClassicInterval atanh(ClassicInterval x);

    @Override
    public ClassicInterval sign(ClassicInterval x);

    @Override
    public ClassicInterval ceil(ClassicInterval x);

    @Override
    public ClassicInterval floor(ClassicInterval x);

    @Override
    public ClassicInterval trunc(ClassicInterval x);

    @Override
    public ClassicInterval roundTiesToEven(ClassicInterval x);

    @Override
    public ClassicInterval roundTiesToAway(ClassicInterval x);

    @Override
    public ClassicInterval abs(ClassicInterval x);

    @Override
    public ClassicInterval min(ClassicInterval x1, ClassicInterval x2);

    @Override
    public ClassicInterval min(ClassicInterval x1, ClassicInterval x2, ClassicInterval... xn);

    @Override
    public ClassicInterval max(ClassicInterval x1, ClassicInterval x2);

    @Override
    public ClassicInterval max(ClassicInterval x1, ClassicInterval x2, ClassicInterval... xn);

    @Override
    public ClassicInterval cancelMinus(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval cancelPlus(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval intersection(ClassicInterval x, ClassicInterval y);

    @Override
    public ClassicInterval convexHull(ClassicInterval x, ClassicInterval y);
}
