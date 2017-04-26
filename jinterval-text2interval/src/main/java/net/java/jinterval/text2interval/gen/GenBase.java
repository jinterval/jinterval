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

import java.math.BigInteger;
import java.util.Arrays;
import java.util.Collection;

/**
 *
 */
public class GenBase extends GenSupport {

    protected void genIncludes(
            int digitBlockSize,
            int numDigitBlocks,
            boolean needPow5) {
        s("#include <math.h>");
        s("#include <string.h>");
        s("#include <stdio.h>");
        s("#include <assert.h>");
        s("#include \"jinterval.h\"");
        s();
        s("typedef unsigned long long UDItype;");
        s("typedef unsigned int USItype;");
        s("typedef long long DItype;");
        s("typedef int SItype;");
        s("typedef unsigned char UQItype;");
        s();
        s("#define W_TYPE_SIZE 64");
        s("#define UWtype UDItype");
        s("#define UHWtype USItype");
        s("#include \"longlong.h\"");
        s();
        s("#define DIGIT_BLOCK_SIZE " + digitBlockSize);
        s("#define DIGIT_BLOCK_RADIX " + BigInteger.TEN.pow(digitBlockSize) + "ull");
        s("#define NUM_DIGIT_BLOCKS " + numDigitBlocks);
        s("#define MIN_VALUE_LOG10_CEILING -323");
        s("#define MAX_VALUE_LOG10_CEILING 309");
        s("#define SIGN_MASK 0x8000000000000000ull");
        s("#define EXP_MASK 0x7FF0000000000000ull");
        s();
        s("#define TOLOWER(c) ((c) | 0x20)");
        s("#define ISSPACE(c) ((c) == ' ' || (c) == '\\t')");
        s("struct block_buffer {");
        b();
        {
            s("UWtype *blocks;");
            s("const char *beg, *ptr, *end;");
            s("UDItype len, minpow;");
        }
        e();
        s("};");
        s();
        genLong10pow(digitBlockSize);
        s();
        s("#include \"pow2-table.h\"");
        if (needPow5) {
            s("#include \"pow5-table.h\"");
        }
        s();
        genStaticVars(digitBlockSize);
        s();
        bFun("void* get_addr(char* var)");
        {
            for (String varName : getStaticVarNames()) {
                retIf("!strcmp(var, \"" + varName + "\")", "(void *) &" + varName);
            }
            ret("NULL");
        }
        endFun();
        s();
        genGetNumDigitBlocks();
        s();
        genDiffAddMult();
        s();
        genAddMultPD();
        s();
        genDiffSubMult();
        s();
        genSubMultQN();
        s();
        genDiffMultThisBy();
        s();
        genMultiplyModTen();
        s();
        genMul1();
        s();
//        genPow10();
//        s();
        genInitMult();
        s();
        genInitF();
        s();
        genLoopInitF();
        s();
        genGetS();
        s();
        genGetPartialBlock();
        s();
//        genGetFullBlock();
        genGetFullBlock(digitBlockSize);
        s();
        genConvDec();
        s();
        genLoopConvDec();
        s();
        genSetDigits();
        s();
        genRequest();
        s();
        genGuessDouble();
        s();
        genDoPow();
        s();
        genOneStep();
        s();
        genCmpLoop();
        s();
        genParseExp();
        s();
        genParseHex();
        s();
        genParseZeroTail();
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

    protected void genStaticVars(int digitBlocskSize) {
        s("static UWtype fnBlocks[NUM_DIGIT_BLOCKS];");
        s("static UWtype fdBlocks[NUM_DIGIT_BLOCKS];");
        s("static int fnLen, fdLen;");
        s("static const char *s, *mantS, *firstNZ, *dotPos;");
        s("static DItype log10ceiling, nDigits, fracExp, ulpExp;");
        s("static char pChars[400 + 1100], qChars[1100];");
        s("static UWtype pBlocks[NUM_DIGIT_BLOCKS];");
        s("static UWtype qBlocks[NUM_DIGIT_BLOCKS];");
        s("static struct block_buffer p = { pBlocks };");
        s("static struct block_buffer q = { qBlocks };");
        s("static DItype curpow;");
        s("static int diff_high;");
        s("static UWtype diff_hi;");
        s("static UWtype diff_lo;");
        s("static UWtype ieeeBits;");
        s("static union { double d; UWtype bits; } inf, sup;");
        s("static int isNegative;");
    }

    protected Collection<String> getStaticVarNames() {
        return Arrays.asList("long10pow", "pow2", "pow2len",
                "fnBlocks", "fdBlocks", "fnLen", "fdLen",
                "s", "mantS", "firstNZ", "dotPos", "log10ceiling", "nDigits", "fracExp", 
                "pChars", "qChars", "pBlocks", "qBlocks", "p", "q",
                "curpow", "diff_hi", "diff_lo",
                "ieeeBits", "inf", "sup", "isNegative");
    }

    private void genGetNumDigitBlocks() {
        bFun("int get_num_digit_blocks()");
        {
            ret("NUM_DIGIT_BLOCKS");
        }
        endFun();
    }

    private void genDiffAddMult() {
        bFun("void diff_add_mult(UWtype x, UWtype y)");
        {
            s("UWtype hi, lo, z1, z0;");
            s("umul_ppmm(hi, lo, x, y);");
            s("add_ssaaaa(z1, z0, hi, lo, diff_hi, diff_lo);");
            s("diff_high += z1 < diff_hi || z1 == diff_hi && z0 < diff_lo;");
            s("diff_hi = z1;");
            s("diff_lo = z0;");
        }
        endFun();
    }

    private void genAddMultPD() {
        bFun("void add_mult_pd(int n, UWtype *p, UWtype *fd)");
        {
            s("int i;");
            bFor("i = 0", "i < n", "i++");
            {
                s("diff_add_mult(*p++, *fd--);");
            }
            endFor();
        }
        endFun();
    }

    private void genDiffSubMult() {
        bFun("void diff_sub_mult(UWtype x, UWtype y)");
        {
            s("UWtype hi, lo, z1, z0;");
            s("umul_ppmm(hi, lo, x, y);");
            s("sub_ddmmss(z1, z0, diff_hi, diff_lo, hi, lo);");
            s("diff_high -= z1 > diff_hi || z1 == diff_hi && z0 > diff_lo;");
            s("diff_hi = z1;");
            s("diff_lo = z0;");
        }
        endFun();
    }

    private void genSubMultQN() {
        bFun("void sub_mult_qn(int n, UWtype *q, UWtype *fn)");
        {
            s("int i;");
            bFor("i = 0", "i < n", "i++");
            {
                s("diff_sub_mult(*q++, *fn--);");
            }
            endFor();
        }
        endFun();
    }

    private void genDiffMultThisBy() {
        bFun("void diff_mult_this_by(UWtype x)");
        {
            s("umul_ppmm(diff_hi, diff_lo, x, diff_lo);");
            shortIf("diff_high < 0", "diff_hi -= x;");
        }
        endFun();
    }

    private void genMultiplyModTen() {
        bFun("int multiply_mod_ten(UWtype *dst, UWtype *src, int srcLen, UWtype m)");
        {
            s("int i;");
            s("UWtype carry = 0;");
            bFor("i = 0", "i < srcLen", "i++");
            {
                s("UWtype hi, lo;");
                s("umul_ppmm(hi, lo, *src++, m);");
                s("lo += carry;");
                s("hi += lo < carry;");
                s("udiv_qrnnd(carry, *dst++, hi, lo, DIGIT_BLOCK_RADIX);");
            }
            endFor();
            bWhile("carry != 0");
            {
                s("udiv_qrnnd(carry, *dst++, 0, carry, DIGIT_BLOCK_RADIX);");
                s("i++;");
            }
            endWhile();
            ret("i");
        }
        endFun();
    }

    private void genMul1() {
        bFun("UWtype mul_1(UWtype *dst, UWtype *src, int srcLen, UWtype m)");
        {
            s("int i;");
            s("UWtype carry = 0;");
            bFor("i = 0", "i < srcLen", "i++");
            {
                s("UWtype hi, lo;");
                s("umul_ppmm(hi, lo, src[i], m);");
                s("lo += carry;");
                s("carry = (lo < carry) + hi;");
                s("dst[i] = lo;");
            }
            endFor();
            ret("carry");
        }
        endFun();
    }

//    private void genPow10() {
//        s("static UWtype pow10[] = {");
//        b();
//        {
//            BigInteger p = BigInteger.ONE;
//            for (int i = 0; i <= 19; i++) {
//                s(p + "ull,");
//            }
//        }
//        e();
//        s("};");
//    }

    private void genInitMult() {
        bFun("int init_mult(UWtype *dst, int e, UWtype m)");
        {
            s("int eq = e / 12;");
            s("int er = e - eq * 12;");
            s("assert(0 <= e && e <= 1074);");
            ret("multiply_mod_ten(dst, pow2[eq], pow2len[eq], m << er);");
        }
        endFun();
    }

    private void genInitF() {
        bFun("void init_f(UWtype fBits)");
        {
            s("UWtype mant;");
            s("int exp, trailingZeros;");
            s();
            s("mant = fBits & 0xFFFFFFFFFFFFFull;");
            s("exp = (int) (fBits >> 52);");
            s("assert(exp < 0x7FF);");
            bIf("exp > 0");
            {
                s("mant = mant | 0x10000000000000ull;");
            }
            elseIf();
            {
                s("assert(mant > 0);");
                s("exp = 1;");
            }
            endIf();
            s("exp = exp - 1023 - 52;");
            s("count_trailing_zeros(trailingZeros, mant);");
            s("mant >>= trailingZeros;");
            s("exp += trailingZeros;");
            bIf("exp >= 0");
            {
                s("fnLen = init_mult(fnBlocks, exp, mant);");
                s("fdLen = 1;");
                s("fdBlocks[0] = 1;");
            }
            elseIf();
            {
                s("fnLen = 1;");
                s("fnBlocks[0] = mant;");
                s("fdLen = init_mult(fdBlocks, -exp, 1);");
            }
            endIf();
        }
        endFun();
    }

    private void genLoopInitF() {
        bFun("void loop_init_f(int count, UWtype* fBits)");
        {
            s("int i;");
            bFor("i = 0", "i < count", "i++");
            {
                s("init_f(fBits[i]);");
            }
            endFor();
        }
        endFun();
    }

    private void genGetS() {
        bFun("char get_s(int i)");
        {
            ret("s[i]");
        }
        endFun();
    }

    private void genGetPartialBlock() {
        bFun("UWtype get_partial_block(const char *p, int l)");
        {
            s("UWtype r = 0;");
            bWhile("l-- > 0");
            {
                s("r = r * 10 + *p++ - '0';");
            }
            endWhile();
            ret("r");
        }
        endFun();
    }

    private void genGetFullBlock() {
        bFun("UWtype get_full_block(const char *p)");
        {
            ret("get_partial_block(p, DIGIT_BLOCK_SIZE)");
        }
        endFun();
    }

    private void genGetFullBlock(int digitBlockSize) {
        assert digitBlockSize >= 8 && digitBlockSize <= 19;
        s("#define m1 0x0F0F0F0F0F0F0F0Full");
        s("#define m2 0x00FF00FF00FF00FFull");
        s("#define m3 0x0000FFFF0000FFFFull");
        s("#define m4 0x00000000FFFFFFFFull");
        s();
        bFun("UWtype get_full_block(const char *p)");
        {
            s("unsigned long long v = 0;");
            if (digitBlockSize >= 16) {
                for (int i = 0; i < 16; i++) {
                    s("v = (v << 4) | p[" + i + "]&0xF;");
                }
                s("v = ((v>>4) & m1) * 10 + (v & m1);");
                s("v = ((v>>8) & m2) * 100 + (v & m2);");
                s("v = ((v>>16)& m3) * 10000 + (v & m3);");
                s("v = ((v>>32)& m4) * 100000000 + (v & m4);");
                for (int i = 16; i < digitBlockSize; i++) {
                    s("v = v * 10 + (p[" + i + "] - '0');");
                }
            } else {
                for (int i = 0; i < 8; i++) {
                    s("v = (v << 4) | p[" + i + "]&0xF;");
                }
                s("v = ((v>>4) & m1) * 10 + (v & m1);");
                s("v = ((v>>8) & m2) * 100 + (v & m2);");
                s("v = ((v>>16)& m3) * 10000 + (v & m3);");
                for (int i = 8; i < digitBlockSize; i++) {
                    s("v = v * 10 + (p[" + i + "] - '0');");
                }
            }
            ret("v");
        }
        endFun();
    }

    private void genConvDec() {
        bFun("int conv_dec(char *src, int srcDigits, UWtype *dst)");
        {
            s("assert(srcDigits > 0);");
            s("int i = srcDigits <= DIGIT_BLOCK_SIZE ? srcDigits : (srcDigits + (DIGIT_BLOCK_SIZE - 1)) % DIGIT_BLOCK_SIZE + 1;");
            s("dst[0] = get_partial_block(src, i);");
            s("int l = 1;");
            bWhile("i < srcDigits");
            {
                s("int j;");
                s("UWtype carry = get_full_block(src + i);");
                bFor("j = 0", "j < l", "j++");
                {
                    s("UWtype hi, lo;");
                    s("umul_ppmm(hi, lo, dst[j], DIGIT_BLOCK_RADIX);");
                    s("lo += carry;");
                    s("carry = (lo < carry) + hi;");
                    s("dst[j] = lo;");
                }
                endFor();
                shortIf("carry != 0", "dst[l++] = carry;");
                s("i += DIGIT_BLOCK_SIZE;");
            }
            endWhile();
            ret("l");
        }
        endFun();
    }

    private void genLoopConvDec() {
        bFun("void loop_conv_dec(int count, char *src, int srcDigits, UWtype *dst)");
        {
            s("int i;");
            bFor("i = 0", "i < count", "i++");
            {
                s("conv_dec(src, srcDigits, dst);");
            }
            endFor();
        }
        endFun();
    }

    private void genSetDigits() {
        bFun("void set_digits(struct block_buffer *bb, const char *beg, const char *end)");
        {
            s("bb->beg = beg;");
            s("bb->end = end;");
            s("bb->len = (end - beg + (DIGIT_BLOCK_SIZE - 1)) / DIGIT_BLOCK_SIZE;");
            bIf("end - beg != bb->len * DIGIT_BLOCK_SIZE");
            {
                s("bb->minpow = bb->len - 1;");
                s("bb->ptr = end - bb->minpow * DIGIT_BLOCK_SIZE;");
                s("bb->blocks[0] = get_partial_block(beg, (int) (bb->ptr - beg));");
            }
            elseIf();
            {
                s("bb->minpow = bb->len;");
                s("bb->ptr = beg;");
            }
            endIf();
        }
        endFun();
    }

    private void genGuessDouble() {
        bFun("UWtype guess_double()");
        {
            s("int ieeeUlp;");
            s("UWtype ieeeSignif;");
            s();
            s("int pl = p.end - p.beg < DIGIT_BLOCK_SIZE ? (int) (p.end - p.beg) : DIGIT_BLOCK_SIZE;");
            s("UWtype ph = get_partial_block(p.beg, pl);");
            s("int ql = q.end - q.beg < DIGIT_BLOCK_SIZE ? (int) (q.end - q.beg) : DIGIT_BLOCK_SIZE;");
            s("UWtype qh = get_partial_block(q.beg, ql);");
            s("int e10 = (p.end - p.beg - pl) - (q.end - q.beg - ql);");
            s();
            genBodyGuess();
            ret("ieeeBits");
        }
        endFun();
    }

    private void genBodyGuess() {
        // IN ph, qh, e10
        // OUT ieeeUlp, ieeeSignif, ieeeBits
        b();
        {
            s("int plz, qlz, e2, bla, ieeeExp;");
            s("struct pow5 *p5;");
            s("UWtype mantp5, hi, lo, quo, rem;");
            s("count_leading_zeros(plz, ph);");
            s("ph <<= plz;");
            s("count_leading_zeros(qlz, qh);");
            s("qh <<= qlz;");
            bIf("e10 >= 0");
            {
                s("p5 = pow5 + e10;");
                s("e2 = p5->nBits;");
                s("mantp5 = p5->bBitsML[p5->nWordsL - 1];");
            }
            elseIf();
            {
                s("p5 = pow5 - e10;");
                s("e2 = 1 - p5->nBits;");
                s("mantp5 = p5->bBitsDL[1];");
            }
            endIf();
            s("e2 += e10 + qlz - plz - 63;");
            s("umul_ppmm(hi, lo, ph, mantp5 >> 1);");
            s("udiv_qrnnd(quo, rem, hi, lo, qh);");
            s("count_leading_zeros(bla, quo);");
            s("bla = 64 - bla;");
            s("ieeeExp = e2 + bla - 1;");
            bIf("ieeeExp > 1023");
            {
                s("ieeeUlp = 1024 - 52;");
                s("ieeeSignif = 1ull << 52;");
                s("ieeeBits = 0x7FFull << 52;"); // [Double.MAX_VALUE,Infinity]
            }
            elseIf("ieeeExp >= -1022");
            {
                s("ieeeUlp = ieeeExp - 52;");
                s("assert(ieeeUlp > e2);");
                s("ieeeSignif = ((quo >> ieeeUlp - e2 - 1) + 1) >> 1;");
                s("ieeeBits = ieeeSignif + (((UWtype) (ieeeExp + 1022)) << 52);");
            }
            elseIf();
            {
                s("ieeeUlp = -1022 - 52;");
                s("assert(ieeeUlp > e2);");
                s("ieeeSignif = ((quo >> ieeeUlp - e2 - 1) + 1) >> 1;");
                s("ieeeBits = ieeeSignif;");
            }
            endIf();
            s("assert(ieeeBits <= EXP_MASK);");
        }
        e();
    }

    private void genRequest() {
        bFun("void request(struct block_buffer *bb, UDItype minpow, int l)");
        {
            s("assert(l > 0);");
            bIf("minpow < bb->minpow");
            {
                s("assert(minpow == bb->minpow - 1);");
                s("memmove(bb->blocks + 1, bb->blocks, (l - 1) * sizeof (UWtype));");
                s("bb->blocks[0] = get_full_block(bb->ptr);");
                s("bb->ptr += DIGIT_BLOCK_SIZE;");
                s("assert(bb->ptr <= bb->end);");
                s("bb->minpow = minpow;");
            }
            endIf();
            s("assert(minpow == bb->minpow);");
        }
        endFun();
    }

    private void genDoPow() {
        bFun("void do_pow()");
        {
            s("DItype minFdPow, maxFdPow, minFnPow, maxFnPow;");
            s();
            s("curpow--;");
//            s("printf(\"curpow=%lld\\n\", curpow);");
            s("diff_mult_this_by(DIGIT_BLOCK_RADIX);");
            s();
            s("minFdPow = curpow - (p.len - 1);");
            shortIf("minFdPow < 0", "minFdPow = 0;");
            s("maxFdPow = fdLen - 1;");
            shortIf("maxFdPow > curpow", "maxFdPow = curpow;");
//            s("printf(\"minFdPow=%lld maxFdPow=%lld\\n\", minFdPow, maxFdPow);");
            bIf("minFdPow <= maxFdPow");
            {
                s("int n = (int) (maxFdPow - minFdPow + 1);");
                s("request(&p, curpow - maxFdPow, n);");
                s("add_mult_pd(n, p.blocks, fdBlocks + maxFdPow);");
            }
            endIf();
            s();
            s("minFnPow = curpow - (q.len - 1);");
            shortIf("minFnPow < 0", "minFnPow = 0;");
            s("maxFnPow = fnLen - 1;");
            shortIf("maxFnPow > curpow", "maxFnPow = curpow;");
//            s("printf(\"minFnPow=%lld maxFnPow=%lld\\n\", minFnPow, maxFnPow);");
            bIf("minFnPow <= maxFnPow");
            {
                s("int n = (int) (maxFnPow - minFnPow + 1);");
                s("request(&q, curpow - maxFnPow, n);");
                s("sub_mult_qn(n, q.blocks, fnBlocks + maxFnPow);");
            }
            endIf();
        }
        endFun();
    }

    private void genOneStep() {
        bFun("int one_step()");
        {
            bIf("diff_high < 0");
            {
                retIf("diff_high != -1 || diff_hi < -fdLen-1", "-1");
            }
            elseIf();
            {
                retIf("diff_high != 0 || diff_hi > fnLen", "1");
            }
            endIf();
            s();
            s("do_pow();");
            ret("0");
        }
        endFun();
    }

    private void genCmpLoop() {
        bFun("int cmp_loop()");
        {
            s("UDItype ppow = p.len + fdLen;");
            s("UDItype qpow = q.len + fnLen;");
            s("curpow = (ppow > qpow ? ppow : qpow) - 1;");
            s("diff_high = 0;");
            s("diff_hi = 0;");
            s("diff_lo = 0;");
            bWhile("curpow > 0");
            {
                s("int cmp = one_step();");
                retIf("cmp != 0", "cmp");
            }
            endWhile();
            retIf("diff_high < 0", "-1");
            retIf("diff_high != 0 || diff_hi != 0 || diff_lo != 0", "1");
            ret("0");
        }
        endFun();
    }

    private void genParseExp() {
        s("#define EXPONENT_LIMIT 0x0400000000000000LL");
        s();
        bFun("const char* parseExp(const char *cp, DItype *expptr)");
        {
            s("char c = *++cp;");
            s("int isNegativeExp = 0;");
            bIf("c == '-'");
            {
                s("isNegativeExp = -1;");
                s("c = *++cp;");
            }
            elseIf("c == '+'");
            {
                s("c = *++cp;");
            }
            endIf();
            bIf("c >= '0' && c <= '9'");
            {
                s("DItype exp = 0; // first digit");
                doWhile();
                {
                    shortIf("exp < EXPONENT_LIMIT", "exp = exp*10 + c - '0';");
                    s("c = *++cp;");
                }
                endDoWhile("c >='0' && c <= '9'");
                s("*expptr = (exp ^ isNegativeExp) -isNegativeExp;");
                ret("cp");
            }
            elseIf();
            {
                ret("NULL");
            }
            endIf();
        }
        endFun();
    }
    
    private void genParseHex() {

        bFun("const char* parseHex(const char *cp)");
        {
            s("const char *cp0 = cp;");
            s("const char *dotPos = NULL;");
            s("char c = *cp;");
            bWhile("c == '0'");
            {
                s("c = *++cp;");
            }
            endWhile();
            bIf("c == '.'");
            {
                s("dotPos = cp;");
                s("c = *++cp;");
                bWhile("c == '0'");
                {
                    s("c = *++cp;");
                }
                endWhile();
            }
            endIf();
//            s("printf(\"C:%s %c\\n\", cp, c);");
            s();
            s("int lastNZ = -1;");
            s("int nDigits = 0;");
            s();
            s("UWtype lValue = 0;");
            bFor("", "", "");
            {
                bIf("c <= '9' && c >= '0'");
                {
                    shortIf("c > '0'", "lastNZ = nDigits;");
                    shortIf("nDigits++ < 16", "lValue = (lValue << 4) + (c - '0');");
                }
                elseIf("c == '.'");
                {
                    bIf("dotPos != NULL");
                    {
                        breakFor();
                    }
                    endIf();
                    s("dotPos = cp;");
                }
                elseIf();
                {
                    s("char lo = TOLOWER (c);");
                    bIf("lo < 'a' || lo > 'f'");
                    {
                        breakFor();
                    }
                    endIf();
                    s("lastNZ = nDigits;");
                    shortIf("nDigits++ < 16", "lValue = (lValue << 4) + (lo - ('a' - 10));");
                }
                endIf();
                s("c = *++cp;");
            }
            endFor();
//            s("printf(\"D:%s %c nDigits=%d lValue=%llx\\n\", cp, c, nDigits, lValue);");
            s();
            s("DItype expMant = (dotPos != NULL ? dotPos + 1 - cp + nDigits : nDigits)*4L;");
            s("DItype exp = 0;");
            retIf("TOLOWER(c) != 'p'", "NULL");
            s("cp = parseExp(cp, &exp);");
            retIf("cp == NULL", "NULL");
//            s("printf(\"E:%s %c nDigits=%d lValue=%llx exp=%lld\\n\", cp, c, nDigits, lValue, exp);");
            bIf("nDigits == 0");
            {
                retIf("cp <= cp0 + 1 && *cp0 != '0'", "NULL");
                s("inf.bits = sup.bits = 0;");
                ret("cp");
            }
            endIf();
            s();
            s("exp += expMant;");
//            s("printf(\"F:%s %s %c nDigits=%d lValue=%llx exp=%lld\\n\", cp, dotPos, c, nDigits, lValue, exp);");
            shortIf("nDigits < 16", "lValue <<= 4*(16 - nDigits);");
            bWhile("(DItype)lValue >= 0");
            {
                s("lValue <<= 1;");
                s("exp--;");
            }
            endWhile();
            // assert "2^(exp - 1) <= Ev < 2^exp"
//            s("printf(\"G:%s %c nDigits=%d lValue=%llx exp=%lld\\n\", cp, c, nDigits, lValue, exp);");
            bIf("exp > -1022");
            {
                bIf("exp > 1023");
                {
                    s("// Infinity");
                    s("inf.bits = EXP_MASK - 1;");
                    s("sup.bits = EXP_MASK;");
                }
                elseIf();
                {
                    s("// normal");
                    s("int ieeeExp = (int)(exp - 1);");
                    s("int cmp = !((lValue & ((1ull << (63 - 52)) - 1)) == 0 && lastNZ < 16);");
                    s("lValue >>= 63 - 52;");
                    s("inf.bits = (((UWtype) (ieeeExp + 1022)) << 52) + lValue;");
                    s("sup.bits = cmp ? inf.bits + 1 : inf.bits;");
                }
                endIf();
            }
            elseIf("exp >= (-1022 - 52)");
            {
                s("// subnormal");
                s("int threshShift = (int)((63 - 1022 - 52) - exp);");
                s("assert(threshShift > 0 && threshShift < 64);");
                s("int cmp = !((lValue & ((1ull << threshShift) - 1)) == 0 && lastNZ < 16);");
                s("lValue >>= threshShift;");
                s("inf.bits = lValue;");
                s("sup.bits = cmp ? inf.bits + 1 : inf.bits;");
            }
            elseIf();
            {
                s("// 0");
                s("inf.bits = 0;");
                s("sup.bits = 1;");
            }
            endIf();
            ret("cp");
        }
        endFun();
    }
    
    private void genParseZeroTail() {
        bFun("const char* parseZeroTail(const char *cp, const char *cp0)");
        {
            s("char lo = TOLOWER(*cp);");
            retIf("lo == 'x'", "cp == cp0 + 1 && *cp0 == '0' ? parseHex(cp + 1) : NULL");
            bIf("cp <= cp0 + 1 && *cp != '0'");
            {
                retIf("cp != cp0 || lo != 'i' || TOLOWER(cp[1]) != 'n' || TOLOWER(cp[2]) != 'f'", "NULL");
                bIf("TOLOWER(cp[3]) != 'i'");
                {
                    s("cp += 3;");
                }
                elseIf();
                {
                    retIf("TOLOWER(cp[4]) != 'n' || TOLOWER(cp[5]) != 'i' || TOLOWER(cp[6]) != 't' || TOLOWER(cp[7]) != 'y'", "NULL");
                    s("cp += 8;");
                }
                endIf();
                s("inf.bits = sup.bits = EXP_MASK;");
                ret("cp");
            }
            endIf();
            bIf("lo == 'e'");
            {
                s("DItype decExp;");
                s("cp = parseExp(cp, &decExp);");
                retIf("cp == NULL", "NULL");
            }
            elseIf("*cp == '/'");
            {
                s("int nonzero = 0;");
                s("char c = *++cp;");
                bWhile("c <= '9' && c >= '0'");
                {
                    shortIf("c != '0'", "nonzero = 1;");
                    s("c = *++cp;");
                }
                endWhile();
                retIf("!nonzero", "NULL");
            }
            endIf();
            s("inf.bits = sup.bits = 0;");
            ret("cp");
        }
        endFun();
    }

}
