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

import net.java.jinterval.interval.set.OverlapState;
import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.kaucher.KaucherInterval;
import net.java.jinterval.rational.*;

/**
 *
 */
class RationalInterval implements Interval {

    private final ExtendedRational inf;
    private final ExtendedRational sup;
    private final Decoration decoration;

    RationalInterval(ExtendedRational inf, ExtendedRational sup, Decoration decoration) {
        if (decoration == null) {
            throw new NullPointerException();
        }
        this.inf = inf;
        this.sup = sup;
        this.decoration = decoration;
    }

    /**
     * Level 1 inf
     *
     * @return
     */
    @Override
    public ExtendedRational inf() {
        return inf;
    }

    @Override
    public ExtendedRational inf(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkFloor(numberFormat).rnd(inf());
    }

    @Override
    public double doubleInf() {
        return inf(BinaryValueSet.BINARY64).doubleValueExact();
    }

    @Override
    public float floatInf() {
        return inf(BinaryValueSet.BINARY32).floatValue();
    }

    /**
     * Level 1 sup
     *
     * @return
     */
    @Override
    public ExtendedRational sup() {
        return sup;
    }

    @Override
    public ExtendedRational sup(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(sup());
    }

    @Override
    public double doubleSup() {
        return sup(BinaryValueSet.BINARY64).doubleValueExact();
    }

    @Override
    public float floatSup() {
        return sup(BinaryValueSet.BINARY32).floatValue();
    }

    /**
     * Level 1 mid
     *
     * @return
     */
    @Override
    public Rational mid() {
        if (isCommonInterval()) {
            return RationalOps.mul(RationalOps.add((Rational) inf, (Rational) sup), Utils.RAT_HALF);
        } else {
            throw new DomainException();
        }
    }

    @Override
    public Rational mid(BinaryValueSet numberFormat) {
        if (isCommonInterval()) {
            ExtendedRational mid = ExtendedRationalContexts.mkNearest(numberFormat).rnd(mid());
            if (mid instanceof Rational) {
                return (Rational) mid;
            }
            return numberFormat.getMaxValue(mid.isNegativeInfinity());
        } else if (inf instanceof Rational) {
            return numberFormat.getMaxValue(false);
        } else if (sup instanceof Rational) {
            return numberFormat.getMaxValue(true);
        } else {
            assert isEntire();
            return Rational.zero();
        }
    }

    @Override
    public double doubleMid() {
        return mid(BinaryValueSet.BINARY64).doubleValueExact();
    }

    @Override
    public float floatMid() {
        return mid(BinaryValueSet.BINARY32).floatValue();
    }

    /**
     * Level 1 wid
     *
     * @return
     */
    @Override
    public ExtendedRational wid() {
        return ExtendedRationalOps.sub(sup, inf);
    }

    @Override
    public ExtendedRational wid(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).sub(sup, inf);
    }

    @Override
    public double doubleWid() {
        return wid(BinaryValueSet.BINARY64).doubleValueExact();
    }

    @Override
    public float floatWid() {
        return wid(BinaryValueSet.BINARY32).floatValue();
    }

    /**
     * Level 1 rad
     *
     * @return
     */
    @Override
    public ExtendedRational rad() {
        return ExtendedRationalOps.mul(ExtendedRationalOps.sub(sup, inf), Utils.RAT_HALF);
    }

    @Override
    public ExtendedRational rad(BinaryValueSet numberFormat) {
        Rational mid = mid(numberFormat);
        ExtendedRational r = ExtendedRationalOps.max(ExtendedRationalOps.sub(mid, inf), ExtendedRationalOps.sub(sup, mid));
        return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(r);
    }

    @Override
    public double doubleRad() {
        return rad(BinaryValueSet.BINARY64).doubleValueExact();
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
        ExtendedRational r = ExtendedRationalOps.max(ExtendedRationalOps.sub(mid, inf), ExtendedRationalOps.sub(sup, mid));
        return new MidRad(mid, ExtendedRationalContexts.mkCeiling(radNumberFormat).rnd(r));
    }

    /**
     * Level 1 mag
     *
     * @return
     */
    @Override
    public ExtendedRational mag() {
        if (inf.signum() >= 0) {
            return sup;
        } else if (sup.signum() <= 0) {
            return ExtendedRationalOps.neg(inf);
        } else {
            return ExtendedRationalOps.max(ExtendedRationalOps.neg(inf), sup);
        }
    }

    @Override
    public ExtendedRational mag(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(mag());
    }

    @Override
    public double doubleMag() {
        return mag(BinaryValueSet.BINARY64).doubleValueExact();
    }

    @Override
    public float floatMag() {
        return mag(BinaryValueSet.BINARY32).floatValue();
    }

    /**
     * Level 1 mig
     *
     * @return
     */
    @Override
    public ExtendedRational mig() {
        if (inf.signum() >= 0) {
            return inf;
        } else if (sup.signum() <= 0) {
            return ExtendedRationalOps.neg(inf);
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
        return mig(BinaryValueSet.BINARY64).doubleValueExact();
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
        return inf.isNegativeInfinity() && sup.isPositiveInfinity();
    }

    public boolean isCommonInterval() {
        return !inf.isNegativeInfinity() && !sup.isPositiveInfinity() && inf.le(sup);
    }

    public boolean isSingleton() {
        return inf.eq(sup);
    }

    public boolean isMember(ExtendedRational m) {
        return m != null && inf().le(m) && m.le(sup()) && m.isFinite();
    }

    public boolean isMember(double m) {
        if (Double.isInfinite(m) || Double.isNaN(m)) {
            return false;
        }
        Rational mr = Rational.valueOf(m);
        return inf.le(mr) && mr.le(sup);
    }

    public boolean isMember(float m) {
        if (Float.isInfinite(m) || Float.isNaN(m)) {
            return false;
        }
        Rational mr = Rational.valueOf(m);
        return inf.le(mr) && mr.le(sup);
    }

    private static boolean isEmpty(Interval that) {
        return that.inf().gt(that.sup());
    }

    @Override
    public boolean equal(Interval that) {
        return this.inf().equals(that.inf()) && this.sup().equals(that.sup());
    }

    @Override
    public boolean subset(Interval that) {
        if (isEmpty(that)) {
            return false;
        } else {
            return that.inf().le(this.inf()) && this.sup().le(that.sup());
        }
    }

    public boolean less(Interval that) {
        if (isEmpty(that)) {
            return false;
        } else {
            return this.inf().le(that.inf()) && this.sup().le(that.sup());
        }
    }

    public boolean precedes(Interval that) {
        if (isEmpty(that)) {
            return true;
        } else {
            return this.sup().le(that.inf());
        }
    }

    private static boolean ltPrime(ExtendedRational x, ExtendedRational y) {
        return x.le(y) && (!x.isFinite() || x.lt(y));
    }

    @Override
    public boolean interior(Interval that) {
        if (isEmpty(that)) {
            return false;
        } else {
            return ltPrime(that.inf(), this.inf()) && ltPrime(this.sup(), that.sup());
        }
    }

    public boolean strictLess(Interval that) {
        if (isEmpty(that)) {
            return false;
        } else {
            return ltPrime(this.inf(), that.inf()) && ltPrime(this.sup(), that.sup());
        }
    }

    public boolean strictPrecedes(Interval that) {
        if (isEmpty(that)) {
            return true;
        } else {
            return this.sup().lt(that.inf());
        }
    }

    @Override
    public boolean disjoint(Interval that) {
        if (isEmpty(that)) {
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
        return "[" + inf() + "," + sup() + "]";
    }

    @Override
    public String toStringDecorated() {
        return toString() + "_" + decoration.toString().toLowerCase();
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof RationalInterval) {
            RationalInterval that = (RationalInterval) o;
            return this.inf().eq(that.inf()) && this.sup().eq(that.sup()) && this.getDecoration() == that.getDecoration();
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 5;
        double thisInf = doubleInf();
        double thisSup = doubleSup();
        hash = 97 * hash + (int) (Double.doubleToLongBits(thisInf) ^ (Double.doubleToLongBits(thisInf) >>> 32));
        hash = 97 * hash + (int) (Double.doubleToLongBits(thisSup) ^ (Double.doubleToLongBits(thisSup) >>> 32));
        hash = 97 * hash + (this.decoration != null ? this.decoration.hashCode() : 0);
        return hash;
    }

    static class Bounded extends RationalInterval implements ClassicInterval {

        Bounded(Rational inf, Rational sup, Decoration decoration) {
            super(inf, sup, decoration);
            if (inf.compareTo(sup) > 0) {
                throw new IllegalArgumentException();
            }
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

    static class Unbounded extends RationalInterval implements SetInterval {

        Unbounded(ExtendedRational inf, ExtendedRational sup, Decoration decoration) {
            super(inf, sup, decoration);
            if (inf.compareTo(sup) > 0) {
                throw new IllegalArgumentException();
            }
            assert inf.isNegativeInfinity() || sup.isPositiveInfinity();
        }
    }

    static class Dual extends RationalInterval implements KaucherInterval {

        Dual(Rational inf, Rational sup, Decoration decoration) {
            super(inf, sup, decoration);
            if (inf.compareTo(sup) <= 0) {
                throw new IllegalArgumentException();
            }
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
            return RationalOps.max(RationalOps.abs(inf()), RationalOps.abs(sup()));
        }

        @Override
        public Rational mig() {
            return (Rational) super.mig();
        }
    }
}
