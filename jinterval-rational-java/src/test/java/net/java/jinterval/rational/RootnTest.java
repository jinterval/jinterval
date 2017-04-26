/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.java.jinterval.rational;

import java.math.BigDecimal;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 */
public class RootnTest {

    public RootnTest() {
    }

    @BeforeClass
    public static void setUpClass() {
    }

    @AfterClass
    public static void tearDownClass() {
    }

    @Before
    public void setUp() {
    }

    @After
    public void tearDown() {
    }

    @Test
    public void testRationalOps() {
        assertEquals(Rational.valueOf(0.5), RationalOps.rootn(Rational.valueOf(0.125), 3));
        assertEquals(Rational.valueOf(2), RationalOps.rootn(Rational.valueOf(0.125), -3));
    }

    @Test(expected = IrrationalException.class)
    public void testIrrational() {
        RationalOps.rootn(Rational.valueOf(2), 2);
    }

    @Test
    public void testBinary64() {
        double v = Math.cbrt(2);
        ExtendedRationalContext rcN = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64);
        assertEquals(Rational.valueOf(v), rcN.rootn(Rational.valueOf(2), 3));
        ExtendedRationalContext rcF = ExtendedRationalContexts.mkFloor(BinaryValueSet.BINARY64);
        assertEquals(Rational.valueOf(Math.nextDown(v)), rcF.rootn(Rational.valueOf(2), 3));
        ExtendedRationalContext rcC = ExtendedRationalContexts.mkCeiling(BinaryValueSet.BINARY64);
        assertEquals(Rational.valueOf(v), rcC.rootn(Rational.valueOf(2), 3));
    }
}
