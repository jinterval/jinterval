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
/**
 * Calculates the LUP-decomposition of a square matrix. <p>The LUP-decomposition
 * of a matrix A consists of three matrices L, U and P that satisfy: P&times;A =
 * L&times;U. L is lower triangular (with unit diagonal terms), U is upper
 * triangular and P is a permutation matrix. All matrices are m&times;m.</p>
 * <p>As shown by the presence of the P matrix, this decomposition is
 * implemented using partial pivoting.</p> <p>This class is based on the class
 * with similar name from the <a
 * href="http://math.nist.gov/javanumerics/jama/">JAMA</a> library.</p> <ul>
 * <li>a {@link #getP() getP} method has been added,</li> <li>the {@code det}
 * method has been renamed as {@link #getDeterminant()
 *   getDeterminant},</li> <li>the {@code getDoublePivot} method has been removed
 * (but the int based {@link #getPivot() getPivot} method has been kept),</li>
 * <li>the {@code solve} and {@code isNonSingular} methods have been replaced by
 * a {@link #getSolver() getSolver} method and the equivalent methods provided
 * by the returned {@link DecompositionSolver}.</li>
 * </ul>
 *
 * @see <a
 * href="http://mathworld.wolfram.com/LUDecomposition.html">MathWorld</a>
 * @see <a href="http://en.wikipedia.org/wiki/LU_decomposition">Wikipedia</a>
 */
/**
 * LU Decomposition. <P> For an m-by-n matrix A with m >= n, the LU
 * decomposition is an m-by-n unit lower triangular matrix L, an n-by-n upper
 * triangular matrix U, and a permutation vector piv of length m so that
 * A(piv,:) = L*U. If m < n, then L is m-by-m and U is m-by-n. <P> The LU
 * decompostion with pivoting always exists, even if the matrix is singular, so
 * the constructor will never fail. The primary use of the LU decomposition is
 * in the solution of square systems of simultaneous linear equations. This will
 * fail if isNonsingular() returns false.
 */
package net.java.jinterval.linear;

import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public class LUDecomposition {

    /*
     * ------------------------ Class variables ------------------------
     */
    /**
     * Array for internal storage of decomposition.
     */
    private ExtendedRational[][] LU;
    /**
     * Row and column dimensions, and pivot sign.
     *
     * @serial column dimension.
     * @serial row dimension.
     * @serial pivot sign.
     */
    private int m, n, pivsign;
    /**
     * Internal storage of pivot vector.
     *
     * @serial pivot vector.
     */
    private int[] piv;

    /*
     * ------------------------ Constructor ------------------------
     */
    /**
     * LU Decomposition
     *
     * @param A Rectangular matrix
     * @return Structure to access L, U and piv.
     */
    public LUDecomposition(ExtendedRationalContext rc, RationalMatrix A) {

        // Use a "left-looking", dot-product, Crout/Doolittle algorithm.

        m = A.getRowDimension();
        n = A.getColumnDimension();
        LU = new ExtendedRational[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                LU[i][j] = A.getEntry(i, j);
            }
        }
        piv = new int[m];
        for (int i = 0; i < m; i++) {
            piv[i] = i;
        }
        pivsign = 1;
        ExtendedRational[] LUrowi;
        ExtendedRational[] LUcolj = new ExtendedRational[m];

        // Outer loop.

        for (int j = 0; j < n; j++) {

            // Make a copy of the j-th column to localize references.

            for (int i = 0; i < m; i++) {
                LUcolj[i] = LU[i][j];
            }

            // Apply previous transformations.

            for (int i = 0; i < m; i++) {
                LUrowi = LU[i];

                // Most of the time is spent in the following dot product.

                int kmax = Math.min(i, j);
                ExtendedRational s = Rational.zero();
                for (int k = 0; k < kmax; k++) {
                    s = rc.add(s, rc.mul(LUrowi[k], LUcolj[k]));
                }

                LUrowi[j] = LUcolj[i] = rc.sub(LUcolj[i], s);
            }

            // Find pivot and exchange if necessary.

            int p = j;
            for (int i = j + 1; i < m; i++) {
                if (ExtendedRationalOps.abs(LUcolj[i]).gt(ExtendedRationalOps.abs(LUcolj[p]))) {
                    p = i;
                }
            }
            if (p != j) {
                for (int k = 0; k < n; k++) {
                    ExtendedRational t = LU[p][k];
                    LU[p][k] = LU[j][k];
                    LU[j][k] = t;
                }
                int k = piv[p];
                piv[p] = piv[j];
                piv[j] = k;
                pivsign = -pivsign;
            }

            // Compute multipliers.

            if (j < m & LU[j][j].signum() != 0) {
                for (int i = j + 1; i < m; i++) {
                    LU[i][j] = rc.div(LU[i][j], LU[j][j]);
                }
            }
        }
    }

    /*
     * ------------------------ Temporary, experimental code.
     * ------------------------ *\
     *
     * \** LU Decomposition, computed by Gaussian elimination. <P> This
     * constructor computes L and U with the "daxpy"-based elimination algorithm
     * used in LINPACK and MATLAB. In Java, we suspect the dot-product, Crout
     * algorithm will be faster. We have temporarily included this constructor
     * until timing experiments confirm this suspicion. <P> @param A Rectangular
     * matrix @param linpackflag Use Gaussian elimination. Actual value ignored.
     * @return Structure to access L, U and piv. \
     *
     * public LUDecomposition (Matrix A, int linpackflag) { // Initialize. LU =
     * A.getArrayCopy(); m = A.getRowDimension(); n = A.getColumnDimension();
     * piv = new int[m]; for (int i = 0; i < m; i++) { piv[i] = i; } pivsign =
     * 1; // Main loop. for (int k = 0; k < n; k++) { // Find pivot. int p = k;
     * for (int i = k+1; i < m; i++) { if (Math.abs(LU[i][k]) >
     * Math.abs(LU[p][k])) { p = i; } } // Exchange if necessary. if (p != k) {
     * for (int j = 0; j < n; j++) { double t = LU[p][j]; LU[p][j] = LU[k][j];
     * LU[k][j] = t; } int t = piv[p]; piv[p] = piv[k]; piv[k] = t; pivsign =
     * -pivsign; } // Compute multipliers and eliminate k-th column. if
     * (LU[k][k] != 0.0) { for (int i = k+1; i < m; i++) { LU[i][k] /= LU[k][k];
     * for (int j = k+1; j < n; j++) { LU[i][j] -= LU[i][k]*LU[k][j]; } } } } }
     *
     * \* ------------------------ End of temporary code.
     * ------------------------
     */

    /*
     * ------------------------ Public Methods ------------------------
     */
    /**
     * Is the matrix nonsingular?
     *
     * @return true if U, and hence A, is nonsingular.
     */
    public boolean isNonsingular() {
        for (int j = 0; j < n; j++) {
            if (LU[j][j].signum() == 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * Return lower triangular factor
     *
     * @return L
     */
    public RationalMatrix getL() {
        RationalMatrix X = new Array2DRowRationalMatrix(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > j) {
                    X.setEntry(i, j, LU[i][j]);
                } else if (i == j) {
                    X.setEntry(i, j, Rational.one());
                } else {
                    X.setEntry(i, j, Rational.zero());
                }
            }
        }
        return X;
    }

    /**
     * Return upper triangular factor
     *
     * @return U
     */
    public RationalMatrix getU() {
        RationalMatrix X = new Array2DRowRationalMatrix(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i <= j) {
                    X.setEntry(i, j, LU[i][j]);
                } else {
                    X.setEntry(i, j, Rational.zero());
                }
            }
        }
        return X;
    }

    /**
     * Return pivot permutation vector
     *
     * @return piv
     */
    public int[] getPivot() {
        int[] p = new int[m];
        for (int i = 0; i < m; i++) {
            p[i] = piv[i];
        }
        return p;
    }

    /**
     * Return pivot permutation vector as a one-dimensional double array
     *
     * @return (double) piv
     */
    public Rational[] getRationalPivot() {
        Rational[] vals = new Rational[m];
        for (int i = 0; i < m; i++) {
            vals[i] = Rational.valueOf(piv[i]);
        }
        return vals;
    }

    /**
     * Determinant
     *
     * @return det(A)
     * @exception IllegalArgumentException Matrix must be square
     */
    public ExtendedRational det(ExtendedRationalContext rc) {
        if (m != n) {
            throw new IllegalArgumentException("Matrix must be square.");
        }
        ExtendedRational d = Rational.valueOf(pivsign);
        for (int j = 0; j < n; j++) {
            d = rc.mul(d, LU[j][j]);
        }
        return d;
    }

    /**
     * Solve A*X = B
     *
     * @param B A Matrix with as many rows as A and any number of columns.
     * @return X so that L*U*X = B(piv,:)
     * @exception IllegalArgumentException Matrix row dimensions must agree.
     * @exception RuntimeException Matrix is singular.
     */
    public RationalMatrix solve(ExtendedRationalContext rc, RationalMatrix B) {
        if (B.getRowDimension() != m) {
            throw new IllegalArgumentException("Matrix row dimensions must agree.");
        }
        if (!this.isNonsingular()) {
            throw new RuntimeException("Matrix is singular.");
        }

        // Copy right hand side with pivoting
        int nx = B.getColumnDimension();
        RationalMatrix Xmat = new Array2DRowRationalMatrix(piv.length, nx);
        for (int i = 0; i < piv.length; i++) {
            for (int j = 0; j < nx; j++) {
                Xmat.setEntry(i, j, B.getEntry(piv[i], j));
            }
        }

        // Solve L*Y = B(piv,:)
        for (int k = 0; k < n; k++) {
            for (int i = k + 1; i < n; i++) {
                for (int j = 0; j < nx; j++) {
                    Xmat.setEntry(i, j, rc.sub(Xmat.getEntry(i, j), rc.mul(Xmat.getEntry(k, j), LU[i][k])));
                }
            }
        }
        // Solve U*X = Y;
        for (int k = n - 1; k >= 0; k--) {
            for (int j = 0; j < nx; j++) {
                Xmat.setEntry(k, j, rc.div(Xmat.getEntry(k, j), LU[k][k]));
            }
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < nx; j++) {
                    Xmat.setEntry(i, j, rc.sub(Xmat.getEntry(i, j), rc.mul(Xmat.getEntry(k, j), LU[i][k])));
                }
            }
        }
        return Xmat;
    }

    /**
     * Solve A*X = b
     *
     * @param b A Vector with as many elements as rows in A.
     * @return X so that L*U*X = b(piv)
     * @exception IllegalArgumentException Matrix row dimensions must agree.
     * @exception RuntimeException Matrix is singular.
     */
    public RationalVector solve(ExtendedRationalContext rc, RationalVector b) {
        if (b.getDimension() != m) {
            throw new IllegalArgumentException("Matrix row dimensions must agree.");
        }
        if (!this.isNonsingular()) {
            throw new RuntimeException("Matrix is singular.");
        }

        // Copy right hand side with pivoting
        RationalVector Xvec = new ArrayRationalVector(piv.length);
        for (int i = 0; i < piv.length; i++) {
            Xvec.setEntry(i, b.getEntry(piv[i]));
        }

        // Solve L*Y = b(piv)
        for (int k = 0; k < n; k++) {
            for (int i = k + 1; i < n; i++) {
                Xvec.setEntry(i, rc.sub(Xvec.getEntry(i), rc.mul(Xvec.getEntry(k), LU[i][k])));
            }
        }
        // Solve U*X = Y;
        for (int k = n - 1; k >= 0; k--) {
            Xvec.setEntry(k, rc.div(Xvec.getEntry(k), LU[k][k]));
            for (int i = 0; i < k; i++) {
                Xvec.setEntry(i, rc.sub(Xvec.getEntry(i), rc.mul(Xvec.getEntry(k), LU[i][k])));
            }
        }
        return Xvec;
    }
}
