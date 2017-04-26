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

import java.util.Arrays;
import java.util.Map;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * A product of several variables.
 */
public class VarProduct {

    public static final VarProduct ONE = new VarProduct(new String[0]);
    final String[] varNames;

    VarProduct(String[] names) {
        this.varNames = names.clone();
    }

    public boolean contains(String varName) {
        for (String vn : varNames) {
            if (varName.equals(vn)) {
                return true;
            }
        }
        return false;
    }

    public VarProduct remove(String varName) {
        if (!contains(varName)) {
            throw new IllegalArgumentException();
        }
        if (varNames.length == 1) {
            return ONE;
        }
        String[] newVarNames = new String[varNames.length - 1];
        int k = 0;
        for (String vn : varNames) {
            if (!varName.equals(vn)) {
                newVarNames[k++] = vn;
            }
        }
        assert k == newVarNames.length;
        return new VarProduct(newVarNames);
    }

    @Override
    public boolean equals(Object o) {
        return o instanceof VarProduct && Arrays.equals(this.varNames, ((VarProduct) o).varNames);
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 71 * hash + Arrays.deepHashCode(this.varNames);
        return hash;
    }

    @Override
    public String toString() {
        if (isOne()) {
            return "1";
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < varNames.length; i++) {
            if (i > 0) {
                sb.append("*");
            }
            sb.append(varNames[i]);
        }
        return sb.toString();
    }

    /**
     * Returns true if the product doesn't contains any variables and so it is
     * one.
     *
     * @return true if this product is empty
     */
    public boolean isOne() {
        return varNames.length == 0;
    }

    /**
     * Multiply this and that products
     *
     * @param that that product
     * @return the product that is multiplication of given products
     */
    public VarProduct mul(VarProduct that) {
        if (this.isOne()) {
            return that;
        } else if (that.isOne()) {
            return this;
        } else {
            String[] a = new String[this.varNames.length + that.varNames.length];
            System.arraycopy(this.varNames, 0, a, 0, this.varNames.length);
            System.arraycopy(that.varNames, 0, a, this.varNames.length, that.varNames.length);
            return new VarProduct(a);
        }
    }

    /**
     * Interval evaluation of the product with variable values from the given
     * environment
     *
     * @param ic interval context
     * @param env environment with variable values
     * @return interval evaluation
     */
    public SetInterval eval(SetIntervalContext ic, Map<String, SetInterval> env) {
        SetInterval prod = ic.numsToInterval(1, 1);
        for (String varName : varNames) {
            SetInterval varValue = env.get(varName);
            if (varValue == null) {
                throw new IllegalArgumentException(varName);
            }
            prod = ic.mul(prod, varValue);
        }
        return prod;
    }

    public Rational scale(Map<String, Rational> scale) {
        Rational prod = Rational.one();
        for (String varName : varNames) {
            Rational varScale = scale.get(varName);
            if (varScale == null) {
                continue;
            }
            prod = RationalOps.mul(prod, varScale);
        }
        return prod;
    }
}
