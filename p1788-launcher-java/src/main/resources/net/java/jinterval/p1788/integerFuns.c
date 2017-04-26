#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "jinterval.h"

#define INF_SUP        0
#define INF_SUP_NAN    1
#define NEGINF_SUP_NAN 0

#define SIGN_MASK_B64    0x8000000000000000ULL
#define EXP_MASK_B64     0x7ff0000000000000ULL
#define EXP_BIAS_B64     1023
#define PRECISION_B64    53
#define POS_INFINITY_B64 0x7ff0000000000000ULL
#define NEG_INFINITY_B64 0xffffffffffffffffULL

struct BARE_BITS_B64 {
    long long int inf;
    long long int sup;
};

#if INF_SUP
#define inf(x) ((x)->inf)
#define sup(x) ((x)->sup)
#define infbits(x) (((struct BARE_BITS_B64*)(x))->inf)
#define supbits(x) (((struct BARE_BITS_B64*)(x))->sup)
#define setbits(r,bi,bs) (((struct BARE_BITS_B64*)(r))->inf = (bi), ((struct BARE_BITS_B64*)(r))->sup = (bs))
#endif
#if INF_SUP_NAN
#define inf(x) ((x)->inf == 0.0 ? -0.0 : ((x)->inf == (x)->inf ? (x)->inf : +INFINITY))
#define sup(x) ((x)->sup == 0.0 ? +0.0 : ((x)->sup == (x)->sup ? (x)->sup : -INFINITY))
#define infbits(x) ((x)->inf == (x)->inf ? ((struct BARE_BITS_B64*)(x))->inf : POS_INFINITY_B64)
#define supbits(x) ((x)->sup == (x)->sup ? ((struct BARE_BITS_B64*)(x))->sup : NEG_INFINITY_B64)
#define setbits(r,bi,bs) (((struct BARE_BITS_B64*)(r))->inf = (bi), ((struct BARE_BITS_B64*)(r))->sup = (bs))
#endif
#if NEGINF_SUP_NAN
#define inf(x) ((x)->inf == 0.0 ? -0.0 : ((x)->inf == (x)->inf ? -(x)->inf : +INFINITY))
#define sup(x) ((x)->sup == 0.0 ? +0.0 : ((x)->sup == (x)->sup ? (x)->sup : -INFINITY))
#define infbits(x) ((x)->inf == (x)->inf ? ((struct BARE_BITS_B64*)(x))->inf ^ SIGN_MASK : POS_INFINITY_B64)
#define supbits(x) ((x)->sup == (x)->sup ? ((struct BARE_BITS_B64*)(x))->sup : NEG_INFINITY_B64)
#define setbits(r,bi,bs) (((struct BARE_BITS_B64*)(r))->inf = (bi) ^ SIGN_MASK, ((struct BARE_BITS_B64*)(r))->sup = (bs))
#endif

#define MIN(x,y) ((x) < (y) ? (x) : (y))

static int isValidBareInfsupB64(BARE_INFSUP_B64 *x) {
#if INF_SUP
    return x->inf == +INFINITY && x->sup == -INFINITY
            || x->inf <= x->sup && x->inf != +INFINITY && x->sup != -INFINITY
            && (x->inf != 0 || 1 / x->inf < 0)
            && (x->sup != 0 || 1 / x->sup > 0);
#endif
#if INF_SUP_NAN
    return x->inf != x->inf && x->sup != x->sup
            || x->inf <= x->sup && x->inf != +INFINITY && x->sup != -INFINITY;
#endif
#if NEGINF_SUP_NAN
    return x->inf != x->inf && x->sup != x->sup
            || -x->inf <= x->sup && x->inf != -INFINITY && x->sup != -INFINITY;
#endif
}

static int isValidDecoratedInfsupB64(DECORATED_INFSUP_B64 *x) {
    switch (x->decoration) {
        case COM:
            return isValidBareInfsupB64((BARE_INFSUP_B64*) x)
                    && -INFINITY < inf(x) && inf(x) <= sup(x) && sup(x) < +INFINITY;
        case DAC:
        case DEF:
            return isValidBareInfsupB64((BARE_INFSUP_B64*) x)
                    && inf(x) <= sup(x);
        case TRV:
            return isValidBareInfsupB64((BARE_INFSUP_B64*) x);
        case ILL:
            return x->inf != x->inf && x->sup != x->sup;
        default:
            return 0;
    }
}

static void setEmptyBareInfsupB64(BARE_INFSUP_B64 *x) {
#if INF_SUP
    x->inf = +INFINITY;
    x->sup = -INFINITY;
#endif
#if INF_SUP_NAN || NEGINF_SUP_NAN
    x->inf = x->sup = NAN;
#endif
}

static void setNaNDecoratedInfsupB64(DECORATED_INFSUP_B64 *x) {
    x->decoration = ILL;
    x->inf = x->sup = NAN;
}

int roundTiesToEvenBareInfsupB64(BARE_INFSUP_B64 *r, BARE_INFSUP_B64 *x) {
    assert(isValidBareInfsupB64(x));
    int d = COM;

    unsigned long long xi = infbits(x);
    int inf_e = ((int) ((xi & EXP_MASK_B64) >> (PRECISION_B64 - 1))) - EXP_BIAS_B64; // exponent of inf
    if (inf_e <= -1) {
        if ((xi & ~SIGN_MASK_B64) <= 0x3fe0000000000000ULL) // +-0.5
        {
            if ((xi & ~SIGN_MASK_B64) == 0x3fe0000000000000ULL) // +-0.5
            {
                d = DAC;
            }
            xi = SIGN_MASK_B64; // -0
        }
        else
        {
            xi = (xi & SIGN_MASK_B64) | 0x3ff0000000000000ULL; // +-1
        }
    } else if (inf_e < (PRECISION_B64 - 1)) {
        int sh = (PRECISION_B64 - 1) - inf_e; // bits to clear
        xi += (1ULL << (sh - 1)); // add 1/2
        if ((xi & ((1ULL << sh) - 1)) == 0) { // tie
            xi = (xi >> (sh + 1)) << (sh + 1); // round to even
            d = DAC;
        } else {
            xi = (xi >> sh) << sh;
        }
    }

    unsigned long long xs = supbits(x);
    int sup_e = ((int) ((xs & EXP_MASK_B64) >> (PRECISION_B64 - 1))) - EXP_BIAS_B64; // exponent of sup
    if (sup_e <= -1) {
        if ((xs & ~SIGN_MASK_B64) <= 0x3fe0000000000000ULL) // +-0.5
        {
            if ((xs & ~SIGN_MASK_B64) == 0x3fe0000000000000ULL) // +-0.5
            {
                d = DAC;
            }
            xs = 0; // +0
        }
        else
        {
            xs = (xs & SIGN_MASK_B64) | 0x3ff0000000000000ULL; // +-1
        }
    } else if (sup_e < (PRECISION_B64 - 1)) {
        int sh = (PRECISION_B64 - 1) - sup_e; // bits to clear
        xs += (1ULL << (sh - 1)); // add 1/2
        if ((xs & ((1ULL << sh) - 1)) == 0) { // tie
            xs = (xs >> (sh + 1)) << (sh + 1); // round to even
            d = DAC;
        } else {
            xs = (xs >> sh) << sh;
        }
    }

    if (xi != xs && (xi != SIGN_MASK_B64 || xs != 0)) {
        if (xs == NEG_INFINITY_B64) {
            setEmptyBareInfsupB64(r);
            return TRV;
        }
        d = DEF;
    }
    setbits(r, xi, xs);
    return d;
}

int roundTiesToAwayBareInfsupB64(BARE_INFSUP_B64 *r, BARE_INFSUP_B64 *x) {
    assert(isValidBareInfsupB64(x));
    int d = COM;

    unsigned long long xi = infbits(x);
    int inf_e = ((int) ((xi & EXP_MASK_B64) >> (PRECISION_B64 - 1))) - EXP_BIAS_B64; // exponent of inf
    if (inf_e <= -1) {
        if ((xi & ~SIGN_MASK_B64) < 0x3fe0000000000000ULL) // +-0.5
        {
            xi = SIGN_MASK_B64; // -0
        } else {
            if ((xi & ~SIGN_MASK_B64) == 0x3fe0000000000000ULL) // +-0.5
            {
                d = DAC;
            }
            xi = (xi & SIGN_MASK_B64) | 0x3ff0000000000000ULL; // +-1
        }
    } else if (inf_e < (PRECISION_B64 - 1)) {
        int sh = (PRECISION_B64 - 1) - inf_e; // bits to clear
        xi += (1ULL << (sh - 1)); // add 1/2
        if ((xi & ((1ULL << sh) - 1)) == 0) { // tie
            d = DAC;
        }
        xi = (xi >> sh) << sh; // round away
    }

    unsigned long long xs = supbits(x);
    int sup_e = ((int) ((xs & EXP_MASK_B64) >> (PRECISION_B64 - 1))) - EXP_BIAS_B64; // exponent of sup
    if (sup_e <= -1) {
        if ((xs & ~SIGN_MASK_B64) < 0x3fe0000000000000ULL) // +-0.5
        {
            xs = SIGN_MASK_B64; // -0
        } else {
            if ((xs & ~SIGN_MASK_B64) == 0x3fe0000000000000ULL) // +-0.5
            {
                d = DAC;
            }
            xs = (xs & SIGN_MASK_B64) | 0x3ff0000000000000ULL; // +-1
        }
    } else if (sup_e < (PRECISION_B64 - 1)) {
        int sh = (PRECISION_B64 - 1) - sup_e; // bits to clear
        xs += (1ULL << (sh - 1)); // add 1/2
        if ((xs & ((1ULL << sh) - 1)) == 0) { // tie
            d = DAC;
        }
        xs = (xs >> sh) << sh; // round away
    }

    if (xi != xs && (xi != SIGN_MASK_B64 || xs != 0)) {
        if (xs == NEG_INFINITY_B64) {
            setEmptyBareInfsupB64(r);
            return TRV;
        }
        d = DEF;
    }
    setbits(r, xi, xs);
    return d;
}

void roundTiesToEvenDecoratedInfsupB64(DECORATED_INFSUP_B64 *r, DECORATED_INFSUP_B64 *x) {
    assert(isValidDecoratedInfsupB64(x));
    if (x->decoration == ILL) {
        setNaNDecoratedInfsupB64(r);
        return;
    }
    int d = roundTiesToEvenBareInfsupB64((BARE_INFSUP_B64*) r, (BARE_INFSUP_B64*) x);
    r->decoration = MIN(d, x->decoration);
}

void roundTiesToAwayDecoratedInfsupB64(DECORATED_INFSUP_B64 *r, DECORATED_INFSUP_B64 *x) {
    assert(isValidDecoratedInfsupB64(x));
    if (x->decoration == ILL) {
        setNaNDecoratedInfsupB64(r);
        return;
    }
    int d = roundTiesToAwayBareInfsupB64((BARE_INFSUP_B64*) r, (BARE_INFSUP_B64*) x);
    r->decoration = MIN(d, x->decoration);
}
