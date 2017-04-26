
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <assert.h>
#include <mpfr.h>
#include "p1788_reduction.inc.c"
#include "mpfi_p1788.h"
#include "p1788.h"


#define MPFR_SAVE_RANGE_EXP(tag) mpfr_exp_t saved_emin, saved_emax; set_range_exp_tag((tag), &saved_emin, &saved_emax);
#define MPFR_RESTORE_RANGE_EXP() (mpfr_set_emin(saved_emin), mpfr_set_emax(saved_emax))

static void set_range_exp_tag(int tag, mpfr_exp_t* saved_emin, mpfr_exp_t* saved_emax) {
    *saved_emin = mpfr_get_emin();
    *saved_emax = mpfr_get_emax();
    switch (tag) {
        case TAG_f:
            mpfr_set_emin(FLT_MIN_EXP - FLT_MANT_DIG + 1);
            mpfr_set_emax(FLT_MAX_EXP);
            break;
        case TAG_d:
            mpfr_set_emin(DBL_MIN_EXP - DBL_MANT_DIG + 1);
            mpfr_set_emax(DBL_MAX_EXP);
            break;
        case TAG_l:
            mpfr_set_emin(LDBL_MIN_EXP - LDBL_MANT_DIG + 1);
            mpfr_set_emax(LDBL_MAX_EXP);
            break;
        default:
            assert(0);
            break;
    }
}

static mpfr_prec_t p1788_get_prec(int tag) {
    switch (tag) {
        case TAG_f:
            return FLT_MANT_DIG;
            break;
        case TAG_d:
            return DBL_MANT_DIG;
            break;
        case TAG_l:
            return LDBL_MANT_DIG;
            break;
        default:
            assert(0);
            break;
    }
}

static int is_valid_b(int tag, const void *x) {
    switch (tag) {
        case TAG_f:
            {
                BARE_INFSUP_B32* p = (BARE_INFSUP_B32*) x;
                return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || p->inf != p->inf && p->sup != p->sup;
            }
            break;
        case TAG_d:
            {
                BARE_INFSUP_B64* p = (BARE_INFSUP_B64*) x;
                return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || p->inf != p->inf && p->sup != p->sup;
            }
            break;
        case TAG_l:
            {
                BARE_INFSUP_B80* p = (BARE_INFSUP_B80*) x;
                return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || p->inf != p->inf && p->sup != p->sup;
            }
            break;
        default:
            assert(0);
            break;
    }
}

static int is_valid_d(int tag, const void *x) {
    switch (tag) {
        case TAG_f:
            {
                DECORATED_INFSUP_B32* p = (DECORATED_INFSUP_B32*) x;
                switch (p->decoration) {
                    case COM:
                        return p->inf <= p->sup && p->inf != -INFINITY && p->sup != INFINITY;
                        break;
                    case DAC:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY;
                        break;
                    case DEF:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY;
                        break;
                    case TRV:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || p->inf != p->inf && p->sup != p->sup;
                        break;
                    case ILL:
                        return p->inf != p->inf && p->sup != p->sup;
                        break;
                    default:
                        return 0;
                        break;
                }
            }
            break;
        case TAG_d:
            {
                DECORATED_INFSUP_B64* p = (DECORATED_INFSUP_B64*) x;
                switch (p->decoration) {
                    case COM:
                        return p->inf <= p->sup && p->inf != -INFINITY && p->sup != INFINITY;
                        break;
                    case DAC:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY;
                        break;
                    case DEF:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY;
                        break;
                    case TRV:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || p->inf != p->inf && p->sup != p->sup;
                        break;
                    case ILL:
                        return p->inf != p->inf && p->sup != p->sup;
                        break;
                    default:
                        return 0;
                        break;
                }
            }
            break;
        case TAG_l:
            {
                DECORATED_INFSUP_B80* p = (DECORATED_INFSUP_B80*) x;
                switch (p->decoration) {
                    case COM:
                        return p->inf <= p->sup && p->inf != -INFINITY && p->sup != INFINITY;
                        break;
                    case DAC:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY;
                        break;
                    case DEF:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY;
                        break;
                    case TRV:
                        return p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || p->inf != p->inf && p->sup != p->sup;
                        break;
                    case ILL:
                        return p->inf != p->inf && p->sup != p->sup;
                        break;
                    default:
                        return 0;
                        break;
                }
            }
            break;
        default:
            assert(0);
            break;
    }
}

static int is_nai(int tag, const void *x) {
    switch (tag) {
        case TAG_f:
            return ((DECORATED_INFSUP_B32*) x)->decoration == ILL;
            break;
        case TAG_d:
            return ((DECORATED_INFSUP_B64*) x)->decoration == ILL;
            break;
        case TAG_l:
            return ((DECORATED_INFSUP_B80*) x)->decoration == ILL;
            break;
        default:
            assert(0);
            break;
    }
}

static void p1788_get_fr(mpfr_ptr mx, int tag, const void *x) {
    mpfr_init2(mx, p1788_get_prec(tag));
    int t;
    switch (tag) {
        case TAG_f:
            t = mpfr_set_flt(mx, *((float*) x), MPFR_RNDN);
            break;
        case TAG_d:
            t = mpfr_set_d(mx, *((double*) x), MPFR_RNDN);
            break;
        case TAG_l:
            t = mpfr_set_ld(mx, *((long double*) x), MPFR_RNDN);
            break;
        default:
            assert(0);
            break;
    }
    assert(t == 0);
}

static void p1788_b_get_fi(mpfi_ptr mx, int tag, const void *x) {
    mpfi_init2(mx, p1788_get_prec(tag));
    int tl, tr;
    switch (tag) {
        case TAG_f:
            {
                BARE_INFSUP_B32* p = (BARE_INFSUP_B32*) x;
                tl = mpfr_set_flt(&mx->left, p->inf, MPFR_RNDD);
                tr = mpfr_set_flt(&mx->right, p->sup, MPFR_RNDU);
            }
            break;
        case TAG_d:
            {
                BARE_INFSUP_B64* p = (BARE_INFSUP_B64*) x;
                tl = mpfr_set_d(&mx->left, p->inf, MPFR_RNDD);
                tr = mpfr_set_d(&mx->right, p->sup, MPFR_RNDU);
            }
            break;
        case TAG_l:
            {
                BARE_INFSUP_B80* p = (BARE_INFSUP_B80*) x;
                tl = mpfr_set_ld(&mx->left, p->inf, MPFR_RNDD);
                tr = mpfr_set_ld(&mx->right, p->sup, MPFR_RNDU);
            }
            break;
        default:
            assert(0);
            break;
    }
    assert(tl == 0 && tr == 0);
    if (mpfr_zero_p(&mx->left) && mpfr_signbit(&mx->left)) mpfr_set_zero(&mx->left, 1);
    if (mpfr_zero_p(&mx->right) && !mpfr_signbit(&mx->right)) mpfr_set_zero(&mx->right, -1);
    if (mpfi_is_empty(mx)) mpfi_p1788_empty(mx);
}

static int p1788_d_get_fi(mpfi_ptr mx, int tag, const void *x, int dec) {
    mpfi_init2(mx, p1788_get_prec(tag));
    int tl, tr, mydec;
    switch (tag) {
        case TAG_f:
            {
                DECORATED_INFSUP_B32* p = (DECORATED_INFSUP_B32*) x;
                tl = mpfr_set_flt(&mx->left, p->inf, MPFR_RNDD);
                tr = mpfr_set_flt(&mx->right, p->sup, MPFR_RNDU);
                mydec = p->decoration;
            }
            break;
        case TAG_d:
            {
                DECORATED_INFSUP_B64* p = (DECORATED_INFSUP_B64*) x;
                tl = mpfr_set_d(&mx->left, p->inf, MPFR_RNDD);
                tr = mpfr_set_d(&mx->right, p->sup, MPFR_RNDU);
                mydec = p->decoration;
            }
            break;
        case TAG_l:
            {
                DECORATED_INFSUP_B80* p = (DECORATED_INFSUP_B80*) x;
                tl = mpfr_set_ld(&mx->left, p->inf, MPFR_RNDD);
                tr = mpfr_set_ld(&mx->right, p->sup, MPFR_RNDU);
                mydec = p->decoration;
            }
            break;
        default:
            assert(0);
            break;
    }
    assert(tl == 0 && tr == 0);
    if (mpfr_zero_p(&mx->left) && mpfr_signbit(&mx->left)) mpfr_set_zero(&mx->left, 1);
    if (mpfr_zero_p(&mx->right) && !mpfr_signbit(&mx->right)) mpfr_set_zero(&mx->right, -1);
    if (mpfi_is_empty(mx)) mpfi_p1788_empty(mx);
    return mydec < dec ? mydec : dec;
}

static void p1788_set_nan(int tag, void *x) {
    switch (tag) {
        case TAG_f:
            *((float*) x) = NAN;
            break;
        case TAG_d:
            *((double*) x) = NAN;
            break;
        case TAG_l:
            *((long double*) x) = NAN;
            break;
        default:
            assert(0);
            break;
    }
}

static void p1788_set_fr(int tag, void *x, mpfr_srcptr mx) {
    switch (tag) {
        case TAG_f:
            *((float*) x) = mpfr_get_flt(mx, MPFR_RNDN);
            break;
        case TAG_d:
            *((double*) x) = mpfr_get_d(mx, MPFR_RNDN);
            break;
        case TAG_l:
            *((long double*) x) = mpfr_get_ld(mx, MPFR_RNDN);
            break;
        default:
            assert(0);
            break;
    }
}

static void p1788_b_set_fi(int tag, void *x, mpfi_srcptr mx) {
    switch (tag) {
        case TAG_f:
            {
                BARE_INFSUP_B32* p = (BARE_INFSUP_B32*) x;
                if (mpfi_is_empty(mx)) {
                    p->inf = NAN;
                    p->sup = NAN;
                } else {
                    p->inf = mpfr_zero_p(&mx->left) ? -0.0 : mpfr_get_flt(&mx->left, MPFR_RNDD);
                    p->sup = mpfr_zero_p(&mx->right) ? +0.0 : mpfr_get_flt(&mx->right, MPFR_RNDU);
                }
            }
            break;
        case TAG_d:
            {
                BARE_INFSUP_B64* p = (BARE_INFSUP_B64*) x;
                if (mpfi_is_empty(mx)) {
                    p->inf = NAN;
                    p->sup = NAN;
                } else {
                    p->inf = mpfr_zero_p(&mx->left) ? -0.0 : mpfr_get_d(&mx->left, MPFR_RNDD);
                    p->sup = mpfr_zero_p(&mx->right) ? +0.0 : mpfr_get_d(&mx->right, MPFR_RNDU);
                }
            }
            break;
        case TAG_l:
            {
                BARE_INFSUP_B80* p = (BARE_INFSUP_B80*) x;
                if (mpfi_is_empty(mx)) {
                    p->inf = NAN;
                    p->sup = NAN;
                } else {
                    p->inf = mpfr_zero_p(&mx->left) ? -0.0 : mpfr_get_ld(&mx->left, MPFR_RNDD);
                    p->sup = mpfr_zero_p(&mx->right) ? +0.0 : mpfr_get_ld(&mx->right, MPFR_RNDU);
                }
            }
            break;
        default:
            assert(0);
            break;
    }
}

static void p1788_d_set_fi(int tag, void *x, mpfi_srcptr mx, int dec) {
    switch (tag) {
        case TAG_f:
            {
                DECORATED_INFSUP_B32* p = (DECORATED_INFSUP_B32*) x;
                if (dec <= ILL) {
                    p->inf = p->sup = NAN;
                    dec = ILL;
                } else if (mpfi_is_empty(mx)) {
                    p->inf = NAN;
                    p->sup = NAN;
                } else {
                    p->inf = mpfr_zero_p(&mx->left) ? -0.0 : mpfr_get_flt(&mx->left, MPFR_RNDD);
                    p->sup = mpfr_zero_p(&mx->right) ? +0.0 : mpfr_get_flt(&mx->right, MPFR_RNDU);
                }
                p->decoration = dec;
            }
            break;
        case TAG_d:
            {
                DECORATED_INFSUP_B64* p = (DECORATED_INFSUP_B64*) x;
                if (dec <= ILL) {
                    p->inf = p->sup = NAN;
                    dec = ILL;
                } else if (mpfi_is_empty(mx)) {
                    p->inf = NAN;
                    p->sup = NAN;
                } else {
                    p->inf = mpfr_zero_p(&mx->left) ? -0.0 : mpfr_get_d(&mx->left, MPFR_RNDD);
                    p->sup = mpfr_zero_p(&mx->right) ? +0.0 : mpfr_get_d(&mx->right, MPFR_RNDU);
                }
                p->decoration = dec;
            }
            break;
        case TAG_l:
            {
                DECORATED_INFSUP_B80* p = (DECORATED_INFSUP_B80*) x;
                if (dec <= ILL) {
                    p->inf = p->sup = NAN;
                    dec = ILL;
                } else if (mpfi_is_empty(mx)) {
                    p->inf = NAN;
                    p->sup = NAN;
                } else {
                    p->inf = mpfr_zero_p(&mx->left) ? -0.0 : mpfr_get_ld(&mx->left, MPFR_RNDD);
                    p->sup = mpfr_zero_p(&mx->right) ? +0.0 : mpfr_get_ld(&mx->right, MPFR_RNDU);
                }
                p->decoration = dec;
            }
            break;
        default:
            assert(0);
            break;
    }
}

int p1788_bar_isValid(int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return EXC_INVALID_OPERAND;
    return 1;
}

int p1788_dec_isValid(int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    return 1;
}

int p1788_bar_empty(int r_tag, void *r) {
    switch (r_tag) {
        case TAG_f:
            {
                BARE_INFSUP_B32* p = (BARE_INFSUP_B32*) r;
                p->inf = NAN;
                p->sup = NAN;
            }
            break;
        case TAG_d:
            {
                BARE_INFSUP_B64* p = (BARE_INFSUP_B64*) r;
                p->inf = NAN;
                p->sup = NAN;
            }
            break;
        case TAG_l:
            {
                BARE_INFSUP_B80* p = (BARE_INFSUP_B80*) r;
                p->inf = NAN;
                p->sup = NAN;
            }
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}

int p1788_dec_empty(int r_tag, void *r) {
    switch (r_tag) {
        case TAG_f:
            {
                DECORATED_INFSUP_B32* p = (DECORATED_INFSUP_B32*) r;
                p->inf = NAN;
                p->sup = NAN;
                p->decoration = TRV;
            }
            break;
        case TAG_d:
            {
                DECORATED_INFSUP_B64* p = (DECORATED_INFSUP_B64*) r;
                p->inf = NAN;
                p->sup = NAN;
                p->decoration = TRV;
            }
            break;
        case TAG_l:
            {
                DECORATED_INFSUP_B80* p = (DECORATED_INFSUP_B80*) r;
                p->inf = NAN;
                p->sup = NAN;
                p->decoration = TRV;
            }
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}

int p1788_bar_entire(int r_tag, void *r) {
    switch (r_tag) {
        case TAG_f:
            {
                BARE_INFSUP_B32* p = (BARE_INFSUP_B32*) r;
                p->inf = -INFINITY;
                p->sup = +INFINITY;
            }
            break;
        case TAG_d:
            {
                BARE_INFSUP_B64* p = (BARE_INFSUP_B64*) r;
                p->inf = -INFINITY;
                p->sup = +INFINITY;
            }
            break;
        case TAG_l:
            {
                BARE_INFSUP_B80* p = (BARE_INFSUP_B80*) r;
                p->inf = -INFINITY;
                p->sup = +INFINITY;
            }
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}

int p1788_dec_entire(int r_tag, void *r) {
    switch (r_tag) {
        case TAG_f:
            {
                DECORATED_INFSUP_B32* p = (DECORATED_INFSUP_B32*) r;
                p->inf = -INFINITY;
                p->sup = +INFINITY;
                p->decoration = DAC;
            }
            break;
        case TAG_d:
            {
                DECORATED_INFSUP_B64* p = (DECORATED_INFSUP_B64*) r;
                p->inf = -INFINITY;
                p->sup = +INFINITY;
                p->decoration = DAC;
            }
            break;
        case TAG_l:
            {
                DECORATED_INFSUP_B80* p = (DECORATED_INFSUP_B80*) r;
                p->inf = -INFINITY;
                p->sup = +INFINITY;
                p->decoration = DAC;
            }
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}

int p1788_dec_nai(int r_tag, void *r) {
    switch (r_tag) {
        case TAG_f:
            {
                DECORATED_INFSUP_B32* p = (DECORATED_INFSUP_B32*) r;
                p->inf = NAN;
                p->sup = NAN;
                p->decoration = ILL;
            }
            break;
        case TAG_d:
            {
                DECORATED_INFSUP_B64* p = (DECORATED_INFSUP_B64*) r;
                p->inf = NAN;
                p->sup = NAN;
                p->decoration = ILL;
            }
            break;
        case TAG_l:
            {
                DECORATED_INFSUP_B80* p = (DECORATED_INFSUP_B80*) r;
                p->inf = NAN;
                p->sup = NAN;
                p->decoration = ILL;
            }
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}

int p1788_bar_convertType(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_convertType(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_convertType(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_convertType(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_pos(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_pos(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_pos(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_pos(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_neg(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_neg(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_neg(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_neg(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_add(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_add(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_add(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_add(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_sub(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sub(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_sub(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sub(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_mul(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_mul(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_mul(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_mul(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_div(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_div(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_div(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_div(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_recip(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_recip(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_recip(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_recip(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_sqr(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sqr(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_sqr(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sqr(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_sqrt(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrt(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_sqrt(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrt(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_fma(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y, int z_tag, const void *z) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y) || !is_valid_b(z_tag, z)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my, mz;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    p1788_b_get_fi(mz, z_tag, z);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_fma(mr, mx, my, mz));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mz);
    return 0;
}

int p1788_dec_fma(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y, int z_tag, const void *z) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y) || !is_valid_d(z_tag, z)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y) || is_nai(z_tag, z)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my, mz;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    d = p1788_d_get_fi(mz, z_tag, z, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_fma(mr, mx, my, mz)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mz);
    return 0;
}

int p1788_bar_pown(int r_tag, void *r, int x_tag, const void *x, int p) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_pown(mr, mx, p));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_pown(int r_tag, void *r, int x_tag, const void *x, int p) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_pown(mr, mx, p)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_pow(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_pow(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_pow(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_pow(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_exp(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_exp(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_exp(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_exp(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_exp2(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_exp2(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_exp2(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_exp2(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_exp10(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_exp10(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_exp10(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_exp10(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_log(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_log(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_log(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_log(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_log2(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_log2(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_log2(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_log2(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_log10(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_log10(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_log10(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_log10(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_sin(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sin(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_sin(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sin(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_cos(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cos(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_cos(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_cos(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_tan(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_tan(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_tan(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_tan(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_asin(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_asin(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_asin(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_asin(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_acos(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_acos(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_acos(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_acos(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_atan(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_atan(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_atan(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_atan2(int r_tag, void *r, int y_tag, const void *y, int x_tag, const void *x) {
    if (!is_valid_b(y_tag, y) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, my, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(my, y_tag, y);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2(mr, my, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(my);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_atan2(int r_tag, void *r, int y_tag, const void *y, int x_tag, const void *x) {
    if (!is_valid_d(y_tag, y) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(y_tag, y) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, my, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(my, y_tag, y, COM);
    d = p1788_d_get_fi(mx, x_tag, x, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2(mr, my, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(my);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_sinh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sinh(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_sinh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sinh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_cosh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cosh(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_cosh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_cosh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_tanh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_tanh(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_tanh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_tanh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_asinh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_asinh(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_asinh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_asinh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_acosh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_acosh(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_acosh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_acosh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_atanh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atanh(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_atanh(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_atanh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_sign(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sign(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_sign(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sign(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_ceil(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_ceil(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_ceil(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_ceil(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_floor(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_floor(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_floor(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_floor(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_trunc(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_trunc(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_trunc(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_trunc(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_roundTiesToEven(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToEven(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_roundTiesToEven(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToEven(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_roundTiesToAway(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToAway(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_roundTiesToAway(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToAway(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_abs(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_abs(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_abs(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_abs(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_min(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_min(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_min(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_min(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_max(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_max(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_max(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    d = p1788_d_get_fi(my, y_tag, y, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_max(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec < d ? locdec : d);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_mulRevToPair(int r_tag, void *r1, void *r2, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_b(b_tag, b) || !is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r1), p1788_bar_empty(r_tag, r2), EXC_INVALID_OPERAND;
    mpfi_t mr1, mr2, mb, mc;
    mpfi_init2(mr1, p1788_get_prec(r_tag));
    mpfi_init2(mr2, p1788_get_prec(r_tag));
    p1788_b_get_fi(mb, b_tag, b);
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_mulRevToPairSubnormal(mr1, mr2, mb, mc);
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r1, mr1);
    p1788_b_set_fi(r_tag, r2, mr2);
    mpfi_clear(mr1);
    mpfi_clear(mr2);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_mulRevToPair(int r_tag, void *r1, void *r2, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_d(b_tag, b) || !is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r1), p1788_dec_nai(r_tag, r2), EXC_INVALID_OPERAND;
    if (is_nai(b_tag, b) || is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r1), p1788_dec_nai(r_tag, r2);
    mpfi_t mr1, mr2, mb, mc;
    mpfi_init2(mr1, p1788_get_prec(r_tag));
    mpfi_init2(mr2, p1788_get_prec(r_tag));
    int d = p1788_d_get_fi(mb, b_tag, b, COM);
    d = p1788_d_get_fi(mc, c_tag, c, d);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_mulRevToPairSubnormal(mr1, mr2, mb, mc) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r1, mr1, locdec < d ? locdec : d);
    p1788_d_set_fi(r_tag, r2, mr2, TRV);
    mpfi_clear(mr1);
    mpfi_clear(mr2);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_sqrRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_sqrRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_sqrRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_sqrRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_absRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_absRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_absRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_absRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_absRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_absRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_absRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_absRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_pownRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x, int p) {
    if (!is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRev(mr, mc, mx, p));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_pownRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x, int p) {
    if (!is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRev(mr, mc, mx, p));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_pownRevEntire(int r_tag, void *r, int c_tag, const void *c, int p) {
    if (!is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRevEntire(mr, mc, p));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_pownRevEntire(int r_tag, void *r, int c_tag, const void *c, int p) {
    if (!is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRevEntire(mr, mc, p));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_sinRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_sinRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_sinRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_sinRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_cosRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_cosRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_cosRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_cosRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_tanRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_tanRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_tanRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_tanRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_coshRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_coshRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRev(mr, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_coshRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_coshRevEntire(int r_tag, void *r, int c_tag, const void *c) {
    if (!is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRevEntire(mr, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_mulRev(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(b_tag, b) || !is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mb, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mb, b_tag, b);
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRev(mr, mb, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_mulRev(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(b_tag, b) || !is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(b_tag, b) || is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mb, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mb, b_tag, b, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRev(mr, mb, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_mulRevEntire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_b(b_tag, b) || !is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mb, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mb, b_tag, b);
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRevEntire(mr, mb, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_mulRevEntire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_d(b_tag, b) || !is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(b_tag, b) || is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mb, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mb, b_tag, b, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRevEntire(mr, mb, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_powRev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(b_tag, b) || !is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mb, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mb, b_tag, b);
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1(mr, mb, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_powRev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(b_tag, b) || !is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(b_tag, b) || is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mb, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mb, b_tag, b, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1(mr, mb, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_powRev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_b(b_tag, b) || !is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mb, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mb, b_tag, b);
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1Entire(mr, mb, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_powRev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_d(b_tag, b) || !is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(b_tag, b) || is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mb, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mb, b_tag, b, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1Entire(mr, mb, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_powRev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, ma, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2(mr, ma, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_powRev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, ma, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2(mr, ma, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_powRev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, ma, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2Entire(mr, ma, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_powRev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, ma, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2Entire(mr, ma, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_atan2Rev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(b_tag, b) || !is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mb, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mb, b_tag, b);
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1(mr, mb, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_atan2Rev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(b_tag, b) || !is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(b_tag, b) || is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mb, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mb, b_tag, b, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1(mr, mb, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_atan2Rev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_b(b_tag, b) || !is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mb, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mb, b_tag, b);
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1Entire(mr, mb, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_atan2Rev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c) {
    if (!is_valid_d(b_tag, b) || !is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(b_tag, b) || is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mb, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mb, b_tag, b, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1Entire(mr, mb, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mb);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_atan2Rev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(c_tag, c) || !is_valid_b(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, ma, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mc, c_tag, c);
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2(mr, ma, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_atan2Rev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(c_tag, c) || !is_valid_d(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(c_tag, c) || is_nai(x_tag, x)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, ma, mc, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2(mr, ma, mc, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_atan2Rev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(c_tag, c)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, ma, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mc, c_tag, c);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2Entire(mr, ma, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    return 0;
}

int p1788_dec_atan2Rev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(c_tag, c)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(c_tag, c)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, ma, mc;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mc, c_tag, c, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2Entire(mr, ma, mc));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(ma);
    mpfi_clear(mc);
    return 0;
}

int p1788_bar_cancelMinus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelMinus(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_cancelMinus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    p1788_d_get_fi(my, y_tag, y, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelMinus(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_cancelPlus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelPlus(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_cancelPlus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    p1788_d_get_fi(my, y_tag, y, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelPlus(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_intersection(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_intersection(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_intersection(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    p1788_d_get_fi(my, y_tag, y, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_intersection(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_convexHull(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_b(x_tag, x) || !is_valid_b(y_tag, y)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    p1788_b_get_fi(my, y_tag, y);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_convexHull(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_dec_convexHull(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y) {
    if (!is_valid_d(x_tag, x) || !is_valid_d(y_tag, y)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x) || is_nai(y_tag, y)) return p1788_dec_nai(r_tag, r);
    mpfi_t mr, mx, my;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    p1788_d_get_fi(my, y_tag, y, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_convexHull(mr, mx, my));
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, TRV);
    mpfi_clear(mr);
    mpfi_clear(mx);
    mpfi_clear(my);
    return 0;
}

int p1788_bar_numsToInterval(int r_tag, void *r, int l_tag, const void *l, int u_tag, const void *u) {
    mpfi_t mr;
    mpfr_t ml, mu;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_get_fr(ml, l_tag, l);
    p1788_get_fr(mu, u_tag, u);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_numsToInterval(mr, ml, mu);
    if (locdec >= 0) (locdec = mpfi_p1788_subnormalize(mr, locdec), 0);
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfr_clear(ml);
    mpfr_clear(mu);
    return locdec;
}

int p1788_dec_numsToInterval(int r_tag, void *r, int l_tag, const void *l, int u_tag, const void *u) {
    mpfi_t mr;
    mpfr_t ml, mu;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_get_fr(ml, l_tag, l);
    p1788_get_fr(mu, u_tag, u);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_numsToInterval(mr, ml, mu);
    if (locdec >= 0) locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec);
    mpfi_clear(mr);
    mpfr_clear(ml);
    mpfr_clear(mu);
    return locdec >= 0 ? 0 : locdec;
}

int p1788_dec_numsDecToInterval(int r_tag, void *r, int l_tag, const void *l, int u_tag, const void *u, int dec) {
    if (dec != COM && dec != DAC && dec != DEF && dec != TRV && dec != ILL) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr;
    mpfr_t ml, mu;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_get_fr(ml, l_tag, l);
    p1788_get_fr(mu, u_tag, u);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_numsDecToInterval(mr, ml, mu, dec);
    if (locdec >= 0) locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec);
    mpfi_clear(mr);
    mpfr_clear(ml);
    mpfr_clear(mu);
    return locdec >= 0 ? 0 : locdec;
}

int p1788_bar_textToInterval(int r_tag, void *r, const char* s) {
    if (s == NULL) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_textToInterval(mr, s);
    if (locdec >= 0) (locdec = mpfi_p1788_subnormalize(mr, locdec), 0);
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    return locdec;
}

int p1788_dec_textToDecoratedInterval(int r_tag, void *r, const char* s) {
    if (s == NULL) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_textToDecoratedInterval(mr, s);
    if (locdec >= 0) locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec);
    mpfi_clear(mr);
    return locdec >= 0 ? 0 : locdec;
}

int p1788_bar_inf(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_infSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_dec_inf(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r), 0;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_infSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_bar_sup(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_supSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_dec_sup(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r), 0;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_supSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_bar_mid(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_midSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_dec_mid(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r), 0;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_midSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_bar_rad(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_radSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_dec_rad(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r), 0;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_radSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_bar_wid(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_widSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_dec_wid(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r), 0;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_widSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_bar_mag(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_magSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_dec_mag(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r), 0;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_magSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_bar_mig(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_migSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_dec_mig(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r), 0;
    mpfi_t mx;
    mpfr_t mr;
    mpfr_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_migSubnormal(mr, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r, mr);
    mpfi_clear(mx);
    mpfr_clear(mr);
    return 0;
}

int p1788_bar_midRad(int r_tag, void *r1, void *r2, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_set_nan(r_tag, r1), p1788_set_nan(r_tag, r2), EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mr1, mr2;
    mpfr_init2(mr1, p1788_get_prec(r_tag));
    mpfr_init2(mr2, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_midRadSubnormal(mr1, mr2, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r1, mr1);
    p1788_set_fr(r_tag, r2, mr2);
    mpfi_clear(mx);
    mpfr_clear(mr1);
    mpfr_clear(mr2);
    return 0;
}

int p1788_dec_midRad(int r_tag, void *r1, void *r2, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_set_nan(r_tag, r1), p1788_set_nan(r_tag, r2), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_set_nan(r_tag, r1), p1788_set_nan(r_tag, r2), 0;
    mpfi_t mx;
    mpfr_t mr1, mr2;
    mpfr_init2(mr1, p1788_get_prec(r_tag));
    mpfr_init2(mr2, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_midRadSubnormal(mr1, mr2, mx);
    MPFR_RESTORE_RANGE_EXP();
    p1788_set_fr(r_tag, r1, mr1);
    p1788_set_fr(r_tag, r2, mr2);
    mpfi_clear(mx);
    mpfr_clear(mr1);
    mpfr_clear(mr2);
    return 0;
}

int p1788_bar_isEmpty(int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return EXC_INVALID_OPERAND;
    mpfi_t mx;
    p1788_b_get_fi(mx, x_tag, x);
    int result = mpfi_p1788_isEmpty(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_dec_isEmpty(int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return 0;
    mpfi_t mx;
    p1788_d_get_fi(mx, x_tag, x, TRV);
    int result = mpfi_p1788_isEmpty(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_bar_isEntire(int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return EXC_INVALID_OPERAND;
    mpfi_t mx;
    p1788_b_get_fi(mx, x_tag, x);
    int result = mpfi_p1788_isEntire(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_dec_isEntire(int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return 0;
    mpfi_t mx;
    p1788_d_get_fi(mx, x_tag, x, TRV);
    int result = mpfi_p1788_isEntire(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_dec_isNaI(int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    return is_nai(x_tag, x);
}

int p1788_bar_isCommonInterval(int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return EXC_INVALID_OPERAND;
    mpfi_t mx;
    p1788_b_get_fi(mx, x_tag, x);
    int result = mpfi_p1788_isCommonInterval(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_dec_isCommonInterval(int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return 0;
    mpfi_t mx;
    p1788_d_get_fi(mx, x_tag, x, TRV);
    int result = mpfi_p1788_isCommonInterval(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_bar_isSingleton(int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return EXC_INVALID_OPERAND;
    mpfi_t mx;
    p1788_b_get_fi(mx, x_tag, x);
    int result = mpfi_p1788_isSingleton(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_dec_isSingleton(int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return 0;
    mpfi_t mx;
    p1788_d_get_fi(mx, x_tag, x, TRV);
    int result = mpfi_p1788_isSingleton(mx);
    mpfi_clear(mx);
    return result;
}

int p1788_bar_isMember(int m_tag, const void *m, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return EXC_INVALID_OPERAND;
    mpfi_t mx;
    mpfr_t mm;
    p1788_get_fr(mm, m_tag, m);
    p1788_b_get_fi(mx, x_tag, x);
    int result = mpfi_p1788_isMember(mm, mx);
    mpfi_clear(mx);
    mpfr_clear(mm);
    return result;
}

int p1788_dec_isMember(int m_tag, const void *m, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return 0;
    mpfi_t mx;
    mpfr_t mm;
    p1788_get_fr(mm, m_tag, m);
    p1788_d_get_fi(mx, x_tag, x, TRV);
    int result = mpfi_p1788_isMember(mm, mx);
    mpfi_clear(mx);
    mpfr_clear(mm);
    return result;
}

int p1788_bar_equal(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_equal(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_equal(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_equal(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_subset(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_subset(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_subset(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_subset(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_less(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_less(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_less(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_less(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_precedes(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_precedes(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_precedes(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_precedes(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_interior(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_interior(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_interior(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_interior(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_strictLess(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_strictLess(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_strictLess(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_strictLess(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_strictPrecedes(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_strictPrecedes(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_strictPrecedes(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_strictPrecedes(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_disjoint(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_disjoint(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_disjoint(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_disjoint(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_bar_overlap(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_b(a_tag, a) || !is_valid_b(b_tag, b)) return EXC_INVALID_OPERAND;
    mpfi_t ma, mb;
    p1788_b_get_fi(ma, a_tag, a);
    p1788_b_get_fi(mb, b_tag, b);
    int result = mpfi_p1788_overlap(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_overlap(int a_tag, const void *a, int b_tag, const void *b) {
    if (!is_valid_d(a_tag, a) || !is_valid_d(b_tag, b)) return EXC_INVALID_OPERAND;
    if (is_nai(a_tag, a) || is_nai(b_tag, b)) return 0;
    mpfi_t ma, mb;
    p1788_d_get_fi(ma, a_tag, a, TRV);
    p1788_d_get_fi(mb, b_tag, b, TRV);
    int result = mpfi_p1788_overlap(ma, mb);
    mpfi_clear(ma);
    mpfi_clear(mb);
    return result;
}

int p1788_dec_newDec(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_newDec(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_decorationPart(int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return 0;
    mpfi_t mx;
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    mpfi_clear(mx);
    return d;
}

int p1788_bar_intervalPart(int r_tag, void *r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return p1788_bar_empty(r_tag, r), EXC_INTERVAL_PART_OF_NAI;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_d_get_fi(mx, x_tag, x, TRV);
    MPFR_SAVE_RANGE_EXP(r_tag);
    mpfi_p1788_subnormalize(mr, mpfi_p1788_intervalPart(mr, mx));
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_setDec(int r_tag, void *r, int x_tag, const void *x, int dec) {
    if (!is_valid_b(x_tag, x) || dec != COM && dec != DAC && dec != DEF && dec != TRV && dec != ILL) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr, mx;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_setDec(mr, mx, dec)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec);
    mpfi_clear(mr);
    mpfi_clear(mx);
    return 0;
}

int p1788_sum(int r_tag, void *r, int n, void *a, int rnd) {
    switch (r_tag) {
        case TAG_f:
            p1788_sum_f((float*) r, n, (float*) a, rnd);
            break;
        case TAG_d:
            p1788_sum_d((double*) r, n, (double*) a, rnd);
            break;
        case TAG_l:
            p1788_sum_l((long double*) r, n, (long double*) a, rnd);
            break;
        default:
            assert(0);
            break;
    }
}

int p1788_sumAbs(int r_tag, void *r, int n, void *a, int rnd) {
    switch (r_tag) {
        case TAG_f:
            p1788_sumAbs_f((float*) r, n, (float*) a, rnd);
            break;
        case TAG_d:
            p1788_sumAbs_d((double*) r, n, (double*) a, rnd);
            break;
        case TAG_l:
            p1788_sumAbs_l((long double*) r, n, (long double*) a, rnd);
            break;
        default:
            assert(0);
            break;
    }
}

int p1788_dot(int r_tag, void *r, int n, void *a, void *b, int rnd) {
    switch (r_tag) {
        case TAG_f:
            p1788_dot_f((float*) r, n, (float*) a, (float*) b, rnd);
            break;
        case TAG_d:
            p1788_dot_d((double*) r, n, (double*) a, (double*) b, rnd);
            break;
        case TAG_l:
            p1788_dot_l((long double*) r, n, (long double*) a, (long double*) b, rnd);
            break;
        default:
            assert(0);
            break;
    }
}

int p1788_sumSquare(int r_tag, void *r, int n, void *a, int rnd) {
    switch (r_tag) {
        case TAG_f:
            p1788_sumSquare_f((float*) r, n, (float*) a, rnd);
            break;
        case TAG_d:
            p1788_sumSquare_d((double*) r, n, (double*) a, rnd);
            break;
        case TAG_l:
            p1788_sumSquare_l((long double*) r, n, (long double*) a, rnd);
            break;
        default:
            assert(0);
            break;
    }
}

int p1788_bar_intervalToText(char **r, int x_tag, const void *x, const char* cs) {
    if (!is_valid_b(x_tag, x) || cs == NULL) return *r = strdup("[]"), EXC_INVALID_OPERAND;
    mpfi_t mx;
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(x_tag);
    *r = mpfi_p1788_intervalToText(mx, ILL, cs);
    MPFR_RESTORE_RANGE_EXP();
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_intervalToText(char **r, int x_tag, const void *x, const char* cs) {
    if (!is_valid_d(x_tag, x) || cs == NULL) return *r = strdup("[nai]"), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return *r = strdup("[nai]"), 0;
    mpfi_t mx;
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(x_tag);
    *r = mpfi_p1788_intervalToText(mx, d, cs);
    MPFR_RESTORE_RANGE_EXP();
    mpfi_clear(mx);
    return 0;
}

int p1788_bar_exactToInterval(int r_tag, void *r, const char* s) {
    if (s == NULL) return p1788_bar_empty(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_exactToInterval(mr, s);
    if (locdec >= 0) (locdec = mpfi_p1788_subnormalize(mr, locdec), 0);
    MPFR_RESTORE_RANGE_EXP();
    p1788_b_set_fi(r_tag, r, mr);
    mpfi_clear(mr);
    return locdec;
}

int p1788_dec_exactToDecoratedInterval(int r_tag, void *r, const char* s) {
    if (s == NULL) return p1788_dec_nai(r_tag, r), EXC_INVALID_OPERAND;
    mpfi_t mr;
    mpfi_init2(mr, p1788_get_prec(r_tag));
    MPFR_SAVE_RANGE_EXP(r_tag);
    int locdec = mpfi_p1788_exactToDecoratedInterval(mr, s);
    if (locdec >= 0) locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    MPFR_RESTORE_RANGE_EXP();
    p1788_d_set_fi(r_tag, r, mr, locdec);
    mpfi_clear(mr);
    return locdec >= 0 ? 0 : locdec;
}

int p1788_bar_intervalToExact(char **r, int x_tag, const void *x) {
    if (!is_valid_b(x_tag, x)) return *r = strdup("[]"), EXC_INVALID_OPERAND;
    mpfi_t mx;
    p1788_b_get_fi(mx, x_tag, x);
    MPFR_SAVE_RANGE_EXP(x_tag);
    *r = mpfi_p1788_intervalToExact(mx, ILL);
    MPFR_RESTORE_RANGE_EXP();
    mpfi_clear(mx);
    return 0;
}

int p1788_dec_intervalToExact(char **r, int x_tag, const void *x) {
    if (!is_valid_d(x_tag, x)) return *r = strdup("[nai]"), EXC_INVALID_OPERAND;
    if (is_nai(x_tag, x)) return *r = strdup("[nai]"), 0;
    mpfi_t mx;
    int d = p1788_d_get_fi(mx, x_tag, x, COM);
    MPFR_SAVE_RANGE_EXP(x_tag);
    *r = mpfi_p1788_intervalToExact(mx, d);
    MPFR_RESTORE_RANGE_EXP();
    mpfi_clear(mx);
    return 0;
}
