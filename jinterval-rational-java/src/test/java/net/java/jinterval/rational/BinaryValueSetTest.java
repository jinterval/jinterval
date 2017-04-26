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
import static org.junit.Assert.*;
import org.junit.*;

/**
 *
 * @author nadezhin
 */
public class BinaryValueSetTest {

    private BinaryValueSet.MathContext context64;

    public BinaryValueSetTest() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }

    @Before
    public void setUp() {
        context64 = BinaryValueSet.BINARY64.roundNearest();
    }

    @After
    public void tearDown() {
        context64 = null;
    }

    /**
     * Test of valueOf method, of class BinaryValueSet.
     */
    @Test
    public void testValueOf() {
        System.out.println("valueOf");
        int setPrecision = 10;
        RoundingMode setRoundingMode = RoundingMode.CEILING;
        BinaryValueSet.MathContext result = new BinaryValueSet(setPrecision).getMathContext(setRoundingMode);
        assertSame(setRoundingMode, result.roundingMode);
        assertEquals(setPrecision, result.getPrecision());
        assertEquals(Integer.MAX_VALUE - 1, result.getValueSet().getMaxExp());
        assertEquals(-Integer.MAX_VALUE + setPrecision, result.getValueSet().getMinExp());
    }

    /**
     * Test of round method, of class BinaryValueSet.
     */
    @Test
    public void testRound_Number() {
        System.out.println("round");
        Number v = Double.POSITIVE_INFINITY;
        ExtendedRational expResult = ExtendedRational.POSITIVE_INFINITY;
        ExtendedRational result = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY16).rnd(v);
        assertSame(expResult, result);
    }

    /**
     * Test of round method, of class BinaryValueSet.
     */
    @Test
    public void testRound_Rational() {
        System.out.println("round");
        ExtendedRational v = ExtendedRational.valueOf(new BigDecimal("0.1"));
        ExtendedRational expResult = ExtendedRational.valueOf(BigInteger.valueOf(1638/*
                 * 4
                 */), -14);
        ExtendedRational result = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY16).rnd(v);
        assertEquals(expResult, result);
    }

    /**
     * Test of round method, of class BinaryValueSet.
     */
    @Test
    public void testRound_Binary() {
        System.out.println("round");
        ExtendedRational v = ExtendedRational.valueOf(0.1);
        ExtendedRational expResult = ExtendedRational.valueOf(BigInteger.valueOf(1638/*
                 * 4
                 */), -14);
        ExtendedRational result = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY16).rnd(v);
        assertEquals(expResult, result);
    }

    /**
     * Test of getPrecision method, of class BinaryValueSet.
     */
    @Test
    public void testGetPrecision() {
        System.out.println("getPrecision");
        int expResult = 53;
        int result = context64.getPrecision();
        assertEquals(expResult, result);
    }

    /**
     * Test of getRoundingMode method, of class BinaryValueSet.
     */
    @Test
    public void testGetRoundingMode() {
        System.out.println("getRoundingMode");
        RoundingMode expResult = RoundingMode.HALF_EVEN;
        RoundingMode result = context64.getRoundingMode();
        assertSame(expResult, result);
    }

    /**
     * Test of equals method, of class BinaryValueSet.
     */
    @Test
    public void testEquals() {
        System.out.println("equals");
        assertFalse(context64.equals(BinaryValueSet.BINARY16));
    }

    /**
     * Test of hashCode method, of class BinaryValueSet.
     */
    @Test
    public void testHashCode() {
        System.out.println("hashCode");
        int expResult = BinaryValueSet.BINARY64.hashCode() + RoundingMode.HALF_EVEN.hashCode() * 59;
        int result = context64.hashCode();
        assertEquals(expResult, result);
    }

    /**
     * Test of toString method, of class BinaryValueSet.
     */
    @Test
    public void testToString() {
        System.out.println("toString");
        String expResult = "precision=53 roundingMode=HALF_EVEN";
        String result = context64.toString();
        assertEquals(expResult, result);
    }
}
