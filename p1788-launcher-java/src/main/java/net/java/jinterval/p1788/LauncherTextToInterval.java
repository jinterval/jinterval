/*
 * Copyright (c) 2012, JInterval Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. * Redistributions in
 * binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
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
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.p1788;

import net.java.jinterval.p1788.bridj.DECORATED_INFSUP_B64;
import net.java.jinterval.p1788.bridj.LibGmp;
import net.java.jinterval.p1788.bridj.LibTextToInterval;
import net.java.jinterval.p1788.bridj.LibTextToIntervalGmp;
import org.bridj.Pointer;
import org.bridj.ann.Ptr;

/**
 *
 */
public class LauncherTextToInterval {

    static Pointer<LibGmp.AllocateFunction> oldAlloc;
    static Pointer<LibGmp.ReallocateFunction> oldRealloc;
    static Pointer<LibGmp.FreeFunction> oldFree;

    static long allocationCount = 0;
    static long curAllocated = 0;
    static long maxAllocated = 0;
    static long totalAllocated = 0;

    private static void printStat() {
        System.out.printf("allocationCount=%d curAllocation=%d maxAllocation=%d totalAllocation=%d\n",
                allocationCount, curAllocated, maxAllocated, totalAllocated);
    }

    static LibGmp.AllocateFunction allocCounter = new LibGmp.AllocateFunction() {

        @Override
        public @Ptr
        long apply(@Ptr long size) {
            allocationCount++;
            curAllocated += size;
            if (curAllocated > maxAllocated) {
                maxAllocated = curAllocated;
            }
            totalAllocated += size;
            return oldAlloc.get().apply(size);
        }
    };

    static LibGmp.ReallocateFunction reallocCounter = new LibGmp.ReallocateFunction() {

        @Override
        public @Ptr
        long apply(@Ptr long ptr, long old_size, long new_size) {
            allocationCount++;
            curAllocated += new_size - old_size;
            if (curAllocated > maxAllocated) {
                maxAllocated = curAllocated;
            }
            totalAllocated += new_size;
            return oldRealloc.get().apply(ptr, old_size, new_size);
        }

    };

    static LibGmp.FreeFunction freeCounter = new LibGmp.FreeFunction() {

        @Override
        public void apply(@Ptr long ptr, long size) {
            curAllocated -= size;
            oldFree.get().apply(ptr, size);
        }

    };

    public static void main(String[] args) {

        Pointer<Pointer<LibGmp.AllocateFunction>> allocPtr = Pointer.allocatePointer(LibGmp.AllocateFunction.class);
        Pointer<Pointer<LibGmp.ReallocateFunction>> reallocPtr = Pointer.allocatePointer(LibGmp.ReallocateFunction.class);
        Pointer<Pointer<LibGmp.FreeFunction>> freePtr = Pointer.allocatePointer(LibGmp.FreeFunction.class);
        LibGmp.__gmp_get_memory_functions(allocPtr, reallocPtr, freePtr);
        oldAlloc = allocPtr.get();
        oldRealloc = reallocPtr.get();
        oldFree = freePtr.get();
        LibGmp.__gmp_set_memory_functions(allocCounter.toPointer(), reallocCounter.toPointer(), freeCounter.toPointer());

        int l = 1000000;
//        l = 426281;
        l = 420921;
        StringBuilder sb = new StringBuilder();
        switch (1) {
            case 1:
                sb.append("[1");
                for (int i = 0; i < l; i++) {
                    sb.append('0');
                }
                sb.append("2/1");
                for (int i = 0; i < l; i++) {
                    sb.append('0');
                }
                sb.append("1]");
                break;
            case 2:
                sb.append("[1.");
                for (int i = 0; i < l; i++) {
                    sb.append('0');
                }
                sb.append("1]");
                break;
            case 3:
                sb.append("1");
                for (int i = 0; i < l; i++) {
                    sb.append('0');
                }
                sb.append("2");
                break;
        }
        String s = sb.toString();
//        long start1 = System.currentTimeMillis();
//        SetInterval result1 = ictx.text2interval(s);
//        long stop1 = System.currentTimeMillis();
        Pointer<Byte> mem = Pointer.allocateBytes(s.length() + 1);
        mem.setCString(s);
        Pointer<DECORATED_INFSUP_B64> result = Pointer.getPointer(new DECORATED_INFSUP_B64());
        printStat();

        result.get().inf(Double.NaN);
        result.get().sup(Double.NaN);
        long start2 = System.currentTimeMillis();
        LibTextToInterval.textToInterval(mem.getPeer(), result.getPeer());
        long stop2 = System.currentTimeMillis();
        System.out.println("inf=" + result.get().inf());
        System.out.println("sup=" + result.get().sup());
        System.out.println("decoration=" + result.get().decoration());
        System.out.println((stop2 - start2) / 1000. + " " + result.get());
        printStat();

        result.get().inf(Double.NaN);
        result.get().sup(Double.NaN);
        long start3 = System.currentTimeMillis();
        LibTextToIntervalGmp.textToDecoratedInfsupB64_gmp_sloppy(mem.getPeer(), result.getPeer());
        long stop3 = System.currentTimeMillis();
        System.out.println("inf=" + result.get().inf());
        System.out.println("sup=" + result.get().sup());
        System.out.println("decoration=" + result.get().decoration());
        System.out.println((stop3 - start3) / 1000. + " " + result.get());
        printStat();

        result.get().inf(Double.NaN);
        result.get().sup(Double.NaN);
        long start4 = System.currentTimeMillis();
        LibTextToIntervalGmp.textToDecoratedInfsupB64_gmp_strict(mem.getPeer(), result.getPeer());
        long stop4 = System.currentTimeMillis();
        System.out.println("inf=" + result.get().inf());
        System.out.println("sup=" + result.get().sup());
        System.out.println("decoration=" + result.get().decoration());
        System.out.println((stop4 - start4) / 1000. + " " + result.get());
        printStat();
    }
}
