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
import net.java.jinterval.rational.ExtendedRationalContexts;

/**
 *
 */
class SetIntervalContextAccur64 extends SetIntervalContextInfSup {

    static final double piInf = Math.PI;
    static final double piSup = Math.nextUp(Math.PI);
    static final double piHalfInf = Math.PI / 2;
    static final double piHalfSup = Math.nextUp(Math.PI / 2);
    static final double eulerInf = Math.E;
    static final double eulerSup = Math.nextUp(Math.E);

    SetIntervalContextAccur64() {
        super(ExtendedRationalContexts.mkFloor(BinaryValueSet.BINARY64),
                ExtendedRationalContexts.mkCeiling(BinaryValueSet.BINARY64));
    }

    @Override
    public SetInterval hull(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            return x;
        }
        if (x.isEmpty()) {
            return SetUtils.copyEmpty(x);
        }
        return super.hull(x);
    }

    @Override
    public SetInterval numsToInterval(double l, double u) {
        if (l <= u && l != Double.POSITIVE_INFINITY && u != Double.NEGATIVE_INFINITY) {
            return Utils.set(l, u, Decoration.COM);
        }
        throw new UndefinedOperationException();
    }

    @Override
    public SetInterval numsDecToInterval(double l, double u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        if (l <= u && l != Double.POSITIVE_INFINITY && u != Double.NEGATIVE_INFINITY && decoration != Decoration.ILL) {
            if (decoration != Decoration.COM || Double.isFinite(l) && Double.isFinite(u)) {
                return Utils.set(l, u, decoration);
            }
        }
        throw new UndefinedOperationException();
    }

    @Override
    public SetInterval pi() {
        return Utils.set(piInf, piSup);
    }

    @Override
    public SetInterval euler() {
        return Utils.set(eulerInf, eulerSup);
    }

    @Override
    public SetInterval neg(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            return Utils.set(-xs, -xi, d);
        } else {
            return super.neg(x);
        }
    }

    @Override
    public SetInterval add(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            double yi = y.doubleInf();
            double ys = y.doubleSup();
            Decoration d = x.getDecoration().min(y.getDecoration());
            return Utils.set(Utils.addDn(xi, yi), Utils.addUp(xs, ys), d);
        } else {
            return super.add(x, y);
        }
    }

    @Override
    public SetInterval sub(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            double yi = y.doubleInf();
            double ys = y.doubleSup();
            Decoration d = x.getDecoration().min(y.getDecoration());
            return Utils.set(Utils.subDn(xi, ys), Utils.subUp(xs, yi), d);
        } else {
            return super.sub(x, y);
        }
    }

    @Override
    public SetInterval mul(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            double yi = y.doubleInf();
            double ys = y.doubleSup();
            Decoration d = x.getDecoration().min(y.getDecoration());
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
            return Utils.set(inf, sup, d);
        } else {
            return super.mul(x, y);
        }
    }

    @Override
    public SetInterval div(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            double yi = y.doubleInf();
            double ys = y.doubleSup();
            Decoration d = x.getDecoration().min(y.getDecoration());
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
                    return EmptyInterval.empty();
                }
                if (xi == 0 && xs == 0) {
                    inf = sup = 0;
                } else if (xi >= 0) {
                    inf = yi == 0 ? Utils.divDn(xi, ys) : Double.NEGATIVE_INFINITY;
                    sup = ys == 0 ? -Utils.divDn(xi, -yi) : Double.POSITIVE_INFINITY;
                } else if (xs <= 0) {
                    inf = ys == 0 ? Utils.divDn(-xs, -yi) : Double.NEGATIVE_INFINITY;
                    sup = yi == 0 ? -Utils.divDn(-xs, ys) : Double.POSITIVE_INFINITY;
                } else {
                    inf = Double.NEGATIVE_INFINITY;
                    sup = Double.POSITIVE_INFINITY;
                }
                d = d.min(Decoration.TRV);
            }
            return Utils.set(inf, sup, d);
        } else {
            return super.div(x, y);
        }
    }

    @Override
    public SetInterval recip(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            if (xi > 0 || xs < 0) {
                return Utils.set(Utils.divDn(1, xs), Utils.divUp(1, xi), d);
            } else if (xs < 0) {
                return Utils.set(-Utils.divUp(1, -xs), -Utils.divDn(1, -xi), d);
            }
            if (xi == 0 && xs == 0) {
                return EmptyInterval.empty();
            }
            double inf = xi == 0 ? Utils.divDn(1, xs) : Double.NEGATIVE_INFINITY;
            double sup = xs == 0 ? -Utils.divDn(1, -xi) : Double.POSITIVE_INFINITY;
            return Utils.set(inf, sup, d.min(Decoration.TRV));
        } else {
            return super.recip(x);
        }
    }

    @Override
    public SetInterval sqr(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
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
            return Utils.set(inf, sup, d);
        } else {
            return super.sqr(x);
        }
    }

    @Override
    public SetInterval sqrt(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            if (xi >= 0) {
                return Utils.set(Utils.sqrtDn(xi), Utils.sqrtUp(xs), d);
            }
            if (xs < 0) {
                return EmptyInterval.empty();
            }
            return Utils.set(0, Utils.sqrtUp(xs), d.min(Decoration.TRV));
        } else {
            return super.sqrt(x);
        }
    }

    @Override
    public SetInterval pown(SetInterval x, int p) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            double inf;
            double sup;
            if (p > 0) {
                if (xi >= 0) {
                    inf = Utils.pownDn(xi, p);
                    sup = Utils.pownUp(xs, p);
                } else if (xs <= 0) {
                    if ((p & 1) != 0) {
                        inf = -Utils.pownUp(-xi, p);
                        sup = -Utils.pownDn(-xs, p);
                    } else {
                        inf = Utils.pownDn(-xs, p);
                        sup = Utils.pownUp(-xi, p);
                    }
                } else if ((p & 1) != 0) {
                    inf = -Utils.pownUp(-xi, p);
                    sup = Utils.pownUp(xs, p);
                } else {
                    inf = 0;
                    sup = Utils.pownUp(Math.max(-xi, xs), p);
                }
            } else if (p < 0) {
                if (xi > 0) {
                    inf = Utils.pownDn(xs, p);
                    sup = Utils.pownUp(xi, p);
                } else if (xs < 0) {
                    if ((p & 1) != 0) {
                        inf = -Utils.pownUp(-xs, p);
                        sup = -Utils.pownDn(-xi, p);
                    } else {
                        inf = Utils.pownDn(-xi, p);
                        sup = Utils.pownUp(-xs, p);
                    }
                } else if (xi == 0 && xs == 0) {
                    return EmptyInterval.empty();
                } else {
                    if ((p & 1) != 0) {
                        inf = xi == 0 ? Utils.pownDn(xs, p) : Double.NEGATIVE_INFINITY;
                        sup = xs == 0 ? -Utils.pownDn(-xi, p) : Double.POSITIVE_INFINITY;
                    } else {
                        inf = Utils.pownDn(Math.max(-xi, xs), p);
                        sup = Double.POSITIVE_INFINITY;
                    }
                    d = d.min(Decoration.TRV);
                }
            } else {
                inf = sup = 1;
            }
            return Utils.set(inf, sup, d);
        } else {
            return super.pown(x, p);
        }
    }

    @Override
    public SetInterval pow(SetInterval x, SetInterval y) {
        if (Utils.isNonemptyInfSupDouble(x) && Utils.isNonemptyInfSupDouble(y)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            double yi = y.doubleInf();
            double ys = y.doubleSup();
            Decoration d = x.getDecoration().min(y.getDecoration());

            if (xi < 0 || xi == 0 && yi <= 0) {
                d = d.min(Decoration.TRV);
            }
            if (xs <= 0) {
                if (xs < 0 || ys <= 0) {
                    return EmptyInterval.empty();
                }
                return Utils.set(0, 0, d);
            }
            int xicmp = Double.compare(xi, 1);
            int xscmp = Double.compare(xs, 1);

            double inf, sup;

            //[ 1, 1 ] * x = x * [ 0, 0 ] = [ 1, 1 ]
            if ((xicmp == 0 && xscmp == 0) || (yi == 0 && ys == 0)) {
                inf = sup = 1;
            } else if (ys <= 0) {
                if (xscmp <= 0) {
                    inf = Utils.powDn(xs, ys);
                    sup = xi > 0 ? Utils.powUp(xi, yi) : Double.POSITIVE_INFINITY;
                } else if (xicmp >= 0) {
                    inf = Utils.powDn(xs, yi);
                    sup = Utils.powUp(xi, ys);
                } else {
                    inf = Utils.powDn(xs, yi);
                    sup = xi > 0 ? Utils.powUp(xi, yi) : Double.POSITIVE_INFINITY;
                }
            } else if (yi >= 0) {
                if (xscmp <= 0) {
                    inf = xi > 0 ? Utils.powDn(xi, ys) : 0;
                    sup = Utils.powUp(xs, yi);
                } else if (xicmp >= 0) {
                    inf = Utils.powDn(xi, yi);
                    sup = Utils.powUp(xs, ys);
                } else {
                    inf = xi > 0 ? Utils.powDn(xi, ys) : 0;
                    sup = Utils.powUp(xs, ys);
                }
            } else if (xscmp <= 0) {
                inf = xi > 0 ? Utils.powDn(xi, ys) : 0;
                sup = xi > 0 ? Utils.powUp(xi, yi) : Double.POSITIVE_INFINITY;
            } else if (xicmp >= 0) {
                inf = Utils.powDn(xs, yi);
                sup = Utils.powUp(xs, ys);
            } else {
                inf = xi > 0
                        ? Math.min(Utils.powDn(xi, ys), Utils.powDn(xs, yi))
                        : 0;
                sup = xi > 0
                        ? Math.max(Utils.powUp(xi, yi), Utils.powUp(xs, ys))
                        : Double.POSITIVE_INFINITY;
            }
            return Utils.set(inf, sup, d);
        } else {
            return super.pow(x, y);
        }
    }

    @Override
    public SetInterval exp(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            double l = Math.nextDown(Math.exp(xi));
            double u = Math.nextUp(Math.exp(xs));
            return Utils.set(l, u, d);
        } else {
            return super.exp(x);
        }
    }

    @Override
    public SetInterval log(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            if (xi > 0) {
                return Utils.set(Math.nextDown(Math.log(xi)), Math.nextUp(Math.log(xs)), d);
            }
            if (xs <= 0) {
                return EmptyInterval.empty();
            }
            return Utils.set(Double.NEGATIVE_INFINITY, Math.nextUp(Math.log(xs)), d.min(Decoration.TRV));
        } else {
            return super.log(x);
        }
    }

    @Override
    public SetInterval sin(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            if (-piHalfInf <= xi && xs <= piHalfInf) {
                // Spead-up only for subintervals of [-pi/2,+pi/2]
                Decoration d = x.getDecoration();
                double l = xi == 0 ? 0 : Math.max(-1, Math.nextDown(Math.sin(xi)));
                double u = xs == 0 ? 0 : Math.min(1, Math.nextUp(Math.sin(xs)));
                return Utils.set(l, u, d);
            }
        }
        return super.sin(x);
    }

    @Override
    public SetInterval cos(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            if (0 <= xi && xs <= 2 * piHalfInf) {
                // Spead-up only for subintervals of [0,pi]
                Decoration d = x.getDecoration();
                double l = xs == 0 ? 1 : Math.max(-1, Math.nextDown(Math.cos(xs)));
                double u = xi == 0 ? 1 : Math.min(1, Math.nextUp(Math.cos(xi)));
                return Utils.set(l, u, d);
            }
        }
        return super.cos(x);
    }

    @Override
    public SetInterval tan(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            if (-piHalfInf <= xi && xs <= piHalfInf) {
                // Spead-up only for subintervals of [-pi/2,+pi/2]
                Decoration d = x.getDecoration();
                double l = Math.nextDown(Math.tan(xi));
                double u = Math.nextUp(Math.tan(xs));
                return Utils.set(l, u, d);
            }
        }
        return super.tan(x);
    }

    @Override
    public SetInterval asin(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();

            if (xs < -1 || xi > +1) {
                return EmptyInterval.empty();
            } else {
                if (xi < -1) {
                    xi = -1;
                    d = d.min(Decoration.TRV);
                }
                if (xs > +1) {
                    xs = +1;
                    d = d.min(Decoration.TRV);
                }
                return Utils.set(Utils.nextDn(Math.asin(xi)), Utils.nextUp(Math.asin(xs)), d);
            }
        } else {
            return super.asin(x);
        }
    }

    @Override
    public SetInterval acos(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();

            if (xs < -1 || xi > +1) {
                return EmptyInterval.empty();
            } else {
                if (xi < -1) {
                    xi = -1;
                    d = d.min(Decoration.TRV);
                }
                if (xs > +1) {
                    xs = +1;
                    d = d.min(Decoration.TRV);
                }
                return Utils.set(Utils.nextDn(Math.acos(xs)), Utils.nextUp(Math.acos(xi)), d);
            }
        } else {
            return super.acos(x);
        }
    }

    @Override
    public SetInterval atan(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            double l = Math.nextDown(Math.atan(xi));
            double u = Math.nextUp(Math.atan(xs));
            return Utils.set(l, u, d);
        } else {
            return super.atan(x);
        }
    }

    @Override
    public SetInterval sinh(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            double l = Math.nextDown(Math.sinh(xi));
            double u = Math.nextUp(Math.sinh(xs));
            return Utils.set(l, u, d);
        } else {
            return super.sinh(x);
        }
    }

    @Override
    public SetInterval cosh(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            double inf;
            double sup;
            if (xi >= 0) {
                inf = Utils.nextDn(Math.cosh(xi));
                sup = Utils.nextUp(Math.cosh(xs));
            } else if (xs <= 0) {
                inf = Utils.nextDn(Math.cosh(xs));
                sup = Utils.nextUp(Math.cosh(xi));
            } else {
                double xa = Math.max(-xi, xs);
                inf = 1;
                sup = Utils.nextUp(Math.cosh(xa));
            }
            return Utils.set(inf, sup, d);
        } else {
            return super.cosh(x);
        }
    }

    @Override
    public SetInterval tanh(SetInterval x) {
        if (Utils.isNonemptyInfSupDouble(x)) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            Decoration d = x.getDecoration();
            double l = Math.nextDown(Math.tanh(xi));
            double u = Math.nextUp(Math.tanh(xs));
            return Utils.set(l, u, d);
        } else {
            return super.tanh(x);
        }
    }

    @Override
    public SetInterval rootn(SetInterval x, int q) {
        if (Utils.isNonemptyInfSupDouble(x) && q > 0 && x.doubleInf() >= 0) {
            double xi = x.doubleInf();
            double xs = x.doubleSup();
            double yi = Utils.divDn(1, q);
            double ys = Utils.divUp(1, q);
            Decoration d = x.getDecoration();
            double inf;
            double sup;

            //[ 1, 1 ] ^ 1/q = [ 1, 1 ]
            if (xi == 1 && xs == 1) {
                inf = sup = 1;
            } else if (xs <= 1) {
                inf = xi > 0 ? Utils.powDn(xi, ys) : 0;
                sup = xs < 1 ? Utils.powUp(xs, yi) : 1;
            } else if (xi >= 1) {
                inf = xi > 1 ? Utils.powDn(xi, yi) : 1;
                sup = Utils.powUp(xs, ys);
            } else {
                inf = xi > 0 ? Utils.powDn(xi, ys) : 0;
                sup = Utils.powUp(xs, ys);
            }
            return Utils.set(inf, sup, d);
        } else {
            return super.rootn(x, q);
        }
    }
}
