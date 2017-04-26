/*
 * Copyright (c) 2016, JInterval Project.
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
package net.java.jinterval.interval.set;

import java.math.BigInteger;
import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.rational.Rational;

/**
 *
 */
class SetIntervalEvaluatorGeneric extends SetIntervalEvaluator {

    private final SetIntervalContext ic;
    private final SetInterval[] regs;

    SetIntervalEvaluatorGeneric(SetIntervalContext ic, CodeList codeList, Expression[] results) {
        super(codeList, results);
        this.ic = ic;
        regs = new SetInterval[codeList.getNumExprs()];
        codeList.acceptConstants(this);
    }

    SetIntervalEvaluatorGeneric(SetIntervalContext ic, int size) {
        this.ic = ic;
        regs = new SetInterval[size];
    }

    @Override
    public SetInterval get(int i) {
        return regs[i];
    }

    @Override
    public void set(int i, SetInterval v) {
        regs[i] = v;
    }

    @Override
    public void visitInp(int r, String name) {
    }

    @Override
    public void visitLit(int r, String numerator, String denominator) {
        regs[r] = ic.textToInterval("[" + numerator + "/" + denominator + "]");
    }

    @Override
    public void visitLit(int r, String literal) {
        regs[r] = ic.textToInterval("[" + literal + "]");
    }

    @Override
    public void visitInterval(int r, String inf, String sup) {
        regs[r] = ic.textToInterval("[" + inf + "," + sup + "]");
    }

    @Override
    public void visitNum(int r, Number num) {
        Rational rat = Rational.valueOf(num);
        regs[r] = ic.numsToInterval(rat, rat);
    }

    @Override
    public void visitPi(int r) {
        regs[r] = ic.pi();
    }

    @Override
    public void visitEuler(int r) {
        regs[r] = ic.euler();
    }

    @Override
    public void visitNeg(int r, int x) {
        regs[r] = ic.neg(regs[x]);
    }

    @Override
    public void visitAdd(int r, int x, int y) {
        regs[r] = ic.add(regs[x], regs[y]);
    }

    @Override
    public void visitSub(int r, int x, int y) {
        regs[r] = ic.sub(regs[x], regs[y]);
    }

    @Override
    public void visitMul(int r, int x, int y) {
        regs[r] = ic.mul(regs[x], regs[y]);
    }

    @Override
    public void visitDiv(int r, int x, int y) {
        regs[r] = ic.div(regs[x], regs[y]);
    }

    @Override
    public void visitRecip(int r, int x) {
        regs[r] = ic.recip(regs[x]);
    }

    @Override
    public void visitSqr(int r, int x) {
        regs[r] = ic.sqr(regs[x]);
    }

    @Override
    public void visitSqrt(int r, int x) {
        regs[r] = ic.sqrt(regs[x]);
    }

    @Override
    public void visitFma(int r, int x, int y, int z) {
        regs[r] = ic.fma(regs[x], regs[y], regs[z]);
    }

    @Override
    public void visitPown(int r, int x, int p) {
        regs[r] = ic.pown(regs[x], p);
    }

    @Override
    public void visitPown(int r, int x, BigInteger p) {
        regs[r] = ic.pown(regs[x], p);
    }

    @Override
    public void visitPown(int r, int x, long p) {
        regs[r] = ic.pown(regs[x], p);
    }

    @Override
    public void visitPow(int r, int x, int y) {
        regs[r] = ic.pow(regs[x], regs[y]);
    }

    @Override
    public void visitExp(int r, int x) {
        regs[r] = ic.exp(regs[x]);
    }

    @Override
    public void visitExp2(int r, int x) {
        regs[r] = ic.exp2(regs[x]);
    }

    @Override
    public void visitExp10(int r, int x) {
        regs[r] = ic.exp10(regs[x]);
    }

    @Override
    public void visitLog(int r, int x) {
        regs[r] = ic.log(regs[x]);
    }

    @Override
    public void visitLog2(int r, int x) {
        regs[r] = ic.log2(regs[x]);
    }

    @Override
    public void visitLog10(int r, int x) {
        regs[r] = ic.log10(regs[x]);
    }

    @Override
    public void visitSin(int r, int x) {
        regs[r] = ic.sin(regs[x]);
    }

    @Override
    public void visitCos(int r, int x) {
        regs[r] = ic.cos(regs[x]);
    }

    @Override
    public void visitTan(int r, int x) {
        regs[r] = ic.tan(regs[x]);
    }

    @Override
    public void visitAsin(int r, int x) {
        regs[r] = ic.asin(regs[x]);
    }

    @Override
    public void visitAcos(int r, int x) {
        regs[r] = ic.acos(regs[x]);
    }

    @Override
    public void visitAtan(int r, int x) {
        regs[r] = ic.atan(regs[x]);
    }

    @Override
    public void visitAtan2(int r, int y, int x) {
        regs[r] = ic.atan2(regs[y], regs[x]);
    }

    @Override
    public void visitSinh(int r, int x) {
        regs[r] = ic.sinh(regs[x]);
    }

    @Override
    public void visitCosh(int r, int x) {
        regs[r] = ic.cosh(regs[x]);
    }

    @Override
    public void visitTanh(int r, int x) {
        regs[r] = ic.tanh(regs[x]);
    }

    @Override
    public void visitAsinh(int r, int x) {
        regs[r] = ic.asinh(regs[x]);
    }

    @Override
    public void visitAcosh(int r, int x) {
        regs[r] = ic.acosh(regs[x]);
    }

    @Override
    public void visitAtanh(int r, int x) {
        regs[r] = ic.atanh(regs[x]);
    }

    @Override
    public void visitSign(int r, int x) {
        regs[r] = ic.sign(regs[x]);
    }

    @Override
    public void visitCeil(int r, int x) {
        regs[r] = ic.ceil(regs[x]);
    }

    @Override
    public void visitFloor(int r, int x) {
        regs[r] = ic.floor(regs[x]);
    }

    @Override
    public void visitTrunc(int r, int x) {
        regs[r] = ic.trunc(regs[x]);
    }

    @Override
    public void visitRoundTiesToEven(int r, int x) {
        regs[r] = ic.roundTiesToEven(regs[x]);
    }

    @Override
    public void visitRoundTiesToAway(int r, int x) {
        regs[r] = ic.roundTiesToEven(regs[x]);
    }

    @Override
    public void visitAbs(int r, int x) {
        regs[r] = ic.abs(regs[x]);
    }

    @Override
    public void visitMin(int r, int x, int y) {
        regs[r] = ic.min(regs[x], regs[y]);
    }

    @Override
    public void visitMax(int r, int x, int y) {
        regs[r] = ic.max(regs[x], regs[y]);
    }

    @Override
    public void visitRootn(int r, int x, BigInteger q) {
        regs[r] = ic.rootn(regs[x], q);
    }

    @Override
    public void visitRootn(int r, int x, long q) {
        regs[r] = ic.rootn(regs[x], q);
    }

    @Override
    public void visitRootn(int r, int x, int q) {
        regs[r] = ic.rootn(regs[x], q);
    }

    @Override
    public void visitHypot(int r, int x, int y) {
        regs[r] = ic.hypot(regs[x], regs[y]);
    }
}
