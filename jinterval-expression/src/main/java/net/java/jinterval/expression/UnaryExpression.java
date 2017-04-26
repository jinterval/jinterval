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
class UnaryExpression extends Expression {

    enum Kind {
        Neg, Recip, Sqr, Sqrt, Pown, Exp, Exp2, Exp10, Log, Log2, Log10,
        Sin, Cos, Tan, Asin, Acos, Atan,
        Sinh, Cosh, Tanh, Asinh, Acosh, Atanh,
        Sign, Ceil, Floor, Trunc, RoundTiesToEven, RoundTiesToAway, Abs,
        Rootn
    }

    final Kind kind;
    final Expression x;
    final BigInteger n;

    UnaryExpression(Kind kind, Expression x) {
        super(x.getCodeList(), x.isConstant);
        this.kind = kind;
        this.x = x;
        n = null;
    }

    UnaryExpression(Kind kind, Expression x, BigInteger n) {
        super(x.getCodeList(), x.isConstant);
        this.kind = kind;
        this.x = x;
        this.n = n;
    }

    @Override
    public void accept(ExpressionVisitor visitor) {
        int bitLength;
        switch (kind) {
            case Neg:
                visitor.visitNeg(this.index, x.index);
                break;
            case Recip:
                visitor.visitRecip(this.index, x.index);
                break;
            case Sqr:
                visitor.visitSqr(this.index, x.index);
                break;
            case Sqrt:
                visitor.visitSqrt(this.index, x.index);
                break;
            case Pown:
                bitLength = n.bitLength();
                if (bitLength <= Integer.SIZE) {
                    visitor.visitPown(this.index, x.index, n.intValueExact());
                } else if (bitLength <= Long.SIZE) {
                    visitor.visitPown(this.index, x.index, n.longValueExact());
                } else {
                    visitor.visitPown(this.index, x.index, n);
                }
                break;
            case Exp:
                visitor.visitExp(this.index, x.index);
                break;
            case Exp2:
                visitor.visitExp2(this.index, x.index);
                break;
            case Exp10:
                visitor.visitExp10(this.index, x.index);
                break;
            case Log:
                visitor.visitLog(this.index, x.index);
                break;
            case Log2:
                visitor.visitLog2(this.index, x.index);
                break;
            case Log10:
                visitor.visitLog10(this.index, x.index);
                break;
            case Sin:
                visitor.visitSin(this.index, x.index);
                break;
            case Cos:
                visitor.visitCos(this.index, x.index);
                break;
            case Tan:
                visitor.visitTan(this.index, x.index);
                break;
            case Asin:
                visitor.visitAsin(this.index, x.index);
                break;
            case Acos:
                visitor.visitAcos(this.index, x.index);
                break;
            case Atan:
                visitor.visitAtan(this.index, x.index);
                break;
            case Sinh:
                visitor.visitSinh(this.index, x.index);
                break;
            case Cosh:
                visitor.visitCosh(this.index, x.index);
                break;
            case Tanh:
                visitor.visitTanh(this.index, x.index);
                break;
            case Asinh:
                visitor.visitAsinh(this.index, x.index);
                break;
            case Acosh:
                visitor.visitAcosh(this.index, x.index);
                break;
            case Atanh:
                visitor.visitAtanh(this.index, x.index);
                break;
            case Sign:
                visitor.visitSign(this.index, x.index);
                break;
            case Ceil:
                visitor.visitCeil(this.index, x.index);
                break;
            case Floor:
                visitor.visitFloor(this.index, x.index);
                break;
            case Trunc:
                visitor.visitTrunc(this.index, x.index);
                break;
            case RoundTiesToEven:
                visitor.visitRoundTiesToEven(this.index, x.index);
                break;
            case RoundTiesToAway:
                visitor.visitRoundTiesToAway(this.index, x.index);
                break;
            case Abs:
                visitor.visitAbs(this.index, x.index);
                break;
            case Rootn:
                bitLength = n.bitLength();
                if (bitLength <= Integer.SIZE) {
                    visitor.visitRootn(this.index, x.index, n.intValueExact());
                } else if (bitLength <= Long.SIZE) {
                    visitor.visitRootn(this.index, x.index, n.longValueExact());
                } else {
                    visitor.visitRootn(this.index, x.index, n);
                }
                break;
            default:
                throw new AssertionError();
        }
    }
}
