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
abstract class ConstantExpression extends Expression {

    ConstantExpression(CodeList owner) {
        super(owner, true);
    }

    static class Literal extends ConstantExpression {

        private final String literal;

        Literal(CodeList owner, String literal) {
            super(owner);
            this.literal = literal;
        }

        @Override
        public void accept(ExpressionVisitor visitor) {
            visitor.visitLit(this.index, literal);
        }
    }

    static class Fraction extends ConstantExpression {

        private final String numerator;
        private final String denominator;

        Fraction(CodeList owner, String numerator, String denominator) {
            super(owner);
            this.numerator = numerator;
            this.denominator = denominator;
        }

        @Override
        public void accept(ExpressionVisitor visitor) {
            visitor.visitLit(this.index, numerator, denominator);
        }
    }

    static class Interval extends ConstantExpression {

        private final String inf;
        private final String sup;

        Interval(CodeList owner, String inf, String sup) {
            super(owner);
            this.inf = inf;
            this.sup = sup;
        }

        @Override
        public void accept(ExpressionVisitor visitor) {
            visitor.visitInterval(this.index, inf, sup);
        }
    }

    static class Num extends ConstantExpression {

        private final Number num;

        Num(CodeList owner, Number num) {
            super(owner);
            this.num = num;
        }

        @Override
        public void accept(ExpressionVisitor visitor) {
            visitor.visitNum(this.index, num);
        }
    }

    static class Pi extends ConstantExpression {

        Pi(CodeList owner) {
            super(owner);
        }

        @Override
        public void accept(ExpressionVisitor visitor) {
            visitor.visitPi(this.index);
        }
    }

    static class Euler extends ConstantExpression {

        Euler(CodeList owner) {
            super(owner);
        }

        @Override
        public void accept(ExpressionVisitor visitor) {
            visitor.visitEuler(this.index);
        }
    }
}
