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
package net.java.jinterval.text2interval.gen;

import java.io.File;
import java.io.IOException;
import java.math.BigInteger;
import java.util.List;
import net.java.jinterval.text2interval.Text2interval;

/**
 *
 */
public class GenPow2 extends GenSupport {

    void gen(File file, List<String> headerLines) throws IOException {
        create(file, headerLines);

        int n = 1075 / 12 + 1;
        BigInteger[][] pows = new BigInteger[n][];
        for (int i = 0; i < n; i++) {
            pows[i] = Text2interval.stringToBlocks(BigInteger.ONE.shiftLeft(i * 12).toString());
        }
        for (int i = 0; i < n; i++) {
            s("static UWtype pow2_" + i * 12 + "[] = {");
            b();
            {
                for (int j = 0; j < pows[i].length; j++) {
                    s(pows[i][j].toString() + "ull,");
                }
            }
            e();
            s("};");
        }
        s("static UWtype* pow2[] = {");
        b();
        {
            for (int i = 0; i < n; i++) {
                s("pow2_" + i * 12 + ",");
            }
        }
        e();
        s("};");
        s();
        s("static int pow2len[] = {");
        b();
        {
            for (int i = 0; i < n; i++) {
                s("sizeof pow2_" + i * 12 + " / sizeof(UWtype),"/*pows[i].length + ","*/);
            }
        }
        e();
        s("};");

        close();
    }
}
