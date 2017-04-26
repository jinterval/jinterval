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
package net.java.jinterval.symbolic;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 *
 */
public class Symbolic {

    public class Term implements Comparable<Term> {

        public final int[] pows;

        Term(int[] pows) {
            this.pows = pows;
        }

        @Override
        public int compareTo(Term that) {
            for (int i = Math.max(this.pows.length, that.pows.length) - 1; i >= 0; i--) {
                int thisP = i < this.pows.length ? this.pows[i] : 0;
                int thatP = i < that.pows.length ? that.pows[i] : 0;
                if (thisP != thatP) {
                    return Integer.compare(thisP, thatP);
                }
            }
            return 0;
        }

        @Override
        public boolean equals(Object o) {
            return o instanceof Term && Arrays.equals(this.pows, ((Term) o).pows);
        }

        @Override
        public int hashCode() {
            int hash = 7;
            hash = 59 * hash + Arrays.hashCode(this.pows);
            return hash;
        }

        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            for (int k = pows.length - 1; k >= 0; k--) {
                int pk = pows[k];
                if (pk == 0) {
                    continue;
                }
                if (sb.length() > 0) {
                    sb.append("*");
                }
                sb.append(allVarsList.get(k));
                if (pk > 1) {
                    sb.append("^").append(pk);
                }
            }
            return sb.toString();
        }

        public SetInterval eval(SetIntervalContext ic, Map<String, SetInterval> env) {
            SetInterval prod = ic.numsToInterval(1, 1);
            for (int k = 0; k < pows.length; k++) {
                int pk = pows[k];
                if (pk == 0) {
                    continue;
                }
                String varName = allVarsList.get(k);
                SetInterval x = env.get(varName);
                prod = ic.mul(prod, ic.pown(x, pk));
            }
            return prod;
        }
    }
    private static final SetInterval ZERO_INTERVAL = SetIntervalOps.nums2(0, 0);
    public final VarProduct varProduct;
    public final UnivariateRationalPolynom v;
    public final Map<VarProduct, UnivariateRationalPolynom> errs = new LinkedHashMap<VarProduct, UnivariateRationalPolynom>();
    public SetInterval more;
    public static final Map<String, Integer> allVars = new LinkedHashMap<String, Integer>();
    public static final List<String> allVarsList = new ArrayList<String>();

    static {
        allVars.put("u", 0);
        allVarsList.add("u");
    }
    public final Map<Term, Rational> monomials = new TreeMap<Term, Rational>();

    Symbolic(VarProduct varProduct, UnivariateRationalPolynom v, SetInterval more) {
        for (String varName : varProduct.varNames) {
            if (varName.contains("e_")) {
                throw new IllegalArgumentException();
            }
        }
        this.varProduct = varProduct;
        this.v = v;
        this.more = more;
    }

    private int findVar(String varName) {
        Integer i = allVars.get(varName);
        if (i == null) {
            assert allVars.size() == allVarsList.size();
            i = allVars.size();
            allVars.put(varName, i);
            allVarsList.add(varName);
        }
        return i;
    }

    private void addMonomial(Rational c, Term term) {
        Rational oldC = monomials.get(term);
        if (oldC != null) {
            c = RationalOps.add(oldC, c);
        }
        if (c.signum() != 0) {
            monomials.put(term, c);
        } else {
            monomials.remove(term);
        }
    }

    private Symbolic initMonomials() {
        if (v.isZero()) {
            return this;
        }
        for (String varName : varProduct.varNames) {
            findVar(varName);
        }
        for (int p = 0; p <= v.getOrder(); p++) {
            Rational c = v.getCoeff(p);
            if (c.signum() == 0) {
                continue;
            }
            int[] pows = new int[allVars.size()];
            for (String varName : varProduct.varNames) {
                pows[findVar(varName)]++;
            }
            pows[0] += p;
            addMonomial(c, new Term(pows));
        }
        return this;
    }

    private static Symbolic valueOf(String[] varNames, Rational[] coeff) {
        VarProduct varProduct = new VarProduct(varNames);
        return new Symbolic(varProduct, UnivariateRationalPolynom.valueOf(coeff), ZERO_INTERVAL).initMonomials();
    }

    private static Symbolic valueOf(String[] varNames, double[] coeff) {
        Rational[] cr = new Rational[coeff.length];
        for (int i = 0; i < coeff.length; i++) {
            cr[i] = Rational.valueOf(coeff[i]);
        }
        return valueOf(varNames, cr);
    }

    public static Symbolic valueOf(Rational... coeff) {
        return valueOf(new String[]{}, coeff);
    }

    public static Symbolic valueOf(String varName1, Rational... coeff) {
        return valueOf(new String[]{varName1}, coeff);
    }

    public static Symbolic valueOf(String varName1, String varName2, Rational... coeff) {
        return valueOf(new String[]{varName1, varName2}, coeff);
    }

    public static Symbolic valueOf(double... coeff) {
        return valueOf(new String[]{}, coeff);
    }

    public static Symbolic valueOf(String varName1, double... coeff) {
        return valueOf(new String[]{varName1}, coeff);
    }

    public static Symbolic valueOf(String varName1, String varName2, double... coeff) {
        return valueOf(new String[]{varName1, varName2}, coeff);
    }

    public static Symbolic valueOf(UnivariateRationalPolynom v) {
        return new Symbolic(new VarProduct(new String[0]), v, ZERO_INTERVAL).initMonomials();
    }

    public void print(SetIntervalContext ic, PrintStream out) {
        if (varProduct.isOne()) {
            out.print("= " + v.toString("u"));
        } else {
            out.print("= " + varProduct + "*(" + v.toString("u") + ")");
        }
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : errs.entrySet()) {
            VarProduct varProduct = e.getKey();
            out.println();
            out.print("+ " + varProduct + "*(" + e.getValue().toString("u") + ")");
        }
        if (!more.equal(ZERO_INTERVAL)) {
            out.println();
            out.print("+ " + ic.hull(more));
        }
        out.println();
    }

    public void print(SetIntervalContext ic, PrintStream out, Map<String, Rational> scaleMap) {
        Rational scaleU = scaleMap.get("u");
        if (scaleU == null) {
            scaleU = Rational.one();
        }
        if (varProduct.isOne()) {
            out.print("= " + v.toString("u", Rational.one(), scaleU));
        } else {
            out.print("= " + varProduct + "*(" + v.toString("u", varProduct.scale(scaleMap), scaleU) + ")");
        }
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : errs.entrySet()) {
            VarProduct varProduct = e.getKey();
            out.println();
            out.print("+ " + varProduct + "*(" + e.getValue().toString("u", varProduct.scale(scaleMap), scaleU) + ")");
        }
        if (!more.equal(ZERO_INTERVAL)) {
            out.println();
            out.print("+ " + ic.hull(more));
        }
        out.println();
    }

    public Symbolic addErr(String eName) {
        if (!eName.contains("e_")) {
            throw new IllegalArgumentException();
        }
        VarProduct vp = new VarProduct(new String[]{eName});
        if (this.errs.containsKey(vp)) {
            throw new IllegalArgumentException();
        }
        Symbolic res = new Symbolic(this.varProduct, this.v, this.more);
        res.errs.putAll(this.errs);
        res.errs.put(vp, UnivariateRationalPolynom.valueOf(Rational.one()));
        int varI = findVar(eName);
        int[] pows = new int[allVars.size()];
        pows[varI]++;
        res.monomials.putAll(this.monomials);
        res.addMonomial(Rational.one(), new Term(pows));
        return res;
    }

//    public Symbolic addMore(SetInterval more) {
//        Symbolic res = new Symbolic(this.varProduct, this.v, SetIntervalOps.add(this.more, more));
//        res.errs.putAll(this.errs);
//        res.monomials.putAll(this.monomials);
//        return res;
//    }
    public Symbolic add(Symbolic that, SetIntervalContext ic) {
        if (!this.varProduct.equals(that.varProduct)) {
            throw new IllegalArgumentException();
        }
        Symbolic res = new Symbolic(this.varProduct, this.v.add(that.v), ic.add(this.more, that.more));
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : this.errs.entrySet()) {
            VarProduct vp = e.getKey();
            UnivariateRationalPolynom px = e.getValue();
            UnivariateRationalPolynom py = that.errs.get(vp);
            if (py != null) {
                UnivariateRationalPolynom pr = px.add(py);
                if (!pr.isZero()) {
                    res.errs.put(vp, pr);
                }
            } else {
                res.errs.put(vp, px);
            }
        }
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : that.errs.entrySet()) {
            VarProduct vp = e.getKey();
            if (this.errs.containsKey(vp)) {
                continue;
            }
            UnivariateRationalPolynom py = e.getValue();
            res.errs.put(vp, py);
        }
        res.monomials.putAll(this.monomials);
        for (Map.Entry<Term, Rational> e : that.monomials.entrySet()) {
            res.addMonomial(e.getValue(), e.getKey());
        }
        return res;
    }

    public Symbolic sub(Symbolic that, SetIntervalContext ic) {
        return add(that.mul(Rational.valueOf(-1), ic), ic);
    }

    public Symbolic mul(Rational c, SetIntervalContext ic) {
        SetInterval cc = ic.numsToInterval(c, c);
        Symbolic res = new Symbolic(this.varProduct, this.v.mul(c), ic.mul(this.more, cc));
//        res.more = ic.mul(this.more, cc);
        if (c.signum() != 0) {
            for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : this.errs.entrySet()) {
                VarProduct varProduct = e.getKey();
                res.errs.put(varProduct, e.getValue().mul(c));
            }
            res.monomials.putAll(this.monomials);
            for (Map.Entry<Term, Rational> e : res.monomials.entrySet()) {
                e.setValue(RationalOps.mul(c, e.getValue()));
            }
        }
        return res;
    }

    public Symbolic mul(Symbolic that, SetIntervalContext ic, Map<String, SetInterval> env) {
        SetInterval vx = this.eval(ic, env);
        SetInterval vy = that.eval(ic, env);
        SetInterval vex = this.evalErrs(ic, env);
        SetInterval vey = that.evalErrs(ic, env);
        SetInterval newMore = ZERO_INTERVAL;
        newMore = ic.fma(this.more, vy, newMore);
        SetInterval u = env.get("u");
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : this.errs.entrySet()) {
            VarProduct vp = e.getKey();
            UnivariateRationalPolynom p = e.getValue();
            newMore = ic.fma(ic.mul(vp.eval(ic, env), p.eval(ic, u)), vey, newMore);
        }
        newMore = ic.fma(that.more, vx, newMore);
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : that.errs.entrySet()) {
            VarProduct vp = e.getKey();
            UnivariateRationalPolynom p = e.getValue();
            newMore = ic.fma(ic.mul(vp.eval(ic, env), p.eval(ic, u)), vex, newMore);
        }
        Symbolic res = new Symbolic(this.varProduct.mul(that.varProduct), this.v.mul(that.v), newMore);
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : this.errs.entrySet()) {
            VarProduct vpx = e.getKey();
            UnivariateRationalPolynom px = e.getValue();
            res.errs.put(vpx.mul(that.varProduct), px.mul(that.v));
        }
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : that.errs.entrySet()) {
            VarProduct vpy = e.getKey();
            VarProduct vp = this.varProduct.mul(vpy);
            UnivariateRationalPolynom py = e.getValue();
            UnivariateRationalPolynom pr = res.errs.get(vp);
            if (pr != null) {
                pr = pr.add(this.v.mul(py));
            } else {
                pr = this.v.mul(py);
            }
            res.errs.put(vp, pr);
        }
        for (Map.Entry<Term, Rational> xe : this.monomials.entrySet()) {
            for (Map.Entry<Term, Rational> ye : that.monomials.entrySet()) {
                Term xt = xe.getKey();
                Rational xc = xe.getValue();
                Term yt = ye.getKey();
                Rational yc = ye.getValue();
                Rational c = RationalOps.mul(xc, yc);
                int[] pows = new int[Math.max(xt.pows.length, yt.pows.length)];
                for (int i = 0; i < pows.length; i++) {
                    pows[i] = (i < xt.pows.length ? xt.pows[i] : 0) + (i < yt.pows.length ? yt.pows[i] : 0);
                }
                res.addMonomial(c, new Term(pows));
            }
        }
        return res;
    }

    public Symbolic[] splitByVar(String varName) {
        if (varName.equals("u")) {
            throw new IllegalArgumentException();
        }
        int varI = findVar(varName);
        VarProduct vp0, vp1;
        UnivariateRationalPolynom v0, v1;
        if (varProduct.contains(varName)) {
            vp0 = VarProduct.ONE;
            v0 = UnivariateRationalPolynom.ZERO;
            vp1 = varProduct.remove(varName);
            v1 = v;
        } else {
            vp0 = varProduct;
            v0 = v;
            vp1 = VarProduct.ONE;
            v1 = UnivariateRationalPolynom.ZERO;
        }
        Symbolic res0 = new Symbolic(vp0, v0, more);
        Symbolic res1 = new Symbolic(vp1, v1, SetIntervalOps.nums2(0, 0));
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : errs.entrySet()) {
            VarProduct vp = e.getKey();
            UnivariateRationalPolynom v = e.getValue();
            if (vp.contains(varName)) {
                res1.errs.put(vp.remove(varName), v);
            } else {
                res0.errs.put(vp, v);
            }
        }
        for (Map.Entry<Term, Rational> e : monomials.entrySet()) {
            Rational c = e.getValue();
            Term t = e.getKey();
            switch (t.pows[varI]) {
                case 0:
                    res0.addMonomial(c, t);
                    break;
                case 1:
                    int[] pows = t.pows.clone();
                    pows[varI]--;
                    res1.addMonomial(c, new Term(pows));
                    break;
                default:
                    throw new AssertionError();
            }
        }
        return new Symbolic[]{res0, res1};
    }

    public boolean isZero() {
        return v.isZero() && errs.isEmpty() && more.inf().signum() == 0 && more.sup().signum() == 0;
    }

    public SetInterval eval(SetIntervalContext ic, Map<String, SetInterval> env) {
        SetInterval u = env.get("u");
        return ic.fma(varProduct.eval(ic, env), v.eval(ic, u), evalErrs(ic, env));
    }

    public SetInterval evalErrs(SetIntervalContext ic, Map<String, SetInterval> env) {
        SetInterval s = more;
        SetInterval u = env.get("u");
        for (Map.Entry<VarProduct, UnivariateRationalPolynom> e : errs.entrySet()) {
            VarProduct vp = e.getKey();
            UnivariateRationalPolynom px = e.getValue();
            SetInterval prod = vp.eval(ic, env);
            s = ic.fma(prod, px.eval(ic, u), s);
        }
        return s;
    }

    public SetInterval evalMonomials(SetIntervalContext ic, Map<String, SetInterval> env) {
        SetInterval s = ic.numsToInterval(0, 0);
        for (Map.Entry<Term, Rational> e : monomials.entrySet()) {
            Term t = e.getKey();
            Rational c = e.getValue();
            s = ic.fma(ic.numsToInterval(c, c), t.eval(ic, env), s);
        }
        return s;
    }

    public SetInterval evalMonomials(Map<String, SetInterval> env) {
        SetIntervalContext icTerm = SetIntervalContexts.getExact();
        SetIntervalContext icExpr = SetIntervalContexts.getTightest(BinaryValueSet.INTEGER_UNLIMITED);
        SetInterval s = icExpr.numsToInterval(0, 0);
        for (Map.Entry<Term, Rational> e : monomials.entrySet()) {
            Term t = e.getKey();
            Rational c = e.getValue();
            SetInterval vt = icTerm.mul(icTerm.numsToInterval(c, c), t.eval(icTerm, env));
            s = icExpr.add(s, vt);
        }
        return s;
    }

    public void printMonomials(PrintStream out) {
        for (Map.Entry<Term, Rational> e : monomials.entrySet()) {
            Term t = e.getKey();
            Rational c = e.getValue();
            String ts = t.toString();
            out.print(ts);
            if (!ts.isEmpty()) {
                out.print("*");
            }
            out.println(c);
        }
    }
}
