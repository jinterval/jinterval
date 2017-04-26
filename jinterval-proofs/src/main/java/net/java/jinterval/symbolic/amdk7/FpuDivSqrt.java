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
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * FPU-DIV-SQRT algorithm. Section 4.1 from D. Russinoff's paper:
 * http://www.russinoff.com/papers/k7-div-sqrt.html
 */
public class FpuDivSqrt {

    public final int M;
    public final MultiplierOp op;
    public final int pc;
    public final RoundingControl rc;
    public final FpEncoding a;
    public final FpEncoding b;
    public final FpEncoding estimate;
    public final boolean sign;
    public final FpuMul[] n;
    public final FpuMul[] t;
    public final FpuMul[] d;
    public final FpuMul last;
    public final Rational qExact;
    public final FpEncoding q;
    public final FpuMul back;
    public final FpEncoding rem;
    public final boolean remZero;
    public final boolean remNeg;
    public final boolean remPos;
    public final boolean qLsb;
    public final boolean qGuard;
    public final FpEncoding z;

    /**
     * Div
     *
     * @param M
     * @param a
     * @param b
     * @param estimate
     */
    public FpuDivSqrt(int M, int pc, RoundingControl rc, FpEncoding a, FpEncoding b, FpEncoding estimate, int nIter) {
        this.M = M;
        this.op = MultiplierOp.OpDiv;
        this.pc = pc;
        this.rc = rc;
        this.a = a;
        this.b = b;
        this.estimate = estimate;
        sign = a.sgn ^ b.sgn;
        assert nIter > 0;
        n = new FpuMul[nIter];
        t = null;
        d = new FpuMul[nIter];
        FpEncoding ni = a;
        FpEncoding di = b;
        FpEncoding ri = estimate;
        for (int i = 0; i < nIter; i++) {
            d[i] = new FpuMul(M, MultiplierOp.OpDiv, M, -1, RoundingControl.RcNear, di, ri, null);
            n[i] = new FpuMul(M, MultiplierOp.OpMul, M, -1, RoundingControl.RcNear, ni, ri, null);
            di = d[i].z;
            ri = d[i].r;
            ni = n[i].z;
        }
        last = new FpuMul(M, MultiplierOp.OpLast, M, pc, RoundingControl.RcNear, ni, ri, null);
        qExact = RationalOps.mul(ni.rationalValue(), ri.rationalValue());
        q = last.z;
        back = new FpuMul(M, MultiplierOp.OpBack, M, -1, RoundingControl.RcChop, b, q, a);
        rem = back.r;
        remZero = !back.inexact;
        remNeg = !rem.sig.testBit(M - 2) && !remZero;
        remPos = rem.sig.testBit(M - 2);
        qLsb = q.sig.testBit(M - pc);
        qGuard = q.sig.testBit(M - pc - 1);
        z = round();
    }

    /**
     * Sqrt
     *
     * @param M
     * @param b
     * @param estimate
     */
    public FpuDivSqrt(int M, int pc, RoundingControl rc, FpEncoding b, FpEncoding estimate, int nIter) {
        this.M = M;
        this.op = MultiplierOp.OpSqrt;
        this.pc = pc;
        this.rc = rc;
        this.a = null;
        this.b = b;
        this.estimate = estimate;
        sign = false;
        assert nIter > 0;
        n = new FpuMul[nIter];
        t = new FpuMul[nIter];
        d = new FpuMul[nIter];
        FpEncoding ni = b;
        FpEncoding di = b;
        FpEncoding ri = estimate;
        for (int i = 0; i < nIter; i++) {
            t[i] = new FpuMul(M, MultiplierOp.OpMul, M, -1, RoundingControl.RcNear, ri, ri, null);
            d[i] = new FpuMul(M, MultiplierOp.OpMul, M, -1, RoundingControl.RcNear, di, ri, null);
            n[i] = new FpuMul(M, MultiplierOp.OpSqrt, M, -1, RoundingControl.RcNear, ni, t[i].z, null);
            di = d[i].z;
            ri = n[i].r;
            ni = n[i].z;
        }
        last = new FpuMul(M, MultiplierOp.OpLast, M, pc, RoundingControl.RcNear, di, ri, null);
        qExact = RationalOps.mul(di.rationalValue(), ri.rationalValue());
        q = last.z;
        back = new FpuMul(M, MultiplierOp.OpBack, M, -1, RoundingControl.RcChop, q, q, b);
        rem = back.r;
        remZero = !back.inexact;
        remNeg = !rem.sig.testBit(M - 2) && !remZero;
        remPos = rem.sig.testBit(M - 2);
        qLsb = q.sig.testBit(M - pc);
        qGuard = q.sig.testBit(M - pc - 1);
        z = round();
    }

    private FpEncoding round() {
        BigInteger maskM = BigInteger.ONE.shiftLeft(M).subtract(BigInteger.ONE.shiftLeft(M - pc));
        if (op == MultiplierOp.OpDiv && a.sig.signum() == 0) {
            return new FpEncoding(M, sign, BigInteger.ZERO, a.expo);
        } else if (op == MultiplierOp.OpSqrt && b.sig.signum() == 0) {
            return new FpEncoding(M, sign, BigInteger.ZERO, b.expo);
        } else if ((rc == RoundingControl.RcPos && sign || rc == RoundingControl.RcNeg && !sign || rc == RoundingControl.RcChop)
                && !qGuard && remNeg) {
            if (q.sig.and(maskM).equals(BigInteger.ONE.shiftLeft(M - 1))) {
                return new FpEncoding(M, sign, maskM, q.expo - 1);
            } else {
                return new FpEncoding(M, sign, q.sig.and(maskM).add(maskM).clearBit(M), q.expo);
            }
        } else if ((rc == RoundingControl.RcPos && !sign || rc == RoundingControl.RcNeg && sign) && (qGuard || remPos)
                || rc == RoundingControl.RcNear && qGuard && remPos
                || rc == RoundingControl.RcNear && qGuard && remZero && qLsb) {
        } else if (q.sig.and(maskM).equals(maskM)) {
            return new FpEncoding(M, sign, BigInteger.ONE.shiftLeft(M - 1), q.expo + 1);
        } else {
            return new FpEncoding(M, sign, q.sig.and(maskM).add(BigInteger.ONE.shiftLeft(M - pc)).clearBit(M), q.expo);
        }
        return new FpEncoding(M, sign, q.sig.and(maskM), q.expo);
    }
}
