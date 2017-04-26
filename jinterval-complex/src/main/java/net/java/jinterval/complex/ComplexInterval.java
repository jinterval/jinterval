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
public interface ComplexInterval {

    /**
     * Level 1 real inf
     *
     * @return
     */
    public ExtendedRational realInf();

    public ExtendedRational realInf(BinaryValueSet numberFormat);

    public double doubleRealInf();

    public float floatRealInf();

    /**
     * Level 1 real sup
     *
     * @return
     */
    public ExtendedRational realSup();

    public ExtendedRational realSup(BinaryValueSet numberFormat);

    public double doubleRealSup();

    public float floatRealSup();

    /**
     * Level 1 imaginary inf
     *
     * @return
     */
    public ExtendedRational imagInf();

    public ExtendedRational imagInf(BinaryValueSet numberFormat);

    public double doubleImagInf();

    public float floatImagInf();

    /**
     * Level 1 imaginary sup
     *
     * @return
     */
    public ExtendedRational imagSup();

    public ExtendedRational imagSup(BinaryValueSet numberFormat);

    public double doubleImagSup();

    public float floatImagSup();

    /**
     * Level 1 real mid
     *
     * @return
     */
    public Rational realMid();

    public Rational realMid(BinaryValueSet numberFormat);

    public double doubleRealMid();

    public float floatRealMid();

    /**
     * Level 1 imaginary mid
     *
     * @return
     */
    public Rational imagMid();

    public Rational imagMid(BinaryValueSet numberFormat);

    public double doubleImagMid();

    public float floatImagMid();

    /**
     * Level 1 real wid
     *
     * @return
     */
    public ExtendedRational realWid();

    public ExtendedRational realWid(BinaryValueSet numberFormat);

    public double doubleRealWid();

    public float floatRealWid();

    /**
     * Level 1 imaginary wid
     *
     * @return
     */
    public ExtendedRational imagWid();

    public ExtendedRational imagWid(BinaryValueSet numberFormat);

    public double doubleImagWid();

    public float floatImagWid();

    /**
     * Level 1 rad
     *
     * @return
     */
    public ExtendedRational rad();

    public ExtendedRational rad(BinaryValueSet numberFormat);

    public double doubleRad();

    public float floatRad();

    /**
     * Level 1 mag
     *
     * @return
     */
    public ExtendedRational mag();

    public ExtendedRational mag(BinaryValueSet numberFormat);

    public double doubleMag();

    public float floatMag();

    /**
     * Level 1 mig
     *
     * @return
     */
    public ExtendedRational mig();

    public ExtendedRational mig(BinaryValueSet numberFormat);

    public double doubleMig();

    public float floatMig();

    public boolean isEmpty();

    public boolean isBounded();
    
    public boolean isEntire();

    public boolean isBox();

    public boolean isDisc();

    public boolean isEqual(ComplexInterval that);

    public boolean containedIn(ComplexInterval that);

    //public boolean lessEqual(ComplexInterval that);
    //public boolean precedesEqual(ComplexInterval that);
    public boolean containedInInterior(ComplexInterval that);

    //public boolean less(ComplexInterval that);
    // public boolean precedes(ComplexInterval that);
    public boolean areDisjoint(ComplexInterval that);

    //public Decoration getDecoration();
    public boolean possiblyUndefined();

    public boolean isMutable();
}
