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

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Collection;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public class SetIntervalContextInfSupBase implements SetIntervalContext {

    public final ExtendedRationalContext mcInf;
    public final ExtendedRationalContext mcSup;

    public SetIntervalContextInfSupBase(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup) {
        this.mcInf = mcInf;
        this.mcSup = mcSup;
    }

    @Override
    public SetInterval hull(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf = mcInf.rnd(xi);
        ExtendedRational sup = mcSup.rnd(xs);
        if (inf.eq(xi) && sup.eq(xs)) {
            return x;
        } else {
            return Utils.set(inf, sup, x.getDecoration());
        }
    }

    @Override
    public SetInterval newDec(SetInterval x) {
        if (x.isEmpty()) {
            return EmptyInterval.Empty;
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf = mcInf.rnd(xi);
        ExtendedRational sup = mcSup.rnd(xs);
        Decoration dec = x.getDecoration();
        if (dec == Decoration.COM && !(inf.isFinite() && sup.isFinite())) {
            dec = Decoration.DAC;
        }
        if (inf.eq(xi) && sup.eq(xs) && dec == x.getDecoration()) {
            return x;
        } else {
            return Utils.set(inf, sup, dec);
        }
    }

    @Override
    public SetInterval empty() {
        return EmptyInterval.empty();
    }

    @Override
    public SetInterval entire() {
        return Utils.entire(Decoration.DAC);
    }

    @Override
    public SetInterval nai() {
        return EmptyInterval.NaI();
    }

    @Override
    public SetInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
        if (l != null && u != null
                && l.le(u) && !l.isPositiveInfinity() && !u.isNegativeInfinity()) {
            ExtendedRational inf = mcInf.rnd(l);
            ExtendedRational sup = mcSup.rnd(u);
            return Utils.set(inf, sup, Decoration.COM);
        }
        throw new UndefinedOperationException();
    }

    @Override
    public SetInterval numsToInterval(double l, double u) {
        if (l <= u && l != Double.POSITIVE_INFINITY && u != Double.NEGATIVE_INFINITY) {
            ExtendedRational inf = mcInf.rnd(ExtendedRational.valueOf(l));
            ExtendedRational sup = mcSup.rnd(ExtendedRational.valueOf(u));
            return Utils.set(inf, sup, Decoration.COM);
        }
        throw new UndefinedOperationException();
    }

    @Override
    public SetInterval numsToInterval(float l, float u) {
        return numsToInterval((double) l, (double) u);
    }

    @Override
    public SetInterval numsDecToInterval(ExtendedRational l, ExtendedRational u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        if (l != null && u != null && l.le(u) 
                && !l.isPositiveInfinity() && !u.isNegativeInfinity() && decoration != Decoration.ILL) {
            ExtendedRational inf = mcInf.rnd(l);
            ExtendedRational sup = mcSup.rnd(u);
            if (decoration != Decoration.COM || inf.isFinite() && sup.isFinite()) {
                return Utils.set(inf, sup, decoration);
            }
        }
        throw new UndefinedOperationException();
    }

    @Override
    public SetInterval numsDecToInterval(double l, double u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        if (l <= u && l != Double.POSITIVE_INFINITY && u != Double.NEGATIVE_INFINITY && decoration != Decoration.ILL) {
            ExtendedRational inf = mcInf.rnd(ExtendedRational.valueOf(l));
            ExtendedRational sup = mcSup.rnd(ExtendedRational.valueOf(u));
            if (decoration != Decoration.COM || inf.isFinite() && sup.isFinite()) {
                return Utils.set(inf, sup, decoration);
            }
        }
        throw new UndefinedOperationException();
    }

    @Override
    public SetInterval numsDecToInterval(float l, float u, Decoration decoration) {
        return numsDecToInterval((double) l, (double) u, decoration);
    }

    @Override
    public SetInterval textToInterval(String s) {
        return textToInterval(s, false, true);
    }

    @Override
    public SetInterval textToDecoratedInterval(String s) {
        return textToInterval(s, true, true);
    }

    public SetInterval textToIntervalSloppy(String s) {
        return textToInterval(s, true, false);
    }

    private SetInterval textToInterval(String s, boolean decorated, boolean strictBoundsCheck) {
        try {
            ExtendedRational inf, sup;
            Decoration d = null;
            String ss = s.toUpperCase();
//            String ss = s.trim().toUpperCase();
            int indexD = ss.indexOf('_');
            if (indexD >= 0) {
                if (!decorated) {
                    throw new UndefinedOperationException();
                }
                try {
                    d = Decoration.valueOf(ss.substring(indexD + 1).toUpperCase());
                    if (d == Decoration.ILL) {
                        throw new UndefinedOperationException();
                    }
                } catch (IllegalArgumentException e) {
                    throw new UndefinedOperationException(e);
                }
                ss = ss.substring(0, indexD);
            }
            if (ss.length() >= 2 && ss.charAt(0) == '[' && ss.charAt(ss.length() - 1) == ']') {
                ss = ss.substring(1, ss.length() - 1);
                int indexC = ss.indexOf(',');
                if (indexC >= 0) {
                    String infS = ss.substring(0, indexC).trim();
                    String supS = ss.substring(indexC + 1).trim();
                    inf = infS.isEmpty() ? ExtendedRational.NEGATIVE_INFINITY : ExtendedRational.valueOf(infS);
                    sup = supS.isEmpty() ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.valueOf(supS);
                } else {
                    ss = ss.trim();
                    if (ss.equals("NAI")) {
                        if (!decorated || d != null) {
                            throw new UndefinedOperationException();
                        }
                        return EmptyInterval.NaI();
                    }
                    if (ss.isEmpty() || ss.equals("EMPTY")) {
                        if (d != null && d != Decoration.TRV) {
                            throw new UndefinedOperationException();
                        }
                        return empty();
                    } else if (ss.equals("ENTIRE")) {
                        inf = ExtendedRational.NEGATIVE_INFINITY;
                        sup = ExtendedRational.POSITIVE_INFINITY;
                    } else {
                        inf = sup = ExtendedRational.valueOf(ss);
                    }
                }
            } else {
                int indexQ = ss.indexOf('?');
                if (indexQ < 0) {
                    throw new UndefinedOperationException();
                }
                int indexE = ss.indexOf('E');
                if (indexE >= 0 && indexE < indexQ) {
                    throw new UndefinedOperationException();
                }
                String ms = ss.substring(0, indexQ);
                String es = indexE >= 0 ? ss.substring(indexE) : "";
                int p = indexQ + 1;
                if (p < ss.length() && ss.charAt(p) == '?') {
                    p++;
                } else {
                    while (p < ss.length() && '0' <= ss.charAt(p) && ss.charAt(p) <= '9') {
                        p++;
                    }
                }
                String ds = ss.substring(indexQ + 1, p);
                int dir = 0;
                if (p < ss.length()) {
                    if (ss.charAt(p) == 'U') {
                        dir = 1;
                        p++;
                    } else if (ss.charAt(p) == 'D') {
                        dir = -1;
                        p++;
                    }
                }
                if (p != ss.length() && p != indexE) {
                    throw new UndefinedOperationException();
                }
                BigDecimal bdm = new BigDecimal(ms + es);
                BigDecimal bdr;
                if (ds.isEmpty()) {
                    bdr = BigDecimal.valueOf(1, bdm.scale()).multiply(BigDecimal.valueOf(0.5));
                } else if (ds.equals("?")) {
                    bdr = null;
                } else {
                    bdr = new BigDecimal(new BigInteger(ds), bdm.scale());
                }
                inf = dir > 0 ? ExtendedRational.valueOf(bdm) : bdr == null ? ExtendedRational.NEGATIVE_INFINITY : ExtendedRational.valueOf(bdm.subtract(bdr));
                sup = dir < 0 ? ExtendedRational.valueOf(bdm) : bdr == null ? ExtendedRational.POSITIVE_INFINITY : ExtendedRational.valueOf(bdm.add(bdr));
            }
            if (inf.isPositiveInfinity() || sup.isNegativeInfinity()
                    || d == Decoration.COM && !(inf.isFinite() && sup.isFinite())) {
                throw new UndefinedOperationException();
            }
            if (d == null) {
                d = Decoration.COM;
            }
            if (!strictBoundsCheck && inf.isFinite() && sup.isFinite()) {
                ExtendedRational infInf = mcInf.rnd(inf);
                ExtendedRational supInf = mcSup.rnd(inf);
                ExtendedRational infSup = mcInf.rnd(sup);
                ExtendedRational supSup = mcSup.rnd(sup);
                if (infInf.eq(infSup) && supInf.eq(supSup)) {
                    SetInterval result = Utils.set(infInf, supSup, d);
                    throw new PossiblyUndefinedOperationException(result);
                }
            }
            if (inf.gt(sup)) {
                throw new UndefinedOperationException();
            }
            return Utils.set(mcInf.rnd(inf), mcSup.rnd(sup), d);
        } catch (NumberFormatException e) {
            throw new UndefinedOperationException(e);
        }
    }

    @Override
    public SetInterval pi() {
        return Utils.set(mcInf.pi(), mcSup.pi());
    }

    @Override
    public SetInterval euler() {
        return Utils.set(mcInf.euler(), mcSup.euler());
    }

    @Override
    public SetInterval neg(SetInterval x) {
        return eval(UnaryPiece.negPieces, x);
    }

    @Override
    public SetInterval add(SetInterval x, SetInterval y) {
        return eval(BinaryPiece.addPieces, x, y);
    }

    @Override
    public SetInterval sub(SetInterval x, SetInterval y) {
        return eval(BinaryPiece.subPieces, x, y);
    }

    @Override
    public SetInterval mul(SetInterval x, SetInterval y) {
        return eval(BinaryPiece.mulPieces, x, y);
    }

    @Override
    public SetInterval div(SetInterval x, SetInterval y) {
        return eval(BinaryPiece.divPieces, x, y);
    }

    @Override
    public SetInterval recip(SetInterval x) {
        return eval(UnaryPiece.recipPieces, x);
    }

    @Override
    public SetInterval sqr(SetInterval x) {
        return eval(UnaryPiece.sqrPieces, x);
    }

    @Override
    public SetInterval sqrt(SetInterval x) {
        return eval(UnaryPiece.sqrtPieces, x);
    }

    @Override
    public SetInterval fma(SetInterval x, SetInterval y, SetInterval z) {
        return add(SetIntervalOps.mul(x, y), z);
    }

    @Override
    public SetInterval pown(SetInterval x, BigInteger p) {
        return eval(UnaryPiece.genPownPieces(p), x);
    }

    @Override
    public SetInterval pown(SetInterval x, long p) {
        return eval(UnaryPiece.genPownPieces(p), x);
    }

    @Override
    public SetInterval pown(SetInterval x, int p) {
        return eval(UnaryPiece.genPownPieces(p), x);
    }

    @Override
    public SetInterval pow(SetInterval x, SetInterval y) {
        return eval(BinaryPiece.powPieces, x, y);
    }

    @Override
    public SetInterval exp(SetInterval x) {
        return eval(UnaryPiece.expPieces, x);
    }

    @Override
    public SetInterval exp2(SetInterval x) {
        return eval(UnaryPiece.exp2Pieces, x);
    }

    @Override
    public SetInterval exp10(SetInterval x) {
        return eval(UnaryPiece.exp10Pieces, x);
    }

    @Override
    public SetInterval log(SetInterval x) {
        return eval(UnaryPiece.logPieces, x);
    }

    @Override
    public SetInterval log2(SetInterval x) {
        return eval(UnaryPiece.log2Pieces, x);
    }

    @Override
    public SetInterval log10(SetInterval x) {
        return eval(UnaryPiece.log10Pieces, x);
    }

    @Override
    public SetInterval sin(SetInterval x) {
        return Trigonometry.sin.eval(mcInf, mcSup, x);
    }

    @Override
    public SetInterval cos(SetInterval x) {
        return Trigonometry.cos.eval(mcInf, mcSup, x);
    }

    @Override
    public SetInterval tan(SetInterval x) {
        return Trigonometry.tan.eval(mcInf, mcSup, x);
    }

    @Override
    public SetInterval asin(SetInterval x) {
        return eval(UnaryPiece.asinPieces, x);
    }

    @Override
    public SetInterval acos(SetInterval x) {
        return eval(UnaryPiece.acosPieces, x);
    }

    @Override
    public SetInterval atan(SetInterval x) {
        return eval(UnaryPiece.atanPieces, x);
    }

    @Override
    public SetInterval atan2(SetInterval y, SetInterval x) {
        return eval(BinaryPiece.atan2Pieces, y, x);
    }

    @Override
    public SetInterval sinh(SetInterval x) {
        return eval(UnaryPiece.sinhPieces, x);
    }

    @Override
    public SetInterval cosh(SetInterval x) {
        return eval(UnaryPiece.coshPieces, x);
    }

    @Override
    public SetInterval tanh(SetInterval x) {
        return eval(UnaryPiece.tanhPieces, x);
    }

    @Override
    public SetInterval asinh(SetInterval x) {
        return eval(UnaryPiece.asinhPieces, x);
    }

    @Override
    public SetInterval acosh(SetInterval x) {
        return eval(UnaryPiece.acoshPieces, x);
    }

    @Override
    public SetInterval atanh(SetInterval x) {
        return eval(UnaryPiece.atanhPieces, x);
    }

    @Override
    public SetInterval sign(SetInterval x) {
        return eval(UnaryPiece.signPieces, x);
    }

    @Override
    public SetInterval ceil(SetInterval x) {
        return hull(SetIntervalOps.ceil(x));
    }

    @Override
    public SetInterval floor(SetInterval x) {
        return hull(SetIntervalOps.floor(x));
    }

    @Override
    public SetInterval trunc(SetInterval x) {
        return hull(SetIntervalOps.trunc(x));
    }

    @Override
    public SetInterval roundTiesToEven(SetInterval x) {
        return hull(SetIntervalOps.roundTiesToEven(x));
    }

    @Override
    public SetInterval roundTiesToAway(SetInterval x) {
        return hull(SetIntervalOps.roundTiesToAway(x));
    }

    @Override
    public SetInterval abs(SetInterval x) {
        return eval(UnaryPiece.absPieces, x);
    }

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2) {
        return hull(SetIntervalOps.min(x1, x2));
    }

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2, SetInterval... xn) {
        SetInterval r = min(x1, x2);
        for (SetInterval x : xn) {
            r = min(r, x);
        }
        return r;
    }

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2) {
        return hull(SetIntervalOps.max(x1, x2));
    }

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2, SetInterval... xn) {
        SetInterval r = max(x1, x2);
        for (SetInterval x : xn) {
            r = max(r, x);
        }
        return r;
    }

    @Override
    public SetInterval sqrRev(SetInterval c, SetInterval x) {
        return evalRev(UnaryPiece.sqrPieces, c, x);
    }

    @Override
    public SetInterval absRev(SetInterval c, SetInterval x) {
        return evalRev(UnaryPiece.absPieces, c, x);
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, BigInteger p) {
        return evalRev(UnaryPiece.genPownPieces(p), c, x);
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, long p) {
        return evalRev(UnaryPiece.genPownPieces(p), c, x);
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, int p) {
        return evalRev(UnaryPiece.genPownPieces(p), c, x);
    }

    @Override
    public SetInterval sinRev(SetInterval c, SetInterval x) {
        return Trigonometry.sin.evalRev(mcInf, mcSup, c, x);
    }

    @Override
    public SetInterval cosRev(SetInterval c, SetInterval x) {
        return Trigonometry.cos.evalRev(mcInf, mcSup, c, x);
    }

    @Override
    public SetInterval tanRev(SetInterval c, SetInterval x) {
        return Trigonometry.tan.evalRev(mcInf, mcSup, c, x);
    }

    @Override
    public SetInterval coshRev(SetInterval c, SetInterval x) {
        return evalRev(UnaryPiece.coshPieces, c, x);
    }

    @Override
    public SetInterval mulRev(SetInterval b, SetInterval c, SetInterval x) {
        return evalRev1(BinaryPiece.mulPieces, b, c, x);
    }

    @Override
    public SetInterval powRev1(SetInterval b, SetInterval c, SetInterval x) {
        return evalRev1(BinaryPiece.powPieces, b, c, x);
    }

    @Override
    public SetInterval powRev2(SetInterval a, SetInterval c, SetInterval x) {
        return evalRev2(BinaryPiece.powPieces, a, c, x);
    }

    @Override
    public SetInterval atan2Rev1(SetInterval b, SetInterval c, SetInterval x) {
        return evalRev1(BinaryPiece.atan2Pieces, b, c, x);
    }

    @Override
    public SetInterval atan2Rev2(SetInterval a, SetInterval c, SetInterval x) {
        return evalRev2(BinaryPiece.atan2Pieces, a, c, x);
    }

    @Override
    public MulRevPair mulRevToPair(SetInterval b, SetInterval c) {
        if (b.isNaI() || c.isNaI()) {
            return new MulRevPair(nai(), nai());
        }
        if (b.inf().gt(Rational.zero()) || b.sup().lt(Rational.zero())) {
            return new MulRevPair(div(c, b), empty());
        }
        if (c.isMember(Rational.zero())) {
            return new MulRevPair(mulRev(b, c, entire()), empty());
        }
        SetInterval n = mulRev(b, c, Utils.set(ExtendedRational.NEGATIVE_INFINITY, Rational.zero()));
        SetInterval p = mulRev(b, c, Utils.set(Rational.zero(), ExtendedRational.POSITIVE_INFINITY));
        return n.isEmpty() ? new MulRevPair(p, empty()) : new MulRevPair(n, p);
    }

    @Override
    public SetInterval cancelMinus(SetInterval x, SetInterval y) {
        if (x.isNaI() || y.isNaI()) {
            return EmptyInterval.NaI;
        }
        if (x.isEmpty() && (y.isEmpty() || y.isCommonInterval())) {
            return EmptyInterval.empty();
        }
        if (x.isCommonInterval() && y.isCommonInterval() && x.wid().ge(y.wid())) {
            ExtendedRational inf = mcInf.sub(x.inf(), y.inf());
            ExtendedRational sup = mcSup.sub(x.sup(), y.sup());
            return Utils.set(inf, sup, Decoration.TRV);
        }
        return Utils.entire(Decoration.TRV);
    }

    @Override
    public SetInterval cancelPlus(SetInterval x, SetInterval y) {
        if (x.isNaI() || y.isNaI()) {
            return EmptyInterval.NaI;
        }
        if (x.isEmpty() && (y.isEmpty() || y.isCommonInterval())) {
            return EmptyInterval.empty();
        }
        if (x.isCommonInterval() && y.isCommonInterval() && x.wid().ge(y.wid())) {
            ExtendedRational inf = mcInf.add(x.inf(), y.sup());
            ExtendedRational sup = mcSup.add(x.sup(), y.inf());
            return Utils.set(inf, sup, Decoration.TRV);
        }
        return Utils.entire(Decoration.TRV);
    }

    @Override
    public SetInterval intersection(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration()).min(Decoration.TRV);
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
            return Utils.set(mcInf.rnd(inf), mcSup.rnd(sup), d);
        } else {
            return EmptyInterval.empty(d);
        }
    }

    @Override
    public SetInterval convexHull(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration()).min(Decoration.TRV);
        if (d == Decoration.ILL) {
            return EmptyInterval.NaI();
        }
        ExtendedRational inf;
        ExtendedRational sup;
        if (x.isEmpty()) {
            if (y.isEmpty()) {
                return EmptyInterval.empty(d);
            } else {
                inf = mcInf.rnd(y.inf());
                sup = mcSup.rnd(y.sup());
            }
        } else if (y.isEmpty()) {
            inf = mcInf.rnd(x.inf());
            sup = mcSup.rnd(x.sup());
        } else {
            inf = mcInf.min(x.inf(), y.inf());
            sup = mcSup.max(x.sup(), y.sup());
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval setDec(SetInterval x, Decoration dec) {
        return SetIntervalOps.setDec(hull(x), dec);
    }

    @Override
    public SetInterval rootn(SetInterval x, BigInteger q) {
        return eval(UnaryPiece.genRootnPieces(q), x);
    }

    @Override
    public SetInterval rootn(SetInterval x, long q) {
        return eval(UnaryPiece.genRootnPieces(q), x);
    }

    @Override
    public SetInterval rootn(SetInterval x, int q) {
        return eval(UnaryPiece.genRootnPieces(q), x);
    }

    @Override
    public SetInterval hypot(SetInterval x, SetInterval y) {
        return sqrt(SetIntervalOps.add(SetIntervalOps.sqr(x), SetIntervalOps.sqr(y)));
    }

    private SetInterval eval(Collection<UnaryPiece> pieces, SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        Decoration d = x.getDecoration();
        assert d.ordinal() >= Decoration.TRV.ordinal();
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        SetInterval r = null;
        for (UnaryPiece p : pieces) {
            SetInterval pr = p.op(this, xi, xs);
            if (pr != null) {
                r = r == null ? pr : SetIntervalOps.convexHull(r, pr);
                d = d.min(pr.getDecoration());
            }
        }
        if (r == null) {
            return EmptyInterval.empty();
        }
        if (r.getDecoration() == d) {
            return r;
        }
        return Utils.set(r.inf(), r.sup(), d);
    }

    private SetInterval eval(Collection<BinaryPiece> pieces, SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        assert d.ordinal() >= Decoration.TRV.ordinal();
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();
        SetInterval r = null;
        for (BinaryPiece p : pieces) {
            SetInterval pr = p.op(this, xi, xs, yi, ys);
            if (pr != null) {
                r = r == null ? pr : SetIntervalOps.convexHull(r, pr);
                d = d.min(pr.getDecoration());
            }
        }
        if (r == null) {
            return EmptyInterval.empty();
        }
        if (r.getDecoration() == d) {
            return r;
        }
        return Utils.set(r.inf(), r.sup(), d);
    }

    private SetInterval evalRev(Collection<UnaryPiece> pieces, SetInterval c, SetInterval x) {
        if (c.isEmpty() || x.isEmpty()) {
            return EmptyInterval.empty(c.getDecoration().min(x.getDecoration()));
        }
        ExtendedRational ci = c.inf();
        ExtendedRational cs = c.sup();
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        SetInterval r = null;
        for (UnaryPiece p : pieces) {
            SetInterval pr = p.opRev(this, ci, cs, xi, xs);
            if (pr != null) {
                r = r == null ? pr : SetIntervalOps.convexHull(r, pr);
            }
        }
        if (r == null) {
            return EmptyInterval.empty();
        }
        return Utils.set(r.inf(), r.sup(), Decoration.TRV);
    }

    private SetInterval evalRev1(Collection<BinaryPiece> pieces, SetInterval b, SetInterval c, SetInterval x) {
        if (b.isEmpty() || c.isEmpty() || x.isEmpty()) {
            return EmptyInterval.empty(b.getDecoration().min(c.getDecoration()).min(x.getDecoration()));
        }
        ExtendedRational bi = b.inf();
        ExtendedRational bs = b.sup();
        ExtendedRational ci = c.inf();
        ExtendedRational cs = c.sup();
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        SetInterval r = null;
        for (BinaryPiece p : pieces) {
            SetInterval pr = p.opRev1(this, bi, bs, ci, cs, xi, xs);
            if (pr != null) {
                r = r == null ? pr : SetIntervalOps.convexHull(r, pr);
            }
        }
        if (r == null) {
            return EmptyInterval.empty();
        }
        return Utils.set(r.inf(), r.sup(), Decoration.TRV);
    }

    private SetInterval evalRev2(Collection<BinaryPiece> pieces, SetInterval a, SetInterval c, SetInterval x) {
        if (a.isEmpty() || c.isEmpty() || x.isEmpty()) {
            return EmptyInterval.empty(a.getDecoration().min(c.getDecoration()).min(x.getDecoration()));
        }
        ExtendedRational ai = a.inf();
        ExtendedRational as = a.sup();
        ExtendedRational ci = c.inf();
        ExtendedRational cs = c.sup();
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        SetInterval r = null;
        for (BinaryPiece p : pieces) {
            SetInterval pr = p.opRev2(this, ai, as, ci, cs, xi, xs);
            if (pr != null) {
                r = r == null ? pr : SetIntervalOps.convexHull(r, pr);
            }
        }
        if (r == null) {
            return EmptyInterval.empty();
        }
        return Utils.set(r.inf(), r.sup(), Decoration.TRV);
    }
}
