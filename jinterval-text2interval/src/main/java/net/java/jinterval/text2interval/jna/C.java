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
package net.java.jinterval.text2interval.jna;

import com.sun.jna.Memory;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.PointerByReference;
import java.math.BigDecimal;

/**
 *
 */
public class C {

    static {
        Native.register("c");
    }
    public static final int LC_ALL = 6;

    public static native double strtod(Pointer s, PointerByReference endptr);

    public static native double strtod_l(Pointer s, PointerByReference endptr, Pointer locale);

    public static native Pointer newlocale(int category, String locale, Pointer base);

    public static native void freelocale(Pointer locobj);

    private static void testHalfMinValue() {
        Memory m = new Memory(2000);
        PointerByReference endptr = new PointerByReference();
        Pointer posix = newlocale(LC_ALL, "POSIX", Pointer.NULL);
        String s = new BigDecimal(Double.MIN_VALUE).multiply(new BigDecimal("0.5")).toString();
        m.setString(0, s);
        System.out.println(s);
        double d1 = strtod_l(m, endptr, posix);
        double d2 = Double.parseDouble(s);
        if (d1 != d2) {
            System.out.println(Double.toHexString(strtod_l(m, endptr, posix)));
            System.out.println(Double.toHexString(Double.parseDouble(s)));
        }
    }

    private static void testPowers() {
        Memory m = new Memory(2000);
        PointerByReference endptr = new PointerByReference();
        Pointer posix = newlocale(LC_ALL, "POSIX", Pointer.NULL);
        for (int i = 1023; i >= -1074; i--) {
            double d = Math.scalb(1.0, i);
            double ulp = Math.ulp(d);
            String s = new BigDecimal(d).add(new BigDecimal(ulp).multiply(BigDecimal.valueOf(+0.5))).toString();
            m.setString(0, s);
            double d1 = strtod_l(m, endptr, posix);
            double d2 = Double.parseDouble(s);
            if (d1 != d2) {
                System.out.println(s);
                System.out.println(Double.toHexString(strtod_l(m, endptr, posix)));
                System.out.println(Double.toHexString(Double.parseDouble(s)));
            }
        }
    }

    private static void bench() {
        Memory m = new Memory(2000);
        PointerByReference endptr = new PointerByReference();
        Pointer posix = newlocale(LC_ALL, "POSIX", Pointer.NULL);
//        String s = new BigDecimal(Double.MIN_VALUE).multiply(BigDecimal.valueOf(0.5)).toString();
        String s = " 3.518437208883201171875E+013 ";
        m.setString(0, s);
        System.out.println("m=" + m);
        System.out.println(Double.toHexString(strtod_l(m, endptr, posix)));
        System.out.println(Double.toHexString(Double.parseDouble(s)));
        double sum1 = 0;
        long time0 = System.nanoTime();
        for (int i = 0; i < 1000000; i++) {
            double v = strtod_l(m, endptr, posix);
            sum1 += v;
        }
        double sum2 = 0;
        long time1 = System.nanoTime();
        for (int i = 0; i < 1000000; i++) {
            double v = Double.parseDouble(s);
            sum2 += v;
        }
        long time2 = System.nanoTime();
        assert sum1 == sum2;
        freelocale(posix);
        System.out.println("endptr=" + endptr.getValue());
        System.out.println(sum1 + " " + (time1 - time0) / 1000000);
        System.out.println(sum2 + " " + (time2 - time1) / 1000000);
    }

    private static void bench2() {
        StringBuilder sb = new StringBuilder();
        sb.append("1.");
        for (int i = 0; i < 1000 * 1000; i++) {
            sb.append('1');
        }
        String s = sb.toString();
        Memory m = new Memory(s.length() + 1);
        m.setString(0, s);
        PointerByReference endptr = new PointerByReference();
        Pointer posix = newlocale(LC_ALL, "POSIX", Pointer.NULL);
        long time0 = System.nanoTime();
        double d = strtod_l(m, endptr, posix);
        long time1 = System.nanoTime();
        System.out.println(Double.toHexString(d) + " " + (time1 - time0)/1e6 + "mSec");
        freelocale(posix);
    }
    
    public static void main(String[] args) {
        testHalfMinValue();
        testPowers();
//        bench();
//        bench2();
    }
}
