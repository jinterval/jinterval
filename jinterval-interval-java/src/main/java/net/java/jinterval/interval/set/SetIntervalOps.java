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
package net.java.jinterval.interval.set;

import java.math.BigInteger;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public class SetIntervalOps {

    private SetIntervalOps() {
    }

    public static SetInterval empty() {
        return empty(Decoration.TRV);
    }

    public static SetInterval empty(Decoration decoration) {
        return EmptyInterval.empty(decoration);
    }

    public static SetInterval nums2(ExtendedRational l, ExtendedRational u) {
        return nums2(l, u, Decoration.COM);
    }

    public static SetInterval nums2(ExtendedRational l, ExtendedRational u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        if (l != null && u != null && l.le(u)
                && !l.isPositiveInfinity() && !u.isNegativeInfinity() && decoration != Decoration.ILL) {
            return Utils.set(l, u, decoration);
        }
        throw new UndefinedOperationException();
    }

    public static SetInterval nums2(double l, double u) {
        return nums2(l, u, Decoration.COM);
    }

    public static SetInterval nums2(double l, double u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        if (l <= u && l != Double.POSITIVE_INFINITY && u != Double.NEGATIVE_INFINITY
                && decoration != Decoration.ILL) {
            return Utils.set(l, u, decoration);
        }
        throw new UndefinedOperationException();
    }

    public static SetInterval neg(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xl = x.inf();
        ExtendedRational xu = x.sup();
        ExtendedRational l = ExtendedRationalOps.neg(xu);
        ExtendedRational u = ExtendedRationalOps.neg(xl);
        return Utils.set(l, u, x.getDecoration());
    }

    public static SetInterval add(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xl = x.inf();
        ExtendedRational xu = x.sup();
        ExtendedRational yl = y.inf();
        ExtendedRational yu = y.sup();
        ExtendedRational l = ExtendedRationalOps.add(xl, yl);
        ExtendedRational u = ExtendedRationalOps.add(xu, yu);
        return Utils.set(l, u, d);
    }

    public static SetInterval sub(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xl = x.inf();
        ExtendedRational xu = x.sup();
        ExtendedRational yl = y.inf();
        ExtendedRational yu = y.sup();
        ExtendedRational l = ExtendedRationalOps.sub(xl, yu);
        ExtendedRational u = ExtendedRationalOps.sub(xu, yl);
        return Utils.set(l, u, d);
    }

    public static SetInterval mul(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();
        ExtendedRational inf, sup;

        //[ 0, 0 ] * x = x * [ 0, 0 ] = [ 0, 0 ]
        if ((xi.signum() == 0 && xs.signum() == 0) || (yi.signum() == 0 && ys.signum() == 0)) {
            inf = sup = Rational.zero();
        } else if (ys.signum() <= 0) {
            if (xs.signum() <= 0) {
                inf = ExtendedRationalOps.mul(xs, ys);
                sup = ExtendedRationalOps.mul(xi, yi);
            } else if (xi.signum() >= 0) {
                inf = ExtendedRationalOps.mul(xs, yi);
                sup = ExtendedRationalOps.mul(xi, ys);
            } else {
                inf = ExtendedRationalOps.mul(xs, yi);
                sup = ExtendedRationalOps.mul(xi, yi);
            }
        } else if (yi.signum() >= 0) {
            if (xs.signum() <= 0) {
                inf = ExtendedRationalOps.mul(xi, ys);
                sup = ExtendedRationalOps.mul(xs, yi);
            } else if (xi.signum() >= 0) {
                inf = ExtendedRationalOps.mul(xi, yi);
                sup = ExtendedRationalOps.mul(xs, ys);
            } else {
                inf = ExtendedRationalOps.mul(xi, ys);
                sup = ExtendedRationalOps.mul(xs, ys);
            }
        } else if (xs.signum() <= 0) {
            inf = ExtendedRationalOps.mul(xi, ys);
            sup = ExtendedRationalOps.mul(xi, yi);
        } else if (xi.signum() >= 0) {
            inf = ExtendedRationalOps.mul(xs, yi);
            sup = ExtendedRationalOps.mul(xs, ys);
        } else {
            inf = ExtendedRationalOps.min(ExtendedRationalOps.mul(xi, ys), ExtendedRationalOps.mul(xs, yi));
            sup = ExtendedRationalOps.max(ExtendedRationalOps.mul(xi, yi), ExtendedRationalOps.mul(xs, ys));
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval div(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();
        ExtendedRational inf, sup;

        if (yi.signum() > 0) {
            if (xi.signum() > 0) { // x > 0, y > 0
                inf = ExtendedRationalOps.div(xi, ys);
                sup = ExtendedRationalOps.div(xs, yi);
            } else if (xs.signum() < 0) { // x < 0, y > 0
                inf = ExtendedRationalOps.div(xi, yi);
                sup = ExtendedRationalOps.div(xs, ys);
            } else { // 0 in x, y > 0
                inf = ExtendedRationalOps.div(xi, yi);
                sup = ExtendedRationalOps.div(xs, yi);
            }
        } else if (ys.signum() < 0) {
            if (xi.signum() > 0) { // x > 0, y < 0
                inf = ExtendedRationalOps.div(xs, ys);
                sup = ExtendedRationalOps.div(xi, yi);
            } else if (xs.signum() < 0) { // x < 0, y < 0
                inf = ExtendedRationalOps.div(xs, yi);
                sup = ExtendedRationalOps.div(xi, ys);
            } else { // 0 in x, y < 0
                inf = ExtendedRationalOps.div(xs, ys);
                sup = ExtendedRationalOps.div(xi, ys);
            }
        } else { // 0 in y
            if (yi.signum() == 0 && ys.signum() == 0) {
                return EmptyInterval.empty();
            }
            if (xi.signum() == 0 && xs.signum() == 0) {
                inf = sup = Rational.zero();
            } else if (xi.signum() >= 0) {
                inf = yi.signum() == 0 ? ExtendedRationalOps.div(xi, ys) : ExtendedRational.NEGATIVE_INFINITY;
                sup = ys.signum() == 0 ? ExtendedRationalOps.div(xi, yi) : ExtendedRational.POSITIVE_INFINITY;
            } else if (xs.signum() <= 0) {
                inf = ys.signum() == 0 ? ExtendedRationalOps.div(xs, yi) : ExtendedRational.NEGATIVE_INFINITY;
                sup = yi.signum() == 0 ? ExtendedRationalOps.div(xs, ys) : ExtendedRational.POSITIVE_INFINITY;
            } else {
                inf = ExtendedRational.NEGATIVE_INFINITY;
                sup = ExtendedRational.POSITIVE_INFINITY;
            }
            d = d.min(Decoration.TRV);
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval recip(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        if (xi.signum() > 0 || xs.signum() < 0) {
            return Utils.set(ExtendedRationalOps.recip(xs), ExtendedRationalOps.recip(xi), d);
        }
        if (xi.signum() == 0 && xs.signum() == 0) {
            return EmptyInterval.empty();
        }
        ExtendedRational inf = xi.signum() == 0 ? ExtendedRationalOps.recip(xs)
                : ExtendedRational.NEGATIVE_INFINITY;
        ExtendedRational sup = xs.signum() == 0 ? ExtendedRationalOps.recip(xi)
                : ExtendedRational.POSITIVE_INFINITY;
        return Utils.set(inf, sup, d.min(Decoration.TRV));
    }

    public static SetInterval sqr(SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf;
        ExtendedRational sup;
        if (xi.signum() >= 0) {
            inf = ExtendedRationalOps.sqr(xi);
            sup = ExtendedRationalOps.sqr(xs);
        } else if (xs.signum() <= 0) {
            inf = ExtendedRationalOps.sqr(xs);
            sup = ExtendedRationalOps.sqr(xi);
        } else {
            inf = Rational.zero();
            sup = ExtendedRationalOps.max(ExtendedRationalOps.sqr(xi), ExtendedRationalOps.sqr(xs));
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval sqrt(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        if (xi.signum() >= 0) {
            return Utils.set(ExtendedRationalOps.sqrt(xi), ExtendedRationalOps.sqrt(xs), d);
        }
        if (xs.signum() < 0) {
            return EmptyInterval.empty();
        }
        return Utils.set(Rational.zero(), ExtendedRationalOps.sqrt(xs), d.min(Decoration.TRV));
    }

    public static SetInterval fma(SetInterval x, SetInterval y, SetInterval z) {
        return add(mul(x, y), z);
    }

    public static SetInterval pown(SetInterval x, BigInteger p) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf;
        ExtendedRational sup;
        if (p.signum() > 0) {
            if (p.testBit(0) || xi.signum() >= 0) {
                inf = ExtendedRationalOps.pown(xi, p);
                sup = ExtendedRationalOps.pown(xs, p);
            } else if (xs.signum() <= 0) {
                inf = ExtendedRationalOps.pown(xs, p);
                sup = ExtendedRationalOps.pown(xi, p);
            } else {
                inf = Rational.zero();
                sup = ExtendedRationalOps.max(ExtendedRationalOps.pown(xi, p), ExtendedRationalOps.pown(xs, p));
            }
        } else if (p.signum() < 0) {
            if (xi.signum() > 0) {
                inf = ExtendedRationalOps.pown(xs, p);
                sup = ExtendedRationalOps.pown(xi, p);
            } else if (xs.signum() < 0) {
                if (p.testBit(0)) {
                    inf = ExtendedRationalOps.pown(xs, p);
                    sup = ExtendedRationalOps.pown(xi, p);
                } else {
                    inf = ExtendedRationalOps.pown(xi, p);
                    sup = ExtendedRationalOps.pown(xs, p);
                }
            } else if (xi.signum() == 0 && xs.signum() == 0) {
                return EmptyInterval.empty();
            } else if (p.testBit(0)) {
                inf = xi.signum() == 0 ? ExtendedRationalOps.pown(xs, p) : ExtendedRational.NEGATIVE_INFINITY;
                sup = xs.signum() == 0 ? ExtendedRationalOps.pown(xi, p) : ExtendedRational.POSITIVE_INFINITY;
                d = d.min(Decoration.DEF);
            } else {
                if (xi.signum() == 0) {
                    inf = ExtendedRationalOps.pown(xs, p);
                } else if (xs.signum() == 0) {
                    inf = ExtendedRationalOps.pown(xi, p);
                } else {
                    inf = ExtendedRationalOps.min(ExtendedRationalOps.pown(xi, p), ExtendedRationalOps.pown(xs, p));
                }
                sup = ExtendedRational.POSITIVE_INFINITY;
            }
        } else {
            inf = sup = Rational.one();
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval sign(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        ExtendedRational inf = ExtendedRationalOps.sign(xi);
        ExtendedRational sup = ExtendedRationalOps.sign(xs);
        if (inf.ne(sup)) {
            d = d.min(Decoration.DEF);
        } else if (inf.signum() == 0) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval ceil(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        ExtendedRational inf = ExtendedRationalOps.ceil(xi);
        ExtendedRational sup = ExtendedRationalOps.ceil(xs);
        if (inf.ne(sup)) {
            d = d.min(Decoration.DEF);
        } else if (xs.eq(sup)) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval floor(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        ExtendedRational inf = ExtendedRationalOps.floor(xi);
        ExtendedRational sup = ExtendedRationalOps.floor(xs);
        if (inf.ne(sup)) {
            d = d.min(Decoration.DEF);
        } else if (xi.eq(inf)) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval roundTiesToEven(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        ExtendedRational inf = ExtendedRationalOps.roundTiesToEven(xi);
        ExtendedRational sup = ExtendedRationalOps.roundTiesToEven(xs);
        if (inf.ne(sup)) {
            d = d.min(Decoration.DEF);
        } else if (xi.eq(ExtendedRationalOps.sub(inf, Utils.RAT_HALF)) || xs.eq(ExtendedRationalOps.add(sup, Utils.RAT_HALF))) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval roundTiesToAway(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        ExtendedRational inf = ExtendedRationalOps.roundTiesToAway(xi);
        ExtendedRational sup = ExtendedRationalOps.roundTiesToAway(xs);
        if (inf.ne(sup)) {
            d = d.min(Decoration.DEF);
        } else if (xi.eq(ExtendedRationalOps.sub(inf, Utils.RAT_HALF)) || xs.eq(ExtendedRationalOps.add(sup, Utils.RAT_HALF))) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval trunc(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        ExtendedRational inf = ExtendedRationalOps.trunc(xi);
        ExtendedRational sup = ExtendedRationalOps.trunc(xs);
        if (inf.ne(sup)) {
            d = d.min(Decoration.DEF);
        } else if (inf.signum() > 0 && xi.eq(inf) || sup.signum() < 0 && xs.eq(sup)) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval abs(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational inf;
        ExtendedRational sup;
        if (Utils.ZERO.strictPrecedes(x)) {
            inf = x.inf();
            sup = x.sup();
        } else if (x.strictPrecedes(Utils.ZERO)) {
            inf = ExtendedRationalOps.neg(x.sup());
            sup = ExtendedRationalOps.neg(x.inf());
        } else {
            inf = Rational.zero();
            sup = ExtendedRationalOps.max(ExtendedRationalOps.neg(x.inf()), x.sup());
        }
        return Utils.set(inf, sup, x.getDecoration());
    }

    public static SetInterval min(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational inf = ExtendedRationalOps.min(x.inf(), y.inf());
        ExtendedRational sup = ExtendedRationalOps.min(x.sup(), y.sup());
        return Utils.set(inf, sup, d);
    }

    public static SetInterval max(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational inf = ExtendedRationalOps.max(x.inf(), y.inf());
        ExtendedRational sup = ExtendedRationalOps.max(x.sup(), y.sup());
        return Utils.set(inf, sup, d);
    }

    public static SetInterval innerPlus(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        if (x.isCommonInterval() && y.isCommonInterval() && x.wid().ge(y.wid())) {
            ExtendedRational inf = ExtendedRationalOps.add(x.inf(), y.sup());
            ExtendedRational sup = ExtendedRationalOps.add(x.sup(), y.inf());
            return Utils.set(inf, sup, d);
        }
        return EmptyInterval.NaI();
    }

    public static SetInterval innerMinus(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        if (x.isCommonInterval() && y.isCommonInterval() && x.wid().ge(y.wid())) {
            ExtendedRational inf = ExtendedRationalOps.sub(x.inf(), y.inf());
            ExtendedRational sup = ExtendedRationalOps.sub(x.sup(), y.sup());
            return Utils.set(inf, sup, d);
        }
        return EmptyInterval.NaI();
    }

    public static SetInterval intersection(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().max(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();
        ExtendedRational inf = ExtendedRationalOps.max(xi, yi);
        ExtendedRational sup = ExtendedRationalOps.min(xs, ys);
        if (inf.le(sup)) {
            return Utils.set(inf, sup, d);
        } else {
            return EmptyInterval.empty(d);
        }
    }

    public static SetInterval convexHull(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        ExtendedRational inf;
        ExtendedRational sup;
        if (x.isEmpty()) {
            if (y.isEmpty()) {
                return EmptyInterval.empty(d);
            } else {
                inf = y.inf();
                sup = y.sup();
            }
        } else if (y.isEmpty()) {
            inf = x.inf();
            sup = x.sup();
        } else {
            inf = ExtendedRationalOps.min(x.inf(), y.inf());
            sup = ExtendedRationalOps.max(x.sup(), y.sup());
        }
        return Utils.set(inf, sup, d);
    }

    public static SetInterval setDec(SetInterval x, Decoration dec) {
        if (dec == null || x == null) {
            throw new InvalidOperandException();
        }
        if (dec == Decoration.ILL) {
            return EmptyInterval.NaI;
        }
        if (x.isEmpty()) {
            return EmptyInterval.Empty;
        }
        if (dec == Decoration.COM && !x.isCommonInterval()) {
            dec = Decoration.DAC;
        }
        return dec == x.getDecoration() ? x : Utils.set(x.inf(), x.sup(), dec);
    }

}
