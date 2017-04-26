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

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.ExtendedRationalOps;

/**
 * x[0] = 0.5 x[n+1] = 3.75 * x[n] * (1 - x[n])
 */
public class Logistic {

    private static final int MIN_EXP = -(1 << 14) + 2;
    private static final int MAX_EXP = (1 << 14) - 1;
    private static final BinaryValueSet extendedBinary32 = new BinaryValueSet(32 - 8, MIN_EXP, MAX_EXP);
    private static final BinaryValueSet limitedBinary2048 = new BinaryValueSet(2048 - 31, MIN_EXP, MAX_EXP);
    private static final BinaryValueSet limitedBinary4096 = new BinaryValueSet(4096 - 35, MIN_EXP, MAX_EXP);
    private static final BinaryValueSet limitedBinary8192 = new BinaryValueSet(8192 - 39, MIN_EXP, MAX_EXP);
    private static final BinaryValueSet limitedBinary16384 = new BinaryValueSet(16384 - 43, MIN_EXP, MAX_EXP);
    private static final BinaryValueSet limitedBinary32768 = new BinaryValueSet(32768 - 47, MIN_EXP, MAX_EXP);

    // Point computation
    private static void logisticPoint(String msg, ExtendedRationalContext rctx, int n) {
        ExtendedRational k_1 = ExtendedRational.valueOf(1);
        ExtendedRational k_3_75 = ExtendedRational.valueOf(3.75);
        ExtendedRational x = ExtendedRational.valueOf(0.5);
        for (int i = 0; i < n; i++) {
            ExtendedRational approxX1 = rctx.sub(k_1, x);
            ExtendedRational approxX1X = rctx.mul(x, approxX1);
            ExtendedRational approxNewX = rctx.mul(k_3_75, approxX1X);
            x = approxNewX;
//            System.out.println("i=" + i + " x=" + x.doubleValue());
        }
        System.out.println(msg + " x=" + x.doubleValue());
    }

    // Simple interval computation
    private static void logisticInterval(String msg, SetIntervalContext ictx, int n) {
        SetInterval ki_1 = ictx.numsToInterval(1, 1);
        SetInterval ki_3_75 = ictx.numsToInterval(3.75, 3.75);
        SetInterval x = ictx.numsToInterval(0.5, 0.5);
        for (int i = 0; i < n; i++) {
            SetInterval approxX1 = ictx.sub(ki_1, x);
            SetInterval approxX1X = ictx.mul(x, approxX1);
            SetInterval approxNewX = ictx.mul(ki_3_75, approxX1X);
            x = approxNewX;
//            System.out.println("i=" + i + " x=[" + x.doubleInf() + "," + x.doubleSup() + "]");
        }
        System.out.println(msg + " x=[" + x.doubleInf() + "," + x.doubleSup() + "]");
    }

    // Center form computation
    private static void logisticCenterForm(String msg, ExtendedRationalContext rctx, SetIntervalContext ictx, int n) {
        ExtendedRational k_1 = ExtendedRational.valueOf(1);
        ExtendedRational k_3_75 = ExtendedRational.valueOf(3.75);
        ExtendedRational xc = ExtendedRational.valueOf(0.5);
        SetInterval ki_0 = ictx.numsToInterval(0, 0);
        SetInterval ki_3_75 = ictx.numsToInterval(3.75, 3.75);
        SetInterval ki_7_5 = ictx.numsToInterval(7.5, 7.5);
        SetInterval xe = ki_0;
        for (int i = 0; i < n; i++) {
            ExtendedRational approxX1 = rctx.sub(k_1, xc);
            ExtendedRational approxX1X = rctx.mul(xc, approxX1);
            ExtendedRational approxNewX = rctx.mul(k_3_75, approxX1X);

            ExtendedRational exactX1 = ExtendedRationalOps.sub(k_1, xc);
            ExtendedRational exactX1X = ExtendedRationalOps.mul(xc, exactX1);
            ExtendedRational exactNewX = ExtendedRationalOps.mul(k_3_75, exactX1X);

            ExtendedRational errX = ExtendedRationalOps.sub(exactNewX, approxNewX);

            SetInterval xi = ictx.add(ictx.numsToInterval(xc, xc), ictx.convexHull(xe, ki_0));
            SetInterval deriv = ictx.sub(ki_3_75, ictx.mul(ki_7_5, xi));
            xc = approxNewX;
            xe = ictx.add(ictx.numsToInterval(errX, errX), ictx.mul(deriv, xe));
//            System.out.println("i=" + i + " xc=" + xc.doubleValue() + " xe=[" + xe.doubleInf() + "," + xe.doubleSup() + "]");
        }
        SetInterval xi = SetIntervalOps.add(SetIntervalOps.nums2(xc, xc), xe);
        System.out.println(msg + " xc=" + xc.doubleValue() + " xi=[" + xi.doubleInf() + "," + xi.doubleSup() + "] xe=[" + xe.doubleInf() + "," + xe.doubleSup() + "]");
    }

    public static void main(String[] args) {
        int n1 = 30;
        System.out.println("n= " + n1);
        logisticPoint("64", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64), n1);
        logisticCenterForm("64/e32", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64), SetIntervalContexts.getTightest(extendedBinary32), n1);
        logisticInterval("/64", SetIntervalContexts.getTightest(BinaryValueSet.BINARY64), n1);
        logisticPoint("128", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY128), n1);
        logisticInterval("/128", SetIntervalContexts.getTightest(BinaryValueSet.BINARY128), n1);
        System.out.println();
        int n2 = 2790;
        System.out.println("n= " + n2);
        logisticPoint("64", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64), n2);
        logisticPoint("128", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY128), n2);
        logisticPoint("256", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY256), n2);
        logisticPoint("512", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY512), n2);
        logisticPoint("1024", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY1024), n2);
        logisticCenterForm("1024/e32", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY1024), SetIntervalContexts.getTightest(extendedBinary32), n2);
        logisticPoint("2048", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY2048), n2);
        logisticCenterForm("2048/e32", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY2048), SetIntervalContexts.getTightest(extendedBinary32), n2);
        logisticInterval("/l2048", SetIntervalContexts.getTightest(limitedBinary2048), n2);
        logisticInterval("/l4096", SetIntervalContexts.getTightest(limitedBinary4096), n2);
        logisticInterval("/l8192", SetIntervalContexts.getTightest(limitedBinary8192), n2);
        System.out.println();
        int n3 = 10000;
        System.out.println("n= " + n3);
        logisticPoint("64", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64), n3);
        logisticPoint("128", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY128), n3);
        logisticPoint("256", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY256), n3);
        logisticPoint("512", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY512), n3);
        logisticPoint("1024", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY1024), n3);
        logisticPoint("2048", ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY2048), n3);
        logisticPoint("e4096", ExtendedRationalContexts.mkNearest(limitedBinary4096), n3);
        logisticCenterForm("l4096/e32", ExtendedRationalContexts.mkNearest(limitedBinary4096), SetIntervalContexts.getTightest(extendedBinary32), n3);
        logisticPoint("l8192", ExtendedRationalContexts.mkNearest(limitedBinary8192), n3);
        logisticCenterForm("l8192/e32", ExtendedRationalContexts.mkNearest(limitedBinary8192), SetIntervalContexts.getTightest(extendedBinary32), n3);
        logisticInterval("/l8192", SetIntervalContexts.getTightest(limitedBinary8192), n3);
        logisticInterval("/l16384", SetIntervalContexts.getTightest(limitedBinary16384), n3);
        logisticInterval("/l32768", SetIntervalContexts.getTightest(limitedBinary32768), n3);
    }
}
