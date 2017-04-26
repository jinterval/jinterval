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

import java.math.BigInteger;

/**
 *
 */
public class PrimitiveEvaluators {

    public static float[] evaluateFloat(CodeList cl, float[] args, Expression... results) {
        if (args.length != cl.getNumInps()) {
            throw new IllegalArgumentException();
        }
        FloatEvaluator ev = new FloatEvaluator(cl);
        System.arraycopy(args, 0, ev.values, 0, cl.getNumInps());
        cl.acceptConstants(ev);
        cl.acceptForward(ev);
        float[] ret = new float[results.length];
        for (int i = 0; i < results.length; i++) {
            ret[i] = ev.values[results[i].getIndex()];
        }
        return ret;
    }

    private static class FloatEvaluator implements ExpressionVisitor {

        final float[] values;

        FloatEvaluator(CodeList cl) {
            values = new float[cl.getNumExprs()];
        }

        @Override
        public void visitInp(int r, String name) {
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            values[r] = (float) (Double.valueOf(numerator) / Double.valueOf(denominator));
        }

        @Override
        public void visitLit(int r, String literal) {
            values[r] = Float.valueOf(literal);
        }

        @Override
        public void visitInterval(int r, String inf, String sup) {
            values[r] = 0.5f * Float.valueOf(inf) + 0.5f * Float.valueOf(sup);
        }

        @Override
        public void visitNum(int r, Number num) {
            values[r] = num.floatValue();
        }

        @Override
        public void visitPi(int r) {
            values[r] = (float) Math.PI;
        }

        @Override
        public void visitEuler(int r) {
            values[r] = (float) Math.E;
        }

        @Override
        public void visitNeg(int r, int x) {
            values[r] = -values[x];
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            values[r] = values[x] + values[y];
        }

        @Override
        public void visitSub(int r, int x, int y) {
            values[r] = values[x] - values[y];
        }

        @Override
        public void visitMul(int r, int x, int y) {
            values[r] = values[x] * values[y];
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            values[r] = values[x] / values[y];
        }

        @Override
        public void visitRecip(int r, int x) {
            values[r] = 1 / values[x];
        }

        @Override
        public void visitSqr(int r, int x) {
            values[r] = values[x] * values[x];
        }

        @Override
        public void visitSqrt(int r, int x) {
            values[r] = (float) Math.sqrt(values[x]);
        }

        @Override
        public void visitFma(int r, int x, int y, int z) {
            values[r] = values[x] * values[y] + values[z];
        }

        @Override
        public void visitPown(int r, int x, BigInteger p) {
            values[r] = (float) Math.pow(values[x], p.doubleValue());
        }

        @Override
        public void visitPown(int r, int x, long p) {
            values[r] = (float) Math.pow(values[x], p);
        }

        @Override
        public void visitPown(int r, int x, int p) {
            values[r] = (float) Math.pow(values[x], p);
        }

        @Override
        public void visitPow(int r, int x, int y) {
            values[r] = (float) Math.pow(values[x], values[y]);
        }

        @Override
        public void visitExp(int r, int x) {
            values[r] = (float) Math.exp(values[x]);
        }

        @Override
        public void visitExp2(int r, int x) {
            values[r] = (float) Math.exp(values[x] * Math.log(2));
        }

        @Override
        public void visitExp10(int r, int x) {
            values[r] = (float) Math.exp(values[x] * Math.log(10));
        }

        @Override
        public void visitLog(int r, int x) {
            values[r] = (float) Math.log(values[x]);
        }

        @Override
        public void visitLog2(int r, int x) {
            values[r] = (float) (Math.log(values[x]) / Math.log(2));
        }

        @Override
        public void visitLog10(int r, int x) {
            values[r] = (float) Math.log10(values[x]);
        }

        @Override
        public void visitSin(int r, int x) {
            values[r] = (float) Math.sin(values[x]);
        }

        @Override
        public void visitCos(int r, int x) {
            values[r] = (float) Math.cos(values[x]);
        }

        @Override
        public void visitTan(int r, int x) {
            values[r] = (float) Math.tan(values[x]);
        }

        @Override
        public void visitAsin(int r, int x) {
            values[r] = (float) Math.asin(values[x]);
        }

        @Override
        public void visitAcos(int r, int x) {
            values[r] = (float) Math.acos(values[x]);
        }

        @Override
        public void visitAtan(int r, int x) {
            values[r] = (float) Math.atan(values[x]);
        }

        @Override
        public void visitAtan2(int r, int y, int x) {
            values[r] = (float) Math.atan2(values[y], values[x]);
        }

        @Override
        public void visitSinh(int r, int x) {
            values[r] = (float) Math.sinh(values[x]);
        }

        @Override
        public void visitCosh(int r, int x) {
            values[r] = (float) Math.cosh(values[x]);
        }

        @Override
        public void visitTanh(int r, int x) {
            values[r] = (float) Math.tanh(values[x]);
        }

        @Override
        public void visitAsinh(int r, int x) {
            double xv = values[x];
            double ra = Math.log(Math.abs(xv) + xv * xv);
            values[r] = (float) Math.copySign(ra, xv);
        }

        @Override
        public void visitAcosh(int r, int x) {
            double xv = values[x];
            values[r] = xv >= 1 ? (float) Math.log(xv + Math.sqrt((xv - 1) * (xv + 1))) : Float.NaN;
        }

        @Override
        public void visitAtanh(int r, int x) {
            double xv = values[x];
            values[r] = Math.abs(xv) < 1 ? (float) (Math.log(1 + xv) - Math.log(1 - xv)) : Float.NaN;
        }

        @Override
        public void visitSign(int r, int x) {
            values[r] = Math.signum(values[x]);
        }

        @Override
        public void visitCeil(int r, int x) {
            values[r] = (float) Math.ceil(values[x]);
        }

        @Override
        public void visitFloor(int r, int x) {
            values[r] = (float) Math.floor(values[x]);
        }

        @Override
        public void visitTrunc(int r, int x) {
            float xv = values[x];
            int rv = (int) xv;
            values[r] = rv != Integer.MAX_VALUE && rv != Integer.MIN_VALUE ? rv : xv;
        }

        @Override
        public void visitRoundTiesToEven(int r, int x) {
            values[r] = (float) Math.rint(values[x]);
        }

        @Override
        public void visitRoundTiesToAway(int r, int x) {
            throw new UnsupportedOperationException();
        }

        @Override
        public void visitAbs(int r, int x) {
            values[r] = Math.abs(values[x]);
        }

        @Override
        public void visitMin(int r, int x, int y) {
            values[r] = Math.min(values[x], values[y]);
        }

        @Override
        public void visitMax(int r, int x, int y) {
            values[r] = Math.max(values[x], values[y]);
        }

        @Override
        public void visitRootn(int r, int x, BigInteger q) {
            values[r] = (float) Math.pow(values[x], 1 / q.doubleValue());
        }

        @Override
        public void visitRootn(int r, int x, long q) {
            values[r] = (float) Math.pow(values[x], 1 / (double) q);
        }

        @Override
        public void visitRootn(int r, int x, int q) {
            values[r] = (float) Math.pow(values[x], 1 / (double) q);
        }

        @Override
        public void visitHypot(int r, int x, int y) {
            values[r] = (float) Math.hypot(x, y);
        }
    }

    public static double[] evaluateDouble(CodeList cl, double[] args, Expression... results) {
        if (args.length != cl.getNumInps()) {
            throw new IllegalArgumentException();
        }
        DoubleEvaluator ev = new DoubleEvaluator(cl);
        System.arraycopy(args, 0, ev.values, 0, cl.getNumInps());
        cl.acceptConstants(ev);
        cl.acceptForward(ev);
        double[] ret = new double[results.length];
        for (int i = 0; i < results.length; i++) {
            ret[i] = ev.values[results[i].getIndex()];
        }
        return ret;
    }

    private static class DoubleEvaluator implements ExpressionVisitor {

        final double[] values;

        DoubleEvaluator(CodeList cl) {
            values = new double[cl.getNumExprs()];
        }

        @Override
        public void visitInp(int r, String name) {
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            values[r] = Double.valueOf(numerator) / Double.valueOf(denominator);
        }

        @Override
        public void visitLit(int r, String literal) {
            values[r] = Double.valueOf(literal);
        }

        @Override
        public void visitInterval(int r, String inf, String sup) {
            values[r] = 0.5 * Double.valueOf(inf) + 0.5 * Double.valueOf(sup);
        }

        @Override
        public void visitNum(int r, Number num) {
            values[r] = num.doubleValue();
        }

        @Override
        public void visitPi(int r) {
            values[r] = Math.PI;
        }

        @Override
        public void visitEuler(int r) {
            values[r] = Math.E;
        }

        @Override
        public void visitNeg(int r, int x) {
            values[r] = -values[x];
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            values[r] = values[x] + values[y];
        }

        @Override
        public void visitSub(int r, int x, int y) {
            values[r] = values[x] - values[y];
        }

        @Override
        public void visitMul(int r, int x, int y) {
            values[r] = values[x] * values[y];
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            values[r] = values[x] / values[y];
        }

        @Override
        public void visitRecip(int r, int x) {
            values[r] = 1 / values[x];
        }

        @Override
        public void visitSqr(int r, int x) {
            values[r] = values[x] * values[x];
        }

        @Override
        public void visitSqrt(int r, int x) {
            values[r] = Math.sqrt(values[x]);
        }

        @Override
        public void visitFma(int r, int x, int y, int z) {
            values[r] = values[x] * values[y] + values[z];
        }

        @Override
        public void visitPown(int r, int x, BigInteger p) {
            values[r] = (float) Math.pow(values[x], p.doubleValue());
        }

        @Override
        public void visitPown(int r, int x, long p) {
            values[r] = (float) Math.pow(values[x], p);
        }

        @Override
        public void visitPown(int r, int x, int p) {
            values[r] = Math.pow(values[x], p);
        }

        @Override
        public void visitPow(int r, int x, int y) {
            values[r] = Math.pow(values[x], values[y]);
        }

        @Override
        public void visitExp(int r, int x) {
            values[r] = Math.exp(values[x]);
        }

        @Override
        public void visitExp2(int r, int x) {
            values[r] = Math.exp(values[x] * Math.log(2));
        }

        @Override
        public void visitExp10(int r, int x) {
            values[r] = Math.exp(values[x] * Math.log(10));
        }

        @Override
        public void visitLog(int r, int x) {
            values[r] = Math.log(values[x]);
        }

        @Override
        public void visitLog2(int r, int x) {
            values[r] = Math.log(values[x]) / Math.log(2);
        }

        @Override
        public void visitLog10(int r, int x) {
            values[r] = Math.log10(values[x]);
        }

        @Override
        public void visitSin(int r, int x) {
            values[r] = Math.sin(values[x]);
        }

        @Override
        public void visitCos(int r, int x) {
            values[r] = Math.cos(values[x]);
        }

        @Override
        public void visitTan(int r, int x) {
            values[r] = Math.tan(values[x]);
        }

        @Override
        public void visitAsin(int r, int x) {
            values[r] = Math.asin(values[x]);
        }

        @Override
        public void visitAcos(int r, int x) {
            values[r] = Math.acos(values[x]);
        }

        @Override
        public void visitAtan(int r, int x) {
            values[r] = Math.atan(values[x]);
        }

        @Override
        public void visitAtan2(int r, int y, int x) {
            values[r] = Math.atan2(values[y], values[x]);
        }

        @Override
        public void visitSinh(int r, int x) {
            values[r] = Math.sinh(values[x]);
        }

        @Override
        public void visitCosh(int r, int x) {
            values[r] = Math.cosh(values[x]);
        }

        @Override
        public void visitTanh(int r, int x) {
            values[r] = Math.tanh(values[x]);
        }

        @Override
        public void visitAsinh(int r, int x) {
            double xv = values[x];
            double ra = Math.log(Math.abs(xv) + xv * xv);
            values[r] = Math.copySign(ra, xv);
        }

        @Override
        public void visitAcosh(int r, int x) {
            double xv = values[x];
            values[r] = xv >= 1 ? Math.log(xv + Math.sqrt((xv - 1) * (xv + 1))) : Double.NaN;
        }

        @Override
        public void visitAtanh(int r, int x) {
            double xv = values[x];
            values[r] = Math.abs(xv) < 1 ? Math.log(1 + xv) - Math.log(1 - xv) : Double.NaN;
        }

        @Override
        public void visitSign(int r, int x) {
            values[r] = Math.signum(values[x]);
        }

        @Override
        public void visitCeil(int r, int x) {
            values[r] = Math.ceil(values[x]);
        }

        @Override
        public void visitFloor(int r, int x) {
            values[r] = Math.floor(values[x]);
        }

        @Override
        public void visitTrunc(int r, int x) {
            double xv = values[x];
            long rv = (long) xv;
            values[r] = rv != Long.MAX_VALUE && rv != Long.MIN_VALUE ? rv : xv;
        }

        @Override
        public void visitRoundTiesToEven(int r, int x) {
            values[r] = Math.rint(values[x]);
        }

        @Override
        public void visitRoundTiesToAway(int r, int x) {
            throw new UnsupportedOperationException();
        }

        @Override
        public void visitAbs(int r, int x) {
            values[r] = Math.abs(values[x]);
        }

        @Override
        public void visitMin(int r, int x, int y) {
            values[r] = Math.min(values[x], values[y]);
        }

        @Override
        public void visitMax(int r, int x, int y) {
            values[r] = Math.max(values[x], values[y]);
        }

        @Override
        public void visitRootn(int r, int x, BigInteger q) {
            values[r] = Math.pow(values[x], 1 / q.doubleValue());
        }

        @Override
        public void visitRootn(int r, int x, long q) {
            values[r] = Math.pow(values[x], 1 / (double) q);
        }

        @Override
        public void visitRootn(int r, int x, int q) {
            values[r] = Math.pow(values[x], 1 / (double) q);
        }

        @Override
        public void visitHypot(int r, int x, int y) {
            values[r] = Math.hypot(x, y);
        }
    }

}
