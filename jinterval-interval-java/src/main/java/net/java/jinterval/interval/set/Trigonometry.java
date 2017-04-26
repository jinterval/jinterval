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
import net.java.jinterval.rational.CReal;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalContextBinary;
import net.java.jinterval.rational.RationalOps;
import net.java.jinterval.rational.StdFuns;

/**
 *
 */
public abstract class Trigonometry {

    static Trigonometry sin = new Trigonometry(
            Rational.valueOf(-1),
            Rational.valueOf(1),
            false, false) {
                @Override
                ExtendedRational op(ExtendedRationalContext rc, ExtendedRational x) {
                    return rc.sin(x);
                }

                @Override
                CReal getCReal(Rational x) {
                    return StdFuns.sin(x);
                }

                @Override
                CReal getRevCReal(ExtendedRational x, BigInteger k) {
                    return StdFuns.asin((Rational) x, k, k.testBit(0));
                }
            };
    static Trigonometry cos = new Trigonometry(
            Rational.valueOf(-1),
            Rational.valueOf(1),
            true, false) {
                @Override
                ExtendedRational op(ExtendedRationalContext rc, ExtendedRational x) {
                    return rc.cos(x);
                }

                @Override
                CReal getCReal(Rational x) {
                    return StdFuns.cos(x);
                }

                @Override
                CReal getRevCReal(ExtendedRational x, BigInteger k) {
                    if (k.testBit(0)) {
                        return StdFuns.acos((Rational) x, k.add(BigInteger.ONE), true);
                    } else {
                        return StdFuns.acos((Rational) x, k, false);
                    }
                }
            };
    static Trigonometry tan = new Trigonometry(
            ExtendedRational.NEGATIVE_INFINITY,
            ExtendedRational.POSITIVE_INFINITY,
            false, true) {
                @Override
                ExtendedRational op(ExtendedRationalContext rc, ExtendedRational x) {
                    return rc.tan(x);
                }

                @Override
                CReal getCReal(Rational x) {
                    return StdFuns.tan(x);
                }

                @Override
                CReal getRevCReal(ExtendedRational x, BigInteger k) {
                    if (x.isPositiveInfinity()) {
                        return StdFuns.atan2(Rational.one(), Rational.zero(), k);
                    } else if (x.isNegativeInfinity()) {
                        return StdFuns.atan2(Rational.valueOf(-1), Rational.zero(), k);
                    } else {
                        return StdFuns.atan((Rational) x, k);
                    }
                }
            };
    private final ExtendedRational rInf, rSup;
    private final boolean symm;
    private final boolean brk;

    abstract ExtendedRational op(ExtendedRationalContext rc, ExtendedRational x);

    abstract CReal getCReal(Rational x);

    abstract CReal getRevCReal(ExtendedRational x, BigInteger k);

    Trigonometry(ExtendedRational rInf, ExtendedRational rSup, boolean symm, boolean brk) {
        this.rInf = rInf;
        this.rSup = rSup;
        this.symm = symm;
        this.brk = brk;
    }

    private boolean increasing(BigInteger kPi) {
        return brk || kPi.testBit(0) == symm;
    }

    SetInterval eval(ExtendedRationalContext rcInf, ExtendedRationalContext rcSup, SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        if (x.doubleWid() > (brk ? 3.2 : 6.3)) {
            if (brk) {
                d = d.min(Decoration.TRV);
            }
            return Utils.set(rInf, rSup, d);
        }
        Rational xi = (Rational) x.inf();
        Rational xs = (Rational) x.sup();
        BigInteger ki = RationalOps.piHalfFloor(xi);
        BigInteger ks = RationalOps.piHalfFloor(xs);
        if (!symm) {
            ki = ki.add(BigInteger.ONE);
            ks = ks.add(BigInteger.ONE);
        }
        ki = ki.shiftRight(1);
        ks = ks.shiftRight(1);
        ExtendedRational inf, sup;
        switch (ks.subtract(ki).intValue()) {
            case 0:
                if (increasing(ki)) {
                    inf = op(rcInf, xi);
                    sup = op(rcSup, xs);
                } else {
                    inf = op(rcInf, xs);
                    sup = op(rcSup, xi);
                }
                break;
            case 1:
                if (increasing(ki)) {
                    inf = op(rcInf, xi);
                    sup = rSup;
                } else {
                    inf = rInf;
                    sup = op(rcSup, xi);
                }
                if (increasing(ks)) {
                    inf = ExtendedRationalOps.min(inf, rInf);
                    sup = ExtendedRationalOps.max(sup, op(rcSup, xs));
                } else {
                    inf = ExtendedRationalOps.min(inf, op(rcInf, xs));
                    sup = ExtendedRationalOps.max(sup, rSup);
                }
                if (brk) {
                    d = d.min(Decoration.TRV);
                }
                break;
            default:
                inf = rInf;
                sup = rSup;
                if (brk) {
                    d = d.min(Decoration.TRV);
                }
        }
        return Utils.set(inf, sup, d);
    }

    private ExtendedRational evalRevImpl(ExtendedRationalContext rc, ExtendedRational c, BigInteger kPi) {
        return rc.rnd(getRevCReal(c, kPi));
    }

    SetInterval evalRev(ExtendedRationalContext rcInf, ExtendedRationalContext rcSup, SetInterval c, SetInterval x) {
        Decoration d = x.getDecoration().min(c.getDecoration()).min(Decoration.TRV);
        if (c.isEmpty() || x.isEmpty() || c.sup().lt(rInf) || c.inf().gt(rSup)) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational ci = ExtendedRationalOps.max(c.inf(), rInf);
        ExtendedRational cs = ExtendedRationalOps.min(c.sup(), rSup);
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        BigInteger ki = null, ks = null;
        ExtendedRational inf = null, sup = null;
        if (xi.isNegativeInfinity()) {
            inf = ExtendedRational.NEGATIVE_INFINITY;
        } else {
            ki = RationalOps.piHalfFloor((Rational) xi);
            if (!symm) {
                ki = ki.add(BigInteger.ONE);
            }
            ki = ki.shiftRight(1);
            CReal cr = getCReal((Rational) xi);
            if (increasing(ki)) {
                if (cr.compare(cs) > 0) {
                    ki = ki.add(BigInteger.ONE);
                } else if (cr.compare(ci) < 0) {
                    inf = evalRevImpl(rcInf, ci, ki);
                } else {
                    inf = rcInf.rnd(xi);
                }
            } else {
                if (cr.compare(ci) < 0) {
                    ki = ki.add(BigInteger.ONE);
                } else if (cr.compare(cs) > 0) {
                    inf = evalRevImpl(rcInf, cs, ki);
                } else {
                    inf = rcInf.rnd(xi);
                }
            }
            if (inf == null) {
                if (increasing(ki)) {
                    inf = evalRevImpl(rcInf, ci, ki);
                } else {
                    inf = evalRevImpl(rcInf, cs, ki);
                }
            }
        }
        if (xs.isPositiveInfinity()) {
            sup = ExtendedRational.POSITIVE_INFINITY;
        } else {
            ks = RationalOps.piHalfFloor((Rational) xs);
            if (!symm) {
                ks = ks.add(BigInteger.ONE);
            }
            ks = ks.shiftRight(1);
            CReal cr = getCReal((Rational) xs);
            if (increasing(ks)) {
                if (cr.compare(ci) < 0) {
                    ks = ks.subtract(BigInteger.ONE);
                } else if (cr.compare(cs) > 0) {
                    sup = evalRevImpl(rcSup, cs, ks);
                } else {
                    sup = rcSup.rnd(xs);
                }
            } else {
                if (cr.compare(cs) > 0) {
                    ks = ks.subtract(BigInteger.ONE);
                } else if (cr.compare(ci) < 0) {
                    sup = evalRevImpl(rcSup, ci, ks);
                } else {
                    sup = rcSup.rnd(xs);
                }
            }
            if (sup == null) {
                if (increasing(ks)) {
                    sup = evalRevImpl(rcSup, cs, ks);
                } else {
                    sup = evalRevImpl(rcSup, ci, ks);
                }
            }
        }
        return ki != null && ks != null && ki.compareTo(ks) > 0 ? EmptyInterval.empty(d) : Utils.set(inf, sup, d);
    }
}
