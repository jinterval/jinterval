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

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;

/**
 *
 */
class SetIntervalContextNearest extends SetIntervalContextInfSupBase {

    SetIntervalContextNearest() {
        this(ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64));
    }

    private SetIntervalContextNearest(ExtendedRationalContext mc) {
        super(mc, mc);
    }

    @Override
    public SetInterval hull(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x) || x.isEmpty()) {
            return x;
        } else {
            return Utils.set(x.inf().doubleValueHalfEven(), x.sup().doubleValueHalfEven(), x.getDecoration());
        }
    }

    @Override
    public SetInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
        return SetIntervalOps.nums2(
                l != null ? l.doubleValueHalfEven() : Double.NaN,
                u != null ? u.doubleValueHalfEven() : Double.NaN);
    }

    @Override
    public SetInterval numsToInterval(double l, double u) {
        return SetIntervalOps.nums2(l, u);
    }

    @Override
    public SetInterval numsDecToInterval(ExtendedRational l, ExtendedRational u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        return SetIntervalOps.nums2(
                l != null ? l.doubleValueHalfEven() : Double.NaN,
                u != null ? u.doubleValueHalfEven() : Double.NaN,
                decoration);
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
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.negate(x.doubleInf(), x.doubleSup(), x.getDecoration());
        } else {
            return super.neg(x);
        }
    }

    @Override
    public SetInterval add(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return DIEF.addNearest(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.add(x, y);
        }
    }

    @Override
    public SetInterval sub(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return DIEF.subtractNearest(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.sub(x, y);
        }
    }

    @Override
    public SetInterval mul(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return DIEF.multiplyNearest(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.mul(x, y);
        }
    }

    @Override
    public SetInterval div(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return DIEF.divideNearest(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.div(x, y);
        }
    }

    @Override
    public SetInterval recip(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return DIEF.recipNearest(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.recip(x);
        }
    }

    @Override
    public SetInterval sqrt(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return DIEF.sqrtNearest(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.sqrt(x);
        }
    }

    @Override
    public SetInterval sign(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.sign(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.sign(x);
        }
    }

    @Override
    public SetInterval ceil(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.ceil(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.ceil(x);
        }
    }

    @Override
    public SetInterval floor(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.floor(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.floor(x);
        }
    }

    @Override
    public SetInterval trunc(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.trunc(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.trunc(x);
        }
    }

    @Override
    public SetInterval roundTiesToEven(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.roundTiesToEven(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.roundTiesToEven(x);
        }
    }

    @Override
    public SetInterval roundTiesToAway(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.roundTiesToAway(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.roundTiesToAway(x);
        }
    }

    @Override
    public SetInterval abs(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return SetUtils.abs(
                    x.doubleInf(), x.doubleSup(),
                    x.getDecoration());
        } else {
            return super.abs(x);
        }
    }

    @Override
    public SetInterval min(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return SetUtils.min(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.min(x, y);
        }
    }

    @Override
    public SetInterval max(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return SetUtils.max(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.max(x, y);
        }
    }

    @Override
    public SetInterval cancelMinus(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return DIEF.cancelMinusNearest(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.cancelMinus(x, y);
        }
    }

    @Override
    public SetInterval cancelPlus(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return DIEF.cancelPlusNearest(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.cancelPlus(x, y);
        }
    }

    @Override
    public SetInterval intersection(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return SetUtils.intersection(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().max(y.getDecoration()));
        } else {
            return super.intersection(x, y);
        }
    }

    @Override
    public SetInterval convexHull(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            return SetUtils.convexHull(
                    x.doubleInf(), x.doubleSup(),
                    y.doubleInf(), y.doubleSup(),
                    x.getDecoration().min(y.getDecoration()));
        } else {
            return super.convexHull(x, y);
        }
    }
}
