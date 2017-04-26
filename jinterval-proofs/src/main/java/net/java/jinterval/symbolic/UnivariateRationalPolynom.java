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
package net.java.jinterval.symbolic;

import java.util.Arrays;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * Univariate polynom with Rational coefficients
 */
public class UnivariateRationalPolynom {

    public static final UnivariateRationalPolynom ZERO = new UnivariateRationalPolynom(new Rational[0]);
    private final Rational[] coeff;

    private UnivariateRationalPolynom(Rational[] coeff) {
        this.coeff = coeff;
    }

    public int getOrder() {
        return coeff.length - 1;
    }

    public int getLowest() {
        int p;
        for (p = 0; p < coeff.length; p++) {
            if (coeff[p].signum() != 0) {
                break;
            }
        }
        return p;
    }

    public Rational getCoeff(int p) {
        return coeff[p];
    }

    public boolean isZero() {
        return coeff.length == 0;
    }

    public static UnivariateRationalPolynom valueOf(Rational... coeff) {
        Rational[] res = null;
        for (int i = coeff.length - 1; i >= 0; i--) {
            Rational c = coeff[i];
            if (c == null) {
                throw new NullPointerException();
            }
            if (res != null) {
                res[i] = c;
            } else if (c.signum() != 0) {
                res = new Rational[i + 1];
                res[i] = c;
            }
        }
        return res != null ? new UnivariateRationalPolynom(res) : ZERO;
    }

    public UnivariateRationalPolynom add(UnivariateRationalPolynom that) {
        Rational[] res = null;
        for (int i = Math.max(this.coeff.length, that.coeff.length) - 1; i >= 0; i--) {
            Rational xi = i < this.coeff.length ? this.coeff[i] : Rational.zero();
            Rational yi = i < that.coeff.length ? that.coeff[i] : Rational.zero();
            Rational sum = RationalOps.add(xi, yi);
            if (res != null) {
                res[i] = sum;
            } else if (sum.signum() != 0) {
                res = new Rational[i + 1];
                res[i] = sum;
            }
        }
        return res != null ? new UnivariateRationalPolynom(res) : ZERO;
    }

    public UnivariateRationalPolynom sub(UnivariateRationalPolynom that) {
        return add(that.mul(Rational.valueOf(-1)));
    }

    public UnivariateRationalPolynom mul(Rational c) {
        if (isZero() || c.signum() == 0) {
            return ZERO;
        }
        Rational[] res = new Rational[coeff.length];
        for (int i = 0; i < coeff.length; i++) {
            res[i] = RationalOps.mul(coeff[i], c);
        }
        return new UnivariateRationalPolynom(res);
    }

    public UnivariateRationalPolynom mul(UnivariateRationalPolynom that) {
        if (this.isZero() || that.isZero()) {
            return ZERO;
        }
        Rational[] res = new Rational[this.coeff.length + that.coeff.length - 1];
        for (int p = 0; p < res.length; p++) {
            Rational s = Rational.zero();
            for (int px = 0; px < this.coeff.length; px++) {
                int py = p - px;
                if (0 <= py && py < that.coeff.length) {
                    s = RationalOps.fma(this.coeff[px], that.coeff[py], s);
                }
            }
            res[p] = s;
        }
        return new UnivariateRationalPolynom(res);
    }

    public UnivariateRationalPolynom divideByPowX(int p) {
        if (getLowest() < p) {
            throw new IllegalArgumentException();
        } else if (p > coeff.length) {
            return ZERO;
        } else {
            return new UnivariateRationalPolynom(Arrays.copyOfRange(coeff, p, coeff.length));
        }
    }

    public SetInterval eval(SetIntervalContext ic, SetInterval x) {
        SetInterval s = ic.numsToInterval(0, 0);
        for (int p = coeff.length - 1; p >= 0; p--) {
            Rational c = coeff[p];
            s = ic.fma(x, s, ic.numsToInterval(c, c));
        }
        return s;
    }

    @Override
    public boolean equals(Object o) {
        return o instanceof UnivariateRationalPolynom
                && Arrays.equals(this.coeff, ((UnivariateRationalPolynom) o).coeff);
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 59 * hash + Arrays.deepHashCode(this.coeff);
        return hash;
    }

    @Override
    public String toString() {
        return toString("x");
    }

    public String toString(String varName) {
        if (isZero()) {
            return "0";
        }
        StringBuilder sb = new StringBuilder();
        for (int p = 0; p < coeff.length; p++) {
            Rational c = coeff[p];
            if (c.signum() == 0) {
                continue;
            }
            if (sb.length() != 0) {
                sb.append(' ');
            }
            if (c.signum() > 0 && p != 0) {
                sb.append('+');
            }
            sb.append(c);
            if (p == 0) {
                continue;
            }
            sb.append('*');
            sb.append(varName);
            if (p > 1) {
                sb.append('^');
                sb.append(p);
            }
        }
        return sb.toString();
    }

    public String toString(String varName, Rational scale, Rational scaleU) {
        if (isZero()) {
            return "0";
        }
        StringBuilder sb = new StringBuilder();
        for (int p = 0; p < coeff.length; p++) {
            Rational c = coeff[p];
            if (c.signum() == 0) {
                scale = RationalOps.mul(scale, scaleU);
                continue;
            }
            if (sb.length() != 0) {
                sb.append(' ');
            }
            if (c.signum() > 0 && p != 0) {
                sb.append('+');
            }
            sb.append(RationalOps.mul(c, scale));
            scale = RationalOps.mul(scale, scaleU);
            if (p == 0) {
                continue;
            }
            sb.append('*');
            sb.append(varName);
            if (p > 1) {
                sb.append('^');
                sb.append(p);
            }
        }
        return sb.toString();
    }

    void check() {
        for (Rational c : coeff) {
            assert c != null;
        }
        if (coeff.length > 0) {
            assert coeff[coeff.length - 1].signum() != 0;
        }
    }
}
