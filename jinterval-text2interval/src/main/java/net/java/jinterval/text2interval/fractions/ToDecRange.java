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
import java.util.ArrayList;
import java.util.List;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 *
 */
public class ToDecRange {

    final BinaryValueSet f;
    final int q;
    final BigInteger cMin;
    final BigInteger cMax;
    final Rational rMin;
    final Rational rMax;
    final int ord2;
    final int ordD;
    final int qb;

    private ToDecRange(BinaryValueSet f, int q, BigInteger cMin, BigInteger cMax, int ordD) {
        this.f = f;
        this.q = q;
        this.cMin = cMin;
        this.cMax = cMax;
        this.ordD = ordD;
        int e = q + f.getPrecision() - 1;
        assert f.getMinExp() <= e && e <= f.getMaxExp();
        assert cMin.signum() > 0;
        assert e == f.getMinExp() || cMin.bitLength() == f.getPrecision();
        assert cMin.compareTo(cMax) <= 0;
        assert cMax.bitLength() == cMin.bitLength();
        rMin = Rational.valueOf(cMin, q);
        rMax = Rational.valueOf(cMax, q);
        ord2 = rMin.intFloorLog2() + 1;
        assert ord2 == rMax.intFloorLog2() + 1;
        Rational expD = ordD >= 0
                ? Rational.valueOf(BigInteger.TEN.pow(ordD))
                : RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(-ordD)));
        Rational expD1 = RationalOps.div(expD, Rational.valueOf(10));
        assert expD1.compareTo(rMin) <= 0;
        assert rMax.compareTo(expD) < 0;
        qb = q - (e == f.getMinExp() || cMin.bitCount() != 1 ? 1 : 2);
    }

    static List<ToDecRange> makeRanges(BinaryValueSet f) {
        ExtendedRationalContext rc = ExtendedRationalContexts.mkCeiling(f);
        List<ToDecRange> result = new ArrayList<>();
        int qMin = f.getMinExp() - f.getPrecision() + 1;
        String s = BigInteger.ONE.shiftLeft(-qMin).toString();
        int ordD = -s.length() + 1;
        Rational expD = RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(-ordD)));
        ExtendedRational expDceil = rc.rnd(expD);
        BigInteger cLast = ExtendedRationalOps.div(expDceil, Rational.exp2(qMin)).toBigInteger();
        cLast = cLast.subtract(BigInteger.ONE);
        for (int i = 0; i < f.getPrecision(); i++) {
            BigInteger cMin = BigInteger.ONE.shiftLeft(i);
            BigInteger cMax = BigInteger.ONE.shiftLeft(i + 1).subtract(BigInteger.ONE);
            if (cMax.compareTo(cLast) < 0) {
                result.add(new ToDecRange(f, qMin, cMin, cMax, ordD));
            } else {
                if (cMax.equals(cLast)) {
                    result.add(new ToDecRange(f, qMin, cMin, cMax, ordD));
                } else {
                    result.add(new ToDecRange(f, qMin, cMin, cLast, ordD));
                    result.add(new ToDecRange(f, qMin, cLast.add(BigInteger.ONE), cMax, ordD + 1));
                }
                ordD++;
                expD = RationalOps.mul(expD, Rational.valueOf(10));
                expDceil = rc.rnd(expD);
                cLast = ExtendedRationalOps.div(expDceil, Rational.exp2(qMin)).toBigInteger();
                cLast = cLast.subtract(BigInteger.ONE);
            }
        }
        BigInteger cPow = BigInteger.ONE.shiftLeft(f.getPrecision() - 1);
        BigInteger cMin = cPow.add(BigInteger.ONE);
        BigInteger cMax = BigInteger.ONE.shiftLeft(f.getPrecision()).subtract(BigInteger.ONE);
        for (int e = f.getMinExp() + 1; e <= f.getMaxExp(); e++) {
            int q = e - f.getPrecision() + 1;
            if (expDceil.isFinite()) {
                cLast = ExtendedRationalOps.div(expDceil, Rational.exp2(q)).toBigInteger();
                cLast = cLast.subtract(BigInteger.ONE);
            } else {
                cLast = null;
            }
            result.add(new ToDecRange(f, q, cPow, cPow, ordD));
            if (cLast == null || cMax.compareTo(cLast) < 0) {
                result.add(new ToDecRange(f, q, cMin, cMax, ordD));
            } else {
                if (cMax.equals(cLast)) {
                    result.add(new ToDecRange(f, q, cMin, cMax, ordD));
                } else {
                    result.add(new ToDecRange(f, q, cMin, cLast, ordD));
                    result.add(new ToDecRange(f, q, cLast.add(BigInteger.ONE), cMax, ordD + 1));
                }
                ordD++;
                expD = RationalOps.mul(expD, Rational.valueOf(10));
                expDceil = rc.rnd(expD);
            }
        }
        return result;
    }

    static void exploreRanges(BinaryValueSet f) {
        int H = BigInteger.ONE.shiftLeft(f.getPrecision()).toString().length() + 1;
        List<ToDecRange> ranges = makeRanges(f);
        int P = f.getPrecision();
        int qMin = f.getMinExp() - P + 1;
        int qMax = f.getMaxExp() - P + 1;
        System.out.println("prec=" + f.getPrecision()
                + " q in [" + qMin + ".." + qMax + "]"
                + " H=" + H
                + " " + ranges.size() + " ranges");
        Rational epsMin = null, epsMax = null;
        for (ToDecRange range : ranges) {
            System.out.println(range.rMin + ".." + range.rMax
                    + " qb=" + range.qb
                    + " ordD=" + range.ordD);
            BigInteger cbMin = range.cMin.shiftLeft(range.q - range.qb);
            BigInteger cbMax = range.cMax.shiftLeft(range.q - range.qb);
            int e = range.ordD - H;
            Rational ulpD = e >= 0
                    ? Rational.valueOf(BigInteger.TEN.pow(e))
                    : RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(-e)));
            Rational alpha = RationalOps.div(Rational.exp2(range.qb), ulpD);
//            System.out.println("  alpha=" + alpha);
            Fractions fractions = new Fractions(alpha);
            BigInteger cbExact = fractions.searchExact(cbMin, cbMax);
            if (cbExact != null) {
                Rational fH = RationalOps.mul(Rational.valueOf(cbExact), alpha);
                BigInteger sH = fH.toBigInteger();
                assert Rational.valueOf(sH).equals(fH);
                System.out.println("  exact cb=0x" + cbExact.toString(16) + " sH=" + sH + " fH=" + fH);
            }
            BigInteger cbBelow = fractions.search(cbMin, cbMax, false);
            if (cbBelow != null) {
                Rational v = Rational.valueOf(cbBelow, range.qb);
                Rational fH = RationalOps.mul(Rational.valueOf(cbBelow), alpha);
                BigInteger sH = fH.toBigInteger();
                Rational eps = RationalOps.sub(fH, Rational.valueOf(sH));
                System.out.println("  below cb=0x" + cbBelow.toString(16) + " eps=" + Double.toHexString(eps.doubleValue()));
                if (eps.signum() > 0 && (epsMin == null || eps.compareTo(epsMin) < 0)) {
                    epsMin = eps;
                }
            }
            BigInteger cbAbove = fractions.search(cbMin, cbMax, true);
            if (cbAbove != null) {
                Rational v = Rational.valueOf(cbAbove, range.qb);
                Rational fH = RationalOps.mul(Rational.valueOf(cbAbove), alpha);
                BigInteger sH = fH.toBigInteger();
                Rational eps = RationalOps.sub(fH, Rational.valueOf(sH));
                Rational eps1 = RationalOps.sub(Rational.one(), eps);
                if (eps1.signum() > 0 && (epsMax == null || eps.compareTo(epsMax) > 0)) {
                    epsMax = eps;
                }
                System.out.println("  above cb=0x" + cbAbove.toString(16) + " eps=1-" + Double.toHexString(eps.doubleValue()));
            }
        }
        Rational eps1 = RationalOps.sub(Rational.one(), epsMax);
        System.out.println("eps in [ " + Double.toHexString(epsMin.doubleValue())
                + " .. 1 - " + Double.toHexString(eps1.doubleValue()) + " ]");
    }

    public static void main(String[] args) {
//       exploreRanges(BinaryValueSet.BINARY16);
//        exploreRanges(BinaryValueSet.BINARY32);
        exploreRanges(BinaryValueSet.BINARY64);
//        exploreRanges(BinaryValueSet.BINARY80);
//        exploreRanges(BinaryValueSet.BINARY128);
    }

}
