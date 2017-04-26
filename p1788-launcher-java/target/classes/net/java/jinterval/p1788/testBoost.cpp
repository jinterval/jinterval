#include <boost/numeric/interval.hpp>

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

using namespace boost::numeric;
using namespace interval_lib;

typedef interval<double,
                 policies<save_state<rounded_transc_std<double> >,
                          checking_base<double> > > I;

extern "C" {

void test_boost_setup() {
}

int test_boost_neg(I* x, I* r) {
    *r = - *x;
    return EXC_NONE;
}

int test_boost_add(I* x, I* y, I* r) {
    *r = *x + *y;
    return EXC_NONE;
}

int test_boost_sub(I* x, I* y, I* r) {
    *r = *x - *y;
    return EXC_NONE;
}

int test_boost_mul(I* x, I* y, I* r) {
    *r = *x * *y;
    return EXC_NONE;
}

int test_boost_div(I* x, I* y, I* r) {
    *r = *x / *y;
    return EXC_NONE;
}

int test_boost_recip(I* x, I* r) {
    *r = multiplicative_inverse( *x );
    return EXC_NONE;
}

int test_boost_sqrt(I* x, I* r) {
    *r = sqrt( *x ) ;
    return EXC_NONE;
}

int test_boost_hypot(I* x, I *y, I* r) {
    *r = sqrt( square( *x ) + square( *y ));
    return EXC_NONE;
}

int test_boost_fma(I* x, I *y, I *z, I* r) {
    *r = *x * *y + *z;
    return EXC_NONE;
}

int test_boost_sqr(I* x, I* r) {
    *r = square( *x );
    return EXC_NONE;
}

int test_boost_pown(I* x, int *p, I* r) {
    *r = pow( *x, *p );
    return EXC_NONE;
}

//int test_boost_pow(I* x, int *y, I* r) {
//    return EXC_NONE;
//}

int test_boost_exp(I* x, I* r) {
    *r = exp( *x );
    return EXC_NONE;
}

//int test_boost_exp2(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_boost_exp10(I* x, I* r) {
//    return EXC_NONE;
//}

int test_boost_log(I* x, I* r) {
    *r = log( *x );
    return EXC_NONE;
}

//int test_boost_log2(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_boost_log10(I* x, I* r) {
//}

int test_boost_sin(I* x, I* r) {
    *r = sin( *x );
    return EXC_NONE;
}

int test_boost_cos(I* x, I* r) {
    *r = cos( *x );
    return EXC_NONE;
}

int test_boost_tan(I* x, I* r) {
    *r = tan( *x );
    return EXC_NONE;
}

int test_boost_asin(I* x, I* r) {
    *r = asin( *x );
    return EXC_NONE;
}

int test_boost_acos(I* x, I* r) {
    *r = acos( *x );
    return EXC_NONE;
}

int test_boost_atan(I* x, I* r) {
    *r = atan( *x );
    return EXC_NONE;
}

//int test_boost_atan2(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_boost_sinh(I* x, I* r) {
    *r = sinh( *x );
    return EXC_NONE;
}

int test_boost_cosh(I* x, I* r) {
    *r = cosh( *x );
    return EXC_NONE;
}

int test_boost_tanh(I* x, I* r) {
    *r = tanh( *x );
    return EXC_NONE;
}

int test_boost_asinh(I* x, I* r) {
    *r = asinh( *x );
    return EXC_NONE;
}

int test_boost_acosh(I* x, I* r) {
    *r = acosh( *x );
    return EXC_NONE;
}

int test_boost_atanh(I* x, I* r) {
    *r = atanh( *x );
    return EXC_NONE;
}

//int test_boost_sign(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_boost_ceil(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_boost_floor(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_boost_round(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_boost_trunc(I* x, I* r) {
//    return EXC_NONE;
//}

int test_boost_abs(I* x, I* r) {
    *r = abs( *x );
    return EXC_NONE;
}

int test_boost_min(I* x, I *y, I* r) {
    *r = min( *x, *y );
    return EXC_NONE;
}

int test_boost_max(I* x, I *y, I* r) {
    *r = max( *x, *y );
    return EXC_NONE;
}

int test_boost_intersection(I* x, I *y, I* r) {
    *r = intersect( *x, *y );
    return EXC_NONE;
}

int test_boost_convexHull(I* x, I *y, I* r) {
    *r = hull( *x, *y );
    return EXC_NONE;
}

}
