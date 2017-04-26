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
package net.java.jinterval.complex;

import net.java.jinterval.rational.DomainException;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.interval.classic.ClassicIntervalContext;
import net.java.jinterval.interval.classic.ClassicIntervalContexts;

/**
 *
 */
public class ComplexIntervalContextBoxRational implements ComplexIntervalContext {

    private final ClassicIntervalContext impl;

    ComplexIntervalContextBoxRational() {
        this.impl = ClassicIntervalContexts.getExact();
    }

    public ComplexInterval hull(ComplexInterval x) {
        if (x instanceof ComplexIntervalRationalBox) {
            return x;
        }
        return new ComplexIntervalRationalBox(
                x.realInf(),
                x.realSup(),
                x.imagInf(),
                x.imagSup(),
                x.possiblyUndefined());
    }

    public ComplexInterval nums2interval(ExtendedRational rl, ExtendedRational ru, ExtendedRational il, ExtendedRational iu) {
        if (!rl.le(ru) || !il.le(iu)
                || rl.isPositiveInfinity() || ru.isNegativeInfinity()
                || il.isPositiveInfinity() || iu.isNegativeInfinity()) {
            throw new DomainException();
        }
        return new ComplexIntervalRationalBox(rl, ru, il, iu, false);
    }

    public ComplexInterval nums2interval(double rl, double ru, double il, double iu) {
        if (!(rl <= ru) || !(il <= iu)
                || rl == Double.POSITIVE_INFINITY || ru == Double.NEGATIVE_INFINITY
                || il == Double.POSITIVE_INFINITY || iu == Double.NEGATIVE_INFINITY) {
            throw new DomainException();
        }
        return new ComplexIntervalRationalBox(ExtendedRational.valueOf(rl), ExtendedRational.valueOf(ru),
                ExtendedRational.valueOf(il), ExtendedRational.valueOf(iu), false);
    }

    public ComplexInterval nums2interval(float rl, float ru, float il, float iu) {
        return nums2interval((double) rl, (double) ru, (double) il, (double) iu);
    }

    public ComplexInterval negate(ComplexInterval x) {
        return new ComplexIntervalRationalBox(
                ExtendedRationalOps.neg(x.realSup()),
                ExtendedRationalOps.neg(x.realInf()),
                ExtendedRationalOps.neg(x.imagSup()),
                ExtendedRationalOps.neg(x.imagInf()),
                x.possiblyUndefined());
    }

    public ComplexInterval add(ComplexInterval x, ComplexInterval y) {
        return new ComplexIntervalRationalBox(
                ExtendedRationalOps.add(x.realInf(), x.realInf()),
                ExtendedRationalOps.add(x.realSup(), x.realSup()),
                ExtendedRationalOps.add(x.imagInf(), x.imagInf()),
                ExtendedRationalOps.add(x.imagSup(), x.imagSup()),
                x.possiblyUndefined() | y.possiblyUndefined());
    }

    public ComplexInterval subtract(ComplexInterval x, ComplexInterval y) {
        return new ComplexIntervalRationalBox(
                ExtendedRationalOps.sub(x.realInf(), x.realSup()),
                ExtendedRationalOps.sub(x.realSup(), x.realInf()),
                ExtendedRationalOps.sub(x.imagInf(), x.imagSup()),
                ExtendedRationalOps.sub(x.imagSup(), x.imagInf()),
                x.possiblyUndefined() | y.possiblyUndefined());
    }

    public ComplexInterval multiply(ComplexInterval x, ComplexInterval y) {
        ClassicInterval x_real = impl.numsToInterval(x.realInf(), x.realSup());
        ClassicInterval x_imag = impl.numsToInterval(x.imagInf(), x.imagSup());
        ClassicInterval y_real = impl.numsToInterval(y.realInf(), y.realSup());
        ClassicInterval y_imag = impl.numsToInterval(y.imagInf(), y.imagSup());
        ClassicInterval real = impl.sub(impl.mul(x_real, y_real), impl.mul(x_imag, y_imag));
        ClassicInterval imag = impl.add(impl.mul(x_real, y_imag), impl.mul(x_real, y_imag));
        return new ComplexIntervalRationalBox(
                real.inf(), real.sup(),
                imag.inf(), imag.sup(),
                x.possiblyUndefined() | y.possiblyUndefined());
    }

    public ComplexInterval divide(ComplexInterval x, ComplexInterval y) {
        ClassicInterval x_real = impl.numsToInterval(x.realInf(), x.realSup());
        ClassicInterval x_imag = impl.numsToInterval(x.imagInf(), x.imagSup());
        ClassicInterval y_real = impl.numsToInterval(y.realInf(), y.realSup());
        ClassicInterval y_imag = impl.numsToInterval(y.imagInf(), y.imagSup());
        ClassicInterval real = impl.add(impl.mul(x_real, y_real), impl.mul(x_imag, y_imag));
        ClassicInterval imag = impl.sub(impl.mul(x_real, y_imag), impl.mul(x_real, y_imag));
        ClassicInterval k = impl.numsToInterval(ExtendedRational.one(), ExtendedRational.one());
        k = impl.div(k, impl.add(impl.pown(y_real, 2), impl.pown(y_imag, 2)));
        real = impl.mul(k, real);
        imag = impl.mul(k, imag);
        return new ComplexIntervalRationalBox(
                real.inf(), real.sup(),
                imag.inf(), imag.sup(),
                x.possiblyUndefined() | y.possiblyUndefined());
    }

    public ComplexInterval recip(ComplexInterval x) {
        ClassicInterval real = impl.recip(impl.numsToInterval(x.realInf(), x.realSup()));
        ClassicInterval imag = impl.recip(impl.numsToInterval(x.imagInf(), x.imagSup()));
        return new ComplexIntervalRationalBox(
                real.inf(), real.sup(),
                imag.inf(), imag.sup(),
                x.possiblyUndefined());
    }

    public ComplexInterval fma(ComplexInterval x, ComplexInterval y, ComplexInterval z) {
        ComplexInterval xy = multiply(x, y);
        return add(xy, z);
    }
}