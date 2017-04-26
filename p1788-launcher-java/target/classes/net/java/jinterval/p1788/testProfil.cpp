#include <BIAS/Bias0.h>
#include <BIAS/BiasF.h>

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

typedef BIASINTERVAL I;

extern "C" {

void test_profil_setup() {
    BiasInit();
    BiasFuncInit();
}

int test_profil_neg(I* x, I* r) {
    BiasNeg(r, x);
    return EXC_NONE;
}

int test_profil_add(I* x, I* y, I* r) {
    BiasAddII(r, x, y);
    return EXC_NONE;
}

int test_profil_sub(I* x, I* y, I* r) {
    BiasSubII(r, x, y);
    return EXC_NONE;
}

int test_profil_mul(I* x, I* y, I* r) {
    BiasMulII(r, x, y);
    return EXC_NONE;
}

int test_profil_div(I* x, I* y, I* r) {
    BiasDivII(r, x, y);
    return EXC_NONE;
}

int test_profil_recip(I* x, I* r) {
    double one = 1.0;
    BiasDivRI(r, &one, x);
    return EXC_NONE;
}

int test_profil_sqrt(I* x, I* r) {
    BiasSqrt(r, x);
    return EXC_NONE;
}

int test_profil_hypot(I* x, I* y, I* r) {
    I xx, yy;
    BiasSqr(&xx, x);
    BiasSqr(&yy, y);
    BiasAddII(r, &xx, &yy);
    return EXC_NONE;
}

int test_profil_fma(I* x, I* y, I* z, I* r) {
    *r = *z;
    BiasMacII(r, x, y);
    return EXC_NONE;
}

int test_profil_sqr(I* x, I* r) {
    BiasSqr(r, x);
    return EXC_NONE;
}

int test_profil_pown(I* x, int *p, I* r) {
    BiasPowerN(r, x, *p);
    return EXC_NONE;
}

int test_profil_pow(I* x, I *y, I* r) {
    BiasPowerI(r, x, y);
    return EXC_NONE;
}

int test_profil_exp(I* x, I* r) {
    BiasExp(r, x);
    return EXC_NONE;
}

//int test_profil_exp2(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_profil_exp10(I* x, I* r) {
//    return EXC_NONE;
//}

int test_profil_log(I* x, I* r) {
    BiasLog(r, x);
    return EXC_NONE;
}

//int test_profil_log2(I* x, I* r) {
//    return EXC_NONE;
//}

int test_profil_log10(I* x, I* r) {
    BiasLog10(r, x);
    return EXC_NONE;
}

int test_profil_sin(I* x, I* r) {
    BiasSin(r, x);
    return EXC_NONE;
}

int test_profil_cos(I* x, I* r) {
    BiasCos(r, x);
    return EXC_NONE;
}

int test_profil_tan(I* x, I* r) {
    BiasTan(r, x);
    return EXC_NONE;
}

int test_profil_asin(I* x, I* r) {
    BiasArcSin(r, x);
    return EXC_NONE;
}

int test_profil_acos(I* x, I* r) {
    BiasArcCos(r, x);
    return EXC_NONE;
}

int test_profil_atan(I* x, I* r) {
    BiasArcTan(r, x);
    return EXC_NONE;
}

int test_profil_atan2(I* x, I *y, I* r) {
    return EXC_NONE;
}

int test_profil_sinh(I* x, I* r) {
    BiasSinh(r, x);
    return EXC_NONE;
}

int test_profil_cosh(I* x, I* r) {
    BiasCosh(r, x);
    return EXC_NONE;
}

int test_profil_tanh(I* x, I* r) {
    BiasTanh(r, x);
    return EXC_NONE;
}

int test_profil_asinh(I* x, I* r) {
    BiasArSinh(r, x);
    return EXC_NONE;
}

int test_profil_acosh(I* x, I* r) {
    BiasArCosh(r, x);
    return EXC_NONE;
}

int test_profil_atanh(I* x, I* r) {
    BiasArTanh(r, x);
    return EXC_NONE;
}

//int test_profil_sign(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_profil_ceil(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_profil_floor(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_profil_round(I* x, I* r) {
//    return EXC_NONE;
//}

//int test_profil_trunc(I* x, I* r) {
//    return EXC_NONE;
//}

int test_profil_abs(I* x, I* r) {
    BiasIAbs(r, x);
    return EXC_NONE;
}

//int test_profil_min(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

//int test_profil_max(I* x, I *y, I* r) {
//    return EXC_NONE;
//}

int test_profil_intersection(I* x, I *y, I* r) {
    if (!BiasIntersection(r, x , y)) {
        r->inf = r->sup = BiasNaN;
    }
    return EXC_NONE;
}

int test_filib_convexHull(I* x, I *y, I* r) {
    BiasHullII(r, x , y);
    return EXC_NONE;
}

}