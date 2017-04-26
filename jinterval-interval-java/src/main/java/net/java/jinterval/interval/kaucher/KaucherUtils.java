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
package net.java.jinterval.interval.kaucher;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.DomainException;

/**
 *
 */
class KaucherUtils {

    static KaucherInterval negate(double xi, double xs, Decoration d) {
        return Utils.kaucher(-xs, -xi, d);
    }

    static KaucherInterval addNearest(double xi, double xs, double yi, double ys, Decoration d) {
        return Utils.kaucher(xi + yi, xs + ys, d);
    }

    static KaucherInterval subtractNearest(double xi, double xs, double yi, double ys, Decoration d) {
        return Utils.kaucher(xi - ys, xs - yi, d);
    }

    static KaucherInterval multiplyNearest(double xi, double xs, double yi, double ys, Decoration d) {
        double inf, sup;

        if (xi >= 0 && xs >= 0) {
            if (yi >= 0 && ys >= 0) {
                inf = xi * yi;
                sup = xs * ys;
            } else if (yi <= 0 && ys <= 0) {
                inf = xs * yi;
                sup = xi * ys;
            } else if (yi <= 0 && ys >= 0) {
                inf = xs * yi;
                sup = xs * ys;
            } else {
                inf = xi * yi;
                sup = xi * ys;
            }
        } else if (xi <= 0 && xs <= 0) {
            if (yi >= 0 && ys >= 0) {
                inf = xi * ys;
                sup = xs * yi;
            } else if (yi <= 0 && ys <= 0) {
                inf = xs * ys;
                sup = xi * yi;
            } else if (yi <= 0 && ys >= 0) {
                inf = xi * ys;
                sup = xi * yi;
            } else {
                inf = xs * ys;
                sup = xs * yi;
            }
        } else if (xi <= 0 && xs >= 0) {
            if (yi >= 0 && ys >= 0) {
                inf = xi * ys;
                sup = xs * ys;
            } else if (yi <= 0 && ys <= 0) {
                inf = xs * yi;
                sup = xi * yi;
            } else if (yi <= 0 && ys >= 0) {
                inf = Math.min(xi * ys, xs * yi);
                sup = Math.max(xi * yi, xs * ys);
            } else {
                inf = sup = 0;
            }
        } else {
            if (yi >= 0 && ys >= 0) {
                inf = xi * yi;
                sup = xs * yi;
            } else if (yi <= 0 && ys <= 0) {
                inf = xs * ys;
                sup = xi * ys;
            } else if (yi <= 0 && ys >= 0) {
                inf = sup = 0;
            } else {
                inf = Math.max(xi * yi, xs * ys);
                sup = Math.min(xi * ys, xs * yi);
            }
        }
        return Utils.kaucher(inf, sup, d);
    }

    static KaucherInterval divideNearest(double xi, double xs, double yi, double ys, Decoration d) {
        KaucherInterval yr = recipNearest(yi, ys, d);
        return multiplyNearest(xi, xs, yr.doubleInf(), yr.doubleSup(), d);
    }

    static KaucherInterval recipNearest(double xi, double xs, Decoration d) {
        if (xi > 0 && xs > 0 || xi < 0 && xs < 0) {
            double inf = 1 / xs;
            double sup = 1 / xi;
            return Utils.kaucher(inf, sup, d);
        } else {
            throw new DomainException();
        }
    }

    static KaucherInterval sqrtNearest(double xi, double xs, Decoration d) {
        if (xi >= 0 && xs >= 0) {
            double inf = Math.sqrt(xi);
            double sup = Math.sqrt(xs);
            return Utils.kaucher(inf, sup, d);
        } else {
            throw new DomainException();
        }

    }

    static KaucherInterval innerPlusNearest(double xi, double xs, double yi, double ys, Decoration d) {
        double inf = xi + ys;
        double sup = xs + yi;
        return Utils.kaucher(inf, sup, d);
    }

    static KaucherInterval innerMinusNearest(double xi, double xs, double yi, double ys, Decoration d) {
        double inf = xi - yi;
        double sup = xs - ys;
        return Utils.kaucher(inf, sup, d);
    }

    static KaucherInterval intersection(double xi, double xs, double yi, double ys, Decoration d) {
        double inf = Math.max(xi, yi);
        double sup = Math.min(xs, ys);
        return Utils.kaucher(inf, sup, d);
    }

    static KaucherInterval convexHull(double xi, double xs, double yi, double ys, Decoration d) {
        double inf = Math.min(xi, yi);
        double sup = Math.max(xs, ys);
        return Utils.kaucher(inf, sup, d);
    }
}
