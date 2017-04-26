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
import com.hp.creals.CRext;
import com.hp.creals.UnaryCRFunction;
import com.hp.creals.prescaled_sin_CR;
import java.math.BigInteger;

/**
 *
 */
public class StdFuns {

    private static final double doubleLn2 = Math.log(2);
    private static final double doubleLn2Dn = doubleLn2 - 2 * Math.ulp(doubleLn2);
    private static final double doubleLn2ByLn10 = Math.log(2) / Math.log(10);
    private static final CR crLn2 = CR.valueOf(2).ln();
    private static final CR crRecipLn2 = crLn2.inverse();
    private static final CR crLn10 = CR.valueOf(10).ln();
    private static final CR crRecipLn10 = crLn10.inverse();
    private static final CR crPiHalf = CR.PI.shiftRight(1);
    private static final CR crRecipPi = CR.PI.inverse();
    private static final CR crOne = CR.valueOf(1);

    static {
        crLn2.get_appr(-60);
        crRecipLn2.get_appr(-60);
        crLn10.get_appr(-60);
        crRecipLn10.get_appr(-60);
        crPiHalf.get_appr(-60);
        crRecipPi.get_appr(-60);
        crOne.get_appr(-60);
    }

    private static CR shift(CR x, int n) {
        while (n >= Rational.EXP_LIMIT) {
            x = x.shiftRight(-Rational.EXP_LIMIT);
            n -= Rational.EXP_LIMIT;
        }
        while (n <= -Rational.EXP_LIMIT) {
            x = x.shiftLeft(-Rational.EXP_LIMIT);
            n += Rational.EXP_LIMIT;
        }
        return n == 0 ? x : x.shiftLeft(n);
    }

    /**
     * Returns integer estimation k of log2(abs(log(x))) such that
     * log2(abs(log(x))) in [k, k + 2[.
     *
     * @param x x
     * @return integer estimation k of log2(abs(log(x)))
     * @throws ArithmeticException if x is 1.
     */
    static int log2LogXinf(Rational x) {
        int e = x.intFloorLog2();
        assert -Rational.EXP_LIMIT <= e && e < Rational.EXP_LIMIT;
        long l;
        if (e >= 0) {
            if (e <= 1) {
                return RationalOps.sub(x, Rational.one()).intFloorLog2() - 1;
            }
            l = (long) (e * doubleLn2Dn);
        } else {
            if (e >= -2) {
                return RationalOps.sub(x, Rational.one()).intFloorLog2();
            }
            l = (long) ((-1 - e) * doubleLn2Dn);
        }
        assert l > 0;
        return Long.SIZE - 1 - Long.numberOfLeadingZeros(l);
    }

    private static CR logCR(Rational x) {
        CR crx = CReal.r2cr(x);
        int e = x.intFloorLog2();
        CR result;
        if (e == 0 || e == -1) {
            result = crx.ln();
        } else {
            result = crx.shiftRight(e).ln().add(crLn2.multiply(CR.valueOf(e)));
        }
        result.get_appr(log2LogXinf(x) - 2);
        return result;
    }

    public static CReal sqrt(Rational x) {
        return pow(x, Rational.exp2(-1));
    }

    public static CReal hypot(Rational x, Rational y) {
        return sqrt(RationalOps.add(RationalOps.mul(x, x), RationalOps.mul(y, y)));
    }

    public static CReal pown(Rational x, BigInteger p) {
        if (p.signum() == 0) {
            return CReal.valueOf(Rational.one());
        }
        Rational y = Rational.valueOf(p);
        if (x.signum() < 0) {
            if (p.testBit(0)) {
                return CReal.negate(pow(RationalOps.neg(x), y));
            }
            return pow(RationalOps.neg(x), y);
        }
        return pow(x, y);
    }

    private static class FunPow extends CReal.Irrational {

        private final Rational x;
        private final Rational y;

        private FunPow(Rational x, Rational y, CR logR, int e) {
            this.x = x;
            this.y = y;
            assert x.signum() > 0;
            signum = 1;
            if (e == 0) {
                m = logR.exp();
            } else {
                m = shift(logR.subtract(crLn2.multiply(CR.valueOf(e))).exp(), e);
            }
            floorLog2inf = e - 1;
//            floorLog2sup = e;
        }

        @Override
        boolean isExact(Rational r) {
            return exactValue != null ? exactValue.equals(r) : powEquals(x, y, r);
        }
    };

    public static CReal pow(Rational x, Rational y) {
        if (x.signum() < 0) {
            throw new DomainException();
        }
        if (x.signum() == 0) {
            if (y.signum() <= 0) {
                throw new DomainException();
            }
            return CReal.valueOf(Rational.zero());
        }
        int cmpX = x.compareTo(Rational.one());
        if (cmpX == 0 || y.signum() == 0) {
            return CReal.valueOf(Rational.one());
        }

        CR crx = CReal.r2cr(x);
        int eX = x.intFloorLog2();
        CR logX;
        if (eX == 0 || eX == -1) {
            logX = crx.ln();
        } else {
            logX = crx.shiftRight(eX).ln().add(crLn2.multiply(CR.valueOf(eX)));
        }
        int floorLog2LogXinf = log2LogXinf(x);
        int floorLog2LogXsup = floorLog2LogXinf + 1;
        logX.get_appr(floorLog2LogXinf - 1);
        long floorLog2Y = y.intFloorLog2();
        if (floorLog2LogXsup + floorLog2Y > Rational.EXP_LIMIT_SH) {
            return (cmpX > 0) == (y.signum() > 0) ? CReal.overflow(1) : CReal.underflow(1);
        }
        CR logR = logX.multiply(CReal.r2cr(y));
        BigInteger be = logR.multiply(crRecipLn2).get_appr(0);
        assert be.bitLength() < Integer.SIZE;
        int e = be.intValue();
        if (e > Rational.EXP_LIMIT) {
            return CReal.overflow(1);
        } else if (e < -Rational.EXP_LIMIT) {
            return CReal.underflow(1);
        } else {
            return new FunPow(x, y, logR, e);
        }
    }

    private static class FunExp extends CReal.Irrational {

        private final Rational x;

        FunExp(Rational x, CR crx, int e) {
            this.x = x;
            assert x.signum() != 0;
            signum = 1;
            if (e == 0) {
                m = crx.exp();
            } else {
                m = shift(crx.subtract(crLn2.multiply(CR.valueOf(e))).exp(), e);
            }
            floorLog2inf = e - 1;
//            floorLog2sup = e;
        }
    }

    public static CReal exp(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.one());
        }
        if (x.intFloorLog2() > Rational.EXP_LIMIT_SH) {
            return x.signum() > 0 ? CReal.overflow(1) : CReal.underflow(1);
        }
        CR crx = CReal.r2cr(x);
        BigInteger be = crx.multiply(crRecipLn2).get_appr(0);
        assert be.bitLength() < Integer.SIZE;
        int e = be.intValue();
        if (e > Rational.EXP_LIMIT) {
            return CReal.overflow(1);
        } else if (e < -Rational.EXP_LIMIT) {
            return CReal.underflow(1);
        } else {
            return new FunExp(x, crx, e);
        }
    }

    public static final CReal EULER = exp(Rational.one());

    public static CReal exp2(Rational x) {
        return pow(Rational.valueOf(2), x);
    }

    public static CReal exp10(Rational x) {
        return pow(Rational.valueOf(10), x);
    }

    static class FunLog extends CReal.Irrational {

        private final Rational x;

        FunLog(Rational x) {
            this.x = x;
            assert x.signum() > 0;
            signum = x.compareTo(Rational.one());
            assert signum != 0;
            floorLog2inf = log2LogXinf(x);
            m = logCR(x);
        }
    }

    public static CReal log(Rational x) {
        if (x.signum() <= 0) {
            throw new DomainException();
        }
        if (x.equals(Rational.one())) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunLog(x);
    }

    static class FunLog2 extends CReal.Irrational {

        private final Rational x;

        FunLog2(Rational x) {
            this.x = x;
            assert x.signum() > 0;
            signum = x.compareTo(Rational.one());
            assert signum != 0;
            assert x.getNumeratorWithout2s().bitLength() > 1 || x.getDenominatorWithout2s().bitLength() > 1;
            floorLog2inf = log2LogXinf(x);
            int e = x.intFloorLog2();
            m = crRecipLn2.multiply(logCR(RationalOps.mul(x, Rational.exp2(-e)))).add(CR.valueOf(e));
        }
    }

    public static CReal log2(Rational x) {
        if (x.signum() <= 0) {
            throw new DomainException();
        }
        if (x.getNumeratorWithout2s().bitLength() == 1 && x.getDenominatorWithout2s().bitLength() == 1) {
            return CReal.valueOf(Rational.valueOf(x.intExp2()));
        }
        return new FunLog2(x);
    }

    static class FunLog10 extends CReal.Irrational {

        private final Rational x;

        FunLog10(Rational x) {
            this.x = x;
            assert x.signum() > 0;
            signum = x.compareTo(Rational.one());
            assert signum != 0;
            m = crRecipLn10.multiply(logCR(x));
            floorLog2inf = log2LogXinf(x) - 2;
        }
    }

    public static CReal log10(Rational x) {
        if (x.signum() <= 0) {
            throw new DomainException();
        }
        int exp = x.intExp2();
        BigInteger n = x.getNumeratorWithout2s();
        BigInteger d = x.getDenominatorWithout2s();
        if (exp == 0 && n.bitLength() == 1 && d.bitLength() == 1) {
            return CReal.valueOf(Rational.valueOf(exp));
        }
        if (exp > 0 && d.bitLength() == 1 && powEquals(BigInteger.valueOf(5), exp, n, 1)) {
            return CReal.valueOf(Rational.valueOf(exp));
        }
        if (exp < 0 && n.bitLength() == 1 && powEquals(BigInteger.valueOf(5), -exp, d, 1)) {
            return CReal.valueOf(Rational.valueOf(exp));
        }
        return new FunLog10(x);
    }

    static class FunLogB extends CReal.Irrational {

        private final Rational b, x;

        FunLogB(Rational b, Rational x) {
            this.b = b;
            this.x = x;
            assert b.signum() > 0 && x.signum() > 0;
            signum = b.compareTo(Rational.one()) * x.compareTo(Rational.one());
            assert signum != 0;
            floorLog2inf = log2LogXinf(x) - log2LogXinf(b) - 2;
            m = logCR(x).divide(logCR(b));
        }

        @Override
        boolean isExact(Rational r) {
            return exactValue != null ? exactValue.equals(r) : powEquals(b, r, x);
        }
    }

    public static CReal logb(Rational b, Rational x) {
        return new FunLogB(b, x);
    }

    private static class FunSin extends CReal.Irrational {

        private final Rational x;

        FunSin(Rational x) {
            this.x = x;
            assert x.signum() != 0;
            CR crx = r2cr(x);
            BigInteger q = crRecipPi.multiply(crx).get_appr(-3);
            if (q.abs().bitLength() <= 1) { // q = -1, 0, +1 
                signum = crx.signum();
                m = new prescaled_sin_CR(crx);
                int floorLog2 = x.intFloorLog2();
                floorLog2inf = floorLog2 - 1;
//                floorLog2sup = floorLog2;
                stepHint = -floorLog2;
            } else {
                BigInteger qh;
                CR xn;
                int msd;
                switch (q.intValue() & 0x0F) {
                    case 15:
                    case 0:
                    case 1:
                        qh = q.subtract(BigInteger.valueOf(-1)).shiftRight(2).clearBit(1).clearBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = xn.signum();
                        m = new prescaled_sin_CR(xn);
                        msd = CRext.msd(xn);
                        floorLog2inf = msd - 2;
//                        floorLog2sup = msd;
                        break;
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        qh = q.subtract(BigInteger.valueOf(2)).shiftRight(2).clearBit(1).setBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = 1;
                        m = xn.cos();
                        floorLog2inf = -2;
//                        floorLog2sup = 0;
                        break;
                    case 7:
                    case 8:
                    case 9:
                        qh = q.subtract(BigInteger.valueOf(7)).shiftRight(2).setBit(1).clearBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = -xn.signum();
                        m = new prescaled_sin_CR(xn).negate();
                        msd = CRext.msd(xn);
                        floorLog2inf = msd - 2;
//                        floorLog2sup = msd;
                        break;
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                        qh = q.subtract(BigInteger.valueOf(10)).shiftRight(2).setBit(1).setBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = -1;
                        m = xn.cos().negate();
                        floorLog2inf = -2;
//                        floorLog2sup = 0;
                        break;
                    default:
                        throw new AssertionError();
                }
            }
        }
    }

    public static CReal sin(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunSin(x);
    }

    private static class FunCos extends CReal.Irrational {

        private final Rational x;

        FunCos(Rational x) {
            this.x = x;
            assert x.signum() != 0;
            CR crx = r2cr(x);
            BigInteger q = crRecipPi.multiply(crx).get_appr(-3);
            BigInteger qh;
            CR xn;
            int msd;
            switch (q.intValue() & 0x0F) {
                case 14:
                case 15:
                case 0:
                case 1:
                case 2:
                    qh = q.subtract(BigInteger.valueOf(-2)).shiftRight(2).clearBit(1).clearBit(0);
                    xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                    signum = 1;
                    m = xn.cos();
                    floorLog2inf = -2;
//                    floorLog2sup = 0;
                    break;
                case 3:
                case 4:
                case 5:
                    qh = q.subtract(BigInteger.valueOf(3)).shiftRight(2).clearBit(1).setBit(0);
                    xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                    signum = -xn.signum();
                    m = new prescaled_sin_CR(xn).negate();
                    msd = CRext.msd(xn);
                    floorLog2inf = msd - 2;
//                    floorLog2sup = msd;
                    break;
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    qh = q.subtract(BigInteger.valueOf(6)).shiftRight(2).setBit(1).clearBit(0);
                    xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                    signum = -1;
                    m = xn.cos().negate();
                    floorLog2inf = -2;
//                    floorLog2sup = 0;
                    break;
                case 11:
                case 12:
                case 13:
                    qh = q.subtract(BigInteger.valueOf(11)).shiftRight(2).setBit(1).setBit(0);
                    xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                    signum = xn.signum();
                    m = new prescaled_sin_CR(xn);
                    msd = CRext.msd(xn);
                    floorLog2inf = msd - 2;
//                    floorLog2sup = msd;
                    break;
                default:
                    throw new AssertionError();
            }
        }
    }

    public static CReal cos(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.one());
        }
        return new FunCos(x);
    }

    private static class FunTan extends CReal.Irrational {

        private final Rational x;

        FunTan(Rational x) {
            this.x = x;
            assert x.signum() != 0;
            CR crx = r2cr(x);
            BigInteger q = crRecipPi.multiply(crx).get_appr(-3);
            if (q.abs().bitLength() <= 1) { // q = -1, 0, +1 
                signum = crx.signum();
                m = new prescaled_sin_CR(crx).divide(crx.cos());
                int floorLog2 = x.intFloorLog2();
                floorLog2inf = floorLog2;
//                floorLog2sup = floorLog2 + 1;
                stepHint = -floorLog2;
            } else {
                CR sin;
                CR cos;
                BigInteger qh;
                CR xn;
                int msd;
                switch (q.intValue() & 0x07) {
                    case 7:
                    case 0:
                    case 1:
                        qh = q.subtract(BigInteger.valueOf(-1)).shiftRight(2).clearBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = xn.signum();
                        sin = new prescaled_sin_CR(xn);
                        cos = xn.cos();
                        msd = CRext.msd(xn);
                        floorLog2inf = msd - 1;
//                        floorLog2sup = msd + 2;
                        break;
                    case 2:
                        qh = q.subtract(BigInteger.valueOf(2)).shiftRight(2).clearBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = 1;
                        sin = xn.sin();
                        cos = xn.cos();
                        floorLog2inf = -3;
//                        floorLog2sup = 3;
                        break;
                    case 3:
                    case 4:
                    case 5:
                        qh = q.subtract(BigInteger.valueOf(3)).shiftRight(2).setBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = -xn.signum();
                        sin = xn.cos();
                        cos = new prescaled_sin_CR(xn).negate();
                        msd = CRext.msd(xn);
                        floorLog2inf = -msd - 2;
//                        floorLog2sup = -msd + 2;
                        break;
                    case 6:
                        qh = q.subtract(BigInteger.valueOf(6)).shiftRight(2).setBit(0);
                        xn = crx.subtract(crPiHalf.multiply(CR.valueOf(qh)));
                        signum = -1;
                        sin = xn.cos();
                        cos = xn.sin().negate();
                        floorLog2inf = -3;
//                        floorLog2sup = 3;
                        break;
                    default:
                        throw new AssertionError();
                }
                m = sin.divide(cos);
            }
        }
    }

    public static CReal tan(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunTan(x);
    }

    private static class FunAsin extends CReal.Irrational {

        private final Rational x;
        private final BigInteger kPi;
        private final boolean negate;

        FunAsin(Rational x, BigInteger kPi, boolean negate) {
            this.x = x;
            this.kPi = kPi;
            this.negate = negate;
            signum = x.signum();
            if (RationalOps.abs(x).gt(Rational.one())) {
                throw new DomainException();
            }
            if (signum == 0) {
                m = CR.valueOf(0);
            } else if (x.intFloorLog2() <= -3) {
                UnaryCRFunction sinFunction = new UnaryCRFunction() {
                    @Override
                    public CR execute(CR x) {
                        return new prescaled_sin_CR(x);
                    }
                };
                m = sinFunction.inverseMonotone(r2cr(Rational.valueOf(-0.5)), r2cr(Rational.valueOf(0.5))).execute(r2cr(x));
                int floorLog2 = x.intFloorLog2();
                floorLog2inf = floorLog2;
//                floorLog2sup = floorLog2 + 1;
                stepHint = -floorLog2;
            } else {
                m = UnaryCRFunction.asinFunction.execute(r2cr(x));
                floorLog2inf = -2;
//                floorLog2sup = 0;
            }
            if (negate) {
                m = m.negate();
                signum = -signum;
            }
            if (kPi.signum() != 0) {
                m = m.add(crPiHalf.multiply(CR.valueOf(kPi.shiftLeft(1))));
                signum = kPi.signum();
                floorLog2inf = kPi.abs().bitLength() - 2;
            }
            assert signum != 0;
        }
    }

    public static CReal asin(Rational x, BigInteger kPi, boolean negate) {
        if (x.signum() == 0 && kPi.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunAsin(x, kPi, negate);
    }

    private static class FunAcos extends CReal.Irrational {

        private final Rational x;
        private final BigInteger kPi;
        private final boolean negate;

        FunAcos(Rational x, BigInteger kPi, boolean negate) {
            this.x = x;
            this.kPi = kPi;
            this.negate = negate;
            signum = 1;
            m = UnaryCRFunction.acosFunction.execute(r2cr(x));
            if (x.eq(Rational.one())) {
                assert kPi.signum() != 0;
                m = CR.valueOf(0);
            } else if (x.gt(Rational.exp2(-1))) {
                Rational x1 = RationalOps.sub(Rational.one(), x);
                int floorLog2 = x1.intFloorLog2();
                floorLog2inf = floorLog2 / 2 - 1;
//                floorLog2sup = (floorLog2 + 1) / 2 + 1;
            } else {
                floorLog2inf = 0;
//                floorLog2sup = 1;
            }
            if (negate) {
                m = m.negate();
                signum = -signum;
            }
            if (kPi.signum() != 0) {
                assert kPi.abs().compareTo(BigInteger.ONE) > 0;
                m = m.add(crPiHalf.multiply(CR.valueOf(kPi.shiftLeft(1))));
                signum = kPi.signum();
                floorLog2inf = kPi.abs().bitLength() - 2;
            }
            assert signum != 0;
        }
    }

    public static CReal acos(Rational x, BigInteger kPi, boolean negate) {
        if (RationalOps.abs(x).gt(Rational.one())) {
            throw new DomainException();
        }
        if (x.equals(Rational.one()) && kPi.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunAcos(x, kPi, negate);
    }

    public static CReal atan(Rational x, BigInteger kPi) {
        return atan2(x, Rational.one(), kPi);
    }

    private static class FunAtan2 extends CReal.Irrational {

        private final Rational y;
        private final Rational x;
        private final BigInteger kPi;

        private FunAtan2(Rational y, Rational x, BigInteger kPi) {
            this.y = y;
            this.x = x;
            this.kPi = kPi;

            if (x.signum() > 0) {
                Rational arg = x.equals(Rational.one()) ? y : RationalOps.div(y, x);
                signum = arg.signum();
                if (signum == 0) {
                    m = CR.valueOf(0);
                } else if (arg.intFloorLog2() <= -4) {
                    UnaryCRFunction tanFunction = new UnaryCRFunction() {
                        @Override
                        public CR execute(CR x) {
                            return new prescaled_sin_CR(x).divide(x.cos());
                        }
                    };
                    Rational l = signum > 0 ? Rational.zero() : arg;
                    Rational u = signum > 0 ? arg : Rational.zero();
                    m = tanFunction.inverseMonotone(r2cr(l), r2cr(u)).execute(r2cr(arg));
                    int floorLog2 = arg.intFloorLog2();
                    floorLog2inf = floorLog2 - 1;
//                    floorLog2sup = floorLog2;
                    stepHint = -floorLog2;
                } else {
                    m = UnaryCRFunction.atanFunction.execute(r2cr(arg));
                    floorLog2inf = -4; // -3
                }
            } else if (x.signum() < 0) {
                if (y.signum() == 0) {
                    signum = 1;
                    m = CR.PI;
                    floorLog2inf = 1;
//                    floorLog2sup = 1;
                } else if (y.signum() > 0) {
                    signum = 1;
                    m = UnaryCRFunction.atanFunction.execute(r2cr(RationalOps.div(y, x))).add(CR.PI);
                    floorLog2inf = 0;
//                    floorLog2sup = 1;
                } else {
                    signum = -1;
                    m = UnaryCRFunction.atanFunction.execute(r2cr(RationalOps.div(y, x))).subtract(CR.PI);
                    floorLog2inf = 0;
//                    floorLog2sup = 1;
                }
            } else {
                if (y.signum() == 0) {
                    throw new DomainException();
                }
                signum = y.signum();
                if (signum > 0) {
                    m = CR.PI.shiftRight(1);
                    floorLog2inf = 0;
//                    floorLog2sup = 0;
                } else {
                    m = CR.PI.negate().shiftRight(1);
                    floorLog2inf = 0;
//                    floorLog2sup = 0;
                }
            }
            if (kPi.signum() != 0) {
                m = m.add(crPiHalf.multiply(CR.valueOf(kPi.shiftLeft(1))));
                signum = kPi.signum();
                floorLog2inf = kPi.abs().bitLength() - 2;
            }
            assert signum != 0;
        }
    };

    public static CReal atan2(Rational y, Rational x, BigInteger kPi) {
        if (y.signum() == 0 && x.signum() > 0 && kPi.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunAtan2(y, x, kPi);
    }

    public static CReal atan2rev1(Rational z, Rational x) {
        // x*tan(z)
        if (z.signum() == 0 || x.signum() == 0) {
            return CReal.ZERO;
        }
        return CReal.mul(x, tan(z));
    }

    public static CReal atan2rev2(Rational z, Rational y) {
        // y/tan(z)
        if (z.signum() == 0) {
            throw new DomainException();
        }
        if (y.signum() == 0) {
            return CReal.ZERO;
        }
        return CReal.div(y, tan(z));
    }

    public static final CReal PI = atan2(Rational.zero(), Rational.valueOf(-1), BigInteger.ZERO);
    public static final CReal PI_HALF = atan2(Rational.one(), Rational.zero(), BigInteger.ZERO);
    public static final CReal MINUS_PI_HALF = atan2(Rational.valueOf(-1), Rational.zero(), BigInteger.ZERO);
    public static final CReal MINUS_PI = atan2(Rational.zero(), Rational.one(), BigInteger.valueOf(-1));

    private static class FunSinh extends CReal.Irrational {

        private final Rational x;

        private FunSinh(Rational x) {
            this.x = x;
            signum = x.signum();
            assert signum != 0;
            CR crx = r2cr(x);
            BigInteger be = crx.multiply(crRecipLn2).get_appr(0);
            if (be.bitLength() >= Integer.SIZE) {
                floorLog2inf = Integer.MAX_VALUE;
//                floorLog2sup = Integer.MAX_VALUE;
            } else {
                int e = be.intValue();
                if (e == 0) {
                    m = crx.exp().subtract(crx.negate().exp()).shiftRight(1);
                    int floorLog2 = x.intFloorLog2();
                    floorLog2inf = floorLog2;
//                    floorLog2sup = floorLog2 + 2;
                    stepHint = -floorLog2;
                } else {
                    CR xn = crx.subtract(crLn2.multiply(CR.valueOf(e)));
                    xn.get_appr(Math.abs(e) - 2);
                    m = xn.exp().shiftLeft(e).subtract(xn.negate().exp().shiftRight(e)).shiftRight(1);
                    floorLog2inf = Math.abs(e) - 3;
//                    floorLog2sup = Math.abs(e);
                }
            }
        }
    };

    public static CReal sinh(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        if (x.intFloorLog2() > Rational.EXP_LIMIT_SH) {
            return CReal.overflow(x.signum());
        }
        return new FunSinh(x);
    }

    private static class FunCosh extends CReal.Irrational {

        private final Rational x;

        private FunCosh(Rational x) {
            this.x = x;
            assert x.signum() != 0;
            signum = 1;
            CR crx = r2cr(x);
            BigInteger be = crx.multiply(crRecipLn2).get_appr(0);
            if (be.bitLength() >= Integer.SIZE) {
                floorLog2inf = Integer.MAX_VALUE;
//                floorLog2sup = Integer.MAX_VALUE;
            } else {
                int e = be.intValue();
                if (e == 0) {
                    m = crx.exp().add(crx.negate().exp()).shiftRight(1);
                    floorLog2inf = 0;
//                    floorLog2sup = 2;
                } else {
                    CR xn = crx.subtract(crLn2.multiply(CR.valueOf(e)));
                    xn.get_appr(Math.abs(e) - 2);
                    m = xn.exp().shiftLeft(e).add(xn.negate().exp().shiftRight(e)).shiftRight(1);
                    floorLog2inf = Math.abs(e) - 3;
//                    floorLog2sup = Math.abs(e);
                }
            }
        }
    };

    public static CReal cosh(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.one());
        }
        if (x.intFloorLog2() >= Integer.SIZE) {
            return CReal.overflow(1);
        }
        return new FunCosh(x);
    }

    private static class FunTanh extends CReal.Irrational {

        private final Rational x;

        private FunTanh(Rational x) {
            this.x = x;
            signum = x.signum();
            assert signum != 0;
            if (x.intFloorLog2() >= Integer.SIZE) {
                m = CR.valueOf(signum);
                floorLog2inf = -1;
//                floorLog2sup = -1;
            } else {
                CR crx = r2cr(x);

                BigInteger be = crx.multiply(crRecipLn2).get_appr(0);
                int e;
                if (be.bitLength() >= Integer.SIZE) {
                    m = CR.valueOf(signum);
                    floorLog2inf = -1;
//                    floorLog2sup = -1;
                } else {
                    e = be.intValue();
                    if (e > 1) {
                        if (e > Rational.EXP_LIMIT / 2 + 10) {
                            m = CR.valueOf(1);
                            floorLog2inf = -1;
//                            floorLog2sup = -1;
                        } else {
                            CR xn = crx.subtract(crLn2.multiply(CR.valueOf(e)));
                            CR p = shift(xn.shiftLeft(1).negate().exp(), -e * 2);
                            CR n = crOne.subtract(p);
                            n.get_appr(-10);
                            CR d = crOne.add(p);
                            d.get_appr(-10);
                            m = n.divide(d);
                            floorLog2inf = -3;
//                            floorLog2sup = -1;
                        }
                    } else if (e < -1) {
                        if (e < -Rational.EXP_LIMIT / 2 - 10) {
                            m = CR.valueOf(-1);
                            floorLog2inf = -1;
//                            floorLog2sup = -1;
                        } else {
                            CR xn = crx.subtract(crLn2.multiply(CR.valueOf(e)));
                            CR p = shift(xn.shiftLeft(1).exp(), e * 2);
                            CR n = crOne.subtract(p);
                            n.get_appr(-10);
                            CR d = crOne.add(p);
                            d.get_appr(-10);
                            m = n.divide(d).negate();
                            floorLog2inf = -3;
//                            floorLog2sup = -1;
                        }
                    } else {
                        CR rP = crx.exp();
                        rP.get_appr(-10);
                        CR rM = crx.negate().exp();
                        rM.get_appr(-10);
                        CR n = rP.subtract(rM);
                        int floorLog2 = x.intFloorLog2();
                        n.get_appr(floorLog2 - 3);
                        CR d = rP.add(rM);
                        d.get_appr(-1);
                        m = n.divide(d);
                        floorLog2inf = floorLog2 - 4;
//                        floorLog2sup = floorLog2;
                        stepHint = -floorLog2;
                    }
                }
            }
        }

        @Override
        public int compare(ExtendedRational r) {
            if (ExtendedRationalOps.abs(r).ge(Rational.one())) {
                return -r.signum();
            }
            return super.compare(r);
        }
    };

    public static CReal tanh(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunTanh(x);
    }

    private static class FunAsinh extends CReal.Irrational {

        private final Rational x;

        FunAsinh(Rational x) {
            this.x = x;
            signum = x.signum();
            assert signum != 0;
            Rational xa = RationalOps.abs(x);
            CR crx = r2cr(xa);
            CR y = crx.add(CR.valueOf(1).add(crx.multiply(crx)).sqrt());
            int e = xa.intFloorLog2();
            if (e < 0) {
                m = y.ln();
                floorLog2inf = e - 2;
//                floorLog2sup = e + 2;
                if (x.signum() < 0) {
                    m = m.negate();
                }
            } else {
                m = y.shiftRight(e).ln().add(crLn2.multiply(CR.valueOf(e)));
                long l = (long) (Math.abs(e) * doubleLn2);
                int log2l = Long.SIZE - Long.numberOfLeadingZeros(l);
                floorLog2inf = log2l - 3;
//                floorLog2sup = log2l + 2;
                if (x.signum() < 0) {
                    m = m.negate();
                }
            }
        }
    }

    public static CReal asinh(Rational x) {
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunAsinh(x);
    }

    private static class FunAcosh extends CReal.Irrational {

        private final Rational x;

        FunAcosh(Rational x) {
            this.x = x;
            assert x.gt(Rational.one());
            signum = 1;
            CR crx = r2cr(x);
            CR y = crx.add(crx.multiply(crx).subtract(CR.valueOf(1)).sqrt());
            int e = x.intFloorLog2();
            if (e <= 0) {
                m = y.ln();
                Rational x1 = RationalOps.sub(x, Rational.one());
                int floorLog2 = x1.intFloorLog2();
                floorLog2inf = floorLog2 / 2 - 1;
//                floorLog2sup = (floorLog2 + 1) / 2 + 1;
            } else {
                m = y.shiftRight(e).ln().add(crLn2.multiply(CR.valueOf(e)));
                long l = (long) (Math.abs(e) * doubleLn2);
                int log2l = Long.SIZE - Long.numberOfLeadingZeros(l);
                floorLog2inf = log2l - 2;
//                floorLog2sup = log2l + 1;
            }
        }
    }

    public static CReal acosh(Rational x) {
        int cmp = x.compareTo(Rational.one());
        if (cmp < 0) {
            throw new DomainException();
        }
        if (cmp == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunAcosh(x);
    }

    private static class FunAtanh extends CReal.Irrational {

        private final Rational x;

        FunAtanh(Rational x) {
            this.x = x;
            signum = x.signum();
            assert signum != 0;
            Rational y = RationalOps.div(RationalOps.add(Rational.one(), x), RationalOps.sub(Rational.one(), x));
            CR cry = r2cr(y);
            int e = y.intFloorLog2();
            if (e == 0 || e == -1) {
                m = cry.ln().shiftRight(1);
                Rational y1 = RationalOps.sub(y, Rational.one());
                int log2y1 = y1.intFloorLog2();
                floorLog2inf = log2y1 - 2;
//                floorLog2sup = log2y1;
                stepHint = log2y1;
            } else {
                m = cry.shiftRight(e).ln().add(crLn2.multiply(CR.valueOf(e))).shiftRight(1);
                long l = (long) (Math.abs(e) * doubleLn2);
                int log2l = Long.SIZE - Long.numberOfLeadingZeros(l);
                floorLog2inf = log2l - 3;
//                floorLog2sup = log2l - 1;
            }
        }
    }

    public static CReal atanh(Rational x) {
        if (RationalOps.abs(x).ge(Rational.one())) {
            throw new DomainException();
        }
        if (x.signum() == 0) {
            return CReal.valueOf(Rational.zero());
        }
        return new FunAtanh(x);
    }

    public static CReal rootn(Rational x, BigInteger q) {
        if (q.signum() == 0) {
            throw new IllegalArgumentException();
        }
        if (x.signum() == 0) {
            if (q.signum() < 0) {
                throw new DomainException();
            }
            return CReal.ZERO;
        }
        Rational y = Rational.valueOf(BigInteger.ONE, q);
        if (x.signum() < 0) {
            if (!q.testBit(0)) {
                throw new DomainException();
            }
            return CReal.negate(pow(RationalOps.neg(x), y));
        }
        return pow(x, y);
    }

    /**
     * Checks if `x.pow(y) == r`
     */
    private static boolean powEquals(Rational x, Rational y, Rational r) {
        assert x.signum() > 0 && r.signum() > 0;
        if (Math.abs(y.intExp2()) >= Integer.SIZE) {
            return false;
        }
        BigInteger n = y.biNumerator();
        BigInteger d = y.biDenominator();
        if (n.abs().bitLength() >= Integer.SIZE || d.bitLength() >= Integer.SIZE) {
            return false;
        }
        int ni = n.intValue();
        int di = d.intValue();
        if (ni > 0) {
            return x.intExp2() * (long) ni == r.intExp2() * (long) di
                    && powEquals(x.getNumeratorWithout2s(), ni, r.getNumeratorWithout2s(), di)
                    && powEquals(x.getDenominatorWithout2s(), ni, r.getDenominatorWithout2s(), di);
        } else if (ni < 0) {
            if (ni == Integer.MIN_VALUE) {
                return false;
            }
            return x.intExp2() * (long) ni == r.intExp2() * (long) di
                    && powEquals(x.biDenominator(), -ni, r.biNumerator(), di)
                    && powEquals(x.biNumerator(), -ni, r.biDenominator(), di);
        } else {
            return r.equals(Rational.one());
        }
    }

    /**
     * Checks if `x.pow(xp) == y.pow(yp)` avoiding calculation of huge pows. x
     * and y can't have common factors.' Algorithm. Suppose that n = Floor(xp /
     * yp) Then the above condition is equivalent to x.pow(n*yp) * x.pow(xp -
     * n*yp) == y.pow(yp) As x and y don't have prime factors, this is
     * equivalent to (y / x.pow(n)).pow(yp) == x.pow(xp - n*yp)
     */
    private static boolean powEquals(BigInteger x, int xp, BigInteger y, int yp) {
        assert x.signum() > 0 && xp > 0 && y.signum() > 0 && yp > 0;
        int n = xp / yp;
        if ((x.bitLength() - 1) * n >= y.bitLength()) {
            return false;
        }
        BigInteger[] qr = y.divideAndRemainder(x.pow(n));
        BigInteger q = qr[0];
        BigInteger r = qr[1];
        return r.signum() == 0 && (xp == n * yp ? q.equals(BigInteger.ONE) : powEquals(q, yp, x, xp - n * yp));
    }

    static BigInteger piHalfFloor(Rational x) {
        if (x.signum() == 0) {
            return BigInteger.ZERO;
        }
        CR q = CReal.r2cr(x).shiftLeft(2).divide(CR.PI);
        BigInteger bq = q.BigIntegerValue();
        return (bq.testBit(0) || q.compareTo(CR.valueOf(bq)) >= 0 ? bq : bq.subtract(BigInteger.ONE)).shiftRight(1);
    }
}
