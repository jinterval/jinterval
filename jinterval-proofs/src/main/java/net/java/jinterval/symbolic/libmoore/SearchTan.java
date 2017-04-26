package net.java.jinterval.symbolic.libmoore;

import java.math.BigInteger;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;

public class SearchTan {

    static void showTan(int p) {
        BinaryValueSet valueSet = new BinaryValueSet(p);
        ExtendedRationalContext rcDn = ExtendedRationalContexts.mkFloor(valueSet);
        ExtendedRationalContext rcUp = ExtendedRationalContexts.mkCeiling(valueSet);
        ExtendedRationalContext rc2 = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY512);
        ExtendedRational pi = rc2.pi();
        ExtendedRational pi_up = rcUp.rnd(pi);
        ExtendedRational pi_1_2 = rc2.mul(pi, Rational.valueOf(0.5));
        ExtendedRational xi = rcUp.mul(pi, Rational.valueOf(0.5));
        ExtendedRational pi_3_2 = rc2.mul(pi, Rational.valueOf(1.5));
        ExtendedRational xs = rcDn.mul(pi, Rational.valueOf(1.5));
        ExtendedRational xdiff = rcUp.sub(xs, xi);
        SetIntervalContext ic = SetIntervalContexts.getTightest(valueSet);
        SetInterval x = ic.numsToInterval(xi, xs);
        ExtendedRational wid = x.wid(valueSet);
        SetInterval tan = ic.tan(x);
        System.out.println("  pi    =" + pi);
        System.out.println("  pi_up =" + pi_up);
        System.out.println("  1/2*pi=" + pi_1_2);
        System.out.println("  xi    =" + xi);
        System.out.println("  3/2*pi=" + pi_3_2);
        System.out.println("  xs    =" + xs);
        System.out.println("  x2-x1 =" + xdiff);
        System.out.println("  x     =" + x);
        System.out.println("  wid(x)=" + wid);
        System.out.println("  tan(x)=" + tan);

    }

    public static void main(String[] args) {
        ExtendedRationalContext rc2 = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY1024);
        ExtendedRational x;
        for (int p = 128; p < 256; p++) {
            x = rc2.pi();
            Rational scale = Rational.valueOf(BigInteger.valueOf(3), p - 2);
            x = rc2.mul(x, scale);
            x = ExtendedRationalOps.ceil(x);
            BigInteger bx = x.toBigInteger();
            BigInteger bxmod = bx.mod(BigInteger.valueOf(12));
            System.out.println("p=" + p + " " + bxmod + " " + Rational.valueOf(bx, 1 - p));
            if (bxmod.equals(BigInteger.valueOf(9))) {
                showTan(p);
            }
        }
    }
}
