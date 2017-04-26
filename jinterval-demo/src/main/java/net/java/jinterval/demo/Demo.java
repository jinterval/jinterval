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
package net.java.jinterval.demo;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.ils.IntervalMatrix;
import net.java.jinterval.ils.IntervalVector;
import net.java.jinterval.ils.GaussSeidelIterativeSolver;
import net.java.jinterval.ils.SubdiffNewtonIterativeSolver;

/**
 *
 *
 */
public class Demo {

    private static void evaluateSimpleExpressions() {
        // SetIntervalContext ic = SetIntervalContexts.getInfSup(BinaryValueSet.BINARY16);
        // SetIntervalContext ic = SetIntervalContexts.getInfSup(BinaryValueSet.BINARY32);
        // SetIntervalContext ic = SetIntervalContexts.getInfSup(BinaryValueSet.BINARY128);
        SetIntervalContext ic = SetIntervalContexts.getExact();

        SetInterval x = ic.numsToInterval(1, 2);          // create x = [1,2] from numbers
        SetInterval y = ic.numsToInterval(3, 5);          // create y = [2,3] from numbers
        SetInterval z = ic.textToInterval("[1/3, 4.5]");	// create interval from string

        SetInterval s = ic.add(x, y);                    // s = x + y
        SetInterval d = ic.div(s, y);                 // d = s / y

        System.out.println("x+y = " + s);
        System.out.println("(x+y)/y = " + d);

        if (d.subset(z)) {	                            // if d in z
            ExtendedRational a = z.inf();		        //   get z lower bound as a rational number
            ExtendedRational b = z.sup(); 		        //   get z upper bound as a rational number
            System.out.println("[" + a + "," + b + "] contains " + d);
        } else {
            double r = z.doubleRad();                   // else get double approximation of z radius
            System.out.println("rad z = " + r);
        }
    }

    public static Expression createRevisitedRumpExpression() {
        CodeList rump = CodeList.create("a", "b");
        Expression a = rump.getInp(0);
        Expression b = rump.getInp(1);
        Expression c333_75 = rump.num(333.75, "c333_75");
        Expression c11 = rump.num(11, "c11");
        Expression c121 = rump.num(121, "c121");
        Expression c2 = rump.num(2, "c2");
        Expression c5_5 = rump.num(5.5, "c5_5");
        return c333_75.sub(a.pown(2)).mul(b.pown(6)).name("term1")
                .add(a.pown(2).mul(
                        c11.mul(a.pown(2)).mul(b.pown(2))
                        .sub(c121.mul(b.pown(4)))
                        .sub(c2)).name("term2"))
                .add(c5_5.mul(b.pown(8)).name("term3"))
                .add(a.div(c2.mul(b)).name("term4"))
                .name("revisitedRump");
    }
    
    private static void evaluateRumpExpression(String message, BinaryValueSet valueSet) {
        System.out.println("=== " + message + " ===");
        Expression rump = createRevisitedRumpExpression();
        Rational a = Rational.valueOf(77617);
        Rational b = Rational.valueOf(33096);

        try {
            ExtendedRationalContext rc = valueSet != null
                    ? ExtendedRationalContexts.mkNearest(valueSet)
                    : ExtendedRationalContexts.exact();
            ExtendedRational[] args = {a, b};
            ExtendedRational r = ExtendedRationalContexts.evaluateRational(rc, rump.getCodeList(), args, rump)[0];
            System.out.println("r=" + r.doubleValue() + " " + r);
        } catch (ArithmeticException e) {
            System.out.println("r=NaN");
        }

        SetIntervalContext ic = valueSet != null
            ? SetIntervalContexts.getTightest(valueSet)
            : SetIntervalContexts.getExact();
        SetInterval[] args = {ic.numsToInterval(a, a), ic.numsToInterval(b, b)};
        SetInterval i = SetIntervalContexts.evaluateSetInterval(ic, rump.getCodeList(), args, rump)[0];
        System.out.println("i=" + i);
    }

    private static void testRumpExpression() {
        System.out.println("RumpExpression");
        evaluateRumpExpression("BINARY16", BinaryValueSet.BINARY16);
        evaluateRumpExpression("BINARY32", BinaryValueSet.BINARY32);
        evaluateRumpExpression("BINARY64", BinaryValueSet.BINARY64);
        evaluateRumpExpression("BINARY128", BinaryValueSet.BINARY128);
        evaluateRumpExpression("BINARY256", BinaryValueSet.BINARY256);
        evaluateRumpExpression("Exact", null);
    }

    private static void testDecorationsSqrt1() {
        SetIntervalContext ic = SetIntervalContexts.getDoubleNearest();
        SetInterval x, y;

        // 1) sqrt([0,1]) = ([0,1]; COM)
        x = ic.numsToInterval(0, 1);
        y = ic.sqrt(x);
        System.out.println("sqrt(" + x + ") = " + y + " " + y.getDecoration());

        // 2) sqrt([-1,1]) = ([0,1]; CON)
        x = ic.numsToInterval(-1, 1);
        y = ic.sqrt(x);
        System.out.println("\nsqrt(" + x + ") = " + y + " " + y.getDecoration());

        // 3) sqrt([-2,-1]) = ([EMPTY]; NDF)
        x = ic.numsToInterval(-2, -1);
        y = ic.sqrt(x);
        System.out.println("\nsqrt(" + x + ") = " + y + " " + y.getDecoration());

        // 4) sqrt([EMPTY]) = ([EMPTY]; SAF)
        x = ic.empty();
        y = ic.sqrt(x);
        System.out.println("\nsqrt(" + x + ") = " + y + " " + y.getDecoration());
    }

    private static void testDecorationsSqrt() {
        SetIntervalContext ic = SetIntervalContexts.getDoubleNearest();
        SetInterval x, y;

        x = ic.numsToInterval(0, 1);
        y = ic.sqrt(x);
        System.out.println("sqrt(" + x + ") = " + y + " " + y.getDecoration());

        x = ic.numsToInterval(-1, 1);
        y = ic.sqrt(x);
        System.out.println("\nsqrt(" + x + ") = " + y + " " + y.getDecoration());

        x = ic.numsToInterval(-2, -1);
        y = ic.sqrt(x);
        System.out.println("\nsqrt(" + x + ") = " + y + " " + y.getDecoration());

        x = ic.empty();
        y = ic.sqrt(x);
        System.out.println("\nsqrt(" + x + ") = " + y + " " + y.getDecoration());
    }

    private static void testDecorationsRecip1() {
        SetIntervalContext ic = SetIntervalContexts.getDoubleNearest();
        SetInterval x, y, z;

        // 1) 1/[0, 0] = ([EMPTY]; NDF)
        x = ic.numsToInterval(0, 0);
        y = ic.recip(x);
        System.out.println("1/" + x + " = " + y + " " + y.getDecoration());

        // 2) x = [0; 1] 
        //    y = 1/x = ([1,Inf]; CON)
        x = ic.numsToInterval(0, 1);
        y = ic.recip(x);
        System.out.println("\n1/" + x + " = " + y + " " + y.getDecoration());

        // 3) 1/[eps, 1] = ([1, 1/eps]; SAF)
        x = ic.numsToInterval(Double.MIN_VALUE, 1);
        y = ic.recip(x);
        System.out.println("\n1/" + x + " = " + y + " " + y.getDecoration());

        // 4) x = [1,+oo] = ([1,+oo]; SAF)
        //    y = 1/x = ([0,1]; CON)
        //    z = 1/y = ([0,1]; CON)
        x = ic.numsToInterval(0, Double.POSITIVE_INFINITY);
        y = ic.recip(x);
        z = ic.recip(y);
        System.out.println("\nx = " + x + " " + x.getDecoration() + "\n"
                + "y = 1/x = " + y + " " + y.getDecoration() + "\n"
                + "z = 1/y = " + z + " " + z.getDecoration());
    }

    private static void testDecorationsRecip() {
        SetIntervalContext ic = SetIntervalContexts.getDoubleNearest();
        SetInterval x, y;

        x = ic.numsToInterval(0, 0);
        y = ic.recip(x);
        System.out.println("1/" + x + " = " + y + " " + y.getDecoration());

        x = ic.numsToInterval(0, 1);
        y = ic.recip(x);
        System.out.println("\n1/" + x + " = " + y + " " + y.getDecoration());

        x = ic.numsToInterval(Double.MIN_VALUE, 1);
        y = ic.recip(x);
        System.out.println("\n1/" + x + " = " + y + " " + y.getDecoration());

        x = ic.numsToInterval(0, Double.POSITIVE_INFINITY);
        y = ic.recip(x);
        System.out.println("\nx = " + x + " " + x.getDecoration()
                + "  y = 1/x = " + y + " " + y.getDecoration());
    }

    protected static SetInterval infsup(double inf, double sup) {
        return SetIntervalOps.nums2(inf, sup);
    }

    private static void solveBarthNudingILS() {
        // Define Barth-Nuding ILS
        IntervalMatrix A = new IntervalMatrix(
                new IntervalVector(infsup(2, 4), infsup(-2, 0)),
                new IntervalVector(infsup(-1, 0), infsup(2, 4)));

        IntervalVector b = new IntervalVector(
                infsup(1, 2),
                infsup(-2, 2));

        // Construct solver
        GaussSeidelIterativeSolver solver
                = new GaussSeidelIterativeSolver(BinaryValueSet.BINARY64, 16);

        // Solve ILS
        IntervalVector x = solver.solve(A, b);

        System.out.println("A:\n" + A);
        System.out.println("b:\n" + b);
        System.out.println("x:\n" + x);
    }

    private static void solveBarthNudingILS1() {
        // Define value set and construct context
        BinaryValueSet valueSet = BinaryValueSet.BINARY64;
        SetIntervalContext ic = SetIntervalContexts.getTightest(valueSet);

        // Define Barth-Nuding ILS
        IntervalMatrix A = new IntervalMatrix(2, 2);
        A.setEntry(0, 0, ic.numsToInterval(2, 4));
        A.setEntry(0, 1, ic.numsToInterval(-2, 0));
        A.setEntry(1, 0, ic.numsToInterval(-1, 0));
        A.setEntry(1, 1, ic.numsToInterval(2, 4));
//        IntervalMatrix A = new IntervalMatrix(new SetInterval[][] { 
//            { n2i( 2,4), n2i(-2,0) },
//            { n2i(-1,0), n2i( 2,4) } 
//        });

        IntervalVector b = new IntervalVector(2);
        b.setEntry(0, ic.numsToInterval(1, 2));
        b.setEntry(1, ic.numsToInterval(-2, 2));

        // Construct solver
        GaussSeidelIterativeSolver solver
                = new GaussSeidelIterativeSolver(valueSet, 16);

        // Solve ILS
        IntervalVector x = solver.solve(A, b);

        System.out.println("A:\n" + A);
        System.out.println("b:\n" + b);
        System.out.println("x:\n" + x);
    }

    private static void solveILSUsingSubdiffNewton() {
        SetIntervalContext ic = SetIntervalContexts.getDoubleNearest();

        IntervalMatrix A = new IntervalMatrix(2, 2);
        A.setEntry(0, 0, ic.numsToInterval(2, 4));
        A.setEntry(0, 1, ic.numsToInterval(-2, 1));
        A.setEntry(1, 0, ic.numsToInterval(-1, 2));
        A.setEntry(1, 1, ic.numsToInterval(2, 4));

        IntervalVector b = new IntervalVector(2);
        b.setEntry(0, ic.numsToInterval(-2, 2));
        b.setEntry(1, ic.numsToInterval(-2, 2));
//        b.setEntry(0, ic.nums2interval(2, -2));
//        b.setEntry(0, ic.nums2interval(2, -2));

        SubdiffNewtonIterativeSolver solver
                = new SubdiffNewtonIterativeSolver(BinaryValueSet.BINARY64, 16);

        IntervalVector x = solver.solve(A, b);

        System.out.println("A:\n" + A);
        System.out.println("b:\n" + b);
        System.out.println("x:\n" + x);
    }

//    private static testIRSolver{
//        IRSolver s = new IRSolver
//    }
    // Computes rational approximation to e (Euler number)
    public static void evaluateTaylorExpansion() {
        ExtendedRationalContext rc;
        rc = ExtendedRationalContexts.exact();
        //rc = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY32);

        ExtendedRational one = ExtendedRational.one();
        ExtendedRational fact = one;
        ExtendedRational e = one;
        for (int i = 1; i <= 10; i++) {
            System.out.println("e = " + e + "  (" + e.doubleValue() + ")");
            fact = rc.mul(fact, ExtendedRational.valueOf(i));
            e = rc.add(e, rc.div(one, fact));
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        evaluateSimpleExpressions();
        testRumpExpression();
        //testDecorationsSqrt();
        //testDecorationsRecip();
        //solveILSUsingSubdiffNewton();
        //solveBarthNudingILS();
        //evaluateTaylorExpansion();
    }
}
