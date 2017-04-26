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
import java.util.List;

/**
 *
 */
public class GenParse extends GenBase {

    void gen(File file, List<String> headerLines, int digitBlockSize, int numDigitBlocks) throws IOException {
        create(file, headerLines);
        genIncludes(digitBlockSize, numDigitBlocks, true);
        s();
        genSkipWhitespaces();
        s();
        genScanDecimal();
        s();
        genParseRat();
        s();
        genConvertDec();
        s();
        genConvert();
        s();
        genParseNum();
        s();
        genParseUncertain();
        s();
        genText2Interval();
        close();
    }

    private void genSkipWhitespaces() {
        bFun("const char *skip_whitespaces(const char *cp)");
        {
            s("cp--;");
            s("char c;");
            doWhile();
            {
                s("c = *++cp;");
            }
            endDoWhile("ISSPACE (c)");
            ret("cp");
        }
        endFun();
    }

    private void genScanDecimal() {
        s("// OUT isNegative, mantS, firstNZ, dotPos");
        bFun("const char *scan_decimal(const char *cp)");
        {
            s("cp = skip_whitespaces(cp);");
            s("char c = *cp;");
            s("isNegative = 0;");
            bIf("c == '-' || c == '+'");
            {
                shortIf("c == '-'", "isNegative = 1;");
                s("c = *++cp;");
            }
            endIf();
            s();
            s("mantS = cp;");
            s("firstNZ = NULL;");
            s("dotPos = NULL;");
            s("const char *lastNZ = NULL;");
            s();
            bWhile("c == '0'");
            {
                s("c = *++cp;");
            }
            endWhile();
            shortIf("c <= '9' && c > '0'", "firstNZ = cp;");
            bWhile("c <= '9' && c >= '0'");
            {
                shortIf("c > '0'", "lastNZ = cp;");
                s("c = *++cp;");
            }
            endWhile();
            bIf("c == '.'");
            {
                s("dotPos = cp;");
                s("c = *++cp;");
                bIf("firstNZ == NULL");
                {
                    bWhile("c == '0'");
                    {
                        s("c = *++cp;");
                    }
                    endWhile();
                    shortIf("c <= '9' && c > '0'", "firstNZ = cp;");
                }
                endIf();
                bWhile("c <= '9' && c >= '0'");
                {
                    shortIf("c > '0'", "lastNZ = cp;");
                    s("c = *++cp;");
                }
                endWhile();
            }
            endIf();
            bIf("firstNZ == NULL");
            {
                s("nDigits = 0;");
                s("log10ceiling = fracExp = ulpExp = dotPos != NULL ? dotPos - cp + 1 : 0;");
                ret("cp");
            }
            endIf();
            s("assert(lastNZ != NULL);");
            s("lastNZ++;");
            s("nDigits = lastNZ - firstNZ;");
            bIf("dotPos == NULL");
            {
                s("log10ceiling = cp - firstNZ;");
                s("fracExp = cp - lastNZ;");
                s("ulpExp = 0;");
            }
            elseIf("lastNZ <= dotPos");
            {
                s("log10ceiling = dotPos - firstNZ;");
                s("fracExp = dotPos - lastNZ;");
                s("ulpExp = dotPos - cp + 1;");
            }
            elseIf("dotPos < firstNZ");
            {
                s("log10ceiling = (dotPos - firstNZ) + 1;");
                s("fracExp = (dotPos - lastNZ) + 1;");
                s("ulpExp = dotPos - cp + 1;");
            }
            elseIf();
            {
                s("log10ceiling = dotPos - firstNZ;");
                s("fracExp = (dotPos - lastNZ) + 1;");
                s("nDigits--;");
                s("ulpExp = dotPos - cp + 1;");
            }
            endIf();
            ret("cp");
        }
        endFun();
    }

    private void genParseRat() {
        bFun("const char* parseRat(const char *cp, const char *begp)");
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
                s("inf.bits = EXP_MASK - 1;");
                s("sup.bits = EXP_MASK;");
                ret("cp");
            }
            endIf();
            bIf("ieeeBits == 0");
            {
                s("inf.bits = 0;");
                s("sup.bits = 1;");
                ret("cp");
            }
            endIf();
            s("init_f(ieeeBits);");
            s("int cmp = cmp_loop();");
            s("inf.bits = cmp >= 0 ? ieeeBits : ieeeBits - 1;");
            s("sup.bits = cmp <= 0 ? ieeeBits : ieeeBits + 1;");
            ret("cp");
        }
        endFun();
    }

    private void genConvertDec() {
        bFun("void convertDec(int log10ceiling, int fracExp, int hasMore)");
        {
            s("assert(log10ceiling >= MIN_VALUE_LOG10_CEILING);");
            s("assert(log10ceiling <= MAX_VALUE_LOG10_CEILING);");
            bIf("log10ceiling >= 17");
            {
                bIf("fracExp < 0");
                {
                    s("fracExp = 0;");
                    s("hasMore = 1;");
                }
                endIf();
            }
            elseIf("fracExp < -1022 - 52");
            {
                s("fracExp = -1022 - 52;");
                s("hasMore = 1;");
            }
            endIf();
            s("int nDigits = log10ceiling - fracExp;");
            s("char *pCharsBeg = pChars + MAX_VALUE_LOG10_CEILING - log10ceiling;");
            bIf("fracExp > 0");
            {
                s("assert(!hasMore);");
                s("memset(pCharsBeg + nDigits, '0', fracExp);");
                s("set_digits(&p, pCharsBeg, pCharsBeg + nDigits + fracExp);");
                s("qChars[0] = '1';");
                s("set_digits(&q, qChars, qChars + 1);");
            };
            elseIf();
            {
                bIf("hasMore");
                {
                    s("pCharsBeg[nDigits] = '1';");
                    s("nDigits++;");
                    s("fracExp--;");
                }
                endIf();
                s("set_digits(&p, pCharsBeg, pCharsBeg + nDigits);");
                s("qChars[0] = '1';");
                s("memset(qChars + 1, '0', -fracExp);");
                s("set_digits(&q, qChars, qChars - fracExp + 1);");
            }
            endIf();
            s("guess_double();");
            bIf("ieeeBits == EXP_MASK");
            {
                s("inf.bits = EXP_MASK - 1;");
                s("sup.bits = EXP_MASK;");
                ret("");
            }
            endIf();
            bIf("ieeeBits == 0");
            {
                s("inf.bits = 0;");
                s("sup.bits = 1;");
                ret("");
            }
            endIf();
            s("init_f(ieeeBits);");
            s("int cmp = cmp_loop();");
            s("inf.bits = cmp >= 0 ? ieeeBits : ieeeBits - 1;");
            s("sup.bits = cmp <= 0 ? ieeeBits : ieeeBits + 1;");
        }
        endFun();
    }

    private void genConvert() {
        bFun("void convert()");
        {
            bIf("log10ceiling < MIN_VALUE_LOG10_CEILING");
            {
                s("inf.bits = 0;");
                s("sup.bits = 1;");
                ret("");
            }
            endIf();
            bIf("log10ceiling > MAX_VALUE_LOG10_CEILING");
            {
                s("inf.bits = EXP_MASK - 1;");
                s("sup.bits = EXP_MASK;");
                ret("");
            }
            endIf();
            s("int hasMore = 0;");
            bIf("fracExp < -1022 - 52");
            {
                s("nDigits -= -1022 - 52 - fracExp;");
                s("fracExp = -1022 - 52;");
                s("hasMore = 1;");
            }
            endIf();
            s("char *pCharsBeg = pChars + MAX_VALUE_LOG10_CEILING - log10ceiling;");
            bIf("dotPos == NULL || dotPos < firstNZ || dotPos >= firstNZ + nDigits");
            {
                s("memcpy(pCharsBeg, firstNZ, nDigits);");
            }
            elseIf();
            {
                s("memcpy(pCharsBeg, firstNZ, dotPos - firstNZ);");
                s("memcpy(pCharsBeg + (dotPos - firstNZ), dotPos + 1, nDigits - (dotPos - firstNZ));");
            }
            endIf();
            s("convertDec(log10ceiling, fracExp, hasMore);");
        }
        endFun();
    }

    private void genParseNum() {
        bFun("const char* parseNum(const char *cp)");
        {
            s("inf.bits = sup.bits = 0xFFF8000000000000ull;");
            s("cp = scan_decimal(cp);");
            s();
            retIf("nDigits == 0", "parseZeroTail(cp, mantS)");
            s();
            s("char c = *cp;");
            bIf("c == '/'");
            {
                retIf("dotPos != NULL", "NULL");
                ret("parseRat(cp, firstNZ);");
            }
            endIf();
            bIf("c == 'E' || c == 'e'");
            {
                s("DItype decExp = 0;");
                s("cp = parseExp(cp, &decExp);");
                retIf("cp == NULL", "NULL");
                s("log10ceiling += decExp;");
                s("fracExp += decExp;");
            }
            endIf();
            s();
            s("convert();");
            ret("cp");
        }
        endFun();
    }

    private void genParseUncertain() {
        bFun("const char* parseUncertain(const char *cp)");
        {
            s("DItype e;");
            s("const char *p;");
            s("const char* lastCp = cp = scan_decimal(cp);");
            retIf("cp == NULL || nDigits == 0 && cp <= mantS + 1 && *mantS != '0'", "NULL");
            s("char c = *cp;");
            retIf("*cp != '?'", "NULL");
            s("c = *++cp;");
            s("const char *radBeg = cp;");
            bWhile("c == '0'");
            {
                s("c = *++cp;");
            }
            endWhile();
            s("const char *radFirstNZ = cp;");
            bWhile("c <= '9' && c >= '0'");
            {
                s("c = *++cp;");
            }
            endWhile();
            s("int radInf = 0;");
            bIf("radBeg == cp && *cp == '?'");
            {
                s("radInf = 1;");
                s("c = *++cp;");
            }
            endIf();
            s("const char *radEnd = cp;");
            s("char lo = TOLOWER(c);");
            s("int dir = 0;");
            bIf("lo == 'u'");
            {
                s("dir = +1;");
                s("lo = TOLOWER(*++cp);");
            }
            elseIf("lo == 'd'");
            {
                s("dir = -1;");
                s("lo = TOLOWER(*++cp);");
            }
            endIf();
            shortIf("isNegative", "dir = -dir;");
            s("DItype decExp = 0;");
            bIf("lo == 'e'");
            {
                s("cp = parseExp(cp, &decExp);");
                retIf("cp == NULL", "NULL");
                s("log10ceiling += decExp;");
                s("fracExp += decExp;");
                s("ulpExp += decExp;");
            }
            endIf();
            s("DItype nRadDigits = radEnd - radFirstNZ;");
            bIf("radInf || nRadDigits == 0 && radBeg != radEnd");
            {
                bIf("nDigits == 0");
                {
                    s("inf.bits = sup.bits = 0;");
                }
                elseIf();
                {
                    s("convert();");
                }
                endIf();
                bIf("radInf");
                {
                    shortIf("dir <= 0", "inf.bits = SIGN_MASK | EXP_MASK;");
                    shortIf("dir >= 0", "sup.bits = EXP_MASK;");
                }
                endIf();
                ret("cp");
            }
            endIf();
            s("int lowerCarryInf = 0, lowerCarrySup = 0;");
            s("int lowerHasMoreInf = 0, lowerHasMoreSup = 0;");
            bIf("ulpExp < -1022 - 52 || nRadDigits == 0 && ulpExp == -1022 - 52");
            {
                bIf("radBeg == radEnd");
                {
                    s("lowerHasMoreInf = lowerHasMoreSup = 1;");
                    s("lowerCarryInf = -1;");
                }
                endIf();
                s("p = lastCp;");
                s("DItype em = log10ceiling;");
                shortIf("em < ulpExp + nRadDigits", "em = ulpExp + nRadDigits;");
                s("em++;");
                shortIf("em > -1022 - 52", "em = -1022 - 52;");
                bFor("e = ulpExp - 1", "e < em", "e++");
                {
                    s("char midChar = '0';");
                    bIf("ulpExp <= e && e < log10ceiling");
                    {
                        s("midChar = *--p;");
                        shortIf("midChar == '.'", "midChar = *--p;");
                    }
                    endIf();
                    s("char radChar = '0';");
                    bIf("e < ulpExp + nRadDigits");
                    {
                        s("radChar = radEnd[ulpExp - e - 1];");
                    }
                    endIf();
                    s();
                    s("int sumSup = (midChar - '0') + lowerCarrySup;");
                    shortIf("dir >= 0", "sumSup += radChar - '0';");
                    bIf("sumSup >= 10");
                    {
                        s("sumSup -= 10;");
                        s("lowerCarrySup = 1;");
                    }
                    elseIf();
                    {
                        s("lowerCarrySup = 0;");
                    }
                    endIf();
                    shortIf("sumSup != 0", "lowerHasMoreSup = 1;");
                    s();
                    s("int sumInf = (midChar - '0') + lowerCarryInf;");
                    shortIf("dir <= 0", "sumInf -= radChar - '0';");
                    bIf("sumInf < 0");
                    {
                        s("sumInf += 10;");
                        s("lowerCarryInf = -1;");
                    }
                    elseIf();
                    {
                        s("lowerCarryInf = 0;");
                    }
                    endIf();
                    shortIf("sumInf != 0", "lowerHasMoreInf = 1;");
                }
                endFor();
            }
            endIf();
//            s("printf(\"lowerCarryInf=%d lowerHasMoreInf=%d lowerCarrySup=%d lowerHasMoreSup=%d\\n\", lowerCarryInf, lowerHasMoreInf, lowerCarrySup, lowerHasMoreSup);");
            s("int higherCarryInf = 0, higherCarrySup = 0;");
            bIf("log10ceiling > MAX_VALUE_LOG10_CEILING || ulpExp + nRadDigits >= MAX_VALUE_LOG10_CEILING");
            {
                s("p = firstNZ;");
                s("DItype ep = log10ceiling > ulpExp + nRadDigits ? log10ceiling : ulpExp + nRadDigits;");
                s("DItype em = ulpExp - 2 > MAX_VALUE_LOG10_CEILING ? ulpExp - 2: MAX_VALUE_LOG10_CEILING;");
                bFor("e = ep - 1", "e >= em", "e--");
                {
                    s("char midChar = '0';");
                    bIf("fracExp <= e && e < log10ceiling");
                    {
                        s("midChar = *p++;");
                        shortIf("midChar == '.'", "midChar = *p++;");
                    }
                    endIf();
                    s("char radChar = '0';");
                    bIf("ulpExp <= e && e < ulpExp + nRadDigits");
                    {
                        s("radChar = radEnd[ulpExp - e - 1];");
                    }
                    elseIf("e == ulpExp - 1");
                    {
                        s("radChar = '5';");
                    }
                    endIf();
                    s();
                    s("int sumSup = (midChar - '0');");
                    shortIf("dir >= 0", "sumSup += radChar - '0';");
                    shortIf("sumSup", "higherCarrySup = 1;");
                    s();
                    s("int sumInf = (midChar - '0') + higherCarryInf*10;");
                    shortIf("dir <= 0", "sumInf -= radChar - '0';");
                    shortIf("higherCarryInf == 0 || higherCarryInf == -1", "higherCarryInf = sumInf;");
//                    s("printf(\"e=%lld midChar=%c radChar=%c higherCarrySup=%d higherCarryInf=%d\\n\", e, midChar, radChar, higherCarrySup, higherCarryInf);");
                }
                endFor();
            }
            endIf();
//            s("printf(\"higherCarryInf=%d higherCarrySup=%d\\n\", higherCarryInf, higherCarrySup);");
            s();
            s("DItype uncertainUlpExp1;");
            bIf("radBeg == radEnd");
            {
                s("uncertainUlpExp1 = ulpExp - 1 < -1022 - 52 ? -1022 - 52 : ulpExp - 1;");
            }
            elseIf();
            {
                s("uncertainUlpExp1 = ulpExp < -1022 - 52 ? -1022 - 52 : ulpExp;");
            }
            endIf();
            shortIf("nDigits == 0", "log10ceiling = uncertainUlpExp1;");
            s("p = ulpExp >= uncertainUlpExp1 ? lastCp : lastCp - (uncertainUlpExp1 - ulpExp);");
            shortIf("dotPos != NULL && p <= dotPos", "p--;");
            s("int log10ceilingSup = uncertainUlpExp1;");
            bFor("e = uncertainUlpExp1", "e < MAX_VALUE_LOG10_CEILING", "e++");
            {
                s("char midChar = '0';");
                bIf("ulpExp <= e && e < log10ceiling");
                {
                    s("midChar = *--p;");
                    shortIf("midChar == '.'", "midChar = *--p;");
                }
                endIf();
                s("char radChar = '0';");
                bIf("ulpExp <= e && e < ulpExp + nRadDigits");
                {
                    s("radChar = radEnd[ulpExp - e - 1];");
                }
                elseIf("e == ulpExp - 1");
                {
                    s("radChar = '5';");
                }
                endIf();
                s("int sum = (midChar - '0') + lowerCarrySup;");
                shortIf("dir >= 0", "sum += radChar - '0';");
                s("char supChar;");
                bIf("sum >= 10");
                {
                    s("supChar = sum + ('0' - 10);");
                    s("lowerCarrySup = 1;");
                }
                elseIf();
                {
                    s("supChar = sum + '0';");
                    s("lowerCarrySup = 0;");
                }
                endIf();
                s("pChars[MAX_VALUE_LOG10_CEILING - e - 1] = supChar;");
                shortIf("supChar != '0'", "log10ceilingSup = e + 1;");
//                s("printf(\"e=%lld midChar=%c radChar=%c supChar=%c\\n\", e, midChar, radChar, supChar);");
            }
            endFor();
            s("UWtype supbits;");
            bIf("higherCarrySup || lowerCarrySup");
            {
                s("supbits = EXP_MASK;");
            }
            elseIf("log10ceilingSup < MIN_VALUE_LOG10_CEILING");
            {
                s("supbits = 1;");
            }
            elseIf();
            {
                s("convertDec(log10ceilingSup, uncertainUlpExp1, lowerHasMoreSup);");
                s("supbits = sup.bits;");
            }
            endIf();
            s();
            s("p = ulpExp >= uncertainUlpExp1 ? lastCp : lastCp - (uncertainUlpExp1 - ulpExp);");
            shortIf("dotPos != NULL && p <= dotPos", "p--;");
            s("int log10ceilingInf = uncertainUlpExp1;");
            bFor("e = uncertainUlpExp1", "e < MAX_VALUE_LOG10_CEILING", "e++");
            {
                s("char midChar = '0';");
                bIf("ulpExp <= e && e < log10ceiling");
                {
                    s("midChar = *--p;");
                    shortIf("midChar == '.'", "midChar = *--p;");
                }
                endIf();
                s("char radChar = '0';");
                bIf("ulpExp <= e && e < ulpExp + nRadDigits");
                {
                    s("radChar = radEnd[ulpExp - e - 1];");
                }
                elseIf("e == ulpExp - 1");
                {
                    s("radChar = '5';");
                }
                endIf();
                s("int sum = (midChar - '0') + lowerCarryInf;");
                shortIf("dir <= 0", "sum -= radChar - '0';");
                s("char infChar;");
                bIf("sum < 0");
                {
                    s("infChar = sum + ('0' + 10);");
                    s("lowerCarryInf = -1;");
                }
                elseIf();
                {
                    s("infChar = sum + '0';");
                    s("lowerCarryInf = 0;");
                }
                endIf();
                s("pChars[MAX_VALUE_LOG10_CEILING - e - 1] = infChar;");
                shortIf("infChar != '0'", "log10ceilingInf = e + 1;");
//                s("printf(\"e=%lld midChar=%c radChar=%c infChar=%c\\n\", e, midChar, radChar, infChar);");
            }
            endFor();
//            s("printf(\"lowerCarryInf=%d higherCarryInf=%d log10ceilingInf=%d\\n\", lowerCarryInf, higherCarryInf, log10ceilingInf);");
            s("higherCarryInf += lowerCarryInf;");
            bIf("higherCarryInf == 0");
            {
                bIf("log10ceilingInf <= uncertainUlpExp1");
                {
                    s("inf.bits = 0;");
                }
                elseIf();
                {
                    s("convertDec(log10ceilingInf, uncertainUlpExp1, lowerHasMoreInf);");
                }
                endIf();
            }
            elseIf("higherCarryInf == -1");
            {
                s("e = uncertainUlpExp1;");
                bIf("!lowerHasMoreInf");
                {
                    bWhile("e < MAX_VALUE_LOG10_CEILING && pChars[MAX_VALUE_LOG10_CEILING - e - 1] == '0'");
                    {
                        s("e++;");
                    }
                    endWhile();
                }
                endIf();
                bIf("e < MAX_VALUE_LOG10_CEILING");
                {
                    s("char infChar = ('0' + '9' + 1) - pChars[MAX_VALUE_LOG10_CEILING - e - 1];");
                    s("pChars[MAX_VALUE_LOG10_CEILING - e - 1] = infChar;");
                    s("log10ceilingInf = e + 1;");
//                    s("printf(\"e=%d infChar=%c\\n\", e, infChar);");
                    s("e++;");
                }
                endIf();
                bWhile("e < MAX_VALUE_LOG10_CEILING");
                {
                    s("char infChar = ('0' + '9') - pChars[MAX_VALUE_LOG10_CEILING - e - 1];");
                    s("pChars[MAX_VALUE_LOG10_CEILING - e - 1] = infChar;");
                    shortIf("infChar != '0'", "log10ceilingInf = e + 1;");
//                    s("printf(\"e=%d infChar=%c\\n\", e, infChar);");
                    s("e++;");
                }
                endWhile();
                bIf("log10ceilingInf > MAX_VALUE_LOG10_CEILING");
                {
                    s("inf.bits = SIGN_MASK | EXP_MASK;");
                }
                elseIf("log10ceilingInf < MIN_VALUE_LOG10_CEILING");
                {
                    s("inf.bits = SIGN_MASK | 1;");
                }
                elseIf();
                {
                    s("convertDec(log10ceilingInf, uncertainUlpExp1, lowerHasMoreInf);");
                    s("inf.bits = SIGN_MASK | sup.bits;");
                }
                endIf();
            }
            elseIf("higherCarryInf > 0");
            {
                s("inf.bits = EXP_MASK - 1;");
            }
            elseIf();
            {
                s("inf.bits = SIGN_MASK | EXP_MASK;");
            }
            endIf();
            s("sup.bits = supbits;");
            ret("cp");
        }
        endFun();
    }

    private void genText2Interval() {
        bFun("void textToInterval(const char *cp, DECORATED_INFSUP_B64 *ret)");
        {
            s("double locInf, locSup;");
            s("int isinf = 0;");
//            s("cp = skip_whitespaces(cp);");
            s("char c = *cp;");
            bIf("c == '['");
            {
                s("cp = skip_whitespaces(cp + 1);");
                bIf("*cp == ']'");
                {
                    s("inf.bits = 0xFFF8000000000000ull;");
                    s("locInf = locSup = inf.d;");
                }
                elseIf("TOLOWER(*cp) == 'e'");
                {
                    bIf("TOLOWER(cp[1]) == 'm' && TOLOWER(cp[2]) == 'p' && TOLOWER(cp[3]) == 't' && TOLOWER(cp[4]) == 'y'");
                    {
                        s("cp += 5;");
                        s("inf.bits = 0xFFF8000000000000ull;");
                        s("locInf = locSup = inf.d;");
                    }
                    elseIf("TOLOWER(cp[1]) == 'n' && TOLOWER(cp[2]) == 't' && TOLOWER(cp[3]) == 'i' && TOLOWER(cp[4]) == 'r' && TOLOWER(cp[5]) == 'e'");
                    {
                        s("cp += 6;");
                        s("inf.bits = SIGN_MASK | EXP_MASK;");
                        s("sup.bits = EXP_MASK;");
                        s("locInf = inf.d;");
                        s("locSup = sup.d;");
                        s("isinf = 1;");
                    }
                    elseIf();
                    {
                        s("cp = NULL;");
                    }
                    endIf();
                    shortIf("cp != NULL", "cp = skip_whitespaces(cp);");
                }
                elseIf();
                {
                    bIf("*cp == ','");
                    {
                        s("isNegative = 1;");
                        s("inf.bits = sup.bits = EXP_MASK;");
                    }
                    elseIf();
                    {
                        s("cp = parseNum(cp);");
                    }
                    endIf();
                    bIf("cp != NULL");
                    {
                        shortIf("inf.bits == EXP_MASK", "isinf = 1;");
                        s("locInf = !isNegative ? inf.d : sup.d != 0 ? -sup.d : 0;");
                        s("locSup = !isNegative ? sup.d : inf.d != 0 ? -inf.d : 0;");
                        shortIf("!isNegative && inf.bits == EXP_MASK", "cp = NULL; // +Infinity forbidden");
                    }
                    endIf();
                    shortIf("cp != NULL", "cp = skip_whitespaces(cp);");
                    bIf("cp != NULL && *cp == ','");
                    {
                        s("cp = skip_whitespaces(cp + 1);");
                        bIf("*cp == ']'");
                        {
                            s("isNegative = 0;");
                            s("inf.bits = sup.bits = EXP_MASK;");
                        }
                        elseIf();
                        {
                            s("cp = parseNum(cp);");
                        }
                        endIf();
                        bIf("cp != NULL");
                        {
                            shortIf("inf.bits == EXP_MASK", "isinf = 1;");
                            s("double rightInf = !isNegative ? inf.d : sup.d != 0 ? -sup.d : 0;");
                            s("double rightSup = !isNegative ? sup.d : inf.d != 0 ? -inf.d : 0;");
                            shortIf("isNegative && sup.bits == EXP_MASK", "cp = NULL; // -Infinity forbidden");
                            bIf("cp != NULL");
                            {
                                bIf("locSup <= rightInf");
                                {
                                    s("locSup = rightSup;");
                                }
                                elseIf("locInf != rightInf || locSup != rightSup");
                                {
                                    s("cp = NULL;");
                                }
                                endIf();
                            }
                            endIf();
                            shortIf("cp != NULL", "cp = skip_whitespaces(cp);");
                        }
                        endIf();
                    }
                    elseIf();
                    {
                        shortIf("isNegative && sup.bits == EXP_MASK", "cp = NULL; // -Infinity forbidden");
                    }
                    endIf();
                }
                endIf();
                s("cp = cp != NULL && *cp == ']' ? cp + 1 : NULL;");
            }
            elseIf();
            {
                s("cp = parseUncertain(cp);");
                s("locInf = isNegative ? -sup.d : inf.d;");
                s("locSup = isNegative ? -inf.d : sup.d;");
            }
            endIf();
            s("int decor = COM;");
            bIf("cp != NULL");
            {
                bIf("*cp == '_'");
                {
                    s("cp++;");
                    bIf("TOLOWER(cp[0]) == 't' && TOLOWER(cp[1]) == 'r' && TOLOWER(cp[2]) == 'v'");
                    {
                        s("decor = TRV;");
                    }
                    elseIf("TOLOWER(cp[0]) == 'd' && TOLOWER(cp[1]) == 'e' && TOLOWER(cp[2]) == 'f'");
                    {
                        s("decor = DEF;");
                    }
                    elseIf("TOLOWER(cp[0]) == 'd' && TOLOWER(cp[1]) == 'a' && TOLOWER(cp[2]) == 'c'");
                    {
                        s("decor = DAC;");
                    }
                    elseIf("TOLOWER(cp[0]) == 'c' && TOLOWER(cp[1]) == 'o' && TOLOWER(cp[2]) == 'm'");
                    {
                        s("decor = COM;");
                    }
                    elseIf();
                    {
                        s("cp = NULL;");
                    }
                    endIf();
                }
                elseIf();
                {
                    s("decor = locInf != locInf ? TRV : isinf ? DAC : COM;");
                }
                endIf();
            }
            endIf();
//            shortIf("cp != NULL", "cp = skip_whitespaces(cp);");
            shortIf("cp != NULL && *cp != 0", "cp = NULL;");
            shortIf("cp != NULL && (locInf != locInf && decor != TRV || isinf && decor == COM)", "cp = NULL;");
            shortIf("cp != NULL && decor == COM && (locInf == -INFINITY || locSup == +INFINITY)", "decor = DAC;");
            bIf("cp == NULL");
            {
                s("inf.bits = 0xFFF8000000000000ull;");
                s("ret->inf = ret->sup = inf.d;");
                s("ret->decoration = ILL;");
            }
            elseIf();
            {
                s("ret->inf = locInf;");
                s("ret->sup = locSup;");
                s("ret->decoration = decor;");
            }
            endIf();
        }
        endFun();
    }
}
