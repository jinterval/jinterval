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
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

/**
 *
 */
public class GenTest extends GenBase {

    void gen(File file, List<String> headerLines, int digitBlockSize, int numDigitBlocks) throws IOException {
        create(file, headerLines);
        genIncludes(digitBlockSize, numDigitBlocks, true);
        s();
        genParseRat();
        s();
        genMakeBBits(digitBlockSize);
        s();
        genConvert(digitBlockSize);
        s();
        genParseNum();
        close();
    }

    @Override
    protected void genStaticVars(int digitBlockSize) {
        super.genStaticVars(digitBlockSize);
        s("static UWtype bBits[NUM_DIGIT_BLOCKS];");
        s();
        genLong10pow(digitBlockSize);
        s();
        genSmall10pow();
        s();
    }

    @Override
    protected Collection<String> getStaticVarNames() {
        List<String> result = new ArrayList<String>(super.getStaticVarNames());
        result.addAll(Arrays.asList("bBits", "long10pow", "small10pow"));
        return result;
    }

    private void genLong10pow(int digitBlockSize) {
        s("const static unsigned long long long10pow[] = {");
        b();
        for (int i = 0; i <= digitBlockSize; i++) {
            String s = "1";
            for (int j = 0; j < i; j++) {
                s += "0";
            }
            s(s + "ull,");
        }
        e();
        s("};");
    }

    private void genSmall10pow() {
        s("/*");
        s(" * All the positive powers of 10 that can be");
        s(" * represented exactly in double/float.");
        s(" */");
        s("const static double small10pow[] = {");
        b();
        for (int i = 0; i < 23; i++) {
            s("1.0e" + i + ",");
        }
        e();
        s("};");
    }

    private void genParseRat() {
        bFun("const char* parseRat(const char *cp, const char *begp, UWtype hp)");
        {
            s("const char *endp = cp;");
            s("set_digits(&p, begp, endp);");
            s("char c = *++cp;");
            bWhile("c == '0'");
            {
                s("c = *++cp;");
            }
            endWhile();
            s("const char *begq = cp;");
            retIf("c > '9' || c < '0'", "NULL");
            doWhile();
            {
                s("c = *++cp;");
            }
            endDoWhile("c <= '9' && c >= '0'");
            s("set_digits(&q, begq, cp);");
            s("DItype diffLen = (endp - begp) - (cp - begq);");
            bIf("diffLen > 310");
            {
                s("ieeeBits = EXP_MASK;");
            }
            elseIf("diffLen < -330");
            {
                s("ieeeBits = 0;");
            }
            elseIf();
            {
                s("guess_double();");
            }
            endIf();
            bIf("ieeeBits == EXP_MASK");
            {
                s("infBits = EXP_MASK - 1;");
                s("supBits = EXP_MASK;");
                ret("cp");
            }
            endIf();
            bIf("ieeeBits == 0");
            {
                s("infBits = 0;");
                s("supBits = 1;");
                ret("cp");
            }
            endIf();
            s("init_f(ieeeBits);");
            s("int cmp = cmp_loop();");
            s("infBits = cmp >= 0 ? ieeeBits : ieeeBits - 1;");
            s("supBits = cmp <= 0 ? ieeeBits : ieeeBits + 1;");
            ret("cp");
        }
        endFun();
    }

    private void genConvertByFPU() {
    }

    private void genHugeExponents() {
        s("DItype log10ceiling = decExp + nDigits;");
        bIf("log10ceiling < MIN_VALUE_LOG10_CEILING");
        {
            s("infBits = 0;");
            s("supBits = 1;");
            ret("");
        }
        endIf();
        bIf("log10ceiling > MAX_VALUE_LOG10_CEILING");
        {
            s("supBits = EXP_MASK - 1;");
            s("infBits = EXP_MASK;");
            ret("");
        }
        endIf();
    }

    private void genMakeBBits(int digitBIockSize) {
        String limb_t = "UWtype";
        boolean is64 = true;
        bFun("static int makeBBits(" + limb_t + "* bBits, int bBits_length, unsigned long long lValue, const char *p, int nTailDigit)");
        s("// Fill lValue");
        s("int k = bBits_length - 1;");
        if (is64) {
            s("bBits[k] = lValue;");
        } else {
            s("bBits[k] = (" + limb_t + ") lValue;");
            s("bBits[k - 1] = (" + limb_t + ") (lValue >> 32);");
            shortIf("bBits[k - 1] != 0", "k--;");
        }
        s();
        s("// Convert by blocks of nine digits");
        s("int j = 0;");
        bWhile("j < nTailDigit");
        {
            s("int l = nTailDigit - j;");
            shortIf("l > " + digitBIockSize, "l = " + digitBIockSize + ";");
            s(limb_t + " v = 0;");
            s("int i;");
            bFor("i = 0", "i < l", "i++");
            {
                s("char c = *p++;");
                shortIf("c == '.'", "c = *p++;");
                s("v = v * 10 + c - '0';");
            }
            endFor();
            s("j += l;");
            s(limb_t + " tenL = long10pow[l];");
            s(limb_t + " carry = v;");
            bFor("i = bBits_length - 1", "i >= k", "i--");
            {
                s(limb_t + " pL, pH;");
                s("umul_ppmm(pH, pL, tenL, bBits[i]);");
                s("add_ssaaaa(carry, bBits[i], pH, pL, 0, carry);");
            }
            endFor();
            shortIf("carry != 0", "bBits[--k] = (" + limb_t + ") carry;");
        }
        endWhile();
        s();
        s("// Normalization");
        s("int n = bBits_length - k - 1;");
        s("int nLeadingZeros;");
        s("count_leading_zeros(nLeadingZeros, bBits[k]);");
        s("int bitLen = W_TYPE_SIZE - nLeadingZeros;");
        bIf("nLeadingZeros > 0");
        {
            s("assert(bitLen > 0);");
            s("int i;");
            bFor("i = 0", "i < n", "i++");
            {
                s("bBits[i] = (bBits[k + i] << nLeadingZeros) | (bBits[k + i + 1] >> bitLen);");
            }
            endFor();
            s("bBits[n] = bBits[k + n] << nLeadingZeros;");
        }
        elseIf();
        {
            s("memcpy(bBits, bBits + k, (n + 1) * sizeof (" + limb_t + "));");
        }
        endIf();
        ret("W_TYPE_SIZE * n + bitLen");
        endFun();
    }

    private void genSearchP5() {
        String limb_t = "UWtype";
        s("int threshExp;");
        s("struct pow5 *p5;");
        s(limb_t + "* p5bBits;");
        s("int p5nWords;");
        bIf("pentExp >= 0");
        {
            s("p5 = pow5 + pentExp;");
            s("threshExp = binExp + p5->nBits;");
            s("p5bBits = p5->bBitsML;");
            s("p5nWords = p5->nWordsL;");
        }
        elseIf();
        {
            s("p5 = pow5 - pentExp;");
            s("threshExp = binExp - p5->nBits + 1;");
            s("p5bBits = p5->bBitsDL;");
            s("p5nWords = 2;");
        }
        endIf();
        s("// assert \"2^(threshExp - 2) <= Ev < 2^threshExp\"");
    }

    private void genComputeThresh() {
        s("// Partially multiply \"0.bits * 2^binExp\" by p^5");
        s("// Approximation will be \"0.sumH * 2^binExp + 0.sumL * 2^(binExp - W_TYPE_SIZE)\"");
        s("UWtype sumH, sumL;");
        s("umul_ppmm(sumH, sumL, lBits, p5bBits[p5nWords - 1]);");
        s("assert((sumH & 0xC000000000000000ull) != 0);");
        s("/*");
        s(" * Let \"x = 0.xbits * 2^xp\" and \"y = 0.ybits * 2^yp\" are floating numbers, define");
        s(" * m-partial product as");
        s(" *   \"Mult(x, y, m) = (Sum | 0 <= i, 0 <= j, i + j < m |");
        s(" *                     xbits[i*32:(i+1)*32-1]*ybits[j*32:(j+1)*32-1] * 2^(pa + pb - 32*(i+j+2))\"");
        s(" * Let \"sumHL\" is concatenation of 64 bits of sumH and lower 32 bits of \"sumL\".");
        s(" * Estimating cancelled items of partial product and \"sumL\", accuracy of \"sumH\" is 4 bits.");
        s(" */");
        s("// assert \"0.sumHL * 2^threshExp == Mult(0.bits * 2^binExp, 5^pentExp, 2)\"");
        s("// assert \"0 <= Ev - sumH.0 * 2^threshExp  <  4 * 2^(threshExp - 64)\"");
        s();
        s("/*");
        s(" * The accuracy of sumH permits to retain only two adjacent floating-point candidates.");
        s(" *");
        s(" * A vicinity of floating-point number for a given floating precision and");
        s(" * for a given rounding mode is a set of real numbers which rounds to this");
        s(" * floating point number.");
        s(" *");
        s(" * A threshold for a given floating precision and rounding mode is");
        s(" * a real number \"Th = 0.threshBits * 2^threshExp\" , which separates two");
        s(" * adjacent vicinities. Threshold is between adjacent floating-point numbers, for");
        s(" * HALF_* rounding modes and it is floating-point number otherwise.");
        s(" *");
        s(" * The code below chooses two adjacent vicinities and subtract threshold between them");
        s(" * from \"sumHL\". It also prepares in \"ieeeBits\" bit coding of the lower floating-point number");
        s(" * for HALF_* rounding modes, or threshold floating-point number otherwise.");
        s(" */");
        s("int highBit = (sumH & SIGN_MASK) != 0;");
        s("int ieeeExp = threshExp - (highBit ? 1 : 2);");
        s("int ulpExp;");
        s("int threshShift;");
        s("UWtype threshBits;");
        bIf("ieeeExp > -1023");
        {
            bIf("ieeeExp > 1023");
            {
                s("// Double.POSITIVE_INFINTIY or Double.MAX_VALUE");
                s("supBits = EXP_MASK - 1;");
                s("infBits = EXP_MASK;");
                ret("");
            }
            elseIf();
            {
                s("threshShift = (highBit ? 62 - 52 : 61 - 52);");
                s("threshBits = sumH >> threshShift;");
                s("threshBits = threshBits + 1;");
                s("ieeeBits |= (((UWtype) (ieeeExp + 1022)) << 52) + (threshBits >> 1);");
                s("ulpExp = ieeeExp - 52;");
            }
            endIf();
        }
        elseIf();
        {
            s("threshShift = (64 - 1023 - 52) - threshExp;");
            bIf("threshShift >= 64");
            {
                s("infBits = 0;");
                s("supBits = 1;");
                ret("");
            }
            elseIf();
            {
                s("assert(threshShift < 64);");
                s("threshBits = sumH >> threshShift;");
                s("threshBits = threshBits + 1;");
                s("ieeeBits |= threshBits >> 1;");
                s("ulpExp = 1 - 1023 - 52;");
            }
            endIf();
        }
        endIf();

        bIf("threshShift < 62");
        {
            s("assert((1LL << (62 - threshShift)) <= threshBits);");
        }
        elseIf();
        {
            s("assert(1LL <= threshBits);");

        }
        endIf();
        s("assert(threshBits <= (1LL << (64 - threshShift)));");
    }

    private void genCmpBinOpt() {
        String limb_t = "UWtype";
        s("int hasTail = pentExp < 0;");
        s("/*");
        s(" * Define");
        s(" *   \"Diff(m) = (Mult(0.bits * 2^binExp, 5^pentExp, m) - Th) * 2^(32*(m + 1) - threshExp)\".");
        s(" */");
        s("// assert \"|diff| <  Long.MAX_VALUE ? diff == Diff(2) : signum(diff) == signum(Diff(2))\"");
        s();
        s("// Compute Diff(m) until signum(Diff) found.");
        s(limb_t + " diffL = (" + limb_t + ")sumL;");
        s(limb_t + " diffH = (" + limb_t + ")sumH;");
        s(limb_t + " diffHi = (int)(sumH >> 32);");
        bIf("wBits == 1");
        {
            s("int m;");
            bFor("m = 1", "", "m++");
            {
                bIf("(signed)diffHi >= 0");
                {
                    s("diff = diffHi != 0 || diffH != 0 || diffL != 0 || hasTail || m < p5nWords + wBits - 1;");
                    breakFor();
                }
                endIf();
                bIf("diffHi != (" + limb_t + ")-1 || diffH != (" + limb_t + ")-1");
//                bIf("diffHi != -1 || diffH < ("+limb_t+")-1 || diffH == ("+limb_t+")-1 && diffL == 0");
                {
                    s("diff = -1;");
                    breakFor();
                }
                endIf();

                bIf("m >= p5nWords");
                {
                    s("diff = hasTail ? 0 : -1;");
                    breakFor();
                }
                endIf();
                s();
                s("assert (diffHi == -1);");
                s(limb_t + " pH, pL;");
                s("umul_ppmm(pH, pL, bBits[0], p5bBits[m]);");
//                s("add_sssaaaaaa(diffHi, diffH, diffL, diffH, diffL, 0, 0, pH, pL);");
            }
            endFor();
        }
        elseIf();
        {
//            s("diff = cmp_bin(diffHi, diffH, diffL, bBits, wBits, p5bBits, p5nWords, hasTail);");
//            s("printf(\"cmp_bin=%d ieeeBits=%llx threshBits=%llx\\n\", diff, ieeeBits, threshBits);");
        }
        endIf();
        bIf("diff == 0 && pentExp < 0");
        {
//            s("diff = cmp_gmp(bBits, wBits, p5, threshBits, threshShift);");
//            s("printf(\"cmp_gmp=%d ieeeBits=%llx threshBits=%llx\\n\", diff, ieeeBits, threshBits);");
        }
        endIf();
    }

    private void genConvert(int digitBlockSize) {
        bFun("void convert(DItype decExp, const char *p, const char *dotPos, int dotLen, int nDigits, int iDigits, UWtype lValue)");
        s("assert(iDigits == nDigits || iDigits == DIGIT_BLOCK_SIZE);");
        genConvertByFPU();
        genHugeExponents();
        s();
        s("UWtype* bBits = NULL;");
        s("int binExp = 0x80000000;");
        s("// Convert \"digits\" to \"bits\".");
        s("// assert \"Ev == digits.0 * 2^(log10ceiling - nDigits) * 5^pentExp\"");
        s("int nBits; // size of \"bits\".");
        s("int wBits; // size of \"bits\" in words.");
        s("UWtype lBits; // Left-adjusted higher \"bits\".");
        s("int hasMore = 0;");
        bIf("iDigits < nDigits");
        {
            bIf("log10ceiling >= 17");
            {
                bIf("decExp < 0");
                {
                    s("nDigits = log10ceiling;");
                    s("hasMore = 1;");
                }
                endIf();
            }
            elseIf();
            {
                s("int p = log10ceiling - 1;");
                s("int ulpExp = (p >= 0 ? pow5[p].nBits : 1 - pow5[-p].nBits) + p - 53;");
                int minUlpExp = -1022 - 52;
                shortIf("ulpExp < " + minUlpExp, "ulpExp = " + minUlpExp + ";");
                bIf("decExp < ulpExp - 1");
                {
                    s("nDigits = log10ceiling - ulpExp + 1;");
                    s("hasMore = 1;");
                }
                endIf();
            }
            endIf();
            s("int bBits_length = (nDigits + " + (digitBlockSize - 1) + ") / " + digitBlockSize + ";");
            s("assert(bBits_length <= NUM_DIGIT_BLOCKS);");
            s("binExp = makeBBits(bBits, bBits_length, lValue, p, nDigits - iDigits);");
            s("iDigits = nDigits;");
            s("// \"digits\" are longer.");
            s("// Gather all \"digits\" into \"bBits\".");
            s("int n = (binExp - 1) / W_TYPE_SIZE;");
            s("// Remove trailing zero words from \"bBits\".");
            bWhile("bBits[n] == 0");
            {
                s("n--;");
            }
            endWhile();
            s("// Put higher bits form \"bBits\" into \"lBits\", remove \"bBits\" if they fit.");
            s("wBits = n + 1;");
            s("lBits = bBits[0];");
            s("// Calculate \"nBits\".");
            s("int numTrailingZeros;");
            s("count_trailing_zeros(numTrailingZeros, bBits[n]);");
            s("nBits = W_TYPE_SIZE * wBits - numTrailingZeros;");
        }
        elseIf();
        {
            s("int numLeadingZeros, numTrailingZeros;");
            s("count_leading_zeros(numLeadingZeros, lValue);");
            s("count_trailing_zeros(numTrailingZeros, lValue);");
            s("binExp = 64 - numLeadingZeros;");
            s("nBits = binExp - numTrailingZeros;");
            s("lBits = lValue << numLeadingZeros;");
            s("wBits = 1;");
            s("bBits[0] = lBits;");
        }
        endIf();
        s();
        s("int pentExp = log10ceiling - iDigits;");
        s("binExp += pentExp;");
        s("// assert \"Ev == 0.bits * 2^binExp * 5^pentExp\".");
        s();
        genSearchP5();
        s();
        genComputeThresh();
//        s("printf(\"A: threshBits=%llx ulpExp=%d ieeeBits=%llx\\n\", threshBits, ulpExp, ieeeBits);");

        s("int diff;");
        s("assert(iDigits == nDigits);");
        s("sumH -= threshBits << threshShift;");
        genCmpBinOpt();
//            s("printf(\"diff=%d hasMore=%d\\n\", diff, hasMore);");
        shortIf("diff == 0 && hasMore", "diff = 1;");
        s("// Correct ieeeBits");
        shortIf("(threshBits & 2) != 0 && diff >= 0 || diff > 0", "ieeeBits++;");
        s("set_errno:");
        bIf("((ieeeBits + 0x10000000000000ll)&0x7FEFFFFFFFFFFFFFll) == 0");
        {
            s("// setErrno");
        }
        endIf();
        s("union { double d; long long l; } u;");
        s("u.l = ieeeBits;");
//        ret("u.d");
        endFun();
    }

    private void genParseNum() {
        bFun("const char* parseNum(const char *nptr)");
        {
            s("infBits = supBits = 0xFFF8000000000000ull;");
            s("const char *cp = nptr - 1;");
            s("char c;");
            doWhile();
            {
                s("c = *++cp;");
            }
            endDoWhile("ISSPACE (c)");
            s("isNegative = 0;");
            bIf("c == '-' || c == '+'");
            {
                shortIf("c == '-'", "isNegative = 1;");
                s("c = *++cp;");
            }
            endIf();
            s();
            s("const char *mantS = cp;");
            s("const char *dotPos = NULL;");
            s("const char *firstNZ = NULL;");
            s("const char *lastNZ = NULL;");
            s();
            s("int iDigits = 0;");
            s("UWtype lValue = 0;");
            s("UDItype nZeros = 0;");
            s();
//            s("loop:");
            bFor("", "", "");
            {
                bWhile("c <= '9' && c >= '0'");
                {
                    bIf("c > '0'");
                    {
                        bIf("firstNZ == NULL");
                        {
                            s("firstNZ = cp;");
                        }
                        elseIf("iDigits + nZeros <= DIGIT_BLOCK_SIZE");
                        {
                            s("lValue *= long10pow[nZeros];");
                            s("iDigits += nZeros;");
                        }
                        elseIf("iDigits < DIGIT_BLOCK_SIZE");
                        {
                            s("lValue *= long10pow[DIGIT_BLOCK_SIZE - iDigits];");
                            s("iDigits = DIGIT_BLOCK_SIZE;");
                        }
                        endIf();
                        doWhile();
                        {
                            bIf("iDigits < DIGIT_BLOCK_SIZE");
                            {
                                s("lValue = lValue * 10 + (c - '0');");
                                s("iDigits++;");
                            }
                            endIf();
                            s("c = *++cp;");
                        }
                        endDoWhile("c <= '9' && c > '0'");
                        s("lastNZ = cp;");
                    }
                    endIf();
                    s("nZeros = 0;");
                    bWhile("c == '0'");
                    {
                        s("nZeros++;");
                        s("c = *++cp;");
                    }
                    endWhile();
                }
                endWhile();
                s("lastNZ = cp - nZeros;");
                bIf("c == '.'");
                {
                    bIf("dotPos != NULL");
                    {
                        breakFor();
                    }
                    endIf();
                    s("dotPos = cp;");
                    s("c = *++cp;");
                }
                elseIf();
                {
                    breakFor();
                }
                endIf();
            }
            endFor();
            s();
            s("UDItype nDigits = lastNZ - firstNZ;");
            s("DItype fracExp;");
            bIf("dotPos != NULL");
            {
                s("fracExp = dotPos - lastNZ;");
                bIf("lastNZ > dotPos");
                {
                    s("fracExp++;");
                    shortIf("firstNZ < dotPos", "nDigits--;");
                }
                endIf();
            }
            elseIf();
            {
                s("fracExp = cp - lastNZ;");
            }
            endIf();
            s();
            retIf("nDigits == 0", "parseZeroTail(cp, mantS)");
            s();
            bIf("c == '/'");
            {
                retIf("dotPos != NULL", "NULL");
                ret("parseRat(cp, firstNZ, lValue);");
            }
            endIf();
            s("DItype decExp = 0;");
            bIf("c == 'E' || c == 'e'");
            {
                s("cp = parseExp(cp, &decExp);");
                bIf("cp == NULL");
                {
                    ret("nptr");
                }
                endIf();
            }
            endIf();
            s();
            s("const char *tailI;");
            bIf("iDigits < nDigits");
            {
                s("tailI = firstNZ + iDigits;");
                shortIf("dotPos > firstNZ && dotPos <= tailI", "tailI++;");
            }
            elseIf();
            {
                s("tailI = lastNZ;");
            }
            endIf();
            // ret("convert(isNegative, decExp + fracExp, tailI, dotPos, dotLen, nDigits, iDigits, lValue);");
            ret("NULL");
        }
        endFun();
    }
}
