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

import java.io.Serializable;
import java.math.BigInteger;
import java.math.RoundingMode;

/**
 * Immutable objects which encapsulate floating-point value set.
 *
 * @author nadezhin
 */
public class BinaryValueSet implements Serializable {

    /**
     * A {@code BinaryValueSet} object whose settings have the values required
     * for "unlimited" precision arithmetic. The precision is limited only by
     * size of BigInteger. The values of the settings are:      <code>
     *  precision=Integer.MAX_VALUE
     *  minexp=0
     *  maxexp=Integer.MAX_VALUE-1
     * </code>
     */
    public static final BinaryValueSet BINARY_UNLIMITED
            = new BinaryValueSet(Rational.EXP_LIMIT, 0, Rational.EXP_LIMIT - 1);
//            new BinaryValueSet(Integer.MAX_VALUE, 0, Integer.MAX_VALUE - 1);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary16 format, 11 digits, minexp=-14 maxexp=15.
     */
    public static final BinaryValueSet BINARY16
            = new BinaryValueSet(11, -14, 15);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary32 format, 24 digits, minexp=-126, maxexp=127.
     */
    public static final BinaryValueSet BINARY32
            = new BinaryValueSet(24, -126, 127);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary64 format, 53 digits, minexp=-1022, maxexp=1023.
     */
    public static final BinaryValueSet BINARY64
            = new BinaryValueSet64();
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary128 format, 34 digits, minexp=-16382, maxexp=16383.
     */
    public static final BinaryValueSet BINARY128
            = new BinaryValueSet(113, -16382, 16383);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the x87
     * Binary80 format, 64 digits, minexp=-16382, maxexp=16383.
     */
    public static final BinaryValueSet BINARY80
            = new BinaryValueSet(64, -16382, 16383);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary256 format.
     */
    public static final BinaryValueSet BINARY256
            = new BinaryValueSet(256 - 19, -(1 << 18) + 2, (1 << 18) - 1);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary512 format.
     */
    public static final BinaryValueSet BINARY512
            = new BinaryValueSet(512 - 23, -(1 << 22) + 2, (1 << 22) - 1);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary1024 format.
     */
    public static final BinaryValueSet BINARY1024
            = new BinaryValueSet(1024 - 27, -(1 << 26) + 2, (1 << 26) - 1);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching the
     * IEEE 754R Binary2048 format.
     */
    public static final BinaryValueSet BINARY2048
            = new BinaryValueSet(2048 - 31, -(1 << 30) + 2, (1 << 30) - 1);
    /**
     * A {@code BinaryValueSet} object whose settings have the values required
     * for "unlimited" precision integer arithmetic. The precision is limited
     * only by size of BigInteger. The values of the settings are:      <code>
     *  precision=Integer.MAX_VALUE
     *  minexp=Integer.MAX_VALUE-1
     *  maxexp=Integer.MAX_VALUE-1
     * </code>
     */
    public static final BinaryValueSet INTEGER_UNLIMITED
            = new BinaryValueSet(Rational.EXP_LIMIT, Rational.EXP_LIMIT - 1, Rational.EXP_LIMIT - 1);
//            new BinaryValueSet(Integer.MAX_VALUE, Integer.MAX_VALUE - 1, Integer.MAX_VALUE - 1);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching
     * Integer8 format.
     */
    public static final BinaryValueSet INTEGER8
            = new BinaryValueSet(7, 6, 6);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching
     * Integer16 format.
     */
    public static final BinaryValueSet INTEGER16
            = new BinaryValueSet(15, 14, 14);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching
     * Integer32 format.
     */
    public static final BinaryValueSet INTEGER32
            = new BinaryValueSet(31, 30, 30);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching
     * Integer64 format.
     */
    public static final BinaryValueSet INTEGER64
            = new BinaryValueSet(63, 62, 62);
    /**
     * A {@code BinaryValueSet} object with a precision setting matching
     * Integer128 format.
     */
    public static final BinaryValueSet INTEGER128
            = new BinaryValueSet(127, 126, 126);

    /**
     *
     * @param rm
     * @return
     */
    public MathContext getMathContext(RoundingMode rm) {
        MathContext mc = mathContexts[rm.ordinal()];
        if (mc == null) {
            mathContexts[rm.ordinal()] = mc = makeMathContext(rm);
        }
        return mc;
    }

    MathContext makeMathContext(RoundingMode rm) {
        return new MathContext(this, rm);
    }

    /**
     *
     * @return
     */
    public MathContext roundCeiling() {
        return getMathContext(RoundingMode.CEILING);
    }

    /**
     *
     * @return
     */
    public MathContext roundFloor() {
        return getMathContext(RoundingMode.FLOOR);
    }

    /**
     *
     * @return
     */
    public MathContext roundNearest() {
        return getMathContext(RoundingMode.HALF_EVEN);
    }

    public boolean contains(ExtendedRational x) {
        if (!x.isFinite() || x.signum() == 0) {
            return true;
        }
        if (x.getDenominatorWithout2s().compareTo(BigInteger.ONE) != 0) {
            return false;
        }
        int floorLog2 = x.intFloorLog2();
        if (floorLog2 > maxexp) {
            return false;
        }
        if (floorLog2 < minexp) {
            floorLog2 = minexp;
        }
        return x.intExp2() >= floorLog2 - precision + 1;
    }

    public ExtendedRational ulp(ExtendedRational x) {
        if (!x.isFinite()) {
            return ExtendedRational.POSITIVE_INFINITY;
        }
        int floorLog2 = x.signum() == 0 ? minexp : x.intFloorLog2();
        if (floorLog2 > maxexp) {
            return ExtendedRational.POSITIVE_INFINITY;
        }
        if (floorLog2 < minexp) {
            floorLog2 = minexp;
        }
        return ExtendedRational.exp2(floorLog2 - precision + 1);
    }

    public ExtendedRational next(ExtendedRational x, int dir) {
        if (!contains(x) || dir == 0) {
            throw new IllegalArgumentException();
        }
        if (!x.isFinite()) {
            return (x.signum() > 0) == (dir > 0) ? x : getMaxValue(x.signum() < 0);
        }
        Rational ulp = (Rational) ulp(x);
        if ((x.signum() > 0 && dir < 0 || x.signum() < 0 && dir > 0)
                && x.getNumeratorWithout2sAbs().bitLength() == 1 && x.intFloorLog2() > minexp) {
            ulp = RationalOps.mul(ulp, Rational.exp2(-1));
        }
        if (dir < 0) {
            ulp = RationalOps.neg(ulp);
        }
        Rational n = RationalOps.add((Rational) x, ulp);
        if (n.signum() != 0 && n.intFloorLog2() > maxexp) {
            return n.signum() < 0 ? ExtendedRational.NEGATIVE_INFINITY : ExtendedRational.POSITIVE_INFINITY;
        }
        assert contains(n);
        return n;
    }

    public Rational getMaxValue() {
        return getMaxValue(false);
    }

    public Rational getMaxValue(boolean sign) {
        BigInteger q = BigInteger.ONE.shiftLeft(precision).subtract(BigInteger.ONE);
        if (sign) {
            q = q.negate();
        }
        return Rational.valueOf(q, maxexp - precision + 1);
    }
    /**
     * The number of digits to be used for an operation. Note that leading zeros
     * (in the coefficient of a number) are never significant.
     *
     * <p>
     * {@code precision} will always be positive.
     *
     * @serial
     */
    final int precision;
    /**
     * The minimal exponent of result of an operation. The finite rusult will be
     * always multiple of {@code (2 ^ (minexp - precision + 1)}.
     *
     *
     * @serial
     */
    final int minexp;
    /**
     * The exponent of limit of result of an operation. The finite rusult will
     * be always limited by {@code (2 ^ (maxexp + 1))}.
     *
     *
     * @serial
     */
    final int maxexp;
    private final MathContext[] mathContexts = new MathContext[RoundingMode.class.getEnumConstants().length];

    public BinaryValueSet(int precision, int minexp, int maxexp) {
        if (precision < 0) {
            throw new IllegalArgumentException("precision < 0");
        }
        this.precision = precision;
        this.minexp = minexp;
        this.maxexp = maxexp;
    }

    public BinaryValueSet(int precision) {
        this(precision, precision - Integer.MAX_VALUE, Integer.MAX_VALUE - 1);
    }

    public int getPrecision() {
        return precision;
    }

    public int getMinExp() {
        return minexp;
    }

    public int getMaxExp() {
        return maxexp;
    }

    /**
     * Compares this {@code BinaryValueSet} with the specified {@code Object}
     * for equality.
     *
     * @param x {@code Object} to which this {@code BinaryValueSet} is to be
     * compared.
     * @return {@code true} if and only if the specified {@code Object} is a
     * {@code BinaryValueSet} object which has exactly the same settings as this
     * object
     */
    @Override
    public boolean equals(Object x) {
        BinaryValueSet vs;
        if (!(x instanceof BinaryValueSet)) {
            return false;
        }
        vs = (BinaryValueSet) x;
        return vs.precision == this.precision && vs.minexp == this.minexp && vs.maxexp == this.maxexp;
    }

    /**
     * Returns the hash code for this {@code MathContext}.
     *
     * @return hash code for this {@code MathContext}
     */
    @Override
    public int hashCode() {
        return this.precision + this.minexp * 59 + this.maxexp * 71;
    }

    public static ExtendedRational fromBinary(int k, BigInteger bits) {
        int p;
        if (k == 16) {
            p = k - 5;
        } else if (k == 32) {
            p = k - 8;
        } else if (k == 64) {
            p = k - 11;
        } else if (k == 128) {
            p = k - 15;
        } else if (k == 256) {
            p = k - 19;
        } else if (k == 512) {
            p = k - 23;
        } else if (k == 1024) {
            p = k - 27;
        } else if (k == 2048) {
            p = k - 31;
        } else if (k == 4096) {
            p = k - 35;
        } else {
            throw new UnsupportedOperationException();
        }
        return fromBinary(k, p, bits);
    }

    /**
     *
     * @param k storage width in bits
     * @param p precision in bits
     * @param bits bits
     * @return
     */
    public static ExtendedRational fromBinary(int k, int p, BigInteger bits) {
        if (bits.signum() < 0 || bits.bitLength() > k) {
            throw new IllegalArgumentException();
        }
        assert k - p > 1 && k - p < Integer.SIZE;
        BigInteger expMask = BigInteger.ONE.shiftLeft(k - 1).subtract(BigInteger.ONE.shiftLeft(p - 1));
        BigInteger significandMask = BigInteger.ONE.shiftLeft(p - 1).subtract(BigInteger.ONE);
        BigInteger emax = BigInteger.ONE.shiftLeft(k - p - 1).subtract(BigInteger.ONE);
        boolean signField = bits.testBit(k - 1);
        BigInteger expField = bits.and(expMask).shiftRight(p - 1);
        BigInteger significandField = bits.and(significandMask);
        BigInteger exp = expField.subtract(emax);
        if (exp.compareTo(emax) > 0) {
            if (significandField.signum() == 0) {
                return signField ? ExtendedRational.NEGATIVE_INFINITY : ExtendedRational.POSITIVE_INFINITY;
            } else {
                return null; // NaN
            }
        }
        BigInteger significand;
        if (expField.signum() > 0) {
            significand = significandField.setBit(p - 1);
        } else {
            if (significandField.signum() == 0) {
                return Rational.zero();
            }
            significand = significandField;
            exp = exp.add(BigInteger.ONE);
        }
        if (exp.bitLength() > 31) {
            throw new ArithmeticException("Number format overflow");
        }
        long lexp = exp.longValue() - p + 1;
        int iexp = (int) lexp;
        if (iexp != lexp) {
            throw new ArithmeticException("Number format overflow");
        }
        if (signField) {
            significand = significand.negate();
        }
        return Rational.valueOf(significand, iexp);
    }

    public static class MathContext {

        final BinaryValueSet valueSet;
        final RoundingMode roundingMode;

        MathContext(BinaryValueSet valueSet, RoundingMode roundingMode) {
            if (roundingMode == null) {
                throw new NullPointerException("roundingMode");
            }
            this.valueSet = valueSet;
            this.roundingMode = roundingMode;
        }

        ExtendedRational round(RationalImpl v) {
            BigInteger n = v.getNumeratorWithout2s();
            BigInteger d = v.getDenominatorWithout2s();
            int signum = n.signum();
            assert signum != 0 && d.signum() > 0;
            BigInteger na = n.abs();
            long dotExp = Math.max(v.intFloorLog2(), valueSet.minexp);
            long ulpExp = dotExp - (valueSet.precision - 1);
            long lsh = v.intExp2() - ulpExp;
            int ish = (int) lsh;
            assert ish == lsh;
            if (ish > 0) {
                na = na.shiftLeft(ish);
            } else if (ish < 0) {
                d = d.shiftLeft(-ish);
            }
            BigInteger[] i = na.divideAndRemainder(d);
            BigInteger q = i[0];
            BigInteger r = i[1];
            if (r.signum() != 0) {
                boolean increment;
                int cmpFracHalf;
                switch (roundingMode) {
                    case UP:             // Away from zero
                        increment = true;
                        break;
                    case DOWN:    // Towards zero
                        increment = false;
                        break;
                    case CEILING: // Towards +infinity
                        increment = (signum > 0);
                        break;
                    case FLOOR:   // Towards -infinity
                        increment = (signum < 0);
                        break;
                    case HALF_UP:
                        // add(r) here is faster than multiply(2) or shiftLeft(1)
                        cmpFracHalf = r.add(r).abs().compareTo(d);
                        increment = cmpFracHalf >= 0;
                        break;
                    case HALF_DOWN:
                        // add(r) here is faster than multiply(2) or shiftLeft(1)
                        cmpFracHalf = r.add(r).abs().compareTo(d);
                        increment = cmpFracHalf > 0;
                        break;
                    case HALF_EVEN:
                        // add(r) here is faster than multiply(2) or shiftLeft(1)
                        cmpFracHalf = r.add(r).abs().compareTo(d);
                        increment = cmpFracHalf > 0 || cmpFracHalf == 0
                                && q.testBit(0);
                        break;
                    case UNNECESSARY:      // Rounding prohibited
                    default:
                        throw new ArithmeticException("Rounding necessary");
                }
                if (increment) {
                    q = q.add(BigInteger.ONE);
                }
            }
            if (dotExp - valueSet.precision + q.bitLength() > valueSet.maxexp) {
                return overflow(signum);
            }
            if (signum < 0) {
                q = q.negate();
            }
            return Rational.valueOf(q, (int) (dotExp - valueSet.precision + 1));
        }

        ExtendedRational round(BinaryImpl v) {
            return roundBinary(v);
        }

        ExtendedRational round(BinaryDoubleImpl v) {
            return roundBinary(v);
        }

        private ExtendedRational roundBinary(Binary v) {
            int signum = v.signum();
            assert v.isFinite();
            if (signum == 0) {
                return v;
            }
            BigInteger n = v.getNumeratorWithout2s();
            long exp = v.intExp2();
            BigInteger na = n.abs();
            long dotExp = exp + (na.bitLength() - 1);
            long maxPrec = valueSet.precision;
            if (dotExp < valueSet.minexp) {
                maxPrec = valueSet.precision - (valueSet.minexp - dotExp);
            }
            if (na.bitLength() <= maxPrec) {
                return dotExp <= valueSet.maxexp ? v : overflow(signum);
            }
            long lsh = na.bitLength() - maxPrec;
            int ish = (int) lsh;
            assert ish == lsh;
            boolean increment;
            switch (roundingMode) {
                case UP:             // Away from zero
                    increment = true;
                    break;
                case DOWN:    // Towards zero
                    increment = false;
                    break;
                case CEILING: // Towards +infinity
                    increment = (signum > 0);
                    break;
                case FLOOR:   // Towards -infinity
                    increment = (signum < 0);
                    break;
                case HALF_UP:
                    increment = na.testBit(ish - 1);
                    break;
                case HALF_DOWN:
                    increment = ish > 1 && na.testBit(ish - 1);
                    break;
                case HALF_EVEN:
                    increment = na.testBit(ish - 1) && (ish > 1 || na.testBit(ish));
                    break;
                case UNNECESSARY:      // Rounding prohibited
                default:
                    throw new ArithmeticException("Rounding necessary");
            }
            na = na.shiftRight(ish);
            if (increment) {
                na = na.add(BigInteger.ONE);
            }
            if (na.signum() == 0) {
                return Rational.zero();
            }
            exp = exp + ish;
            if (exp + (na.bitLength() - 1) > valueSet.maxexp) {
                return overflow(signum);
            }
            if (signum < 0) {
                na = na.negate();
            }
            return Binary.valueOf(na, (int) exp);
        }

        public ExtendedRational overflow(int signum) {
            boolean inf = true;
            switch (roundingMode) {
                case DOWN:    // Towards zero
                    inf = false;
                    break;
                case CEILING: // Towards +infinity
                    if (signum < 0) {
                        inf = false;
                    }
                    break;
                case FLOOR:   // Towards -infinity
                    if (signum > 0) {
                        inf = false;
                    }
                    break;
                case UNNECESSARY:      // Rounding prohibited
                    throw new ArithmeticException("Rounding necessary");
                default:
            }
            if (inf) {
                return signum > 0 ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.NEGATIVE_INFINITY;
            }
            BigInteger q = BigInteger.ONE.shiftLeft(valueSet.precision).subtract(BigInteger.ONE);
            if (signum < 0) {
                q = q.negate();
            }
            return Rational.valueOf(q, valueSet.maxexp - valueSet.precision + 1);
        }

        public ExtendedRational underflow(int signum) {
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

        /**
         * Returns the {@code BinaryValueSet} to which this MathContext rounds.
         *
         * @return a {@code BinaryValueSet} to which this MathContext rounds.
         */
        public BinaryValueSet getValueSet() {
            return valueSet;
        }

        /**
         * Returns the {@code precision} setting. This value is always
         * non-negative.
         *
         * @return an {@code int} which is the value of the {@code precision}
         * setting
         */
        public int getPrecision() {
            return valueSet.precision;
        }

        /**
         * Returns the roundingMode setting. This will be one of null null         {@link  RoundingMode#CEILING},
         * {@link  RoundingMode#DOWN},
         * {@link  RoundingMode#FLOOR},
         * {@link  RoundingMode#HALF_DOWN},
         * {@link  RoundingMode#HALF_EVEN},
         * {@link  RoundingMode#HALF_UP},
         * {@link  RoundingMode#UNNECESSARY}, or {@link  RoundingMode#UP}.
         *
         * @return a {@code RoundingMode} object which is the value of the
         * {@code roundingMode} setting
         */
        public RoundingMode getRoundingMode() {
            return roundingMode;
        }

        /**
         * Compares this {@code MathContext} with the specified {@code Object}
         * for equality.
         *
         * @param that {@code Object} to which this {@code MathContext} is to be
         * compared.
         * @return {@code true} if and only if the specified {@code Object} is a
         * {@code MathContext} object which has exactly the same settings as
         * this object
         */
        @Override
        public boolean equals(Object that) {
            return that instanceof MathContext
                    && this.getValueSet().equals(((MathContext) that).getValueSet()) && roundingMode == ((MathContext) that).roundingMode;
        }

        /**
         * Returns the hash code for this {@code MathContext}.
         *
         * @return hash code for this {@code MathContext}
         */
        @Override
        public int hashCode() {
            return getValueSet().hashCode() + roundingMode.hashCode() * 59;
        }

        /**
         * Returns the string representation of this {@code MathContext}. The
         * {@code String} returned represents the settings of the
         * {@code MathContext} object as two space-delimited words (separated by
         * a single space character, <tt>'&#92;u0020'</tt>, and with no leading
         * or trailing white space), as follows: <ol> <li> The string
         * {@code "precision="}, immediately followed by the value of the
         * precision setting as a numeric string as if generated by the
         * {@link Integer#toString(int) Integer.toString} method.
         *
         * <li> The string {@code "roundingMode="}, immediately followed by the
         * value of the {@code roundingMode} setting as a word. This word will
         * be the same as the name of the corresponding public constant in the
         * {@link RoundingMode} enum. </ol>
         * <p>
         * For example:
         * <pre>
         * precision=9 roundingMode=HALF_UP
         * </pre>
         *
         * Additional words may be appended to the result of {@code toString} in
         * the future if more properties are added to this class.
         *
         * @return a {@code String} representing the context settings
         */
        @Override
        public java.lang.String toString() {
            return "precision=" + valueSet.precision + " " + "roundingMode="
                    + roundingMode.toString();
        }
    }
}
