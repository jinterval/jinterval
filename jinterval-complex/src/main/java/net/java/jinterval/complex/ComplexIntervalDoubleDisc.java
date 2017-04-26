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
package net.java.jinterval.complex;

import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
class ComplexIntervalDoubleDisc implements ComplexInterval {

    private final double realMid;
    private final double imagMid;
    private final double rad;
    private final boolean possiblyUndefined;

    ComplexIntervalDoubleDisc(double realMid, double imagMid, double rad, boolean possiblyUndefined) {
        assert Double.NEGATIVE_INFINITY < realMid && realMid <= Double.POSITIVE_INFINITY
                && Double.NEGATIVE_INFINITY < imagMid && imagMid <= Double.POSITIVE_INFINITY
                && 0 <= rad && rad < Double.POSITIVE_INFINITY;
        this.realMid = realMid;
        this.imagMid = imagMid;
        this.rad = rad;
        this.possiblyUndefined = possiblyUndefined;
    }

    public ExtendedRational realInf() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational realInf(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleRealInf() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatRealInf() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational realSup() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational realSup(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleRealSup() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatRealSup() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational imagInf() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational imagInf(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleImagInf() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatImagInf() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational imagSup() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational imagSup(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleImagSup() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatImagSup() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public Rational realMid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public Rational realMid(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleRealMid() {
        return realMid;
    }

    public float floatRealMid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public Rational imagMid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public Rational imagMid(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleImagMid() {
        return imagMid;
    }

    public float floatImagMid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational realWid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational realWid(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleRealWid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatRealWid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational imagWid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational imagWid(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleImagWid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatImagWid() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational rad() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational rad(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleRad() {
        return rad;
    }

    public float floatRad() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational mag() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational mag(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleMag() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatMag() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational mig() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public ExtendedRational mig(BinaryValueSet numberFormat) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public double doubleMig() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public float floatMig() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean isEmpty() {
        return false;
    }

    public boolean isBounded() {
        return true;
    }

    public boolean isEntire() {
        return false;
    }

    public boolean isBox() {
        return rad == 0;
    }

    public boolean isDisc() {
        return true;
    }

    public boolean isEqual(ComplexInterval that) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean containedIn(ComplexInterval that) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean containedInInterior(ComplexInterval that) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean areDisjoint(ComplexInterval that) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    public boolean possiblyUndefined() {
        return possiblyUndefined;
    }

    public boolean isMutable() {
        return false;
    }
}
