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
package net.java.jinterval.interval.kaucher;

import java.math.BigInteger;
import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.rational.DomainException;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public abstract class AbstractKaucherIntervalContext implements KaucherIntervalContext {

    public final AbstractKaucherIntervalContext.Table table;

    public interface UnaryOp {

        public KaucherInterval call(KaucherInterval x);
        /**
         * Dummy UnaryOp
         */
        public static AbstractKaucherIntervalContext.UnaryOp UNDEFINED = new AbstractKaucherIntervalContext.UnaryOp() {
            public KaucherInterval call(KaucherInterval x) {
                throw new UnsupportedOperationException("Not supported yet.");
            }
        };
    }

    public interface ParameterizedUnaryOp {

        public KaucherInterval call(KaucherInterval x, BigInteger p);

        public KaucherInterval call(KaucherInterval x, long p);

        public KaucherInterval call(KaucherInterval x, int p);
        /**
         * Dummy ParameterizedUnaryOp
         */
        public static AbstractKaucherIntervalContext.ParameterizedUnaryOp UNDEFINED = new AbstractKaucherIntervalContext.ParameterizedUnaryOp() {
            public KaucherInterval call(KaucherInterval x, BigInteger p) {
                throw new UnsupportedOperationException("Not supported yet.");
            }

            public KaucherInterval call(KaucherInterval x, long p) {
                throw new UnsupportedOperationException("Not supported yet.");
            }

            public KaucherInterval call(KaucherInterval x, int p) {
                throw new UnsupportedOperationException("Not supported yet.");
            }
        };
    }

    public interface BinaryOp {

        public KaucherInterval call(KaucherInterval x, KaucherInterval y);
        /**
         * Dummy BinaryOp
         */
        public static AbstractKaucherIntervalContext.BinaryOp UNDEFINED = new AbstractKaucherIntervalContext.BinaryOp() {
            public KaucherInterval call(KaucherInterval x, KaucherInterval y) {
                throw new UnsupportedOperationException("Not supported yet.");
            }
        };
    }

    public interface TernaryOp {

        public KaucherInterval call(KaucherInterval x, KaucherInterval y, KaucherInterval z);
        /**
         * Dummy TernaryOp
         */
        public static AbstractKaucherIntervalContext.TernaryOp UNDEFINED = new AbstractKaucherIntervalContext.TernaryOp() {
            public KaucherInterval call(KaucherInterval x, KaucherInterval y, KaucherInterval z) {
                throw new UnsupportedOperationException("Not supported yet.");
            }
        };
    }

    public static class Table {

        public final AbstractKaucherIntervalContext.TernaryOp fma;
        public final AbstractKaucherIntervalContext.UnaryOp sqr;
        public final AbstractKaucherIntervalContext.ParameterizedUnaryOp pown;
        public final AbstractKaucherIntervalContext.BinaryOp pow;
        public final AbstractKaucherIntervalContext.UnaryOp exp;
        public final AbstractKaucherIntervalContext.UnaryOp exp2;
        public final AbstractKaucherIntervalContext.UnaryOp exp10;
        public final AbstractKaucherIntervalContext.UnaryOp log;
        public final AbstractKaucherIntervalContext.UnaryOp log2;
        public final AbstractKaucherIntervalContext.UnaryOp log10;
        public final AbstractKaucherIntervalContext.UnaryOp sin;
        public final AbstractKaucherIntervalContext.UnaryOp cos;
        public final AbstractKaucherIntervalContext.UnaryOp tan;
        public final AbstractKaucherIntervalContext.UnaryOp asin;
        public final AbstractKaucherIntervalContext.UnaryOp acos;
        public final AbstractKaucherIntervalContext.UnaryOp atan;
        public final AbstractKaucherIntervalContext.BinaryOp atan2;
        public final AbstractKaucherIntervalContext.UnaryOp sinh;
        public final AbstractKaucherIntervalContext.UnaryOp cosh;
        public final AbstractKaucherIntervalContext.UnaryOp tanh;
        public final AbstractKaucherIntervalContext.UnaryOp asinh;
        public final AbstractKaucherIntervalContext.UnaryOp acosh;
        public final AbstractKaucherIntervalContext.UnaryOp atanh;
        public final AbstractKaucherIntervalContext.ParameterizedUnaryOp rootn;
        public final AbstractKaucherIntervalContext.BinaryOp hypot;

        protected Table() {
            this(
                    AbstractKaucherIntervalContext.TernaryOp.UNDEFINED, // fma
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // sqr
                    AbstractKaucherIntervalContext.ParameterizedUnaryOp.UNDEFINED, // pown
                    AbstractKaucherIntervalContext.BinaryOp.UNDEFINED, // pow
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // exp
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // exp2
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // exp10
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // log
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // log2
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // log10
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // sin
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // cos
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // tan
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // asin
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // acos
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // atan
                    AbstractKaucherIntervalContext.BinaryOp.UNDEFINED, // atan2
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // sinh
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // cosh
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // tanh
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // asinh
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // acosh
                    AbstractKaucherIntervalContext.UnaryOp.UNDEFINED, // atanh
                    AbstractKaucherIntervalContext.ParameterizedUnaryOp.UNDEFINED, // rootn
                    AbstractKaucherIntervalContext.BinaryOp.UNDEFINED // hypot
            );
        }

        protected Table(
                AbstractKaucherIntervalContext.TernaryOp fma,
                AbstractKaucherIntervalContext.UnaryOp sqr,
                AbstractKaucherIntervalContext.ParameterizedUnaryOp pown,
                AbstractKaucherIntervalContext.BinaryOp pow,
                AbstractKaucherIntervalContext.UnaryOp exp,
                AbstractKaucherIntervalContext.UnaryOp exp2,
                AbstractKaucherIntervalContext.UnaryOp exp10,
                AbstractKaucherIntervalContext.UnaryOp log,
                AbstractKaucherIntervalContext.UnaryOp log2,
                AbstractKaucherIntervalContext.UnaryOp log10,
                AbstractKaucherIntervalContext.UnaryOp sin,
                AbstractKaucherIntervalContext.UnaryOp cos,
                AbstractKaucherIntervalContext.UnaryOp tan,
                AbstractKaucherIntervalContext.UnaryOp asin,
                AbstractKaucherIntervalContext.UnaryOp acos,
                AbstractKaucherIntervalContext.UnaryOp atan,
                AbstractKaucherIntervalContext.BinaryOp atan2,
                AbstractKaucherIntervalContext.UnaryOp sinh,
                AbstractKaucherIntervalContext.UnaryOp cosh,
                AbstractKaucherIntervalContext.UnaryOp tanh,
                AbstractKaucherIntervalContext.UnaryOp asinh,
                AbstractKaucherIntervalContext.UnaryOp acosh,
                AbstractKaucherIntervalContext.UnaryOp atanh,
                AbstractKaucherIntervalContext.ParameterizedUnaryOp rootn,
                AbstractKaucherIntervalContext.BinaryOp hypot) {
            this.fma = fma;
            this.sqr = sqr;
            this.pown = pown;
            this.pow = pow;
            this.exp = exp;
            this.exp2 = exp2;
            this.exp10 = exp10;
            this.log = log;
            this.log2 = log2;
            this.log10 = log10;
            this.sin = sin;
            this.cos = cos;
            this.tan = tan;
            this.asin = asin;
            this.acos = acos;
            this.atan = atan;
            this.atan2 = atan2;
            this.sinh = sinh;
            this.cosh = cosh;
            this.tanh = tanh;
            this.asinh = asinh;
            this.acosh = acosh;
            this.atanh = atanh;
            this.rootn = rootn;
            this.hypot = hypot;
        }
    }

    public AbstractKaucherIntervalContext(AbstractKaucherIntervalContext.Table table) {
        this.table = table;
    }

    @Override
    public abstract KaucherInterval hull(KaucherInterval x);

    @Override
    public KaucherInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
        if (l instanceof Rational && u instanceof Rational) {
            return hull(KaucherIntervalOps.nums2((Rational) l, (Rational) u));
        } else {
            throw new DomainException();
        }
    }

    @Override
    public KaucherInterval numsToInterval(double l, double u) {
        return numsToInterval(ExtendedRational.valueOf(l), ExtendedRational.valueOf(u));
    }

    @Override
    public KaucherInterval numsToInterval(float l, float u) {
        return numsToInterval((double) l, (double) u);
    }

    @Override
    public ClassicInterval textToInterval(String s) {
        throw new UnsupportedOperationException();
    }

    @Override
    public ClassicInterval textToDecoratedInterval(String s) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval pi() {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval euler() {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval neg(KaucherInterval x) {
        return hull(KaucherIntervalOps.neg(x));
    }

    @Override
    public KaucherInterval add(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.add(x, y));
    }

    @Override
    public KaucherInterval sub(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.sub(x, y));
    }

    @Override
    public KaucherInterval mul(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.mul(x, y));
    }

    @Override
    public KaucherInterval div(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.div(x, y));
    }

    @Override
    public KaucherInterval recip(KaucherInterval x) {
        return hull(KaucherIntervalOps.recip(x));
    }

    @Override
    public KaucherInterval sqr(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval sqrt(KaucherInterval x) {
        return hull(KaucherIntervalOps.sqrt(x));
    }

    @Override
    public KaucherInterval fma(KaucherInterval x, KaucherInterval y, KaucherInterval z) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval pown(KaucherInterval x, BigInteger p) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval pown(KaucherInterval x, long p) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval pown(KaucherInterval x, int p) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval pow(KaucherInterval x, KaucherInterval y) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval exp(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval exp2(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval exp10(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval log(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval log2(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval log10(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval sin(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval cos(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval tan(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval asin(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval acos(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval atan(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval atan2(KaucherInterval y, KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval sinh(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval cosh(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval tanh(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval asinh(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval acosh(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval atanh(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval sign(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval ceil(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval floor(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval trunc(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval roundTiesToEven(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval roundTiesToAway(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval abs(KaucherInterval x) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval min(KaucherInterval x1, KaucherInterval x2) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval min(KaucherInterval x1, KaucherInterval x2, KaucherInterval... xn) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval max(KaucherInterval x1, KaucherInterval x2) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval max(KaucherInterval x1, KaucherInterval x2, KaucherInterval... xn) {
        throw new UnsupportedOperationException();
    }

    @Override
    public KaucherInterval cancelMinus(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.innerMinus(x, y));
    }

    @Override
    public KaucherInterval cancelPlus(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.innerPlus(x, y));
    }

    @Override
    public KaucherInterval intersection(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.intersection(x, y));
    }

    @Override
    public KaucherInterval convexHull(KaucherInterval x, KaucherInterval y) {
        return hull(KaucherIntervalOps.convexHull(x, y));
    }
}
