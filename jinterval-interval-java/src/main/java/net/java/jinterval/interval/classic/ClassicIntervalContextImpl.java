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
import net.java.jinterval.interval.Interval;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.rational.DomainException;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 *
 */
class ClassicIntervalContextImpl implements ClassicIntervalContext {

    private final SetIntervalContext impl;

    ClassicIntervalContextImpl(SetIntervalContext impl) {
        this.impl = impl;
    }

    @Override
    public ClassicInterval hull(ClassicInterval x) {
        return checkClassic(impl.hull(x));
    }

    @Override
    public ClassicInterval newDec(ClassicInterval x) {
        return checkClassic(impl.newDec(x));
    }

    @Override
    public ClassicInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
        Interval r = impl.numsToInterval(l, u);
        if (r instanceof ClassicInterval) {
            return (ClassicInterval) r;
        }
        if (l.isNegativeInfinity() || u.isPositiveInfinity()) {
            throw new DomainException();
        }
        throw nonclassic();
    }

    @Override
    public ClassicInterval numsToInterval(double l, double u) {
        Interval r = impl.numsToInterval(l, u);
        if (r instanceof ClassicInterval) {
            return (ClassicInterval) r;
        }
        if (l == Double.NEGATIVE_INFINITY || u == Double.POSITIVE_INFINITY) {
            throw new DomainException();
        }
        throw nonclassic();
    }

    @Override
    public ClassicInterval numsToInterval(float l, float u) {
        Interval r = impl.numsToInterval(l, u);
        if (r instanceof ClassicInterval) {
            return (ClassicInterval) r;
        }
        if (l == Float.NEGATIVE_INFINITY || u == Float.POSITIVE_INFINITY) {
            throw new DomainException();
        }
        throw nonclassic();
    }

    @Override
    public ClassicInterval textToInterval(String s) {
        return checkClassic(impl.textToInterval(s));
    }

    @Override
    public ClassicInterval textToDecoratedInterval(String s) {
        return checkClassic(impl.textToDecoratedInterval(s));
    }

    @Override
    public ClassicInterval pi() {
        return checkClassic(impl.pi());
    }

    @Override
    public ClassicInterval euler() {
        return checkClassic(impl.euler());
    }

    @Override
    public ClassicInterval neg(ClassicInterval x) {
        return checkClassic(impl.neg(x));
    }

    @Override
    public ClassicInterval add(ClassicInterval x, ClassicInterval y) {
        return checkClassic(impl.add(x, y));
    }

    @Override
    public ClassicInterval sub(ClassicInterval x, ClassicInterval y) {
        return checkClassic(impl.sub(x, y));
    }

    @Override
    public ClassicInterval mul(ClassicInterval x, ClassicInterval y) {
        return checkClassic(impl.mul(x, y));
    }

    @Override
    public ClassicInterval div(ClassicInterval x, ClassicInterval y) {
        if (Utils.ZERO.subset(y)) {
            throw new DomainException();
        }
        return checkClassic(impl.div(x, y));
    }

    @Override
    public ClassicInterval recip(ClassicInterval x) {
        if (Utils.ZERO.subset(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.recip(x));
    }

    @Override
    public ClassicInterval sqr(ClassicInterval x) {
        return checkClassic(impl.sqr(x));
    }

    @Override
    public ClassicInterval sqrt(ClassicInterval x) {
        if (!Utils.ZERO.precedes(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.sqrt(x));
    }

    @Override
    public ClassicInterval fma(ClassicInterval x, ClassicInterval y, ClassicInterval z) {
        return checkClassic(impl.fma(x, y, z));
    }

    @Override
    public ClassicInterval pown(ClassicInterval x, BigInteger p) {
        if (p.signum() < 0 && Utils.ZERO.subset(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.pown(x, p));
    }

    @Override
    public ClassicInterval pown(ClassicInterval x, long p) {
        if (p < 0 && Utils.ZERO.subset(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.pown(x, p));
    }

    @Override
    public ClassicInterval pown(ClassicInterval x, int p) {
        if (p < 0 && Utils.ZERO.subset(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.pown(x, p));
    }

    @Override
    public ClassicInterval pow(ClassicInterval x, ClassicInterval y) {
        if (!Utils.ZERO.precedes(x) || Utils.ZERO.subset(x) && !Utils.ZERO.strictPrecedes(y)) {
            throw new DomainException();
        }
        return checkClassic(impl.pow(x, y));
    }

    @Override
    public ClassicInterval exp(ClassicInterval x) {
        return checkClassic(impl.exp(x));
    }

    @Override
    public ClassicInterval exp2(ClassicInterval x) {
        return checkClassic(impl.exp2(x));
    }

    @Override
    public ClassicInterval exp10(ClassicInterval x) {
        return checkClassic(impl.exp10(x));
    }

    @Override
    public ClassicInterval log(ClassicInterval x) {
        if (!Utils.ZERO.strictPrecedes(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.log(x));
    }

    @Override
    public ClassicInterval log2(ClassicInterval x) {
        if (!Utils.ZERO.strictPrecedes(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.log2(x));
    }

    @Override
    public ClassicInterval log10(ClassicInterval x) {
        if (!Utils.ZERO.strictPrecedes(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.log10(x));
    }

    @Override
    public ClassicInterval sin(ClassicInterval x) {
        return checkClassic(impl.sin(x));
    }

    @Override
    public ClassicInterval cos(ClassicInterval x) {
        return checkClassic(impl.cos(x));
    }

    @Override
    public ClassicInterval tan(ClassicInterval x) {
        if (!x.isCommonInterval()) {
            throw new DomainException();
        }
        Interval r = impl.tan(x);
        if (!(r instanceof ClassicInterval)) { // TODO throw DomainException when x contains (k + 1/2)*pi
            throw nonclassic();
        }
        return (ClassicInterval) r;
    }

    @Override
    public ClassicInterval asin(ClassicInterval x) {
        if (!x.subset(Utils.M1P1)) {
            throw new DomainException();
        }
        return checkClassic(impl.asin(x));
    }

    @Override
    public ClassicInterval acos(ClassicInterval x) {
        if (!x.subset(Utils.M1P1)) {
            throw new DomainException();
        }
        return checkClassic(impl.acos(x));
    }

    @Override
    public ClassicInterval atan(ClassicInterval x) {
        return checkClassic(impl.atan(x));
    }

    @Override
    public ClassicInterval atan2(ClassicInterval y, ClassicInterval x) {
        if (Utils.ZERO.subset(y) && !Utils.ZERO.strictPrecedes(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.atan2(y, x));
    }

    @Override
    public ClassicInterval sinh(ClassicInterval x) {
        return checkClassic(impl.sinh(x));
    }

    @Override
    public ClassicInterval cosh(ClassicInterval x) {
        return checkClassic(impl.cosh(x));
    }

    @Override
    public ClassicInterval tanh(ClassicInterval x) {
        return checkClassic(impl.tanh(x));
    }

    @Override
    public ClassicInterval asinh(ClassicInterval x) {
        return checkClassic(impl.asinh(x));
    }

    @Override
    public ClassicInterval acosh(ClassicInterval x) {
        if (!Utils.M1P1.precedes(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.acosh(x));
    }

    @Override
    public ClassicInterval atanh(ClassicInterval x) {
        if (!x.interior(Utils.M1P1)) {
            throw new DomainException();
        }
        return checkClassic(impl.atanh(x));
    }

    @Override
    public ClassicInterval sign(ClassicInterval x) {
        if (Utils.ZERO.subset(x)) {
            throw new DomainException();
        }
        return checkClassic(impl.sign(x));
    }

    @Override
    public ClassicInterval ceil(ClassicInterval x) {
        Rational inf = (Rational) x.inf();
        Rational sup = (Rational) x.sup();
        Rational infR = RationalOps.ceil(inf);
        Rational supR = RationalOps.ceil(sup);
        if (infR.ne(supR) || inf.le(RationalOps.sub(infR, Rational.one())) || sup.ge(supR)) {
            throw new DomainException();
        }
        return checkClassic(impl.ceil(x));
    }

    @Override
    public ClassicInterval floor(ClassicInterval x) {
        Rational inf = (Rational) x.inf();
        Rational sup = (Rational) x.sup();
        Rational infR = RationalOps.floor(inf);
        Rational supR = RationalOps.floor(sup);
        if (infR.ne(supR) || inf.le(infR) || sup.ge(RationalOps.add(supR, Rational.one()))) {
            throw new DomainException();
        }
        return checkClassic(impl.floor(x));
    }

    @Override
    public ClassicInterval trunc(ClassicInterval x) {
        Rational inf = (Rational) x.inf();
        Rational sup = (Rational) x.sup();
        Rational infR = RationalOps.trunc(inf);
        Rational supR = RationalOps.trunc(sup);
        if (infR.ne(supR)) {
            throw new DomainException();
        }
        if (infR.signum() > 0) {
            if (inf.le(infR) || sup.ge(RationalOps.add(supR, Rational.one()))) {
                throw new DomainException();
            }
        } else if (supR.signum() < 0) {
            if (inf.le(RationalOps.sub(infR, Rational.one())) || sup.ge(supR)) {
                throw new DomainException();
            }
        } else if (!x.interior(Utils.M1P1)) {
            throw new DomainException();
        }
        return checkClassic(impl.trunc(x));
    }

    @Override
    public ClassicInterval roundTiesToEven(ClassicInterval x) {
        Rational inf = (Rational) x.inf();
        Rational sup = (Rational) x.sup();
        Rational infR = RationalOps.roundTiesToEven(inf);
        Rational supR = RationalOps.roundTiesToEven(sup);
        if (infR.ne(supR) || inf.le(RationalOps.sub(infR, Utils.RAT_HALF)) || sup.ge(RationalOps.add(supR, Utils.RAT_HALF))) {
            throw new DomainException();
        }
        return checkClassic(impl.roundTiesToEven(x));
    }

    @Override
    public ClassicInterval roundTiesToAway(ClassicInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ClassicInterval abs(ClassicInterval x) {
        return checkClassic(impl.abs(x));
    }

    @Override
    public ClassicInterval min(ClassicInterval x1, ClassicInterval x2) {
        return checkClassic(impl.min(x1, x2));
    }

    @Override
    public ClassicInterval min(ClassicInterval x1, ClassicInterval x2, ClassicInterval... xn) {
        return checkClassic(impl.min(x1, x2, xn));
    }

    @Override
    public ClassicInterval max(ClassicInterval x1, ClassicInterval x2) {
        return checkClassic(impl.max(x1, x2));
    }

    @Override
    public ClassicInterval max(ClassicInterval x1, ClassicInterval x2, ClassicInterval... xn) {
        return checkClassic(impl.max(x1, x2, xn));
    }

    @Override
    public ClassicInterval cancelMinus(ClassicInterval x, ClassicInterval y) {
        return checkClassic(impl.cancelMinus(x, y));
    }

    @Override
    public ClassicInterval cancelPlus(ClassicInterval x, ClassicInterval y) {
        return checkClassic(impl.cancelPlus(x, y));
    }

    @Override
    public ClassicInterval intersection(ClassicInterval x, ClassicInterval y) {
        if (x.disjoint(y)) {
            throw new DomainException();
        }
        return checkClassic(impl.intersection(x, y));
    }

    @Override
    public ClassicInterval convexHull(ClassicInterval x, ClassicInterval y) {
        return checkClassic(impl.convexHull(x, y));
    }

    private static ClassicInterval checkClassic(Interval r) {
        if (r instanceof ClassicInterval /*&& r.getDecoration() == Decoration.COM*/) {
            return (ClassicInterval) r;
        }
        throw nonclassic();
    }

    private static ArithmeticException nonclassic() {
        return new ArithmeticException("nonclassic");
    }
}
