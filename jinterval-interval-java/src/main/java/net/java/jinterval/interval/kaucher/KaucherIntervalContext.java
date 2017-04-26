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
package net.java.jinterval.interval.kaucher;

import java.math.BigInteger;
import net.java.jinterval.interval.IntervalContext;
import net.java.jinterval.rational.ExtendedRational;

/**
 *
 */
public interface KaucherIntervalContext extends IntervalContext<KaucherInterval> {

    @Override
    public KaucherInterval hull(KaucherInterval x);

    @Override
    public KaucherInterval numsToInterval(ExtendedRational l, ExtendedRational u);

    @Override
    public KaucherInterval numsToInterval(double l, double u);

    @Override
    public KaucherInterval numsToInterval(float l, float u);

    @Override
    public KaucherInterval textToInterval(String s);

    @Override
    public KaucherInterval textToDecoratedInterval(String s);

    @Override
    public KaucherInterval pi();

    @Override
    public KaucherInterval euler();

    @Override
    public KaucherInterval neg(KaucherInterval x);

    @Override
    public KaucherInterval add(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval sub(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval mul(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval div(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval recip(KaucherInterval x);

    @Override
    public KaucherInterval sqr(KaucherInterval x);

    @Override
    public KaucherInterval sqrt(KaucherInterval x);

    @Override
    public KaucherInterval fma(KaucherInterval x, KaucherInterval y, KaucherInterval z);

    @Override
    public KaucherInterval pown(KaucherInterval x, BigInteger p);

    @Override
    public KaucherInterval pown(KaucherInterval x, long p);

    @Override
    public KaucherInterval pown(KaucherInterval x, int p);

    @Override
    public KaucherInterval pow(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval exp(KaucherInterval x);

    @Override
    public KaucherInterval exp2(KaucherInterval x);

    @Override
    public KaucherInterval exp10(KaucherInterval x);

    @Override
    public KaucherInterval log(KaucherInterval x);

    @Override
    public KaucherInterval log2(KaucherInterval x);

    @Override
    public KaucherInterval log10(KaucherInterval x);

    @Override
    public KaucherInterval sin(KaucherInterval x);

    @Override
    public KaucherInterval cos(KaucherInterval x);

    @Override
    public KaucherInterval tan(KaucherInterval x);

    @Override
    public KaucherInterval asin(KaucherInterval x);

    @Override
    public KaucherInterval acos(KaucherInterval x);

    @Override
    public KaucherInterval atan(KaucherInterval x);

    @Override
    public KaucherInterval atan2(KaucherInterval y, KaucherInterval x);

    @Override
    public KaucherInterval sinh(KaucherInterval x);

    @Override
    public KaucherInterval cosh(KaucherInterval x);

    @Override
    public KaucherInterval tanh(KaucherInterval x);

    @Override
    public KaucherInterval asinh(KaucherInterval x);

    @Override
    public KaucherInterval acosh(KaucherInterval x);

    @Override
    public KaucherInterval atanh(KaucherInterval x);

    @Override
    public KaucherInterval sign(KaucherInterval x);

    @Override
    public KaucherInterval ceil(KaucherInterval x);

    @Override
    public KaucherInterval trunc(KaucherInterval x);

    @Override
    public KaucherInterval floor(KaucherInterval x);

    @Override
    public KaucherInterval roundTiesToEven(KaucherInterval x);

    @Override
    public KaucherInterval roundTiesToAway(KaucherInterval x);

    @Override
    public KaucherInterval abs(KaucherInterval x);

    @Override
    public KaucherInterval min(KaucherInterval x1, KaucherInterval x2);

    @Override
    public KaucherInterval min(KaucherInterval x1, KaucherInterval x2, KaucherInterval... xn);

    @Override
    public KaucherInterval max(KaucherInterval x1, KaucherInterval x2);

    @Override
    public KaucherInterval max(KaucherInterval x1, KaucherInterval x2, KaucherInterval... xn);

    @Override
    public KaucherInterval cancelMinus(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval cancelPlus(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval intersection(KaucherInterval x, KaucherInterval y);

    @Override
    public KaucherInterval convexHull(KaucherInterval x, KaucherInterval y);
}
