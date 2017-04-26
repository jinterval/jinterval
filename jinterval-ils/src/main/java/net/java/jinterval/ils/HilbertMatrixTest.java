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
public class HilbertMatrixTest extends MatlabOps {

    public static void main(String[] args) {
        BinaryValueSet valueSet = BinaryValueSet.BINARY64;
        ExtendedRationalContext rcExact = ExtendedRationalContexts.exact();
        ExtendedRationalContext rc = ExtendedRationalContexts.mkNearest(valueSet);
        SetIntervalContext icExact = SetIntervalContexts.getExact();
        SetIntervalContext ic = SetIntervalContexts.getTightest(valueSet);
        for (int n = 1; n <= 10; n++) {
            System.out.println("n=" + n);
            RationalMatrix Hexact = hilbert(n);
//            System.out.println("H" + Hexact);
            RationalMatrix Hrnd = hilbert(rc, n);
//            System.out.println("Hrnd" + Hrnd);
            RationalMatrix HInv = inv(rc, Hexact);
//            System.out.println("Hinv" + HInv);
            RationalMatrix HrndInv = inv(rc, Hrnd);
            System.out.println("HrndInv" + HrndInv);
            RationalMatrix defect = sub(rcExact, mul(rcExact, Hexact, HrndInv), eye(n));
            System.out.println("defect " + abs(defect).getMaxValue().doubleValueCeiling() + " " + defect);
//            System.out.println("defect " + abs(defect).getMaxValue().doubleValueCeiling());
            RationalMatrix defectRnd = sub(rcExact, mul(rcExact, Hrnd, HrndInv), eye(n));
            System.out.println("defectRnd " + abs(defectRnd).getMaxValue().doubleValueCeiling());
//            System.out.println("defectRnd " + abs(defectRnd).getMaxValue().doubleValueCeiling() + " " + defectRnd);
            IntervalMatrix Hiexact = new IntervalMatrix(Hexact);
            IntervalMatrix HirndInv = new IntervalMatrix(HrndInv);
            IntervalMatrix idefect = sub(ic, mul(ic, Hiexact, HirndInv), new IntervalMatrix(eye(n)));
            ExtendedRational eps = idefect.mag().getMaxValue();
            System.out.println("idefect " + eps.doubleValueCeiling() + " " + idefect);
            if (eps.gt(Rational.valueOf(0.5 / n))) {
                continue;
            }
            ExtendedRational epsn = ExtendedRationalOps.div(ExtendedRationalOps.mul(ExtendedRationalOps.mul(eps, eps), Rational.valueOf(n)),
                    ExtendedRationalOps.sub(Rational.one(), ExtendedRationalOps.mul(eps, Rational.valueOf(n))));
            IntervalMatrix corr0 = new IntervalMatrix(n, n);
            for (int i = 0; i < n; i++) {
                SetInterval s = ic.numsToInterval(0, 0);
                for (int j = 0; j < n; j++) {
                    ExtendedRational a = ExtendedRationalOps.abs(HrndInv.getEntry(i, j));
                    s = ic.add(s, ic.numsToInterval(ExtendedRationalOps.neg(a), a));
                }
                s = ic.mul(s, ic.numsToInterval(ExtendedRationalOps.neg(epsn), epsn));
                for (int j = 0; j < n; j++) {
                    corr0.setEntry(i, j, s);
                }
            }
            System.out.println("corr0" + corr0);
            IntervalMatrix corr = add(ic, HirndInv, sub(ic, corr0, mul(ic, HirndInv, idefect)));
            System.out.println("corr" + corr);
            System.out.println("Hiinvexact" + Hiexact.invGauss(icExact));
            System.out.println("Hiinv" + Hiexact.invGauss(ic));
        }
    }
}
