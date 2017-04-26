#include "mpfi_p1788.h"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

typedef struct {
    double inf;
    double sup;
    char decoration;
} I;

static void arg(mpfi_t mx, I* x) {
    mpfi_init(mx);
    mpfi_interv_d(mx, x->inf, x->sup);
}

static void hull(I* r, mpfi_t mr, int t) {
    r->inf = mpfr_get_d(&mr->left, MPFR_RNDD);
    r->sup = mpfr_get_d(&mr->right, MPFR_RNDU);
    r->decoration = t;
}

void test_mpfi_p1788_setup() {
    mpfr_set_default_prec(53);
    mpfr_set_emin(-1073);
    mpfr_set_emax(1024);
}

int test_mpfi_p1788_pos(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_pos(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_neg(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_neg(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_add(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_add(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_sub(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_sub(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_mul(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_mul(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_div(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_div(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_recip(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_recip(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_sqrt(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_sqrt(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_fma(I* x, I*y, I*z, I* r) {
    mpfi_t mx, my, mz, mr;

    arg(mx, x);
    arg(my, y);
    arg(mz, z);
    mpfi_init(mr);
    int t = mpfi_p1788_fma(mr, mx, my, mz);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mz);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_sqr(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_sqr(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_pown(I* x, int *p, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_pown(mr, mx, *p);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_pow(I* x, I *y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_pow(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_exp(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_exp(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_exp2(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_exp2(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_exp10(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_exp10(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_log(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_log(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_log2(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_log2(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_log10(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_log10(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_sin(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_sin(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_cos(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_cos(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_tan(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_tan(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_asin(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_asin(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_acos(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_acos(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_atan(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_atan(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_atan2(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_atan2(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_sinh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_sinh(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_cosh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_cosh(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_tanh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_tanh(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_asinh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_asinh(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_acosh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_acosh(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_atanh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_atanh(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_sign(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_sign(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_ceil(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_ceil(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_floor(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_floor(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_trunc(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_trunc(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_roundTiesToEven(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_roundTiesToEven(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_roundTiesToAway(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_roundTiesToAway(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_abs(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    int t = mpfi_p1788_abs(mr, mx);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_min(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_min(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_max(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    int t = mpfi_p1788_max(mr, mx, my);
    hull(r, mr, t);
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr);
    return EXC_NONE;
}

int test_mpfi_p1788_mulRevToPair(I* x, I* y, I* r1, I* r2) {
    mpfi_t mx, my, mr1, mr2;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr1);
    mpfi_init(mr2);
    int t = mpfi_p1788_mulRevToPair (mr1, mr2, mx, my);
    if (mpfi_is_empty (mr2))
    {
        hull (r1, mr1, t);
        hull (r2, mr2, TRV);
    }
    else
    {
        hull (r1, mr1, t & !MPFI_FLAGS_LEFT_ENDPOINT_INEXACT);
        hull (r2, mr2, t & !MPFI_FLAGS_RIGHT_ENDPOINT_INEXACT);
    }
    mpfi_clear(mx);
    mpfi_clear(my);
    mpfi_clear(mr1);
    mpfi_clear(mr2);
    return EXC_NONE;
}

#if 0
int test_mpfi_intersection(I* x, I *y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_intersect(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

void test_mpfi_convexHull(I* x, I *y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_union(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}
#endif

