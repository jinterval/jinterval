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
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.List;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author nadezhin
 */
public class RationalTest {

    private List<ExtendedRational> vals = new ArrayList<ExtendedRational>();

    public RationalTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }

    @Before
    public void setUp() {
        vals.add(ExtendedRational.zero());
        addPair(Double.MIN_VALUE);
        addPair(1 / 3.0);
        addPair(-56, 0x55555555555555L, 1);
        addPair(0, 1, 3);
        addPair(1);
        addPair(Double.MAX_VALUE);
        addPair(Double.MAX_EXPONENT - 53, 0x3FFFFFFFFFFFFFL, 1);
        addPair(Double.MAX_EXPONENT + 1, 1, 1);
        vals.add(0, ExtendedRational.NEGATIVE_INFINITY);
        vals.add(ExtendedRational.POSITIVE_INFINITY);
    }

    private void addPair(double v) {
        ExtendedRational r = ExtendedRational.valueOf(-v);
        assertTrue(r instanceof BinaryDouble);
        assertTrue(r.doubleValue(RoundingMode.UNNECESSARY) == -v);
        vals.add(0, r);
        r = ExtendedRational.valueOf(v);
        assertTrue(r instanceof BinaryDouble);
        assertTrue(r.doubleValue(RoundingMode.UNNECESSARY) == v);
        vals.add(r);
    }

    private void addPair(int exp, long nom, long denom) {
        BigInteger posNom = BigInteger.valueOf(nom);
        BigInteger negNom = posNom.negate();
        BigInteger rdenom = BigInteger.valueOf(denom);
        ExtendedRational r = ExtendedRational.valueOf(negNom, rdenom, exp);
        assertEquals(exp, r.intExp2());
        assertEquals(negNom, r.getNumeratorWithout2s());
        assertEquals(rdenom, r.getDenominatorWithout2s());
        vals.add(0, r);
        r = ExtendedRational.valueOf(posNom, rdenom, exp);
        assertEquals(exp, r.intExp2());
        assertEquals(posNom, r.getNumeratorWithout2s());
        assertEquals(rdenom, r.getDenominatorWithout2s());
        vals.add(r);
    }

    @After
    public void tearDown() {
        vals = null;
    }

    /**
     * Test of isNegativeInfinity method, of class RationalNumber.
     */
    @Test
    public void testIsNegativeInfinity() {
        System.out.println("isNegativeInfinity");

        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational val = vals.get(i);
            boolean expected = i == 0;
            assertEquals(expected, val.isNegativeInfinity());
        }
    }

    /**
     * Test of isPositiveInfinity method, of class RationalNumber.
     */
    @Test
    public void testIsPositiveInfinity() {
        System.out.println("isPositiveInfinity");

        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational val = vals.get(i);
            boolean expected = i == vals.size() - 1;
            assertEquals(expected, val.isPositiveInfinity());
        }
    }

    /**
     * Test of isFinite method, of class RationalNumber.
     */
    @Test
    public void testIsFinite() {
        System.out.println("isFinite");

        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational val = vals.get(i);
            boolean expected = i != 0 && i != vals.size() - 1;
            assertEquals(expected, val.isFinite());
        }
    }

    /**
     * Test of getNominator method, of class RationalNumber.
     */
    @Test
    public void testGetNominator() {
        System.out.println("getNominator");

        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational val = vals.get(i);
            BigInteger expected = val.getNumeratorWithout2s();
            int exp = val.intExp2();
            if (exp > 0) {
                expected = expected.shiftLeft(exp);
            }
            assertEquals(expected, val.biNumerator());
        }
    }

    /**
     * Test of getDenominator method, of class RationalNumber.
     */
    @Test
    public void testGetDenominator() {
        System.out.println("getDenominator");

        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational val = vals.get(i);
            BigInteger expected = val.getDenominatorWithout2s();
            int exp = val.intExp2();
            if (exp < 0) {
                expected = expected.shiftLeft(-exp);
            }
            assertEquals(expected, val.biDenominator());
        }
    }

    /**
     * Test of signum method, of class RationalNumber.
     */
    @Test
    public void testSignum() {
        System.out.println("signum");

        int iz = vals.size() / 2;
        assertSame(ExtendedRational.zero(), vals.get(iz));
        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational val = vals.get(i);
            int expected = i < iz ? -1 : i > iz ? +1 : 0;
            assertEquals(expected, val.signum());
        }
    }

    /**
     * Test of compareTo method, of class RationalNumber.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        int iz = vals.size() / 2;
        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational x = vals.get(i);
            for (int j = 0; j < vals.size(); j++) {
                ExtendedRational y = vals.get(j);
                boolean expected = i == j;
                assertEquals(expected, x.equals(y));
            }
        }
    }

    /**
     * Test of compareTo method, of class RationalNumber.
     */
    @Test
    public void testCompareTo() {
        System.out.println("compareTo");
        int iz = vals.size() / 2;
        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational x = vals.get(i);
            for (int j = 0; j < vals.size(); j++) {
                ExtendedRational y = vals.get(j);
                int expected = Integer.signum(i - j);
                assertEquals(expected, x.compareTo(y));
                if (x instanceof BinaryDouble && y instanceof BinaryDouble) {
                    assertEquals(expected, ((BinaryDouble) x).compareTo((BinaryDouble) y));
                }
            }
        }
    }

    /**
     * Test of doubleValue method, of class RationalNumber.
     */
    @Test
    public void testDoubleValue_RoundingMode() {
        System.out.println("doubleValue");

        BigInteger maxDenom
                = BigInteger.ONE.shiftLeft(-Double.MIN_EXPONENT + 52);
        BigInteger maxNom
                = new BigDecimal(Double.MAX_VALUE).toBigIntegerExact();
        ExtendedRational halfPosInf
                = sum(ExtendedRational.valueOf(Double.MAX_VALUE), half(ExtendedRational.valueOf(Math.ulp(Double.MAX_VALUE))));
        ExtendedRational halfNegInf
                = sum(ExtendedRational.valueOf(-Double.MAX_VALUE), half(ExtendedRational.valueOf(-Math.ulp(Double.MAX_VALUE))));
        for (ExtendedRational val : vals) {
            BigInteger nom = val.biNumerator();
            BigInteger absNom = nom.abs();
            BigInteger denom = val.biDenominator();
            for (RoundingMode m : RoundingMode.class.getEnumConstants()) {
                double d;
                try {
                    d = val.doubleValue(m);
                } catch (ArithmeticException e) {
                    assertTrue(denom.bitCount() != 1
                            || denom.compareTo(maxDenom) > 0
                            || absNom.bitLength() > 53 || nom.compareTo(maxNom)
                            > 0);
                    continue;
                }
                if (d > 0) {
                    assertTrue(nom.signum() == 1);
                } else if (d < 0) {
                    assertTrue(nom.signum() == -1);
                }
                ExtendedRational bi, bs;
                boolean ci, cs;
                switch (m) {
                    case UP:
                        if (d == 0) {
                            bi = bs = ExtendedRational.zero();
                            ci = cs = true;
                        } else if (d > 0) {
                            bi = ExtendedRational.valueOf(-Math.nextUp(-d));
                            ci = false;
                            bs = ExtendedRational.valueOf(d);
                            cs = true;
                        } else {
                            bi = ExtendedRational.valueOf(d);
                            ci = true;
                            bs = ExtendedRational.valueOf(Math.nextUp(d));
                            cs = false;
                        }
                        break;
                    case DOWN:
                        if (d == 0) {
                            bi
                                    = ExtendedRational.valueOf(-Double.MIN_VALUE);
                            bs
                                    = ExtendedRational.valueOf(Double.MIN_VALUE);
                            ci = cs = false;
                        } else if (d > 0) {
                            bi = ExtendedRational.valueOf(d);
                            ci = true;
                            bs = ExtendedRational.valueOf(Math.nextUp(d));
                            cs = d == Double.POSITIVE_INFINITY;
                        } else {
                            bi = ExtendedRational.valueOf(-Math.nextUp(-d));
                            ci = d == Double.NEGATIVE_INFINITY;
                            bs = ExtendedRational.valueOf(d);
                            cs = true;
                        }
                        break;
                    case CEILING:
                        bi = ExtendedRational.valueOf(-Math.nextUp(-d));
                        ci = d == Double.NEGATIVE_INFINITY;
                        bs = ExtendedRational.valueOf(d);
                        cs = true;
                        break;
                    case FLOOR:
                        bi = ExtendedRational.valueOf(d);
                        ci = true;
                        bs = ExtendedRational.valueOf(Math.nextUp(d));
                        cs = d == Double.POSITIVE_INFINITY;
                        break;
                    case HALF_UP:
                    case HALF_DOWN:
                    case HALF_EVEN:
                        if (d == Double.NEGATIVE_INFINITY) {
                            bi = ExtendedRational.NEGATIVE_INFINITY;
                        } else if (d == -Double.MAX_VALUE) {
                            bi = halfNegInf;
                        } else if (d == Double.POSITIVE_INFINITY) {
                            bi = halfPosInf;
                        } else {
                            bi
                                    = half(sum(ExtendedRational.valueOf(d), ExtendedRational.valueOf(-Math.nextUp(-d))));
                        }
                        if (d == Double.POSITIVE_INFINITY) {
                            bs = ExtendedRational.POSITIVE_INFINITY;
                        } else if (d == Double.MAX_VALUE) {
                            bs = halfPosInf;
                        } else if (d == Double.NEGATIVE_INFINITY) {
                            bs = halfNegInf;
                        } else {
                            bs
                                    = half(sum(ExtendedRational.valueOf(d), ExtendedRational.valueOf(Math.nextUp(d))));
                        }
                        ci = bi == ExtendedRational.NEGATIVE_INFINITY;
                        cs = bs == ExtendedRational.POSITIVE_INFINITY;
                        if (m == RoundingMode.HALF_UP) {
                            if (d > 0) {
                                ci = true;
                            }
                            if (d < 0) {
                                cs = true;
                            }
                        } else if (m == RoundingMode.HALF_DOWN) {
                            if (d <= 0) {
                                ci = true;
                            }
                            if (d >= 0) {
                                cs = true;
                            }
                        }
                        if (m == RoundingMode.HALF_EVEN) {
                            if ((Double.doubleToRawLongBits(d) & 1)
                                    == 0) {
                                ci = cs = true;
                            }
                        }
                        break;
                    case UNNECESSARY:
                        bi = bs = ExtendedRational.valueOf(d);
                        ci = cs = true;
                        break;
                    default:
                        throw new AssertionError();
                }
                assertTrue(val.compareTo(bi) >= (ci ? 0 : +1));
                assertTrue(val.compareTo(bs) <= (cs ? 0 : -1));
                int signVal = val.signum();
                int signD = d < 0 ? -1 : d > 0 ? +1 : 0;
                assertEquals(signVal, signD);
            }
        }
    }

    private ExtendedRational sum(ExtendedRational x, ExtendedRational y) {
        int xe = x.intExp2();
        BigInteger xn = x.getNumeratorWithout2s();
        BigInteger xd = x.getDenominatorWithout2s();
        int ye = y.intExp2();
        BigInteger yn = y.getNumeratorWithout2s();
        BigInteger yd = y.getDenominatorWithout2s();
        int e;
        if (xe > ye) {
            xn = xn.shiftLeft(xe - ye);
            e = ye;
        } else {
            yn = yn.shiftLeft(ye - xe);
            e = xe;
        }
        return ExtendedRational.valueOf(xn.multiply(yd).add(yn.multiply(xd)), yd.multiply(yd), e);
    }

    private ExtendedRational half(ExtendedRational v) {
        return ExtendedRational.valueOf(v.getNumeratorWithout2s(), v.getDenominatorWithout2s(), v.intExp2()
                - 1);
    }

    /**
     * Test of doubleValueCeiling method, of class RationalNumber.
     */
    @Test
    public void testDoubleValueCeiling() {
        System.out.println("doubleValueCeiling");
        for (ExtendedRational val : vals) {
            double expected = val.doubleValue(RoundingMode.CEILING);
            assertTrue(expected == val.doubleValueCeiling());
            if (expected == 0.0) {
                assertTrue(1 / expected == 1 / val.doubleValueCeiling());
            }
        }
    }

    /**
     * Test of doubleValueFloor method, of class RationalNumber.
     */
    @Test
    public void testDoubleValueFloor() {
        System.out.println("doubleValueFloor");
        for (ExtendedRational val : vals) {
            double expected = val.doubleValue(RoundingMode.FLOOR);
            assertTrue(expected == val.doubleValueFloor());
            if (expected == 0.0) {
                assertTrue(1 / expected == 1 / val.doubleValueCeiling());
            }
        }
    }

    /**
     * Test of valueOf method, of class RationalNumber.
     */
    @Test
    public void testValueOf_int() {
        System.out.println("valueOf int");
        assertSame(ExtendedRational.zero(), ExtendedRational.valueOf(0));
    }

    /**
     * Test of valueOf method, of class RationalNumber.
     */
    @Test
    public void testValueOf_double() {
        System.out.println("valueOf double");
        for (ExtendedRational val : vals) {
            double d = val.doubleValue(RoundingMode.HALF_EVEN);
            ExtendedRational r = ExtendedRational.valueOf(d);
            assertTrue(d == r.doubleValue(RoundingMode.UNNECESSARY));
        }
    }

    /**
     * Test of valueOf method, of class RationalNumber.
     */
    @Test(expected = java.lang.ArithmeticException.class)
    public void testValueOf_double_NaN() {
        System.out.println("valueOf Double.NaN");
        ExtendedRational.valueOf(Double.NaN);
    }

    @Test
    public void testValueOf_pow2() {
        System.out.println("pow2");
        assertEquals(ExtendedRational.valueOf(0.5), ExtendedRational.exp2(-1));
        assertEquals(ExtendedRational.valueOf(1), ExtendedRational.exp2(0));
        assertEquals(ExtendedRational.valueOf(2), ExtendedRational.exp2(1));
    }

    @Test
    public void testValueOf_long() {
        System.out.println("valueOf long");
        checkRationalNumber(63, -1, 1, ExtendedRational.valueOf(Long.MIN_VALUE));
        assertSame(ExtendedRational.zero(), ExtendedRational.valueOf(0L));
        checkRationalNumber(0, Long.MAX_VALUE, 1, ExtendedRational.valueOf(Long.MAX_VALUE));
    }

    /**
     * Test of valueOf method, of class RationalNumber.
     */
    @Test
    public void testValueOf_integer_BigInteger() {
        System.out.println("valueOf");
        for (ExtendedRational val : vals) {
            if (!val.getDenominatorWithout2s().equals(BigInteger.ONE)) {
                continue;
            }
            ExtendedRational n = ExtendedRational.valueOf(val.getNumeratorWithout2s(), val.intExp2());
            ExtendedRational expected = val.signum() == 0 ? ExtendedRational.zero() : val;
            checkRationalNumber(expected, n);
        }
    }

    /**
     * Test of valueOf method, of class RationalNumber.
     */
    @Test
    public void testValueOf_BigDecimal() {
        System.out.println("valueOf BigDecimal");
        checkRationalNumber(-1, 181, 25, ExtendedRational.valueOf(new BigDecimal("3.62")));
    }

    /**
     * Test of valueOf method, of class RationalNumber.
     */
    @Test
    public void testValueOf_BigInteger_BigInteger() {
        System.out.println("valueOf");
        checkRationalNumber(-2, -7, 3, ExtendedRational.valueOf(BigInteger.valueOf(7), BigInteger.valueOf(-12)));
        for (ExtendedRational v : vals) {
            ExtendedRational n = ExtendedRational.valueOf(v.biNumerator(), v.biDenominator());
            ExtendedRational expected = v.signum() == 0 ? ExtendedRational.zero() : v;
            checkRationalNumber(expected, n);
        }
    }

    /**
     * Test of valueOf method, of class RationalNumber.
     */
    @Test
    public void testValueOf_3args() {
        System.out.println("valueOf");
        for (ExtendedRational v : vals) {
            ExtendedRational n = ExtendedRational.valueOf(v.getNumeratorWithout2s(), v.getDenominatorWithout2s(), v.intExp2());
            ExtendedRational expected = v.signum() == 0 ? ExtendedRational.zero() : v;
            checkRationalNumber(expected, n);
        }
    }

    private void checkRationalNumber(ExtendedRational expected, ExtendedRational r) {
        assertEquals(expected, r);
        checkRationalNumber(expected.intExp2(), expected.getNumeratorWithout2s(), expected.getDenominatorWithout2s(), r);
        assertEquals(expected.hashCode(), r.hashCode());
    }

    private void checkRationalNumber(int exp, long p, long q, ExtendedRational r) {
        checkRationalNumber(exp, BigInteger.valueOf(p), BigInteger.valueOf(q), r);
    }

    private void checkRationalNumber(int exp, BigInteger p, BigInteger q, ExtendedRational r) {
        assertEquals(exp, r.intExp2());
        assertEquals(p, r.getNumeratorWithout2s());
        assertEquals(q, r.getDenominatorWithout2s());
        checkNumber(r);
    }

    private void checkNumber(ExtendedRational r) {
        int exp = r.intExp2();
        BigInteger p = r.getNumeratorWithout2s();
        BigInteger q = r.getDenominatorWithout2s();
        if (q.signum() == 0) {
            assertEquals(0, exp);
            if (p.signum() > 0) {
                assertSame(ExtendedRational.POSITIVE_INFINITY, r);
                assertEquals(BigInteger.valueOf(1), p);
            } else {
                assertSame(ExtendedRational.NEGATIVE_INFINITY, r);
                assertEquals(BigInteger.valueOf(-1), p);
            }
            assertSame(BigInteger.ZERO, q);
        } else if (p.signum() == 0) {
            assertSame(r, ExtendedRational.zero());
            assertEquals(0, exp);
            assertSame(BigInteger.ZERO, p);
            assertSame(BigInteger.ONE, q);
        } else {
            assertTrue(p.testBit(0));
            assertTrue(q.testBit(0));
            assertEquals(BigInteger.ONE, p.gcd(q));
        }
    }

    /**
     * Test of getExp method, of class RationalNumber.
     */
    @Test
    public void testGetExp() {
        System.out.println("getExp");
        assertEquals(Double.MIN_EXPONENT - 52, ExtendedRational.valueOf(-Double.MIN_VALUE).intExp2());
    }

    /**
     * Test of getP method, of class RationalNumber.
     */
    @Test
    public void testGetP() {
        System.out.println("getP");
        assertEquals(BigInteger.valueOf(-1), ExtendedRational.valueOf(-Double.MIN_VALUE).getNumeratorWithout2s());
    }

    /**
     * Test of getQ method, of class RationalNumber.
     */
    @Test
    public void testGetQ() {
        System.out.println("getQ");
        assertEquals(BigInteger.valueOf(1), ExtendedRational.valueOf(-Double.MIN_VALUE).getDenominatorWithout2s());
    }

    /**
     * Test of byteValue method, of class RationalNumber.
     */
    @Test
    public void testByteValue() {
        System.out.println("byteValue");
        assertEquals((byte) 0, ExtendedRational.NEGATIVE_INFINITY.byteValue());
        assertEquals((byte) -1, ExtendedRational.POSITIVE_INFINITY.byteValue());
    }

    /**
     * Test of byteValue method, of class RationalNumber.
     */
    @Test
    public void testShortValue() {
        System.out.println("shortValue");
        assertEquals((short) 0, ExtendedRational.NEGATIVE_INFINITY.shortValue());
        assertEquals((short) -1, ExtendedRational.POSITIVE_INFINITY.shortValue());
    }

    /**
     * Test of intValue method, of class RationalNumber.
     */
    @Test
    public void testIntValue() {
        System.out.println("intValue");
        assertEquals(Integer.MIN_VALUE, ExtendedRational.NEGATIVE_INFINITY.intValue());
        assertEquals(Integer.MAX_VALUE, ExtendedRational.POSITIVE_INFINITY.intValue());
    }

    /**
     * Test of longValue method, of class RationalNumber.
     */
    @Test
    public void testLongValue() {
        System.out.println("longValue");
        assertEquals(Long.MIN_VALUE, ExtendedRational.NEGATIVE_INFINITY.longValue());
        assertEquals(Long.MAX_VALUE, ExtendedRational.POSITIVE_INFINITY.longValue());
    }

    /**
     * Test of floatValue method, of class RationalNumber.
     */
    @Test
    public void testFloatValue() {
        System.out.println("floatValue");
        assertTrue(Float.NEGATIVE_INFINITY == ExtendedRational.NEGATIVE_INFINITY.floatValue());
        assertTrue(Float.POSITIVE_INFINITY == ExtendedRational.POSITIVE_INFINITY.floatValue());
    }

    /**
     * Test of doubleValue method, of class RationalNumber.
     */
    @Test
    public void testDoubleValue() {
        System.out.println("doubleValue");
        assertTrue(Double.NEGATIVE_INFINITY == ExtendedRational.NEGATIVE_INFINITY.doubleValue());
        assertTrue(Double.POSITIVE_INFINITY == ExtendedRational.POSITIVE_INFINITY.doubleValue());
    }

    /**
     * Test of negate method, of class RationalNumber.
     */
    @Test
    public void testNegate() {
        System.out.println("negate");
        for (int i = 0; i < vals.size(); i++) {
            ExtendedRational val = vals.get(i);
            ExtendedRational expected = vals.get(vals.size() - 1 - i);
            checkRationalNumber(expected, ExtendedRationalOps.neg(val));
        }
    }

    /**
     * Test of add method, of class RationalNumber.
     */
    @Test
    public void testAdd() {
        System.out.println("add");
        for (ExtendedRational x : vals) {
            for (ExtendedRational y : vals) {
                ExtendedRational r;
                try {
                    r = ExtendedRationalOps.add(x, y);
                } catch (ArithmeticException e) {
                    if (x.signum() > 0) {
                        assertSame(ExtendedRational.POSITIVE_INFINITY, x);
                        assertSame(ExtendedRational.NEGATIVE_INFINITY, y);
                    } else {
                        assertSame(ExtendedRational.NEGATIVE_INFINITY, x);
                        assertSame(ExtendedRational.POSITIVE_INFINITY, y);
                    }
                    continue;
                }
                BigInteger xn = x.biNumerator();
                BigInteger xd = x.biDenominator();
                BigInteger yn = y.biNumerator();
                BigInteger yd = y.biDenominator();
                BigInteger n = xn.multiply(yd).add(yn.multiply(xd));
                BigInteger d = xd.multiply(yd);
                ExtendedRational expected;
                if (d.signum() != 0) {
                    expected = ExtendedRational.valueOf(n, d);
                } else if (yd.signum() == 0) {
                    expected = y;
                } else {
                    expected = x;
                }
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of subtract method, of class RationalNumber.
     */
    @Test
    public void testSubtract() {
        System.out.println("subtract");
        for (ExtendedRational x : vals) {
            for (ExtendedRational y : vals) {
                ExtendedRational r;
                try {
                    r = ExtendedRationalOps.sub(x, y);
                } catch (ArithmeticException e) {
                    if (x.signum() > 0) {
                        assertSame(ExtendedRational.POSITIVE_INFINITY, x);
                        assertSame(ExtendedRational.POSITIVE_INFINITY, y);
                    } else {
                        assertSame(ExtendedRational.NEGATIVE_INFINITY, x);
                        assertSame(ExtendedRational.NEGATIVE_INFINITY, y);
                    }
                    continue;
                }
                ExtendedRational expected = ExtendedRationalOps.add(x, ExtendedRationalOps.neg(y));
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of inverse method, of class RationalNumber.
     */
    @Test
    public void testInverse() {
        System.out.println("inverse");
        for (ExtendedRational val : vals) {
            ExtendedRational r;
            try {
                r = ExtendedRationalOps.recip(val);
            } catch (DomainException e) {
                assertTrue(val.signum() == 0);
                continue;
            }
            ExtendedRational expected = ExtendedRational.valueOf(val.biDenominator(), val.biNumerator());
            if (expected.signum() == 0) {
            } else if (val.signum() == 0) {
                if (val == ExtendedRational.zero()) {
                    expected = ExtendedRational.NEGATIVE_INFINITY;
                }
            }
            assertEquals(expected, r);
        }
    }

    /**
     * Test of multiply method, of class RationalNumber.
     */
    @Test
    public void testMultiply() {
        System.out.println("multiply");
        for (ExtendedRational x : vals) {
            for (ExtendedRational y : vals) {
                ExtendedRational r;
                try {
                    r = ExtendedRationalOps.mul(x, y);
                } catch (ArithmeticException e) {
                    assertTrue(!x.isFinite() && y.signum() == 0 || !y.isFinite()
                            && x.signum() == 0);
                    continue;
                }
                BigInteger n = x.biNumerator().multiply(y.biNumerator());
                BigInteger d = x.biDenominator().multiply(y.biDenominator());
                ExtendedRational expected = ExtendedRational.valueOf(n, d);
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of divide method, of class RationalNumber.
     */
    @Test
    public void testDivide() {
        System.out.println("divide");
        for (ExtendedRational x : vals) {
            for (ExtendedRational y : vals) {
                ExtendedRational r;
                try {
                    r = ExtendedRationalOps.div(x, y);
                } catch (ArithmeticException e) {
                    assertTrue(y.signum() == 0 || !x.isFinite() && !y.isFinite());
                    continue;
                }
                BigInteger n = x.biNumerator().multiply(y.biDenominator());
                BigInteger d = x.biDenominator().multiply(y.biNumerator());
                boolean xSign = x.signum() < 0;
                boolean ySign = y.signum() < 0;
                boolean sign = xSign ^ ySign;
                ExtendedRational expected = ExtendedRational.valueOf(n, d);
                if (!expected.isFinite()) {
                    expected = sign ? ExtendedRational.NEGATIVE_INFINITY : ExtendedRational.POSITIVE_INFINITY;
                }
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of min method, of class RationalNumber.
     */
    @Test
    public void testMin() {
        System.out.println("min");
        for (ExtendedRational x : vals) {
            for (ExtendedRational y : vals) {
                ExtendedRational expected = x.compareTotalTo(y) < 0 ? x : y;
                ExtendedRational r = ExtendedRationalOps.min(x, y);
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of max method, of class RationalNumber.
     */
    @Test
    public void testMax() {
        System.out.println("max");
        for (ExtendedRational x : vals) {
            for (ExtendedRational y : vals) {
                ExtendedRational expected = x.compareTotalTo(y) > 0 ? x : y;
                ExtendedRational r = ExtendedRationalOps.max(x, y);
                assertEquals(expected, r);
            }
        }
    }

    @Test
    public void testFromToString() {
        System.out.println("fromToString");
        testFromToString("0", Rational.zero());
        testFromToString("inf", ExtendedRational.POSITIVE_INFINITY);
        testFromToString("-inf", ExtendedRational.NEGATIVE_INFINITY);
        testFromToString("4/3", Rational.valueOf(4, 3));
        testFromToString("-4/3", Rational.valueOf(-4, 3));
        testFromToString("0.2", Rational.valueOf(1, 5));
        testFromToString("-0.2", Rational.valueOf(-1, 5));
        testFromToString("2.2", Rational.valueOf(11, 5));
        testFromToString("-2.2", Rational.valueOf(-11, 5));
        testFromToString("2E-7", Rational.valueOf(1, 5000000));
        testFromToString("-2E-7", Rational.valueOf(-1, 5000000));
        testFromToString("0.0625", Rational.valueOf(1, 16));
        testFromToString("-0.0625", Rational.valueOf(-1, 16));
        testFromToString("0x1p-5", Rational.valueOf(1, 32));
        testFromToString("-0x1p-5", Rational.valueOf(-1, 32));
        testFromToString("0x1.1p-6", Rational.valueOf(17, 1024));
        testFromToString("0x1.2p-6", Rational.valueOf(18, 1024));
        testFromToString("0x1.4p-6", Rational.valueOf(20, 1024));
        testFromToString("0x1.8p-6", Rational.valueOf(24, 1024));
        testFromToString("1", Rational.valueOf(1));
        testFromToString("-1", Rational.valueOf(-1));
        testFromToString("1.1E+5", Rational.valueOf(110000));
        testFromToString("-1.1E+5", Rational.valueOf(-110000));
    }

    private void testFromToString(String s, ExtendedRational r) {
        assertEquals(s, r.toString());
        assertEquals(r, ExtendedRational.valueOf(s));
    }

    @Test
    public void testBadStrings() {
        String[] badStrings = {
            "",
            "++0",
            "- 0",
            "5. 1",
            "7.1.2",
            "-0x",
            "-00x1p7",
            "0x1.fp6/3",
            "+-7/3",
            "-7 /3",
            "7/ 3",
            "1p6",
            "1.e+-9",
            "infin",};
        for (String badString : badStrings) {
            try {
                ExtendedRational.valueOf(badString);
                fail("Expected exception on bad string " + badString);
            } catch (NumberFormatException e) {
                // Expected
            }
        }
    }
}
