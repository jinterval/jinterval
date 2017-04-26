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
package net.java.jinterval.interval.set;

import java.math.BigInteger;
import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public class SetIntervalEvaluatorBareTightest64 extends SetIntervalEvaluator {

    private final double[] bounds;
    private static final SetIntervalContext ic = SetIntervalContexts.getTightest64();

    SetIntervalEvaluatorBareTightest64(CodeList codeList, Expression[] results) {
        super(codeList, results);
        bounds = new double[2 * codeList.getNumExprs()];
        codeList.acceptConstants(this);
    }

    SetIntervalEvaluatorBareTightest64(int size) {
        bounds = new double[2 * size];
    }

    @Override
    public SetInterval get(int i) {
        double inf = getInf(i);
        double sup = getSup(i);
        if (Double.isNaN(inf)) {
            return EmptyInterval.Empty;
        } else {
            return Utils.set(inf, sup, Decoration.TRV);
        }
    }

    @Override
    public void set(int i, SetInterval v) {
        if (v.isNaI()) {
            throw new IllegalArgumentException();
        }
        set(i, v.doubleInf(), v.doubleSup());
    }

    double getInf(int i) {
        return bounds[2 * i];
    }

    double getSup(int i) {
        return bounds[2 * i + 1];
    }

    void set(int i, double inf, double sup) {
        bounds[2 * i] = inf;
        bounds[2 * i + 1] = sup;
    }

    void setEmpty(int i) {
        set(i, Double.NaN, Double.NaN);
    }

    @Override
    public void visitInp(int r, String name) {
    }

    @Override
    public void visitLit(int r, String numerator, String denominator) {
        set(r, ic.textToInterval("[" + numerator + "/" + denominator + "]"));
    }

    @Override
    public void visitLit(int r, String literal) {
        set(r, ic.textToInterval("[" + literal + "]"));
    }

    @Override
    public void visitInterval(int r, String inf, String sup) {
        set(r, ic.textToInterval("[" + inf + "," + sup + "]"));
    }

    @Override
    public void visitNum(int r, Number num) {
        if (num instanceof Double
                || num instanceof Float
                || num instanceof Integer
                || num instanceof Short
                || num instanceof Byte) {
            double v = num.doubleValue();
            if (!Double.isFinite(v)) {
                throw new IllegalArgumentException();
            }
            set(r, v, v);
        } else {
            Rational rat = Rational.valueOf(num);
            set(r, rat.doubleValueFloor(), rat.doubleValueCeiling());
        }
    }

    @Override
    public void visitPi(int r) {
        set(r, SetIntervalContextAccur64.piInf, SetIntervalContextAccur64.piSup);
    }

    @Override
    public void visitEuler(int r) {
        set(r, SetIntervalContextAccur64.eulerInf, SetIntervalContextAccur64.eulerSup);
    }

    @Override
    public void visitNeg(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        set(r, -xs, -xi);
    }

    @Override
    public void visitAdd(int r, int x, int y) {
        double xi = getInf(x);
        double xs = getSup(x);
        double yi = getInf(y);
        double ys = getSup(y);
        set(r, Utils.addDn(xi, yi), Utils.addUp(xs, ys));
    }

    @Override
    public void visitSub(int r, int x, int y) {
        double xi = getInf(x);
        double xs = getSup(x);
        double yi = getInf(y);
        double ys = getSup(y);
        set(r, Utils.subDn(xi, ys), Utils.subUp(xs, yi));
    }

    @Override
    public void visitMul(int r, int x, int y) {
        double xi = getInf(x);
        double xs = getSup(x);
        double yi = getInf(y);
        double ys = getSup(y);
        if (Double.isNaN(xi + yi)) {
            setEmpty(r);
            return;
        }

        double inf, sup;

        //[ 0, 0 ] * x = x * [ 0, 0 ] = [ 0, 0 ]
        if ((xi == 0 && xs == 0) || (yi == 0 && ys == 0)) {
            inf = sup = 0;
        } else if (ys <= 0) {
            if (xs <= 0) {
                inf = Utils.mulDn(-xs, -ys);
                sup = Utils.mulUp(-xi, -yi);
            } else if (xi >= 0) {
                inf = -Utils.mulUp(xs, -yi);
                sup = -Utils.mulDn(xi, -ys);
            } else {
                inf = -Utils.mulUp(xs, -yi);
                sup = Utils.mulUp(-xi, -yi);
            }
        } else if (yi >= 0) {
            if (xs <= 0) {
                inf = -Utils.mulUp(-xi, ys);
                sup = -Utils.mulDn(-xs, yi);
            } else if (xi >= 0) {
                inf = Utils.mulDn(xi, yi);
                sup = Utils.mulUp(xs, ys);
            } else {
                inf = -Utils.mulUp(-xi, ys);
                sup = Utils.mulUp(xs, ys);
            }
        } else if (xs <= 0) {
            inf = -Utils.mulUp(-xi, ys);
            sup = Utils.mulUp(-xi, -yi);
        } else if (xi >= 0) {
            inf = -Utils.mulUp(xs, -yi);
            sup = Utils.mulUp(xs, ys);
        } else {
            inf = -Math.max(Utils.mulUp(-xi, ys), Utils.mulUp(xs, -yi));
            sup = Math.max(Utils.mulUp(-xi, -yi), Utils.mulUp(xs, ys));
        }

        set(r, inf, sup);
    }

    @Override
    public void visitDiv(int r, int x, int y) {
        double xi = getInf(x);
        double xs = getSup(x);
        double yi = getInf(y);
        double ys = getSup(y);
        if (Double.isNaN(xi + yi)) {
            setEmpty(r);
            return;
        }

        double inf, sup;
        if (yi > 0) {
            if (xi > 0) { // x > 0, y > 0
                inf = Utils.divDn(xi, ys);
                sup = Utils.divUp(xs, yi);
            } else if (xs < 0) { // x < 0, y > 0
                inf = -Utils.divUp(-xi, yi);
                sup = -Utils.divDn(-xs, ys);
            } else { // 0 in x, y > 0
                inf = -Utils.divUp(-xi, yi);
                sup = Utils.divUp(xs, yi);
            }
        } else if (ys < 0) {
            if (xi > 0) { // x > 0, y < 0
                inf = -Utils.divUp(xs, -ys);
                sup = -Utils.divDn(xi, -yi);
            } else if (xs < 0) { // x < 0, y < 0
                inf = Utils.divDn(-xs, -yi);
                sup = Utils.divUp(-xi, -ys);
            } else { // 0 in x, y < 0
                inf = -Utils.divUp(xs, -ys);
                sup = Utils.divUp(-xi, -ys);
            }
        } else { // 0 in y
            if (yi == 0 && ys == 0) {
                setEmpty(r);
                return;
            }
            if (xi == 0 && xs == 0) {
                inf = sup = 0;
            } else if (xi >= 0) {
                inf = yi == 0 ? Utils.divDn(xi, ys) : Double.NEGATIVE_INFINITY;
                sup = ys == 0 ? -Utils.divDn(xi, -yi) : Double.POSITIVE_INFINITY;
            } else if (xs <= 0) {
                inf = ys == 0 ? Utils.divDn(-xs, -yi) : Double.NEGATIVE_INFINITY;
                sup = yi == 0 ? -Utils.divDn(-xs, ys) : Double.POSITIVE_INFINITY;
            } else if (Double.isNaN(xi)) {
                inf = sup = Double.NaN;
            } else {
                inf = Double.NEGATIVE_INFINITY;
                sup = Double.POSITIVE_INFINITY;
            }
        }
        set(r, inf, sup);
    }

    @Override
    public void visitRecip(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        if (xi > 0 || xs < 0) {
            set(r, Utils.divDn(1, xs), Utils.divUp(1, xi));
        } else if (xs < 0) {
            set(r, -Utils.divUp(1, -xs), -Utils.divDn(1, -xi));
        } else if (xi == 0 && xs == 0) {
            setEmpty(r);
        } else {
            double inf = xi == 0 ? Utils.divDn(1, xs) : Double.NEGATIVE_INFINITY;
            double sup = xs == 0 ? -Utils.divDn(1, -xi) : Double.POSITIVE_INFINITY;
            set(r, inf, sup);
        }
    }

    @Override
    public void visitSqr(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        double inf;
        double sup;
        if (xi >= 0) {
            inf = Utils.mulDn(xi, xi);
            sup = Utils.mulUp(xs, xs);
        } else if (xs <= 0) {
            inf = Utils.mulDn(-xs, -xs);
            sup = Utils.mulUp(-xi, -xi);
        } else {
            double xa = Math.max(-xi, xs);
            inf = 0;
            sup = Utils.mulUp(xa, xa);
        }
        set(r, inf, sup);
    }

    @Override
    public void visitSqrt(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        if (xi >= 0) {
            set(r, Utils.sqrtDn(xi), Utils.sqrtUp(xs));
        } else if (xs < 0) {
            setEmpty(r);
        } else {
            set(r, 0, Utils.sqrtUp(xs));
        }
    }

    @Override
    public void visitFma(int r, int x, int y, int z) {
        set(r, ic.fma(get(x), get(y), get(z)));
    }

    @Override
    public void visitPown(int r, int x, BigInteger p) {
        set(r, ic.pown(get(x), p));
    }

    @Override
    public void visitPown(int r, int x, long p) {
        set(r, ic.pown(get(x), p));
    }

    @Override
    public void visitPown(int r, int x, int p) {
        set(r, ic.pown(get(x), p));
    }

    @Override
    public void visitPow(int r, int x, int y) {
        set(r, ic.pow(get(x), get(y)));
    }

    @Override
    public void visitExp(int r, int x) {
        set(r, ic.exp(get(x)));
    }

    @Override
    public void visitExp2(int r, int x) {
        set(r, ic.exp2(get(x)));
    }

    @Override
    public void visitExp10(int r, int x) {
        set(r, ic.exp10(get(x)));
    }

    @Override
    public void visitLog(int r, int x) {
        set(r, ic.log(get(x)));
    }

    @Override
    public void visitLog2(int r, int x) {
        set(r, ic.log2(get(x)));
    }

    @Override
    public void visitLog10(int r, int x) {
        set(r, ic.log10(get(x)));
    }

    @Override
    public void visitSin(int r, int x) {
        set(r, ic.sin(get(x)));
    }

    @Override
    public void visitCos(int r, int x) {
        set(r, ic.cos(get(x)));
    }

    @Override
    public void visitTan(int r, int x) {
        set(r, ic.tan(get(x)));
    }

    @Override
    public void visitAsin(int r, int x) {
        set(r, ic.asin(get(x)));
    }

    @Override
    public void visitAcos(int r, int x) {
        set(r, ic.acos(get(x)));
    }

    @Override
    public void visitAtan(int r, int x) {
        set(r, ic.atan(get(x)));
    }

    @Override
    public void visitAtan2(int r, int y, int x) {
        set(r, ic.atan2(get(y), get(x)));
    }

    @Override
    public void visitSinh(int r, int x) {
        set(r, ic.sinh(get(x)));
    }

    @Override
    public void visitCosh(int r, int x) {
        set(r, ic.cosh(get(x)));
    }

    @Override
    public void visitTanh(int r, int x) {
        set(r, ic.tanh(get(x)));
    }

    @Override
    public void visitAsinh(int r, int x) {
        set(r, ic.asinh(get(x)));
    }

    @Override
    public void visitAcosh(int r, int x) {
        set(r, ic.acosh(get(x)));
    }

    @Override
    public void visitAtanh(int r, int x) {
        set(r, ic.atanh(get(x)));
    }

    @Override
    public void visitSign(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        double inf;
        double sup;
        if (xi > 0) {
            inf = sup = 1;
        } else if (xs < 0) {
            inf = sup = -1;
        } else {
            inf = xi < 0 ? -1 : 0;
            sup = xs > 0 ? 1 : 0;
        }
        set(r, inf, sup);
    }

    @Override
    public void visitCeil(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        double inf = Math.ceil(xi);
        double sup = Math.ceil(xs);
        set(r, inf, sup);
    }

    @Override
    public void visitFloor(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        double inf = Math.floor(xi);
        double sup = Math.floor(xs);
        set(r, inf, sup);
    }

    @Override
    public void visitTrunc(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        double inf;
        double sup;
        if (xi >= 0) {
            inf = Math.floor(xi);
            sup = Math.floor(xs);
        } else if (xs <= 0) {
            inf = Math.ceil(xi);
            sup = Math.floor(xs);
        } else {
            inf = Math.ceil(xi);
            sup = Math.floor(xs);
        }
        set(r, inf, sup);
    }

    @Override
    public void visitRoundTiesToEven(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        double inf = Math.rint(xi);
        double sup = Math.rint(xs);
        set(r, inf, sup);
    }

    @Override
    public void visitRoundTiesToAway(int r, int x) {
        set(r, ic.roundTiesToAway(get(x)));
    }

    @Override
    public void visitAbs(int r, int x) {
        double xi = getInf(x);
        double xs = getSup(x);
        if (Double.isNaN(xi)) {
            setEmpty(r);
            return;
        }
        double inf;
        double sup;
        if (xi >= 0) {
            inf = xi;
            sup = xs;
        } else if (xs <= 0) {
            inf = -xs;
            sup = -xi;
        } else {
            inf = 0;
            sup = Math.max(-xi, xs);
        }
        set(r, inf, sup);
    }

    @Override
    public void visitMin(int r, int x, int y) {
        double xi = getInf(x);
        double xs = getSup(x);
        double yi = getInf(y);
        double ys = getSup(y);
        if (Double.isNaN(xi + yi)) {
            setEmpty(r);
            return;
        }
        set(r, Math.min(xi, yi), Math.min(xs, ys));
    }

    @Override
    public void visitMax(int r, int x, int y) {
        double xi = getInf(x);
        double xs = getSup(x);
        double yi = getInf(y);
        double ys = getSup(y);
        if (Double.isNaN(xi + yi)) {
            setEmpty(r);
            return;
        }
        set(r, Math.max(xi, yi), Math.max(xs, ys));
    }

    @Override
    public void visitRootn(int r, int x, BigInteger q) {
        set(r, ic.rootn(get(x), q));
    }

    @Override
    public void visitRootn(int r, int x, long q) {
        set(r, ic.rootn(get(x), q));
    }

    @Override
    public void visitRootn(int r, int x, int q) {
        set(r, ic.rootn(get(x), q));
    }

    @Override
    public void visitHypot(int r, int x, int y) {
        set(r, ic.hypot(get(x), get(y)));
    }
}
