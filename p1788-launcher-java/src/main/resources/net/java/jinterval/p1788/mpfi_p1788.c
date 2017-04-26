#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <mpfr.h>
#include <mpfi.h>

#include "mpfi_p1788.h"

#include "p1788_textToInterval.inc.c"
#include "mpfr_ext.inc.c"

/* Decorations */
#define ILL 0
#define TRV 4
#define DEF 8
#define DAC 12
#define COM 16

/* Exceptions */
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

/* Overlap States */
#define OVERLAP_bothEmpty 0
#define OVERLAP_firstEmpty 1
#define OVERLAP_secondEmpty 2
#define OVERLAP_before 3
#define OVERLAP_meets 4
#define OVERLAP_overlaps 5
#define OVERLAP_starts 6
#define OVERLAP_containedBy 7
#define OVERLAP_finishes 8
#define OVERLAP_equal 9
#define OVERLAP_finishedBy 10
#define OVERLAP_contains 11
#define OVERLAP_startedBy 12
#define OVERLAP_overlappedBy 13
#define OVERLAP_metBy 14
#define OVERLAP_after 15

// INFSUP_NAN=0 inf-sup representation
// INFSUP_NAN=1 inf-sup-nan representation
#define INFSUP_NAN 1

extern mp_prec_t mpfi_quadrant (mpz_ptr quad, mpfr_srcptr x);

int mpfi_p1788_check_range (mpfi_ptr rop, int t)
{
    if (mpfi_is_empty (rop)) return t;
    int tl = (t & MPFI_FLAGS_LEFT_ENDPOINT_INEXACT) != 0 ? -1 : 0;
    int tr = (t & MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT) != 0 ? 1 : 0;
    tl = mpfr_check_range (&rop->left, tl, MPFR_RNDD);
    tr = mpfr_check_range (&rop->right, tl, MPFR_RNDU);
    int d = t & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    return t | (d == COM && mpfi_inf_p (rop) ? DAC : d);
}

int mpfi_p1788_subnormalize (mpfi_ptr rop, int t)
{
    if (mpfi_is_empty (rop)) return t;
    int tl = (t & MPFI_FLAGS_LEFT_ENDPOINT_INEXACT) != 0 ? -1 : 0;
    int tr = (t & MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT) != 0 ? 1 : 0;
    tl = mpfr_subnormalize (&rop->left, tl, MPFR_RNDD);
    tr = mpfr_subnormalize (&rop->right, tl, MPFR_RNDU);
    int d = t & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    return t | (d == COM && mpfi_inf_p (rop) ? DAC : d);
}

int mpfi_p1788_empty (mpfi_ptr rop)
{
    if (INFSUP_NAN)
    {
        mpfr_set_nan (&rop->left);
        mpfr_set_nan (&rop->right);
    }
    else
    {
        mpfr_set_inf (&rop->left, 1);
        mpfr_set_inf (&rop->right, -1);
    }
    return TRV;
}

int mpfi_p1788_entire (mpfi_ptr rop)
{
    mpfr_set_inf (&rop->left, -1);
    mpfr_set_inf (&rop->right, 1);
    return DAC;
}

int mpfi_p1788_numsToInterval (mpfi_ptr rop, mpfr_srcptr l, mpfr_srcptr u)
{
    int cmp = mpfr_cmp(l, u);
    if (cmp > 0 || cmp == 0 && (!mpfr_number_p (l) || !mpfr_number_p (u)))
    {
        mpfi_p1788_empty (rop);
        return EXC_UNDEFINED_OPERATION;
    }
    return mpfi_p1788_check_range (rop, mpfi_interv_fr (rop, l, u) | COM);
}

int mpfi_p1788_numsDecToInterval (mpfi_ptr rop, mpfr_srcptr l, mpfr_srcptr u, int dec)
{
    int cmp = mpfr_cmp(l, u);
    if (cmp > 0 || cmp == 0 && (!mpfr_number_p (l) || !mpfr_number_p (u))
            || dec == COM && (mpfr_inf_p (l) || mpfr_inf_p (u))
            || dec == ILL)
    {
        mpfi_p1788_empty (rop);
        return EXC_UNDEFINED_OPERATION;
    }
    return mpfi_p1788_check_range (rop, mpfi_interv_fr (rop, l, u) | dec);
}

static int mpfi_p1788_textToIntervalImpl(mpfi_ptr rop, const char *cp, int decorated)
{
    mpq_t infq, supq;
    mpq_init (infq);
    mpq_init (supq);
    int isInfinityInf, isInfinitySup;
    int d = parse_interval(cp, decorated, infq, &isInfinityInf, supq, &isInfinitySup);
    int t = 0;
    if (d >= 0 && isInfinityInf <= isInfinitySup)
    {
        int tl = isInfinityInf
            ? (mpfr_set_inf (&rop->left, -1), 0)
            : mpfr_set_q (&rop->left, infq, MPFR_RNDD);
        int tr = isInfinitySup
            ? (mpfr_set_inf (&rop->right, 1), 0)
            : mpfr_set_q (&rop->right, supq, MPFR_RNDU);
        int t = 0;
        if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
        if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
        if (mpfr_zero_p (&rop->left) && mpfr_signbit (&rop->left))
            mpfr_set_zero (&rop->left, 1);
        if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
            mpfr_set_zero (&rop->right, -1);
    }
    else
    {
        mpfi_p1788_empty (rop);
    }
    mpq_clear (infq);
    mpq_clear (supq);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_textToInterval(mpfi_ptr rop, const char *cp)
{
    return mpfi_p1788_textToIntervalImpl (rop, cp, 0);
}

int mpfi_p1788_textToDecoratedInterval(mpfi_ptr rop, const char *cp)
{
    return mpfi_p1788_textToIntervalImpl (rop, cp, 1);
}

int mpfi_p1788_exactToInterval (mpfi_ptr rop, const char *cp)
{
    return mpfi_p1788_textToInterval (rop, cp);
}

int mpfi_p1788_exactToDecoratedInterval (mpfi_ptr rop, const char *cp)
{
    return mpfi_p1788_textToDecoratedInterval (rop, cp);
}

int mpfi_p1788_convertType (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_set (rop, op) | COM);
}

int mpfi_p1788_newDec (mpfi_ptr rop, mpfi_srcptr op)
{
    return mpfi_p1788_convertType (rop, op);
}

int mpfi_p1788_intervalPart (mpfi_ptr rop, mpfi_srcptr op)
{
    return mpfi_p1788_convertType (rop, op);
}

int mpfi_p1788_setDec (mpfi_ptr rop, mpfi_srcptr op, int dec)
{
    if (dec != COM && dec != DAC && dec != DEF && dec != TRV && dec != ILL)
        return mpfi_p1788_empty (rop), EXC_INVALID_OPERAND;
    if (dec == ILL)
        return mpfi_p1788_empty (rop), ILL;
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    if (dec == COM && mpfi_inf_p (op)) dec = DAC;
    return mpfi_p1788_check_range (rop, mpfi_set (rop, op) | dec);
}

int mpfi_p1788_pos (mpfi_ptr rop, mpfi_srcptr op)
{
    return mpfi_p1788_convertType (rop, op);
}

int mpfi_p1788_neg (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_neg (rop, op) | COM);
}

int mpfi_p1788_add (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_add (rop, op1, op2) | COM);
}

int mpfi_p1788_sub (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_sub (rop, op1, op2) | COM);
}

int mpfi_p1788_mul (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p(op1) || mpfi_inf_p(op2) ? DAC : COM;
    return mpfi_p1788_check_range (rop, mpfi_mul (rop, op1, op2) | d);
}

int mpfi_p1788_div (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2) || mpfi_is_zero (op2))
        return mpfi_p1788_empty (rop);
    int d = mpfi_has_zero (op2) ? TRV : mpfi_inf_p (op1) || mpfi_inf_p (op2) ? DAC : COM;
    if (mpfi_is_zero (op1))
        return mpfi_set_ui (rop, 0) | d;
    return mpfi_p1788_check_range (rop, mpfi_div (rop, op1, op2) | d);
}

int mpfi_p1788_recip (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfi_is_zero (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_has_zero (op) ? TRV : mpfi_inf_p (op) ? DAC : COM;
    return mpfi_p1788_check_range (rop, mpfi_inv (rop, op) | d);
}

int mpfi_p1788_sqrt (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_sgn (&op->right) < 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_sgn (&op->left) < 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    int t;
    if (mpfr_sgn (&op->left) >= 0)
    {
        t = mpfi_sqrt (rop, op);
    }
    else
    {
        mpfr_set_zero (&rop->left, 1);
        t = mpfr_sqrt (&rop->right, &op->right, MPFR_RNDU) ? MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT : 0;
    }
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_fma (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2, mpfi_srcptr op3)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2) || mpfi_is_empty (op3))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op1) || mpfi_inf_p (op2) || mpfi_inf_p (op3) ? DAC : COM;
    mpfi_t prod;
    mpfi_init2 (prod, mpfi_get_prec (op1) + mpfi_get_prec (op2));
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    int t = mpfi_mul (prod, op1, op2);
    assert (t == MPFI_FLAGS_BOTH_ENDPOINTS_EXACT);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    t = mpfi_p1788_check_range ( rop, mpfi_add (rop, prod, op3));
    mpfi_clear (prod);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_sqr (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_sqr (rop, op) | COM);
}

int mpfi_p1788_pown (mpfi_ptr rop, mpfi_srcptr op, long int n)
{
    if (mpfi_is_empty (op) || n < 0 && mpfi_is_zero (op))
        return mpfi_p1788_empty (rop);
    int d = n < 0 && mpfi_has_zero (op) ? TRV : mpfi_inf_p(op) ? DAC : COM;
    if (n == 0)
        return mpfi_p1788_check_range (rop, mpfi_set_ui (rop, 1) | d);

    int tl = 0, tr = 0;
    if (n & 1)
    {
        if (n > 0)
        {
            tl = mpfr_pow_si (&rop->left, &op->left, n, MPFR_RNDD);
            tr = mpfr_pow_si (&rop->right, &op->right, n, MPFR_RNDU);
        }
        else if (mpfr_sgn (&op->left) >= 0 || mpfr_sgn (&op->right) <= 0)
        {
            mpfr_t tmp;
            mpfr_init2 (tmp, mpfr_get_prec (&rop->left));
            tl = mpfr_pow_si (tmp, &op->right, n, MPFR_RNDD);
            tr = mpfr_pow_si (&rop->right, &op->left, n, MPFR_RNDU);
            mpfr_set (&rop->left, tmp, MPFR_RNDD);
            mpfr_clear (tmp);
        }
        else
        {
            return mpfi_p1788_entire (rop), TRV;
        }
    }
    else if (n > 0)
    {
        if (mpfr_sgn (&op->left) >= 0)
        {
            tl = mpfr_pow_si (&rop->left, &op->left, n, MPFR_RNDD);
            tr = mpfr_pow_si (&rop->right, &op->right, n, MPFR_RNDU);
        }
        else if (mpfr_sgn (&op->right) <= 0)
        {
            mpfr_t tmp;
            mpfr_init2 (tmp, mpfr_get_prec (&rop->left));
            tl = mpfr_pow_si (tmp, &op->right, n, MPFR_RNDD);
            tr = mpfr_pow_si (&rop->right, &op->left, n, MPFR_RNDU);
            mpfr_set (&rop->left, tmp, MPFR_RNDD);
            mpfr_clear (tmp);
        }
        else
        {
            tr = mpfr_pow_si (&rop->right, mpfr_cmpabs (&op->left, &op->right) > 0 ? &op->left : &op->right, n, MPFR_RNDU);
            mpfr_set_zero (&rop->left, 1);
        }
    }
    else
    {
        if (mpfr_sgn (&op->left) >= 0)
        {
            mpfr_t tmp;
            mpfr_init2 (tmp, mpfr_get_prec (&rop->left));
            tl = mpfr_pow_si (tmp, &op->right, n, MPFR_RNDD);
            tr = mpfr_pow_si (&rop->right, &op->left, n, MPFR_RNDU);
            mpfr_set (&rop->left, tmp, MPFR_RNDD);
            mpfr_clear (tmp);
        }
        else if (mpfr_sgn (&op->right) <= 0)
        {
            tl = mpfr_pow_si (&rop->left, &op->left, n, MPFR_RNDD);
            tr = mpfr_pow_si (&rop->right, &op->right, n, MPFR_RNDU);
        }
        else
        {
            tl = mpfr_pow_si (&rop->left, mpfr_cmpabs (&op->left, &op->right) > 0 ? &op->left : &op->right, n, MPFR_RNDD);
            mpfr_set_inf (&rop->right, 1);
        }
    }
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    if (mpfr_zero_p (&rop->left) && mpfr_signbit (&rop->left))
        mpfr_set_zero (&rop->left, 1);
    if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
        mpfr_set_zero (&rop->right, -1);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_pow (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
        return mpfi_p1788_empty (rop);
    int d = mpfr_sgn (&op1->left) < 0 || mpfr_sgn (&op1->left) == 0 && mpfr_sgn (&op2->left) <= 0 ? TRV
            : mpfi_inf_p (op1) || mpfi_inf_p (op2) ? DAC : COM;
    if (mpfr_sgn (&op1->right) <= 0)
    {
        if (mpfr_sgn (&op1->right) < 0 || mpfr_sgn (&op2->right) <= 0)
                return  mpfi_p1788_empty (rop);
        return mpfi_set_ui (rop, 0) | d;
    }

    int xlcmp = mpfr_cmp_ui (&op1->left, 1);
    int xrcmp = mpfr_cmp_ui (&op1->right, 1);
    if (xlcmp == 0 && xrcmp == 0 || mpfi_is_zero (op2))
        return mpfi_set_ui (rop, 1) | d;

    mpfr_t tmp;
    mpfr_init2 (tmp, mpfr_get_prec (&rop->left));
    int tl = 0, tr = 0;
    if (mpfr_sgn (&op2->right) <= 0)
    {
        if (xrcmp <= 0) {
            tl = mpfr_pow (tmp, &op1->right, &op2->right, MPFR_RNDD);
            if (mpfr_sgn (&op1->left) > 0)
                tr = mpfr_pow (&rop->right, &op1->left, &op2->left, MPFR_RNDU);
            else
                mpfr_set_inf (&rop->right, 1);
        } else if (xlcmp >= 0) {
            tl = mpfr_pow (tmp, &op1->right, &op2->left, MPFR_RNDD);
            tr = mpfr_pow (&rop->right, &op1->left, &op2->right, MPFR_RNDU);
        } else {
            tl = mpfr_pow (tmp, &op1->right, &op2->left, MPFR_RNDD);
            if (mpfr_sgn (&op1->left) > 0)
                tr = mpfr_pow (&rop->right, &op1->left, &op2->left, MPFR_RNDU);
            else
                mpfr_set_inf (&rop->right, 1);
        }
    } else if (mpfr_sgn (&op2->left) >= 0) {
        if (xrcmp <= 0) {
            if (mpfr_sgn (&op1->left) > 0)
                tl = mpfr_pow (tmp, &op1->left, &op2->right, MPFR_RNDD);
            else
                mpfr_set_zero (tmp, 1);
            tr = mpfr_pow (&rop->right, &op1->right, &op2->left, MPFR_RNDU);
        } else if (xlcmp >= 0) {
            tl = mpfr_pow (tmp, &op1->left, &op2->left, MPFR_RNDD);
            tr = mpfr_pow (&rop->right, &op1->right, &op2->right, MPFR_RNDU);
        } else {
            if (mpfr_sgn (&op1->left) > 0)
                tl = mpfr_pow (tmp, &op1->left, &op2->right, MPFR_RNDD);
            else
                mpfr_set_zero (tmp, 1);
            tr = mpfr_pow (&rop->right, &op1->right, &op2->right, MPFR_RNDU);
        }
    } else if (xrcmp <= 0) {
        if (mpfr_sgn (&op1->left) > 0)
        {
            tl = mpfr_pow (tmp, &op1->left, &op2->right, MPFR_RNDD);
            tr = mpfr_pow (&rop->right, &op1->left, &op2->left, MPFR_RNDU);
        }
        else
        {
            mpfr_set_zero (tmp, 1);
            mpfr_set_inf (&rop->right, 1);
        }
    } else if (xlcmp >= 0) {
        tl = mpfr_pow (tmp, &op1->right, &op2->left, MPFR_RNDD);
        tr = mpfr_pow (&rop->right, &op1->right, &op2->right, MPFR_RNDU);
    } else if (mpfr_sgn (&op1->left) > 0)
    {
        mpfr_t tmp2;
        mpfr_init2 (tmp2, mpfr_get_prec (&rop->left));
        tl = mpfr_pow (tmp, &op1->left, &op2->right, MPFR_RNDD);
        int tl2 = mpfr_pow (tmp2, &op1->right, &op2->left, MPFR_RNDD);
        int cmpl = mpfr_cmp (tmp, tmp2);
        if (cmpl > 0)
        {
            mpfr_set (tmp, tmp2, MPFR_RNDD);
            tl = tl2;
        } else if (cmpl == 0 && tl < tl2)
        {
            assert (tl2 == 0);
            tl = tl2;
        }
        mpfr_clear (tmp2);
        mpfr_init2 (tmp2, mpfr_get_prec (&rop->right));
        tr = mpfr_pow (&rop->right, &op1->left, &op2->left, MPFR_RNDU);
        int tr2 = mpfr_pow (tmp2, &op1->right, &op2->right, MPFR_RNDU);
        int cmpr = mpfr_cmp (&rop->right, tmp2);
        if (cmpr < 0)
        {
            mpfr_set (&rop->right, tmp2, MPFR_RNDU);
            tr = tr2;
        } else if (cmpr == 0 && tr > tr2)
        {
            assert (tr2 == 0);
            tr = tr2;
        }
        mpfr_clear (tmp2);
    } else
    {
        mpfr_set_zero (tmp, 1);
        mpfr_set_inf (&rop->right, 1);
    }
    mpfr_set (&rop->left, tmp, MPFR_RNDD);
    mpfr_clear (tmp);
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    if (mpfr_zero_p (&rop->left) && mpfr_signbit (&rop->left))
        mpfr_set_zero (&rop->left, 1);
    if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
        mpfr_set_zero (&rop->right, -1);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_exp (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op) ? DAC : COM;
    return mpfi_p1788_check_range (rop, mpfi_exp (rop, op) | d);
}

int mpfi_p1788_exp2 (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op) ? DAC : COM;
    return mpfi_p1788_check_range (rop, mpfi_exp2 (rop, op) | d);
}

int mpfi_p1788_exp10 (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op) ? DAC : COM;
    int tl = mpfr_exp10 (&rop->left, &op->left, MPFR_RNDD);
    int tr = mpfr_exp10 (&rop->right, &op->right, MPFR_RNDU);
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    if (mpfr_zero_p (&rop->left) && mpfr_signbit (&rop->left))
        mpfr_set_zero (&rop->left, 1);
    if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
        mpfr_set_zero (&rop->right, -1);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_log (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_sgn (&op->right) <= 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_sgn (&op->left) <= 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    int t;
    if (mpfr_sgn (&op->left) >= 0)
    {
        t = mpfi_log (rop, op);
    }
    else
    {
        mpfr_set_inf (&rop->left, -1);
        t = mpfr_log (&rop->right, &op->right, MPFR_RNDU) ? MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT : 0;
        if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
            mpfr_set_zero (&rop->right, -1);
    }
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_log2 (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_sgn (&op->right) <= 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_sgn (&op->left) <= 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    int t;
    if (mpfr_sgn (&op->left) >= 0)
    {
        t = mpfi_log2 (rop, op);
    }
    else
    {
        mpfr_set_inf (&rop->left, -1);
        t = mpfr_log2 (&rop->right, &op->right, MPFR_RNDU) ? MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT : 0;
        if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
            mpfr_set_zero (&rop->right, -1);
    }
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_log10 (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_sgn (&op->right) <= 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_sgn (&op->left) <= 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    int t;
    if (mpfr_sgn (&op->left) >= 0)
    {
        t = mpfi_log10 (rop, op);
    }
    else
    {
        mpfr_set_inf (&rop->left, -1);
        t = mpfr_log10 (&rop->right, &op->right, MPFR_RNDU) ? MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT : 0;
        if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
            mpfr_set_zero (&rop->right, -1);
    }
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_sin (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op) ? DAC : COM;
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    int t = mpfi_sin (rop, op);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_cos (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op) ? DAC : COM;
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    int t = mpfi_cos (rop, op);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_tan (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    int d;
    if (mpfi_inf_p (op))
    {
        d = TRV;
    }
    else
    {
        mpz_t kl, kr;
        mpz_init (kl);
        mpz_init (kr);
        mpfi_quadrant (kl, &op->left);
        mpz_add_ui (kl, kl, 1);
        mpz_fdiv_q_2exp (kl, kl, 1);
        mpfi_quadrant (kr, &op->right);
        mpz_add_ui (kr, kr, 1);
        mpz_fdiv_q_2exp (kr, kr, 1);
        d = mpz_cmp (kl, kr) == 0 ? COM : TRV;
        mpz_clear (kl);
        mpz_clear (kr);
    }
    int t = mpfi_tan (rop, op);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_asin (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_cmp_si (&op->left, 1) > 0 || mpfr_cmp_si (&op->right, -1) < 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_cmp_si (&op->left, -1) < 0 || mpfr_cmp_si (&op->right, 1) > 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_t opm;
    mpfi_init2 (opm, mpfi_get_prec (rop));
    mpfi_interv_si (opm, -1, 1);
    mpfi_intersect (opm, opm, op);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    int t = mpfi_asin (rop, opm);
    mpfi_clear (opm);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_acos (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_cmp_si (&op->left, 1) > 0 || mpfr_cmp_si (&op->right, -1) < 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_cmp_si (&op->left, -1) < 0 || mpfr_cmp_si (&op->right, 1) > 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_t opm;
    mpfi_init2 (opm, mpfi_get_prec (rop));
    mpfi_interv_si (opm, -1, 1);
    mpfi_intersect (opm, opm, op);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    int t = mpfi_acos (rop, opm);
    mpfi_clear (opm);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_atan (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op) ? DAC : COM;
    return mpfi_p1788_check_range (rop, mpfi_atan (rop, op) | d);
}

int mpfi_p1788_atan2 (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2)
            || mpfr_zero_p (&op1->left) && mpfr_zero_p (&op1->right)
            && mpfr_zero_p (&op2->left) && mpfr_zero_p (&op2->right))
        return mpfi_p1788_empty (rop);
    int d;
    if (mpfi_has_zero (op1) && mpfr_sgn (&op2->left) <= 0)
        d = mpfr_sgn (&op2->right) >= 0 ? TRV : mpfr_sgn (&op1->left) < 0 ? DEF : DAC;
    else
        d = mpfi_inf_p (op1) || mpfi_inf_p (op2) ? DAC : COM;
    int t = 0;
    if (mpfr_sgn (&op2->left) < 0 && mpfr_sgn (&op1->left) < 0 && mpfr_zero_p (&op1->right))
    {
        mpfr_const_pi (&rop->left, MPFR_RNDU);
        mpfr_neg (&rop->left, &rop->left, MPFR_RNDD);
        mpfr_const_pi (&rop->right, MPFR_RNDU);
        t = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    }
    else if (mpfi_is_zero (op1))
    {
        int sgn_op2_left = mpfr_sgn (&op2->left);
        if (mpfr_sgn (&op2->right) > 0)
        {
            mpfr_set_zero (&rop->left, 1);
        }
        else
        {
            mpfr_const_pi (&rop->left, MPFR_RNDD);
            t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
        }
        if (sgn_op2_left < 0)
        {
            mpfr_const_pi (&rop->right, MPFR_RNDU);
            t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
        }
        else
        {
            mpfr_set_zero (&rop->right, -1);
        }
    }
    else if (mpfi_is_zero (op2))
    {
        mpfr_exp_t emin_rop = mpfr_get_emin();
        mpfr_exp_t emax_rop = mpfr_get_emax();
        mpfr_set_emin (mpfr_get_emin_min ());
        mpfr_set_emax (mpfr_get_emax_max ());
        if (mpfr_sgn (&op1->left) < 0)
        {
            mpfr_const_pi (&rop->left, MPFR_RNDU);
            mpfr_neg (&rop->left, &rop->left, MPFR_RNDD);
            mpfr_div_2exp (&rop->left, &rop->left, 1, MPFR_RNDD);
        }
        else
        {
            mpfr_const_pi (&rop->left, MPFR_RNDD);
            mpfr_div_2exp (&rop->left, &rop->left, 1, MPFR_RNDD);
        }
        if (mpfr_sgn (&op1->right) > 0)
        {
            mpfr_const_pi (&rop->right, MPFR_RNDU);
            mpfr_div_2exp (&rop->right, &rop->right, 1, MPFR_RNDU);
        }
        else
        {
            mpfr_const_pi (&rop->right, MPFR_RNDD);
            mpfr_neg (&rop->right, &rop->right, MPFR_RNDU);
            mpfr_div_2exp (&rop->right, &rop->right, 1, MPFR_RNDU);
        }
        t = MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        mpfr_set_emin (emin_rop);
        mpfr_set_emax (emax_rop);
    }
    else
    {
        t = mpfi_atan2 (rop, op1, op2);
    }
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_sinh (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_sinh (rop, op) | COM);
}

int mpfi_p1788_cosh (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_cosh (rop, op) | COM);
}

int mpfi_p1788_tanh (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op) ? DAC : COM;
    return mpfi_p1788_check_range (rop, mpfi_tanh (rop, op) | d);
}

int mpfi_p1788_asinh (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_asinh (rop, op) | COM);
}

int mpfi_p1788_acosh (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_cmp_ui (&op->right, 1) < 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_cmp_ui (&op->left, 1) < 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    int t;
    if (mpfr_cmp_ui (&op->left, 1) >= 0)
    {
        t = mpfi_acosh (rop, op);
    }
    else
    {
        mpfr_set_zero (&rop->left, 1);
        t = mpfr_acosh (&rop->right, &op->right, MPFR_RNDU) ? MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT : 0;
        if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
            mpfr_set_zero (&rop->right, -1);

    }
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_atanh (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op) || mpfr_cmp_si (&op->left, 1) >= 0 || mpfr_cmp_si (&op->right, -1) <= 0)
        return mpfi_p1788_empty (rop);
    int d = mpfr_cmp_si (&op->left, -1) <= 0 || mpfr_cmp_si (&op->right, 1) >= 0 ? TRV : mpfi_inf_p (op) ? DAC : COM;
    int tl = mpfr_cmp_si (&op->left, -1) > 0 ? mpfr_atanh (&rop->left, &op->left, MPFR_RNDD) : (mpfr_set_inf (&rop->left, -1), 0);
    int tr = mpfr_cmp_si (&op->right, 1) < 0 ? mpfr_atanh (&rop->right, &op->right, MPFR_RNDU) : (mpfr_set_inf (&rop->right, 1), 0);
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    if (mpfr_zero_p (&rop->left) && mpfr_signbit (&rop->left))
        mpfr_set_zero (&rop->left, 1);
    if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
        mpfr_set_zero (&rop->right, -1);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_sign (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    int d;
    if (mpfi_has_zero (op))
        d = mpfr_zero_p (&op->left) && mpfr_zero_p (&op->right) ? DAC : DEF;
    else
        d = mpfi_inf_p (op) ? DAC : COM;
    int t = mpfi_interv_si (rop, mpfr_sgn (&op->left), mpfr_sgn (&op->right));
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_ceil (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin();
    mpfr_exp_t emax_rop = mpfr_get_emax();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_t exact;
    mpfi_init2 (exact, mpfi_get_prec (op));
	mpfr_rint(&exact->left, &op->left, MPFR_RNDU);
	mpfr_rint(&exact->right, &op->right, MPFR_RNDU);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    int d = mpfr_cmp (&exact->left, &exact->right) != 0 ? DEF
            : mpfr_integer_p (&op->right) ? DAC : COM;
    int t = mpfi_p1788_convertType (rop, exact) & MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    mpfi_clear (exact);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_floor (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin();
    mpfr_exp_t emax_rop = mpfr_get_emax();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_t exact;
    mpfi_init2 (exact, mpfi_get_prec (op));
	mpfr_rint(&exact->left, &op->left, MPFR_RNDD);
	mpfr_rint(&exact->right, &op->right, MPFR_RNDD);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    int d = mpfr_cmp (&exact->left, &exact->right) != 0 ? DEF
            : mpfr_integer_p (&op->left) ? DAC : COM;
    int t = mpfi_p1788_convertType (rop, exact) & MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    mpfi_clear (exact);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_trunc (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin();
    mpfr_exp_t emax_rop = mpfr_get_emax();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_t exact;
    mpfi_init2 (exact, mpfi_get_prec (op));
	mpfr_rint(&exact->left, &op->left, MPFR_RNDZ);
	mpfr_rint(&exact->right, &op->right, MPFR_RNDZ);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    int d = mpfr_cmp (&exact->left, &exact->right) != 0 ? DEF
            : mpfr_integer_p (&op->left) && !mpfr_zero_p (&op->left)
                || mpfr_integer_p (&op->right) && !mpfr_zero_p (&op->right) ? DAC : COM;
    int t = mpfi_p1788_convertType (rop, exact) & MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    mpfi_clear (exact);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_roundTiesToEven (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin();
    mpfr_exp_t emax_rop = mpfr_get_emax();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_t op_2, exact;
    mpfi_init2 (op_2, mpfi_get_prec (op));
    mpfi_init2 (exact, mpfi_get_prec (op));
    mpfi_mul_2exp (op_2, op, 1);
	mpfr_rint(&exact->left, &op->left, MPFR_RNDN);
	mpfr_rint(&exact->right, &op->right, MPFR_RNDN);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    int d = mpfr_cmp (&exact->left, &exact->right) != 0 ? DEF
            : mpfr_integer_p (&op_2->left) && !mpfr_integer_p (&op->left)
                || mpfr_integer_p (&op_2->right) && !mpfr_integer_p (&op->right) ? DAC : COM;
    mpfi_clear (op_2);
    int t = mpfi_p1788_convertType (rop, exact) & MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    mpfi_clear (exact);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_roundTiesToAway (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin();
    mpfr_exp_t emax_rop = mpfr_get_emax();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_t op_2, exact;
    mpfi_init2 (op_2, mpfi_get_prec (op));
    mpfi_init2 (exact, mpfi_get_prec (op));
    mpfi_mul_2exp (op_2, op, 1);
	mpfr_round(&exact->left, &op->left);
	mpfr_round(&exact->right, &op->right);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    int d = mpfr_cmp (&exact->left, &exact->right) != 0 ? DEF
            : mpfr_integer_p (&op_2->left) && !mpfr_integer_p (&op->left)
                || mpfr_integer_p (&op_2->right) && !mpfr_integer_p (&op->right) ? DAC : COM;
    mpfi_clear (op_2);
    int t = mpfi_p1788_convertType (rop, exact) & MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
    mpfi_clear (exact);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_abs (mpfi_ptr rop, mpfi_srcptr op)
{
    if (mpfi_is_empty (op))
        return mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, mpfi_abs (rop, op) | COM);
}

int mpfi_p1788_min (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op1) || mpfi_inf_p (op2) ? DAC : COM;

	int tl = mpfr_min (&rop->left, &op1->left, &op2->left, MPFR_RNDD);
	int tr = mpfr_min (&rop->right, &op1->right, &op2->right, MPFR_RNDU);
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    if (mpfr_zero_p (&rop->left) && mpfr_signbit (&rop->left))
        mpfr_set_zero (&rop->left, 1);
    if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
        mpfr_set_zero (&rop->right, -1);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_max (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
        return mpfi_p1788_empty (rop);
    int d = mpfi_inf_p (op1) || mpfi_inf_p (op2) ? DAC : COM;

	int tl = mpfr_max (&rop->left, &op1->left, &op2->left, MPFR_RNDD);
	int tr = mpfr_max (&rop->right, &op1->right, &op2->right, MPFR_RNDU);
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    if (mpfr_zero_p (&rop->left) && mpfr_signbit (&rop->left))
        mpfr_set_zero (&rop->left, 1);
    if (mpfr_zero_p (&rop->right) && !mpfr_signbit (&rop->right))
        mpfr_set_zero (&rop->right, -1);
    return mpfi_p1788_check_range (rop, t | d);
}

int mpfi_p1788_mulRevToPair (mpfi_ptr rop1, mpfi_ptr rop2, mpfi_srcptr b, mpfi_srcptr c)
{
    if (mpfi_is_empty (b) || mpfi_is_empty (c))
        return mpfi_p1788_empty (rop2), mpfi_p1788_empty (rop1);
    if (mpfr_sgn (&b->left) >= 0 || mpfr_sgn (&b->right) <= 0 || mpfi_has_zero (c))
    {
        int td = mpfi_has_zero (c) && mpfi_has_zero (b) ? (mpfi_p1788_entire (rop1), TRV) : mpfi_p1788_div (rop1, c, b);
        mpfi_p1788_empty (rop2);
        return td;
    }
    int tl, tr;
    mpfr_set_inf (&rop1->left, -1);
    mpfr_set_inf (&rop2->right, 1);
    if (mpfr_sgn (&c->left) > 0)
    {
		tr = mpfr_div (&rop1->right, &c->left, &b->left, MPFR_RNDU);
		tl = mpfr_div (&rop2->left, &c->left, &b->right, MPFR_RNDD);
    }
    else
    {
        assert (mpfr_sgn (&c->right) < 0);
		tr = mpfr_div (&rop1->right, &c->right, &b->right, MPFR_RNDU);
        tl = mpfr_div (&rop2->left, &c->right, &b->left, MPFR_RNDD);
    }
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    if (mpfr_zero_p (&rop1->right) && !mpfr_signbit (&rop1->right))
        mpfr_set_zero (&rop1->right, -1);
    if (mpfr_zero_p (&rop2->left) && mpfr_signbit (&rop2->left))
        mpfr_set_zero (&rop2->left, 1);
    return t | TRV;
}

int mpfi_p1788_mulRevToPairSubnormal(mpfi_ptr rop1, mpfi_ptr rop2, mpfi_srcptr b, mpfi_srcptr c)
{
    int td = mpfi_p1788_mulRevToPair(rop1, rop2, b, c);
    if (mpfi_p1788_isEmpty(rop2))
    {
        td = mpfi_p1788_subnormalize(rop1, td);
    }
    else
    {
        td = mpfi_p1788_subnormalize(rop1, td & MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT | TRV)
           | mpfi_p1788_subnormalize(rop2, td & MPFI_FLAGS_LEFT_ENDPOINT_INEXACT | TRV);
    }
    return td;
}

/*
 * tl =  0 ==> r->left  is exact min(r)
 * tl = -2 ==> r->left  is exact inf(r), but not min(r)
 * tl = -1 ==> r->left  is lower than inf(r)
 * tr =  0 ==> r->right is exact max(r)
 * tr =  2 ==> r->right is exact sup(r), but not max(r)
 * tr =  1 ==> r->right is upper than sup(r)
 */
static int mpfi_p1788_put_rev (mpfi_ptr rop, mpfi_srcptr x, mpfi_srcptr r, int tl, int tr, int t)
{
    if (mpfi_is_empty (r) || mpfr_cmp (&x->left, &r->right) >= !tr || mpfr_cmp (&r->left, &x->right) >= !tl)
        return t;

    if (tl != -1) tl = 0;
    int cl = mpfr_cmp (&rop->left, &r->left);
    if (cl < 0 || cl == 0 && tl == 0)
    {
        tl = t & MPFI_FLAGS_LEFT_ENDPOINT_INEXACT ? -1 : 0;
    }
    else
    {
        if (mpfr_set (&rop->left, &r->left, MPFR_RNDD)) tl = -1;
    }
    if (mpfr_cmp (&rop->left, &x->left) < 0)
        tl = mpfr_set (&rop->left, &x->left, MPFR_RNDD);

    if (tr != 1) tr = 0;
    int cr = mpfr_cmp (&rop->right, &r->right);
    if (cr > 0 || cr == 0 && tr == 0)
    {
        tr = t & MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT ? 1 : 0;
    }
    else
    {
        if (mpfr_set (&rop->right, &r->right, MPFR_RNDU)) tr = 1;
    }
    if (mpfr_cmp (&rop->right, &x->right) > 0)
        tr = mpfr_set (&rop->right, &x->right, MPFR_RNDU);

    t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    return t;
}

static int mpfi_p1788_rev2 (mpfi_ptr rop, mpfi_srcptr x, mpfi_srcptr r1, int t1l, int t1r, mpfi_srcptr r2, int t2l, int t2r)
{
    mpfr_set_inf (&rop->left, 1);
    mpfr_set_inf (&rop->right, -1);
    int t = 0;
    t = mpfi_p1788_put_rev (rop, x, r1, t1l, t1r, t);
    t = mpfi_p1788_put_rev (rop, x, r2, t2l, t2r, t);
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_pownRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x, long int n)
{
    if (mpfi_is_empty (c) || mpfi_is_empty (x))
        return mpfi_p1788_empty (rop);
    mpfi_t r1, r2;
    mpfi_init2 (r1, mpfi_get_prec (rop));
    mpfi_init2 (r2, mpfi_get_prec (rop));
    int t1l = 0, t1r = 0, t2l = 0, t2r = 0;
    if (n & 1)
    {
        if (n > 0)
        {
            t1l = mpfr_root_si (&r1->left,  &c->left, n, MPFR_RNDD);
            t1r = mpfr_root_si (&r1->right, &c->right, n, MPFR_RNDU);
        }
        else if (mpfi_is_zero (c))
        {
        }
        else if (mpfr_sgn (&c->left) >= 0 || mpfr_sgn (&c->right) <= 0)
        {
            t1l = mpfr_inf_p (&c->right)
                    ? (mpfr_set_zero (&r1->left,   1), -2)
                    : mpfr_root_si (&r1->left,  &c->right, n, MPFR_RNDD);
            t1r = mpfr_inf_p (&c->left)
                    ? (mpfr_set_zero (&r1->right, -1),  2)
                    : mpfr_root_si (&r1->right, &c->left,  n, MPFR_RNDU);
        }
        else
        {
            mpfr_set_inf (&r1->left, -1);
            t1r = mpfr_inf_p (&c->left)
                    ? (mpfr_set_zero (&r1->right, -1),  2)
                    : mpfr_root_si (&r1->right, &c->left,  n, MPFR_RNDU);
            t2l = mpfr_inf_p (&c->right)
                    ? (mpfr_set_zero (&r2->left,   1), -2)
                    : mpfr_root_si (&r2->left,  &c->right, n, MPFR_RNDD);
            mpfr_set_inf (&r2->right, 1);
        }
    }
    else
    {
        if (n > 0)
        {
            if (mpfr_sgn (&c->right) >= 0)
            {
                t1l = mpfr_sgn (&c->left) >= 0
                        ? mpfr_root_si (&r1->left,  &c->left, n, MPFR_RNDD)
                        : (mpfr_set_zero (&r1->left, 1), 0);
                t1r = mpfr_root_si (&r1->right, &c->right, n, MPFR_RNDU);
            }
        }
        else if (n < 0)
        {
            if (mpfr_sgn (&c->right) > 0)
            {
                t1l = mpfr_inf_p (&c->right)
                        ? (mpfr_set_zero (&r1->left, 1), -2)
                        : mpfr_root_si (&r1->left,  &c->right, n, MPFR_RNDD);
                t1r = mpfr_sgn (&c->left) <= 0
                        ? (mpfr_set_inf (&r1->right, 1), 0)
                        : mpfr_root_si (&r1->right, &c->left, n, MPFR_RNDU);
            }
        } else if (mpfr_cmp_ui (&c->left, 1) <= 0 && mpfr_cmp_ui (&c->right, 1) >= 0) {
            mpfr_set_zero (&r1->left, 1);
            mpfr_set_inf (&r1->right, 1);
        }
        mpfr_neg (&r2->left, &r1->right, MPFR_RNDD);
        t2l = -t1r;
        mpfr_neg (&r2->right, &r1->left, MPFR_RNDU);
        t2r = -t1l;
    }
    int td = mpfi_p1788_rev2 (rop, x, r1, t1l, t1r, r2, t2l, t2r);
    mpfi_clear (r1);
    mpfi_clear (r2);
    return td;
}

int mpfi_p1788_pownRevEntire (mpfi_ptr rop, mpfi_srcptr c, long int n)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_pownRev (rop, c, x, n);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_sqrRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x)
{
    return mpfi_p1788_pownRev (rop, c, x, 2);
}

int mpfi_p1788_sqrRevEntire (mpfi_ptr rop, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_sqrRev (rop, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_absRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x)
{
    if (mpfi_is_empty (c) || mpfi_is_empty (x) || mpfr_sgn (&c->right) < 0)
        return mpfi_p1788_empty (rop);
    mpfi_t r1, r2;
    mpfi_init2 (r1, mpfi_get_prec (rop));
    mpfi_init2 (r2, mpfi_get_prec (rop));
    int tl = mpfr_sgn (&c->left) > 0
                    ? mpfr_set (&r1->left,  &c->left, MPFR_RNDD)
                    : (mpfr_set_zero (&r1->left, 1), 0);
    int tr = mpfr_set (&r1->right, &c->right, MPFR_RNDU);
    mpfr_neg (&r2->left, &r1->right, MPFR_RNDD);
    mpfr_neg (&r2->right, &r1->left, MPFR_RNDU);
    int td = mpfi_p1788_rev2 (rop, x, r1, tl, tr, r2, -tr, -tl);
    mpfi_clear (r1);
    mpfi_clear (r2);
    return td;
}

int mpfi_p1788_absRevEntire (mpfi_ptr rop, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_absRev (rop, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_sinRev(mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x)
{
	if (mpfi_is_empty (c) || mpfi_is_empty (x) || mpfr_cmp_si (&c->left, +1) > 0 || mpfr_cmp_si (&c->right, -1) < 0)
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
	mpfi_t cm, rop_acc, r;
    mpfi_init2 (cm, mpfi_get_prec (c));
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_interv_si (cm, -1, 1);
    mpfi_intersect (cm, cm, c);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    mpfr_init2 (&rop_acc->left, mpfr_get_prec (&rop->left));
    mpfr_init2 (&rop_acc->right, mpfr_get_prec (&rop->right));
    mpfr_set_inf (&rop_acc->left, 1);
    mpfr_set_inf (&rop_acc->right, -1);
    mpfi_init2 (r, mpfi_get_prec (rop));
    mpz_t npi;
    mpz_init (npi);

	int tl, tr, t = 0, i;
	if (mpfr_inf_p(&x->left))
	{
		mpfr_set_inf (&rop_acc->left, -1);
	}
	else
	{
		mpfr_quadrant (npi, &x->left);
		mpz_add_ui (npi, npi, 1);
		mpz_fdiv_q_2exp (npi, npi, 1);
		for (i = 0; i < 2; i++)
		{
			if (mpz_tstbit (npi, 0))
			{
				tl = mpfr_asin_npi (&r->left, &cm->right, npi, MPFR_RNDD);
				tr = mpfr_asin_npi (&r->right, &cm->left, npi, MPFR_RNDU);
			}
			else
			{
				tl = mpfr_asin_npi (&r->left, &cm->left, npi, MPFR_RNDD);
				tr = mpfr_asin_npi (&r->right, &cm->right, npi, MPFR_RNDU);
			}
            t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
			mpz_add_ui (npi, npi, 1);
		}
	}
	if (mpfr_inf_p (&x->right))
	{
		mpfr_set_inf (&rop_acc->right, 1);
	}
	else
	{
		mpfr_quadrant (npi, &x->right);
		mpz_add_ui (npi, npi, 1);
		mpz_fdiv_q_2exp (npi, npi, 1);
		for (i = 0; i < 2; i++)
		{
			if (mpz_tstbit (npi, 0))
			{
				tl = mpfr_asin_npi (&r->left, &cm->right, npi, MPFR_RNDD);
				tr = mpfr_asin_npi (&r->right, &cm->left, npi, MPFR_RNDU);
			}
			else
			{
				tl = mpfr_asin_npi (&r->left, &cm->left, npi, MPFR_RNDD);
				tr = mpfr_asin_npi (&r->right, &cm->right, npi, MPFR_RNDU);
			}
            t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
			mpz_sub_ui (npi, npi, 1);
		}
	}
	mpz_clear (npi);
    mpfi_clear (cm);
    mpfi_clear (r);
    mpfi_set (rop, rop_acc);
    mpfi_clear (rop_acc);
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_sinRevEntire(mpfi_ptr rop, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_sinRev (rop, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_cosRev(mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x)
{
	if (mpfi_is_empty (c) || mpfi_is_empty (x) || mpfr_cmp_si (&c->left, +1) > 0 || mpfr_cmp_si (&c->right, -1) < 0)
        return mpfi_p1788_empty (rop);
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
	mpfi_t cm, rop_acc, r;
    mpfi_init2 (cm, mpfi_get_prec (c));
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    mpfi_interv_si (cm, -1, 1);
    mpfi_intersect (cm, cm, c);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    mpfr_init2 (&rop_acc->left, mpfr_get_prec (&rop->left));
    mpfr_init2 (&rop_acc->right, mpfr_get_prec (&rop->right));
    mpfr_set_inf (&rop_acc->left, 1);
    mpfr_set_inf (&rop_acc->right, -1);
    mpfi_init2 (r, mpfi_get_prec (rop));
    mpz_t npi;
    mpz_init (npi);

	int tl, tr, t = 0, i;
	if (mpfr_inf_p(&x->left))
	{
		mpfr_set_inf (&rop_acc->left, -1);
	}
	else
	{
		mpfr_quadrant (npi, &x->left);
		mpz_fdiv_q_2exp (npi, npi, 1);
		for (i = 0; i < 2; i++)
		{
			if (mpz_tstbit (npi, 0))
			{
				tl = mpfr_acos_npi (&r->left, &cm->left, npi, MPFR_RNDD);
				tr = mpfr_acos_npi (&r->right, &cm->right, npi, MPFR_RNDU);
			}
			else
			{
				tl = mpfr_acos_npi (&r->left, &cm->right, npi, MPFR_RNDD);
				tr = mpfr_acos_npi (&r->right, &cm->left, npi, MPFR_RNDU);
			}
            t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
			mpz_add_ui (npi, npi, 1);
		}
	}
	if (mpfr_inf_p (&x->right))
	{
		mpfr_set_inf (&rop_acc->right, 1);
	}
	else
	{
		mpfr_quadrant (npi, &x->right);
		mpz_fdiv_q_2exp (npi, npi, 1);
		for (i = 0; i < 2; i++)
		{
			if (mpz_tstbit (npi, 0))
			{
				tl = mpfr_acos_npi (&r->left, &cm->left, npi, MPFR_RNDD);
				tr = mpfr_acos_npi (&r->right, &cm->right, npi, MPFR_RNDU);
			}
			else
			{
				tl = mpfr_acos_npi (&r->left, &cm->right, npi, MPFR_RNDD);
				tr = mpfr_acos_npi (&r->right, &cm->left, npi, MPFR_RNDU);
			}
            t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
			mpz_sub_ui (npi, npi, 1);
		}
	}
	mpz_clear (npi);
    mpfi_clear (cm);
    mpfi_clear (r);
    mpfi_set (rop, rop_acc);
    mpfi_clear (rop_acc);
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_cosRevEntire(mpfi_ptr rop, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_cosRev (rop, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_tanRev(mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x)
{
	if (mpfi_is_empty (c) || mpfi_is_empty (x))
        return mpfi_p1788_empty (rop);
	mpfi_t rop_acc, r;
    mpfr_init2 (&rop_acc->left, mpfr_get_prec (&rop->left));
    mpfr_init2 (&rop_acc->right, mpfr_get_prec (&rop->right));
    mpfr_set_inf (&rop_acc->left, 1);
    mpfr_set_inf (&rop_acc->right, -1);
    mpfi_init2 (r, mpfi_get_prec (rop));
    mpz_t npi;
    mpz_init (npi);

	int tl, tr, t = 0, i;
	if (mpfr_inf_p(&x->left))
	{
		mpfr_set_inf (&rop_acc->left, -1);
	}
	else
	{
		mpfr_quadrant (npi, &x->left);
		mpz_add_ui (npi, npi, 1);
		mpz_fdiv_q_2exp (npi, npi, 1);
		for (i = 0; i < 2; i++)
		{
    		tl = mpfr_atan_npi (&r->left, &c->left, npi, MPFR_RNDD);
			tr = mpfr_atan_npi (&r->right, &c->right, npi, MPFR_RNDU);
            t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
			mpz_add_ui (npi, npi, 1);
		}
	}
	if (mpfr_inf_p (&x->right))
	{
		mpfr_set_inf (&rop_acc->right, 1);
	}
	else
	{
		mpfr_quadrant (npi, &x->right);
		mpz_add_ui (npi, npi, 1);
		mpz_fdiv_q_2exp (npi, npi, 1);
		for (i = 0; i < 2; i++)
		{
			tl = mpfr_atan_npi (&r->left, &c->left, npi, MPFR_RNDD);
			tr = mpfr_atan_npi (&r->right, &c->right, npi, MPFR_RNDU);
            t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
			mpz_sub_ui (npi, npi, 1);
		}
	}
	mpz_clear (npi);
    mpfi_clear (r);
    mpfi_set (rop, rop_acc);
    mpfi_clear (rop_acc);
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_tanRevEntire(mpfi_ptr rop, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_tanRev (rop, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_coshRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x)
{
    if (mpfi_is_empty (c) || mpfi_is_empty (x) || mpfr_cmp_ui (&c->right, 1) < 0)
        return mpfi_p1788_empty (rop);
    mpfi_t r1, r2;
    mpfi_init2 (r1, mpfi_get_prec (rop));
    mpfi_init2 (r2, mpfi_get_prec (rop));
    int tl = mpfr_cmp_ui (&c->left, 1) > 0
                    ? mpfr_acosh (&r1->left,  &c->left, MPFR_RNDD)
                    : (mpfr_set_zero (&r1->left, 1), 0);
    int tr = mpfr_acosh (&r1->right, &c->right, MPFR_RNDU);
    mpfr_neg (&r2->left, &r1->right, MPFR_RNDD);
    mpfr_neg (&r2->right, &r1->left, MPFR_RNDU);
    int td = mpfi_p1788_rev2 (rop, x, r1, tl, tr, r2, -tr, -tl);
    mpfi_clear (r1);
    mpfi_clear (r2);
    return td;
}

int mpfi_p1788_coshRevEntire (mpfi_ptr rop, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_coshRev (rop, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_mulRev (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c, mpfi_srcptr x)
{
    if (mpfi_is_empty (b) || mpfi_is_empty (c) || mpfi_is_empty (x))
        return mpfi_p1788_empty (rop);

    mpfi_t r1, r2;
    mpfi_init2 (r1, mpfi_get_prec (rop));
    mpfi_init2 (r2, mpfi_get_prec (rop));
    int t1l = 0, t1r = 0, t2l = 0, t2r = 0;
    if (mpfi_has_zero (c))
    {
        if (mpfr_sgn (&b->left) > 0)
        {
            t1l = mpfr_div (&r1->left,  &c->left,  &b->left,  MPFR_RNDD);
            t1r = mpfr_div (&r1->right, &c->right, &b->left,  MPFR_RNDU);
        }
        else if (mpfr_sgn (&b->right) < 0)
        {
            t1l = mpfr_div (&r1->left,  &c->right, &b->right, MPFR_RNDD);
            t1r = mpfr_div (&r1->right, &c->left,  &b->right, MPFR_RNDU);
        }
        else
        {
            mpfi_p1788_entire (r1);
        }
    }
    else
    {
        if (mpfr_sgn (&b->right) > 0)
        {
            if (mpfr_sgn (&c->left) > 0)
            {
                t1l = mpfr_div (&r1->left,  &c->left,  &b->right, MPFR_RNDD);
                if (mpfr_inf_p (&b->right)) t1l = -2;
                t1r = mpfr_sgn (&b->left) <= 0
                        ? (mpfr_set_inf (&r1->right, 1), 0)
                        : mpfr_div (&r1->right, &c->right, &b->left,  MPFR_RNDU);
            }
            else
            {
                assert (mpfr_sgn (&c->right) < 0);
                t1l = mpfr_sgn (&b->left) <= 0
                        ? (mpfr_set_inf (&r1->left, -1), 0)
                        : mpfr_div (&r1->left,  &c->left,  &b->left,  MPFR_RNDD);
                t1r = mpfr_div (&r1->right, &c->right, &b->right, MPFR_RNDU);
                if (mpfr_inf_p (&b->right)) t1r = 2;
            }
        }
        if (mpfr_sgn (&b->left) < 0)
        {
            if (mpfr_sgn (&c->right) < 0)
            {
                t2l = mpfr_div (&r2->left,  &c->right, &b->left,  MPFR_RNDD);
                if (mpfr_inf_p (&b->left)) t2l = -2;
                t2r = mpfr_sgn (&b->right) >= 0
                        ? (mpfr_set_inf (&r2->right, 1), 0)
                        : mpfr_div (&r2->right, &c->left,  &b->right, MPFR_RNDU);
            }
            else
            {
                assert (mpfr_sgn (&c->left) > 0);
                t2l = mpfr_sgn (&b->right) >= 0
                        ? (mpfr_set_inf (&r2->left, -1), 0)
                        : mpfr_div (&r2->left,  &c->right, &b->right, MPFR_RNDD);
                t2r = mpfr_div (&r2->right, &c->left,  &b->left,  MPFR_RNDU);
                if (mpfr_inf_p (&b->left)) t2r = 2;
            }
        }
    }
    int td = mpfi_p1788_rev2 (rop, x, r1, t1l, t1r, r2, t2l, t2r);
    mpfi_clear (r1);
    mpfi_clear (r2);
    return td;
}

int mpfi_p1788_mulRevEntire (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_mulRev (rop, b, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_powRev1 (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c, mpfi_srcptr x)
{
    if (mpfi_is_empty (b) || mpfi_is_empty (c) || mpfi_is_empty (x))
        return mpfi_p1788_empty (rop);

    mpfi_t r1, r2;
    mpfi_init2 (r1, mpfi_get_prec (rop));
    mpfi_init2 (r2, mpfi_get_prec (rop));
    int t1l = 0, t1r = 0, t2l = 0, t2r = 0;
    if (mpfr_sgn (&c->right) <= 0)
    {
        if (mpfr_zero_p (&c->right) && mpfr_sgn (&b->right) > 0)
            mpfi_set_ui (r1, 0);
    }
    else if (mpfr_cmp_ui (&c->left, 1) <= 0 && mpfr_cmp_ui (&c->right, 1) >= 0)
    {
        if (mpfr_sgn (&b->left) > 0)
        {
            t1l = mpfr_sgn (&c->left) <= 0
                    ? (mpfr_set_zero (&r1->left, 1), 0)
                    : mpfr_root_fr (&r1->left,  &c->left,  &b->left,  MPFR_RNDD);
            t1r = mpfr_root_fr (&r1->right, &c->right, &b->left,  MPFR_RNDU);
        }
        else if (mpfr_sgn (&b->right) < 0)
        {
            t1l = mpfr_root_fr (&r1->left,  &c->right, &b->right, MPFR_RNDD);
            t1r = mpfr_sgn (&c->left) <= 0
                    ? (mpfr_set_inf (&r1->right, 1), 0)
                    : mpfr_root_fr (&r1->right, &c->left,  &b->right, MPFR_RNDU);
        }
        else
        {
            mpfr_set_zero (&r1->left, 1);
            t1l = -2;
            mpfr_set_inf (&r1->right, 1);
        }
    }
    else
    {
        if (mpfr_sgn (&b->right) > 0)
        {
            if (mpfr_cmp_ui (&c->left, 1) > 0)
            {
                t1l = mpfr_root_fr (&r1->left,  &c->left,  &b->right, MPFR_RNDD);
                if (mpfr_inf_p (&b->right)) t1l = -2;
                t1r = mpfr_sgn (&b->left) <= 0
                        ? (mpfr_set_inf (&r1->right, 1), 0)
                        : mpfr_root_fr (&r1->right, &c->right, &b->left,  MPFR_RNDU);
            }
            else
            {
                assert (mpfr_cmp_ui (&c->right, 1) < 0);
                t1l = mpfr_sgn (&c->left) <= 0
                        ? (mpfr_set_zero (&r1->left, 1), 0)
                        : mpfr_sgn (&b->left) <= 0
                        ? (mpfr_set_zero (&r1->left, 1), -2)
                        : mpfr_root_fr (&r1->left,  &c->left,  &b->left,  MPFR_RNDD);
                t1r = mpfr_root_fr (&r1->right, &c->right, &b->right, MPFR_RNDU);
                if (mpfr_inf_p (&b->right)) t1r = 2;
            }
        }
        if (mpfr_sgn (&b->left) < 0)
        {
            if (mpfr_cmp_ui (&c->right, 1) < 0)
            {
                t2l = mpfr_root_fr (&r2->left,  &c->right, &b->left,  MPFR_RNDD);
                if (mpfr_inf_p (&b->left)) t2l = -2;
                t2r = mpfr_sgn (&c->left) <= 0 || mpfr_sgn (&b->right) >= 0
                        ? (mpfr_set_inf (&r2->right, 1), 0)
                        : mpfr_root_fr (&r2->right, &c->left,  &b->right, MPFR_RNDU);
            }
            else
            {
                assert (mpfr_cmp_ui (&c->left, 1) > 0);
                t2l = mpfr_inf_p (&c->right) || mpfr_sgn (&b->right) >= 0
                        ? (mpfr_set_zero (&r2->left, 1), -2)
                        : mpfr_root_fr (&r2->left,  &c->right, &b->right, MPFR_RNDD);
                t2r = mpfr_root_fr (&r2->right, &c->left,  &b->left,  MPFR_RNDU);
                if (mpfr_inf_p (&b->left)) t2r = 2;
            }
        }
    }
    int td = mpfi_p1788_rev2 (rop, x, r1, t1l, t1r, r2, t2l, t2r);
    mpfi_clear (r1);
    mpfi_clear (r2);
    return td;
}

int mpfi_p1788_powRev1Entire (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_powRev1 (rop, b, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_powRev2 (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c, mpfi_srcptr x)
{
    if (mpfi_is_empty (a) || mpfi_is_empty (c) || mpfi_is_empty (x))
        return mpfi_p1788_empty (rop);

    mpfi_t r1, r2;
    mpfi_init2 (r1, mpfi_get_prec (rop));
    mpfi_init2 (r2, mpfi_get_prec (rop));
    int t1l = 0, t1r = 0, t2l = 0, t2r = 0;
    if (mpfr_sgn (&c->right) <= 0 || mpfr_sgn (&a->right) <= 0)
    {
        if (mpfi_has_zero (a) && mpfi_has_zero (c))
        {
            mpfr_set_zero (&r1->left, 1);
            t1l = -2;
            mpfr_set_inf (&r1->right, 1);
        }
    }
    else if (mpfr_cmp_ui (&c->left, 1) <= 0 && mpfr_cmp_ui (&c->right, 1) >= 0)
    {
        if (mpfr_cmp_ui (&a->left, 1) > 0)
        {
            t1l = mpfr_sgn (&c->left) <= 0
                    ? (mpfr_set_inf (&r1->left, -1), 0)
                    : mpfr_log_base (&r1->left,  &c->left,  &a->left,  MPFR_RNDD);
            t1r = mpfr_log_base (&r1->right, &c->right, &a->left,  MPFR_RNDU);
        }
        else if (mpfr_cmp_ui (&a->right, 1) < 0)
        {
            t1l = mpfr_log_base (&r1->left,  &c->right, &a->right, MPFR_RNDD);
            t1r = mpfr_sgn (&c->left) <= 0
                    ? (mpfr_set_inf (&r1->right, 1), 0)
                    :mpfr_log_base (&r1->right, &c->left,  &a->right, MPFR_RNDU);
        }
        else
        {
            mpfi_p1788_entire (r1);
        }
    }
    else
    {
        if (mpfr_cmp_ui (&a->right, 1) > 0)
        {
            if (mpfr_cmp_ui (&c->left, 1) > 0)
            {
                t1l = mpfr_log_base (&r1->left,  &c->left,  &a->right, MPFR_RNDD);
                if (mpfr_inf_p (&a->right)) t1l = -2;
                t1r = mpfr_cmp_ui (&a->left, 1) <= 0
                        ? (mpfr_set_inf (&r1->right, 1), 0)
                        : mpfr_log_base (&r1->right, &c->right, &a->left,  MPFR_RNDU);
            }
            else
            {
                assert (mpfr_cmp_ui (&c->right, 1) < 0);
                t1l = mpfr_sgn (&c->left) <= 0 || mpfr_cmp_ui (&a->left, 1) <= 0
                        ? (mpfr_set_inf (&r1->left, -1), 0)
                        : mpfr_log_base (&r1->left,  &c->left,  &a->left,  MPFR_RNDD);
                t1r = mpfr_log_base (&r1->right, &c->right, &a->right, MPFR_RNDU);
                if (mpfr_inf_p (&a->right)) t1r = 2;
            }
        }
        if (mpfr_cmp_ui (&a->left, 1) < 0)
        {
            if (mpfr_cmp_ui (&c->right, 1) < 0)
            {
                t2l = mpfr_sgn (&a->left) <= 0
                        ? (mpfr_set_zero (&r2->left, 1), -2)
                        : mpfr_log_base (&r2->left,  &c->right, &a->left,  MPFR_RNDD);
                t2r = mpfr_sgn (&c->left) <= 0 || mpfr_cmp_ui (&a->right, 1) >= 0
                        ? (mpfr_set_inf (&r2->right, 1), 0)
                        : mpfr_log_base (&r2->right, &c->left,  &a->right, MPFR_RNDU);
            }
            else
            {
                assert (mpfr_cmp_ui (&c->left, 1) > 0);
                t2l = mpfr_cmp_ui (&a->right, 1) >= 0
                        ? (mpfr_set_inf (&r2->left, -1), 0)
                        : mpfr_log_base (&r2->left,  &c->right, &a->right, MPFR_RNDD);
                t2r = mpfr_sgn (&a->left) <= 0
                        ? (mpfr_set_zero (&r2->right, 1), 2)
                        : mpfr_log_base (&r2->right, &c->left,  &a->left,  MPFR_RNDU);
            }
        }
    }
    int td = mpfi_p1788_rev2 (rop, x, r1, t1l, t1r, r2, t2l, t2r);
    mpfi_clear (r1);
    mpfi_clear (r2);
    return td;
}

int mpfi_p1788_powRev2Entire (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_powRev2 (rop, a, c, x);
    mpfi_clear (x);
    return td;
}

static int mpfi_p1788_quadrant_limited (mpfr_srcptr x)
{
    if (mpfr_cmp_si (x, 7) >= 0)
        return 2;
    if (mpfr_cmp_si (x, -7) <= 0)
        return -3;
    mpz_t z;
    mpz_init (z);
    mpfr_quadrant (z, x);
    int k = mpz_get_si (z);
    mpz_clear (z);
    return k;
}

int mpfi_p1788_atan2Rev1 (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c, mpfi_srcptr x)
{
    if (mpfi_is_empty (b) || mpfi_is_empty (c) || mpfi_is_empty (x))
        return mpfi_p1788_empty (rop);

    int kl = mpfi_p1788_quadrant_limited (&c->left);
    int kr = mpfi_p1788_quadrant_limited (&c->right);

	mpfi_t rop_acc, r;
    mpfr_init2 (&rop_acc->left, mpfr_get_prec (&rop->left));
    mpfr_init2 (&rop_acc->right, mpfr_get_prec (&rop->right));
    mpfr_set_inf (&rop_acc->left, 1);
    mpfr_set_inf (&rop_acc->right, -1);
    mpfi_init2 (r, mpfi_get_prec (rop));
    int t = 0;
    int tl, tr;

    if (kl <= -2 && kr >= -2 && mpfr_sgn (&b->left) < 0)
    {
        tl = kr > -2 || mpfr_inf_p (&b->left)
                ? (mpfr_set_inf (&r->left, -1), 0)
                : mpfr_mul_tan (&r->left, &b->left, &c->right, MPFR_RNDD);
        tr = kl < -2 || mpfr_sgn (&b->right) >= 0
                ? (mpfr_set_zero (&r->right, -1), 2)
                : mpfr_mul_tan (&r->right, &b->right, &c->left, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl < -1 && kr >= -1 && mpfi_has_zero (b))
    {
        tl = (mpfr_set_inf (&r->left, -1), 0);
        tr = (mpfr_set_zero (&r->right, -1), 2);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl <= -1 && kr >= -1 && mpfr_sgn (&b->right) > 0)
    {
        tl = kl < -1 || mpfr_inf_p (&b->right)
                ? (mpfr_set_inf (&r->left, -1), 0)
                : mpfr_mul_tan (&r->left, &b->right, &c->left, MPFR_RNDD);
        tr = kr > -1 || mpfr_sgn (&b->left) <= 0
                ? (mpfr_set_zero (&r->right, 1), 2)
                : mpfr_mul_tan (&r->right, &b->left, &c->right, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (mpfi_has_zero (c) && mpfr_sgn (&b->right) > 0)
    {
        assert (kl <= 0 && kr >= 0);
        tl = (mpfr_set_zero (&r->left, 1), 0);
        tr = (mpfr_set_zero (&r->right, -1), 0);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl <= 0 && kr >= 0 && mpfr_sgn (&b->right) > 0 && mpfr_sgn (&c->right) > 0)
    {
        tl = kl < 0 || mpfr_sgn (&b->left) <= 0 || mpfr_sgn (&c->left) == 0
                ? (mpfr_set_zero (&r->left, 1), -2)
                : mpfr_mul_tan (&r->left, &b->left, &c->left, MPFR_RNDD);
        tr = kr > 0 || mpfr_inf_p (&b->right)
                ? (mpfr_set_inf (&r->right, 1), 0)
                : mpfr_mul_tan (&r->right, &b->right, &c->right, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl < 1 && kr >= 1 && mpfi_has_zero (b))
    {
        tl = (mpfr_set_zero (&r->left, 1), -2);
        tr = (mpfr_set_inf (&r->right, 1), 0);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl <= 1 && kr >= 1 && mpfr_sgn (&b->left) < 0)
    {
        tl = kr > 1 || mpfr_sgn (&b->right) >= 0
                ? (mpfr_set_zero (&r->left, 1), -2)
                : mpfr_mul_tan (&r->left, &b->right, &c->right, MPFR_RNDD);
        tr = kl < 1 || mpfr_inf_p (&b->left)
                ? (mpfr_set_inf (&r->right, 1), 0)
                : mpfr_mul_tan (&r->right, &b->left, &c->left, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl < 2 && kr >= 2 && mpfr_sgn (&b->left) < 0)
    {
        tl = (mpfr_set_zero (&r->left, 1), 0);
        tr = (mpfr_set_zero (&r->right, -1), 0);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    mpfi_clear (r);
    mpfi_set (rop, rop_acc);
    mpfi_clear (rop_acc);
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_atan2Rev1Entire (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_atan2Rev1 (rop, b, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_atan2Rev2 (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c, mpfi_srcptr x)
{
    if (mpfi_is_empty (a) || mpfi_is_empty (c) || mpfi_is_empty (x))
        return mpfi_p1788_empty (rop);

    int kl = mpfi_p1788_quadrant_limited (&c->left);
    int kr = mpfi_p1788_quadrant_limited (&c->right);

	mpfi_t rop_acc, r;
    mpfr_init2 (&rop_acc->left, mpfr_get_prec (&rop->left));
    mpfr_init2 (&rop_acc->right, mpfr_get_prec (&rop->right));
    mpfr_set_inf (&rop_acc->left, 1);
    mpfr_set_inf (&rop_acc->right, -1);
    mpfi_init2 (r, mpfi_get_prec (rop));
    int t = 0;
    int tl, tr;

    if (kl <= -2 && kr >= -2 && mpfr_sgn (&a->left) < 0)
    {
        tl = kl < -2 || mpfr_inf_p (&a->left)
                ? (mpfr_set_inf (&r->left, -1), 0)
                : mpfr_mul_cot (&r->left, &a->left, &c->left, MPFR_RNDD);
        tr = kr > -2 || mpfr_sgn (&a->right) >= 0
                ? (mpfr_set_zero (&r->right, -1), 2)
                : mpfr_mul_cot (&r->right, &a->right, &c->right, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl < -1 && kr >= -1 && mpfr_sgn (&a->left) < 0)
    {
        tl = (mpfr_set_zero (&r->left, 1), 0);
        tr = (mpfr_set_zero (&r->right, -1), 0);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl <= -1 && kr >= -1 && mpfr_sgn (&a->left) < 0)
    {
        tl = kl < -1 || mpfr_sgn (&a->right) >= 0
                ? (mpfr_set_zero (&r->left, 1), -2)
                : mpfr_mul_cot (&r->left, &a->right, &c->left, MPFR_RNDD);
        tr = kr > -1 || mpfr_inf_p (&a->left)
                ? (mpfr_set_inf (&r->right, 1), 0)
                : mpfr_mul_cot (&r->right, &a->left, &c->right, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (mpfi_has_zero (c) && mpfi_has_zero (a))
    {
        assert (kl <= 0 && kr >= 0);
        tl = (mpfr_set_zero (&r->left, 0), -2);
        tr = (mpfr_set_inf (&r->right, 1), 0);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl <= 0 && kr >= 0 && mpfr_sgn (&a->right) > 0 && mpfr_sgn (&c->right) > 0)
    {
        tl = kr > 0 || mpfr_sgn (&a->left) <= 0
                ? (mpfr_set_zero (&r->left, 1), -2)
                : mpfr_mul_cot (&r->left, &a->left, &c->right, MPFR_RNDD);
        tr = kl < 0 || mpfr_inf_p (&a->right) || mpfr_sgn (&c->left) == 0
                ? (mpfr_set_inf (&r->right, 1), 0)
                : mpfr_mul_cot (&r->right, &a->right, &c->left, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl < 1 && kr >= 1 && mpfr_sgn (&a->right) > 0)
    {
        tl = (mpfr_set_zero (&r->left, 1), 0);
        tr = (mpfr_set_zero (&r->right, -1), 0);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl <= 1 && kr >= 1 && mpfr_sgn (&a->right) > 0)
    {
        tl = kr > 1 || mpfr_inf_p (&a->right)
                ? (mpfr_set_inf (&r->left, -1), 0)
                : mpfr_mul_cot (&r->left, &a->right, &c->right, MPFR_RNDD);
        tr = kl < 1 || mpfr_sgn (&a->left) <= 0
                ? (mpfr_set_zero (&r->right, 1), 2)
                : mpfr_mul_cot (&r->right, &a->left, &c->left, MPFR_RNDU);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    if (kl < 2 && kr >= 2 && mpfi_has_zero (a))
    {
        tl = (mpfr_set_inf (&r->left, -1), 0);
        tr = (mpfr_set_zero (&r->right, -1), 2);
        t = mpfi_p1788_put_rev (rop_acc, x, r, tl, tr, t);
    }
    mpfi_clear (r);
    mpfi_set (rop, rop_acc);
    mpfi_clear (rop_acc);
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_atan2Rev2Entire (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c)
{
    mpfi_t x;
    mpfi_init2 (x, MPFR_PREC_MIN);
    mpfi_p1788_entire (x);
    int td = mpfi_p1788_atan2Rev2 (rop, a, c, x);
    mpfi_clear (x);
    return td;
}

int mpfi_p1788_cancelMinus (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) && (mpfi_is_empty (op2) || mpfi_bounded_p (op2)))
        return mpfi_p1788_empty (rop);
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2) || !mpfi_bounded_p (op1) || !mpfi_bounded_p (op2))
        return mpfi_p1788_entire (rop), TRV;

	mpq_t dw, q;
	mpq_init (dw);
	mpq_init (q);
	mpfr_get_q (q, &op1->right);
	mpq_set (dw, q);
	mpfr_get_q (q, &op1->left);
	mpq_sub (dw, dw, q);
	mpfr_get_q (q, &op2->right);
	mpq_sub (dw, dw, q);
	mpfr_get_q (q, &op2->left);
	mpq_add (dw, dw, q);
	mpq_clear (q);
    int tl = 0, tr = 0;
	if (mpq_sgn (dw) < 0)
	{
		mpfr_set_inf (&rop->left, -1);
		mpfr_set_inf (&rop->right, +1);
	}
	else
	{
		tl = mpfr_sub (&rop->left, &op1->left, &op2->left, MPFR_RNDD);
		tr = mpfr_sub (&rop->right, &op1->right, &op2->right, MPFR_RNDU);
	}
	mpq_clear (dw);
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_cancelPlus (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
    if (mpfi_is_empty (op1) && (mpfi_is_empty (op2) || mpfi_bounded_p (op2)))
        return mpfi_p1788_empty (rop);
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2) || !mpfi_bounded_p (op1) || !mpfi_bounded_p (op2))
        return mpfi_p1788_entire (rop), TRV;

	mpq_t dw, q;
	mpq_init (dw);
	mpq_init (q);
	mpfr_get_q (q, &op1->right);
	mpq_set (dw, q);
	mpfr_get_q (q, &op1->left);
	mpq_sub (dw, dw, q);
	mpfr_get_q (q, &op2->right);
	mpq_sub (dw, dw, q);
	mpfr_get_q (q, &op2->left);
	mpq_add (dw, dw, q);
	mpq_clear (q);
    int tl = 0, tr = 0;
	if (mpq_sgn (dw) < 0)
	{
		mpfr_set_inf (&rop->left, -1);
		mpfr_set_inf (&rop->right, +1);
	}
	else
	{
		tl = mpfr_add (&rop->left, &op1->left, &op2->right, MPFR_RNDD);
		tr = mpfr_add (&rop->right, &op1->right, &op2->left, MPFR_RNDU);
	}
	mpq_clear (dw);
    int t = 0;
    if (tl) t |= MPFI_FLAGS_LEFT_ENDPOINT_INEXACT;
    if (tr) t |= MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT;
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_intersection (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
        return mpfi_p1788_empty (rop);

    int t = mpfi_intersect (rop, op1, op2);
    if (mpfi_is_empty (rop))
        t = mpfi_p1788_empty (rop);
    return mpfi_p1788_check_range (rop, t | TRV);
}

int mpfi_p1788_convexHull (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2)
{
	if (mpfi_is_empty (op1))
        return mpfi_p1788_convertType (rop, op2);
	if (mpfi_is_empty (op2))
        return mpfi_p1788_convertType (rop, op1);
    return mpfi_p1788_check_range (rop, mpfi_union (rop, op1, op2) | TRV);
}

int mpfi_p1788_inf (mpfr_ptr rop, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_inf (rop, 1), 0;
    int t = mpfr_check_range (rop, mpfr_set (rop, &op->left, MPFR_RNDD), MPFR_RNDD);
	if (mpfr_zero_p (rop) && !mpfr_signbit (rop)) mpfr_set_zero (rop, -1);
	return t;
}

int mpfi_p1788_infSubnormal (mpfr_ptr rop, mpfi_srcptr op) {
    int t = mpfr_subnormalize (rop, mpfi_p1788_inf (rop, op), MPFR_RNDD);
	if (mpfr_zero_p (rop) && !mpfr_signbit (rop)) mpfr_set_zero (rop, -1);
	return t;
}

int mpfi_p1788_sup (mpfr_ptr rop, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_inf (rop, -1), 0;
    int t = mpfr_check_range (rop, mpfr_set (rop, &op->right, MPFR_RNDU), MPFR_RNDU);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_supSubnormal (mpfr_ptr rop, mpfi_srcptr op) {
    int t = mpfr_subnormalize (rop, mpfi_p1788_sup (rop, op), MPFR_RNDU);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_mid (mpfr_ptr rop, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_nan (rop), 0;
    if (mpfi_inf_p (op))
    {
        if (!mpfr_inf_p (&op->left))
        {
            mpfr_set_inf (rop, 1);
            mpfr_nextbelow (rop);
            return -1;
        }
        if (!mpfr_inf_p (&op->right))
        {
            mpfr_set_inf (rop, -1);
            mpfr_nextabove (rop);
            return 1;
        }
        mpfr_set_zero (rop, 1);
        return 0;
    }
    mpfr_exp_t emin_rop = mpfr_get_emin ();
    mpfr_exp_t emax_rop = mpfr_get_emax ();
    mpfr_set_emin (mpfr_get_emin_min ());
    mpfr_set_emax (mpfr_get_emax_max ());
    int t = mpfi_mid (rop, op);
    mpfr_set_emin (emin_rop);
    mpfr_set_emax (emax_rop);
    t = mpfr_check_range (rop, t, MPFR_RNDN);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_midSubnormal (mpfr_ptr rop, mpfi_srcptr op) {
    int t = mpfr_subnormalize (rop, mpfi_p1788_mid (rop, op), MPFR_RNDN);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_midRad (mpfr_ptr mid, mpfr_ptr rad, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_nan (mid), mpfr_set_nan (rad), 0;
    int tmid = mpfi_p1788_mid (mid, op);
    mpfr_t r1, r2;
    mpfr_init2 (r1, mpfr_get_prec (rad));
    mpfr_init2 (r2, mpfr_get_prec (rad));
    int t1 = mpfr_sub (r1, &op->right, mid, MPFR_RNDU);
    int t2 = mpfr_sub (r2, mid, &op->left, MPFR_RNDU);
    int trad;
    int cmp = mpfr_cmp (r1, r2);
    if (cmp < 0)
    {
        mpfr_set (rad, r2, MPFR_RNDU);
        trad = t2;
    }
    else if (cmp > 0)
    {
        mpfr_set (rad, r1, MPFR_RNDU);
        trad = t1;
    }
    else
    {
        mpfr_set (rad, r1, MPFR_RNDU);
        trad = t1 == 1 && t2 == 1 ? 1 : 0;
    }
    mpfr_clear (r1);
    mpfr_clear (r2);
    trad = mpfr_check_range (rad, trad, MPFR_RNDU);
	if (mpfr_zero_p (rad) && mpfr_signbit (rad)) mpfr_set_zero (rad, 1);
    // Return is similar to return of mpfr_sin_cos
    if (tmid < 0) tmid = 2;
    if (trad < 0) trad = 2;
    return tmid + (trad << 2);
}

int mpfi_p1788_midRadSubnormal (mpfr_ptr mid, mpfr_ptr rad, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_nan (mid), mpfr_set_nan (rad), 0;
    int tmid = mpfi_p1788_midSubnormal (mid, op);
    mpfr_t r1, r2;
    mpfr_init2 (r1, mpfr_get_prec (rad));
    mpfr_init2 (r2, mpfr_get_prec (rad));
    int t1 = mpfr_sub (r1, &op->right, mid, MPFR_RNDU);
    int t2 = mpfr_sub (r2, mid, &op->left, MPFR_RNDU);
    int trad;
    int cmp = mpfr_cmp (r1, r2);
    if (cmp < 0)
    {
        mpfr_set (rad, r2, MPFR_RNDU);
        trad = t2;
    }
    else if (cmp > 0)
    {
        mpfr_set (rad, r1, MPFR_RNDU);
        trad = t1;
    }
    else
    {
        mpfr_set (rad, r1, MPFR_RNDU);
        trad = t1 == 1 && t2 == 1 ? 1 : 0;
    }
    mpfr_clear (r1);
    mpfr_clear (r2);
    trad = mpfr_subnormalize (rad, mpfr_check_range (rad, trad, MPFR_RNDU), MPFR_RNDU);
	if (mpfr_zero_p (rad) && mpfr_signbit (rad)) mpfr_set_zero (rad, 1);
    // Return is similar to return of mpfr_sin_cos
    if (tmid < 0) tmid = 2;
    if (trad < 0) trad = 2;
    return tmid + (trad << 2);
}

int mpfi_p1788_rad (mpfr_ptr rop, mpfi_srcptr op) {
    mpfr_t mid;
    mpfr_init2 (mid, mpfr_get_prec (rop));
    int t = mpfi_p1788_midRad (mid, rop, op) >> 2;
    mpfr_clear (mid);
    if (t > 1) t = -1;
    return t;
}

int mpfi_p1788_radSubnormal (mpfr_ptr rop, mpfi_srcptr op) {
    mpfr_t mid;
    mpfr_init2 (mid, mpfr_get_prec (rop));
    int t = mpfi_p1788_midRadSubnormal (mid, rop, op) >> 2;
    mpfr_clear (mid);
    if (t > 1) t = -1;
    return t;
}

int mpfi_p1788_wid (mpfr_ptr rop, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_nan (rop), 0;
    int t = mpfr_check_range (rop, mpfi_diam_abs (rop, op), MPFR_RNDU);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_widSubnormal (mpfr_ptr rop, mpfi_srcptr op) {
    int t = mpfr_subnormalize (rop, mpfi_p1788_wid (rop, op), MPFR_RNDU);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_mag (mpfr_ptr rop, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_nan (rop), 0;
    int t = mpfr_check_range (rop, mpfi_mag (rop, op), MPFR_RNDU);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_magSubnormal (mpfr_ptr rop, mpfi_srcptr op) {
    int t = mpfr_subnormalize (rop, mpfi_p1788_mag (rop, op), MPFR_RNDU);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_mig (mpfr_ptr rop, mpfi_srcptr op) {
	if (mpfi_is_empty (op))
        return mpfr_set_nan (rop), 0;
    int t = mpfr_check_range (rop, mpfi_mig (rop, op), MPFR_RNDD);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_migSubnormal (mpfr_ptr rop, mpfi_srcptr op) {
    int t = mpfr_subnormalize (rop, mpfi_p1788_mig (rop, op), MPFR_RNDU);
	if (mpfr_zero_p (rop) && mpfr_signbit (rop)) mpfr_set_zero (rop, 1);
	return t;
}

int mpfi_p1788_isValid(mpfi_srcptr op) {
    if (mpfr_zero_p (&op->left) && mpfr_signbit (&op->left)
            || mpfr_zero_p (&op->right) && !mpfr_signbit (&op->right))
        return 0;
    int cmp = mpfr_cmp (&op->left, &op->right);
	return cmp < 0
            || cmp == 0 && mpfr_number_p (&op->left) && mpfr_number_p (&op->right)
            || INFSUP_NAN && mpfr_nan_p (&op->left) && mpfr_nan_p (&op->right)
            || !INFSUP_NAN && cmp > 0 && mpfr_inf_p (&op->left) && mpfr_inf_p (&op->right);
}

int mpfi_p1788_isEmpty (mpfi_srcptr op)
{
    return mpfi_is_empty (op);
}

int mpfi_p1788_isEntire (mpfi_srcptr op)
{
	if (mpfi_is_empty (op)) return 0;
	return mpfr_inf_p (&op->left) && mpfr_inf_p (&op->right);
}

int mpfi_p1788_isNaI (mpfi_srcptr op)
{
	return 0;
}

int mpfi_p1788_isCommonInterval (mpfi_srcptr op)
{
	if (mpfi_is_empty (op)) return 0;
	return mpfr_number_p (&op->left) && mpfr_number_p (&op->right);
}

int mpfi_p1788_isSingleton (mpfi_srcptr op)
{
	if (mpfi_is_empty (op)) return 0;
	return mpfr_cmp (&op->left, &op->right) == 0;
}

int mpfi_p1788_isMember(mpfr_srcptr m, mpfi_srcptr x)  {
	if (mpfi_is_empty (x) || mpfr_nan_p (m)) return 0;
	return mpfr_cmp (&x->left, m) <= 0 && mpfr_cmp (m, &x->right) <= 0 && mpfr_number_p (m);
}

int mpfi_p1788_equal (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            if (!mpfi_is_empty (op1)) return 0;
            if (!mpfi_is_empty (op2)) return 0;
            return 1;
	}
	return mpfr_cmp (&op1->left, &op2->left) == 0 && mpfr_cmp (&op1->right, &op2->right) == 0;
}

int mpfi_p1788_subset (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            if (!mpfi_is_empty (op1)) return 0;
            return 1;
	}
	return mpfr_cmp (&op1->left, &op2->left) >= 0 && mpfr_cmp (&op1->right, &op2->right) <= 0;
}

int mpfi_p1788_less (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            if (!mpfi_is_empty (op1)) return 0;
            if (!mpfi_is_empty (op2)) return 0;
            return 1;
	}
	return mpfr_cmp (&op1->left, &op2->left) <= 0 && mpfr_cmp (&op1->right, &op2->right) <= 0;
}

int mpfi_p1788_precedes (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            return 1;
	}
	return mpfr_cmp (&op1->right, &op2->left) <= 0;
}

static int lessInf(mpfr_srcptr a, mpfr_srcptr b) {
	int cmp = mpfr_cmp (a, b);
	return cmp < 0 || cmp == 0 && mpfr_inf_p (a);
}

int mpfi_p1788_interior (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            if (!mpfi_is_empty (op1)) return 0;
            return 1;
	}
	return lessInf (&op2->left, &op1->left) && lessInf (&op1->right, &op2->right);
}

int mpfi_p1788_strictLess (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            if (!mpfi_is_empty (op1)) return 0;
            if (!mpfi_is_empty (op2)) return 0;
            return 1;
	}
	return lessInf (&op1->left, &op2->left) && lessInf (&op1->right, &op2->right);
}

int mpfi_p1788_strictPrecedes (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            return 1;
	}
	return mpfr_cmp (&op1->right, &op2->left) < 0;
}

int mpfi_p1788_disjoint (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            return 1;
	}
	return mpfr_cmp (&op1->right, &op2->left) < 0 || mpfr_cmp (&op1->left, &op2->right) > 0;
}

int mpfi_p1788_overlap (mpfi_srcptr op1, mpfi_srcptr op2) {
	if (mpfi_is_empty (op1) || mpfi_is_empty (op2))
	{
            if (!mpfi_is_empty (op1)) return 1 << OVERLAP_secondEmpty;
            if (!mpfi_is_empty (op2)) return 1 << OVERLAP_firstEmpty;
            return 1 << OVERLAP_bothEmpty;
	}
	if (mpfr_cmp (&op1->right, &op2->left) < 0) {
		return 1 << OVERLAP_before;
	}
	if (mpfr_cmp (&op1->left, &op1->right) < 0 && mpfr_cmp (&op1->right, &op2->left) == 0 && mpfr_cmp (&op2->left, &op2->right) < 0) {
		return 1 << OVERLAP_meets;
	}
	if (mpfr_cmp (&op1->left, &op2->left) < 0 && mpfr_cmp (&op2->left, &op1->right) < 0 && mpfr_cmp (&op1->right, &op2->right) < 0) {
		return 1 << OVERLAP_overlaps;
	}
	if (mpfr_cmp (&op1->left, &op2->left) == 0 && mpfr_cmp (&op1->right, &op2->right) < 0) {
		return 1 << OVERLAP_starts;
	}
	if (mpfr_cmp (&op2->left, &op1->left) < 0 && mpfr_cmp (&op1->right, &op2->right) < 0) {
		return 1 << OVERLAP_containedBy;
	}
	if (mpfr_cmp (&op2->left, &op1->left) < 0 && mpfr_cmp (&op1->right, &op2->right) == 0) {
		return 1 << OVERLAP_finishes;
	}
	if (mpfr_cmp (&op1->left, &op2->left) == 0 && mpfr_cmp (&op1->right, &op2->right) == 0) {
		return 1 << OVERLAP_equal;
	}
	if (mpfr_cmp (&op1->left, &op2->left) < 0 && mpfr_cmp (&op2->right, &op1->right) == 0) {
		return 1 << OVERLAP_finishedBy;
	}
	if (mpfr_cmp (&op1->left, &op2->left) < 0 && mpfr_cmp (&op2->right, &op1->right) < 0) {
		return 1 << OVERLAP_contains;
	}
	if (mpfr_cmp (&op2->left, &op1->left) == 0 && mpfr_cmp (&op2->right, &op1->right) < 0) {
		return 1 << OVERLAP_startedBy;
	}
	if (mpfr_cmp (&op2->left, &op1->left) < 0 && mpfr_cmp (&op1->left, &op2->right) < 0 && mpfr_cmp (&op2->right, &op1->right) < 0) {
		return 1 << OVERLAP_overlappedBy;
	}
	if (mpfr_cmp (&op2->left, &op2->right) < 0 && mpfr_cmp (&op2->right, &op1->left) == 0 && mpfr_cmp (&op1->left, &op1->right) < 0) {
		return 1 << OVERLAP_metBy;
	}
	if (mpfr_cmp (&op2->right, &op1->right) < 0) {
		return 1 << OVERLAP_after;
	}
	assert(0);
	return 0;
}

static char *numberToText (char *cp, mpfr_srcptr x, int subnormal)
{
	if (mpfr_sgn (x) == 0)
	{
		*cp++ = '0';
		return cp;
	}
	if (mpfr_sgn (x) < 0)
		*cp++ = '-';
	if (mpfr_inf_p (x))
	{
		*cp++ = 'i';
		*cp++ = 'n';
		*cp++ = 'f';
		return cp;
	}
	*cp++ = '0';
	*cp++ = 'x';
	mpz_t m, tmp;
	mpz_init (m);
	mpz_init (tmp);
	mpfr_exp_t e = mpfr_get_z_2exp (m, x);
	mpz_abs (m, m);
	mpfr_prec_t prec = mpfr_get_prec (x);
	mpfr_prec_t p;
	if (!subnormal || e >= mpfr_get_emin () + prec - 1)
	{
		*cp++ = '1';
		*cp++ = '.';
		p = prec - 1;
		e += prec - 1;
	}
	else
	{
		*cp++ = '0';
		*cp++ = '.';
		p = prec;
		e += prec;
	}
	while (p >= 4)
	{
		mpz_fdiv_q_2exp (tmp, m, p - 4);
		int d = mpz_fdiv_ui (tmp, 16);
		*cp++ = d < 10 ? '0' + d : 'a' + (d - 10);
		p -= 4;
	}
	if (p > 0)
	{
		int d = mpz_fdiv_ui (m, 1 << p);
		d <<= 4 - p;
		*cp++ = d < 10 ? '0' + d : 'a' + (d - 10);
	}
	mpz_clear (m);
	mpz_clear (tmp);
	*cp++ = 'p';
	return cp + sprintf (cp, "%lld", (long long int) e);
}

char *mpfi_p1788_intervalToText (mpfi_srcptr x, int dec, const char *cs)
{
    int subnormal = 1;
	if (mpfi_is_empty (x)) return strdup(dec ? "[]_trv" : "[]");
    mpfr_prec_t prec = mpfi_get_prec (x);
	char *buf = malloc (prec + 50);
	char *cp = buf;
	*cp++ = '[';
	cp = numberToText (cp, &x->left, subnormal);
	*cp++ = ',';
	cp = numberToText (cp, &x->right, subnormal);
	*cp++ = ']';
	if (dec >= TRV)
	{
		*cp++ = '_';
		switch (dec)
		{
			case COM:
				strcpy (cp, "com");
				break;
			case DAC:
				strcpy (cp, "dac");
				break;
			case DEF:
				strcpy (cp, "def");
				break;
			case TRV:
				strcpy (cp, "trv");
				break;
			default:
				*cp++ = '\0';
				assert (0);
		}
	}
	else
	{
		*cp++ = '\0';
	}
    cp = strdup (buf);
    free (buf);
    return cp;
}

char *mpfi_p1788_intervalToExact (mpfi_srcptr x, int dec)
{
    return mpfi_p1788_intervalToText (x, dec, NULL);
}
