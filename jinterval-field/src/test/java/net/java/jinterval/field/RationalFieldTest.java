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

import java.math.RoundingMode;
import org.apache.commons.math3.linear.ArrayFieldVector;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 *
 */
public class RationalFieldTest {

    private RationalField fieldF;
    private RationalField fieldN;
    private RationalField fieldC;
    
    @Before
    public void setUp() {
        fieldF = new RationalField(RoundingMode.FLOOR);
        fieldN = new RationalField(RoundingMode.HALF_EVEN);
        fieldC = new RationalField(RoundingMode.CEILING);
    }
    
    @After
    public void tearDown() {
        fieldF = null;
        fieldN = null;
        fieldC = null;
    }
    
    @Test
    public void testVector() {
        System.out.println("testVector");
        double v = 1/5.;
        RationalFieldElement vF = fieldF.get(v);
        RationalFieldElement vN = fieldN.get(v);
        RationalFieldElement vC = fieldC.get(v);
        RationalFieldElement[] arrF = { vF, vF, vF, vF, vF, vF, vF, vF, vF }; 
        RationalFieldElement[] arrN = { vN, vN, vN, vN, vN, vN, vN, vN, vN }; 
        RationalFieldElement[] arrC = { vC, vC, vC, vC, vC, vC, vC, vC, vC };
        ArrayFieldVector<RationalFieldElement> vecF = new ArrayFieldVector(arrF);
        ArrayFieldVector<RationalFieldElement> vecN = new ArrayFieldVector(arrN);
        ArrayFieldVector<RationalFieldElement> vecC = new ArrayFieldVector(arrC);
        System.out.println("Floor   " + vecF.dotProduct(vecF).getValue().doubleValue());
        System.out.println("Near    " + vecN.dotProduct(vecN).getValue().doubleValue());
        System.out.println("Ceiling " + vecC.dotProduct(vecC).getValue().doubleValue());
    }
    
}
