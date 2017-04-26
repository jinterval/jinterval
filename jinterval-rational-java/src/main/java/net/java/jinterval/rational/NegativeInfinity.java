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
package net.java.jinterval.rational;

import java.math.RoundingMode;

/**
 * Singleton class that represents Negative Infinity.
 */
class NegativeInfinity extends Infinity {

    static final NegativeInfinity INSTANCE = new NegativeInfinity();

    private NegativeInfinity() {
        super(-1);
    }

    @Override
    public int signum() {
        return -1;
    }

    @Override
    public int compareTo(ExtendedRational that) {
        return that.isNegativeInfinity() ? 0 : -1;
    }

    @Override
    int compareTo(BinaryImpl that) {
        return -1;
    }

    @Override
    int compareTo(BinaryDoubleImpl that) {
        return -1;
    }

    @Override
    public float floatValue(RoundingMode roundingMode) {
        return Float.NEGATIVE_INFINITY;
    }

    @Override
    public int intValue() {
        return Integer.MIN_VALUE;
    }

    @Override
    public long longValue() {
        return Long.MIN_VALUE;
    }

    @Override
    public String toString() {
        return "-inf";
    }

    @Override
    public String toHexString(BinaryValueSet valueSet) {
        return "-inf";
    }
}
