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
public class GenPow5 extends GenSupport {

    void gen(File file, List<String> headerLines) throws IOException {
        create(file, headerLines);

        int n = 330;
        Text2interval.Pow5[] pow5s = new Text2interval.Pow5[n];
        for (int i = 0; i < n; i++) {
            pow5s[i] = new Text2interval.Pow5(i);
        }

        for (int i = 0; i < n; i++) {
            s("static UWtype pow5_bits_" + i + "[] = {");
            b();
            {
                BigInteger b = pow5s[i].pow5;
                int nw = (b.bitLength() + 63) / 64;
                b = b.shiftLeft(64 * nw - b.bitLength());
                for (int j = 0; j < nw; j++) {
                    s("0x" + b.shiftRight(j * 64).mod(BigInteger.ONE.shiftLeft(64)).toString(16) + "ull,");
                }
            }
            e();
            s("};");
        }


        s("static struct pow5 {");
        b();
        {
            s("int nBits; // Nubmer of bits in p^n");
//            s("int nWords;");
            s("int nWordsL;");
//            s("UWtype lbits; // 64 least-significand bits of p^n");
//            s("unsigned int* bBitsM; // Left-justified bits of p^n");
//            s("unsigned int* bBitsD; // A few first bits of p^n");
            s("UWtype *bBitsML;");
            s("UWtype bBitsDL[2];");
        }
        e();
        s("} pow5[] = {");
        b();
        {
            for (int i = 0; i < n; i++) {
                Text2interval.Pow5 p5 = pow5s[i];
                BigInteger b = p5.pow5;
                int nw = (b.bitLength() + 63) / 64;
                s("/* " + i + " */ { " + p5.ep + ", " + nw + ", pow5_bits_" + i + ","
                        //                        + " {0x" + Long.toHexString(p5.lp) + "ull, 0x" + Long.toHexString(p5.hp) + "ull},"
                        + " {0x" + Long.toHexString(p5.ln) + "ull, 0x" + Long.toHexString(p5.hn) + "ull}},");
            }
        }
        e();
        s("};");

        close();
    }
}
