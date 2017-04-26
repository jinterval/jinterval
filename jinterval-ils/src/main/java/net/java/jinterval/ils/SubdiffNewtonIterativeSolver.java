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
import net.java.jinterval.interval.kaucher.KaucherInterval;
import net.java.jinterval.interval.kaucher.KaucherIntervalContext;
import net.java.jinterval.interval.kaucher.KaucherIntervalContexts;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.linear.*;
import net.java.jinterval.rational.*;
import org.apache.commons.math3.exception.DimensionMismatchException;
import org.apache.commons.math3.exception.MaxCountExceededException;
import org.apache.commons.math3.exception.NullArgumentException;
import org.apache.commons.math3.linear.NonSquareOperatorException;
import org.apache.commons.math3.util.IterationManager;
import org.apache.commons.math3.util.MathUtils;

class DummyUtils {
    //set pair of F using A(i,j),[x(j),x(j+n)]

    public static void calcSubgrad(RationalMatrix F, int i, int j, KaucherInterval a, KaucherInterval b) {
        int n = F.getRowDimension() / 2;
        int k, m;

        Rational ai = a.inf();
        Rational as = a.sup();
        Rational bi = b.inf();
        Rational bs = b.sup();

        if (ai.signum() * as.signum() > 0) {
            k = (ai.signum() > 0) ? 0 : 2;
        } else {
            k = (ai.lt(as)) ? 1 : 3;
        }

        if (bi.signum() * bs.signum() > 0) {
            m = (bi.signum() > 0) ? 1 : 3;
        } else {
            m = (bi.le(bs)) ? 2 : 4;
        }

        switch (4 * k + m) {
            case 1:
                F.setEntry(i, j, ai);
                F.setEntry(i + n, j + n, as);
                break;
            case 2:
                F.setEntry(i, j, as);
                F.setEntry(i + n, j + n, as);
                break;
            case 3:
                F.setEntry(i, j, as);
                F.setEntry(i + n, j + n, ai);
                break;
            case 4:
                F.setEntry(i, j, ai);
                F.setEntry(i + n, j + n, ai);
                break;
            case 5:
                F.setEntry(i, j + n, RationalOps.neg(ai));
                F.setEntry(i + n, j + n, as);
                break;
            case 6:
                if (RationalOps.mul(ai, bs).lt(RationalOps.mul(as, bi))) {
                    F.setEntry(i, j + n, RationalOps.neg(ai));
                } else {
                    F.setEntry(i, j, as);
                }
                if (RationalOps.mul(ai, bi).gt(RationalOps.mul(as, bs))) {
                    F.setEntry(i + n, j, RationalOps.neg(ai));
                } else {
                    F.setEntry(i + n, j + n, as);
                }
                break;
            case 7:
                F.setEntry(i, j, as);
                F.setEntry(i + n, j, RationalOps.neg(ai));
                break;
            case 9:
                F.setEntry(i, j + n, RationalOps.neg(ai));
                F.setEntry(i + n, j, RationalOps.neg(as));
                break;
            case 10:
                F.setEntry(i, j + n, RationalOps.neg(ai));
                F.setEntry(i + n, j, RationalOps.neg(ai));
                break;
            case 11:
                F.setEntry(i, j + n, RationalOps.neg(as));
                F.setEntry(i + n, j, RationalOps.neg(ai));
                break;
            case 12:
                F.setEntry(i, j + n, RationalOps.neg(as));
                F.setEntry(i + n, j, RationalOps.neg(as));
                break;
            case 13:
                F.setEntry(i, j, ai);
                F.setEntry(i + n, j, RationalOps.neg(as));
                break;
            case 15:
                F.setEntry(i, j + n, RationalOps.neg(as));
                F.setEntry(i + n, j + n, ai);
                break;
            case 16:
                if (RationalOps.mul(ai, bi).gt(RationalOps.mul(as, bs))) {
                    F.setEntry(i, j, ai);
                } else {
                    F.setEntry(i, j + n, RationalOps.neg(as));
                }
                if (RationalOps.mul(ai, bs).lt(RationalOps.mul(as, bi))) {
                    F.setEntry(i + n, j + n, ai);
                } else {
                    F.setEntry(i + n, j, RationalOps.neg(as));
                }
                break;
        }
    }
}

/**
 *
 * @author sz
 */
public class SubdiffNewtonIterativeSolver {

    private final ExtendedRationalContext rcNear;
    private final KaucherIntervalContext ctx;
    Rational Eps = Rational.valueOf(1.0e-7);
    Rational Tau = Rational.valueOf(1.0);
    /**
     * The object in charge of managing the iterations.
     */
    private final IterationManager manager;

    /**
     * Creates a new instance of this class, with default iteration manager.
     *
     * @param maxIterations the maximum number of iterations
     */
    public SubdiffNewtonIterativeSolver(BinaryValueSet valueSet, int maxIterations) {
        this(valueSet, new IterationManager(maxIterations));
    }

    /**
     * Creates a new instance of this class, with custom iteration manager.
     *
     * @param manager the custom iteration manager
     * @throws NullArgumentException if {@code manager} is {@code null}
     */
    public SubdiffNewtonIterativeSolver(BinaryValueSet valueSet, final IterationManager manager)
            throws NullArgumentException {
        if (valueSet != null) {
            rcNear = ExtendedRationalContexts.mkNearest(valueSet);
            ctx = KaucherIntervalContexts.getInfSup(valueSet);
        } else {
            rcNear = ExtendedRationalContexts.exact();
            ctx = KaucherIntervalContexts.getExact();
        }
        Eps = Rational.exp2(-valueSet.getPrecision() + 3);
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
            final IntervalVector b) throws
            NullArgumentException, NonSquareOperatorException,
            DimensionMismatchException {
        MathUtils.checkNotNull(a);
        MathUtils.checkNotNull(b);
        if (a.getRowDimension() != a.getColumnDimension()) {
            throw new NonSquareOperatorException(a.getRowDimension(),
                    a.getColumnDimension());
        }
        if (b.getDimension() != a.getRowDimension()) {
            throw new DimensionMismatchException(b.getDimension(),
                    a.getRowDimension());
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
     * Returns formal solution of the interval linear system A &middot; x = b.
     * in Kaucher arithmetics
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
        return solveInPlace(a, b);
    }

    public IntervalVector solveInPlace(IntervalMatrix A, IntervalVector b)
            throws NullArgumentException, NonSquareOperatorException,
            DimensionMismatchException, MaxCountExceededException {

        checkParameters(A, b);

        int n = A.getRowDimension();

        RationalMatrix F = new Array2DRowRationalMatrix(2 * n, 2 * n);
        RationalVector xx = new ArrayRationalVector(2 * n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                Rational p = A.getEntry(i, j).mid();
                if (p.signum() >= 0) {
                    F.setEntry(i, j, p);
                    F.setEntry(i + n, j + n, p);
                } else {
                    F.setEntry(i + n, j, RationalOps.neg(p));
                    F.setEntry(i, j + n, RationalOps.neg(p));
                }
            }
        }

        xx.setSubVector(0, MatlabOps.neg(b.getInf()));
        xx.setSubVector(n, b.getSup());
        xx = new LUDecomposition(rcNear, F).solve(rcNear, xx);

        ExtendedRational r = ExtendedRational.POSITIVE_INFINITY,
                q = Rational.one();
        RationalVector x;

        for (manager.resetIterationCount();
                manager.getIterations() < manager.getMaxIterations()
                && rcNear.div(r, q).gt(Eps);
                manager.incrementIterationCount()) {
            r = Rational.zero();
            x = xx.copy();
            F = F.scalarMultiply(rcNear, Rational.zero());

            for (int i = 0; i < n; i++) {
                KaucherInterval s = ctx.numsToInterval(Rational.zero(), Rational.zero());
                for (int j = 0; j < n; j++) {
                    KaucherInterval g = ctx.numsToInterval(A.getEntry(i, j).inf(), A.getEntry(i, j).sup());
                    KaucherInterval h = ctx.numsToInterval(ExtendedRationalOps.neg(x.getEntry(j)), x.getEntry(j + n));
                    KaucherInterval t = ctx.mul(g, h);
                    s = ctx.add(s, t);
                    DummyUtils.calcSubgrad(F, i, j, g, h);
                }
                KaucherInterval t = ctx.numsToInterval(b.getEntry(i).inf(), b.getEntry(i).sup());

                t = ctx.sub(s, t);

                xx.setEntry(i, RationalOps.neg(t.inf()));
                xx.setEntry(i + n, t.sup());

                r = rcNear.add(r, t.mag());
            }
            xx = new LUDecomposition(rcNear, F).solve(rcNear, xx);
            xx = x.subtract(rcNear, xx.mapMultiply(rcNear, Tau));
            q = xx.getL1Norm(rcNear);
            if (q.le(Rational.valueOf(1.0e-23))) {
                q = Rational.one();
            }
        }

        if (manager.getIterations() == manager.getMaxIterations()) {
            throw new MaxCountExceededException(manager.getMaxIterations());
        }

        IntervalVector result = new IntervalVector(n);
        for (int i = 0; i < n; i++) {
            result.setEntry(i, SetIntervalOps.nums2(xx.getEntry(n + i), ExtendedRationalOps.neg(xx.getEntry(i)), Decoration.COM));
        }
        return result;
    }
}
