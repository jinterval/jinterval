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
package net.java.jinterval.field;

import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.Rational;
import org.apache.commons.math3.Field;
import org.apache.commons.math3.RealFieldElement;
import org.apache.commons.math3.exception.DimensionMismatchException;

/**
 * Representation of Rational number with specified rounding context
 */
public class RationalFieldElement implements RealFieldElement<RationalFieldElement> {

    private final RationalField field;
    private final ExtendedRational value;

    RationalFieldElement(RationalField field, ExtendedRational value) {
        this.field = field;
        this.value = value;
    }

    public ExtendedRationalContext getContext() {
        return field.getContext();
    }

    public ExtendedRational getValue() {
        return value;
    }

    private RationalFieldElement newElement(ExtendedRational value) {
        return new RationalFieldElement(field, value);
    }

    // FieldElement methods
    @Override
    public RationalFieldElement add(RationalFieldElement a) {
        return newElement(getContext().add(value, a.value));
    }

    @Override
    public RationalFieldElement subtract(RationalFieldElement a) {
        return newElement(getContext().sub(value, a.value));
    }

    @Override
    public RationalFieldElement negate() {
        return newElement(getContext().neg(value));
    }

    @Override
    public RationalFieldElement multiply(int n) {
        return newElement(getContext().mul(value, ExtendedRational.valueOf(n)));
    }

    @Override
    public RationalFieldElement multiply(RationalFieldElement a) {
        return newElement(getContext().mul(value, a.value));
    }

    @Override
    public RationalFieldElement divide(RationalFieldElement a) {
        return newElement(getContext().div(value, a.value));
    }

    @Override
    public RationalFieldElement reciprocal() {
        return newElement(getContext().recip(value));
    }

    @Override
    public Field<RationalFieldElement> getField() {
        return field;
    }

    // RealFieldElement methods
    @Override
    public double getReal() {
        return value.doubleValue();
    }

    @Override
    public RationalFieldElement add(double a) {
        return newElement(getContext().add(value, getContext().rnd(a)));
    }

    @Override
    public RationalFieldElement subtract(double a) {
        return newElement(getContext().sub(value, getContext().rnd(a)));
    }

    @Override
    public RationalFieldElement multiply(double a) {
        return newElement(getContext().mul(value, getContext().rnd(a)));
    }

    @Override
    public RationalFieldElement divide(double a) {
        return newElement(getContext().div(value, getContext().rnd(a)));
    }

    @Override
    public RationalFieldElement remainder(double a) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public RationalFieldElement remainder(RationalFieldElement a) throws DimensionMismatchException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public RationalFieldElement abs() {
        return newElement(getContext().abs(value));
    }

    @Override
    public RationalFieldElement ceil() {
        return newElement(getContext().ceil(value));
    }

    @Override
    public RationalFieldElement floor() {
        return newElement(getContext().floor(value));
    }

    @Override
    public RationalFieldElement rint() {
        return newElement(getContext().roundTiesToEven(value));
    }

    @Override
    public long round() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public RationalFieldElement signum() {
        return newElement(getContext().sign(value));
    }

    @Override
    public RationalFieldElement copySign(RationalFieldElement sign) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public RationalFieldElement copySign(double sign) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public RationalFieldElement scalb(int n) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public RationalFieldElement hypot(RationalFieldElement y) throws DimensionMismatchException {
        return newElement(getContext().hypot(value, y.value));
    }

    @Override
    public RationalFieldElement sqrt() {
        return newElement(getContext().sqrt(value));
    }

    @Override
    public RationalFieldElement cbrt() {
        return newElement(getContext().rootn(value, 3));
    }

    @Override
    public RationalFieldElement rootN(int n) {
        return newElement(getContext().rootn(value, n));
    }

    @Override
    public RationalFieldElement pow(double p) {
        return newElement(getContext().pow(value, getContext().rnd(p)));
    }

    @Override
    public RationalFieldElement pow(int n) {
        return newElement(getContext().pown(value, n));
    }

    @Override
    public RationalFieldElement pow(RationalFieldElement e) throws DimensionMismatchException {
        return newElement(getContext().pow(value, e.value));
    }

    @Override
    public RationalFieldElement exp() {
        return newElement(getContext().exp(value));
    }

    @Override
    public RationalFieldElement expm1() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public RationalFieldElement log() {
        return newElement(getContext().log(value));
    }

    @Override
    public RationalFieldElement log1p() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public RationalFieldElement cos() {
        return newElement(getContext().cos(value));
    }

    @Override
    public RationalFieldElement sin() {
        return newElement(getContext().sin(value));
    }

    @Override
    public RationalFieldElement tan() {
        return newElement(getContext().tan(value));
    }

    @Override
    public RationalFieldElement acos() {
        return newElement(getContext().acos(value));
    }

    @Override
    public RationalFieldElement asin() {
        return newElement(getContext().asin(value));
    }

    @Override
    public RationalFieldElement atan() {
        return newElement(getContext().atan(value));
    }

    @Override
    public RationalFieldElement atan2(RationalFieldElement x) throws DimensionMismatchException {
        return newElement(getContext().atan2(value, x.value));
    }

    @Override
    public RationalFieldElement cosh() {
        return newElement(getContext().cosh(value));
    }

    @Override
    public RationalFieldElement sinh() {
        return newElement(getContext().sinh(value));
    }

    @Override
    public RationalFieldElement tanh() {
        return newElement(getContext().tanh(value));
    }

    @Override
    public RationalFieldElement acosh() {
        return newElement(getContext().acosh(value));
    }

    @Override
    public RationalFieldElement asinh() {
        return newElement(getContext().asinh(value));
    }

    @Override
    public RationalFieldElement atanh() {
        return newElement(getContext().atanh(value));
    }

    @Override
    public RationalFieldElement linearCombination(RationalFieldElement[] a, RationalFieldElement[] b) throws DimensionMismatchException {
        if (a.length != b.length) {
            throw new DimensionMismatchException(a.length, b.length);
        }
        ExtendedRational s = Rational.zero();
        for (int i = 0; i < a.length; i++) {
            s = getContext().fma(a[i].value, b[i].value, s);
        }
        return newElement(s);
    }

    @Override
    public RationalFieldElement linearCombination(double[] a, RationalFieldElement[] b) throws DimensionMismatchException {
        if (a.length != b.length) {
            throw new DimensionMismatchException(a.length, b.length);
        }
        ExtendedRational s = Rational.zero();
        for (int i = 0; i < a.length; i++) {
            s = getContext().fma(getContext().rnd(a[i]), b[i].value, s);
        }
        return newElement(s);
    }

    @Override
    public RationalFieldElement linearCombination(RationalFieldElement a1, RationalFieldElement b1, RationalFieldElement a2, RationalFieldElement b2) {
        RationalFieldElement[] a = {a1, a2};
        RationalFieldElement[] b = {b1, b2};
        return linearCombination(a, b);
    }

    @Override
    public RationalFieldElement linearCombination(double a1, RationalFieldElement b1, double a2, RationalFieldElement b2) {
        double[] a = {a1, a2};
        RationalFieldElement[] b = {b1, b2};
        return linearCombination(a, b);
    }

    @Override
    public RationalFieldElement linearCombination(RationalFieldElement a1, RationalFieldElement b1, RationalFieldElement a2, RationalFieldElement b2, RationalFieldElement a3, RationalFieldElement b3) {
        RationalFieldElement[] a = {a1, a2, a3};
        RationalFieldElement[] b = {b1, b2, b3};
        return linearCombination(a, b);
    }

    @Override
    public RationalFieldElement linearCombination(double a1, RationalFieldElement b1, double a2, RationalFieldElement b2, double a3, RationalFieldElement b3) {
        double[] a = {a1, a2, a3};
        RationalFieldElement[] b = {b1, b2, b3};
        return linearCombination(a, b);
    }

    @Override
    public RationalFieldElement linearCombination(RationalFieldElement a1, RationalFieldElement b1, RationalFieldElement a2, RationalFieldElement b2, RationalFieldElement a3, RationalFieldElement b3, RationalFieldElement a4, RationalFieldElement b4) {
        RationalFieldElement[] a = {a1, a2, a3, a4};
        RationalFieldElement[] b = {b1, b2, b3, b4};
        return linearCombination(a, b);
    }

    @Override
    public RationalFieldElement linearCombination(double a1, RationalFieldElement b1, double a2, RationalFieldElement b2, double a3, RationalFieldElement b3, double a4, RationalFieldElement b4) {
        double[] a = {a1, a2, a3, a4};
        RationalFieldElement[] b = {b1, b2, b3, b4};
        return linearCombination(a, b);
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
