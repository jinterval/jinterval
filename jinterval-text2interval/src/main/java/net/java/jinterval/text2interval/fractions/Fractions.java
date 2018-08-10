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
package net.java.jinterval.text2interval.fractions;

import java.math.BigInteger;
import java.math.RoundingMode;
import java.util.ArrayList;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * Expansion of rational number into continuous fractions
 */
public class Fractions {

    /**
     * The rational number
     */
    private final Rational alpha;
    /**
     * Numerator of the rational number.
     */
    private final BigInteger alphaN;
    /**
     * Denominator of the rational number.
     */
    private final BigInteger alphaD;
    /**
     * Dummy fraction zero.
     */
    private final Fraction fractionM2;
    /**
     * Dummy fraction positive infinity.
     */
    private final Fraction fractionM1;
    /**
     * Sequence of fractions with increasing accuracy. Even fractions are
     * approximations below. Odd fractions are approximations above. Zero
     * fraction is natural number
     */
    private final ArrayList<Fraction> fracts = new ArrayList<Fraction>();

    public Fractions(Rational alpha) {
        assert alpha.signum() > 0;
        this.alpha = alpha;
        alphaN = alpha.biNumerator();
        alphaD = alpha.biDenominator();
        fractionM2 = new Fraction(-2, null, null);
        fractionM1 = new Fraction(-1, fractionM2, null);
        BigInteger n = alphaN;
        BigInteger d = alphaD;
        Fraction prev = fractionM1;
        do {
            BigInteger[] qr = n.divideAndRemainder(d);
            Fraction f = new Fraction(fracts.size(), prev, qr[0]);
            fracts.add(f);
            prev = f;
            n = d;
            d = qr[1];
        } while (d.signum() > 0);
        ExtendedRational f2 = Rational.zero();
        ExtendedRational f1 = ExtendedRational.POSITIVE_INFINITY;
        for (int i = 0; i < fracts.size(); i++) {
            ExtendedRational f = fracts.get(i).r;
            BigInteger qi = fracts.get(i).q;
            if (i > 0) {
                assert qi.signum() > 0;
            }
            assert f.biNumerator().equals(f1.biNumerator().multiply(qi).add(f2.biNumerator()));
            assert f.biDenominator().equals(f1.biDenominator().multiply(qi).add(f2.biDenominator()));
            int cmp = f.compareTo(alpha);
            assert i == fracts.size() - 1 ? cmp == 0 : i % 2 == 1 ? cmp > 0 : cmp < 0;
            f2 = f1;
            f1 = f;
        }
    }

    /**
     * Ceiling of x/d assuming that d is positive
     *
     * @param x dividend
     * @param d positive divider
     * @return ceiling of x/d
     */
    private static BigInteger divideCeiling(BigInteger x, BigInteger d) {
        assert d.signum() > 0;
        BigInteger[] qr = x.divideAndRemainder(d);
        BigInteger q = qr[0];
        int signum = qr[1].signum();
        if (signum > 0) {
            q = q.add(BigInteger.ONE);
        }
        return q;
    }

    /**
     * Floor of x/d assuming that d is positive
     *
     * @param x dividend
     * @param d positive divider
     * @return ceiling of x/d
     */
    private static BigInteger divideFloor(BigInteger x, BigInteger d) {
        assert d.signum() > 0;
        BigInteger[] qr = x.divideAndRemainder(d);
        BigInteger q = qr[0];
        int signum = qr[1].signum();
        if (signum < 0) {
            q = q.subtract(BigInteger.ONE);
        }
        return q;
    }

    /**
     * Search for such x in the range [xMin..xMax] that x*alpha is exact integer
     *
     * @param xMin minimal x
     * @param xMax maximal x
     * @return either found x or null
     */
    public BigInteger searchExact(BigInteger xMin, BigInteger xMax) {
        assert xMin.compareTo(xMax) <= 0;
        BigInteger q = divideCeiling(xMin, alphaD);
        BigInteger x = q.multiply(alphaD);
        return x.compareTo(xMax) <= 0 ? x : null;
    }

    public BigInteger searchOdd(BigInteger xMin, BigInteger xMax, boolean isAbove) {
        Record record = new Record(isAbove, true);
        int t = fracts.size() - 1;
        while (t > 0 && xMax.compareTo(fracts.get(t - 1).denominator) <= 0) {
            t--;
        }
        Fraction top = fracts.get(t);
        assert xMin.signum() >= 0;
        assert xMin.compareTo(xMax) <= 0;
        if (xMin.equals(xMax)) {
            return xMin;
        }
        BigInteger kMin = divideFloor(xMin, alphaD);
        for (int i = 0; i <= 2; i++) {
            BigInteger kMinX = kMin.multiply(alphaD);
            BigInteger kMinY = kMin.multiply(alphaN);
            boolean kOddY = kMin.testBit(0) & alphaN.testBit(0);
            if (xMin.compareTo(kMinX) <= 0 && kMinX.compareTo(xMax) <= 0) {
                BigInteger kMinY_ = kMinY;
                if (kMinY_.testBit(0)) {
                    kMinY_ = kMinY_.add(BigInteger.valueOf(isAbove ? +2 : -2));
                } else {
                    kMinY_ = kMinY_.add(BigInteger.valueOf(isAbove ? +1 : -1));
                }
                record.update(kMinX, kMinY_, isAbove, true);
            }
            top.computeRecord(record, kOddY, kMinX, kMinY, xMin.subtract(kMinX), xMax.subtract(kMinX), isAbove, true);
            kMin = kMin.add(BigInteger.ONE);
        }
        return record.x;
    }

    public BigInteger search(BigInteger xMin, BigInteger xMax, boolean isAbove) {
        assert xMin.signum() >= 0;
        assert xMin.compareTo(xMax) <= 0;
        if (xMin.equals(xMax) || alphaD.equals(BigInteger.ONE)) {
            return xMin;
        }
        BigInteger qrMin[] = xMin.divideAndRemainder(alphaD);
        BigInteger qrMax[] = xMax.divideAndRemainder(alphaD);
        ExtendedRationalContext rc = ExtendedRationalContexts.valueOf(
                BinaryValueSet.INTEGER_UNLIMITED,
                isAbove ? RoundingMode.CEILING : RoundingMode.FLOOR);
        BigInteger l = qrMin[1].max(BigInteger.ONE);
        BigInteger r = qrMin[0].compareTo(qrMax[0]) == 0 ? qrMax[1] : alphaD.subtract(BigInteger.ONE);
        BigInteger xr = searchTop(l, r, isAbove);
        Rational y = RationalOps.mul(alpha, Rational.valueOf(xr));
        Rational epsBest = RationalOps.sub((Rational) rc.rnd(y), y);
        if (!isAbove) {
            epsBest = RationalOps.neg(epsBest);
        }
        assert epsBest.signum() > 0;
        BigInteger xBest = qrMin[0].multiply(alphaD).add(xr);

        if (qrMin[0].compareTo(qrMax[0]) < 0) {
            l = BigInteger.ONE;
            r = qrMax[0].subtract(qrMin[0]).compareTo(BigInteger.ONE) == 0 ? qrMax[1] : alphaD.subtract(BigInteger.ONE);
            if (r.signum() > 0) {
                xr = searchTop(l, r, isAbove);
                y = RationalOps.mul(alpha, Rational.valueOf(xr));
                Rational eps = RationalOps.sub((Rational) rc.rnd(y), y);
                if (!isAbove) {
                    eps = RationalOps.neg(eps);
                }
                assert eps.signum() > 0;
                if (eps.compareTo(epsBest) < 0) {
                    epsBest = eps;
                    xBest = qrMin[0].add(BigInteger.ONE).multiply(alphaD).add(xr);
                }
            }
        }
        assert xMin.compareTo(xBest) <= 0 && xBest.compareTo(xMax) <= 0;
        return xBest;
    }

    private BigInteger searchTop(BigInteger xMin, BigInteger xMax, boolean isAbove) {
        int level = fracts.size() - 1;
        Fraction top = fracts.get(level);
        assert xMin.signum() > 0 && xMin.compareTo(xMax) <= 0 && xMax.compareTo(alphaD) < 0;
        if (isAbove == (level % 2 == 1)) {
            return alphaD.subtract(search(alphaD.subtract(xMax), alphaD.subtract(xMin), top));
        } else {
            return search(xMin, xMax, top);
        }
    }

    private BigInteger search(BigInteger xMin, BigInteger xMax, Fraction frac) {
        assert frac.level >= 1;
        BigInteger d = frac.denominator;
        BigInteger d1 = frac.prev.denominator;
        BigInteger qi = frac.q;
        assert xMin.signum() > 0 && xMin.compareTo(xMax) <= 0 && xMax.compareTo(d) < 0;
        BigInteger k = divideCeiling(xMin, d1);
        assert k.signum() > 0;
        if (k.compareTo(qi) <= 0) {
            BigInteger x = k.multiply(d1);
            if (x.compareTo(xMax) <= 0) {
                return x;
            }
            BigInteger x1 = x.subtract(d1);
            assert x1.compareTo(xMin) < 0 && xMax.compareTo(x) < 0;
            return x.subtract(search(x.subtract(xMax), x.subtract(xMin), frac.prev));
        } else {
            BigInteger x = qi.multiply(d1);
            return x.add(search(xMin.subtract(x), xMax.subtract(x), frac.prev.prev));
        }
    }

    void printBounds() {
        System.out.println("alpha = " + alpha);
        System.out.println(" = " + alpha.biNumerator() + " / " + alpha.biDenominator());
        System.out.print(" = ");
        for (Fraction f : fracts) {
            System.out.print(f.q);
            if (f.level < fracts.size() - 1) {
                System.out.print(" + 1/(");
            }
        }
        for (int i = 1; i < fracts.size(); i++) {
            System.out.print(")");
        }
        System.out.println();
        for (Fraction f : fracts) {
            System.out.print(" " + f.numerator + "/" + f.denominator);
        }
        System.out.println();

        SetInterval fracRange = SetIntervalOps.empty();
        for (Fraction f : fracts) {
            if (f.level == 0) {
                continue;
            }
            BigInteger i = BigInteger.ONE;
            do {
                BigInteger qq = f.prev.prev.denominator.add(f.prev.denominator.multiply(i));
                Rational v = RationalOps.mul(alpha, Rational.valueOf(qq));
                BigInteger iv = v.toBigInteger();
                Rational fracV = RationalOps.sub(v, Rational.valueOf(iv));
//                System.out.println(f.prev.prev.denominator + " + " + i + " * " + f.prev.denominator
//                        + " = " + qq);
                if (qq.compareTo(BigInteger.ONE) > 0) {
                    System.out.println("0 < i < " + qq + " ==> " + fracRange.inf() + " <= frac(alpha*i) <= " + fracRange.sup());
                }
                System.out.println("frac(alpha*" + qq + ") = " + fracV);
                if (i.equals(f.q)) {
                    assert fracV.equals(f.fracAlphaDen);
                    assert fracRange.equal(f.fracAlphaDenHull);
                }
                fracRange = SetIntervalOps.convexHull(fracRange, SetIntervalOps.nums2(fracV, fracV));
                i = i.add(BigInteger.ONE);
            } while (i.compareTo(f.q) <= 0);
        }
    }

    void printBounds2() {
        System.out.println("alpha = " + alpha.doubleValue());
        /*
        System.out.print(" = ");
        for (Fraction f : fracts) {
            System.out.print(f.q);
            if (f.level < fracts.size() - 1) {
                System.out.print(" + 1/(");
            }
        }
        for (int i = 1; i < fracts.size(); i++) {
            System.out.print(")");
        }
        System.out.println();
        for (Fraction f : fracts) {
            System.out.print(" " + f.numerator + "/" + f.denominator);
        }
        System.out.println();
         */

        Rational eps = Rational.valueOf(0x1.5p-64);
        BigInteger cbMax = BigInteger.ONE.shiftLeft(54).add(BigInteger.valueOf(2));
        for (Fraction f : fracts) {
            if (f.level == 0) {
                continue;
            }
            if (!f.fracAlphaDenHull.isEmpty()) {
                Rational inf = (Rational) f.fracAlphaDenHull.inf();
                Rational sup1 = RationalOps.sub(Rational.one(), (Rational) f.fracAlphaDenHull.sup());
                if (inf.le(eps) || sup1.le(eps)) {
                    System.out.println("!!!!!!!!!!!!!!!!!");
                }
                System.out.println("0 < i < " + f.denominator.toString(16)
                        + " ==> " + Double.toHexString(inf.doubleValue()) + " <= frac(alpha*i) <= 1 - "
                        + Double.toHexString(sup1.doubleValue()));
            }
            if (f.level % 2 == 0) {
                System.out.println("frac(alpha*" + f.denominator.toString(16) + ") = "
                        + Double.toHexString(f.fracAlphaDen.doubleValue()));
            } else {
                Rational frac1 = RationalOps.sub(Rational.one(), f.fracAlphaDen);
                System.out.println("frac(alpha*" + f.denominator.toString(16) + ") = 1 - "
                        + Double.toHexString(frac1.doubleValue()));
            }
            if (f.denominator.compareTo(cbMax) > 0) {
                break;
            }
        }
    }

    /**
     * Integer point (x,y) with x less than denominator of a fraction which is
     * above/below line y = x*alpha, odd/even and closest to the line
     */
    private class Record {

        private final boolean isAbove_;
        private final boolean isOdd_;
        /**
         * x-coordinate of the best point or null
         */
        BigInteger x;
        /**
         * y-coordinate of the best point or null
         */
        BigInteger y;
        /**
         * signed verical distance from the best point to the line
         */
        Rational eps;

        private Record(boolean isAbove, boolean isOdd) {
            this.isAbove_ = isAbove;
            this.isOdd_ = isOdd;
        }

        @Override
        public boolean equals(Object o) {
            if (o instanceof Record) {
                Record that = (Record) o;
                return this.isAbove_ == that.isAbove_
                        && this.isOdd_ == that.isOdd_
                        && this.x.equals(that.x)
                        && this.y.equals(that.y)
                        && this.eps.equals(that.eps);
            }
            return false;
        }

        /**
         * Update record if point (newX,newY_) is closer to the line y = x*alpha
         * than previous point. Check that newY_ is the closest odd/even point
         * with given x=newX which is strictly above/below the line y = x*alpha
         *
         * @param newX x-coordinate of candidate point
         * @param newY_ expected y-coordinate of candidate point
         * @param isAbove above/below
         * @param isOdd odd/even
         */
        private void update(BigInteger newX, BigInteger newY_, boolean isAbove, boolean isOdd) {
            assert isAbove == isAbove_;
            assert isOdd == isOdd_;
            BigInteger t = newX.multiply(alphaN);
            Rational exact = RationalOps.mul(alpha, Rational.valueOf(newX));
            if (isAbove) {
                BigInteger newY = divideFloor(t, alphaD).add(BigInteger.ONE);
                if (newY.testBit(0) != isOdd) {
                    newY = newY.add(BigInteger.ONE);
                }
                assert newY.equals(newY_);
                Rational newEps = RationalOps.sub(Rational.valueOf(newY), exact);
                assert newEps.signum() > 0;
                if (eps == null || newEps.compareTo(eps) < 0) {
                    x = newX;
                    y = newY;
                    eps = newEps;
                }
            } else {
                BigInteger newY = divideCeiling(t, alphaD).subtract(BigInteger.ONE);
                if (newY.testBit(0) != isOdd) {
                    newY = newY.subtract(BigInteger.ONE);
                }
                assert newY.equals(newY_);
                Rational newEps = RationalOps.sub(Rational.valueOf(newY), exact);
                assert newEps.signum() < 0;
                if (eps == null || newEps.compareTo(eps) > 0) {
                    x = newX;
                    y = newY;
                    eps = newEps;
                }
            }
        }

        /**
         * Update record of a fraction by candidate point which is some
         * reference point plus record of the previous (rougher) fraction
         *
         * @param subX x-coordinate of reference point
         * @param subY y-coordinate of reference point
         * @param subRecord record of prevoud fraction
         * @param isAbove
         * @param isOdd
         */
        private void update(BigInteger subX, BigInteger subY, Record subRecord, boolean isAbove, boolean isOdd) {
            assert isAbove == isAbove_;
            assert isOdd == isOdd_;
            if (subRecord.eps != null) {
                assert subRecord.isAbove_ == isAbove;
                assert subRecord.isOdd_ ^ subY.testBit(0) == isOdd;
                update(subX.add(subRecord.x), subY.add(subRecord.y), isAbove, isOdd);
            }
        }
    }

    /**
     * Continous fraction of alpha with certain depth level.
     */
    private class Fraction {

        /**
         * depth level
         */
        private final int level;
        /**
         * Previous (rougher fraction)
         */
        private final Fraction prev;
        /**
         * Integer quotient of the fraction
         */
        private final BigInteger q;
        /**
         * Numerator of approximation to alpha define by this level
         */
        private final BigInteger numerator;
        /**
         * Denominator of approximation to alpha define by this level
         */
        private final BigInteger denominator;
        /**
         * Approximation to alpha define by this level
         */
        private final ExtendedRational r;
        /**
         * Fractional part of alpha*denominator
         */
        private final Rational fracAlphaDen;
        /**
         * Hull of possible fractional parts of alpha*i where 0 < i <
         * denominator.
         */
        private final SetInterval fracAlphaDenHull;
        /**
         * True of approximation is above the line y = alpha*x
         */
        private final boolean aboveAlpha;
        /**
         * signed vertical distance to the line
         */
        private final Rational eps;
        /**
         * true if numerator is odd
         */
        private final boolean oddY;
        private final Record aboveEvenRecord = new Record(true, false);
        private final Record aboveOddRecord = new Record(true, true);
        private final Record belowEvenRecord = new Record(false, false);
        private final Record belowOddRecord = new Record(false, true);
        private boolean inited;

        private Fraction(int level, Fraction prev, BigInteger q) {
            this.level = level;
            this.prev = prev;
            this.q = q;
            aboveAlpha = (level & 1) != 0;
            switch (level) {
                case -2:
                    numerator = BigInteger.ZERO;
                    denominator = BigInteger.ONE;
                    r = Rational.zero();
                    fracAlphaDen = null;
                    fracAlphaDenHull = SetIntervalOps.empty();
                    break;
                case -1:
                    numerator = BigInteger.ONE;
                    denominator = BigInteger.ZERO;
                    r = Rational.POSITIVE_INFINITY;
                    fracAlphaDen = null;
                    fracAlphaDenHull = SetIntervalOps.empty();
                    break;
                default:
                    assert prev.level == level - 1;
                    numerator = prev.prev.numerator.add(prev.numerator.multiply(q));
                    denominator = prev.prev.denominator.add(prev.denominator.multiply(q));
                    r = Rational.valueOf(numerator, denominator);
                    Rational alphaDen = RationalOps.mul(alpha, Rational.valueOf(denominator));
                    BigInteger floorAlphaDen = alphaDen.toBigInteger();
                    fracAlphaDen = RationalOps.sub(alphaDen, Rational.valueOf(floorAlphaDen));
                    if (level == 0 || r.isInteger()) {
                        assert denominator.equals(BigInteger.ONE);
                        fracAlphaDenHull = SetIntervalOps.empty();
                    } else if (level % 2 == 0) {
                        Rational fracHi = prev.fracAlphaDen;
                        Rational fracHi1 = RationalOps.sub(Rational.one(), fracHi);
                        Rational fracLo = RationalOps.add(fracAlphaDen, fracHi1);
                        fracAlphaDenHull = SetIntervalOps.nums2(fracLo, fracHi);
                    } else {
                        Rational fracLo = prev.fracAlphaDen;
                        Rational fracHi = fracAlphaDen;
                        if (fracHi.signum() == 0) {
                            assert fracLo.signum() > 0;
                            fracHi = Rational.one();
                        }
                        fracHi = RationalOps.sub(fracHi, fracLo);
                        fracAlphaDenHull = SetIntervalOps.nums2(fracLo, fracHi);
                    }
                    break;
            }
            assert numerator.equals(r.biNumerator());
            assert denominator.equals(r.biDenominator());
            eps = RationalOps.sub(Rational.valueOf(numerator), RationalOps.mul(Rational.valueOf(denominator), alpha));
            assert aboveAlpha ? eps.signum() >= 0 : eps.signum() <= 0;
            oddY = numerator.testBit(0);
            if (denominator.compareTo(BigInteger.ONE) > 0) {
                assert level >= 1;
                BigInteger lower = BigInteger.ONE;
                BigInteger upper = denominator.subtract(BigInteger.ONE);
                Record aboveEvenRecord_ = new Record(true, false);
                Record aboveOddRecord_ = new Record(true, true);
                Record belowEvenRecord_ = new Record(false, false);
                Record belowOddRecord_ = new Record(false, true);
                computeRecord(aboveEvenRecord_, false, BigInteger.ZERO, BigInteger.ZERO, lower, upper, true, false);
                computeRecord(aboveOddRecord_, false, BigInteger.ZERO, BigInteger.ZERO, lower, upper, true, true);
                computeRecord(belowEvenRecord_, false, BigInteger.ZERO, BigInteger.ZERO, lower, upper, false, false);
                computeRecord(belowOddRecord_, false, BigInteger.ZERO, BigInteger.ZERO, lower, upper, false, true);

                computeInternalRecord(aboveEvenRecord, true, false);
                computeInternalRecord(aboveOddRecord, true, true);
                computeInternalRecord(belowEvenRecord, false, false);
                computeInternalRecord(belowOddRecord, false, true);

                assert aboveEvenRecord.equals(aboveEvenRecord_);
                assert aboveOddRecord.equals(aboveOddRecord_);
                assert belowEvenRecord.equals(belowEvenRecord_);
                assert belowOddRecord.equals(belowOddRecord_);

                if (oddY) {
                    if (aboveEvenRecord.eps != null) {
                        assert aboveEvenRecord.x.add(belowOddRecord.x).equals(denominator);
                    }
                    if (aboveOddRecord.eps != null) {
                        assert aboveOddRecord.x.add(belowEvenRecord.x).equals(denominator);
                    }
                } else {
                    if (aboveEvenRecord.eps != null) {
                        assert aboveEvenRecord.x.add(belowEvenRecord.x).equals(denominator);
                    }
                    if (aboveOddRecord.eps != null) {
                        assert aboveOddRecord.x.add(belowOddRecord.x).equals(denominator);
                    }

                }
            }
            inited = true;
        }

        private Record getRecord(boolean isAbove, boolean isOdd) {
            if (isAbove) {
                return isOdd ? aboveOddRecord : aboveEvenRecord;
            } else {
                return isOdd ? belowOddRecord : belowEvenRecord;
            }
        }

        private void computeInternalRecord(Record record, boolean isAbove, boolean isOdd) {
            BigInteger x1 = getX(isAbove, BigInteger.ONE);
            BigInteger y1 = getY(isAbove, BigInteger.ONE);
            BigInteger y1_ = y1;
            if (y1_.testBit(0) != isOdd) {
                y1_ = y1_.add(BigInteger.valueOf(isAbove ? +1 : -1));
            }
            boolean odd1 = isOddY(isAbove, BigInteger.ONE);
            BigInteger x2 = q.compareTo(BigInteger.ONE) > 0 ? getX(isAbove, BigInteger.valueOf(2)) : null;
            BigInteger y2 = q.compareTo(BigInteger.ONE) > 0 ? getY(isAbove, BigInteger.valueOf(2)) : null;
            BigInteger y2_ = y2;
            if (y2 != null && y2_.testBit(0) != isOdd) {
                y2_ = y2_.add(BigInteger.valueOf(isAbove ? +1 : -1));
            }
            boolean odd2 = q.compareTo(BigInteger.ONE) > 0 && isOddY(isAbove, BigInteger.valueOf(2));
            BigInteger xq = getX(isAbove, q);
            BigInteger yq = getY(isAbove, q);
            BigInteger yq_ = yq;
            if (yq_.testBit(0) != isOdd) {
                yq_ = yq_.add(BigInteger.valueOf(isAbove ? +1 : -1));
            }
            boolean oddq = isOddY(isAbove, q);
            if (isAbove == aboveAlpha) {
                assert xq.equals(prev.prev.denominator);
                record.update(BigInteger.ZERO, BigInteger.ZERO, prev.prev.getRecord(isAbove, isOdd), isAbove, isOdd);
                if (x2 != null) {
                    if (x2.signum() > 0) {
                        record.update(x2, y2_, isAbove, isOdd);
                    }
                    record.update(x2, y2, prev.getRecord(isAbove, isOdd ^ odd2), isAbove, isOdd);
                }
                if (x1.signum() > 0) {
                    record.update(x1, y1_, isAbove, isOdd);
                }
                record.update(x1, y1, prev.getRecord(isAbove, isOdd ^ odd1), isAbove, isOdd);
            } else {
                assert x1.equals(prev.denominator);
                record.update(BigInteger.ZERO, BigInteger.ZERO, prev.getRecord(isAbove, isOdd), isAbove, isOdd);
                if (x1.compareTo(denominator) < 0) {
                    record.update(x1, y1_, isAbove, isOdd);
                }
                if (x2 != null) {
                    record.update(x1, y1, prev.getRecord(isAbove, isOdd ^ odd1), isAbove, isOdd);
                    if (x2.compareTo(denominator) < 0) {
                        record.update(x2, y2_, isAbove, isOdd);
                    }
                }
                record.update(xq, yq, prev.prev.getRecord(isAbove, isOdd ^ oddq), isAbove, isOdd);
            }
//            System.out.println(numerator+"/"+denominator+(isAbove ? " above" : " below")+(isOdd ? " odd" : " even"));
//            System.out.println("x="+record.x);
//            System.out.println("y="+record.y);
//            if (eps != null) {
//                System.out.println("eps="+record.eps.doubleValue());
//            }
        }

        private void computeRecord(Record record, boolean subOdd, BigInteger subX, BigInteger subY, BigInteger minX, BigInteger maxX, boolean isAbove, boolean isOdd) {
            assert subOdd == subY.testBit(0);
            BigInteger lower = BigInteger.ONE;
            BigInteger upper = denominator.subtract(BigInteger.ONE);
            if (upper.signum() <= 0) {
                return;
            }
            if (inited && minX.compareTo(lower) <= 0 && maxX.compareTo(upper) >= 0) {
                Record subRec = getRecord(isAbove, subOdd ^ isOdd);
                record.update(subX.add(subRec.x), subY.add(subRec.y), isAbove, isOdd);
                return;
            }
            minX = minX.max(lower);
            maxX = maxX.min(upper);
//            System.out.println("sub="+subX+" subOdd="+subOdd+" level="+level);
//            System.out.println("min="+subX.add(minX));
//            System.out.println("max="+subX.add(maxX));
            if (minX.compareTo(maxX) > 0) {
                return;
            }
            if (isAbove == aboveAlpha) {
                BigInteger kMin = divideCeiling(denominator.subtract(maxX), prev.denominator);
                if (kMin.compareTo(q) <= 0) {
                    BigInteger kMinX = getX(isAbove, kMin);
                    BigInteger kMinY = getY(isAbove, kMin);
                    if (minX.compareTo(kMinX) <= 0 && kMinX.compareTo(maxX) <= 0 && subOdd ^ isOddY(isAbove, kMin) == isOdd) {
                        record.update(subX.add(kMinX), subY.add(kMinY), isAbove, isOdd);
                        return;
                    }
                }
                prev.prev.computeRecord(record, subOdd, subX, subY, minX, maxX, isAbove, isOdd);
                BigInteger k = kMin.add(BigInteger.valueOf(2)).min(q);
                while (k.compareTo(kMin) >= 0) {
                    BigInteger x = getX(isAbove, k);
                    BigInteger y = getY(isAbove, k);
                    if (x.compareTo(minX) >= 0 && x.compareTo(maxX) <= 0) {
                        BigInteger y_ = y;
                        if (y_.testBit(0) != subOdd ^ isOdd) {
                            y_ = y_.add(BigInteger.valueOf(isAbove ? +1 : -1));
                        }
                        record.update(subX.add(x), subY.add(y_), isAbove, isOdd);
                    }
                    prev.computeRecord(record, subOdd ^ isOddY(isAbove, k), subX.add(x), subY.add(y), minX.subtract(x), maxX.subtract(x), isAbove, isOdd);
                    k = k.subtract(BigInteger.ONE);
                }
            } else {
                BigInteger kMin = divideCeiling(minX, prev.denominator);
                if (kMin.compareTo(q) <= 0) {
                    BigInteger kMinX = getX(isAbove, kMin);
                    BigInteger kMinY = getY(isAbove, kMin);
                    if (minX.compareTo(kMinX) <= 0 && kMinX.compareTo(maxX) <= 0 && subOdd ^ isOddY(isAbove, kMin) == isOdd) {
                        record.update(subX.add(kMinX), subY.add(kMinY), isAbove, isOdd);
                        return;
                    }
                }
                BigInteger k = kMin.subtract(BigInteger.ONE);
                assert k.signum() >= 0;
                while (k.compareTo(q) <= 0 && k.compareTo(kMin.add(BigInteger.ONE)) <= 0) {
                    BigInteger x = getX(isAbove, k);
                    BigInteger y = getY(isAbove, k);
                    if (x.compareTo(minX) >= 0 && x.compareTo(maxX) <= 0) {
                        BigInteger y_ = y;
                        if (y_.testBit(0) != subOdd ^ isOdd) {
                            y_ = y_.add(BigInteger.valueOf(isAbove ? +1 : -1));
                        }
                        record.update(subX.add(x), subY.add(y_), isAbove, isOdd);
                    }
                    if (k.compareTo(q) < 0) {
                        prev.computeRecord(record, subOdd ^ isOddY(isAbove, k), subX.add(x), subY.add(y), minX.subtract(x), maxX.subtract(x), isAbove, isOdd);
                    }
                    k = k.add(BigInteger.ONE);
                }
                BigInteger xq = getX(isAbove, q);
                BigInteger yq = getY(isAbove, q);
                prev.prev.computeRecord(record, subOdd ^ isOddY(isAbove, q), subX.add(xq), subY.add(yq), minX.subtract(xq), maxX.subtract(xq), isAbove, isOdd);
            }
        }

        private BigInteger getX(boolean isAbove, BigInteger k) {
            assert level >= 0;
            assert k.signum() >= 0 && k.compareTo(q) <= 0;
            BigInteger offset = k.signum() > 0 ? prev.denominator.multiply(k) : BigInteger.ZERO;
            return isAbove == aboveAlpha ? denominator.subtract(offset) : offset;
        }

        private BigInteger getY(boolean isAbove, BigInteger k) {
            assert level >= 0;
            assert k.signum() >= 0 && k.compareTo(q) <= 0;
            BigInteger offset = k.signum() > 0 ? prev.numerator.multiply(k) : BigInteger.ZERO;
            return isAbove == aboveAlpha ? numerator.subtract(offset) : offset;
        }

        private boolean isOddY(boolean isAbove, BigInteger k) {
            assert level >= 0;
            assert k.signum() >= 0 && k.compareTo(q) <= 0;
            boolean offset = k.testBit(0) & prev.oddY;
            return isAbove == aboveAlpha ? oddY ^ offset : offset;
        }

        private Rational getEps(boolean isAbove, BigInteger k) {
            assert level >= 0;
            assert k.signum() >= 0 && k.compareTo(q) <= 0;
            Rational offset = k.signum() > 0 ? RationalOps.mul(prev.eps, Rational.valueOf(k)) : Rational.zero();
            return isAbove == aboveAlpha ? RationalOps.sub(eps, offset) : offset;
        }

        private BigInteger getInnerX(boolean isAbove) {
            assert level >= 0;
            if (numerator.compareTo(BigInteger.ONE) <= 0) {
                return null;
            }
            return isAbove == aboveAlpha ? denominator.subtract(prev.denominator) : prev.denominator;
        }

        private BigInteger getInnerY(boolean isAbove) {
            assert level >= 0;
            if (numerator.compareTo(BigInteger.ONE) <= 0) {
                return null;
            }
            return isAbove == aboveAlpha ? numerator.subtract(prev.numerator) : prev.numerator;
        }

        private Rational getInnerEps(boolean isAbove) {
            assert level >= 0;
            if (numerator.compareTo(BigInteger.ONE) <= 0) {
                return null;
            }
            return isAbove == aboveAlpha ? RationalOps.sub(eps, prev.eps) : prev.eps;
        }

        private BigInteger getInnerX(boolean isAbove, boolean isOdd) {
            assert level > 0;
            if (level == 1) {
                assert numerator.compareTo(BigInteger.ONE) > 0;
            }
            return null;
        }
    }

    public static void main(String[] args) {
        Rational alpha = Rational.valueOf(43, 33);
        Fractions fractions = new Fractions(alpha);
        fractions.printBounds();
    }
}
