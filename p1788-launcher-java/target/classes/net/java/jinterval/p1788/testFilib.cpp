#include <interval/interval.hpp>

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

using filib::interval;
typedef filib::interval<double,filib::native_switched,filib::i_mode_extended> I;

extern "C" {

void test_filib_setup() {
    filib::fp_traits<double>::setup();
}

int test_filib_neg(I* x, I* r) {
    *r = - *x;
    return EXC_NONE;
}

int test_filib_add(I* x, I* y, I* r) {
    *r = *x + *y;
    return EXC_NONE;
}

int test_filib_sub(I* x, I* y, I* r) {
    *r = *x - *y;
    return EXC_NONE;
}

int test_filib_mul(I* x, I* y, I* r) {
    *r = *x * *y;
    return EXC_NONE;
}

int test_filib_div(I* x, I* y, I* r) {
    *r = *x / *y;
    return EXC_NONE;
}

int test_filib_recip(I* x, I* r) {
    *r = 1.0 / *x;
    return EXC_NONE;
}

int test_filib_sqrt(I* x, I* r) {
    *r = sqrt( *x );
    return EXC_NONE;
}

int test_filib_hypot(I* x, I *y, I* r) {
    *r = sqrt( sqr( *x ) + sqr( *y ));
    return EXC_NONE;
}

int test_filib_fma(I* x, I *y, I *z, I* r) {
    *r = *x * *y + *z;
    return EXC_NONE;
}

int test_filib_sqr(I* x, I* r) {
    *r = sqr( *x );
    return EXC_NONE;
}

int test_filib_pown(I* x, int *p, I* r) {
    *r = power( *x, *p );
    return EXC_NONE;
}

int test_filib_pow(I* x, I *y, I* r) {
    *r = pow( *x, *y );
    return EXC_NONE;
}

int test_filib_exp(I* x, I* r) {
    *r = exp( *x );
    return EXC_NONE;
}

int test_filib_exp2(I* x, I* r) {
    *r = exp2( *x );
    return EXC_NONE;
}

int test_filib_exp10(I* x, I* r) {
    *r = exp10( *x );
    return EXC_NONE;
}

int test_filib_log(I* x, I* r) {
    *r = log( *x );
    return EXC_NONE;
}

int test_filib_log2(I* x, I* r) {
    *r = log2( *x );
    return EXC_NONE;
}

int test_filib_log10(I* x, I* r) {
    *r = log10( *x );
    return EXC_NONE;
}

int test_filib_sin(I* x, I* r) {
    *r = sin( *x );
    return EXC_NONE;
}

int test_filib_cos(I* x, I* r) {
    *r = cos( *x );
    return EXC_NONE;
}

int test_filib_tan(I* x, I* r) {
    *r = tan( *x );
    return EXC_NONE;
}

int test_filib_asin(I* x, I* r) {
    *r = asin( *x );
    return EXC_NONE;
}

int test_filib_acos(I* x, I* r) {
    *r = acos( *x );
    return EXC_NONE;
}

int test_filib_atan(I* x, I* r) {
    *r = atan( *x );
    return EXC_NONE;
}

//int test_filib_atan2(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_filib_sinh(I* x, I* r) {
    *r = sinh( *x );
    return EXC_NONE;
}

int test_filib_cosh(I* x, I* r) {
    *r = cosh( *x );
    return EXC_NONE;
}

int test_filib_tanh(I* x, I* r) {
    *r = tanh( *x );
    return EXC_NONE;
}

int test_filib_asinh(I* x, I* r) {
    *r = asinh( *x );
    return EXC_NONE;
}

int test_filib_acosh(I* x, I* r) {
    *r = acosh( *x );
    return EXC_NONE;
}

int test_filib_atanh(I* x, I* r) {
    *r = atanh( *x );
    return EXC_NONE;
}

//int test_filib_sign(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_filib_ceil(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_filib_floor(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_filib_round(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_filib_trunc(I* x, I* r) {
//    return EXC_NONE;
//}

int test_filib_abs(I* x, I* r) {
    *r = abs( *x );
    return EXC_NONE;
}

//int test_filib_min(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

//int test_filib_max(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_filib_intersection(I* x, I *y, I* r) {
    *r = intersect( *x , *y );
    return EXC_NONE;
}

int test_filib_convexHull(I* x, I *y, I* r) {
    *r = hull( *x , *y );
    return EXC_NONE;
}

}