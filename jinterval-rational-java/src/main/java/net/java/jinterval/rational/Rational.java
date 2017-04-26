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

/**
 *
 */
public abstract class Rational extends ExtendedRational {

    static final int EXP_LIMIT_SH = 28;
    static final int EXP_LIMIT = 1 << EXP_LIMIT_SH;
    private static final Rational ONE = (Rational) valueOf(1);
    private static final BigInteger BI_MINUS_ONE = BigInteger.valueOf(-1);
    static final BigInteger BI_FIVE = BigInteger.valueOf(5);
    private static final long SIGN_MASK = 0x8000000000000000L;
    private static final long MANTISSA_MASK = 0xfffffffffffffL;
    static final MathContext mathContextExact = new MathContext(0, RoundingMode.UNNECESSARY);

    public static Rational valueOf(Number v) {
        if (v instanceof Rational) {
            return (Rational) v;
        }
        NumberConvertor numberConvertor = numberConvertors.get(v.getClass());
        if (numberConvertor == null) {
            if (v instanceof ExtendedRational) {
                throw new DomainException();
            }
            throw new UnsupportedOperationException();
        }
        return numberConvertor.rationalValue(v);
    }

    public static Rational valueOf(Byte v) {
        return Rational.valueOf(v.intValue());
    }

    public static Rational valueOf(Short v) {
        return Rational.valueOf(v.intValue());
    }

    public static Rational valueOf(Integer v) {
        return Rational.valueOf(v.intValue());
    }

    public static Rational valueOf(Long v) {
        return Rational.valueOf(v.longValue());
    }

    public static Rational valueOf(Float v) {
        return Rational.valueOf(v.doubleValue());
    }

    public static Rational valueOf(Double v) {
        return Rational.valueOf(v.doubleValue());
    }

    public static Rational valueOf(int v) {
        return v == 0 ? zero() : new BinaryDoubleImpl(v);
    }

    public static Rational valueOf(long v) {
        return Rational.valueOfImpl(BigInteger.valueOf(v), 0);
    }

    public static Rational valueOf(double v) {
        if (v >= -Double.MAX_VALUE && v <= Double.MAX_VALUE) {
            if (v == 0) {
                return zero();
            }
            return new BinaryDoubleImpl(v);
        }
        throw new DomainException();
    }

    /**
     * Returns rational
     * <code>2^exp</code>
     *
     * @param exp
     */
    public static Rational exp2(int exp) {
        if (Math.abs(exp) >= EXP_LIMIT) {
            throw new ArithmeticException("Overflow");
        }
        return valueOfImpl(BigInteger.ONE, exp);
    }

    public static Rational zero() {
        return Zero.INSTANCE;
    }

    public static Rational one() {
        return ONE;
    }

    public static Rational valueOf(BigInteger v) {
        return Rational.valueOf(v, 0);
    }

    public static Rational valueOf(BigInteger unscaledValue, int exp) {
        checkBitLengthOverflow(unscaledValue);
        return valueOfImpl(unscaledValue, exp);
    }

    static Rational valueOfImpl(BigInteger unscaledValue, int exp) {
        long lexp = exp;
        int lowestBit = unscaledValue.getLowestSetBit();
        if (lowestBit != 0) {
            if (lowestBit < 0) {
                assert unscaledValue.signum() == 0;
                return zero();
            }
            lexp += lowestBit;
            unscaledValue = unscaledValue.shiftRight(lowestBit);
        }
        BigInteger abs = unscaledValue.abs();
        int bitLength = abs.bitLength();
        long nexp = lexp + bitLength - 1;
        if (bitLength <= 53 && nexp >= Double.MIN_EXPONENT && nexp
                <= Double.MAX_EXPONENT) {
            long bits = abs.longValue() << (53 - bitLength);
            assert (bits & ~MANTISSA_MASK) == (MANTISSA_MASK + 1);
            bits &= MANTISSA_MASK;
            bits |= (long) (nexp - (Double.MIN_EXPONENT - 1)) << 52;
            assert (bits & SIGN_MASK) == 0;
            if (unscaledValue.signum() < 0) {
                bits = bits | SIGN_MASK;
            }
            return new BinaryDoubleImpl(Double.longBitsToDouble(bits));
        } else if (bitLength <= 52 && nexp < Double.MIN_EXPONENT && lexp >= Double.MIN_EXPONENT
                - 52) {
            long bits = abs.longValue() << (lexp - (Double.MIN_EXPONENT - 52));
            assert (bits & MANTISSA_MASK) == bits;
            if (unscaledValue.signum() < 0) {
                bits = bits | SIGN_MASK;
            }
            return new BinaryDoubleImpl(Double.longBitsToDouble(bits));
        } else {
            if (lexp < -EXP_LIMIT + 1 || nexp > EXP_LIMIT - 1) {
                throw new ArithmeticException("Value too large");
            }
            return new BinaryImpl(unscaledValue.signum(), abs, (int) lexp);
        }
    }

    public static Rational valueOf(BigDecimal v) {
        BigInteger numerator = v.unscaledValue();
        int scale = v.scale();
        BigInteger denominator;
        if (scale >= 0) {
            denominator = BI_FIVE.pow(scale);
        } else {
            numerator = numerator.multiply(BI_FIVE.pow(-scale));
            denominator = BigInteger.ONE;
        }
        return Rational.valueOf(numerator, denominator, -scale);
    }

    public static Rational valueOf(long numerator, long denominator) {
        return Rational.valueOf(BigInteger.valueOf(numerator), BigInteger.valueOf(denominator));
    }

    public static Rational valueOf(BigInteger numerator, BigInteger denominator) {
        return Rational.valueOf(numerator, denominator, 0);
    }

    public static Rational valueOf(BigInteger numerator, BigInteger denominator, int exp) {
        checkBitLengthOverflow(numerator);
        checkBitLengthOverflow(denominator);
        return valueOfImpl(numerator, denominator, exp);
    }

    static Rational valueOfImpl(BigInteger numerator, BigInteger denominator, int exp) {
        checkBitLengthOverflow(numerator);
        checkBitLengthOverflow(denominator);
        long lexp = exp;
        int lowestDenominatorBit = denominator.getLowestSetBit();
        if (lowestDenominatorBit != 0) {
            if (lowestDenominatorBit < 0) {
                assert denominator.signum() == 0;
                throw new DomainException();
            }
            lexp -= lowestDenominatorBit;
            denominator = denominator.shiftRight(lowestDenominatorBit);
        }
        int lowestNumeratorBit = numerator.getLowestSetBit();
        if (lowestNumeratorBit != 0) {
            if (lowestNumeratorBit < 0) {
                return Rational.zero();
            }
            lexp += lowestNumeratorBit;
            numerator = numerator.shiftRight(lowestNumeratorBit);
        }
        if (denominator.signum() < 0) {
            numerator = numerator.negate();
            denominator = denominator.negate();
        }
        BigInteger gcd = numerator.gcd(denominator);
        if (!gcd.equals(BigInteger.ONE)) {
            numerator = numerator.divide(gcd);
            denominator = denominator.divide(gcd);
        }
        if (denominator.equals(BigInteger.ONE)) {
            int iexp = (int) lexp;
            if (iexp != lexp) {
                throw new ArithmeticException("Value too large");
            }
            return valueOfImpl(numerator, iexp);
        } else {
            if (lexp >= 0) {
                if (lexp > EXP_LIMIT - numerator.abs().bitLength() || denominator.bitLength() > EXP_LIMIT) {
                    throw new ArithmeticException("Overfflow");
                }
            } else {
                if (numerator.abs().bitLength() > EXP_LIMIT || lexp < -EXP_LIMIT + denominator.bitLength()) {
                    throw new ArithmeticException("Overflow");
                }
            }
            return new RationalImpl((int) lexp, numerator, denominator);
        }
    }

    public static Rational valueOf(String str) {
        ExtendedRational r = ExtendedRational.valueOf(str);
        if (r instanceof Rational) {
            return (Rational) r;
        }
        throw new DomainException();
    }

    static void checkBitLengthOverflow(BigInteger v) {
        BigInteger shifted = v.shiftRight(Integer.MAX_VALUE);
        if (shifted.signum() != 0 && !shifted.equals(BI_MINUS_ONE)) {
            throw new ArithmeticException("Overflow");
        }
    }
}
