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
package net.java.jinterval.interval.set;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Interval;
import net.java.jinterval.interval.MidRad;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.DomainException;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
class EmptyInterval implements SetInterval {

    public static final EmptyInterval NaI = new EmptyInterval(Decoration.ILL);
    public static final EmptyInterval Empty = new EmptyInterval(Decoration.TRV);

    private static final EmptyInterval[] emptyCache = new EmptyInterval[Decoration.values().length];

    static {
        for (Decoration d : Decoration.values()) {
            emptyCache[d.ordinal()] = new EmptyInterval(d);
        }
    }
    private final Decoration decoration;

    private EmptyInterval(Decoration decoration) {
        if (decoration == null) {
            throw new NullPointerException();
        }
        this.decoration = decoration;
    }

    public static EmptyInterval NaI() {
        return NaI;
    }

    public static SetInterval empty() {
        return Empty;
    }

    public static SetInterval empty(Decoration decoration) {
        return decoration == Decoration.ILL ? NaI : Empty;
    }

    public static EmptyInterval valueOf(Decoration decoration) {
        return emptyCache[decoration.ordinal()];
    }

    /**
     * Level 1 inf
     *
     * @return
     */
    @Override
    public ExtendedRational inf() {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    @Override
    public ExtendedRational inf(BinaryValueSet numberFormat) {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    @Override
    public double doubleInf() {
        return Double.POSITIVE_INFINITY;
    }

    @Override
    public float floatInf() {
        return Float.POSITIVE_INFINITY;
    }

    /**
     * Level 1 sup
     *
     * @return
     */
    @Override
    public ExtendedRational sup() {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    @Override
    public ExtendedRational sup(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    @Override
    public double doubleSup() {
        return Double.NEGATIVE_INFINITY;
    }

    @Override
    public float floatSup() {
        return Float.NEGATIVE_INFINITY;
    }

    /**
     * Level 1 mid
     *
     * @return
     */
    @Override
    public Rational mid() {
        throw new DomainException();
    }

    @Override
    public Rational mid(BinaryValueSet numberFormat) {
        throw new DomainException();
    }

    @Override
    public double doubleMid() {
        throw new DomainException();
    }

    @Override
    public float floatMid() {
        throw new DomainException();
    }

    /**
     * Level 1 wid
     *
     * @return
     */
    @Override
    public ExtendedRational wid() {
        throw new DomainException();
    }

    @Override
    public ExtendedRational wid(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    @Override
    public double doubleWid() {
        return Double.NEGATIVE_INFINITY;
    }

    @Override
    public float floatWid() {
        return Float.NEGATIVE_INFINITY;
    }

    /**
     * Level 1 rad
     *
     * @return
     */
    @Override
    public ExtendedRational rad() {
        throw new DomainException();
    }

    @Override
    public ExtendedRational rad(BinaryValueSet numberFormat) {
        throw new DomainException();
    }

    @Override
    public double doubleRad() {
        throw new DomainException();
    }

    @Override
    public float floatRad() {
        throw new DomainException();
    }

    /**
     * Level 1 midRad
     *
     * @return
     */
    @Override
    public MidRad midRad() {
        throw new DomainException();
    }

    @Override
    public MidRad midRad(BinaryValueSet midNumberFormat, BinaryValueSet radNumberFormat) {
        throw new DomainException();
    }

    /**
     * Level 1 mag
     *
     * @return
     */
    @Override
    public ExtendedRational mag() {
        throw new DomainException();
    }

    @Override
    public ExtendedRational mag(BinaryValueSet numberFormat) {
        return ExtendedRational.NEGATIVE_INFINITY;
    }

    @Override
    public double doubleMag() {
        return Double.NEGATIVE_INFINITY;
    }

    @Override
    public float floatMag() {
        return Float.NEGATIVE_INFINITY;
    }

    /**
     * Level 1 mig
     *
     * @return
     */
    @Override
    public ExtendedRational mig() {
        throw new DomainException();
    }

    @Override
    public ExtendedRational mig(BinaryValueSet numberFormat) {
        return ExtendedRational.POSITIVE_INFINITY;
    }

    @Override
    public double doubleMig() {
        return Double.POSITIVE_INFINITY;
    }

    @Override
    public float floatMig() {
        return Float.POSITIVE_INFINITY;
    }

    @Override
    public boolean isEmpty() {
        return true;
    }

    @Override
    public boolean isEntire() {
        return false;
    }

    @Override
    public boolean isNaI() {
        return decoration == Decoration.ILL;
    }

    @Override
    public boolean isCommonInterval() {
        return false;
    }

    @Override
    public boolean isSingleton() {
        return false;
    }

    @Override
    public boolean isMember(ExtendedRational m) {
        return false;
    }

    @Override
    public boolean isMember(double m) {
        return false;
    }

    @Override
    public boolean isMember(float m) {
        return false;
    }

    @Override
    public boolean equal(Interval that) {
        return that instanceof EmptyInterval;
    }

    @Override
    public boolean subset(Interval that) {
        return true;
    }

    @Override
    public boolean less(Interval that) {
        return that instanceof EmptyInterval;
    }

    @Override
    public boolean precedes(Interval that) {
        return true;
    }

    @Override
    public boolean interior(Interval that) {
        return true;
    }

    @Override
    public boolean strictLess(Interval that) {
        return that instanceof EmptyInterval;
    }

    @Override
    public boolean strictPrecedes(Interval that) {
        return true;
    }

    @Override
    public boolean disjoint(Interval that) {
        return true;
    }

    @Override
    public OverlapState overlap(Interval that) {
        if (that instanceof EmptyInterval) {
            return OverlapState.bothEmpty;
        } else {
            return OverlapState.firstEmpty;
        }
    }

    @Override
    public Decoration getDecoration() {
        return decoration;
    }

    public boolean possiblyUndefined() {
        return decoration.possiblyUndefined();
    }

    public boolean isMutable() {
        return false;
    }

    @Override
    public String intervalToExact(BinaryValueSet valueSet) {
        return toString();
    }

    @Override
    public String intervalToExactDecorated(BinaryValueSet valueSet) {
        return toStringDecorated();
    }

    @Override
    public String toString() {
        return "[]";
    }

    @Override
    public String toStringDecorated() {
        return isNaI() ? "[nai]" : "[]";
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof EmptyInterval) {
            EmptyInterval that = (EmptyInterval) o;
            return this.getDecoration() == that.getDecoration();
        }
        return false;
    }

    public boolean canEqual(Interval o) {
        return o instanceof EmptyInterval;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 19 * hash + (this.decoration != null ? this.decoration.hashCode() : 0);
        return hash;
    }
}
