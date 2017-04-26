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
 /*
 * DIEF = Double Interval Elementary Functions
 *
 * Класс содержит в себе простейшие математические функции:
 * тригонометрические (sin, cos, tan, cot, asin, acos и т.д.)
 * и экспоненциальные (exp, log, sqr, sqrt)
 *
 * список элементарных функций:
 * Intrval trigonometric functions:
 sin+
 cos+
 tan+
 cot+
 sec+
 csc+
 asin+
 acos+
 atan+
 acot+
 asec
 acsc
 modpi2+

 Interval exponential functions:
 exp+
 log+
 log10+
 log2+
 sqr+
 isqr+
 sqrt+

 */
package net.java.jinterval.interval.set;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Interval;
import net.java.jinterval.interval.Utils;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;

/**
 *
 * @author danilov.maxim
 */
class DIEF {

    private static final double log2 = Math.log(2);
    private static final double log10 = Math.log(10);

    static SetInterval addNearest(double xi, double xs, double yi, double ys, Decoration d) {
        return Utils.set(xi + yi, xs + ys, d);
    }

    static SetInterval subtractNearest(double xi, double xs, double yi, double ys, Decoration d) {
        return Utils.set(xi - ys, xs - yi, d);
    }

    static SetInterval multiplyNearest(double xi, double xs, double yi, double ys, Decoration d) {
        double inf, sup;

        //[ 0, 0 ] * x = x * [ 0, 0 ] = [ 0, 0 ]
        if ((xi == 0 && xs == 0) || (yi == 0 && ys == 0)) {
            inf = sup = 0;
        } else if (ys <= 0) {
            if (xs <= 0) {
                inf = xs * ys;
                sup = xi * yi;
            } else if (xi >= 0) {
                inf = xs * yi;
                sup = xi * ys;
            } else {
                inf = xs * yi;
                sup = xi * yi;
            }
        } else if (yi >= 0) {
            if (xs <= 0) {
                inf = xi * ys;
                sup = xs * yi;
            } else if (xi >= 0) {
                inf = xi * yi;
                sup = xs * ys;
            } else {
                inf = xi * ys;
                sup = xs * ys;
            }
        } else if (xs <= 0) {
            inf = xi * ys;
            sup = xi * yi;
        } else if (xi >= 0) {
            inf = xs * yi;
            sup = xs * ys;
        } else {
            inf = Math.min(xi * ys, xs * yi);
            sup = Math.max(xi * yi, xs * ys);
        }
        return Utils.set(inf, sup, d);
    }

    static SetInterval divideNearest(double xi, double xs, double yi, double ys, Decoration d) {
        double inf, sup;

        if (yi > 0) {
            if (xi > 0) { // x > 0, y > 0
                inf = xi / ys;
                sup = xs / yi;
            } else if (xs < 0) { // x < 0, y > 0
                inf = xi / yi;
                sup = xs / ys;
            } else { // 0 in x, y > 0
                inf = xi / yi;
                sup = xs / yi;
            }
        } else if (ys < 0) {
            if (xi > 0) { // x > 0, y < 0
                inf = xs / ys;
                sup = xi / yi;
            } else if (xs < 0) { // x < 0, y < 0
                inf = xs / yi;
                sup = xi / ys;
            } else { // 0 in x, y < 0
                inf = xs / ys;
                sup = xi / ys;
            }
        } else { // 0 in y
            if (yi == 0 && ys == 0) {
                return EmptyInterval.empty();
            }
            if (xi == 0 && xs == 0) {
                inf = sup = 0;
            } else if (xi >= 0) {
                inf = yi == 0 ? xi / ys : Double.NEGATIVE_INFINITY;
                sup = ys == 0 ? xi / yi : Double.POSITIVE_INFINITY;
            } else if (xs <= 0) {
                inf = ys == 0 ? xs / yi : Double.NEGATIVE_INFINITY;
                sup = yi == 0 ? xs / ys : Double.POSITIVE_INFINITY;
            } else {
                inf = Double.NEGATIVE_INFINITY;
                sup = Double.POSITIVE_INFINITY;
            }
            d = d.min(Decoration.TRV);
        }
        return Utils.set(inf, sup, d);
    }

    static SetInterval recipNearest(double xi, double xs, Decoration d) {
        if (xi > 0 || xs < 0) {
            return Utils.set(1 / xs, 1 / xi, d);
        }
        if (xi == 0 && xs == 0) {
            return EmptyInterval.empty();
        }
        double inf = xi == 0 ? 1 / xs : Double.NEGATIVE_INFINITY;
        double sup = xs == 0 ? 1 / xi : Double.POSITIVE_INFINITY;
        return Utils.set(inf, sup, d.min(Decoration.TRV));
    }

    static SetInterval sqrtNearest(double xi, double xs, Decoration d) {
        if (xi >= 0) {
            return Utils.set(Math.sqrt(xi), Math.sqrt(xs), d);
        }
        if (xs >= 0) {
            return Utils.set(0, Math.sqrt(xs), d.min(Decoration.TRV));
        }
        return EmptyInterval.empty();
    }

    static SetInterval cancelPlusNearest(double xi, double xs, double yi, double ys, Decoration d) {
        double xw = xs - xi;
        double yw = ys - yi;
        if (xw > yw && xw < Double.POSITIVE_INFINITY) {
            return Utils.set(xi + ys, xs + yi, d);
        } else if (xw == yw) {
            ExtendedRational exw = ExtendedRationalOps.add(ExtendedRational.valueOf(xi), ExtendedRational.valueOf(ys));
            ExtendedRational eyw = ExtendedRationalOps.add(ExtendedRational.valueOf(xs), ExtendedRational.valueOf(yi));
            if (exw instanceof Rational && exw.ge(eyw)) {
                return Utils.set(xi - yi, xs - ys, d);
            }
        }
        return EmptyInterval.NaI();
    }

    static SetInterval cancelMinusNearest(double xi, double xs, double yi, double ys, Decoration d) {
        double xw = xs - xi;
        double yw = ys - yi;
        if (xw > yw && xw < Double.POSITIVE_INFINITY) {
            return Utils.set(xi - yi, xs - ys, d);
        } else if (xw == yw) {
            ExtendedRational exw = ExtendedRationalOps.sub(ExtendedRational.valueOf(xi), ExtendedRational.valueOf(yi));
            ExtendedRational eyw = ExtendedRationalOps.sub(ExtendedRational.valueOf(xs), ExtendedRational.valueOf(ys));
            if (exw instanceof Rational && exw.ge(eyw)) {
                return Utils.set(xi - yi, xs - ys, d);
            }
        }
        return EmptyInterval.NaI();
    }

    /**
     * Функция возвращает количество вхождений в интервал периода равного Pi
     *
     */
    public static int imodpi2(Interval arg) {
//        System.out.println("int mopi2 "+(int)(arg.wid()/(java.lang.Math.PI/2)));
        return (int) (arg.doubleWid() / (Math.PI / 2));
    }

    /**
     * Функция возвращает целую часть от деления на Pi
     *
     */
    public static int modpi2(double arg) {
        //      System.out.println("period "+arg/(Math.PI/2));
        //      System.out.println("period 2 "+(Math.abs(arg/(Math.PI/2))-0.5));
        return (int) (arg / (Math.PI / 2));
    }

    /**
     * Интервальный арккосинус. возвращается правильный интервал Interval acos.
     *
     */
    public static SetInterval acos(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        }
        double xi = arg.doubleInf();
        double xs = arg.doubleSup();
        if (xs < -1 || xi > +1) {
            return EmptyInterval.empty();
        } else {
            Decoration d = arg.getDecoration();
            if (xi < -1) {
                xi = -1;
                d = d.min(Decoration.TRV);
            }
            if (xs > +1) {
                xs = +1;
                d = d.min(Decoration.TRV);
            }
            return Utils.set(Math.acos(xs), Math.acos(xi), d);
        }
    }

    /**
     * Интервальный арксинус. возвращается правильный интервал Interval asin.
     *
     */
    public static SetInterval asin(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        }
        double xi = arg.doubleInf();
        double xs = arg.doubleSup();
        if (xs < -1 || xi > +1) {
            return EmptyInterval.empty();
        } else {
            Decoration d = arg.getDecoration();
            if (xi < -1) {
                xi = -1;
                d = d.min(Decoration.TRV);
            }
            if (xs > +1) {
                xs = +1;
                d = d.min(Decoration.TRV);
            }
            return Utils.set(Math.asin(xi), Math.asin(xs), d);
        }
    }

    /**
     * Интервальный арктангенс. возвращается правильный интервал Interval atan.
     *
     */
    public static SetInterval atan(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else {
            return Utils.set(Math.atan(arg.doubleInf()),
                    Math.atan(arg.doubleSup()), arg.getDecoration());
        }
    }

    /**
     * Интервальный арккотангенс. возвращается правильный интервал Interval
     * acot.
     *
     */
    public static SetInterval acot(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else {
            return Utils.set(Math.PI / 2
                    - Math.atan(arg.doubleSup()),
                    Math.PI / 2 - Math.atan(arg.doubleInf()), arg.getDecoration());
        }
    }

    /**
     * Интервальный косинус. возвращается правильный интервал Interval cos.
     *
     */
    public static SetInterval cos(SetInterval arg) {
        int k;
        double kpi, lb, ub;
        if (arg.isEmpty()) {
            return arg;
        } else if (DIEF.imodpi2(arg) > 2) {
            return Utils.set(-1, 1, arg.getDecoration());
        } else if (arg.doubleSup() <= 0) {
            k = DIEF.modpi2(arg.doubleInf()) / 2;
            kpi = k * (Math.PI);
            //  System.out.println("сработал <0");
            //  System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi < arg.doubleSup()) {
                if (k % 2 == 0) {
                    return Utils.set(Math.min(Math.cos(arg.doubleInf()), Math.cos(arg.doubleSup())), 1, arg.getDecoration());
                } else {
                    return Utils.set(-1, Math.max(Math.cos(arg.doubleInf()), Math.cos(arg.doubleSup())), arg.getDecoration());
                }
            } else {
                lb = Math.cos(arg.doubleInf());
                ub = Math.cos(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        } else if ((arg.doubleInf() <= 0) && (arg.doubleSup()
                >= 0)) {
            k = DIEF.modpi2(Math.max(Math.abs(arg.doubleInf()), arg.doubleSup())) / 2;
            kpi = k * (Math.PI);
            //  System.out.println("сработал <>");
            //  System.out.println("k = "+k+" kpi = "+kpi);
            if (((-kpi > arg.doubleInf()) || (kpi < arg.doubleSup()))
                    && (k != 0)) {
                return Utils.set(-1, 1, arg.getDecoration());
            } else {
                return Utils.set(Math.min(Math.cos(arg.doubleInf()), Math.cos(arg.doubleSup())), 1, arg.getDecoration());
            }
        } else {
            k = DIEF.modpi2(arg.doubleSup()) / 2;
            kpi = k * (Math.PI);
            //  System.out.println("сработал >0");
            //  System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi > arg.doubleInf()) {
                if (k % 2 == 0) {
                    return Utils.set(Math.min(Math.cos(arg.doubleInf()), Math.cos(arg.doubleSup())), 1, arg.getDecoration());
                } else {
                    return Utils.set(-1, Math.max(Math.cos(arg.doubleInf()), Math.cos(arg.doubleSup())), arg.getDecoration());
                }
            } else {
                lb = Math.cos(arg.doubleInf());
                ub = Math.cos(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        }

    }

    /**
     * Интервальный синус. возвращается правильный интервал Interval sin.
     *
     */
    public static SetInterval sin(SetInterval arg) {
        int k, kp, km;
        double kpi, kppi, kmpi, lb, ub;
        if (arg.isEmpty()) {
            return arg;
        } else if (DIEF.imodpi2(arg) > 2) {
            return Utils.set(-1, 1, arg.getDecoration());
        } else if (arg.doubleSup() <= 0) {
            k = DIEF.modpi2(arg.doubleInf());
            kpi = k * (Math.PI / 2);
            // System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi < arg.doubleSup()) {
                if (-k % 4 == 3) {
                    return Utils.set(Math.min(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), 1, arg.getDecoration());
                } else if (-k % 4 == 1) {
                    return Utils.set(-1, Math.max(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), arg.getDecoration());
                } else {
                    return Utils.set(Math.min(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), Math.max(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), arg.getDecoration());
                }
            } else {
                lb = Math.sin(arg.doubleInf());
                ub = Math.sin(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        } else if ((arg.doubleInf() <= 0) && (arg.doubleSup()
                >= 0)) {
            kp = DIEF.modpi2(arg.doubleSup());
            kppi = kp * (Math.PI);

            km = DIEF.modpi2(arg.doubleInf());
            kmpi = km * (Math.PI);

            //  System.out.println("сработал <>");
            if ((kp != 0) && (km != 0)) {
                return Utils.set(-1, 1, arg.getDecoration());
            } else if ((km == 0) && (kp != 0)) {
                return Utils.set(Math.min(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), 1, arg.getDecoration());
            } else if ((km != 0) && (kp == 0)) {
                return Utils.set(-1, Math.sin(arg.doubleSup()), arg.getDecoration());
            } else {
                return Utils.set(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup()), arg.getDecoration());
            }
        } else {
            k = DIEF.modpi2(arg.doubleSup());
            kpi = k * (Math.PI / 2);
            //  System.out.println("сработал >0");
            //  System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi > arg.doubleInf()) {
                if (k % 4 == 1) {
                    return Utils.set(Math.min(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), 1, arg.getDecoration());
                } else if (k % 4 == 3) {
                    return Utils.set(-1, Math.max(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), arg.getDecoration());
                } else {
                    return Utils.set(Math.min(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), Math.max(Math.sin(arg.doubleInf()), Math.sin(arg.doubleSup())), arg.getDecoration());
                }
            } else {
                lb = Math.sin(arg.doubleInf());
                ub = Math.sin(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        }

    }

    /**
     * Интервальный тангенс. возвращается правильный интервал Interval tan.
     *
     */
    public static SetInterval tan(SetInterval arg) {
        int k;
        double kpi2;
        if (arg.isEmpty() || (DIEF.imodpi2(arg) >= 2)) {
            return arg;
        } else if (arg.doubleSup() < 0) {
            k = DIEF.modpi2(arg.doubleInf());
            kpi2 = k * (Math.PI / 2);

            if (kpi2 < arg.doubleSup()) {
                if (k % 2 != 0) {
                    return EmptyInterval.empty();
                } else {
                    return Utils.set(Math.tan(arg.doubleInf()), Math.tan(arg.doubleSup()), arg.getDecoration());
                }
            } else {
                return Utils.set(Math.tan(arg.doubleInf()), Math.tan(arg.doubleSup()), arg.getDecoration());
            }
        } else if ((arg.doubleInf() <= 0) && (arg.doubleSup()
                >= 0)) {
            if (DIEF.modpi2(Math.max(Math.abs(arg.doubleInf()), arg.doubleSup()))
                    >= 1) {
                return EmptyInterval.empty();
            } else {
                return Utils.set(Math.tan(arg.doubleInf()), Math.tan(arg.doubleSup()), arg.getDecoration());
            }
        } else {
            k = DIEF.modpi2(arg.doubleSup());
            kpi2 = k * (Math.PI / 2);

            if (kpi2 > arg.doubleInf()) {
                if (k % 2 != 0) {
                    return EmptyInterval.empty();
                } else {
                    return Utils.set(Math.tan(arg.doubleInf()), Math.tan(arg.doubleSup()), arg.getDecoration());
                }
            } else {
                return Utils.set(Math.tan(arg.doubleInf()), Math.tan(arg.doubleSup()), arg.getDecoration());
            }
        }

    }

    /**
     * Интервальный котангенс. возвращается правильный интервал Interval cot.
     *
     */
    public static SetInterval cot(SetInterval arg) {
        int k;
        double kpi;
        if (arg.isEmpty()) {
            return arg;
        } else if (DIEF.imodpi2(arg) >= 2) {
            return EmptyInterval.empty();
        } else if (arg.doubleSup() < 0) {
            System.out.println("worked <0 v cot");
            k = DIEF.modpi2(arg.doubleInf()) / 2;
            kpi = k * Math.PI;
            System.out.println("k = " + k + " kpi = " + kpi);

            if (kpi < arg.doubleSup()) {
                return EmptyInterval.empty();
                //else return new DoubleInterval(Math.tan(arg.doubleInf()),Math.tan(arg.doubleSup()));
            } else {
                double inf = Math.min(1 / Math.tan(arg.doubleSup()), 1 / Math.tan(arg.doubleInf()));
                double sup = Math.max(1 / Math.tan(arg.doubleSup()), 1 / Math.tan(arg.doubleInf()));
                return Utils.set(inf, sup, arg.getDecoration());
            }
        } else if ((arg.doubleInf() <= 0) && (arg.doubleSup()
                >= 0)) {
            System.out.println("worked <> v cot ");
            return EmptyInterval.empty();
            //else return new DoubleInterval(Math.ceil(Math.tan(arg.doubleInf())),Math.tan(arg.doubleSup()));
        } else {
            k = DIEF.modpi2(arg.doubleSup()) / 2;
            kpi = k * Math.PI;

            if (kpi > arg.doubleInf()) {
                return EmptyInterval.empty();
                //else return new DoubleInterval(Math.tan(arg.doubleInf()),Math.tan(arg.doubleSup()));
            } else {
                return Utils.set(1 / Math.tan(arg.doubleSup()), 1
                        / Math.tan(arg.doubleInf()), arg.getDecoration());
            }
        }

    }

    /**
     * Интервальный секанс (1/cos). возвращается правильный интервал Interval
     * sec.
     *
     */
    public static SetInterval sec(SetInterval arg) {
        int k/*
                 * , kp, km
                 */;
        double kpi,/*
                 * kppi, kmpi,
                 */ lb, ub;
        if (arg.isEmpty()) {
            return arg;
        } else if (DIEF.imodpi2(arg) >= 2) {
            return EmptyInterval.empty();
        } else if (arg.doubleSup() <= 0) {
            k = DIEF.modpi2(arg.doubleInf());
            kpi = k * (Math.PI / 2);
            //  System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi < arg.doubleSup()) {
                if (k % 2 != 0) {
                    return EmptyInterval.empty();
                } else if ((k / 2) % 2 != 0) {
                    return Utils.set(Math.min(1
                            / Math.cos(arg.doubleInf()), 1
                            / Math.cos(arg.doubleSup())), -1, arg.getDecoration());
                } else {
                    return Utils.set(1, Math.max(1
                            / Math.cos(arg.doubleInf()), 1
                            / Math.cos(arg.doubleSup())), arg.getDecoration());
                }
            } else {
                lb = 1 / Math.cos(arg.doubleInf());
                ub = 1 / Math.cos(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        } else if ((arg.doubleInf() <= 0) && (arg.doubleSup()
                >= 0)) {
            if (DIEF.modpi2(Math.max(Math.abs(arg.doubleInf()), arg.doubleSup()))
                    > 1) {
                return EmptyInterval.empty();
            } else {
                return Utils.set(1, Math.max(1
                        / Math.cos(arg.doubleInf()), 1
                        / Math.cos(arg.doubleSup())), arg.getDecoration());
            }
        } else {
            k = DIEF.modpi2(arg.doubleSup());
            kpi = k * (Math.PI / 2);
            //   System.out.println("сработал >0");
            //   System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi > arg.doubleInf()) {
                if (k % 2 != 0) {
                    return EmptyInterval.empty();
                } else if ((k / 2) % 2 != 0) {
                    return Utils.set(Math.min(1
                            / Math.cos(arg.doubleInf()), 1
                            / Math.cos(arg.doubleSup())), -1, arg.getDecoration());
                } else {
                    return Utils.set(1, Math.max(1
                            / Math.cos(arg.doubleInf()), 1
                            / Math.cos(arg.doubleSup())), arg.getDecoration());
                }
            } else {
                lb = 1 / Math.cos(arg.doubleInf());
                ub = 1 / Math.cos(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        }

    }

    /**
     * Интервальный косеканс (1/sin). возвращается правильный интервал Interval
     * csc.
     *
     */
    public static SetInterval csc(SetInterval arg) {
        int k;
        double kpi, lb, ub;
        if (arg.isEmpty()) {
            return arg;
        } else if (DIEF.imodpi2(arg) >= 2) {
            return EmptyInterval.empty();
        } else if (arg.doubleSup() < 0) {
            k = DIEF.modpi2(arg.doubleInf());
            kpi = ((int) (k / 2)) * Math.PI;
            //   System.out.println("сработал <0");
            //   System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi < arg.doubleSup()) {
                if ((k / 2) % 2 == 0) {
                    return EmptyInterval.empty();
                }
                if (-k % 4 == 3) {
                    return Utils.set(
                            1,
                            Math.max(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            arg.getDecoration());
                } else if (-k % 4 == 1) {
                    return Utils.set(
                            Math.min(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            -1,
                            arg.getDecoration());
                } else {
                    return Utils.set(
                            Math.min(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            Math.max(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            arg.getDecoration());
                }
            } else {
                lb = 1 / Math.sin(arg.doubleInf());
                ub = 1 / Math.sin(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        } else if ((arg.doubleInf() <= 0) && (arg.doubleSup()
                >= 0)) {
            return EmptyInterval.empty();
        } else {
            k = DIEF.modpi2(arg.doubleSup());
            kpi = k * Math.PI / 2;
            //    System.out.println("сработал >0");
            //   System.out.println("k = "+k+" kpi = "+kpi);
            if (kpi > arg.doubleInf()) {
                if (((k / 2) % 2 == 0) && ((int) (k / 2) != 0)) {
                    return EmptyInterval.empty();
                }
                if (k % 4 == 1) {
                    return Utils.set(
                            1,
                            Math.max(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            arg.getDecoration());
                } else if (k % 4 == 3) {
                    return Utils.set(
                            Math.min(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            -1,
                            arg.getDecoration());
                } else {
                    return Utils.set(
                            Math.min(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            Math.max(1 / Math.sin(arg.doubleInf()), 1 / Math.sin(arg.doubleSup())),
                            arg.getDecoration());
                }
            } else {
                lb = 1 / Math.sin(arg.doubleInf());
                ub = 1 / Math.sin(arg.doubleSup());
                return Utils.set(Math.min(lb, ub), Math.max(lb, ub), arg.getDecoration());
            }
        }
    }

    public static SetInterval cos2(SetInterval arg) {
        return sin(Utils.set(arg.doubleInf() + Math.PI / 2, arg.doubleSup() + Math.PI / 2, arg.getDecoration()));
    }

    /**
     * Интервальный арксеканс. возвращается правильный интервал Interval asec.
     *
     */
    public static SetInterval asec(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        }
        return acos(recipNearest(arg.doubleInf(), arg.doubleSup(), arg.getDecoration()));
    }

    /**
     * Интервальный арккосеканс. возвращается правильный интервал Interval acsc.
     *
     */
    public static SetInterval acsc(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        }
        return asin(recipNearest(arg.doubleInf(), arg.doubleSup(), arg.getDecoration()));
    }

    /**
     * Интервальная функция exp. возвращается правильный интервал Interval exp.
     *
     */
    public static SetInterval exp(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else {
            return Utils.set(Math.exp(arg.doubleInf()), Math.exp(arg.doubleSup()), arg.getDecoration());
        }
    }

    /**
     * Интервальная функция exp2. возвращается правильный интервал Interval
     * exp2.
     *
     */
    public static SetInterval exp2(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else {
            return Utils.set(Math.exp(arg.doubleInf() * log2), Math.exp(arg.doubleSup() * log2), arg.getDecoration());
        }
    }

    /**
     * Интервальная функция exp10. возвращается правильный интервал Interval
     * exp10.
     *
     */
    public static SetInterval exp10(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else {
            return Utils.set(Math.exp(arg.doubleInf() * log10), Math.exp(arg.doubleSup() * log10), arg.getDecoration());
        }
    }

    /**
     * Интервальный гиперболический синус, возвращается правильный интервал
     * Interval sinh.
     *
     */
    public static SetInterval sinh(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else {
            return Utils.set((Math.exp(arg.doubleInf()) - Math.exp(-arg.doubleInf())) / 2, (Math.exp(arg.doubleSup()) - Math.exp(-arg.doubleSup())) / 2, arg.getDecoration());
        }
    }

    /**
     * Интервальный гиперболический косинус, возвращается правильный интервал
     * Interval cosh.
     *
     */
    public static SetInterval cosh(SetInterval arg) {
        if ((arg.doubleInf() < 0) && (arg.doubleSup() < 0)) {
            return Utils.set((Math.exp(arg.doubleSup()) + Math.exp(-arg.doubleSup())) / 2, (Math.exp(arg.doubleInf()) + Math.exp(-arg.doubleInf())) / 2, arg.getDecoration());
        } else if ((arg.doubleInf() * arg.doubleSup()) <= 0) {
            double maxbound = 0;
            maxbound = Math.max(Math.abs(arg.doubleInf()), arg.doubleSup());
            return Utils.set(1, (Math.exp(maxbound) + Math.exp(-maxbound)) / 2, arg.getDecoration());
        } else {
            return Utils.set((Math.exp(arg.doubleInf()) + Math.exp(-arg.doubleInf())) / 2, (Math.exp(arg.doubleSup()) + Math.exp(-arg.doubleSup())) / 2, arg.getDecoration());
        }
    }

    /**
     * Интервальный логарифм по основанию е. возвращается правильный интервал
     * Interval log.
     *
     */
    public static SetInterval log(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        }
        if (arg.doubleSup() <= 0) {
            return EmptyInterval.empty();
        }
        if (arg.doubleInf() > 0) {
            return Utils.set(Math.log(arg.doubleInf()), Math.log(arg.doubleSup()), arg.getDecoration());
        } else {
            return Utils.set(Double.NEGATIVE_INFINITY, Math.log(arg.doubleSup()), arg.getDecoration().min(Decoration.TRV));
        }
    }

    /**
     * Интервальный логарифм по основанию 10. возвращается правильный интервал
     * Interval log10.
     *
     */
    public static SetInterval log10(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        }
        if ((arg.doubleSup() > 0) && (arg.doubleInf() > 0)) {
            return Utils.set(Math.log10(arg.doubleInf()), Math.log10(arg.doubleSup()), arg.getDecoration());
        } else {
            return EmptyInterval.empty();
        }

    }

    /**
     * Интервальный логарифм по основанию 2. возвращается правильный интервал
     * Interval log2.
     *
     */
    public static SetInterval log2(SetInterval arg) {
        double lb, ub;
        if (arg.isEmpty()) {
            return arg;
        }
        if ((arg.doubleSup() > 0) && (arg.doubleInf() > 0)) {
            lb = Math.log(arg.doubleInf()) / Math.log(2);
            ub = Math.log(arg.doubleSup()) / Math.log(2);
            if (arg.doubleInf() == 1) {
                lb = 0;
            }
            if (arg.doubleSup() == 1) {
                ub = 0;
            }
            return Utils.set(lb, ub, arg.getDecoration());
        } else {
            return EmptyInterval.empty();
        }

    }

    /**
     * Возведение интервала в степень 2, т.е. интервал умножается сам на себя.
     * возвращается правильный интервал Interval isqr.
     *
     */
    public static SetInterval isqr(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else {
            double ai = arg.doubleInf();
            double as = arg.doubleSup();
            return multiplyNearest(ai, as, ai, as, arg.getDecoration());
        }
    }

    /**
     * функция возвращает значение интервальной функции y=sqr(x) возвращается
     * правильный интервал Interval y=sqr(x).
     *
     */
    public static SetInterval sqr(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        } else if (arg.doubleSup() < 0) {
            return Utils.set(
                    arg.doubleSup() * arg.doubleSup(),
                    arg.doubleInf() * arg.doubleInf(),
                    arg.getDecoration());
        } else if ((arg.doubleInf() <= 0) && (arg.doubleSup() >= 0)) {
            double ub = Math.max(Math.abs(arg.doubleInf()), arg.doubleSup());
            return Utils.set(0, ub * ub, arg.getDecoration());
        } else {
            return Utils.set(
                    arg.doubleInf() * arg.doubleInf(),
                    arg.doubleSup() * arg.doubleSup(),
                    arg.getDecoration());
        }
    }

    /**
     * функция возвращает значение интервальной функции y=sqrt(x) возвращается
     * правильный интервал Interval y=sqrt(x).
     *
     */
    public static SetInterval sqrt(SetInterval arg) {
        if (arg.isEmpty()) {
            return arg;
        }
        if ((arg.doubleInf() >= 0) && (arg.doubleSup() >= 0)) {
            return Utils.set(Math.sqrt(arg.doubleInf()), Math.sqrt(arg.doubleSup()), arg.getDecoration());
        } else {
            return EmptyInterval.empty();
        }

    }

    public static SetInterval power(SetInterval a, SetInterval y) {
        Decoration d = a.getDecoration().min(y.getDecoration());
        if (a.isEmpty() || y.isEmpty()) {
            return EmptyInterval.empty(d);
        }
        if (a.doubleSup() < 0 || a.doubleSup() == 0 && y.doubleSup() <= 0) {
            return EmptyInterval.empty();
        }
        if (a.doubleInf() < 0 || a.doubleInf() == 0 && y.doubleInf() <= 0) {
            d = d.min(Decoration.TRV);
        }
        SetInterval x = Utils.set(Math.max(0, a.doubleInf()), a.doubleSup(), d);
        if (y.doubleInf() == y.doubleSup()) {
            long n = (long) y.doubleInf();
            if (n == y.doubleInf()) {
                return power(x, n);
            }
        }
        SetInterval logx = DIEF.log(x);
        assert !y.isEmpty() && !logx.isEmpty();
        SetInterval ylogx = multiplyNearest(y.doubleInf(), y.doubleSup(), logx.doubleInf(), logx.doubleSup(), d);
        return DIEF.exp(ylogx);
    }

    public static SetInterval power(SetInterval a, long n) {
        if (a.isEmpty()) {
            return a;
        }
        try {
            double l = a.doubleInf();
            double h = a.doubleSup();
            assert l <= h;
            double lr, hr;
            if (n >= -4 && n <= 4) {
                switch ((int) n) {
                    case 4:
                        if (l >= 0) {
                            lr = l * l;
                            hr = h * h;
                        } else if (h <= 0) {
                            lr = h * h;
                            hr = l * l;
                        } else {
                            lr = 0;
                            double m = Math.max(-l, h);
                            hr = m * m;
                        }
                        lr = lr * lr;
                        hr = hr * hr;
                        break;
                    case 3:
                        lr = l * l * l;
                        hr = h * h * h;
                        break;
                    case 2:
                        if (l >= 0) {
                            lr = l * l;
                            hr = h * h;
                        } else if (h <= 0) {
                            lr = h * h;
                            hr = l * l;
                        } else {
                            lr = 0;
                            double m = Math.max(-l, h);
                            hr = m * m;
                        }
                        break;
                    case 1:
                        lr = l;
                        hr = h;
                        break;
                    case 0:
                        lr = hr = 1.0;
                        break;
                    case -1:
                        if (l > 0 || h < 0) {
                            lr = 1 / h;
                            hr = 1 / l;
                        } else {
                            return EmptyInterval.empty();
                        }
                        break;
                    case -2:
                        if (l > 0) {
                            lr = 1 / h;
                            hr = 1 / l;
                        } else if (h < 0) {
                            lr = 1 / l;
                            hr = 1 / h;
                        } else {
                            return EmptyInterval.empty();
                        }
                        lr = lr * lr;
                        hr = hr * hr;
                        break;
                    case -3:
                        if (l > 0 || h < 0) {
                            lr = 1 / h;
                            hr = 1 / l;
                        } else {
                            return EmptyInterval.empty();
                        }
                        lr = lr * lr * lr;
                        hr = hr * hr * hr;
                        break;
                    case -4:
                        if (l > 0) {
                            lr = 1 / h;
                            hr = 1 / l;
                        } else if (h < 0) {
                            lr = 1 / l;
                            hr = 1 / h;
                        } else {
                            return EmptyInterval.empty();
                        }
                        lr = lr * lr;
                        lr = lr * lr;
                        hr = hr * hr;
                        hr = hr * hr;
                        break;
                    default:
                        throw new AssertionError();
                }
            } else if (n > 0) {
                if ((n & 1) != 0 || l >= 0) {
                    lr = powerPos(l, n);
                    hr = powerPos(h, n);
                } else if (h <= 0) {
                    lr = powerPos(h, n);
                    hr = powerPos(l, n);
                } else {
                    lr = 0;
                    hr = powerPos(Math.max(-l, h), n);
                }
            } else if (n == Long.MIN_VALUE) {
                return power(power(a, 2), n / 2);
            } else if ((n & 1) != 0 || l > 0) {
                lr = powerPos(1 / h, -n);
                hr = powerPos(1 / l, -n);
            } else if (h < 0) {
                lr = powerPos(1 / l, -n);
                hr = powerPos(1 / h, -n);
            } else {
                return EmptyInterval.empty();
            }
            return Utils.set(lr, hr, a.getDecoration());
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    private static double powerPos(double a, long n) {
        double r = 1.0;
        while (n > 0) {
            if ((n & 1) != 0) {
                r *= a;
                n--;
            } else {
                a = a * a;
                n = n >> 1;
            }
        }
        return r;
    }

    public static SetInterval intersect(SetInterval x, SetInterval y) {
        Decoration d = x.getDecoration().min(y.getDecoration());
        if (x.disjoint(y)) {
            return EmptyInterval.empty(d);
        }
        return Utils.set(Math.max(x.doubleInf(), y.doubleInf()), Math.min(x.doubleSup(), y.doubleSup()), d);
    }

    public static SetInterval union(SetInterval x, SetInterval y) {
        return Utils.set(
                Math.min(x.doubleInf(), y.doubleInf()),
                Math.max(x.doubleSup(), y.doubleSup()),
                x.getDecoration().min(y.getDecoration()));
    }
}
