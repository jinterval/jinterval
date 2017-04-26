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
 * @author nadezhin
 */
abstract class BinaryDouble extends Binary {

    final double value;

    BinaryDouble(double value) {
        this.value = value;
    }

    @Override
    public double doubleValue(RoundingMode roundingMode) {
        return value;
    }

    @Override
    public double doubleValueUp() {
        return value;
    }

    @Override
    public double doubleValueDown() {
        return value;
    }

    @Override
    public double doubleValueCeiling() {
        return value;
    }

    @Override
    public double doubleValueFloor() {
        return value;
    }

    @Override
    public double doubleValueHalfUp() {
        return value;
    }

    @Override
    public double doubleValueHalfDown() {
        return value;
    }

    @Override
    public double doubleValueHalfEven() {
        return value;
    }

    @Override
    public double doubleValueExact() {
        return value;
    }

    @Override
    public float floatValue() {
        return (float) value;
    }

    @Override
    public double doubleValue() {
        return value;
    }

    @Override
    public int hashCode() {
        long bits = Double.doubleToRawLongBits(value);
        return (int) (bits ^ (bits >>> 32));
    }

    @Override
    public boolean equals(Object o) {
        return o instanceof BinaryDouble && value == ((BinaryDouble) o).value;
    }
}
