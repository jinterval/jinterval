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

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.UndefinedOperationException;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.Rational;
import org.junit.After;
import org.junit.Assert;
import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

/**
 *
 */
public class Text2IntervalTest {

    SetIntervalContext ic;

    @Before
    public void setUp() {
        ic = SetIntervalContexts.getExact();
    }

    @After
    public void tearDown() {
        ic = null;
    }

    @Test
    public void testTextToIntervalEmpty() {
        System.out.println("text2IntervalEmpty");

        SetInterval v1 = ic.textToDecoratedInterval("[ empty ]_trv");
        assertTrue(v1.isEmpty());
        assertSame(Decoration.TRV, v1.getDecoration());

        SetInterval v2 = ic.textToDecoratedInterval("[ nai ]");
        assertTrue(v2.isEmpty());
        assertSame(Decoration.ILL, v2.getDecoration());
    }

    @Test
    public void testTextToInterval() {
        System.out.println("textToInterval");
        check("[empty]", ExtendedRational.POSITIVE_INFINITY, ExtendedRational.NEGATIVE_INFINITY, Decoration.TRV);
        check("[empty]_trv", ExtendedRational.POSITIVE_INFINITY, ExtendedRational.NEGATIVE_INFINITY, Decoration.TRV);
        check("[]", ExtendedRational.POSITIVE_INFINITY, ExtendedRational.NEGATIVE_INFINITY, Decoration.TRV);
        check("[]_trv", ExtendedRational.POSITIVE_INFINITY, ExtendedRational.NEGATIVE_INFINITY, Decoration.TRV);
        checkNaI("[empty]_ill");
        checkNaI("[]_ill");
        checkNaI("[empty");
        checkNaI("[empty,entire]");
        check("[entire]", ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY, Decoration.DAC);
        checkNaI("[entire]_com");
        check("[entire]_trv", ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY, Decoration.TRV);
        checkNaI("[entire]_ill");
        check("[1,2]", Rational.valueOf(1), Rational.valueOf(2), Decoration.COM);
        checkNaI("[2,1]");
        check("[0.5,2/3]", Rational.valueOf(0.5), Rational.valueOf(2, 3), Decoration.COM);
        check("[0.5,]", Rational.valueOf(0.5), ExtendedRational.POSITIVE_INFINITY, Decoration.DAC);
        check("[,2/3]", ExtendedRational.NEGATIVE_INFINITY, Rational.valueOf(2, 3), Decoration.DAC);
        check("[,]", ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY, Decoration.DAC);
        checkNaI("[2/3,0.5]");
        check("0?", Rational.valueOf(-0.5), Rational.valueOf(0.5), Decoration.COM);
        check("0?u", Rational.zero(), Rational.valueOf(0.5), Decoration.COM);
        check("0?D", Rational.valueOf(-0.5), Rational.zero(), Decoration.COM);
        check(".0?", Rational.valueOf(-1, 20), Rational.valueOf(1, 20), Decoration.COM);
        check(".0?U", Rational.zero(), Rational.valueOf(1, 20), Decoration.COM);
        check(".0?d", Rational.valueOf(-1, 20), Rational.zero(), Decoration.COM);
        check(".0?e5", Rational.valueOf(-5000), Rational.valueOf(5000), Decoration.COM);
        check(".0?Ue+5", Rational.zero(), Rational.valueOf(5000), Decoration.COM);
        check(".0?de05", Rational.valueOf(-5000), Rational.zero(), Decoration.COM);
        check("7?", Rational.valueOf(6.5), Rational.valueOf(7.5), Decoration.COM);
        check("7?1", Rational.valueOf(6), Rational.valueOf(8), Decoration.COM);
        check("7?2", Rational.valueOf(5), Rational.valueOf(9), Decoration.COM);
        check("7?2u", Rational.valueOf(7), Rational.valueOf(9), Decoration.COM);
        check("7?2d", Rational.valueOf(5), Rational.valueOf(7), Decoration.COM);
        check("7??e3", ExtendedRational.NEGATIVE_INFINITY, ExtendedRational.POSITIVE_INFINITY, Decoration.DAC);
        check("7??ue3", Rational.valueOf(7000), ExtendedRational.POSITIVE_INFINITY, Decoration.DAC);
        check("7??de3", ExtendedRational.NEGATIVE_INFINITY, Rational.valueOf(7000), Decoration.DAC);
        checkNaI("7?2du");
        checkNaI("7");
    }

    private void check(String s, ExtendedRational inf, ExtendedRational sup, Decoration d) {
        SetInterval v = ic.textToDecoratedInterval(s);
        assertEquals(inf, v.inf());
        assertEquals(sup, v.sup());
        assertSame(d, v.getDecoration());
    }

    private void checkNaI(String s) {
        try {
            ic.textToDecoratedInterval(s);
            fail();
        } catch (UndefinedOperationException e) {
        }
    }
}
