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
package net.java.jinterval.text2interval;

import com.sun.jna.Memory;
import com.sun.jna.ptr.DoubleByReference;
import java.math.BigInteger;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.text2interval.jna.DecoratedInfSupB64;
import net.java.jinterval.text2interval.jna.T;

/**
 * Class that tries to implement infsup-b64-text2interval operation in effiicent
 * way. This class is not thread-safe.
 */
public class Text2interval {

    private static final int DIGIT_BLOCK_SIZE = 19;
    private static final BigInteger BI_DIGIT_BLOCK_RADIX = BigInteger.TEN.pow(DIGIT_BLOCK_SIZE);
    private final SetIntervalContext ctx = SetIntervalContexts.getTightest(BinaryValueSet.BINARY64);
    String s;
    int pBeg, qBeg;
    private final int NUM_DIGIT_BLOCKS = T.get_num_digit_blocks();
    Memory mems;
    String ps, qs, fns, fds;
    BigInteger[] pb, qb, fnb, fdb;

    public SetInterval text2interval(String s) {
//        benchConvDec();
//        showNaN();
        double d = 1.23455e-10;
//        d = Double.MAX_VALUE;
        d = 1;
//        d = Double.MIN_VALUE;
        test(d);
        return ctx.textToInterval(s);
    }

    private void benchConvDec() {
        Memory m = new Memory(1 * 1000 * 1000);
        Memory ms = new Memory(1 * 1000 * 1000);
        for (int i = 0; i < 20; i++) {
            BigInteger bi = BigInteger.ONE.shiftLeft(1 << i);
            String s = bi.toString();
            assert s.length() < m.size();
            ms.setString(0, s);
            long time0 = System.nanoTime();
            int len = T.loop_conv_dec(1000, ms, s.length(), m);
            long time1 = System.nanoTime();
            assert len == (bi.bitLength() + 63) / 64;
            for (int j = 0; j < len; j++) {
                assert m.getLong(j * 8) == bi.shiftRight(j * 64).longValue();
            }
            System.out.println(i + " " + (time1 - time0) / 1e6 + "uSec");
        }
    }

    private void showNaN() {
        double x = 0.0;
        double z = x / x;
        System.out.println(Long.toHexString(Double.doubleToRawLongBits(z)));
    }

    private void test(double d) {
        Rational r = Rational.valueOf(d);
        StringBuilder sb;
        sb = new StringBuilder();
        sb.append(r.biNumerator().toString());
//        for (int i = 0; i < 100 * 1000 * 1000; i++) {
//            sb.append('0');
//        }
        sb.append("00");
        ps = sb.toString();
        pb = stringToBlocks(ps);
        sb = new StringBuilder();
        sb.append(r.biDenominator().toString());
//        for (int i = 0; i < 100 * 1000 * 1000; i++) {
//            sb.append('0');
//        }
        sb.append("00");
        qs = sb.toString();
        qb = stringToBlocks(qs);
        sb = null;
//        s = "-" + ps + "/" + qs;
        s = "[" + ps + "/" + qs + "]";
        System.out.println("s.length()=" + s.length());

//        if (ps.length() - 310 > qs.length()) {
//            return; // [Double.MAX_VALUE,Infinity]
//        }
//        if (ps.length() < qs.length() - 330) {
//            return; // [0,Double.MIN_VALUE]
//        }
//        if (ps.length() < 2 * DIGIT_BLOCK_SIZE || qs.length() < 2 * DIGIT_BLOCK_SIZE) {
//            BigInteger bp = new BigInteger(ps);
//            BigInteger bq = new BigInteger(qs);
//            int lbp = bp.getLowestSetBit();
//            bp = bp.shiftRight(lbp);
//            int lbq = bq.getLowestSetBit();
//            bq = bq.shiftRight(lbq);
//            int e = lbp - lbq;
//            int dl = bp.bitLength() - bq.bitLength();
//            if (dl < 54) {
//                bp = bp.shiftLeft(54 - dl);
//                e -= 54 - dl;
//            }
//            BigInteger[] qr = bp.divideAndRemainder(bq);
//            BigInteger quot = qr[0];
//            boolean exact = qr[1].signum() == 0;
//            int blQuot = quot.bitLength();
//            assert blQuot >= 53;
//            int ieeeExp = e + blQuot - 1;
//            if (ieeeExp > 1023) {
//                return; // [Double.MAX_VALUE,Infinity]
//            }
//            int ieeeUlp = Math.max(ieeeExp, -1022) - 52;
//            assert ieeeUlp >= e;
//            exact = exact && e + quot.getLowestSetBit() >= ieeeUlp;
//            BigInteger m = quot.shiftRight(ieeeUlp - e);
//            assert m.bitLength() <= 53;
//            long ieeeBits = m.longValue();
//            if (ieeeExp > -1022) {
//                ieeeBits += (ieeeExp + 1022L) << 52;
//            }
//            double l = Double.longBitsToDouble(ieeeBits);
//            double u = exact ? l : Double.longBitsToDouble(ieeeBits + 1);
//            return; // [l,u]
//        }

//        pBeg = 1;
        pBeg = 0;
        qBeg = s.length() - 1 - qs.length();
//        s = "[0.150]";
        s = "1.00?99e309";
//        s = "[-0x1.2aaaaaaaaaaabp1,-0x1.2aaaaaaaaaaabp1]";
        mems = new Memory(s.length() + 1);
        mems.setString(0, s);
        T.s.setPointer(0, mems);
        T.p.read();
        T.q.read();
        DecoratedInfSupB64 ret = new DecoratedInfSupB64();
        for (int i = 0; i < 1; i++) {
//            T.set_digits(T.p, mems.share(pBeg), mems.share(pBeg + ps.length()));
//            T.set_digits(T.q, mems.share(qBeg), mems.share(qBeg + qs.length()));
            long time0 = System.nanoTime();
            T.textToInterval(mems, ret);
//            evalRat();
            long time1 = System.nanoTime();
//            T.p.read();
//            T.q.read();
//            System.out.println("mems="+ mems);
//            System.out.println("pbeg="+ T.p.beg);
//            System.out.println("pend="+ T.p.end);
//            System.out.println("qbeg="+ T.q.beg);
//            System.out.println("qend="+ T.q.end);
            double l = ret.inf;
            double u = ret.sup;
            byte decor = ret.decoration;
            System.out.println("[" + l + "," + u + "]_" + decor + " " + (time1 - time0) / 1e3 + "uSec");
        }
    }

    private void evalRat() {
        long fBits = T.guess_double();
        int cmp;
        if (fBits == 0) {
            cmp = +1;
        } else if (fBits >= 0x7FF0000000000000L) {
            cmp = -1;
        } else {
            T.init_f(fBits);
            cmp = T.cmp_loop();
        }
        T.infBits.setLong(0, cmp >= 0 ? fBits : fBits - 1);
        T.supBits.setLong(0, cmp <= 0 ? fBits : fBits + 1);
    }

    private void evalRat2() {
        long fBits = T.guess_double();
        int cmp;
        if (fBits == 0) {
            cmp = +1;
        } else if (fBits >= 0x7FF0000000000000L) {
            cmp = -1;
        } else {
            T.init_f(fBits);
            cmp = 0;
            if (ps.length() >= 2 * DIGIT_BLOCK_SIZE && qs.length() >= 2 * DIGIT_BLOCK_SIZE) {
                cmp = cmp128();
            }
            if (cmp == 0) {
                cmp = cmpLoop();
            }
        }
        T.infBits.setLong(0, cmp >= 0 ? fBits : fBits - 1);
        T.supBits.setLong(0, cmp <= 0 ? fBits : fBits + 1);
    }

    private int cmp128() {
        BigInteger ph = new BigInteger(ps.substring(0, 2 * DIGIT_BLOCK_SIZE));
        assert ph.bitLength() <= 128;
        BigInteger qh = new BigInteger(qs.substring(0, 2 * DIGIT_BLOCK_SIZE));
        assert qh.bitLength() <= 128;
        int e10 = ps.length() - qs.length();
        int e2;
        Pow5 pow5;
        BigInteger m2;
        if (e10 >= 0) {
            pow5 = new Pow5(e10);
            e2 = pow5.ep;
            m2 = pow5.mp;
        } else {
            pow5 = new Pow5(-e10);
            e2 = pow5.en;
            m2 = pow5.mn;
        }

        long ieeeBits = T.ieeeBits.getLong(0);
        int expField = (int) (ieeeBits >> 52);
        int ieeeUlp;
        int exp;
        BigInteger m;
        if (expField > 0) {
            exp = -1023 + 1 + expField;
            m = BigInteger.valueOf(0x10000000000000L | ieeeBits & 0xFFFFFFFFFFFFFL).shiftLeft(64 - 53);
        } else {
            int leading = Long.numberOfLeadingZeros(ieeeBits);
            exp = -1022 - 52 + 64 - leading;
            m = BigInteger.valueOf(ieeeBits & 0xFFFFFFFFFFFFFL).shiftLeft(leading);
        }
        assert m.bitLength() == 64;
        BigInteger left = ph.multiply(m2).shiftRight(128);
        int leftE = e2 + e10;
        BigInteger right = qh.multiply(m).shiftRight(64);
        int rightE = exp;
        if (leftE > rightE) {
            right = right.shiftRight(leftE - rightE);
        } else {
            left = left.shiftRight(rightE - leftE);
        }
        BigInteger diff = left.subtract(right);
        if (diff.abs().bitLength() > 3) {
            if (diff.signum() > 0) {
                return +1; // [f,Double.longBitsToDouble(ieeeBits+1)]
            } else {
                return -1; // [Double.longBitsToDouble(ieeeBits-1),f]
            }
        }
        return 0;
    }

    private int cmpLoop() {
        checkF();
        int fnLen = T.fnLen.getInt(0);
        int fdLen = T.fdLen.getInt(0);
        T.curpow.setLong(0, Math.max(pb.length + fdLen, qb.length + fnLen) - 1);
        T.diff_high.setInt(0, 0);
        T.diff_hi.setLong(0, 0);
        T.diff_lo.setLong(0, 0);
        check();

        while (T.curpow.getLong(0) > 0) {
            int cmp = T.one_step();
            if (cmp != 0) {
                return cmp;
            }
            check();
        }
        int diffHigh = T.diff_high.getInt(0);
        long diffHi = T.diff_hi.getLong(0);
        long diffLo = T.diff_lo.getLong(0);
        if (diffHigh < 0) {
            return -1;
        } else if (diffHigh != 0 || diffHi != 0 || diffLo != 0) {
            return 1;
        } else {
            return 0;
        }
    }

    public static BigInteger[] stringToBlocks(String s) {
        BigInteger[] r = new BigInteger[(s.length() + DIGIT_BLOCK_SIZE - 1) / DIGIT_BLOCK_SIZE];
        for (int i = 0; i < r.length; i++) {
            int endIndex = s.length() - i * DIGIT_BLOCK_SIZE;
            int beginIndex = Math.max(0, endIndex - DIGIT_BLOCK_SIZE);
            r[i] = new BigInteger(s.substring(beginIndex, endIndex));
        }
        return r;
    }

    private BigInteger prodBlocks(BigInteger[] bx, BigInteger[] by, long n) {
        BigInteger r = BigInteger.ZERO;
        long p = bx.length + by.length;
        while (--p >= n) {
            r = r.multiply(BI_DIGIT_BLOCK_RADIX);
            for (int i = 0; i < bx.length; i++) {
                long j = p - i;
                if (0 <= j && j < by.length) {
                    r = r.add(bx[i].multiply(by[(int) j]));
                }
            }
        }
        return r;
    }

    public static class Pow5 {

        public final int p;
        public BigInteger pow5;
        public int ep;
        public BigInteger mp;
        public long hp, lp;
        public int en;
        public BigInteger mn;
        public long hn, ln;

        public Pow5(int p) {
            assert p >= 0;
            this.p = p;
            pow5 = BigInteger.valueOf(5).pow(p);
            ep = pow5.bitLength();
            mp = pow5.shiftLeft(128 - ep);
            assert mp.bitLength() == 128;
            hp = mp.shiftRight(64).longValue();
            lp = mp.longValue();

            en = p == 0 ? 1 : 1 - ep;
            mn = BigInteger.ONE.shiftLeft(128 - en).divide(pow5);
            assert mn.bitLength() == 128;
            hn = mn.shiftRight(64).longValue();
            ln = mn.longValue();
        }
    }

    private void check() {
        for (int i = 0; i < s.length(); i++) {
            assert T.get_s(i) == s.charAt(i);
        }
        assert T.get_s(s.length()) == 0;
        assert T.fnLen.getInt(0) == fnb.length;
        for (int i = 0; i < fnb.length; i++) {
            BigInteger b = fnb[i];
            assert b.bitLength() < 64;
            assert T.fnBlocks.getLong(i * 8) == b.longValue();
        }
        assert T.fdLen.getInt(0) == fdb.length;
        for (int i = 0; i < fdb.length; i++) {
            BigInteger b = fdb[i];
            assert b.bitLength() < 64;
            assert T.fdBlocks.getLong(i * 8) == b.longValue();
        }

        T.p.read();
        assert T.p.beg.equals(mems.share(pBeg));
        assert T.p.end.equals(mems.share(pBeg + ps.length()));
        assert T.p.ptr.equals(mems.share(pBeg + ps.length() - T.p.minpow * DIGIT_BLOCK_SIZE));
        assert T.p.len == pb.length;
        long maxPowP = Math.min(pb.length, T.curpow.getLong(0) + 1);
        for (long pow = T.p.minpow; pow < maxPowP; pow++) {
            long v = pow < pb.length ? pb[(int) pow].longValue() : 0;
            int ind = (int) (pow - T.p.minpow);
            assert T.p.blocks.getLong(ind * 8L) == v;
        }


        T.q.read();
        assert T.q.beg.equals(mems.share(qBeg));
        assert T.q.end.equals(mems.share(qBeg + qs.length()));
        assert T.q.ptr.equals(mems.share(qBeg + qs.length() - T.q.minpow * DIGIT_BLOCK_SIZE));
        assert T.q.len == qb.length;
        long maxPowQ = Math.min(qb.length, T.curpow.getLong(0) + 1);
        for (long pow = T.q.minpow; pow < maxPowQ; pow++) {
            long v = pow < qb.length ? qb[(int) pow].longValue() : 0;
            int ind = (int) (pow - T.q.minpow);
            assert T.q.blocks.getLong(ind * 8L) == v;
        }

        long curPow = T.curpow.getLong(0);
        BigInteger expectedDiff = prodBlocks(pb, fdb, curPow).subtract(prodBlocks(qb, fnb, curPow));
        assert expectedDiff.longValue() == T.diff_lo.getLong(0);
        assert expectedDiff.shiftRight(64).longValue() == T.diff_hi.getLong(0);
        assert expectedDiff.shiftRight(128).equals(BigInteger.valueOf(T.diff_high.getInt(0)));
    }

    private void checkF() {
        long fBits = T.ieeeBits.getLong(0);
        double f = Double.longBitsToDouble(fBits);

        Rational r = Rational.valueOf(f);
        fns = r.biNumerator().toString();
        fnb = stringToBlocks(fns);
        fds = r.biDenominator().toString();
        fdb = stringToBlocks(fds);
        assert T.fnLen.getInt(0) == fnb.length;
        for (int i = 0; i < fnb.length; i++) {
            assert T.fnBlocks.getLong(i * 8) == fnb[i].longValue();
        }
        assert T.fdLen.getInt(0) == fdb.length;
        for (int i = 0; i < fdb.length; i++) {
            assert T.fdBlocks.getLong(i * 8) == fdb[i].longValue();
        }
    }
}
