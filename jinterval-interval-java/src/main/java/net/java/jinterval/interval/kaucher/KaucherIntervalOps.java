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
import net.java.jinterval.rational.*;

/**
 *
 */
public class KaucherIntervalOps {

    private KaucherIntervalOps() {
    }

    public static KaucherInterval hull(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x) {
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf = mcInf.rnd(xi);
        ExtendedRational sup = mcSup.rnd(xs);
        if (inf.eq(xi) && sup.eq(xs)) {
            return x;
        } else if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, x.getDecoration());
        } else {
            throw new ArithmeticException("Overflow");
        }
    }

    public static KaucherInterval newDec(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x) {
        ExtendedRational xi = x.inf();
        ExtendedRational xs = x.sup();
        ExtendedRational inf = mcInf.rnd(xi);
        ExtendedRational sup = mcSup.rnd(xs);
        if (inf.eq(xi) && sup.eq(xs) && x.getDecoration() == Decoration.COM) {
            return x;
        } else if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, Decoration.COM);
        } else {
            throw new ArithmeticException("Overflow");
        }
    }

    public static KaucherInterval nums2(ExtendedRational l, ExtendedRational u) {
        return Utils.kaucher((Rational) l, (Rational) u, Decoration.COM);
    }

    public static KaucherInterval nums2(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, ExtendedRational l, ExtendedRational u) {
        ExtendedRational inf = mcInf.rnd(l);
        ExtendedRational sup = mcSup.rnd(u);
        if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, Decoration.COM);
        }
        throw new ArithmeticException("overflow");
    }

    public static KaucherInterval nums2(double l, double u) {
        if (Math.abs(l) < Double.POSITIVE_INFINITY && Math.abs(u) < Double.POSITIVE_INFINITY) {
            return Utils.kaucher(l, u, Decoration.COM);
        }
        throw new ArithmeticException("overflow");
    }

    public static KaucherInterval neg(KaucherInterval x) {
        return neg(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x);
    }

    public static KaucherInterval neg(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x) {
        Rational xl = x.inf();
        Rational xu = x.sup();
        ExtendedRational l = mcInf.neg(xu);
        ExtendedRational u = mcSup.neg(xl);
        if (l instanceof Rational && u instanceof Rational) {
            return Utils.kaucher((Rational) l, (Rational) u, x.getDecoration());
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval add(KaucherInterval x, KaucherInterval y) {
        return add(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval add(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        Rational xl = x.inf();
        Rational xu = x.sup();
        Rational yl = y.inf();
        Rational yu = y.sup();
        ExtendedRational l = mcInf.add(xl, yl);
        ExtendedRational u = mcSup.add(xu, yu);
        if (l instanceof Rational && u instanceof Rational) {
            return Utils.kaucher((Rational) l, (Rational) u, d);
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval sub(KaucherInterval x, KaucherInterval y) {
        return sub(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval sub(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        Rational xl = x.inf();
        Rational xu = x.sup();
        Rational yl = y.inf();
        Rational yu = y.sup();
        ExtendedRational l = mcInf.sub(xl, yu);
        ExtendedRational u = mcSup.sub(xu, yl);
        if (l instanceof Rational && u instanceof Rational) {
            return Utils.kaucher((Rational) l, (Rational) u, d);
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval mul(KaucherInterval x, KaucherInterval y) {
        return mul(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval mul(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        Rational xi = x.inf();
        Rational xs = x.sup();
        Rational yi = y.inf();
        Rational ys = y.sup();
        ExtendedRational inf, sup;

        if (xi.signum() >= 0 && xs.signum() >= 0) {
            if (yi.signum() >= 0 && ys.signum() >= 0) {
                inf = mcInf.mul(xi, yi);
                sup = mcSup.mul(xs, ys);
            } else if (yi.signum() <= 0 && ys.signum() <= 0) {
                inf = mcInf.mul(xs, yi);
                sup = mcSup.mul(xi, ys);
            } else if (yi.signum() <= 0 && ys.signum() >= 0) {
                inf = mcInf.mul(xs, yi);
                sup = mcSup.mul(xs, ys);
            } else {
                inf = mcInf.mul(xi, yi);
                sup = mcSup.mul(xi, ys);
            }
        } else if (xi.signum() <= 0 && xs.signum() <= 0) {
            if (yi.signum() >= 0 && ys.signum() >= 0) {
                inf = mcInf.mul(xi, ys);
                sup = mcSup.mul(xs, yi);
            } else if (yi.signum() <= 0 && ys.signum() <= 0) {
                inf = mcInf.mul(xs, ys);
                sup = mcSup.mul(xi, yi);
            } else if (yi.signum() <= 0 && ys.signum() >= 0) {
                inf = mcInf.mul(xi, ys);
                sup = mcSup.mul(xi, yi);
            } else {
                inf = mcInf.mul(xs, ys);
                sup = mcSup.mul(xs, yi);
            }
        } else if (xi.signum() <= 0 && xs.signum() >= 0) {
            if (yi.signum() >= 0 && ys.signum() >= 0) {
                inf = mcInf.mul(xi, ys);
                sup = mcSup.mul(xs, ys);
            } else if (yi.signum() <= 0 && ys.signum() <= 0) {
                inf = mcInf.mul(xs, yi);
                sup = mcSup.mul(xi, yi);
            } else if (yi.signum() <= 0 && ys.signum() >= 0) {
                inf = mcInf.min(mcInf.mul(xi, ys), mcInf.mul(xs, yi));
                sup = mcSup.max(mcSup.mul(xi, yi), mcSup.mul(xs, ys));
            } else {
                inf = sup = Rational.zero();
            }
        } else {
            if (yi.signum() >= 0 && ys.signum() >= 0) {
                inf = mcInf.mul(xi, yi);
                sup = mcSup.mul(xs, yi);
            } else if (yi.signum() <= 0 && ys.signum() <= 0) {
                inf = mcInf.mul(xs, ys);
                sup = mcSup.mul(xi, ys);
            } else if (yi.signum() <= 0 && ys.signum() >= 0) {
                inf = sup = Rational.zero();
            } else {
                inf = mcInf.max(mcInf.mul(xi, yi), mcInf.mul(xs, ys));
                sup = mcSup.min(mcSup.mul(xi, ys), mcSup.mul(xs, yi));
            }
        }
        if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, d);
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval div(KaucherInterval x, KaucherInterval y) {
        return div(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval div(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        return mul(mcInf, mcSup, x, recip(y));
    }

    public static KaucherInterval recip(KaucherInterval x) {
        return recip(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x);
    }

    public static KaucherInterval recip(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x) {
        Rational xi = x.inf();
        Rational xs = x.sup();
        if (xi.signum() > 0 && xs.signum() > 0 || xi.signum() < 0 && xs.signum() < 0) {
            ExtendedRational inf = mcInf.recip(xs);
            ExtendedRational sup = mcSup.recip(xi);
            if (inf instanceof Rational && sup instanceof Rational) {
                return Utils.kaucher((Rational) inf, (Rational) sup, x.getDecoration());
            } else {
                throw new ArithmeticException("overflow");
            }
        } else {
            throw new DomainException();
        }
    }

    public static KaucherInterval sqrt(KaucherInterval x) {
        return sqrt(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x);
    }

    public static KaucherInterval sqrt(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x) {
        Rational xi = x.inf();
        Rational xs = x.sup();
        if (xi.signum() >= 0 && xs.signum() >= 0) {
            ExtendedRational inf = mcInf.sqrt(xi);
            ExtendedRational sup = mcSup.sqrt(xs);
            if (inf instanceof Rational && sup instanceof Rational) {
                return Utils.kaucher((Rational) inf, (Rational) sup, x.getDecoration());
            } else {
                throw new ArithmeticException("overflow");
            }
        } else {
            throw new DomainException();
        }
    }

    public static KaucherInterval innerPlus(KaucherInterval x, KaucherInterval y) {
        return innerPlus(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval innerPlus(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        ExtendedRational inf = mcInf.add(x.inf(), y.sup());
        ExtendedRational sup = mcSup.add(x.sup(), y.inf());
        if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, d);
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval innerMinus(KaucherInterval x, KaucherInterval y) {
        return innerMinus(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval innerMinus(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        ExtendedRational inf = mcInf.sub(x.inf(), y.inf());
        ExtendedRational sup = mcSup.sub(x.sup(), y.sup());
        if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, d);
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval intersection(KaucherInterval x, KaucherInterval y) {
        return intersection(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval intersection(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        ExtendedRational inf = mcInf.max(x.inf(), y.inf());
        ExtendedRational sup = mcSup.min(x.sup(), y.sup());
        if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, d);
        } else {
            throw new ArithmeticException("overflow");
        }
    }

    public static KaucherInterval convexHull(KaucherInterval x, KaucherInterval y) {
        return convexHull(ExtendedRationalContexts.exact(), ExtendedRationalContexts.exact(), x, y);
    }

    public static KaucherInterval convexHull(ExtendedRationalContext mcInf, ExtendedRationalContext mcSup, KaucherInterval x, KaucherInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        ExtendedRational inf = mcInf.min(x.inf(), y.inf());
        ExtendedRational sup = mcSup.max(x.sup(), y.sup());
        if (inf instanceof Rational && sup instanceof Rational) {
            return Utils.kaucher((Rational) inf, (Rational) sup, d);
        } else {
            throw new ArithmeticException("overflow");
        }
    }
}
