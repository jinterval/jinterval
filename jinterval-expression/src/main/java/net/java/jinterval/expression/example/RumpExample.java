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
package net.java.jinterval.expression.example;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.expression.ExpressionPrinter;
import net.java.jinterval.expression.OptimizationProblem;
import net.java.jinterval.expression.PrimitiveEvaluators;

/**
 *
 */
public class RumpExample {

    /**
     * Original Rump's example. Rump, S.M.: Algorithms for Verified Inclusions:
     * Theory and Practice, in: Moore, R.E. (ed.). Reliability in Computing: The
     * Role of Interval Methods in Scientific Computing, chapter 1, Computer
     * Arithmetic and Mathematical Software, Academic Press, Boston, 1988, pp.
     * 109-126. This is formula (1.1) in "Revisited Rump's example"
     *
     * @return original Rump's example
     */
    public static Expression createOriginal() {
        CodeList rump = CodeList.create("a", "b");
        Expression a = rump.getInp(0);
        Expression b = rump.getInp(1);
        Expression c333_75 = rump.lit("333.75").name("c333_75");
        Expression c11 = rump.lit("11").name("c11");
        Expression c121 = rump.lit("121").name("c121");
        Expression c2 = rump.lit("2").name("c2");
        Expression c5_5 = rump.lit("5.5").name("c5_5");
        return c333_75.mul(b.pown(6))
                .add(a.pown(2).mul(
                        c11.mul(a.pown(2)).mul(b.pown(2))
                        .sub(b.pown(6))
                        .sub(c121.mul(b.pown(4)))
                        .sub(c2)))
                .add(c5_5.mul(b.pown(8)))
                .add(a.div(c2.mul(b)))
                .name("originalRump");
    }

    /**
     * Revisited Rump's example. Eugene Loh and G. William Walster. Rump's
     * Example Revisited. Reliable Computing, 8:245-248, 2002. Kluwer Academic
     * Publishers, Netherlands. This is formula (1.4) in "Revisited Rump's
     * example"
     *
     * @return revisited Rump's example
     */
    public static Expression createRevisited() {
        CodeList rump = CodeList.create("a", "b");
        Expression a = rump.getInp(0);
        Expression b = rump.getInp(1);
        Expression c333_75 = rump.lit("333.75").name("c333_75");
        Expression c11 = rump.lit("11").name("c11");
        Expression c121 = rump.lit("121").name("c121");
        Expression c2 = rump.lit("2").name("c2");
        Expression c5_5 = rump.lit("5.5").name("c5_5");
        return c333_75.sub(a.pown(2)).mul(b.pown(6)).name("term1")
                .add(a.pown(2).mul(
                        c11.mul(a.pown(2)).mul(b.pown(2))
                        .sub(c121.mul(b.pown(4)))
                        .sub(c2)).name("term2"))
                .add(c5_5.mul(b.pown(8)).name("term3"))
                .add(a.div(c2.mul(b)).name("term4"))
                .name("revisitedRump");
    }

    public static OptimizationProblem createOptimzationProblem() {
        String[] box = {"[0,77617]", "[33096,1e30]"};
        return new OptimizationProblem(createRevisited(), box);
    }

    public static void main(String[] args) {
        Expression e = createRevisited();
        ExpressionPrinter.printGradient(System.out, e);
        float[] floatArgs = {77617, 33096};
        double[] doubleArgs = {77617, 33096};
        System.out.println("evaluateFloat " + PrimitiveEvaluators.evaluateFloat(e.getCodeList(), floatArgs, e)[0]);
        System.out.println("evaluateDouble " + PrimitiveEvaluators.evaluateDouble(e.getCodeList(), doubleArgs, e)[0]);
    }
}
