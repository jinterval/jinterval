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

import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.linear.RationalVector;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.ExtendedRationalContext;
import org.apache.commons.math3.exception.DimensionMismatchException;
import org.apache.commons.math3.exception.MaxCountExceededException;
import org.apache.commons.math3.exception.NullArgumentException;
import org.apache.commons.math3.linear.NonSquareOperatorException;
import org.apache.commons.math3.util.IterationManager;
import org.apache.commons.math3.util.MathUtils;

/**
 * Gauss-Seiadel iterative solver of interval linear system of equations A
 * &middot; x = b with Hansen-Rohn-Bliek preconditioning for H-matricies
 *
 * @author sz
 */
public class GaussSeidelIterativeSolver extends MatlabOps {

    private static final boolean DEBUG = false;
    private final ExtendedRationalContext rcInv;
    private final ExtendedRationalContext rcDown;
    private final ExtendedRationalContext rcUp;
    private final SetIntervalContext ctx;
    /**
     * The object in charge of managing the iterations.
     */
    private final IterationManager manager;

    /**
     * Creates a new instance of this class, with default iteration manager.
     *
     * @param maxIterations the maximum number of iterations
     */
    public GaussSeidelIterativeSolver(BinaryValueSet valueSet, int maxIterations) {
        this(valueSet, new IterationManager(maxIterations));
    }

    /**
     * Creates a new instance of this class, with custom iteration manager.
     *
     * @param manager the custom iteration manager
     * @throws NullArgumentException if {@code manager} is {@code null}
     */
    public GaussSeidelIterativeSolver(BinaryValueSet valueSet, final IterationManager manager)
            throws NullArgumentException {
        if (valueSet != null) {
            rcInv = ExtendedRationalContexts.mkNearest(valueSet);
            rcDown = ExtendedRationalContexts.mkFloor(valueSet);
            rcUp = ExtendedRationalContexts.mkCeiling(valueSet);
            ctx = SetIntervalContexts.getTightest(valueSet);
        } else {
            rcInv = rcDown = rcUp = ExtendedRationalContexts.exact();
            ctx = SetIntervalContexts.getExact();
        }
        MathUtils.checkNotNull(manager);
        this.manager = manager;
    }

    /**
     * Performs all dimension checks on the parameters of
     * {@link #solve(IntervalMatrix, IntervalVector, IntervalVector) solve} and
     * {@link #solveInPlace(IntervalMatrix, IntervalVector, IntervalVector) solveInPlace},
     * and throws an exception if one of the checks fails.
     *
     * @param a the interval matrix A of the system
     * @param b the right-hand side interval vector
     * @param x0 the initial interval guess of the solution
     * @throws NullArgumentException if one of the parameters is {@code null}
     * @throws NonSquareOperatorException if {@code a} is not square
     * @throws DimensionMismatchException if {@code b} or {@code x0} have
     * dimensions inconsistent with {@code a}
     */
    protected static void checkParameters(final IntervalMatrix a,
            final IntervalVector b, final IntervalVector x0) throws
            NullArgumentException, NonSquareOperatorException,
            DimensionMismatchException {
        MathUtils.checkNotNull(a);
        MathUtils.checkNotNull(b);
        MathUtils.checkNotNull(x0);
        if (a.getRowDimension() != a.getColumnDimension()) {
            throw new NonSquareOperatorException(a.getRowDimension(),
                    a.getColumnDimension());
        }
        if (b.getDimension() != a.getRowDimension()) {
            throw new DimensionMismatchException(b.getDimension(),
                    a.getRowDimension());
        }
        if (x0.getDimension() != a.getColumnDimension()) {
            throw new DimensionMismatchException(x0.getDimension(),
                    a.getColumnDimension());
        }
    }

    /**
     * Returns the iteration manager attached to this solver.
     *
     * @return the manager
     */
    public IterationManager getIterationManager() {
        return manager;
    }

    /**
     * Returns an outer estimate of the united solution set to the interval
     * linear system A &middot; x = b.
     *
     * @param a the interval matrix A of the system
     * @param b the right-hand side interval vector
     * @return an interval vector containing the solution set
     * @throws NullArgumentException if one of the parameters is {@code null}
     * @throws NonSquareOperatorException if {@code a} is not square
     * @throws DimensionMismatchException if {@code b} has dimensions
     * inconsistent with {@code a}
     * @throws MaxCountExceededException at exhaustion of the iteration count,
     * unless a custom
     * {@link org.apache.commons.math3.util.Incrementor.MaxCountExceededCallback callback}
     * has been set at construction
     */
    public IntervalVector solve(final IntervalMatrix a, final IntervalVector b)
            throws NullArgumentException, NonSquareOperatorException,
            DimensionMismatchException, MaxCountExceededException {
        MathUtils.checkNotNull(a);
        //final IntervalVector x = new IntervalVector(a.getColumnDimension());
        //x.set(ctx.empty());
        return solveInPlace(a, b, null);
    }

    /**
     * Returns an outer estimate of the united solution set to the interval
     * linear system A &middot; x = b.
     *
     * @param a the interval matrix A of the system
     * @param b the right-hand side interval vector
     * @param x0 the initial interval vector containing the solution
     * @return an interval vector containing the solution set
     * @throws NullArgumentException if one of the parameters is {@code null}
     * @throws NonSquareOperatorException if {@code a} is not square
     * @throws DimensionMismatchException if {@code b} or {@code x0} have
     * dimensions inconsistent with {@code a}
     * @throws MaxCountExceededException at exhaustion of the iteration count,
     * unless a custom
     * {@link org.apache.commons.math3.util.Incrementor.MaxCountExceededCallback callback}
     * has been set at construction
     */
    public IntervalVector solve(IntervalMatrix a, IntervalVector b, IntervalVector x0)
            throws NullArgumentException, NonSquareOperatorException,
            DimensionMismatchException, MaxCountExceededException {
        MathUtils.checkNotNull(x0);
        return solveInPlace(a, b, x0);
    }

    /**
     * Returns an outer estimate of the united solution to the interval linear
     * system A &middot; x = b. The solution is computed in-place (initial guess
     * is modified).
     *
     * @param a the linear operator A of the system
     * @param b the right-hand side vector
     * @param x0 initial guess of the solution
     * @return a reference to {@code x0} (shallow copy) updated with the
     * solution
     * @throws NullArgumentException if one of the parameters is {@code null}
     * @throws NonSquareOperatorException if {@code a} is not square
     * @throws DimensionMismatchException if {@code b} or {@code x0} have
     * dimensions inconsistent with {@code a}
     * @throws MaxCountExceededException at exhaustion of the iteration count,
     * unless a custom
     * {@link org.apache.commons.math3.util.Incrementor.MaxCountExceededCallback callback}
     * has been set at construction
     */
    public IntervalVector solveInPlace(IntervalMatrix A, IntervalVector b,
            IntervalVector x0) throws NullArgumentException, NonSquareOperatorException,
            DimensionMismatchException, MaxCountExceededException {

        int n = dim(A);

        IntervalVector x = x0 != null ? x0.copy() : new IntervalVector(n, ctx.entire());

        // dA = diag(A);  
        IntervalVector dA = diag(A);
        // build comparison matrix C  
        RationalMatrix C = compmat(A);
        if (DEBUG) {
            System.out.println("C:\n" + C);
        }


        // B = inv(C); 
        RationalMatrix B = inv(rcInv, C);
        if (DEBUG) {
            System.out.println("B:\n" + B);
        }

        // v = abs(B*ones(n,1));
        RationalMatrix v = abs(mul(rcInv, B, ones(n, 1)));
        if (DEBUG) {
            System.out.println("v: " + v);
        }

        // SetRoundDown;
        // Cv = C*v; 
        RationalMatrix Cv = mul(rcDown, C, v);
        if (DEBUG) {
            System.out.println("Cv: " + Cv);
        }

        if (Cv.getMinValue().signum() > 0) {
            // A is H-matrix

            //dC = diag(C);
            RationalVector dC = diag(C);

            // R = C*B - eye(n,n); 
            RationalMatrix R = sub(rcDown, mul(rcDown, C, B), eye(n));

            // SetRoundUp;
            // w = zeros(1,n);      
            // for i = 1:n
            //    w = max(w,(-R(i,:))/Cv(i));
            // end ; 
            RationalMatrix w = zeros(1, n);
            for (int i = 0; i < n; i++) {
                w = max(w, div(rcUp, neg(R.getSubMatrix(i, i, 0, n - 1)), Cv.getEntry(i, 0)));
            }

            // dlow = v.*w-diag(B); dlow=-dlow;
            RationalVector vw = mul_(rcUp, v.getColumnVector(0), w.getRowVector(0));
            RationalVector dlow = sub(rcUp, vw, B.diag());
            dlow = neg(dlow);

            // B = B + v*w;
            B = add(rcUp, B, mul(rcUp, v, w));

            // u = B*abs(b);
            RationalVector u = mul(rcUp, B, b.mag());

            //d = diag(B); 
            RationalVector d = B.diag();

            // alpha = dC + (-1)./d;
            RationalVector alpha = add(rcUp, dC, div(rcUp, Rational.valueOf(-1), d));
            // beta = u./d-abs(b);
            RationalVector beta = sub(rcUp, div(rcUp, u, dlow), b.mag());
            // x = (b + midrad(0,beta))./(dA + midrad(0, alpha);
            x = div(ctx, add(ctx, b, midrad(Rational.zero(), beta)), add(ctx, dA, midrad(Rational.zero(), alpha)));

        }

        //y = x;
        //for k = 1:IterLim;
        //    for i = 1:n;
        //        s = b(i);
        //        for j = 1:n;
        //            if i~=j then
        //                s = s - A(i,j)*y(j);
        //            end
        //        end
        //        s = intersection( s/A(i,i), y(i) ); 
        //        y(i) = s;
        //    end
        //end

        IntervalVector y = x.copy();

        for (manager.resetIterationCount();
                manager.getIterations() < manager.getMaxIterations();
                manager.incrementIterationCount()) {
            for (int i = 0; i < n; i++) {
                SetInterval s = b.getEntry(i);
                for (int j = 0; j < n; j++) {
                    SetInterval Aij = A.getEntry(i, j);
                    if (i != j) {
                        s = ctx.sub(s, ctx.mul(Aij, y.getEntry(j)));
                    }
                }
                SetInterval Aii = A.getEntry(i, i);
                s = ctx.intersection(ctx.div(s, Aii), y.getEntry(i));
                y.setEntry(i, s);
            }
        }

        return y;
    }
}
