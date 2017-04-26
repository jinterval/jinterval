#include "p1788/p1788.hpp"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4
#define EXC_UNKNOWN                      -5

typedef p1788::infsup::interval<double, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor> B;
typedef p1788::infsup::decorated_interval<double, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor> I;

int decode_exception() {
    switch (p1788::exception::state()) {
        case p1788::exception::none_bit:
            return EXC_NONE;
        case p1788::exception::undefined_operation_bit:
            return EXC_UNDEFINED_OPERATION;
        case p1788::exception::possibly_undefined_operation_bit:
            return EXC_POSSIBLY_UNDEFINED_OPERATION;
        case p1788::exception::interval_part_of_nai_bit:
            return EXC_INTERVAL_PART_OF_NAI;
        case p1788::exception::invalid_operand_bit:
            return EXC_INVALID_OPERAND;
        default:
            return EXC_UNKNOWN;
    }
}

extern "C" {

void test_libieee1788_setup() {
}

int test_libieee1788_pos(I *x, I *r) {
    p1788::exception::clear();
    *r = pos(*x);
    return decode_exception();
}

int test_libieee1788_neg(I *x, I *r) {
    p1788::exception::clear();
    *r = neg(*x);
    return decode_exception();
}

int test_libieee1788_add(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = add(*x, *y);
    return decode_exception();
}

int test_libieee1788_sub(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = sub(*x, *y);
    return decode_exception();
}

int test_libieee1788_mul(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = mul(*x, *y);
    return decode_exception();
}

int test_libieee1788_div(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = div(*x, *y);
    return decode_exception();
}

int test_libieee1788_recip(I *x, I *r) {
    p1788::exception::clear();
    *r = recip(*x);
    return decode_exception();
}

int test_libieee1788_sqr(I *x, I *r) {
    p1788::exception::clear();
    *r = sqr(*x);
    return decode_exception();
}

int test_libieee1788_sqrt(I *x, I *r) {
    p1788::exception::clear();
    *r = sqrt(*x);
    return decode_exception();
}

int test_libieee1788_fma(I *x, I *y, I *z, I *r) {
    p1788::exception::clear();
    *r = fma(*x, *y, *z);
    return decode_exception();
}

int test_libieee1788_pown(I *x, int *p, I *r) {
    p1788::exception::clear();
    *r = pown(*x, *p);
    return decode_exception();
}

int test_libieee1788_pow(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = pow(*x, *y);
    return decode_exception();
}

int test_libieee1788_exp(I *x, I *r) {
    p1788::exception::clear();
    *r = exp(*x);
    return decode_exception();
}

int test_libieee1788_exp2(I *x, I *r) {
    p1788::exception::clear();
    *r = exp2(*x);
    return decode_exception();
}

int test_libieee1788_exp10(I *x, I *r) {
    p1788::exception::clear();
    *r = exp10(*x);
    return decode_exception();
}

int test_libieee1788_log(I *x, I *r) {
    p1788::exception::clear();
    *r = log(*x);
    return decode_exception();
}

int test_libieee1788_log2(I *x, I *r) {
    p1788::exception::clear();
    *r = log2(*x);
    return decode_exception();
}

int test_libieee1788_log10(I *x, I *r) {
    p1788::exception::clear();
    *r = log10(*x);
    return decode_exception();
}

int test_libieee1788_sin(I *x, I *r) {
    p1788::exception::clear();
    *r = sin(*x);
    return decode_exception();
}

int test_libieee1788_cos(I *x, I *r) {
    p1788::exception::clear();
    *r = cos(*x);
    return decode_exception();
}

int test_libieee1788_tan(I *x, I *r) {
    p1788::exception::clear();
    *r = tan(*x);
    return decode_exception();
}

int test_libieee1788_asin(I *x, I *r) {
    p1788::exception::clear();
    *r = asin(*x);
    return decode_exception();
}

int test_libieee1788_acos(I *x, I *r) {
    p1788::exception::clear();
    *r = acos(*x);
    return decode_exception();
}

int test_libieee1788_atan(I *x, I *r) {
    p1788::exception::clear();
    *r = atan(*x);
    return decode_exception();
}

int test_libieee1788_atan2(I *y, I *x, I *r) {
    p1788::exception::clear();
    *r = atan2(*y, *x);
    return decode_exception();
}

int test_libieee1788_sinh(I *x, I *r) {
    p1788::exception::clear();
    *r = sinh(*x);
    return decode_exception();
}

int test_libieee1788_cosh(I *x, I *r) {
    p1788::exception::clear();
    *r = cosh(*x);
    return decode_exception();
}

int test_libieee1788_tanh(I *x, I *r) {
    p1788::exception::clear();
    *r = tanh(*x);
    return decode_exception();
}

int test_libieee1788_asinh(I *x, I *r) {
    p1788::exception::clear();
    *r = asinh(*x);
    return decode_exception();
}

int test_libieee1788_acosh(I *x, I *r) {
    p1788::exception::clear();
    *r = acosh(*x);
    return decode_exception();
}

int test_libieee1788_atanh(I *x, I *r) {
    p1788::exception::clear();
    *r = atanh(*x);
    return decode_exception();
}

int test_libieee1788_sign(I *x, I *r) {
    p1788::exception::clear();
    *r = sign(*x);
    return decode_exception();
}

int test_libieee1788_ceil(I *x, I *r) {
    p1788::exception::clear();
    *r = ceil(*x);
    return decode_exception();
}

int test_libieee1788_floor(I *x, I *r) {
    p1788::exception::clear();
    *r = floor(*x);
    return decode_exception();
}

int test_libieee1788_trunc(I *x, I *r) {
    p1788::exception::clear();
    *r = trunc(*x);
    return decode_exception();
}

int test_libieee1788_roundTiesToEven(I *x, I *r) {
    p1788::exception::clear();
    *r = round_ties_to_even(*x);
    return decode_exception();
}

int test_libieee1788_roundTiesToAway(I *x, I *r) {
    p1788::exception::clear();
    *r = round_ties_to_away(*x);
    return decode_exception();
}

int test_libieee1788_abs(I *x, I *r) {
    p1788::exception::clear();
    *r = abs(*x);
    return decode_exception();
}

int test_libieee1788_min(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = min(*x, *y);
    return decode_exception();
}

int test_libieee1788_max(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = max(*x, *y);
    return decode_exception();
}

int test_libieee1788_mulRevToPair(I *b, I *c, I *r1, I *r2) {
    p1788::exception::clear();
    std::pair<I,I> results = mul_rev_to_pair(*b, *c);
    *r1 = results.first;
    *r2 = results.second;
    return decode_exception();
}

int test_libieee1788_sqrRev(I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = sqr_rev(*c, *x);
    return decode_exception();
}

int test_libieee1788_sqrRevEntire(I *c, I *r) {
    p1788::exception::clear();
    *r = sqr_rev(*c);
    return decode_exception();
}

int test_libieee1788_absRev(I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = abs_rev(*c, *x);
    return decode_exception();
}

int test_libieee1788_absRevEntire(I *c, I *r) {
    p1788::exception::clear();
    *r = abs_rev(*c);
    return decode_exception();
}

int test_libieee1788_pownRev(I *c, I *x, int *p, I *r) {
    p1788::exception::clear();
    *r = pown_rev(*c, *x, *p);
    return decode_exception();
}

int test_libieee1788_pownRevEntire(I *c, int *p, I *r) {
    p1788::exception::clear();
    *r = pown_rev(*c, *p);
    return decode_exception();
}

int test_libieee1788_sinRev(I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = sin_rev(*c, *x);
    return decode_exception();
}

int test_libieee1788_sinRevEntire(I *c, I *r) {
    p1788::exception::clear();
    *r = sin_rev(*c);
    return decode_exception();
}

int test_libieee1788_cosRev(I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = cos_rev(*c, *x);
    return decode_exception();
}

int test_libieee1788_cosRevEntire(I *c, I *r) {
    p1788::exception::clear();
    *r = cos_rev(*c);
    return decode_exception();
}

int test_libieee1788_tanRev(I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = tan_rev(*c, *x);
    return decode_exception();
}

int test_libieee1788_tanRevEntire(I *c, I *r) {
    p1788::exception::clear();
    *r = tan_rev(*c);
    return decode_exception();
}

int test_libieee1788_coshRev(I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = cosh_rev(*c, *x);
    return decode_exception();
}

int test_libieee1788_coshRevEntire(I *c, I *r) {
    p1788::exception::clear();
    *r = cosh_rev(*c);
    return decode_exception();
}

int test_libieee1788_mulRev(I *b, I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = mul_rev(*b, *c, *x);
    return decode_exception();
}

int test_libieee1788_mulRevEntire(I *b, I *c, I *r) {
    p1788::exception::clear();
    *r = mul_rev(*b, *c);
    return decode_exception();
}

int test_libieee1788_powRev1_BAD(I *b, I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = I();
//    *r = pow_rev1(*b, *c, *x);
    return decode_exception();
}

int test_libieee1788_powRev2_BAD(I *a, I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = I();
//    *r = pow_rev2(*a, *c, *x);
    return decode_exception();
}

int test_libieee1788_atan2Rev1_BAD(I *b, I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = I();
//    *r = atan2_rev1(*b, *c, *x);
    return decode_exception();
}

int test_libieee1788_atan2Rev2_BAD(I *a, I *c, I *x, I *r) {
    p1788::exception::clear();
    *r = I();
//    *r = atan2_rev2(*a, *c, *x);
    return decode_exception();
}

int test_libieee1788_cancelMinus(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = cancel_minus(*x, *y);
    return decode_exception();
}

int test_libieee1788_cancelPlus(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = cancel_plus(*x, *y);
    return decode_exception();
}

int test_libieee1788_intersection(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = intersection(*x, *y);
    return decode_exception();
}

int test_libieee1788_convexHull(I *x, I *y, I *r) {
    p1788::exception::clear();
    *r = convex_hull(*x, *y);
    return decode_exception();
}

int test_libieee1788_empty(I *r) {
    p1788::exception::clear();
    *r = I::empty();
    return decode_exception();
}

int test_libieee1788_nai(I *r) {
    p1788::exception::clear();
    *r = I::nai();
    return decode_exception();
}

int test_libieee1788_entire(I *r) {
    p1788::exception::clear();
    *r = I::entire();
    return decode_exception();
}

int test_libieee1788_numsToInterval(double *l, double *u, I *r) {
    p1788::exception::clear();
    *r = I(*l, *u);
    return decode_exception();
}

int test_libieee1788_numsDecToInterval(double *l, double *u, int *dec, I *r) {
    p1788::exception::clear();
    *r = I(*l, *u, static_cast<p1788::decoration::decoration>(*dec));
    return decode_exception();
}

int test_libieee1788_textToInterval(const char* s, B *r) {
    p1788::exception::clear();
    *r = B(std::string(s));
    return decode_exception();
}

int test_libieee1788_textToDecoratedInterval(const char* s, I *r) {
    p1788::exception::clear();
    *r = I(std::string(s));
    return decode_exception();
}

int test_libieee1788_inf(I *x, double *r) {
    p1788::exception::clear();
    *r = inf(*x);
    return decode_exception();
}

int test_libieee1788_sup(I *x, double *r) {
    p1788::exception::clear();
    *r = sup(*x);
    return decode_exception();
}

int test_libieee1788_mid(I *x, double *r) {
    p1788::exception::clear();
    *r = mid(*x);
    return decode_exception();
}

int test_libieee1788_rad(I *x, double *r) {
    p1788::exception::clear();
    *r = rad(*x);
    return decode_exception();
}

int test_libieee1788_midRad(I *x, double *mid, double *rad) {
    p1788::exception::clear();
    std::pair<double,double> midRad = mid_rad(*x);
    *mid = midRad.first;
    *rad = midRad.second;
    return decode_exception();
}

int test_libieee1788_wid(I *x, double *r) {
    p1788::exception::clear();
    *r = wid(*x);
    return decode_exception();
}

int test_libieee1788_mag(I *x, double *r) {
    p1788::exception::clear();
    *r = mag(*x);
    return decode_exception();
}

int test_libieee1788_mig(I *x, double *r) {
    p1788::exception::clear();
    *r = mig(*x);
    return decode_exception();
}

int test_libieee1788_isEmpty(I *x, bool *r) {
    p1788::exception::clear();
    *r = is_empty(*x);
    return decode_exception();
}

int test_libieee1788_isEntire(I *x, bool *r) {
    p1788::exception::clear();
    *r = is_entire(*x);
    return decode_exception();
}

int test_libieee1788_isNaI(I *x, bool *r) {
    p1788::exception::clear();
    *r = is_nai(*x);
    return decode_exception();
}

int test_libieee1788_equal(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = equal(*x, *y);
    return decode_exception();
}

int test_libieee1788_subset(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = subset(*x, *y);
    return decode_exception();
}

int test_libieee1788_less(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = less(*x, *y);
    return decode_exception();
}

int test_libieee1788_precedes(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = precedes(*x, *y);
    return decode_exception();
}

int test_libieee1788_interior(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = interior(*x, *y);
    return decode_exception();
}

int test_libieee1788_strictLess(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = strict_less(*x, *y);
    return decode_exception();
}

int test_libieee1788_strictPrecedes(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = strict_precedes(*x, *y);
    return decode_exception();
}

int test_libieee1788_disjoint(I *x, I *y, bool *r) {
    p1788::exception::clear();
    *r = disjoint(*x, *y);
    return decode_exception();
}

int test_libieee1788_isSingleton(I *x, bool *r) {
    p1788::exception::clear();
    *r = is_singleton(*x);
    return decode_exception();
}

int test_libieee1788_isCommonInterval(I *x, bool *r) {
    p1788::exception::clear();
    *r = is_common_interval(*x);
    return decode_exception();
}

int test_libieee1788_isMember(double *m, I *x, bool *r) {
    p1788::exception::clear();
    *r = is_member(*m, *x);
    return decode_exception();
}

int test_libieee1788_overlap(I *x, I *y, int *r) {
    p1788::exception::clear();
    *r = static_cast<int>(overlap(*x, *y));
    return decode_exception();
}

int test_libieee1788_intervalToExact(B *x, const char** s) {
    p1788::exception::clear();
    *s = strdup(interval_to_exact(*x).c_str());
    return decode_exception();
}

int test_libieee1788_intervalToDecoratedExact(I *x, const char** s) {
    p1788::exception::clear();
    *s = strdup(interval_to_exact(*x).c_str());
    return decode_exception();
}

int test_libieee1788_newDec(B *x, I* r) {
    p1788::exception::clear();
    *r = I(*x);
    return decode_exception();
}

int test_libieee1788_setDec(B *x, int* dec, I* r) {
    p1788::exception::clear();
    *r = I(*x, static_cast<p1788::decoration::decoration>(*dec));
    return decode_exception();
}

int test_libieee1788_intervalPart(I* x, B *r) {
    p1788::exception::clear();
    *r = B(*x);
    return decode_exception();
}

int test_libieee1788_decorationPart(I* x, int *r) {
    p1788::exception::clear();
    *r = static_cast<int>(decoration(*x));
    return decode_exception();
}

int test_libieee1788_convertType(I* x, I *r) {
    p1788::exception::clear();
    *r = I(*x);
    return decode_exception();
}

}