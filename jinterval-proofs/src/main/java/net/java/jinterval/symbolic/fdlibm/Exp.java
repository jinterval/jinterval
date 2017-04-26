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

import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;
import net.java.jinterval.symbolic.Symbolic;
import sun.misc.DoubleConsts;

/* Ctanh(x) = 1/x + x/3 - x^3/45 + ...
 *  +   (-1)^(n-1) * 2^(2*n) * B(2*n) / (2*n)! * x^(2*n-1)
 *
 */
/**
 * Error analysis of fdlibm log function
 */
public class Exp {

    static final SetIntervalContext ic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY128);
    static final SetIntervalContext pic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY80);
    static final SetInterval noErr = SetIntervalOps.nums2(0, 0);

    /**
     * Calcualte (n*2)-th Taylor coefficient of x*coth(x/2)
     *
     * @param n index of coefficient
     * @return coefficient
     */
    private static Rational calcR(int n) {
        /**
         * coth(x) = 1/x + x/3 - x^3/45 + 2^(2*n) * B(2*n) / (2*n)! * x^(2*n-1)
         * Return x*coth(x/2)
         */
        Rational result = RationalOps.mul(Rational.valueOf(2),
                BernoulliNumbers.getBernoulliNumber(2 * n));
        for (int i = 1; i <= n * 2; i++) {
            result = RationalOps.div(result, Rational.valueOf(i));
        }
        return result;
    }

    Map<String, SetInterval> env = new HashMap<String, SetInterval>();
//    SetInterval xi = SetIntervalOps.nums2(0x1p-28, 0x1.62e41ffffffffp-2);
//    SetInterval xi = SetIntervalOps.nums2(0x1.62e41ffffffffp-2, 0x1.62e41ffffffffp-2);
    SetInterval xi = SetIntervalOps.nums2(0x1.0ba55f673d19p-2, 0x1.62e41ffffffffp-2);
//     SetInterval xi = SetIntervalOps.nums2(0x1p-28, 0x1.0ba55f673d18p-2);

    Rational x0 = xi.mid();
//    Rational x0 = Rational.zero();
    SetInterval x0i = SetIntervalOps.nums2(x0, x0);
    Symbolic x = Symbolic.valueOf(x0, Rational.one());
    int tailN = 10;
    Rational droppedCoeff = calcR(tailN);
    Symbolic exactR = Symbolic.valueOf(0);
    {
        env.put("u", ic.sub(xi, x0i));
        System.out.println("u IN " + print(env.get("u")));
        for (int n = tailN -1; n >= 0; n--) {
            exactR = exactR.mul(x, ic, env);
            exactR = exactR.mul(x, ic, env);
            exactR = exactR.add(Symbolic.valueOf(calcR(n)), ic);
        }
        exactR = exactR.addErr("e_truncR");
        env.put("e_truncR", ic.mul(
                ic.numsToInterval(droppedCoeff, droppedCoeff),
                ic.pown(xi, 2*tailN)));
        System.out.println("e_truncR IN " + print(env.get("e_truncR")));
    }
    final Symbolic exactCT1 = exactR.sub(Symbolic.valueOf(2), ic);
    final Symbolic exactC = x.sub(exactCT1, ic);
    
    final Symbolic one = Symbolic.valueOf(1.0);
    final Symbolic[] halF = {Symbolic.valueOf(0.5), Symbolic.valueOf(-0.5)};
    final Symbolic huge = Symbolic.valueOf(1.0e+300);
    final Symbolic o_threshold = cnst(7.09782712893383973096e+02, 0x40862E42, 0xFEFA39EF);
    final Symbolic u_threshold = cnst(-7.45133219101941108420e+02, 0xc0874910, 0xD52D3051);
    final Symbolic[] ln2HI = {
        cnst(6.93147180369123816490e-01, 0x3fe62e42, 0xfee00000),
        cnst(-6.93147180369123816490e-01, 0xbfe62e42, 0xfee00000)
    };
    final Symbolic[] ln2LO = {
        cnst(1.90821492927058770002e-10, 0x3dea39ef, 0x35793c76),
        cnst(-1.90821492927058770002e-10, 0xbdea39ef, 0x35793c76)
    };
    final Symbolic invln2 = cnst(1.44269504088896338700e+00, 0x3ff71547, 0x652b82fe);
    final Symbolic P1 = cnst(1.66666666666666019037e-01, 0x3FC55555, 0x5555553E);
    final Symbolic P2 = cnst(-2.77777777770155933842e-03, 0xBF66C16C, 0x16BEBD93);
    final Symbolic P3 = cnst(6.61375632143793436117e-05, 0x3F11566A, 0xAF25DE2C);
    final Symbolic P4 = cnst(-1.65339022054652515390e-06, 0xBEBBBD41, 0xC5D26BF1);
    final Symbolic P5 = cnst(4.13813679705723846039e-08, 0x3E663769, 0x72BEA4D0);

    final Symbolic t = addErr(x.mul(x, ic, env), "e_t"); // t=x*x
    final Symbolic ct5 = addErr(t.mul(P5, ic, env), "e_ct5"); // ct5=t*P5
    final Symbolic c4 = addErr(P4.add(ct5, ic), "e_c4"); // c4=P4+ct5
    final Symbolic ct4 = addErr(t.mul(c4, ic, env), "e_ct4"); // ct4=t*c4
    final Symbolic c3 = addErr(P3.add(ct4, ic), "e_c3"); // c3=P3+ct4
    final Symbolic ct3 = addErr(t.mul(c3, ic, env), "e_ct3"); // ct3=t*c3
    final Symbolic c2 = addErr(P2.add(ct3, ic), "e_c2"); // c2=P2+ct3
    final Symbolic ct2 = addErr(t.mul(c2, ic, env), "e_ct2"); // ct2=t*c2
    final Symbolic c1 = addErr(P1.add(ct2, ic), "e_c1"); // c1=P1+ct2
    final Symbolic ct1 = addErr(t.mul(c1, ic, env), "e_ct1"); // ct1=t*c1
    final Symbolic c = addErr(x.sub(ct1, ic), "e_c"); // c=x-ct1

    final Symbolic errCT1 = ct1.sub(exactCT1, ic);
    final Symbolic errC = c.sub(exactC, ic);

    private static Symbolic cnst(double v, int hi, int lo) {
        long vbits = Double.doubleToRawLongBits(v);
        assert hi == vbits >> 32;
        assert lo == (int) vbits;
        return Symbolic.valueOf(v);
    }

    private Symbolic addErr(Symbolic s, String errName) {
        SetInterval si = s.eval(ic, env);
        ExtendedRational mag = si.mag();
        assert mag.isFinite();
        SetInterval err;
        if (mag.signum() == 0) {
            err = noErr;
        } else {
            int exp = mag.intFloorLog2();
            assert exp <= Double.MAX_EXPONENT;
            exp = Math.max(exp, Double.MIN_EXPONENT);
            Rational halfUlp = Rational.exp2(exp - DoubleConsts.SIGNIFICAND_WIDTH);
            err = SetIntervalOps.nums2(RationalOps.neg(halfUlp), halfUlp);
        }
        System.out.println(errName + " IN " + print(err));
        env.put(errName, err);
        return s.addErr(errName);
    }

    private void show(PrintStream out) {
        out.print("x ");
        x.print(ic, out);
        out.println("in " + print(x.eval(ic, env)));
        out.println();

        out.println("exactR = x*arccoth(x/2)");
        exactR.print(pic, out);
        out.println("in " + print(exactR.eval(ic, env)));
        out.println();

        out.println("exactCT1 = exactR - 2");
        exactCT1.print(pic, out);
        out.println("in " + print(exactCT1.eval(ic, env)));
        out.println();

        out.println("exactC = x - exactCT1");
        exactC.print(pic, out);
        out.println("in " + print(exactC.eval(ic, env)));
        out.println();

        out.println("t = x*x");
        t.print(pic, out);
        out.println("in " + print(t.eval(ic, env)));
        out.println();

        out.println("ct5 = t*P5");
        ct5.print(pic, out);
        out.println("in " + print(ct5.eval(ic, env)));
        out.println();

        out.println("c4 = P4+ct5");
        c4.print(pic, out);
        out.println("in " + print(c4.eval(ic, env)));
        out.println();

        out.println("ct4 = t*c4");
        ct4.print(pic, out);
        out.println("in " + print(ct4.eval(ic, env)));
        out.println();

        out.println("c3 = P3+ct4");
        c3.print(pic, out);
        out.println("in " + print(c3.eval(ic, env)));
        out.println();

        out.println("ct3 = t*c3");
        ct3.print(pic, out);
        out.println("in " + print(ct3.eval(ic, env)));
        out.println();

        out.println("c2 = P2+ct3");
        c2.print(pic, out);
        out.println("in " + print(c2.eval(ic, env)));
        out.println();

        out.println("ct2 = t*c2");
        ct2.print(pic, out);
        out.println("in " + print(ct2.eval(ic, env)));
        out.println();

        out.println("c1 = P1+ct2");
        c1.print(pic, out);
        out.println("in " + print(c1.eval(ic, env)));
        out.println();

        out.println("ct1 = t*c1");
        ct1.print(pic, out);
        out.println("in " + print(ct1.eval(ic, env)));
        out.println();

        out.println("errCT1 = ct1 - exactCT1");
        errCT1.print(pic, out);
        out.println("in " + print(errCT1.eval(ic, env)));
        out.println();

        out.println("c = x-ct1");
        c.print(pic, out);
        out.println("in " + print(c.eval(ic, env)));
        out.println();

        out.println("errC = c - exactC");
        errC.print(pic, out);
        out.println("in " + print(errC.eval(ic, env)));
        out.println();
    }

    private static String print(SetInterval x) {
        return pic.hull(x).toString();
    }

    public static final void main(String[] args) {
        new Exp().show(System.out);
    }

}
/*
env.put("u", SetIntervalOps.nums2(0x1.62e41ffffffffp-2, 0x1.62e41ffffffffp-2));

ct1 = t*c1
= +0x1.555555555553ep-3*u^2 -0x1.6c16c16bebd93p-9*u^4 +0x1.1566aaf25de2cp-14*u^6 -0x1.bbd41c5d26bf1p-20*u^8 +0x1.6376972bea4dp-25*u^10
+ e_t*(0x1.555555555553ep-3 -0x1.6c16c16bebd93p-8*u^2 +0x1.a01a006b8cd42p-13*u^4 -0x1.bbd41c5d26bf1p-18*u^6 +0x1.bc543cf6e4e04p-23*u^8)
+ e_ct5*(+1*u^8)
+ e_c4*(+1*u^8)
+ e_ct4*(+1*u^6)
+ e_c3*(+1*u^6)
+ e_ct3*(+1*u^4)
+ e_c2*(+1*u^4)
+ e_ct2*(+1*u^2)
+ e_c1*(+1*u^2)
+ e_ct1*(1)
+ [-0x1.01d31b6fc44702c8p-112,0x1.01d31b6fc44702c8p-112]
in [0x1.4755868d6a4c8cfap-6,0x1.4755868d6a4cb70ap-6]

errCT1 = ct1 - exactCT1
= -35/54043195528445952*u^2 +7908649/103762935414616227840*u^4 -50957498341/17432173149655526277120*u^6 +1091848520972507/22313181631559073634713600*u^8 -328828951704499817/883601992609739315934658560*u^10 +691/653837184000*u^12 -1/37362124800*u^14 +3617/5335311421440000*u^16 -43867/2554547108585472000*u^18
+ e_t*(0x1.555555555553ep-3 -0x1.6c16c16bebd93p-8*u^2 +0x1.a01a006b8cd42p-13*u^4 -0x1.bbd41c5d26bf1p-18*u^6 +0x1.bc543cf6e4e04p-23*u^8)
+ e_ct5*(+1*u^8)
+ e_c4*(+1*u^8)
+ e_ct4*(+1*u^6)
+ e_c3*(+1*u^6)
+ e_ct3*(+1*u^4)
+ e_c2*(+1*u^4)
+ e_ct2*(+1*u^2)
+ e_c1*(+1*u^2)
+ e_ct1*(1)
+ e_truncC*(-1)
+ [-0x1.01d31b6fc44702c8p-112,0x1.01d31b6fc44702c8p-112]
in [-0x1.d8db118623e4e61cp-59,0x1.b47ee4c7022146dcp-58]
*/
