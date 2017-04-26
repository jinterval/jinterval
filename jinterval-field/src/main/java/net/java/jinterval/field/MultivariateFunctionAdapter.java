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
package net.java.jinterval.field;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.OptimizationProblem;
import net.java.jinterval.expression.PrimitiveEvaluators;
import net.java.jinterval.expression.example.FireRisk;
import net.java.jinterval.rational.Rational;
import org.apache.commons.math3.analysis.MultivariateFunction;
import org.apache.commons.math3.optim.InitialGuess;
import org.apache.commons.math3.optim.MaxEval;
import org.apache.commons.math3.optim.MaxIter;
import org.apache.commons.math3.optim.PointValuePair;
import org.apache.commons.math3.optim.nonlinear.scalar.GoalType;
import org.apache.commons.math3.optim.nonlinear.scalar.MultivariateFunctionMappingAdapter;
import org.apache.commons.math3.optim.nonlinear.scalar.ObjectiveFunction;
import org.apache.commons.math3.optim.nonlinear.scalar.noderiv.MultiDirectionalSimplex;
import org.apache.commons.math3.optim.nonlinear.scalar.noderiv.SimplexOptimizer;

/**
 *
 */
public class MultivariateFunctionAdapter implements MultivariateFunction {

    private static boolean debug = false;
    private static int cnt;

    private final OptimizationProblem problem;

    public static boolean setDebug(boolean v) {
        boolean oldDebug = debug;
        debug = v;
        cnt = 0;
        return debug;
    }

    public static PointValuePair optimize(OptimizationProblem problem) {
        MultivariateFunctionMappingAdapter fun = create(problem);
        SimplexOptimizer optimizer = new SimplexOptimizer(0, 1e-7);
        PointValuePair result = optimizer.optimize(
                new ObjectiveFunction(fun),
                GoalType.MINIMIZE,
                new InitialGuess(new double[problem.getNumInps()]),
                new MultiDirectionalSimplex(problem.getNumInps()),
                MaxEval.unlimited(),
                MaxIter.unlimited());
        return new PointValuePair(fun.unboundedToBounded(result.getPoint()), result.getValue());
    }

    public static MultivariateFunctionMappingAdapter create(OptimizationProblem problem) {
        MultivariateFunction unconstrained = new MultivariateFunctionAdapter(problem);
        double[] lower = new double[problem.getNumInps()];
        double[] upper = new double[problem.getNumInps()];
        for (int i = 0; i < problem.getNumInps(); i++) {
            String s = problem.getInpRange(i).trim();
            int comma = s.indexOf(',');
            if (s.startsWith("[") && s.endsWith("]") && comma > 0) {
                lower[i] = Rational.valueOf(s.substring(1, comma)).doubleValue();
                upper[i] = Rational.valueOf(s.substring(comma + 1, s.length() - 1)).doubleValue();
            }
        }
        return new MultivariateFunctionMappingAdapter(unconstrained, lower, upper);
    }

    private MultivariateFunctionAdapter(OptimizationProblem problem) {
        this.problem = problem;
    }

    @Override
    public double value(double[] point) {
        double v = PrimitiveEvaluators.evaluateDouble(problem.getCodeList(), point, problem.getObjective())[0];
        if (debug) {
            System.out.print(cnt++ + ": " + problem.getObjective().name() + "=" + v + " @");
            for (int i = 0; i < problem.getNumInps(); i++) {
                System.out.print(" " + problem.getCodeList().getInp(i).name() + "=" + point[i]);
            }
            System.out.println();
        }
        return v;
    }
}
