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
package net.java.jinterval.symbolic.fdlibm;

import net.java.jinterval.rational.Rational;

/**
 *
 */
public class BernoulliNumbers {

    private static final Rational[] numbers = {
        Rational.valueOf(1, 1), // 0
        Rational.valueOf(1, 2), // 1
        Rational.valueOf(1, 6), // 2
        Rational.zero(), // 3
        Rational.valueOf(-1, 30), // 4
        Rational.zero(), // 5
        Rational.valueOf(1, 42), // 6
        Rational.zero(), // 7
        Rational.valueOf(-1, 30), // 8
        Rational.zero(), // 9
        Rational.valueOf(5, 66), // 10
        Rational.zero(), // 11
        Rational.valueOf(-691, 2730), // 12
        Rational.zero(), // 13
        Rational.valueOf(7, 6), // 14
        Rational.zero(), // 15
        Rational.valueOf(-3617, 510), // 16
        Rational.zero(), // 17
        Rational.valueOf(43867, 798), // 18
        Rational.zero(), // 19
        Rational.valueOf(-174611, 330) // 20
    };

    public static Rational getBernoulliNumber(int n) {
        return numbers[n];
    }
}
