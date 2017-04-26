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

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;

/**
 *
 */
public class SetIntervalEvaluatorDecoratedAccur64 extends SetIntervalEvaluatorDecoratedTightest64 {

    private static final SetIntervalContext ic = SetIntervalContexts.getAccur64();

    SetIntervalEvaluatorDecoratedAccur64(CodeList codeList, Expression[] results) {
        super(codeList, results);
    }

    SetIntervalEvaluatorDecoratedAccur64(int size) {
        super(size);
    }

    @Override
    public void visitPown(int r, int x, int p) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
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
                setEmpty(r);
                return;
            } else if ((p & 1) != 0) {
                inf = xi == 0 ? Utils.pownDn(xs, p) : Double.NEGATIVE_INFINITY;
                sup = xs == 0 ? -Utils.pownDn(-xi, p) : Double.POSITIVE_INFINITY;
                d = (byte) Math.min(d, Decoration.ENC_TRV);
            } else {
                inf = Utils.pownDn(Math.max(-xi, xs), p);
                sup = Double.POSITIVE_INFINITY;
                d = (byte) Math.min(d, Decoration.ENC_TRV);
            }
        } else {
            inf = sup = 1;
        }
        set(r, inf, sup, d);
    }

    @Override
    public void visitPow(int r, int x, int y) {
        byte d = getDec(x, y);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        double yi = getInf(y);
        double ys = getSup(y);
        if (xi <= 0) {
            if (xi < 0 || yi <= 0) {
                d = (byte) Math.min(d, Decoration.ENC_TRV);
            }
            if (xs <= 0) {
                if (xs < 0 || ys <= 0) {
                    setEmpty(r);
                    return;
                }
                set(r, 0, 0, d);
                return;
            }
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
        set(r, inf, sup, d);
    }

    @Override
    public void visitExp(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        double inf = xi == 0 ? 1 : Utils.nextDn(Math.exp(xi));
        double sup = xs == 0 ? 1 : Utils.nextUp(Math.exp(xs));
        set(r, inf, sup, d);
    }

    @Override
    public void visitLog(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        double inf;
        double sup;
        if (xi > 0) {
            inf = xi == 1 ? 0 : Utils.nextDn(Math.log(xi));
            sup = xs == 1 ? 0 : Utils.nextUp(Math.log(xs));
        } else if (xs <= 0) {
            setEmpty(r);
            return;
        } else {
            inf = Double.NEGATIVE_INFINITY;
            sup = xs == 1 ? 0 : Utils.nextUp(Math.log(xs));
            d = (byte) Math.min(d, Decoration.ENC_TRV);
        }
        set(r, inf, sup, d);
    }

    @Override
    public void visitSin(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        if (-SetIntervalContextAccur64.piHalfInf <= xi && xs <= SetIntervalContextAccur64.piHalfInf) {
            // Spead-up only for subintervals of [-pi/2,+pi/2]
            double l = xi == 0 ? 0 : Math.max(-1, Utils.nextDn(Math.sin(xi)));
            double u = xs == 0 ? 0 : Math.min(1, Utils.nextUp(Math.sin(xs)));
            set(r, l, u, d);
        } else {
            set(r, ic.sin(get(x)));
        }
    }

    @Override
    public void visitCos(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        if (-SetIntervalContextAccur64.piInf <= xi && xs <= SetIntervalContextAccur64.piInf) {
            // Spead-up only for subintervals of [-pi,pi]
            double inf;
            double sup;
            if (xi > 0) {
                inf = Math.max(-1, Utils.nextDn(Math.cos(xs)));
                sup = Math.min(1, Utils.nextUp(Math.cos(xi)));
            } else if (xs < 0) {
                inf = Math.max(-1, Utils.nextDn(Math.cos(xi)));
                sup = Math.min(1, Utils.nextUp(Math.cos(xs)));
            } else {
                inf = Math.max(-1, Utils.nextDn(Math.cos(Math.max(-xi, xs))));
                sup = 1;
            }
            set(r, inf, sup, d);
        } else {
            set(r, ic.cos(get(x)));
        }
    }

    @Override
    public void visitTan(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        if (-SetIntervalContextAccur64.piHalfInf <= xi && xs <= SetIntervalContextAccur64.piHalfInf) {
            // Spead-up only for subintervals of [-pi/2,+pi/2]
            double inf = xi == 0 ? 0 : Utils.nextDn(Math.tan(xi));
            double sup = xs == 0 ? 0 : Utils.nextUp(Math.tan(xs));
            set(r, inf, sup, d);
        } else {
            set(r, ic.sin(get(x)));
        }
    }

    @Override
    public void visitAsin(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        if (xs < -1 || xi > +1) {
            setEmpty(r);
            return;
        }
        if (xi < -1) {
            xi = -1;
            d = (byte) Math.min(d, Decoration.ENC_TRV);
        }
        if (xs > +1) {
            xs = +1;
            d = (byte) Math.min(d, Decoration.ENC_TRV);
        }
        double inf = xi == 0 ? 0 : Utils.nextDn(Math.asin(xi));
        double sup = xs == 0 ? 0 : Utils.nextUp(Math.asin(xs));
        set(r, inf, sup, d);
    }

    @Override
    public void visitAcos(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        if (xs < -1 || xi > +1) {
            setEmpty(r);
            return;
        }
        if (xi < -1) {
            xi = -1;
            d = (byte) Math.min(d, Decoration.ENC_TRV);
        }
        if (xs > +1) {
            xs = +1;
            d = (byte) Math.min(d, Decoration.ENC_TRV);
        }
        double inf = xs == 1 ? 0 : Math.max(0, Utils.nextDn(Math.acos(xs)));
        double sup = xi == 1 ? 0 : Utils.nextUp(Math.acos(xi));
        set(r, inf, sup, d);
    }

    @Override
    public void visitAtan(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        double inf = xi == 0 ? 0 : Utils.nextDn(Math.atan(xi));
        double sup = xs == 0 ? 0 : Utils.nextUp(Math.atan(xs));
        set(r, inf, sup, d);
    }

    @Override
    public void visitSinh(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        double inf = xi == 0 ? 0 : Utils.nextDn(Math.sinh(xi));
        double sup = xs == 0 ? 0 : Utils.nextUp(Math.sinh(xs));
        set(r, inf, sup, d);
    }

    @Override
    public void visitCosh(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        double inf;
        double sup;
        if (xi > 0) {
            inf = Math.max(1, Utils.nextDn(Math.cosh(xi)));
            sup = Utils.nextUp(Math.cosh(xs));
        } else if (xs < 0) {
            inf = Math.max(1, Utils.nextDn(Math.cosh(xs)));
            sup = Utils.nextUp(Math.cosh(xi));
        } else {
            double xa = Math.max(-xi, xs);
            inf = 1;
            sup = Utils.nextUp(Math.cosh(xa));
        }
        set(r, inf, sup, d);
    }

    @Override
    public void visitTanh(int r, int x) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        double inf = xi == 0 ? 0 : Math.max(-1, Utils.nextDn(Math.tanh(xi)));
        double sup = xs == 0 ? 0 : Math.min(1, Utils.nextUp(Math.tanh(xs)));
        set(r, inf, sup, d);
    }

    @Override
    public void visitRootn(int r, int x, int q) {
        byte d = getDec(x);
        if (d <= Decoration.ENC_EMPTY) {
            setEmpty(r, d);
            return;
        }
        double xi = getInf(x);
        double xs = getSup(x);
        if (q > 0 && xi >= 0) {
            double yi = Utils.divDn(1, q);
            double ys = Utils.divUp(1, q);
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
            set(r, inf, sup, d);
        } else {
            set(r, ic.rootn(get(x), q));
        }
    }
}
