/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.java.jinterval.interval.set;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.rational.BinaryValueSet;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author dn146861
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

    private static void check(int nUlps, double inf, double sup, SetInterval actual) {
        for (int i = 0; i < nUlps; i++) {
            inf = Math.nextDown(inf);
            sup = Math.nextUp(sup);
        }
        assertTrue(actual.subset(SetIntervalOps.nums2(inf, sup)));
    }

    @Test
    public void testExact() {
        SetInterval arg = SetIntervalOps.nums2(0.125, 64);
        SetIntervalContext ic = SetIntervalContexts.getExact();
        assertEquals(SetIntervalOps.nums2(0.5, 4), ic.rootn(arg, 3));
        assertEquals(SetIntervalOps.nums2(0.25, 2), ic.rootn(arg, -3));
        assertEquals(SetIntervalOps.nums2(0.125, 64), ic.rootn(arg, 1));
        assertEquals(SetIntervalOps.nums2(0.015625, 8), ic.rootn(arg, -1));
    }

    @Test
    public void testTightest64() {
        SetInterval arg = SetIntervalOps.nums2(0.125, 64);
        SetIntervalContext ic = SetIntervalContexts.getTightest64();
        assertEquals(SetIntervalOps.nums2(0.5, 4), ic.rootn(arg, 3));
        assertEquals(SetIntervalOps.nums2(0.25, 2), ic.rootn(arg, -3));
        assertEquals(SetIntervalOps.nums2(0.125, 64), ic.rootn(arg, 1));
        assertEquals(SetIntervalOps.nums2(0.015625, 8), ic.rootn(arg, -1));
    }

    @Test
    public void testDefault() {
        SetInterval arg = SetIntervalOps.nums2(0.125, 64);
        SetIntervalContext ic = SetIntervalContexts.getDefault();
        check(3, 0.5, 4, ic.rootn(arg, 3));
        check(0, 0.25, 2, ic.rootn(arg, -3));
        check(2, 0.125, 64, ic.rootn(arg, 1));
        check(0, 0.015625, 8, ic.rootn(arg, -1));
    }

    private Expression genExpression(int q) {
        CodeList codeList = CodeList.create("x");
        Expression x = codeList.getInp(0);
        return x.rootn(q);
    }

    @Test
    public void testEvaluator() {
        Expression e = genExpression(3);
        SetInterval[] args = {SetIntervalOps.nums2(0.125, 64)};
        SetIntervalEvaluator ev = SetIntervalEvaluator.createAccurate(BinaryValueSet.BINARY64, e.getCodeList(), e);
        SetInterval actual = ev.evaluate(args)[0];
        check(3, 0.5, 4, actual);
    }

    @Test
    public void testEvaluatorGrad() {
        Expression e = genExpression(3);
        SetInterval[] args = {SetIntervalOps.nums2(0.125, 64)};
        SetIntervalEvaluatorGrad ev = new SetIntervalEvaluatorGrad(e.getCodeList(), new Expression[]{e});
        SetInterval actual = ev.evaluate(args)[0];
        check(3, 0.5, 4, actual);
        SetInterval actualGrad = ev.getD(e.getIndex(), 0);
        check(5, 0.0625 / 3, 4.0 / 3, actualGrad);
    }
}
