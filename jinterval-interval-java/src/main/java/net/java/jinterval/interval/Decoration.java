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

/**
 *
 */
public enum Decoration {

    /**
     * ill-formed
     */
    ILL,
    /**
     * trivial
     */
    TRV,
    /**
     * defined
     */
    DEF,
    /**
     * defined & continuous
     */
    DAC,
    /**
     * common
     */
    COM;

    public Decoration min(Decoration that) {
        return this.ordinal() <= that.ordinal() ? this : that;
    }

    public Decoration max(Decoration that) {
        return this.ordinal() >= that.ordinal() ? this : that;
    }

    public boolean possiblyUndefined() {
        return this.ordinal() <= TRV.ordinal();
    }

    public byte enc(boolean isEmpty) {
        byte enc = (byte) (ordinal() << 2);
        if (isEmpty) {
            if (enc == ENC_TRV) {
                enc = ENC_EMPTY;
            } else if (enc > ENC_TRV) {
                throw new IllegalArgumentException();
            }
        } else if (enc == ENC_ILL) {
            throw new IllegalArgumentException();
        }
        return enc;
    }

    public static Decoration byEnc(byte enc) {
        switch (enc) {
            case ENC_ILL:
                return ILL;
            case ENC_EMPTY:
            case ENC_TRV:
                return TRV;
            case ENC_DEF:
                return DEF;
            case ENC_DAC:
                return DAC;
            case ENC_COM:
                return COM;
            default:
                throw new IllegalArgumentException();
        }
    }

    public static final byte ENC_ILL = 0 << 2;
    public static final byte ENC_EMPTY = 2;
    public static final byte ENC_TRV = 1 << 2;
    public static final byte ENC_DEF = 2 << 2;
    public static final byte ENC_DAC = 3 << 2;
    public static final byte ENC_COM = 4 << 2;
}
