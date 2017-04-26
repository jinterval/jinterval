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
package net.java.jinterval.rational;

import java.math.BigInteger;
import net.java.jinterval.expression.AbstractExpressionVisitor;
import net.java.jinterval.expression.CodeList;

/**
 *
 */
class RationalEvaluator extends AbstractExpressionVisitor {

    private final ExtendedRationalContext rc;
    final ExtendedRational[] values;

    RationalEvaluator(ExtendedRationalContext rc, CodeList cl) {
        this.rc = rc;
        values = new ExtendedRational[cl.getNumExprs()];
    }

    @Override
    public void visitInp(int r, String name) {
    }

    @Override
    public void visitLit(int r, String numerator, String denominator) {
        values[r] = rc.rnd(Rational.valueOf(numerator + "/" + denominator));
    }

    @Override
    public void visitLit(int r, String literal) {
        values[r] = rc.rnd(Rational.valueOf(literal));
    }

    @Override
    public void visitInterval(int r, String inf, String sup) {
        values[r] = rc.mul(Rational.exp2(-1), rc.add(ExtendedRational.valueOf(inf), ExtendedRational.valueOf(sup)));
    }

    @Override
    public void visitNum(int r, Number num) {
        values[r] = rc.rnd(num);
    }

    @Override
    public void visitPi(int r) {
        values[r] = rc.pi();
    }

    @Override
    public void visitEuler(int r) {
        values[r] = rc.euler();
    }

    @Override
    public void visitNeg(int r, int x) {
        values[r] = rc.neg(values[x]);
    }

    @Override
    public void visitAdd(int r, int x, int y) {
        values[r] = rc.add(values[x], values[y]);
    }

    @Override
    public void visitSub(int r, int x, int y) {
        values[r] = rc.sub(values[x], values[y]);
    }

    @Override
    public void visitMul(int r, int x, int y) {
        values[r] = rc.mul(values[x], values[y]);
    }

    @Override
    public void visitDiv(int r, int x, int y) {
        values[r] = rc.div(values[x], values[y]);
    }

    @Override
    public void visitRecip(int r, int x) {
        values[r] = rc.recip(values[x]);
    }

    @Override
    public void visitSqr(int r, int x) {
        values[r] = rc.sqr(values[x]);
    }

    @Override
    public void visitSqrt(int r, int x) {
        values[r] = rc.sqrt(values[x]);
    }

    @Override
    public void visitFma(int r, int x, int y, int z) {
        values[r] = rc.fma(values[x], values[y], values[z]);
    }

    @Override
    public void visitPown(int r, int x, BigInteger p) {
        values[r] = rc.pown(values[x], p);
    }

    @Override
    public void visitPown(int r, int x, long p) {
        values[r] = rc.pown(values[x], p);
    }

    @Override
    public void visitPown(int r, int x, int p) {
        values[r] = rc.pown(values[x], p);
    }

    @Override
    public void visitPow(int r, int x, int y) {
        values[r] = rc.pow(values[x], values[y]);
    }

    @Override
    public void visitExp(int r, int x) {
        values[r] = rc.exp(values[x]);
    }

    @Override
    public void visitExp2(int r, int x) {
        values[r] = rc.exp2(values[x]);
    }

    @Override
    public void visitExp10(int r, int x) {
        values[r] = rc.exp10(values[x]);
    }

    @Override
    public void visitLog(int r, int x) {
        values[r] = rc.log(values[x]);
    }

    @Override
    public void visitLog2(int r, int x) {
        values[r] = rc.log2(values[x]);
    }

    @Override
    public void visitLog10(int r, int x) {
        values[r] = rc.log10(values[x]);
    }

    @Override
    public void visitSin(int r, int x) {
        values[r] = rc.sin(values[x]);
    }

    @Override
    public void visitCos(int r, int x) {
        values[r] = rc.cos(values[x]);
    }

    @Override
    public void visitTan(int r, int x) {
        values[r] = rc.tan(values[x]);
    }

    @Override
    public void visitAsin(int r, int x) {
        values[r] = rc.asin(values[x]);
    }

    @Override
    public void visitAcos(int r, int x) {
        values[r] = rc.acos(values[x]);
    }

    @Override
    public void visitAtan(int r, int x) {
        values[r] = rc.atan(values[x]);
    }

    @Override
    public void visitAtan2(int r, int y, int x) {
        values[r] = rc.atan2(values[y], values[x]);
    }

    @Override
    public void visitSinh(int r, int x) {
        values[r] = rc.sinh(values[x]);
    }

    @Override
    public void visitCosh(int r, int x) {
        values[r] = rc.cosh(values[x]);
    }

    @Override
    public void visitTanh(int r, int x) {
        values[r] = rc.tanh(values[x]);
    }

    @Override
    public void visitAsinh(int r, int x) {
        values[r] = rc.asinh(values[x]);
    }

    @Override
    public void visitAcosh(int r, int x) {
        values[r] = rc.acosh(values[x]);
    }

    @Override
    public void visitAtanh(int r, int x) {
        values[r] = rc.atanh(values[x]);
    }

    @Override
    public void visitSign(int r, int x) {
        values[r] = rc.sign(values[x]);
    }

    @Override
    public void visitCeil(int r, int x) {
        values[r] = rc.ceil(values[x]);
    }

    @Override
    public void visitFloor(int r, int x) {
        values[r] = rc.floor(values[x]);
    }

    @Override
    public void visitTrunc(int r, int x) {
        values[r] = rc.trunc(values[x]);
    }

    @Override
    public void visitRoundTiesToEven(int r, int x) {
        values[r] = rc.roundTiesToEven(values[x]);
    }

    @Override
    public void visitRoundTiesToAway(int r, int x) {
        values[r] = rc.roundTiesToAway(values[x]);
    }

    @Override
    public void visitAbs(int r, int x) {
        values[r] = rc.abs(values[x]);
    }

    @Override
    public void visitMin(int r, int x, int y) {
        values[r] = rc.min(values[x], values[y]);
    }

    @Override
    public void visitMax(int r, int x, int y) {
        values[r] = rc.max(values[x], values[y]);
    }

    @Override
    public void visitRootn(int r, int x, BigInteger q) {
        values[r] = rc.rootn(values[x], q);
    }

    @Override
    public void visitRootn(int r, int x, long q) {
        values[r] = rc.rootn(values[x], q);
    }

    @Override
    public void visitRootn(int r, int x, int q) {
        values[r] = rc.rootn(values[x], q);
    }
}
