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
import org.bridj.Pointer;
import org.bridj.ann.Library;
import org.bridj.ann.Ptr;
import org.bridj.cpp.mfc.CString;

/**
 * BridJ wrappers of libtestJIntervalGmp library
 */
@Library("textToInterval")
public class LibTextToInterval {

    static {
        BridJ.register();
    }

    /* void* */ public static native Pointer<?> get_addr(/* const char*/  CString var);

    /* const char* */ public static native @Ptr
    long parseExp(
            /* const char* */@Ptr long cp,
            /* DItype* */ @Ptr long expptr);

    /* const char* */ public static native @Ptr
    long parseHex(
            /*const char* */@Ptr long cp);

    /* const char* */ public static native @Ptr
    long parseZeroTail(
            /* const char* */@Ptr long cp,
            /* const char* */ @Ptr long cp0);

    /* const char * */ public static native @Ptr
    long skip_whitespaces(
            /*const char* */@Ptr long cp);

    /* const char * */ public static native @Ptr
    long scan_decimal(
            /* const char* */@Ptr long cp);

    /* const char* */ public static native @Ptr
    long parseRat(
            /* const char* */@Ptr long cp,
            /* const char* */ @Ptr long begp);

    public static native void convertDec(int log10ceiling, int fracExp, int hasMore);

    public static native void convert();

    /* const char* */ public static native @Ptr
    long parseNum(
            /* const char* */@Ptr long cp);

    /* const char* */ public static native @Ptr
    long parseUncertain(
            /* const char* */@Ptr long cp);

    public static native void textToInterval(
            /* const char* */@Ptr long cp,
            /* DECORATED_INFSUP_B64* */ @Ptr long ret);
}
