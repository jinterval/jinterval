/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.java.jinterval.field;

import net.java.jinterval.expression.OptimizationProblem;
import net.java.jinterval.expression.example.FireRisk;
import org.apache.commons.math3.optim.PointValuePair;
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
public class MultivariateFunctionAdapterTest {

    boolean savedDebug;

    public MultivariateFunctionAdapterTest() {
    }

    @BeforeClass
    public static void setUpClass() {
    }

    @AfterClass
    public static void tearDownClass() {
    }

    @Before
    public void setUp() {
        savedDebug = MultivariateFunctionAdapter.setDebug(true);
    }

    @After
    public void tearDown() {
        MultivariateFunctionAdapter.setDebug(savedDebug);
    }

    /**
     * Test of optimize method, of class MultivariateFunctionAdapter.
     */
    @Test
    public void testOptimize() {
        System.out.println("optimize");
        OptimizationProblem problem = FireRisk.createOptimizationProblemTempMaxFv();
        PointValuePair pv = MultivariateFunctionAdapter.optimize(problem);
        assertEquals(-0.08021443147650907, pv.getValue(), 1e-16);
        assertEquals(170.0, pv.getPoint()[0], 0);
        assertEquals(299.0, pv.getPoint()[1], 0);
        assertEquals(9.0, pv.getPoint()[2], 0);
        assertEquals(34.8, pv.getPoint()[3], 0);
    }
}
