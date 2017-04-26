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

/**
 *
 */
public class ComplexIntervalContextBoxFast implements ComplexIntervalContext {

    public ComplexInterval hull(ComplexInterval x) {
        if (x instanceof ComplexIntervalDoubleBox) {
            return x;
        }
        return new ComplexIntervalDoubleBox(
                x.doubleRealInf(),
                x.doubleRealSup(),
                x.doubleImagInf(),
                x.doubleImagSup(),
                x.possiblyUndefined());
    }

    public ComplexInterval nums2interval(ExtendedRational rl, ExtendedRational ru, ExtendedRational il, ExtendedRational iu) {
        if (!rl.le(ru) || !il.le(iu)
                || rl.isPositiveInfinity() || ru.isNegativeInfinity()
                || il.isPositiveInfinity() || iu.isNegativeInfinity()) {
            throw new DomainException();
        }
        return nums2interval(rl.doubleValueFloor(), ru.doubleValueCeiling(),
                il.doubleValueFloor(), iu.doubleValueCeiling());
    }

    public ComplexInterval nums2interval(double rl, double ru, double il, double iu) {
        if (!(rl <= ru) || !(il <= iu)
                || rl == Double.POSITIVE_INFINITY || ru == Double.NEGATIVE_INFINITY
                || il == Double.POSITIVE_INFINITY || iu == Double.NEGATIVE_INFINITY) {
            throw new DomainException();
        }
        return new ComplexIntervalDoubleBox(rl, ru, il, iu, false);
    }

    public ComplexInterval nums2interval(float rl, float ru, float il, float iu) {
        return nums2interval((double) rl, (double) ru, (double) il, (double) iu);
    }

    public ComplexInterval negate(ComplexInterval x) {
        return new ComplexIntervalDoubleBox(
                -x.doubleRealSup(),
                -x.doubleRealInf(),
                -x.doubleImagSup(),
                -x.doubleImagInf(),
                x.possiblyUndefined());
    }

    public ComplexInterval add(ComplexInterval x, ComplexInterval y) {
        return new ComplexIntervalDoubleBox(
                x.doubleRealInf() + x.doubleRealInf(),
                x.doubleRealSup() + x.doubleRealSup(),
                x.doubleImagInf() + x.doubleImagInf(),
                x.doubleImagSup() + x.doubleImagSup(),
                x.possiblyUndefined() | y.possiblyUndefined());
    }

    public ComplexInterval subtract(ComplexInterval x, ComplexInterval y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ComplexInterval multiply(ComplexInterval x, ComplexInterval y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ComplexInterval divide(ComplexInterval x, ComplexInterval y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ComplexInterval recip(ComplexInterval x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ComplexInterval fma(ComplexInterval x, ComplexInterval y, ComplexInterval z) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
