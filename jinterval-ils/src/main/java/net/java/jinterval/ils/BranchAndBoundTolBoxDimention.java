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

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalOps;
import org.apache.commons.math3.exception.DimensionMismatchException;
import org.apache.commons.math3.exception.NullArgumentException;
import org.apache.commons.math3.linear.NonSquareOperatorException;
import org.apache.commons.math3.util.MathUtils;

public class BranchAndBoundTolBoxDimention {

    private class Theta {

        private ExtendedRational[] arguments;
        private ExtendedRational maxValue;

        public Theta(IntervalVector rowA) {
            this.CalculateTheta(rowA);
        }

        public Theta(ExtendedRational[] arguments) {
            this.RecalculateTheta(arguments);
        }

        public ExtendedRational[] getArguments() {
            return arguments;
        }

        public ExtendedRational getMaxValue() {
            return maxValue;
        }

        private void CalculateTheta(IntervalVector rowA) {
            ExtendedRational summOfLocalMaxTheta = ExtendedRational.zero();
            int n = rowA.getDimension();
            ExtendedRational[] argLocalMaxTheta = new ExtendedRational[n];

            for (int index = 0; index < n; index++) {
                ExtendedRational infRowA = rowA.getEntry(index).inf();
                ExtendedRational supRowA = rowA.getEntry(index).sup();
                infRowA = ExtendedRationalOps.abs(infRowA);
                supRowA = ExtendedRationalOps.abs(supRowA);

                if (infRowA.compareTo(supRowA) == -1) {
                    summOfLocalMaxTheta = ExtendedRationalOps.add(summOfLocalMaxTheta, supRowA);
                    argLocalMaxTheta[index] = supRowA;
                } else {
                    summOfLocalMaxTheta = ExtendedRationalOps.add(summOfLocalMaxTheta, infRowA);
                    argLocalMaxTheta[index] = infRowA;
                }
            }

            this.arguments = argLocalMaxTheta;
            this.maxValue = summOfLocalMaxTheta;
        }

        private void RecalculateTheta(ExtendedRational[] arguments) {
            ExtendedRational summOfNewLocalMaxTheta = ExtendedRational.zero();
            for (int index = 0; index < arguments.length; index++) {
                summOfNewLocalMaxTheta = ExtendedRationalOps.add(summOfNewLocalMaxTheta, arguments[index]);
            }

            this.arguments = arguments;
            this.maxValue = summOfNewLocalMaxTheta;
        }
    }

    private class Psi {

        private ExtendedRational[] arguments;
        private ExtendedRational minValue;

        public Psi(IntervalVector rowA, SetInterval b, ExtendedRational[] center) {
            this.CalculatePsi(rowA, b, center);
        }

        public Psi(ExtendedRational[] arguments, SetInterval b, ExtendedRational[] center) {
            this.RecalculatePsi(arguments, b, center);
        }

        public ExtendedRational[] getArguments() {
            return arguments;
        }

        public ExtendedRational getMinValue() {
            return minValue;
        }

        private void CalculatePsi(IntervalVector rowA, SetInterval b, ExtendedRational[] center) {
            ExtendedRational summOfLocalMinPsiForMaxValue = ExtendedRational.zero();
            ExtendedRational summOfLocalMinPsiForMinValue = ExtendedRational.zero();

            ExtendedRational radB = b.rad();
            ExtendedRational midB = b.mid();

            int n = rowA.getDimension();

            ExtendedRational[] argOfLocalMinPsiForMaxValue = new ExtendedRational[n];
            ExtendedRational[] argOfLocalMinPsiForMinValue = new ExtendedRational[n];

            for (int index = 0; index < n; index++) {
                ExtendedRational infRowA = rowA.getEntry(index).inf();
                ExtendedRational supRowA = rowA.getEntry(index).sup();

                infRowA = ExtendedRationalOps.mul(infRowA, center[index]);
                supRowA = ExtendedRationalOps.mul(supRowA, center[index]);

                if (center[index].signum() == 1) {
                    summOfLocalMinPsiForMinValue = ExtendedRationalOps.add(summOfLocalMinPsiForMinValue, infRowA);
                    summOfLocalMinPsiForMaxValue = ExtendedRationalOps.add(summOfLocalMinPsiForMaxValue, supRowA);

                    argOfLocalMinPsiForMinValue[index] = infRowA;
                    argOfLocalMinPsiForMaxValue[index] = supRowA;
                } else {
                    summOfLocalMinPsiForMinValue = ExtendedRationalOps.add(summOfLocalMinPsiForMinValue, supRowA);
                    summOfLocalMinPsiForMaxValue = ExtendedRationalOps.add(summOfLocalMinPsiForMaxValue, infRowA);

                    argOfLocalMinPsiForMinValue[index] = supRowA;
                    argOfLocalMinPsiForMaxValue[index] = infRowA;
                }
            }

            ExtendedRational absForMaxValue = ExtendedRationalOps.sub(midB, summOfLocalMinPsiForMaxValue);
            ExtendedRational absForMinValue = ExtendedRationalOps.sub(midB, summOfLocalMinPsiForMinValue);

            absForMaxValue = ExtendedRationalOps.abs(absForMaxValue);
            absForMinValue = ExtendedRationalOps.abs(absForMinValue);

            if (absForMaxValue.compareTo(absForMinValue) == 1) {
                this.minValue = ExtendedRationalOps.sub(radB, absForMaxValue);
                this.arguments = argOfLocalMinPsiForMaxValue;
            } else {
                this.minValue = ExtendedRationalOps.sub(radB, absForMinValue);
                this.arguments = argOfLocalMinPsiForMinValue;
            }
        }

        private void RecalculatePsi(ExtendedRational[] arguments, SetInterval b, ExtendedRational[] center) {
            ExtendedRational summOfNewLocalMinPsi = ExtendedRational.zero();
            ExtendedRational radB = b.rad();
            ExtendedRational midB = b.mid();

            for (int index = 0; index < arguments.length; index++) {
                ExtendedRational argumentsComponent = arguments[index];
                argumentsComponent = ExtendedRationalOps.mul(argumentsComponent, center[index]);

                summOfNewLocalMinPsi = ExtendedRationalOps.add(summOfNewLocalMinPsi, argumentsComponent);
            }

            summOfNewLocalMinPsi = ExtendedRationalOps.sub(midB, summOfNewLocalMinPsi);
            summOfNewLocalMinPsi = ExtendedRationalOps.abs(summOfNewLocalMinPsi);
            summOfNewLocalMinPsi = ExtendedRationalOps.sub(radB, summOfNewLocalMinPsi);

            this.arguments = arguments;
            this.minValue = summOfNewLocalMinPsi;
        }
    }
    private ExtendedRational[] radiuses;
    private IntervalVector box;
    private boolean debug;

    public ExtendedRational[] getRadiuses() {
        return this.radiuses;
    }

    public IntervalVector getBox() {
        return this.box;
    }

    public BranchAndBoundTolBoxDimention(IntervalMatrix a, IntervalVector b, ExtendedRational[] center, boolean debug) {
        this.debug = debug;

        int countOfRows = a.getRowDimension();
        this.radiuses = new ExtendedRational[countOfRows];
        for (int index = 0; index < countOfRows; index++) {
            ExtendedRational localRadius = this.CalculateLocalRadius(a.getRow(index), b.getEntry(index), center);
            this.radiuses[index] = localRadius;
        }

        this.BuildBox(center);
    }

    public BranchAndBoundTolBoxDimention(IntervalMatrix a, IntervalVector b, ExtendedRational[] center) {
        this(a, b, center, false);
    }

    private void BuildBox(ExtendedRational[] center) {
        int rowCount = this.radiuses.length;
        this.box = new IntervalVector(rowCount);
        SetInterval e = SetIntervalOps.nums2(-1, 1);

        for (int index = 0; index < rowCount; index++) {
            SetInterval radiusInterval = SetIntervalOps.nums2(this.radiuses[index], this.radiuses[index]);
            SetInterval centerInterval = SetIntervalOps.nums2(center[index], center[index]);

            SetInterval boxComponent = SetIntervalOps.mul(radiusInterval, e);
            boxComponent = SetIntervalOps.add(centerInterval, boxComponent);

            if (this.debug) {
                System.out.println("i: " + index + " boxComponent: " + boxComponent);
            }

            this.box.setEntry(index, boxComponent);
        }
    }

    protected static void checkParameters(IntervalMatrix a, IntervalVector b) throws
            NullArgumentException, NonSquareOperatorException, DimensionMismatchException {
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

    private int CompareArguments(ExtendedRational[] argOfLocalMinPsi, ExtendedRational[] argLocalOfMaxTheta) {
        int countOfArguments = argLocalOfMaxTheta.length;

        for (int index = 0; index < countOfArguments; index++) {
            ExtendedRational psiArg = argOfLocalMinPsi[index];
            ExtendedRational thetaArg = argLocalOfMaxTheta[index];

            if (psiArg.compareTo(thetaArg) != 0) {
                return index;
            }
        }

        return -1;
    }

    private ExtendedRational CreateNodeTheta(Theta prevTheta, ExtendedRational[] incedentPsiArgs, SetInterval b, ExtendedRational[] center) {
        Psi psi = new Psi(incedentPsiArgs, b, center);

        int result = this.CompareArguments(psi.getArguments(), prevTheta.getArguments());

        if (result != -1) {
            ExtendedRational[] incedentThetaArguments = prevTheta.getArguments().clone();
            ExtendedRational[] incedentPsiArguments = psi.getArguments().clone();

            incedentThetaArguments[result] = psi.getArguments()[result];
            incedentPsiArguments[result] = prevTheta.getArguments()[result];

            ExtendedRational firstFiValue = this.CreateNodeTheta(prevTheta, incedentPsiArguments, b, center);
            ExtendedRational secondFiValue = this.CreateNodePsi(psi, incedentThetaArguments, b, center);

            if (firstFiValue.compareTo(secondFiValue) == 1) {
                return firstFiValue;
            } else {
                return secondFiValue;
            }
        } else {
            ExtendedRational fiValue = ExtendedRationalOps.div(psi.getMinValue(), prevTheta.getMaxValue());
            return fiValue;
        }
    }

    private ExtendedRational CreateNodePsi(Psi prevPsi, ExtendedRational[] incedentThetaArgs, SetInterval b, ExtendedRational[] center) {
        Theta theta = new Theta(incedentThetaArgs);

        int result = this.CompareArguments(prevPsi.getArguments(), theta.getArguments());

        if (result != -1) {
            ExtendedRational[] incedentThetaArguments = theta.getArguments().clone();
            ExtendedRational[] incedentPsiArguments = prevPsi.getArguments().clone();

            incedentThetaArguments[result] = prevPsi.getArguments()[result];
            incedentPsiArguments[result] = theta.getArguments()[result];

            ExtendedRational firstFiValue = this.CreateNodeTheta(theta, incedentPsiArguments, b, center);
            ExtendedRational secondFiValue = this.CreateNodePsi(prevPsi, incedentThetaArguments, b, center);

            if (firstFiValue.compareTo(secondFiValue) == 1) {
                return firstFiValue;
            } else {
                return secondFiValue;
            }
        } else {
            ExtendedRational fiValue = ExtendedRationalOps.div(prevPsi.getMinValue(), theta.getMaxValue());
            return fiValue;
        }

    }

    private ExtendedRational CalculateLocalRadius(IntervalVector rowA, SetInterval b, ExtendedRational[] center) {
        Theta theta = new Theta(rowA);
        Psi psi = new Psi(rowA, b, center);

        int result = this.CompareArguments(theta.getArguments(), psi.getArguments());

        if (result != -1) {
            ExtendedRational[] incedentThetaArguments = theta.getArguments().clone();
            ExtendedRational[] incedentPsiArguments = psi.getArguments().clone();

            incedentThetaArguments[result] = psi.getArguments()[result];
            incedentPsiArguments[result] = theta.getArguments()[result];

            ExtendedRational firstFiValue = this.CreateNodeTheta(theta, incedentPsiArguments, b, center);
            ExtendedRational secondFiValue = this.CreateNodePsi(psi, incedentThetaArguments, b, center);

            if (firstFiValue.compareTo(secondFiValue) == 1) {
                return firstFiValue;
            } else {
                return secondFiValue;
            }
        } else {
            ExtendedRational fiValue = ExtendedRationalOps.div(psi.getMinValue(), theta.getMaxValue());
            return fiValue;
        }
    }
}
