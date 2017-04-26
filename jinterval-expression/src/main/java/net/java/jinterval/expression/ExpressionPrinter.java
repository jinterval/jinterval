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
package net.java.jinterval.expression;

import java.io.PrintStream;

/**
 *
 */
public abstract class ExpressionPrinter extends AbstractExpressionVisitor {

    private enum Kind {
        Dbl, Rat, Intvl, Grad
    };

    private final CodeList cl;
    private PrintStream out;
    private int indent;

    void nl(String msg) {
        out.println();
        for (int i = 0; i < indent; i++) {
            out.print(" ");
        }
        out.print(msg);
    }

    private ExpressionPrinter(CodeList cl) {
        this.cl = cl;
    }

    public static void printDouble(PrintStream out, Expression e) {
        ExpressionPrinter ep = new ExpressionPrinter.Double(e.getCodeList());
        ep.print(out, e);
    }

    public static void printRational(PrintStream out, Expression e) {
        ExpressionPrinter ep = new ExpressionPrinter.Rational(e.getCodeList());
        ep.print(out, e);
    }

    public static void printInterval(PrintStream out, Expression e) {
        ExpressionPrinter ep = new ExpressionPrinter.Interval(e.getCodeList());
        ep.print(out, e);
    }

    public static void printGradient(PrintStream out, Expression e) {
        ExpressionPrinter ep = new ExpressionPrinter.Gradient(e.getCodeList());
        ep.print(out, e);
    }

    abstract void printSignature(String name);

    private void print(PrintStream out, Expression e) {
        if (e.getCodeList() != cl) {
            throw new IllegalArgumentException();
        }
        this.out = out;
        indent = 0;
        try {
            indent += 4;
            printSignature(e.name());
            indent += 4;

            cl.acceptConstants(this);
            cl.acceptForward(this);
            nl("return " + name(e.getIndex()) + ";");

            indent -= 4;
            nl("}");
            indent -= 4;
            out.println();
        } finally {
            this.out = null;
        }
    }

    String name(int x) {
        Expression ex = cl.getExpr(x);
        String s = ex.name();
        if (s == null) {
            s = "_" + ex.getIndex();
        }
        return s;
    }

    private static class Double extends ExpressionPrinter {

        Double(CodeList cl) {
            super(cl);
        }

        @Override
        void printSignature(String name) {
            nl("public double " + name + "(double[] inps) {");
        }

        @Override
        public void visitInp(int r, String name) {
            nl("double " + name(r) + " = inps[" + r + "];");
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            nl("double " + name(r) + " = " + numerator + " / " + denominator + ";");
        }

        @Override
        public void visitLit(int r, String literal) {
            nl("double " + name(r) + " = " + literal + ";");
        }

        @Override
        public void visitInterval(int r, String inf, String sup) {
            nl("double " + name(r) + " = 0.5*" + inf + " + 0.5*" + sup + ";");
        }

        @Override
        public void visitNum(int r, Number num) {
            nl("double " + name(r) + " = " + num + ";");
        }

        @Override
        public void visitPi(int r) {
            nl("double " + name(r) + " = Math.PI;");
        }

        @Override
        public void visitEuler(int r) {
            nl("double " + name(r) + " = Math.E;");
        }

        @Override
        public void visitNeg(int r, int x) {
            nl("double " + name(r) + " = -" + name(x) + ";");
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            nl("double " + name(r) + " = " + name(x) + " + " + name(y) + ";");
        }

        @Override
        public void visitSub(int r, int x, int y) {
            nl("double " + name(r) + " = " + name(x) + " - " + name(y) + ";");
        }

        @Override
        public void visitMul(int r, int x, int y) {
            nl("double " + name(r) + " = " + name(x) + " * " + name(y) + ";");
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            nl("double " + name(r) + " = " + name(x) + " / " + name(y) + ";");
        }

        @Override
        public void visitRecip(int r, int x) {
            nl("double " + name(r) + " = 1 / " + name(x) + ";");
        }

        @Override
        public void visitSqr(int r, int x) {
            nl("double " + name(r) + " = " + name(x) + " * " + name(x) + ";");
        }

        @Override
        public void visitSqrt(int r, int x) {
            nl("double " + name(r) + " = Math.sqrt(" + name(x) + ");");
        }

        @Override
        public void visitPown(int r, int x, int p) {
            nl("double " + name(r) + " = Math.pow(" + name(x) + ", " + p + ");");
        }

        @Override
        public void visitPow(int r, int x, int y) {
            nl("double " + name(r) + " = Math.pow(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitSin(int r, int x) {
            nl("double " + name(r) + " = Math.sin(" + name(x) + ");");
        }

        @Override
        public void visitCos(int r, int x) {
            nl("double " + name(r) + " = Math.cos(" + name(x) + ");");
        }

        @Override
        public void visitTan(int r, int x) {
            nl("double " + name(r) + " = Math.tan(" + name(x) + ");");
        }

        @Override
        public void visitAsin(int r, int x) {
            nl("double " + name(r) + " = Math.asin(" + name(x) + ");");
        }

        @Override
        public void visitAcos(int r, int x) {
            nl("double " + name(r) + " = Math.acos(" + name(x) + ");");
        }

        @Override
        public void visitAtan(int r, int x) {
            nl("double " + name(r) + " = Math.atan(" + name(x) + ");");
        }

        @Override
        public void visitRootn(int r, int x, int q) {
            nl("double " + name(r) + " = Math.pow(" + name(x) + ", 1 / (double)" + q + ");");
        }
    }

    private static class Rational extends ExpressionPrinter {

        Rational(CodeList cl) {
            super(cl);
        }

        @Override
        void printSignature(String name) {
            nl("public ExtendedRational " + name + "(ExtendedRationalContext rc, RationalContext[] inps) {");
        }

        @Override
        public void visitInp(int r, String name) {
            nl("ExtendedRational " + name(r) + " = inps[" + r + "];");
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            nl("ExtendedRational " + name(r) + " = rc.rnd(Rational.valueOf(\"" + numerator + "/" + denominator + "\"));");
        }

        @Override
        public void visitLit(int r, String literal) {
            nl("ExtendedRational " + name(r) + " = rc.rnd(Rational.valueOf(\"" + literal + "\"));");
        }

        @Override
        public void visitInterval(int r, String inf, String sup) {
            nl("ExtendedRational " + name(r) + " = rc.mul(Rational.exp2(-1), rc.add(ExtendedRational.valueOf(\"" + inf + "\"), ExtendedRational.valueOf(\"" + sup + "\")));");
        }

        @Override
        public void visitNum(int r, Number num) {
            nl("Rational " + name(r) + " = rc.rnd(" + num + ");");
        }

        @Override
        public void visitPi(int r) {
            nl("Rational " + name(r) + " = rc.pi();");
        }

        @Override
        public void visitEuler(int r) {
            nl("Rational " + name(r) + " = rc.euler();");
        }

        @Override
        public void visitNeg(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.neg(" + name(x) + ");");
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            nl("ExtendedRational " + name(r) + " = rc.add(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitSub(int r, int x, int y) {
            nl("ExtendedRational " + name(r) + " = rc.sub(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitMul(int r, int x, int y) {
            nl("ExtendedRational " + name(r) + " = rc.mul(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            nl("ExtendedRational " + name(r) + " = rc.div(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitRecip(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.recip(" + name(x) + ");");
        }

        @Override
        public void visitSqr(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.sqr(" + name(x) + ");");
        }

        @Override
        public void visitSqrt(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.sqrt(" + name(x) + ");");
        }

        @Override
        public void visitFma(int r, int x, int y, int z) {
            nl("ExtendedRational " + name(r) + " = rc.fma(" + name(x) + ", " + name(y) + ", " + name(z) + ");");
        }

        @Override
        public void visitPown(int r, int x, int p) {
            nl("ExtendedRational " + name(r) + " = rc.pown(" + name(x) + ", " + p + ");");
        }

        @Override
        public void visitPow(int r, int x, int y) {
            nl("ExtendedRational " + name(r) + " = rc.pow(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitSin(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.sin(" + name(x) + ");");
        }

        @Override
        public void visitCos(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.cos(" + name(x) + ");");
        }

        @Override
        public void visitTan(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.tan(" + name(x) + ");");
        }

        @Override
        public void visitAsin(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.asin(" + name(x) + ");");
        }

        @Override
        public void visitAcos(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.acos(" + name(x) + ");");
        }

        @Override
        public void visitAtan(int r, int x) {
            nl("ExtendedRational " + name(r) + " = rc.atan(" + name(x) + ");");
        }

        @Override
        public void visitRootn(int r, int x, int q) {
            nl("ExtendedRational " + name(r) + " = rc.rootn(" + name(x) + ", " + q + ");");
        }
    }

    private static class Interval extends ExpressionPrinter {

        Interval(CodeList cl) {
            super(cl);
        }

        @Override
        void printSignature(String name) {
            nl("public SetInterval " + name + "(SetIntervalContext ic, SetInterval[] inps) {");
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            nl("SetInterval " + name(r) + " = ic.textToInterval(\"" + numerator + "/" + denominator + "\");");
        }

        @Override
        public void visitLit(int r, String literal) {
            nl("SetInterval " + name(r) + " = ic.textToInterval(\"" + literal + "\");");
        }

        @Override
        public void visitInterval(int r, String inf, String sup) {
            nl("SetInterval " + name(r) + " = ic.textToInterval(\"[" + inf + "," + sup + "]\");");
        }

        @Override
        public void visitInp(int r, String name) {
            nl("SetInterval " + name(r) + " = inps[" + r + "];");
        }

        @Override
        public void visitNum(int r, Number num) {
            nl("SetInterval " + name(r) + " = ic.numsToInterval(" + num + ", " + num + ");");
        }

        @Override
        public void visitPi(int r) {
            nl("SetInterval " + name(r) + " = ic.pi();");
        }

        @Override
        public void visitEuler(int r) {
            nl("SetInterval " + name(r) + " = ic.euler();");
        }

        @Override
        public void visitNeg(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.neg(" + name(x) + ");");
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            nl("SetInterval " + name(r) + " = ic.add(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitSub(int r, int x, int y) {
            nl("SetInterval " + name(r) + " = ic.sub(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitMul(int r, int x, int y) {
            nl("SetInterval " + name(r) + " = ic.mul(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            nl("SetInterval " + name(r) + " = ic.div(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitRecip(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.recip(" + name(x) + ");");
        }

        @Override
        public void visitSqr(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.sqr(" + name(x) + ");");
        }

        @Override
        public void visitSqrt(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.sqrt(" + name(x) + ");");
        }

        @Override
        public void visitFma(int r, int x, int y, int z) {
            nl("ExtendedRational " + name(r) + " = ic.fma(" + name(x) + ", " + name(y) + ", " + name(z) + ");");
        }

        @Override
        public void visitPown(int r, int x, int p) {
            nl("SetInterval " + name(r) + " = ic.pown(" + name(x) + ", " + p + ");");
        }

        @Override
        public void visitPow(int r, int x, int y) {
            nl("SetInterval " + name(r) + " = ic.pow(" + name(x) + ", " + name(y) + ");");
        }

        @Override
        public void visitSin(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.sin(" + name(x) + ");");
        }

        @Override
        public void visitCos(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.cos(" + name(x) + ");");
        }

        @Override
        public void visitTan(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.tan(" + name(x) + ");");
        }

        @Override
        public void visitAsin(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.asin(" + name(x) + ");");
        }

        @Override
        public void visitAcos(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.acos(" + name(x) + ");");
        }

        @Override
        public void visitAtan(int r, int x) {
            nl("SetInterval " + name(r) + " = ic.atan(" + name(x) + ");");
        }

        @Override
        public void visitRootn(int r, int x, int q) {
            nl("SetInterval " + name(r) + " = ic.rootn(" + name(x) + ", " + q + ");");
        }
    }

    private static class Gradient extends ExpressionPrinter {

        Gradient(CodeList cl) {
            super(cl);
        }

        @Override
        void printSignature(String name) {
            nl("public Gradient " + name + "(Gradient.Factory factory, Gradient[] inps) {");
        }

        @Override
        public void visitInp(int r, String name) {
            nl("Gradient " + name(r) + " = inps[" + r + "];");
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            nl("Gradient " + name(r) + " = factory.num(ExtendedRational.valueOf(\"" + numerator + "/" + denominator + "\"));");
        }

        @Override
        public void visitLit(int r, String literal) {
            nl("Gradient " + name(r) + " = factory.num(ExtndedRational.valueOf(\"" + literal + "\"));");
        }

        @Override
        public void visitInterval(int r, String inf, String sup) {
            nl("Gradient " + name(r) + " = factory.nums(ExtendedRational.valueOf(\"" + inf + "\"), ExtnededRational.valueOf(\"" + sup + "\"));");
        }

        @Override
        public void visitNum(int r, Number num) {
            nl("Gradient " + name(r) + " = factory.num(" + num + ");");
        }

        @Override
        public void visitPi(int r) {
            nl("Gradient " + name(r) + " = factory.pi();");
        }

        @Override
        public void visitEuler(int r) {
            nl("Gradient " + name(r) + " = factory.euler();");
        }

        @Override
        public void visitNeg(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".neg();");
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            nl("Gradient " + name(r) + " = " + name(x) + ".add(" + name(y) + ");");
        }

        @Override
        public void visitSub(int r, int x, int y) {
            nl("Gradient " + name(r) + " = " + name(x) + ".sub(" + name(y) + ");");
        }

        @Override
        public void visitMul(int r, int x, int y) {
            nl("Gradient " + name(r) + " = " + name(x) + ".mul(" + name(y) + ");");
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            nl("Gradient " + name(r) + " = " + name(x) + ".div(" + name(y) + ");");
        }

        @Override
        public void visitRecip(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".recip();");
        }

        @Override
        public void visitSqr(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".sqr();");
        }

        @Override
        public void visitSqrt(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".sqrt();");
        }

        @Override
        public void visitFma(int r, int x, int y, int z) {
            nl("ExtendedRational " + name(r) + " = " + name(x) + "fma(" + name(y) + ", " + name(z) + ");");
        }

        @Override
        public void visitPown(int r, int x, int p) {
            nl("Gradient " + name(r) + " = " + name(x) + ".pown(" + p + ");");
        }

        @Override
        public void visitPow(int r, int x, int y) {
            nl("Gradient " + name(r) + " = " + name(x) + ".pow(" + name(y) + ");");
        }

        @Override
        public void visitSin(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".sin();");
        }

        @Override
        public void visitCos(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".cos();");
        }

        @Override
        public void visitTan(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".tan();");
        }

        @Override
        public void visitAsin(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".asin();");
        }

        @Override
        public void visitAcos(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".acos();");
        }

        @Override
        public void visitAtan(int r, int x) {
            nl("Gradient " + name(r) + " = " + name(x) + ".atan();");
        }

        @Override
        public void visitRootn(int r, int x, int q) {
            nl("Gradient " + name(r) + " = " + name(x) + ".rootn(" + q + ");");
        }
    }

}
