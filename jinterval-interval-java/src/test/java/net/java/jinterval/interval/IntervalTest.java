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
package net.java.jinterval.interval;

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.*;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 */
public class IntervalTest {

    private static ExtendedRational pow(ExtendedRationalContext rc, ExtendedRational x, int p) {
        ExtendedRational r = Rational.one();
        for (int i = 0; i < p; i++) {
            r = rc.mul(r, x);
        }
        return r;
    }

    private static SetInterval pow(SetIntervalContext ic, SetInterval x, int p) {
        SetInterval r = ic.numsToInterval(Rational.one(), Rational.one());
        for (int i = 0; i < p; i++) {
            r = ic.mul(r, x);
        }
        return r;
    }

    private static void evaluateRumpExpression(String message, BinaryValueSet valueSet) {
        System.out.println("=== " + message + " ===");
        ExtendedRationalContext rc;
        SetIntervalContext ic;
        if (valueSet != null) {
            rc = ExtendedRationalContexts.mkNearest(valueSet);
            ic = SetIntervalContexts.getTightest(valueSet);
        } else {
            rc = ExtendedRationalContexts.exact();
            ic = SetIntervalContexts.getExact();
        }


        Rational x0 = Rational.valueOf(77617);
        Rational y0 = Rational.valueOf(33096);
        Rational c333_75 = Rational.valueOf(333.75);
        Rational c11 = Rational.valueOf(11);
        Rational c121 = Rational.valueOf(121);
        Rational c2 = Rational.valueOf(2);
        Rational c5_5 = Rational.valueOf(5.5);

        try {
            ExtendedRational r1 = rc.mul(rc.sub(c333_75, pow(rc, x0, 2)), pow(rc, y0, 6));
            ExtendedRational r2 = rc.mul(pow(rc, x0, 2),
                    rc.sub(rc.sub(rc.mul(rc.mul(c11, pow(rc, x0, 2)), pow(rc, y0, 2)), rc.mul(c121, pow(rc, y0, 4))), c2));
            ExtendedRational r3 = rc.mul(c5_5, pow(rc, y0, 8));
            ExtendedRational r4 = rc.div(x0, rc.mul(c2, y0));
            ExtendedRational r = rc.add(rc.add(rc.add(r1, r2), r3), r4);
            System.out.println("r=" + r.doubleValue() + " " + r);
        } catch (ArithmeticException e) {
            System.out.println("r=NaN");
        }

        SetInterval x = ic.numsToInterval(x0, x0);
        SetInterval y = ic.numsToInterval(y0, y0);
        SetInterval ic333_75 = ic.numsToInterval(c333_75, c333_75);
        SetInterval ic11 = ic.numsToInterval(c11, c11);
        SetInterval ic121 = ic.numsToInterval(c121, c121);
        SetInterval ic2 = ic.numsToInterval(c2, c2);
        SetInterval ic5_5 = ic.numsToInterval(c5_5, c5_5);

        SetInterval i1 = ic.mul(ic.sub(ic333_75, pow(ic, x, 2)), pow(ic, y, 6));
        SetInterval i2 = ic.mul(pow(ic, x, 2),
                ic.sub(ic.sub(ic.mul(ic.mul(ic11, pow(ic, x, 2)), pow(ic, y, 2)), ic.mul(ic121, pow(ic, y, 4))), ic2));
        SetInterval i3 = ic.mul(ic5_5, pow(ic, y, 8));
        SetInterval i4 = ic.div(x, ic.mul(ic2, y));
        SetInterval i = ic.add(ic.add(ic.add(i1, i2), i3), i4);
        System.out.println("i=" + i);
    }

    @Test
    public void testRumpExpression() {
        System.out.println("RumpExpression");
        evaluateRumpExpression("BINARY16", BinaryValueSet.BINARY16);
        evaluateRumpExpression("BINARY32", BinaryValueSet.BINARY32);
        evaluateRumpExpression("BINARY64", BinaryValueSet.BINARY64);
        evaluateRumpExpression("BINARY128", BinaryValueSet.BINARY128);
        evaluateRumpExpression("BINARY256", BinaryValueSet.BINARY256);
        evaluateRumpExpression("Exact", null);
    }
}
