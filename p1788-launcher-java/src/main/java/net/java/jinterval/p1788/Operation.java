/*
 * Copyright (c) 2012, JInterval Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. * Redistributions in
 * binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
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
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.p1788;

import java.lang.reflect.Type;
import java.math.BigInteger;
import java.util.Arrays;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.MidRad;
import net.java.jinterval.interval.set.IntvlPartOfNaI;
import net.java.jinterval.interval.set.MulRevPair;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.text2interval.gen.GenP1788;
import net.java.jinterval.text2interval.gen.GenP1788Base;
import org.bridj.Platform;

/**
 *
 */
public enum Operation {

    empty(GenP1788.opEmpty) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.empty();
        }
    },
    entire(GenP1788.opEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.entire();
        }
    },
    nai(GenP1788.opNaI) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.nai();
        }
    },
    convertType(GenP1788.opConvertType) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.hull((SetInterval) a[0]);
        }

    },
    numsToInterval(GenP1788.opNumsToInterval) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.numsToInterval((ExtendedRational) a[0], (ExtendedRational) a[1]);
        }
    },
    numsDecToInterval(GenP1788.opNumsDecToInterval) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.numsDecToInterval((ExtendedRational) a[0], (ExtendedRational) a[1], (Decoration) a[2]);
        }
    },
    textToInterval(GenP1788.opTextToInterval) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.textToInterval((String) a[0]);
        }
    },
    textToDecoratedInterval(GenP1788.opTextToDecoratedInterval) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.textToDecoratedInterval((String) a[0]);
        }
    },
    pos(GenP1788.opPos) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.hull((SetInterval) a[0]);
        }
    },
    neg(GenP1788.opNeg) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.neg((SetInterval) a[0]);
        }
    },
    add(GenP1788.opAdd) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.add((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    sub(GenP1788.opSub) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sub((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    mul(GenP1788.opMul) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.mul((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    div(GenP1788.opDiv) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.div((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    recip(GenP1788.opRecip) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.recip((SetInterval) a[0]);
        }
    },
    sqr(GenP1788.opSqr) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sqr((SetInterval) a[0]);
        }
    },
    sqrt(GenP1788.opSqrt) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sqrt((SetInterval) a[0]);
        }
    },
    fma(GenP1788.opFma) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.fma((SetInterval) a[0], (SetInterval) a[1], (SetInterval) a[2]);
        }
    },
    pown(GenP1788.opPown) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.pown((SetInterval) a[0], (BigInteger) a[1]);
        }
    },
    pow(GenP1788.opPow) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.pow((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    exp(GenP1788.opExp) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.exp((SetInterval) a[0]);
        }
    },
    exp2(GenP1788.opExp2) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.exp2((SetInterval) a[0]);
        }
    },
    exp10(GenP1788.opExp10) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.exp10((SetInterval) a[0]);
        }
    },
    log(GenP1788.opLog) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.log((SetInterval) a[0]);
        }
    },
    log2(GenP1788.opLog2) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.log2((SetInterval) a[0]);
        }
    },
    log10(GenP1788.opLog10) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.log10((SetInterval) a[0]);
        }
    },
    sin(GenP1788.opSin) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sin((SetInterval) a[0]);
        }
    },
    cos(GenP1788.opCos) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.cos((SetInterval) a[0]);
        }
    },
    tan(GenP1788.opTan) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.tan((SetInterval) a[0]);
        }
    },
    asin(GenP1788.opAsin) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.asin((SetInterval) a[0]);
        }
    },
    acos(GenP1788.opAcos) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.acos((SetInterval) a[0]);
        }
    },
    atan(GenP1788.opAtan) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.atan((SetInterval) a[0]);
        }
    },
    atan2(GenP1788.opAtan2) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.atan2((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    sinh(GenP1788.opSinh) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sinh((SetInterval) a[0]);
        }
    },
    cosh(GenP1788.opCosh) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.cosh((SetInterval) a[0]);
        }
    },
    tanh(GenP1788.opTanh) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.tanh((SetInterval) a[0]);
        }
    },
    asinh(GenP1788.opAsinh) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.asinh((SetInterval) a[0]);
        }
    },
    acosh(GenP1788.opAcosh) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.acosh((SetInterval) a[0]);
        }
    },
    atanh(GenP1788.opAtanh) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.atanh((SetInterval) a[0]);
        }
    },
    sign(GenP1788.opSign) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sign((SetInterval) a[0]);
        }
    },
    ceil(GenP1788.opCeil) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.ceil((SetInterval) a[0]);
        }
    },
    floor(GenP1788.opFloor) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.floor((SetInterval) a[0]);
        }
    },
    trunc(GenP1788.opTrunc) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.trunc((SetInterval) a[0]);
        }
    },
    roundTiesToEven(GenP1788.opRoundTiesToEven) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.roundTiesToEven((SetInterval) a[0]);
        }
    },
    roundTiesToAway(GenP1788.opRoundTiesToAway) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.roundTiesToAway((SetInterval) a[0]);
        }
    },
    abs(GenP1788.opAbs) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.abs((SetInterval) a[0]);
        }
    },
    min(GenP1788.opMin) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.min((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    max(GenP1788.opMax) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.max((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    mulRevToPair(GenP1788.opMulRevToPair) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            MulRevPair pair = ctx.mulRevToPair((SetInterval) a[0], (SetInterval) a[1]);
            r[0] = pair.first;
            r[1] = pair.second;
        }
    },
    sqrRev(GenP1788.opSqrRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sqrRev((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    sqrRevEntire(GenP1788.opSqrRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sqrRev((SetInterval) a[0], ENTIRE);
        }
    },
    absRev(GenP1788.opAbsRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.absRev((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    absRevEntire(GenP1788.opAbsRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.absRev((SetInterval) a[0], ENTIRE);
        }
    },
    pownRev(GenP1788.opPownRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.pownRev((SetInterval) a[0], (SetInterval) a[1], (BigInteger) a[2]);
        }
    },
    pownRevEntire(GenP1788.opPownRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.pownRev((SetInterval) a[0], ENTIRE, (BigInteger) a[1]);
        }
    },
    sinRev(GenP1788.opSinRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sinRev((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    sinRevEntire(GenP1788.opSinRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.sinRev((SetInterval) a[0], ENTIRE);
        }
    },
    cosRev(GenP1788.opCosRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.cosRev((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    cosRevEntire(GenP1788.opCosRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.cosRev((SetInterval) a[0], ENTIRE);
        }
    },
    tanRev(GenP1788.opTanRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.tanRev((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    tanRevEntire(GenP1788.opTanRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.tanRev((SetInterval) a[0], ENTIRE);
        }
    },
    coshRev(GenP1788.opCoshRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.coshRev((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    coshRevEntire(GenP1788.opCoshRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.coshRev((SetInterval) a[0], ENTIRE);
        }
    },
    mulRev(GenP1788.opMulRev) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.mulRev((SetInterval) a[0], (SetInterval) a[1], (SetInterval) a[2]);
        }
    },
    mulRevEntire(GenP1788.opMulRevEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.mulRev((SetInterval) a[0], (SetInterval) a[1], ENTIRE);
        }
    },
    powRev1(GenP1788.opPowRev1) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.powRev1((SetInterval) a[0], (SetInterval) a[1], (SetInterval) a[2]);
        }
    },
    powRev1Entire(GenP1788.opPowRev1Entire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.powRev1((SetInterval) a[0], (SetInterval) a[1], ENTIRE);
        }
    },
    powRev2(GenP1788.opPowRev2) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.powRev2((SetInterval) a[0], (SetInterval) a[1], (SetInterval) a[2]);
        }
    },
    powRev2Entire(GenP1788.opPowRev2Entire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.powRev2((SetInterval) a[0], (SetInterval) a[1], ENTIRE);
        }
    },
    atan2Rev1(GenP1788.opAtan2Rev1) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.atan2Rev1((SetInterval) a[0], (SetInterval) a[1], (SetInterval) a[2]);
        }
    },
    atan2Rev1Entire(GenP1788.opAtan2Rev1Entire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.atan2Rev1((SetInterval) a[0], (SetInterval) a[1], ENTIRE);
        }
    },
    atan2Rev2(GenP1788.opAtan2Rev2) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.atan2Rev2((SetInterval) a[0], (SetInterval) a[1], (SetInterval) a[2]);
        }
    },
    atan2Rev2Entire(GenP1788.opAtan2Rev2Entire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.atan2Rev2((SetInterval) a[0], (SetInterval) a[1], ENTIRE);
        }
    },
    cancelMinus(GenP1788.opCancelMinus) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.cancelMinus((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    cancelPlus(GenP1788.opCancelPlus) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.cancelPlus((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    intersection(GenP1788.opIntersection) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.intersection((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    convexHull(GenP1788.opConvexHull) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.convexHull((SetInterval) a[0], (SetInterval) a[1]);
        }
    },
    inf(GenP1788.opInf) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet numberFormat = (BinaryValueSet) contexts[0];
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isNaI() ? null : x.inf(numberFormat);
        }
    },
    sup(GenP1788.opSup) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet numberFormat = (BinaryValueSet) contexts[0];
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isNaI() ? null : x.sup(numberFormat);
        }
    },
    mid(GenP1788.opMid) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet numberFormat = (BinaryValueSet) contexts[0];
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isEmpty() ? null : x.mid(numberFormat);
        }
    },
    rad(GenP1788.opRad) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet numberFormat = (BinaryValueSet) contexts[0];
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isEmpty() ? null : x.rad(numberFormat);
        }
    },
    wid(GenP1788.opWid) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet numberFormat = (BinaryValueSet) contexts[0];
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isEmpty() ? null : x.wid(numberFormat);
        }
    },
    mag(GenP1788.opMag) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet numberFormat = (BinaryValueSet) contexts[0];
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isEmpty() ? null : x.mag(numberFormat);
        }
    },
    mig(GenP1788.opMig) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet numberFormat = (BinaryValueSet) contexts[0];
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isEmpty() ? null : x.mig(numberFormat);
        }
    },
    midRad(GenP1788.opMidRad) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet midNumberFormat = (BinaryValueSet) contexts[0];
            BinaryValueSet radNumberFormat = (BinaryValueSet) contexts[1];
            SetInterval x = (SetInterval) a[0];
            if (x.isEmpty()) {
                r[0] = r[1] = null;
            } else {
                MidRad midRad = x.midRad(midNumberFormat, radNumberFormat);
                r[0] = midRad.mid;
                r[1] = midRad.rad;
            }
        }
    },
    isEmpty(GenP1788.opIsEmpty) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            r[0] = !x.isNaI() && x.isEmpty();
        }
    },
    isEntire(GenP1788.opIsEntire) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            r[0] = !x.isNaI() && x.isEntire();
        }
    },
    isNaI(GenP1788.opIsNaI) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            r[0] = x.isNaI();
        }
    },
    isCommonInterval(GenP1788.opIsCommonInterval) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            r[0] = !x.isNaI() && x.isCommonInterval();
        }
    },
    isSingleton(GenP1788.opIsSingleton) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            r[0] = !x.isNaI() && x.isSingleton();
        }
    },
    isMember(GenP1788.opIsMember) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            ExtendedRational m = (ExtendedRational) a[0];
            SetInterval x = (SetInterval) a[1];
            r[0] = m != null && !x.isNaI() && x.isMember(m);
        }
    },
    equal(GenP1788.opEqual) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.equal(y);
        }
    },
    subset(GenP1788.opSubset) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.subset(y);
        }
    },
    less(GenP1788.opLess) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.less(y);
        }
    },
    precedes(GenP1788.opPrecedes) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.precedes(y);
        }
    },
    interior(GenP1788.opInterior) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.interior(y);
        }
    },
    strictLess(GenP1788.opStrictLess) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.strictLess(y);
        }
    },
    strictPrecedes(GenP1788.opStrictPrecedes) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.strictPrecedes(y);
        }
    },
    disjoint(GenP1788.opDisjoint) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() && x.disjoint(y);
        }
    },
    overlap(GenP1788.opOverlap) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetInterval x = (SetInterval) a[0];
            SetInterval y = (SetInterval) a[1];
            r[0] = !x.isNaI() && !y.isNaI() ? x.overlap(y) : null;
        }
    },
    newDec(GenP1788.opNewDec) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.newDec((SetInterval) a[0]);
        }
    },
    intervalPart(GenP1788.opIntervalPart) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            SetInterval x = (SetInterval) a[0];
            if (x.isNaI()) {
                throw new IntvlPartOfNaI();
            }
            r[0] = ctx.newDec((SetInterval) a[0]);
        }
    },
    decorationPart(GenP1788.opDecorationPart) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            r[0] = ((SetInterval) a[0]).getDecoration();
        }
    },
    setDec(GenP1788.opSetDec) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            SetIntervalContext ctx = (SetIntervalContext) contexts[0];
            r[0] = ctx.setDec((SetInterval) a[0], (Decoration) a[1]);
        }
    },
    intervalToExact(GenP1788.opIntervalToExact) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet valueSet = (BinaryValueSet) contexts[0];
            r[0] = ((SetInterval) a[0]).intervalToExact(valueSet);
        }
    },
    intervalToDecoratedExact(GenP1788.opIntervalToExact) {
        @Override
        void eval(Object[] contexts, Object[] r, Object... a) {
            BinaryValueSet valueSet = (BinaryValueSet) contexts[0];
            r[0] = ((SetInterval) a[0]).intervalToExactDecorated(valueSet);
        }
    };

    private final GenP1788Base.Operation oper;
    private final Type[] parameters;

    private Operation(GenP1788Base.Operation oper) {
        this.oper = oper;
        parameters = new Type[oper.results.length + oper.args.length];
        Arrays.fill(parameters, Platform.is64Bits() ? long.class : int.class);
    }

    GenP1788Base.Operation getBaseOperation() {
        return oper;
    }

    Type[] getParameters() {
        return parameters;
    }

    abstract void eval(Object[] contexts, Object[] r, Object... a);

    private static SetInterval ENTIRE
            = SetIntervalOps.nums2(ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY);
}
