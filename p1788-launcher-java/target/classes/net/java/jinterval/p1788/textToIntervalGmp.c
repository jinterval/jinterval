#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include "jinterval.h"

#include "p1788_textToInterval.inc.c"

static void convertNum(mpq_t q, int isInfinity, double* inf, double* sup)
{
	if (isInfinity > 0)
	{
		*inf = *sup = +INFINITY;
		return;
	}
	else if (isInfinity < 0)
	{
		*inf = *sup = -INFINITY;
		return;
	}
	double d = mpq_get_d(q);
	if (d == +INFINITY)
	{
		*inf = nexttoward(d, -INFINITY);
		*sup = d;
	}
	else if (d == -INFINITY)
	{
		*inf = d;
		*sup = nexttoward(d, +INFINITY);
	}
	else {
		mpq_t dq;
		mpq_init(dq);
		mpq_set_d(dq, d);
		int cmp = mpq_cmp(q, dq);
		if (cmp > 0)
		{
			*inf = d;
			*sup = nexttoward(d, +INFINITY);
		}
		else if (cmp < 0)
		{
			*inf = nexttoward(d, -INFINITY);
			*sup = d;
		}
		else
		{
			*inf = *sup = d;
		}
		mpq_clear(dq);
	}
}

static int convert(mpq_t infq, int isInfinityInf, mpq_t supq, int isInfinitySup, double* inf, double* sup, int strictBoundsCheck)
{
	double inf1, sup1;

	if (isInfinityInf == +1 || isInfinitySup == -1) return 1;
	if (strictBoundsCheck)
	{
		if (isInfinityInf == 0 && isInfinitySup == 0 && mpq_cmp(infq, supq) > 0) return 1;
	}
	convertNum(infq, isInfinityInf, inf, &inf1);
	convertNum(supq, isInfinitySup, &sup1, sup);
	if (!strictBoundsCheck)
	{
		if (inf1 >= sup1 && (*inf != sup1 || inf1 != *sup)) return 1;
	}
	return 0;
}

static int textToIntervalImpl(const char* cp, DECORATED_INFSUP_B64* interval, int decorated, int strictBoundsCheck)
{
    mpq_t infq, supq;
    int isInfinityInf, isInfinitySup;
    mpq_init(infq);
    mpq_init(supq);

    int d = parse_interval(cp, decorated, infq, &isInfinityInf, supq, &isInfinitySup);
    if (d < 0)
    {
        // Syntax error
        interval->inf = interval->sup = NAN;
        interval->decoration = ILL;
    }
    else if (isInfinityInf > isInfinitySup)
    {
        // Empty
        assert (d == ILL || d == TRV);
        interval->inf = interval->sup = NAN;
        interval->decoration = d;
        d = 0;
    }
    else if (convert(infq, isInfinityInf, supq, isInfinitySup, &interval->inf, &interval->sup, strictBoundsCheck))
    {
        // Bad endpoints
        assert (d >= TRV);
        interval->inf = interval->sup = NAN;
        interval->decoration = ILL;
        d = EXC_UNDEFINED_OPERATION;
    }
    else
    {
        // Good interval
        assert (d >= TRV);
        interval->decoration = d;
        d = 0;
    }
    mpq_clear(infq);
    mpq_clear(supq);
    return d;
}

int textToDecoratedInfsupB64_gmp_sloppy(const char *text, DECORATED_INFSUP_B64* interval)
{
    return textToIntervalImpl(text, interval, 1, 0);
}

int textToDecoratedInfsupB64_gmp_strict(const char *text, DECORATED_INFSUP_B64* interval)
{
    return textToIntervalImpl(text, interval, 1, 1);
}

int textToBareInfsupB64_gmp_sloppy(const char *text, BARE_INFSUP_B64* interval)
{
    DECORATED_INFSUP_B64 decorated;
    int exc = textToIntervalImpl(text, &decorated, 0, 0);
    interval->inf = decorated.inf;
    interval->sup = decorated.sup;
    return exc;
}

int textToBareInfsupB64_gmp_strict(const char *text, BARE_INFSUP_B64* interval)
{
    DECORATED_INFSUP_B64 decorated;
    int exc = textToIntervalImpl(text, &decorated, 0, 1);
    interval->inf = decorated.inf;
    interval->sup = decorated.sup;
    return exc;
}

