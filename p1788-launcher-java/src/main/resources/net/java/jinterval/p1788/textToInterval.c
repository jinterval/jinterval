/*
   Copyright (C) 2013 JInterval Project.

   This file was generated automatically, don't edit.

   The JInterval C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   In addition to the permissions in the GNU Lesser General Public
   License, the Free Software Foundation gives you unlimited
   permission to link the compiled version of this file into
   combinations with other programs, and to distribute those
   combinations without any restriction coming from the use of this
   file.  (The Lesser General Public License restrictions do apply in
   other respects; for example, they cover modification of the file,
   and distribution when not linked into a combine executable.)

   The JInterval C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the JInterval C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "jinterval.h"

typedef unsigned long long UDItype;
typedef unsigned int USItype;
typedef long long DItype;
typedef int SItype;
typedef unsigned char UQItype;

#define W_TYPE_SIZE 64
#define UWtype UDItype
#define UHWtype USItype
#include "longlong.h"

#define DIGIT_BLOCK_SIZE 19
#define DIGIT_BLOCK_RADIX 10000000000000000000ull
#define NUM_DIGIT_BLOCKS 28
#define MIN_VALUE_LOG10_CEILING -323
#define MAX_VALUE_LOG10_CEILING 309
#define SIGN_MASK 0x8000000000000000ull
#define EXP_MASK 0x7FF0000000000000ull

#define TOLOWER(c) ((c) | 0x20)
#define ISSPACE(c) ((c) == ' ' || (c) == '\t')
struct block_buffer {
    UWtype *blocks;
    const char *beg, *ptr, *end;
    UDItype len, minpow;
};

const static unsigned long long long10pow[] = {
    1ull,
    10ull,
    100ull,
    1000ull,
    10000ull,
    100000ull,
    1000000ull,
    10000000ull,
    100000000ull,
    1000000000ull,
    10000000000ull,
    100000000000ull,
    1000000000000ull,
    10000000000000ull,
    100000000000000ull,
    1000000000000000ull,
    10000000000000000ull,
    100000000000000000ull,
    1000000000000000000ull,
    10000000000000000000ull,
};

#include "pow2-table.h"
#include "pow5-table.h"

static UWtype fnBlocks[NUM_DIGIT_BLOCKS];
static UWtype fdBlocks[NUM_DIGIT_BLOCKS];
static int fnLen, fdLen;
static const char *s, *mantS, *firstNZ, *dotPos;
static DItype log10ceiling, nDigits, fracExp, ulpExp;
static char pChars[400 + 1100], qChars[1100];
static UWtype pBlocks[NUM_DIGIT_BLOCKS];
static UWtype qBlocks[NUM_DIGIT_BLOCKS];
static struct block_buffer p = { pBlocks };
static struct block_buffer q = { qBlocks };
static DItype curpow;
static int diff_high;
static UWtype diff_hi;
static UWtype diff_lo;
static UWtype ieeeBits;
static union { double d; UWtype bits; } inf, sup;
static int isNegative;

void* get_addr(char* var) {
    if (!strcmp(var, "long10pow")) return (void *) &long10pow;
    if (!strcmp(var, "pow2")) return (void *) &pow2;
    if (!strcmp(var, "pow2len")) return (void *) &pow2len;
    if (!strcmp(var, "fnBlocks")) return (void *) &fnBlocks;
    if (!strcmp(var, "fdBlocks")) return (void *) &fdBlocks;
    if (!strcmp(var, "fnLen")) return (void *) &fnLen;
    if (!strcmp(var, "fdLen")) return (void *) &fdLen;
    if (!strcmp(var, "s")) return (void *) &s;
    if (!strcmp(var, "mantS")) return (void *) &mantS;
    if (!strcmp(var, "firstNZ")) return (void *) &firstNZ;
    if (!strcmp(var, "dotPos")) return (void *) &dotPos;
    if (!strcmp(var, "log10ceiling")) return (void *) &log10ceiling;
    if (!strcmp(var, "nDigits")) return (void *) &nDigits;
    if (!strcmp(var, "fracExp")) return (void *) &fracExp;
    if (!strcmp(var, "pChars")) return (void *) &pChars;
    if (!strcmp(var, "qChars")) return (void *) &qChars;
    if (!strcmp(var, "pBlocks")) return (void *) &pBlocks;
    if (!strcmp(var, "qBlocks")) return (void *) &qBlocks;
    if (!strcmp(var, "p")) return (void *) &p;
    if (!strcmp(var, "q")) return (void *) &q;
    if (!strcmp(var, "curpow")) return (void *) &curpow;
    if (!strcmp(var, "diff_hi")) return (void *) &diff_hi;
    if (!strcmp(var, "diff_lo")) return (void *) &diff_lo;
    if (!strcmp(var, "ieeeBits")) return (void *) &ieeeBits;
    if (!strcmp(var, "inf")) return (void *) &inf;
    if (!strcmp(var, "sup")) return (void *) &sup;
    if (!strcmp(var, "isNegative")) return (void *) &isNegative;
    return NULL;
}

int get_num_digit_blocks() {
    return NUM_DIGIT_BLOCKS;
}

void diff_add_mult(UWtype x, UWtype y) {
    UWtype hi, lo, z1, z0;
    umul_ppmm(hi, lo, x, y);
    add_ssaaaa(z1, z0, hi, lo, diff_hi, diff_lo);
    diff_high += z1 < diff_hi || z1 == diff_hi && z0 < diff_lo;
    diff_hi = z1;
    diff_lo = z0;
}

void add_mult_pd(int n, UWtype *p, UWtype *fd) {
    int i;
    for (i = 0;i < n;i++) {
        diff_add_mult(*p++, *fd--);
    }
}

void diff_sub_mult(UWtype x, UWtype y) {
    UWtype hi, lo, z1, z0;
    umul_ppmm(hi, lo, x, y);
    sub_ddmmss(z1, z0, diff_hi, diff_lo, hi, lo);
    diff_high -= z1 > diff_hi || z1 == diff_hi && z0 > diff_lo;
    diff_hi = z1;
    diff_lo = z0;
}

void sub_mult_qn(int n, UWtype *q, UWtype *fn) {
    int i;
    for (i = 0;i < n;i++) {
        diff_sub_mult(*q++, *fn--);
    }
}

void diff_mult_this_by(UWtype x) {
    umul_ppmm(diff_hi, diff_lo, x, diff_lo);
    if (diff_high < 0) diff_hi -= x;
}

int multiply_mod_ten(UWtype *dst, UWtype *src, int srcLen, UWtype m) {
    int i;
    UWtype carry = 0;
    for (i = 0;i < srcLen;i++) {
        UWtype hi, lo;
        umul_ppmm(hi, lo, *src++, m);
        lo += carry;
        hi += lo < carry;
        udiv_qrnnd(carry, *dst++, hi, lo, DIGIT_BLOCK_RADIX);
    }
    while (carry != 0) {
        udiv_qrnnd(carry, *dst++, 0, carry, DIGIT_BLOCK_RADIX);
        i++;
    }
    return i;
}

UWtype mul_1(UWtype *dst, UWtype *src, int srcLen, UWtype m) {
    int i;
    UWtype carry = 0;
    for (i = 0;i < srcLen;i++) {
        UWtype hi, lo;
        umul_ppmm(hi, lo, src[i], m);
        lo += carry;
        carry = (lo < carry) + hi;
        dst[i] = lo;
    }
    return carry;
}

int init_mult(UWtype *dst, int e, UWtype m) {
    int eq = e / 12;
    int er = e - eq * 12;
    assert(0 <= e && e <= 1074);
    return multiply_mod_ten(dst, pow2[eq], pow2len[eq], m << er);;
}

void init_f(UWtype fBits) {
    UWtype mant;
    int exp, trailingZeros;

    mant = fBits & 0xFFFFFFFFFFFFFull;
    exp = (int) (fBits >> 52);
    assert(exp < 0x7FF);
    if (exp > 0) {
        mant = mant | 0x10000000000000ull;
    } else {
        assert(mant > 0);
        exp = 1;
    }
    exp = exp - 1023 - 52;
    count_trailing_zeros(trailingZeros, mant);
    mant >>= trailingZeros;
    exp += trailingZeros;
    if (exp >= 0) {
        fnLen = init_mult(fnBlocks, exp, mant);
        fdLen = 1;
        fdBlocks[0] = 1;
    } else {
        fnLen = 1;
        fnBlocks[0] = mant;
        fdLen = init_mult(fdBlocks, -exp, 1);
    }
}

void loop_init_f(int count, UWtype* fBits) {
    int i;
    for (i = 0;i < count;i++) {
        init_f(fBits[i]);
    }
}

char get_s(int i) {
    return s[i];
}

UWtype get_partial_block(const char *p, int l) {
    UWtype r = 0;
    while (l-- > 0) {
        r = r * 10 + *p++ - '0';
    }
    return r;
}

#define m1 0x0F0F0F0F0F0F0F0Full
#define m2 0x00FF00FF00FF00FFull
#define m3 0x0000FFFF0000FFFFull
#define m4 0x00000000FFFFFFFFull

UWtype get_full_block(const char *p) {
    unsigned long long v = 0;
    v = (v << 4) | p[0]&0xF;
    v = (v << 4) | p[1]&0xF;
    v = (v << 4) | p[2]&0xF;
    v = (v << 4) | p[3]&0xF;
    v = (v << 4) | p[4]&0xF;
    v = (v << 4) | p[5]&0xF;
    v = (v << 4) | p[6]&0xF;
    v = (v << 4) | p[7]&0xF;
    v = (v << 4) | p[8]&0xF;
    v = (v << 4) | p[9]&0xF;
    v = (v << 4) | p[10]&0xF;
    v = (v << 4) | p[11]&0xF;
    v = (v << 4) | p[12]&0xF;
    v = (v << 4) | p[13]&0xF;
    v = (v << 4) | p[14]&0xF;
    v = (v << 4) | p[15]&0xF;
    v = ((v>>4) & m1) * 10 + (v & m1);
    v = ((v>>8) & m2) * 100 + (v & m2);
    v = ((v>>16)& m3) * 10000 + (v & m3);
    v = ((v>>32)& m4) * 100000000 + (v & m4);
    v = v * 10 + (p[16] - '0');
    v = v * 10 + (p[17] - '0');
    v = v * 10 + (p[18] - '0');
    return v;
}

int conv_dec(char *src, int srcDigits, UWtype *dst) {
    assert(srcDigits > 0);
    int i = srcDigits <= DIGIT_BLOCK_SIZE ? srcDigits : (srcDigits + (DIGIT_BLOCK_SIZE - 1)) % DIGIT_BLOCK_SIZE + 1;
    dst[0] = get_partial_block(src, i);
    int l = 1;
    while (i < srcDigits) {
        int j;
        UWtype carry = get_full_block(src + i);
        for (j = 0;j < l;j++) {
            UWtype hi, lo;
            umul_ppmm(hi, lo, dst[j], DIGIT_BLOCK_RADIX);
            lo += carry;
            carry = (lo < carry) + hi;
            dst[j] = lo;
        }
        if (carry != 0) dst[l++] = carry;
        i += DIGIT_BLOCK_SIZE;
    }
    return l;
}

void loop_conv_dec(int count, char *src, int srcDigits, UWtype *dst) {
    int i;
    for (i = 0;i < count;i++) {
        conv_dec(src, srcDigits, dst);
    }
}

void set_digits(struct block_buffer *bb, const char *beg, const char *end) {
    bb->beg = beg;
    bb->end = end;
    bb->len = (end - beg + (DIGIT_BLOCK_SIZE - 1)) / DIGIT_BLOCK_SIZE;
    if (end - beg != bb->len * DIGIT_BLOCK_SIZE) {
        bb->minpow = bb->len - 1;
        bb->ptr = end - bb->minpow * DIGIT_BLOCK_SIZE;
        bb->blocks[0] = get_partial_block(beg, (int) (bb->ptr - beg));
    } else {
        bb->minpow = bb->len;
        bb->ptr = beg;
    }
}

void request(struct block_buffer *bb, UDItype minpow, int l) {
    assert(l > 0);
    if (minpow < bb->minpow) {
        assert(minpow == bb->minpow - 1);
        memmove(bb->blocks + 1, bb->blocks, (l - 1) * sizeof (UWtype));
        bb->blocks[0] = get_full_block(bb->ptr);
        bb->ptr += DIGIT_BLOCK_SIZE;
        assert(bb->ptr <= bb->end);
        bb->minpow = minpow;
    }
    assert(minpow == bb->minpow);
}

UWtype guess_double() {
    int ieeeUlp;
    UWtype ieeeSignif;

    int pl = p.end - p.beg < DIGIT_BLOCK_SIZE ? (int) (p.end - p.beg) : DIGIT_BLOCK_SIZE;
    UWtype ph = get_partial_block(p.beg, pl);
    int ql = q.end - q.beg < DIGIT_BLOCK_SIZE ? (int) (q.end - q.beg) : DIGIT_BLOCK_SIZE;
    UWtype qh = get_partial_block(q.beg, ql);
    int e10 = (p.end - p.beg - pl) - (q.end - q.beg - ql);

        int plz, qlz, e2, bla, ieeeExp;
        struct pow5 *p5;
        UWtype mantp5, hi, lo, quo, rem;
        count_leading_zeros(plz, ph);
        ph <<= plz;
        count_leading_zeros(qlz, qh);
        qh <<= qlz;
        if (e10 >= 0) {
            p5 = pow5 + e10;
            e2 = p5->nBits;
            mantp5 = p5->bBitsML[p5->nWordsL - 1];
        } else {
            p5 = pow5 - e10;
            e2 = 1 - p5->nBits;
            mantp5 = p5->bBitsDL[1];
        }
        e2 += e10 + qlz - plz - 63;
        umul_ppmm(hi, lo, ph, mantp5 >> 1);
        udiv_qrnnd(quo, rem, hi, lo, qh);
        count_leading_zeros(bla, quo);
        bla = 64 - bla;
        ieeeExp = e2 + bla - 1;
        if (ieeeExp > 1023) {
            ieeeUlp = 1024 - 52;
            ieeeSignif = 1ull << 52;
            ieeeBits = 0x7FFull << 52;
        } else if (ieeeExp >= -1022) {
            ieeeUlp = ieeeExp - 52;
            assert(ieeeUlp > e2);
            ieeeSignif = ((quo >> ieeeUlp - e2 - 1) + 1) >> 1;
            ieeeBits = ieeeSignif + (((UWtype) (ieeeExp + 1022)) << 52);
        } else {
            ieeeUlp = -1022 - 52;
            assert(ieeeUlp > e2);
            ieeeSignif = ((quo >> ieeeUlp - e2 - 1) + 1) >> 1;
            ieeeBits = ieeeSignif;
        }
        assert(ieeeBits <= EXP_MASK);
    return ieeeBits;
}

void do_pow() {
    DItype minFdPow, maxFdPow, minFnPow, maxFnPow;

    curpow--;
    diff_mult_this_by(DIGIT_BLOCK_RADIX);

    minFdPow = curpow - (p.len - 1);
    if (minFdPow < 0) minFdPow = 0;
    maxFdPow = fdLen - 1;
    if (maxFdPow > curpow) maxFdPow = curpow;
    if (minFdPow <= maxFdPow) {
        int n = (int) (maxFdPow - minFdPow + 1);
        request(&p, curpow - maxFdPow, n);
        add_mult_pd(n, p.blocks, fdBlocks + maxFdPow);
    }

    minFnPow = curpow - (q.len - 1);
    if (minFnPow < 0) minFnPow = 0;
    maxFnPow = fnLen - 1;
    if (maxFnPow > curpow) maxFnPow = curpow;
    if (minFnPow <= maxFnPow) {
        int n = (int) (maxFnPow - minFnPow + 1);
        request(&q, curpow - maxFnPow, n);
        sub_mult_qn(n, q.blocks, fnBlocks + maxFnPow);
    }
}

int one_step() {
    if (diff_high < 0) {
        if (diff_high != -1 || diff_hi < -fdLen-1) return -1;
    } else {
        if (diff_high != 0 || diff_hi > fnLen) return 1;
    }

    do_pow();
    return 0;
}

int cmp_loop() {
    UDItype ppow = p.len + fdLen;
    UDItype qpow = q.len + fnLen;
    curpow = (ppow > qpow ? ppow : qpow) - 1;
    diff_high = 0;
    diff_hi = 0;
    diff_lo = 0;
    while (curpow > 0) {
        int cmp = one_step();
        if (cmp != 0) return cmp;
    }
    if (diff_high < 0) return -1;
    if (diff_high != 0 || diff_hi != 0 || diff_lo != 0) return 1;
    return 0;
}

#define EXPONENT_LIMIT 0x0400000000000000LL

const char* parseExp(const char *cp, DItype *expptr) {
    char c = *++cp;
    int isNegativeExp = 0;
    if (c == '-') {
        isNegativeExp = -1;
        c = *++cp;
    } else if (c == '+') {
        c = *++cp;
    }
    if (c >= '0' && c <= '9') {
        DItype exp = 0; // first digit
        do {
            if (exp < EXPONENT_LIMIT) exp = exp*10 + c - '0';
            c = *++cp;
        } while (c >='0' && c <= '9');
        *expptr = (exp ^ isNegativeExp) -isNegativeExp;
        return cp;
    } else {
        return NULL;
    }
}

const char* parseHex(const char *cp) {
    const char *cp0 = cp;
    const char *dotPos = NULL;
    char c = *cp;
    while (c == '0') {
        c = *++cp;
    }
    if (c == '.') {
        dotPos = cp;
        c = *++cp;
        while (c == '0') {
            c = *++cp;
        }
    }

    int lastNZ = -1;
    int nDigits = 0;

    UWtype lValue = 0;
    for (;;) {
        if (c <= '9' && c >= '0') {
            if (c > '0') lastNZ = nDigits;
            if (nDigits++ < 16) lValue = (lValue << 4) + (c - '0');
        } else if (c == '.') {
            if (dotPos != NULL) {
                break;
            }
            dotPos = cp;
        } else {
            char lo = TOLOWER (c);
            if (lo < 'a' || lo > 'f') {
                break;
            }
            lastNZ = nDigits;
            if (nDigits++ < 16) lValue = (lValue << 4) + (lo - ('a' - 10));
        }
        c = *++cp;
    }

    DItype expMant = (dotPos != NULL ? dotPos + 1 - cp + nDigits : nDigits)*4L;
    DItype exp = 0;
    if (TOLOWER(c) != 'p') return NULL;
    cp = parseExp(cp, &exp);
    if (cp == NULL) return NULL;
    if (nDigits == 0) {
        if (cp <= cp0 + 1 && *cp0 != '0') return NULL;
        inf.bits = sup.bits = 0;
        return cp;
    }

    exp += expMant;
    if (nDigits < 16) lValue <<= 4*(16 - nDigits);
    while ((DItype)lValue >= 0) {
        lValue <<= 1;
        exp--;
    }
    if (exp > -1022) {
        if (exp > 1023) {
            // Infinity
            inf.bits = EXP_MASK - 1;
            sup.bits = EXP_MASK;
        } else {
            // normal
            int ieeeExp = (int)(exp - 1);
            int cmp = !((lValue & ((1ull << (63 - 52)) - 1)) == 0 && lastNZ < 16);
            lValue >>= 63 - 52;
            inf.bits = (((UWtype) (ieeeExp + 1022)) << 52) + lValue;
            sup.bits = cmp ? inf.bits + 1 : inf.bits;
        }
    } else if (exp >= (-1022 - 52)) {
        // subnormal
        int threshShift = (int)((63 - 1022 - 52) - exp);
        assert(threshShift > 0 && threshShift < 64);
        int cmp = !((lValue & ((1ull << threshShift) - 1)) == 0 && lastNZ < 16);
        lValue >>= threshShift;
        inf.bits = lValue;
        sup.bits = cmp ? inf.bits + 1 : inf.bits;
    } else {
        // 0
        inf.bits = 0;
        sup.bits = 1;
    }
    return cp;
}

const char* parseZeroTail(const char *cp, const char *cp0) {
    char lo = TOLOWER(*cp);
    if (lo == 'x') return cp == cp0 + 1 && *cp0 == '0' ? parseHex(cp + 1) : NULL;
    if (cp <= cp0 + 1 && *cp != '0') {
        if (cp != cp0 || lo != 'i' || TOLOWER(cp[1]) != 'n' || TOLOWER(cp[2]) != 'f') return NULL;
        if (TOLOWER(cp[3]) != 'i') {
            cp += 3;
        } else {
            if (TOLOWER(cp[4]) != 'n' || TOLOWER(cp[5]) != 'i' || TOLOWER(cp[6]) != 't' || TOLOWER(cp[7]) != 'y') return NULL;
            cp += 8;
        }
        inf.bits = sup.bits = EXP_MASK;
        return cp;
    }
    if (lo == 'e') {
        DItype decExp;
        cp = parseExp(cp, &decExp);
        if (cp == NULL) return NULL;
    } else if (*cp == '/') {
        int nonzero = 0;
        char c = *++cp;
        while (c <= '9' && c >= '0') {
            if (c != '0') nonzero = 1;
            c = *++cp;
        }
        if (!nonzero) return NULL;
    }
    inf.bits = sup.bits = 0;
    return cp;
}

const char *skip_whitespaces(const char *cp) {
    cp--;
    char c;
    do {
        c = *++cp;
    } while (ISSPACE (c));
    return cp;
}

// OUT isNegative, mantS, firstNZ, dotPos
const char *scan_decimal(const char *cp) {
    cp = skip_whitespaces(cp);
    char c = *cp;
    isNegative = 0;
    if (c == '-' || c == '+') {
        if (c == '-') isNegative = 1;
        c = *++cp;
    }

    mantS = cp;
    firstNZ = NULL;
    dotPos = NULL;
    const char *lastNZ = NULL;

    while (c == '0') {
        c = *++cp;
    }
    if (c <= '9' && c > '0') firstNZ = cp;
    while (c <= '9' && c >= '0') {
        if (c > '0') lastNZ = cp;
        c = *++cp;
    }
    if (c == '.') {
        dotPos = cp;
        c = *++cp;
        if (firstNZ == NULL) {
            while (c == '0') {
                c = *++cp;
            }
            if (c <= '9' && c > '0') firstNZ = cp;
        }
        while (c <= '9' && c >= '0') {
            if (c > '0') lastNZ = cp;
            c = *++cp;
        }
    }
    if (firstNZ == NULL) {
        nDigits = 0;
        log10ceiling = fracExp = ulpExp = dotPos != NULL ? dotPos - cp + 1 : 0;
        return cp;
    }
    assert(lastNZ != NULL);
    lastNZ++;
    nDigits = lastNZ - firstNZ;
    if (dotPos == NULL) {
        log10ceiling = cp - firstNZ;
        fracExp = cp - lastNZ;
        ulpExp = 0;
    } else if (lastNZ <= dotPos) {
        log10ceiling = dotPos - firstNZ;
        fracExp = dotPos - lastNZ;
        ulpExp = dotPos - cp + 1;
    } else if (dotPos < firstNZ) {
        log10ceiling = (dotPos - firstNZ) + 1;
        fracExp = (dotPos - lastNZ) + 1;
        ulpExp = dotPos - cp + 1;
    } else {
        log10ceiling = dotPos - firstNZ;
        fracExp = (dotPos - lastNZ) + 1;
        nDigits--;
        ulpExp = dotPos - cp + 1;
    }
    return cp;
}

const char* parseRat(const char *cp, const char *begp) {
    const char *endp = cp;
    set_digits(&p, begp, endp);
    char c = *++cp;
    while (c == '0') {
        c = *++cp;
    }
    const char *begq = cp;
    if (c > '9' || c < '0') return NULL;
    do {
        c = *++cp;
    } while (c <= '9' && c >= '0');
    set_digits(&q, begq, cp);
    DItype diffLen = (endp - begp) - (cp - begq);
    if (diffLen > 310) {
        ieeeBits = EXP_MASK;
    } else if (diffLen < -330) {
        ieeeBits = 0;
    } else {
        guess_double();
    }
    if (ieeeBits == EXP_MASK) {
        inf.bits = EXP_MASK - 1;
        sup.bits = EXP_MASK;
        return cp;
    }
    if (ieeeBits == 0) {
        inf.bits = 0;
        sup.bits = 1;
        return cp;
    }
    init_f(ieeeBits);
    int cmp = cmp_loop();
    inf.bits = cmp >= 0 ? ieeeBits : ieeeBits - 1;
    sup.bits = cmp <= 0 ? ieeeBits : ieeeBits + 1;
    return cp;
}

void convertDec(int log10ceiling, int fracExp, int hasMore) {
    assert(log10ceiling >= MIN_VALUE_LOG10_CEILING);
    assert(log10ceiling <= MAX_VALUE_LOG10_CEILING);
    if (log10ceiling >= 17) {
        if (fracExp < 0) {
            fracExp = 0;
            hasMore = 1;
        }
    } else if (fracExp < -1022 - 52) {
        fracExp = -1022 - 52;
        hasMore = 1;
    }
    int nDigits = log10ceiling - fracExp;
    char *pCharsBeg = pChars + MAX_VALUE_LOG10_CEILING - log10ceiling;
    if (fracExp > 0) {
        assert(!hasMore);
        memset(pCharsBeg + nDigits, '0', fracExp);
        set_digits(&p, pCharsBeg, pCharsBeg + nDigits + fracExp);
        qChars[0] = '1';
        set_digits(&q, qChars, qChars + 1);
    } else {
        if (hasMore) {
            pCharsBeg[nDigits] = '1';
            nDigits++;
            fracExp--;
        }
        set_digits(&p, pCharsBeg, pCharsBeg + nDigits);
        qChars[0] = '1';
        memset(qChars + 1, '0', -fracExp);
        set_digits(&q, qChars, qChars - fracExp + 1);
    }
    guess_double();
    if (ieeeBits == EXP_MASK) {
        inf.bits = EXP_MASK - 1;
        sup.bits = EXP_MASK;
        return ;
    }
    if (ieeeBits == 0) {
        inf.bits = 0;
        sup.bits = 1;
        return ;
    }
    init_f(ieeeBits);
    int cmp = cmp_loop();
    inf.bits = cmp >= 0 ? ieeeBits : ieeeBits - 1;
    sup.bits = cmp <= 0 ? ieeeBits : ieeeBits + 1;
}

void convert() {
    if (log10ceiling < MIN_VALUE_LOG10_CEILING) {
        inf.bits = 0;
        sup.bits = 1;
        return ;
    }
    if (log10ceiling > MAX_VALUE_LOG10_CEILING) {
        inf.bits = EXP_MASK - 1;
        sup.bits = EXP_MASK;
        return ;
    }
    int hasMore = 0;
    if (fracExp < -1022 - 52) {
        nDigits -= -1022 - 52 - fracExp;
        fracExp = -1022 - 52;
        hasMore = 1;
    }
    char *pCharsBeg = pChars + MAX_VALUE_LOG10_CEILING - log10ceiling;
    if (dotPos == NULL || dotPos < firstNZ || dotPos >= firstNZ + nDigits) {
        memcpy(pCharsBeg, firstNZ, nDigits);
    } else {
        memcpy(pCharsBeg, firstNZ, dotPos - firstNZ);
        memcpy(pCharsBeg + (dotPos - firstNZ), dotPos + 1, nDigits - (dotPos - firstNZ));
    }
    convertDec(log10ceiling, fracExp, hasMore);
}

const char* parseNum(const char *cp) {
    inf.bits = sup.bits = 0xFFF8000000000000ull;
    cp = scan_decimal(cp);

    if (nDigits == 0) return parseZeroTail(cp, mantS);

    char c = *cp;
    if (c == '/') {
        if (dotPos != NULL) return NULL;
        return parseRat(cp, firstNZ);;
    }
    if (c == 'E' || c == 'e') {
        DItype decExp = 0;
        cp = parseExp(cp, &decExp);
        if (cp == NULL) return NULL;
        log10ceiling += decExp;
        fracExp += decExp;
    }

    convert();
    return cp;
}

const char* parseUncertain(const char *cp) {
    DItype e;
    const char *p;
    const char* lastCp = cp = scan_decimal(cp);
    if (cp == NULL || nDigits == 0 && cp <= mantS + 1 && *mantS != '0') return NULL;
    char c = *cp;
    if (*cp != '?') return NULL;
    c = *++cp;
    const char *radBeg = cp;
    while (c == '0') {
        c = *++cp;
    }
    const char *radFirstNZ = cp;
    while (c <= '9' && c >= '0') {
        c = *++cp;
    }
    int radInf = 0;
    if (radBeg == cp && *cp == '?') {
        radInf = 1;
        c = *++cp;
    }
    const char *radEnd = cp;
    char lo = TOLOWER(c);
    int dir = 0;
    if (lo == 'u') {
        dir = +1;
        lo = TOLOWER(*++cp);
    } else if (lo == 'd') {
        dir = -1;
        lo = TOLOWER(*++cp);
    }
    if (isNegative) dir = -dir;
    DItype decExp = 0;
    if (lo == 'e') {
        cp = parseExp(cp, &decExp);
        if (cp == NULL) return NULL;
        log10ceiling += decExp;
        fracExp += decExp;
        ulpExp += decExp;
    }
    DItype nRadDigits = radEnd - radFirstNZ;
    if (radInf || nRadDigits == 0 && radBeg != radEnd) {
        if (nDigits == 0) {
            inf.bits = sup.bits = 0;
        } else {
            convert();
        }
        if (radInf) {
            if (dir <= 0) inf.bits = SIGN_MASK | EXP_MASK;
            if (dir >= 0) sup.bits = EXP_MASK;
        }
        return cp;
    }
    int lowerCarryInf = 0, lowerCarrySup = 0;
    int lowerHasMoreInf = 0, lowerHasMoreSup = 0;
    if (ulpExp < -1022 - 52 || nRadDigits == 0 && ulpExp == -1022 - 52) {
        if (radBeg == radEnd) {
            lowerHasMoreInf = lowerHasMoreSup = 1;
            lowerCarryInf = -1;
        }
        p = lastCp;
        DItype em = log10ceiling;
        if (em < ulpExp + nRadDigits) em = ulpExp + nRadDigits;
        em++;
        if (em > -1022 - 52) em = -1022 - 52;
        for (e = ulpExp - 1;e < em;e++) {
            char midChar = '0';
            if (ulpExp <= e && e < log10ceiling) {
                midChar = *--p;
                if (midChar == '.') midChar = *--p;
            }
            char radChar = '0';
            if (e < ulpExp + nRadDigits) {
                radChar = radEnd[ulpExp - e - 1];
            }

            int sumSup = (midChar - '0') + lowerCarrySup;
            if (dir >= 0) sumSup += radChar - '0';
            if (sumSup >= 10) {
                sumSup -= 10;
                lowerCarrySup = 1;
            } else {
                lowerCarrySup = 0;
            }
            if (sumSup != 0) lowerHasMoreSup = 1;

            int sumInf = (midChar - '0') + lowerCarryInf;
            if (dir <= 0) sumInf -= radChar - '0';
            if (sumInf < 0) {
                sumInf += 10;
                lowerCarryInf = -1;
            } else {
                lowerCarryInf = 0;
            }
            if (sumInf != 0) lowerHasMoreInf = 1;
        }
    }
    int higherCarryInf = 0, higherCarrySup = 0;
    if (log10ceiling > MAX_VALUE_LOG10_CEILING || ulpExp + nRadDigits >= MAX_VALUE_LOG10_CEILING) {
        p = firstNZ;
        DItype ep = log10ceiling > ulpExp + nRadDigits ? log10ceiling : ulpExp + nRadDigits;
        DItype em = ulpExp - 2 > MAX_VALUE_LOG10_CEILING ? ulpExp - 2: MAX_VALUE_LOG10_CEILING;
        for (e = ep - 1;e >= em;e--) {
            char midChar = '0';
            if (fracExp <= e && e < log10ceiling) {
                midChar = *p++;
                if (midChar == '.') midChar = *p++;
            }
            char radChar = '0';
            if (ulpExp <= e && e < ulpExp + nRadDigits) {
                radChar = radEnd[ulpExp - e - 1];
            } else if (e == ulpExp - 1) {
                radChar = '5';
            }

            int sumSup = (midChar - '0');
            if (dir >= 0) sumSup += radChar - '0';
            if (sumSup) higherCarrySup = 1;

            int sumInf = (midChar - '0') + higherCarryInf*10;
            if (dir <= 0) sumInf -= radChar - '0';
            if (higherCarryInf == 0 || higherCarryInf == -1) higherCarryInf = sumInf;
        }
    }

    DItype uncertainUlpExp1;
    if (radBeg == radEnd) {
        uncertainUlpExp1 = ulpExp - 1 < -1022 - 52 ? -1022 - 52 : ulpExp - 1;
    } else {
        uncertainUlpExp1 = ulpExp < -1022 - 52 ? -1022 - 52 : ulpExp;
    }
    if (nDigits == 0) log10ceiling = uncertainUlpExp1;
    p = ulpExp >= uncertainUlpExp1 ? lastCp : lastCp - (uncertainUlpExp1 - ulpExp);
    if (dotPos != NULL && p <= dotPos) p--;
    int log10ceilingSup = uncertainUlpExp1;
    for (e = uncertainUlpExp1;e < MAX_VALUE_LOG10_CEILING;e++) {
        char midChar = '0';
        if (ulpExp <= e && e < log10ceiling) {
            midChar = *--p;
            if (midChar == '.') midChar = *--p;
        }
        char radChar = '0';
        if (ulpExp <= e && e < ulpExp + nRadDigits) {
            radChar = radEnd[ulpExp - e - 1];
        } else if (e == ulpExp - 1) {
            radChar = '5';
        }
        int sum = (midChar - '0') + lowerCarrySup;
        if (dir >= 0) sum += radChar - '0';
        char supChar;
        if (sum >= 10) {
            supChar = sum + ('0' - 10);
            lowerCarrySup = 1;
        } else {
            supChar = sum + '0';
            lowerCarrySup = 0;
        }
        pChars[MAX_VALUE_LOG10_CEILING - e - 1] = supChar;
        if (supChar != '0') log10ceilingSup = e + 1;
    }
    UWtype supbits;
    if (higherCarrySup || lowerCarrySup) {
        supbits = EXP_MASK;
    } else if (log10ceilingSup < MIN_VALUE_LOG10_CEILING) {
        supbits = 1;
    } else {
        convertDec(log10ceilingSup, uncertainUlpExp1, lowerHasMoreSup);
        supbits = sup.bits;
    }

    p = ulpExp >= uncertainUlpExp1 ? lastCp : lastCp - (uncertainUlpExp1 - ulpExp);
    if (dotPos != NULL && p <= dotPos) p--;
    int log10ceilingInf = uncertainUlpExp1;
    for (e = uncertainUlpExp1;e < MAX_VALUE_LOG10_CEILING;e++) {
        char midChar = '0';
        if (ulpExp <= e && e < log10ceiling) {
            midChar = *--p;
            if (midChar == '.') midChar = *--p;
        }
        char radChar = '0';
        if (ulpExp <= e && e < ulpExp + nRadDigits) {
            radChar = radEnd[ulpExp - e - 1];
        } else if (e == ulpExp - 1) {
            radChar = '5';
        }
        int sum = (midChar - '0') + lowerCarryInf;
        if (dir <= 0) sum -= radChar - '0';
        char infChar;
        if (sum < 0) {
            infChar = sum + ('0' + 10);
            lowerCarryInf = -1;
        } else {
            infChar = sum + '0';
            lowerCarryInf = 0;
        }
        pChars[MAX_VALUE_LOG10_CEILING - e - 1] = infChar;
        if (infChar != '0') log10ceilingInf = e + 1;
    }
    higherCarryInf += lowerCarryInf;
    if (higherCarryInf == 0) {
        if (log10ceilingInf <= uncertainUlpExp1) {
            inf.bits = 0;
        } else {
            convertDec(log10ceilingInf, uncertainUlpExp1, lowerHasMoreInf);
        }
    } else if (higherCarryInf == -1) {
        e = uncertainUlpExp1;
        if (!lowerHasMoreInf) {
            while (e < MAX_VALUE_LOG10_CEILING && pChars[MAX_VALUE_LOG10_CEILING - e - 1] == '0') {
                e++;
            }
        }
        if (e < MAX_VALUE_LOG10_CEILING) {
            char infChar = ('0' + '9' + 1) - pChars[MAX_VALUE_LOG10_CEILING - e - 1];
            pChars[MAX_VALUE_LOG10_CEILING - e - 1] = infChar;
            log10ceilingInf = e + 1;
            e++;
        }
        while (e < MAX_VALUE_LOG10_CEILING) {
            char infChar = ('0' + '9') - pChars[MAX_VALUE_LOG10_CEILING - e - 1];
            pChars[MAX_VALUE_LOG10_CEILING - e - 1] = infChar;
            if (infChar != '0') log10ceilingInf = e + 1;
            e++;
        }
        if (log10ceilingInf > MAX_VALUE_LOG10_CEILING) {
            inf.bits = SIGN_MASK | EXP_MASK;
        } else if (log10ceilingInf < MIN_VALUE_LOG10_CEILING) {
            inf.bits = SIGN_MASK | 1;
        } else {
            convertDec(log10ceilingInf, uncertainUlpExp1, lowerHasMoreInf);
            inf.bits = SIGN_MASK | sup.bits;
        }
    } else if (higherCarryInf > 0) {
        inf.bits = EXP_MASK - 1;
    } else {
        inf.bits = SIGN_MASK | EXP_MASK;
    }
    sup.bits = supbits;
    return cp;
}

void textToInterval(const char *cp, DECORATED_INFSUP_B64 *ret) {
    double locInf, locSup;
    int isinf = 0;
    char c = *cp;
    if (c == '[') {
        cp = skip_whitespaces(cp + 1);
        if (*cp == ']') {
            inf.bits = 0xFFF8000000000000ull;
            locInf = locSup = inf.d;
        } else if (TOLOWER(*cp) == 'e') {
            if (TOLOWER(cp[1]) == 'm' && TOLOWER(cp[2]) == 'p' && TOLOWER(cp[3]) == 't' && TOLOWER(cp[4]) == 'y') {
                cp += 5;
                inf.bits = 0xFFF8000000000000ull;
                locInf = locSup = inf.d;
            } else if (TOLOWER(cp[1]) == 'n' && TOLOWER(cp[2]) == 't' && TOLOWER(cp[3]) == 'i' && TOLOWER(cp[4]) == 'r' && TOLOWER(cp[5]) == 'e') {
                cp += 6;
                inf.bits = SIGN_MASK | EXP_MASK;
                sup.bits = EXP_MASK;
                locInf = inf.d;
                locSup = sup.d;
                isinf = 1;
            } else {
                cp = NULL;
            }
            if (cp != NULL) cp = skip_whitespaces(cp);
        } else {
            if (*cp == ',') {
                isNegative = 1;
                inf.bits = sup.bits = EXP_MASK;
            } else {
                cp = parseNum(cp);
            }
            if (cp != NULL) {
                if (inf.bits == EXP_MASK) isinf = 1;
                locInf = !isNegative ? inf.d : sup.d != 0 ? -sup.d : 0;
                locSup = !isNegative ? sup.d : inf.d != 0 ? -inf.d : 0;
                if (!isNegative && inf.bits == EXP_MASK) cp = NULL; // +Infinity forbidden
            }
            if (cp != NULL) cp = skip_whitespaces(cp);
            if (cp != NULL && *cp == ',') {
                cp = skip_whitespaces(cp + 1);
                if (*cp == ']') {
                    isNegative = 0;
                    inf.bits = sup.bits = EXP_MASK;
                } else {
                    cp = parseNum(cp);
                }
                if (cp != NULL) {
                    if (inf.bits == EXP_MASK) isinf = 1;
                    double rightInf = !isNegative ? inf.d : sup.d != 0 ? -sup.d : 0;
                    double rightSup = !isNegative ? sup.d : inf.d != 0 ? -inf.d : 0;
                    if (isNegative && sup.bits == EXP_MASK) cp = NULL; // -Infinity forbidden
                    if (cp != NULL) {
                        if (locSup <= rightInf) {
                            locSup = rightSup;
                        } else if (locInf != rightInf || locSup != rightSup) {
                            cp = NULL;
                        }
                    }
                    if (cp != NULL) cp = skip_whitespaces(cp);
                }
            } else {
                if (isNegative && sup.bits == EXP_MASK) cp = NULL; // -Infinity forbidden
            }
        }
        cp = cp != NULL && *cp == ']' ? cp + 1 : NULL;
    } else {
        cp = parseUncertain(cp);
        locInf = isNegative ? -sup.d : inf.d;
        locSup = isNegative ? -inf.d : sup.d;
    }
    int decor = COM;
    if (cp != NULL) {
        if (*cp == '_') {
            cp++;
            if (TOLOWER(cp[0]) == 't' && TOLOWER(cp[1]) == 'r' && TOLOWER(cp[2]) == 'v') {
                decor = TRV;
            } else if (TOLOWER(cp[0]) == 'd' && TOLOWER(cp[1]) == 'e' && TOLOWER(cp[2]) == 'f') {
                decor = DEF;
            } else if (TOLOWER(cp[0]) == 'd' && TOLOWER(cp[1]) == 'a' && TOLOWER(cp[2]) == 'c') {
                decor = DAC;
            } else if (TOLOWER(cp[0]) == 'c' && TOLOWER(cp[1]) == 'o' && TOLOWER(cp[2]) == 'm') {
                decor = COM;
            } else {
                cp = NULL;
            }
        } else {
            decor = locInf != locInf ? TRV : isinf ? DAC : COM;
        }
    }
    if (cp != NULL && *cp != 0) cp = NULL;
    if (cp != NULL && (locInf != locInf && decor != TRV || isinf && decor == COM)) cp = NULL;
    if (cp != NULL && decor == COM && (locInf == -INFINITY || locSup == +INFINITY)) decor = DAC;
    if (cp == NULL) {
        inf.bits = 0xFFF8000000000000ull;
        ret->inf = ret->sup = inf.d;
        ret->decoration = ILL;
    } else {
        ret->inf = locInf;
        ret->sup = locSup;
        ret->decoration = decor;
    }
}
