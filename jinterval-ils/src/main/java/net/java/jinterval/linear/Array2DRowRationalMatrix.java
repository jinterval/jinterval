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

/**
 *
 */
public class Array2DRowRationalMatrix implements RationalMatrix {

    private final int m;
    private final int n;
    private final ExtendedRational[][] a;

    public Array2DRowRationalMatrix(int m, int n) {
        this(m, n, Rational.zero());
    }

    public Array2DRowRationalMatrix(int m, int n, ExtendedRational v) {
        this.m = m;
        this.n = n;
        a = new ExtendedRational[m][n];
        for (ExtendedRational[] row : a) {
            Arrays.fill(row, v);
        }
    }

    public int getRowDimension() {
        return m;
    }

    public int getColumnDimension() {
        return n;
    }

    public ExtendedRational getEntry(int i, int j) {
        return a[i][j];
    }

    public void setEntry(int i, int j, ExtendedRational v) {
        if (v == null) {
            throw new NullPointerException();
        }
        a[i][j] = v;
    }

    public RationalVector diag() {
        int n = Math.min(getRowDimension(), getColumnDimension());
        RationalVector d = new ArrayRationalVector(n);
        for (int i = 0; i < n; i++) {
            d.setEntry(i, getEntry(i, i));
        }
        return d;
    }

    public RationalVector getRowVector(int i) {
        RationalVector row = new ArrayRationalVector(n);
        for (int j = 0; j < n; j++) {
            row.setEntry(j, a[i][j]);
        }
        return row;
    }

    public void setRowVector(int i, RationalVector v) {
        if (v.getDimension() != n) {
            throw new ArithmeticException();
        }
        for (int j = 0; j < n; j++) {
            a[i][j] = v.getEntry(j);
        }
    }

    public RationalVector getColumnVector(int j) {
        RationalVector col = new ArrayRationalVector(m);
        for (int i = 0; i < m; i++) {
            col.setEntry(i, a[i][j]);
        }
        return col;
    }

    public RationalMatrix getSubMatrix(int startRow, int endRow, int startColumn, int endColumn) {
        if (startRow > endRow || startColumn > endColumn) {
            throw new IllegalArgumentException();
        }
        RationalMatrix r = new Array2DRowRationalMatrix(endRow - startRow + 1, endColumn - startColumn + 1);
        for (int i = startRow; i <= endRow; i++) {
            for (int j = startColumn; j <= endColumn; j++) {
                r.setEntry(i - startRow, j - startColumn, a[i][j]);
            }
        }
        return r;
    }

    public ExtendedRational getMinValue() {
        ExtendedRational r = ExtendedRational.POSITIVE_INFINITY;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r = ExtendedRationalOps.min(r, a[i][j]);
            }
        }
        return r;
    }

    public ExtendedRational getMaxValue() {
        ExtendedRational r = ExtendedRational.NEGATIVE_INFINITY;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r = ExtendedRationalOps.max(r, a[i][j]);
            }
        }
        return r;
    }

    public RationalMatrix add(ExtendedRationalContext ctx, RationalMatrix that) {
        if (that.getColumnDimension() != m || that.getRowDimension() != n) {
            throw new ArithmeticException();
        }
        Array2DRowRationalMatrix r = new Array2DRowRationalMatrix(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r.setEntry(i, j, ctx.add(a[i][j], that.getEntry(i, j)));
            }
        }
        return r;
    }

    public RationalMatrix subtract(ExtendedRationalContext ctx, RationalMatrix that) {
        if (that.getColumnDimension() != m || that.getRowDimension() != n) {
            throw new ArithmeticException();
        }
        Array2DRowRationalMatrix r = new Array2DRowRationalMatrix(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r.setEntry(i, j, ctx.sub(a[i][j], that.getEntry(i, j)));
            }
        }
        return r;
    }

    public RationalMatrix multiply(ExtendedRationalContext ctx, RationalMatrix that) {
        if (that.getRowDimension() != n) {
            throw new ArithmeticException();
        }
        Array2DRowRationalMatrix r = new Array2DRowRationalMatrix(m, that.getColumnDimension());
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < that.getColumnDimension(); j++) {
                ExtendedRational s = Rational.zero();
                for (int k = 0; k < n; k++) {
                    s = ctx.add(s, ctx.mul(a[i][k], that.getEntry(k, j)));
                }
                r.a[i][j] = s;
            }
        }
        return r;
    }

    public RationalVector multiply(ExtendedRationalContext ctx, RationalVector that) {
        if (that.getDimension() != n) {
            throw new ArithmeticException();
        }
        ArrayRationalVector r = new ArrayRationalVector(m);
        for (int i = 0; i < m; i++) {
            ExtendedRational s = Rational.zero();
            for (int k = 0; k < n; k++) {
                s = ctx.add(s, ctx.mul(a[i][k], that.getEntry(k)));
            }
            r.setEntry(i, s);
        }
        return r;
    }

    public RationalMatrix scalarMultiply(ExtendedRationalContext ctx, ExtendedRational v) {
        Array2DRowRationalMatrix r = new Array2DRowRationalMatrix(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r.a[i][j] = ctx.mul(a[i][j], v);
            }
        }
        return r;
    }

    public RationalMatrix copy() {
        Array2DRowRationalMatrix r = new Array2DRowRationalMatrix(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r.a[i][j] = a[i][j];
            }
        }
        return r;
    }

    @Override
    public String toString() {
        String rets = "";
        String s = "";
        rets += "/\n";
        for (ExtendedRational[] i : a) {
            s = "| ";
            for (ExtendedRational j : i) {
                s += " " + j.doubleValue();
            }
            rets += s + " |\n";
        }
        rets += "\\\n";
        return rets;
    }
}
