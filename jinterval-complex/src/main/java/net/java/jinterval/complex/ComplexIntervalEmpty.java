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
import net.java.jinterval.rational.DomainException;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
class ComplexIntervalEmpty implements ComplexInterval {

    private static final ComplexIntervalEmpty emptyF = new ComplexIntervalEmpty(false);
    private static final ComplexIntervalEmpty emptyT = new ComplexIntervalEmpty(true);
    private final boolean possiblyUndefined;

    private ComplexIntervalEmpty(boolean possiblyUndefined) {
        this.possiblyUndefined = possiblyUndefined;
    }

    public static ComplexIntervalEmpty valueOf(boolean possiblyUndefined) {
        return possiblyUndefined ? emptyT : emptyF;
    }

    public ExtendedRational realInf() {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    public ExtendedRational realInf(BinaryValueSet numberFormat) {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    public double doubleRealInf() {
        return Double.POSITIVE_INFINITY;
    }

    public float floatRealInf() {
        return Float.POSITIVE_INFINITY;
    }

    public ExtendedRational realSup() {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    public ExtendedRational realSup(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    public double doubleRealSup() {
        return Double.NEGATIVE_INFINITY;
    }

    public float floatRealSup() {
        return Float.NEGATIVE_INFINITY;
    }

    public ExtendedRational imagInf() {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    public ExtendedRational imagInf(BinaryValueSet numberFormat) {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    public double doubleImagInf() {
        return Double.POSITIVE_INFINITY;
    }

    public float floatImagInf() {
        return Float.POSITIVE_INFINITY;
    }

    public ExtendedRational imagSup() {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    public ExtendedRational imagSup(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    public double doubleImagSup() {
        return Double.NEGATIVE_INFINITY;
    }

    public float floatImagSup() {
        return Float.NEGATIVE_INFINITY;
    }

    public Rational realMid() {
        throw new DomainException();
    }

    public Rational realMid(BinaryValueSet numberFormat) {
        throw new DomainException();
    }

    public double doubleRealMid() {
        throw new DomainException();
    }

    public float floatRealMid() {
        throw new DomainException();
    }

    public Rational imagMid() {
        throw new DomainException();
    }

    public Rational imagMid(BinaryValueSet numberFormat) {
        throw new DomainException();
    }

    public double doubleImagMid() {
        throw new DomainException();
    }

    public float floatImagMid() {
        throw new DomainException();
    }

    public ExtendedRational realWid() {
        throw new DomainException();
    }

    public ExtendedRational realWid(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    public double doubleRealWid() {
        return Double.NEGATIVE_INFINITY;
    }

    public float floatRealWid() {
        return Float.NEGATIVE_INFINITY;
    }

    public ExtendedRational imagWid() {
        throw new DomainException();
    }

    public ExtendedRational imagWid(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    public double doubleImagWid() {
        return Double.NEGATIVE_INFINITY;
    }

    public float floatImagWid() {
        return Float.NEGATIVE_INFINITY;
    }

    public ExtendedRational rad() {
        throw new DomainException();
    }

    public ExtendedRational rad(BinaryValueSet numberFormat) {
        throw new DomainException();
    }

    public double doubleRad() {
        throw new DomainException();
    }

    public float floatRad() {
        throw new DomainException();
    }

    public ExtendedRational mag() {
        throw new DomainException();
    }

    public ExtendedRational mag(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    public double doubleMag() {
        return Double.NEGATIVE_INFINITY;
    }

    public float floatMag() {
        return Float.NEGATIVE_INFINITY;
    }

    public ExtendedRational mig() {
        throw new DomainException();
    }

    public ExtendedRational mig(BinaryValueSet numberFormat) {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    public double doubleMig() {
        return Double.POSITIVE_INFINITY;
    }

    public float floatMig() {
        return Float.POSITIVE_INFINITY;
    }

    public boolean isEmpty() {
        return true;
    }

    public boolean isBounded() {
        return true;
    }

    public boolean isEntire() {
        return false;
    }

    public boolean isBox() {
        return false;
    }

    public boolean isDisc() {
        return false;
    }

    public boolean isEqual(ComplexInterval that) {
        return that.isEmpty();
    }

    public boolean containedIn(ComplexInterval that) {
        return true;
    }

    public boolean containedInInterior(ComplexInterval that) {
        return true;
    }

    public boolean areDisjoint(ComplexInterval that) {
        return true;
    }

    public boolean possiblyUndefined() {
        return possiblyUndefined;
    }

    public boolean isMutable() {
        return false;
    }
}
