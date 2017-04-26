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
package net.java.jinterval.expression;

import java.math.BigInteger;

/**
 *
 */
public class AbstractExpressionVisitor implements ExpressionVisitor {

    @Override
    public void visitInp(int r, String name) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitLit(int r, String numerator, String denominator) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitLit(int r, String literal) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitInterval(int r, String inf, String sup) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitNum(int r, Number num) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitPi(int r) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitEuler(int r) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitNeg(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAdd(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitSub(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitMul(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitDiv(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitRecip(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitSqr(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitSqrt(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitFma(int r, int x, int y, int z) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitPown(int r, int x, BigInteger p) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitPown(int r, int x, long n) {
        visitPown(r, x, BigInteger.valueOf(n));
    }

    @Override
    public void visitPown(int r, int x, int n) {
        visitPown(r, x, (long) n);
    }

    @Override
    public void visitPow(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitExp(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitExp2(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitExp10(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitLog(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitLog2(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitLog10(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitSin(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitCos(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitTan(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAsin(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAcos(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAtan(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAtan2(int r, int y, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitSinh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitCosh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitTanh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAsinh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAcosh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAtanh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitSign(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitCeil(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitFloor(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitTrunc(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitRoundTiesToEven(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitRoundTiesToAway(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitAbs(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitMin(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitMax(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitRootn(int r, int x, BigInteger q) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void visitRootn(int r, int x, long q) {
        visitRootn(r, x, BigInteger.valueOf(q));
    }

    @Override
    public void visitRootn(int r, int x, int q) {
        visitRootn(r, x, (long) q);
    }

    @Override
    public void visitHypot(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
