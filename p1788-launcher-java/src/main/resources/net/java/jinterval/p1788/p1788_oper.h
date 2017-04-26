
#include <assert.h>
#include "p1788.h"



#define p1788_bar_isValid_F(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isValid(TAG_f, (x)))

#define p1788_bar_isValid_D(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isValid(TAG_d, (x)))

#define p1788_bar_isValid_L(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isValid(TAG_l, (x)))

#define p1788_dec_isValid_F(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isValid(TAG_f, (x)))

#define p1788_dec_isValid_D(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isValid(TAG_d, (x)))

#define p1788_dec_isValid_L(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isValid(TAG_l, (x)))


#define p1788_bar_empty_F(r) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_empty(TAG_f, (r)))

#define p1788_bar_empty_D(r) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_empty(TAG_d, (r)))

#define p1788_bar_empty_L(r) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_empty(TAG_l, (r)))

#define p1788_dec_empty_F(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_empty(TAG_f, (r)))

#define p1788_dec_empty_D(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_empty(TAG_d, (r)))

#define p1788_dec_empty_L(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_empty(TAG_l, (r)))


#define p1788_bar_entire_F(r) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_entire(TAG_f, (r)))

#define p1788_bar_entire_D(r) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_entire(TAG_d, (r)))

#define p1788_bar_entire_L(r) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_entire(TAG_l, (r)))

#define p1788_dec_entire_F(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_entire(TAG_f, (r)))

#define p1788_dec_entire_D(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_entire(TAG_d, (r)))

#define p1788_dec_entire_L(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_entire(TAG_l, (r)))


#define p1788_dec_nai_F(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_nai(TAG_f, (r)))

#define p1788_dec_nai_D(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_nai(TAG_d, (r)))

#define p1788_dec_nai_L(r) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_nai(TAG_l, (r)))


#define p1788_bar_convertType_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convertType(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_convertType_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convertType(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_convertType_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convertType(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_convertType_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convertType(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_convertType_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convertType(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_convertType_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convertType(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_convertType_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convertType(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_convertType_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convertType(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_convertType_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convertType(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_convertType_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convertType(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_convertType_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convertType(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_convertType_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convertType(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_convertType_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convertType(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_convertType_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convertType(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_convertType_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convertType(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_convertType_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convertType(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_convertType_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convertType(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_convertType_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convertType(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_pos_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pos(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_pos_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pos(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_pos_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pos(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_pos_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pos(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_pos_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pos(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_pos_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pos(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_pos_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pos(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_pos_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pos(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_pos_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pos(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_pos_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pos(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_pos_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pos(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_pos_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pos(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_pos_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pos(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_pos_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pos(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_pos_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pos(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_pos_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pos(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_pos_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pos(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_pos_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pos(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_neg_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_neg(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_neg_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_neg(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_neg_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_neg(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_neg_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_neg(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_neg_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_neg(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_neg_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_neg(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_neg_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_neg(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_neg_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_neg(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_neg_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_neg(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_neg_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_neg(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_neg_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_neg(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_neg_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_neg(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_neg_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_neg(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_neg_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_neg(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_neg_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_neg(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_neg_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_neg(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_neg_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_neg(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_neg_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_neg(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_add_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_add_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_add_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_add_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_add_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_add_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_add_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_add_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_add_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_add_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_add_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_add_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_add_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_add_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_add_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_add_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_add_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_add_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_add_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_add_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_add_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_add_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_add_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_add_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_add_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_add(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_add_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_add(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_add_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_add(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_add_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_add_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_add_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_add_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_add_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_add_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_add_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_add_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_add_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_add_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_add_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_add_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_add_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_add_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_add_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_add_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_add_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_add_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_add_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_add_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_add_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_add_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_add_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_add_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_add_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_add(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_add_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_add(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_add_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_add(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_sub_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_sub_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_sub_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_sub_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_sub_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_sub_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_sub_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_sub_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_sub_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_sub_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_sub_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_sub_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_sub_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_sub_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_sub_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_sub_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_sub_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_sub_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_sub_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_sub_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_sub_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_sub_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_sub_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_sub_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_sub_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sub(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_sub_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sub(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_sub_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sub(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_sub_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_sub_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_sub_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_sub_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_sub_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_sub_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_sub_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_sub_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_sub_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_sub_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_sub_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_sub_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_sub_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_sub_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_sub_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_sub_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_sub_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_sub_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_sub_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_sub_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_sub_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_sub_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_sub_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_sub_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_sub_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sub(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_sub_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sub(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_sub_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sub(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_mul_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_mul_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_mul_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_mul_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_mul_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_mul_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_mul_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_mul_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_mul_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_mul_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_mul_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_mul_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_mul_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_mul_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_mul_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_mul_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_mul_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_mul_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_mul_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_mul_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_mul_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_mul_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_mul_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_mul_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_mul_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mul(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_mul_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mul(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_mul_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mul(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_mul_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_mul_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_mul_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_mul_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_mul_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_mul_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_mul_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_mul_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_mul_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_mul_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_mul_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_mul_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_mul_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_mul_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_mul_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_mul_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_mul_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_mul_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_mul_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_mul_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_mul_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_mul_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_mul_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_mul_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_mul_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mul(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_mul_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mul(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_mul_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mul(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_div_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_div_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_div_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_div_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_div_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_div_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_div_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_div_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_div_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_div_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_div_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_div_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_div_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_div_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_div_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_div_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_div_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_div_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_div_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_div_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_div_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_div_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_div_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_div_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_div_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_div(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_div_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_div(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_div_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_div(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_div_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_div_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_div_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_div_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_div_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_div_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_div_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_div_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_div_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_div_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_div_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_div_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_div_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_div_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_div_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_div_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_div_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_div_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_div_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_div_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_div_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_div_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_div_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_div_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_div_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_div(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_div_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_div(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_div_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_div(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_recip_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_recip(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_recip_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_recip(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_recip_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_recip(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_recip_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_recip(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_recip_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_recip(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_recip_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_recip(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_recip_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_recip(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_recip_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_recip(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_recip_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_recip(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_recip_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_recip(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_recip_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_recip(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_recip_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_recip(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_recip_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_recip(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_recip_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_recip(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_recip_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_recip(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_recip_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_recip(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_recip_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_recip(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_recip_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_recip(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_sqr_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqr(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_sqr_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqr(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_sqr_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqr(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_sqr_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqr(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_sqr_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqr(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_sqr_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqr(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_sqr_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqr(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_sqr_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqr(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_sqr_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqr(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_sqr_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqr(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_sqr_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqr(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_sqr_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqr(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_sqr_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqr(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_sqr_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqr(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_sqr_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqr(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_sqr_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqr(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_sqr_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqr(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_sqr_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqr(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_sqrt_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrt(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_sqrt_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrt(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_sqrt_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrt(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_sqrt_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrt(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_sqrt_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrt(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_sqrt_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrt(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_sqrt_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrt(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_sqrt_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrt(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_sqrt_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrt(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_sqrt_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrt(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_sqrt_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrt(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_sqrt_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrt(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_sqrt_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrt(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_sqrt_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrt(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_sqrt_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrt(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_sqrt_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrt(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_sqrt_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrt(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_sqrt_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrt(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_fma_FFFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_FFFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_FFFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_FFDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_FFDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_FFDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_FFLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_FFLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_FFLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_f, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_FDFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_FDFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_FDFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_FDDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_FDDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_FDDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_FDLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_FDLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_FDLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_d, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_FLFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_FLFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_FLFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_FLDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_FLDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_FLDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_FLLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_FLLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_FLLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_f, (r), TAG_l, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_DFFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_DFFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_DFFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_DFDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_DFDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_DFDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_DFLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_DFLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_DFLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_f, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_DDFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_DDFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_DDFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_DDDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_DDDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_DDDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_DDLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_DDLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_DDLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_d, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_DLFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_DLFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_DLFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_DLDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_DLDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_DLDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_DLLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_DLLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_DLLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_d, (r), TAG_l, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_LFFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_LFFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_LFFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_LFDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_LFDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_LFDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_LFLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_LFLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_LFLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_f, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_LDFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_LDFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_LDFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_LDDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_LDDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_LDDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_LDLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_LDLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_LDLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_d, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_bar_fma_LLFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_bar_fma_LLFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_bar_fma_LLFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_bar_fma_LLDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_bar_fma_LLDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_bar_fma_LLDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_bar_fma_LLLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_bar_fma_LLLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_bar_fma_LLLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(z)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_fma(TAG_l, (r), TAG_l, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_FFFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_FFFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_FFFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_FFDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_FFDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_FFDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_FFLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_FFLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_FFLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_f, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_FDFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_FDFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_FDFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_FDDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_FDDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_FDDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_FDLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_FDLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_FDLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_d, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_FLFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_FLFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_FLFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_FLDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_FLDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_FLDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_FLLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_FLLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_FLLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_f, (r), TAG_l, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_DFFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_DFFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_DFFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_DFDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_DFDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_DFDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_DFLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_DFLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_DFLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_f, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_DDFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_DDFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_DDFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_DDDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_DDDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_DDDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_DDLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_DDLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_DDLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_d, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_DLFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_DLFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_DLFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_DLDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_DLDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_DLDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_DLLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_DLLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_DLLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_d, (r), TAG_l, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_LFFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_LFFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_LFFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_LFDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_LFDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_LFDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_LFLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_LFLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_LFLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_f, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_LDFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_LDFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_LDFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_LDDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_LDDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_LDDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_LDLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_LDLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_LDLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_d, (x), TAG_l, (y), TAG_l, (z)))

#define p1788_dec_fma_LLFF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_f, (y), TAG_f, (z)))

#define p1788_dec_fma_LLFD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_f, (y), TAG_d, (z)))

#define p1788_dec_fma_LLFL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_f, (y), TAG_l, (z)))

#define p1788_dec_fma_LLDF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_d, (y), TAG_f, (z)))

#define p1788_dec_fma_LLDD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_d, (y), TAG_d, (z)))

#define p1788_dec_fma_LLDL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_d, (y), TAG_l, (z)))

#define p1788_dec_fma_LLLF(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_l, (y), TAG_f, (z)))

#define p1788_dec_fma_LLLD(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_l, (y), TAG_d, (z)))

#define p1788_dec_fma_LLLL(r, x, y, z) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(z)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_fma(TAG_l, (r), TAG_l, (x), TAG_l, (y), TAG_l, (z)))


#define p1788_bar_pown_FFi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pown(TAG_f, (r), TAG_f, (x), *(p)))

#define p1788_bar_pown_FDi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pown(TAG_f, (r), TAG_d, (x), *(p)))

#define p1788_bar_pown_FLi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pown(TAG_f, (r), TAG_l, (x), *(p)))

#define p1788_bar_pown_DFi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pown(TAG_d, (r), TAG_f, (x), *(p)))

#define p1788_bar_pown_DDi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pown(TAG_d, (r), TAG_d, (x), *(p)))

#define p1788_bar_pown_DLi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pown(TAG_d, (r), TAG_l, (x), *(p)))

#define p1788_bar_pown_LFi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pown(TAG_l, (r), TAG_f, (x), *(p)))

#define p1788_bar_pown_LDi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pown(TAG_l, (r), TAG_d, (x), *(p)))

#define p1788_bar_pown_LLi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pown(TAG_l, (r), TAG_l, (x), *(p)))

#define p1788_dec_pown_FFi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pown(TAG_f, (r), TAG_f, (x), *(p)))

#define p1788_dec_pown_FDi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pown(TAG_f, (r), TAG_d, (x), *(p)))

#define p1788_dec_pown_FLi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pown(TAG_f, (r), TAG_l, (x), *(p)))

#define p1788_dec_pown_DFi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pown(TAG_d, (r), TAG_f, (x), *(p)))

#define p1788_dec_pown_DDi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pown(TAG_d, (r), TAG_d, (x), *(p)))

#define p1788_dec_pown_DLi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pown(TAG_d, (r), TAG_l, (x), *(p)))

#define p1788_dec_pown_LFi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pown(TAG_l, (r), TAG_f, (x), *(p)))

#define p1788_dec_pown_LDi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pown(TAG_l, (r), TAG_d, (x), *(p)))

#define p1788_dec_pown_LLi(r, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pown(TAG_l, (r), TAG_l, (x), *(p)))


#define p1788_bar_pow_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_pow_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_pow_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_pow_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_pow_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_pow_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_pow_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_pow_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_pow_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_pow_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_pow_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_pow_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_pow_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_pow_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_pow_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_pow_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_pow_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_pow_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_pow_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_pow_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_pow_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_pow_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_pow_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_pow_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_pow_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pow(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_pow_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pow(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_pow_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pow(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_pow_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_pow_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_pow_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_pow_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_pow_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_pow_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_pow_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_pow_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_pow_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_pow_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_pow_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_pow_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_pow_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_pow_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_pow_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_pow_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_pow_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_pow_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_pow_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_pow_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_pow_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_pow_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_pow_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_pow_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_pow_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pow(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_pow_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pow(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_pow_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pow(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_exp_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_exp_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_exp_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_exp_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_exp_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_exp_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_exp_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_exp_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_exp_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_exp_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_exp_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_exp_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_exp_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_exp_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_exp_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_exp_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_exp_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_exp_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_exp2_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp2(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_exp2_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp2(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_exp2_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp2(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_exp2_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp2(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_exp2_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp2(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_exp2_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp2(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_exp2_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp2(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_exp2_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp2(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_exp2_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp2(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_exp2_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp2(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_exp2_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp2(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_exp2_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp2(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_exp2_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp2(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_exp2_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp2(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_exp2_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp2(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_exp2_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp2(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_exp2_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp2(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_exp2_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp2(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_exp10_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp10(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_exp10_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp10(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_exp10_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp10(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_exp10_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp10(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_exp10_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp10(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_exp10_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp10(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_exp10_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exp10(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_exp10_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exp10(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_exp10_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exp10(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_exp10_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp10(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_exp10_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp10(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_exp10_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp10(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_exp10_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp10(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_exp10_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp10(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_exp10_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp10(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_exp10_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exp10(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_exp10_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exp10(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_exp10_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exp10(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_log_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_log_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_log_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_log_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_log_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_log_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_log_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_log_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_log_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_log_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_log_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_log_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_log_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_log_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_log_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_log_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_log_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_log_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_log2_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log2(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_log2_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log2(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_log2_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log2(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_log2_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log2(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_log2_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log2(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_log2_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log2(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_log2_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log2(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_log2_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log2(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_log2_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log2(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_log2_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log2(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_log2_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log2(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_log2_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log2(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_log2_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log2(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_log2_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log2(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_log2_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log2(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_log2_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log2(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_log2_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log2(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_log2_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log2(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_log10_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log10(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_log10_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log10(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_log10_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log10(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_log10_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log10(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_log10_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log10(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_log10_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log10(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_log10_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_log10(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_log10_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_log10(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_log10_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_log10(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_log10_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log10(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_log10_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log10(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_log10_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log10(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_log10_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log10(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_log10_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log10(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_log10_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log10(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_log10_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_log10(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_log10_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_log10(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_log10_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_log10(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_sin_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sin(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_sin_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sin(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_sin_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sin(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_sin_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sin(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_sin_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sin(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_sin_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sin(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_sin_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sin(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_sin_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sin(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_sin_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sin(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_sin_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sin(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_sin_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sin(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_sin_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sin(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_sin_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sin(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_sin_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sin(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_sin_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sin(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_sin_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sin(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_sin_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sin(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_sin_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sin(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_cos_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cos(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_cos_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cos(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_cos_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cos(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_cos_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cos(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_cos_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cos(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_cos_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cos(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_cos_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cos(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_cos_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cos(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_cos_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cos(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_cos_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cos(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_cos_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cos(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_cos_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cos(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_cos_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cos(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_cos_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cos(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_cos_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cos(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_cos_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cos(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_cos_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cos(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_cos_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cos(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_tan_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tan(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_tan_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tan(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_tan_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tan(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_tan_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tan(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_tan_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tan(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_tan_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tan(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_tan_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tan(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_tan_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tan(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_tan_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tan(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_tan_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tan(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_tan_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tan(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_tan_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tan(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_tan_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tan(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_tan_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tan(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_tan_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tan(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_tan_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tan(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_tan_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tan(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_tan_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tan(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_asin_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_asin(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_asin_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_asin(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_asin_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_asin(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_asin_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_asin(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_asin_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_asin(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_asin_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_asin(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_asin_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_asin(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_asin_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_asin(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_asin_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_asin(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_asin_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_asin(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_asin_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_asin(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_asin_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_asin(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_asin_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_asin(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_asin_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_asin(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_asin_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_asin(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_asin_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_asin(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_asin_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_asin(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_asin_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_asin(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_acos_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_acos(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_acos_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_acos(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_acos_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_acos(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_acos_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_acos(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_acos_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_acos(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_acos_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_acos(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_acos_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_acos(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_acos_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_acos(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_acos_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_acos(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_acos_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_acos(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_acos_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_acos(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_acos_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_acos(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_acos_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_acos(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_acos_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_acos(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_acos_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_acos(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_acos_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_acos(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_acos_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_acos(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_acos_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_acos(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_atan_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_atan_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_atan_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_atan_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_atan_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_atan_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_atan_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_atan_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_atan_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_atan_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_atan_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_atan_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_atan_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_atan_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_atan_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_atan_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_atan_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_atan_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_atan2_FFF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_f, (r), TAG_f, (y), TAG_f, (x)))

#define p1788_bar_atan2_FFD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_f, (r), TAG_f, (y), TAG_d, (x)))

#define p1788_bar_atan2_FFL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_f, (r), TAG_f, (y), TAG_l, (x)))

#define p1788_bar_atan2_FDF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_f, (r), TAG_d, (y), TAG_f, (x)))

#define p1788_bar_atan2_FDD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_f, (r), TAG_d, (y), TAG_d, (x)))

#define p1788_bar_atan2_FDL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_f, (r), TAG_d, (y), TAG_l, (x)))

#define p1788_bar_atan2_FLF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_f, (r), TAG_l, (y), TAG_f, (x)))

#define p1788_bar_atan2_FLD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_f, (r), TAG_l, (y), TAG_d, (x)))

#define p1788_bar_atan2_FLL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_f, (r), TAG_l, (y), TAG_l, (x)))

#define p1788_bar_atan2_DFF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_d, (r), TAG_f, (y), TAG_f, (x)))

#define p1788_bar_atan2_DFD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_d, (r), TAG_f, (y), TAG_d, (x)))

#define p1788_bar_atan2_DFL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_d, (r), TAG_f, (y), TAG_l, (x)))

#define p1788_bar_atan2_DDF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_d, (r), TAG_d, (y), TAG_f, (x)))

#define p1788_bar_atan2_DDD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_d, (r), TAG_d, (y), TAG_d, (x)))

#define p1788_bar_atan2_DDL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_d, (r), TAG_d, (y), TAG_l, (x)))

#define p1788_bar_atan2_DLF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_d, (r), TAG_l, (y), TAG_f, (x)))

#define p1788_bar_atan2_DLD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_d, (r), TAG_l, (y), TAG_d, (x)))

#define p1788_bar_atan2_DLL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_d, (r), TAG_l, (y), TAG_l, (x)))

#define p1788_bar_atan2_LFF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_l, (r), TAG_f, (y), TAG_f, (x)))

#define p1788_bar_atan2_LFD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_l, (r), TAG_f, (y), TAG_d, (x)))

#define p1788_bar_atan2_LFL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_l, (r), TAG_f, (y), TAG_l, (x)))

#define p1788_bar_atan2_LDF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_l, (r), TAG_d, (y), TAG_f, (x)))

#define p1788_bar_atan2_LDD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_l, (r), TAG_d, (y), TAG_d, (x)))

#define p1788_bar_atan2_LDL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_l, (r), TAG_d, (y), TAG_l, (x)))

#define p1788_bar_atan2_LLF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2(TAG_l, (r), TAG_l, (y), TAG_f, (x)))

#define p1788_bar_atan2_LLD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2(TAG_l, (r), TAG_l, (y), TAG_d, (x)))

#define p1788_bar_atan2_LLL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2(TAG_l, (r), TAG_l, (y), TAG_l, (x)))

#define p1788_dec_atan2_FFF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_f, (r), TAG_f, (y), TAG_f, (x)))

#define p1788_dec_atan2_FFD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_f, (r), TAG_f, (y), TAG_d, (x)))

#define p1788_dec_atan2_FFL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_f, (r), TAG_f, (y), TAG_l, (x)))

#define p1788_dec_atan2_FDF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_f, (r), TAG_d, (y), TAG_f, (x)))

#define p1788_dec_atan2_FDD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_f, (r), TAG_d, (y), TAG_d, (x)))

#define p1788_dec_atan2_FDL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_f, (r), TAG_d, (y), TAG_l, (x)))

#define p1788_dec_atan2_FLF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_f, (r), TAG_l, (y), TAG_f, (x)))

#define p1788_dec_atan2_FLD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_f, (r), TAG_l, (y), TAG_d, (x)))

#define p1788_dec_atan2_FLL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_f, (r), TAG_l, (y), TAG_l, (x)))

#define p1788_dec_atan2_DFF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_d, (r), TAG_f, (y), TAG_f, (x)))

#define p1788_dec_atan2_DFD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_d, (r), TAG_f, (y), TAG_d, (x)))

#define p1788_dec_atan2_DFL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_d, (r), TAG_f, (y), TAG_l, (x)))

#define p1788_dec_atan2_DDF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_d, (r), TAG_d, (y), TAG_f, (x)))

#define p1788_dec_atan2_DDD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_d, (r), TAG_d, (y), TAG_d, (x)))

#define p1788_dec_atan2_DDL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_d, (r), TAG_d, (y), TAG_l, (x)))

#define p1788_dec_atan2_DLF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_d, (r), TAG_l, (y), TAG_f, (x)))

#define p1788_dec_atan2_DLD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_d, (r), TAG_l, (y), TAG_d, (x)))

#define p1788_dec_atan2_DLL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_d, (r), TAG_l, (y), TAG_l, (x)))

#define p1788_dec_atan2_LFF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_l, (r), TAG_f, (y), TAG_f, (x)))

#define p1788_dec_atan2_LFD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_l, (r), TAG_f, (y), TAG_d, (x)))

#define p1788_dec_atan2_LFL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_l, (r), TAG_f, (y), TAG_l, (x)))

#define p1788_dec_atan2_LDF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_l, (r), TAG_d, (y), TAG_f, (x)))

#define p1788_dec_atan2_LDD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_l, (r), TAG_d, (y), TAG_d, (x)))

#define p1788_dec_atan2_LDL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_l, (r), TAG_d, (y), TAG_l, (x)))

#define p1788_dec_atan2_LLF(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2(TAG_l, (r), TAG_l, (y), TAG_f, (x)))

#define p1788_dec_atan2_LLD(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2(TAG_l, (r), TAG_l, (y), TAG_d, (x)))

#define p1788_dec_atan2_LLL(r, y, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2(TAG_l, (r), TAG_l, (y), TAG_l, (x)))


#define p1788_bar_sinh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinh(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_sinh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinh(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_sinh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinh(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_sinh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinh(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_sinh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinh(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_sinh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinh(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_sinh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinh(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_sinh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinh(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_sinh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinh(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_sinh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinh(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_sinh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinh(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_sinh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinh(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_sinh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinh(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_sinh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinh(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_sinh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinh(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_sinh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinh(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_sinh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinh(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_sinh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinh(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_cosh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosh(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_cosh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosh(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_cosh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosh(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_cosh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosh(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_cosh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosh(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_cosh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosh(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_cosh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosh(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_cosh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosh(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_cosh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosh(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_cosh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosh(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_cosh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosh(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_cosh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosh(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_cosh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosh(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_cosh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosh(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_cosh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosh(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_cosh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosh(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_cosh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosh(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_cosh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosh(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_tanh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanh(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_tanh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanh(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_tanh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanh(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_tanh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanh(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_tanh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanh(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_tanh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanh(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_tanh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanh(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_tanh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanh(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_tanh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanh(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_tanh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanh(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_tanh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanh(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_tanh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanh(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_tanh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanh(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_tanh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanh(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_tanh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanh(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_tanh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanh(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_tanh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanh(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_tanh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanh(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_asinh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_asinh(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_asinh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_asinh(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_asinh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_asinh(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_asinh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_asinh(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_asinh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_asinh(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_asinh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_asinh(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_asinh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_asinh(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_asinh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_asinh(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_asinh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_asinh(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_asinh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_asinh(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_asinh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_asinh(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_asinh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_asinh(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_asinh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_asinh(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_asinh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_asinh(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_asinh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_asinh(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_asinh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_asinh(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_asinh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_asinh(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_asinh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_asinh(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_acosh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_acosh(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_acosh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_acosh(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_acosh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_acosh(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_acosh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_acosh(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_acosh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_acosh(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_acosh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_acosh(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_acosh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_acosh(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_acosh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_acosh(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_acosh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_acosh(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_acosh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_acosh(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_acosh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_acosh(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_acosh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_acosh(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_acosh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_acosh(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_acosh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_acosh(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_acosh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_acosh(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_acosh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_acosh(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_acosh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_acosh(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_acosh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_acosh(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_atanh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atanh(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_atanh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atanh(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_atanh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atanh(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_atanh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atanh(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_atanh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atanh(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_atanh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atanh(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_atanh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atanh(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_atanh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atanh(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_atanh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atanh(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_atanh_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atanh(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_atanh_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atanh(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_atanh_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atanh(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_atanh_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atanh(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_atanh_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atanh(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_atanh_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atanh(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_atanh_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atanh(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_atanh_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atanh(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_atanh_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atanh(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_sign_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sign(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_sign_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sign(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_sign_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sign(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_sign_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sign(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_sign_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sign(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_sign_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sign(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_sign_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sign(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_sign_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sign(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_sign_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sign(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_sign_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sign(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_sign_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sign(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_sign_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sign(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_sign_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sign(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_sign_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sign(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_sign_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sign(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_sign_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sign(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_sign_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sign(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_sign_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sign(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_ceil_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_ceil(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_ceil_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_ceil(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_ceil_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_ceil(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_ceil_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_ceil(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_ceil_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_ceil(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_ceil_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_ceil(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_ceil_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_ceil(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_ceil_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_ceil(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_ceil_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_ceil(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_ceil_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_ceil(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_ceil_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_ceil(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_ceil_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_ceil(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_ceil_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_ceil(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_ceil_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_ceil(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_ceil_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_ceil(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_ceil_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_ceil(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_ceil_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_ceil(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_ceil_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_ceil(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_floor_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_floor(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_floor_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_floor(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_floor_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_floor(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_floor_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_floor(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_floor_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_floor(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_floor_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_floor(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_floor_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_floor(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_floor_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_floor(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_floor_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_floor(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_floor_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_floor(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_floor_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_floor(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_floor_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_floor(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_floor_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_floor(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_floor_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_floor(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_floor_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_floor(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_floor_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_floor(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_floor_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_floor(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_floor_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_floor(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_trunc_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_trunc(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_trunc_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_trunc(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_trunc_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_trunc(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_trunc_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_trunc(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_trunc_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_trunc(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_trunc_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_trunc(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_trunc_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_trunc(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_trunc_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_trunc(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_trunc_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_trunc(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_trunc_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_trunc(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_trunc_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_trunc(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_trunc_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_trunc(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_trunc_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_trunc(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_trunc_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_trunc(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_trunc_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_trunc(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_trunc_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_trunc(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_trunc_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_trunc(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_trunc_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_trunc(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_roundTiesToEven_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_roundTiesToEven(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_roundTiesToEven_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_roundTiesToEven(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_roundTiesToEven_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_roundTiesToEven(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_roundTiesToEven_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_roundTiesToEven(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_roundTiesToEven_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_roundTiesToEven(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_roundTiesToEven_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_roundTiesToEven(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_roundTiesToEven_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_roundTiesToEven(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_roundTiesToEven_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_roundTiesToEven(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_roundTiesToEven_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_roundTiesToEven(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_roundTiesToEven_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_roundTiesToEven(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_roundTiesToEven_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_roundTiesToEven(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_roundTiesToEven_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_roundTiesToEven(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_roundTiesToEven_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_roundTiesToEven(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_roundTiesToEven_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_roundTiesToEven(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_roundTiesToEven_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_roundTiesToEven(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_roundTiesToEven_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_roundTiesToEven(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_roundTiesToEven_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_roundTiesToEven(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_roundTiesToEven_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_roundTiesToEven(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_roundTiesToAway_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_roundTiesToAway(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_roundTiesToAway_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_roundTiesToAway(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_roundTiesToAway_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_roundTiesToAway(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_roundTiesToAway_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_roundTiesToAway(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_roundTiesToAway_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_roundTiesToAway(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_roundTiesToAway_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_roundTiesToAway(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_roundTiesToAway_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_roundTiesToAway(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_roundTiesToAway_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_roundTiesToAway(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_roundTiesToAway_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_roundTiesToAway(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_roundTiesToAway_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_roundTiesToAway(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_roundTiesToAway_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_roundTiesToAway(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_roundTiesToAway_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_roundTiesToAway(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_roundTiesToAway_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_roundTiesToAway(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_roundTiesToAway_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_roundTiesToAway(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_roundTiesToAway_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_roundTiesToAway(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_roundTiesToAway_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_roundTiesToAway(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_roundTiesToAway_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_roundTiesToAway(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_roundTiesToAway_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_roundTiesToAway(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_abs_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_abs(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_abs_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_abs(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_abs_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_abs(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_abs_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_abs(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_abs_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_abs(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_abs_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_abs(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_abs_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_abs(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_abs_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_abs(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_abs_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_abs(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_abs_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_abs(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_abs_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_abs(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_abs_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_abs(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_abs_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_abs(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_abs_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_abs(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_abs_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_abs(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_abs_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_abs(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_abs_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_abs(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_abs_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_abs(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_min_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_min_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_min_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_min_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_min_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_min_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_min_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_min_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_min_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_min_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_min_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_min_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_min_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_min_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_min_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_min_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_min_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_min_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_min_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_min_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_min_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_min_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_min_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_min_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_min_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_min(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_min_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_min(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_min_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_min(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_min_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_min_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_min_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_min_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_min_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_min_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_min_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_min_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_min_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_min_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_min_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_min_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_min_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_min_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_min_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_min_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_min_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_min_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_min_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_min_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_min_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_min_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_min_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_min_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_min_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_min(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_min_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_min(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_min_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_min(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_max_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_max_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_max_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_max_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_max_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_max_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_max_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_max_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_max_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_max_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_max_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_max_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_max_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_max_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_max_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_max_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_max_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_max_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_max_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_max_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_max_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_max_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_max_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_max_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_max_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_max(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_max_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_max(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_max_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_max(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_max_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_max_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_max_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_max_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_max_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_max_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_max_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_max_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_max_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_max_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_max_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_max_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_max_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_max_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_max_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_max_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_max_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_max_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_max_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_max_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_max_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_max_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_max_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_max_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_max_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_max(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_max_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_max(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_max_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_max(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_mulRevToPair_FFFF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_FFFD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_FFFL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_FFDF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_FFDD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_FFDL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_FFLF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_FFLD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_FFLL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B32) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_f, (r1), (r2), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_DDFF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_DDFD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_DDFL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_DDDF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_DDDD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_DDDL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_DDLF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_DDLD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_DDLL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B64) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_d, (r1), (r2), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_LLFF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_LLFD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_LLFL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_LLDF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_LLDD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_LLDL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_mulRevToPair_LLLF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_mulRevToPair_LLLD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_mulRevToPair_LLLL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(BARE_INFSUP_B80) && sizeof(*(r2)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevToPair(TAG_l, (r1), (r2), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_FFFF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_FFFD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_FFFL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_FFDF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_FFDD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_FFDL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_FFLF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_FFLD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_FFLL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_f, (r1), (r2), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_DDFF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_DDFD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_DDFL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_DDDF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_DDDD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_DDDL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_DDLF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_DDLD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_DDLL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_d, (r1), (r2), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_LLFF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_LLFD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_LLFL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_LLDF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_LLDD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_LLDL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_mulRevToPair_LLLF(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_mulRevToPair_LLLD(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_mulRevToPair_LLLL(r1, r2, b, c) \
  (assert(sizeof(*(r1)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(r2)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevToPair(TAG_l, (r1), (r2), TAG_l, (b), TAG_l, (c)))


#define p1788_bar_sqrRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_sqrRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_sqrRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_sqrRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_sqrRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_sqrRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_sqrRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_sqrRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_bar_sqrRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_bar_sqrRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_bar_sqrRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_bar_sqrRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_bar_sqrRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_bar_sqrRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sqrRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_bar_sqrRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sqrRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_bar_sqrRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sqrRevEntire(TAG_l, (r), TAG_l, (c)))

#define p1788_dec_sqrRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_dec_sqrRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_dec_sqrRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_dec_sqrRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_dec_sqrRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_dec_sqrRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_dec_sqrRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sqrRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_dec_sqrRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sqrRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_dec_sqrRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sqrRevEntire(TAG_l, (r), TAG_l, (c)))


#define p1788_bar_absRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_absRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_absRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_absRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_absRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_absRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_absRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_absRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_absRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_absRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_absRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_absRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_absRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_absRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_absRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_absRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_absRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_absRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_absRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_absRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_absRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_absRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_absRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_absRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_absRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_absRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_absRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_absRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_absRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_absRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_absRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_absRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_absRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_absRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_absRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_absRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_absRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_absRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_absRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_absRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_absRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_absRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_absRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_absRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_absRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_absRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_absRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_absRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_absRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_absRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_absRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_absRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_absRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_absRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_absRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_bar_absRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_bar_absRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_bar_absRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_bar_absRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_bar_absRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_bar_absRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_absRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_bar_absRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_absRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_bar_absRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_absRevEntire(TAG_l, (r), TAG_l, (c)))

#define p1788_dec_absRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_dec_absRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_dec_absRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_dec_absRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_dec_absRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_dec_absRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_dec_absRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_absRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_dec_absRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_absRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_dec_absRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_absRevEntire(TAG_l, (r), TAG_l, (c)))


#define p1788_bar_pownRev_FFFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_f, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_FFDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_f, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_FFLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_f, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_FDFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_d, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_FDDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_d, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_FDLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_d, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_FLFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_l, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_FLDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_l, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_FLLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_f, (r), TAG_l, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_DFFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_f, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_DFDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_f, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_DFLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_f, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_DDFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_d, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_DDDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_d, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_DDLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_d, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_DLFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_l, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_DLDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_l, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_DLLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_d, (r), TAG_l, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_LFFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_f, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_LFDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_f, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_LFLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_f, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_LDFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_d, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_LDDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_d, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_LDLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_d, (c), TAG_l, (x), *(p)))

#define p1788_bar_pownRev_LLFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_l, (c), TAG_f, (x), *(p)))

#define p1788_bar_pownRev_LLDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_l, (c), TAG_d, (x), *(p)))

#define p1788_bar_pownRev_LLLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRev(TAG_l, (r), TAG_l, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_FFFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_f, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_FFDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_f, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_FFLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_f, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_FDFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_d, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_FDDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_d, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_FDLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_d, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_FLFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_l, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_FLDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_l, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_FLLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_f, (r), TAG_l, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_DFFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_f, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_DFDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_f, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_DFLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_f, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_DDFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_d, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_DDDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_d, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_DDLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_d, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_DLFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_l, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_DLDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_l, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_DLLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_d, (r), TAG_l, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_LFFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_f, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_LFDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_f, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_LFLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_f, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_LDFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_d, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_LDDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_d, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_LDLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_d, (c), TAG_l, (x), *(p)))

#define p1788_dec_pownRev_LLFi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_l, (c), TAG_f, (x), *(p)))

#define p1788_dec_pownRev_LLDi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_l, (c), TAG_d, (x), *(p)))

#define p1788_dec_pownRev_LLLi(r, c, x, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRev(TAG_l, (r), TAG_l, (c), TAG_l, (x), *(p)))


#define p1788_bar_pownRev_FFi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRevEntire(TAG_f, (r), TAG_f, (c), *(p)))

#define p1788_bar_pownRev_FDi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRevEntire(TAG_f, (r), TAG_d, (c), *(p)))

#define p1788_bar_pownRev_FLi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRevEntire(TAG_f, (r), TAG_l, (c), *(p)))

#define p1788_bar_pownRev_DFi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRevEntire(TAG_d, (r), TAG_f, (c), *(p)))

#define p1788_bar_pownRev_DDi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRevEntire(TAG_d, (r), TAG_d, (c), *(p)))

#define p1788_bar_pownRev_DLi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRevEntire(TAG_d, (r), TAG_l, (c), *(p)))

#define p1788_bar_pownRev_LFi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_pownRevEntire(TAG_l, (r), TAG_f, (c), *(p)))

#define p1788_bar_pownRev_LDi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_pownRevEntire(TAG_l, (r), TAG_d, (c), *(p)))

#define p1788_bar_pownRev_LLi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_pownRevEntire(TAG_l, (r), TAG_l, (c), *(p)))

#define p1788_dec_pownRev_FFi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRevEntire(TAG_f, (r), TAG_f, (c), *(p)))

#define p1788_dec_pownRev_FDi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRevEntire(TAG_f, (r), TAG_d, (c), *(p)))

#define p1788_dec_pownRev_FLi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRevEntire(TAG_f, (r), TAG_l, (c), *(p)))

#define p1788_dec_pownRev_DFi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRevEntire(TAG_d, (r), TAG_f, (c), *(p)))

#define p1788_dec_pownRev_DDi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRevEntire(TAG_d, (r), TAG_d, (c), *(p)))

#define p1788_dec_pownRev_DLi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRevEntire(TAG_d, (r), TAG_l, (c), *(p)))

#define p1788_dec_pownRev_LFi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_pownRevEntire(TAG_l, (r), TAG_f, (c), *(p)))

#define p1788_dec_pownRev_LDi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_pownRevEntire(TAG_l, (r), TAG_d, (c), *(p)))

#define p1788_dec_pownRev_LLi(r, c, p) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_pownRevEntire(TAG_l, (r), TAG_l, (c), *(p)))


#define p1788_bar_sinRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_sinRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_sinRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_sinRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_sinRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_sinRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_sinRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_sinRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_sinRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_sinRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_sinRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_sinRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_sinRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_sinRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_sinRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_sinRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_sinRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_sinRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_sinRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_sinRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_sinRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_sinRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_sinRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_sinRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_sinRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_sinRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_sinRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_sinRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_sinRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_sinRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_sinRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_sinRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_sinRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_sinRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_sinRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_sinRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_sinRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_sinRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_sinRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_sinRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_sinRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_sinRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_sinRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_sinRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_sinRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_sinRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_sinRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_sinRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_sinRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_sinRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_sinRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_sinRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_sinRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_sinRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_sinRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_bar_sinRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_bar_sinRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_bar_sinRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_bar_sinRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_bar_sinRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_bar_sinRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sinRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_bar_sinRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sinRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_bar_sinRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sinRevEntire(TAG_l, (r), TAG_l, (c)))

#define p1788_dec_sinRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_dec_sinRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_dec_sinRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_dec_sinRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_dec_sinRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_dec_sinRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_dec_sinRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sinRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_dec_sinRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sinRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_dec_sinRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sinRevEntire(TAG_l, (r), TAG_l, (c)))


#define p1788_bar_cosRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_cosRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_cosRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_cosRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_cosRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_cosRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_cosRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_cosRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_cosRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_cosRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_cosRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_cosRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_cosRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_cosRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_cosRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_cosRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_cosRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_cosRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_cosRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_cosRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_cosRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_cosRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_cosRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_cosRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_cosRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_cosRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_cosRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_cosRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_cosRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_cosRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_cosRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_cosRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_cosRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_cosRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_cosRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_cosRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_cosRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_cosRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_cosRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_cosRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_cosRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_cosRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_cosRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_cosRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_cosRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_cosRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_cosRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_cosRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_cosRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_cosRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_cosRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_cosRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_cosRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_cosRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_cosRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_bar_cosRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_bar_cosRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_bar_cosRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_bar_cosRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_bar_cosRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_bar_cosRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cosRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_bar_cosRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cosRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_bar_cosRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cosRevEntire(TAG_l, (r), TAG_l, (c)))

#define p1788_dec_cosRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_dec_cosRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_dec_cosRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_dec_cosRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_dec_cosRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_dec_cosRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_dec_cosRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cosRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_dec_cosRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cosRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_dec_cosRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cosRevEntire(TAG_l, (r), TAG_l, (c)))


#define p1788_bar_tanRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_tanRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_tanRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_tanRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_tanRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_tanRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_tanRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_tanRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_tanRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_tanRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_tanRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_tanRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_tanRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_tanRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_tanRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_tanRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_tanRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_tanRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_tanRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_tanRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_tanRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_tanRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_tanRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_tanRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_tanRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_tanRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_tanRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_tanRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_tanRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_tanRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_tanRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_tanRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_tanRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_tanRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_tanRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_tanRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_tanRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_tanRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_tanRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_tanRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_tanRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_tanRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_tanRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_tanRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_tanRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_tanRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_tanRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_tanRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_tanRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_tanRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_tanRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_tanRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_tanRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_tanRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_tanRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_bar_tanRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_bar_tanRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_bar_tanRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_bar_tanRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_bar_tanRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_bar_tanRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_tanRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_bar_tanRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_tanRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_bar_tanRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_tanRevEntire(TAG_l, (r), TAG_l, (c)))

#define p1788_dec_tanRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_dec_tanRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_dec_tanRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_dec_tanRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_dec_tanRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_dec_tanRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_dec_tanRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_tanRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_dec_tanRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_tanRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_dec_tanRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_tanRevEntire(TAG_l, (r), TAG_l, (c)))


#define p1788_bar_coshRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_coshRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_coshRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_coshRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_coshRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_coshRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_coshRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_coshRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_coshRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_coshRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_coshRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_coshRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_coshRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_coshRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_coshRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_coshRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_coshRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_coshRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_coshRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_coshRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_coshRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_coshRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_coshRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_coshRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_coshRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_coshRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_coshRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_coshRev_FFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_coshRev_FFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_coshRev_FFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_coshRev_FDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_coshRev_FDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_coshRev_FDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_coshRev_FLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_coshRev_FLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_coshRev_FLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_f, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_coshRev_DFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_coshRev_DFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_coshRev_DFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_coshRev_DDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_coshRev_DDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_coshRev_DDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_coshRev_DLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_coshRev_DLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_coshRev_DLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_d, (r), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_coshRev_LFF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_coshRev_LFD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_coshRev_LFL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_coshRev_LDF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_coshRev_LDD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_coshRev_LDL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_coshRev_LLF(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_coshRev_LLD(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_coshRev_LLL(r, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRev(TAG_l, (r), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_coshRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_bar_coshRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_bar_coshRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_bar_coshRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_bar_coshRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_bar_coshRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_bar_coshRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_coshRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_bar_coshRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_coshRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_bar_coshRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_coshRevEntire(TAG_l, (r), TAG_l, (c)))

#define p1788_dec_coshRev_FF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRevEntire(TAG_f, (r), TAG_f, (c)))

#define p1788_dec_coshRev_FD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRevEntire(TAG_f, (r), TAG_d, (c)))

#define p1788_dec_coshRev_FL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRevEntire(TAG_f, (r), TAG_l, (c)))

#define p1788_dec_coshRev_DF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRevEntire(TAG_d, (r), TAG_f, (c)))

#define p1788_dec_coshRev_DD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRevEntire(TAG_d, (r), TAG_d, (c)))

#define p1788_dec_coshRev_DL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRevEntire(TAG_d, (r), TAG_l, (c)))

#define p1788_dec_coshRev_LF(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_coshRevEntire(TAG_l, (r), TAG_f, (c)))

#define p1788_dec_coshRev_LD(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_coshRevEntire(TAG_l, (r), TAG_d, (c)))

#define p1788_dec_coshRev_LL(r, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_coshRevEntire(TAG_l, (r), TAG_l, (c)))


#define p1788_bar_mulRev_FFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_FLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_FLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_FLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_DLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_DLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_DLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_mulRev_LLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_mulRev_LLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_mulRev_LLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRev(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_FLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_FLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_FLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_DLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_DLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_DLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_mulRev_LLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_mulRev_LLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_mulRev_LLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRev(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_mulRev_FFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_mulRev_FFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_mulRev_FFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_mulRev_FDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_mulRev_FDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_mulRev_FDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_mulRev_FLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_mulRev_FLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_mulRev_FLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_f, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_mulRev_DFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_mulRev_DFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_mulRev_DFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_mulRev_DDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_mulRev_DDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_mulRev_DDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_mulRev_DLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_mulRev_DLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_mulRev_DLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_d, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_mulRev_LFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_mulRev_LFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_mulRev_LFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_mulRev_LDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_mulRev_LDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_mulRev_LDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_mulRev_LLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_mulRev_LLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_mulRev_LLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mulRevEntire(TAG_l, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_mulRev_FFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_mulRev_FFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_mulRev_FFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_mulRev_FDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_mulRev_FDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_mulRev_FDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_mulRev_FLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_mulRev_FLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_mulRev_FLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_f, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_mulRev_DFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_mulRev_DFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_mulRev_DFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_mulRev_DDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_mulRev_DDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_mulRev_DDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_mulRev_DLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_mulRev_DLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_mulRev_DLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_d, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_mulRev_LFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_mulRev_LFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_mulRev_LFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_mulRev_LDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_mulRev_LDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_mulRev_LDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_mulRev_LLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_mulRev_LLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_mulRev_LLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mulRevEntire(TAG_l, (r), TAG_l, (b), TAG_l, (c)))


#define p1788_bar_powRev1_FFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_FLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_FLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_FLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_DLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_DLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_DLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev1_LLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev1_LLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev1_LLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_FLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_FLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_FLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_DLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_DLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_DLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev1_LLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev1_LLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev1_LLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_powRev1_FFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_powRev1_FFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_powRev1_FFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_powRev1_FDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_powRev1_FDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_powRev1_FDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_powRev1_FLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_powRev1_FLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_powRev1_FLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_f, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_powRev1_DFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_powRev1_DFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_powRev1_DFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_powRev1_DDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_powRev1_DDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_powRev1_DDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_powRev1_DLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_powRev1_DLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_powRev1_DLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_d, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_powRev1_LFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_powRev1_LFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_powRev1_LFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_powRev1_LDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_powRev1_LDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_powRev1_LDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_powRev1_LLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_powRev1_LLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_powRev1_LLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev1Entire(TAG_l, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_powRev1_FFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_powRev1_FFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_powRev1_FFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_powRev1_FDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_powRev1_FDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_powRev1_FDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_powRev1_FLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_powRev1_FLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_powRev1_FLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_f, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_powRev1_DFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_powRev1_DFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_powRev1_DFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_powRev1_DDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_powRev1_DDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_powRev1_DDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_powRev1_DLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_powRev1_DLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_powRev1_DLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_d, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_powRev1_LFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_powRev1_LFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_powRev1_LFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_powRev1_LDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_powRev1_LDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_powRev1_LDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_powRev1_LLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_powRev1_LLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_powRev1_LLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev1Entire(TAG_l, (r), TAG_l, (b), TAG_l, (c)))


#define p1788_bar_powRev2_FFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_FLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_FLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_FLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_DLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_DLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_DLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_powRev2_LLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_powRev2_LLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_powRev2_LLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_FLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_FLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_FLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_DLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_DLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_DLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_powRev2_LLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_powRev2_LLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_powRev2_LLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_powRev2_FFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_bar_powRev2_FFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_bar_powRev2_FFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_bar_powRev2_FDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_bar_powRev2_FDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_bar_powRev2_FDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_bar_powRev2_FLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_bar_powRev2_FLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_bar_powRev2_FLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_f, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_bar_powRev2_DFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_bar_powRev2_DFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_bar_powRev2_DFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_bar_powRev2_DDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_bar_powRev2_DDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_bar_powRev2_DDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_bar_powRev2_DLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_bar_powRev2_DLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_bar_powRev2_DLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_d, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_bar_powRev2_LFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_bar_powRev2_LFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_bar_powRev2_LFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_bar_powRev2_LDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_bar_powRev2_LDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_bar_powRev2_LDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_bar_powRev2_LLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_bar_powRev2_LLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_bar_powRev2_LLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_powRev2Entire(TAG_l, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_dec_powRev2_FFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_dec_powRev2_FFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_dec_powRev2_FFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_dec_powRev2_FDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_dec_powRev2_FDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_dec_powRev2_FDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_dec_powRev2_FLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_dec_powRev2_FLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_dec_powRev2_FLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_f, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_dec_powRev2_DFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_dec_powRev2_DFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_dec_powRev2_DFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_dec_powRev2_DDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_dec_powRev2_DDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_dec_powRev2_DDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_dec_powRev2_DLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_dec_powRev2_DLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_dec_powRev2_DLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_d, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_dec_powRev2_LFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_dec_powRev2_LFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_dec_powRev2_LFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_dec_powRev2_LDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_dec_powRev2_LDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_dec_powRev2_LDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_dec_powRev2_LLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_dec_powRev2_LLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_dec_powRev2_LLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_powRev2Entire(TAG_l, (r), TAG_l, (a), TAG_l, (c)))


#define p1788_bar_atan2Rev1_FFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_FLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_FLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_FLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_DLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_DLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_DLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev1_LLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev1_LLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev1_LLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_FLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_FLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_FLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_f, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_DLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_DLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_DLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_d, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LFFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LFFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LFFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LFDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LFDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LFDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LFLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LFLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LFLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_f, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LDFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LDFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LDFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LDDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LDDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LDDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LDLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LDLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LDLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_d, (b), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LLFF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LLFD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LLFL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LLDF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LLDD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LLDL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev1_LLLF(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev1_LLLD(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev1_LLLL(r, b, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1(TAG_l, (r), TAG_l, (b), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_atan2Rev1_FFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_FFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_FFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_FDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_FDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_FDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_FLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_FLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_FLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_f, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_DFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_DFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_DFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_DDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_DDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_DDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_DLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_DLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_DLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_d, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_LFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_LFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_LFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_LDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_LDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_LDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_bar_atan2Rev1_LLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_bar_atan2Rev1_LLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_bar_atan2Rev1_LLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev1Entire(TAG_l, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_FFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_FFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_FFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_FDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_FDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_FDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_FLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_FLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_FLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_f, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_DFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_DFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_DFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_DDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_DDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_DDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_DLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_DLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_DLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_d, (r), TAG_l, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_LFF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_f, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_LFD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_f, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_LFL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_f, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_LDF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_d, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_LDD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_d, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_LDL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_d, (b), TAG_l, (c)))

#define p1788_dec_atan2Rev1_LLF(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_l, (b), TAG_f, (c)))

#define p1788_dec_atan2Rev1_LLD(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_l, (b), TAG_d, (c)))

#define p1788_dec_atan2Rev1_LLL(r, b, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev1Entire(TAG_l, (r), TAG_l, (b), TAG_l, (c)))


#define p1788_bar_atan2Rev2_FFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_FLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_FLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_FLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_DLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_DLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_DLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_bar_atan2Rev2_LLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_bar_atan2Rev2_LLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_bar_atan2Rev2_LLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_FLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_FLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_FLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_f, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_DLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_DLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_DLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_d, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LFFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LFFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LFFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LFDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LFDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LFDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LFLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LFLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LFLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_f, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LDFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LDFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LDFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LDDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LDDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LDDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LDLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LDLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LDLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_d, (a), TAG_l, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LLFF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LLFD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LLFL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_f, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LLDF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LLDD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LLDL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_d, (c), TAG_l, (x)))

#define p1788_dec_atan2Rev2_LLLF(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_f, (x)))

#define p1788_dec_atan2Rev2_LLLD(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_d, (x)))

#define p1788_dec_atan2Rev2_LLLL(r, a, c, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2(TAG_l, (r), TAG_l, (a), TAG_l, (c), TAG_l, (x)))


#define p1788_bar_atan2Rev2_FFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_FFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_FFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_FDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_FDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_FDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_FLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_FLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_FLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_f, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_DFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_DFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_DFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_DDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_DDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_DDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_DLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_DLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_DLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_d, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_LFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_LFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_LFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_LDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_LDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_LDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_bar_atan2Rev2_LLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_bar_atan2Rev2_LLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_bar_atan2Rev2_LLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(c)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_atan2Rev2Entire(TAG_l, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_FFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_FFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_FFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_FDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_FDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_FDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_FLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_FLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_FLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_f, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_DFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_DFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_DFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_DDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_DDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_DDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_DLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_DLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_DLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_d, (r), TAG_l, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_LFF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_f, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_LFD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_f, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_LFL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_f, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_LDF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_d, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_LDD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_d, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_LDL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_d, (a), TAG_l, (c)))

#define p1788_dec_atan2Rev2_LLF(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_l, (a), TAG_f, (c)))

#define p1788_dec_atan2Rev2_LLD(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_l, (a), TAG_d, (c)))

#define p1788_dec_atan2Rev2_LLL(r, a, c) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(c)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_atan2Rev2Entire(TAG_l, (r), TAG_l, (a), TAG_l, (c)))


#define p1788_bar_cancelMinus_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_cancelMinus_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_cancelMinus_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_cancelMinus_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelMinus(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_cancelMinus_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_cancelMinus_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_cancelMinus_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelMinus(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_cancelPlus_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_cancelPlus_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_cancelPlus_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_cancelPlus_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_cancelPlus(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_cancelPlus_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_cancelPlus_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_cancelPlus_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_cancelPlus(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_intersection_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_intersection_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_intersection_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_intersection_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_intersection_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_intersection_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_intersection_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_intersection_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_intersection_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_intersection_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_intersection_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_intersection_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_intersection_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_intersection_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_intersection_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_intersection_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_intersection_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_intersection_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_intersection_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_intersection_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_intersection_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_intersection_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_intersection_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_intersection_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_intersection_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intersection(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_intersection_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intersection(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_intersection_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intersection(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_intersection_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_intersection_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_intersection_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_intersection_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_intersection_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_intersection_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_intersection_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_intersection_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_intersection_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_intersection_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_intersection_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_intersection_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_intersection_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_intersection_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_intersection_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_intersection_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_intersection_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_intersection_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_intersection_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_intersection_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_intersection_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_intersection_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_intersection_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_intersection_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_intersection_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intersection(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_intersection_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intersection(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_intersection_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intersection(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_convexHull_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_convexHull_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_convexHull_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_convexHull_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_convexHull_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_convexHull_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_convexHull_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_convexHull_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_convexHull_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_convexHull_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_convexHull_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_convexHull_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_convexHull_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_convexHull_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_convexHull_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_convexHull_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_convexHull_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_convexHull_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_bar_convexHull_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_bar_convexHull_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_bar_convexHull_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_bar_convexHull_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_bar_convexHull_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_bar_convexHull_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_bar_convexHull_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_bar_convexHull_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_bar_convexHull_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80) && sizeof(*(y)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_convexHull(TAG_l, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_convexHull_FFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_convexHull_FFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_convexHull_FFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_convexHull_FDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_convexHull_FDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_convexHull_FDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_convexHull_FLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_convexHull_FLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_convexHull_FLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_f, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_convexHull_DFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_convexHull_DFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_convexHull_DFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_convexHull_DDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_convexHull_DDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_convexHull_DDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_convexHull_DLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_convexHull_DLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_convexHull_DLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_d, (r), TAG_l, (x), TAG_l, (y)))

#define p1788_dec_convexHull_LFF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_f, (x), TAG_f, (y)))

#define p1788_dec_convexHull_LFD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_f, (x), TAG_d, (y)))

#define p1788_dec_convexHull_LFL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_f, (x), TAG_l, (y)))

#define p1788_dec_convexHull_LDF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_d, (x), TAG_f, (y)))

#define p1788_dec_convexHull_LDD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_d, (x), TAG_d, (y)))

#define p1788_dec_convexHull_LDL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_d, (x), TAG_l, (y)))

#define p1788_dec_convexHull_LLF(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_l, (x), TAG_f, (y)))

#define p1788_dec_convexHull_LLD(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_l, (x), TAG_d, (y)))

#define p1788_dec_convexHull_LLL(r, x, y) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(y)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_convexHull(TAG_l, (r), TAG_l, (x), TAG_l, (y)))


#define p1788_bar_numsToInterval_Fff(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_f, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Ffd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_f, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Ffl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_f, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Fdf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_d, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Fdd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_d, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Fdl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_d, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Flf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_l, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Fld(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_l, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Fll(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_f, (r), TAG_l, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Dff(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_f, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Dfd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_f, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Dfl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_f, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Ddf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_d, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Ddd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_d, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Ddl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_d, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Dlf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_l, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Dld(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_l, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Dll(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_d, (r), TAG_l, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Lff(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_f, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Lfd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_f, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Lfl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_f, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Ldf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_d, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Ldd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_d, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Ldl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_d, (l), TAG_l, (u)))

#define p1788_bar_numsToInterval_Llf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_l, (l), TAG_f, (u)))

#define p1788_bar_numsToInterval_Lld(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_l, (l), TAG_d, (u)))

#define p1788_bar_numsToInterval_Lll(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_bar_numsToInterval(TAG_l, (r), TAG_l, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Fff(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_f, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Ffd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_f, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Ffl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_f, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Fdf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_d, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Fdd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_d, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Fdl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_d, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Flf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_l, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Fld(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_l, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Fll(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_f, (r), TAG_l, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Dff(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_f, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Dfd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_f, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Dfl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_f, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Ddf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_d, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Ddd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_d, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Ddl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_d, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Dlf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_l, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Dld(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_l, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Dll(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_d, (r), TAG_l, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Lff(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_f, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Lfd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_f, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Lfl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_f, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Ldf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_d, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Ldd(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_d, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Ldl(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_d, (l), TAG_l, (u)))

#define p1788_dec_numsToInterval_Llf(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_l, (l), TAG_f, (u)))

#define p1788_dec_numsToInterval_Lld(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_l, (l), TAG_d, (u)))

#define p1788_dec_numsToInterval_Lll(r, l, u) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsToInterval(TAG_l, (r), TAG_l, (l), TAG_l, (u)))


#define p1788_dec_numsDecToInterval_Fffi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_f, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Ffdi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_f, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Ffli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_f, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Fdfi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_d, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Fddi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_d, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Fdli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_d, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Flfi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_l, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Fldi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_l, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Flli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_f, (r), TAG_l, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Dffi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_f, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Dfdi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_f, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Dfli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_f, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Ddfi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_d, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Dddi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_d, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Ddli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_d, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Dlfi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_l, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Dldi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_l, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Dlli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_d, (r), TAG_l, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Lffi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_f, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Lfdi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_f, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Lfli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(float) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_f, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Ldfi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_d, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Lddi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_d, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Ldli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_d, (l), TAG_l, (u), (dec)))

#define p1788_dec_numsDecToInterval_Llfi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(float)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_l, (l), TAG_f, (u), (dec)))

#define p1788_dec_numsDecToInterval_Lldi(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(double)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_l, (l), TAG_d, (u), (dec)))

#define p1788_dec_numsDecToInterval_Llli(r, l, u, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(l)) == sizeof(long double) && sizeof(*(u)) == sizeof(long double)), \
   p1788_dec_numsDecToInterval(TAG_l, (r), TAG_l, (l), TAG_l, (u), (dec)))


#define p1788_bar_textToInterval_Fc(r, s) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_textToInterval(TAG_f, (r), (s)))

#define p1788_bar_textToInterval_Dc(r, s) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_textToInterval(TAG_d, (r), (s)))

#define p1788_bar_textToInterval_Lc(r, s) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_textToInterval(TAG_l, (r), (s)))


#define p1788_dec_textToDecoratedInterval_Fc(r, s) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_textToDecoratedInterval(TAG_f, (r), (s)))

#define p1788_dec_textToDecoratedInterval_Dc(r, s) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_textToDecoratedInterval(TAG_d, (r), (s)))

#define p1788_dec_textToDecoratedInterval_Lc(r, s) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_textToDecoratedInterval(TAG_l, (r), (s)))


#define p1788_bar_inf_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_inf(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_inf_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_inf(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_inf_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_inf(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_inf_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_inf(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_inf_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_inf(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_inf_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_inf(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_inf_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_inf(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_inf_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_inf(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_inf_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_inf(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_inf_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_inf(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_inf_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_inf(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_inf_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_inf(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_inf_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_inf(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_inf_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_inf(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_inf_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_inf(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_inf_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_inf(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_inf_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_inf(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_inf_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_inf(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_sup_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sup(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_sup_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sup(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_sup_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sup(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_sup_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sup(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_sup_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sup(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_sup_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sup(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_sup_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_sup(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_sup_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_sup(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_sup_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_sup(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_sup_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sup(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_sup_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sup(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_sup_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sup(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_sup_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sup(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_sup_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sup(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_sup_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sup(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_sup_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_sup(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_sup_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_sup(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_sup_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_sup(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_mid_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mid(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_mid_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mid(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_mid_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mid(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_mid_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mid(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_mid_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mid(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_mid_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mid(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_mid_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mid(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_mid_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mid(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_mid_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mid(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_mid_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mid(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_mid_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mid(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_mid_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mid(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_mid_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mid(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_mid_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mid(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_mid_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mid(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_mid_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mid(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_mid_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mid(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_mid_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mid(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_rad_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_rad(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_rad_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_rad(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_rad_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_rad(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_rad_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_rad(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_rad_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_rad(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_rad_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_rad(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_rad_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_rad(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_rad_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_rad(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_rad_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_rad(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_rad_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_rad(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_rad_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_rad(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_rad_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_rad(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_rad_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_rad(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_rad_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_rad(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_rad_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_rad(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_rad_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_rad(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_rad_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_rad(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_rad_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_rad(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_wid_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_wid(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_wid_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_wid(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_wid_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_wid(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_wid_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_wid(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_wid_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_wid(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_wid_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_wid(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_wid_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_wid(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_wid_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_wid(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_wid_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_wid(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_wid_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_wid(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_wid_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_wid(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_wid_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_wid(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_wid_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_wid(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_wid_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_wid(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_wid_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_wid(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_wid_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_wid(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_wid_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_wid(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_wid_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_wid(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_mag_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mag(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_mag_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mag(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_mag_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mag(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_mag_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mag(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_mag_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mag(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_mag_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mag(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_mag_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mag(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_mag_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mag(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_mag_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mag(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_mag_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mag(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_mag_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mag(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_mag_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mag(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_mag_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mag(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_mag_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mag(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_mag_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mag(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_mag_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mag(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_mag_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mag(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_mag_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mag(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_mig_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mig(TAG_f, (r), TAG_f, (x)))

#define p1788_bar_mig_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mig(TAG_f, (r), TAG_d, (x)))

#define p1788_bar_mig_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mig(TAG_f, (r), TAG_l, (x)))

#define p1788_bar_mig_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mig(TAG_d, (r), TAG_f, (x)))

#define p1788_bar_mig_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mig(TAG_d, (r), TAG_d, (x)))

#define p1788_bar_mig_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mig(TAG_d, (r), TAG_l, (x)))

#define p1788_bar_mig_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_mig(TAG_l, (r), TAG_f, (x)))

#define p1788_bar_mig_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_mig(TAG_l, (r), TAG_d, (x)))

#define p1788_bar_mig_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_mig(TAG_l, (r), TAG_l, (x)))

#define p1788_dec_mig_fF(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mig(TAG_f, (r), TAG_f, (x)))

#define p1788_dec_mig_fD(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mig(TAG_f, (r), TAG_d, (x)))

#define p1788_dec_mig_fL(r, x) \
  (assert(sizeof(*(r)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mig(TAG_f, (r), TAG_l, (x)))

#define p1788_dec_mig_dF(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mig(TAG_d, (r), TAG_f, (x)))

#define p1788_dec_mig_dD(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mig(TAG_d, (r), TAG_d, (x)))

#define p1788_dec_mig_dL(r, x) \
  (assert(sizeof(*(r)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mig(TAG_d, (r), TAG_l, (x)))

#define p1788_dec_mig_lF(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_mig(TAG_l, (r), TAG_f, (x)))

#define p1788_dec_mig_lD(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_mig(TAG_l, (r), TAG_d, (x)))

#define p1788_dec_mig_lL(r, x) \
  (assert(sizeof(*(r)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_mig(TAG_l, (r), TAG_l, (x)))


#define p1788_bar_midRad_ffF(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(float) && sizeof(*(r2)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_midRad(TAG_f, (r1), (r2), TAG_f, (x)))

#define p1788_bar_midRad_ffD(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(float) && sizeof(*(r2)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_midRad(TAG_f, (r1), (r2), TAG_d, (x)))

#define p1788_bar_midRad_ffL(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(float) && sizeof(*(r2)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_midRad(TAG_f, (r1), (r2), TAG_l, (x)))

#define p1788_bar_midRad_ddF(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(double) && sizeof(*(r2)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_midRad(TAG_d, (r1), (r2), TAG_f, (x)))

#define p1788_bar_midRad_ddD(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(double) && sizeof(*(r2)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_midRad(TAG_d, (r1), (r2), TAG_d, (x)))

#define p1788_bar_midRad_ddL(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(double) && sizeof(*(r2)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_midRad(TAG_d, (r1), (r2), TAG_l, (x)))

#define p1788_bar_midRad_llF(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(long double) && sizeof(*(r2)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_midRad(TAG_l, (r1), (r2), TAG_f, (x)))

#define p1788_bar_midRad_llD(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(long double) && sizeof(*(r2)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_midRad(TAG_l, (r1), (r2), TAG_d, (x)))

#define p1788_bar_midRad_llL(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(long double) && sizeof(*(r2)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_midRad(TAG_l, (r1), (r2), TAG_l, (x)))

#define p1788_dec_midRad_ffF(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(float) && sizeof(*(r2)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_midRad(TAG_f, (r1), (r2), TAG_f, (x)))

#define p1788_dec_midRad_ffD(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(float) && sizeof(*(r2)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_midRad(TAG_f, (r1), (r2), TAG_d, (x)))

#define p1788_dec_midRad_ffL(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(float) && sizeof(*(r2)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_midRad(TAG_f, (r1), (r2), TAG_l, (x)))

#define p1788_dec_midRad_ddF(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(double) && sizeof(*(r2)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_midRad(TAG_d, (r1), (r2), TAG_f, (x)))

#define p1788_dec_midRad_ddD(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(double) && sizeof(*(r2)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_midRad(TAG_d, (r1), (r2), TAG_d, (x)))

#define p1788_dec_midRad_ddL(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(double) && sizeof(*(r2)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_midRad(TAG_d, (r1), (r2), TAG_l, (x)))

#define p1788_dec_midRad_llF(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(long double) && sizeof(*(r2)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_midRad(TAG_l, (r1), (r2), TAG_f, (x)))

#define p1788_dec_midRad_llD(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(long double) && sizeof(*(r2)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_midRad(TAG_l, (r1), (r2), TAG_d, (x)))

#define p1788_dec_midRad_llL(r1, r2, x) \
  (assert(sizeof(*(r1)) == sizeof(long double) && sizeof(*(r2)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_midRad(TAG_l, (r1), (r2), TAG_l, (x)))


#define p1788_bar_isEmpty_F(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isEmpty(TAG_f, (x)))

#define p1788_bar_isEmpty_D(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isEmpty(TAG_d, (x)))

#define p1788_bar_isEmpty_L(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isEmpty(TAG_l, (x)))

#define p1788_dec_isEmpty_F(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isEmpty(TAG_f, (x)))

#define p1788_dec_isEmpty_D(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isEmpty(TAG_d, (x)))

#define p1788_dec_isEmpty_L(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isEmpty(TAG_l, (x)))


#define p1788_bar_isEntire_F(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isEntire(TAG_f, (x)))

#define p1788_bar_isEntire_D(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isEntire(TAG_d, (x)))

#define p1788_bar_isEntire_L(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isEntire(TAG_l, (x)))

#define p1788_dec_isEntire_F(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isEntire(TAG_f, (x)))

#define p1788_dec_isEntire_D(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isEntire(TAG_d, (x)))

#define p1788_dec_isEntire_L(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isEntire(TAG_l, (x)))


#define p1788_dec_isNaI_F(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isNaI(TAG_f, (x)))

#define p1788_dec_isNaI_D(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isNaI(TAG_d, (x)))

#define p1788_dec_isNaI_L(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isNaI(TAG_l, (x)))


#define p1788_bar_isCommonInterval_F(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isCommonInterval(TAG_f, (x)))

#define p1788_bar_isCommonInterval_D(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isCommonInterval(TAG_d, (x)))

#define p1788_bar_isCommonInterval_L(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isCommonInterval(TAG_l, (x)))

#define p1788_dec_isCommonInterval_F(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isCommonInterval(TAG_f, (x)))

#define p1788_dec_isCommonInterval_D(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isCommonInterval(TAG_d, (x)))

#define p1788_dec_isCommonInterval_L(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isCommonInterval(TAG_l, (x)))


#define p1788_bar_isSingleton_F(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isSingleton(TAG_f, (x)))

#define p1788_bar_isSingleton_D(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isSingleton(TAG_d, (x)))

#define p1788_bar_isSingleton_L(x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isSingleton(TAG_l, (x)))

#define p1788_dec_isSingleton_F(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isSingleton(TAG_f, (x)))

#define p1788_dec_isSingleton_D(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isSingleton(TAG_d, (x)))

#define p1788_dec_isSingleton_L(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isSingleton(TAG_l, (x)))


#define p1788_bar_isMember_fF(m, x) \
  (assert(sizeof(*(m)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isMember(TAG_f, (m), TAG_f, (x)))

#define p1788_bar_isMember_fD(m, x) \
  (assert(sizeof(*(m)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isMember(TAG_f, (m), TAG_d, (x)))

#define p1788_bar_isMember_fL(m, x) \
  (assert(sizeof(*(m)) == sizeof(float) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isMember(TAG_f, (m), TAG_l, (x)))

#define p1788_bar_isMember_dF(m, x) \
  (assert(sizeof(*(m)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isMember(TAG_d, (m), TAG_f, (x)))

#define p1788_bar_isMember_dD(m, x) \
  (assert(sizeof(*(m)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isMember(TAG_d, (m), TAG_d, (x)))

#define p1788_bar_isMember_dL(m, x) \
  (assert(sizeof(*(m)) == sizeof(double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isMember(TAG_d, (m), TAG_l, (x)))

#define p1788_bar_isMember_lF(m, x) \
  (assert(sizeof(*(m)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_isMember(TAG_l, (m), TAG_f, (x)))

#define p1788_bar_isMember_lD(m, x) \
  (assert(sizeof(*(m)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_isMember(TAG_l, (m), TAG_d, (x)))

#define p1788_bar_isMember_lL(m, x) \
  (assert(sizeof(*(m)) == sizeof(long double) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_isMember(TAG_l, (m), TAG_l, (x)))

#define p1788_dec_isMember_fF(m, x) \
  (assert(sizeof(*(m)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isMember(TAG_f, (m), TAG_f, (x)))

#define p1788_dec_isMember_fD(m, x) \
  (assert(sizeof(*(m)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isMember(TAG_f, (m), TAG_d, (x)))

#define p1788_dec_isMember_fL(m, x) \
  (assert(sizeof(*(m)) == sizeof(float) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isMember(TAG_f, (m), TAG_l, (x)))

#define p1788_dec_isMember_dF(m, x) \
  (assert(sizeof(*(m)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isMember(TAG_d, (m), TAG_f, (x)))

#define p1788_dec_isMember_dD(m, x) \
  (assert(sizeof(*(m)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isMember(TAG_d, (m), TAG_d, (x)))

#define p1788_dec_isMember_dL(m, x) \
  (assert(sizeof(*(m)) == sizeof(double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isMember(TAG_d, (m), TAG_l, (x)))

#define p1788_dec_isMember_lF(m, x) \
  (assert(sizeof(*(m)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_isMember(TAG_l, (m), TAG_f, (x)))

#define p1788_dec_isMember_lD(m, x) \
  (assert(sizeof(*(m)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_isMember(TAG_l, (m), TAG_d, (x)))

#define p1788_dec_isMember_lL(m, x) \
  (assert(sizeof(*(m)) == sizeof(long double) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_isMember(TAG_l, (m), TAG_l, (x)))


#define p1788_bar_equal_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_equal(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_equal_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_equal(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_equal_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_equal(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_equal_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_equal(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_equal_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_equal(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_equal_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_equal(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_equal_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_equal(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_equal_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_equal(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_equal_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_equal(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_equal_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_equal(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_equal_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_equal(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_equal_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_equal(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_equal_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_equal(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_equal_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_equal(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_equal_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_equal(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_equal_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_equal(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_equal_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_equal(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_equal_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_equal(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_subset_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_subset(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_subset_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_subset(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_subset_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_subset(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_subset_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_subset(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_subset_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_subset(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_subset_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_subset(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_subset_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_subset(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_subset_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_subset(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_subset_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_subset(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_subset_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_subset(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_subset_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_subset(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_subset_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_subset(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_subset_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_subset(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_subset_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_subset(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_subset_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_subset(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_subset_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_subset(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_subset_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_subset(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_subset_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_subset(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_less_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_less(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_less_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_less(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_less_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_less(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_less_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_less(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_less_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_less(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_less_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_less(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_less_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_less(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_less_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_less(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_less_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_less(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_less_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_less(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_less_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_less(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_less_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_less(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_less_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_less(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_less_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_less(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_less_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_less(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_less_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_less(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_less_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_less(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_less_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_less(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_precedes_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_precedes(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_precedes_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_precedes(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_precedes_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_precedes(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_precedes_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_precedes(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_precedes_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_precedes(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_precedes_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_precedes(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_precedes_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_precedes(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_precedes_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_precedes(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_precedes_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_precedes(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_precedes_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_precedes(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_precedes_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_precedes(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_precedes_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_precedes(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_precedes_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_precedes(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_precedes_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_precedes(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_precedes_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_precedes(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_precedes_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_precedes(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_precedes_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_precedes(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_precedes_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_precedes(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_interior_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_interior(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_interior_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_interior(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_interior_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_interior(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_interior_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_interior(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_interior_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_interior(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_interior_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_interior(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_interior_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_interior(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_interior_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_interior(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_interior_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_interior(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_interior_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_interior(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_interior_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_interior(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_interior_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_interior(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_interior_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_interior(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_interior_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_interior(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_interior_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_interior(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_interior_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_interior(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_interior_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_interior(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_interior_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_interior(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_strictLess_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_strictLess(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_strictLess_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_strictLess(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_strictLess_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_strictLess(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_strictLess_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_strictLess(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_strictLess_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_strictLess(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_strictLess_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_strictLess(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_strictLess_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_strictLess(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_strictLess_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_strictLess(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_strictLess_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_strictLess(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_strictLess_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_strictLess(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_strictLess_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_strictLess(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_strictLess_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_strictLess(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_strictLess_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_strictLess(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_strictLess_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_strictLess(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_strictLess_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_strictLess(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_strictLess_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_strictLess(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_strictLess_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_strictLess(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_strictLess_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_strictLess(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_strictPrecedes_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_strictPrecedes(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_strictPrecedes_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_strictPrecedes(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_strictPrecedes_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_strictPrecedes(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_strictPrecedes_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_strictPrecedes(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_strictPrecedes_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_strictPrecedes(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_strictPrecedes_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_strictPrecedes(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_strictPrecedes_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_strictPrecedes(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_strictPrecedes_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_strictPrecedes(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_strictPrecedes_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_strictPrecedes(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_strictPrecedes_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_strictPrecedes(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_strictPrecedes_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_strictPrecedes(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_strictPrecedes_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_strictPrecedes(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_strictPrecedes_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_strictPrecedes(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_strictPrecedes_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_strictPrecedes(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_strictPrecedes_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_strictPrecedes(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_strictPrecedes_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_strictPrecedes(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_strictPrecedes_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_strictPrecedes(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_strictPrecedes_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_strictPrecedes(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_disjoint_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_disjoint(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_disjoint_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_disjoint(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_disjoint_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_disjoint(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_disjoint_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_disjoint(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_disjoint_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_disjoint(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_disjoint_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_disjoint(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_disjoint_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_disjoint(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_disjoint_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_disjoint(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_disjoint_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_disjoint(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_disjoint_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_disjoint(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_disjoint_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_disjoint(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_disjoint_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_disjoint(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_disjoint_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_disjoint(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_disjoint_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_disjoint(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_disjoint_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_disjoint(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_disjoint_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_disjoint(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_disjoint_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_disjoint(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_disjoint_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_disjoint(TAG_l, (a), TAG_l, (b)))


#define p1788_bar_overlap_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_overlap(TAG_f, (a), TAG_f, (b)))

#define p1788_bar_overlap_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_overlap(TAG_f, (a), TAG_d, (b)))

#define p1788_bar_overlap_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B32) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_overlap(TAG_f, (a), TAG_l, (b)))

#define p1788_bar_overlap_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_overlap(TAG_d, (a), TAG_f, (b)))

#define p1788_bar_overlap_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_overlap(TAG_d, (a), TAG_d, (b)))

#define p1788_bar_overlap_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B64) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_overlap(TAG_d, (a), TAG_l, (b)))

#define p1788_bar_overlap_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_overlap(TAG_l, (a), TAG_f, (b)))

#define p1788_bar_overlap_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_overlap(TAG_l, (a), TAG_d, (b)))

#define p1788_bar_overlap_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(BARE_INFSUP_B80) && sizeof(*(b)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_overlap(TAG_l, (a), TAG_l, (b)))

#define p1788_dec_overlap_FF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_overlap(TAG_f, (a), TAG_f, (b)))

#define p1788_dec_overlap_FD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_overlap(TAG_f, (a), TAG_d, (b)))

#define p1788_dec_overlap_FL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_overlap(TAG_f, (a), TAG_l, (b)))

#define p1788_dec_overlap_DF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_overlap(TAG_d, (a), TAG_f, (b)))

#define p1788_dec_overlap_DD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_overlap(TAG_d, (a), TAG_d, (b)))

#define p1788_dec_overlap_DL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_overlap(TAG_d, (a), TAG_l, (b)))

#define p1788_dec_overlap_LF(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_overlap(TAG_l, (a), TAG_f, (b)))

#define p1788_dec_overlap_LD(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_overlap(TAG_l, (a), TAG_d, (b)))

#define p1788_dec_overlap_LL(a, b) \
  (assert(sizeof(*(a)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(b)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_overlap(TAG_l, (a), TAG_l, (b)))


#define p1788_newDec_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_dec_newDec(TAG_f, (r), TAG_f, (x)))

#define p1788_newDec_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_dec_newDec(TAG_f, (r), TAG_d, (x)))

#define p1788_newDec_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_dec_newDec(TAG_f, (r), TAG_l, (x)))

#define p1788_newDec_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_dec_newDec(TAG_d, (r), TAG_f, (x)))

#define p1788_newDec_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_dec_newDec(TAG_d, (r), TAG_d, (x)))

#define p1788_newDec_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_dec_newDec(TAG_d, (r), TAG_l, (x)))

#define p1788_newDec_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_dec_newDec(TAG_l, (r), TAG_f, (x)))

#define p1788_newDec_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_dec_newDec(TAG_l, (r), TAG_d, (x)))

#define p1788_newDec_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_dec_newDec(TAG_l, (r), TAG_l, (x)))


#define p1788_decorationPart_F(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_bar_decorationPart(TAG_f, (x)))

#define p1788_decorationPart_D(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_bar_decorationPart(TAG_d, (x)))

#define p1788_decorationPart_L(x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_bar_decorationPart(TAG_l, (x)))


#define p1788_intervalPart_FF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_bar_intervalPart(TAG_f, (r), TAG_f, (x)))

#define p1788_intervalPart_FD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_bar_intervalPart(TAG_f, (r), TAG_d, (x)))

#define p1788_intervalPart_FL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_bar_intervalPart(TAG_f, (r), TAG_l, (x)))

#define p1788_intervalPart_DF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_bar_intervalPart(TAG_d, (r), TAG_f, (x)))

#define p1788_intervalPart_DD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_bar_intervalPart(TAG_d, (r), TAG_d, (x)))

#define p1788_intervalPart_DL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_bar_intervalPart(TAG_d, (r), TAG_l, (x)))

#define p1788_intervalPart_LF(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_bar_intervalPart(TAG_l, (r), TAG_f, (x)))

#define p1788_intervalPart_LD(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_bar_intervalPart(TAG_l, (r), TAG_d, (x)))

#define p1788_intervalPart_LL(r, x) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80) && sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_bar_intervalPart(TAG_l, (r), TAG_l, (x)))


#define p1788_setDec_FFi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_dec_setDec(TAG_f, (r), TAG_f, (x), (dec)))

#define p1788_setDec_FDi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_dec_setDec(TAG_f, (r), TAG_d, (x), (dec)))

#define p1788_setDec_FLi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_dec_setDec(TAG_f, (r), TAG_l, (x), (dec)))

#define p1788_setDec_DFi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_dec_setDec(TAG_d, (r), TAG_f, (x), (dec)))

#define p1788_setDec_DDi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_dec_setDec(TAG_d, (r), TAG_d, (x), (dec)))

#define p1788_setDec_DLi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_dec_setDec(TAG_d, (r), TAG_l, (x), (dec)))

#define p1788_setDec_LFi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_dec_setDec(TAG_l, (r), TAG_f, (x), (dec)))

#define p1788_setDec_LDi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_dec_setDec(TAG_l, (r), TAG_d, (x), (dec)))

#define p1788_setDec_LLi(r, x, dec) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80) && sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_dec_setDec(TAG_l, (r), TAG_l, (x), (dec)))


#define p1788_sum_fifi(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(float)), \
   p1788_sum(TAG_f, (r), (n), (a), (rnd)))

#define p1788_sum_didi(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(double)), \
   p1788_sum(TAG_d, (r), (n), (a), (rnd)))

#define p1788_sum_lili(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(long double)), \
   p1788_sum(TAG_l, (r), (n), (a), (rnd)))


#define p1788_sumAbs_fifi(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(float)), \
   p1788_sumAbs(TAG_f, (r), (n), (a), (rnd)))

#define p1788_sumAbs_didi(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(double)), \
   p1788_sumAbs(TAG_d, (r), (n), (a), (rnd)))

#define p1788_sumAbs_lili(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(long double)), \
   p1788_sumAbs(TAG_l, (r), (n), (a), (rnd)))


#define p1788_dot_fiffi(r, n, a, b, rnd) \
  (assert(sizeof(*(r)) == sizeof(float)), \
   p1788_dot(TAG_f, (r), (n), (a), (b), (rnd)))

#define p1788_dot_diddi(r, n, a, b, rnd) \
  (assert(sizeof(*(r)) == sizeof(double)), \
   p1788_dot(TAG_d, (r), (n), (a), (b), (rnd)))

#define p1788_dot_lilli(r, n, a, b, rnd) \
  (assert(sizeof(*(r)) == sizeof(long double)), \
   p1788_dot(TAG_l, (r), (n), (a), (b), (rnd)))


#define p1788_sumSquare_fifi(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(float)), \
   p1788_sumSquare(TAG_f, (r), (n), (a), (rnd)))

#define p1788_sumSquare_didi(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(double)), \
   p1788_sumSquare(TAG_d, (r), (n), (a), (rnd)))

#define p1788_sumSquare_lili(r, n, a, rnd) \
  (assert(sizeof(*(r)) == sizeof(long double)), \
   p1788_sumSquare(TAG_l, (r), (n), (a), (rnd)))


#define p1788_bar_intervalToText_cFc(r, x, cs) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intervalToText((r), TAG_f, (x), (cs)))

#define p1788_bar_intervalToText_cDc(r, x, cs) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intervalToText((r), TAG_d, (x), (cs)))

#define p1788_bar_intervalToText_cLc(r, x, cs) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intervalToText((r), TAG_l, (x), (cs)))

#define p1788_dec_intervalToText_cFc(r, x, cs) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intervalToText((r), TAG_f, (x), (cs)))

#define p1788_dec_intervalToText_cDc(r, x, cs) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intervalToText((r), TAG_d, (x), (cs)))

#define p1788_dec_intervalToText_cLc(r, x, cs) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intervalToText((r), TAG_l, (x), (cs)))


#define p1788_bar_exactToInterval_Fc(r, s) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_exactToInterval(TAG_f, (r), (s)))

#define p1788_bar_exactToInterval_Dc(r, s) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_exactToInterval(TAG_d, (r), (s)))

#define p1788_bar_exactToInterval_Lc(r, s) \
  (assert(sizeof(*(r)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_exactToInterval(TAG_l, (r), (s)))


#define p1788_dec_exactToDecoratedInterval_Fc(r, s) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_exactToDecoratedInterval(TAG_f, (r), (s)))

#define p1788_dec_exactToDecoratedInterval_Dc(r, s) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_exactToDecoratedInterval(TAG_d, (r), (s)))

#define p1788_dec_exactToDecoratedInterval_Lc(r, s) \
  (assert(sizeof(*(r)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_exactToDecoratedInterval(TAG_l, (r), (s)))


#define p1788_bar_intervalToExact_cF(r, x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B32)), \
   p1788_bar_intervalToExact((r), TAG_f, (x)))

#define p1788_bar_intervalToExact_cD(r, x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B64)), \
   p1788_bar_intervalToExact((r), TAG_d, (x)))

#define p1788_bar_intervalToExact_cL(r, x) \
  (assert(sizeof(*(x)) == sizeof(BARE_INFSUP_B80)), \
   p1788_bar_intervalToExact((r), TAG_l, (x)))

#define p1788_dec_intervalToExact_cF(r, x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B32)), \
   p1788_dec_intervalToExact((r), TAG_f, (x)))

#define p1788_dec_intervalToExact_cD(r, x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B64)), \
   p1788_dec_intervalToExact((r), TAG_d, (x)))

#define p1788_dec_intervalToExact_cL(r, x) \
  (assert(sizeof(*(x)) == sizeof(DECORATED_INFSUP_B80)), \
   p1788_dec_intervalToExact((r), TAG_l, (x)))

