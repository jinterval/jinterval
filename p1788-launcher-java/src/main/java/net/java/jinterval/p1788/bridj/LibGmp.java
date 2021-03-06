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
import org.bridj.Callback;
import org.bridj.Pointer;
import org.bridj.ann.Library;
import org.bridj.ann.Ptr;

/**
 * BridJ wrappers of libgmp library
 */
@Library("gmp")
public class LibGmp {

    static {
        BridJ.register();
    }

    public static abstract class AllocateFunction extends Callback<AllocateFunction> {

        public abstract @Ptr
        long apply(long size);
    }

    public static abstract class ReallocateFunction extends Callback<ReallocateFunction> {

        public abstract @Ptr
        long apply(@Ptr long ptr, long old_size, long new_size);
    }

    public static abstract class FreeFunction extends Callback<FreeFunction> {

        public abstract void apply(@Ptr long ptr, long size);
    }

    public static native long __gmpn_set_str(@Ptr long rp, @Ptr long str, long strsize, int base);

    public static native void __gmp_get_memory_functions(
            Pointer<Pointer<AllocateFunction>> allocFuncPtr,
            Pointer<Pointer<ReallocateFunction>> reallocFuncPtr,
            Pointer<Pointer<FreeFunction>> freeFuncPtr);

    public static native void __gmp_set_memory_functions(
            Pointer<AllocateFunction> allocFuncPtr,
            Pointer<ReallocateFunction> reallocFuncPtr,
            Pointer<FreeFunction> freeFuncPtr);
}
