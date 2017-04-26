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
package net.java.jinterval.interval.kaucher;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;

/**
 *
 */
public class KaucherIntervalContexts {

    public static KaucherIntervalContext getExact() {
        return new AbstractKaucherIntervalContext(new AbstractKaucherIntervalContext.Table()) {
            @Override
            public KaucherInterval hull(KaucherInterval x) {
                return x;
            }

            @Override
            public KaucherInterval newDec(KaucherInterval x) {
                return Utils.kaucher(x.inf(), x.sup(), Decoration.COM);
            }
        };
    }

    public static KaucherIntervalContext getInfSup(BinaryValueSet valueSet) {
        final ExtendedRationalContext mcInf = ExtendedRationalContexts.mkFloor(valueSet);
        final ExtendedRationalContext mcSup = ExtendedRationalContexts.mkCeiling(valueSet);
        return new AbstractKaucherIntervalContext(new AbstractKaucherIntervalContext.Table()) {
            @Override
            public KaucherInterval hull(KaucherInterval x) {
                return KaucherIntervalOps.hull(mcInf, mcSup, x);
            }

            @Override
            public KaucherInterval newDec(KaucherInterval x) {
                return KaucherIntervalOps.newDec(mcInf, mcSup, x);
            }

            @Override
            public KaucherInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
                return KaucherIntervalOps.nums2(mcInf, mcSup, l, u);
            }

            @Override
            public KaucherInterval neg(KaucherInterval x) {
                return KaucherIntervalOps.neg(mcInf, mcSup, x);
            }

            @Override
            public KaucherInterval add(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.add(mcInf, mcSup, x, y);
            }

            @Override
            public KaucherInterval sub(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.sub(mcInf, mcSup, x, y);
            }

            @Override
            public KaucherInterval mul(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.mul(mcInf, mcSup, x, y);
            }

            @Override
            public KaucherInterval div(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.div(mcInf, mcSup, x, y);
            }

            @Override
            public KaucherInterval recip(KaucherInterval x) {
                return KaucherIntervalOps.recip(mcInf, mcSup, x);
            }

            @Override
            public KaucherInterval sqrt(KaucherInterval x) {
                return KaucherIntervalOps.sqrt(mcInf, mcSup, x);
            }

            @Override
            public KaucherInterval cancelMinus(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.innerMinus(mcInf, mcSup, x, y);
            }

            @Override
            public KaucherInterval cancelPlus(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.innerMinus(mcInf, mcSup, x, y);
            }

            @Override
            public KaucherInterval intersection(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.intersection(mcInf, mcSup, x, y);
            }

            @Override
            public KaucherInterval convexHull(KaucherInterval x, KaucherInterval y) {
                return KaucherIntervalOps.convexHull(mcInf, mcSup, x, y);
            }
        };
    }

    public static KaucherIntervalContext getDoubleNearest() {
        final ExtendedRationalContext mc = ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64);
        return new AbstractKaucherIntervalContext(new AbstractKaucherIntervalContext.Table()) {
            @Override
            public KaucherInterval hull(KaucherInterval x) {
                if (Utils.isNonemptyInfSupDouble(x)) {
                    return x;
                } else {
                    return Utils.kaucher(x.inf().doubleValueHalfEven(), x.sup().doubleValueHalfEven(), x.getDecoration());
                }
            }

            @Override
            public KaucherInterval newDec(KaucherInterval x) {
                if (Utils.isNonemptyInfSupDouble(x) && x.getDecoration() == Decoration.COM) {
                    return x;
                } else {
                    return Utils.kaucher(x.inf().doubleValueHalfEven(), x.sup().doubleValueHalfEven(), Decoration.COM);
                }
            }

            @Override
            public KaucherInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
                return KaucherIntervalOps.nums2(l.doubleValueHalfEven(), u.doubleValueHalfEven());
            }

            @Override
            public KaucherInterval numsToInterval(double l, double u) {
                return KaucherIntervalOps.nums2(l, u);
            }

            @Override
            public KaucherInterval neg(KaucherInterval x) {
                if (Utils.isNonemptyInfSupDouble(x)) {
                    return KaucherUtils.negate(x.doubleInf(), x.doubleSup(), x.getDecoration());
                } else {
                    return KaucherIntervalOps.neg(mc, mc, x);
                }
            }

            @Override
            public KaucherInterval add(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.addNearest(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().min(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.add(mc, mc, x, y);
                }
            }

            @Override
            public KaucherInterval sub(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.subtractNearest(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().min(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.sub(mc, mc, x, y);
                }
            }

            @Override
            public KaucherInterval mul(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.multiplyNearest(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().min(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.mul(mc, mc, x, y);
                }
            }

            @Override
            public KaucherInterval div(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.divideNearest(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().min(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.div(mc, mc, x, y);
                }
            }

            @Override
            public KaucherInterval recip(KaucherInterval x) {
                if (Utils.isNonemptyInfSupDouble(x)) {
                    return KaucherUtils.recipNearest(
                            x.doubleInf(), x.doubleSup(),
                            x.getDecoration());
                } else {
                    return KaucherIntervalOps.recip(mc, mc, x);
                }
            }

            @Override
            public KaucherInterval sqrt(KaucherInterval x) {
                if (Utils.isNonemptyInfSupDouble(x)) {
                    return KaucherUtils.sqrtNearest(
                            x.doubleInf(), x.doubleSup(),
                            x.getDecoration());
                } else {
                    return KaucherIntervalOps.sqrt(mc, mc, x);
                }
            }

            @Override
            public KaucherInterval cancelMinus(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.innerMinusNearest(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().min(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.innerMinus(mc, mc, x, y);
                }
            }

            @Override
            public KaucherInterval cancelPlus(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.innerPlusNearest(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().min(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.innerPlus(mc, mc, x, y);
                }
            }

            @Override
            public KaucherInterval intersection(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.intersection(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().max(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.intersection(mc, mc, x, y);
                }
            }

            @Override
            public KaucherInterval convexHull(KaucherInterval x, KaucherInterval y) {
                if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
                    return KaucherUtils.convexHull(
                            x.doubleInf(), x.doubleSup(),
                            y.doubleInf(), y.doubleSup(),
                            x.getDecoration().min(y.getDecoration()));
                } else {
                    return KaucherIntervalOps.convexHull(mc, mc, x, y);
                }
            }
        };
    }
}
