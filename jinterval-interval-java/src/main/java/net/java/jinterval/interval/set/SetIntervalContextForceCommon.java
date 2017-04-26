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
import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
class SetIntervalContextForceCommon implements SetIntervalContext {

    private final SetIntervalContext impl;

    SetIntervalContextForceCommon(SetIntervalContext impl) {
        this.impl = impl;
    }

    @Override
    public SetInterval hull(SetInterval x) {
        return checkClassic(impl.hull(x));
    }

    @Override
    public SetInterval empty() {
        throw nonclassic();
    }

    @Override
    public SetInterval entire() {
        throw nonclassic();
    }

    @Override
    public SetInterval nai() {
        throw nonclassic();
    }

    @Override
    public SetInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
        return checkClassic(impl.numsToInterval(l, u));
    }

    @Override
    public SetInterval numsToInterval(double l, double u) {
        return checkClassic(impl.numsToInterval(l, u));
    }

    @Override
    public SetInterval numsToInterval(float l, float u) {
        return checkClassic(impl.numsToInterval(l, u));
    }

    @Override
    public SetInterval numsDecToInterval(ExtendedRational l, ExtendedRational u, Decoration decoration) {
        return checkClassic(impl.numsDecToInterval(l, u, decoration));
    }

    @Override
    public SetInterval numsDecToInterval(double l, double u, Decoration decoration) {
        return checkClassic(impl.numsDecToInterval(l, u, decoration));
    }

    @Override
    public SetInterval numsDecToInterval(float l, float u, Decoration decoration) {
        return checkClassic(impl.numsDecToInterval(l, u, decoration));
    }

    @Override
    public SetInterval textToInterval(String s) {
        return checkClassic(impl.textToInterval(s));
    }

    @Override
    public SetInterval textToDecoratedInterval(String s) {
        return checkClassic(impl.textToInterval(s));
    }

    @Override
    public SetInterval pi() {
        return checkClassic(impl.pi());
    }

    @Override
    public SetInterval euler() {
        return checkClassic(impl.euler());
    }

    @Override
    public SetInterval neg(SetInterval x) {
        return checkClassic(impl.neg(x));
    }

    @Override
    public SetInterval add(SetInterval x, SetInterval y) {
        return checkClassic(impl.add(x, y));
    }

    @Override
    public SetInterval sub(SetInterval x, SetInterval y) {
        return checkClassic(impl.sub(x, y));
    }

    @Override
    public SetInterval mul(SetInterval x, SetInterval y) {
        return checkClassic(impl.mul(x, y));
    }

    @Override
    public SetInterval div(SetInterval x, SetInterval y) {
        if (y.inf().signum() <= 0 && y.sup().signum() >= 0) {
            throw nonclassic();
        }
        return checkClassic(impl.div(x, y));
    }

    @Override
    public SetInterval recip(SetInterval x) {
        return checkClassic(impl.recip(x));
    }

    @Override
    public SetInterval sqr(SetInterval x) {
        return checkClassic(impl.sqr(x));
    }

    @Override
    public SetInterval sqrt(SetInterval x) {
        return checkClassic(impl.sqrt(x));
    }

    @Override
    public SetInterval fma(SetInterval x, SetInterval y, SetInterval z) {
        return checkClassic(impl.fma(x, y, z));
    }

    @Override
    public SetInterval pown(SetInterval x, BigInteger p) {
        return checkClassic(impl.pown(x, p));
    }

    @Override
    public SetInterval pown(SetInterval x, long p) {
        return checkClassic(impl.pown(x, p));
    }

    @Override
    public SetInterval pown(SetInterval x, int p) {
        return checkClassic(impl.pown(x, p));
    }

    @Override
    public SetInterval pow(SetInterval x, SetInterval y) {
        return checkClassic(impl.pow(x, y));
    }

    @Override
    public SetInterval exp(SetInterval x) {
        return checkClassic(impl.exp(x));
    }

    @Override
    public SetInterval exp2(SetInterval x) {
        return checkClassic(impl.exp2(x));
    }

    @Override
    public SetInterval exp10(SetInterval x) {
        return checkClassic(impl.exp10(x));
    }

    @Override
    public SetInterval log(SetInterval x) {
        return checkClassic(impl.log(x));
    }

    @Override
    public SetInterval log2(SetInterval x) {
        return checkClassic(impl.log2(x));
    }

    @Override
    public SetInterval log10(SetInterval x) {
        return checkClassic(impl.log10(x));
    }

    @Override
    public SetInterval sin(SetInterval x) {
        return checkClassic(impl.sin(x));
    }

    @Override
    public SetInterval cos(SetInterval x) {
        return checkClassic(impl.cos(x));
    }

    @Override
    public SetInterval tan(SetInterval x) {
        return checkClassic(impl.tan(x));
    }

    @Override
    public SetInterval asin(SetInterval x) {
        return checkClassic(impl.asin(x));
    }

    @Override
    public SetInterval acos(SetInterval x) {
        return checkClassic(impl.atan(x));
    }

    @Override
    public SetInterval atan(SetInterval x) {
        return checkClassic(impl.atan(x));
    }

    @Override
    public SetInterval atan2(SetInterval y, SetInterval x) {
        return checkClassic(impl.atan2(y, x));
    }

    @Override
    public SetInterval sinh(SetInterval x) {
        return checkClassic(impl.sinh(x));
    }

    @Override
    public SetInterval cosh(SetInterval x) {
        return checkClassic(impl.cosh(x));
    }

    @Override
    public SetInterval tanh(SetInterval x) {
        return checkClassic(impl.tanh(x));
    }

    @Override
    public SetInterval asinh(SetInterval x) {
        return checkClassic(impl.asinh(x));
    }

    @Override
    public SetInterval acosh(SetInterval x) {
        return checkClassic(impl.acosh(x));
    }

    @Override
    public SetInterval atanh(SetInterval x) {
        return checkClassic(impl.atanh(x));
    }

    @Override
    public SetInterval sign(SetInterval x) {
        return checkClassic(impl.sign(x));
    }

    @Override
    public SetInterval ceil(SetInterval x) {
        return checkClassic(impl.ceil(x));
    }

    @Override
    public SetInterval floor(SetInterval x) {
        return checkClassic(impl.floor(x));
    }

    @Override
    public SetInterval trunc(SetInterval x) {
        return checkClassic(impl.trunc(x));
    }

    @Override
    public SetInterval roundTiesToEven(SetInterval x) {
        return checkClassic(impl.roundTiesToEven(x));
    }

    @Override
    public SetInterval roundTiesToAway(SetInterval x) {
        return checkClassic(impl.roundTiesToAway(x));
    }

    @Override
    public SetInterval abs(SetInterval x) {
        return checkClassic(impl.abs(x));
    }

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2) {
        return checkClassic(impl.min(x1, x2));
    }

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2, SetInterval... xn) {
        return checkClassic(impl.min(x1, x2, xn));
    }

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2) {
        return checkClassic(impl.max(x1, x2));
    }

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2, SetInterval... xn) {
        return checkClassic(impl.max(x1, x2));
    }

    @Override
    public SetInterval sqrRev(SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval absRev(SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, BigInteger p) {
        throw nonclassic();
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, long p) {
        throw nonclassic();
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, int p) {
        throw nonclassic();
    }

    @Override
    public SetInterval sinRev(SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval cosRev(SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval tanRev(SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval coshRev(SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval mulRev(SetInterval b, SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval powRev1(SetInterval b, SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval powRev2(SetInterval a, SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval atan2Rev1(SetInterval b, SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public SetInterval atan2Rev2(SetInterval a, SetInterval c, SetInterval x) {
        throw nonclassic();
    }

    @Override
    public MulRevPair mulRevToPair(SetInterval b, SetInterval c) {
        throw nonclassic();
    }

    @Override
    public SetInterval cancelMinus(SetInterval x, SetInterval y) {
        return checkClassic(cancelMinus(x, y));
    }

    @Override
    public SetInterval cancelPlus(SetInterval x, SetInterval y) {
        return checkClassic(cancelPlus(x, y));
    }

    @Override
    public SetInterval intersection(SetInterval x, SetInterval y) {
        checkClassic(x);
        checkClassic(y);
        SetInterval r = impl.intersection(x, y);
        if (!r.isCommonInterval()) {
            throw nonclassic();
        }
        return Utils.classic((Rational) r.inf(), (Rational) r.sup());
    }

    @Override
    public SetInterval convexHull(SetInterval x, SetInterval y) {
        checkClassic(x);
        checkClassic(y);
        SetInterval r = impl.convexHull(x, y);
        if (!r.isCommonInterval()) {
            throw nonclassic();
        }
        return Utils.classic((Rational) r.inf(), (Rational) r.sup());
    }

    @Override
    public SetInterval setDec(SetInterval x, Decoration dec) {
        checkClassic(x);
        if (dec != Decoration.COM) {
            throw nonclassic();
        }
        return checkClassic(impl.setDec(x, dec));
    }

    @Override
    public SetInterval rootn(SetInterval x, BigInteger q) {
        return checkClassic(impl.rootn(x, q));
    }

    @Override
    public SetInterval rootn(SetInterval x, long q) {
        return checkClassic(impl.rootn(x, q));
    }

    @Override
    public SetInterval rootn(SetInterval x, int q) {
        return checkClassic(impl.rootn(x, q));
    }

    @Override
    public SetInterval hypot(SetInterval x, SetInterval y) {
        return checkClassic(impl.hypot(x, y));
    }

    @Override
    public SetInterval newDec(SetInterval x) {
        return checkClassic(impl.newDec(x));
    }

    private static SetInterval checkClassic(SetInterval r) {
        if (r instanceof ClassicInterval && r.getDecoration() == Decoration.COM) {
            return r;
        }
        throw nonclassic();
    }

    private static ArithmeticException nonclassic() {
        return new ArithmeticException("nonclassic");
    }
}
