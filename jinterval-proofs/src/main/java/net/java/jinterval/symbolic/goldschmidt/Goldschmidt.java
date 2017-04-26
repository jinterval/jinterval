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
package net.java.jinterval.symbolic.goldschmidt;

import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;
import net.java.jinterval.symbolic.Symbolic;
import net.java.jinterval.symbolic.UnivariateRationalPolynom;

/**
 *
 */
public class Goldschmidt {

    private static SetIntervalContext pic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY32);

    /**
     * First p terms of Taylor expansion of 1/(1 - u)
     *
     * @param p number of terms
     * @return truncated Taylor expansion
     */
    private static UnivariateRationalPolynom taylorRecip(int p) {
        Rational[] coeff = new Rational[p + 1];
        Arrays.fill(coeff, Rational.one());
        return UnivariateRationalPolynom.valueOf(coeff);
    }

    /**
     * First p terms of Taylor expansion of sqrt(1 - u)
     *
     * @param p number of terms
     * @return truncated Taylor expansion
     */
    private static UnivariateRationalPolynom taylorSqrt(int p) {
        Rational[] coeff = new Rational[p + 1];
        Rational c = Rational.one();
        for (int k = 0; k <= p; k++) {
            coeff[k] = c;
            c = RationalOps.mul(c, Rational.valueOf(2 * (k + 1) - 1, 2 * (k + 1)));
        }
        return UnivariateRationalPolynom.valueOf(coeff);
    }

    /**
     * Error bounds of truncated Taylor expansion of recip or sqrt
     *
     * @param taylor truncated Taylor expansion Taylor
     * @param ic interval context
     * @param u bounds of u
     * @return bounds of taylorError exactFun(u) - taylor(u) tp[p]*|u|^(p +
     * 1)/(1-|u|)
     */
    private static SetInterval taylorErr(UnivariateRationalPolynom taylor, SetIntervalContext ic, SetInterval u) {
        u = ic.abs(u);
        int p = taylor.getOrder();
        Rational highTerm = RationalOps.abs(taylor.getCoeff(p));
        SetInterval nom = ic.mul(ic.numsToInterval(highTerm, highTerm), ic.pown(u, p + 1));
        SetInterval den = ic.sub(ic.numsToInterval(1, 1), u);
        return ic.mul(ic.numsToInterval(-1, +1), ic.div(nom, den));
    }

    private static String showErr(String mult, UnivariateRationalPolynom taylor, SetInterval taylorErr,
            UnivariateRationalPolynom approx, SetIntervalContext ic, SetInterval u) {
        UnivariateRationalPolynom diff = taylor.sub(approx);
        int lowestP = diff.getLowest();
        UnivariateRationalPolynom diffScaled = diff.divideByPowX(lowestP);
        SetInterval diffScaledBound = diffScaled.eval(ic, u);
        return mult + "*(u^" + lowestP + "*" + diffScaledBound + " + " + taylorErr + ")";
    }

    private static String print(SetInterval x) {
        return pic.hull(x).toString();
    }

    private static void testDiv(PrintStream out) {
        SetIntervalContext ic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY128);
        int eWidePrec = 67 + 10;
        SetInterval eWide = ic.numsToInterval(RationalOps.neg(Rational.exp2(-eWidePrec)), Rational.exp2(-eWidePrec));
        int uWidePrec = 5;
        SetInterval uWide = ic.numsToInterval(Rational.zero()/*valueOf(-1, 1 << uWidePrec)*/, Rational.valueOf(+1, 1 << uWidePrec));
        UnivariateRationalPolynom taylor = taylorRecip(20);
        Map<String, SetInterval> env = new HashMap<String, SetInterval>();

        Symbolic c_2 = Symbolic.valueOf(2);

        env.put("A", ic.numsToInterval(1, 2));
        out.println("A in " + print(env.get("A")));
        out.println("B=(1-u)/T");
        env.put("T", ic.numsToInterval(0.5, 1));
        out.println("T in " + print(env.get("T")));
        env.put("u", uWide);
        out.println("u in " + print(env.get("u")));
        out.println("e_* in " + print(eWide));
        SetInterval eTail = taylorErr(taylor, ic, uWide);
        env.put("e_tail", eTail);
        out.println("e_tail in " + print(eTail));
        Symbolic mathFun = Symbolic.valueOf("A", "T", 1).mul(Symbolic.valueOf(taylor).addErr("e_tail"), ic, env);
        out.println("A/B = ");
        mathFun.print(pic, out);
        out.println("in " + print(mathFun.eval(ic, env)));
        out.println();

        Symbolic ni = Symbolic.valueOf("A", "T", 1).addErr("e_n0");
        env.put("e_n0", eWide);
        Symbolic di = Symbolic.valueOf(1, -1);
        Symbolic ri = c_2.sub(di, ic).addErr("e_r0");
        env.put("e_r0", eWide);
        di = di.addErr("e_d0");
        env.put("e_d0", eWide);

        out.println("n0 = A*T + e_n0");
        ni.print(pic, out);
        out.println("in " + print(ni.eval(ic, env)));
        out.println();
        out.println("diff=");
        Symbolic dni = mathFun.sub(ni, ic);
        dni.print(pic, out);
        out.println("in " + print(dni.eval(ic, env)));
        out.println();

        out.println("d0 = B*T + e_d0");
        di.print(pic, out);
        out.println("in " + print(di.eval(ic, env)));
        out.println();

        out.println("r0 = (2 - B*T) + e_r0");
        ri.print(pic, out);
        out.println("in " + print(ri.eval(ic, env)));
        out.println();

        for (int i = 0; i < 4; i++) {
            ni = ri.mul(ni, ic, env).addErr("e_n" + (i + 1));
            env.put("e_n" + (i + 1), eWide);
            di = ri.mul(di, ic, env);
            ri = c_2.sub(di, ic).addErr("e_r" + (i + 1));
            env.put("e_r" + (i + 1), eWide);
            di = di.addErr("e_d" + (i + 1));
            env.put("e_d" + (i + 1), eWide);

            out.println("n" + (i + 1) + " = n" + i + "*r" + i + " + e_n" + (i + 1));
            ni.print(pic, out);
            out.println("in " + print(ni.eval(ic, env)));
            out.println();
            out.println("diff=");
            dni = mathFun.sub(ni, ic);
            dni.print(pic, out);
            out.println("in " + print(dni.eval(ic, env)));
            out.println();
            out.println("<<< " + dni.monomials.size());
            System.out.println("<<< " + dni.monomials.size());
            dni.printMonomials(out);
            out.println(">>>");

            out.println("d" + (i + 1) + " = d" + i + "*r" + i + " + e_d" + (i + 1));
            di.print(pic, out);
            out.println("in " + print(di.eval(ic, env)));
            out.println();

            out.println("r" + (i + 1) + " = (2 - d" + i + "*r" + i + ") + e_r" + (i + 1));
            ri.print(pic, out);
            out.println("in " + print(ri.eval(ic, env)));
            out.println();
        }
    }

    private static void testSqrt(PrintStream out) {
        SetIntervalContext ic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY128);
        int eWidePrec = 50;
        SetInterval eWide = ic.numsToInterval(Rational.valueOf(-1, 1L << eWidePrec), Rational.valueOf(+1, 1L << eWidePrec));
        int uWidePrec = 5;
        SetInterval uWide = ic.numsToInterval(Rational.valueOf(-1, 1 << uWidePrec), Rational.valueOf(+1, 1 << uWidePrec));
        UnivariateRationalPolynom taylor = taylorSqrt(20);
        Map<String, SetInterval> env = new HashMap<String, SetInterval>();

        Symbolic c_1_5 = Symbolic.valueOf(1.5);
        Symbolic c_0_5 = Symbolic.valueOf(0.5);

        out.println("B=(1-u)/T^2");
        env.put("B", ic.numsToInterval(1, 4));
        env.put("T", ic.numsToInterval(0.5, 1));
        env.put("u", uWide);
        out.println();
        SetInterval eTail = taylorErr(taylor, ic, uWide);
        env.put("e_tail", eTail);
        out.println("e_tail in " + print(eTail));
        Symbolic mathFun = Symbolic.valueOf("B", "T", 1).mul(Symbolic.valueOf(taylor).addErr("e_tail"), ic, env);
        out.println("sqrt(B) = ");
        mathFun.print(pic, out);
        out.println();

        Symbolic ti = Symbolic.valueOf("T", "T", 1);
        Symbolic di = Symbolic.valueOf("B", "T", 1, -1).addErr("e_d0");
        env.put("e_d0", eWide);
        Symbolic ni = Symbolic.valueOf(1, -1);
        Symbolic ri = c_1_5.sub(ni.mul(c_0_5, ic, env), ic).addErr("e_r0");
        env.put("e_r0", eWide);
        ni = ni.addErr("e_n0");
        env.put("e_n0", eWide);

        out.println("t0 = T*T");

        out.println("d0 = B*T + e_d0");
        di.print(pic, out);
        out.println();
        out.println("diff=");
        mathFun.sub(di, ic).print(pic, out);
        out.println();

        out.println("n0 = B*t0 + e_n0");
        ni.print(pic, out);
        out.println();

        out.println("r0 = (3 - B*t0)/2 + e_r0");
        ri.print(pic, out);
        out.println();

        for (int i = 0; i < 4; i++) {
            ti = ri.mul(ri, ic, env).addErr("e_t" + (i + 1));
            env.put("e_t" + (i + 1), eWide);
            di = ri.mul(di, ic, env).addErr("e_d" + (i + 1));
            env.put("e_d" + (i + 1), eWide);
            ni = ti.mul(ni, ic, env);
            ri = c_1_5.sub(ni.mul(c_0_5, ic, env), ic).addErr("e_r" + (i + 1));
            env.put("e_r" + (i + 1), eWide);
            ni = ni.addErr("e_n" + (i + 1));
            env.put("e_n" + (i + 1), eWide);

            out.println("t" + (i + 1) + " = r" + i + "*r" + i + " + e_t" + (i + 1));
            ti.print(pic, out);
            out.println();

            out.println("d" + (i + 1) + " = d" + i + "*r" + i + " + e_d" + (i + 1));
            di.print(pic, out);
            out.println();
            out.println("diff=");
            Symbolic ddi = mathFun.sub(di, ic);
            ddi.print(pic, out);
            out.println();
            out.println("<<< " + ddi.monomials.size());
            System.out.println("<<< " + ddi.monomials.size());
            ddi.printMonomials(out);
            out.println(">>>");

            out.println("n" + (i + 1) + " = n" + i + "*t" + (i + 1) + " + e_n" + (i + 1));
            ni.print(pic, out);
            out.println();

            out.println("r" + (i + 1) + " = (3 - n" + i + "*t" + (i + 1) + ")/2 + e_r" + (i + 1));
            ri.print(pic, out);
            out.println();
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        try (PrintStream out = new PrintStream("div_u.txt")) {
            testDiv(out);
        }
        try (PrintStream out = new PrintStream("sqrt_u.txt")) {
            testSqrt(out);
        }
    }
}
