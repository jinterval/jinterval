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

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.io.Serializable;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * An entry to the table for toDec algorithm
 */
public class ToDecTable implements Serializable {

    static final long serialVersionUID = 100;

    final BinaryValueSet f;
    final int qb;
    final BigInteger cblMin;
    final BigInteger cbrMax;
    final Rational vlMin;
    final Rational vrMax;
    final int r;

    private static int ord10pow2(int e) {
        // Constants suggested by Raffaello Giulietti
        long Q = 41;
        long C = 661_971_961_083L;
        return (int) ((C * e) >> Q) + 1;
    }

    private static int ord2pow10(int e) {
        // Constants suggested by Raffaello Giulietti
        long Q = 40;
        long C = 3_652_498_566_964L;
        return (int) ((C * e) >> Q) + 1;
    }

    private static void checkOrd10pow2() {
        int e_range = 2048;
//        int e_range = 5_456_721;
        int cacheOrd10 = ord10pow2(-e_range);
        Rational cachePow10Pred = RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(-cacheOrd10 + 1)));
        Rational cachePow10 = RationalOps.mul(cachePow10Pred, Rational.valueOf(10));
        for (int e = -e_range; e <= e_range; e++) {
            int ord10 = ord10pow2(e);
            while (cacheOrd10 != ord10) {
                cacheOrd10++;
                cachePow10Pred = cachePow10;
                cachePow10 = RationalOps.mul(cachePow10, Rational.valueOf(10));
            }
            Rational pow2 = Rational.exp2(e);
            assert cachePow10Pred.compareTo(pow2) <= 0;
            assert pow2.compareTo(cachePow10) < 0;
        }
    }

    private static void checkOrd2pow10() {
        int e_range = 2048;
//        int e_range = 5_456_721;
        Rational pow10 = RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(e_range)));
        for (int e = -e_range; e <= e_range; e++) {
            int ord2 = ord2pow10(e);
            assert ord2 == pow10.intFloorLog2() + 1;
            pow10 = RationalOps.mul(pow10, Rational.valueOf(10));
        }
    }

    private ToDecTable(BinaryValueSet f, int qb, int r) {
        this.f = f;
        this.qb = qb;
        int q = qb + 1;
        int e = qb + f.getPrecision();
        assert f.getMinExp() <= e && e <= f.getMaxExp();
        this.cblMin = e == f.getMinExp()
                ? BigInteger.ONE
                : BigInteger.ONE.shiftLeft(f.getPrecision()).subtract(BigInteger.ONE);
        this.cbrMax = BigInteger.ONE.shiftLeft(f.getPrecision() + 1).add(BigInteger.ONE);
        vlMin = Rational.valueOf(cblMin, qb);
        vrMax = Rational.valueOf(cbrMax, qb);
        this.r = r;
        assert r == ord10pow2(q) - 1;
        Rational ulp = Rational.exp2(q);
        Rational ulpD = r >= 0
                ? Rational.valueOf(BigInteger.TEN.pow(r))
                : RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(-r)));
        Rational ulpD1 = RationalOps.mul(ulpD, Rational.valueOf(10));
        assert ulpD.compareTo(ulp) <= 0;
        assert ulp.compareTo(ulpD1) < 0;
    }

    static List<ToDecTable> makeTable(BinaryValueSet f) {
        List<ToDecTable> table = new ArrayList<>();
        int qMin = f.getMinExp() - f.getPrecision() + 1;
        String s = BigInteger.ONE.shiftLeft(-qMin).toString();
        int r = -s.length();
        Rational ulpD = RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(-r)));
        Rational ulpD1 = RationalOps.mul(ulpD, Rational.valueOf(10));
        table.add(new ToDecTable(f, qMin - 1, r));
        for (int e = f.getMinExp() + 1; e <= f.getMaxExp(); e++) {
            int q = e - f.getPrecision() + 1;
            Rational ulp = Rational.exp2(q);
            while (ulp.compareTo(ulpD1) >= 0) {
                r++;
                ulpD = ulpD1;
                ulpD1 = RationalOps.mul(ulpD, Rational.valueOf(10));
            }
            table.add(new ToDecTable(f, q - 1, r));
        }
        return table;
    }

    static void printTable(BinaryValueSet f, List<ToDecTable> table) {
        System.out.println("prec=" + f.getPrecision());
        for (ToDecTable e : table) {
            System.out.println("qb=" + e.qb
                    + " v in [ " + e.vlMin + " .. " + e.vrMax + "]"
                    + " ulp=" + Rational.exp2(e.qb + 1)
                    + " r=" + e.r
            );
        }
    }

    public static SetInterval findNonzeroFract(BinaryValueSet f, List<ToDecTable> table) {
        int P = f.getPrecision();
        int qMin = f.getMinExp() - P + 1;
        int qMax = f.getMaxExp() - P + 1;
        System.out.println("prec=" + f.getPrecision()
                + " q in [" + qMin + ".." + qMax + "]"
                + " " + table.size() + " table entries");
        Rational epsMin = null, epsMax = null;
        for (ToDecTable entry : table) {
            System.out.println(entry.vlMin + ".." + entry.vrMax
                    + " qb=" + entry.qb
                    + " r=" + entry.r);
            BigInteger cblMin = entry.cblMin;
            BigInteger cbrMax = entry.cbrMax;
            int r = entry.r;
            Rational halfUlp = Rational.exp2(entry.qb);
            Rational ulpD = r >= 0
                    ? Rational.valueOf(BigInteger.TEN.pow(r))
                    : RationalOps.recip(Rational.valueOf(BigInteger.TEN.pow(-r)));
            Rational alpha = RationalOps.div(halfUlp, ulpD);
            alpha = RationalOps.mul(Rational.valueOf(2), alpha);
//            System.out.println("  alpha=" + alpha);
            Fractions fractions = new Fractions(alpha);
            fractions.printBounds2();
//            fractions.printBounds();
            BigInteger cbExact = fractions.searchExact(cblMin, cbrMax);
            if (cbExact != null) {
                Rational fH = RationalOps.mul(Rational.valueOf(cbExact), alpha);
                BigInteger sH = fH.toBigInteger();
                assert Rational.valueOf(sH).equals(fH);
                System.out.println("  exact cb=0x" + cbExact.toString(16) + " sH=" + sH + " fH=" + fH);
            }
            BigInteger cbBelow = fractions.search(cblMin, cbrMax, false);
            if (cbBelow != null) {
                Rational v = Rational.valueOf(cbBelow, entry.qb);
                Rational fH = RationalOps.mul(Rational.valueOf(cbBelow), alpha);
                BigInteger sH = fH.toBigInteger();
                Rational eps = RationalOps.sub(fH, Rational.valueOf(sH));
                System.out.println("  below cb=0x" + cbBelow.toString(16) + " eps=" + Double.toHexString(eps.doubleValue()));
                if (eps.signum() > 0 && (epsMin == null || eps.compareTo(epsMin) < 0)) {
                    epsMin = eps;
                }
            }
            BigInteger cbAbove = fractions.search(cblMin, cbrMax, true);
            if (cbAbove != null) {
                Rational v = Rational.valueOf(cbAbove, entry.qb);
                Rational fH = RationalOps.mul(Rational.valueOf(cbAbove), alpha);
                BigInteger sH = fH.toBigInteger();
                Rational eps = RationalOps.sub(fH, Rational.valueOf(sH));
                Rational eps1 = RationalOps.sub(Rational.one(), eps);
                if (eps1.signum() > 0 && (epsMax == null || eps.compareTo(epsMax) > 0)) {
                    epsMax = eps;
                }
                System.out.println("  above cb=0x" + cbAbove.toString(16) + " eps=1-" + Double.toHexString(eps1.doubleValue()));
            }
        }
        return SetIntervalOps.nums2(epsMin, epsMax);
    }

    public static void exploreTable(BinaryValueSet f) {
        List<ToDecTable> table = makeTable(f);
//        printTable(f, table);
        SetInterval epsInterval = findNonzeroFract(f, table);
        Rational epsMin = (Rational) epsInterval.inf();
        Rational epsMax = (Rational) epsInterval.sup();
        Rational epsMax1 = RationalOps.sub(Rational.one(), epsMax);
        Rational eps = RationalOps.min(epsMin, epsMax1);
        int M = -eps.intFloorLog2();
        System.out.println("eps in [ " + Double.toHexString(epsMin.doubleValue())
                + " .. 1 - " + Double.toHexString(epsMax1.doubleValue()) + " ]"
                + " M=" + M);
        int rMin = table.get(0).r;
        int rMax = table.get(0).r;

    }

    private static void writeTable(BinaryValueSet f, File file) throws IOException {
        List<ToDecTable> table = makeTable(f);
        try (ObjectOutputStream out
                = new ObjectOutputStream(
                        new BufferedOutputStream(
                                new FileOutputStream(file)))) {
            out.writeObject(table);
        }
    }

    private static List<ToDecTable> readTable(File file) throws IOException, ClassNotFoundException {
        try (ObjectInputStream in
                = new ObjectInputStream(
                        new BufferedInputStream(
                                new FileInputStream(file)))) {
            return (List<ToDecTable>) in.readObject();
        }
    }

    private static void genTableR(PrintStream out, List<ToDecTable> table) {
        int pMin = -table.get(table.size() - 1).r;
        int pMax = -table.get(0).r;
        out.println("static final int MIN_POW_5 = " + pMin + ";");
        out.println();
        Rational pow5 = RationalOps.recip(Rational.valueOf(BigInteger.valueOf(5).pow(-pMin)));
        out.println("");
        out.println("private static p(int q, long ch, long cl) {}");
        out.println();
        long MASK = (1L << 63) - 1;
        for (int p = pMin; p <= pMax; p++) {
            int q63 = pow5.intFloorLog2() + 1 - 63;
            int q126 = pow5.intFloorLog2() + 1 - 2 * 63;
            BigInteger c = RationalOps.div(pow5, Rational.exp2(q126)).toBigInteger();
            if (pow5.ne(Rational.valueOf(c, q126))) {
                c = c.add(BigInteger.ONE);
            }
            long cl = c.longValue() & MASK;
            long ch = c.shiftRight(63).longValue() & MASK;
            assert ch == RationalOps.div(pow5, Rational.exp2(q63)).longValue();
            out.printf("  p(%d, 0x%016xL, 0x%016xL); // 5^%d\n", q126, ch, cl, p);
            pow5 = RationalOps.mul(pow5, Rational.valueOf(5));
        }
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        checkOrd10pow2();
        checkOrd2pow10();
        BinaryValueSet f = BinaryValueSet.BINARY64;
        File file = new File("double-table,ser");
//        writeTable(f, file);
        List<ToDecTable> table = readTable(file);
        findNonzeroFract(f, table);
        genTableR(System.out, table);
    }
}
