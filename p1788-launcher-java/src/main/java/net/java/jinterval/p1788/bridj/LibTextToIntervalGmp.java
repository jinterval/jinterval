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
package net.java.jinterval.p1788.bridj;

import org.bridj.BridJ;
import org.bridj.ann.Library;
import org.bridj.ann.Ptr;

/**
 * BridJ wrappers of libtestJIntervalGmp library
 */
@Library(value = "textToIntervalGmp", dependencies = {"gmp"})
public class LibTextToIntervalGmp {

    static {
        BridJ.register();
    }

    public static native int textToDecoratedInfsupB64_gmp_sloppy(
            /* const char* */@Ptr long text,
            /* DECORATED_INFSUP_B64* */ @Ptr long interval);

    public static native int textToDecoratedInfsupB64_gmp_strict(
            /* const char* */@Ptr long text,
            /* DECORATED_INFSUP_B64* */ @Ptr long interval);

    public static native int textToBareInfsupB64_gmp_sloppy(
            /* const char* */@Ptr long text,
            /* BARE_INFSUP_B64* */ @Ptr long interval);

    public static native int textToBareInfsupB64_gmp_strict(
            /* const char* */@Ptr long text,
            /* BARE_INFSUP_B64* */ @Ptr long interval);
}
