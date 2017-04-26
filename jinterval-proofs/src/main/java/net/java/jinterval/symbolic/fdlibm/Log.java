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
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;
import net.java.jinterval.symbolic.Symbolic;

/**
 * Error analysis of fdlibm log function
 */
public class Log {

    static final SetIntervalContext ic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY128);
    static final SetIntervalContext pic = SetIntervalContexts.getTightest(BinaryValueSet.BINARY80);
    static final SetInterval noErr = SetIntervalOps.nums2(0, 0);
    static final SetInterval err0 = SetIntervalOps.nums2(-0x1p-53, 0x1p-53);
    static final SetInterval err1 = SetIntervalOps.nums2(-0x1p-52, 0x1p-52);

    Map<String, SetInterval> env = new HashMap<String, SetInterval>();
    final Symbolic exactLog = Symbolic.valueOf(
            Rational.valueOf(0),
            Rational.valueOf(1),
            Rational.valueOf(-1, 2),
            Rational.valueOf(1, 3),
            Rational.valueOf(-1, 4),
            Rational.valueOf(1, 5)).addErr("e_trunc");

    {
        env.put("u", SetIntervalOps.nums2(-0x1p-20, 0x1p-20 - Math.ulp(1.0)));
//        env.put("u", SetIntervalOps.nums2(-0x1p-20, -0x1p-27));
//        env.put("u", SetIntervalOps.nums2(-0x1p-27, -0x1p-52));
//        env.put("u", SetIntervalOps.nums2(-0x1p-53, -0x1p-53));
//        env.put("u", SetIntervalOps.nums2(0x1p-52, 0x1p-52));
//        env.put("u", SetIntervalOps.nums2(0x1p-51, 0x1p-27));
//        env.put("u", SetIntervalOps.nums2(0x1p-27, 0x1p-20));
        System.out.println("u IN " + print(env.get("u")));
        Rational droppedCoeff = Rational.valueOf(-1, 6);
        env.put("e_trunc", ic.mul(
                ic.numsToInterval(droppedCoeff, droppedCoeff),
                ic.pown(env.get("u"), 6)));
        System.out.println("e_trunc IN " + print(env.get("e_trunc")));
    }

    final Symbolic ln2_hi = cnst(6.93147180369123816490e-01, 0x3fe62e42, 0xfee00000);
    final Symbolic ln2_lo = cnst(1.90821492927058770002e-10, 0x3dea39ef, 0x35793c76);
    final Symbolic two54 = cnst(1.80143985094819840000e+16, 0x43500000, 0x00000000);
    final Symbolic Lg1 = cnst(6.666666666666735130e-01, 0x3FE55555, 0x55555593);
    final Symbolic Lg2 = cnst(3.999999999940941908e-01, 0x3FD99999, 0x9997FA04);
    final Symbolic Lg3 = cnst(2.857142874366239149e-01, 0x3FD24924, 0x94229359);
    final Symbolic Lg4 = cnst(2.222219843214978396e-01, 0x3FCC71C5, 0x1D8E78AF);
    final Symbolic Lg5 = cnst(1.818357216161805012e-01, 0x3FC74664, 0x96CB03DE);
    final Symbolic Lg6 = cnst(1.531383769920937332e-01, 0x3FC39A09, 0xD078C69F);
    final Symbolic Lg7 = cnst(1.479819860511658591e-01, 0x3FC2F112, 0xDF3E5244);
    final Symbolic u = Symbolic.valueOf(1);
    final Symbolic x = Symbolic.valueOf(1, 1);
    final Symbolic f = x.sub(Symbolic.valueOf(1), ic); // f = x - 1; exactly
    final Symbolic f2 = addErr(f.mul(f, ic, env), "e_f2"); // f2 = f*f + e_f2
    final Symbolic f3 = addErr(Symbolic.valueOf(0.33333333333333333)
            .mul(f, ic, env), "e_f3"); // f3 = 0.33333333333333333*f + e_f3
    final Symbolic f4 = addErr(Symbolic.valueOf(0.5).sub(f3, ic), "e_f4"); // f4 = 0.5 - f3 + e_f4
    final Symbolic R = addErr(f2.mul(f4, ic, env), "e_R"); // R = f2*f4 + e_R
    final Symbolic R2 = f.sub(R, ic); // return f - R /* + e_R2 */;
    final Symbolic err = R2.sub(exactLog, ic);

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
            Rational halfUlp = Rational.exp2(exp - 53);
            err = SetIntervalOps.nums2(RationalOps.neg(halfUlp), halfUlp);
        }
        System.out.println(errName + " IN " + print(err));
        env.put(errName, err);
        return s.addErr(errName);
    }

    private void show(PrintStream out) {
        out.print("u ");
        u.print(ic, out);
        out.print("x ");
        x.print(ic, out);

        out.println("exactLog = log(x)");
        exactLog.print(ic, out);
        out.println("in " + print(exactLog.eval(ic, env)));
        out.println();

        out.println("f = x-1.0");
        f.print(ic, out);
        out.println("in " + print(f.eval(ic, env)));
        out.println();

        out.println("f2 = f*f");
        f2.print(ic, out);
        out.println("in " + print(f2.eval(ic, env)));
        out.println();

        out.println("f3 = 0.33333333333333333*f");
        f3.print(ic, out);
        out.println("in " + print(f3.eval(ic, env)));
        out.println();

        out.println("f4 = 0.5-f3");
        f4.print(ic, out);
        out.println("in " + print(f4.eval(ic, env)));
        out.println();

        out.println("R = f2*f4");
        R.print(ic, out);
        out.println("in " + print(R.eval(ic, env)));
        out.println();

        out.println("R2 = f-R");
        R2.print(ic, out);
        out.println("in " + print(R2.eval(ic, env)));
        out.println();

        out.println("err = R2 - exactLog");
        err.print(ic, out);
        out.println("in " + print(err.eval(ic, env)));
//        env.put("e_R2", noErr);
//        out.println("in " + print(err.eval(ic, env)));
        out.println();
    }

    private static String print(SetInterval x) {
        return pic.hull(x).toString();
    }

    public static final void main(String[] args) {
        new Log().show(System.out);
    }

}
