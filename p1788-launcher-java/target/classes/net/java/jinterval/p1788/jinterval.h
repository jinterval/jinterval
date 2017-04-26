#define ILL 0
#define TRV 4
#define DEF 8
#define DAC 12
#define COM 16

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

extern int roundTiesToEvenBareInfsupB64(BARE_INFSUP_B64 *r, BARE_INFSUP_B64 *x);
extern int roundTiesToAwayBareInfsupB64(BARE_INFSUP_B64 *r, BARE_INFSUP_B64 *x);

extern void roundTiesToEvenDecoratedInfsupB64(DECORATED_INFSUP_B64 *r, DECORATED_INFSUP_B64 *x);
extern void roundTiesToAwayDecoratedInfsupB64(DECORATED_INFSUP_B64 *r, DECORATED_INFSUP_B64 *x);

extern int textToBareInfsupB64_gmp_strict(const char* s, BARE_INFSUP_B64 *r);
extern int textToBareInfsupB64_gmp_sloppy(const char* s, BARE_INFSUP_B64 *r);
extern int textToDecoratedInfsupB64_gmp_strict(const char* s, DECORATED_INFSUP_B64 *r);
extern int textToDecoratedInfsupB64_gmp_sloppy(const char* s, DECORATED_INFSUP_B64 *r);

extern void textToInterval(const char *cp, DECORATED_INFSUP_B64 *ret);

