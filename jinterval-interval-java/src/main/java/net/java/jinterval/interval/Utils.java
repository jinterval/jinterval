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
package net.java.jinterval.interval;

import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.kaucher.KaucherInterval;
import net.java.jinterval.rational.*;

/**
 *
 */
public class Utils {

    public static final ClassicInterval ZERO = (ClassicInterval) Utils.set(0, 0);
    public static final ClassicInterval M1P1 = (ClassicInterval) Utils.set(-1, +1);
    public static final Rational RAT_HALF = Rational.exp2(-1);
    private static final SetInterval[] entireCache = new SetInterval[Decoration.values().length];

    static {
        for (Decoration d : Decoration.values()) {
            entireCache[d.ordinal()] = new DoubleInterval.Unbounded(Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY, d.min(Decoration.DAC));
        }
    }

    private Utils() {
    }

    public static ClassicInterval classic(Rational inf, Rational sup) {
        return classic(inf, sup, Decoration.COM);
    }

    public static ClassicInterval classic(Rational inf, Rational sup, Decoration decoration) {
        if (inf.isDouble() && sup.isDouble()) {
            return classic(inf.doubleValueExact(), sup.doubleValueExact(), decoration);
        } else {
            return new RationalInterval.Bounded((Rational) inf, (Rational) sup, decoration);
        }
    }

    public static ClassicInterval classic(double inf, double sup) {
        return classic(inf, sup, Decoration.COM);
    }

    public static ClassicInterval classic(double inf, double sup, Decoration decoration) {
        if (Double.NEGATIVE_INFINITY < inf && sup < Double.POSITIVE_INFINITY) {
            return new DoubleInterval.Bounded(inf, sup, decoration);
        } else {
            throw new DomainException();
        }
    }

    public static SetInterval set(ExtendedRational inf, ExtendedRational sup) {
        return set(inf, sup, Decoration.COM);
    }

    public static SetInterval set(ExtendedRational inf, ExtendedRational sup, Decoration decoration) {
        if (inf.isDouble() && sup.isDouble()) {
            return set(inf.doubleValueExact(), sup.doubleValueExact(), decoration);
        } else if (inf instanceof Rational && sup instanceof Rational) {
            return new RationalInterval.Bounded((Rational) inf, (Rational) sup, decoration);
        } else {
            return new RationalInterval.Unbounded(inf, sup, decoration.min(Decoration.DAC));
        }
    }

    public static SetInterval set(double inf, double sup) {
        return set(inf, sup, Decoration.COM);
    }

    public static SetInterval set(double inf, double sup, Decoration decoration) {
        if (Double.NEGATIVE_INFINITY < inf && sup < Double.POSITIVE_INFINITY) {
            return new DoubleInterval.Bounded(inf, sup, decoration);
        } else {
            return new DoubleInterval.Unbounded(inf, sup, decoration.min(Decoration.DAC));
        }
    }

    public static boolean isNonemptyInfSupDouble(Interval x) {
        return x instanceof DoubleInterval;
    }

    public static SetInterval entire(Decoration decoration) {
        return entireCache[decoration.ordinal()];
    }

    public static KaucherInterval kaucher(Rational inf, Rational sup) {
        return kaucher(inf, sup, Decoration.COM);
    }

    public static KaucherInterval kaucher(Rational inf, Rational sup, Decoration decoration) {
        if (inf.isDouble() && sup.isDouble()) {
            return kaucher(inf.doubleValueExact(), sup.doubleValueExact(), decoration);
        } else if (inf instanceof Rational && sup instanceof Rational) {
            if (inf.le(sup)) {
                return new RationalInterval.Bounded((Rational) inf, (Rational) sup, decoration);
            } else {
                return new RationalInterval.Dual((Rational) inf, (Rational) sup, decoration.min(Decoration.DAC));
            }
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval kaucher(double inf, double sup) {
        return kaucher(inf, sup, Decoration.COM);
    }

    public static KaucherInterval kaucher(double inf, double sup, Decoration decoration) {
        if (Double.NEGATIVE_INFINITY < inf && sup < Double.POSITIVE_INFINITY) {
            if (inf <= sup) {
                return new DoubleInterval.Bounded(inf, sup, decoration);
            } else {
                return new DoubleInterval.Dual(inf, sup, decoration.min(Decoration.DAC));
            }
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static double nextDn(double x) {
        return -Math.nextUp(-x);
    }

    public static double nextUp(double x) {
        return Math.nextUp(x);
    }

    /**
     * Add doubles rounding to floor.
     *
     * @param x first operand
     * @param y second operand
     * @return sum of arguments rounded to floor, NaN if arguments are
     * infinities of opposite signs or any of them is NaN
     */
    public static double addDn(double x, double y) {
        double r = x + y;
        return r - x > y || r - y > x ? nextDn(r) : r;
    }

    /**
     * Add doubles rounding to ceiling.
     *
     * @param x first operand
     * @param y second operand
     * @return sum of arguments rounded to ceiling, NaN if arguments are
     * infinities of opposite signs or any of them is NaN
     */
    public static double addUp(double x, double y) {
        double r = x + y;
        return r - x < y || r - y < x ? nextUp(r) : r;
    }

    /**
     * Subtract doubles rounding to floor.
     *
     * @param x first operand
     * @param y second operand
     * @return difference of arguments rounded to floor, NaN if arguments are
     * infinities of same sign or any of them is NaN
     */
    public static double subDn(double x, double y) {
        double r = x - y;
        return x - r < y || r + y > x ? nextDn(r) : r;
    }

    /**
     * Subtract doubles rounding to ceiling.
     *
     * @param x first operand
     * @param y second operand
     * @return difference of arguments rounded to floor, NaN if arguments are
     * infinities of same sign or any of them is NaN
     */
    public static double subUp(double x, double y) {
        double r = x - y;
        return x - r > y || r + y < x ? nextUp(r) : r;
    }

    private static final ExtendedRationalContext floor64 = ExtendedRationalContexts.mkFloor(BinaryValueSet.BINARY64);

    public static double mulDn(double x, double y) {
        long xbits = Double.doubleToRawLongBits(x);
        long ybits = Double.doubleToRawLongBits(y);
        int xexp = (int) (xbits >>> 52);
        int yexp = (int) (ybits >>> 52);
        double z = x * y;
        if (xexp != 0 && xexp < 0x7ff && yexp != 0 && yexp < 0x7ff) {
            long zbits = Double.doubleToRawLongBits(z);
            int zexp = (int) (zbits >>> 52);
            if (zexp != 0 && zexp < 0x7ff) {
                long xsig = (1L << 52) | (xbits & ((1L << 52) - 1));
                long ysig = (1L << 52) | (ybits & ((1L << 52) - 1));
                long prod = xsig * ysig;
                int dexp = zexp - xexp - yexp;
                if (dexp == -1023) {
                    // drop 52 bits
                    prod = prod & ((1L << 53) - 1);
                    if (prod > (1L << 51) && (prod < (2L << 51))
                            || prod >= (3L << 51)) {
                        z = nextDn(z);
                    }
                } else {
                    assert dexp == -1022;
                    // drop 53 bits
                    prod = prod & ((1L << 54) - 1);
                    if (prod > (1L << 52) && prod < (2L << 52)
                            || prod >= (3L << 52)) {
                        z = nextDn(z);
                    }
                }
                return z;
            }
        } else if (x == 0 || y == 0) {
            return z;
        }
        return floor64.mul(ExtendedRational.valueOf(x), ExtendedRational.valueOf(y)).doubleValue();
    }

    private static final ExtendedRationalContext ceil64 = ExtendedRationalContexts.mkCeiling(BinaryValueSet.BINARY64);

    public static double mulUp(double x, double y) {
        long xbits = Double.doubleToRawLongBits(x);
        long ybits = Double.doubleToRawLongBits(y);
        int xexp = (int) (xbits >>> 52);
        int yexp = (int) (ybits >>> 52);
        double z = x * y;
        if (xexp != 0 && xexp < 0x7ff && yexp != 0 && yexp < 0x7ff) {
            long zbits = Double.doubleToRawLongBits(z);
            int zexp = (int) (zbits >>> 52);
            if (zexp != 0 && zexp < 0x7ff) {
                long xsig = (1L << 52) | (xbits & ((1L << 52) - 1));
                long ysig = (1L << 52) | (ybits & ((1L << 52) - 1));
                long prod = xsig * ysig;
                int dexp = zexp - xexp - yexp;
                if (dexp == -1023) {
                    // drop 52 bits
                    prod = prod & ((1L << 53) - 1);
                    if (prod > 0 && prod <= (1L << 51)
                            || prod > (2L << 51) && prod < (3L << 51)) {
                        z = nextUp(z);
                    }
                } else {
                    assert dexp == -1022;
                    // drop 53 bits
                    prod = prod & ((1L << 54) - 1);
                    if (prod > 0 && prod <= (1L << 52)
                            || prod > (2L << 52) && prod < (3L << 52)) {
                        z = nextUp(z);
                    }
                }
                return z;
            }
        } else if (x == 0 || y == 0) {
            return z;
        }
        return ceil64.mul(ExtendedRational.valueOf(x), ExtendedRational.valueOf(y)).doubleValue();
    }

    public static double divDn(double x, double y) {
        if (x >= 0 && y > 0) {
            double r = x / y;
            return x < Utils.mulUp(y, r) ? nextDn(r) : r;
        }
        return floor64.div(ExtendedRational.valueOf(x), ExtendedRational.valueOf(y)).doubleValue();
    }

    public static double divUp(double x, double y) {
        if (x >= 0 && y > 0) {
            double r = x / y;
            return x > Utils.mulDn(y, r) ? nextUp(r) : r;
        }
        return ceil64.div(ExtendedRational.valueOf(x), ExtendedRational.valueOf(y)).doubleValue();
    }

    public static double sqrtDn(double x) {
        double r = Math.sqrt(x);
        return x < Utils.mulUp(r, r) ? nextDn(r) : r;
    }

    public static double sqrtUp(double x) {
        double r = Math.sqrt(x);
        return x > Utils.mulDn(r, r) ? nextUp(r) : r;
    }

    public static double powDn(double x, double y) {
        if (x > 0) {
            double r = nextDn(nextDn(Math.pow(x, y)));
            if (x >= 1 && y >= 0 || x <= 1 && y <= 0) {
                return Math.max(1, r);
            } else {
                return Math.max(0, r);
            }
        } else {
            return floor64.pow(ExtendedRational.valueOf(x), ExtendedRational.valueOf(y)).doubleValue();
        }
    }

    public static double powUp(double x, double y) {
        if (x > 0) {
            double r = nextUp(nextUp(Math.pow(x, y)));
            if (x >= 1 && y <= 0 || x <= 1 && y >= 0) {
                return Math.min(1, r);
            } else {
                return r;
            }
        } else {
            return ceil64.pow(ExtendedRational.valueOf(x), ExtendedRational.valueOf(y)).doubleValue();
        }
    }

    public static double pownDn(double x, int p) {
        if (x > 0) {
            switch (p) {
                case 0:
                    return 1;
                case 1:
                    return x;
                case 2:
                    return Utils.mulDn(x, x);
                case 3:
                    return Utils.mulDn(x, Utils.mulDn(x, x));
                case 4:
                    double x2 = Utils.mulDn(x, x);
                    return Utils.mulDn(x2, x2);
                case 5:
                    x2 = Utils.mulDn(x, x);
                    return Utils.mulDn(x, Utils.mulDn(x2, x2));
                case 6:
                    x2 = Utils.mulDn(x, x);
                    return Utils.mulDn(x2, Utils.mulDn(x2, x2));
                case 7:
                    x2 = Utils.mulDn(x, x);
                    double x4 = Utils.mulDn(x2, x2);
                    return Utils.mulDn(x, Utils.mulDn(x2, x4));
                case 8:
                    x2 = Utils.mulDn(x, x);
                    x4 = Utils.mulDn(x2, x2);
                    return Utils.mulDn(x4, x4);
                case 9:
                    x2 = Utils.mulDn(x, x);
                    x4 = Utils.mulDn(x2, x2);
                    return Utils.mulDn(x, Utils.mulDn(x4, x4));
                case 10:
                    x2 = Utils.mulDn(x, x);
                    x4 = Utils.mulDn(x2, x2);
                    return Utils.mulDn(x2, Utils.mulDn(x4, x4));
                default:
                    if (p < 0 && p > -10) {
                        return Utils.divDn(1, pownUp(x, -p));
                    }
                    return Utils.powDn(x, (double) p);
            }
        } else if (x == 0 && p > 0) {
            return 0;
        } else {
            return floor64.pown(ExtendedRational.valueOf(x), p).doubleValue();
        }

    }

    public static double pownUp(double x, int p) {
        if (x > 0) {
            switch (p) {
                case 0:
                    return 1;
                case 1:
                    return x;
                case 2:
                    return Utils.mulUp(x, x);
                case 3:
                    return Utils.mulUp(x, Utils.mulUp(x, x));
                case 4:
                    double x2 = Utils.mulUp(x, x);
                    return Utils.mulUp(x2, x2);
                case 5:
                    x2 = Utils.mulUp(x, x);
                    return Utils.mulUp(x, Utils.mulUp(x2, x2));
                case 6:
                    x2 = Utils.mulUp(x, x);
                    return Utils.mulUp(x2, Utils.mulUp(x2, x2));
                case 7:
                    x2 = Utils.mulUp(x, x);
                    double x4 = Utils.mulUp(x2, x2);
                    return Utils.mulUp(x, Utils.mulUp(x2, x4));
                case 8:
                    x2 = Utils.mulUp(x, x);
                    x4 = Utils.mulUp(x2, x2);
                    return Utils.mulUp(x4, x4);
                case 9:
                    x2 = Utils.mulUp(x, x);
                    x4 = Utils.mulUp(x2, x2);
                    return Utils.mulUp(x, Utils.mulUp(x4, x4));
                case 10:
                    x2 = Utils.mulUp(x, x);
                    x4 = Utils.mulUp(x2, x2);
                    return Utils.mulUp(x2, Utils.mulUp(x4, x4));
                default:
                    if (p < 0 && p > -10) {
                        return Utils.divUp(1, pownDn(x, -p));
                    }
                    return Utils.powUp(x, (double) p);
            }
        } else if (x == 0 && p > 0) {
            return 0;
        } else {
            return ceil64.pown(ExtendedRational.valueOf(x), p).doubleValue();
        }
    }
}
