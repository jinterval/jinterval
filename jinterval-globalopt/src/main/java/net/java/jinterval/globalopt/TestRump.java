/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package net.java.jinterval.globalopt;

import net.java.jinterval.expression.OptimizationProblem;
import net.java.jinterval.expression.example.RumpExample;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public class TestRump {

    private static String p(SetInterval x) {
        return "[" + x.doubleInf() + "," + x.doubleSup() + "]";
    }

    public static void main(String[] args) {
        OptimizationProblem problem = RumpExample.createOptimzationProblem();
        SetIntervalContext ic = SetIntervalContexts.getDefault();
        double tolerance = 1e180;
        IAOGO algorithm = new IAOGO(problem);
        long startTime = System.currentTimeMillis();
        SetInterval result = algorithm.start(Rational.valueOf(tolerance), ic);
        long stopTime = System.currentTimeMillis();
            System.out.println("tol=" + tolerance
                    + " res=" + p(result) + " time=" + (stopTime - startTime) / 1E3 + "s");
    }

}
