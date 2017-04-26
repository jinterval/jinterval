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
package net.java.jinterval.ils;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.linear.Array2DRowRationalMatrix;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.rational.ExtendedRational;
import org.apache.commons.math3.exception.DimensionMismatchException;

/**
 * Dummy interval matrix in Commons Math style
 *
 * @author sz
 */
public class IntervalMatrix {

    final int m;
    final int n;
    private final SetInterval[][] a;

    public IntervalMatrix(SetInterval[][] array) {
        m = array.length;
        n = array[0].length;
        a = new SetInterval[m][n];
        for (int i = 0; i < m; i++) {
            if (array[i].length != n) {
                throw new IllegalArgumentException();
            }
            for (int j = 0; j < n; j++) {
                a[i][j] = array[i][j];
            }
        }
    }

    public IntervalMatrix(IntervalVector... rows) {
        m = rows[0].getDimension();
        n = rows.length;
        a = new SetInterval[m][n];
        for (int j = 0; j < n; j++) {
            if (rows[j].getDimension() != m) {
                throw new IllegalArgumentException();
            }
            for (int i = 0; i < m; i++) {
                a[i][j] = rows[j].getEntry(i);
            }
        }
    }

    public IntervalMatrix(int rows, int cols) {
        m = rows;
        n = cols;
        a = new SetInterval[m][n];
    }

    public IntervalMatrix(int rows, int cols, SetInterval value) {
        m = rows;
        n = cols;
        a = new SetInterval[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = value;
            }
        }
    }

    public IntervalMatrix(RationalMatrix inf, RationalMatrix sup) {
        this(inf.getRowDimension(), inf.getColumnDimension());
        if (inf.getRowDimension() != sup.getRowDimension() || inf.getColumnDimension() != sup.getColumnDimension()) {
            throw new IllegalArgumentException();
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = SetIntervalOps.nums2(inf.getEntry(i, j), sup.getEntry(i, j), Decoration.COM);
            }
        }
    }

    public IntervalMatrix(RationalMatrix A) {
        this(A, A);
    }

    public int getRowDimension() {
        return m;
    }

    public int getColumnDimension() {
        return n;
    }

    public SetInterval getEntry(int i, int j) {
        return a[i][j];
    }

    public IntervalVector getRow(int i) {
        IntervalVector row = new IntervalVector(this.getColumnDimension());

        for (int j = 0; j < this.getColumnDimension(); j++) {
            row.setEntry(j, this.getEntry(i, j));
        }

        return row;
    }

    public IntervalVector getColumn(int j) {
        IntervalVector column = new IntervalVector(this.getRowDimension());

        for (int i = 0; i < this.getRowDimension(); i++) {
            column.setEntry(i, this.getEntry(i, j));
        }

        return column;
    }

    public void setEntry(int i, int j, SetInterval value) {
        a[i][j] = value;
    }

    public RationalMatrix mid() {
        int rows = this.getRowDimension(),
                cols = this.getColumnDimension();

        RationalMatrix rm = new Array2DRowRationalMatrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rm.setEntry(i, j, this.getEntry(i, j).mid());
            }
        }
        return rm;
    }

    public RationalMatrix rad() {
        int rows = this.getRowDimension(),
                cols = this.getColumnDimension();

        RationalMatrix rm = new Array2DRowRationalMatrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rm.setEntry(i, j, this.getEntry(i, j).rad());
            }
        }
        return rm;
    }

    public RationalMatrix mig() {
        int rows = this.getRowDimension(),
                cols = this.getColumnDimension();

        RationalMatrix rm = new Array2DRowRationalMatrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rm.setEntry(i, j, this.getEntry(i, j).mig());
            }
        }
        return rm;
    }

    public RationalMatrix mag() {
        int rows = this.getRowDimension(),
                cols = this.getColumnDimension();

        RationalMatrix rm = new Array2DRowRationalMatrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                rm.setEntry(i, j, this.getEntry(i, j).mag());
            }
        }
        return rm;
    }

    public IntervalMatrix add(SetIntervalContext ctx, IntervalMatrix b)
            throws DimensionMismatchException {
        int arows = this.getRowDimension(),
                acols = this.getColumnDimension(),
                brows = b.getRowDimension(),
                bcols = b.getColumnDimension();

        if (arows != brows || acols != bcols) {
            throw new DimensionMismatchException(acols, bcols);
        }

        IntervalMatrix c = new IntervalMatrix(getRowDimension(), getColumnDimension());
        for (int i = 0; i < arows; i++) {
            for (int j = 0; j < acols; j++) {
                c.setEntry(i, j, ctx.add(this.getEntry(i, j), b.getEntry(i, j)));
            }
        }

        return c;
    }

    public IntervalMatrix subtract(SetIntervalContext ctx, IntervalMatrix b)
            throws DimensionMismatchException {
        int arows = this.getRowDimension(),
                acols = this.getColumnDimension(),
                brows = b.getRowDimension(),
                bcols = b.getColumnDimension();

        if (arows != brows) {
            throw new DimensionMismatchException(arows, brows);
        }
        if (acols != bcols) {
            throw new DimensionMismatchException(acols, bcols);
        }

        IntervalMatrix c = new IntervalMatrix(getRowDimension(), getColumnDimension());

        for (int i = 0; i < arows; i++) {
            for (int j = 0; j < acols; j++) {
                c.setEntry(i, j, ctx.sub(this.getEntry(i, j), b.getEntry(i, j)));
            }
        }

        return c;
    }

    public IntervalVector operate(SetIntervalContext ctx, IntervalVector v) {
        IntervalMatrix mv = new IntervalMatrix(v.getDimension(), 1);

        for (int i = 0; i < v.getDimension(); i++) {
            mv.setEntry(i, 0, v.getEntry(i));
        }

        IntervalMatrix mAv = this.multiply(ctx, mv);
        IntervalVector Av = new IntervalVector(mAv.getRowDimension());

        for (int i = 0; i < v.getDimension(); i++) {
            Av.setEntry(i, mAv.getEntry(i, 0));
        }

        return Av;
    }

    public IntervalMatrix multiply(SetIntervalContext ctx, IntervalMatrix b)
            throws DimensionMismatchException {
        int arows = this.getRowDimension(),
                acols = this.getColumnDimension(),
                brows = b.getRowDimension(),
                bcols = b.getColumnDimension();

        if (acols != brows) {
            throw new DimensionMismatchException(acols, bcols);
        }
        int crows = arows,
                ccols = bcols;

        SetInterval[][] c = new SetInterval[crows][ccols];
        for (int i = 0; i < crows; i++) {
            for (int j = 0; j < ccols; j++) {
                SetInterval sum = ctx.numsToInterval(0, 0);
                for (int k = 0; k < acols; k++) {
                    sum = ctx.add(sum, ctx.mul(this.getEntry(i, k), b.getEntry(k, j)));
                }
                c[i][j] = sum;
            }
        }
        return new IntervalMatrix(c);
    }

    public RationalMatrix abs() { //max(abs(inf),abs(sup))
        return mag();
//        int rows = this.getRowDimension(),
//                cols = this.getColumnDimension();
//
//        RationalMatrix rm = new Array2DRowRationalMatrix(rows, cols);
//
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//                StandardInterval Aij = this.getEntry(i, j);
//                double absinf = Math.abs(Aij.doubleInf());
//                double abssup = Math.abs(Aij.doubleSup());
//                rm.setEntry(i, j, (absinf > abssup) ? absinf : abssup);
//            }
//        }
//        return rm;
    }

    public IntervalVector diag() {
        int n = Math.min(getRowDimension(), getColumnDimension());
        IntervalVector d = new IntervalVector(n);
        for (int i = 0; i < n; i++) {
            d.setEntry(i, getEntry(i, i));
        }
        return d;
    }

    public IntervalMatrix invGauss(SetIntervalContext ctx) {
        if (m != n) {
            throw new IllegalArgumentException();
        }
        SetInterval zero = ctx.numsToInterval(0, 0);
        SetInterval one = ctx.numsToInterval(1, 1);
        SetInterval[][] ac = new SetInterval[n][n];
        SetInterval[][] ai = new SetInterval[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                SetInterval v = a[i][j];
                ac[i][j] = ctx.hull(v);
                ai[i][j] = i != j ? zero : one;
            }
        }
        for (int i = 0; i < n; i++) {
            SetInterval aii = ac[i][i];
            ac[i][i] = one;
            for (int j = i + 1; j < n; j++) {
                ac[i][j] = ctx.div(ac[i][j], aii);
            }
            for (int j = 0; j <= i; j++) {
                ai[i][j] = ctx.div(ai[i][j], aii);
            }
            for (int k = i + 1; k < n; k++) {
                SetInterval aki = ac[k][i];
                ac[k][i] = zero;
                for (int j = i + 1; j < n; j++) {
                    ac[k][j] = ctx.sub(ac[k][j], ctx.mul(aki, ac[i][j]));
                }
                for (int j = 0; j <= i; j++) {
                    ai[k][j] = ctx.sub(ai[k][j], ctx.mul(aki, ai[i][j]));
                }
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            for (int k = i + 1; k < n; k++) {
                SetInterval aik = ac[i][k];
                ac[i][k] = zero;
                for (int j = 0; j < n; j++) {
                    ai[i][j] = ctx.sub(ai[i][j], ctx.mul(aik, ai[k][j]));
                }
            }
        }
        return new IntervalMatrix(ai);
    }

    @Override
    public String toString() {
        String rets = "";
        String s = "";
        rets += "/\n";
        for (SetInterval[] i : a) {
            s = "| ";
            for (SetInterval j : i) {
                s += " " + j;
            }
            rets += s + " |\n";
        }
        rets += "\\\n";
        return rets;
    }
}
