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
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;
import net.java.jinterval.rational.StdFuns;

/**
 *
 */
public class SetIntervalContextInfSup extends SetIntervalContextInfSupBase {

    public SetIntervalContextInfSup(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup) {
        super(mcInf, mcSup);
    }

    @Override
    public SetInterval neg(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational l = mcInf.neg(xs);
        ExtendedRational u = mcSup.neg(xi);
        return Utils.set(l, u, x.getDecoration());
    }

    @Override
    public SetInterval add(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xl = x.inf();
        ExtendedRational xu = x.sup();
        ExtendedRational yl = y.inf();
        ExtendedRational yu = y.sup();
        ExtendedRational l = mcInf.add(xl, yl);
        ExtendedRational u = mcSup.add(xu, yu);
        return Utils.set(l, u, d);
    }

    @Override
    public SetInterval sub(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xl = x.inf();
        ExtendedRational xu = x.sup();
        ExtendedRational yl = y.inf();
        ExtendedRational yu = y.sup();
        ExtendedRational l = mcInf.sub(xl, yu);
        ExtendedRational u = mcSup.sub(xu, yl);
        return Utils.set(l, u, d);
    }

    @Override
    public SetInterval mul(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();
        ExtendedRational inf, sup;

        //[ 0, 0 ] * x = x * [ 0, 0 ] = [ 0, 0 ]
        if ((xi.signum() == 0 && xs.signum() == 0) || (yi.signum() == 0 && ys.signum() == 0)) {
            inf = sup = Rational.zero();
        } else if (ys.signum() <= 0) {
            if (xs.signum() <= 0) {
                inf = mcInf.mul(xs, ys);
                sup = mcSup.mul(xi, yi);
            } else if (xi.signum() >= 0) {
                inf = mcInf.mul(xs, yi);
                sup = mcSup.mul(xi, ys);
            } else {
                inf = mcInf.mul(xs, yi);
                sup = mcSup.mul(xi, yi);
            }
        } else if (yi.signum() >= 0) {
            if (xs.signum() <= 0) {
                inf = mcInf.mul(xi, ys);
                sup = mcSup.mul(xs, yi);
            } else if (xi.signum() >= 0) {
                inf = mcInf.mul(xi, yi);
                sup = mcSup.mul(xs, ys);
            } else {
                inf = mcInf.mul(xi, ys);
                sup = mcSup.mul(xs, ys);
            }
        } else if (xs.signum() <= 0) {
            inf = mcInf.mul(xi, ys);
            sup = mcSup.mul(xi, yi);
        } else if (xi.signum() >= 0) {
            inf = mcInf.mul(xs, yi);
            sup = mcSup.mul(xs, ys);
        } else {
            inf = ExtendedRationalOps.min(mcInf.mul(xi, ys), mcInf.mul(xs, yi));
            sup = ExtendedRationalOps.max(mcSup.mul(xi, yi), mcSup.mul(xs, ys));
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval div(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();
        ExtendedRational inf, sup;

        if (yi.signum() > 0) {
            if (xi.signum() > 0) { // x > 0, y > 0
                inf = mcInf.div(xi, ys);
                sup = mcSup.div(xs, yi);
            } else if (xs.signum() < 0) { // x < 0, y > 0
                inf = mcInf.div(xi, yi);
                sup = mcSup.div(xs, ys);
            } else { // 0 in x, y > 0
                inf = mcInf.div(xi, yi);
                sup = mcSup.div(xs, yi);
            }
        } else if (ys.signum() < 0) {
            if (xi.signum() > 0) { // x > 0, y < 0
                inf = mcInf.div(xs, ys);
                sup = mcSup.div(xi, yi);
            } else if (xs.signum() < 0) { // x < 0, y < 0
                inf = mcInf.div(xs, yi);
                sup = mcSup.div(xi, ys);
            } else { // 0 in x, y < 0
                inf = mcInf.div(xs, ys);
                sup = mcSup.div(xi, ys);
            }
        } else { // 0 in y
            if (yi.signum() == 0 && ys.signum() == 0) {
                return EmptyInterval.empty();
            }
            if (xi.signum() == 0 && xs.signum() == 0) {
                inf = sup = Rational.zero();
            } else if (xi.signum() >= 0) {
                inf = yi.signum() == 0 ? mcInf.div(xi, ys) : ExtendedRational.NEGATIVE_INFINITY;
                sup = ys.signum() == 0 ? mcSup.div(xi, yi) : ExtendedRational.POSITIVE_INFINITY;
            } else if (xs.signum() <= 0) {
                inf = ys.signum() == 0 ? mcInf.div(xs, yi) : ExtendedRational.NEGATIVE_INFINITY;
                sup = yi.signum() == 0 ? mcSup.div(xs, ys) : ExtendedRational.POSITIVE_INFINITY;
            } else {
                inf = ExtendedRational.NEGATIVE_INFINITY;
                sup = ExtendedRational.POSITIVE_INFINITY;
            }
            d = d.min(Decoration.TRV);
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval recip(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        if (xi.signum() > 0 || xs.signum() < 0) {
            return Utils.set(mcInf.recip(xs), mcSup.recip(xi), d);
        }
        if (xi.signum() == 0 && xs.signum() == 0) {
            return EmptyInterval.empty();
        }
        ExtendedRational inf = xi.signum() == 0 ? mcInf.recip(xs)
                : ExtendedRational.NEGATIVE_INFINITY;
        ExtendedRational sup = xs.signum() == 0 ? mcSup.recip(xi)
                : ExtendedRational.POSITIVE_INFINITY;
        return Utils.set(inf, sup, d.min(Decoration.TRV));
    }

    @Override
    public SetInterval sqr(SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf;
        ExtendedRational sup;
        if (xi.signum() >= 0) {
            inf = mcInf.sqr(xi);
            sup = mcSup.sqr(xs);
        } else if (xs.signum() <= 0) {
            inf = mcInf.sqr(xs);
            sup = mcSup.sqr(xi);
        } else {
            inf = Rational.zero();
            sup = ExtendedRationalOps.max(mcSup.sqr(xi), mcSup.sqr(xs));
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval sqrt(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        if (xi.signum() >= 0) {
            return Utils.set(mcInf.sqrt(xi), mcSup.sqrt(xs), d);
        }
        if (xs.signum() < 0) {
            return EmptyInterval.empty();
        }
        return Utils.set(Rational.zero(), mcSup.sqrt(xs), d.min(Decoration.TRV));
    }

    @Override
    public SetInterval pown(SetInterval x, BigInteger p) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf;
        ExtendedRational sup;
        if (p.signum() > 0) {
            if (p.testBit(0) || xi.signum() >= 0) {
                inf = mcInf.pown(xi, p);
                sup = mcSup.pown(xs, p);
            } else if (xs.signum() <= 0) {
                inf = mcInf.pown(xs, p);
                sup = mcSup.pown(xi, p);
            } else {
                inf = Rational.zero();
                sup = ExtendedRationalOps.max(mcSup.pown(xi, p), mcSup.pown(xs, p));
            }
        } else if (p.signum() < 0) {
            if (xi.signum() > 0) {
                inf = mcInf.pown(xs, p);
                sup = mcSup.pown(xi, p);
            } else if (xs.signum() < 0) {
                if (p.testBit(0)) {
                    inf = mcInf.pown(xs, p);
                    sup = mcSup.pown(xi, p);
                } else {
                    inf = mcInf.pown(xi, p);
                    sup = mcSup.pown(xs, p);
                }
            } else if (xi.signum() == 0 && xs.signum() == 0) {
                return EmptyInterval.empty();
            } else {
                if (p.testBit(0)) {
                    inf = xi.signum() == 0 ? mcInf.pown(xs, p) : ExtendedRational.NEGATIVE_INFINITY;
                    sup = xs.signum() == 0 ? mcSup.pown(xi, p) : ExtendedRational.POSITIVE_INFINITY;
                } else {
                    if (xi.signum() == 0) {
                        inf = mcInf.pown(xs, p);
                    } else if (xs.signum() == 0) {
                        inf = mcInf.pown(xi, p);
                    } else {
                        inf = ExtendedRationalOps.min(mcInf.pown(xi, p), mcInf.pown(xs, p));
                    }
                    sup = ExtendedRational.POSITIVE_INFINITY;
                }
                d = d.min(Decoration.TRV);
            }
        } else {
            inf = sup = Rational.one();
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval pow(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();

        if (xi.signum() <= 0) {
            if (xi.signum() < 0 || yi.signum() <= 0) {
                d = d.min(Decoration.TRV);
            }
            if (xs.signum() <= 0) {
                if (xs.signum() < 0 || ys.signum() <= 0) {
                    return EmptyInterval.empty();
                }
                return Utils.set(Rational.zero(), Rational.zero(), d);
            }
        }
        int xicmp = xi.compareTo(Rational.one());
        int xscmp = xs.compareTo(Rational.one());

        ExtendedRational inf, sup;

        //[ 1, 1 ] * x = x * [ 0, 0 ] = [ 1, 1 ]
        if ((xicmp == 0 && xscmp == 0) || (yi.signum() == 0 && ys.signum() == 0)) {
            inf = sup = Rational.one();
        } else if (ys.signum() <= 0) {
            if (xscmp <= 0) {
                inf = mcInf.pow(xs, ys);
                sup = xi.signum() > 0 ? mcSup.pow(xi, yi) : ExtendedRational.POSITIVE_INFINITY;
            } else if (xicmp >= 0) {
                inf = mcInf.pow(xs, yi);
                sup = mcSup.pow(xi, ys);
            } else {
                inf = mcInf.pow(xs, yi);
                sup = xi.signum() > 0 ? mcSup.pow(xi, yi) : ExtendedRational.POSITIVE_INFINITY;
            }
        } else if (yi.signum() >= 0) {
            if (xscmp <= 0) {
                inf = xi.signum() > 0 ? mcInf.pow(xi, ys) : Rational.zero();
                sup = mcSup.pow(xs, yi);
            } else if (xicmp >= 0) {
                inf = mcInf.pow(xi, yi);
                sup = mcSup.pow(xs, ys);
            } else {
                inf = xi.signum() > 0 ? mcInf.pow(xi, ys) : Rational.zero();
                sup = mcSup.pow(xs, ys);
            }
        } else if (xscmp <= 0) {
            inf = xi.signum() > 0 ? mcInf.pow(xi, ys) : Rational.zero();
            sup = xi.signum() > 0 ? mcSup.pow(xi, yi) : ExtendedRational.POSITIVE_INFINITY;
        } else if (xicmp >= 0) {
            inf = mcInf.pow(xs, yi);
            sup = mcSup.pow(xs, ys);
        } else {
            inf = xi.signum() > 0 ? ExtendedRationalOps.min(mcInf.pow(xi, ys), mcInf.pow(xs, yi)) : Rational.zero();
            sup = xi.signum() > 0 ? ExtendedRationalOps.max(mcSup.pow(xi, yi), mcSup.pow(xs, ys)) : ExtendedRational.POSITIVE_INFINITY;
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval exp(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational l = mcInf.exp(xi);
        ExtendedRational u = mcSup.exp(xs);
        return Utils.set(l, u, x.getDecoration());
    }

    @Override
    public SetInterval exp2(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational l = mcInf.exp2(xi);
        ExtendedRational u = mcSup.exp2(xs);
        return Utils.set(l, u, x.getDecoration());
    }

    @Override
    public SetInterval exp10(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational l = mcInf.exp10(xi);
        ExtendedRational u = mcSup.exp10(xs);
        return Utils.set(l, u, x.getDecoration());
    }

    @Override
    public SetInterval log(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        if (xi.signum() > 0) {
            return Utils.set(mcInf.log(xi), mcSup.log(xs), d);
        }
        if (xs.signum() <= 0) {
            return EmptyInterval.empty();
        }
        return Utils.set(Rational.NEGATIVE_INFINITY, mcSup.log(xs), d.min(Decoration.TRV));
    }

    @Override
    public SetInterval log2(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        if (xi.signum() > 0) {
            return Utils.set(mcInf.log2(xi), mcSup.log2(xs), d);
        }
        if (xs.signum() <= 0) {
            return EmptyInterval.empty();
        }
        return Utils.set(Rational.NEGATIVE_INFINITY, mcSup.log2(xs), d.min(Decoration.TRV));
    }

    @Override
    public SetInterval log10(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        if (xi.signum() > 0) {
            return Utils.set(mcInf.log10(xi), mcSup.log10(xs), d);
        }
        if (xs.signum() <= 0) {
            return EmptyInterval.empty();
        }
        return Utils.set(Rational.NEGATIVE_INFINITY, mcSup.log10(xs), d.min(Decoration.TRV));
    }

    @Override
    public SetInterval sin(SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        if (x.doubleWid() > 6.3) {
            return Utils.set(Rational.valueOf(-1), Rational.one(), d);
        }
        Rational xi = (Rational) x.inf();
        Rational xs = (Rational) x.sup();
        BigInteger ki = RationalOps.piHalfFloor(xi);
        BigInteger ks = RationalOps.piHalfFloor(xs);
        ExtendedRational inf;
        if (ki.subtract(BigInteger.valueOf(3)).shiftRight(2).equals(ks.subtract(BigInteger.valueOf(3)).shiftRight(2))) {
            inf = ExtendedRationalOps.min(mcInf.sin(xi), mcInf.sin(xs));
        } else {
            inf = Rational.valueOf(-1);
        }
        ExtendedRational sup;
        if (ki.subtract(BigInteger.ONE).shiftRight(2).equals(ks.subtract(BigInteger.ONE).shiftRight(2))) {
            sup = ExtendedRationalOps.max(mcSup.sin(xi), mcSup.sin(xs));
        } else {
            sup = Rational.one();
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval cos(SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        if (x.doubleWid() > 6.3) {
            return Utils.set(Rational.valueOf(-1), Rational.one(), d);
        }
        Rational xi = (Rational) x.inf();
        Rational xs = (Rational) x.sup();
        BigInteger ki = RationalOps.piHalfFloor(xi);
        BigInteger ks = RationalOps.piHalfFloor(xs);
        ExtendedRational inf;
        if (ki.subtract(BigInteger.valueOf(2)).shiftRight(2).equals(ks.subtract(BigInteger.valueOf(2)).shiftRight(2))) {
            inf = ExtendedRationalOps.min(mcInf.cos(xi), mcInf.cos(xs));
        } else {
            inf = Rational.valueOf(-1);
        }
        ExtendedRational sup;
        if (ki.shiftRight(2).equals(ks.shiftRight(2))) {
            sup = ExtendedRationalOps.max(mcSup.cos(xi), mcSup.cos(xs));
        } else {
            sup = Rational.one();
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval tan(SetInterval x) {
        Decoration d = x.getDecoration();
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        if (x.doubleWid() > 3.2) {
            return Utils.entire(Decoration.TRV);
        }
        Rational xi = (Rational) x.inf();
        Rational xs = (Rational) x.sup();
        BigInteger ki = RationalOps.piHalfFloor(xi);
        BigInteger ks = RationalOps.piHalfFloor(xs);
        ExtendedRational inf;
        ExtendedRational sup;
        if (ki.subtract(BigInteger.ONE).shiftRight(1).equals(ks.subtract(BigInteger.ONE).shiftRight(1))) {
            inf = ExtendedRationalOps.min(mcInf.tan(xi), mcInf.tan(xs));
            sup = ExtendedRationalOps.max(mcSup.tan(xi), mcSup.tan(xs));
        } else {
            inf = ExtendedRational.NEGATIVE_INFINITY;
            sup = ExtendedRational.POSITIVE_INFINITY;
            d = d.min(Decoration.TRV);
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval atan2(SetInterval y, SetInterval x) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational yi = y.inf();
        ExtendedRational ys = y.sup();
        if (xi.signum() == 0 && xs.signum() == 0 && yi.signum() == 0 && ys.signum() == 0) {
            return EmptyInterval.empty();
        }
        ExtendedRational inf;
        ExtendedRational sup;
        if (yi.signum() <= 0 && ys.signum() >= 0 && xi.signum() < 0) {
            sup = mcSup.rnd(StdFuns.PI);
        } else if (xi.signum() < 0 && yi.signum() >= 0) {
            sup = mcSup.atan2(yi, xi);
        } else if (ys.signum() > 0 && xi.signum() >= 0) {
            sup = mcSup.atan2(ys, xi);
        } else if (xs.signum() > 0 && ys.signum() <= 0) {
            sup = mcSup.atan2(ys, xs);
        } else {
            assert yi.signum() < 0 && xs.signum() <= 0;
            sup = mcSup.atan2(yi, xs);
        }
        if (yi.signum() < 0 && ys.signum() >= 0 && xi.signum() < 0) {
            inf = mcInf.neg(sup);
        } else if (xi.signum() < 0 && ys.signum() < 0) {
            inf = mcInf.atan2(ys, xi);
        } else if (yi.signum() < 0 && xi.signum() >= 0) {
            inf = mcInf.atan2(yi, xi);
        } else if (xs.signum() > 0 && yi.signum() >= 0) {
            inf = mcInf.atan2(yi, xs);
        } else if (ys.signum() > 0 && xs.signum() <= 0) {
            inf = mcInf.atan2(ys, xs);
        } else {
            assert yi.signum() == 0 && ys.signum() == 0 && xs.signum() <= 0;
            inf = mcInf.rnd(StdFuns.PI);
        }
        if (yi.signum() <= 0 && ys.signum() >= 0 && xi.signum() <= 0) {
            d = d.min(xs.signum() >= 0 ? Decoration.TRV : yi.signum() < 0 ? Decoration.DEF : Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    @Override
    public SetInterval sign(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        Decoration d = x.getDecoration();
        ExtendedRational inf = ExtendedRationalOps.sign(xi);
        ExtendedRational sup = ExtendedRationalOps.sign(xs);
        if (inf.ne(sup)) {
            d = d.min(Decoration.DEF);
        } else if (inf.signum() == 0) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(mcInf.rnd(inf), mcSup.rnd(sup), d);
    }

    @Override
    public SetInterval abs(SetInterval x) {
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        ExtendedRational inf;
        ExtendedRational sup;
        if (Utils.ZERO.strictPrecedes(x)) {
            inf = mcInf.rnd(x.inf());
            sup = mcSup.rnd(x.sup());
        } else if (x.strictPrecedes(Utils.ZERO)) {
            inf = mcInf.neg(x.sup());
            sup = mcSup.neg(x.inf());
        } else {
            inf = mcInf.rnd(Rational.zero());
            sup = mcSup.max(ExtendedRationalOps.neg(x.inf()), x.sup());
        }
        return Utils.set(inf, sup, x.getDecoration());
    }
}
