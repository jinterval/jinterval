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
package net.java.jinterval.interval;

import java.math.BigInteger;
import net.java.jinterval.rational.ExtendedRational;

/**
 *
 */
public interface IntervalContext<I extends Interval> {

    public I hull(I x);

    public I newDec(I x);

    public I numsToInterval(ExtendedRational l, ExtendedRational u);

    public I numsToInterval(double l, double u);

    public I numsToInterval(float l, float u);

    public I textToInterval(String s);

    public I textToDecoratedInterval(String s);

    public I pi();

    public I euler();

    public I neg(I x);

    public I add(I x, I y);

    public I sub(I x, I y);

    public I mul(I x, I y);

    public I div(I x, I y);

    public I recip(I x);

    public I sqr(I x);

    public I sqrt(I x);

    public I fma(I x, I y, I z);

    public I pown(I x, BigInteger p);

    public I pown(I x, long p);

    public I pown(I x, int p);

    public I pow(I x, I y);

    public I exp(I x);

    public I exp2(I x);

    public I exp10(I x);

    public I log(I x);

    public I log2(I x);

    public I log10(I x);

    public I sin(I x);

    public I cos(I x);

    public I tan(I x);

    public I asin(I x);

    public I acos(I x);

    public I atan(I x);

    public I atan2(I y, I x);

    public I sinh(I x);

    public I cosh(I x);

    public I tanh(I x);

    public I asinh(I x);

    public I acosh(I x);

    public I atanh(I x);

    public I sign(I x);

    public I ceil(I x);

    public I floor(I x);

    public I trunc(I x);

    public I roundTiesToEven(I x);

    public I roundTiesToAway(I x);

    public I abs(I x);

    public I min(I x1, I x2);

    public I min(I x1, I x2, I... xn);

    public I max(I x1, I x2);

    public I max(I x1, I x2, I... xn);

    public I cancelMinus(I x, I y);

    public I cancelPlus(I x, I y);

    public I intersection(I x, I y);

    public I convexHull(I x, I y);
}
