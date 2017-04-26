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
import java.util.ArrayList;
import java.util.List;
import static org.junit.Assert.*;
import org.junit.*;

/**
 *
 * @author nadezhin
 */
public class BinaryTest {

    private List<Binary> vals = new ArrayList<Binary>();

    public BinaryTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }

    @Before
    public void setUp() {
        vals.add((Binary) ExtendedRational.zero());
        addPair(Double.MIN_VALUE);
        addPair(1 / 3.0);
        addPair(-56, 0x55555555555555L);
        addPair(1);
        addPair(Double.MAX_VALUE);
        addPair(Double.MAX_EXPONENT - 53, 0x3FFFFFFFFFFFFFL);
        addPair(Double.MAX_EXPONENT + 1, 1);
    }

    private void addPair(double v) {
        Binary r = (Binary) Binary.valueOf(-v);
        assertTrue(r instanceof BinaryDouble);
        assertTrue(r.doubleValue(RoundingMode.UNNECESSARY) == -v);
        vals.add(0, r);
        r = (Binary) Binary.valueOf(v);
        assertTrue(r instanceof BinaryDouble);
        assertTrue(r.doubleValue(RoundingMode.UNNECESSARY) == v);
        vals.add(r);
    }

    private void addPair(int exp, long unscaledValue) {
        BigInteger posUnscaled = BigInteger.valueOf(unscaledValue);
        BigInteger negUnscaled = posUnscaled.negate();
        Binary r = (Binary) ExtendedRational.valueOf(negUnscaled, exp);
        assertEquals(exp, r.intExp2());
        assertEquals(negUnscaled, r.getNumeratorWithout2s());
        vals.add(0, r);
        r = (Binary) ExtendedRational.valueOf(posUnscaled, exp);
        assertEquals(exp, r.intExp2());
        assertEquals(posUnscaled, r.getNumeratorWithout2s());
        vals.add(r);
    }

    @After
    public void tearDown() {
        vals = null;
    }

    /**
     * Test of getExp method, of class Binary.
     */
    @Test
    public void testGetExp() {
        System.out.println("getExp");
        assertEquals(Double.MIN_EXPONENT - 52, Binary.valueOf(-Double.MIN_VALUE).intExp2());
    }

    /**
     * Test of getUnscaledValue method, of class Binary.
     */
    @Test
    public void testGetUnscaledValue() {
        System.out.println("getUnscaledValue");
        assertEquals(BigInteger.valueOf(-1), Binary.valueOf(-Double.MIN_VALUE).getNumeratorWithout2s());
    }

    /**
     * Test of signum method, of class Binary.
     */
    @Test
    public void testSignum() {
        System.out.println("signum");

        int iz = vals.size() / 2;
        assertSame(Binary.zero(), vals.get(iz));
        for (int i = 0; i < vals.size(); i++) {
            Binary val = vals.get(i);
            int expected = i < iz ? -1 : i > iz ? +1 : 0;
            assertEquals(expected, val.signum());
        }
    }

    /**
     * Test of compareTo method, of class Binary.
     */
    @Test
    public void testCompareTo_Rational() {
        System.out.println("compareTo");
        ExtendedRational r =
                ExtendedRational.valueOf(BigInteger.valueOf(1), BigInteger.valueOf(3));
        for (Binary val : vals) {
            int expected = ((ExtendedRational) val).compareTo(r);
            assertEquals(expected, val.compareTo(r));
        }
    }

    /**
     * Test of compareTo method, of class Binary.
     */
    @Test
    public void testCompareTo_Binary() {
        System.out.println("compareTo");
        int iz = vals.size() / 2;
        for (int i = 0; i < vals.size(); i++) {
            Binary x = vals.get(i);
            for (int j = 0; j < vals.size(); j++) {
                Binary y = vals.get(j);
                int expected = Integer.signum(i - j);
                assertEquals(expected, x.compareTo(y));
                if (x instanceof BinaryDouble && y instanceof BinaryDouble) {
                    assertEquals(expected, ((BinaryDouble) x).compareTo((BinaryDouble) y));
                }
            }
        }
    }

//    /**
//     * Test of round method, of class Binary.
//     */
//    @Test
//    public void testRound_BinaryMathContext() {
//        System.out.println("round");
//        BinaryValueSet BINARY1 = new BinaryValueSet(1);
//        for (Binary val : vals) {
//            for (RoundingMode m : RoundingMode.class.getEnumConstants()) {
//                if (m == RoundingMode.UNNECESSARY) {
//                    continue;
//                }
//                ExtendedRationalContext ctx = ExtendedRationalContexts.valueOf(BINARY1, m);
//                ExtendedRational expected = ctx.rnd((ExtendedRational) val);
//                assertEquals(expected, ctx.rnd(val));
//            }
//        }
//    }

    /**
     * Test of negate method, of class Binary.
     */
    @Test
    public void testNegate() {
        System.out.println("negate");
        for (int i = 0; i < vals.size(); i++) {
            Binary val = vals.get(i);
            Binary expected = vals.get(vals.size() - 1 - i);
            checkBinary(expected, RationalOps.neg(val));
        }
    }

    /**
     * Test of abs method, of class Binary.
     */
    @Test
    public void testAbs() {
        System.out.println("abs");
        int iz = vals.size() / 2;
        for (int i = 0; i < vals.size(); i++) {
            Binary val = vals.get(i);
            Binary expected = vals.get(i >= iz ? i : iz - (i - iz));
            checkBinary(expected, RationalOps.abs(val));
        }
    }

    /**
     * Test of add method, of class Binary.
     */
    @Test
    public void testAdd() {
        System.out.println("add");
        for (Binary x : vals) {
            for (Binary y : vals) {
                Rational r;
                try {
                    r = RationalOps.add(x, y);
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

                ExtendedRational expected = ExtendedRationalOps.add(x, y);
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of subtract method, of class Binary.
     */
    @Test
    public void testSubtract() {
        System.out.println("subtract");
        for (Binary x : vals) {
            for (Binary y : vals) {
                ExtendedRational r;
                try {
                    r = RationalOps.sub(x, y);
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
                ExtendedRational expected = RationalOps.sub(x, y);
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of multiply method, of class Binary.
     */
    @Test
    public void testMultiply() {
        System.out.println("multiply");
        for (Binary x : vals) {
            for (Binary y : vals) {
                ExtendedRational r;
                try {
                    r = RationalOps.mul(x, y);
                } catch (ArithmeticException e) {
                    assertTrue(!x.isFinite() && y.signum() == 0 || !y.isFinite()
                            && x.signum() == 0);
                    continue;
                }
                ExtendedRational expected = ExtendedRationalOps.mul(x, y);
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of min method, of class Binary.
     */
    @Test
    public void testMin() {
        System.out.println("min");
        for (Binary x : vals) {
            for (Binary y : vals) {
                Binary expected = x.compareTotalTo(y) < 0 ? x : y;
                ExtendedRational r = x.min(y);
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of max method, of class Binary.
     */
    @Test
    public void testMax() {
        System.out.println("max");
        for (Binary x : vals) {
            for (Binary y : vals) {
                Binary expected = x.compareTotalTo(y) > 0 ? x : y;
                ExtendedRational r = x.max(y);
                assertEquals(expected, r);
            }
        }
    }

    /**
     * Test of getUnscaledDivisor method, of class Binary.
     */
    @Test
    public void testGetUnscaledDivisor() {
        System.out.println("getUnscaledDivisor");
        assertSame(BigInteger.ONE, Binary.valueOf(-Double.MIN_VALUE).getDenominatorWithout2s());
    }

    /**
     * Test of precision method, of class Binary.
     */
    @Test
    public void testPrecision() {
        System.out.println("precision");
        for (Binary x : vals) {
            int expected;
            if (!x.isFinite() || x.signum() == 0) {
                expected = 1;
            } else {
                expected = x.getNumeratorWithout2s().abs().bitLength();
            }
            assertEquals(expected, x.precision());
        }
    }

    @Test
    public void testStrangeAdd() {
        System.out.println("strangeAdd");
        double a = -0x1abfaad70b78fdp-56;
        double b = +0xf1da075f7e71fp-53;
        double c = a + b;
        ExtendedRationalContext ctx = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64);
        assertEquals(ExtendedRational.valueOf(c), ctx.add(ExtendedRational.valueOf(a), ExtendedRational.valueOf(b)));
    }

    private void checkBinary(Binary expected, ExtendedRational r) {
        assertEquals(expected, r);
        checkBinary(expected.intExp2(), expected.getNumeratorWithout2s(), r);
        assertEquals(expected.hashCode(), r.hashCode());
    }

    private void checkBinary(int exp, BigInteger p, ExtendedRational r) {
        assertEquals(exp, r.intExp2());
        assertEquals(p, r.getNumeratorWithout2s());
        checkNumber((Binary) r);
    }

    private void checkNumber(Binary r) {
        int exp = r.intExp2();
        BigInteger p = r.getNumeratorWithout2s();
        if (!r.isFinite()) {
            assertTrue(r == Binary.NEGATIVE_INFINITY || r
                    == Binary.POSITIVE_INFINITY);
            assertEquals(1, r.precision());
            return;
        }
        assertEquals(BigInteger.ONE, r.getDenominatorWithout2s());
        if (p.signum() == 0) {
            assertSame(r, Binary.zero());
            assertEquals(0, exp);
            assertSame(BigInteger.ZERO, p);
        } else {
            assertTrue(p.testBit(0));
        }
    }
}
