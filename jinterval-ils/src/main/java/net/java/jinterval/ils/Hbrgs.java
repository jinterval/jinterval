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
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;

/**
 *
 */
public class Hbrgs {

    public static void solve(String msg, Sample sample, BinaryValueSet valueSet) {
        System.out.println(msg);

        IntervalMatrix A = sample.getA();
        IntervalVector b = sample.getb();
        IntervalVector x0 = sample.getx0();
        IntervalVector x;

        GaussSeidelIterativeSolver solver = new GaussSeidelIterativeSolver(valueSet, 16);

        x = solver.solve(A, b, x0);

        System.out.println("x:\n" + x);
    }

    private static void solve(String sampleName, Sample sample) {
        System.out.println("== " + sampleName + " ==");
        System.out.println("A:\n" + sample.getA());
        System.out.println("b:\n" + sample.getb());
        solve(sampleName + " BINARY16", sample, BinaryValueSet.BINARY16);
        solve(sampleName + " BINARY32", sample, BinaryValueSet.BINARY32);
        solve(sampleName + " BINARY64", sample, BinaryValueSet.BINARY64);
        solve(sampleName + " BINARY80", sample, BinaryValueSet.BINARY80);
        solve(sampleName + " BINARY128", sample, BinaryValueSet.BINARY128);
        solve(sampleName + " BINARY256", sample, BinaryValueSet.BINARY256);
        solve(sampleName + " Exact", sample, null);
    }
         
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        solve("Sample1", new Sample1());
        solve("Sample2", new Sample2());
        solve("Sample3", new Sample3());
//       solve("Sample4", new Sample4());
//        solve("Sample5", new Sample5());
        solve("Sample6", new Sample6());
    }
}
