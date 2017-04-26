#include <gmp.h>

/* Decorations */
#define ILL 0
#define TRV 4
#define DEF 8
#define DAC 12
#define COM 16

#define EXC_UNDEFINED_OPERATION          -1

typedef long long p1788_exp_t;

// Parse interal literals

#define IS_SPACE_CHAR(c) ((c) == ' ' || (c) == '\t')
#define TOLOWER(c) ((c) | 0x20)

static const char* parse_sp(const char* cp)
{
	while (IS_SPACE_CHAR(*cp))
		cp++;
	return cp;
}

static const char* parse_opt_sign(const char* cp, int* isNegative)
{
	if (*cp == '+')
	{
		*isNegative = 0;
		cp++;
	}
	else if (*cp == '-')
	{
		*isNegative = 1;
		cp++;
	}
	else
	{
		*isNegative = 0;
	}
	return cp;
}

static const char* parse_significand(const char* cp, int radix, mpz_t significand, mp_bitcnt_t* ndigits, mp_bitcnt_t* fractionDigits, int* hasDot)
{
	const char* cp0 = cp;
	const char* firstNZ = NULL;
	const char* dotPos = NULL;
	char c = *cp;
	char* significandChars;
	while ('0' <= c && c <= '9' || radix == 16 && 'a' <= TOLOWER(c) && TOLOWER(c) <= 'f')
	{
		if (firstNZ == NULL && c != '0') firstNZ = cp;
		c = *++cp;
	}
	if (c == '.')
	{
		dotPos = cp;
		c = *++cp;
		while ('0' <= c && c <= '9' || radix == 16 && 'a' <= TOLOWER(c) && TOLOWER(c) <= 'f')
		{
			if (firstNZ == NULL && c != '0') firstNZ = cp;
			c = *++cp;
		}
	}

	if (cp == cp0 || cp == cp0 + 1 && *cp0 == '.')
	{
		return NULL;
	}

    void *(*alloc_func_ptr) (size_t);
    void (*free_func_ptr) (void *, size_t);
    mp_get_memory_functions(&alloc_func_ptr, NULL, &free_func_ptr);
	mp_bitcnt_t nd;
	if (firstNZ == NULL)
 	{
		nd = 0;
		significandChars = (*alloc_func_ptr)(1);
	}
	else if (dotPos != NULL && firstNZ < dotPos)
	{
		nd = cp - firstNZ - 1;
		significandChars = (*alloc_func_ptr)(1 + nd);
		memcpy(significandChars, firstNZ, dotPos - firstNZ);
		memcpy(significandChars + (dotPos - firstNZ), dotPos + 1, cp - dotPos - 1);
	}
	else
	{
		nd = cp - firstNZ;
		significandChars = (*alloc_func_ptr)(1 + nd);
		memcpy(significandChars, firstNZ, nd);
	}
	significandChars[nd] = 0;
	mpz_set_str(significand, significandChars, radix);
	(*free_func_ptr)(significandChars, 1 + nd);
	*ndigits = nd;
	*fractionDigits = dotPos != NULL ? cp - dotPos - 1 : 0;
	*hasDot = dotPos != NULL;
	return cp;
}


static const char* parse_exponent(const char* cp, p1788_exp_t* exp)
{
	int isNegative;
	cp = parse_opt_sign(cp, &isNegative);
	if ('0' <= *cp && *cp <= '9') {
		p1788_exp_t e = 0;
		while ('0' <= *cp && *cp <= '9')
		{
			e = e*10 + *cp - '0'; // TODO: Overflow is possible here
			cp++;
		}
		*exp = isNegative ? -e : e;
		return cp;
	} else {
		return NULL;
	}
}

static const char* parse_number(const char* cp, mpq_t number, int* isInfinity)
{
	int isNegative;
	mp_bitcnt_t ndigits;
	mp_bitcnt_t fractionDigits;
	p1788_exp_t exponent = 0;
	int hasDot;

	*isInfinity = 0;
	cp = parse_opt_sign(cp, &isNegative);
	if (cp[0] == '0' && TOLOWER(cp[1]) == 'x')
	{
		cp = parse_significand(cp + 2, 16, mpq_numref(number), &ndigits, &fractionDigits, &hasDot);
                if (cp != NULL && isNegative) mpq_neg(number, number);
		if (cp != NULL && TOLOWER(cp[0]) != 'p')
		{
			cp = NULL;
		}
		if (cp != NULL)
		{
			cp = parse_exponent(cp + 1, &exponent);
		}
		if (cp != NULL)
		{
			exponent -= 4*fractionDigits;
			if (exponent >= 0)
			{
				mpq_mul_2exp(number, number, exponent);
			}
			else
			{
				mpq_div_2exp(number, number, -exponent);
			}
		}
	}
	else if (TOLOWER(cp[0]) == 'i')
	{
		if (TOLOWER(cp[1]) == 'n' && TOLOWER(cp[2]) == 'f')
		{
			if (TOLOWER(cp[3]) == 'i' &&
				TOLOWER(cp[4]) == 'n' &&
				TOLOWER(cp[5]) == 'i' &&
				TOLOWER(cp[6]) == 't' &&
				TOLOWER(cp[7]) == 'y')
			{
				cp += 8;
			}
			else
			{
				cp += 3;
			}
			*isInfinity = isNegative ? -1 : 1;
			return cp;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		cp = parse_significand(cp, 10, mpq_numref(number), &ndigits, &fractionDigits, &hasDot);
		if (cp != NULL && isNegative) mpq_neg(number, number);
		if (cp != NULL && cp[0] == '/')
		{
			const char* cp0;
			mpq_t denq;
			cp++;
			while (*cp == '0')
				cp++;
			cp0 = cp;
			while ('0' <= *cp && *cp <= '9')
				cp++;
			if (cp == cp0)
				return NULL;
            void *(*alloc_func_ptr) (size_t);
            void (*free_func_ptr) (void *, size_t);
            mp_get_memory_functions(&alloc_func_ptr, NULL, &free_func_ptr);
			char* denomChars = (char*) (*alloc_func_ptr)(cp - cp0 + 1);
			memcpy(denomChars, cp0, cp - cp0);
			denomChars[cp - cp0] = 0;
			mpq_init(denq);
			mpq_set_str(denq, denomChars, 10);
			(*free_func_ptr)(denomChars, cp - cp0 + 1);
			mpq_div(number, number, denq);
			mpq_clear(denq);
			return cp;
		}
		if (cp != NULL && TOLOWER(cp[0]) == 'e')
		{
			cp = parse_exponent(cp + 1, &exponent);
		}
		if (cp != NULL)
		{
			mpz_t pow10z;
			mpq_t pow10q;
			mpz_init(pow10z);
			mpq_init(pow10q);
			exponent -= fractionDigits;
			if (exponent >= 0)
			{
				mpz_ui_pow_ui(pow10z, 10, exponent);
				mpq_set_z(pow10q, pow10z);
				mpq_mul(number, number, pow10q);
			}
			else
			{
				mpz_ui_pow_ui(pow10z, 10, -exponent);
				mpq_set_z(pow10q, pow10z);
				mpq_div(number, number, pow10q);
			}
			mpq_clear(pow10q);
			mpz_clear(pow10z);
		}
	}
	return cp;
}

static const char* parseUncertain(const char* cp, mpq_t infq, int* isInfinityInf, mpq_t supq, int* isInfinitySup)
{
	int isNegative;
	mpz_t mid;
	mp_bitcnt_t ndigits;
	mp_bitcnt_t fractionDigits;
	p1788_exp_t exponent = 0;
	int hasDot;

	mpz_init(mid);
	cp = parse_opt_sign(cp, &isNegative);
	cp = parse_significand(cp, 10, mid, &ndigits, &fractionDigits, &hasDot);
	if (cp != NULL && cp[0] != '?') cp = NULL;
	if (cp != NULL)
	{
		mpz_t rad, infr, supr;
		char c = *++cp;
		int infiniteRad = 0;
		*isInfinityInf = 0;
		*isInfinitySup = 0;
		if (isNegative) mpz_neg(mid, mid);
		mpz_init(rad);
		mpz_init(infr);
		mpz_init(supr);
		if ('0' <= c && c <= '9')
		{
			const char* cp0 = cp;
			while ('0' <= c && c <= '9')
			{
				c = *++cp;
			}
            void *(*alloc_func_ptr) (size_t);
            void (*free_func_ptr) (void *, size_t);
            mp_get_memory_functions(&alloc_func_ptr, NULL, &free_func_ptr);
			char* radChars = (char*) (*alloc_func_ptr)(cp - cp0 + 1);
			memcpy(radChars, cp0, cp - cp0);
			radChars[cp - cp0] = 0;
			mpz_set_str(rad, radChars, 10);
			(*free_func_ptr)(radChars, cp - cp0 + 1);
		}
		else if (c == '?')
		{
			infiniteRad = 1;
			c = *++cp;
		}
		else
		{
			mpz_mul_ui(mid, mid, 10);
			mpz_set_ui(rad, 5);
			fractionDigits++;
		}
		if (TOLOWER(c) == 'd')
		{
			c = *++cp;
			mpz_sub(infr, mid, rad);
			mpz_set(supr, mid);
			*isInfinityInf = -infiniteRad;
		}
		else if (TOLOWER(c) == 'u')
		{
			c = *++cp;
			mpz_set(infr, mid);
			mpz_add(supr, mid, rad);
			*isInfinitySup = infiniteRad;
		}
		else
		{
			mpz_sub(infr, mid, rad);
			mpz_add(supr, mid, rad);
			*isInfinityInf = -infiniteRad;
			*isInfinitySup = infiniteRad;
		}
		mpz_clear(rad);
		mpq_set_z(infq, infr);
		mpq_set_z(supq, supr);
		mpz_clear(infr);
		mpz_clear(supr);

		if (TOLOWER(c) == 'e')
		{
			cp = parse_exponent(cp + 1, &exponent);
		}
		if (cp != NULL)
		{
			mpz_t pow10z;
			mpq_t pow10q;
			mpz_init(pow10z);
			mpq_init(pow10q);
			exponent -= fractionDigits;
			if (exponent >= 0)
			{
				mpz_ui_pow_ui(pow10z, 10, exponent);
				mpq_set_z(pow10q, pow10z);
				mpq_mul(infq, infq, pow10q);
				mpq_mul(supq, supq, pow10q);
			}
			else
			{
				mpz_ui_pow_ui(pow10z, 10, -exponent);
				mpq_set_z(pow10q, pow10z);
				mpq_div(infq, infq, pow10q);
				mpq_div(supq, supq, pow10q);
			}
			mpq_clear(pow10q);
			mpz_clear(pow10z);
		}
	}
	mpz_clear(mid);
	return cp;
}

static int parse_interval(const char *cp, int decorated,
        mpq_t infq, int *isInfinityInf, mpq_t supq, int *isInfinitySup)
{
	int decor = COM;
	int isemp = 0;
	*isInfinityInf = 1;
    *isInfinitySup = -1;
	char c = *cp;
	if (c == '[')
	{
		cp = parse_sp(cp + 1);
		if (cp[0] == ']')
		{
			isemp = 1;
			decor = TRV;
		}
		else if (TOLOWER(cp[0]) == 'e')
		{
			if (TOLOWER(cp[1]) == 'm' &&
				TOLOWER(cp[2]) == 'p' &&
				TOLOWER(cp[3]) == 't' &&
				TOLOWER(cp[4]) == 'y')
			{
				isemp = 1;
				decor = TRV;
				cp += 5;
			}
			else if (TOLOWER(cp[1]) == 'n' &&
				TOLOWER(cp[2]) == 't' &&
				TOLOWER(cp[3]) == 'i' &&
				TOLOWER(cp[4]) == 'r' &&
				TOLOWER(cp[5]) == 'e')
			{
				*isInfinityInf = -1;
				*isInfinitySup = 1;
				cp += 6;
			}
			else
			{
				return EXC_UNDEFINED_OPERATION;
			}
		}
		else if (decorated && TOLOWER(cp[0]) == 'n')
		{
			if (TOLOWER(cp[1]) == 'a' &&
				TOLOWER(cp[2]) == 'i')
			{
				isemp = 1;
				decor = ILL;
				cp += 3;
			}
			else
			{
				return EXC_UNDEFINED_OPERATION;
			}
		}
		else
		{
            *isInfinityInf = *isInfinitySup = 0;
			if (*cp == ',')
			{
				*isInfinityInf = -1;
			}
			else
			{
				cp = parse_number(cp, infq, isInfinityInf);
			}
            if (cp == NULL) return EXC_UNDEFINED_OPERATION;
			cp = parse_sp(cp);
			if (*cp == ',')
			{
				cp = parse_sp(cp + 1);
				if (*cp == ']')
				{
					*isInfinitySup = 1;
				}
				else
				{
					cp = parse_number(cp, supq, isInfinitySup);
                    if (cp == NULL) return EXC_UNDEFINED_OPERATION;
				}
			}
			else
			{
				mpq_set(supq, infq);
				*isInfinitySup = *isInfinityInf;
			}
			cp = parse_sp(cp);
			if (*isInfinityInf == 1 || *isInfinitySup == -1
				|| !*isInfinityInf && !*isInfinitySup && mpq_cmp (infq, supq) > 0)
			{
				*isInfinityInf = 1;
				*isInfinitySup = -1;
				return EXC_UNDEFINED_OPERATION;
            }
		}
		cp = parse_sp(cp);
		if (*cp != ']') return EXC_UNDEFINED_OPERATION;
		cp++;
	}
	else
	{
		cp = parseUncertain(cp, infq, isInfinityInf, supq, isInfinitySup);
		if (cp == NULL) return EXC_UNDEFINED_OPERATION;
	}
	if (decorated && decor != ILL && *cp == '_')
	{
		cp++;
		if (TOLOWER(cp[0]) == 't' && TOLOWER(cp[1]) == 'r' && TOLOWER(cp[2]) == 'v')
		{
			decor = TRV;
		}
		else if (TOLOWER(cp[0]) == 'd' && TOLOWER(cp[1]) == 'e' && TOLOWER(cp[2]) == 'f')
		{
			if (*isInfinityInf > *isInfinitySup) return EXC_UNDEFINED_OPERATION;
			decor = DEF;
		}
		else if (TOLOWER(cp[0]) == 'd' && TOLOWER(cp[1]) == 'a' && TOLOWER(cp[2]) == 'c')
		{
			if (*isInfinityInf > *isInfinitySup) return EXC_UNDEFINED_OPERATION;
			decor = DAC;
		}
		else if (TOLOWER(cp[0]) == 'c' && TOLOWER(cp[1]) == 'o' && TOLOWER(cp[2]) == 'm')
		{
			if (*isInfinityInf || *isInfinitySup) return EXC_UNDEFINED_OPERATION;
			decor = COM;
		}
		else
		{
            return EXC_UNDEFINED_OPERATION;
		}
		cp += 3;
	}
	else
	{
        if (decor == COM && (*isInfinityInf || *isInfinitySup)) decor = DAC;
	}
	if (*cp != 0)
	{
		return EXC_UNDEFINED_OPERATION;
	}
	return decor;
}
