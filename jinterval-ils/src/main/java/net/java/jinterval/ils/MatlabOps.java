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
import net.java.jinterval.linear.*;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.ExtendedRationalContext;

/**
 *
 */
public class MatlabOps {

    public static int dim(IntervalMatrix A) {
        int m = A.getColumnDimension();
        int n = A.getRowDimension();
        if (m != n) {
            throw new IllegalArgumentException();
        }
        return n;
    }

    public static IntervalVector diag(IntervalMatrix A) {
        return A.diag();
    }

    public static IntervalMatrix add(SetIntervalContext ctx, IntervalMatrix A, IntervalMatrix B) {
        return A.add(ctx, B);
    }

    public static IntervalMatrix sub(SetIntervalContext ctx, IntervalMatrix A, IntervalMatrix B) {
        return A.subtract(ctx, B);
    }

    public static IntervalMatrix mul(SetIntervalContext ctx, IntervalMatrix A, IntervalMatrix B) {
        return A.multiply(ctx, B);
    }

    public static IntervalVector add(SetIntervalContext ctx, IntervalVector a, IntervalVector b) {
        if (a.getDimension() != b.getDimension()) {
            throw new IllegalArgumentException();
        }
        IntervalVector r = new IntervalVector(a.getDimension());
        for (int i = 0; i < a.getDimension(); i++) {
            r.setEntry(i, ctx.add(a.getEntry(i), b.getEntry(i)));
        }
        return r;
    }

    public static IntervalVector div(SetIntervalContext ctx, IntervalVector a, IntervalVector b) {
        if (a.getDimension() != b.getDimension()) {
            throw new IllegalArgumentException();
        }
        IntervalVector r = new IntervalVector(a.getDimension());
        for (int i = 0; i < a.getDimension(); i++) {
            r.setEntry(i, ctx.div(a.getEntry(i), b.getEntry(i)));
        }
        return r;
    }

    public static RationalVector diag(RationalMatrix A) {
        return A.diag();
    }

    public static RationalMatrix compmat(IntervalMatrix A) {
        int n = dim(A);
        RationalMatrix C = new Array2DRowRationalMatrix(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                SetInterval Aij = A.getEntry(i, j);
                if (i == j) {
                    C.setEntry(i, j, Aij.mig()); // C(i,j) = mig(A(i,j))
                } else {
                    C.setEntry(i, j, ExtendedRationalOps.neg(Aij.mag())); // C(i,j) = -mag(A(i,j))
                }
            }
        }
        return C;
    }

    public IntervalVector midrad(Rational mid, RationalVector rad) {
        IntervalVector r = new IntervalVector(rad.getDimension());
        for (int i = 0; i < rad.getDimension(); i++) {
            ExtendedRational l = ExtendedRationalOps.sub(mid, rad.getEntry(i));
            ExtendedRational u = ExtendedRationalOps.add(mid, rad.getEntry(i));
            r.setEntry(i, SetIntervalOps.nums2(l, u, Decoration.COM));
        }
        return r;
    }

    public static RationalVector neg(RationalVector b) {
        RationalVector r = new ArrayRationalVector(b.getDimension());
        for (int i = 0; i < b.getDimension(); i++) {
            r.setEntry(i, ExtendedRationalOps.neg(b.getEntry(i)));
        }
        return r;
    }

    public static RationalVector abs(RationalVector b) {
        RationalVector r = new ArrayRationalVector(b.getDimension());
        for (int i = 0; i < b.getDimension(); i++) {
            r.setEntry(i, ExtendedRationalOps.abs(b.getEntry(i)));
        }
        return r;
    }

    public static RationalVector add(ExtendedRationalContext rc, RationalVector a, RationalVector b) {
        if (a.getDimension() != b.getDimension()) {
            throw new IllegalArgumentException();
        }
        RationalVector r = new ArrayRationalVector(a.getDimension());
        for (int i = 0; i < a.getDimension(); i++) {
            r.setEntry(i, rc.add(a.getEntry(i), b.getEntry(i)));
        }
        return r;
    }

    public static RationalVector sub(ExtendedRationalContext rc, RationalVector a, RationalVector b) {
        if (a.getDimension() != b.getDimension()) {
            throw new IllegalArgumentException();
        }
        RationalVector r = new ArrayRationalVector(a.getDimension());
        for (int i = 0; i < a.getDimension(); i++) {
            r.setEntry(i, rc.sub(a.getEntry(i), b.getEntry(i)));
        }
        return r;
    }

    public static RationalVector div(ExtendedRationalContext rc, RationalVector a, RationalVector b) {
        if (a.getDimension() != b.getDimension()) {
            throw new IllegalArgumentException();
        }
        RationalVector r = new ArrayRationalVector(a.getDimension());
        for (int i = 0; i < a.getDimension(); i++) {
            r.setEntry(i, rc.div(a.getEntry(i), b.getEntry(i)));
        }
        return r;
    }

    public static RationalVector div(ExtendedRationalContext rc, ExtendedRational a, RationalVector b) {
        RationalVector r = new ArrayRationalVector(b.getDimension());
        for (int i = 0; i < b.getDimension(); i++) {
            r.setEntry(i, rc.div(a, b.getEntry(i)));
        }
        return r;
    }

    public static RationalVector div(ExtendedRationalContext rc, RationalVector a, ExtendedRational v) {
        RationalVector r = new ArrayRationalVector(a.getDimension());
        for (int i = 0; i < a.getDimension(); i++) {
            r.setEntry(i, rc.div(a.getEntry(i), v));
        }
        return r;
    }

    public static RationalVector min(RationalVector x, RationalVector y) {
        if (x.getDimension() != y.getDimension()) {
            throw new IllegalArgumentException();
        }
        RationalVector r = new ArrayRationalVector(x.getDimension());
        for (int i = 0; i < r.getDimension(); i++) {
            r.setEntry(i, ExtendedRationalOps.min(x.getEntry(i), y.getEntry(i)));
        }
        return r;
    }

    public static RationalVector max(RationalVector a, RationalVector b) {
        if (a.getDimension() != b.getDimension()) {
            throw new IllegalArgumentException();
        }
        RationalVector r = new ArrayRationalVector(a.getDimension());
        for (int i = 0; i < a.getDimension(); i++) {
            r.setEntry(i, ExtendedRationalOps.max(a.getEntry(i), b.getEntry(i)));
        }
        return r;
    }

    public static RationalMatrix neg(RationalMatrix A) {
        RationalMatrix r = new Array2DRowRationalMatrix(A.getRowDimension(), A.getColumnDimension());
        for (int i = 0; i < r.getRowDimension(); i++) {
            for (int j = 0; j < r.getColumnDimension(); j++) {
                r.setEntry(i, j, ExtendedRationalOps.neg(A.getEntry(i, j)));
            }
        }
        return r;
    }

    public static RationalMatrix abs(RationalMatrix A) {
        RationalMatrix r = new Array2DRowRationalMatrix(A.getRowDimension(), A.getColumnDimension());
        for (int i = 0; i < r.getRowDimension(); i++) {
            for (int j = 0; j < r.getColumnDimension(); j++) {
                r.setEntry(i, j, ExtendedRationalOps.abs(A.getEntry(i, j)));
            }
        }
        return r;
    }

    public static RationalMatrix max(RationalMatrix A, RationalMatrix B) {
        if (A.getRowDimension() != B.getRowDimension() || A.getColumnDimension() != B.getColumnDimension()) {
            throw new IllegalArgumentException();
        }
        RationalMatrix r = new Array2DRowRationalMatrix(A.getRowDimension(), A.getColumnDimension());
        for (int i = 0; i < r.getRowDimension(); i++) {
            for (int j = 0; j < r.getColumnDimension(); j++) {
                r.setEntry(i, j, ExtendedRationalOps.max(A.getEntry(i, j), B.getEntry(i, j)));
            }
        }
        return r;
    }

    public static RationalMatrix add(ExtendedRationalContext rc, RationalMatrix A, RationalMatrix B) {
        return A.add(rc, B);
    }

    public static RationalMatrix sub(ExtendedRationalContext rc, RationalMatrix A, RationalMatrix B) {
        return A.subtract(rc, B);
    }

    public static RationalMatrix mul(ExtendedRationalContext rc, RationalMatrix A, RationalMatrix B) {
        return A.multiply(rc, B);
    }

    /**
     * Element-by-element matrix multiplication (A.*B in Matlab)
     */
    public static RationalMatrix mul_(ExtendedRationalContext rc, RationalMatrix A, RationalMatrix B) {
        if (A.getRowDimension() != B.getRowDimension()
                || A.getColumnDimension() != B.getColumnDimension()) {
            throw new ArithmeticException();
        }
        RationalMatrix r = new Array2DRowRationalMatrix(A.getRowDimension(), A.getColumnDimension());
        for (int i = 0; i < A.getRowDimension(); i++) {
            for (int j = 0; j < A.getColumnDimension(); j++) {
                r.setEntry(i, j, rc.mul(A.getEntry(i, j), B.getEntry(i, j)));
            }
        }
        return r;
    }

    /**
     * Element-by-element vector multiplication (A.*B in Matlab)
     */
    public static RationalVector mul_(ExtendedRationalContext rc, RationalVector A, RationalVector B) {
        if (A.getDimension() != B.getDimension()) {
            throw new ArithmeticException();
        }
        RationalVector r = new ArrayRationalVector(A.getDimension());
        for (int i = 0; i < A.getDimension(); i++) {
            r.setEntry(i, rc.mul(A.getEntry(i), B.getEntry(i)));
        }
        return r;
    }

    public static RationalVector mul(ExtendedRationalContext rc, RationalMatrix A, RationalVector b) {
        return A.multiply(rc, b);
    }

    public static RationalMatrix mul(ExtendedRationalContext rc, RationalMatrix A, Rational b) {
        int m = A.getColumnDimension();
        int n = A.getRowDimension();
        RationalMatrix r = new Array2DRowRationalMatrix(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                r.setEntry(i, j, rc.mul(A.getEntry(i, j), b));
            }
        }
        return r;
    }

    public static RationalVector mul(ExtendedRationalContext rc, RationalVector A, ExtendedRational b) {
        int n = A.getDimension();
        RationalVector r = new ArrayRationalVector(n);
        for (int i = 0; i < n; i++) {
            r.setEntry(i, rc.mul(A.getEntry(i), b));
        }
        return r;
    }

    public static RationalMatrix div(ExtendedRationalContext rc, RationalMatrix A, ExtendedRational v) {
        RationalMatrix r = new Array2DRowRationalMatrix(A.getRowDimension(), A.getColumnDimension());
        for (int i = 0; i < A.getRowDimension(); i++) {
            for (int j = 0; j < A.getColumnDimension(); j++) {
                r.setEntry(i, j, rc.div(A.getEntry(i, j), v));
            }
        }
        return r;
    }

    public static RationalMatrix inv(ExtendedRationalContext rc, RationalMatrix A) {
        return new LUDecomposition(rc, A).solve(rc, eye(A.getColumnDimension()));
    }

    public static ExtendedRational dot(ExtendedRationalContext rc, RationalVector x1, RationalVector x2) {
        if (x1.getDimension() != x2.getDimension()) {
            throw new IllegalArgumentException();
        }
        ExtendedRational r = Rational.zero();
        for (int i = 0; i < x1.getDimension(); i++) {
            r = rc.add(r, rc.mul(x1.getEntry(i), x2.getEntry(i)));
        }
        return r;
    }

    public static ExtendedRational min(RationalVector x) {
        ExtendedRational r = ExtendedRational.POSITIVE_INFINITY;
        for (int i = 0; i < x.getDimension(); i++) {
            r = ExtendedRationalOps.min(r, x.getEntry(i));
        }
        return r;
    }

    public static ExtendedRational max(RationalVector x) {
        ExtendedRational r = ExtendedRational.NEGATIVE_INFINITY;
        for (int i = 0; i < x.getDimension(); i++) {
            r = ExtendedRationalOps.max(r, x.getEntry(i));
        }
        return r;
    }

    public static RationalVector cross(ExtendedRationalContext rc, RationalVector x, RationalVector y) {
        if (x.getDimension() != 3) {
            throw new IllegalArgumentException();
        }
        if (y.getDimension() != 3) {
            throw new IllegalArgumentException();
        }
        ExtendedRational x0 = x.getEntry(0);
        ExtendedRational x1 = x.getEntry(1);
        ExtendedRational x2 = x.getEntry(2);
        ExtendedRational y0 = y.getEntry(0);
        ExtendedRational y1 = y.getEntry(1);
        ExtendedRational y2 = y.getEntry(2);
        RationalVector r = new ArrayRationalVector(3);
        r.setEntry(0, rc.sub(rc.mul(x1, y2), rc.mul(x2, y1)));
        r.setEntry(1, rc.sub(rc.mul(x2, y0), rc.mul(x0, y2)));
        r.setEntry(2, rc.sub(rc.mul(x0, y1), rc.mul(x1, y0)));
        return r;
    }

    public static RationalMatrix eye(int n) {
        return MatrixUtils.createRationalIdentityMatrix(n);
    }

    public static RationalMatrix deleteRow(RationalMatrix A, int row) {
        int m = A.getRowDimension();
        int n = A.getColumnDimension();
        if (row < 0 || row >= m) {
            throw new IllegalArgumentException();
        }
        RationalMatrix r = new Array2DRowRationalMatrix(m - 1, n);
        int ii = 0;
        for (int i = 0; i < m; i++) {
            if (i == row) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                r.setEntry(ii, j, A.getEntry(i, j));
            }
            ii++;
        }
        return r;
    }

    public static RationalVector deleteElem(RationalVector b, int ind) {
        int n = b.getDimension();
        if (ind < 0 || ind >= n) {
            throw new IllegalArgumentException();
        }
        RationalVector r = new ArrayRationalVector(n - 1);
        int ii = 0;
        for (int i = 0; i < n; i++) {
            if (i == ind) {
                continue;
            }
            r.setEntry(ii, b.getEntry(i));
            ii++;
        }
        return r;
    }

    public static RationalMatrix concatVer(RationalMatrix... blocks) {
        if (blocks.length == 0) {
            throw new IllegalArgumentException();
        }
        int n = blocks[0].getColumnDimension();
        int m = 0;
        for (RationalMatrix block : blocks) {
            if (block.getColumnDimension() != n) {
                throw new IllegalArgumentException();
            }
            m += block.getRowDimension();
        }
        RationalMatrix r = new Array2DRowRationalMatrix(m, n);
        int ii = 0;
        for (RationalMatrix block : blocks) {
            for (int i = 0; i < block.getRowDimension(); i++) {
                for (int j = 0; j < n; j++) {
                    r.setEntry(ii, j, block.getEntry(i, j));
                }
                ii++;
            }
        }
        assert ii == m;
        return r;
    }

    public static RationalMatrix concatVer(RationalVector... rows) {
        if (rows.length == 0) {
            throw new IllegalArgumentException();
        }
        int m = rows.length;
        int n = rows[0].getDimension();
        RationalMatrix r = new Array2DRowRationalMatrix(m, n);
        for (int i = 0; i < m; i++) {
            if (rows[i].getDimension() != n) {
                throw new IllegalArgumentException();
            }
            for (int j = 0; j < n; j++) {
                r.setEntry(i, j, rows[i].getEntry(j));
            }
        }
        return r;
    }

    public static RationalMatrix concatHor(RationalMatrix... blocks) {
        if (blocks.length == 0) {
            throw new IllegalArgumentException();
        }
        int m = blocks[0].getRowDimension();
        int n = 0;
        for (RationalMatrix block : blocks) {
            if (block.getRowDimension() != m) {
                throw new IllegalArgumentException();
            }
            n += block.getColumnDimension();
        }
        RationalMatrix r = new Array2DRowRationalMatrix(m, n);
        int jj = 0;
        for (RationalMatrix block : blocks) {
            for (int j = 0; j < block.getColumnDimension(); j++) {
                for (int i = 0; i < m; i++) {
                    r.setEntry(i, jj, block.getEntry(i, j));
                }
                jj++;
            }
        }
        assert jj == n;
        return r;
    }

    public static RationalMatrix concatHor(RationalVector... cols) {
        if (cols.length == 0) {
            throw new IllegalArgumentException();
        }
        int n = cols.length;
        int m = cols[0].getDimension();
        RationalMatrix r = new Array2DRowRationalMatrix(m, n);
        for (int j = 0; j < n; j++) {
            if (cols[j].getDimension() != m) {
                throw new IllegalArgumentException();
            }
            for (int i = 0; i < m; i++) {
                r.setEntry(i, j, cols[j].getEntry(i));
            }
        }
        return r;
    }

    public static RationalVector concat(RationalVector... blocks) {
        int n = 0;
        for (RationalVector block : blocks) {
            n += block.getDimension();
        }
        RationalVector r = new ArrayRationalVector(n);
        int ii = 0;
        for (RationalVector block : blocks) {
            for (int i = 0; i < block.getDimension(); i++) {
                r.setEntry(ii++, block.getEntry(i));
            }
        }
        assert ii == n;
        return r;
    }

    public static RationalVector vec(double... v) {
        RationalVector r = new ArrayRationalVector(v.length);
        for (int i = 0; i < v.length; i++) {
            r.setEntry(i, ExtendedRational.valueOf(v[i]));
        }
        return r;
    }

    public static RationalVector vec(ExtendedRational... v) {
        RationalVector r = new ArrayRationalVector(v.length);
        for (int i = 0; i < v.length; i++) {
            r.setEntry(i, v[i]);
        }
        return r;
    }

    public static RationalMatrix hilbert(int n) {
        return MatrixUtils.createHilbertMatrix(n);
    }

    public static RationalMatrix hilbert(ExtendedRationalContext rc, int n) {
        return MatrixUtils.createHilbertMatrix(rc, n);
    }

    public static RationalVector zeros(int n) {
        return new ArrayRationalVector(n, Rational.zero());
    }

    public static RationalMatrix zeros(int m, int n) {
        return new Array2DRowRationalMatrix(m, n);
    }

    public static RationalVector ones(int n) {
        return new ArrayRationalVector(n, Rational.one());
    }

    public static RationalMatrix ones(int m, int n) {
        return new Array2DRowRationalMatrix(m, n, Rational.one());
    }
}
