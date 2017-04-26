#include "mpfi.h"
#include "mpfr.h"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

typedef double I;

static void arg(mpfi_t mx, I* x) {
    mpfi_init(mx);
    mpfi_interv_d(mx, x[0], x[1]);
}

static void hull(I* r, mpfi_t mr) {
    mpfr_t mri;
    mpfr_t mrs;

    mpfr_init(mri);
    mpfr_init(mrs);

    mpfi_get_left(mri, mr);
    mpfi_get_right(mrs, mr);
    r[0] = mpfr_get_d(mri, MPFR_RNDD);
    r[1] = mpfr_get_d(mrs, MPFR_RNDU);
}

void test_mpfi_setup() {
    mpfr_set_default_prec(53);
}

int test_mpfi_neg(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_neg(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_negateRev(I* c, I* x, I* r) {
    mpfi_t mc, mx, mr;

    arg(mc, c);
    arg(mx, x);
    mpfi_init(mr);
    mpfi_neg(mc, mc);
    mpfi_intersect(mr, mc, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_add(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_add(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_sub(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_sub(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_mul(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_mul(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_div(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_div(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_recip(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_inv(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_sqrt(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_sqrt(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_hypot(I* x, I*y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_hypot(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_fma(I* x, I*y, I*z, I* r) {
    mpfi_t mx, my, mz, mxy, mr;

    arg(mx, x);
    arg(my, y);
    arg(mz, z);
    mpfi_init2(mxy, 2*53);
    mpfi_mul(mxy, mx, my);
    mpfi_init(mr);
    mpfi_add(mr, mxy, mz);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_sqr(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_sqr(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

//int test_mpfi_pown(I* x, int *p, I* r) {
//    return EXC_NONE;
//}

//int test_mpfi_pow(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_mpfi_exp(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_exp(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_exp2(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_exp2(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

//int test_mpfi_exp10(I* x, I* r) {
//    return EXC_NONE;
//}

int test_mpfi_log(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_log(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_log2(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_log2(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_log10(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_log10(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_sin(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_sin(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_cos(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_cos(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_tan(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_tan(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_asin(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_asin(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_acos(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_acos(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_atan(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_atan(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_atan2(I* x, I* y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_atan2(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_sinh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_sinh(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_cosh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_cosh(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_tanh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_tanh(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_asinh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_asinh(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_acosh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_acosh(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_atanh(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_atanh(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

//int test_mpfi_sign(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_mpfi_ceil(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_mpfi_floor(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_mpfi_round(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_mpfi_trunc(I* x, I* r) {
//    return EXC_NONE;
//}

int test_mpfi_abs(I* x, I* r) {
    mpfi_t mx, mr;

    arg(mx, x);
    mpfi_init(mr);
    mpfi_abs(mr, mx);
    hull(r, mr);
    return EXC_NONE;
}

//int test_mpfi_min(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

//int test_mpfi_max(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_mpfi_intersection(I* x, I *y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_intersect(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}

int test_mpfi_convexHull(I* x, I *y, I* r) {
    mpfi_t mx, my, mr;

    arg(mx, x);
    arg(my, y);
    mpfi_init(mr);
    mpfi_union(mr, mx, my);
    hull(r, mr);
    return EXC_NONE;
}
