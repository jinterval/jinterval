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
package net.java.jinterval.rational;

import com.hp.creals.CR;
import java.math.BigInteger;
import java.math.RoundingMode;

/**
 *
 */
public abstract class CReal {

    public static final CReal NEGATIVE_INFINITY = valueOf(ExtendedRational.NEGATIVE_INFINITY);
    public static final CReal MINUS_ONE = valueOf(Rational.valueOf(-1));
    public static final CReal ZERO = valueOf(Rational.zero());
    public static final CReal ONE = valueOf(Rational.one());
    public static final CReal POSITIVE_INFINITY = valueOf(ExtendedRational.POSITIVE_INFINITY);

    static final int EXTRA_BITS = 8;

    public abstract long getFloorLog2inf();

    public abstract long getFloorLog2sup();

    public abstract BigInteger get_appr(int precision);

    public abstract int compare(ExtendedRational v);

    public abstract ExtendedRational peekExactValue();

    public int signum() {
        return compare(Rational.zero());
    }

    private static class RationalImpl extends CReal {

        private final ExtendedRational exactValue;

        RationalImpl(ExtendedRational exactValue) {
            this.exactValue = exactValue;
        }

        @Override
        public long getFloorLog2inf() {
            return exactValue.intFloorLog2();
        }

        @Override
        public long getFloorLog2sup() {
            return exactValue.intFloorLog2();
        }

        @Override
        public BigInteger get_appr(int precision) {
            if (!(exactValue instanceof Rational)) {
                throw new ArithmeticException();
            }
            Rational v = RationalOps.mul((Rational) exactValue, Rational.exp2(-precision));
            return RationalOps.roundToIntegral(v, RoundingMode.HALF_DOWN).toBigInteger();
        }

        @Override
        public int compare(ExtendedRational v) {
            return exactValue.compareTo(v);
        }

        @Override
        public ExtendedRational peekExactValue() {
            return exactValue;
        }
    }

    static CReal valueOf(ExtendedRational v) {
        return new RationalImpl(v);
    }

    private static class Overflow extends CReal {

        private final int signum;

        Overflow(int signum) {
            assert signum == -1 || signum == +1;
            this.signum = signum;
        }

        @Override
        public long getFloorLog2inf() {
            return Integer.MAX_VALUE;
        }

        @Override
        public long getFloorLog2sup() {
            throw new ArithmeticException();
        }

        @Override
        public BigInteger get_appr(int precision) {
            throw new ArithmeticException();
        }

        @Override
        public int compare(ExtendedRational r) {
            return r.isFinite() || r.signum() != signum ? signum : -signum;
        }

        @Override
        public ExtendedRational peekExactValue() {
            return null;
        }
    }

    static CReal overflow(int signum) {
        return new Overflow(signum);
    }

    private static class Underflow extends CReal {

        private final int signum;

        Underflow(int signum) {
            assert signum == -1 || signum == +1;
            this.signum = signum;
        }

        @Override
        public long getFloorLog2inf() {
            return Integer.MIN_VALUE;
        }

        @Override
        public long getFloorLog2sup() {
            throw new ArithmeticException();
        }

        @Override
        public BigInteger get_appr(int precision) {
            return BigInteger.ZERO;
        }

        @Override
        public int compare(ExtendedRational r) {
            return r.signum() == signum ? -signum : signum;
        }

        @Override
        public ExtendedRational peekExactValue() {
            return null;
        }
    }

    static CReal underflow(int signum) {
        return new Underflow(signum);
    }

    static class Irrational extends CReal {

        int signum;
        long floorLog2inf;
        Rational exactValue;
        CR m;
        int stepHint;

        boolean isExact(Rational r) {
            return r.equals(exactValue);
        }

        @Override
        public long getFloorLog2inf() {
            return floorLog2inf;
        }

        @Override
        public long getFloorLog2sup() {
            int fl = (int) floorLog2inf - 1;
            if (fl != floorLog2inf - 1) {
                throw new ArithmeticException();
            }
            BigInteger t = get_appr(fl);
            BigInteger ta = t.abs();
            int bitLength = ta.bitLength();
            assert bitLength >= 1;
            return floorLog2inf - 2 + bitLength;
        }

        @Override
        public BigInteger get_appr(int precision) {
            BigInteger t = m.get_appr(precision);
            BigInteger ta = t.abs();
            int bitLength = ta.bitLength();
            assert floorLog2inf - precision <= bitLength - 1;
            if (ta.getLowestSetBit() >= bitLength - 1) {
                if (bitLength - 2 > floorLog2inf - precision) {
                    floorLog2inf = precision + (long) (bitLength - 2);
                }
            } else {
                if (bitLength - 1 > floorLog2inf - precision) {
                    floorLog2inf = precision + (long) (bitLength - 1);
                }
            }
            return t;
        }

        @Override
        public int compare(ExtendedRational r) {
            if (exactValue != null) {
                return exactValue.compareTo(r);
            }
            if (r.signum() == 0) {
                assert signum != 0;
                return signum;
            }
            if (r.isPositiveInfinity()) {
                return -1;
            }
            if (r.isNegativeInfinity()) {
                return +1;
            }
            assert r.getDenominatorWithout2s().equals(BigInteger.ONE);
            int eStep = Math.max(r.getNumeratorWithout2s().abs().bitLength(), stepHint);
            int e = r.intFloorLog2() - eStep - EXTRA_BITS;
            BigInteger te = RationalOps.mul((Rational) r, Rational.exp2(-e)).toBigInteger();
            boolean exactTest = false;
            boolean loopOnce = false;
            for (;;) {
                BigInteger appr = m.get_appr(e);
                int cmp = appr.compareTo(te);
                if (cmp != 0) {
                    return cmp;
                }
                if (!exactTest && loopOnce) {
                    if (isExact((Rational) r)) {
                        exactValue = (Rational) r;
                        assert floorLog2inf <= exactValue.intFloorLog2();
                        floorLog2inf = exactValue.intFloorLog2();
                        return 0;
                    }
                    exactTest = true;
                }
                e -= eStep;
                te = te.shiftLeft(eStep);
                loopOnce = true;
            }
        }

        @Override
        public ExtendedRational peekExactValue() {
            ExtendedRational v = exactValue;
            if (v != null) {
                assert signum == v.signum();
                assert signum != 0;
                assert floorLog2inf == v.intFloorLog2();
            }
            return v;
        }
    }

    private static CReal recip(CReal x) {
        int signum = x.signum();
        assert signum != 0;
        ExtendedRational exact = x.peekExactValue();
        if (exact != null) {
            assert exact.isFinite();
            return valueOf(RationalOps.recip((Rational) exact));
        }
        long floorLog2sup = x.getFloorLog2sup();
        CReal.Irrational result = new CReal.Irrational();
        result.signum = signum;
        result.floorLog2inf = -floorLog2sup - 1;
        result.m = ((CReal.Irrational) x).m.inverse();
        result.stepHint = ((CReal.Irrational) x).stepHint;
        result.getFloorLog2sup();
        return result;
    }
    
    static CR r2cr(Rational x) {
        BigInteger n = x.getNumeratorWithout2s();
        BigInteger d = x.getDenominatorWithout2s();
        int e = x.intExp2();
        if (d.bitLength() == 1) {
            assert d.equals(BigInteger.ONE);
            CR r = CR.valueOf(n).shiftLeft(e);
            r.get_appr(n.bitLength() > 2 ? e : e - 1);
            return r;
        } else {
            CR crn = CR.valueOf(n);
            crn.get_appr(n.bitLength() > 2 ? 0 : -1);
            CR crd = CR.valueOf(d);
            assert d.signum() > 0 && d.bitLength() >= 2;
            crd.get_appr(0);
            CR r = crn.divide(crd).shiftLeft(e);
            r.get_appr(e + n.bitLength() - d.bitLength() - 60);
            return r;
        }
    }

    static CReal mul(Rational x, CReal y) {
        assert x.signum() != 0;
        int signumY = y.signum();
        assert signumY != 0;
        ExtendedRational exactY = y.peekExactValue();
        if (exactY != null) {
            assert exactY.isFinite();
            return valueOf(RationalOps.mul(x, (Rational) exactY));
        }
        CReal.Irrational result = new CReal.Irrational();
        result.signum = x.signum() * signumY;
        result.floorLog2inf = x.intFloorLog2() + y.getFloorLog2inf();
        result.m = r2cr(x).multiply(((CReal.Irrational) y).m);
        result.stepHint = ((CReal.Irrational) y).stepHint;
        result.getFloorLog2sup();
        return result;
    }

    static CReal div(Rational x, CReal y) {
        return mul(x, recip(y));
    }
    
    private static class Negate extends CReal {

        private final CReal x;

        Negate(CReal x) {
            this.x = x;
        }

        @Override
        public long getFloorLog2inf() {
            return x.getFloorLog2inf();
        }

        @Override
        public long getFloorLog2sup() {
            return x.getFloorLog2sup();
        }

        @Override
        public BigInteger get_appr(int precision) {
            return x.get_appr(precision).negate();
        }

        @Override
        public int compare(ExtendedRational r) {
            return -x.compare(ExtendedRationalOps.neg(r));
        }

        @Override
        public ExtendedRational peekExactValue() {
            ExtendedRational v = x.peekExactValue();
            return v != null ? ExtendedRationalOps.neg(v) : null;
        }
    }

    static CReal negate(CReal x) {
        return new Negate(x);
    }

}
