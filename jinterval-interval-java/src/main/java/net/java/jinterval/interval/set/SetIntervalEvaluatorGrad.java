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
package net.java.jinterval.interval.set;

import java.math.BigInteger;
import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public class SetIntervalEvaluatorGrad extends SetIntervalEvaluator {

    private final SetIntervalContext ic;
    private final SetIntervalEvaluator center;
    private final SetIntervalEvaluatorBareAccur64 grad;
    private final SetInterval[] inpVals;
    private final int wid;
    private final int bias;
    private final int tmp;

    public SetIntervalEvaluatorGrad(CodeList codeList, Expression[] results) {
        super(codeList, results);
        ic = SetIntervalContexts.getDefault();
        center = SetIntervalEvaluator.createAccurate(BinaryValueSet.BINARY64, codeList, results);
        wid = codeList.getNumInps() + 1;
        bias = codeList.getNumExprs() * wid - 1;
        tmp = bias + wid;
        grad = new SetIntervalEvaluatorBareAccur64(tmp + wid + 2); // two tmp variables
        inpVals = new SetInterval[codeList.getNumInps()];
        codeList.acceptConstants(this);
    }

    public SetIntervalEvaluatorGrad(SetIntervalContext ic, CodeList codeList, Expression[] results) {
        super(codeList, results);
        this.ic = ic;
        center = SetIntervalEvaluator.create(ic, codeList, results);
        wid = codeList.getNumInps() + 1;
        bias = codeList.getNumExprs() * wid - 1;
        tmp = bias + wid;
        grad = new SetIntervalEvaluatorBareAccur64(tmp + wid + 2); // two tmp variables
        inpVals = new SetInterval[codeList.getNumInps()];
        codeList.acceptConstants(this);
    }

    @Override
    public SetInterval get(int i) {
        return grad.get(i * wid);
    }

    public SetInterval getCenter(int i) {
        return center.get(i);
    }

    public SetInterval getRefined(int i) {
        SetInterval s = SetIntervalOps.nums2(0, 0);
        for (int j = 0; j < wid - 1; j++) {
            SetInterval gr = getD(i, j);
            SetInterval bias = ic.sub(inpVals[j], getCenter(j));
            s = ic.add(s, ic.mul(gr, bias));
        }
        return ic.intersection(get(i), ic.add(center.get(i), s));
    }

    public SetInterval getD(int i, int j) {
        if (j < 0 | j >= wid - 1) {
            throw new IllegalArgumentException();
        }
        return grad.get(i * wid + (j + 1));
    }

    /**
     * Evaluate CodeList and return interval values specified Expressions
     *
     * @param results array where to put results
     * @param resultsOffset put results at array elements from this offset
     * @param args array with interval values of inputs
     * @param argCenters array with center points of inputs
     * @param argsOffset get args at array elements from this offset
     */
    public void evaluate(SetInterval[] results, int resultsOffset,
            SetInterval[] args, Rational[] argCenters, int argsOffset) {
        for (int i = 0; i < codeList.getNumInps(); i++) {
            SetInterval v = args[i + argsOffset];
            Rational vC = argCenters[i + argsOffset];
            setInp(i, v, vC);
        }
        codeList.acceptForward(this);
        for (int i = 0; i < results.length; i++) {
            results[i + resultsOffset] = get(this.results[i].getIndex());
        }
    }

    private Rational mid(SetInterval v) {
        Rational midR = v.mid();
        SetInterval midI = ic.numsToInterval(midR, midR);
        if (!midI.isSingleton()) {
            if (midI.inf().signum() >= 0) {
                midR = (Rational) midI.inf();
            } else if (midI.sup().signum() <= 0) {
                midR = (Rational) midI.sup();
            } else {
                midR = Rational.zero();
            }
        }
        return midR;
    }

    @Override
    public void set(int i, SetInterval v) {
        setInp(i, v, mid(v));
    }

    private void setInp(int i, SetInterval v, Rational vC) {
        if (i < 0 || i >= wid - 1) {
            throw new IllegalArgumentException();
        }
        inpVals[i] = v;
        grad.set(i * wid, v);
        for (int k = 1; k < wid; k++) {
            grad.set(i * wid + k, 0, 0);
        }
        grad.set(i * wid + i + 1, 1, 1);
        SetInterval midS = SetIntervalOps.nums2(vC, vC);
        if (!midS.isSingleton() || !midS.subset(v)) {
            throw new IllegalArgumentException();
        }
        center.set(i, midS);
        int bk = bias + i + 1;
        grad.set(bk, midS);
        grad.visitSub(bk, i * wid, bk);
    }

    private void adjustByGrad(int r) {
        grad.set(tmp, 0, 0);
        for (int k = 1; k < wid; k++) {
            grad.visitMul(tmp + 1, r * wid + k, bias + k);
            grad.visitAdd(tmp, tmp, tmp + 1);
        }
        grad.set(tmp + 1, center.get(r));
        grad.visitAdd(tmp, tmp, tmp + 1);
        double inf = Math.max(grad.getInf(r * wid), grad.getInf(tmp));
        double sup = Math.min(grad.getSup(r * wid), grad.getSup(tmp));
        assert inf <= sup;
        grad.set(r * wid, inf, sup);
    }

    @Override
    public void visitInp(int r, String name) {
    }

    private void fillConst(int r) {
        grad.set(r * wid, center.get(r));
        for (int k = 1; k < wid; k++) {
            grad.set(wid * r + k, 0, 0);
        }
    }

    @Override
    public void visitLit(int r, String numerator, String denominator) {
        center.visitLit(r, numerator, denominator);
        fillConst(r);
    }

    @Override
    public void visitLit(int r, String literal) {
        center.visitLit(r, literal);
        fillConst(r);
    }

    @Override
    public void visitInterval(int r, String inf, String sup) {
        center.visitInterval(r, inf, sup);
        fillConst(r);
    }

    @Override
    public void visitNum(int r, Number num) {
        center.visitNum(r, num);
        fillConst(r);
    }

    @Override
    public void visitPi(int r) {
        center.visitPi(r);
        fillConst(r);
    }

    @Override
    public void visitEuler(int r) {
        center.visitEuler(r);
        fillConst(r);
    }

    @Override
    public void visitNeg(int r, int x) {
        center.visitNeg(r, x);
        for (int k = 0; k < wid; k++) {
            // -x'
            grad.visitNeg(r * wid + k, x * wid + k);
        }
    }

    @Override
    public void visitAdd(int r, int x, int y) {
        center.visitAdd(r, x, y);
        for (int k = 0; k < wid; k++) {
            // x' + y'
            grad.visitAdd(r * wid + k, x * wid + k, y * wid + k);
        }
    }

    @Override
    public void visitSub(int r, int x, int y) {
        center.visitSub(r, x, y);
        for (int k = 0; k < wid; k++) {
            // x' - y'
            grad.visitSub(r * wid + k, x * wid + k, y * wid + k);
        }
    }

    @Override
    public void visitMul(int r, int x, int y) {
        center.visitMul(r, x, y);
        grad.visitMul(r * wid, x * wid, y * wid);
        for (int k = 1; k < wid; k++) {
            // x*y' + x'*y
            int rk = r * wid + k;
            grad.visitMul(rk, x * wid, y * wid + k);
            grad.visitMul(tmp, x * wid + k, y * wid);
            grad.visitAdd(rk, rk, tmp);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitDiv(int r, int x, int y) {
        center.visitDiv(r, x, y);
        grad.visitDiv(r * wid, x * wid, y * wid);
        for (int k = 1; k < wid; k++) {
            // (x'*y - x*y')/y^2
            int rk = r * wid + k;
            grad.visitMul(rk, x * wid + k, y * wid);
            grad.visitMul(tmp, x * wid, y * wid + k);
            grad.visitSub(rk, rk, tmp);
            grad.visitSqr(tmp, y * wid);
            grad.visitDiv(rk, rk, tmp);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitRecip(int r, int x) {
        center.visitRecip(r, x);
        grad.visitRecip(r * wid, x * wid);
        for (int k = 1; k < wid; k++) {
            // -x'/x^2
            int rk = r * wid + k;
            grad.visitSqr(rk, x * wid);
            grad.visitDiv(rk, x * wid + k, rk);
            grad.visitNeg(rk, rk);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitSqr(int r, int x) {
        center.visitSqr(r, x);
        grad.visitSqr(r * wid, x * wid);
        for (int k = 1; k < wid; k++) {
            // 2*x*x'
            int rk = r * wid + k;
            grad.set(rk, 2, 2);
            grad.visitMul(rk, rk, x * wid);
            grad.visitMul(rk, rk, x * wid + k);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitSqrt(int r, int x) {
        center.visitSqrt(r, x);
        grad.visitSqrt(r * wid, x * wid);
        for (int k = 1; k < wid; k++) {
            // x'/(2*r)
            int rk = r * wid + k;
            grad.set(rk, 2, 2);
            grad.visitMul(rk, rk, r * wid);
            grad.visitDiv(rk, x * wid + k, rk);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitFma(int r, int x, int y, int z) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitPown(int r, int x, BigInteger p) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitPown(int r, int x, long p) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitPown(int r, int x, int p) {
        if (p == Integer.MIN_VALUE) {
            throw new UnsupportedOperationException();
        }
        center.visitPown(r, x, p);
        grad.visitPown(r * wid, x * wid, p);
        for (int k = 1; k < wid; k++) {
            // p*x^(p-1)*x'
            int rk = r * wid + k;
            grad.set(rk, p, p);
            grad.visitPown(tmp, x * wid, p - 1);
            grad.visitMul(rk, rk, tmp);
            grad.visitMul(rk, rk, x * wid + k);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitPow(int r, int x, int y) {
        center.visitPow(r, x, y);
        grad.visitPow(r * wid, x * wid, y * wid);
        for (int k = 1; k < wid; k++) {
            // x'*y*x^(y-1) + y'*r*ln(x)
            int rk = r * wid + k;
            grad.set(rk, 1, 1);
            grad.visitSub(rk, y * wid, rk);
            grad.visitPow(rk, x * wid, rk);
            grad.visitMul(rk, y * wid, rk);
            grad.visitMul(rk, x * wid + k, rk);
            grad.visitLog(tmp, x * wid);
            grad.visitMul(tmp, r * wid, tmp);
            grad.visitMul(tmp, y * wid + k, tmp);
            grad.visitAdd(rk, rk, tmp);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitExp(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitExp2(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitExp10(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitLog(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitLog2(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitLog10(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitSin(int r, int x) {
        center.visitSin(r, x);
        grad.visitSin(r * wid, x * wid);
        for (int k = 1; k < wid; k++) {
            // cos(x)*x'
            int rk = r * wid + k;
            grad.visitCos(rk, x * wid);
            grad.visitMul(rk, rk, x * wid + k);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitCos(int r, int x) {
        center.visitCos(r, x);
        grad.visitCos(r * wid, x * wid);
        for (int k = 1; k < wid; k++) {
            // -(sin(x)*x')
            int rk = r * wid + k;
            grad.visitSin(rk, x * wid);
            grad.visitMul(rk, rk, x * wid + k);
            grad.visitNeg(rk, rk);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitTan(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitAsin(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitAcos(int r, int x) {
        center.visitAcos(r, x);
        grad.visitAcos(r * wid, x * wid);
        for (int k = 1; k < wid; k++) {
            // -x'/sqrt(1-x^2)
            int rk = r * wid + k;
            grad.visitSqr(rk, x * wid);
            grad.set(tmp, 1, 1);
            grad.visitSub(rk, tmp, rk);
            grad.visitSqrt(rk, rk);
            grad.visitDiv(rk, x * wid + k, rk);
            grad.visitNeg(rk, rk);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitAtan(int r, int x) {
        center.visitAtan(r, x);
        grad.visitAtan(r * wid, x * wid);
        for (int k = 1; k < wid; k++) {
            // 1/(1+x^2)*x'
            int rk = r * wid + k;
            grad.set(tmp, 1, 1);
            grad.visitSqr(rk, x * wid);
            grad.visitAdd(rk, tmp, rk);
            grad.visitDiv(rk, tmp, rk);
            grad.visitMul(rk, rk, x * wid + k);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitAtan2(int r, int y, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitSinh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitCosh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitTanh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitAsinh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitAcosh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitAtanh(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitSign(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitCeil(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitFloor(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitTrunc(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitRoundTiesToEven(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitRoundTiesToAway(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitAbs(int r, int x) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitMin(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitMax(int r, int x, int y) {
        center.visitMax(r, x, y);
        grad.visitMax(r * wid, x * wid, y * wid);
        if (grad.getSup(x * wid) < grad.getInf(y * wid)) {
            // y'
            for (int k = 1; k < wid; k++) {
                int yk = y * wid + k;
                grad.set(r * wid + k, grad.getInf(yk), grad.getSup(yk));
            }
        } else if (grad.getSup(y * wid) < grad.getInf(x * wid)) {
            // x'
            for (int k = 1; k < wid; k++) {
                int xk = x * wid + k;
                grad.set(r * wid + k, grad.getInf(xk), grad.getSup(xk));
            }
        } else {
            for (int k = 1; k < wid; k++) {
                grad.set(r * wid + k, Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);
            }
        }
        adjustByGrad(r);
    }

    @Override
    public void visitRootn(int r, int x, BigInteger q) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitRootn(int r, int x, long q) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void visitRootn(int r, int x, int q) {
        if (q <= 0) {
            throw new UnsupportedOperationException();
        }
        center.visitRootn(r, x, q);
        grad.visitRootn(r * wid, x * wid, q);
        for (int k = 1; k < wid; k++) {
            // x^(1/q-1)/q*x'
            int rk = r * wid + k;
            grad.set(tmp, q, q);
            grad.visitRecip(rk, tmp);
            grad.set(tmp + 1, 1, 1);
            grad.visitSub(rk, rk, tmp + 1);
            grad.visitPow(rk, x * wid, rk);
            grad.visitDiv(rk, rk, tmp);
            grad.visitMul(rk, rk, x * wid + k);
        }
        adjustByGrad(r);
    }

    @Override
    public void visitHypot(int r, int x, int y) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
