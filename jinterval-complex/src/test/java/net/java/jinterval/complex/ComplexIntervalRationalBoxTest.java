/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package net.java.jinterval.complex;

import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.Ignore;

/**
 *
 */
public class ComplexIntervalRationalBoxTest {

    private ComplexIntervalRationalBox box3;

    public ComplexIntervalRationalBoxTest() {
    }

    @BeforeClass
    public static void setUpClass() {
    }

    @AfterClass
    public static void tearDownClass() {
    }

    @Before
    public void setUp() {
        box3 = new ComplexIntervalRationalBox(
                Rational.valueOf(1, 3), Rational.valueOf(2, 3), Rational.valueOf(4, 3), Rational.valueOf(5, 3), false);
    }

    @After
    public void tearDown() {
        box3 = null;
    }

    /**
     * Test of realInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealInf_0args() {
        System.out.println("realInf");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.realInf();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of realInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealInf_BinaryValueSet() {
        System.out.println("realInf");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.realInf(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleRealInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleRealInf() {
        System.out.println("doubleRealInf");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleRealInf();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatRealInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatRealInf() {
        System.out.println("floatRealInf");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatRealInf();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of realSup method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealSup_0args() {
        System.out.println("realSup");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.realSup();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of realSup method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealSup_BinaryValueSet() {
        System.out.println("realSup");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.realSup(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleRealSup method, of class ComplexIntervalRationalBox.
     */
    @Test
    public void testDoubleRealSup() {
        System.out.println("doubleRealSup");
        ComplexIntervalRationalBox instance = box3;
        double expResult = Math.nextUp(2.0 / 3.0);
        double result = instance.doubleRealSup();
        assertEquals(expResult, result, 0.0);
    }

    /**
     * Test of floatRealSup method, of class ComplexIntervalRationalBox.
     */
    @Test
    public void testFloatRealSup() {
        System.out.println("floatRealSup");
        ComplexIntervalRationalBox instance = box3;
        float expResult = 2.0f / 3.0f;
        float result = instance.floatRealSup();
        assertEquals(expResult, result, 0.0);
    }

    /**
     * Test of imagInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagInf_0args() {
        System.out.println("imagInf");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.imagInf();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of imagInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagInf_BinaryValueSet() {
        System.out.println("imagInf");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.imagInf(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleImagInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleImagInf() {
        System.out.println("doubleImagInf");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleImagInf();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatImagInf method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatImagInf() {
        System.out.println("floatImagInf");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatImagInf();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of imagSup method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagSup_0args() {
        System.out.println("imagSup");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.imagSup();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of imagSup method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagSup_BinaryValueSet() {
        System.out.println("imagSup");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.imagSup(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleImagSup method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleImagSup() {
        System.out.println("doubleImagSup");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleImagSup();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatImagSup method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatImagSup() {
        System.out.println("floatImagSup");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatImagSup();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of realMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealMid_0args() {
        System.out.println("realMid");
        ComplexIntervalRationalBox instance = null;
        Rational expResult = null;
        Rational result = instance.realMid();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of realMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealMid_BinaryValueSet() {
        System.out.println("realMid");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        Rational expResult = null;
        Rational result = instance.realMid(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleRealMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleRealMid() {
        System.out.println("doubleRealMid");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleRealMid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatRealMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatRealMid() {
        System.out.println("floatRealMid");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatRealMid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of imagMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagMid_0args() {
        System.out.println("imagMid");
        ComplexIntervalRationalBox instance = null;
        Rational expResult = null;
        Rational result = instance.imagMid();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of imagMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagMid_BinaryValueSet() {
        System.out.println("imagMid");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        Rational expResult = null;
        Rational result = instance.imagMid(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleImagMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleImagMid() {
        System.out.println("doubleImagMid");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleImagMid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatImagMid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatImagMid() {
        System.out.println("floatImagMid");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatImagMid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of realWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealWid_0args() {
        System.out.println("realWid");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.realWid();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of realWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRealWid_BinaryValueSet() {
        System.out.println("realWid");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.realWid(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleRealWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleRealWid() {
        System.out.println("doubleRealWid");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleRealWid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatRealWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatRealWid() {
        System.out.println("floatRealWid");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatRealWid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of imagWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagWid_0args() {
        System.out.println("imagWid");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.imagWid();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of imagWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testImagWid_BinaryValueSet() {
        System.out.println("imagWid");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.imagWid(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleImagWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleImagWid() {
        System.out.println("doubleImagWid");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleImagWid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatImagWid method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatImagWid() {
        System.out.println("floatImagWid");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatImagWid();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of rad method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRad_0args() {
        System.out.println("rad");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.rad();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of rad method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testRad_BinaryValueSet() {
        System.out.println("rad");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.rad(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleRad method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleRad() {
        System.out.println("doubleRad");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleRad();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatRad method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatRad() {
        System.out.println("floatRad");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatRad();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of mag method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testMag_0args() {
        System.out.println("mag");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.mag();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of mag method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testMag_BinaryValueSet() {
        System.out.println("mag");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.mag(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleMag method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleMag() {
        System.out.println("doubleMag");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleMag();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatMag method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatMag() {
        System.out.println("floatMag");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatMag();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of mig method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testMig_0args() {
        System.out.println("mig");
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.mig();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of mig method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testMig_BinaryValueSet() {
        System.out.println("mig");
        BinaryValueSet numberFormat = null;
        ComplexIntervalRationalBox instance = null;
        ExtendedRational expResult = null;
        ExtendedRational result = instance.mig(numberFormat);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of doubleMig method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testDoubleMig() {
        System.out.println("doubleMig");
        ComplexIntervalRationalBox instance = null;
        double expResult = 0.0;
        double result = instance.doubleMig();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of floatMig method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testFloatMig() {
        System.out.println("floatMig");
        ComplexIntervalRationalBox instance = null;
        float expResult = 0.0F;
        float result = instance.floatMig();
        assertEquals(expResult, result, 0.0);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isEmpty method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testIsEmpty() {
        System.out.println("isEmpty");
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.isEmpty();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isBounded method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testIsBounded() {
        System.out.println("isBounded");
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.isBounded();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isEntire method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testIsEntire() {
        System.out.println("isEntire");
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.isEntire();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isBox method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testIsBox() {
        System.out.println("isBox");
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.isBox();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isDisc method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testIsDisc() {
        System.out.println("isDisc");
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.isDisc();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isEqual method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testIsEqual() {
        System.out.println("isEqual");
        ComplexInterval that = null;
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.isEqual(that);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of containedIn method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testContainedIn() {
        System.out.println("containedIn");
        ComplexInterval that = null;
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.containedIn(that);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of containedInInterior method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testContainedInInterior() {
        System.out.println("containedInInterior");
        ComplexInterval that = null;
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.containedInInterior(that);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of areDisjoint method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testAreDisjoint() {
        System.out.println("areDisjoint");
        ComplexInterval that = null;
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.areDisjoint(that);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of possiblyUndefined method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testPossiblyUndefined() {
        System.out.println("possiblyUndefined");
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.possiblyUndefined();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isMutable method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testIsMutable() {
        System.out.println("isMutable");
        ComplexIntervalRationalBox instance = null;
        boolean expResult = false;
        boolean result = instance.isMutable();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of toString method, of class ComplexIntervalRationalBox.
     */
    @Ignore
    @Test
    public void testToString() {
        System.out.println("toString");
        ComplexIntervalRationalBox instance = null;
        String expResult = "";
        String result = instance.toString();
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }
}
