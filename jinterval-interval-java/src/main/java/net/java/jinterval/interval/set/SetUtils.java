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

/**
 *
 */
class SetUtils {

    static SetInterval copyEmpty(SetInterval x) {
        return x.isEmpty() ? x : EmptyInterval.empty(x.getDecoration());
    }

    static SetInterval negate(double xi, double xs, Decoration d) {
        return Utils.set(-xs, -xi, d);
    }

    static SetInterval caseOp(
            double ci, double cs, Decoration cd,
            double gi, double gs, Decoration gd,
            double hi, double hs, Decoration hd) {
        if (ci >= 0) {
            return Utils.set(gi, gs, cd.min(gd));
        }
        if (cs < 0) {
            return Utils.set(hi, hs, cd.min(hd));
        }
        return Utils.set(Math.min(gi, hi), Math.max(gs, hs), cd.min(gd).min(hd).min(Decoration.DAC));
    }

    static SetInterval sign(double xi, double xs, Decoration d) {
        double inf, sup;
        if (xi > 0) {
            inf = sup = 1;
        } else if (xs < 0) {
            inf = sup = -1;
        } else {
            inf = xi < 0 ? -1 : 0;
            sup = xs > 0 ? 1 : 0;
            d = d.min(xi == xs ? Decoration.DAC : Decoration.DEF);
        }
        return Utils.set(inf, sup, d);
    }

    static SetInterval ceil(double xi, double xs, Decoration d) {
        double inf = Math.ceil(xi);
        double sup = Math.ceil(xs);
        if (inf != sup) {
            d = d.min(Decoration.DEF);
        } else if (!(sup > xs)) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    static SetInterval floor(double xi, double xs, Decoration d) {
        double inf = Math.floor(xi);
        double sup = Math.floor(xs);
        if (inf != sup) {
            d = d.min(Decoration.DEF);
        } else if (!(inf < xi)) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    static SetInterval trunc(double xi, double xs, Decoration d) {
        double inf, sup;
        if (xi > 0) {
            inf = Math.floor(xi);
            sup = Math.floor(xs);
            if (inf != sup) {
                d = d.min(Decoration.DEF);
            } else if (!(inf < xi)) {
                d = d.min(Decoration.DAC);
            }
        } else if (xs < 0) {
            inf = Math.ceil(xi);
            sup = Math.ceil(xs);
            if (inf != sup) {
                d = d.min(Decoration.DEF);
            } else if (!(sup > xs)) {
                d = d.min(Decoration.DAC);
            }
        } else {
            inf = Math.ceil(xi);
            sup = Math.floor(xi);
            if (xi <= -1 || xs >= 1) {
                d = d.min(Decoration.DEF);
            }
        }
        return Utils.set(inf, sup, d);
    }

    static SetInterval roundTiesToEven(double xi, double xs, Decoration d) {
        double inf = Math.rint(xi);
        double sup = Math.rint(xs);
        if (inf != sup) {
            d = d.min(Decoration.DEF);
        } else if (!(Math.abs(xi - inf) < 0.5 && Math.abs(xs - sup) < 0.5)) {
            d = d.min(Decoration.DAC);
        }
        return Utils.set(inf, sup, d);
    }

    static SetInterval roundTiesToAway(double xi, double xs, Decoration d) {
        throw new UnsupportedOperationException();
    }

    static SetInterval abs(double xi, double xs, Decoration d) {
        if (xi > 0) {
            return Utils.set(xi, xs, d);
        } else if (xs < 0) {
            return Utils.set(-xs, -xi, d);
        } else {
            return Utils.set(0, Math.max(-xi, xs));
        }
    }

    static SetInterval min(double xi, double xs, double yi, double ys, Decoration d) {
        return Utils.set(Math.min(xi, yi), Math.min(xs, ys), d);
    }

    static SetInterval max(double xi, double xs, double yi, double ys, Decoration d) {
        return Utils.set(Math.max(xi, yi), Math.max(xs, ys), d);
    }

    static SetInterval intersection(double xi, double xs, double yi, double ys, Decoration d) {
        double inf = Math.max(xi, yi);
        double sup = Math.min(xs, ys);
        if (inf <= sup) {
            return Utils.set(inf, sup, d);
        } else {
            return EmptyInterval.NaI();
        }
    }

    static SetInterval convexHull(double xi, double xs, double yi, double ys, Decoration d) {
        double inf = Math.min(xi, yi);
        double sup = Math.max(xs, ys);
        return Utils.set(inf, sup, d);
    }
}
