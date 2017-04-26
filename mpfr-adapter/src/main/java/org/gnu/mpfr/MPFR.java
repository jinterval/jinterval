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
package org.gnu.mpfr;

import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.LongByReference;

/**
 *
 */
public class MPFR {

    static {
        Native.register("mpfr");
    }
    /**
     * round to nearest,with ties to even
     */
    public static final int MPFR_RNDN = 0;
    /**
     * round toward zero
     */
    public static final int MPFR_RNDZ = 1;
    /**
     * round toward +Inf
     */
    public static final int MPFR_RNDU = 2;
    /**
     * round toward -Inf
     */
    public static final int MPFR_RNDD = 3;
    /**
     * round away from zero
     */
    public static final int MPFR_RNDA = 4;
    /**
     * faithful rounding (not implemented yet)
     */
    public static final int MPFR_RNDF = 5;
    /**
     * round to nearest, with ties away from zeros (mpfr_round)
     */
    public static final int MPFR_RNDNA = -1;

    // Initialization Functions
    public static native void mpfr_init2(MPFR_T x, long prec);

    public static native void mpfr_clear(MPFR_T x);

    public static native void mpfr_set_prec(MPFR_T x, long prec);

    public static native int mpfr_get_prec(MPFR_T x);

    // Assignment Functions
    public static native int mpfr_set(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_set_ui(MPFR_T rop, long op, int rnd);

    public static native int mpfr_set_si(MPFR_T rop, long op, int rnd);

    public static native int mpfr_set_d(MPFR_T rop, double op, int rnd);

    public static native int mpfr_set_ui_2exp(MPFR_T rop, long op, int e, int rnd);

    public static native int mpfr_set_si_2exp(MPFR_T rop, long op, int e, int rnd);

    public static native int mpfr_set_str(MPFR_T rop, String s, int base, int rnd);

    public static native int mpfr_set_nan(MPFR_T rop);

    public static native int mpfr_set_inf(MPFR_T rop, int sign);

    public static native int mpfr_set_zero(MPFR_T rop, int sign);

    public static native int mpfr_swap(MPFR_T x, MPFR_T y);

    // Combined Initialization and Assignment functions
    // Conversion Functions
    public static native float mpfr_get_flt(MPFR_T op, int rnd);

    public static native double mpfr_get_d(MPFR_T op, int rnd);

    public static native long mpfr_get_si(MPFR_T op, int rnd);

    public static native long mpfr_get_ui(MPFR_T op, int rnd);

    public static native double mpfr_get_d_2exp(LongByReference exp, MPFR_T op, int rnd);

//    public static native double mpfr_frexp(LongByReference exp, MPFR_T y, MPFR_T x, int rnd);
    public static native String mpfr_get_str(Pointer str, LongByReference expptr, int b, int n, MPFR_T op, int rnd);

    public static native boolean mpfr_fits_ulong_p(MPFR_T op, int rnd);

    public static native boolean mpfr_fits_slong_p(MPFR_T op, int rnd);

    public static native boolean mpfr_fits_uint_p(MPFR_T op, int rnd);

    public static native boolean mpfr_fits_sint_p(MPFR_T op, int rnd);

    public static native boolean mpfr_fits_ushort_p(MPFR_T op, int rnd);

    public static native boolean mpfr_fits_sshort_p(MPFR_T op, int rnd);

    public static native boolean mpfr_fits_uintmax_p(MPFR_T op, int rnd);

    public static native boolean mpfr_fits_intmax_p(MPFR_T op, int rnd);

    // Basic Arithmetic Functions
    public static native int mpfr_add(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_sub(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_mul(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_sqr(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_div(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_ui_div(MPFR_T rop, long op1, MPFR_T op2, int rnd);

    public static native int mpfr_sqrt(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_cbrt(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_root(MPFR_T rop, MPFR_T op, long k, int rnd);

    public static native int mpfr_pow(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_pow_si(MPFR_T rop, MPFR_T op1, long op2, int rnd);

    public static native int mpfr_neg(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_abs(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_dim(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_mul_2ui(MPFR_T rop, MPFR_T op1, long op2, int rnd);

    public static native int mpfr_mul_2si(MPFR_T rop, MPFR_T op1, long op2, int rnd);

    public static native int mpfr_div_2ui(MPFR_T rop, MPFR_T op1, long op2, int rnd);

    public static native int mpfr_div_2si(MPFR_T rop, MPFR_T op1, long op2, int rnd);

    // Comparison Functions
    public static native int mpfr_cmp(MPFR_T op1, MPFR_T op2);

    public static native int mpfr_cmp_ui(MPFR_T op1, long op2);

    public static native int mpfr_cmp_si(MPFR_T op1, long op2);

    public static native int mpfr_cmp_d(MPFR_T op1, double op2);

    public static native int mpfr_cmp_ui_2exp(MPFR_T op1, long op2, long e);

    public static native int mpfr_cmp_si(MPFR_T op1, long op2, long e);

    public static native boolean mpfr_nan_p(MPFR_T x);

    public static native boolean mpfr_inf_p(MPFR_T x);

    public static native boolean mpfr_number_p(MPFR_T x);

    public static native boolean mpfr_zero_p(MPFR_T x);

    public static native boolean mpfr_regular_p(MPFR_T x);

    public static native int mpfr_sgn(MPFR_T x);

    // Special functions
    public static native int mpfr_log(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_log2(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_log10(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_exp(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_exp2(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_exp10(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_cos(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_sin(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_tan(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_acos(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_asin(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_atan(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_atan2(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_cosh(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_sinh(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_tanh(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_acosh(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_asinh(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_atanh(MPFR_T rop, MPFR_T op, int rnd);

    public static native int mpfr_fma(MPFR_T rop, MPFR_T op1, MPFR_T op2, MPFR_T op3, int rnd);

    public static native int mpfr_hypot(MPFR_T rop, MPFR_T op1, MPFR_T op2, int rnd);

    public static native int mpfr_const_pi(MPFR_T rop, int rnd);

    public static native int mpfr_const_euler(MPFR_T rop, int rnd);

    // Exception Related Functions
    public static native long mpfr_get_emin_min();

    public static native long mpfr_get_emin_max();

    public static native long mpfr_get_emax_min();

    public static native long mpfr_get_emax_max();
}
