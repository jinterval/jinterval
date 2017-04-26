static void p1788_sum_f(float *r, int n, float* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta;
	mpfr_init2(accum, (FLT_MAX_EXP + FLT_MANT_DIG)*2 + 88);
	mpfr_init2(ta, FLT_MANT_DIG);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_flt(ta, a[i], MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_flt(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(accum);
}

static void p1788_sum_d(double *r, int n, double* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta;
	mpfr_init2(accum, (DBL_MAX_EXP + DBL_MANT_DIG)*2 + 88);
	mpfr_init2(ta, DBL_MANT_DIG);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_d(ta, a[i], MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_d(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(accum);
}

static void p1788_sum_l(long double *r, int n, long double* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta;
	mpfr_init2(accum, (LDBL_MAX_EXP + LDBL_MANT_DIG)*2 + 88);
	mpfr_init2(ta, LDBL_MANT_DIG);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_ld(ta, a[i], MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_ld(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(accum);
}

static void p1788_sumAbs_f(float *r, int n, float* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta;
	mpfr_init2(accum, (FLT_MAX_EXP + FLT_MANT_DIG)*2 + 88);
	mpfr_init2(ta, FLT_MANT_DIG);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_flt(ta, a[i], MPFR_RNDN);
		mpfr_abs(ta, ta, MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_flt(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(accum);
}

static void p1788_sumAbs_d(double *r, int n, double* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta;
	mpfr_init2(accum, (DBL_MAX_EXP + DBL_MANT_DIG)*2 + 88);
	mpfr_init2(ta, DBL_MANT_DIG);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_d(ta, a[i], MPFR_RNDN);
		mpfr_abs(ta, ta, MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_d(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(accum);
}

static void p1788_sumAbs_l(long double *r, int n, long double* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta;
	mpfr_init2(accum, (LDBL_MAX_EXP + LDBL_MANT_DIG)*2 + 88);
	mpfr_init2(ta, LDBL_MANT_DIG);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_ld(ta, a[i], MPFR_RNDN);
		mpfr_abs(ta, ta, MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_ld(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(accum);
}

static void p1788_dot_f(float *r, int n, float* a, float *b, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta, tb, tp;
	mpfr_init2(accum, (FLT_MAX_EXP + FLT_MANT_DIG)*4 + 88);
	mpfr_init2(ta, FLT_MANT_DIG);
	mpfr_init2(tb, FLT_MANT_DIG);
	mpfr_init2(tp, FLT_MANT_DIG*2);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_flt(ta, a[i], MPFR_RNDN);
		mpfr_set_flt(tb, b[i], MPFR_RNDN);
		mpfr_mul(tp, ta, tb, MPFR_RNDN);
		mpfr_add(accum, accum, tp, MPFR_RNDN);
	}
	*r = mpfr_get_flt(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(tb);
	mpfr_clear(tp);
	mpfr_clear(accum);
}

static void p1788_dot_d(double *r, int n, double* a, double *b, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta, tb, tp;
	mpfr_init2(accum, (DBL_MAX_EXP + DBL_MANT_DIG)*4 + 88);
	mpfr_init2(ta, DBL_MANT_DIG);
	mpfr_init2(tb, DBL_MANT_DIG);
	mpfr_init2(tp, DBL_MANT_DIG*2);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_d(ta, a[i], MPFR_RNDN);
		mpfr_set_d(tb, b[i], MPFR_RNDN);
		mpfr_mul(tp, ta, tb, MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_d(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(tb);
	mpfr_clear(tp);
	mpfr_clear(accum);
}

static void p1788_dot_l(long double *r, int n, long double* a, long double *b, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta, tb, tp;
	mpfr_init2(accum, (LDBL_MAX_EXP + LDBL_MANT_DIG)*4 + 88);
	mpfr_init2(ta, LDBL_MANT_DIG);
	mpfr_init2(tb, LDBL_MANT_DIG);
	mpfr_init2(tp, LDBL_MANT_DIG*2);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_ld(ta, a[i], MPFR_RNDN);
		mpfr_set_ld(tb, b[i], MPFR_RNDN);
		mpfr_mul(tp, ta, tb, MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_ld(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(tb);
	mpfr_clear(tp);
	mpfr_clear(accum);
}

static void p1788_sumSquare_f(float *r, int n, float* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta, tb, tp;
	mpfr_init2(accum, (FLT_MAX_EXP + FLT_MANT_DIG)*4 + 88);
	mpfr_init2(ta, FLT_MANT_DIG);
	mpfr_init2(tp, FLT_MANT_DIG*2);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_flt(ta, a[i], MPFR_RNDN);
		mpfr_sqr(tp, ta, MPFR_RNDN);
		mpfr_add(accum, accum, tp, MPFR_RNDN);
	}
	*r = mpfr_get_flt(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(tp);
	mpfr_clear(accum);
}

static void p1788_sumSquare_d(double *r, int n, double* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta, tb, tp;
	mpfr_init2(accum, (DBL_MAX_EXP + DBL_MANT_DIG)*4 + 88);
	mpfr_init2(ta, DBL_MANT_DIG);
	mpfr_init2(tp, DBL_MANT_DIG*2);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_d(ta, a[i], MPFR_RNDN);
		mpfr_sqr(tp, ta, MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_d(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(tp);
	mpfr_clear(accum);
}

static void p1788_sumSquare_l(long double *r, int n, long double* a, mpfr_rnd_t rnd)
{
	mpfr_t accum, ta, tb, tp;
	mpfr_init2(accum, (LDBL_MAX_EXP + LDBL_MANT_DIG)*4 + 88);
	mpfr_init2(ta, LDBL_MANT_DIG);
	mpfr_init2(tp, LDBL_MANT_DIG*2);
	int i;
	for (i = 0; i < n; i++)
	{
		mpfr_set_ld(ta, a[i], MPFR_RNDN);
		mpfr_sqr(tp, ta, MPFR_RNDN);
		mpfr_add(accum, accum, ta, MPFR_RNDN);
	}
	*r = mpfr_get_ld(accum, rnd);
	mpfr_clear(ta);
	mpfr_clear(tp);
	mpfr_clear(accum);
}
