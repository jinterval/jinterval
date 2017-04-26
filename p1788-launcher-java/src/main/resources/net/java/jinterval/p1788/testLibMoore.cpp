#include "moore/config/minimal.h"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

typedef Moore::TInterval<> I;

extern "C" {

void test_moore_setup() {
}


int test_moore_neg(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = neg(*x);
    return EXC_NONE;
}

int test_moore_add(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = add(*x, *y);
    return EXC_NONE;
}

int test_moore_sub(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = sub(*x, *y);
    return EXC_NONE;
}

int test_moore_mul(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = mul(*x, *y);
    return EXC_NONE;
}

int test_moore_div(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = div(*x, *y);
    return EXC_NONE;
}

int test_moore_recip(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = recip(*x);
    return EXC_NONE;
}

int test_moore_sqr(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = sqr(*x);
    return EXC_NONE;
}

int test_moore_sqrt(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = sqrt(*x);
    return EXC_NONE;
}

int test_moore_fma(I *x, I *y, I *z, I *r) {
    Moore::UpRounding rnd;
    *r = fma(*x, *y, *z);
    return EXC_NONE;
}

int test_moore_pown(I *x, int *p, I *r) {
    Moore::UpRounding rnd;
    *r = *p == 0 && !is_empty(*x)? I(1.0, 1.0) : pown(*x, *p);
    return EXC_NONE;
}

int test_moore_pow(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = pow(*x, *y);
    return EXC_NONE;
}

int test_moore_exp(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = exp(*x);
    return EXC_NONE;
}

int test_moore_exp2(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = exp2(*x);
    return EXC_NONE;
}

int test_moore_exp10(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = exp10(*x);
    return EXC_NONE;
}

int test_moore_log(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = log(*x);
    return EXC_NONE;
}

int test_moore_log2(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = log2(*x);
    return EXC_NONE;
}

int test_moore_log10(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = log10(*x);
    return EXC_NONE;
}

int test_moore_sin(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = sin(*x);
    return EXC_NONE;
}

int test_moore_cos(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = cos(*x);
    return EXC_NONE;
}

int test_moore_tan(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = tan(*x);
    return EXC_NONE;
}

int test_moore_asin(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = asin(*x);
    return EXC_NONE;
}

int test_moore_acos(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = acos(*x);
    return EXC_NONE;
}

int test_moore_atan(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = atan(*x);
    return EXC_NONE;
}

int test_moore_atan2(I *y, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = atan2(*y, *x);
    return EXC_NONE;
}

int test_moore_sinh(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = sinh(*x);
    return EXC_NONE;
}

int test_moore_cosh(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = cosh(*x);
    return EXC_NONE;
}

int test_moore_tanh(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = tanh(*x);
    return EXC_NONE;
}

int test_moore_asinh(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = asinh(*x);
    return EXC_NONE;
}

int test_moore_acosh(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = acosh(*x);
    return EXC_NONE;
}

int test_moore_atanh(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = atanh(*x);
    return EXC_NONE;
}

int test_moore_sign(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = sign(*x);
    return EXC_NONE;
}

int test_moore_ceil(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = ceil(*x);
    return EXC_NONE;
}

int test_moore_floor(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = floor(*x);
    return EXC_NONE;
}

int test_moore_trunc(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = trunc(*x);
    return EXC_NONE;
}

int test_moore_roundTiesToEven(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = round_ties_to_even(*x);
    return EXC_NONE;
}

int test_moore_roundTiesToAway(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = round_ties_to_away(*x);
    return EXC_NONE;
}

int test_moore_abs(I *x, I *r) {
    Moore::UpRounding rnd;
    *r = fabs(*x);
    return EXC_NONE;
}

int test_moore_min(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = min(*x, *y);
    return EXC_NONE;
}

int test_moore_max(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = max(*x, *y);
    return EXC_NONE;
}

int test_moore_mulRevToPair(I *b, I *c, I *r1, I *r2) {
    Moore::UpRounding rnd;
    std::pair<I,I> results = mul_rev_to_pair(*b, *c);
    *r1 = results.first;
    *r2 = results.second;
    return EXC_NONE;
}

int test_moore_sqrRev(I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = sqr_rev(*c, *x);
    return EXC_NONE;
}

int test_moore_sqrRevEntire(I *c, I *r) {
    Moore::UpRounding rnd;
    *r = sqr_rev(*c, I::entire());
    return EXC_NONE;
}

int test_moore_absRev(I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = abs_rev(*c, *x);
    return EXC_NONE;
}

int test_moore_absRevEntire(I *c, I *r) {
    Moore::UpRounding rnd;
    *r = abs_rev(*c, I::entire());
    return EXC_NONE;
}

int test_moore_pownRev(I *c, I *x, int* p, I *r) {
    Moore::UpRounding rnd;
    *r = pown_rev(*c, *x, *p);
    return EXC_NONE;
}

int test_moore_pownRevEntire(I *c, int* p, I *r) {
    Moore::UpRounding rnd;
    *r = pown_rev(*c, I::entire(), *p);
    return EXC_NONE;
}

int test_moore_sinRev(I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = sin_rev(*c, *x);
    return EXC_NONE;
}

int test_moore_sinRevEntire(I *c, I *r) {
    Moore::UpRounding rnd;
    *r = sin_rev(*c, I::entire());
    return EXC_NONE;
}

int test_moore_cosRev(I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = cos_rev(*c, *x);
    return EXC_NONE;
}

int test_moore_cosRevEntire(I *c, I *r) {
    Moore::UpRounding rnd;
    *r = cos_rev(*c, I::entire());
    return EXC_NONE;
}

int test_moore_tanRev(I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = tan_rev(*c, *x);
    return EXC_NONE;
}

int test_moore_tanRevEntire(I *c, I *r) {
    Moore::UpRounding rnd;
    *r = tan_rev(*c, I::entire());
    return EXC_NONE;
}

int test_moore_coshRev(I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = cosh_rev(*c, *x);
    return EXC_NONE;
}

int test_moore_coshRevEntire(I *c, I *r) {
    Moore::UpRounding rnd;
    *r = cosh_rev(*c, I::entire());
    return EXC_NONE;
}

int test_moore_mulRev(I *b, I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = mul_rev(*b, *c, *x);
    return EXC_NONE;
}

int test_moore_mulRevEntire(I *b, I *c, I *r) {
    Moore::UpRounding rnd;
    *r = mul_rev(*b, *c, I::entire());
    return EXC_NONE;
}

int test_moore_powRev1(I *b, I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = pow_rev1(*b, *c, *x);
    return EXC_NONE;
}

int test_moore_powRev1Entire(I *b, I *c, I *r) {
    Moore::UpRounding rnd;
    *r = pow_rev1(*b, *c, I::entire());
    return EXC_NONE;
}

int test_moore_powRev2(I *a, I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = pow_rev2(*a, *c, *x);
    return EXC_NONE;
}

int test_moore_powRev2Entire(I *a, I *c, I *r) {
    Moore::UpRounding rnd;
    *r = pow_rev2(*a, *c, I::entire());
    return EXC_NONE;
}

int test_moore_atan2Rev1(I *b, I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = atan2_rev1(*b, *c, *x);
    return EXC_NONE;
}

int test_moore_atan2Rev1Entire(I *b, I *c, I *r) {
    Moore::UpRounding rnd;
    *r = atan2_rev1(*b, *c, I::entire());
    return EXC_NONE;
}

int test_moore_atan2Rev2(I *a, I *c, I *x, I *r) {
    Moore::UpRounding rnd;
    *r = atan2_rev2(*a, *c, *x);
    return EXC_NONE;
}

int test_moore_atan2Rev2Entire(I *a, I *c, I *r) {
    Moore::UpRounding rnd;
    *r = atan2_rev2(*a, *c, I::entire());
    return EXC_NONE;
}

int test_moore_cancelMinus(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = cancel_minus(*x, *y);
    return EXC_NONE;
}

int test_moore_cancelPlus(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = cancel_plus(*x, *y);
    return EXC_NONE;
}

int test_moore_intersection(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = intersection(*x, *y);
    return EXC_NONE;
}

int test_moore_convexHull(I *x, I *y, I *r) {
    Moore::UpRounding rnd;
    *r = hull(*x, *y);
    return EXC_NONE;
}

int test_moore_empty(I *r) {
    Moore::UpRounding rnd;
    *r = I();
    return EXC_NONE;
}

int test_moore_entire(I *r) {
    Moore::UpRounding rnd;
    *r = I::entire();
    return EXC_NONE;
}

int test_moore_numsToInterval(double *l, double *u, I *r) {
    Moore::UpRounding rnd;
    Moore::Accuracy exception = Moore::nums_to_interval(*r, *l, *u);
    return exception == Moore::Accuracy::Invalid ? EXC_UNDEFINED_OPERATION
         : exception == Moore::Accuracy::Imprecise ? EXC_POSSIBLY_UNDEFINED_OPERATION
         : EXC_NONE;
}

int test_moore_textToInterval(const char* s, I *r) {
    Moore::UpRounding rnd;
    Moore::Accuracy exception = Moore::text_to_interval(*r, s);
    return exception == Moore::Accuracy::Invalid ? EXC_UNDEFINED_OPERATION
         : exception == Moore::Accuracy::Imprecise ? EXC_POSSIBLY_UNDEFINED_OPERATION
         : EXC_NONE;
}

int test_moore_inf(I* x, double *r) {
    Moore::UpRounding rnd;
    *r = inf(*x);
    return EXC_NONE;
}

int test_moore_sup(I* x, double *r) {
    Moore::UpRounding rnd;
    *r = sup(*x);
    return EXC_NONE;
}

int test_moore_mid(I* x, double *r) {
    Moore::UpRounding rnd;
    *r = mid(*x);
    return EXC_NONE;
}

int test_moore_rad(I* x, double *r) {
    Moore::UpRounding rnd;
    *r = rad(*x);
    return EXC_NONE;
}

int test_moore_midRad(I* x, double *rmid, double *rrad) {
    Moore::UpRounding rnd;
    *rmid = mid_rad(*rrad, *x);
    return EXC_NONE;
}

int test_moore_wid(I* x, double *r) {
    Moore::UpRounding rnd;
    *r = wid(*x);
    return EXC_NONE;
}

int test_moore_mag(I* x, double *r) {
    Moore::UpRounding rnd;
    *r = mag(*x);
    return EXC_NONE;
}

int test_moore_mig(I* x, double *r) {
    Moore::UpRounding rnd;
    *r = mig(*x);
    return EXC_NONE;
}

int test_moore_isEmpty(I* x, bool *r) {
    Moore::UpRounding rnd;
    *r = is_empty(*x);
    return EXC_NONE;
}

int test_moore_isEntire(I* x, bool *r) {
    Moore::UpRounding rnd;
    *r = is_entire(*x);
    return EXC_NONE;
}

//int test_moore_isNaI(I* x, bool *r) {
//    Moore::UpRounding rnd;
//    *r = false;
//    return EXC_NONE;
//}

int test_moore_equal(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = *x == *y;
    return EXC_NONE;
}

int test_moore_subset(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = is_subset(*x, *y);
    return EXC_NONE;
}

int test_moore_less(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = is_less(*x, *y);
    return EXC_NONE;
}

int test_moore_precedes(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = precedes(*x, *y);
    return EXC_NONE;
}

int test_moore_interior(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = is_interior(*x, *y);
    return EXC_NONE;
}

int test_moore_strictLess(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = is_strictly_less(*x, *y);
    return EXC_NONE;
}

int test_moore_strictPrecedes(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = strictly_precedes(*x, *y);
    return EXC_NONE;
}

int test_moore_disjoint(I* x, I* y, bool *r) {
    Moore::UpRounding rnd;
    *r = are_disjoint(*x, *y);
    return EXC_NONE;
}

int test_moore_isSingleton(I* x, bool *r) {
    Moore::UpRounding rnd;
    *r = is_singleton(*x);
    return EXC_NONE;
}

int test_moore_isCommonInterval(I* x, bool *r) {
    Moore::UpRounding rnd;
    *r = is_common_interval(*x);
    return EXC_NONE;
}

int test_moore_isMember(double *m, I* x, bool *r) {
    Moore::UpRounding rnd;
    *r = is_member(*m, *x);
    return EXC_NONE;
}

int test_moore_overlap(I *x, I *y, int *r) {
    Moore::UpRounding rnd;
    *r = static_cast<int>(overlap(*x, *y));
    return EXC_NONE;
}

int test_moore_intervalToExact(I *x, const char** s) {
    Moore::UpRounding rnd;
    *s = strdup(interval_to_exact(*x).c_str());
    return EXC_NONE;
}

}
