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

import java.io.Serializable;
import java.math.BigInteger;

/**
 *
 */
public abstract class Expression implements Serializable {

    private final CodeList owner;
    final int index;
    final boolean isConstant;
    private String name;

    protected Expression(CodeList owner, boolean isConstant) {
        this.owner = owner;
        index = owner.exprs.size();
        owner.add(this);
        this.isConstant = isConstant;
    }

    public final CodeList getCodeList() {
        return owner;
    }

    public int getIndex() {
        return index;
    }

    public boolean isConstant() {
        return isConstant;
    }

    public final String name() {
        return name != null ? name : "_" + index;
    }

    public final Expression name(String name) {
        this.name = name;
        return this;
    }

    public abstract void accept(ExpressionVisitor visitor);

    public Expression neg() {
        return new UnaryExpression(UnaryExpression.Kind.Neg, this);
    }

    public Expression add(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Add, this, that);
    }

    public Expression sub(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Sub, this, that);
    }

    public Expression mul(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Mul, this, that);
    }

    public Expression div(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Div, this, that);
    }

    public Expression recip() {
        return new UnaryExpression(UnaryExpression.Kind.Recip, this);
    }

    public Expression sqr() {
        return new UnaryExpression(UnaryExpression.Kind.Sqr, this);
    }

    public Expression sqrt() {
        return new UnaryExpression(UnaryExpression.Kind.Sqrt, this);
    }

    public Expression fma(Expression y, Expression z) {
        return new TernaryExpression(TernaryExpression.Kind.Fma, this, y, z);
    }

    public Expression pown(BigInteger p) {
        return new UnaryExpression(UnaryExpression.Kind.Pown, this, p);
    }

    public Expression pown(long p) {
        return new UnaryExpression(UnaryExpression.Kind.Pown, this, BigInteger.valueOf(p));
    }

    public Expression pown(int p) {
        return new UnaryExpression(UnaryExpression.Kind.Pown, this, BigInteger.valueOf(p));
    }

    public Expression pow(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Pow, this, that);
    }

    public Expression exp() {
        return new UnaryExpression(UnaryExpression.Kind.Exp, this);
    }

    public Expression exp2() {
        return new UnaryExpression(UnaryExpression.Kind.Exp2, this);
    }

    public Expression exp10() {
        return new UnaryExpression(UnaryExpression.Kind.Exp10, this);
    }

    public Expression log() {
        return new UnaryExpression(UnaryExpression.Kind.Log, this);
    }

    public Expression log2() {
        return new UnaryExpression(UnaryExpression.Kind.Log2, this);
    }

    public Expression log10() {
        return new UnaryExpression(UnaryExpression.Kind.Log10, this);
    }

    public Expression sin() {
        return new UnaryExpression(UnaryExpression.Kind.Sin, this);
    }

    public Expression cos() {
        return new UnaryExpression(UnaryExpression.Kind.Cos, this);
    }

    public Expression tan() {
        return new UnaryExpression(UnaryExpression.Kind.Tan, this);
    }

    public Expression asin() {
        return new UnaryExpression(UnaryExpression.Kind.Asin, this);
    }

    public Expression acos() {
        return new UnaryExpression(UnaryExpression.Kind.Acos, this);
    }

    public Expression atan() {
        return new UnaryExpression(UnaryExpression.Kind.Atan, this);
    }

    public Expression atan2(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Atan2, this, that);
    }

    public Expression sinh() {
        return new UnaryExpression(UnaryExpression.Kind.Sinh, this);
    }

    public Expression cosh() {
        return new UnaryExpression(UnaryExpression.Kind.Cosh, this);
    }

    public Expression tanh() {
        return new UnaryExpression(UnaryExpression.Kind.Tanh, this);
    }

    public Expression asinh() {
        return new UnaryExpression(UnaryExpression.Kind.Asinh, this);
    }

    public Expression acosh() {
        return new UnaryExpression(UnaryExpression.Kind.Acosh, this);
    }

    public Expression atanh() {
        return new UnaryExpression(UnaryExpression.Kind.Atanh, this);
    }

    public Expression sign() {
        return new UnaryExpression(UnaryExpression.Kind.Sign, this);
    }

    public Expression ceil() {
        return new UnaryExpression(UnaryExpression.Kind.Ceil, this);
    }

    public Expression floor() {
        return new UnaryExpression(UnaryExpression.Kind.Floor, this);
    }

    public Expression trunc() {
        return new UnaryExpression(UnaryExpression.Kind.Trunc, this);
    }

    public Expression roundTiesToEven() {
        return new UnaryExpression(UnaryExpression.Kind.RoundTiesToEven, this);
    }

    public Expression roundTiesToAway() {
        return new UnaryExpression(UnaryExpression.Kind.RoundTiesToAway, this);
    }

    public Expression abs() {
        return new UnaryExpression(UnaryExpression.Kind.Abs, this);
    }

    public Expression min(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Min, this, that);
    }

    public Expression max(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Max, this, that);
    }

    public Expression rootn(BigInteger q) {
        return new UnaryExpression(UnaryExpression.Kind.Rootn, this, q);
    }

    public Expression rootn(long q) {
        return new UnaryExpression(UnaryExpression.Kind.Rootn, this, BigInteger.valueOf(q));
    }

    public Expression rootn(int q) {
        return new UnaryExpression(UnaryExpression.Kind.Rootn, this, BigInteger.valueOf(q));
    }

    public Expression hypot(Expression that) {
        return new BinaryExpression(BinaryExpression.Kind.Hypot, this, that);
    }
}
