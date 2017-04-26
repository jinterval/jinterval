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
package net.java.jinterval.interval.set;

import java.math.BigInteger;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.IntervalContext;
import net.java.jinterval.rational.ExtendedRational;

/**
 *
 */
public interface SetIntervalContext extends IntervalContext<SetInterval> {

    @Override
    public SetInterval hull(SetInterval x);

    public SetInterval empty();

    public SetInterval entire();

    public SetInterval nai();

    @Override
    public SetInterval numsToInterval(ExtendedRational l, ExtendedRational u);

    @Override
    public SetInterval numsToInterval(double l, double u);

    @Override
    public SetInterval numsToInterval(float l, float u);

    public SetInterval numsDecToInterval(ExtendedRational l, ExtendedRational u, Decoration decoration);

    public SetInterval numsDecToInterval(double l, double u, Decoration decoration);

    public SetInterval numsDecToInterval(float l, float u, Decoration decoration);

    @Override
    public SetInterval textToInterval(String s);

    @Override
    public SetInterval textToDecoratedInterval(String s);

    @Override
    public SetInterval pi();

    @Override
    public SetInterval euler();

    @Override
    public SetInterval neg(SetInterval x);

    @Override
    public SetInterval add(SetInterval x, SetInterval y);

    @Override
    public SetInterval sub(SetInterval x, SetInterval y);

    @Override
    public SetInterval mul(SetInterval x, SetInterval y);

    @Override
    public SetInterval div(SetInterval x, SetInterval y);

    @Override
    public SetInterval recip(SetInterval x);

    @Override
    public SetInterval sqr(SetInterval x);

    @Override
    public SetInterval sqrt(SetInterval x);

    @Override
    public SetInterval fma(SetInterval x, SetInterval y, SetInterval z);

    @Override
    public SetInterval pown(SetInterval x, BigInteger p);

    @Override
    public SetInterval pown(SetInterval x, long p);

    @Override
    public SetInterval pown(SetInterval x, int p);

    @Override
    public SetInterval pow(SetInterval x, SetInterval y);

    @Override
    public SetInterval exp(SetInterval x);

    @Override
    public SetInterval exp2(SetInterval x);

    @Override
    public SetInterval exp10(SetInterval x);

    @Override
    public SetInterval log(SetInterval x);

    @Override
    public SetInterval log2(SetInterval x);

    @Override
    public SetInterval log10(SetInterval x);

    @Override
    public SetInterval sin(SetInterval x);

    @Override
    public SetInterval cos(SetInterval x);

    @Override
    public SetInterval tan(SetInterval x);

    @Override
    public SetInterval asin(SetInterval x);

    @Override
    public SetInterval acos(SetInterval x);

    @Override
    public SetInterval atan(SetInterval x);

    @Override
    public SetInterval atan2(SetInterval y, SetInterval x);

    @Override
    public SetInterval sinh(SetInterval x);

    @Override
    public SetInterval cosh(SetInterval x);

    @Override
    public SetInterval tanh(SetInterval x);

    @Override
    public SetInterval asinh(SetInterval x);

    @Override
    public SetInterval acosh(SetInterval x);

    @Override
    public SetInterval atanh(SetInterval x);

    @Override
    public SetInterval sign(SetInterval x);

    @Override
    public SetInterval ceil(SetInterval x);

    @Override
    public SetInterval floor(SetInterval x);

    @Override
    public SetInterval trunc(SetInterval x);

    @Override
    public SetInterval roundTiesToEven(SetInterval x);

    @Override
    public SetInterval roundTiesToAway(SetInterval x);

    @Override
    public SetInterval abs(SetInterval x);

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2);

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2, SetInterval... xn);

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2);

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2, SetInterval... xn);

    public SetInterval sqrRev(SetInterval c, SetInterval x);

    public SetInterval absRev(SetInterval c, SetInterval x);

    public SetInterval pownRev(SetInterval c, SetInterval x, BigInteger p);

    public SetInterval pownRev(SetInterval c, SetInterval x, long p);

    public SetInterval pownRev(SetInterval c, SetInterval x, int p);

    public SetInterval sinRev(SetInterval c, SetInterval x);

    public SetInterval cosRev(SetInterval c, SetInterval x);

    public SetInterval tanRev(SetInterval c, SetInterval x);

    public SetInterval coshRev(SetInterval c, SetInterval x);

    public SetInterval mulRev(SetInterval b, SetInterval c, SetInterval x);

    public SetInterval powRev1(SetInterval b, SetInterval c, SetInterval x);

    public SetInterval powRev2(SetInterval a, SetInterval c, SetInterval x);

    public SetInterval atan2Rev1(SetInterval b, SetInterval c, SetInterval x);

    public SetInterval atan2Rev2(SetInterval a, SetInterval c, SetInterval x);

    public MulRevPair mulRevToPair(SetInterval b, SetInterval c);

    @Override
    public SetInterval cancelMinus(SetInterval x, SetInterval y);

    @Override
    public SetInterval cancelPlus(SetInterval x, SetInterval y);

    @Override
    public SetInterval intersection(SetInterval x, SetInterval y);

    @Override
    public SetInterval convexHull(SetInterval x, SetInterval y);

    public SetInterval setDec(SetInterval x, Decoration dec);

    public SetInterval rootn(SetInterval x, BigInteger q);

    public SetInterval rootn(SetInterval x, long q);

    public SetInterval rootn(SetInterval x, int q);

    public SetInterval hypot(SetInterval x, SetInterval y);
}
