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

import com.hp.creals.CR;
import java.util.ArrayList;
import java.util.List;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 */
public class StdFunsTest {

    @Before
    public void setUp() {
    }

    @After
    public void tearDown() {
    }

    @Test
    public void testPowCalculations() {
        testPowCalculation(0.25);
        testPowCalculation(0.2501);
        testPowCalculation(0.5);
        testPowCalculation(0.501);
        testPowCalculation(0.6);
        testPowCalculation(0.7);
        testPowCalculation(0.8);
        testPowCalculation(0.9);
        testPowCalculation(0.95);
        testPowCalculation(0.99);
        testPowCalculation(0.999);
        testPowCalculation(0.9999);
        testPowCalculation(1 - 0.5 * Math.ulp(1));
        testPowCalculation(1 + Math.ulp(1));
        testPowCalculation(1.0001);
        testPowCalculation(1.001);
        testPowCalculation(1.01);
        testPowCalculation(1.05);
        testPowCalculation(1.1);
        testPowCalculation(1.2);
        testPowCalculation(1.3);
        testPowCalculation(1.4);
        testPowCalculation(1.49);
        testPowCalculation(1.5);
        testPowCalculation(1.99);
        testPowCalculation(2.0);
        testPowCalculation(2.99);
        testPowCalculation(3.0);
        testPowCalculation(3.99);

        testPowCalculation(4.0);
        testPowCalculation(4.99);
        testPowCalculation(5.0);
        testPowCalculation(7.99);
        testPowCalculation(8.0);
        testPowCalculation(15.99);
        testPowCalculation(16.0);
        testPowCalculation(31.99);
        testPowCalculation(32.0);
        testPowCalculation(63.99);
        testPowCalculation(64.0);

        for (int i = 6; i < 100000; i++) {
//            System.out.println(i + ": ");
            testPowCalculation2(i);
        }
    }

    private void testPowCalculation(double x) {
//        System.out.println(-Math.nextUp(-Math.log(2)));
//        System.out.println(Math.log(2));
//        System.out.println(Math.nextUp(Math.log(2)));

        double logX = Math.log(x);
        double log2logX = Math.log(Math.abs(logX)) / Math.log(2);
        Rational rx = Rational.valueOf(x);
        int fl = StdFuns.log2LogXinf(rx);
//        assertTrue(fl <= log2logX);
//        assertTrue(log2logX < fl + 2);
//        System.out.println("x=" + x + " logX=" + logX + " fl=" + fl + " log2logX=" + log2logX + " diff=" + (log2logX - fl));
    }

    private void testPowCalculation2(int log2x) {
        double logX = log2x * Math.log(2);
        double log2logX = Math.log(Math.abs(logX)) / Math.log(2);
        Rational rx = Rational.exp2(log2x);
        int fl = StdFuns.log2LogXinf(rx);
//        assertTrue(fl <= log2logX);
//        assertTrue(log2logX < fl + 2);
//        System.out.println("x=2^" + log2x + " logX=" + logX + " fl=" + fl + " log2logX=" + log2logX + " diff=" + (log2logX - fl));
    }

    @Test
    public void testLog() {
//        System.out.println("log");
//        List<Double> vals = new ArrayList<Double>();
//        addVal(vals, 0x1p-1000);
//        addVal(vals, 1e-300);
//        addVal(vals, 0x1p-10);
//        addVal(vals, 1e-3);
//        addVal(vals, 0x1p-9);
//        addVal(vals, 0x1p-8);
//        addVal(vals, 0x1p-7);
//        addVal(vals, 1e-2);
//        addVal(vals, 0x1p-6);
//        addVal(vals, 0x1p-5);
//        addVal(vals, 0x1p-4);
//        addVal(vals, 1e-1);
//        addVal(vals, 0x1p-3);
//        addVal(vals, 0x1p-2);
//        addVal(vals, 0x1p-1);
//        addVal(vals, 1 - 0x1p-2);
//        addVal(vals, 1 - 0x1p-3);
//        addVal(vals, 1 - 0x1p-4);
//        addVal(vals, 1 - 0x1p-5);
//        addVal(vals, 1 - 0x1p-6);
//        addVal(vals, 1 - 0x1p-7);
//        addVal(vals, 1 - 0x1p-8);
//        addVal(vals, 1 - 0x1p-9);
//        addVal(vals, 1 - 0x1p-10);
//        addVal(vals, 1);
//        addVal(vals, 1 + 0x1p-10);
//        addVal(vals, 1 + 0x1p-9);
//        addVal(vals, 1 + 0x1p-8);
//        addVal(vals, 1 + 0x1p-7);
//        addVal(vals, 1 + 0x1p-6);
//        addVal(vals, 1 + 0x1p-5);
//        addVal(vals, 1 + 0x1p-4);
//        addVal(vals, 1 + 0x1p-3);
//        addVal(vals, 1 + 0x1p-2);
//        addVal(vals, 1 + 0x1p-1);
//        addVal(vals, 0x1p1);
//        addVal(vals, 0x1p2);
//        addVal(vals, 0x1p3);
//        addVal(vals, 1e1);
//        addVal(vals, 0x1p4);
//        addVal(vals, 0x1p5);
//        addVal(vals, 0x1p6);
//        addVal(vals, 1e2);
//        addVal(vals, 0x1p7);
//        addVal(vals, 0x1p8);
//        addVal(vals, 0x1p9);
//        addVal(vals, 1e3);
//        addVal(vals, 0x1p10);
//        addVal(vals, 1e300);
//        addVal(vals, 0x1p1000);
//        for (double v : vals) {
//            StdFuns.FunLog funLog = new StdFuns.FunLog(Rational.valueOf(v));
//            double log = Math.log(v);
//            int e = Math.getExponent(log);
//            System.out.println("log(" + Double.toHexString(v) + ")=" + log + " " + e + " " + funLog.floorLog2inf + " " + funLog.floorLog2sup);
//            if (v != 1) {
//                assertTrue(e >= funLog.floorLog2inf && e <= funLog.floorLog2sup);
//            }
//        }
//        for (double v : vals) {
//            StdFuns.FunLog2 funLog = new StdFuns.FunLog2(Rational.valueOf(v));
//            double log = Math.log(v) / Math.log(2);
//            int e = Math.getExponent(log);
//            System.out.println("log2(" + Double.toHexString(v) + ")=" + log + " " + e + " " + funLog.floorLog2inf + " " + funLog.floorLog2sup);
//            if (v != 1) {
//                assertTrue(e >= funLog.floorLog2inf && e <= funLog.floorLog2sup);
//            }
//        }
//        for (double v : vals) {
//            StdFuns.FunLog10 funLog = new StdFuns.FunLog10(Rational.valueOf(v));
//            double log = Math.log(v) / Math.log(10);
//            int e = Math.getExponent(log);
//            System.out.println("log10(" + Double.toHexString(v) + ")=" + log + " " + e + " " + funLog.floorLog2inf + " " + funLog.floorLog2sup);
//            if (v != 1) {
//                assertTrue(e >= funLog.floorLog2inf && e <= funLog.floorLog2sup);
//            }
//        }
    }

    private static void addVal(List<Double> list, double v) {
        double eps = 0x1p-48;
        list.add(v * (1 - eps));
        list.add(v);
        list.add(v * (1 + eps));
    }
}
