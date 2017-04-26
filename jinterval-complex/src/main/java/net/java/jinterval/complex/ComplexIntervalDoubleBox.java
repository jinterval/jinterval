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

import net.java.jinterval.interval.Utils;
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
public class ComplexIntervalDoubleBox implements ComplexInterval {

    private final double realInf;
    private final double realSup;
    private final double imagInf;
    private final double imagSup;
    private final boolean possiblyUndefined;
    private static final Rational HALF = Rational.exp2(-1);

    ComplexIntervalDoubleBox(double realInf, double realSup, double imagInf, double imagSup, boolean possiblyUndefined) {
        assert realInf <= realSup && imagInf <= imagSup
                && realInf < Double.POSITIVE_INFINITY && Double.NEGATIVE_INFINITY < realSup
                && imagInf < Double.POSITIVE_INFINITY && Double.NEGATIVE_INFINITY < imagSup;
        this.realInf = realInf;
        this.realSup = realSup;
        this.imagInf = imagInf;
        this.imagSup = imagSup;
        this.possiblyUndefined = possiblyUndefined;
    }

    public ExtendedRational realInf() {
        return ExtendedRational.valueOf(realInf);
    }

    public ExtendedRational realInf(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(realInf);
        } else {
            return ExtendedRationalContexts.mkFloor(numberFormat).rnd(realInf());
        }
    }

    public double doubleRealInf() {
        return realInf;
    }

    public float floatRealInf() {
        return realInf(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational realSup() {
        return ExtendedRational.valueOf(realSup);
    }

    public ExtendedRational realSup(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(realSup);
        } else {
            return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(realSup());
        }
    }

    public double doubleRealSup() {
        return realSup;
    }

    public float floatRealSup() {
        return realSup(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational imagInf() {
        return ExtendedRational.valueOf(imagInf);
    }

    public ExtendedRational imagInf(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(imagInf);
        } else {
            return ExtendedRationalContexts.mkFloor(numberFormat).rnd(imagInf());
        }
    }

    public double doubleImagInf() {
        return imagInf;
    }

    public float floatImagInf() {
        return imagInf(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational imagSup() {
        return ExtendedRational.valueOf(imagSup);
    }

    public ExtendedRational imagSup(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(imagSup);
        } else {
            return ExtendedRationalContexts.mkCeiling(numberFormat).rnd(imagSup());
        }
    }

    public double doubleImagSup() {
        return imagSup;
    }

    public float floatImagSup() {
        return imagSup(BinaryValueSet.BINARY32).floatValue();
    }

    public Rational realMid() {
        if (Double.NEGATIVE_INFINITY < realInf && realSup < Double.POSITIVE_INFINITY) {
            return RationalOps.mul(RationalOps.add(Rational.valueOf(realInf), Rational.valueOf(realSup)), HALF);
        } else {
            throw new DomainException();
        }
    }

    public Rational realMid(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return Rational.valueOf(doubleRealMid());
        }
        if (Double.NEGATIVE_INFINITY < realInf) {
            if (realSup < Double.POSITIVE_INFINITY) {
                ExtendedRational mid = ExtendedRationalContexts.mkNearest(numberFormat).rnd(realMid());
                if (mid instanceof Rational) {
                    return (Rational) mid;
                }
                return numberFormat.getMaxValue(mid.isNegativeInfinity());
            } else {
                return numberFormat.getMaxValue(false);
            }
        } else if (realSup < Double.POSITIVE_INFINITY) {
            return numberFormat.getMaxValue(true);
        } else {
            return Rational.zero();
        }
    }

    public double doubleRealMid() {
        double mid = (realInf + realSup) * 0.5;
        if (Math.abs(mid) < Double.POSITIVE_INFINITY) {
            return mid;
        }
        mid = 0.5 * realInf + 0.5 * realSup;
        if (mid > Double.NEGATIVE_INFINITY) {
            if (mid < Double.POSITIVE_INFINITY) {
                return mid;
            } else {
                return Double.MAX_VALUE;
            }
        } else if (mid == Double.NEGATIVE_INFINITY) {
            return -Double.MAX_VALUE;
        } else {
            return 0;
        }
    }

    public float floatRealMid() {
        return realMid(BinaryValueSet.BINARY32).floatValue();
    }

    public Rational imagMid() {
        if (Double.NEGATIVE_INFINITY < imagInf && imagSup < Double.POSITIVE_INFINITY) {
            return RationalOps.mul(RationalOps.add(Rational.valueOf(imagInf), Rational.valueOf(imagSup)), HALF);
        } else {
            throw new DomainException();
        }
    }

    public Rational imagMid(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return Rational.valueOf(doubleImagMid());
        }
        if (Double.NEGATIVE_INFINITY < imagInf) {
            if (imagSup < Double.POSITIVE_INFINITY) {
                ExtendedRational mid = ExtendedRationalContexts.mkNearest(numberFormat).rnd(imagMid());
                if (mid instanceof Rational) {
                    return (Rational) mid;
                }
                return numberFormat.getMaxValue(mid.isNegativeInfinity());
            } else {
                return numberFormat.getMaxValue(false);
            }
        } else if (imagSup < Double.POSITIVE_INFINITY) {
            return numberFormat.getMaxValue(true);
        } else {
            return Rational.zero();
        }
    }

    public double doubleImagMid() {
        double mid = (imagInf + imagSup) * 0.5;
        if (Math.abs(mid) < Double.POSITIVE_INFINITY) {
            return mid;
        }
        mid = 0.5 * imagInf + 0.5 * imagSup;
        if (mid > Double.NEGATIVE_INFINITY) {
            if (mid < Double.POSITIVE_INFINITY) {
                return mid;
            } else {
                return Double.MAX_VALUE;
            }
        } else if (mid == Double.NEGATIVE_INFINITY) {
            return -Double.MAX_VALUE;
        } else {
            return 0;
        }
    }

    public float floatImagMid() {
        return imagMid(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational realWid() {
        return ExtendedRationalOps.sub(realSup(), realInf());
    }

    public ExtendedRational realWid(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(doubleRealWid());
        }
        return ExtendedRationalContexts.mkCeiling(numberFormat).sub(realSup(), realInf());
    }

    public double doubleRealWid() {
        return Utils.subUp(realSup, realInf);
    }

    public float floatRealWid() {
        return realWid(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational imagWid() {
        return ExtendedRationalOps.sub(imagSup(), imagInf());
    }

    public ExtendedRational imagWid(BinaryValueSet numberFormat) {
        if (numberFormat == BinaryValueSet.BINARY64) {
            return ExtendedRational.valueOf(doubleImagWid());
        }
        return ExtendedRationalContexts.mkCeiling(numberFormat).sub(imagSup(), imagInf());
    }

    public double doubleImagWid() {
        return Utils.subUp(imagSup, imagInf);
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
        ExtendedRational realM = ExtendedRational.valueOf(Math.max(-realInf, realSup));
        ExtendedRational imagM = ExtendedRational.valueOf(Math.max(-imagInf, imagSup));
        return ExtendedRationalOps.hypot(realM, imagM);
    }

    public ExtendedRational mag(BinaryValueSet numberFormat) {
        ExtendedRational realM = ExtendedRational.valueOf(Math.max(-realInf, realSup));
        ExtendedRational imagM = ExtendedRational.valueOf(Math.max(-imagInf, imagSup));
        return ExtendedRationalContexts.mkCeiling(numberFormat).hypot(realM, imagM);
    }

    public double doubleMag() {
        return mag(BinaryValueSet.BINARY64).doubleValue();
    }

    public float floatMag() {
        return mag(BinaryValueSet.BINARY32).floatValue();
    }

    public ExtendedRational mig() {
        double realM;
        if (realInf > 0) {
            realM = realInf;
        } else if (realSup < 0) {
            realM = -realSup;
        } else {
            realM = 0;
        }
        double imagM;
        if (imagInf > 0) {
            imagM = imagInf;
        } else if (realSup < 0) {
            imagM = -imagSup;
        } else {
            imagM = 0;
        }
        if (realM == 0) {
            return Rational.valueOf(imagM);
        }
        if (imagM == 0) {
            return Rational.valueOf(realM);
        }
        return ExtendedRationalOps.hypot(Rational.valueOf(realM), Rational.valueOf(imagM));
    }

    public ExtendedRational mig(BinaryValueSet numberFormat) {
        double realM;
        if (realInf > 0) {
            realM = realInf;
        } else if (realSup < 0) {
            realM = -realSup;
        } else {
            realM = 0;
        }
        double imagM;
        if (imagInf > 0) {
            imagM = imagInf;
        } else if (realSup < 0) {
            imagM = -imagSup;
        } else {
            imagM = 0;
        }
        if (realM == 0) {
            if (numberFormat == BinaryValueSet.BINARY64) {
                return Rational.valueOf(imagM);
            }
            return ExtendedRationalContexts.mkFloor(numberFormat).rnd(Rational.valueOf(imagM));
        }
        if (imagM == 0) {
            if (numberFormat == BinaryValueSet.BINARY64) {
                return Rational.valueOf(realM);
            }
            return ExtendedRationalContexts.mkFloor(numberFormat).rnd(Rational.valueOf(realM));
        }
        return ExtendedRationalContexts.mkFloor(numberFormat).hypot(Rational.valueOf(realM), Rational.valueOf(imagM));
    }

    public double doubleMig() {
        double realM;
        if (realInf > 0) {
            realM = realInf;
        } else if (realSup < 0) {
            realM = -realSup;
        } else {
            realM = 0;
        }
        double imagM;
        if (imagInf > 0) {
            imagM = imagInf;
        } else if (realSup < 0) {
            imagM = -imagSup;
        } else {
            imagM = 0;
        }
        if (realM == 0) {
            return imagM;
        }
        if (imagM == 0) {
            return realM;
        }
        return ExtendedRationalContexts.mkFloor(BinaryValueSet.BINARY64).hypot(Rational.valueOf(realM), Rational.valueOf(imagM)).doubleValue();
    }

    public float floatMig() {
        return mig(BinaryValueSet.BINARY32).floatValue();
    }

    public boolean isEmpty() {
        return false;
    }

    public boolean isBounded() {
        return Double.NEGATIVE_INFINITY < realInf && realSup < Double.POSITIVE_INFINITY
                && Double.NEGATIVE_INFINITY < imagInf && imagSup < Double.POSITIVE_INFINITY;
    }

    public boolean isEntire() {
        return Double.NEGATIVE_INFINITY == realInf && realSup == Double.POSITIVE_INFINITY
                && Double.NEGATIVE_INFINITY == imagInf && imagSup == Double.POSITIVE_INFINITY;
    }

    public boolean isBox() {
        return true;
    }

    public boolean isDisc() {
        return isEntire() || realInf == realSup && imagInf == imagSup;
    }

    public boolean isEqual(ComplexInterval that) {
        if (that instanceof ComplexIntervalDoubleBox) {
            ComplexIntervalDoubleBox t = (ComplexIntervalDoubleBox) that;
            return realInf == t.realInf && realSup == t.realSup && imagInf == t.imagInf && imagSup == t.imagSup;
        }
        return that.isBox()
                && this.realInf().eq(that.realInf()) && this.realSup().eq(that.realSup())
                && this.imagInf().eq(that.imagInf()) && this.imagSup().eq(that.imagSup());
    }

    public boolean containedIn(ComplexInterval that) {
        if (that instanceof ComplexIntervalDoubleBox) {
            ComplexIntervalDoubleBox t = (ComplexIntervalDoubleBox) that;
            return t.realInf <= realInf && realSup <= t.realSup
                    && t.imagInf <= imagInf && imagSup <= t.imagSup;
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
        if (that instanceof ComplexIntervalDoubleBox) {
            ComplexIntervalDoubleBox t = (ComplexIntervalDoubleBox) that;
            return t.realInf < realInf && realSup < t.realSup
                    && t.imagInf < imagInf && imagSup < t.imagSup;
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
        if (that instanceof ComplexIntervalDoubleBox) {
            ComplexIntervalDoubleBox t = (ComplexIntervalDoubleBox) that;
            return t.realSup < realInf || realSup < t.realInf
                    || t.imagSup < imagInf || imagSup < t.imagInf;
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
}
