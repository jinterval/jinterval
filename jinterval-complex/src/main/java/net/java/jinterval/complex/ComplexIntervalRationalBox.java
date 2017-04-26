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

import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.DomainException;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 *
 */
public class ComplexIntervalRationalBox implements ComplexInterval {

    private final ExtendedRational realInf;
    private final ExtendedRational realSup;
    private final ExtendedRational imagInf;
    private final ExtendedRational imagSup;
    private final boolean possiblyUndefined;
    private static final Rational HALF = Rational.exp2(-1);

    ComplexIntervalRationalBox(ExtendedRational realInf, ExtendedRational realSup, ExtendedRational imagInf, ExtendedRational imagSup, boolean possiblyUndefined) {
        this.realInf = realInf;
        this.realSup = realSup;
        this.imagInf = imagInf;
        this.imagSup = imagSup;
        this.possiblyUndefined = possiblyUndefined;
    }

    public ExtendedRational realInf() {
        return realInf;
    }

    public ExtendedRational realInf(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkFloor(numberFormat).rnd(realInf);
    }

    public double doubleRealInf() {
        return realInf(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatRealInf() {
        return realInf(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational realSup() {
        return realSup;
    }

    public ExtendedRational realSup(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(realSup);
    }

    public double doubleRealSup() {
        return realSup(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatRealSup() {
        return realSup(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational imagInf() {
        return imagInf;
    }

    public ExtendedRational imagInf(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkFloor(numberFormat).rnd(imagInf);
    }

    public double doubleImagInf() {
        return imagInf(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatImagInf() {
        return imagInf(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational imagSup() {
        return imagSup;
    }

    public ExtendedRational imagSup(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(imagSup);
    }

    public double doubleImagSup() {
        return imagSup(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatImagSup() {
        return imagSup(BinaryValueSet.BINARY32).floatValue();
    }

    public Rational realMid() {
        if (!realInf.isNegativeInfinity() && !realSup.isPositiveInfinity()) {
            return RationalOps.mul(RationalOps.add((Rational) realInf, (Rational) realSup), HALF);
        } else {
            throw new DomainException();
        }
    }

    public Rational realMid(BinaryValueSet numberFormat) {
        if (!realInf.isNegativeInfinity() && !realSup.isPositiveInfinity()) {
            ExtendedRational realMid = ExtendedRationalContexts.mkNearest(numberFormat).rnd(realMid());
            if (realMid instanceof Rational) {
                return (Rational) realMid;
            }
            return numberFormat.getMaxValue(realMid.isNegativeInfinity());
        } else if (realInf instanceof Rational) {
            return numberFormat.getMaxValue(false);
        } else if (realSup instanceof Rational) {
            return numberFormat.getMaxValue(true);
        } else {
            assert isEntire();
            return Rational.zero();
        }
    }

    public double doubleRealMid() {
        return realMid(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatRealMid() {
        return realMid(BinaryValueSet.BINARY32).floatValue();
    }

    public Rational imagMid() {
        if (!imagInf.isNegativeInfinity() && !imagSup.isPositiveInfinity()) {
            return RationalOps.mul(RationalOps.add((Rational) imagInf, (Rational) imagSup), HALF);
        } else {
            throw new DomainException();
        }
    }

    public Rational imagMid(BinaryValueSet numberFormat) {
        if (!imagInf.isNegativeInfinity() && !imagSup.isPositiveInfinity()) {
            ExtendedRational imagMid = ExtendedRationalContexts.mkNearest(numberFormat).rnd(imagMid());
            if (imagMid instanceof Rational) {
                return (Rational) imagMid;
            }
            return numberFormat.getMaxValue(imagMid.isNegativeInfinity());
        } else if (imagInf instanceof Rational) {
            return numberFormat.getMaxValue(false);
        } else if (imagSup instanceof Rational) {
            return numberFormat.getMaxValue(true);
        } else {
            assert isEntire();
            return Rational.zero();
        }
    }

    public double doubleImagMid() {
        return imagMid(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatImagMid() {
        return imagMid(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational realWid() {
        return ExtendedRationalOps.sub(realSup(), realInf());
    }

    public ExtendedRational realWid(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).sub(realSup(), realInf());
    }

    public double doubleRealWid() {
        return realWid(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatRealWid() {
        return realWid(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational imagWid() {
        return ExtendedRationalOps.sub(imagSup(), imagInf());
    }

    public ExtendedRational imagWid(BinaryValueSet numberFormat) {
        return ExtendedRationalContexts.mkCeiling(numberFormat).sub(imagSup(), imagInf());
    }

    public double doubleImagWid() {
        return imagWid(BinaryValueSet.BINARY64).doubleValueExact();
    }

    public float floatImagWid() {
        return imagWid(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational rad() {
        return ExtendedRationalOps.mul(ExtendedRationalOps.hypot(realWid(), imagWid()), HALF);
    }

    public ExtendedRational rad(BinaryValueSet numberFormat) {
        Rational realMid = realMid(numberFormat);
        Rational imagMid = imagMid(numberFormat);
        ExtendedRational realR = ExtendedRationalOps.max(
                ExtendedRationalOps.sub(realMid, realInf()),
                ExtendedRationalOps.sub(realSup(), realMid));
        ExtendedRational imagR = ExtendedRationalOps.max(
                ExtendedRationalOps.sub(imagMid, imagInf()),
                ExtendedRationalOps.sub(imagSup(), imagMid));
        return ExtendedRationalContexts.mkCeiling(numberFormat).hypot(realR, imagR);
    }

    public double doubleRad() {
        return rad(BinaryValueSet.BINARY64).doubleValue();
    }

    public float floatRad() {
        return rad(BinaryValueSet.BINARY64).floatValue();
    }

    public ExtendedRational mag() {
        ExtendedRational realM = ExtendedRationalOps.max(ExtendedRationalOps.neg(realInf), realSup);
        ExtendedRational imagM = ExtendedRationalOps.max(ExtendedRationalOps.neg(imagInf), imagSup);
        return ExtendedRationalOps.hypot(realM, imagM);
    }

    public ExtendedRational mag(BinaryValueSet numberFormat) {
        ExtendedRational realM = ExtendedRationalOps.max(ExtendedRationalOps.neg(realInf), realSup);
        ExtendedRational imagM = ExtendedRationalOps.max(ExtendedRationalOps.neg(imagInf), imagSup);
        return ExtendedRationalContexts.mkCeiling(numberFormat).hypot(realM, imagM);
    }

    public double doubleMag() {
        return mag(BinaryValueSet.BINARY64).doubleValue();
    }

    public float floatMag() {
        return mag(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational mig() {
        ExtendedRational realM;
        if (realInf.gt(Rational.zero())) {
            realM = realInf;
        } else if (realSup.lt(Rational.zero())) {
            realM = ExtendedRationalOps.neg(realSup);
        } else {
            realM = Rational.zero();
        }
        ExtendedRational imagM;
        if (imagInf.gt(Rational.zero())) {
            imagM = imagInf;
        } else if (realSup.lt(Rational.zero())) {
            imagM = ExtendedRationalOps.neg(imagSup);
        } else {
            imagM = Rational.zero();
        }
        if (realM.eq(Rational.zero())) {
            return imagM;
        }
        if (imagM.eq(Rational.zero())) {
            return realM;
        }
        return ExtendedRationalOps.hypot(realM, imagM);
    }

    public ExtendedRational mig(BinaryValueSet numberFormat) {
        ExtendedRational realM;
        if (realInf.gt(Rational.zero())) {
            realM = realInf;
        } else if (realSup.lt(Rational.zero())) {
            realM = ExtendedRationalOps.neg(realSup);
        } else {
            realM = Rational.zero();
        }
        ExtendedRational imagM;
        if (imagInf.gt(Rational.zero())) {
            imagM = imagInf;
        } else if (realSup.lt(Rational.zero())) {
            imagM = ExtendedRationalOps.neg(imagSup);
        } else {
            imagM = Rational.zero();
        }
        if (realM.eq(Rational.zero())) {
            return imagM;
        }
        if (imagM.eq(Rational.zero())) {
            return realM;
        }
        return ExtendedRationalContexts.mkFloor(numberFormat).hypot(realM, imagM);
    }

    public double doubleMig() {
        return mig(BinaryValueSet.BINARY64).doubleValue();
    }

    public float floatMig() {
        return mig(BinaryValueSet.BINARY32).floatValue();
    }

    public boolean isEmpty() {
        return false;
    }

    public boolean isBounded() {
        return !realInf.isNegativeInfinity() && !realSup.isPositiveInfinity()
                && !imagInf.isNegativeInfinity() && !imagSup.isPositiveInfinity();
    }

    public boolean isEntire() {
        return realInf.isNegativeInfinity() && realSup.isPositiveInfinity()
                && imagInf.isNegativeInfinity() && imagSup.isPositiveInfinity();
    }

    public boolean isBox() {
        return true;
    }

    public boolean isDisc() {
        return isEntire() || realInf.eq(realSup) && imagInf.eq(imagSup);
    }

    public boolean isEqual(ComplexInterval that) {
        if (that instanceof ComplexIntervalRationalBox) {
            ComplexIntervalRationalBox t = (ComplexIntervalRationalBox) that;
            return realInf.eq(t.realInf) && realSup.eq(t.realSup)
                    && imagInf.eq(t.imagInf) && imagSup.eq(t.imagSup);
        }
        return that.isBox()
                && this.realInf().eq(that.realInf()) && this.realSup().eq(that.realSup())
                && this.imagInf().eq(that.imagInf()) && this.imagSup().eq(that.imagSup());
    }

    public boolean containedIn(ComplexInterval that) {
        if (that instanceof ComplexIntervalRationalBox) {
            ComplexIntervalRationalBox t = (ComplexIntervalRationalBox) that;
            return t.realInf.le(realInf) && realSup.le(t.realSup)
                    && t.imagInf.le(imagInf) && imagSup.le(t.imagSup);
        }
        if (that.isEmpty()) {
            return false;
        }
        if (that.isBox()) {
            return that.realInf().le(this.realInf()) && this.realSup().le(that.realSup())
                    && that.imagInf().le(this.imagInf()) && this.imagSup().le(that.imagSup());
        }
        if (that.isDisc()) {
            ExtendedRational thatRealMid = that.realMid();
            ExtendedRational thatImagMid = that.imagMid();
            ExtendedRational realM = ExtendedRationalOps.max(
                    ExtendedRationalOps.sub(thatRealMid, realInf()),
                    ExtendedRationalOps.sub(realSup(), thatRealMid));
            ExtendedRational imagM = ExtendedRationalOps.max(
                    ExtendedRationalOps.sub(thatImagMid, imagInf()),
                    ExtendedRationalOps.sub(imagSup(), thatImagMid));
            return ExtendedRationalOps.add(ExtendedRationalOps.sqr(realM), ExtendedRationalOps.sqr(imagM))
                    .le(ExtendedRationalOps.sqr(that.rad()));
        }
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean containedInInterior(ComplexInterval that) {
        if (that instanceof ComplexIntervalRationalBox) {
            ComplexIntervalRationalBox t = (ComplexIntervalRationalBox) that;
            return t.realInf.lt(realInf) && realSup.lt(t.realSup)
                    && t.imagInf.lt(imagInf) && imagSup.lt(t.imagSup);
        }
        if (that.isEmpty()) {
            return false;
        }
        if (that.isBox()) {
            return that.realInf().lt(this.realInf()) && this.realSup().lt(that.realSup())
                    && that.imagInf().lt(this.imagInf()) && this.imagSup().lt(that.imagSup());
        }
        if (that.isDisc()) {
            ExtendedRational thatRealMid = that.realMid();
            ExtendedRational thatImagMid = that.imagMid();
            ExtendedRational realM = ExtendedRationalOps.max(
                    ExtendedRationalOps.sub(thatRealMid, realInf()),
                    ExtendedRationalOps.sub(realSup(), thatRealMid));
            ExtendedRational imagM = ExtendedRationalOps.max(
                    ExtendedRationalOps.sub(thatImagMid, imagInf()),
                    ExtendedRationalOps.sub(imagSup(), thatImagMid));
            return ExtendedRationalOps.add(ExtendedRationalOps.sqr(realM), ExtendedRationalOps.sqr(imagM))
                    .lt(ExtendedRationalOps.sqr(that.rad()));
        }
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean areDisjoint(ComplexInterval that) {
        if (that instanceof ComplexIntervalRationalBox) {
            ComplexIntervalRationalBox t = (ComplexIntervalRationalBox) that;
            return t.realSup.lt(realInf) || realSup.lt(t.realInf)
                    || t.imagSup.lt(imagInf) || imagSup.lt(t.imagInf);
        }
        if (that.isEmpty()) {
            return false;
        }
        if (that.isBox()) {
            return that.realSup().lt(this.realInf()) || this.realSup().lt(that.realInf())
                    || that.imagSup().lt(this.imagInf()) && this.imagSup().lt(that.imagInf());
        }
        if (that.isDisc()) {
            ExtendedRational thatRealMid = that.realMid();
            ExtendedRational thatImagMid = that.imagMid();
            ExtendedRational realM;
            if (realSup().lt(thatRealMid)) {
                realM = ExtendedRationalOps.sub(thatRealMid, realSup());
            } else if (realInf().gt(thatRealMid)) {
                realM = ExtendedRationalOps.sub(realInf(), thatRealMid);
            } else {
                realM = Rational.zero();
            }
            ExtendedRational imagM;
            if (imagSup().lt(thatImagMid)) {
                imagM = ExtendedRationalOps.sub(thatImagMid, imagSup());
            } else if (imagInf().gt(thatImagMid)) {
                imagM = ExtendedRationalOps.sub(imagInf(), thatImagMid);
            } else {
                imagM = Rational.zero();
            }
            if (realM.signum() == 0) {
                return that.rad().gt(imagM);
            }
            if (imagM.signum() == 0) {
                return that.rad().gt(realM);
            }
            return ExtendedRationalOps.add(ExtendedRationalOps.sqr(realM), ExtendedRationalOps.sqr(imagM))
                    .gt(ExtendedRationalOps.sqr(that.rad()));
        }
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean possiblyUndefined() {
        return possiblyUndefined;
    }

    public boolean isMutable() {
        return false;
    }

    public String toString() {
        return "[" + imagInf.toString() + ", " + imagSup.toString() + "] + [" + realInf.toString() + ", " + realSup.toString() + "] * i";
    }
}