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
package net.java.jinterval.linear;

import java.util.Arrays;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import org.apache.commons.math3.exception.DimensionMismatchException;

/**
 *
 */
public class ArrayRationalVector implements RationalVector {

    private final ExtendedRational[] a;

    public ArrayRationalVector(int n) {
        this(n, Rational.zero());
    }

    public ArrayRationalVector(int n, ExtendedRational v) {
        a = new ExtendedRational[n];
        if (v == null) {
            throw new NullPointerException();
        }
        Arrays.fill(a, v);
    }

    public int getDimension() {
        return a.length;
    }

    public ExtendedRational getEntry(int i) {
        return a[i];
    }

    public void setEntry(int i, ExtendedRational v) {
        if (v == null) {
            throw new NullPointerException();
        }
        a[i] = v;
    }

    public RationalVector getSubVector(int from, int len) {
        ArrayRationalVector sub = new ArrayRationalVector(len);
        for (int i = 0; i < len; i++) {
            sub.a[i] = a[from + i];
        }
        return sub;
    }

    public void setSubVector(int from, RationalVector v) {
        for (int i = 0; i < v.getDimension(); i++) {
            a[from + i] = v.getEntry(i);
        }
    }

    public RationalVector copy() {
        return getSubVector(0, getDimension());
    }

    public ExtendedRational getMinValue() {
        ExtendedRational r = ExtendedRational.POSITIVE_INFINITY;
        for (ExtendedRational v : a) {
            r = ExtendedRationalOps.min(r, v);
        }
        return r;
    }

    public ExtendedRational getL1Norm(ExtendedRationalContext ctx) {
        ExtendedRational r = Rational.zero();
        for (ExtendedRational v : a) {
            r = ctx.add(r, ExtendedRationalOps.abs(v));
        }
        return r;
    }

    public RationalVector subtract(ExtendedRationalContext ctx, RationalVector that) {
        int n = that.getDimension();
        if (a.length != n) {
            throw new DimensionMismatchException(a.length, n);
        }
        ArrayRationalVector r = new ArrayRationalVector(n);
        for (int i = 0; i < n; i++) {
            r.setEntry(i, ctx.sub(a[i], that.getEntry(i)));
        }
        return r;
    }

    public RationalVector mapMultiply(ExtendedRationalContext ctx, ExtendedRational v) {
        ArrayRationalVector r = new ArrayRationalVector(getDimension());
        for (int i = 0; i < getDimension(); i++) {
            r.setEntry(i, ctx.mul(a[i], v));
        }
        return r;
    }

    public RationalVector mapDivide(ExtendedRationalContext ctx, ExtendedRational v) {
        ArrayRationalVector r = new ArrayRationalVector(getDimension());
        for (int i = 0; i < getDimension(); i++) {
            r.setEntry(i, ctx.div(a[i], v));
        }
        return r;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof RationalVector) {
            RationalVector that = (RationalVector) o;
            if (this.getDimension() == that.getDimension()) {
                for (int i = 0; i < getDimension(); i++) {
                    if (!this.getEntry(i).equals(that.getEntry(i))) {
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 29 * hash + Arrays.deepHashCode(this.a);
        return hash;
    }

    @Override
    public String toString() {
        String rets = "";
        String s = "";
        rets += "/\n";
        for (ExtendedRational i : a) {
            rets += "|  " + i.doubleValue() + " |\n";
        }
        rets += "\\\n";
        return rets;
    }
}
