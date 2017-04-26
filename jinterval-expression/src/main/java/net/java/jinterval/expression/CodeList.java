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
 * AND ANY EXPRESS Ovoid IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
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

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 *
 */
public class CodeList implements Serializable {

    public static CodeList create(String... inps) {
        return new CodeList(inps);
    }

    public int getNumInps() {
        return inps.length;
    }

    public Expression getInp(int i) {
        return inps[i];
    }

    public int getNumExprs() {
        return exprs.size();
    }

    public Expression getExpr(int i) {
        return exprs.get(i);
    }

    public Expression lit(String literal) {
        int index = literal.indexOf('/');
        if (index >= 0) {
            return new ConstantExpression.Fraction(this,
                    literal.substring(0, index).trim(),
                    literal.substring(index + 1).trim());
        } else {
            return new ConstantExpression.Literal(this, literal.trim());
        }
    }

    public Expression interval(String inf, String sup) {
        return new ConstantExpression.Interval(this, inf, sup);
    }

    @Deprecated
    public Expression num(Number num) {
        return new ConstantExpression.Num(this, num);
    }

    @Deprecated
    public Expression num(Number num, String name) {
        return new ConstantExpression.Num(this, num).name(name);
    }

    public Expression pi() {
        return new ConstantExpression.Pi(this);
    }

    public Expression euler() {
        return new ConstantExpression.Euler(this);
    }

    private CodeList(String[] inps) {
        this.inps = new InputExpression[inps.length];
        for (int i = 0; i < inps.length; i++) {
            String inpStr = inps[i];
            if (inpStr == null) {
                throw new NullPointerException();
            }
            this.inps[i] = new InputExpression(this, inpStr);
        }
    }

    public void acceptConstants(ExpressionVisitor visitor) {
        for (Expression e : exprs) {
            if (e.isConstant) {
                e.accept(visitor);
            }
        }
    }

    public void acceptForward(ExpressionVisitor visitor) {
        for (Expression e : exprs) {
            if (!e.isConstant) {
                e.accept(visitor);
            }
        }
    }

    public void acceptReverse(ExpressionVisitor visitor) {
        for (int i = exprs.size() - 1; i >= 0; i--) {
            Expression e = exprs.get(i);
            if (!e.isConstant) {
                e.accept(visitor);
            }
        }
    }

    final InputExpression[] inps;
    final List<Expression> exprs = new ArrayList<>();

    final void add(Expression e) {
        assert e.index == exprs.size();
        exprs.add(e);
    }

}
