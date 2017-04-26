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
package net.java.jinterval.symbolic.fdlibm;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * Find double floating-point numbers whech are very close to multiples pi/2 
 */
public class PiApprox {

    static Rational computeFraction(List<BigInteger> l, int n) {
        Rational x = Rational.valueOf(l.get(n - 1));
        for (int i = n - 2; i >= 0; i--) {
            x = RationalOps.recip(x);
            x = RationalOps.add(x, Rational.valueOf(l.get(i)));
        }
        return x;
    }

    static List<Rational> chainedFractions(SetIntervalContext ic, SetInterval x) {
        assert x.isCommonInterval() && x.inf().signum() > 0;
        List<BigInteger> l = new ArrayList();
        for (;;) {
            SetInterval fx = SetIntervalOps.floor(x);
            if (!fx.isSingleton()) {
                break;
            }
            l.add(fx.inf().toBigInteger());
            x = SetIntervalOps.sub(x, fx);
            x = ic.recip(x);
        }
        List<Rational> result = new ArrayList<>();
        for (int n = 1; n < l.size(); n++) {
            result.add(computeFraction(l, n));
        }
        return result;
    }

    private static double bestEvenX;
    private static Rational bestEvenErr;

    private static double bestOddX;
    private static Rational bestOddErr;

    static SetInterval checkDiff(SetIntervalContext ic, SetInterval piHalf, BigInteger fracN, BigInteger fracD, BigInteger k, int e) {
        BigInteger n = fracD.multiply(k);
        Rational nr = Rational.valueOf(n);
        Rational fp = Rational.valueOf(fracN.multiply(k), e - 52);
        SetInterval npi = ic.mul(piHalf, SetIntervalOps.nums2(nr, nr));
        SetInterval diff = ic.sub(npi, SetIntervalOps.nums2(fp, fp));
        Rational err = (Rational) diff.mag();
        if (n.testBit(0)) {
            if (bestOddErr == null || err.lt(bestOddErr)) {
                bestOddErr = err;
                bestOddX = fp.doubleValue();
                System.out.println("O[" + diff.doubleInf() + "," + diff.doubleSup() + "] contains (" + n + "*pi/2 - " + fp + ")");
            }
        } else {
            if (bestEvenErr == null || err.lt(bestEvenErr)) {
                bestEvenErr = err;
                bestEvenX = fp.doubleValue();
                System.out.println("E[" + diff.doubleInf() + "," + diff.doubleSup() + "] contains (" + n + "*pi/2 - " + fp + ")");
            }
        }
        return ic.sub(npi, SetIntervalOps.nums2(fp, fp));
    }

    static void checkE(SetIntervalContext ic, SetInterval piHalf, int e) {
        Rational p = Rational.exp2(52 - e);
        List<Rational> fracs = chainedFractions(ic, ic.mul(piHalf, SetIntervalOps.nums2(p, p)));
        int i = 0;
        while (i < fracs.size() && fracs.get(i).biNumerator().bitLength() < 53) {
            i++;
        }
        assert i < fracs.size();
        Rational frac = fracs.get(i - 1);
        BigInteger fracN = frac.biNumerator();
        BigInteger fracD = frac.biDenominator();
        BigInteger minK = BigInteger.ONE.shiftLeft(52).add(fracN.subtract(BigInteger.ONE)).divide(fracN);
        BigInteger maxK = BigInteger.ONE.shiftLeft(53).divide(fracN);
        checkDiff(ic, piHalf, fracN, fracD, minK, e);
        if (!minK.equals(maxK)) {
            checkDiff(ic, piHalf, fracN, fracD, maxK, e);
        }
    }

    public static void main(String[] args) {
        SetIntervalContext ic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY2048);
        SetInterval piHalf = ic.mul(ic.pi(), ic.numsToInterval(0.5, 0.5));
        for (int e = 1023; e >= 1; e--) {
            if (e == 900) {
                ic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY1024);
            } else if (e == 400) {
                ic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY512);
            }
            System.out.println(e);
            checkE(ic, piHalf, e);
        }
        System.out.println("bestOddX=" + Double.toHexString(bestOddX));
        System.out.println("bestEvenX=" + Double.toHexString(bestEvenX));
    }

}
