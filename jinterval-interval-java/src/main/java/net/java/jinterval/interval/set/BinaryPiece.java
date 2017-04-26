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
import java.util.Arrays;
import java.util.Collection;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.CReal;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;
import net.java.jinterval.rational.StdFuns;

/**
 *
 * @author dn146861
 */
abstract class BinaryPiece {

    private static abstract class PointFunction {

        abstract ExtendedRational op(ExtendedRationalContext rc, Rational x, Rational y);

        abstract int opCmp(Rational x, Rational y, ExtendedRational v);

        abstract ExtendedRational opRev1(ExtendedRationalContext rc, Rational v, Rational y);

        abstract ExtendedRational opRev2(ExtendedRationalContext rc, Rational v, Rational x);
    }
    final PointFunction fun;

    BinaryPiece(PointFunction fun) {
        this.fun = fun;
    }

    abstract SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs, ExtendedRational yi, ExtendedRational ys);

    abstract SetInterval opRev1(SetIntervalContextInfSupBase ctx,
            ExtendedRational bi, ExtendedRational bs,
            ExtendedRational ci, ExtendedRational cs,
            ExtendedRational xi, ExtendedRational xs);

    abstract SetInterval opRev2(SetIntervalContextInfSupBase ctx,
            ExtendedRational ai, ExtendedRational as,
            ExtendedRational ci, ExtendedRational cs,
            ExtendedRational xi, ExtendedRational xs);

    private static class Point extends BinaryPiece {

        private final Rational px, py;
        private final CReal v;

        Point(Rational px, Rational py, CReal v) {
            super(null);
            this.px = px;
            this.py = py;
            this.v = v;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs, ExtendedRational yi, ExtendedRational ys) {
            if (xs.lt(px) || xi.gt(px) || ys.lt(py) || yi.gt(py)) {
                return null;
            }
            return v != null ? Utils.set(ctx.mcInf.rnd(v), ctx.mcSup.rnd(v)) : EmptyInterval.empty();
        }

        @Override
        SetInterval opRev1(SetIntervalContextInfSupBase ctx,
                ExtendedRational bi, ExtendedRational bs,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (v == null || xs.lt(px) || xi.gt(px) || bs.lt(py) || bi.gt(py)
                    || v.compare(ci) < 0 || v.compare(cs) > 0) {
                return null;
            }
            return Utils.set(px, px);
        }

        @Override
        SetInterval opRev2(SetIntervalContextInfSupBase ctx,
                ExtendedRational ai, ExtendedRational as,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (v == null || as.lt(px) || ai.gt(px) || xs.lt(py) || xi.gt(py)
                    || v.compare(ci) < 0 || v.compare(cs) > 0) {
                return null;
            }
            return Utils.set(py, py);
        }
    }

    private static class HorLine extends BinaryPiece {

        private final ExtendedRational lx, ux;
        private final Rational py;
        private final CReal v;
        private final boolean hasBreak;

        HorLine(ExtendedRational lx, ExtendedRational ux, Rational py, CReal v) {
            this(lx, ux, py, v, false);
        }

        HorLine(ExtendedRational lx, ExtendedRational ux, Rational py, CReal v, boolean hasBreak) {
            super(null);
            this.lx = lx;
            this.ux = ux;
            this.py = py;
            this.v = v;
            this.hasBreak = hasBreak;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs, ExtendedRational yi, ExtendedRational ys) {
            if (xs.le(lx) || xi.ge(ux) || ys.lt(py) || yi.gt(py)) {
                return null;
            }
            if (v != null) {
                return Utils.set(ctx.mcInf.rnd(v), ctx.mcSup.rnd(v),
                        hasBreak ? Decoration.DAC : Decoration.COM);
            } else {
                return EmptyInterval.empty();
            }
        }

        @Override
        SetInterval opRev1(SetIntervalContextInfSupBase ctx,
                ExtendedRational bi, ExtendedRational bs,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (v == null || xs.le(lx) || xi.ge(ux) || bs.lt(py) || bi.gt(py)
                    || v.compare(ci) < 0 || v.compare(cs) > 0) {
                return null;
            }
            return Utils.set(ExtendedRationalOps.max(lx, xi), ExtendedRationalOps.min(ux, xs));
        }

        @Override
        SetInterval opRev2(SetIntervalContextInfSupBase ctx,
                ExtendedRational ai, ExtendedRational as,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (v == null || as.le(lx) || ai.ge(ux) || xs.lt(py) || xi.gt(py)
                    || v.compare(ci) < 0 || v.compare(cs) > 0) {
                return null;
            }
            return Utils.set(py, py);
        }
    }

    private static class VerLine extends BinaryPiece {

        private final Rational px;
        private final ExtendedRational ly, uy;
        private final CReal v;
        private final boolean hasBreak;

        VerLine(Rational px, ExtendedRational ly, ExtendedRational uy, CReal v) {
            this(px, ly, uy, v, false);
        }

        VerLine(Rational px, ExtendedRational ly, ExtendedRational uy, CReal v, boolean hasBreak) {
            super(null);
            this.px = px;
            this.ly = ly;
            this.uy = uy;
            this.v = v;
            this.hasBreak = hasBreak;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs, ExtendedRational yi, ExtendedRational ys) {
            if (xs.lt(px) || xi.gt(px) || ys.le(ly) || yi.ge(uy)) {
                return null;
            }
            if (v != null) {
                return Utils.set(ctx.mcInf.rnd(v), ctx.mcSup.rnd(v),
                        hasBreak ? Decoration.DAC : Decoration.COM);
            } else {
                return EmptyInterval.empty();
            }
        }

        @Override
        SetInterval opRev1(SetIntervalContextInfSupBase ctx,
                ExtendedRational bi, ExtendedRational bs,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (v == null || xs.lt(px) || xi.gt(px) || bs.le(ly) || bi.ge(uy)
                    || v.compare(ci) < 0 || v.compare(cs) > 0) {
                return null;
            }
            return Utils.set(px, px);
        }

        @Override
        SetInterval opRev2(SetIntervalContextInfSupBase ctx,
                ExtendedRational ai, ExtendedRational as,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (v == null || as.lt(px) || ai.gt(px) || xs.le(ly) || xi.ge(uy)
                    || v.compare(ci) < 0 || v.compare(cs) > 0) {
                return null;
            }
            return Utils.set(ExtendedRationalOps.max(ly, xi), ExtendedRationalOps.min(uy, xs));
        }
    }

    private static class UndefinedBox extends BinaryPiece {

        private final ExtendedRational lx, ux, ly, uy;

        UndefinedBox(ExtendedRational lx, ExtendedRational ux, ExtendedRational ly, ExtendedRational uy) {
            super(null);
            this.lx = lx;
            this.ux = ux;
            this.ly = ly;
            this.uy = uy;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs, ExtendedRational yi, ExtendedRational ys) {
            if (xs.le(lx) || xi.ge(ux) || ys.le(ly) || yi.ge(uy)) {
                return null;
            }
            return EmptyInterval.empty();
        }

        @Override
        SetInterval opRev1(SetIntervalContextInfSupBase ctx,
                ExtendedRational bi, ExtendedRational bs,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            return null;
        }

        @Override
        SetInterval opRev2(SetIntervalContextInfSupBase ctx,
                ExtendedRational ai, ExtendedRational as,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            return null;
        }
    }

    private static class MonotonicBox extends BinaryPiece {

        private final ExtendedRational lx, ux, ly, uy;
        private final boolean lxBreak, uxBreak, lyBreak, uyBreak;
        private final CReal infLim, supLim;
        private final boolean decreaseX, decreaseY;

        MonotonicBox(PointFunction fun,
                ExtendedRational lx, ExtendedRational ux,
                ExtendedRational ly, ExtendedRational uy,
                CReal infLim, CReal supLim,
                boolean decreaseX, boolean decreaseY) {
            this(fun, lx, false, ux, false, ly, false, uy, false,
                    infLim, supLim, decreaseX, decreaseY);
        }

        MonotonicBox(PointFunction fun,
                ExtendedRational lx, boolean lxBreak, ExtendedRational ux, boolean uxBreak,
                ExtendedRational ly, boolean lyBreak, ExtendedRational uy, boolean uyBreak,
                CReal infLim, CReal supLim,
                boolean decreaseX, boolean decreaseY) {
            super(fun);
            this.lx = lx;
            this.lxBreak = lxBreak;
            this.ux = ux;
            this.uxBreak = uxBreak;
            this.ly = ly;
            this.lyBreak = lyBreak;
            this.uy = uy;
            this.uyBreak = uyBreak;
            this.infLim = infLim;
            this.supLim = supLim;
            this.decreaseX = decreaseX;
            this.decreaseY = decreaseY;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs, ExtendedRational yi, ExtendedRational ys) {
            if (xs.le(lx) || xi.ge(ux) || ys.le(ly) || yi.ge(uy)) {
                return null;
            }
            xi = ExtendedRationalOps.max(xi, lx);
            xs = ExtendedRationalOps.min(xs, ux);
            yi = ExtendedRationalOps.max(yi, ly);
            ys = ExtendedRationalOps.min(ys, uy);
            ExtendedRational ri;
            if ((decreaseX ? xs.eq(ux) : xi.eq(lx)) || (decreaseY ? ys.eq(uy) : yi.eq(ly))) {
                ri = ctx.mcInf.rnd(infLim);
            } else {
                ri = fun.op(ctx.mcInf, (Rational) (decreaseX ? xs : xi), (Rational) (decreaseY ? ys : yi));
            }
            ExtendedRational rs;
            if ((decreaseX ? xi.eq(lx) : xs.eq(ux)) || (decreaseY ? yi.eq(ly) : ys.eq(uy))) {
                rs = ctx.mcSup.rnd(supLim);
            } else {
                rs = fun.op(ctx.mcSup, (Rational) (decreaseX ? xi : xs), (Rational) (decreaseY ? yi : ys));
            }
            Decoration d = lxBreak && xi.le(lx) || uxBreak && xs.ge(ux)
                    || lyBreak && yi.le(ly) || uyBreak && ys.ge(uy) ? Decoration.DEF : Decoration.COM;
            return Utils.set(ri, rs, d);
        }

        @Override
        SetInterval opRev1(SetIntervalContextInfSupBase ctx,
                ExtendedRational bi, ExtendedRational bs,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (xs.le(lx) || xi.ge(ux) || bs.le(ly) || bi.ge(uy)) {
                return null;
            }
            xi = ExtendedRationalOps.max(xi, lx);
            xs = ExtendedRationalOps.min(xs, ux);
            bi = ExtendedRationalOps.max(bi, ly);
            bs = ExtendedRationalOps.min(bs, uy);
            if ((decreaseX ? xs.eq(ux) : xi.eq(lx)) || (decreaseY ? bs.eq(uy) : bi.eq(ly))
                    ? infLim.compare(cs) >= 0
                    : fun.opCmp((Rational) (decreaseX ? xs : xi), (Rational) (decreaseY ? bs : bi), cs) > 0) {
                return null;
            }
            if ((decreaseX ? xi.eq(lx) : xs.eq(ux)) || (decreaseY ? bi.eq(ly) : bs.eq(uy))
                    ? supLim.compare(ci) <= 0
                    : fun.opCmp((Rational) (decreaseX ? xi : xs),
                            (Rational) (decreaseY ? bi : bs),
                            ci) < 0) {
                return null;
            }

            ExtendedRational ri;
            if ((decreaseX ? supLim.compare(cs) <= 0 : infLim.compare(ci) >= 0)
                    || (decreaseY == decreaseX ? bs.eq(uy) : bi.eq(ly))) {
                ri = lx;
            } else {
                ri = fun.opRev1(ctx.mcInf,
                        (Rational) (decreaseX ? cs : ci),
                        (Rational) (decreaseY == decreaseX ? bs : bi));
            }
            ExtendedRational rs;
            if ((decreaseX ? infLim.compare(ci) >= 0 : supLim.compare(cs) <= 0)
                    || (decreaseY == decreaseX ? bi.eq(ly) : bs.eq(uy))) {
                rs = ux;
            } else {
                rs = fun.opRev1(ctx.mcSup,
                        (Rational) (decreaseX ? ci : cs),
                        (Rational) (decreaseY == decreaseX ? bi : bs));
            }
            return Utils.set(ctx.mcInf.max(ri, xi), ctx.mcSup.min(rs, xs));
        }

        @Override
        SetInterval opRev2(SetIntervalContextInfSupBase ctx,
                ExtendedRational ai, ExtendedRational as,
                ExtendedRational ci, ExtendedRational cs,
                ExtendedRational xi, ExtendedRational xs) {
            if (as.le(lx) || ai.ge(ux) || xs.le(ly) || xi.ge(uy)) {
                return null;
            }
            ai = ExtendedRationalOps.max(ai, lx);
            as = ExtendedRationalOps.min(as, ux);
            xi = ExtendedRationalOps.max(xi, ly);
            xs = ExtendedRationalOps.min(xs, uy);
            if ((decreaseX ? as.eq(ux) : ai.eq(lx)) || (decreaseY ? xs.eq(uy) : xi.eq(ly))
                    ? infLim.compare(cs) >= 0
                    : fun.opCmp((Rational) (decreaseX ? as : ai), (Rational) (decreaseY ? xs : xi), cs) > 0) {
                return null;
            }
            if ((decreaseX ? ai.eq(lx) : as.eq(ux)) || (decreaseY ? xi.eq(ly) : xs.eq(uy))
                    ? supLim.compare(ci) <= 0
                    : fun.opCmp((Rational) (decreaseX ? ai : as), (Rational) (decreaseY ? xi : xs), ci) < 0) {
                return null;
            }

            ExtendedRational ri;
            if ((decreaseY ? supLim.compare(cs) <= 0 : infLim.compare(ci) >= 0)
                    || (decreaseX == decreaseY ? as.eq(ux) : ai.eq(lx))) {
                ri = ly;
            } else {
                ri = fun.opRev2(ctx.mcInf,
                        (Rational) (decreaseY ? cs : ci),
                        (Rational) (decreaseX == decreaseY ? as : ai));
            }
            ExtendedRational rs;
            if ((decreaseY ? infLim.compare(ci) >= 0 : supLim.compare(cs) <= 0)
                    || (decreaseX == decreaseY ? ai.eq(lx) : as.eq(ux))) {
                rs = uy;
            } else {
                rs = fun.opRev2(ctx.mcSup,
                        (Rational) (decreaseY ? ci : cs),
                        (Rational) (decreaseX == decreaseY ? ai : as));
            }
            return Utils.set(ctx.mcInf.max(ri, xi), ctx.mcSup.min(rs, xs));
        }
    }

    private static final PointFunction addFun = new PointFunction() {

        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x, Rational y) {
            return rc.add(x, y);
        }

        @Override
        int opCmp(Rational x, Rational y, ExtendedRational v) {
            return RationalOps.add(x, y).compareTo(v);
        }

        @Override
        ExtendedRational opRev1(ExtendedRationalContext rc, Rational v, Rational y) {
            return rc.sub(v, y);
        }

        @Override
        ExtendedRational opRev2(ExtendedRationalContext rc, Rational v, Rational x) {
            return rc.sub(v, x);
        }

    };
    static final Collection<BinaryPiece> addPieces = Arrays.<BinaryPiece>asList(
            new MonotonicBox(addFun,
                    ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false, false));

    private static final PointFunction subFun = new PointFunction() {

        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x, Rational y) {
            return rc.sub(x, y);
        }

        @Override
        int opCmp(Rational x, Rational y, ExtendedRational v) {
            return RationalOps.sub(x, y).compareTo(v);
        }

        @Override
        ExtendedRational opRev1(ExtendedRationalContext rc, Rational v, Rational y) {
            return rc.add(v, y);
        }

        @Override
        ExtendedRational opRev2(ExtendedRationalContext rc, Rational v, Rational x) {
            return rc.sub(x, v);
        }

    };
    static final Collection<BinaryPiece> subPieces = Arrays.<BinaryPiece>asList(
            new MonotonicBox(subFun,
                    ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false, true));

    private static final PointFunction mulFun = new PointFunction() {

        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x, Rational y) {
            return rc.mul(x, y);
        }

        @Override
        int opCmp(Rational x, Rational y, ExtendedRational v) {
            return RationalOps.mul(x, y).compareTo(v);
        }

        @Override
        ExtendedRational opRev1(ExtendedRationalContext rc, Rational v, Rational y) {
            return rc.div(v, y);
        }

        @Override
        ExtendedRational opRev2(ExtendedRationalContext rc, Rational v, Rational x) {
            return rc.div(v, x);
        }

    };
    static final Collection<BinaryPiece> mulPieces = Arrays.<BinaryPiece>asList(
            new MonotonicBox(mulFun,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.ZERO, CReal.POSITIVE_INFINITY, true, true),
            new HorLine(ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.zero(),
                    ExtendedRational.zero(), CReal.ZERO),
            new MonotonicBox(mulFun,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.ZERO, false, true),
            new VerLine(Rational.zero(),
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(), CReal.ZERO),
            new Point(Rational.zero(), Rational.zero(), CReal.ZERO),
            new VerLine(Rational.zero(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY, CReal.ZERO),
            new MonotonicBox(mulFun,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.NEGATIVE_INFINITY, CReal.ZERO, true, false),
            new HorLine(ExtendedRational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.zero(), CReal.ZERO),
            new MonotonicBox(mulFun,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false, false));
    private static final PointFunction divFun = new PointFunction() {

        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x, Rational y) {
            return rc.div(x, y);
        }

        @Override
        int opCmp(Rational x, Rational y, ExtendedRational v) {
            assert y.signum() != 0;
            return RationalOps.div(x, y).compareTo(v);
        }

        @Override
        ExtendedRational opRev1(ExtendedRationalContext rc, Rational v, Rational y) {
            return rc.mul(v, y);
        }

        @Override
        ExtendedRational opRev2(ExtendedRationalContext rc, Rational v, Rational x) {
            return rc.div(x, v);
        }

    };
    static final Collection<BinaryPiece> divPieces = Arrays.<BinaryPiece>asList(
            new HorLine(ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.zero(), null),
            new MonotonicBox(divFun,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.ZERO, CReal.POSITIVE_INFINITY, true, false),
            new MonotonicBox(divFun,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.ZERO, false, false),
            new VerLine(Rational.zero(),
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(), CReal.ZERO),
            new VerLine(Rational.zero(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY, CReal.ZERO),
            new MonotonicBox(divFun,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.NEGATIVE_INFINITY, CReal.ZERO, true, true),
            new MonotonicBox(divFun,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false, true));
    private static final PointFunction powFun = new PointFunction() {

        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x, Rational y) {
            return rc.pow(x, y);
        }

        @Override
        int opCmp(Rational x, Rational y, ExtendedRational v) {
            return StdFuns.pow(x, y).compare(v);
        }

        @Override
        ExtendedRational opRev1(ExtendedRationalContext rc, Rational v, Rational y) {
            return rc.pow(v, RationalOps.recip(y));
        }

        @Override
        ExtendedRational opRev2(ExtendedRationalContext rc, Rational v, Rational x) {
            return rc.rnd(StdFuns.logb(x, v));
        }

    };
    static final Collection<BinaryPiece> powPieces = Arrays.<BinaryPiece>asList(
            new UndefinedBox(ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY),
            new VerLine(Rational.zero(),
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(), null),
            new Point(Rational.zero(), Rational.zero(), null),
            new VerLine(Rational.zero(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY, CReal.ZERO),
            new MonotonicBox(powFun,
                    Rational.zero(), Rational.one(),
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.ONE, CReal.POSITIVE_INFINITY, true, true),
            new HorLine(Rational.zero(), Rational.one(), Rational.zero(), CReal.ONE),
            new MonotonicBox(powFun,
                    Rational.zero(), Rational.one(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.ONE, false, true),
            new VerLine(Rational.one(),
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(), CReal.ONE),
            new Point(Rational.one(), Rational.zero(), CReal.ONE),
            new VerLine(Rational.one(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY, CReal.ONE),
            new MonotonicBox(powFun,
                    Rational.one(), ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.ZERO, CReal.ONE, true, false),
            new HorLine(Rational.one(), ExtendedRational.POSITIVE_INFINITY,
                    Rational.zero(), CReal.ONE),
            new MonotonicBox(powFun,
                    Rational.one(), ExtendedRational.POSITIVE_INFINITY,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ONE, CReal.POSITIVE_INFINITY, false, false));
    private static final PointFunction atan2Fun = new PointFunction() {

        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational y, Rational x) {
            return rc.atan2(y, x);
        }

        @Override
        int opCmp(Rational x, Rational y, ExtendedRational v) {
            return StdFuns.atan2(x, y, BigInteger.ZERO).compare(v);
        }

        @Override
        ExtendedRational opRev1(ExtendedRationalContext rc, Rational v, Rational x) {
            return rc.rnd(StdFuns.atan2rev1(v, x));
        }

        @Override
        ExtendedRational opRev2(ExtendedRationalContext rc, Rational v, Rational y) {
            return rc.rnd(StdFuns.atan2rev2(v, y));
        }

    };
    static final Collection<BinaryPiece> atan2Pieces = Arrays.<BinaryPiece>asList(
            new MonotonicBox(atan2Fun,
                    ExtendedRational.NEGATIVE_INFINITY, false, Rational.zero(), true,
                    ExtendedRational.NEGATIVE_INFINITY, false, Rational.zero(), false,
                    StdFuns.MINUS_PI, StdFuns.MINUS_PI_HALF, true, false),
            new VerLine(ExtendedRational.zero(),
                    ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.zero(),
                    StdFuns.PI, true),
            new MonotonicBox(atan2Fun,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    StdFuns.PI_HALF, StdFuns.PI, true, true),
            new HorLine(ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    Rational.zero(), StdFuns.MINUS_PI_HALF),
            new Point(Rational.zero(), Rational.zero(), null),
            new HorLine(Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    Rational.zero(), StdFuns.PI_HALF),
            new MonotonicBox(atan2Fun,
                    ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    StdFuns.MINUS_PI_HALF, CReal.ZERO, false, false),
            new VerLine(ExtendedRational.zero(),
                    ExtendedRational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO),
            new MonotonicBox(atan2Fun,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, StdFuns.PI_HALF, false, true));
}
