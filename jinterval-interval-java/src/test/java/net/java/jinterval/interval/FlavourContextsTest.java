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

import net.java.jinterval.interval.classic.ClassicInterval;
import net.java.jinterval.interval.classic.ClassicIntervalContext;
import net.java.jinterval.interval.classic.ClassicIntervalContexts;
import net.java.jinterval.interval.kaucher.KaucherInterval;
import net.java.jinterval.interval.kaucher.KaucherIntervalContext;
import net.java.jinterval.interval.kaucher.KaucherIntervalContexts;
import net.java.jinterval.interval.set.Level2SetIntervalInfSupBinary128;
import net.java.jinterval.interval.set.Level2SetIntervalInfSupBinary64;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import static org.junit.Assert.*;
import org.junit.Test;

/**
 *
 */
public class FlavourContextsTest {

    private static <I extends Interval> I algorithm(I a, I b, IntervalContext<I> context) {
        return context.add(a, b);
    }

    @Test
    public void testFlavourContexts() {
        System.out.println("FlavourContexts");

        // Exact contexts of different flavours
        ClassicIntervalContext classicContext = ClassicIntervalContexts.getExact();
        SetIntervalContext setContext = SetIntervalContexts.getExact();
        KaucherIntervalContext kaucherContext = KaucherIntervalContexts.getExact();

        // Input intervals
        ClassicInterval classic_0_1 = classicContext.numsToInterval(0, 1);
        assertSame(Decoration.COM, classic_0_1.getDecoration());

        ClassicInterval classic_2_5 = classicContext.numsToInterval(2, 5);
        assertSame(Decoration.COM, classic_2_5.getDecoration());

        SetInterval set_3_Inf = setContext.numsToInterval(3, Double.POSITIVE_INFINITY);
        assertSame(Decoration.DAC, set_3_Inf.getDecoration());

        KaucherInterval kaucher_7_5 = kaucherContext.numsToInterval(7, 5);
        assertSame(Decoration.DAC, kaucher_7_5.getDecoration());

        // Output intervals
        ClassicInterval classic_2_6 = classicContext.numsToInterval(2, 6);
        assertSame(Decoration.COM, classic_2_6.getDecoration());

        SetInterval set_5_Inf = setContext.numsToInterval(5, Double.POSITIVE_INFINITY);
        assertSame(Decoration.DAC, set_5_Inf.getDecoration());

        KaucherInterval kaucher_7_6 = kaucherContext.numsToInterval(7, 6);
        assertSame(Decoration.DAC, kaucher_7_6.getDecoration());

        ClassicInterval classic_9_10_COM = classicContext.numsToInterval(9, 10);
        assertSame(Decoration.COM, classic_9_10_COM.getDecoration());

        // All contexts returns the same result decorated by COM
        ClassicInterval c1 = algorithm(classic_0_1, classic_2_5, classicContext);
        SetInterval s1 = algorithm(classic_0_1, classic_2_5, classicContext);
        KaucherInterval k1 = algorithm(classic_0_1, classic_2_5, classicContext);
        SetInterval s2 = algorithm(classic_0_1, classic_2_5, setContext);
        KaucherInterval k3 = algorithm(classic_0_1, classic_2_5, kaucherContext);
        assertEquals(classic_2_6, c1);
        assertEquals(classic_2_6, s1);
        assertEquals(classic_2_6, k1);
        assertEquals(classic_2_6, s2);
        assertEquals(classic_2_6, k3);
        assertTrue(c1.isCommonInterval());
        assertTrue(s1.isCommonInterval());
//        assertTrue(k1.isCommonInterval());
        assertTrue(s2.isCommonInterval());
//        assertTrue(k3.isCommonInterval());

        // Only set context is applicable here.
        // Result is decorated by DAC.
        SetInterval s4 = algorithm(classic_2_5, set_3_Inf, setContext);
        assertEquals(set_5_Inf, s4);
        assertFalse(s4.isCommonInterval());

        // Only kaucher context is applicable here
        // Result os decorated by DAC.
        KaucherInterval k5 = algorithm(classic_0_1, kaucher_7_5, kaucherContext);
        assertEquals(kaucher_7_6, k5);
//        assertFalse(k5.isCommonInterval());

        // Only kaucher context is applicable here
        // Result os decorated by DAC, though k6 is classic interval
        KaucherInterval k6 = algorithm(classic_2_5, kaucher_7_5, kaucherContext);
        assertFalse(classic_9_10_COM.equals(k6));
//        assertTrue(k6.isCommonInterval());
    }

    @Test
    public void testLevel2() {
        System.out.println("level2");
        SetInterval set_0_1 = SetIntervalOps.nums2(0, 1);
        Level2SetIntervalInfSupBinary64 set64_0_1 = Level2SetIntervalInfSupBinary64.numsToInterval(0, 1);
        Level2SetIntervalInfSupBinary128 set128_0_1 = Level2SetIntervalInfSupBinary128.numsToInterval(0, 1);

        assertEquals("[0,1]_com", set_0_1.toStringDecorated());
        assertEquals("InfSupBinary64[0,1]_com", set64_0_1.toStringDecorated());
        assertEquals("InfSupBinary128[0,1]_com", set128_0_1.toStringDecorated());

        assertTrue(set_0_1.equal(set_0_1));
        assertTrue(set_0_1.equal(set64_0_1));
        assertTrue(set_0_1.equal(set128_0_1));
        assertTrue(set64_0_1.equal(set_0_1));
        assertTrue(set64_0_1.equal(set64_0_1));
        assertTrue(set64_0_1.equal(set128_0_1));
        assertTrue(set128_0_1.equal(set_0_1));
        assertTrue(set128_0_1.equal(set64_0_1));
        assertTrue(set128_0_1.equal(set128_0_1));

        assertEquals(set_0_1, set_0_1);
        assertEquals(set64_0_1, set64_0_1);
        assertEquals(set128_0_1, set128_0_1);

        assertFalse(set_0_1.equals(set64_0_1));
        assertFalse(set64_0_1.equals(set_0_1));
        assertFalse(set_0_1.equals(set128_0_1));
        assertFalse(set128_0_1.equals(set_0_1));
        assertFalse(set64_0_1.equals(set128_0_1));
        assertFalse(set128_0_1.equals(set64_0_1));
    }
}
