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
public interface ExpressionVisitor {

    void visitInp(int r, String name);

    void visitLit(int r, String numerator, String denominator);

    void visitLit(int r, String literal);

    void visitInterval(int r, String inf, String sup);

    void visitNum(int r, Number num);

    void visitPi(int r);

    void visitEuler(int r);

    void visitNeg(int r, int x);

    void visitAdd(int r, int x, int y);

    void visitSub(int r, int x, int y);

    void visitMul(int r, int x, int y);

    void visitDiv(int r, int x, int y);

    void visitRecip(int r, int x);

    void visitSqr(int r, int x);

    void visitSqrt(int r, int x);

    void visitFma(int r, int x, int y, int z);

    void visitPown(int r, int x, BigInteger p);

    void visitPown(int r, int x, long n);

    void visitPown(int r, int x, int n);

    void visitPow(int r, int x, int y);

    void visitExp(int r, int x);

    void visitExp2(int r, int x);

    void visitExp10(int r, int x);

    void visitLog(int r, int x);

    void visitLog2(int r, int x);

    void visitLog10(int r, int x);

    void visitSin(int r, int x);

    void visitCos(int r, int x);

    void visitTan(int r, int x);

    void visitAsin(int r, int x);

    void visitAcos(int r, int x);

    void visitAtan(int r, int x);

    void visitAtan2(int r, int y, int x);

    void visitSinh(int r, int x);

    void visitCosh(int r, int x);

    void visitTanh(int r, int x);

    void visitAsinh(int r, int x);

    void visitAcosh(int r, int x);

    void visitAtanh(int r, int x);

    void visitSign(int r, int x);

    void visitCeil(int r, int x);

    void visitFloor(int r, int x);

    void visitTrunc(int r, int x);

    void visitRoundTiesToEven(int r, int x);

    void visitRoundTiesToAway(int r, int x);

    void visitAbs(int r, int x);

    void visitMin(int r, int x, int y);

    void visitMax(int r, int x, int y);

    void visitRootn(int r, int x, BigInteger q);

    void visitRootn(int r, int x, long q);

    void visitRootn(int r, int x, int q);

    void visitHypot(int r, int x, int y);

}
