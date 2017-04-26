#include "interval.hpp"
include "exception.h"
// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

using namespace cxsc;

typedef interval I;

extern "C" {

void test_cxsc_setup() {
}

int test_cxsc_neg(I* x, I* r) {
    *r = - *x;
    return EXC_NONE;
}

int test_cxsc_add(I* x, I* y, I* r) {
    *r = *x + *y;
    return EXC_NONE;
}

int test_cxsc_sub(I* x, I* y, I* r) {
    *r = *x - *y;
    return EXC_NONE;
}

int test_cxsc_mul(I* x, I* y, I* r) {
    *r = *x * *y;
    return EXC_NONE;
}

int test_cxsc_div(I* x, I* y, I* r) {
    *r = *x / *y;
    return EXC_NONE;
}

int test_cxsc_recip(I* x, I* r) {
    *r = 1 / *x;
    return EXC_NONE;
}

int test_cxsc_sqrt(I* x, I* r) {
    *r = sqrt( *x );
    return EXC_NONE;
}

int test_cxsc_hypot(I* x, I * y, I* r) {
    *r = sqrt( sqr( *x ) + sqr( *y ));
    return EXC_NONE;
}

int test_cxsc_fma(I* x, I * y, I *z, I* r) {
    *r = *x * *y + *z;
    return EXC_NONE;
}

int test_cxsc_sqr(I* x, I* r) {
    *r = sqr( *x );
    return EXC_NONE;
}

int test_cxsc_exp(I* x, I* r) {
    *r = exp( *x );
    return EXC_NONE;
}

//int test_cxsc_exp2(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_cxsc_exp10(I* x, I* r) {
//    return EXC_NONE;
//}

int test_cxsc_log(I* x, I* r) {
    *r = ln( *x );
    return EXC_NONE;
}

//int test_cxsc_log2(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_cxsc_log10(I* x, I* r) {
//    return EXC_NONE;
//}

int test_cxsc_sin(I* x, I* r) {
    *r = sin( *x );
    return EXC_NONE;
}

int test_cxsc_cos(I* x, I* r) {
    *r = cos( *x );
    return EXC_NONE;
}

int test_cxsc_tan(I* x, I* r) {
    *r = tan( *x );
    return EXC_NONE;
}

int test_cxsc_asin(I* x, I* r) {
    *r = asin( *x );
    return EXC_NONE;
}

int test_cxsc_acos(I* x, I* r) {
    *r = acos( *x );
    return EXC_NONE;
}

int test_cxsc_atan(I* x, I* r) {
    *r = atan( *x );
    return EXC_NONE;
}

//int test_cxsc_atan2(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_cxsc_sinh(I* x, I* r) {
    *r = sinh( *x );
    return EXC_NONE;
}

int test_cxsc_cosh(I* x, I* r) {
    *r = cosh( *x );
    return EXC_NONE;
}

int test_cxsc_tanh(I* x, I* r) {
    *r = tanh( *x );
    return EXC_NONE;
}

int test_cxsc_asinh(I* x, I* r) {
    *r = asinh( *x );
    return EXC_NONE;
}

int test_cxsc_acosh(I* x, I* r) {
    *r = acosh( *x );
    return EXC_NONE;
}

int test_cxsc_atanh(I* x, I* r) {
    *r = atanh( *x );
    return EXC_NONE;
}

//int test_cxsc_sign(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_cxsc_ceil(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_cxsc_floor(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_cxsc_round(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_cxsc_trunc(I* x, I* r) {
//    return EXC_NONE;
//}

int test_cxsc_abs(I* x, I* r) {
    *r = abs( *x );
    return EXC_NONE;
}

//int test_cxsc_min(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

//int test_cxsc_max(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_cxsc_intersection(I* x, I *y, I* r) {
    *r = *x & *y;
    return EXC_NONE;
}

int test_cxsc_convexHull(I* x, I *y, I* r) {
    *r = *x | *y;
    return EXC_NONE;
}

}
