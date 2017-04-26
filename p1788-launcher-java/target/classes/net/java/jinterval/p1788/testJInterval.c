#include <math.h>
#include <stdio.h>

#include "jinterval.h"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

void test_jinterval_setup() {
}

int test_jinterval_roundTiesToEven(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    roundTiesToEvenDecoratedInfsupB64(r, x);
    return EXC_NONE;
}

int test_jinterval_roundTiesToAway(DECORATED_INFSUP_B64 *x, DECORATED_INFSUP_B64 *r) {
    roundTiesToAwayDecoratedInfsupB64(r, x);
    return EXC_NONE;
}

int test_jinterval_textToInterval(const char* s, DECORATED_INFSUP_B64 *r) {
    textToInterval(s, r);
    return EXC_NONE;
}
