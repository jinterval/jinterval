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
package net.java.jinterval.interval;

import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public interface Interval {

    /**
     * Level 1 inf
     *
     * @return
     */
    public ExtendedRational inf();

    public ExtendedRational inf(BinaryValueSet numberFormat);

    public double doubleInf();

    public float floatInf();

    /**
     * Level 1 sup
     *
     * @return
     */
    public ExtendedRational sup();

    public ExtendedRational sup(BinaryValueSet numberFormat);

    public double doubleSup();

    public float floatSup();

    /**
     * Level 1 mid
     *
     * @return
     */
    public Rational mid();

    public Rational mid(BinaryValueSet numberFormat);

    public double doubleMid();

    public float floatMid();

    /**
     * Level 1 wid
     *
     * @return
     */
    public ExtendedRational wid();

    public ExtendedRational wid(BinaryValueSet numberFormat);

    public double doubleWid();

    public float floatWid();

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
     * Level 1 midRad
     *
     * @return
     */
    public MidRad midRad();
    
    public MidRad midRad(BinaryValueSet midNumberFormat, BinaryValueSet radNumberFormar);
    
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

    public boolean equal(Interval that);

    public boolean subset(Interval that);

    public boolean interior(Interval that);

    public boolean disjoint(Interval that);

    public String intervalToExact(BinaryValueSet valueSet);

    public String intervalToExactDecorated(BinaryValueSet valueSet);

    public String toString();

    public String toStringDecorated();
}
