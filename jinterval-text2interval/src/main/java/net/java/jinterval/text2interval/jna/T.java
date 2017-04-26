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

import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.DoubleByReference;

/**
 *
 */
public class T {

    static {
        Native.register("test");
    }
    public static final Pointer long10pow = T.get_addr("long10pow");
    public static final Pointer pow2 = T.get_addr("pow2");
    public static final Pointer pow2len = T.get_addr("pow2len");
    public static final Pointer fnBlocks = T.get_addr("fnBlocks");
    public static final Pointer fdBlocks = T.get_addr("fdBlocks");
    public static final Pointer fnLen = T.get_addr("fnLen");
    public static final Pointer fdLen = T.get_addr("fdLen");
    public static final Pointer s = T.get_addr("s");
    public static final Pointer pChars = T.get_addr("pChars");
    public static final Pointer qChars = T.get_addr("qChars");
    public static final Pointer pBlocks = T.get_addr("pBlocks");
    public static final Pointer qBlocks = T.get_addr("qBlocks");
    public static final StructBlockBuffer p = new StructBlockBuffer(T.get_addr("p"));
    public static final StructBlockBuffer q = new StructBlockBuffer(T.get_addr("q"));
    public static final Pointer curpow = T.get_addr("curpow");
    public static final Pointer diff_high = T.get_addr("diff_high");
    public static final Pointer diff_hi = T.get_addr("diff_hi");
    public static final Pointer diff_lo = T.get_addr("diff_lo");
    public static final Pointer ieeeBits = T.get_addr("ieeeBits");
    public static final Pointer infBits = T.get_addr("infBits");
    public static final Pointer supBits = T.get_addr("supBits");

    public static native Pointer get_addr(String var);

    public static native int get_num_digit_blocks();

    public static native void diff_add_mult(long x, long y);

    public static native void add_mult_pd(int n, Pointer p, Pointer fd);

    public static native void diff_sub_mult(long x, long y);

    public static native void sub_mult_qn(int n, Pointer q, Pointer fn);

    public static native void diff_mult_this_by(long x);

    public static native int multiply_mod_ten(Pointer dst, Pointer src, int srcLen, long m);

    public static native long mul_1(Pointer dst, Pointer src, int srcLen, long m);

    public static native int init_mult(Pointer dst, int e, long m);

    public static native void init_f(long fBits);

    public static native void loop_init_f(int count, long[] fBits);

    public static native char get_s(int i);

    public static native long get_partial_block(Pointer p, int l);

    public static native long get_full_block(Pointer p);

    public static native int conv_dec(Pointer src, int srcDigits, Pointer dst);

    public static native int loop_conv_dec(int count, Pointer src, int srcDigits, Pointer dst);

    public static native void set_digits(StructBlockBuffer bb, Pointer beg, Pointer end);

    public static native void request(StructBlockBuffer bb, long minpow, int l);

    public static native long guess_double();

    public static native void do_pow();

    public static native int one_step();

    public static native int cmp_loop();

    public static native Pointer parseExp(Pointer cp, Pointer exp);

    public static native Pointer parseHex(Pointer cp);

    public static native Pointer parseNum(Pointer cp);

    public static native void textToInterval(Pointer cp, DecoratedInfSupB64 ret);
}
