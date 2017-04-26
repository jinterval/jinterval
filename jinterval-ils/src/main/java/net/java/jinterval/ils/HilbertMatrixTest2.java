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
package net.java.jinterval.ils;

import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.rational.*;

/**
 *
 */
public class HilbertMatrixTest2 extends MatlabOps {

    private static ExtendedRational rms(RationalMatrix m) {
        ExtendedRationalContext rc = ExtendedRationalContexts.mkCeiling(BinaryValueSet.BINARY2048);
        ExtendedRational s = Rational.zero();
        for (int i = 0; i < m.getColumnDimension(); i++) {
            for (int j = 0; j < m.getRowDimension(); j++) {
                s = rc.add(s, rc.sqr(m.getEntry(i, j)));
            }
        }
        return rc.sqrt(rc.div(s, Rational.valueOf(m.getColumnDimension() * m.getRowDimension())));
        
    }
    
    private static void test(String msg, ExtendedRationalContext rc, int n) {
        System.out.print(msg + " n=" + n);
        ExtendedRationalContext rcExact = ExtendedRationalContexts.exact();
        RationalMatrix Hrnd = hilbert(rc, n);
        try {
            long startTime = System.nanoTime();
            RationalMatrix HrndInv = inv(rc, Hrnd);
            long stopTime = System.nanoTime();
            RationalMatrix defectRnd = sub(rcExact, mul(rcExact, Hrnd, HrndInv), eye(n));
            System.out.println(" defectRnd" +
                    " max=" + abs(defectRnd).getMaxValue().doubleValueCeiling() +
                    " rms=" + rms(defectRnd).doubleValueCeiling() + 
                    " " + (stopTime - startTime)/1e9 + " sec");
        } catch (RuntimeException e) {
            System.out.println(" singular");
        }
    }
    
    private static void test(int n) {
        test("b64", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64), n);
        test("b80", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY80), n);
        test("b128", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY128), n);
        test("b256", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY256), n);
        test("b512", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY512), n);
        test("b1024", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY1024), n);
        test("b2048", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY2048), n);
        test("exact", ExtendedRationalContexts.exact(), n);
        System.out.println();
    }

    public static void main(String[] args) {
        test(10);
        test(30);
        test(100);
        test(300);
        test(500);
    }
}
