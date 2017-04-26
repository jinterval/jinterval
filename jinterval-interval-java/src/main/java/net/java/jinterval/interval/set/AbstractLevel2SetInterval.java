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
import net.java.jinterval.interval.Interval;
import net.java.jinterval.interval.MidRad;
import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
abstract class AbstractLevel2SetInterval<I extends AbstractLevel2SetInterval> implements SetInterval {

    final SetInterval impl;

    AbstractLevel2SetInterval(SetInterval impl) {
        this.impl = impl;
    }

    abstract SetIntervalContext ctx();

    abstract I valueOf(SetInterval impl);

    public I neg() {
        return valueOf(ctx().neg(this.impl));
    }

    public I add(I that) {
        return valueOf(ctx().add(this.impl, that.impl));
    }

    public I sub(I that) {
        return valueOf(ctx().sub(this.impl, that.impl));
    }

    public I mul(I that) {
        return valueOf(ctx().mul(this.impl, that.impl));
    }

    public I div(I that) {
        return valueOf(ctx().div(this.impl, that.impl));
    }

    public I recip() {
        return valueOf(ctx().recip(this.impl));
    }

    public I sqr(SetInterval x) {
        return valueOf(ctx().sqr(this.impl));
    }

    public I sqrt() {
        return valueOf(ctx().sqrt(this.impl));
    }

    public I fma(I y, I z) {
        return valueOf(ctx().fma(this.impl, y.impl, z.impl));
    }

    public I pown(BigInteger p) {
        return valueOf(ctx().pown(this.impl, p));
    }

    public I pown(long p) {
        return valueOf(ctx().pown(this.impl, p));
    }

    public I pown(int p) {
        return valueOf(ctx().pown(this.impl, p));
    }

    public I pow(I that) {
        return valueOf(ctx().pow(this.impl, that.impl));
    }

    public I exp() {
        return valueOf(ctx().exp(this.impl));
    }

    public I exp2() {
        return valueOf(ctx().exp2(this.impl));
    }

    public I exp10() {
        return valueOf(ctx().exp10(this.impl));
    }

    public I log() {
        return valueOf(ctx().log(this.impl));
    }

    public I log2() {
        return valueOf(ctx().log2(this.impl));
    }

    public I log10() {
        return valueOf(ctx().log10(this.impl));
    }

    public I sin() {
        return valueOf(ctx().sin(this.impl));
    }

    public I cos() {
        return valueOf(ctx().cos(this.impl));
    }

    public I tan() {
        return valueOf(ctx().tan(this.impl));
    }

    public I asin() {
        return valueOf(ctx().asin(this.impl));
    }

    public I acos() {
        return valueOf(ctx().acos(this.impl));
    }

    public I atan() {
        return valueOf(ctx().atan(this.impl));
    }

    public I atan2(I that) {
        return valueOf(ctx().atan2(this.impl, that.impl));
    }

    public I sinh() {
        return valueOf(ctx().sinh(this.impl));
    }

    public I cosh() {
        return valueOf(ctx().cosh(this.impl));
    }

    public I tanh() {
        return valueOf(ctx().tanh(this.impl));
    }

    public I asinh() {
        return valueOf(ctx().asinh(this.impl));
    }

    public I acosh() {
        return valueOf(ctx().acosh(this.impl));
    }

    public I atanh() {
        return valueOf(ctx().atanh(this.impl));
    }

    public I sign() {
        return valueOf(ctx().sign(this.impl));
    }

    public I ceil() {
        return valueOf(ctx().ceil(this.impl));
    }

    public I floor() {
        return valueOf(ctx().floor(this.impl));
    }

    public I roundTiesToEven() {
        return valueOf(ctx().roundTiesToEven(this.impl));
    }

    public I roundTiesToAway() {
        return valueOf(ctx().roundTiesToEven(this.impl));
    }

    public I trunc() {
        return valueOf(ctx().trunc(this.impl));
    }

    public I abs() {
        return valueOf(ctx().abs(this.impl));
    }

    public I min(I that) {
        return valueOf(ctx().min(this.impl, that.impl));
    }

    public I min(I x2, I... xn) {
        SetInterval[] xni = new SetInterval[xn.length];
        for (int i = 0; i < xni.length; i++) {
            xni[i] = xn[i].impl;
        }
        return valueOf(ctx().min(this.impl, x2.impl, xni));
    }

    public I max(I that) {
        return valueOf(ctx().max(this.impl, that.impl));
    }

    public I max(I x2, I... xn) {
        SetInterval[] xni = new SetInterval[xn.length];
        for (int i = 0; i < xni.length; i++) {
            xni[i] = xn[i].impl;
        }
        return valueOf(ctx().max(this.impl, x2.impl, xni));
    }

    public I innerPlus(I that) {
        return valueOf(ctx().cancelPlus(this.impl, that.impl));
    }

    public I innerMinus(I that) {
        return valueOf(ctx().cancelMinus(this.impl, that.impl));
    }

    public I intersection(I that) {
        return valueOf(ctx().intersection(this.impl, that.impl));
    }

    public I convexHull(I that) {
        return valueOf(ctx().convexHull(this.impl, that.impl));
    }

    public I rootn(BigInteger q) {
        return valueOf(ctx().pown(this.impl, q));
    }

    public I rootn(long q) {
        return valueOf(ctx().pown(this.impl, q));
    }

    public I rootn(int q) {
        return valueOf(ctx().pown(this.impl, q));
    }

    public I hypot(I that) {
        return valueOf(ctx().hypot(this.impl, that.impl));
    }

    @Override
    public ExtendedRational inf() {
        return impl.inf();
    }

    @Override
    public ExtendedRational inf(BinaryValueSet numberFormat) {
        return impl.inf(numberFormat);
    }

    @Override
    public double doubleInf() {
        return impl.doubleInf();
    }

    @Override
    public float floatInf() {
        return impl.floatInf();
    }

    @Override
    public ExtendedRational sup() {
        return impl.sup();
    }

    @Override
    public ExtendedRational sup(BinaryValueSet numberFormat) {
        return impl.sup(numberFormat);
    }

    @Override
    public double doubleSup() {
        return impl.doubleSup();
    }

    @Override
    public float floatSup() {
        return impl.floatSup();
    }

    @Override
    public Rational mid() {
        return impl.mid();
    }

    @Override
    public Rational mid(BinaryValueSet numberFormat) {
        return impl.mid(numberFormat);
    }

    @Override
    public double doubleMid() {
        return impl.doubleMid();
    }

    @Override
    public float floatMid() {
        return impl.floatMid();
    }

    @Override
    public ExtendedRational wid() {
        return impl.wid();
    }

    @Override
    public ExtendedRational wid(BinaryValueSet numberFormat) {
        return impl.wid(numberFormat);
    }

    @Override
    public double doubleWid() {
        return impl.doubleWid();
    }

    @Override
    public float floatWid() {
        return impl.floatWid();
    }

    @Override
    public ExtendedRational rad() {
        return impl.rad();
    }

    @Override
    public ExtendedRational rad(BinaryValueSet numberFormat) {
        return impl.rad(numberFormat);
    }

    @Override
    public double doubleRad() {
        return impl.doubleRad();
    }

    @Override
    public float floatRad() {
        return impl.floatRad();
    }

    @Override
    public MidRad midRad() {
        return impl.midRad();
    }

    @Override
    public MidRad midRad(BinaryValueSet midNumberFormat, BinaryValueSet radNumberFormat) {
        return impl.midRad(midNumberFormat, radNumberFormat);
    }

    @Override
    public ExtendedRational mag() {
        return impl.mag();
    }

    @Override
    public ExtendedRational mag(BinaryValueSet numberFormat) {
        return impl.mag(numberFormat);
    }

    @Override
    public double doubleMag() {
        return impl.doubleMag();
    }

    @Override
    public float floatMag() {
        return impl.floatMag();
    }

    @Override
    public ExtendedRational mig() {
        return impl.mig();
    }

    @Override
    public ExtendedRational mig(BinaryValueSet numberFormat) {
        return impl.mig(numberFormat);
    }

    @Override
    public double doubleMig() {
        return impl.doubleMig();
    }

    @Override
    public float floatMig() {
        return impl.floatMig();
    }

    @Override
    public boolean isEmpty() {
        return impl.isEmpty();
    }

    @Override
    public boolean isEntire() {
        return impl.isEntire();
    }

    @Override
    public boolean isNaI() {
        return impl.isNaI();
    }

    @Override
    public boolean isCommonInterval() {
        return impl.isCommonInterval();
    }

    @Override
    public boolean isSingleton() {
        return impl.isSingleton();
    }

    @Override
    public boolean isMember(ExtendedRational m) {
        return impl.isMember(m);
    }

    @Override
    public boolean isMember(double m) {
        return impl.isMember(m);
    }

    @Override
    public boolean isMember(float m) {
        return impl.isMember(m);
    }

    @Override
    public boolean equal(Interval that) {
        return impl.equal(that);
    }

    @Override
    public boolean subset(Interval that) {
        return impl.subset(that);
    }

    @Override
    public boolean less(Interval that) {
        return impl.less(that);
    }

    @Override
    public boolean precedes(Interval that) {
        return impl.precedes(that);
    }

    @Override
    public boolean interior(Interval that) {
        return impl.interior(that);
    }

    @Override
    public boolean strictLess(Interval that) {
        return impl.strictLess(that);
    }

    @Override
    public boolean strictPrecedes(Interval that) {
        return impl.strictPrecedes(that);
    }

    @Override
    public boolean disjoint(Interval that) {
        return impl.disjoint(that);
    }

    @Override
    public OverlapState overlap(Interval that) {
        return impl.overlap(that);
    }

    @Override
    public Decoration getDecoration() {
        return impl.getDecoration();
    }

    @Override
    public String intervalToExact(BinaryValueSet valueSet) {
        return impl.intervalToExact(valueSet);
    }

    @Override
    public String intervalToExactDecorated(BinaryValueSet valueSet) {
        return impl.intervalToExactDecorated(valueSet);
    }

    @Override
    public int hashCode() {
        return impl.hashCode();
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof AbstractLevel2SetInterval) {
            AbstractLevel2SetInterval that = (AbstractLevel2SetInterval) o;
            return that.canEqual(this) && this.impl.equals(that.impl);
        }
        return false;
    }

    abstract boolean canEqual(AbstractLevel2SetInterval that);

    @Override
    public String toString() {
        return getDatatypeName() + impl.toString();
    }

    @Override
    public String toStringDecorated() {
        return getDatatypeName() + impl.toStringDecorated();
    }

    abstract String getDatatypeName();

    private abstract static class Classic extends AbstractLevel2SetInterval implements ClassicInterval {

        private Classic(ClassicInterval impl) {
            super(impl);
        }

        @Override
        public Rational inf() {
            return ((ClassicInterval) impl).inf();
        }

        @Override
        public Rational sup() {
            return ((ClassicInterval) impl).sup();
        }

        @Override
        public Rational wid() {
            return ((ClassicInterval) impl).wid();
        }

        @Override
        public Rational rad() {
            return ((ClassicInterval) impl).rad();
        }

        @Override
        public Rational mag() {
            return ((ClassicInterval) impl).mag();
        }

        @Override
        public Rational mig() {
            return ((ClassicInterval) impl).mig();
        }
    }
}
