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

/**
 *
 */
class BinaryExpression extends Expression {

    enum Kind {
        Add, Sub, Mul, Div, Pow, Atan2, Min, Max, Hypot
    };

    final Kind kind;
    final Expression x, y;

    BinaryExpression(Kind kind, Expression x, Expression y) {
        super(checkOwner(x, y), x.isConstant & y.isConstant);
        this.kind = kind;
        this.x = x;
        this.y = y;
    }

    @Override
    public void accept(ExpressionVisitor visitor) {
        switch (kind) {
            case Add:
                visitor.visitAdd(this.index, x.index, y.index);
                break;
            case Sub:
                visitor.visitSub(this.index, x.index, y.index);
                break;
            case Mul:
                visitor.visitMul(this.index, x.index, y.index);
                break;
            case Div:
                visitor.visitDiv(this.index, x.index, y.index);
                break;
            case Pow:
                visitor.visitPow(this.index, x.index, y.index);
                break;
            case Atan2:
                visitor.visitAtan2(this.index, x.index, y.index);
                break;
            case Min:
                visitor.visitMin(this.index, x.index, y.index);
                break;
            case Max:
                visitor.visitMax(this.index, x.index, y.index);
                break;
            case Hypot:
                visitor.visitHypot(this.index, x.index, y.index);
                break;
            default:
                throw new AssertionError();
        }
    }

    private static CodeList checkOwner(Expression x, Expression y) {
        CodeList owner = x.getCodeList();
        if (owner != y.getCodeList()) {
            throw new IllegalArgumentException();
        }
        return owner;
    }
}
