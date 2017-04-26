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

import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.math.RoundingMode;
import java.util.IdentityHashMap;

/**
 * @author nadezhin Rational number is 2^exp * P/Q
 */
public abstract class ExtendedRational extends Number implements Comparable<ExtendedRational> {

    public static final ExtendedRational NEGATIVE_INFINITY = NegativeInfinity.INSTANCE;
    public static final ExtendedRational POSITIVE_INFINITY = PositiveInfinity.INSTANCE;
    static final IdentityHashMap<Class<? extends Number>, NumberConvertor> numberConvertors = new IdentityHashMap<Class<? extends Number>, NumberConvertor>();

    static abstract class NumberConvertor {

        abstract Rational rationalValue(Number v);

        ExtendedRational extendedRationalValue(Number v) {
            return rationalValue(v);
        }
    }

    static {
        numberConvertors.put(Byte.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return Rational.valueOf((Byte) v);
            }
        });
        numberConvertors.put(Short.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return Rational.valueOf((Short) v);
            }
        });
        numberConvertors.put(Integer.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return Rational.valueOf((Integer) v);
            }
        });
        numberConvertors.put(Long.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return Rational.valueOf((Long) v);
            }
        });
        numberConvertors.put(Float.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return Rational.valueOf((Float) v);
            }

            @Override
            public ExtendedRational extendedRationalValue(Number v) {
                return ExtendedRational.valueOf((Float) v);
            }
        });
        numberConvertors.put(Double.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return Rational.valueOf((Double) v);
            }

            @Override
            public ExtendedRational extendedRationalValue(Number v) {
                return ExtendedRational.valueOf((Double) v);
            }
        });
        numberConvertors.put(BigInteger.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return Rational.valueOf((BigInteger) v);
            }
        });
        numberConvertors.put(BigDecimal.class, new NumberConvertor() {
            public Rational rationalValue(Number v) {
                return valueOf((BigDecimal) v);
            }
        });
    }

    public static ExtendedRational valueOf(Number v) {
        if (v instanceof ExtendedRational) {
            return (ExtendedRational) v;
        }
        NumberConvertor numberConvertor = numberConvertors.get(v.getClass());
        if (numberConvertor == null) {
            throw new UnsupportedOperationException();
        }
        return numberConvertor.extendedRationalValue(v);
    }

    public static Rational valueOf(Byte v) {
        return Rational.valueOf(v);
    }

    public static Rational valueOf(Short v) {
        return Rational.valueOf(v);
    }

    public static Rational valueOf(Integer v) {
        return Rational.valueOf(v);
    }

    public static Rational valueOf(Long v) {
        return Rational.valueOf(v);
    }

    public static ExtendedRational valueOf(Float v) {
        return ExtendedRational.valueOf(v.doubleValue());
    }

    public static ExtendedRational valueOf(Double v) {
        return ExtendedRational.valueOf(v.doubleValue());
    }

    public static Rational valueOf(int v) {
        return Rational.valueOf(v);
    }

    public static Rational valueOf(long v) {
        return Rational.valueOf(v);
    }

    public static ExtendedRational valueOf(double v) {
        if (v == Double.POSITIVE_INFINITY) {
            return POSITIVE_INFINITY;
        } else if (v == Double.NEGATIVE_INFINITY) {
            return NEGATIVE_INFINITY;
        } else {
            return Rational.valueOf(v);
        }
    }

    /**
     * Returns rational <code>2^exp</code>
     *
     * @param exp
     */
    public static Rational exp2(int exp) {
        return Rational.exp2(exp);
    }

    public static Rational zero() {
        return Rational.zero();
    }

    public static Rational one() {
        return Rational.one();
    }

    public static Rational valueOf(BigInteger v) {
        return Rational.valueOf(v);
    }

    public static Rational valueOf(BigInteger unscaledValue, int exp) {
        return Rational.valueOf(unscaledValue, exp);
    }

    public static Rational valueOf(BigDecimal v) {
        return Rational.valueOf(v);
    }

    public static ExtendedRational valueOf(long numerator, long denominator) {
        return ExtendedRational.valueOf(BigInteger.valueOf(numerator), BigInteger.valueOf(denominator));
    }

    public static ExtendedRational valueOf(BigInteger numerator, BigInteger denominator) {
        return ExtendedRational.valueOf(numerator, denominator, 0);
    }

    public static ExtendedRational valueOf(BigInteger numerator, BigInteger denominator, int exp) {
        if (denominator.signum() != 0) {
            return Rational.valueOf(numerator, denominator, exp);
        } else {
            int nsig = numerator.signum();
            if (nsig == 0) {
                throw new DomainException();
            }
            return nsig > 0 ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.NEGATIVE_INFINITY;
        }
    }

    public static ExtendedRational valueOf(String str) {
        String s = str.trim();
        if (s.isEmpty()) {
            throw new NumberFormatException();
        }
        boolean sign;
        switch (s.charAt(0)) {
            case '-':
                s = s.substring(1);
                sign = true;
                break;
            case '+':
                s = s.substring(1);
                sign = false;
                break;
            default:
                sign = false;
        }
        if (s.isEmpty()) {
            throw new NumberFormatException();
        }
        if (s.charAt(0) == '+' || s.charAt(0) == '-') {
            throw new NumberFormatException();
        }
        if (!s.isEmpty() && Character.toUpperCase(s.charAt(0)) == 'I') {
            if (s.equalsIgnoreCase("Inf") || s.equalsIgnoreCase("Infinity")) {
                return sign ? ExtendedRational.NEGATIVE_INFINITY : ExtendedRational.POSITIVE_INFINITY;
            }
        }
        Rational r;
        if (s.length() > 2 && s.charAt(0) == '0' && Character.toUpperCase(s.charAt(1)) == 'X') {
            s = s.substring(2);
            int exp2 = 0;
            int indexP = s.indexOf('p');
            if (indexP < 0) {
                indexP = s.indexOf('P');
            }
            if (indexP >= 0) {
                exp2 = Integer.parseInt(s.substring(indexP + 1));
                s = s.substring(0, indexP);
            } else {
                throw new NumberFormatException();
            }
            int indexDot = s.indexOf(".");
            if (indexDot >= 0) {
                long e = exp2 + 4 * (indexDot + 1 - (long) s.length());
                if (e != (int) e) {
                    throw new ArithmeticException();
                }
                r = Rational.valueOf(new BigInteger(s.substring(0, indexDot) + s.substring(indexDot + 1), 16), (int) e);
            } else {
                r = Rational.valueOf(new BigInteger(s, 16), exp2);
            }
        } else {
            int indexS = s.indexOf('/');
            if (indexS >= 0) {
                String ns = s.substring(0, indexS);
                String ds = s.substring(indexS + 1);
                if (ds.isEmpty() || ds.charAt(0) == '+' || ds.charAt(0) == '-') {
                    throw new NumberFormatException("Signed denominator in ExctendedRational string");
                }
                BigInteger n = new BigInteger(ns);
                BigInteger d = new BigInteger(s.substring(indexS + 1));
                if (d.signum() == 0) {
                    throw new NumberFormatException("Zero denominator in ExtendedRational string");
                }
                r = Rational.valueOf(n, d);
            } else {
                r = Rational.valueOf(new BigDecimal(s));
            }
        }
        return sign ? RationalOps.neg(r) : r;
    }

    public boolean isNaN() {
        return false;
    }

    public boolean isNegativeInfinity() {
        return this instanceof NegativeInfinity;
    }

    public boolean isPositiveInfinity() {
        return this instanceof PositiveInfinity;
    }

    public boolean isFinite() {
        return !(this instanceof Infinity);
    }

    public boolean isBinary() {
        return this instanceof Binary;
    }

    public boolean isDouble() {
        return this instanceof BinaryDouble || this instanceof Infinity;
    }

    public boolean isInteger() {
        return isBinary() && intExp2() >= 0;
    }

    public Rational numerator() {
        BigInteger numerator = getNumeratorWithout2s();
        int exp = Math.min(0, intExp2());
        return valueOf(numerator, exp);
    }

    public BigInteger biNumerator() {
        BigInteger numerator = getNumeratorWithout2s();
        int exp = intExp2();
        if (exp > 0) {
            numerator = numerator.shiftLeft(exp);
        }
        return numerator;
    }

    public Rational denominator() {
        BigInteger denominator = getDenominatorWithout2s();
        int exp = Math.min(0, -intExp2());
        return valueOf(denominator, exp);
    }

    public BigInteger biDenominator() {
        BigInteger denominator = getDenominatorWithout2s();
        int exp = intExp2();
        if (exp < 0) {
            denominator = denominator.shiftLeft(-exp);
        }
        return denominator;
    }

    public abstract int signum();

    public BigInteger biCeilLog2() {
        return BigInteger.valueOf(intCeilLog2());
    }

    public abstract int intCeilLog2();

    public BigInteger biFloorLog2() {
        return BigInteger.valueOf(intFloorLog2());
    }

    public abstract int intFloorLog2();

    public boolean eq(ExtendedRational that) {
        return compareTo(that) == 0;
    }

    public boolean ne(ExtendedRational that) {
        return compareTo(that) != 0;
    }

    public boolean lt(ExtendedRational that) {
        return compareTo(that) < 0;
    }

    public boolean le(ExtendedRational that) {
        return compareTo(that) <= 0;
    }

    public boolean gt(ExtendedRational that) {
        return compareTo(that) > 0;
    }

    public boolean ge(ExtendedRational that) {
        return compareTo(that) >= 0;
    }

    public int compareTotalTo(ExtendedRational that) {
        return compareTo(that);
    }

    public abstract int compareTo(ExtendedRational that);

    abstract int compareTo(BinaryImpl that);

    abstract int compareTo(BinaryDoubleImpl that);

    public double doubleValue(RoundingMode roundingMode) {
        switch (roundingMode) {
            case UP:
                return doubleValueUp();
            case DOWN:
                return doubleValueDown();
            case CEILING:
                return doubleValueCeiling();
            case FLOOR:
                return doubleValueFloor();
            case HALF_UP:
                return doubleValueHalfUp();
            case HALF_DOWN:
                return doubleValueHalfDown();
            case HALF_EVEN:
                return doubleValueHalfEven();
            case UNNECESSARY:
            default:
                return doubleValueExact();
        }
    }

    public abstract double doubleValueUp();

    public abstract double doubleValueDown();

    public double doubleValueCeiling() {
        return signum() > 0 ? doubleValueUp() : doubleValueDown();
    }

    public double doubleValueFloor() {
        return signum() > 0 ? doubleValueDown() : doubleValueUp();
    }

    public abstract double doubleValueHalfUp();

    public abstract double doubleValueHalfDown();

    public abstract double doubleValueHalfEven();

    public double doubleValueExact() {
        throw new ArithmeticException("Rounding necessary");
    }

    public float floatValue(RoundingMode roundingMode) {
        double rd = ExtendedRationalContexts.valueOf(BinaryValueSet.BINARY32, roundingMode).rnd(this).doubleValue();
        float rf = (float) rd;
        assert rf == rd;
        return rf;
    }

    /**
     * Converts this {@code Rational} to a {@code BigInteger}. This conversion
     * is analogous to a <a
     * href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#25363"><i>narrowing
     * primitive conversion</i></a> from {@code double} to {@code long} as
     * defined in the <a href="http://java.sun.com/docs/books/jls/html/">Java
     * Language Specification</a>: any fractional part of this {@code Rational}
     * will be discarded. Note that this conversion can lose information about
     * the precision of the {@code Rational} value.
     * <p>
     * To have an exception thrown if the conversion is inexact (in other words
     * if a nonzero fractional part is discarded), use the
     * {@link #toBigIntegerExact()} method.
     *
     * @return this {@code Rational} converted to a {@code BigInteger}.
     */
    public BigInteger toBigInteger() {
        BigInteger n = biNumerator();
        BigInteger d = biDenominator();
        assert d.signum() != 0;
        return n.divide(d);
    }

    /**
     * Returns the value of the specified number as an <code>int</code>. This
     * may involve rounding or truncation.
     *
     * @return the numeric value represented by this object after conversion to
     * type <code>int</code>.
     */
    public int intValue() {
        return toBigInteger().intValue();
    }

    /**
     * Returns the value of the specified number as a <code>long</code>. This
     * may involve rounding or truncation.
     *
     * @return the numeric value represented by this object after conversion to
     * type <code>long</code>.
     */
    public long longValue() {
        return toBigInteger().longValue();
    }

    /**
     * Returns the value of the specified number as a <code>float</code>. This
     * may involve rounding.
     *
     * @return the numeric value represented by this object after conversion to
     * type <code>float</code>.
     */
    public float floatValue() {
        return floatValue(RoundingMode.HALF_EVEN);
    }

    /**
     * Returns the value of the specified number as a <code>double</code>. This
     * may involve rounding.
     *
     * @return the numeric value represented by this object after conversion to
     * type <code>double</code>.
     */
    public double doubleValue() {
        return doubleValueHalfEven();
    }

    public BigDecimal bigDecimalValue(MathContext mc) {
        BigInteger n = biNumerator();
        BigInteger d = biDenominator();
        assert d.signum() != 0;
        return new BigDecimal(n).divide(new BigDecimal(d), mc);
    }

    public BigInteger biExp2() {
        return BigInteger.valueOf(intExp2());
    }

    public abstract int intExp2();

    public abstract BigInteger getNumeratorWithout2s();

    abstract BigInteger getNumeratorWithout2sAbs();

    public abstract BigInteger getDenominatorWithout2s();

    public abstract String toHexString(BinaryValueSet valueSet);
}
