
/* Decorations */
#define ILL 0
#define TRV 4
#define DEF 8
#define DAC 12
#define COM 16

/* Exceptions */
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

/* Overlap States */
#define OVERLAP_bothEmpty 0
#define OVERLAP_firstEmpty 1
#define OVERLAP_secondEmpty 2
#define OVERLAP_before 3
#define OVERLAP_meets 4
#define OVERLAP_overlaps 5
#define OVERLAP_starts 6
#define OVERLAP_containedBy 7
#define OVERLAP_finishes 8
#define OVERLAP_equal 9
#define OVERLAP_finishedBy 10
#define OVERLAP_contains 11
#define OVERLAP_startedBy 12
#define OVERLAP_overlappedBy 13
#define OVERLAP_metBy 14
#define OVERLAP_after 15

/* Type tags */
#define TAG_f 0
#define TAG_d 1
#define TAG_l 2


typedef struct {
    float inf;
    float sup;
} BARE_INFSUP_B32;

typedef struct {
    float inf;
    float sup;
    char decoration;
} DECORATED_INFSUP_B32;

typedef struct {
    double inf;
    double sup;
} BARE_INFSUP_B64;

typedef struct {
    double inf;
    double sup;
    char decoration;
} DECORATED_INFSUP_B64;

typedef struct {
    long double inf;
    long double sup;
} BARE_INFSUP_B80;

typedef struct {
    long double inf;
    long double sup;
    char decoration;
} DECORATED_INFSUP_B80;


extern int p1788_bar_isValid(int x_tag, const void *x);
extern int p1788_dec_isValid(int x_tag, const void *x);

extern int p1788_bar_empty(int r_tag, void *r);
extern int p1788_dec_empty(int r_tag, void *r);

extern int p1788_bar_entire(int r_tag, void *r);
extern int p1788_dec_entire(int r_tag, void *r);

extern int p1788_dec_nai(int r_tag, void *r);

extern int p1788_bar_convertType(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_convertType(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_pos(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_pos(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_neg(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_neg(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_add(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_add(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_sub(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_sub(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_mul(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_mul(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_div(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_div(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_recip(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_recip(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_sqr(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_sqr(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_sqrt(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_sqrt(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_fma(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y, int z_tag, const void *z);
extern int p1788_dec_fma(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y, int z_tag, const void *z);

extern int p1788_bar_pown(int r_tag, void *r, int x_tag, const void *x, int p);
extern int p1788_dec_pown(int r_tag, void *r, int x_tag, const void *x, int p);

extern int p1788_bar_pow(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_pow(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_exp(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_exp(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_exp2(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_exp2(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_exp10(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_exp10(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_log(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_log(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_log2(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_log2(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_log10(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_log10(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_sin(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_sin(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_cos(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_cos(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_tan(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_tan(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_asin(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_asin(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_acos(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_acos(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_atan(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_atan(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_atan2(int r_tag, void *r, int y_tag, const void *y, int x_tag, const void *x);
extern int p1788_dec_atan2(int r_tag, void *r, int y_tag, const void *y, int x_tag, const void *x);

extern int p1788_bar_sinh(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_sinh(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_cosh(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_cosh(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_tanh(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_tanh(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_asinh(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_asinh(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_acosh(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_acosh(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_atanh(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_atanh(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_sign(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_sign(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_ceil(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_ceil(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_floor(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_floor(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_trunc(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_trunc(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_roundTiesToEven(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_roundTiesToEven(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_roundTiesToAway(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_roundTiesToAway(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_abs(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_abs(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_min(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_min(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_max(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_max(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_mulRevToPair(int r_tag, void *r1, void *r2, int b_tag, const void *b, int c_tag, const void *c);
extern int p1788_dec_mulRevToPair(int r_tag, void *r1, void *r2, int b_tag, const void *b, int c_tag, const void *c);

extern int p1788_bar_sqrRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_sqrRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_sqrRevEntire(int r_tag, void *r, int c_tag, const void *c);
extern int p1788_dec_sqrRevEntire(int r_tag, void *r, int c_tag, const void *c);

extern int p1788_bar_absRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_absRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_absRevEntire(int r_tag, void *r, int c_tag, const void *c);
extern int p1788_dec_absRevEntire(int r_tag, void *r, int c_tag, const void *c);

extern int p1788_bar_pownRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x, int p);
extern int p1788_dec_pownRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x, int p);

extern int p1788_bar_pownRevEntire(int r_tag, void *r, int c_tag, const void *c, int p);
extern int p1788_dec_pownRevEntire(int r_tag, void *r, int c_tag, const void *c, int p);

extern int p1788_bar_sinRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_sinRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_sinRevEntire(int r_tag, void *r, int c_tag, const void *c);
extern int p1788_dec_sinRevEntire(int r_tag, void *r, int c_tag, const void *c);

extern int p1788_bar_cosRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_cosRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_cosRevEntire(int r_tag, void *r, int c_tag, const void *c);
extern int p1788_dec_cosRevEntire(int r_tag, void *r, int c_tag, const void *c);

extern int p1788_bar_tanRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_tanRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_tanRevEntire(int r_tag, void *r, int c_tag, const void *c);
extern int p1788_dec_tanRevEntire(int r_tag, void *r, int c_tag, const void *c);

extern int p1788_bar_coshRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_coshRev(int r_tag, void *r, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_coshRevEntire(int r_tag, void *r, int c_tag, const void *c);
extern int p1788_dec_coshRevEntire(int r_tag, void *r, int c_tag, const void *c);

extern int p1788_bar_mulRev(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_mulRev(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_mulRevEntire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c);
extern int p1788_dec_mulRevEntire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c);

extern int p1788_bar_powRev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_powRev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_powRev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c);
extern int p1788_dec_powRev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c);

extern int p1788_bar_powRev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_powRev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_powRev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c);
extern int p1788_dec_powRev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c);

extern int p1788_bar_atan2Rev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_atan2Rev1(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_atan2Rev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c);
extern int p1788_dec_atan2Rev1Entire(int r_tag, void *r, int b_tag, const void *b, int c_tag, const void *c);

extern int p1788_bar_atan2Rev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x);
extern int p1788_dec_atan2Rev2(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c, int x_tag, const void *x);

extern int p1788_bar_atan2Rev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c);
extern int p1788_dec_atan2Rev2Entire(int r_tag, void *r, int a_tag, const void *a, int c_tag, const void *c);

extern int p1788_bar_cancelMinus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_cancelMinus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_cancelPlus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_cancelPlus(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_intersection(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_intersection(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_convexHull(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);
extern int p1788_dec_convexHull(int r_tag, void *r, int x_tag, const void *x, int y_tag, const void *y);

extern int p1788_bar_numsToInterval(int r_tag, void *r, int l_tag, const void *l, int u_tag, const void *u);
extern int p1788_dec_numsToInterval(int r_tag, void *r, int l_tag, const void *l, int u_tag, const void *u);

extern int p1788_dec_numsDecToInterval(int r_tag, void *r, int l_tag, const void *l, int u_tag, const void *u, int dec);

extern int p1788_bar_textToInterval(int r_tag, void *r, const char* s);

extern int p1788_dec_textToDecoratedInterval(int r_tag, void *r, const char* s);

extern int p1788_bar_inf(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_inf(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_sup(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_sup(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_mid(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_mid(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_rad(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_rad(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_wid(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_wid(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_mag(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_mag(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_mig(int r_tag, void *r, int x_tag, const void *x);
extern int p1788_dec_mig(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_midRad(int r_tag, void *r1, void *r2, int x_tag, const void *x);
extern int p1788_dec_midRad(int r_tag, void *r1, void *r2, int x_tag, const void *x);

extern int p1788_bar_isEmpty(int x_tag, const void *x);
extern int p1788_dec_isEmpty(int x_tag, const void *x);

extern int p1788_bar_isEntire(int x_tag, const void *x);
extern int p1788_dec_isEntire(int x_tag, const void *x);

extern int p1788_dec_isNaI(int x_tag, const void *x);

extern int p1788_bar_isCommonInterval(int x_tag, const void *x);
extern int p1788_dec_isCommonInterval(int x_tag, const void *x);

extern int p1788_bar_isSingleton(int x_tag, const void *x);
extern int p1788_dec_isSingleton(int x_tag, const void *x);

extern int p1788_bar_isMember(int m_tag, const void *m, int x_tag, const void *x);
extern int p1788_dec_isMember(int m_tag, const void *m, int x_tag, const void *x);

extern int p1788_bar_equal(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_equal(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_subset(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_subset(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_less(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_less(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_precedes(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_precedes(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_interior(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_interior(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_strictLess(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_strictLess(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_strictPrecedes(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_strictPrecedes(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_disjoint(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_disjoint(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_bar_overlap(int a_tag, const void *a, int b_tag, const void *b);
extern int p1788_dec_overlap(int a_tag, const void *a, int b_tag, const void *b);

extern int p1788_dec_newDec(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_bar_decorationPart(int x_tag, const void *x);

extern int p1788_bar_intervalPart(int r_tag, void *r, int x_tag, const void *x);

extern int p1788_dec_setDec(int r_tag, void *r, int x_tag, const void *x, int dec);

extern int p1788_sum(int r_tag, void *r, int n, void *a, int rnd);

extern int p1788_sumAbs(int r_tag, void *r, int n, void *a, int rnd);

extern int p1788_dot(int r_tag, void *r, int n, void *a, void *b, int rnd);

extern int p1788_sumSquare(int r_tag, void *r, int n, void *a, int rnd);

extern int p1788_bar_intervalToText(char **r, int x_tag, const void *x, const char* cs);
extern int p1788_dec_intervalToText(char **r, int x_tag, const void *x, const char* cs);

extern int p1788_bar_exactToInterval(int r_tag, void *r, const char* s);

extern int p1788_dec_exactToDecoratedInterval(int r_tag, void *r, const char* s);

extern int p1788_bar_intervalToExact(char **r, int x_tag, const void *x);
extern int p1788_dec_intervalToExact(char **r, int x_tag, const void *x);

