package ru.nsc.interval.globalopt;

import net.java.jinterval.expression.*;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.rational.Rational;

public class IntervalEvaluator {
    public static SetInterval[] evaluateSetInterval(SetIntervalContext ic, CodeList cl, SetInterval[] args, Expression... results) {
        if (args.length != cl.getNumInps()) {
            throw new IllegalArgumentException();
        }
        SetIntervalEvaluator ev = new SetIntervalEvaluator(cl);
        ev.setContext(ic);
        System.arraycopy(args, 0, ev.values, 0, cl.getNumInps());
        cl.acceptForward(ev);
        SetInterval[] ret = new SetInterval[results.length];
        for (int i = 0; i < results.length; i++) {
            ret[i] = ev.values[results[i].getIndex()];
        }
        return ret;
    }

    public static Gradient[] evaluateGradient(SetIntervalContext ic, CodeList cl, Gradient[] args, Expression... results) {
        if (args.length != cl.getNumInps()) {
            throw new IllegalArgumentException();
        }
        GradientEvaluator ev = new GradientEvaluator(cl, ic);
//        ev.setContext(ic);
        System.arraycopy(args, 0, ev.values, 0, cl.getNumInps());
        cl.acceptForward(ev);
        Gradient[] ret = new Gradient[results.length];
        for (int i = 0; i < results.length; i++) {
            ret[i] = ev.values[results[i].getIndex()];
        }
        return ret;
    }

    public static GradientMV[] evaluateGradientMV(SetIntervalContext ic, CodeList cl, GradientMV[] args, Expression... results) {
        if (args.length != cl.getNumInps()) {
            throw new IllegalArgumentException();
        }
        GradientMVEvaluator ev = new GradientMVEvaluator(cl, ic);
//        ev.setContext(ic);
        System.arraycopy(args, 0, ev.values, 0, cl.getNumInps());
        cl.acceptForward(ev);
        GradientMV[] ret = new GradientMV[results.length];
        for (int i = 0; i < results.length; i++) {
            ret[i] = ev.values[results[i].getIndex()];
        }
        return ret;
    }

    private static class SetIntervalEvaluator extends AbstractExpressionVisitor{
        final SetInterval[] values;
        SetIntervalContext ic;
        SetIntervalEvaluator(CodeList cl) {
            values = new SetInterval[cl.getNumExprs()];
        }

        @Override
        public void visitInp(int r, String name) {
        }

        @Override
        public void visitNum(int r, Number num) {
            Rational rv = Rational.valueOf(num);
            values[r] = ic.numsToInterval(rv, rv);
        }

        @Override
        public void visitPi(int r) {
            values[r] = ic.pi();
        }

        @Override
        public void visitEuler(int r) {
            values[r] = ic.euler();
        }

        @Override
        public void visitNeg(int r, int x) {
            values[r] = ic.neg(values[x]);
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            values[r] = ic.add(values[x], values[y]);
        }

        @Override
        public void visitSub(int r, int x, int y) {
            values[r] = ic.sub(values[x], values[y]);
        }

        @Override
        public void visitMul(int r, int x, int y) {
            values[r] = ic.mul(values[x], values[y]);
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            values[r] = ic.div(values[x], values[y]);
        }

        @Override
        public void visitRecip(int r, int x) {
            values[r] = ic.recip(values[x]);
        }

        @Override
        public void visitSqr(int r, int x) {
            values[r] = ic.sqr(values[x]);
        }

        @Override
        public void visitSqrt(int r, int x) {
            values[r] = ic.sqrt(values[x]);
        }

        @Override
        public void visitPown(int r, int x, int p) {
            values[r] = ic.pown(values[x], p);
        }

        @Override
        public void visitPow(int r, int x, int y) {
            values[r] = ic.pow(values[x], values[y]);
        }

        @Override
        public void visitSin(int r, int x) {
            values[r] = ic.sin(values[x]);
        }

        @Override
        public void visitCos(int r, int x) {
            values[r] = ic.cos(values[x]);
        }

        @Override
        public void visitTan(int r, int x) {
            values[r] = ic.tan(values[x]);
        }

        @Override
        public void visitAsin(int r, int x) {
            values[r] = ic.asin(values[x]);
        }

        @Override
        public void visitAcos(int r, int x) {
            values[r] = ic.acos(values[x]);
        }

        @Override
        public void visitAtan(int r, int x) {
            values[r] = ic.atan(values[x]);
        }

        @Override
        public void visitMax(int r, int x, int y) {
            values[r] = ic.max(values[x], values[y]);
        }

        @Override
        public void visitRootn(int r, int x, int q) {
            values[r] = ic.rootn(values[x], q);
        }

        void setContext(SetIntervalContext ic) {
            this.ic = ic;
        }
    }

    static class GradientEvaluator extends AbstractExpressionVisitor{
       final CodeList cl;
        final Gradient[] values;
        SetIntervalContext ic;
        GradientEvaluator(CodeList cl, SetIntervalContext ic) {
            this.cl = cl;
            values = new Gradient[cl.getNumExprs()];
            this.ic = ic;
            cl.acceptConstants(this);
        }

        @Override
        public void visitInp(int r, String name) {
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            Rational rv = Rational.valueOf(numerator + "/" + denominator);
            SetInterval v = ic.numsToInterval(rv, rv);
            values[r] = Gradient.nums(v.inf(), v.sup());
        }

        @Override
        public void visitLit(int r, String literal) {
            Rational rv = Rational.valueOf(literal);
            SetInterval v = ic.numsToInterval(rv, rv);
            values[r] = Gradient.nums(v.inf(), v.sup());
        }

        @Override
        public void visitNum(int r, Number num) {
            Rational rv = Rational.valueOf(num);
            SetInterval v = ic.numsToInterval(rv, rv);
            values[r] = Gradient.nums(v.inf(), v.sup());
        }

        @Override
        public void visitAbs(int r, int x) {
            values[r] = values[x].abs();
        }

        @Override
        public void visitPi(int r) {
            SetInterval v = ic.pi();
            values[r] = Gradient.nums(v.inf(), v.sup());
        }

        @Override
        public void visitEuler(int r) {
            SetInterval v = ic.euler();
            values[r] = Gradient.nums(v.inf(), v.sup());
        }

        @Override
        public void visitNeg(int r, int x) {
            values[r] = values[x].neg();
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            values[r] = values[x].add(values[y]);
        }

        @Override
        public void visitSub(int r, int x, int y) {
            values[r] = values[x].sub(values[y]);
        }

        @Override
        public void visitMul(int r, int x, int y) {
            values[r] = values[x].mul(values[y]);
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            values[r] = values[x].div(values[y]);
        }

        @Override
        public void visitRecip(int r, int x) {
            values[r] = values[x].recip();
        }

        @Override
        public void visitSqr(int r, int x) {
            values[r] = values[x].sqr();
        }

        @Override
        public void visitSqrt(int r, int x) {
            values[r] = values[x].sqrt();
        }

        @Override
        public void visitPow(int r, int x, int y) {
            if (!cl.getExpr(y).isConstant()) {
                throw new UnsupportedOperationException();
            }
            values[r] = values[x].pow(values[y]);
        }

        @Override
        public void visitSin(int r, int x) {
            values[r] = values[x].sin();
        }

        @Override
        public void visitCos(int r, int x) {
            values[r] = values[x].cos();
        }

        @Override
        public void visitTan(int r, int x) {
            values[r] = values[x].tan();
        }

        @Override
        public void visitAcos(int r, int x) {
            values[r] = values[x].acos();
        }

        @Override
        public void visitAtan(int r, int x) {
            values[r] = values[x].atan();
        }

        @Override
        public void visitMax(int r, int x, int y) {
            values[r] = values[x].max(values[y]);
        }
        
        @Override
        public void visitRootn(int r, int x, int q) {
            values[r] = values[x].rootn(q);
        }

        void setContext(SetIntervalContext ic) {
            this.ic = ic;
        }
    }

    static class GradientMVEvaluator extends AbstractExpressionVisitor{
        final CodeList cl;
        final GradientMV[] values;
        SetIntervalContext ic;
        GradientMVEvaluator(CodeList cl, SetIntervalContext ic) {
            this.cl = cl;
            values = new GradientMV[cl.getNumExprs()];
            this.ic = ic;
            cl.acceptConstants(this);
        }

        @Override
        public void visitAcos(int r, int x) {
            values[r] = values[x].acos();
        }

        @Override
        public void visitInp(int r, String name) {
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            Rational rv = Rational.valueOf(numerator + "/" + denominator);
            SetInterval v = ic.numsToInterval(rv, rv);
            values[r] = GradientMV.nums(v.inf(), v.sup());
        }

        @Override
        public void visitLit(int r, String literal) {
            Rational rv = Rational.valueOf(literal);
            SetInterval v = ic.numsToInterval(rv, rv);
            values[r] = GradientMV.nums(v.inf(), v.sup());
        }

        @Override
        public void visitNum(int r, Number num) {
            Rational rv = Rational.valueOf(num);
            SetInterval v = ic.numsToInterval(rv, rv);
            values[r] = GradientMV.nums(v.inf(), v.sup());
        }

        @Override
        public void visitPow(int r, int x, int y) {
            if (!cl.getExpr(y).isConstant()) {
                throw new UnsupportedOperationException();
            }
            values[r] = values[x].pow(values[y]);
        }

        @Override
        public void visitAbs(int r, int x) {
            values[r] = values[x].abs();
        }

        @Override
        public void visitPi(int r) {
            SetInterval v = ic.pi();
            values[r] = GradientMV.nums(v.inf(), v.sup());
        }

        @Override
        public void visitEuler(int r) {
            SetInterval v = ic.euler();
            values[r] = GradientMV.nums(v.inf(), v.sup());
        }

        @Override
        public void visitNeg(int r, int x) {
            values[r] = values[x].neg();
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            values[r] = values[x].add(values[y]);
        }

        @Override
        public void visitSub(int r, int x, int y) {
            values[r] = values[x].sub(values[y]);
        }

        @Override
        public void visitMul(int r, int x, int y) {
            values[r] = values[x].mul(values[y]);
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            values[r] = values[x].div(values[y]);
        }

        @Override
        public void visitRecip(int r, int x) {
            values[r] = values[x].recip();
        }

        @Override
        public void visitSqr(int r, int x) {
            values[r] = values[x].sqr();
        }

        @Override
        public void visitSqrt(int r, int x) {
            values[r] = values[x].sqrt();
        }

        @Override
        public void visitSin(int r, int x) {
            values[r] = values[x].sin();
        }

        @Override
        public void visitCos(int r, int x) {
            values[r] = values[x].cos();
        }

        @Override
        public void visitAtan(int r, int x) {
            values[r] = values[x].atan();
        }

        @Override
        public void visitMax(int r, int x, int y) {
            values[r] = values[x].max(values[y]);
        }
        
        @Override
        public void visitRootn(int r, int x, int q) {
            values[r] = values[x].rootn(q);
        }

        void setContext(SetIntervalContext ic) {
            this.ic = ic;
        }
    }
}


