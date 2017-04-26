/*
 * Copyright (c) 2016, JInterval Project.
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
package net.java.jinterval.globalopt;

import net.java.jinterval.expression.OptimizationProblem;
import net.java.jinterval.expression.example.FireRisk;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.Rational;

/**
 * @author astronautr
 * @author declow
 */
public class Main {

    private static OptimizationProblem createProblemFireRisk1() {
        return FireRisk.createOptimizationProblem(FireRisk.From.a_b_theta, FireRisk.To.F, false);
    }

    private static OptimizationProblem createProblemFireRisk2() {
        return FireRisk.createOptimizationProblem(FireRisk.From.L_d_theta, FireRisk.To.Fv, false);
    }

    private static OptimizationProblem createProblemFireRisk3() {
        return FireRisk.createOptimizationProblem(FireRisk.From.tpac_T_uw_d, FireRisk.To.Fsqr, true);
    }

    private static String p(SetInterval x) {
        return "[" + x.doubleInf() + "," + x.doubleSup() + "]";
    }

    private static void test(String msg, SetIntervalContext ic, double... tolerances) {
        System.out.println(msg);
        OptimizationProblem problem = createProblemFireRisk2();
        for (double tolerance : tolerances) {
            long startTime = System.currentTimeMillis();
            IAOGO algorithm = new IAOGO(problem);
            //Now we'll launch basic version of interval algorithm of global optimization for chosen objective function,
            //interval box, tolerance and Context (ic)
            SetInterval result = algorithm.start(Rational.valueOf(tolerance), ic);
            long stopTime = System.currentTimeMillis();
            System.out.println("tol=" + tolerance
                    + " res=" + p(result) + " time=" + (stopTime - startTime) / 1E3 + "s");
        }
    }

    public static void main(String[] args) {
        switch (1) {
            case 1:
                test("default", null, 1E-6, 1E-7, 1E-8, 1E-9);
                break;
            case 2:
                test("getPlain()", SetIntervalContexts.getPlain(), 1E-6, 1E-7, 1E-8, 1E-9);
                break;
            case 3:
                test("getAccur64()", SetIntervalContexts.getAccur64(), 1E-6, 1E-7, 1E-8, 1E-9);
                break;
            case 4:
                test("getDoubleNearest()", SetIntervalContexts.getDoubleNearest(), 1E-6, 1E-7, 1E-8, 1E-9);
                break;
            case 5:
                test("getInfSup(BinaryValueSet.BINARY32)", SetIntervalContexts.getTightest(BinaryValueSet.BINARY32), 1E-2, 1E-3, 1E-4, 1E-5);
                break;
            case 6:
                test("getInfSup(BinaryValueSet.BINARY64)", SetIntervalContexts.getTightest(BinaryValueSet.BINARY64), 1E-10, 1E-11, 1E-12, 1E-13);
                break;
            case 7:
                test("getInfSup(BinaryValueSet.BINARY80)", SetIntervalContexts.getTightest(BinaryValueSet.BINARY80), 1E-10, 1E-11, 1E-12, 1E-13, 1E-14, 1E-15, 1E-16, 1E-17);
                break;
            case 8:
                test("getInfSup(BinaryValueSet.BINARY128)", SetIntervalContexts.getTightest(BinaryValueSet.BINARY128), 1E-3, 1E-4, 1E-5);
                break;
        }
    }
}
/*
createProblemFireRisk2
1E-3 0.005000334788230935 1:02
1E-6 0.005116286377372573 1:08
1E-9 0.005116288077828106 1:03

default bare
numSteps=261020 tinyList.size=0 wList.size=9294 interesting=21
tol=1.0E-6 res=[0.005115307837974507,0.005116288077829898] time=28.517s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=2
tol=1.0E-7 res=[0.005116279734958647,0.005116288077829898] time=27.777s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=2
tol=1.0E-8 res=[0.005116279734958647,0.005116288077829898] time=27.752s
numSteps=261020 tinyList.size=0 wList.size=9274 interesting=1
tol=1.0E-9 res=[0.00511628807782963,0.005116288077829898] time=27.733s

default both
numSteps=261020 tinyList.size=0 wList.size=9294 interesting=21
tol=1.0E-6 res=[0.005115307837974507,0.005116288077829898] time=114.309s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=2
tol=1.0E-7 res=[0.005116279734958647,0.005116288077829898] time=105.921s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=2
tol=1.0E-8 res=[0.005116279734958647,0.005116288077829898] time=106.164s
numSteps=261020 tinyList.size=0 wList.size=9274 interesting=1
tol=1.0E-9 res=[0.00511628807782963,0.005116288077829898] time=106.141s

getPlain()
numSteps=261020 tinyList.size=0 wList.size=9294 interesting=20
tol=1.0E-6 res=[0.005115307837974729,0.005116288077829761] time=27.232s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=1
tol=1.0E-7 res=[0.005116279734959234,0.005116288077829761] time=27.066s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=1
tol=1.0E-8 res=[0.005116279734959234,0.005116288077829761] time=26.612s
numSteps=261020 tinyList.size=0 wList.size=9274 interesting=0
tol=1.0E-9 res=[0.005116288077829761,0.005116288077829761] time=26.634s

getAccur64()
numSteps=261020 tinyList.size=0 wList.size=9294 interesting=21
tol=1.0E-6 res=[0.005115307837974507,0.005116288077829898] time=28.979s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=2
tol=1.0E-7 res=[0.005116279734958647,0.005116288077829898] time=28.733s
numSteps=261020 tinyList.size=0 wList.size=9275 interesting=2
tol=1.0E-8 res=[0.005116279734958647,0.005116288077829898] time=28.666s
numSteps=261020 tinyList.size=0 wList.size=9274 interesting=1
tol=1.0E-9 res=[0.00511628807782963,0.005116288077829898] time=28.826s

getDoubleNearest()
numSteps=261020 tinyList.size=0 wList.size=9294 interesting=20
tol=1.0E-6 res=[0.005115307837974689,0.005116288077829761] time=1184.816s

*/
/*
createProblemFireRisk3

default without Decorations
numSteps=473497 tinyList.size=0 wList.size=236749 interesting=236749
tol=0.1 res=[-0.10598550808910248,-0.00598573751647179] time=67.951s

plain without Decorations
getPlain()
numSteps=473497 tinyList.size=0 wList.size=236749 interesting=236749
tol=0.1 res=[-0.10598550808909823,-0.0059857375164736205] time=206.479s

getAccur64() without Decorations
numSteps=473497 tinyList.size=0 wList.size=236749 interesting=236749
tol=0.1 res=[-0.10598550808910248,-0.00598573751647179] time=66.979s

getAccur64() with Decorations
numSteps=473497 tinyList.size=0 wList.size=236749 interesting=236749
tol=0.1 res=[-0.10598550808910248,-0.00598573751647179] time=156.215s
*/

/*
getPlain()
tol=0.001 res=6.605350712421185 time=0.348s
tol=1.0E-4 res=6.605631967925461 time=0.97s
tol=1.0E-5 res=6.605658079647924 time=3.391s
tol=1.0E-6 res=6.605660197332313 time=13.963s
tol=1.0E-7 res=6.605660471995435 time=59.798s

getAccur64()
tol=0.001 res=6.605350712421142 time=0.452s
tol=1.0E-4 res=6.605631967925433 time=1.316s
tol=1.0E-5 res=6.605658079647881 time=5.193s
tol=1.0E-6 res=6.605660197332298 time=12.198s
tol=1.0E-7 res=6.605660471995392 time=64.552s

getDoubleNearest()
tol=0.001 res=6.605350712421185 time=7.383s
tol=1.0E-4 res=6.605631967925461 time=22.374s
tol=1.0E-5 res=6.605658079647924 time=78.629s

getInfSup(BinaryValueSet.BINARY32)
tol=0.001 res=6.605316162109375 time=13.715s
tol=1.0E-4 res=6.605613708496094 time=49.812s

getInfSup(BinaryValueSet.BINARY64)
tol=0.001 res=6.605350712421142 time=13.848s
tol=1.0E-4 res=6.605631967925433 time=43.487s
tol=1.0E-5 res=6.605658079647881 time=148.704s

getInfSup(BinaryValueSet.BINARY80)
tol=0.001 res=6.605350712421182 time=19.449s
tol=1.0E-4 res=6.605631967925464 time=63.268s
tol=1.0E-5 res=6.605658079647916 time=216.264s

getInfSup(BinaryValueSet.BINARY128)
tol=0.001 res=6.605350712421182 time=25.426s
tol=1.0E-4 res=6.605631967925464 time=78.118s
tol=1.0E-5 res=6.605658079647917 time=264.028s
 */
