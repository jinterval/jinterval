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
public class RationalContextBinary implements ExtendedRationalContext {

    protected final BinaryValueSet valueSet;
    protected final RoundingMode rm;
    protected final BinaryValueSet.MathContext mc;

    public RationalContextBinary(BinaryValueSet.MathContext mc) {
        valueSet = mc.valueSet;
        rm = mc.roundingMode;
        this.mc = mc;
    }

    @Override
    public ExtendedRational rnd(CReal x) {
        return rnd_(this, x);
    }

    static ExtendedRational rnd_(ExtendedRationalContext rc, CReal cr) {
        ExtendedRational v = cr.peekExactValue();
        if (v != null) {
            return rc.rnd(v);
        }
        if (!(rc instanceof RationalContextBinary)) {
            throw new IrrationalException();
        }
        RationalContextBinary mc = (RationalContextBinary) rc;
        BinaryValueSet valueSet = mc.valueSet;
        RoundingMode rm = mc.rm;
        int minExp = valueSet.getMinExp();
        int maxExp = valueSet.getMaxExp();
        assert minExp <= maxExp;
        int prec = valueSet.getPrecision();
        assert prec > 1;
        long floorLog2inf = cr.getFloorLog2inf();
        if (floorLog2inf > maxExp) {
            return mc.mc.overflow(cr.signum());
        }
        long el = Math.max(minExp, floorLog2inf) - prec - CReal.EXTRA_BITS;
        int e = (int) el;
        assert e == el;
        boolean half = rm == RoundingMode.HALF_UP || rm == RoundingMode.HALF_DOWN || rm == RoundingMode.HALF_EVEN;
        BigInteger thresholdM;
        int thresholdE;
        BigInteger t = cr.get_appr(e);
        floorLog2inf = cr.getFloorLog2inf();
        BigInteger ta = t.abs();
        int bitLength = ta.bitLength();
        if (bitLength <= 1) {
            if (bitLength == 0) {
                assert e > floorLog2inf;
            } else {
                assert e >= floorLog2inf;
            }
            assert e < minExp - prec - 1;
            return mc.mc.underflow(cr.signum());
        }
        int exp = e + bitLength - 1;
        if (exp > maxExp) {
            assert exp >= floorLog2inf;
            assert bitLength >= prec + 1;
            return mc.mc.overflow(cr.signum());
        }
        assert exp >= floorLog2inf || exp == floorLog2inf - 1 && ta.bitCount() == bitLength;
        int q = Math.max(exp, minExp) - prec + 1;
        assert e < q - 1;
        if (half) {
            thresholdE = q - 1;
            thresholdM = ta.shiftRight(thresholdE - e).setBit(0);
        } else {
            thresholdE = q;
            thresholdM = ta.shiftRight(thresholdE - e);
        }
        if (t.signum() < 0) {
            thresholdM = thresholdM.negate();
        }

        int cmp = cr.compare(Rational.valueOf(thresholdM, thresholdE));
        int tsign = thresholdM.signum();
        if (cmp != 0) {
            int dir;
            switch (rm) {
                case UP:
                    if (cmp > 0) {
                        dir = tsign >= 0 ? +1 : 0;
                    } else {
                        dir = tsign <= 0 ? -1 : 0;
                    }
                    break;
                case DOWN:
                    if (cmp > 0) {
                        dir = tsign < 0 ? +1 : 0;
                    } else {
                        dir = tsign > 0 ? -1 : 0;
                    }
                    break;
                case CEILING:
                    dir = cmp > 0 ? +1 : 0;
                    break;
                case FLOOR:
                    dir = cmp < 0 ? -1 : 0;
                    break;
                case HALF_UP:
                case HALF_DOWN:
                case HALF_EVEN:
                    thresholdM = thresholdM.add(BigInteger.valueOf(cmp)).shiftRight(1);
                    if (thresholdM.abs().bitLength() > prec) {
                        assert thresholdM.abs().equals(BigInteger.ONE.shiftLeft(prec));
                        if (thresholdE == maxExp - prec) {
                            return tsign > 0 ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.NEGATIVE_INFINITY;
                        }
                        assert thresholdE < maxExp - prec;
                    }
                    return Rational.valueOf(thresholdM, thresholdE + 1);
                default:
                    throw new ArithmeticException("inexact");
            }
            BigInteger thresholdM1 = thresholdM.add(BigInteger.valueOf(dir));
            if (thresholdM1.abs().bitLength() > prec && thresholdE >= maxExp - prec + 1) {
                return tsign > 0 ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.NEGATIVE_INFINITY;
            }
            if (thresholdM1.abs().bitLength() == prec - 1 && thresholdM.abs().bitLength() == prec && thresholdE > minExp - prec + 1) {
                assert thresholdM.equals(BigInteger.valueOf(tsign).shiftLeft(prec - 1));
                assert dir == +1 || dir == -1;
                thresholdM1 = thresholdM1.shiftLeft(1).add(BigInteger.valueOf(-dir));
                thresholdE--;
            }
            return Rational.valueOf(thresholdM1, thresholdE);
        } else {
            boolean up;
            switch (rm) {
                case HALF_UP:
                    up = true;
                    break;
                case HALF_DOWN:
                    up = false;
                    break;
                case HALF_EVEN:
                    up = thresholdM.testBit(1);
                    break;
                default:
                    return Rational.valueOf(thresholdM, thresholdE);
            }
            thresholdM = thresholdM.abs().shiftRight(1);
            if (up) {
                thresholdM = thresholdM.add(BigInteger.valueOf(tsign));
            }
            if (tsign < 0) {
                thresholdM = thresholdM.negate();
            }
            return Rational.valueOf(thresholdM, thresholdE + 1);
        }
    }

    @Override
    public ExtendedRational rnd(Number x) {
        return rnd(ExtendedRational.valueOf(x));
    }

    @Override
    public ExtendedRational rnd(ExtendedRational x) {
        if (x instanceof BinaryDoubleImpl) {
            return mc.round((BinaryDoubleImpl) x);
        } else if (x instanceof BinaryImpl) {
            return mc.round((BinaryImpl) x);
        } else if (x instanceof Infinity || x instanceof Zero) {
            return x;
        } else if (x instanceof RationalImpl) {
            return mc.round((RationalImpl) x);
        } else {
            assert x.isNaN();
            return x;
        }
    }

    @Override
    public ExtendedRational pi() {
        return rnd(StdFuns.PI);
    }

    @Override
    public ExtendedRational euler() {
        return rnd(StdFuns.EULER);
    }

    @Override
    public ExtendedRational neg(ExtendedRational x) {
        return rnd(ExtendedRationalOps.neg(x));
    }

    @Override
    public ExtendedRational add(ExtendedRational x, ExtendedRational y) {
        return rnd(ExtendedRationalOps.add(x, y));
    }

    @Override
    public ExtendedRational sub(ExtendedRational x, ExtendedRational y) {
        return rnd(ExtendedRationalOps.sub(x, y));
    }

    @Override
    public ExtendedRational mul(ExtendedRational x, ExtendedRational y) {
        return rnd(ExtendedRationalOps.mul(x, y));
    }

    @Override
    public ExtendedRational div(ExtendedRational x, ExtendedRational y) {
        return rnd(ExtendedRationalOps.div(x, y));
    }

    @Override
    public ExtendedRational recip(ExtendedRational x) {
        return rnd(ExtendedRationalOps.recip(x));
    }

    @Override
    public ExtendedRational sqr(ExtendedRational x) {
        return rnd(ExtendedRationalOps.sqr(x));
    }

    @Override
    public ExtendedRational sqrt(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.sqrt((Rational) x));
        } else {
            return ExtendedRationalOps.sqrtExt(x);
        }
    }

    @Override
    public ExtendedRational fma(ExtendedRational x, ExtendedRational y, ExtendedRational z) {
        return rnd(ExtendedRationalOps.fma(x, y, z));
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, BigInteger p) {
        if (x instanceof Rational) {
            return rnd(StdFuns.pown((Rational) x, p));
        } else {
            return ExtendedRationalOps.pownExt(x, p);
        }
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, long p) {
        return pown(x, BigInteger.valueOf(p));
    }

    @Override
    public ExtendedRational pown(ExtendedRational x, int p) {
        return pown(x, BigInteger.valueOf(p));
    }

    @Override
    public ExtendedRational pow(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return rnd(StdFuns.pow((Rational) x, (Rational) y));
        } else {
            return ExtendedRationalOps.powExt(x, y);
        }
    }

    @Override
    public ExtendedRational exp(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.exp((Rational) x));
        } else {
            return ExtendedRationalOps.expExt(x);
        }
    }

    @Override
    public ExtendedRational exp2(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.exp2((Rational) x));
        } else {
            return ExtendedRationalOps.exp2Ext(x);
        }
    }

    @Override
    public ExtendedRational exp10(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.exp10((Rational) x));
        } else {
            return ExtendedRationalOps.exp10Ext(x);
        }
    }

    @Override
    public ExtendedRational log(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.log((Rational) x));
        } else {
            return ExtendedRationalOps.logExt(x);
        }
    }

    @Override
    public ExtendedRational log2(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.log2((Rational) x));
        } else {
            return ExtendedRationalOps.log2Ext(x);
        }
    }

    @Override
    public ExtendedRational log10(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.log10((Rational) x));
        } else {
            return ExtendedRationalOps.log10Ext(x);
        }
    }

    @Override
    public ExtendedRational sin(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.sin((Rational) x));
        } else {
            return ExtendedRationalOps.sinExt(x);
        }
    }

    @Override
    public ExtendedRational cos(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.cos((Rational) x));
        } else {
            return ExtendedRationalOps.cosExt(x);
        }
    }

    @Override
    public ExtendedRational tan(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.tan((Rational) x));
        } else {
            return ExtendedRationalOps.tanExt(x);
        }
    }

    @Override
    public ExtendedRational asin(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.asin((Rational) x, BigInteger.ZERO, false));
        } else {
            return ExtendedRationalOps.asinExt(x);
        }
    }

    @Override
    public ExtendedRational acos(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.acos((Rational) x, BigInteger.ZERO, false));
        } else {
            return ExtendedRationalOps.acosExt(x);
        }
    }

    @Override
    public ExtendedRational atan(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.atan((Rational) x, BigInteger.ZERO));
        } else if (x.isNegativeInfinity()) {
            return rnd(StdFuns.MINUS_PI_HALF);
        } else if (x.isPositiveInfinity()) {
            return rnd(StdFuns.PI_HALF);
        } else {
            throw new AssertionError();
        }
    }

    @Override
    public ExtendedRational atan2(ExtendedRational y, ExtendedRational x) {
        if (y instanceof Rational && x instanceof Rational) {
            return rnd(StdFuns.atan2((Rational) y, (Rational) x, BigInteger.ZERO));
        } else if (x instanceof Rational) {
            if (y instanceof Rational) {
                throw new AssertionError();
            } else if (y.isNegativeInfinity()) {
                return rnd(StdFuns.MINUS_PI_HALF);
            } else if (y.isPositiveInfinity()) {
                return rnd(StdFuns.PI_HALF);
            } else {
                return y;
            }
        } else if (x.isPositiveInfinity()) {
            if (y instanceof Rational) {
                return Rational.zero();
            } else if (y.isPositiveInfinity() || y.isNegativeInfinity()) {
                throw new DomainException();
            } else {
                return y;
            }
        } else if (x.isNegativeInfinity()) {
            if (y instanceof Rational) {
                int ysign = y.signum();
                if (ysign > 0) {
                    return rnd(StdFuns.PI);
                } else if (ysign < 0) {
                    return rnd(StdFuns.MINUS_PI);
                } else {
                    throw new DomainException();
                }
            } else if (y.isPositiveInfinity() || y.isNegativeInfinity()) {
                throw new DomainException();
            } else {
                return y;
            }
        } else {
            return x;
        }
    }

    @Override
    public ExtendedRational sinh(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.sinh((Rational) x));
        } else {
            return ExtendedRationalOps.sinhExt(x);
        }
    }

    @Override
    public ExtendedRational cosh(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.cosh((Rational) x));
        } else {
            return ExtendedRationalOps.coshExt(x);
        }
    }

    @Override
    public ExtendedRational tanh(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.tanh((Rational) x));
        } else {
            return ExtendedRationalOps.tanhExt(x);
        }
    }

    @Override
    public ExtendedRational asinh(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.asinh((Rational) x));
        } else {
            return ExtendedRationalOps.asinhExt(x);
        }
    }

    @Override
    public ExtendedRational acosh(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.acosh((Rational) x));
        } else {
            return ExtendedRationalOps.acoshExt(x);
        }
    }

    @Override
    public ExtendedRational atanh(ExtendedRational x) {
        if (x instanceof Rational) {
            return rnd(StdFuns.atanh((Rational) x));
        } else {
            return ExtendedRationalOps.atanhExt(x);
        }
    }

    @Override
    public ExtendedRational sign(ExtendedRational x) {
        return rnd(ExtendedRationalOps.sign(x));
    }

    @Override
    public ExtendedRational ceil(ExtendedRational x) {
        return rnd(ExtendedRationalOps.ceil(x));
    }

    @Override
    public ExtendedRational floor(ExtendedRational x) {
        return rnd(ExtendedRationalOps.floor(x));
    }

    @Override
    public ExtendedRational trunc(ExtendedRational x) {
        return rnd(ExtendedRationalOps.trunc(x));
    }

    @Override
    public ExtendedRational roundTiesToEven(ExtendedRational x) {
        return rnd(ExtendedRationalOps.roundTiesToEven(x));
    }

    @Override
    public ExtendedRational roundTiesToAway(ExtendedRational x) {
        return rnd(ExtendedRationalOps.roundTiesToAway(x));
    }

    @Override
    public ExtendedRational abs(ExtendedRational x) {
        return rnd(ExtendedRationalOps.abs(x));
    }

    @Override
    public ExtendedRational min(ExtendedRational x1, ExtendedRational x2) {
        return rnd(ExtendedRationalOps.min(x1, x2));
    }

    @Override
    public ExtendedRational min(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn) {
        return rnd(ExtendedRationalOps.min(x1, x2, xn));
    }

    @Override
    public ExtendedRational max(ExtendedRational x1, ExtendedRational x2) {
        return rnd(ExtendedRationalOps.max(x1, x2));
    }

    @Override
    public ExtendedRational max(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn) {
        return rnd(ExtendedRationalOps.max(x1, x2, xn));
    }

    @Override
    public ExtendedRational rootn(ExtendedRational x, BigInteger q) {
        if (x instanceof Rational) {
            return rnd(StdFuns.rootn((Rational) x, q));
        } else {
            return ExtendedRationalOps.rootnExt(x, q);
        }
    }

    @Override
    public ExtendedRational rootn(ExtendedRational x, long q) {
        return rootn(x, BigInteger.valueOf(q));
    }

    @Override
    public ExtendedRational rootn(ExtendedRational x, int q) {
        return rootn(x, BigInteger.valueOf(q));
    }

    @Override
    public ExtendedRational hypot(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return rnd(StdFuns.hypot((Rational) x, (Rational) y));
        } else {
            return ExtendedRationalOps.hypotExt(x, y);
        }
    }
}
