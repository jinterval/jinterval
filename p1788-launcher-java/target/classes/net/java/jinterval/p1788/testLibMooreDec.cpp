#include "moore/config/minimal.h"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

typedef Moore::Interval<> B;
typedef struct {
    B bare;
    char decoration;
} I;

const double zero = 0.0;

inline bool is_nai(I *r) {
    return static_cast<Moore::Decoration>(r->decoration) < Moore::Decoration::Trv;
}

void setDec0(I *r, Moore::Decoration dec) {
    if (dec < Moore::Decoration::Trv) {
        r->bare = B();
    }
    r->decoration = static_cast<char>(adjust(dec, infx(r->bare), supx(r->bare)));
}

inline void setDec1(I *r, Moore::Decoration dec, I* x) {
    if (static_cast<Moore::Decoration>(x->decoration) < dec)
        dec = static_cast<Moore::Decoration>(x->decoration);
    setDec0(r, dec);
}

inline void setDec2(I *r, Moore::Decoration dec, I* x, I* y) {
    if (static_cast<Moore::Decoration>(x->decoration) < dec)
        dec = static_cast<Moore::Decoration>(x->decoration);
    if (static_cast<Moore::Decoration>(y->decoration) < dec)
        dec = static_cast<Moore::Decoration>(y->decoration);
    setDec0(r, dec);
}

inline void setDec3(I *r, Moore::Decoration dec, I* x, I* y, I *z) {
    if (static_cast<Moore::Decoration>(x->decoration) < dec)
        dec = static_cast<Moore::Decoration>(x->decoration);
    if (static_cast<Moore::Decoration>(y->decoration) < dec)
        dec = static_cast<Moore::Decoration>(y->decoration);
    if (static_cast<Moore::Decoration>(z->decoration) < dec)
        dec = static_cast<Moore::Decoration>(z->decoration);
    setDec0(r, dec);
}

extern "C" {

void test_moore_setup() {
}

int test_moore_neg(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = neg(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_add(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = add(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_sub(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sub(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_mul(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = mul(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_div(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = div(x->bare, y->bare);
    Moore::Decoration localDec = is_member(zero, y->bare) ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_recip(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = recip(x->bare);
    Moore::Decoration localDec = is_member(zero, x->bare) ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_sqr(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sqr(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_sqrt(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sqrt(x->bare);
    Moore::Decoration localDec = inf(x->bare) < 0 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_fma(I *x, I *y, I *z, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = fma(x->bare, y->bare, z->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec3(r, localDec, x, y, z);
    return EXC_NONE;
}

int test_moore_pown(I *x, int *p, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pown(x->bare, *p);
    Moore::Decoration localDec = *p < 0 && is_member(zero, x->bare) ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_pow(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pow(x->bare, y->bare);
    Moore::Decoration localDec = inf(x->bare) < 0
                                 || (is_member(zero, x->bare) && inf(y->bare) <= 0) ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_exp(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = exp(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_exp2(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = exp2(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_exp10(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = exp10(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_log(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = log(x->bare);
    Moore::Decoration localDec = inf(x->bare) <= 0 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_log2(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = log2(x->bare);
    Moore::Decoration localDec = inf(x->bare) <= 0 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_log10(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = log10(x->bare);
    Moore::Decoration localDec = inf(x->bare) <= 0 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_sin(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sin(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_cos(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cos(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

bool in_tan_domain(B x) {
    B cosx = cos(x);
    return inf(cosx) >= 0 || sup(cosx) <= 0;
}

int test_moore_tan(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = tan(x->bare);
    Moore::Decoration localDec = is_entire(r->bare) && !in_tan_domain(x->bare) ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_asin(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = asin(x->bare);
    Moore::Decoration localDec = inf(x->bare) < -1 || sup(x->bare) > 1 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_acos(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = acos(x->bare);
    Moore::Decoration localDec = inf(x->bare) < -1 || sup(x->bare) > 1 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_atan(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = atan(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_atan2(I *y, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = atan2(y->bare, x->bare);
    Moore::Decoration localDec = !is_member(zero, y->bare) || inf(x->bare) > 0  ? Moore::Decoration::Com
                               : sup(x->bare) >= 0 ? Moore::Decoration::Trv
                               : inf(y->bare) < 0 ? Moore::Decoration::Def
                               : Moore::Decoration::Dac;
    setDec2(r, localDec, y, x);
    return EXC_NONE;
}

int test_moore_sinh(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sinh(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_cosh(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cosh(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_tanh(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = tanh(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_asinh(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = asinh(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_acosh(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = acosh(x->bare);
    Moore::Decoration localDec = inf(x->bare) < 1 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_atanh(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = atanh(x->bare);
    Moore::Decoration localDec = inf(x->bare) <= -1 || sup(x->bare) >= 1 ? Moore::Decoration::Trv
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_sign(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sign(x->bare);
    Moore::Decoration localDec = !is_member(zero, x->bare) ? Moore::Decoration::Com
                               : is_singleton(x->bare) ? Moore::Decoration::Dac
                               : Moore::Decoration::Def;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

bool is_integer(double x) {
    return std::isfinite(x) && (fabs(x) >= 0x1p52 || x == (long) x);
}

bool is_half_integer(double x) {
    x = fabs(x);
    return x < 0x1p52 && x*2 == (1|(long) (x*2));
}

int test_moore_ceil(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = ceil(x->bare);
    Moore::Decoration localDec = !is_singleton(r->bare) ? Moore::Decoration::Def
                               : is_integer(sup(x->bare)) ? Moore::Decoration::Dac
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_floor(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = floor(x->bare);
    Moore::Decoration localDec = !is_singleton(r->bare) ? Moore::Decoration::Def
                               : is_integer(inf(x->bare)) ? Moore::Decoration::Dac
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_trunc(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = trunc(x->bare);
    Moore::Decoration localDec = !is_singleton(r->bare) ? Moore::Decoration::Def
                               : (inf(x->bare) > 0 && is_integer(inf(x->bare)))
                                 || (sup(x->bare) < 0 && is_integer(sup(x->bare))) ? Moore::Decoration::Dac
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_roundTiesToEven(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = round_ties_to_even(x->bare);
    Moore::Decoration localDec = !is_singleton(r->bare) ? Moore::Decoration::Def
                               : is_half_integer(inf(x->bare)) || is_half_integer(sup(x->bare)) ? Moore::Decoration::Dac
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_roundTiesToAway(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = round_ties_to_away(x->bare);
    Moore::Decoration localDec = !is_singleton(r->bare) ? Moore::Decoration::Def
                               : is_half_integer(inf(x->bare)) || is_half_integer(sup(x->bare)) ? Moore::Decoration::Dac
                               : Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_abs(I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare =  fabs(x->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec1(r, localDec, x);
    return EXC_NONE;
}

int test_moore_min(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = min(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_max(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = max(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_mulRevToPair(I *b, I *c, I *r1, I *r2) {
    Moore::RaiiRounding rnd;
    std::pair<B,B> results = mul_rev_to_pair(b->bare, c->bare);
    r1->bare = results.first;
    r2->bare = results.second;
    Moore::Decoration localDec1 = is_member(zero, b->bare)? Moore::Decoration::Trv
                                : Moore::Decoration::Com;
    Moore::Decoration localDec2 = Moore::Decoration::Trv;
    setDec2(r1, localDec1, b, c);
    setDec2(r2, localDec2, b, c);
    return EXC_NONE;
}

int test_moore_sqrRev(I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sqr_rev(c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, c, x);
    return EXC_NONE;
}

int test_moore_sqrRevEntire(I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sqr_rev(c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec1(r, localDec, c);
    return EXC_NONE;
}

int test_moore_absRev(I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = abs_rev(c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, c, x);
    return EXC_NONE;
}

int test_moore_absRevEntire(I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = abs_rev(c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec1(r, localDec, c);
    return EXC_NONE;
}

int test_moore_pownRev(I *c, I *x, int* p, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pown_rev(c->bare, x->bare, *p);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, c, x);
    return EXC_NONE;
}

int test_moore_pownRevEntire(I *c, int* p, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pown_rev(c->bare, B::entire(), *p);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec1(r, localDec, c);
    return EXC_NONE;
}

int test_moore_sinRev(I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sin_rev(c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, c, x);
    return EXC_NONE;
}

int test_moore_sinRevEntire(I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = sin_rev(c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec1(r, localDec, c);
    return EXC_NONE;
}

int test_moore_cosRev(I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cos_rev(c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, c, x);
    return EXC_NONE;
}

int test_moore_cosRevEntire(I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cos_rev(c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec1(r, localDec, c);
    return EXC_NONE;
}

int test_moore_tanRev(I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = tan_rev(c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, c, x);
    return EXC_NONE;
}

int test_moore_tanRevEntire(I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = tan_rev(c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec1(r, localDec, c);
    return EXC_NONE;
}

int test_moore_coshRev(I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cosh_rev(c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, c, x);
    return EXC_NONE;
}

int test_moore_coshRevEntire(I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cosh_rev(c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec1(r, localDec, c);
    return EXC_NONE;
}

int test_moore_mulRev(I *b, I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = mul_rev(b->bare, c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec3(r, localDec, b, c, x);
    return EXC_NONE;
}

int test_moore_mulRevEntire(I *b, I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = mul_rev(b->bare, c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, b, c);
    return EXC_NONE;
}

int test_moore_powRev1(I *b, I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pow_rev1(b->bare, c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec3(r, localDec, b, c, x);
    return EXC_NONE;
}

int test_moore_powRev1Entire(I *b, I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pow_rev1(b->bare, c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, b, c);
    return EXC_NONE;
}

int test_moore_powRev2(I *a, I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pow_rev2(a->bare, c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec3(r, localDec, a, c, x);
    return EXC_NONE;
}

int test_moore_powRev2Entire(I *a, I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = pow_rev2(a->bare, c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, a, c);
    return EXC_NONE;
}

int test_moore_atan2Rev1(I *b, I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = atan2_rev1(b->bare, c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec3(r, localDec, b, c, x);
    return EXC_NONE;
}

int test_moore_atan2Rev1Entire(I *b, I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = atan2_rev1(b->bare, c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, b, c);
    return EXC_NONE;
}

int test_moore_atan2Rev2(I *a, I *c, I *x, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = atan2_rev2(a->bare, c->bare, x->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec3(r, localDec, a, c, x);
    return EXC_NONE;
}

int test_moore_atan2Rev2Entire(I *a, I *c, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = atan2_rev2(a->bare, c->bare, B::entire());
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, a, c);
    return EXC_NONE;
}

int test_moore_cancelMinus(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cancel_minus(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_cancelPlus(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = cancel_plus(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_intersection(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = intersection(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_convexHull(I *x, I *y, I *r) {
    Moore::RaiiRounding rnd;
    r->bare = hull(x->bare, y->bare);
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec2(r, localDec, x, y);
    return EXC_NONE;
}

int test_moore_empty(I *r) {
    Moore::RaiiRounding rnd;
    r->bare = B();
    Moore::Decoration localDec = Moore::Decoration::Trv;
    setDec0(r, localDec);
    return EXC_NONE;
}

int test_moore_nai(I *r) {
    Moore::RaiiRounding rnd;
    r->bare = B();
    Moore::Decoration localDec = Moore::Decoration::Ill;
    setDec0(r, localDec);
    return EXC_NONE;
}

int test_moore_entire(I *r) {
    Moore::RaiiRounding rnd;
    r->bare = B::entire();
    Moore::Decoration localDec = Moore::Decoration::Dac;
    setDec0(r, localDec);
    return EXC_NONE;
}

int test_moore_numsToInterval(double *l, double *u, I *r) {
    Moore::RaiiRounding rnd;
    Moore::Accuracy exception = Moore::nums_to_interval(r->bare, *l, *u);
    Moore::Decoration localDec = Moore::Decoration::Com;
    if (exception == Moore::Accuracy::Invalid)
        localDec = Moore::Decoration::Ill;
    setDec0(r, localDec);
    return exception == Moore::Accuracy::Invalid ? EXC_UNDEFINED_OPERATION
         : exception == Moore::Accuracy::Imprecise ? EXC_POSSIBLY_UNDEFINED_OPERATION
         : EXC_NONE;
}

int test_moore_numsDecToInterval(double *l, double *u, int *dec, I *r) {
    Moore::RaiiRounding rnd;
    Moore::Accuracy exception;
    Moore::Decoration localDec = static_cast<Moore::Decoration>(*dec);
    if (localDec < Moore::Decoration::Trv || (localDec > Moore::Decoration::Dac && !(std::isfinite(*l) && std::isfinite(*u)))) {
        exception = Moore::Accuracy::Invalid;
    } else {
        exception = Moore::nums_to_interval(r->bare, *l, *u);
    }
    if (exception == Moore::Accuracy::Invalid)
        localDec = Moore::Decoration::Ill;
    setDec0(r, localDec);
    return exception == Moore::Accuracy::Invalid ? EXC_UNDEFINED_OPERATION
         : exception == Moore::Accuracy::Imprecise ? EXC_POSSIBLY_UNDEFINED_OPERATION
         : EXC_NONE;
}

int test_moore_textToInterval(const char* s, I *r) {
    Moore::RaiiRounding rnd;
    Moore::Accuracy exception = Moore::text_to_interval(r->bare, s);
    Moore::Decoration localDec = Moore::Decoration::Com;
    if (exception == Moore::Accuracy::Invalid)
         localDec = Moore::Decoration::Ill;
    setDec0(r, localDec);
    return exception == Moore::Accuracy::Invalid ? EXC_UNDEFINED_OPERATION
         : exception == Moore::Accuracy::Imprecise ? EXC_POSSIBLY_UNDEFINED_OPERATION
         : EXC_NONE;
}

int test_moore_textToDecoratedInterval(const char* s, I *r) {
    Moore::RaiiRounding rnd;
    Moore::Decoration localDec = Moore::Decoration::Com;
    Moore::Accuracy exception = Moore::text_to_dec_interval(localDec, r->bare, s);
    if (exception == Moore::Accuracy::Invalid)
         localDec = Moore::Decoration::Ill;
    setDec0(r, localDec);
    return exception == Moore::Accuracy::Invalid ? EXC_UNDEFINED_OPERATION
         : exception == Moore::Accuracy::Imprecise ? EXC_POSSIBLY_UNDEFINED_OPERATION
         : EXC_NONE;
}

int test_moore_inf(I* x, double *r) {
    Moore::RaiiRounding rnd;
    *r = is_nai(x) ? std::numeric_limits<double>::quiet_NaN() : inf(x->bare);
    return EXC_NONE;
}

int test_moore_sup(I* x, double *r) {
    Moore::RaiiRounding rnd;
    *r = is_nai(x) ? std::numeric_limits<double>::quiet_NaN() : sup(x->bare);
    return EXC_NONE;
}

int test_moore_mid(I* x, double *r) {
    Moore::RaiiRounding rnd;
    *r = mid(x->bare);
    return EXC_NONE;
}

int test_moore_rad(I* x, double *r) {
    Moore::RaiiRounding rnd;
    *r = rad(x->bare);
    return EXC_NONE;
}

int test_moore_midRad(I* x, double *rmid, double *rrad) {
    Moore::RaiiRounding rnd;
    *rmid = mid_rad(*rrad, x->bare);
    return EXC_NONE;
}

int test_moore_wid(I* x, double *r) {
    Moore::RaiiRounding rnd;
    *r = wid(x->bare);
    return EXC_NONE;
}

int test_moore_mag(I* x, double *r) {
    Moore::RaiiRounding rnd;
    *r = mag(x->bare);
    return EXC_NONE;
}

int test_moore_mig(I* x, double *r) {
    Moore::RaiiRounding rnd;
    *r = mig(x->bare);
    return EXC_NONE;
}

int test_moore_isEmpty(I* x, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && is_empty(x->bare);
    return EXC_NONE;
}

int test_moore_isEntire(I* x, bool *r) {
    Moore::RaiiRounding rnd;
    *r = is_entire(x->bare);
    return EXC_NONE;
}

int test_moore_isNaI(I* x, bool *r) {
    Moore::RaiiRounding rnd;
    *r = static_cast<Moore::Decoration>(x->decoration) < Moore::Decoration::Trv;
    return EXC_NONE;
}

int test_moore_equal(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && x->bare == y->bare;
    return EXC_NONE;
}

int test_moore_subset(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && is_subset(x->bare, y->bare);
    return EXC_NONE;
}

int test_moore_less(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && is_less(x->bare, y->bare);
    return EXC_NONE;
}

int test_moore_precedes(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && precedes(x->bare, y->bare);
    return EXC_NONE;
}

int test_moore_interior(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && is_interior(x->bare, y->bare);
    return EXC_NONE;
}

int test_moore_strictLess(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && is_strictly_less(x->bare, y->bare);
    return EXC_NONE;
}

int test_moore_strictPrecedes(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && strictly_precedes(x->bare, y->bare);
    return EXC_NONE;
}

int test_moore_disjoint(I* x, I* y, bool *r) {
    Moore::RaiiRounding rnd;
    *r = !is_nai(x) && !is_nai(y) && are_disjoint(x->bare, y->bare);
    return EXC_NONE;
}

int test_moore_isSingleton(I* x, bool *r) {
    Moore::RaiiRounding rnd;
    *r = is_singleton(x->bare);
    return EXC_NONE;
}

int test_moore_isCommonInterval(I* x, bool *r) {
    Moore::RaiiRounding rnd;
    *r = is_common_interval(x->bare);
    return EXC_NONE;
}

int test_moore_isMember(double *m, I* x, bool *r) {
    Moore::RaiiRounding rnd;
    *r = is_member(*m, x->bare);
    return EXC_NONE;
}

int test_moore_overlap(I *x, I *y, int *r) {
    Moore::RaiiRounding rnd;
    if (is_nai(x) || is_nai(y))
        *r = 0;
    else
        *r = static_cast<int>(overlap(x->bare, y->bare));
    return EXC_NONE;
}

int test_moore_intervalToExact(B *x, const char** s) {
    Moore::RaiiRounding rnd;
    *s = strdup(interval_to_exact(*x).c_str());
    return EXC_NONE;
}

int test_moore_intervalToDecoratedExact(I *x, const char** s) {
    Moore::RaiiRounding rnd;
    if (is_nai(x))
        *s = strdup("[nai]");
    else if (is_empty(x->bare))
        *s = strdup(interval_to_exact(x->bare).c_str());
    else
        *s = strdup((interval_to_exact(x->bare) + "_" + to_string(static_cast<Moore::Decoration>(x->decoration))).c_str());
    return EXC_NONE;
}

int test_moore_newDec(B *x, I* r) {
    Moore::RaiiRounding rnd;
    r->bare = *x;
    Moore::Decoration localDec = Moore::Decoration::Com;
    setDec0(r, localDec);
    return EXC_NONE;
}

int test_moore_setDec(B *x, int* dec, I* r) {
    Moore::RaiiRounding rnd;
    r->bare = *x;
    Moore::Decoration localDec = static_cast<Moore::Decoration>(*dec);
    setDec0(r, localDec);
    return EXC_NONE;
}

int test_moore_intervalPart(I* x, B *r) {
    Moore::RaiiRounding rnd;
    *r = x->bare;
    return static_cast<Moore::Decoration>(x->decoration) == Moore::Decoration::Ill
         ? EXC_INTERVAL_PART_OF_NAI
         : EXC_NONE;
}

int test_moore_decorationPart(I* x, int *r) {
    Moore::RaiiRounding rnd;
    *r = x->decoration;
    return EXC_NONE;
}

int test_moore_convertType(I* x, I *r) {
    Moore::RaiiRounding rnd;
    *r = *x;
    return EXC_NONE;
}

}


