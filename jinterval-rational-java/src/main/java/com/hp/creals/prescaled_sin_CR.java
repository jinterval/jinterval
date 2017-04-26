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
package com.hp.creals;

import java.math.BigInteger;

/**
 * Representation of the cosine of a constructive real. Private. Uses a Taylor
 * series expansion. Assumes |x| < 1.
 */
public class prescaled_sin_CR extends slow_CR {

    CR op;

    public prescaled_sin_CR(CR x) {
        op = x;
    }

    protected BigInteger approximate(int p) {
        if (p >= 1) {
            return big0;
        }
        int iterations_needed = -p / 2 + 4;  // conservative estimate > 0.
        //  Claim: each intermediate term is accurate
        //  to 2*2^calc_precision.
        //  Total rounding error in series computation is
        //  2*iterations_needed*2^calc_precision,
        //  exclusive of error in op.
        int calc_precision = p - bound_log2(2 * iterations_needed)
                - 4; // for error in op, truncation.
        int op_prec = p - 2;
        BigInteger op_appr = op.get_appr(op_prec);
        // Error in argument results in error of < 1/4 ulp.
        // Cumulative arithmetic rounding error is < 1/16 ulp.
        // Series truncation error < 1/16 ulp.
        // Final rounding error is <= 1/2 ulp.
        // Thus final error is < 1 ulp.
        BigInteger current_term;
        int n;
        BigInteger max_trunc_error =
                big1.shiftLeft(p - 4 - calc_precision);
        n = 1;
        current_term = op_appr.shiftLeft(op_prec - calc_precision);
        BigInteger current_sum = current_term;
        while (current_term.abs().compareTo(max_trunc_error) >= 0) {
            if (Thread.interrupted() || please_stop) {
                throw new AbortedError();
            }
            n += 2;
            /*
             * current_term = - current_term * op * op / n * (n - 1)
             */
            current_term = scale(current_term.multiply(op_appr), op_prec);
            current_term = scale(current_term.multiply(op_appr), op_prec);
            BigInteger divisor = BigInteger.valueOf(-n).multiply(BigInteger.valueOf(n - 1));
            current_term = current_term.divide(divisor);
            current_sum = current_sum.add(current_term);
        }
        return scale(current_sum, calc_precision - p);
    }
}
