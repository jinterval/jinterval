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
package org.gnu.mpfr;

import java.math.BigInteger;
import java.math.RoundingMode;
import net.java.jinterval.rational.*;

/**
 *
 */
public class ExtendedRationalContextMPFR extends RationalContextBinary {

    private final int rndMode;
    private final MPFR_T mr = new MPFR_T();

    public ExtendedRationalContextMPFR(BinaryValueSet valueSet, RoundingMode rm) {
        super(valueSet.getMathContext(rm));
        switch (rm) {
            case UP:
                rndMode = MPFR.MPFR_RNDA;
                break;
            case DOWN:
                rndMode = MPFR.MPFR_RNDZ;
                break;
            case CEILING:
                rndMode = MPFR.MPFR_RNDU;
                break;
            case FLOOR:
                rndMode = MPFR.MPFR_RNDD;
                break;
            case HALF_UP:
                rndMode = MPFR.MPFR_RNDNA;
                break;
            case HALF_EVEN:
                rndMode = MPFR.MPFR_RNDN;
                break;
            default:
                throw new UnsupportedOperationException();
        }
        MPFR.mpfr_init2(mr, valueSet.getPrecision());
    }

    @Override
    public ExtendedRational pi() {
        return rnd(MPFR.mpfr_const_pi(mr, rndMode));
    }

    @Override
    public ExtendedRational euler() {
        return rnd(MPFR.mpfr_const_euler(mr, rndMode));
    }

    @Override
    public ExtendedRational neg(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_neg(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.neg(x);
    }

    @Override
    public ExtendedRational add(ExtendedRational x, ExtendedRational y) {
        if (x.isBinary() && y.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            MPFR_T my = r2mpfr(y);
            ExtendedRational r = rnd(MPFR.mpfr_add(mr, mx, my, rndMode));
            MPFR.mpfr_clear(mx);
            MPFR.mpfr_clear(my);
            return r;
        }
        return super.add(x, y);
    }

    @Override
    public ExtendedRational sub(ExtendedRational x, ExtendedRational y) {
        if (x.isBinary() && y.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            MPFR_T my = r2mpfr(y);
            ExtendedRational r = rnd(MPFR.mpfr_sub(mr, mx, my, rndMode));
            MPFR.mpfr_clear(mx);
            MPFR.mpfr_clear(my);
            return r;
        }
        return super.sub(x, y);
    }

    @Override
    public ExtendedRational mul(ExtendedRational x, ExtendedRational y) {
        if (x.isBinary() && y.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            MPFR_T my = r2mpfr(y);
            ExtendedRational r = rnd(MPFR.mpfr_mul(mr, mx, my, rndMode));
            MPFR.mpfr_clear(mx);
            MPFR.mpfr_clear(my);
            return r;
        }
        return super.mul(x, y);
    }

    @Override
    public ExtendedRational div(ExtendedRational x, ExtendedRational y) {
        if (x.isBinary() && y.isBinary()) {
            if (y.signum() == 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            MPFR_T my = r2mpfr(y);
            ExtendedRational r = rnd(MPFR.mpfr_div(mr, mx, my, rndMode));
            MPFR.mpfr_clear(mx);
            MPFR.mpfr_clear(my);
            return r;
        }
        return super.div(x, y);
    }

    @Override
    public ExtendedRational recip(ExtendedRational x) {
        if (x.isBinary()) {
            if (x.signum() == 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_ui_div(mr, 1, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.recip(x);
    }

    @Override
    public ExtendedRational sqr(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_sqr(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.sqr(x);
    }

    @Override
    public ExtendedRational sqrt(ExtendedRational x) {
        if (x.isBinary()) {
            if (x.signum() < 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_sqrt(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.sqrt(x);
    }

    @Override
    public ExtendedRational fma(ExtendedRational x, ExtendedRational y, ExtendedRational z) {
        if (x.isBinary() && y.isBinary() && z.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            MPFR_T my = r2mpfr(y);
            MPFR_T mz = r2mpfr(z);
            ExtendedRational r = rnd(MPFR.mpfr_fma(mr, mx, my, mz, rndMode));
            MPFR.mpfr_clear(mx);
            MPFR.mpfr_clear(my);
            MPFR.mpfr_clear(mz);
            return r;
        }
        return super.fma(x, y, z);
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, BigInteger p) {
        if (p.bitLength() < 64) {
            return pown(x, p.longValue());
        }
        return super.pown(x, p);
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, long p) {
        if (x.isBinary()) {
            if (x.signum() == 0 && p < 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_pow_si(mr, mx, p, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.pown(x, p);
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, int p) {
        return pown(x, (long) p);
    }

    @Override
    public ExtendedRational pow(ExtendedRational x, ExtendedRational y) {
        if (x.isBinary() && y.isBinary()) {
            if (x.signum() < 0 || x.signum() == 0 && y.signum() <= 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            MPFR_T my = r2mpfr(y);
            ExtendedRational r = rnd(MPFR.mpfr_pow(mr, mx, my, rndMode));
            MPFR.mpfr_clear(mx);
            MPFR.mpfr_clear(my);
            return r;
        }
        return super.pow(x, y);
    }

    @Override
    public ExtendedRational exp(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_exp(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.exp(x);
    }

    @Override
    public ExtendedRational exp2(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_exp2(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.exp2(x);
    }

    @Override
    public ExtendedRational exp10(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_exp10(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.exp10(x);
    }

    @Override
    public ExtendedRational log(ExtendedRational x) {
        if (x.isBinary()) {
            if (x.signum() <= 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_log(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.log(x);
    }

    @Override
    public ExtendedRational log2(ExtendedRational x) {
        if (x.isBinary()) {
            if (x.signum() <= 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_log2(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.log2(x);
    }

    @Override
    public ExtendedRational log10(ExtendedRational x) {
        if (x.isBinary()) {
            if (x.signum() <= 0) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_log10(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.log10(x);
    }

    @Override
    public ExtendedRational sin(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_sin(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.sin(x);
    }

    @Override
    public ExtendedRational cos(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_cos(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.cos(x);
    }

    @Override
    public ExtendedRational tan(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_tan(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.tan(x);
    }

    @Override
    public ExtendedRational asin(ExtendedRational x) {
        if (x.isBinary()) {
            if (RationalOps.abs((Rational) x).gt(Rational.one())) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_asin(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.asin(x);
    }

    @Override
    public ExtendedRational acos(ExtendedRational x) {
        if (x.isBinary()) {
            if (RationalOps.abs((Rational) x).gt(Rational.one())) {
                throw new DomainException();
            }
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_acos(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.acos(x);
    }

    @Override
    public ExtendedRational atan(ExtendedRational x) {
        if (x.isBinary() || x.isPositiveInfinity() || x.isNegativeInfinity()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_atan(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.atan(x);
    }

    @Override
    public ExtendedRational atan2(ExtendedRational y, ExtendedRational x) {
        if (x.isBinary() && y.isBinary()
                || x.isBinary() && (y.isPositiveInfinity() || y.isNegativeInfinity())
                || y.isBinary() && (x.isPositiveInfinity() || x.isNegativeInfinity() && y.signum() != 0)) {
            if (x.signum() == 0 && y.signum() == 0) {
                throw new DomainException();
            }
            MPFR_T my = r2mpfr(y);
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_atan2(mr, my, mx, rndMode));
            MPFR.mpfr_clear(my);
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.atan2(y, x);
    }

    @Override
    public ExtendedRational sinh(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_sinh(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.sinh(x);
    }

    @Override
    public ExtendedRational cosh(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_cosh(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.cosh(x);
    }

    @Override
    public ExtendedRational tanh(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_tanh(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.tanh(x);
    }

    @Override
    public ExtendedRational asinh(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_asinh(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.asinh(x);
    }

    @Override
    public ExtendedRational acosh(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_acosh(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.asinh(x);
    }

    @Override
    public ExtendedRational atanh(ExtendedRational x) {
        if (x.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            ExtendedRational r = rnd(MPFR.mpfr_atanh(mr, mx, rndMode));
            MPFR.mpfr_clear(mx);
            return r;
        }
        return super.atanh(x);
    }

    @Override
    public ExtendedRational hypot(ExtendedRational x, ExtendedRational y) {
        if (x.isBinary() && y.isBinary()) {
            MPFR_T mx = r2mpfr(x);
            MPFR_T my = r2mpfr(y);
            ExtendedRational r = rnd(MPFR.mpfr_hypot(mr, mx, my, rndMode));
            MPFR.mpfr_clear(mx);
            MPFR.mpfr_clear(my);
            return r;
        }
        return super.hypot(x, y);
    }

    private static MPFR_T r2mpfr(ExtendedRational x) {
        BigInteger n = x.getNumeratorWithout2s();
        BigInteger d = x.getDenominatorWithout2s();
        if (n.signum() == 0 || d.signum() == 0) {
            MPFR_T r = new MPFR_T();
            MPFR.mpfr_init2(r, 2);
            if (d.signum() == 0) {
                MPFR.mpfr_set_inf(r, n.signum());
                assert r._mpfr_exp == Long.MIN_VALUE + 3;
            } else {
                MPFR.mpfr_set_zero(r, d.signum());
                assert r._mpfr_exp == Long.MIN_VALUE + 1;
            }
            return r;
        } else if (d.bitLength() == 1) {
            int exp2 = x.intExp2();
            BigInteger na = n.abs();
            int prec = na.bitLength();
            if (prec == 1) {
                na = na.shiftLeft(1);
                prec++;
                exp2--;
            }
            MPFR_T r = new MPFR_T();
            MPFR.mpfr_init2(r, prec);
            assert r._mpfr_prec == prec;
            r._mpfr_sign = x.signum();
            r._mpfr_exp = exp2 + prec;
            int nlimb = (prec + Long.SIZE - 1) / Long.SIZE;
            for (int k = 0; k < nlimb; k++) {
                long l = na.shiftRight(prec - (k + 1) * Long.SIZE).longValue();
                r._mpfr_d.setLong((nlimb - k - 1) * (Long.SIZE / Byte.SIZE), l);
            }
            r.write();
            return r;
        } else {
            throw new DomainException();
        }
    }

    private ExtendedRational rnd(int dir) {
        if (MPFR.mpfr_regular_p(mr)) {
            long xexp = mr._mpfr_exp;
            if (xexp > valueSet.getMaxExp() + 1) {
                return valueSet.getMathContext(rm).overflow(mr._mpfr_sign);
            }
            if (xexp < valueSet.getMinExp() - valueSet.getPrecision()) {
                return zero(valueSet, rm, mr._mpfr_sign);
            }
            ExtendedRational x = mpfr2r(mr);
            if (valueSet.contains(x)) {
                return x;
            }
            assert x instanceof Rational && x.signum() != 0;
            assert x.getDenominatorWithout2s().equals(BigInteger.ONE);
            if (x.intExp2() == valueSet.getMinExp() - valueSet.getPrecision()) {
                if ((rm == RoundingMode.HALF_EVEN || rm == RoundingMode.HALF_UP) && dir != 0) {
                    return ExtendedRationalContexts.valueOf(valueSet, dir < 0 ? RoundingMode.CEILING : RoundingMode.FLOOR).rnd(x);
                }
            } else {
                assert x.intExp2() < valueSet.getMinExp() - valueSet.getPrecision();
            }
            return ExtendedRationalContexts.valueOf(valueSet, rm).rnd(x);

        } else if (MPFR.mpfr_zero_p(mr)) {
            return Rational.zero();
        } else if (MPFR.mpfr_inf_p(mr)) {
            return mr._mpfr_sign > 0 ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.NEGATIVE_INFINITY;
        } else {
            throw new DomainException();
        }
    }

    private static ExtendedRational mpfr2r(MPFR_T x) {
        if (MPFR.mpfr_regular_p(x)) {
            long prec = x._mpfr_prec;
            long nlimb = (int) ((prec + Long.SIZE - 1) / Long.SIZE);
            long lNumBytes = nlimb * 8 + 1;
            int iNumBytes = (int) lNumBytes;
            if (iNumBytes != lNumBytes) {
                throw new ArithmeticException();
            }
            byte[] bytes = new byte[iNumBytes];
            for (int k = 0; k < nlimb; k++) {
                long l = x._mpfr_d.getLong((nlimb - 1 - k) * (Long.SIZE / Byte.SIZE));
                bytes[k * 8 + 1] = (byte) (l >> 56);
                bytes[k * 8 + 2] = (byte) (l >> 48);
                bytes[k * 8 + 3] = (byte) (l >> 40);
                bytes[k * 8 + 4] = (byte) (l >> 32);
                bytes[k * 8 + 5] = (byte) (l >> 24);
                bytes[k * 8 + 6] = (byte) (l >> 16);
                bytes[k * 8 + 7] = (byte) (l >> 8);
                bytes[k * 8 + 8] = (byte) (l >> 0);
            }
            BigInteger bi = new BigInteger(bytes);
            if (x._mpfr_sign < 0) {
                bi = bi.negate();
            }
            long lexp = x._mpfr_exp - nlimb * Long.SIZE;
            int iexp = (int) lexp;
            if (iexp != lexp) {
                throw new ArithmeticException();
            }
            return Rational.valueOf(bi, iexp);
        } else if (MPFR.mpfr_zero_p(x)) {
            return Rational.zero();
        } else if (MPFR.mpfr_inf_p(x)) {
            return x._mpfr_sign > 0 ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.NEGATIVE_INFINITY;
        } else {
            throw new DomainException();
        }
    }

    private static ExtendedRational zero(BinaryValueSet valueSet, RoundingMode roundingMode, int signum) {
        assert signum != 0;
        boolean zero;
        switch (roundingMode) {
            case UP:
                zero = false;
                break;
            case CEILING:
                zero = signum < 0;
                break;
            case FLOOR:
                zero = signum > 0;
                break;
            case UNNECESSARY:
                throw new ArithmeticException("inexact");
            default:
                zero = true;
                break;
        }
        if (zero) {
            return Rational.zero();
        }
        Rational minValue = Rational.exp2(valueSet.getMinExp() - valueSet.getPrecision() + 1);
        return signum > 0 ? minValue : RationalOps.neg(minValue);
    }
}
