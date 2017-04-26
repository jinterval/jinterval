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
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContexts;

/**
 *
 */
class SetIntervalContextPlain extends SetIntervalContextInfSup {

    SetIntervalContextPlain() {
        super(
                ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64),
                ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64));
    }

    @Override
    public SetInterval hull(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x) || x.isEmpty()) {
            return x;
        } else {
            return Utils.set(x.doubleInf(), x.doubleSup(), x.getDecoration());
        }
    }

    @Override
    public SetInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
        return SetIntervalOps.nums2(l.doubleValueFloor(), u.doubleValueCeiling());
    }

    @Override
    public SetInterval numsToInterval(double l, double u) {
        return SetIntervalOps.nums2(l, u);
    }

    @Override
    public SetInterval numsDecToInterval(ExtendedRational l, ExtendedRational u, Decoration decoration) {
        return SetIntervalOps.nums2(l.doubleValueFloor(), u.doubleValueCeiling(), decoration);
    }

    @Override
    public SetInterval numsDecToInterval(double l, double u, Decoration decoration) {
        return SetIntervalOps.nums2(l, u, decoration);
    }

    @Override
    public SetInterval pi() {
        return Utils.set(Math.PI, Math.PI);
    }

    @Override
    public SetInterval euler() {
        return Utils.set(Math.E, Math.E);
    }

    @Override
    public SetInterval neg(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.negate(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval add(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        return DIEF.addNearest(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval sub(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        return DIEF.subtractNearest(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval mul(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        return DIEF.multiplyNearest(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval div(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        return DIEF.divideNearest(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval recip(SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return DIEF.recipNearest(x.doubleInf(), x.doubleSup(), d);
    }

    @Override
    public SetInterval sqr(SetInterval x) {
        return DIEF.sqr(x);
    }

    @Override
    public SetInterval sqrt(SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return DIEF.sqrtNearest(x.doubleInf(), x.doubleSup(), d);
    }

    @Override
    public SetInterval fma(SetInterval x, SetInterval y, SetInterval z) {
        Decoration d = x.getDecoration().min(y.getDecoration()).min(z.getDecoration());
        if (x.isEmpty() || y.isEmpty() || z.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        SetInterval xy = DIEF.multiplyNearest(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
        return DIEF.addNearest(xy.doubleInf(), xy.doubleSup(), x.doubleInf(), x.doubleSup(), d);
    }

    @Override
    public SetInterval pown(SetInterval x, BigInteger p) {
        return DIEF.power(x, p.longValue());
    }

    @Override
    public SetInterval pown(SetInterval x, long p) {
        return DIEF.power(x, p);
    }

    @Override
    public SetInterval pown(SetInterval x, int p) {
        return DIEF.power(x, p);
    }

    @Override
    public SetInterval pow(SetInterval x, SetInterval y) {
        return DIEF.power(x, y);
    }

    @Override
    public SetInterval exp(SetInterval x) {
        return DIEF.exp(x);
    }

    @Override
    public SetInterval exp2(SetInterval x) {
        return DIEF.exp2(x);
    }

    @Override
    public SetInterval exp10(SetInterval x) {
        return DIEF.exp10(x);
    }

    @Override
    public SetInterval log(SetInterval x) {
        return DIEF.log(x);
    }

    @Override
    public SetInterval log2(SetInterval x) {
        return DIEF.log2(x);
    }

    @Override
    public SetInterval log10(SetInterval x) {
        return DIEF.log10(x);
    }

    @Override
    public SetInterval sin(SetInterval x) {
        return DIEF.sin(x);
    }

    @Override
    public SetInterval cos(SetInterval x) {
        return DIEF.cos(x);
    }

    @Override
    public SetInterval tan(SetInterval x) {
        return DIEF.tan(x);
    }

    @Override
    public SetInterval asin(SetInterval x) {
        return DIEF.asin(x);
    }

    @Override
    public SetInterval acos(SetInterval x) {
        return DIEF.acos(x);
    }

    @Override
    public SetInterval atan(SetInterval x) {
        return DIEF.atan(x);
    }

    @Override
    public SetInterval atan2(SetInterval y, SetInterval x) {
        return super.atan2(y, x);
    }

    @Override
    public SetInterval sinh(SetInterval x) {
        return DIEF.sinh(x);
    }

    @Override
    public SetInterval cosh(SetInterval x) {
        return DIEF.cosh(x);
    }

    @Override
    public SetInterval tanh(SetInterval x) {
        return super.tanh(x);
    }

    @Override
    public SetInterval asinh(SetInterval x) {
        return super.asinh(x);
    }

    @Override
    public SetInterval acosh(SetInterval x) {
        return super.cosh(x);
    }

    @Override
    public SetInterval atanh(SetInterval x) {
        return super.atanh(x);
    }

    @Override
    public SetInterval sign(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.sign(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval ceil(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.ceil(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval floor(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.floor(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval trunc(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.trunc(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval roundTiesToEven(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.roundTiesToEven(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval roundTiesToAway(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.roundTiesToAway(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval abs(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return SetUtils.abs(x.doubleInf(), x.doubleSup(), x.getDecoration());
    }

    @Override
    public SetInterval max(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        return SetUtils.max(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval min(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        return SetUtils.min(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval cancelMinus(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        if (y.isEmpty()) {
            return EmptyInterval.NaI();
        }
        return DIEF.cancelMinusNearest(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval cancelPlus(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        if (y.isEmpty()) {
            return EmptyInterval.NaI();
        }
        return DIEF.cancelPlusNearest(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
    }

    @Override
    public SetInterval convexHull(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration()).min(Decoration.TRV);
        if (x.isEmpty()) {
            if (y.isEmpty()) {
                return EmptyInterval.empty(d);
            } else {
                return Utils.set(x.doubleInf(), x.doubleSup(), d);
            }
        } else if (y.isEmpty()) {
            return Utils.set(y.doubleInf(), y.doubleSup(), d);
        } else {
            return SetUtils.convexHull(x.doubleInf(), x.doubleSup(), y.doubleInf(), y.doubleSup(), d);
        }
    }

    @Override
    public SetInterval hypot(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        SetInterval x2 = DIEF.sqr(x);
        SetInterval y2 = DIEF.sqr(y);
        SetInterval x2y2 = DIEF.addNearest(x2.doubleInf(), x2.doubleSup(), y2.doubleInf(), y2.doubleSup(), d);
        return DIEF.sqrtNearest(x2y2.doubleInf(), x2y2.doubleSup(), d);
    }
}
