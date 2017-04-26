/*
 * Copyright (c) 2012, JInterval Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. * Redistributions in
 * binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
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
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.p1788;

import java.math.BigInteger;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.text2interval.gen.GenP1788Base;

/**
 *
 */
public class TestPrinter {

    private static final boolean WR_TST = true;
    private static final boolean WR_C = false;
    private static int testNo;

    private static void printTestHead(String testName, Operation op) {
        if (WR_TST) {
            System.out.print("test g00.l" + testName + " { " + op + "<infsup<b64>>");
        }
        if (WR_C) {
            System.out.println("BOOST_AUTO_TEST_CASE(g00_l" + testName + ")");
            System.out.println("{");
            System.out.print("    BOOST_CHECK_EQUAL( ");
            for (char ch : op.name().toCharArray()) {
                if (Character.isUpperCase(ch)) {
                    System.out.print("_" + Character.toLowerCase(ch));
                } else {
                    System.out.print(ch);
                }
            }
        }
    }

    private static void printCInterval(SetInterval a) {
        System.out.print("I<double>");
        if (a.isEmpty()) {
            System.out.print("::empty()");
        } else {
            System.out.print("(");
            if (a.inf().isNegativeInfinity()) {
                System.out.print("-std::numeric_limits<double>::infinity()");
            } else {
                System.out.print(a.inf().toString());
            }
            System.out.print(",");
            if (a.sup().isPositiveInfinity()) {
                System.out.print("std::numeric_limits<double>::infinity()");
            } else {
                System.out.print(a.sup().toString());
            }
            System.out.print(")");
        }
    }

    private static void printArgInterval(boolean first, SetInterval a) {
        if (WR_TST) {
            System.out.print(" " + a);
        }
        if (WR_C) {
            System.out.print(first ? "(" : ", ");
            printCInterval(a);
        }
    }

    private static void printArgInt(BigInteger a) {
        if (WR_TST) {
            System.out.print(" " + a);
        }
    }

    private static void printArgS(String a) {
        if (WR_TST) {
            System.out.print(" \"" + a + "\"");
        }
    }

    private static void printTightestResult(SetInterval r) {
        if (WR_TST) {
            System.out.print(" = " + r);
        }
        if (WR_C) {
            System.out.print("), ");
            printCInterval(r);
            System.out.println(" );");
            System.out.println("}");
            System.out.println();
        }
    }

    private static void printAccurateResult(SetInterval r) {
        if (WR_TST) {
            System.out.println(" <= " + r + " }");
        }
    }

    static void printLine(Object[] argsJ, Operation op, Object[] tightestRes, Object[] accurateRes) {
        GenP1788Base.Operation oper = op.getBaseOperation();
        int nRes = oper.results.length;
        int nArg = oper.args.length;
        String testName = Integer.toString(testNo++);
        while (testName.length() < 4) {
            testName = "0" + testName;
        }
        printTestHead(testName, op);
        for (int i = 0; i < nArg; i++) {
            switch (oper.args[i]) {
                case INTERVAL: {
                    SetInterval a = (SetInterval) argsJ[i];
                    if (a.isNaI()) {
                        System.out.println("NAI");
                        return;
                    }
                    printArgInterval(i == 0, a);
                }
                break;
//                case POINT:
//                    break;
                case INT: {
                    BigInteger a = (BigInteger) argsJ[i];
                    printArgInt(a);
                }
                break;
//                case DEC:
//                    break;
//                case OVERLAP:
//                    break;
                case TEXT: {
                    String a = (String) argsJ[i];
                    printArgS(a);
                }
                break;
//                case BOOL:
//                    break;
//                case LEN:
//                    break;
//                case POINT_ARRAY:
//                    break;
                default:
                    throw new AssertionError(oper.args[i].name());
            }
        }
        for (int i = 0; i < nRes; i++) {
            if (tightestRes[i] instanceof SetInterval) {
                printTightestResult((SetInterval) tightestRes[i]);
            }
        }
        for (int i = 0; i < nRes; i++) {
            if (accurateRes[i] instanceof SetInterval) {
                printAccurateResult((SetInterval) accurateRes[i]);
            }
        }
    }

}
