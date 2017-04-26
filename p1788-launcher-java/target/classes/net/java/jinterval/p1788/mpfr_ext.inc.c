#include <assert.h>
#include <mpfr.h>

static void mpfr_get_q(mpq_t r, mpfr_srcptr x)
{
	if (!mpfr_regular_p(x))
	{
		mpq_set_ui(r, 0, 1);
		return;
	}
	mpz_t z;
	mpz_init(z);
	mpfr_exp_t exp = mpfr_get_z_2exp(z, x);
	mpq_set_z(r, z);
	mpz_clear(z);
	if (exp > 0) {
		mpq_mul_2exp(r, r, exp);
	} else {
		mpq_div_2exp(r, r, -exp);
        }
}

static void mpfr_as_mpz(mpz_t m, mpfr_srcptr x, mpfr_exp_t emin, mpfr_exp_t emax, int subnormal)
{
	mpfr_prec_t prec = mpfr_get_prec(x);
	if (mpfr_zero_p(x))
	{
		mpz_set_ui(m, 0);
		return;
	}
	mpfr_uexp_t base_m;
	mp_bitcnt_t base_e = prec - 1;
	if (mpfr_number_p(x))
	{
		mpfr_exp_t exp = mpfr_get_exp(x);
		mpfr_get_z_2exp(m, x);
		mpz_abs(m, m);
		mpz_clrbit(m, prec - 1);
		if (!subnormal)
		{
			base_m = exp - emin;
			mpz_add_ui(m, m, 1);
		}
		else if (exp >= emin + prec - 1)
		{
			base_m = exp - emin - prec + 2;
		}
		else
		{
			base_m = 1;
			base_e = exp - emin;
			mpz_tdiv_q_2exp(m, m, prec - 1 - base_e);
		}
	}
	else
	{
		assert(mpfr_inf_p(x));
		if (!subnormal)
		{
			base_m = emax - emin + 1;
			mpz_set_ui(m, 1);
		}
		else
		{
			base_m = emax - emin - prec + 3;
			mpz_set_ui(m, 0);
		}
	}
	// m = m + base_m * 2^base_e
	mpz_t base;
	mpz_init_set_ui(base, base_m);
	mpz_mul_2exp(base, base, base_e);
	mpz_add(m, m, base);
	mpz_clear(base);
	if (mpfr_sgn(x) < 0)
	{
		mpz_neg(m, m);
	}
}

static void mpfr_from_mpz(mpfr_t r, mpz_t m, mpfr_exp_t emin, mpfr_exp_t emax, int subnormal)
{
	int sgn = mpz_sgn(m);
	if (sgn == 0)
	{
		mpfr_set_zero(r, 1);
		return;
	}
	mpfr_prec_t prec = mpfr_get_prec(r);
	mpfr_exp_t exp;
	mpz_t mz, ez;
	mpz_init(mz);
	mpz_init(ez);
	mpz_abs(mz, m);
	if (!subnormal)
	{
		mpz_sub_ui(mz, mz, 1);
		mpz_tdiv_q_2exp(ez, mz, prec - 1);
		if (mpz_cmp_ui(ez, emax - emin + 1) >= 0)
		{
			mpz_clear(ez);
			mpz_clear(mz);
			mpfr_set_inf(r, sgn);
			return;
		}
		exp = mpz_get_ui(ez) + emin;
		mpz_tdiv_r_2exp(mz, mz, prec - 1);
		mpz_setbit(mz, prec - 1);
	}
	else
	{
		mpz_tdiv_q_2exp(ez, mz, prec - 1);
		if (mpz_cmp_ui(ez, emax - emin - prec + 3) >= 0)
		{
			mpz_clear(ez);
			mpz_clear(mz);
			mpfr_set_inf(r, sgn);
			return;
		}
		exp = mpz_get_ui(ez);
		if (exp > 0)
		{
			exp += emin + prec - 2;
			mpz_tdiv_r_2exp(mz, mz, prec - 1);
			mpz_setbit(mz, prec - 1);
		}
		else
		{
			exp = emin + prec - 1;
		}
	}
	mpz_clear(ez);
	mpfr_exp_t saved_emin = mpfr_get_emin();
	mpfr_exp_t saved_emax = mpfr_get_emax();
	mpfr_set_emin(emin);
	mpfr_set_emax(emax);
	int t = mpfr_set_z_2exp(r, mz, exp - prec, MPFR_RNDN);
	assert(t == 0);
	mpz_clear(mz);
	if (sgn < 0)
	{
		mpfr_neg(r, r, MPFR_RNDN);
	}
	mpfr_set_emin(saved_emin);
	mpfr_set_emax(saved_emax);
}

/* returns in k the integer part of the division of x by Pi/2           */
/* the result is exact                                                  */
static void mpfr_quadrant (mpz_ptr k, mpfr_srcptr op)
{
	mpfr_prec_t prec = mpfr_get_prec(op);
	if (mpfr_sgn(op) == 0)
	{
		mpz_set_ui(k, 0);
		return;
	}

	mpfr_exp_t saved_emin = mpfr_get_emin();
	mpfr_exp_t saved_emax = mpfr_get_emax();
	mpfr_set_emin(mpfr_get_emin_min());
	mpfr_set_emax(mpfr_get_emax_max());
	for (;;)
	{
		mpfr_t k_inf, k_sup;

		mpfr_init2(k_inf, prec);
		mpfr_const_pi(k_inf, MPFR_RNDU);
		mpfr_div(k_inf, op, k_inf, MPFR_RNDD);
		mpfr_mul_2ui(k_inf, k_inf, 1, MPFR_RNDD);
		mpfr_floor(k_inf, k_inf);

		mpfr_init2(k_sup, prec);
		mpfr_const_pi(k_sup, MPFR_RNDD);
		mpfr_div(k_sup, op, k_sup, MPFR_RNDU);
		mpfr_mul_2ui(k_sup, k_sup, 1, MPFR_RNDU);
		mpfr_floor(k_sup, k_sup);

		if (mpfr_cmp(k_inf, k_sup) == 0)
		{
			mpfr_get_z(k, k_inf, MPFR_RNDN);
			mpfr_clear(k_inf);
			mpfr_clear(k_sup);
			mpfr_set_emin(saved_emin);
			mpfr_set_emax(saved_emax);
			return;
		}
		mpfr_clear(k_inf);
		mpfr_clear(k_sup);
		prec += mpfr_get_prec(op);
	}
}

static void mpfr_piHalf(mpfr_t r, mpz_t k, mpfr_rnd_t rnd, mpfr_exp_t emin, mpfr_exp_t emax, int subnormal)
{
	if (mpz_sgn(k) == 0)
	{
		mpfr_set_zero(r, 1);
		return;
	}
	mpfr_t r2;
	mpfr_init2(r2, mpfr_get_prec(r));
	mpfr_prec_t prec = mpfr_get_prec(r) * 2;
	do
	{
		mpfr_t inf, sup;

		mpfr_init2(inf, prec);
		mpfr_const_pi(inf, MPFR_RNDD);
		mpfr_div_2exp(inf, inf, 1, MPFR_RNDD);
		mpfr_mul_z(inf, inf, k, MPFR_RNDD);

		mpfr_init2(sup, prec);
		mpfr_const_pi(sup, MPFR_RNDU);
		mpfr_div_2exp(sup, sup, 1, MPFR_RNDU);
		mpfr_mul_z(sup, sup, k, MPFR_RNDU);

		mpfr_exp_t saved_emin = mpfr_get_emin();
		mpfr_exp_t saved_emax = mpfr_get_emax();
		mpfr_set_emin(emin);
		mpfr_set_emax(emax);

		int ti = mpfr_check_range(r, mpfr_set(r, inf, rnd), rnd);
		int ts = mpfr_check_range(r2, mpfr_set(r2, sup, rnd), rnd);
		if (subnormal)
		{
			mpfr_subnormalize(r, ti, rnd);
			mpfr_subnormalize(r2, ts, rnd);
		}
		mpfr_set_emin(saved_emin);
		mpfr_set_emax(saved_emax);
		prec += mpfr_get_prec(r);
	} while (mpfr_cmp(r, r2) != 0);
}

/*
  The result of comparison between r and inverse function f^(-1) (c)
  fwd_fun(rop, op, env) assigns rop = round(f(op)) and returns comparison between rop and f(op).
  decrease != 0 iff f(op) is decreasing
*/
static int cmp_rev(mpfr_ptr r, mpfr_srcptr c, mpfr_t tmp, int (*fwd_fun)(mpfr_ptr rop, mpfr_srcptr op, const void *env), const void *env, int decrease)
{
	mpfr_exp_t saved_emin = mpfr_get_emin();
	mpfr_exp_t saved_emax = mpfr_get_emax();
	if (mpfr_regular_p(c))
	{
		mpfr_set_emin(mpfr_get_exp(c));
		mpfr_set_emax(mpfr_get_exp(c));
	}
	else
	{
		mpfr_set_emin(mpfr_get_emin_min());
		mpfr_set_emax(mpfr_get_emax_max());
	}
	int t = (*fwd_fun) (tmp, r, env);
    mpfr_set_emin(saved_emin);
	mpfr_set_emax(saved_emax);
	int cmp = mpfr_cmp(c, tmp);
	if (cmp == 0) cmp = t;
	if (!decrease) cmp = -cmp;
//fprintf(stderr, "    cmp_rev=%d decrease=%d\n", cmp, decrease);
	return cmp;
}

static int p1788_rev_lin(mpfr_ptr rop, mpfr_srcptr rlim, mpfr_srcptr op, int (*fwd_fun)(mpfr_ptr rop, mpfr_srcptr op, const void *env), const void *env, int decrease, mpfr_rnd_t rnd)
{
    assert(rnd == MPFR_RNDU || rnd == MPFR_RNDD);
    assert (mpfr_cmp(rop, rlim) == (rnd == MPFR_RNDU ? 1 : -1));
    mpfr_t tmp_op;
    mpfr_init2 (tmp_op, mpfr_get_prec(op));
    int t;
    for (;;) {
        if (rnd == MPFR_RNDU)
            mpfr_nextbelow(rop);
        else
            mpfr_nextabove(rop);
        if (mpfr_cmp(rop, rlim) != 0)
        {
            t = -cmp_rev(rop, op, tmp_op, fwd_fun, env, decrease);
            if (t == 0) break;
            if (rnd == MPFR_RNDU ? t < 0 : t > 0) continue;
        }
        if (rnd == MPFR_RNDU)
            mpfr_nextabove(rop);
        else
            mpfr_nextbelow(rop);
        break;
    }
    mpfr_clear(tmp_op);
    return t;
}

static int p1788_rev_bin(mpfr_ptr rop, mpfr_srcptr rlim, mpfr_srcptr op, int (*fwd_fun)(mpfr_ptr rop, mpfr_srcptr op, const void *env), const void *env, int decrease, mpfr_rnd_t rnd)
{
    assert(rnd == MPFR_RNDU || rnd == MPFR_RNDD);
    assert (mpfr_cmp(rop, rlim) == (rnd == MPFR_RNDU ? 1 : -1));
    mpfr_exp_t emin_rop = mpfr_get_emin();
    mpfr_exp_t emax_rop = mpfr_get_emax();
    mpfr_t tmp_op;
    mpfr_init2 (tmp_op, mpfr_get_prec(op));
	mpz_t rop_z, rlim_z, z;
    mpz_init(rop_z);
    mpfr_as_mpz(rop_z, rop, emin_rop, emax_rop, 0);
    mpz_init(rlim_z);
    mpfr_as_mpz(rlim_z, rlim, emin_rop, emax_rop, 0);
	mpz_init(z);
	mp_bitcnt_t k;
	for (k = 0; ; k++)
	{
		mpz_set_ui(z, 1);
		mpz_mul_2exp(z, z, k);
        if (rnd == MPFR_RNDU)
        {
    		mpz_sub(z, rop_z, z);
        	if (mpz_cmp(z, rlim_z) <= 0)
            {
                mpz_set(z, rlim_z);
                break;
            }
        }
        else
        {
    		mpz_add(z, rop_z, z);
        	if (mpz_cmp(z, rlim_z) >= 0)
            {
                mpz_set(z, rlim_z);
                break;
            }
        }
        mpfr_from_mpz(rop, z, emin_rop, emax_rop, 0);
		int t = cmp_rev(rop, op, tmp_op, fwd_fun, env, decrease);
		if (rnd == MPFR_RNDU ? t < 0 : t > 0) break;
		mpz_set(rop_z, z);
		if (t == 0)
		{
            mpfr_clear(tmp_op);
            mpz_clear(rop_z);
            mpz_clear(rlim_z);
			mpz_clear(z);
			return 0;
		}
	}
	mpz_t m;
	mpz_init(m);
	for (;;)
	{
		mpz_add(m, rop_z, z);
        if (rnd == MPFR_RNDU)
            mpz_cdiv_q_ui(m, m, 2);
        else
            mpz_fdiv_q_ui(m, m, 2);
        mpfr_from_mpz(rop, m, emin_rop, emax_rop, 0);
		if (mpz_cmp(m, rop_z) == 0)
		{
            mpfr_clear(tmp_op);
            mpz_clear(rop_z);
            mpz_clear(rlim_z);
			mpz_clear(z);
			mpz_clear(m);
			return rnd == MPFR_RNDU ? 1 : -1;
		}
        if (rnd == MPFR_RNDU)
            assert(mpz_cmp(m, z) > 0);
        else
            assert(mpz_cmp(m, z) < 0);
		int t = cmp_rev(rop, op, tmp_op, fwd_fun, env, decrease);
		if (rnd == MPFR_RNDU ? t < 0 : t > 0)
		{
			mpz_set(z, m);
		}
		else
		{
			mpz_set(rop_z, m);
			if (t == 0)
			{
                mpfr_clear(tmp_op);
                mpz_clear(rop_z);
                mpz_clear(rlim_z);
            	mpz_clear(z);
            	mpz_clear(m);
				return 0;
			}
		}
	}

}

static int p1788_fwd_pown(mpfr_ptr rop, mpfr_srcptr op, const void *env) {
	int p = *((int*) env);
	return mpfr_pow_si(rop, op, p, MPFR_RNDN);
}

static int mpfr_root_si(mpfr_ptr rop, mpfr_srcptr op, long int k, mpfr_rnd_t rnd)
{
	int t;
	if (k >= 0)
	{
		t = mpfr_root(rop, op, k, rnd);
	}
	else if (k == -1)
	{
		t = mpfr_ui_div(rop, 1, op, rnd);
	}
	else if (k == -2)
	{
		t = mpfr_rec_sqrt(rop, op, rnd);
	}
	else if (1) // slow bin
    {
        if (mpfr_nan_p(op) || (k & 1) == 0 && mpfr_sgn(op) < 0)
            return mpfr_set_nan(rop), 0;
        if (mpfr_inf_p(op))
            return mpfr_set_zero(rop, mpfr_signbit(op) && (k & 1) != 0 ? -1 : 1), 0;
        if (mpfr_zero_p(op))
            return mpfr_set_inf(rop, mpfr_signbit(op) && (k & 1) != 0 ? -1 : 1), 0;
        mpfr_t tmp_rop, rlim;
        mpfr_init2(tmp_rop, mpfr_get_prec(rop));
        mpfr_init2(rlim, mpfr_get_prec(rop));
        if (mpfr_sgn (op) > 0)
        {
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_inf(rlim, 1);
        }
        else
        {
            mpfr_set_inf(tmp_rop, -1);
            mpfr_set_zero(rlim, -1);
        }
        if (rnd == MPFR_RNDU)
            mpfr_swap(tmp_rop, rlim);
        t = p1788_rev_bin(tmp_rop, rlim, op, p1788_fwd_pown, &k, 1, rnd);
        mpfr_clear(rlim);
		mpfr_set(rop, tmp_rop, rnd);
        mpfr_clear(tmp_rop);
    }
    else // fast lin
	{
		mpfr_rnd_t rnd1 = rnd == MPFR_RNDU ? MPFR_RNDD : (assert(rnd == MPFR_RNDD), MPFR_RNDU);
		int t1;
        mpfr_t tmp_rop;
        mpfr_init2(tmp_rop, mpfr_get_prec(rop));
		if (-k != k)
		{
			t1 = mpfr_root(tmp_rop, op, -k, rnd1);
		}
		else
		{
			int t2 = mpfr_sqrt(tmp_rop, op, rnd1);
			t1 = mpfr_root(tmp_rop, tmp_rop, -(k >> 1), rnd1);
			if (t1 == 0) t1 = t2;
		}
//		if (mpfr_zero_p(tmp_rop) && (k & 1) == 0 && mpfr_sgn(tmp_rop) < 0)
//			mpfr_set_zero(tmp_rop, 1);
		t = mpfr_ui_div(tmp_rop, 1, tmp_rop, rnd);
		if (t == 0) t = -t1;
		if (t != 0)
		{
            mpfr_t rlim;
            mpfr_init2(rlim, mpfr_get_prec (rop));
            if (mpfr_sgn (op) > 0)
            {
                if (rnd == MPFR_RNDU)
                {
                    mpfr_set_zero(rlim, 1);
                }
                else
                {
                    mpfr_set_inf(rlim, 1);
                }
            }
            else
            {
                if (rnd == MPFR_RNDU)
                {
                    mpfr_set_inf(rlim, -1);
                }
                else
                {
                    mpfr_set_zero(rlim, 1);
                }
            }
            t = p1788_rev_lin(tmp_rop, rlim, op, p1788_fwd_pown, &k, 1, rnd);
            mpfr_clear(rlim);
		}
		mpfr_set(rop, tmp_rop, rnd);
        mpfr_clear(tmp_rop);
	}
	return t;
}

static int mpfr_atrig(mpfr_ptr rop, mpfr_srcptr op, int (*fun)(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd), int sub, mpz_t npi, mpfr_rnd_t rnd)
{
    assert(rnd == MPFR_RNDU || rnd == MPFR_RNDD);
	int t;
	if (mpz_sgn(npi) == 0)
	{
		if (sub)
		{
			mpfr_rnd_t rnd1 = rnd == MPFR_RNDU ? MPFR_RNDD : (assert(rnd == MPFR_RNDD), MPFR_RNDU);
			t = -(*fun)(rop, op, rnd1);
			mpfr_neg(rop, rop, rnd);
		}
		else
		{
			t = (*fun)(rop, op, rnd);
		}
		return t;
	}
	mpfr_exp_t emin_rop = mpfr_get_emin();
	mpfr_exp_t emax_rop = mpfr_get_emax();
	mpfr_set_emin(mpfr_get_emin_min());
	mpfr_set_emax(mpfr_get_emax_max());
	mpfr_prec_t prec = mpfr_get_prec(rop) * 2;
	for (;;)
	{
		mpfr_t pi, inf, sup;
		mpfr_init2(pi, prec);
		mpfr_init2(inf, prec);
		mpfr_init2(sup, prec);

		mpfr_const_pi(pi, MPFR_RNDD);
		mpfr_mul_z(pi, pi, npi, MPFR_RNDD);
		if (sub)
		{
			(*fun)(sup, op, MPFR_RNDU);
			mpfr_sub(sup, pi, sup, MPFR_RNDD);
		}
		else
		{
			(*fun)(inf, op, MPFR_RNDD);
			mpfr_add(inf, pi, inf, MPFR_RNDD);
		}

		mpfr_const_pi(pi, MPFR_RNDU);
		mpfr_mul_z(pi, pi, npi, MPFR_RNDU);
		if (sub)
		{
			(*fun)(inf, op, MPFR_RNDD);
			mpfr_sub(inf, pi, inf, MPFR_RNDU);
		}
		else
		{
			(*fun)(sup, op, MPFR_RNDU);
			mpfr_add(sup, pi, sup, MPFR_RNDU);
		}

		mpfr_clear(pi);
		mpfr_prec_round(inf, mpfr_get_prec(rop), rnd);
		mpfr_prec_round(sup, mpfr_get_prec(rop), rnd);
		if (mpfr_cmp(inf, sup) == 0)
		{
			mpfr_set(rop, inf, rnd);
			mpfr_clear(inf);
			mpfr_clear(sup);
			mpfr_set_emin(emin_rop);
			mpfr_set_emax(emax_rop);
			return mpfr_check_range(rop, rnd == MPFR_RNDU ? 1 : -1, rnd);
		}
		mpfr_clear(inf);
		mpfr_clear(sup);
		prec += mpfr_get_prec(rop);
	}
}

// rop = (-1)^npi * asin(op) + npi*pi
static int mpfr_asin_npi(mpfr_ptr rop, mpfr_srcptr op, mpz_t npi, mpfr_rnd_t rnd)
{
	return mpfr_atrig(rop, op, mpfr_asin, mpz_tstbit(npi, 0), npi, rnd);
}

// rop = (-1)^npi * acos(op) + (npi + (1 - (-1)^npi)/2)*pi
static int mpfr_acos_npi(mpfr_ptr rop, mpfr_srcptr op, mpz_t npi, mpfr_rnd_t rnd)
{
	int sub = mpz_tstbit(npi, 0);
	int t;
	if (sub) {
		mpz_t npi1;
		mpz_init(npi1);
		mpz_add_ui(npi1, npi, 1);
		t = mpfr_atrig(rop, op, mpfr_acos, sub, npi1, rnd);
		mpz_clear(npi1);
	}
	else
	{
		t = mpfr_atrig(rop, op, mpfr_acos, sub, npi, rnd);
	}
	return t;
}

// rop = atan(op) + npi*pi
static int mpfr_atan_npi(mpfr_ptr rop, mpfr_srcptr op, mpz_t npi, mpfr_rnd_t rnd)
{
	return mpfr_atrig(rop, op, mpfr_atan, 0, npi, rnd);
}

static int p1788_fwd_pow_1(mpfr_ptr rop, mpfr_srcptr op, const void *env) {
	mpfr_srcptr op2 = (mpfr_srcptr) env;
	return mpfr_pow(rop, op, op2, MPFR_RNDN);
}

// rop = pow(op1, 1/op2)
static int mpfr_root_fr(mpfr_ptr rop, mpfr_srcptr op1, mpfr_srcptr op2, mpfr_rnd_t rnd)
{
    assert(mpfr_sgn(op1) > 0);
    assert(!mpfr_nan_p(op2) && !mpfr_zero_p(op2));
    if (mpfr_inf_p(op2) || mpfr_cmp_si (op1, 1) == 0)
        return mpfr_set_ui(rop, 1, rnd);
    if (mpfr_inf_p(op1))
        return (mpfr_sgn (op2) > 0 ? mpfr_set_inf (rop, 1) : mpfr_set_zero (rop, 1)), 0;
    mpfr_t tmp_rop, rlim;
    mpfr_init2(tmp_rop, mpfr_get_prec(rop));
    mpfr_init2(rlim, mpfr_get_prec(rop));
    int decrease;
    if (mpfr_cmp_si(op1, 1) > 0)
    {
        if (mpfr_sgn(op2) > 0)
        {
            mpfr_set_si(tmp_rop, 1, MPFR_RNDD);
            mpfr_set_inf(rlim, 1);
            decrease = 0;
        }
        else
        {
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_si(rlim, 1, MPFR_RNDU);
            decrease = 1;
        }
    }
    else
    {
        if (mpfr_sgn(op2) > 0)
        {
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_si(rlim, 1, MPFR_RNDU);
            decrease = 0;
        }
        else
        {
            mpfr_set_si(tmp_rop, 1,MPFR_RNDD);
            mpfr_set_inf(rlim, 1);
            decrease = 1;
        }
    }
    if (rnd == MPFR_RNDU)
        mpfr_swap(tmp_rop, rlim);
    int t = p1788_rev_bin(tmp_rop, rlim, op1, p1788_fwd_pow_1, op2, decrease, rnd);
    mpfr_clear(rlim);
    mpfr_set(rop, tmp_rop, rnd);
    mpfr_clear(tmp_rop);
    return t;
}

static int p1788_fwd_pow_2(mpfr_ptr rop, mpfr_srcptr op, const void *env) {
	mpfr_srcptr op1 = (mpfr_srcptr) env;
	return mpfr_pow(rop, op1, op, MPFR_RNDN);
}

// rop = log(op1) / log(op2))
static int mpfr_log_base(mpfr_ptr rop, mpfr_srcptr op1, mpfr_srcptr op2, mpfr_rnd_t rnd)
{
//fprintf(stderr, "mpfr_log_base\n");
//fprintf(stderr, "op1=");
//mpfr_out_str(stderr, 16, 20, op1, MPFR_RNDN);
//fprintf(stderr, "\n");
//fprintf(stderr, "op2=");
//mpfr_out_str(stderr, 16, 20, op2, MPFR_RNDN);
//fprintf(stderr, "\n");
    assert(mpfr_sgn(op1) > 0);
    assert(mpfr_sgn(op2) > 0 && mpfr_cmp_ui(op2, 1) != 0);
    assert(!mpfr_inf_p(op1) || !mpfr_inf_p(op2));
    if (mpfr_inf_p(op2))
        return mpfr_set_zero(rop, mpfr_cmp_ui (op1, 1) >= 0 ? 1 : -1), 0;
    if (mpfr_inf_p (op1))
        return mpfr_set_inf(rop, mpfr_cmp_ui(op2, 1)), 0;
    if (mpfr_cmp_si (op1, 1) == 0)
        return mpfr_set_ui (rop, 0, rnd);
    mpfr_t tmp_rop, rlim;
    mpfr_init2(tmp_rop, mpfr_get_prec(rop));
    mpfr_init2(rlim, mpfr_get_prec(rop));
    int decrease;
    if (mpfr_cmp_si(op1, 1) > 0)
    {
        if (mpfr_cmp_si(op2, 1) > 0)
        {
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_inf(rlim, 1);
            decrease = 0;
        }
        else
        {
            mpfr_set_inf(tmp_rop, -1);
            mpfr_set_zero(rlim, 1);
            decrease = 1;
        }
    }
    else
    {
        if (mpfr_cmp_si(op2, 1) > 0)
        {
            mpfr_set_inf(tmp_rop, -1);
            mpfr_set_zero(rlim, 1);
            decrease = 0;
        }
        else
        {
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_inf(rlim, 1);
            decrease = 1;
        }
    }
    if (rnd == MPFR_RNDU)
        mpfr_swap(tmp_rop, rlim);
    int t = p1788_rev_bin(tmp_rop, rlim, op1, p1788_fwd_pow_2, op2, decrease, rnd);
    mpfr_clear(rlim);
    mpfr_set(rop, tmp_rop, rnd);
    mpfr_clear(tmp_rop);
//fprintf(stderr, "t=%d rop=", t);
//mpfr_out_str(stderr, 16, 20, rop, MPFR_RNDN);
//fprintf(stderr, "\n");
    return t;
}

static int p1788_fwd_atan2_1(mpfr_ptr rop, mpfr_srcptr op, const void *env) {
	mpfr_srcptr op2 = (mpfr_srcptr) env;
//fprintf(stderr, "  p1788_fwd_atan2\n");
//fprintf(stderr, "  op=");
//mpfr_out_str(stderr, 16, 20, op, MPFR_RNDN);
//fprintf(stderr, "\n");
//fprintf(stderr, "  op2=");
//mpfr_out_str(stderr, 16, 20, op2, MPFR_RNDN);
//fprintf(stderr, "\n");
	int t =  mpfr_atan2(rop, op, op2, MPFR_RNDN);
//fprintf(stderr, "  t=%d rop=", t);
//mpfr_out_str(stderr, 16, 20, rop, MPFR_RNDN);
//fprintf(stderr, "\n");
    return t;
}

// rop = op1 * tan(op2))
static int mpfr_mul_tan(mpfr_ptr rop, mpfr_srcptr op1, mpfr_srcptr op2, mpfr_rnd_t rnd)
{
//fprintf(stderr, "mpfr_mul_tan rnd=%d\n", rnd);
//fprintf(stderr, "op1=");
//mpfr_out_str(stderr, 16, 20, op1, MPFR_RNDN);
//fprintf(stderr, "\n");
//fprintf(stderr, "op2=");
//mpfr_out_str(stderr, 16, 20, op2, MPFR_RNDN);
//fprintf(stderr, "\n");
    assert(mpfr_number_p(op1) && !mpfr_zero_p(op1));
    assert(mpfr_number_p(op2) && !mpfr_zero_p(op2));
    mpfr_t tmp_rop, rlim;
    mpfr_init2(tmp_rop, mpfr_get_prec(rop));
    mpfr_init2(rlim, mpfr_get_prec(rop));

    mpz_t k;
    mpz_init (k);
    mpfr_quadrant (k, op2);
    assert (mpz_cmp_si (k, -2) >= 0 && mpz_cmp_si (k, 1) <= 0);
    int decrease;
    switch (mpz_get_si(k))
    {
        case -2:
            mpfr_set_inf(tmp_rop, -1);
            mpfr_set_zero(rlim, -1);
            decrease = 1;
            break;
        case -1:
            mpfr_set_inf(tmp_rop, -1);
            mpfr_set_zero(rlim, -1);
            decrease = 0;
            break;
        case 0:
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_inf(rlim, 1);
            decrease = 0;
            break;
        case 1:
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_inf(rlim, 1);
            decrease = 1;
            break;
        default:
            assert(0);
    }
    mpz_clear (k);
    assert (decrease == (mpfr_sgn (op1) > 0 ? 0 : 1));
    if (rnd == MPFR_RNDU)
        mpfr_swap(tmp_rop, rlim);
    int t = p1788_rev_bin(tmp_rop, rlim, op2, p1788_fwd_atan2_1, op1, decrease, rnd);
    mpfr_clear(rlim);
    mpfr_set(rop, tmp_rop, rnd);
    mpfr_clear(tmp_rop);
//fprintf(stderr, "t=%d rop=", t);
//mpfr_out_str(stderr, 16, 20, rop, MPFR_RNDN);
//fprintf(stderr, "\n");
    return t;
}

static int p1788_fwd_atan2_2(mpfr_ptr rop, mpfr_srcptr op, const void *env) {
	mpfr_srcptr op1 = (mpfr_srcptr) env;
	return mpfr_atan2(rop, op1, op, MPFR_RNDN);
}

// rop = op1 * cot(op2))
static int mpfr_mul_cot(mpfr_ptr rop, mpfr_srcptr op1, mpfr_srcptr op2, mpfr_rnd_t rnd)
{
//fprintf(stderr, "mpfr_mul_cot rnd=%d\n", rnd);
//fprintf(stderr, "op1=");
//mpfr_out_str(stderr, 16, 20, op1, MPFR_RNDN);
//fprintf(stderr, "\n");
//fprintf(stderr, "op2=");
//mpfr_out_str(stderr, 16, 20, op2, MPFR_RNDN);
//fprintf(stderr, "\n");
    assert(mpfr_number_p(op1) && !mpfr_zero_p(op1));
    assert(mpfr_number_p(op2) && !mpfr_zero_p(op2));
    mpfr_t tmp_rop, rlim;
    mpfr_init2(tmp_rop, mpfr_get_prec(rop));
    mpfr_init2(rlim, mpfr_get_prec(rop));

    mpz_t k;
    mpz_init (k);
    mpfr_quadrant (k, op2);
    assert (mpz_cmp_si (k, -2) >= 0 && mpz_cmp_si (k, 1) <= 0);
    int decrease;
    switch (mpz_get_si(k))
    {
        case -2:
            mpfr_set_inf(tmp_rop, -1);
            mpfr_set_zero(rlim, -1);
            decrease = 0;
            break;
        case -1:
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_inf(rlim, 1);
            decrease = 0;
            break;
        case 0:
            mpfr_set_zero(tmp_rop, 1);
            mpfr_set_inf(rlim, 1);
            decrease = 1;
            break;
        case 1:
            mpfr_set_inf(tmp_rop, -1);
            mpfr_set_zero(rlim, -1);
            decrease = 1;
            break;
        default:
            assert(0);
    }
    mpz_clear (k);
    assert (decrease == (mpfr_sgn (op1) > 0 ? 1 : 0));
    if (rnd == MPFR_RNDU)
        mpfr_swap(tmp_rop, rlim);
    int t = p1788_rev_bin(tmp_rop, rlim, op2, p1788_fwd_atan2_2, op1, decrease, rnd);
    mpfr_clear(rlim);
    mpfr_set(rop, tmp_rop, rnd);
    mpfr_clear(tmp_rop);
//fprintf(stderr, "t=%d rop=", t);
//mpfr_out_str(stderr, 16, 20, rop, MPFR_RNDN);
//fprintf(stderr, "\n");
    return t;
}
