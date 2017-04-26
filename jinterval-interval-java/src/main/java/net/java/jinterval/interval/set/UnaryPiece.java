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
 */
abstract class UnaryPiece {

    private static abstract class PointFunction {

        abstract ExtendedRational op(ExtendedRationalContext rc, Rational x);

        abstract int opCmp(Rational x, ExtendedRational v);

        abstract ExtendedRational opRev(ExtendedRationalContext rc, Rational v);
    }
    final PointFunction fun;

    UnaryPiece(PointFunction fun) {
        this.fun = fun;
    }

    abstract SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs);

    abstract SetInterval opRev(SetIntervalContextInfSupBase ctx, ExtendedRational ci, ExtendedRational cs, ExtendedRational xi, ExtendedRational xs);

    private static class Point extends UnaryPiece {

        private final Rational p;
        private final CReal v;
        private final boolean hasBreak;

        Point(Rational p, CReal v) {
            this(p, v, false);
        }

        Point(Rational p, CReal v, boolean hasBreak) {
            super(null);
            this.p = p;
            this.v = v;
            this.hasBreak = hasBreak;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs) {
            if (xs.lt(p) || xi.gt(p)) {
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
        SetInterval opRev(SetIntervalContextInfSupBase ctx, ExtendedRational ci, ExtendedRational cs, ExtendedRational xi, ExtendedRational xs) {
            if (v == null || xs.lt(p) || xi.gt(p) || v.compare(ci) < 0 || v.compare(cs) > 0) {
                return null;
            }
            return Utils.set(p, p);
        }
    }

    private static class UndefinedUnaryPiece extends UnaryPiece {

        private final ExtendedRational l;
        private final ExtendedRational u;

        UndefinedUnaryPiece(ExtendedRational l, ExtendedRational u) {
            super(null);
            this.l = l;
            this.u = u;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs) {
            if (xs.le(l) || xi.ge(u)) {
                return null;
            }
            return EmptyInterval.empty();
        }

        @Override
        SetInterval opRev(SetIntervalContextInfSupBase ctx, ExtendedRational ci, ExtendedRational cs, ExtendedRational xi, ExtendedRational xs) {
            return null;
        }
    }

    private static class ConstantUnaryPiece extends UnaryPiece {

        private final ExtendedRational l;
        private final boolean lBreak;
        private final ExtendedRational u;
        private final boolean uBreak;
        private final Rational v;

        ConstantUnaryPiece(PointFunction fun, ExtendedRational l, boolean lBreak, ExtendedRational u, boolean uBreak, Rational v) {
            super(fun);
            this.l = l;
            this.lBreak = lBreak;
            this.u = u;
            this.uBreak = uBreak;
            this.v = v;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs) {
            if (xs.le(l) || xi.ge(u)) {
                return null;
            }
            Decoration d = lBreak && xi.le(l) || uBreak && xs.ge(u) ? Decoration.DEF : Decoration.COM;
            return Utils.set(v, v, d);
        }

        @Override
        SetInterval opRev(SetIntervalContextInfSupBase ctx, ExtendedRational ci, ExtendedRational cs, ExtendedRational xi, ExtendedRational xs) {
            if (ci.gt(v) || cs.lt(v) || xs.le(l) || xi.ge(u)) {
                return null;
            }
            xi = ExtendedRationalOps.max(xi, l);
            xs = ExtendedRationalOps.min(xs, u);
            return Utils.set(xi, xs);
        }
    }

    private abstract static class MonotonicUnaryPiece extends UnaryPiece {

        private final boolean decrease;
        private final ExtendedRational l;
        private final boolean lBreak;
        private final ExtendedRational u;
        private final boolean uBreak;
        private final CReal infLim;
        private final CReal supLim;
        private final boolean revNegate;

        MonotonicUnaryPiece(boolean decrease, PointFunction fun, ExtendedRational l, ExtendedRational u, CReal infLim, CReal supLim, boolean revNegate) {
            this(decrease, fun, l, false, u, false, infLim, supLim, revNegate);
        }

        MonotonicUnaryPiece(boolean decrease, PointFunction fun,
                ExtendedRational l, boolean lBreak, ExtendedRational u, boolean uBreak,
                CReal infLim, CReal supLim, boolean revNegate) {
            super(fun);
            if (l == null || u == null || infLim == null || supLim == null) {
                throw new NullPointerException();
            }
            this.decrease = decrease;
            this.l = l;
            this.lBreak = lBreak;
            this.u = u;
            this.uBreak = uBreak;
            this.infLim = infLim;
            this.supLim = supLim;
            this.revNegate = revNegate;
        }

        @Override
        SetInterval op(SetIntervalContextInfSupBase ctx, ExtendedRational xi, ExtendedRational xs) {
            if (xs.le(l) || xi.ge(u)) {
                return null;
            }
            xi = ExtendedRationalOps.max(xi, l);
            xs = ExtendedRationalOps.min(xs, u);
            ExtendedRational inf;
            if (decrease ? xs.eq(u) : xi.eq(l)) {
                inf = ctx.mcInf.rnd(infLim);
            } else {
                inf = fun.op(ctx.mcInf, (Rational) (decrease ? xs : xi));
            }
            ExtendedRational sup;
            if (decrease ? xi.eq(l) : xs.eq(u)) {
                sup = ctx.mcSup.rnd(supLim);
            } else {
                sup = fun.op(ctx.mcSup, (Rational) (decrease ? xi : xs));
            }
            Decoration d = lBreak && xi.le(l) || uBreak && xs.ge(u) ? Decoration.DEF : Decoration.COM;
            return Utils.set(inf, sup, d);
        }

        @Override
        SetInterval opRev(SetIntervalContextInfSupBase ctx, ExtendedRational ci, ExtendedRational cs, ExtendedRational xi, ExtendedRational xs) {
            if (xs.le(l) || xi.ge(u)) {
                return null;
            }
            xi = ExtendedRationalOps.max(xi, l);
            xs = ExtendedRationalOps.min(xs, u);
            ExtendedRational infX = decrease ? xs : xi;
            ExtendedRational supX = decrease ? xi : xs;
            if ((decrease ? xs.eq(u) : xi.eq(l))
                    ? infLim.compare(cs) >= 0
                    : fun.opCmp((Rational) infX, cs) > 0) {
                return null;
            }
            if ((decrease ? xi.eq(l) : xs.eq(u))
                    ? supLim.compare(ci) <= 0
                    : fun.opCmp((Rational) supX, ci) < 0) {
                return null;
            }

            ExtendedRational ri;
            if (decrease ? supLim.compare(cs) <= 0 : infLim.compare(ci) >= 0) {
                ri = l;
            } else {
                Rational infC = (Rational) (decrease ? cs : ci);
                if (revNegate) {
                    ri = ExtendedRationalOps.neg(fun.opRev(ctx.mcSup, infC));
                } else {
                    ri = fun.opRev(ctx.mcInf, infC);
                }
            }
            ExtendedRational rs;
            if (decrease ? infLim.compare(ci) >= 0 : supLim.compare(cs) <= 0) {
                rs = u;
            } else {
                Rational supC = (Rational) (decrease ? ci : cs);
                if (revNegate) {
                    rs = ExtendedRationalOps.neg(fun.opRev(ctx.mcInf, supC));
                } else {
                    rs = fun.opRev(ctx.mcSup, supC);
                }
            }
            return Utils.set(ctx.mcInf.max(ri, xi), ctx.mcSup.min(rs, xs));
        }
    }

    private static class IncreasingUnaryPiece extends MonotonicUnaryPiece {

        IncreasingUnaryPiece(PointFunction fun, ExtendedRational l, ExtendedRational u, CReal infLim, CReal supLim, boolean revNegate) {
            super(false, fun, l, u, infLim, supLim, revNegate);
        }
    }

    private static class DecreasingUnaryPiece extends MonotonicUnaryPiece {

        DecreasingUnaryPiece(PointFunction fun, ExtendedRational l, ExtendedRational u, CReal infLim, CReal supLim, boolean revNegate) {
            super(true, fun, l, u, infLim, supLim, revNegate);
        }
    }
    private static final PointFunction negFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.neg(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return RationalOps.neg(x).compareTo(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.neg(v);
        }
    };
    static final Collection<UnaryPiece> negPieces = Arrays.<UnaryPiece>asList(new DecreasingUnaryPiece(negFun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
            CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction recipFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.recip(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return RationalOps.recip(x).compareTo(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.recip(v);
        }
    };
    static final Collection<UnaryPiece> recipPieces = Arrays.<UnaryPiece>asList(
            new DecreasingUnaryPiece(recipFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.NEGATIVE_INFINITY, CReal.ZERO, false),
            new Point(Rational.zero(), null),
            new DecreasingUnaryPiece(recipFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction sqrtFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.sqrt(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return v.signum() >= 0 ? x.compareTo(ExtendedRationalOps.sqr(v)) : +1;
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.sqr(v);
        }
    };
    static final Collection<UnaryPiece> sqrtPieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.zero()),
            new Point(Rational.zero(), CReal.ZERO),
            new IncreasingUnaryPiece(sqrtFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction sqrFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.sqr(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return RationalOps.sqr(x).compareTo(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.sqrt(v);
        }
    };
    static final Collection<UnaryPiece> sqrPieces = Arrays.<UnaryPiece>asList(
            new DecreasingUnaryPiece(sqrFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.ZERO, CReal.POSITIVE_INFINITY, true),
            new Point(Rational.zero(), CReal.ZERO),
            new IncreasingUnaryPiece(sqrFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));

    private static Collection<UnaryPiece> genPownPieces(PointFunction pownFun, int pSign, boolean pOdd) {
        if (pSign > 0) {
            if (pOdd) {
                return Arrays.<UnaryPiece>asList(
                        new IncreasingUnaryPiece(pownFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                                CReal.NEGATIVE_INFINITY, CReal.ZERO, true),
                        new Point(Rational.zero(), CReal.ZERO),
                        new IncreasingUnaryPiece(pownFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            } else {
                return Arrays.<UnaryPiece>asList(
                        new DecreasingUnaryPiece(pownFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                                CReal.ZERO, CReal.POSITIVE_INFINITY, true),
                        new Point(Rational.zero(), CReal.ZERO),
                        new IncreasingUnaryPiece(pownFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            }
        } else if (pSign < 0) {
            if (pOdd) {
                return Arrays.<UnaryPiece>asList(
                        new DecreasingUnaryPiece(pownFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                                CReal.NEGATIVE_INFINITY, CReal.ZERO, true),
                        new Point(Rational.zero(), null),
                        new DecreasingUnaryPiece(pownFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            } else {
                return Arrays.<UnaryPiece>asList(
                        new IncreasingUnaryPiece(pownFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                                CReal.ZERO, CReal.POSITIVE_INFINITY, true),
                        new Point(Rational.zero(), null),
                        new DecreasingUnaryPiece(pownFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            }
        } else {
            return Arrays.<UnaryPiece>asList(new ConstantUnaryPiece(pownFun, ExtendedRational.NEGATIVE_INFINITY, false, ExtendedRational.POSITIVE_INFINITY, false, Rational.one()));
        }
    }

    static Collection<UnaryPiece> genPownPieces(final BigInteger p) {
        return genPownPieces(new PointFunction() {
            @Override
            ExtendedRational op(ExtendedRationalContext rc, Rational x) {
                return rc.pown(x, p);
            }

            @Override
            int opCmp(Rational x, ExtendedRational v) {
                assert p.signum() >= 0 || x.signum() != 0;
                return StdFuns.pown(x, p).compare(v);
            }

            @Override
            ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
                assert p.signum() != 0;
                return rc.rootn(RationalOps.abs(v), p);
            }
        }, p.signum(), p.testBit(0));
    }

    static Collection<UnaryPiece> genPownPieces(final long p) {
        return genPownPieces(BigInteger.valueOf(p));
    }

    static Collection<UnaryPiece> genPownPieces(final int p) {
        return genPownPieces(BigInteger.valueOf(p));
    }
    private static final PointFunction expFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.exp(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.exp(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.log(v);
        }
    };
    static final Collection<UnaryPiece> expPieces = Arrays.<UnaryPiece>asList(
            new IncreasingUnaryPiece(expFun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction exp2Fun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.exp2(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.exp2(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.log2(v);
        }
    };
    static final Collection<UnaryPiece> exp2Pieces = Arrays.<UnaryPiece>asList(
            new IncreasingUnaryPiece(exp2Fun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction exp10Fun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.exp10(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.exp10(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.log10(v);
        }
    };
    static final Collection<UnaryPiece> exp10Pieces = Arrays.<UnaryPiece>asList(
            new IncreasingUnaryPiece(exp10Fun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction logFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.log(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            assert x.signum() > 0;
            return StdFuns.log(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.exp(v);
        }
    };
    static final Collection<UnaryPiece> logPieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.zero()),
            new Point(Rational.zero(), null),
            new IncreasingUnaryPiece(logFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction log2Fun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.log2(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            assert x.signum() > 0;
            return StdFuns.log2(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.exp2(v);
        }
    };
    static final Collection<UnaryPiece> log2Pieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.zero()),
            new Point(Rational.zero(), null),
            new IncreasingUnaryPiece(log2Fun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction log10Fun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.log10(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            assert x.signum() > 0;
            return StdFuns.log10(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.exp10(v);
        }
    };
    static final Collection<UnaryPiece> log10Pieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.zero()),
            new Point(Rational.zero(), null),
            new IncreasingUnaryPiece(log10Fun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction asinFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.asin(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.asin(x, BigInteger.ZERO, false).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.sin(v);
        }
    };
    static final Collection<UnaryPiece> asinPieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.valueOf(-1)),
            new Point(Rational.valueOf(-1), StdFuns.MINUS_PI_HALF),
            new IncreasingUnaryPiece(asinFun, Rational.valueOf(-1), Rational.one(),
                    StdFuns.MINUS_PI_HALF, StdFuns.PI_HALF, false),
            new Point(Rational.one(), StdFuns.PI_HALF),
            new UndefinedUnaryPiece(Rational.one(), ExtendedRational.POSITIVE_INFINITY));
    private static final PointFunction acosFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.acos(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.acos(x, BigInteger.ZERO, false).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.cos(v);
        }
    };
    static final Collection<UnaryPiece> acosPieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.valueOf(-1)),
            new Point(Rational.valueOf(-1), StdFuns.PI),
            new DecreasingUnaryPiece(acosFun, Rational.valueOf(-1), Rational.one(),
                    CReal.ZERO, StdFuns.PI, false),
            new Point(Rational.one(), CReal.ZERO),
            new UndefinedUnaryPiece(Rational.one(), ExtendedRational.POSITIVE_INFINITY));
    private static final PointFunction atanFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.atan(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.atan(x, BigInteger.ZERO).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.tan(v);
        }
    };
    static final Collection<UnaryPiece> atanPieces = Arrays.<UnaryPiece>asList(
            new IncreasingUnaryPiece(atanFun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    StdFuns.MINUS_PI_HALF, StdFuns.PI_HALF, false));
    private static final PointFunction sinhFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.sinh(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.sinh(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.asinh(v);
        }
    };
    static final Collection<UnaryPiece> sinhPieces = Arrays.<UnaryPiece>asList(
            new IncreasingUnaryPiece(sinhFun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction coshFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.cosh(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.cosh(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.acosh(v);
        }
    };
    static final Collection<UnaryPiece> coshPieces = Arrays.<UnaryPiece>asList(
            new DecreasingUnaryPiece(coshFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.ONE, CReal.POSITIVE_INFINITY, true),
            new Point(Rational.zero(), CReal.ONE),
            new IncreasingUnaryPiece(coshFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ONE, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction tanhFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.tanh(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.tanh(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.atanh(v);
        }
    };
    static final Collection<UnaryPiece> tanhPieces = Arrays.<UnaryPiece>asList(
            new IncreasingUnaryPiece(tanhFun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.MINUS_ONE, CReal.ONE, false));
    private static final PointFunction asinhFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.asinh(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.asinh(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.sinh(v);
        }
    };
    static final Collection<UnaryPiece> asinhPieces = Arrays.<UnaryPiece>asList(
            new IncreasingUnaryPiece(asinhFun, ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY,
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction acoshFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.acosh(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.acosh(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.cosh(v);
        }
    };
    static final Collection<UnaryPiece> acoshPieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.one()),
            new Point(Rational.one(), CReal.ZERO),
            new IncreasingUnaryPiece(acoshFun, Rational.one(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));
    private static final PointFunction atanhFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.atanh(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return StdFuns.atanh(x).compare(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.tanh(v);
        }
    };
    static final Collection<UnaryPiece> atanhPieces = Arrays.<UnaryPiece>asList(
            new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.valueOf(-1)),
            new Point(Rational.valueOf(-1), null),
            new IncreasingUnaryPiece(atanhFun, Rational.valueOf(-1), Rational.one(),
                    CReal.NEGATIVE_INFINITY, CReal.POSITIVE_INFINITY, false),
            new Point(Rational.one(), null),
            new UndefinedUnaryPiece(Rational.one(), ExtendedRational.POSITIVE_INFINITY));
    private static final PointFunction signFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.sign(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return RationalOps.sign(x).compareTo(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            throw new AssertionError();
        }
    };
    static final Collection<UnaryPiece> signPieces = Arrays.<UnaryPiece>asList(
            new ConstantUnaryPiece(signFun, ExtendedRational.NEGATIVE_INFINITY, false, Rational.zero(), true, Rational.valueOf(-1)),
            new Point(Rational.zero(), CReal.ZERO, true),
            new ConstantUnaryPiece(signFun, Rational.zero(), true, ExtendedRational.POSITIVE_INFINITY, false, Rational.one()));
    private static final PointFunction absFun = new PointFunction() {
        @Override
        ExtendedRational op(ExtendedRationalContext rc, Rational x) {
            return rc.abs(x);
        }

        @Override
        int opCmp(Rational x, ExtendedRational v) {
            return RationalOps.abs(x).compareTo(v);
        }

        @Override
        ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
            return rc.rnd(v);
        }
    };
    static final Collection<UnaryPiece> absPieces = Arrays.<UnaryPiece>asList(
            new DecreasingUnaryPiece(absFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                    CReal.ZERO, CReal.POSITIVE_INFINITY, true),
            new Point(Rational.zero(), CReal.ZERO),
            new IncreasingUnaryPiece(absFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                    CReal.ZERO, CReal.POSITIVE_INFINITY, false));

    private static Collection<UnaryPiece> genRootnPieces(PointFunction rootnFun, int qSign, boolean qOdd) {
        if (qSign > 0) {
            if (qOdd) {
                return Arrays.<UnaryPiece>asList(
                        new IncreasingUnaryPiece(rootnFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                                CReal.NEGATIVE_INFINITY, CReal.ZERO, true),
                        new Point(Rational.zero(), CReal.ZERO),
                        new IncreasingUnaryPiece(rootnFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            } else {
                return Arrays.<UnaryPiece>asList(
                        new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.zero()),
                        new Point(Rational.zero(), CReal.ZERO),
                        new IncreasingUnaryPiece(rootnFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            }
        } else if (qSign < 0) {
            if (qOdd) {
                return Arrays.<UnaryPiece>asList(
                        new DecreasingUnaryPiece(rootnFun, ExtendedRational.NEGATIVE_INFINITY, Rational.zero(),
                                CReal.NEGATIVE_INFINITY, CReal.ZERO, true),
                        new Point(Rational.zero(), null),
                        new DecreasingUnaryPiece(rootnFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            } else {
                return Arrays.<UnaryPiece>asList(
                        new UndefinedUnaryPiece(ExtendedRational.NEGATIVE_INFINITY, Rational.zero()),
                        new Point(Rational.zero(), null),
                        new DecreasingUnaryPiece(rootnFun, Rational.zero(), ExtendedRational.POSITIVE_INFINITY,
                                CReal.ZERO, CReal.POSITIVE_INFINITY, false));
            }
        } else {
            throw new IllegalArgumentException();
        }
    }

    static Collection<UnaryPiece> genRootnPieces(final BigInteger q) {
        return genRootnPieces(new PointFunction() {
            @Override
            ExtendedRational op(ExtendedRationalContext rc, Rational x) {
                return rc.rootn(x, q);
            }

            @Override
            int opCmp(Rational x, ExtendedRational v) {
                assert q.signum() != 0;
                if (q.signum() > 0) {
                    if (!q.testBit(0)) {
                        assert x.signum() >= 0;
                        if (v.signum() < 0) {
                            return +1;
                        }
                    }
                    return x.compareTo(ExtendedRationalOps.pown(v, q));
                } else if (x.signum() > 0) {
                    if (v.signum() <= 0) {
                        return +1;
                    }
                    return -x.compareTo(ExtendedRationalOps.pown(v, q));
                } else {
                    assert x.signum() < 0;
                    assert q.testBit(0);
                    if (v.signum() >= 0) {
                        return -1;
                    }
                    return -x.compareTo(ExtendedRationalOps.pown(ExtendedRationalOps.neg(v), q));
                }
            }

            @Override
            ExtendedRational opRev(ExtendedRationalContext rc, Rational v) {
                assert q.signum() != 0;
                return rc.pown(RationalOps.abs(v), q);
            }
        }, q.signum(), q.testBit(0));
    }

    static Collection<UnaryPiece> genRootnPieces(final long q) {
        return genRootnPieces(BigInteger.valueOf(q));
    }

    static Collection<UnaryPiece> genRootnPieces(final int q) {
        return genRootnPieces(BigInteger.valueOf(q));
    }
}
