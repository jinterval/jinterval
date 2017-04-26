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

import java.math.BigInteger;
import java.math.RoundingMode;

/**
 *
 */
public class RationalOps {

    private RationalOps() {
    }

    public static Rational neg(Rational x) {
        if (x instanceof BinaryDoubleImpl) {
            BinaryDoubleImpl xx = (BinaryDoubleImpl) x;
            return new BinaryDoubleImpl(-xx.value);
        } else if (x instanceof Zero) {
            return x;
        } else if (x instanceof BinaryImpl) {
            BinaryImpl xx = (BinaryImpl) x;
            return new BinaryImpl(-xx.signum(), xx.getNumeratorWithout2sAbs(), xx.intExp2());
        } else if (x instanceof RationalImpl) {
            RationalImpl xx = (RationalImpl) x;
            return new RationalImpl(xx.intExp2(), xx.getNumeratorWithout2s().negate(), xx.getDenominatorWithout2s());
        } else {
            throw new AssertionError();
        }
    }

    public static Rational add(Rational x, Rational y) {
        if (x instanceof Zero) {
            return y;
        } else if (y instanceof Zero) {
            return x;
        } else if (x instanceof Binary && y instanceof Binary) {
            BigInteger xUnscaled = x.getNumeratorWithout2s();
            int xExp = x.intExp2();
            BigInteger yUnscaled = y.getNumeratorWithout2s();
            int yExp = y.intExp2();
            int rExp;
            if (xExp < yExp) {
                rExp = xExp;
                yUnscaled = yUnscaled.shiftLeft(yExp - xExp);
            } else {
                rExp = yExp;
                xUnscaled = xUnscaled.shiftLeft(xExp - yExp);
            }
            return Rational.valueOfImpl(xUnscaled.add(yUnscaled), rExp);
        } else {
            int xe = x.intExp2();
            BigInteger xn = x.getNumeratorWithout2s();
            BigInteger xd = x.getDenominatorWithout2s();
            assert xn.signum() != 0 && xd.signum() > 0;
            int ye = y.intExp2();
            BigInteger yn = y.getNumeratorWithout2s();
            BigInteger yd = y.getDenominatorWithout2s();
            assert yn.signum() != 0 && yd.signum() > 0;
            int e;
            if (xe > ye) {
                xn = xn.shiftLeft(xe - ye);
                e = ye;
            } else {
                yn = yn.shiftLeft(ye - xe);
                e = xe;
            }
            return Rational.valueOfImpl(xn.multiply(yd).add(yn.multiply(xd)), xd.multiply(yd), e);
        }
    }

    public static Rational sub(Rational x, Rational y) {
        if (x instanceof Zero) {
            return RationalOps.neg(y);
        } else if (y instanceof Zero) {
            return x;
        } else if (x instanceof Binary && y instanceof Binary) {
            BigInteger xUnscaled = x.getNumeratorWithout2s();
            int xExp = x.intExp2();
            BigInteger yUnscaled = y.getNumeratorWithout2s();
            int yExp = y.intExp2();
            int rExp;
            if (xExp < yExp) {
                rExp = xExp;
                yUnscaled = yUnscaled.shiftLeft(yExp - xExp);
            } else {
                rExp = yExp;
                xUnscaled = xUnscaled.shiftLeft(xExp - yExp);
            }
            return Rational.valueOfImpl(xUnscaled.subtract(yUnscaled), rExp);
        } else {
            int xe = x.intExp2();
            BigInteger xn = x.getNumeratorWithout2s();
            BigInteger xd = x.getDenominatorWithout2s();
            assert xn.signum() != 0 && xd.signum() > 0;
            int ye = y.intExp2();
            BigInteger yn = y.getNumeratorWithout2s();
            BigInteger yd = y.getDenominatorWithout2s();
            assert yn.signum() != 0 && yd.signum() > 0;
            int e;
            if (xe > ye) {
                xn = xn.shiftLeft(xe - ye);
                e = ye;
            } else {
                yn = yn.shiftLeft(ye - xe);
                e = xe;
            }
            return Rational.valueOfImpl(xn.multiply(yd).subtract(yn.multiply(xd)), xd.multiply(yd), e);
        }
    }

    public static Rational mul(Rational x, Rational y) {
        if (x instanceof Zero) {
            return x;
        } else if (y instanceof Zero) {
            return y;
        } else if (x instanceof Binary && y instanceof Binary) {
            BigInteger xUnscaled = x.getNumeratorWithout2s();
            int xExp = x.intExp2();
            BigInteger yUnscaled = y.getNumeratorWithout2s();
            int yExp = y.intExp2();
            return Rational.valueOfImpl(xUnscaled.multiply(yUnscaled), xExp + yExp);
        } else {
            int xe = x.intExp2();
            BigInteger xn = x.getNumeratorWithout2s();
            BigInteger xd = x.getDenominatorWithout2s();
            assert xn.signum() != 0 && xd.signum() > 0;
            int ye = y.intExp2();
            BigInteger yn = y.getNumeratorWithout2s();
            BigInteger yd = y.getDenominatorWithout2s();
            assert yn.signum() != 0 && yd.signum() > 0;
            return Rational.valueOfImpl(xn.multiply(yn), xd.multiply(yd), xe + ye);
        }
    }

    public static Rational div(Rational x, Rational y) {
        return RationalOps.mul(x, RationalOps.recip(y));
    }

    public static Rational recip(Rational x) {
        int exp = x.intExp2();
        BigInteger p = x.getNumeratorWithout2s();
        BigInteger q = x.getDenominatorWithout2s();
        if (p.signum() == 0) {
            throw new DomainException();
        }
        assert q.signum() != 0;
        return Rational.valueOfImpl(q, p, -exp);
    }

    public static Rational sqr(Rational x) {
        return RationalOps.mul(x, x);
    }

    public static Rational sqrt(Rational x) {
        if (x.signum() < 0) {
            throw new DomainException();
        }
        if (x.signum() == 0) {
            return x;
        }
        int exp = x.intExp2();
        if ((exp & 1) != 0) {
            throw new IrrationalException();
        }
        return Rational.valueOfImpl(sqrt(x.getNumeratorWithout2s(), true), sqrt(x.getDenominatorWithout2s(), true), exp / 2);
    }

    public static Rational fma(Rational x, Rational y, Rational z) {
        return RationalOps.add(RationalOps.mul(x, y), z);
    }

    public static Rational pown(Rational x, BigInteger p) {
        Rational.checkBitLengthOverflow(p);
        if (p.bitLength() < 32) {
            return pown(x, p.intValue());
        } else if (x.signum() == 0 && p.signum() > 0) {
            return Rational.zero();
        } else if (abs(x).equals(Rational.one())) {
            return x.signum() > 0 || !p.testBit(0) ? Rational.one() : x;
        } else {
            throw new ArithmeticException("Overflow");
        }
    }

    public static Rational pown(Rational x, long p) {
        int pi = (int) p;
        if (pi == p) {
            return pown(x, pi);
        } else if (x.signum() == 0 && p > 0) {
            return Rational.zero();
        } else if (abs(x).equals(Rational.one())) {
            return x.signum() > 0 || (p & 1) == 0 ? Rational.one() : x;
        } else {
            throw new ArithmeticException("Overflow");
        }
    }

    public static Rational pown(Rational x, int p) {
        int exp = x.intExp2();
        long el = p * (long) exp;
        int ei = (int) el;
        if (el != ei || ei == Integer.MIN_VALUE) {
            throw new ArithmeticException("Overflow");
        }
        if (p > 0) {
            return Rational.valueOf(x.getNumeratorWithout2s().pow(p), x.getDenominatorWithout2s().pow(p), ei);
        } else if (p < 0) {
            if (x.signum() == 0) {
                throw new DomainException();
            }
            return Rational.valueOf(x.getDenominatorWithout2s().pow(-p), x.getNumeratorWithout2s().pow(-p), ei);
        } else {
            return Rational.one();
        }
    }

    public static Rational pow(Rational x, Rational y) {
        if (x.signum() == 0 && y.signum() > 0) {
            return Rational.zero();
        } else if (x.signum() > 0) {
            if (y.signum() == 0 || x.equals(Rational.one())) {
                return Rational.one();
            }
            int yExp = y.intExp2();
            if (yExp < -32) {
                throw new IrrationalException();
            }
            BigInteger yd = y.biDenominator();
            if (yd.bitLength() >= 32) {
                throw new IrrationalException();
            }
            int ydi = yd.intValue();
            int xExp = y.intExp2();
            BigInteger xn = x.getNumeratorWithout2s();
            BigInteger xd = x.getNumeratorWithout2s();
            if (ydi > 1) {
                if (xExp % ydi != 0) {
                    throw new IrrationalException();
                }
                xExp = xExp / ydi;
                xn = rootn(xn, ydi, true);
                xd = rootn(xd, ydi, true);
                x = Rational.valueOfImpl(xn, xd, xExp);
            }
            if (yExp > 32) {
                throw new ArithmeticException();
            }
            BigInteger yn = y.biNumerator();
            return pown(x, yn);
        } else {
            throw new DomainException();
        }
    }

    public static Rational exp(Rational x) {
        if (x.signum() == 0) {
            return Rational.one();
        }
        throw new IrrationalException();
    }

    public static Rational exp2(Rational x) {
        if (x.signum() == 0) {
            return Rational.one();
        } else if (x instanceof Binary && x.intExp2() >= 0) {
            return pown(Rational.valueOf(2), x.toBigInteger());
        } else {
            throw new IrrationalException();
        }
    }

    public static Rational exp10(Rational x) {
        if (x.signum() == 0) {
            return Rational.one();
        } else if (x instanceof Binary && x.intExp2() >= 0) {
            return pown(Rational.valueOf(10), x.toBigInteger());
        } else {
            throw new IrrationalException();
        }
    }

    public static Rational log(Rational x) {
        if (x.signum() <= 0) {
            throw new DomainException();
        } else if (x.equals(Rational.one())) {
            return Rational.zero();
        } else {
            throw new IrrationalException();
        }
    }

    public static Rational log2(Rational x) {
        if (x.signum() <= 0) {
            throw new DomainException();
        } else if (x instanceof Binary && x.getNumeratorWithout2s().bitLength() == 1) {
            return Rational.valueOf(x.intExp2());
        } else {
            throw new IrrationalException();
        }
    }

    public static Rational log10(Rational x) {
        if (x.signum() <= 0) {
            throw new DomainException();
        }
        int exp = x.intExp2();
        if (exp > 0) {
            if (x.getDenominatorWithout2s().bitLength() == 1
                    && rootn(x.getNumeratorWithout2s(), exp, true).equals(Rational.BI_FIVE)) {
                return Rational.valueOf(exp);
            }
        } else if (exp < 0) {
            if (x.getNumeratorWithout2s().bitLength() == 1
                    && rootn(x.getDenominatorWithout2s(), -exp, true).equals(Rational.BI_FIVE)) {
                return Rational.valueOf(exp);
            }
        } else if (x.equals(Rational.one())) {
            return Rational.zero();
        }
        throw new IrrationalException();
    }

    public static Rational sin(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        }
        throw new IrrationalException();
    }

    public static Rational cos(Rational x) {
        if (x.signum() == 0) {
            return Rational.one();
        }
        throw new IrrationalException();
    }

    public static Rational tan(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        }
        throw new IrrationalException();
    }

    public static Rational asin(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        } else if (abs(x).le(Rational.one())) {
            throw new IrrationalException();
        } else {
            throw new DomainException();
        }
    }

    public static Rational acos(Rational x) {
        if (x.equals(Rational.one())) {
            return Rational.zero();
        } else if (abs(x).le(Rational.one())) {
            throw new IrrationalException();
        } else {
            throw new DomainException();
        }
    }

    public static Rational atan(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        }
        throw new IrrationalException();
    }

    public static Rational atan2(Rational y, Rational x) {
        if (y.signum() == 0) {
            if (x.signum() == 0) {
                throw new DomainException();
            } else if (x.signum() > 0) {
                return Rational.zero();
            }
        }
        throw new IrrationalException();
    }

    public static Rational sinh(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        }
        throw new IrrationalException();
    }

    public static Rational cosh(Rational x) {
        if (x.signum() == 0) {
            return Rational.one();
        }
        throw new IrrationalException();
    }

    public static Rational tanh(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        }
        throw new IrrationalException();
    }

    public static Rational asinh(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        }
        throw new IrrationalException();
    }

    public static Rational acosh(Rational x) {
        int cmp = x.compareTo(Rational.one());
        if (cmp == 0) {
            return Rational.zero();
        } else if (cmp < 0) {
            throw new DomainException();
        }
        throw new IrrationalException();
    }

    public static Rational atanh(Rational x) {
        if (x.signum() == 0) {
            return Rational.zero();
        } else if (abs(x).ge(Rational.one())) {
            throw new DomainException();
        }
        throw new IrrationalException();
    }

    public static Rational sign(Rational x) {
        return Rational.valueOf(x.signum());
    }

    public static Rational roundToIntegral(Rational x, RoundingMode rm) {
        ExtendedRationalContext ctx = ExtendedRationalContexts.valueOf(BinaryValueSet.INTEGER_UNLIMITED, rm);
        return (Rational) ctx.rnd(x);
    }

    public static Rational ceil(Rational x) {
        return roundToIntegral(x, RoundingMode.CEILING);
    }

    public static Rational floor(Rational x) {
        return roundToIntegral(x, RoundingMode.FLOOR);
    }

    public static Rational trunc(Rational x) {
        return roundToIntegral(x, RoundingMode.DOWN);
    }

    public static Rational roundTiesToEven(Rational x) {
        return roundToIntegral(x, RoundingMode.HALF_EVEN);
    }

    public static Rational roundTiesToAway(Rational x) {
        return roundToIntegral(x, RoundingMode.HALF_UP);
    }

    public static Rational abs(Rational x) {
        return x.signum() >= 0 ? x : neg(x);
    }

    public static Rational min(Rational x1, Rational x2) {
        return x1.le(x2) ? x1 : x2;
    }

    public static Rational min(Rational x1, Rational x2, Rational... xn) {
        Rational r = min(x1, x2);
        for (Rational x : xn) {
            r = min(r, x);
        }
        return r;
    }

    public static Rational max(Rational x1, Rational x2) {
        return x1.ge(x2) ? x1 : x2;
    }

    public static Rational max(Rational x1, Rational x2, Rational... xn) {
        Rational r = max(x1, x2);
        for (Rational x : xn) {
            r = max(r, x);
        }
        return r;
    }

    public static Rational rootn(Rational x, BigInteger q) {
        Rational.checkBitLengthOverflow(q);
        if (q.bitLength() <= Integer.SIZE) {
            return rootn(x, q.intValueExact());
        }
        if (x.signum() == 0) {
            if (q.signum() < 0) {
                throw new DomainException();
            }
            return Rational.zero();
        }
        if (x.equals(Rational.one())) {
            return Rational.one();
        }
        if (q.testBit(0) && x.equals(Rational.valueOf(-1))) {
            return x;
        }
        throw new IrrationalException();
    }

    public static Rational rootn(Rational x, long q) {
        int qi = (int) q;
        return qi == q ? rootn(x, qi) : rootn(x, BigInteger.valueOf(q));
    }

    public static Rational rootn(Rational x, int q) {
        if (q == 0) {
            throw new IllegalArgumentException();
        }
        if (q < 0) {
            if (x.signum() == 0) {
                throw new DomainException();
            }
            if (q == Integer.MIN_VALUE) {
                if (x.equals(Rational.one())) {
                    return x;
                }
                throw new IrrationalException();
            }
            q = -q;
            x = recip(x);
        }
        if (q == 1) {
            return x;
        }
        int expX = x.intExp2();
        int exp = expX / q;
        if (q * exp != expX) {
            throw new IrrationalException();
        }
        BigInteger num = x.getNumeratorWithout2s();
        if (num.signum() < 0) {
            if ((q & 1) == 0) {
                throw new DomainException();
            }
            num = rootn(num.negate(), q, true).negate();
        } else {
            num = rootn(num, q, true);
        }
        return Rational.valueOf(num, rootn(x.getDenominatorWithout2s(), q, true), exp);
    }

    public static Rational hypot(Rational x, Rational y) {
        return RationalOps.sqrt(RationalOps.add(RationalOps.sqr(x), RationalOps.sqr(y)));
    }

    public static BigInteger piHalfFloor(Rational x) {
        return StdFuns.piHalfFloor(x);
    }

    static BigInteger sqrt(BigInteger v, boolean exact) {
        assert v.signum() > 0;
        BigInteger r = v;
        BigInteger s = BigInteger.ZERO;
        // v == s*s + r
        int qp = (v.bitLength() - 1) / 2;
        while (qp >= 0) {
            BigInteger decR = s.shiftLeft(qp + 1).add(BigInteger.ONE.shiftLeft(qp * 2));
            if (decR.compareTo(r) <= 0) {
                r = r.subtract(decR);
                s = s.add(BigInteger.ONE.shiftLeft(qp));
            }
            qp--;
        }
        if (exact && r.signum() != 0) {
            throw new IrrationalException();
        }
        return s;
    }

    static BigInteger rootn(BigInteger v, int n, boolean exact) {
        assert n >= 2;
        assert v.signum() > 0;
        BigInteger s = BigInteger.ZERO;
        for (int p = (v.bitLength() - 1) / n; p >= 0; p--) {
            BigInteger s1 = s.add(BigInteger.ONE.shiftLeft(p));
            int cmp = s1.pow(n).compareTo(v);
            if (cmp == 0) {
                return s1;
            }
            if (cmp < 0) {
                s = s1;
            }
        }
        if (exact) {
            throw new IrrationalException();
        }
        return s;
    }
}
