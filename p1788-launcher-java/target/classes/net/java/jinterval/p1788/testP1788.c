#include "p1788_oper.h"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

void test_p1788_setup() {
}

int test_p1788_convertType(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_convertType_DD(r, x);
    return EXC_NONE;
}

int test_p1788_pos(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_pos_DD(r, x);
    return EXC_NONE;
}

int test_p1788_neg(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_neg_DD(r, x);
    return EXC_NONE;
}

int test_p1788_add(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_add_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_sub(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sub_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_mul(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_mul_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_div(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_div_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_recip(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_recip_DD(r, x);
    return EXC_NONE;
}

int test_p1788_sqr(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sqr_DD(r, x);
    return EXC_NONE;
}

int test_p1788_sqrt(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sqrt_DD(r, x);
    return EXC_NONE;
}

int test_p1788_fma(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *z, DECORATED_INFSUP_B64 *r) {
    p1788_dec_fma_DDDD(r, x, y, z);
    return EXC_NONE;
}

int test_p1788_pown(DECORATED_INFSUP_B64 *x, int *p, DECORATED_INFSUP_B64 *r) {
    p1788_dec_pown_DDi(r, x, p);
    return EXC_NONE;
}

int test_p1788_pow(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_pow_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_exp(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_exp_DD(r, x);
    return EXC_NONE;
}

int test_p1788_exp2(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_exp2_DD(r, x);
    return EXC_NONE;
}

int test_p1788_exp10(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_exp10_DD(r, x);
    return EXC_NONE;
}

int test_p1788_log(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_log_DD(r, x);
    return EXC_NONE;
}

int test_p1788_log2(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_log2_DD(r, x);
    return EXC_NONE;
}

int test_p1788_log10(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_log10_DD(r, x);
    return EXC_NONE;
}

int test_p1788_sin(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sin_DD(r, x);
    return EXC_NONE;
}

int test_p1788_cos(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_cos_DD(r, x);
    return EXC_NONE;
}

int test_p1788_tan(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_tan_DD(r, x);
    return EXC_NONE;
}

int test_p1788_asin(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_asin_DD(r, x);
    return EXC_NONE;
}

int test_p1788_acos(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_acos_DD(r, x);
    return EXC_NONE;
}

int test_p1788_atan(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_atan_DD(r, x);
    return EXC_NONE;
}

int test_p1788_atan2(DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_atan2_DDD(r, y, x);
    return EXC_NONE;
}

int test_p1788_sinh(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sinh_DD(r, x);
    return EXC_NONE;
}

int test_p1788_cosh(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_cosh_DD(r, x);
    return EXC_NONE;
}

int test_p1788_tanh(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_tanh_DD(r, x);
    return EXC_NONE;
}

int test_p1788_asinh(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_asinh_DD(r, x);
    return EXC_NONE;
}

int test_p1788_acosh(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_acosh_DD(r, x);
    return EXC_NONE;
}

int test_p1788_atanh(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_atanh_DD(r, x);
    return EXC_NONE;
}

int test_p1788_sign(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sign_DD(r, x);
    return EXC_NONE;
}

int test_p1788_ceil(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_ceil_DD(r, x);
    return EXC_NONE;
}

int test_p1788_floor(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_floor_DD(r, x);
    return EXC_NONE;
}

int test_p1788_trunc(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_trunc_DD(r, x);
    return EXC_NONE;
}

int test_p1788_roundTiesToEven(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_roundTiesToEven_DD(r, x);
    return EXC_NONE;
}

int test_p1788_roundTiesToAway(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_roundTiesToAway_DD(r, x);
    return EXC_NONE;
}

int test_p1788_abs(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_abs_DD(r, x);
    return EXC_NONE;
}

int test_p1788_min(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_min_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_max(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_max_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_mulRevToPair(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r1, DECORATED_INFSUP_B64 *r2) {
    p1788_dec_mulRevToPair_DDDD(r1, r2, x, y);
    return EXC_NONE;
}

int test_p1788_sqrRev(DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sqrRev_DDD(r, c, x);
    return EXC_NONE;
}

int test_p1788_absRev(DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_absRev_DDD(r, c, x);
    return EXC_NONE;
}

int test_p1788_pownRev(DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, int *p, DECORATED_INFSUP_B64 *r) {
    p1788_dec_pownRev_DDDi(r, c, x, p);
    return EXC_NONE;
}

int test_p1788_sinRev(DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_sinRev_DDD(r, c, x);
    return EXC_NONE;
}

int test_p1788_cosRev(DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_cosRev_DDD(r, c, x);
    return EXC_NONE;
}

int test_p1788_tanRev(DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_tanRev_DDD(r, c, x);
    return EXC_NONE;
}

int test_p1788_coshRev(DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_coshRev_DDD(r, c, x);
    return EXC_NONE;
}

int test_p1788_mulRev(DECORATED_INFSUP_B64 *b, DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_mulRev_DDDD(r, b, c, x);
    return EXC_NONE;
}

int test_p1788_powRev1(DECORATED_INFSUP_B64 *b, DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_powRev1_DDDD(r, b, c, x);
    return EXC_NONE;
}

int test_p1788_powRev2(DECORATED_INFSUP_B64 *a, DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_powRev2_DDDD(r, a, c, x);
    return EXC_NONE;
}

int test_p1788_atan2Rev1(DECORATED_INFSUP_B64 *b, DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_atan2Rev1_DDDD(r, b, c, x);
    return EXC_NONE;
}

int test_p1788_atan2Rev2(DECORATED_INFSUP_B64 *a, DECORATED_INFSUP_B64 *c, DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_dec_atan2Rev2_DDDD(r, a, c, x);
    return EXC_NONE;
}

int test_p1788_cancelMinus(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_cancelMinus_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_cancelPlus(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_cancelPlus_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_intersection(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_intersection_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_convexHull(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, DECORATED_INFSUP_B64 *r) {
    p1788_dec_convexHull_DDD(r, x, y);
    return EXC_NONE;
}

int test_p1788_equal(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_equal_DD(x, y);
    return EXC_NONE;
}

int test_p1788_subset(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_subset_DD(x, y);
    return EXC_NONE;
}

int test_p1788_less(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_less_DD(x, y);
    return EXC_NONE;
}

int test_p1788_precedes(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_precedes_DD(x, y);
    return EXC_NONE;
}

int test_p1788_interior(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_interior_DD(x, y);
    return EXC_NONE;
}

int test_p1788_strictLess(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_strictLess_DD(x, y);
    return EXC_NONE;
}

int test_p1788_strictPrecedes(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_strictPrecedes_DD(x, y);
    return EXC_NONE;
}

int test_p1788_disjoint(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *y, int *r) {
    *r = p1788_dec_disjoint_DD(x, y);
    return EXC_NONE;
}

int test_p1788_numsToInterval(const double* l, const double* u, DECORATED_INFSUP_B64 *r) {
    int locdec = p1788_dec_numsToInterval_Ddd(r, l, u);
    return locdec < 0 ? locdec : EXC_NONE;
}

int test_p1788_numsDecToInterval(const double* l, const double* u, const int* dec, DECORATED_INFSUP_B64 *r) {
    int locdec = p1788_dec_numsDecToInterval_Dddi(r, l, u, *dec);
    return locdec < 0 ? locdec : EXC_NONE;
}

int test_p1788_textToInterval(const char* s, DECORATED_INFSUP_B64 *r) {
    int locdec = p1788_bar_textToInterval_Dc((BARE_INFSUP_B64*)r, s);
    r->decoration = locdec < 0 ? ILL : locdec;
    return locdec < 0 ? locdec : EXC_NONE;
}

int test_p1788_textToDecoratedInterval(const char* s, DECORATED_INFSUP_B64 *r) {
    int locdec = p1788_dec_textToDecoratedInterval_Dc(r, s);
    return locdec < 0 ? locdec : EXC_NONE;
}

int test_p1788_newDec(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    p1788_newDec_DD(r, (BARE_INFSUP_B64*)x);
    return EXC_NONE;
}

int test_p1788_intervalPart(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    int locdec = p1788_intervalPart_DD((BARE_INFSUP_B64*)r, x);
    r->decoration = locdec < 0 ? ILL : COM;
    return locdec < 0 ? locdec : EXC_NONE;
}

int test_p1788_decorationPart(DECORATED_INFSUP_B64 *x, int *r) {
    *r = p1788_decorationPart_D(x);
    return EXC_NONE;
}

int test_p1788_setDec(DECORATED_INFSUP_B64 *x, int* dec, DECORATED_INFSUP_B64 *r) {
    p1788_setDec_DDi(r, (BARE_INFSUP_B64*)x, *dec);
    return EXC_NONE;
}

int test_p1788_isCommonInterval(DECORATED_INFSUP_B64 *x, int *r) {
    *r = p1788_dec_isCommonInterval_D(x);
    return EXC_NONE;
}

int test_p1788_isSingleton(DECORATED_INFSUP_B64 *x, int *r) {
    *r = p1788_dec_isSingleton_D(x);
    return EXC_NONE;
}

int test_p1788_isMember(double* m, DECORATED_INFSUP_B64 *x, int *r) {
    *r = p1788_dec_isMember_dD(m, x);
    return EXC_NONE;
}

