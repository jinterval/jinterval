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

import java.io.Serializable;
import net.java.jinterval.interval.set.OverlapState;
import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.interval.kaucher.KaucherInterval;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.rational.*;

/**
 *
 */
abstract class DoubleInterval implements Interval, Serializable {

    private final double inf;
    private final double sup;
    private final Decoration decoration;

    DoubleInterval(double inf, double sup, Decoration decoration) {
        if (decoration == null) {
            throw new NullPointerException();
        }
        this.inf = inf;
        this.sup = sup;
        this.decoration = decoration;
    }

    @Override
    public ExtendedRational inf() {
        return ExtendedRational.valueOf(inf);
    }

    @Override
    public ExtendedRational inf(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(inf);
        } else {
            return ExtendedRationalContexts.mkFloor(numberFormat).rnd(inf());
        }
    }

    @Override
    public double doubleInf() {
        return inf;
    }

    @Override
    public float floatInf() {
        return inf(BinaryValueSet.BINARY32).floatValue();
    }

    @Override
    public ExtendedRational sup() {
        return ExtendedRational.valueOf(sup);
    }

    @Override
    public ExtendedRational sup(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(sup);
        } else {
            return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(sup());
        }
    }

    @Override
    public double doubleSup() {
        return sup;
    }

    @Override
    public float floatSup() {
        return sup(BinaryValueSet.BINARY32).floatValue();
    }

    @Override
    public Rational mid() {
        if (isCommonInterval()) {
            return RationalOps.mul(RationalOps.add(Rational.valueOf(inf), Rational.valueOf(sup)), Utils.RAT_HALF);
        } else {
            throw new DomainException();
        }
    }

    @Override
    public Rational mid(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return Rational.valueOf(doubleMid());
        } else if (isCommonInterval()) {
            ExtendedRational mid = ExtendedRationalContexts.mkNearest(numberFormat).rnd(mid());
            if (mid instanceof Rational) {
                return (Rational) mid;
            }
            return numberFormat.getMaxValue(mid.isNegativeInfinity());
        } else if (inf > Double.NEGATIVE_INFINITY) {
            return numberFormat.getMaxValue(false);
        } else if (sup < Double.POSITIVE_INFINITY) {
            return numberFormat.getMaxValue(true);
        } else {
            assert isEntire();
            return Rational.zero();
        }
    }

    @Override
    public double doubleMid() {
        double mid = (inf + sup) * 0.5;
        if (Math.abs(mid) < Double.POSITIVE_INFINITY) {
            return mid;
        }
        mid = 0.5 * inf + 0.5 * sup;
        if (mid > Double.NEGATIVE_INFINITY) {
            if (mid < Double.POSITIVE_INFINITY) {
                return mid;
            } else {
                return Double.MAX_VALUE;
            }
        } else if (mid == Double.NEGATIVE_INFINITY) {
            return -Double.MAX_VALUE;
        } else {
            assert isEntire();
            return 0;
        }
    }

    @Override
    public float floatMid() {
        return mid(BinaryValueSet.BINARY32).floatValue();
    }

    @Override
    public ExtendedRational wid() {
        return ExtendedRationalOps.sub(sup(), inf());
    }

    @Override
    public ExtendedRational wid(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(doubleWid());
        }
        return ExtendedRationalContexts.mkCeiling(numberFormat).sub(sup(), inf());
    }

    @Override
    public double doubleWid() {
        return Utils.subUp(sup, inf);
    }

    @Override
    public float floatWid() {
        return wid(BinaryValueSet.BINARY32).floatValue();
    }

    @Override
    public ExtendedRational rad() {
        return ExtendedRationalOps.mul(ExtendedRationalOps.sub(sup(), inf()), Utils.RAT_HALF);
    }

    @Override
    public ExtendedRational rad(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(doubleRad());
        }
        Rational mid = mid(numberFormat);
        ExtendedRational r = ExtendedRationalOps.max(
                ExtendedRationalOps.sub(mid, inf()),
                ExtendedRationalOps.sub(sup(), mid));
        return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(r);
    }

    @Override
    public double doubleRad() {
        double mid = doubleMid();
        return Math.max(Utils.subUp(sup, mid), Utils.subUp(mid, inf));
    }

    @Override
    public float floatRad() {
        return rad(BinaryValueSet.BINARY32).floatValue();
    }

    /**
     * Level 1 midRad
     *
     * @return
     */
    @Override
    public MidRad midRad() {
        if (isCommonInterval()) {
            return new MidRad(mid(), RationalOps.mul((Rational) wid(), Utils.RAT_HALF));
        } else {
            throw new DomainException();
        }

    }

    @Override
    public MidRad midRad(BinaryValueSet midNumberFormat, BinaryValueSet radNumberFormat) {
        Rational mid = mid(midNumberFormat);
        ExtendedRational r = ExtendedRationalOps.max(ExtendedRationalOps.sub(mid, inf()), ExtendedRationalOps.sub(sup(), mid));
        return new MidRad(mid, ExtendedRationalContexts.mkCeiling(radNumberFormat).rnd(r));
    }

    @Override
    public ExtendedRational mag() {
        if (inf >= 0) {
            return ExtendedRational.valueOf(sup);
        } else if (sup <= 0) {
            return ExtendedRational.valueOf(-inf);
        } else {
            return ExtendedRational.valueOf(Math.max(-inf, sup));
        }
    }

    @Override
    public ExtendedRational mag(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(mag());
    }

    @Override
    public double doubleMag() {
        if (inf >= 0) {
            return sup;
        } else if (sup <= 0) {
            return -inf;
        } else {
            return Math.max(-inf, sup);
        }
    }

    @Override
    public float floatMag() {
        return mag(BinaryValueSet.BINARY32).floatValue();
    }

    @Override
    public ExtendedRational mig() {
        if (inf > 0) {
            return ExtendedRational.valueOf(inf);
        } else if (sup < 0) {
            return ExtendedRational.valueOf(-sup);
        } else {
            return Rational.zero();
        }
    }

    @Override
    public ExtendedRational mig(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkFloor(numberFormat).rnd(mig());
    }

    @Override
    public double doubleMig() {
        if (inf > 0) {
            return inf;
        } else if (sup < 0) {
            return -sup;
        } else {
            return 0;
        }
    }

    @Override
    public float floatMig() {
        return mig(BinaryValueSet.BINARY32).floatValue();
    }

    public boolean isEmpty() {
        return false;
    }

    public boolean isNaI() {
        return false;
    }

    public boolean isEntire() {
        return inf == Double.NEGATIVE_INFINITY && sup == Double.POSITIVE_INFINITY;
    }

    public boolean isCommonInterval() {
        return inf > Double.NEGATIVE_INFINITY && sup < Double.POSITIVE_INFINITY && inf <= sup;
    }

    public boolean isSingleton() {
        return inf == sup;
    }

    public boolean isMember(ExtendedRational m) {
        return m != null && inf().le(m) && m.le(sup()) && m.isFinite();
    }

    public boolean isMember(double m) {
        return inf <= m && m <= sup && !Double.isInfinite(m);
    }

    public boolean isMember(float m) {
        return inf <= m && m <= sup && !Double.isInfinite(m);
    }

    @Override
    public boolean equal(Interval that) {
        if (that instanceof DoubleInterval) {
            return this.inf == ((DoubleInterval) that).inf && this.sup == ((DoubleInterval) that).sup;
        } else {
            return this.inf().equals(that.inf()) && this.sup().equals(that.sup());
        }
    }

    private static boolean isEmpty(Interval that) {
        return that.inf().gt(that.sup());
    }

    @Override
    public boolean subset(Interval that) {
        if (that instanceof DoubleInterval) {
            return ((DoubleInterval) that).inf <= this.inf && this.sup <= ((DoubleInterval) that).sup;
        } else if (isEmpty(that)) {
            return false;
        } else {
            return that.inf().le(this.inf()) && this.sup().le(that.sup());
        }
    }

    public boolean less(Interval that) {
        if (that instanceof DoubleInterval) {
            return this.inf <= ((DoubleInterval) that).inf && this.sup <= ((DoubleInterval) that).sup;
        } else if (isEmpty(that)) {
            return false;
        } else {
            return this.inf().le(that.inf()) && this.sup().le(that.sup());
        }
    }

    public boolean precedes(Interval that) {
        if (that instanceof DoubleInterval) {
            return this.sup <= ((DoubleInterval) that).inf;
        } else if (isEmpty(that)) {
            return true;
        } else {
            return this.sup().le(that.inf());
        }
    }

    private static boolean ltPrime(double x, double y) {
        return x <= y && (Double.isInfinite(x) || x < y);
    }

    private static boolean ltPrime(ExtendedRational x, ExtendedRational y) {
        return x.le(y) && (!x.isFinite() || x.lt(y));
    }

    @Override
    public boolean interior(Interval that) {
        if (that instanceof DoubleInterval) {
            return ltPrime(((DoubleInterval) that).inf, this.inf) && ltPrime(this.sup, ((DoubleInterval) that).sup);
        } else if (isEmpty(that)) {
            return false;
        } else {
            return ltPrime(that.inf(), this.inf()) && ltPrime(this.sup(), that.sup());
        }
    }

    public boolean strictLess(Interval that) {
        if (that instanceof DoubleInterval) {
            return ltPrime(this.inf, ((DoubleInterval) that).inf) && ltPrime(this.sup, ((DoubleInterval) that).sup);
        } else if (isEmpty(that)) {
            return false;
        } else {
            return ltPrime(this.inf(), that.inf()) && ltPrime(this.sup(), that.sup());
        }
    }

    public boolean strictPrecedes(Interval that) {
        if (that instanceof DoubleInterval) {
            return this.sup < ((DoubleInterval) that).inf;
        } else if (isEmpty(that)) {
            return true;
        } else {
            return this.sup().lt(that.inf());
        }
    }

    @Override
    public boolean disjoint(Interval that) {
        if (that instanceof DoubleInterval) {
            return this.sup < ((DoubleInterval) that).inf || ((DoubleInterval) that).sup < this.inf;
        } else if (isEmpty(that)) {
            return true;
        } else {
            return this.sup().lt(that.inf()) || that.sup().lt(this.inf());
        }
    }

    public OverlapState overlap(Interval that) {
        if (isEmpty(that)) {
            return OverlapState.secondEmpty;
        }
        ExtendedRational ai = inf();
        ExtendedRational as = sup();
        ExtendedRational bi = that.inf();
        ExtendedRational bs = that.sup();
        if (as.lt(bi)) {
            return OverlapState.before;
        }
        if (ai.lt(as) && as.eq(bi) && bi.lt(bs)) {
            return OverlapState.meets;
        }
        if (ai.lt(bi) && bi.lt(as) && as.lt(bs)) {
            return OverlapState.overlaps;
        }
        if (ai.eq(bi) && as.lt(bs)) {
            return OverlapState.starts;
        }
        if (bi.lt(ai) && as.lt(bs)) {
            return OverlapState.containedBy;
        }
        if (bi.lt(ai) && as.eq(bs)) {
            return OverlapState.finishes;
        }
        if (ai.eq(bi) && as.eq(bs)) {
            return OverlapState.equal;
        }
        if (ai.lt(bi) && bs.eq(as)) {
            return OverlapState.finishedBy;
        }
        if (ai.lt(bi) && bs.lt(as)) {
            return OverlapState.contains;
        }
        if (bi.eq(ai) && bs.lt(as)) {
            return OverlapState.startedBy;
        }
        if (bi.lt(ai) && ai.lt(bs) && bs.lt(as)) {
            return OverlapState.overlappedBy;
        }
        if (bi.lt(bs) && bs.eq(ai) && ai.lt(as)) {
            return OverlapState.metBy;
        }
        if (bs.lt(as)) {
            return OverlapState.after;
        }
        throw new AssertionError();
    }

    public Decoration getDecoration() {
        return decoration;
    }

    public boolean possiblyUndefined() {
        return decoration.possiblyUndefined();
    }

    public boolean isMutable() {
        return false;
    }

    @Override
    public String intervalToExact(BinaryValueSet valueSet) {
        return "[" + inf().toHexString(valueSet) + "," + sup().toHexString(valueSet) + "]";
    }

    @Override
    public String intervalToExactDecorated(BinaryValueSet valueSet) {
        return intervalToExact(valueSet) + "_" + decoration.toString().toLowerCase();
    }

    @Override
    public String toString() {
        return "[" + inf().toString() + "," + sup().toString() + "]";
    }

    @Override
    public String toStringDecorated() {
        return toString() + "_" + decoration.toString().toLowerCase();
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof DoubleInterval) {
            DoubleInterval that = (DoubleInterval) o;
            return this.inf == that.inf && this.sup == that.sup && this.getDecoration() == that.getDecoration();
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 97 * hash + (int) (Double.doubleToLongBits(this.inf) ^ (Double.doubleToLongBits(this.inf) >>> 32));
        hash = 97 * hash + (int) (Double.doubleToLongBits(this.sup) ^ (Double.doubleToLongBits(this.sup) >>> 32));
        hash = 97 * hash + (this.decoration != null ? this.decoration.hashCode() : 0);
        return hash;
    }

    static class Bounded extends DoubleInterval implements ClassicInterval {

        Bounded(double inf, double sup, Decoration decoration) {
            super(inf, sup, decoration);
            if (!(inf <= sup)) {
                throw new IllegalArgumentException();
            }
            assert Double.NEGATIVE_INFINITY < inf && sup < Double.POSITIVE_INFINITY;
        }

        @Override
        public Rational inf() {
            return (Rational) super.inf();
        }

        @Override
        public Rational sup() {
            return (Rational) super.sup();
        }

        @Override
        public Rational wid() {
            return (Rational) super.wid();
        }

        @Override
        public Rational rad() {
            return (Rational) super.rad();
        }

        @Override
        public Rational mag() {
            return (Rational) super.mag();
        }

        @Override
        public Rational mig() {
            return (Rational) super.mig();
        }
    }

    static class Unbounded extends DoubleInterval implements SetInterval {

        Unbounded(double inf, double sup, Decoration decoration) {
            super(inf, sup, decoration);
            if (!(inf <= sup)) {
                throw new IllegalArgumentException();
            }
            assert Double.NEGATIVE_INFINITY == inf || sup == Double.POSITIVE_INFINITY;
        }
    }

    static class Dual extends DoubleInterval implements KaucherInterval {

        Dual(double inf, double sup, Decoration decoration) {
            super(inf, sup, decoration);
            if (!(inf > sup)) {
                throw new IllegalArgumentException();
            }
            assert Double.NEGATIVE_INFINITY < sup && inf < Double.POSITIVE_INFINITY;
        }

        @Override
        public Rational inf() {
            return (Rational) super.inf();
        }

        @Override
        public Rational sup() {
            return (Rational) super.sup();
        }

        @Override
        public Rational wid() {
            return (Rational) super.wid();
        }

        @Override
        public Rational rad() {
            return (Rational) super.rad();
        }

        @Override
        public Rational mag() {
            return Rational.valueOf(doubleMag());
        }

        @Override
        public double doubleMag() {
            return Math.max(Math.abs(doubleInf()), Math.abs(doubleSup()));
        }

        @Override
        public Rational mig() {
            return (Rational) super.mig();
        }
    }
}
