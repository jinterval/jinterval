#include <math.h>
#include <stdio.h>
#include <gmp.h>

#include "jinterval.h"

// Exception codes
#define EXC_NONE                          0
#define EXC_UNDEFINED_OPERATION          -1
#define EXC_POSSIBLY_UNDEFINED_OPERATION -2
#define EXC_INTERVAL_PART_OF_NAI         -3
#define EXC_INVALID_OPERAND              -4

void test_jintervalgmp_setup() {
}

int test_jintervalgmp_textToDecoratedInterval(const char* s, DECORATED_INFSUP_B64 *r) {
    textToDecoratedInfsupB64_gmp_strict(s, r);
    return EXC_NONE;
}
