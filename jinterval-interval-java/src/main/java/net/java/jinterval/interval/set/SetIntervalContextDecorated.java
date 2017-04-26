/*
 * Copyright (c) 2017, JInterval Project.
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
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * Make Decorated context from bare context
 */
public class SetIntervalContextDecorated implements SetIntervalContext {

    private final SetIntervalContext bare;

    SetIntervalContextDecorated(SetIntervalContext bare) {
        this.bare = bare;
    }

    @Override
    public SetInterval hull(SetInterval x) {
        SetInterval r = bare.hull(x);
        Decoration dec = x.getDecoration();
        return SetIntervalOps.setDec(r, dec);
    }

    @Override
    public SetInterval empty() {
        SetInterval r = bare.empty();
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec);
    }

    @Override
    public SetInterval entire() {
        SetInterval r = bare.entire();
        Decoration localDec = Decoration.DAC;
        return SetIntervalOps.setDec(r, localDec);
    }

    @Override
    public SetInterval nai() {
        SetInterval r = bare.empty();
        Decoration localDec = Decoration.ILL;
        return SetIntervalOps.setDec(r, localDec);
    }

    @Override
    public SetInterval numsToInterval(ExtendedRational l, ExtendedRational u) {
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.numsToInterval(l, u);
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            puoe = e;
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            throw e;
        }
        assert !r.isEmpty();
        Decoration localDec = Decoration.COM;
        SetInterval dr = SetIntervalOps.setDec(r, localDec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    @Override
    public SetInterval numsToInterval(double l, double u) {
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.numsToInterval(l, u);
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            puoe = e;
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            throw e;
        }
        assert !r.isEmpty();
        Decoration localDec = Decoration.COM;
        SetInterval dr = SetIntervalOps.setDec(r, localDec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    @Override
    public SetInterval numsToInterval(float l, float u) {
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.numsToInterval(l, u);
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            puoe = e;
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            throw e;
        }
        assert !r.isEmpty();
        Decoration localDec = Decoration.COM;
        SetInterval dr = SetIntervalOps.setDec(r, localDec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    @Override
    public SetInterval numsDecToInterval(ExtendedRational l, ExtendedRational u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        switch (decoration) {
            case ILL:
                throw new UndefinedOperationException();
            case COM:
                if (!(l.isFinite() && u.isFinite())) {
                    throw new UndefinedOperationException();
                }
                break;
        }
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.numsToInterval(l, u);
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            puoe = e;
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            throw e;
        }
        assert !r.isEmpty();
        Decoration localDec = decoration;
        SetInterval dr = SetIntervalOps.setDec(r, localDec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    @Override
    public SetInterval numsDecToInterval(double l, double u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        switch (decoration) {
            case ILL:
                throw new UndefinedOperationException();
            case COM:
                if (Double.isInfinite(l) || Double.isInfinite(u)) {
                    throw new UndefinedOperationException();
                }
                break;
        }
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.numsToInterval(l, u);
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            puoe = e;
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            throw e;
        }
        assert !r.isEmpty();
        Decoration localDec = decoration;
        SetInterval dr = SetIntervalOps.setDec(r, localDec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    @Override
    public SetInterval numsDecToInterval(float l, float u, Decoration decoration) {
        if (decoration == null) {
            throw new InvalidOperandException();
        }
        switch (decoration) {
            case ILL:
                throw new UndefinedOperationException();
            case COM:
                if (Float.isInfinite(l) || Float.isInfinite(u)) {
                    throw new UndefinedOperationException();
                }
                break;
        }
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.numsToInterval(l, u);
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            puoe = e;
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            throw e;
        }
        assert !r.isEmpty();
        Decoration localDec = decoration;
        SetInterval dr = SetIntervalOps.setDec(r, localDec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    @Override
    public SetInterval textToInterval(String s) {
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.textToInterval(s);
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            puoe = e;
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            throw e;
        }
        Decoration localDec = Decoration.COM;
        SetInterval dr = SetIntervalOps.setDec(r, localDec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    private static boolean isBoundedLiteral(String s) {
        if (s.length() >= 2 && s.charAt(0) == '['
                && s.charAt(s.length() - 1) == ']') {
            s = s.substring(1, s.length() - 1);
            int indexC = s.indexOf(',');
            if (indexC >= 0) {
                String infS = s.substring(0, indexC).trim();
                String supS = s.substring(indexC + 1).trim();
                if (infS.isEmpty() || supS.isEmpty() || infS.contains("INF") || supS.contains("INF")) {
                    // Text interval has infinity bound
                    return false;
                }
            } else if (s.contains("ENTIRE")) {
                return false;
            }
        } else if (s.contains("??")) {
            return false;
        }
        return true;
    }

    private static boolean isNaI(String s) {
        if (s.length() >= 2 && s.charAt(0) == '['
                && s.charAt(s.length() - 1) == ']') {
            s = s.substring(1, s.length() - 1).trim();
            if (s.equals("NAI")) {
                return true;
            }
        }
        return false;
    }

    @Override
    public SetInterval textToDecoratedInterval(String s) {
        Decoration dec = null;
        String ss = s.toUpperCase();
        int indexD = ss.indexOf('_');
        if (indexD >= 0) {
            try {
                dec = Decoration.valueOf(ss.substring(indexD + 1).toUpperCase());
                if (dec == Decoration.ILL) {
                    throw new UndefinedOperationException();
                }
            } catch (IllegalArgumentException e) {
                throw new UndefinedOperationException(e);
            }
            ss = ss.substring(0, indexD);
        }
        SetInterval r;
        PossiblyUndefinedOperationException puoe = null;
        try {
            r = bare.textToInterval(ss);
        } catch (UndefinedOperationException e) {
            assert e.getValue().isNaI();
            if (dec == null && isNaI(ss)) {
                return e.getValue();
            } else {
                throw e;
            }
        } catch (PossiblyUndefinedOperationException e) {
            r = e.getValue();
            assert !r.isEmpty();
            puoe = e;
        }
        if (r.isEmpty()) {
            if (dec != null && dec != Decoration.TRV) {
                throw new UndefinedOperationException();
            }
            dec = Decoration.TRV;
        }
        if (dec == Decoration.COM && !r.isCommonInterval() && !isBoundedLiteral(ss)) {
            throw new UndefinedOperationException();
        }
        if (dec == null) {
            dec = Decoration.COM;
        }
        SetInterval dr = SetIntervalOps.setDec(r, dec);
        if (puoe == null) {
            return dr;
        } else {
            throw new PossiblyUndefinedOperationException(dr, puoe);
        }
    }

    @Override
    public SetInterval pi() {
        SetInterval r = bare.pi();
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec);
    }

    @Override
    public SetInterval euler() {
        SetInterval r = bare.euler();
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec);
    }

    @Override
    public SetInterval neg(SetInterval x) {
        SetInterval r = bare.neg(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval add(SetInterval x, SetInterval y) {
        SetInterval r = bare.add(x, y);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval sub(SetInterval x, SetInterval y) {
        SetInterval r = bare.sub(x, y);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval mul(SetInterval x, SetInterval y) {
        SetInterval r = bare.mul(x, y);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval div(SetInterval x, SetInterval y) {
        SetInterval r = bare.div(x, y);
        Decoration localDec = y.isMember(0) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval recip(SetInterval x) {
        SetInterval r = bare.recip(x);
        Decoration localDec = x.isMember(0) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval sqr(SetInterval x) {
        SetInterval r = bare.sqr(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval sqrt(SetInterval x) {
        SetInterval r = bare.sqrt(x);
        Decoration localDec = x.inf().signum() < 0 ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval fma(SetInterval x, SetInterval y, SetInterval z) {
        SetInterval r = bare.fma(x, y, z);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()).min(z.getDecoration()));
    }

    @Override
    public SetInterval pown(SetInterval x, BigInteger p) {
        SetInterval r = bare.pown(x, p);
        Decoration localDec = p.signum() < 0 && x.isMember(0) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval pown(SetInterval x, long p) {
        SetInterval r = bare.pown(x, p);
        Decoration localDec = p < 0 && x.isMember(0) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval pown(SetInterval x, int p) {
        SetInterval r = bare.pown(x, p);
        Decoration localDec = p < 0 && x.isMember(0) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval pow(SetInterval x, SetInterval y) {
        SetInterval r = bare.pow(x, y);
        Decoration localDec = x.inf().signum() < 0 || x.isMember(0) && y.inf().signum() <= 0 ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval exp(SetInterval x) {
        SetInterval r = bare.exp(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval exp2(SetInterval x) {
        SetInterval r = bare.exp2(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval exp10(SetInterval x) {
        SetInterval r = bare.exp10(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval log(SetInterval x) {
        SetInterval r = bare.log(x);
        Decoration localDec = x.inf().signum() <= 0 ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval log2(SetInterval x) {
        SetInterval r = bare.log2(x);
        Decoration localDec = x.inf().signum() <= 0 ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval log10(SetInterval x) {
        SetInterval r = bare.log10(x);
        Decoration localDec = x.inf().signum() <= 0 ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval sin(SetInterval x) {
        SetInterval r = bare.sin(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval cos(SetInterval x) {
        SetInterval r = bare.cos(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    private static boolean inTanDomain(SetInterval x) {
        if (x.doubleWid() >= 3.2) {
            return false;
        }
        if (x.isEmpty()) {
            return true;
        }
        BigInteger ki = RationalOps.piHalfFloor((Rational) x.inf());
        BigInteger ks = RationalOps.piHalfFloor((Rational) x.sup());
        return ki.subtract(BigInteger.ONE).shiftRight(1)
                .equals(ks.subtract(BigInteger.ONE).shiftRight(1));
    }

    @Override
    public SetInterval tan(SetInterval x) {
        SetInterval r = bare.tan(x);
        Decoration localDec = r.isEntire() && !inTanDomain(x) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval asin(SetInterval x) {
        SetInterval r = bare.asin(x);
        Decoration localDec = !x.subset(SetIntervalOps.nums2(-1, 1)) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval acos(SetInterval x) {
        SetInterval r = bare.acos(x);
        Decoration localDec = !x.subset(SetIntervalOps.nums2(-1, 1)) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval atan(SetInterval x) {
        SetInterval r = bare.atan(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval atan2(SetInterval y, SetInterval x) {
        SetInterval r = bare.atan2(y, x);
        Decoration localDec = !y.isMember(0) || x.inf().signum() > 0 ? Decoration.COM
                : x.sup().signum() >= 0 ? Decoration.TRV
                        : y.inf().signum() < 0 ? Decoration.DEF
                                : Decoration.DAC;
        return SetIntervalOps.setDec(r, localDec.min(y.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval sinh(SetInterval x) {
        SetInterval r = bare.sinh(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval cosh(SetInterval x) {
        SetInterval r = bare.cosh(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval tanh(SetInterval x) {
        SetInterval r = bare.tanh(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval asinh(SetInterval x) {
        SetInterval r = bare.asinh(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval acosh(SetInterval x) {
        SetInterval r = bare.acosh(x);
        Decoration localDec = x.inf().lt(Rational.one()) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval atanh(SetInterval x) {
        SetInterval r = bare.atanh(x);
        Decoration localDec = x.inf().le(Rational.valueOf(-1)) || x.sup().ge(Rational.one()) ? Decoration.TRV : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval sign(SetInterval x) {
        SetInterval r = bare.sign(x);
        Decoration localDec = !x.isMember(0) ? Decoration.COM
                : !x.isSingleton() ? Decoration.DEF
                        : Decoration.DAC;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval ceil(SetInterval x) {
        SetInterval r = bare.ceil(x);
        Decoration localDec = !r.isSingleton() ? Decoration.DEF
                : x.sup().isInteger() ? Decoration.DAC
                        : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval floor(SetInterval x) {
        SetInterval r = bare.floor(x);
        Decoration localDec = !r.isSingleton() ? Decoration.DEF
                : x.inf().isInteger() ? Decoration.DAC
                        : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval trunc(SetInterval x) {
        SetInterval r = bare.trunc(x);
        Decoration localDec = !r.isSingleton() ? Decoration.DEF
                : x.inf().signum() > 0 & x.inf().isInteger()
                || x.sup().signum() < 0 && x.sup().isInteger() ? Decoration.DAC
                        : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval roundTiesToEven(SetInterval x) {
        SetInterval r = bare.roundTiesToEven(x);
        Decoration localDec = !r.isSingleton() ? Decoration.DEF
                : ExtendedRationalOps.add(x.inf(), Utils.RAT_HALF).isInteger()
                || ExtendedRationalOps.sub(x.sup(), Utils.RAT_HALF).isInteger() ? Decoration.DAC
                : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval roundTiesToAway(SetInterval x) {
        SetInterval r = bare.roundTiesToAway(x);
        Decoration localDec = !r.isSingleton() ? Decoration.DEF
                : ExtendedRationalOps.add(x.inf(), Utils.RAT_HALF).isInteger()
                || ExtendedRationalOps.sub(x.sup(), Utils.RAT_HALF).isInteger() ? Decoration.DAC
                : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval abs(SetInterval x) {
        SetInterval r = bare.abs(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2) {
        SetInterval r = bare.min(x1, x2);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x1.getDecoration()).min(x2.getDecoration()));
    }

    private static Decoration minDec(SetInterval x1, SetInterval x2, SetInterval... xn) {
        Decoration dec = x1.getDecoration().min(x2.getDecoration());
        for (SetInterval x : xn) {
            dec = dec.min(x.getDecoration());
        }
        return dec;
    }

    @Override
    public SetInterval min(SetInterval x1, SetInterval x2, SetInterval... xn) {
        SetInterval r = bare.min(x1, x2, xn);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(minDec(x1, x2, xn)));
    }

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2) {
        SetInterval r = bare.max(x1, x2);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x1.getDecoration()).min(x2.getDecoration()));
    }

    @Override
    public SetInterval max(SetInterval x1, SetInterval x2, SetInterval... xn) {
        SetInterval r = bare.max(x1, x2, xn);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(minDec(x1, x2, xn)));
    }

    @Override
    public SetInterval sqrRev(SetInterval c, SetInterval x) {
        SetInterval r = bare.sqrRev(c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval absRev(SetInterval c, SetInterval x) {
        SetInterval r = bare.absRev(c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, BigInteger p) {
        SetInterval r = bare.pownRev(c, x, p);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, long p) {
        SetInterval r = bare.pownRev(c, x, p);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval pownRev(SetInterval c, SetInterval x, int p) {
        SetInterval r = bare.pownRev(c, x, p);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval sinRev(SetInterval c, SetInterval x) {
        SetInterval r = bare.sinRev(c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval cosRev(SetInterval c, SetInterval x) {
        SetInterval r = bare.cosRev(c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval tanRev(SetInterval c, SetInterval x) {
        SetInterval r = bare.tanRev(c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval coshRev(SetInterval c, SetInterval x) {
        SetInterval r = bare.coshRev(c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval mulRev(SetInterval b, SetInterval c, SetInterval x) {
        SetInterval r = bare.mulRev(b, c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(b.getDecoration()).min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval powRev1(SetInterval b, SetInterval c, SetInterval x) {
        SetInterval r = bare.powRev1(b, c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(b.getDecoration()).min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval powRev2(SetInterval a, SetInterval c, SetInterval x) {
        SetInterval r = bare.powRev2(a, c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(a.getDecoration()).min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval atan2Rev1(SetInterval b, SetInterval c, SetInterval x) {
        SetInterval r = bare.atan2Rev1(b, c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(b.getDecoration()).min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public SetInterval atan2Rev2(SetInterval a, SetInterval c, SetInterval x) {
        SetInterval r = bare.atan2Rev2(a, c, x);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(a.getDecoration()).min(c.getDecoration()).min(x.getDecoration()));
    }

    @Override
    public MulRevPair mulRevToPair(SetInterval b, SetInterval c) {
        MulRevPair r2 = bare.mulRevToPair(b, c);
        Decoration localDec1 = b.isMember(0) ? Decoration.TRV : Decoration.COM;
        Decoration localDec2 = Decoration.TRV;
        return new MulRevPair(
                SetIntervalOps.setDec(r2.first, localDec1.min(b.getDecoration()).min(c.getDecoration())),
                SetIntervalOps.setDec(r2.second, localDec2.min(b.getDecoration()).min(c.getDecoration())));

    }

    @Override
    public SetInterval cancelMinus(SetInterval x, SetInterval y) {
        SetInterval r = bare.cancelMinus(x, y);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval cancelPlus(SetInterval x, SetInterval y) {
        SetInterval r = bare.cancelPlus(x, y);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval intersection(SetInterval x, SetInterval y) {
        SetInterval r = bare.intersection(x, y);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval convexHull(SetInterval x, SetInterval y) {
        SetInterval r = bare.convexHull(x, y);
        Decoration localDec = Decoration.TRV;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval setDec(SetInterval x, Decoration dec) {
        return SetIntervalOps.setDec(bare.hull(x), dec);
    }

    @Override
    public SetInterval rootn(SetInterval x, BigInteger q) {
        SetInterval r = bare.rootn(x, q);
        Decoration localDec = !q.testBit(0) && x.inf().signum() < 0
                || q.signum() < 0 && x.isMember(0) ? Decoration.TRV
                : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval rootn(SetInterval x, long q) {
        SetInterval r = bare.rootn(x, q);
        Decoration localDec = (q & 1) == 0 && x.inf().signum() < 0
                || q < 0 && x.isMember(0) ? Decoration.TRV
                : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval rootn(SetInterval x, int q) {
        SetInterval r = bare.rootn(x, q);
        Decoration localDec = (q & 1) == 0 && x.inf().signum() < 0
                || q < 0 && x.isMember(0) ? Decoration.TRV
                : Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

    @Override
    public SetInterval hypot(SetInterval x, SetInterval y) {
        SetInterval r = bare.hypot(x, y);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()).min(y.getDecoration()));
    }

    @Override
    public SetInterval newDec(SetInterval x) {
        SetInterval r = bare.hull(x);
        Decoration localDec = Decoration.COM;
        return SetIntervalOps.setDec(r, localDec.min(x.getDecoration()));
    }

}
