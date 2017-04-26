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
package net.java.jinterval.symbolic.amdk7;

import java.math.BigInteger;
import java.math.RoundingMode;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * FPU-MUL algorithm. Section 3.1 from D. Russinoff's paper:
 * http://www.russinoff.com/papers/k7-div-sqrt.html
 */
public class FpuMul {

    public final int M;
    public final MultiplierOp op;
    public final int pc;
    public final int lastpc;
    public final RoundingControl rc;
    public final FpEncoding x;
    public final FpEncoding y;
    public final FpEncoding z;
    public final FpEncoding r;
    public final FpEncoding d;
    public final boolean inexact;
    final boolean sign;
    final BigInteger manUnrounded;
    final boolean overflow;
    final boolean sticky;
    final BigInteger rconst;
    final BigInteger add;
    final boolean roundCarryout;
    final BigInteger trunc;
    final BigInteger manRounded;
    final int expUnrounded;
    final int expRounded;

    private static BigInteger comp1(BigInteger x, int n) {
        return BigInteger.ONE.shiftLeft(n).subtract(x).subtract(BigInteger.ONE);
    }

    private static int lsb(int M, int pc) {
        return 2 * M - pc;
    }

    public FpuMul(int M, MultiplierOp op, int pc, int lastpc, RoundingControl rc,
            FpEncoding x, FpEncoding y, FpEncoding d) {
        this.M = M;
        this.op = op;
        this.pc = pc;
        this.lastpc = lastpc;
        this.rc = rc;
        this.x = x;
        this.y = y;
        this.d = d;

        sign = x.sgn ^ y.sgn;
        manUnrounded = x.sig.multiply(y.sig);
        overflow = manUnrounded.testBit(2 * M - 1);
        int lsb = lsb(M, pc);
        boolean stickyNoOverflow = manUnrounded.mod(BigInteger.ONE.shiftLeft(lsb - 2)).signum() != 0;
        boolean stickyWithOverflow = stickyNoOverflow || manUnrounded.testBit(lsb - 2);
        sticky = overflow ? stickyWithOverflow : stickyNoOverflow;
        boolean inexactNoOverflow = stickyWithOverflow;
        boolean inexactWithOverflow = inexactNoOverflow || manUnrounded.testBit(lsb - 1);
        inexact = overflow ? inexactWithOverflow : inexactNoOverflow;
        BigInteger rconstWithOverflow;
        if (op == MultiplierOp.OpBack) {
            rconstWithOverflow = comp1(d.sig.shiftLeft(M), 2 * M);
        } else if (op == MultiplierOp.OpLast) {
            rconstWithOverflow = BigInteger.ONE.shiftLeft(lsb(lastpc, M) - 2);
        } else if (rc == RoundingControl.RcNear) {
            rconstWithOverflow = BigInteger.ONE.shiftLeft(lsb - 1);
        } else if (rc == (sign ? RoundingControl.RcNeg : RoundingControl.RcPos)) {
            rconstWithOverflow = BigInteger.ONE.shiftLeft(lsb).subtract(BigInteger.ONE);
        } else {
            rconstWithOverflow = BigInteger.ZERO;
        }
        BigInteger rconstNoOverflow = rconstWithOverflow.shiftRight(1);
        rconst = overflow ? rconstWithOverflow : rconstNoOverflow;
        BigInteger addWithOverflow = manUnrounded.add(rconstWithOverflow);
        BigInteger addNoOverflow = manUnrounded.add(rconstNoOverflow);
        if (op == MultiplierOp.OpBack) {
            addWithOverflow = addWithOverflow.add(BigInteger.ONE);
            addNoOverflow = addNoOverflow.add(BigInteger.ONE);
        }
        addWithOverflow = addWithOverflow.mod(BigInteger.ONE.shiftLeft(2 * M + 1));
        addNoOverflow = addNoOverflow.mod(BigInteger.ONE.shiftLeft(2 * M));
        add = overflow ? addWithOverflow : addNoOverflow;
        boolean roundCarryoutNoOverflow = addNoOverflow.testBit(2 * M - 1);
        boolean roundCarryoutWithOverflow = addWithOverflow.testBit(2 * M);
        roundCarryout = overflow ? roundCarryoutWithOverflow : roundCarryoutNoOverflow;
        BigInteger truncWithOverflow, truncNoOverflow;
        if (op == MultiplierOp.OpLast) {
            truncWithOverflow = BigInteger.ONE.shiftLeft(2 * M).
                    subtract(BigInteger.ONE.shiftLeft(lsb(lastpc, M) - 1));
            truncNoOverflow = BigInteger.ONE.shiftLeft(2 * M).
                    subtract(BigInteger.ONE.shiftLeft(lsb(lastpc, M) - 2));
        } else {
            truncWithOverflow = BigInteger.ONE.shiftLeft(2 * M).
                    subtract(BigInteger.ONE.shiftLeft(lsb));
            truncNoOverflow = BigInteger.ONE.shiftLeft(2 * M).
                    subtract(BigInteger.ONE.shiftLeft(lsb - 1));
        }
        trunc = overflow ? truncWithOverflow : truncNoOverflow;

        BigInteger manRoundedNoOverflow = addNoOverflow;
        if (roundCarryoutNoOverflow) {
            manRoundedNoOverflow = manRoundedNoOverflow.setBit(2 * M - 2);
        }
        manRoundedNoOverflow = manRoundedNoOverflow.and(truncNoOverflow);
        if (rc == RoundingControl.RcNear && !stickyNoOverflow && !addNoOverflow.testBit(lsb - 2)) {
            manRoundedNoOverflow = manRoundedNoOverflow.
                    and(BigInteger.ONE.shiftLeft(2 * M).subtract(BigInteger.ONE).subtract(BigInteger.ONE.shiftLeft(lsb - 1)));
        }

        BigInteger manRoundedWithOverflow = addWithOverflow;
        if (roundCarryoutWithOverflow) {
            manRoundedWithOverflow = manRoundedWithOverflow.setBit(2 * M - 2);
        }
        manRoundedWithOverflow = manRoundedWithOverflow.and(truncWithOverflow);
        if (rc == RoundingControl.RcNear && !stickyWithOverflow && !addWithOverflow.testBit(lsb - 1)) {
            manRoundedWithOverflow = manRoundedWithOverflow.
                    and(BigInteger.ONE.shiftLeft(2 * M).subtract(BigInteger.ONE).subtract(BigInteger.ONE.shiftLeft(lsb)));
        }
        manRounded = overflow ? manRoundedWithOverflow : manRoundedNoOverflow;

        expUnrounded = (x.expo + y.expo + FpEncoding.BIAS + 2) & FpEncoding.EXP_MASK;
        int expRoundedWithOverflow = (expUnrounded + (roundCarryoutWithOverflow ? 2 : 1)) & FpEncoding.EXP_MASK;
        int expRoundedNoOverflow = (expUnrounded + (roundCarryoutNoOverflow ? 1 : 0)) & FpEncoding.EXP_MASK;
        expRounded = overflow ? expRoundedWithOverflow : expRoundedNoOverflow;

        if (x.sig.signum() == 0) {
            z = new FpEncoding(M, sign, BigInteger.ZERO, x.expo);
        } else if (y.sig.signum() == 0) {
            z = new FpEncoding(M, sign, BigInteger.ZERO, y.expo);
        } else if (overflow) {
            z = new FpEncoding(M, sign, manRoundedWithOverflow.shiftRight(M), expRoundedWithOverflow);
        } else {
            z = new FpEncoding(M, sign, manRoundedNoOverflow.shiftRight(M - 1), expRoundedNoOverflow);
        }

        BigInteger maskM = BigInteger.ONE.shiftLeft(M).subtract(BigInteger.ONE);
        if (op == MultiplierOp.OpDiv) {
            if (overflow) {
                r = new FpEncoding(M, false, comp1(manUnrounded, 2 * M).shiftRight(M - 1).and(maskM), FpEncoding.BIAS - 1);
            } else if (!roundCarryoutNoOverflow) {
                r = new FpEncoding(M, false, comp1(manUnrounded, 2 * M).shiftRight(M).and(maskM), FpEncoding.BIAS);
            } else {
                r = new FpEncoding(M, false, maskM, FpEncoding.BIAS - 1);
            }
        } else if (op == MultiplierOp.OpSqrt) {
            if (overflow) {
                r = new FpEncoding(M, false, comp1(manUnrounded, 2 * M).shiftRight(M).and(maskM).setBit(M - 1), FpEncoding.BIAS - 1);
            } else if (!roundCarryoutNoOverflow) {
                r = new FpEncoding(M, false, comp1(manUnrounded, 2 * M).shiftRight(M + 1).and(maskM).setBit(M - 1).clearBit(M - 2), FpEncoding.BIAS);
            } else {
                r = new FpEncoding(M, false, maskM, FpEncoding.BIAS - 1);
            }
        } else {
            r = null;
        }
        check();
    }

    void check() {
        Rational xr = x.rationalValue();
        Rational yr = y.rationalValue();
        Rational exactZ = RationalOps.mul(xr, yr);
        if (exactZ.signum() == 0) {
            assert !overflow;
        } else {
            assert exactZ.intFloorLog2() == xr.intFloorLog2() + yr.intFloorLog2() + (overflow ? 1 : 0);
        }
        assert exactZ.getDenominatorWithout2s().equals(BigInteger.ONE);
        int prec = exactZ.getNumeratorWithout2s().abs().bitLength();
        assert sticky == prec > pc + 1;
        assert inexact == prec > pc;
        int P = overflow ? 2 * M : 2 * M - 1;
        BigInteger exactP = exactZ.getNumeratorWithout2s().abs().shiftLeft(P - prec);
        if (op == MultiplierOp.OpBack) {
            assert rconst.equals(BigInteger.ONE.shiftLeft(P).subtract(d.sig.shiftLeft(P - M)).subtract(BigInteger.ONE));
            assert add.equals(BigInteger.ONE.shiftLeft(P).add(add).subtract(d.sig.shiftLeft(P - M)));
        } else if (op == MultiplierOp.OpLast) {
            assert rconst.equals(BigInteger.ONE.shiftLeft(P - lastpc - 2));
            assert add.equals(exactP.add(BigInteger.ONE.shiftLeft(P - lastpc - 2)));
        } else if (rc == RoundingControl.RcNear) {
            assert rconst.equals(BigInteger.ONE.shiftLeft(P - pc - 1));
            assert add.equals(exactP.add(BigInteger.ONE.shiftLeft(P - pc - 1)));
        } else if (rc == (sign ? RoundingControl.RcNeg : RoundingControl.RcPos)) {
            assert rconst.equals(BigInteger.ONE.shiftLeft(P - pc).subtract(BigInteger.ONE));
            assert add.equals(exactP.add(BigInteger.ONE.shiftLeft(P - pc).subtract(BigInteger.ONE)));
        } else {
            assert rconst.equals(BigInteger.ZERO);
            assert add.equals(exactP);
        }
        assert roundCarryout == add.testBit(P);
        int roundPrec = op == MultiplierOp.OpLast ? lastpc + 1 : pc;
        assert trunc.equals(BigInteger.ONE.shiftLeft(2 * M).
                subtract(BigInteger.ONE.shiftLeft(P - roundPrec)));
        BinaryValueSet valueSet = new BinaryValueSet(roundPrec);
        Rational roundedZ = (Rational) ExtendedRationalContexts.valueOf(valueSet, rc.roundingMode).rnd(exactZ);
        if (op == MultiplierOp.OpLast && rc == RoundingControl.RcNear) {
            Rational roundedAway = (Rational) ExtendedRationalContexts.valueOf(valueSet, RoundingMode.HALF_UP).rnd(exactZ);
            if (!roundedZ.eq(roundedAway) && prec <= pc) {
                roundedZ = roundedAway;
            }
        }
        assert z.rationalValue().equals(roundedZ);
        if (op == MultiplierOp.OpDiv || op == MultiplierOp.OpSqrt) {
            assert exactZ.ge(Rational.valueOf(1.5)) || exactZ.lt(Rational.valueOf(3));
            Rational exactR;
            switch (op) {
                case OpDiv:
                    exactR = RationalOps.sub(Rational.valueOf(2), exactZ);
                    break;
                case OpSqrt:
                    exactR = RationalOps.div(RationalOps.sub(Rational.valueOf(3), exactZ), Rational.valueOf(2));
                    break;
                default:
                    throw new AssertionError();
            }
            BinaryValueSet valueSetR = new BinaryValueSet(M);
            Rational roundedR = (Rational) ExtendedRationalContexts.valueOf(valueSetR, RoundingMode.FLOOR).rnd(exactR);
            if (roundedR.eq(exactR)) {
                Rational ulp = (Rational) valueSetR.ulp(roundedR);
                if (prec == 1) {
                    assert exactR.equals(Rational.one());
                    ulp = RationalOps.div(ulp, Rational.valueOf(2));
                }
                roundedR = RationalOps.sub(roundedR, ulp);
            }
            assert r.rationalValue().equals(roundedR);
        } else {
            assert r == null;
        }
    }

    public static void main(String[] args) {
        int M = 76;
        FpEncoding x = new FpEncoding(M, false, BigInteger.valueOf(3).shiftLeft(M - 2).add(BigInteger.ONE.shiftLeft(M - 54)), FpEncoding.BIAS);
        FpEncoding y = new FpEncoding(M, false, BigInteger.valueOf(3).shiftLeft(M - 2), FpEncoding.BIAS - 1);
        System.out.println("x = " + x.rationalValue());
        System.out.println("y = " + y.rationalValue());
        FpuMul res = new FpuMul(M, MultiplierOp.OpDiv, 53, -1, RoundingControl.RcPos, x, y, null);
        System.out.println("z = " + res.z.rationalValue());
        if (res.r != null) {
            System.out.println("r = " + res.r.rationalValue());
        }
    }
}
