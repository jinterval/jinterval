#include <mpfi.h>

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

extern int mpfi_p1788_check_range (mpfi_ptr rop, int t);
extern int mpfi_p1788_subnormalize (mpfi_ptr rop, int t);
extern int mpfi_p1788_empty (mpfi_ptr rop);
extern int mpfi_p1788_entire (mpfi_ptr rop);
extern int mpfi_p1788_numsToInterval (mpfi_ptr rop, mpfr_srcptr l, mpfr_srcptr u);
extern int mpfi_p1788_numsDecToInterval (mpfi_ptr rop, mpfr_srcptr l, mpfr_srcptr u, int dec);
extern int mpfi_p1788_textToInterval(mpfi_ptr rop, const char *cp);
extern int mpfi_p1788_textToDecoratedInterval(mpfi_ptr rop, const char *cp);
extern int mpfi_p1788_exactToInterval (mpfi_ptr rop, const char *cp);
extern int mpfi_p1788_exactToDecoratedInterval (mpfi_ptr rop, const char *cp);
extern int mpfi_p1788_convertType (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_newDec (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_intervalPart (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_setDec (mpfi_ptr rop, mpfi_srcptr op, int dec);
extern int mpfi_p1788_pos (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_neg (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_add (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_sub (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_mul (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_div (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_recip (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_sqrt (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_fma (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2, mpfi_srcptr op3);
extern int mpfi_p1788_sqr (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_pown (mpfi_ptr rop, mpfi_srcptr op, long int n);
extern int mpfi_p1788_pow (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_exp (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_exp2 (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_exp10 (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_log (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_log2 (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_log10 (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_sin (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_cos (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_tan (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_asin (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_acos (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_atan (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_atan2 (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_sinh (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_cosh (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_tanh (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_asinh (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_acosh (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_atanh (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_sign (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_ceil (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_floor (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_trunc (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_roundTiesToEven (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_roundTiesToAway (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_abs (mpfi_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_min (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_max (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_mulRevToPair (mpfi_ptr rop1, mpfi_ptr rop2, mpfi_srcptr b, mpfi_srcptr c);
extern int mpfi_p1788_mulRevToPairSubnormal(mpfi_ptr rop1, mpfi_ptr rop2, mpfi_srcptr b, mpfi_srcptr c);
extern int mpfi_p1788_pownRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x, long int n);
extern int mpfi_p1788_pownRevEntire (mpfi_ptr rop, mpfi_srcptr c, long int n);
extern int mpfi_p1788_sqrRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_sqrRevEntire (mpfi_ptr rop, mpfi_srcptr c);
extern int mpfi_p1788_absRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_absRevEntire (mpfi_ptr rop, mpfi_srcptr c);
extern int mpfi_p1788_sinRev(mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_sinRevEntire(mpfi_ptr rop, mpfi_srcptr c);
extern int mpfi_p1788_cosRev(mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_cosRevEntire(mpfi_ptr rop, mpfi_srcptr c);
extern int mpfi_p1788_tanRev(mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_tanRevEntire(mpfi_ptr rop, mpfi_srcptr c);
extern int mpfi_p1788_coshRev (mpfi_ptr rop, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_coshRevEntire (mpfi_ptr rop, mpfi_srcptr c);
extern int mpfi_p1788_mulRev (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_mulRevEntire (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c);
extern int mpfi_p1788_powRev1 (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_powRev1Entire (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c);
extern int mpfi_p1788_powRev2 (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_powRev2Entire (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c);
extern int mpfi_p1788_atan2Rev1 (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_atan2Rev1Entire (mpfi_ptr rop, mpfi_srcptr b, mpfi_srcptr c);
extern int mpfi_p1788_atan2Rev2 (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c, mpfi_srcptr x);
extern int mpfi_p1788_atan2Rev2Entire (mpfi_ptr rop, mpfi_srcptr a, mpfi_srcptr c);
extern int mpfi_p1788_cancelMinus (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_cancelPlus (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_intersection (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_convexHull (mpfi_ptr rop, mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_inf (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_infSubnormal (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_sup (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_supSubnormal (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_mid (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_midSubnormal (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_midRad (mpfr_ptr mid, mpfr_ptr rad, mpfi_srcptr op);
extern int mpfi_p1788_midRadSubnormal (mpfr_ptr mid, mpfr_ptr rad, mpfi_srcptr op);
extern int mpfi_p1788_rad (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_radSubnormal (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_wid (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_widSubnormal (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_mag (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_magSubnormal (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_mig (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_migSubnormal (mpfr_ptr rop, mpfi_srcptr op);
extern int mpfi_p1788_isValid(mpfi_srcptr op);
extern int mpfi_p1788_isEmpty (mpfi_srcptr op);
extern int mpfi_p1788_isEntire (mpfi_srcptr op);
extern int mpfi_p1788_isNaI (mpfi_srcptr op);
extern int mpfi_p1788_isCommonInterval (mpfi_srcptr op);
extern int mpfi_p1788_isSingleton (mpfi_srcptr op);
extern int mpfi_p1788_isMember(mpfr_srcptr m, mpfi_srcptr x);
extern int mpfi_p1788_equal (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_subset (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_less (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_precedes (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_interior (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_strictLess (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_strictPrecedes (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_disjoint (mpfi_srcptr op1, mpfi_srcptr op2);
extern int mpfi_p1788_overlap (mpfi_srcptr op1, mpfi_srcptr op2);
extern char *mpfi_p1788_intervalToText (mpfi_srcptr x, int dec, const char *cs);
extern char *mpfi_p1788_intervalToExact (mpfi_srcptr x, int dec);
