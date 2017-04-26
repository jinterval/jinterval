
#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_M_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_M_HPP

#include <assert.h>
#include <mpfi.h>

extern "C" {
#include "p1788.h"
#include "mpfi_p1788.h"
}

#include "p1788/exception/exception.hpp"
#include "p1788/decoration/decoration.hpp"
#include "p1788/util/mpfr_var.hpp"
#include "p1788/util/mixed_type_traits.hpp"
#include "p1788/infsup/base_interval.hpp"

namespace p1788 {
namespace flavor {
namespace infsup {
namespace setbased {

static int signal_exception(int exc) {
    switch (exc) {
        case EXC_UNDEFINED_OPERATION:
            p1788::exception::signal_undefined_operation();
            break;
        case EXC_POSSIBLY_UNDEFINED_OPERATION:
            p1788::exception::signal_possibly_undefined_operation();
            break;
        case EXC_INTERVAL_PART_OF_NAI:
            p1788::exception::signal_interval_part_of_nai();
            break;
        case EXC_INVALID_OPERAND:
            p1788::exception::signal_invalid_operand();
            break;
        default:
            return exc;
            break;
    }
    return 0;
}

template<typename T>
class mpfr_bin_ieee754_flavor_m;

template<typename T>
struct REP
{
    T first;
    T second;

    REP(T inf, T sup) {
        first = inf;
        second = sup;
    }

    // empty
    REP() {
        first = std::numeric_limits<T>::quiet_NaN();
        second = std::numeric_limits<T>::quiet_NaN();
    }

    REP(mpfi_srcptr m) {
        if (mpfi_is_empty(m)) {
            first = std::numeric_limits<T>::quiet_NaN();
            second = std::numeric_limits<T>::quiet_NaN();
        } else {
            mpfr_bin_ieee754_flavor_m<T>::mpfr_var::setup();
            typename mpfr_bin_ieee754_flavor_m<T>::mpfr_var left, right;
            mpfr_subnormalize(left(), mpfr_set(left(), &m->left, MPFR_RNDD), MPFR_RNDD);
            mpfr_subnormalize(right(), mpfr_set(right(), &m->right, MPFR_RNDU), MPFR_RNDU);
            first = mpfr_zero_p(left()) ? -0.0 : left.template get<T>(MPFR_RNDD);
            second = mpfr_zero_p(right()) ? +0.0 : right.template get<T>(MPFR_RNDU);
        }
    }

    bool is_empty() const {
        return !(first <= second);
    }

    void get_fi(mpfi_ptr m) const {
        mpfi_init2(m, mpfr_bin_ieee754_flavor_m<T>::mpfr_var::PREC);
        if (is_empty()) {
            mpfi_p1788_empty(m);
        } else {
            mpfr_bin_ieee754_flavor_m<T>::mpfr_var::setup();
            typename mpfr_bin_ieee754_flavor_m<T>::mpfr_var left(first, MPFR_RNDD), right(second, MPFR_RNDU);
            mpfi_p1788_numsToInterval(m, left(), right());
        }
    }
};

template<typename T>
static bool operator==(REP<T> const& x, REP<T> const& y) {
    return x.first == y.first && x.second == y.second;
}

template<typename T>
struct REP_DEC
{
    REP<T> first;
    decoration::decoration second;

    REP_DEC(REP<T> intvl, decoration::decoration dec) {
        first = intvl;
        second = dec;
    }

    // nai
    REP_DEC() {
        first = REP<T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
        second = decoration::decoration::ill;
    }

    REP_DEC(mpfi_srcptr m, decoration::decoration dec) {
        if (dec == decoration::decoration::ill) {
            first.first = first.second = std::numeric_limits<T>::quiet_NaN();
        } else {
            first = REP<T>(m);
        }
        second = dec;
    }

    bool is_nai() const {
        return second == decoration::decoration::ill;
    }

    decoration::decoration get_fi(mpfi_ptr m, decoration::decoration dec) const {
        first.get_fi(m);
        return std::min(dec, second);
    }
};

template<typename T>
static bool operator==(REP_DEC<T> const& x, REP_DEC<T> const& y) {
    return x.first == y.first && x.second == y.second;
}

template<typename T>
class mpfr_bin_ieee754_flavor_m
{

public:
    typedef p1788::util::mpfr_var<
    std::numeric_limits<T>::digits,
        std::numeric_limits<T>::has_denorm != std::denorm_present ? std::numeric_limits<T>::min_exponent
        : std::numeric_limits<T>::min_exponent - std::numeric_limits<T>::digits + 1,
        std::numeric_limits<T>::max_exponent,
        std::numeric_limits<T>::has_denorm == std::denorm_present
        >   mpfr_var;

    typedef REP<T> representation;
    typedef REP_DEC<T> representation_dec;

    static bool is_valid(representation const& x) {
        bool r = (x.first <= x.second && x.first != std::numeric_limits<T>::infinity() && x.second != -std::numeric_limits<T>::infinity()) || (std::isnan(x.first) && std::isnan(x.second));
        return r || !exception::signal_invalid_operand();
    }

    static bool is_valid(representation_dec const& x) {
        bool r;
        switch (x.second) {
            case decoration::decoration::com:
                r = x.first.first <= x.first.second && x.first.first != -std::numeric_limits<T>::infinity() && x.first.second != std::numeric_limits<T>::infinity();
                break;
            case decoration::decoration::dac:
                r = x.first.first <= x.first.second && x.first.first != std::numeric_limits<T>::infinity() && x.first.second != -std::numeric_limits<T>::infinity();
                break;
            case decoration::decoration::def:
                r = x.first.first <= x.first.second && x.first.first != std::numeric_limits<T>::infinity() && x.first.second != -std::numeric_limits<T>::infinity();
                break;
            case decoration::decoration::trv:
                r = (x.first.first <= x.first.second && x.first.first != std::numeric_limits<T>::infinity() && x.first.second != -std::numeric_limits<T>::infinity()) || (std::isnan(x.first.first) && std::isnan(x.first.second));
                break;
            case decoration::decoration::ill:
                r = std::isnan(x.first.first) && std::isnan(x.first.second);
                break;
            default:
                r = false;
                break;
        }
        return r || !exception::signal_invalid_operand();
    }

    static representation empty() {
        return REP<T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
    }

    static representation_dec empty_dec() {
        return REP_DEC<T>(REP<T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN()), decoration::decoration::trv);
    }

    static representation entire() {
        return REP<T>(-std::numeric_limits<T>::infinity(), +std::numeric_limits<T>::infinity());
    }

    static representation_dec entire_dec() {
        return REP_DEC<T>(REP<T>(-std::numeric_limits<T>::infinity(), +std::numeric_limits<T>::infinity()), decoration::decoration::dac);
    }

    static representation_dec nai() {
        return REP_DEC<T>(REP<T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN()), decoration::decoration::ill);
    }

    template<typename T1>
    static representation convert_type(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_convertType(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec convert_type(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_convertType(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation pos(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_pos(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec pos(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_pos(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation neg(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_neg(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec neg(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_neg(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation add(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_add(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec add(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_add(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation sub(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sub(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sub(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sub(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation mul(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_mul(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec mul(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_mul(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation div(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_div(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec div(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_div(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1>
    static representation recip(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_recip(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec recip(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_recip(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation sqr(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sqr(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec sqr(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sqr(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation sqrt(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrt(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec sqrt(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrt(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation fma(REP<T1> const& x, REP<T2> const& y, REP<T3> const& z) {
        mpfi_t mr, mx, my, mz;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || !mpfr_bin_ieee754_flavor<T3>::is_valid(z)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        z.get_fi(mz);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_fma(mr, mx, my, mz));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        mpfi_clear(mz);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec fma(REP_DEC<T1> const& x, REP_DEC<T2> const& y, REP_DEC<T3> const& z) {
        mpfi_t mr, mx, my, mz;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || !mpfr_bin_ieee754_flavor<T3>::is_valid(z) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill || z.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        d = z.get_fi(mz, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_fma(mr, mx, my, mz)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        mpfi_clear(mz);
        return r;
    }

    template<typename T1>
    static representation pown(REP<T1> const& x, int p) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_pown(mr, mx, p));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec pown(REP_DEC<T1> const& x, int p) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_pown(mr, mx, p)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_pow(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_pow(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1>
    static representation exp(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_exp(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec exp(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_exp(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation exp2(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_exp2(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec exp2(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_exp2(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation exp10(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_exp10(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec exp10(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_exp10(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation log(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_log(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec log(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_log(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation log2(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_log2(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec log2(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_log2(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation log10(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_log10(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec log10(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_log10(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation sin(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sin(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec sin(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sin(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation cos(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cos(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec cos(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_cos(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation tan(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_tan(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec tan(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_tan(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation asin(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_asin(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec asin(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_asin(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation acos(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_acos(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec acos(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_acos(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation atan(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec atan(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_atan(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2(REP<T1> const& y, REP<T2> const& x) {
        mpfi_t mr, my, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(y) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        y.get_fi(my);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2(mr, my, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(my);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2(REP_DEC<T1> const& y, REP_DEC<T2> const& x) {
        mpfi_t mr, my, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(y) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || y.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = y.get_fi(my, decoration::decoration::com);
        d = x.get_fi(mx, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2(mr, my, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(my);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation sinh(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sinh(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec sinh(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sinh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation cosh(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cosh(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec cosh(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_cosh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation tanh(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_tanh(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec tanh(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_tanh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation asinh(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_asinh(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec asinh(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_asinh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation acosh(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_acosh(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec acosh(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_acosh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation atanh(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atanh(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec atanh(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_atanh(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation sign(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sign(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec sign(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_sign(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation ceil(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_ceil(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec ceil(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_ceil(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation floor(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_floor(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec floor(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_floor(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation trunc(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_trunc(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec trunc(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_trunc(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation round_ties_to_even(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToEven(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec round_ties_to_even(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToEven(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation round_ties_to_away(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToAway(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec round_ties_to_away(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_roundTiesToAway(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation abs(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_abs(mr, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation_dec abs(REP_DEC<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_abs(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation min(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_min(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec min(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_min(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation max(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_max(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec max(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        d = y.get_fi(my, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_max(mr, mx, my)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, std::min(static_cast<decoration::decoration>(locdec), d));
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static std::pair<representation,representation> mul_rev_to_pair(REP<T1> const& b, REP<T2> const& c) {
        mpfi_t mr1, mr2, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)) return std::pair<representation, representation>(empty(), empty());
        mpfi_init2(mr1, mpfr_var::PREC);
        mpfi_init2(mr2, mpfr_var::PREC);
        b.get_fi(mb);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_mulRevToPairSubnormal(mr1, mr2, mb, mc);
        representation r1(mr1);
        representation r2(mr2);
        mpfi_clear(mr1);
        mpfi_clear(mr2);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return std::pair<representation,representation>(r1, r2);
    }

    template<typename T1, typename T2>
    static std::pair<representation_dec,representation_dec> mul_rev_to_pair(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        mpfi_t mr1, mr2, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || b.second == decoration::decoration::ill || c.second == decoration::decoration::ill) return std::pair<representation_dec, representation_dec>(nai(), nai());
        mpfi_init2(mr1, mpfr_var::PREC);
        mpfi_init2(mr2, mpfr_var::PREC);
        decoration::decoration d = b.get_fi(mb, decoration::decoration::com);
        d = c.get_fi(mc, d);
        mpfr_var::setup();
        int locdec = mpfi_p1788_mulRevToPairSubnormal(mr1, mr2, mb, mc) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r1(mr1, std::min(static_cast<decoration::decoration>(locdec), d));
        representation_dec r2(mr2, decoration::decoration::trv);
        mpfi_clear(mr1);
        mpfi_clear(mr2);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return std::pair<representation_dec,representation_dec>(r1, r2);
    }

    template<typename T1, typename T2>
    static representation sqr_rev(REP<T1> const& c, REP<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRev(mr, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sqr_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRev(mr, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation sqr_rev(REP<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRevEntire(mr, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1>
    static representation_dec sqr_rev(REP_DEC<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sqrRevEntire(mr, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation abs_rev(REP<T1> const& c, REP<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_absRev(mr, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec abs_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_absRev(mr, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation abs_rev(REP<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_absRevEntire(mr, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1>
    static representation_dec abs_rev(REP_DEC<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_absRevEntire(mr, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation pown_rev(REP<T1> const& c, REP<T2> const& x, int p) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRev(mr, mc, mx, p));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pown_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x, int p) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRev(mr, mc, mx, p));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation pown_rev(REP<T1> const& c, int p) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRevEntire(mr, mc, p));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1>
    static representation_dec pown_rev(REP_DEC<T1> const& c, int p) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_pownRevEntire(mr, mc, p));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation sin_rev(REP<T1> const& c, REP<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRev(mr, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sin_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRev(mr, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation sin_rev(REP<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRevEntire(mr, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1>
    static representation_dec sin_rev(REP_DEC<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_sinRevEntire(mr, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation cos_rev(REP<T1> const& c, REP<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRev(mr, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cos_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRev(mr, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation cos_rev(REP<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRevEntire(mr, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1>
    static representation_dec cos_rev(REP_DEC<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cosRevEntire(mr, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation tan_rev(REP<T1> const& c, REP<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRev(mr, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec tan_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRev(mr, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation tan_rev(REP<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRevEntire(mr, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1>
    static representation_dec tan_rev(REP_DEC<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_tanRevEntire(mr, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation cosh_rev(REP<T1> const& c, REP<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRev(mr, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cosh_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        mpfi_t mr, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x) || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRev(mr, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static representation cosh_rev(REP<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRevEntire(mr, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1>
    static representation_dec cosh_rev(REP_DEC<T1> const& c) {
        mpfi_t mr, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_coshRevEntire(mr, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation mul_rev(REP<T1> const& b, REP<T2> const& c, REP<T3> const& x) {
        mpfi_t mr, mb, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRev(mr, mb, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec mul_rev(REP_DEC<T1> const& b, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        mpfi_t mr, mb, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x) || b.second == decoration::decoration::ill || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRev(mr, mb, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation mul_rev(REP<T1> const& b, REP<T2> const& c) {
        mpfi_t mr, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRevEntire(mr, mb, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec mul_rev(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        mpfi_t mr, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || b.second == decoration::decoration::ill || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_mulRevEntire(mr, mb, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation pow_rev1(REP<T1> const& b, REP<T2> const& c, REP<T3> const& x) {
        mpfi_t mr, mb, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1(mr, mb, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec pow_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        mpfi_t mr, mb, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x) || b.second == decoration::decoration::ill || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1(mr, mb, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow_rev1(REP<T1> const& b, REP<T2> const& c) {
        mpfi_t mr, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1Entire(mr, mb, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        mpfi_t mr, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || b.second == decoration::decoration::ill || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev1Entire(mr, mb, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation pow_rev2(REP<T1> const& a, REP<T2> const& c, REP<T3> const& x) {
        mpfi_t mr, ma, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2(mr, ma, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec pow_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        mpfi_t mr, ma, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x) || a.second == decoration::decoration::ill || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2(mr, ma, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow_rev2(REP<T1> const& a, REP<T2> const& c) {
        mpfi_t mr, ma, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2Entire(mr, ma, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c) {
        mpfi_t mr, ma, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || a.second == decoration::decoration::ill || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_powRev2Entire(mr, ma, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation atan2_rev1(REP<T1> const& b, REP<T2> const& c, REP<T3> const& x) {
        mpfi_t mr, mb, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1(mr, mb, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec atan2_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        mpfi_t mr, mb, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x) || b.second == decoration::decoration::ill || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1(mr, mb, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2_rev1(REP<T1> const& b, REP<T2> const& c) {
        mpfi_t mr, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1Entire(mr, mb, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        mpfi_t mr, mb, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || b.second == decoration::decoration::ill || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        b.get_fi(mb, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev1Entire(mr, mb, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mb);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation atan2_rev2(REP<T1> const& a, REP<T2> const& c, REP<T3> const& x) {
        mpfi_t mr, ma, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma);
        c.get_fi(mc);
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2(mr, ma, mc, mx));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec atan2_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        mpfi_t mr, ma, mc, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x) || a.second == decoration::decoration::ill || c.second == decoration::decoration::ill || x.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2(mr, ma, mc, mx));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2_rev2(REP<T1> const& a, REP<T2> const& c) {
        mpfi_t mr, ma, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma);
        c.get_fi(mc);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2Entire(mr, ma, mc));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c) {
        mpfi_t mr, ma, mc;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(a) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || a.second == decoration::decoration::ill || c.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        a.get_fi(ma, decoration::decoration::trv);
        c.get_fi(mc, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_atan2Rev2Entire(mr, ma, mc));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(ma);
        mpfi_clear(mc);
        return r;
    }

    template<typename T1, typename T2>
    static representation cancel_minus(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelMinus(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cancel_minus(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx, decoration::decoration::trv);
        y.get_fi(my, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelMinus(mr, mx, my));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation cancel_plus(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelPlus(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cancel_plus(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx, decoration::decoration::trv);
        y.get_fi(my, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_cancelPlus(mr, mx, my));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation intersection(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_intersection(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec intersection(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx, decoration::decoration::trv);
        y.get_fi(my, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_intersection(mr, mx, my));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation convex_hull(REP<T1> const& x, REP<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)) return empty();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        y.get_fi(my);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_convexHull(mr, mx, my));
        representation r(mr);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec convex_hull(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        mpfi_t mr, mx, my;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y) || x.second == decoration::decoration::ill || y.second == decoration::decoration::ill) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx, decoration::decoration::trv);
        y.get_fi(my, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_subnormalize(mr, mpfi_p1788_convexHull(mr, mx, my));
        representation_dec r(mr, decoration::decoration::trv);
        mpfi_clear(mr);
        mpfi_clear(mx);
        mpfi_clear(my);
        return r;
    }

    template<typename T1, typename T2>
    static representation nums_to_interval(T1 l, T2 u) {
        mpfi_t mr;
        mpfi_init2(mr, mpfr_var::PREC);
        mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var ml(l, MPFR_RNDN);
        mpfr_bin_ieee754_flavor_m<T2> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T2> ::mpfr_var mu(u, MPFR_RNDN);
        mpfr_var::setup();
        int locdec = mpfi_p1788_numsToInterval(mr, ml(), mu());
        if (locdec >= 0) {
            mpfi_p1788_subnormalize(mr, locdec);
        } else {
            signal_exception(locdec);
        }
        representation r(mr);
        mpfi_clear(mr);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec nums_to_decorated_interval(T1 l, T2 u) {
        mpfi_t mr;
        mpfi_init2(mr, mpfr_var::PREC);
        mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var ml(l, MPFR_RNDN);
        mpfr_bin_ieee754_flavor_m<T2> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T2> ::mpfr_var mu(u, MPFR_RNDN);
        mpfr_var::setup();
        int locdec = mpfi_p1788_numsToInterval(mr, ml(), mu());
        if (locdec >= 0) {
            locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        } else {
            locdec = signal_exception(locdec);
        }
        representation_dec r(mr, static_cast<decoration::decoration>(locdec));
        mpfi_clear(mr);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec nums_dec_to_decorated_interval(T1 l, T2 u, decoration::decoration dec) {
        mpfi_t mr;
        if (!decoration::is_valid(dec)) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var ml(l, MPFR_RNDN);
        mpfr_bin_ieee754_flavor_m<T2> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T2> ::mpfr_var mu(u, MPFR_RNDN);
        mpfr_var::setup();
        int locdec = mpfi_p1788_numsDecToInterval(mr, ml(), mu(), static_cast<int>(dec));
        if (locdec >= 0) {
            locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        } else {
            locdec = signal_exception(locdec);
        }
        representation_dec r(mr, static_cast<decoration::decoration>(locdec));
        mpfi_clear(mr);
        return r;
    }

    static representation text_to_interval(std::string const& s) {
        mpfi_t mr;
        mpfi_init2(mr, mpfr_var::PREC);
        mpfr_var::setup();
        int locdec = mpfi_p1788_textToInterval(mr, s.c_str(), 0);
        if (locdec >= 0) {
            mpfi_p1788_subnormalize(mr, locdec);
        } else {
            signal_exception(locdec);
        }
        representation r(mr);
        mpfi_clear(mr);
        return r;
    }

    static representation_dec text_to_decorated_interval(std::string const& s) {
        mpfi_t mr;
        mpfi_init2(mr, mpfr_var::PREC);
        mpfr_var::setup();
        int locdec = mpfi_p1788_textToDecoratedInterval(mr, s.c_str(), 1);
        if (locdec >= 0) {
            locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        } else {
            locdec = signal_exception(locdec);
        }
        representation_dec r(mr, static_cast<decoration::decoration>(locdec));
        mpfi_clear(mr);
        return r;
    }

    template<typename T1>
    static T inf(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_infSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T inf(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_infSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T sup(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_supSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T sup(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_supSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T mid(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_midSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T mid(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_midSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T rad(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_radSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T rad(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_radSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T wid(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_widSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T wid(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_widSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T mag(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_magSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T mag(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_magSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T mig(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_migSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static T mig(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::numeric_limits<T>::quiet_NaN();
        mpfr_var mr;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_migSubnormal(mr(), mx);
        T r = mr.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static std::pair<T,T> mid_rad(REP<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return std::pair<T,T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
        mpfr_var mr1, mr2;
        x.get_fi(mx);
        mpfr_var::setup();
        mpfi_p1788_midRadSubnormal(mr1(), mr2(), mx);
        T r1 = mr1.template get<T>(MPFR_RNDN);
        T r2 = mr2.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return std::pair<T,T>(r1, r2);;
    }

    template<typename T1>
    static std::pair<T,T> mid_rad(REP_DEC<T1> const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || x.second == decoration::decoration::ill) return std::pair<T,T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());
        mpfr_var mr1, mr2;
        x.get_fi(mx, decoration::decoration::trv);
        mpfr_var::setup();
        mpfi_p1788_midRadSubnormal(mr1(), mr2(), mx);
        T r1 = mr1.template get<T>(MPFR_RNDN);
        T r2 = mr2.template get<T>(MPFR_RNDN);
        mpfi_clear(mx);
        return std::pair<T,T>(r1, r2);;
    }

    static bool is_empty(representation const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x)) return false;
        x.get_fi(mx);
        int r = mpfi_p1788_isEmpty(mx);
        mpfi_clear(mx);
        return r;
    }

    static bool is_empty(representation_dec const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x) || x.second == decoration::decoration::ill) return false;
        x.get_fi(mx, decoration::decoration::trv);
        int r = mpfi_p1788_isEmpty(mx);
        mpfi_clear(mx);
        return r;
    }

    static bool is_entire(representation const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x)) return false;
        x.get_fi(mx);
        int r = mpfi_p1788_isEntire(mx);
        mpfi_clear(mx);
        return r;
    }

    static bool is_entire(representation_dec const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x) || x.second == decoration::decoration::ill) return false;
        x.get_fi(mx, decoration::decoration::trv);
        int r = mpfi_p1788_isEntire(mx);
        mpfi_clear(mx);
        return r;
    }

    static bool is_nai(representation_dec const& x) {
        return is_valid(x) && x.second == decoration::decoration::ill;
    }

    static bool is_common_interval(representation const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x)) return false;
        x.get_fi(mx);
        int r = mpfi_p1788_isCommonInterval(mx);
        mpfi_clear(mx);
        return r;
    }

    static bool is_common_interval(representation_dec const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x) || x.second == decoration::decoration::ill) return false;
        x.get_fi(mx, decoration::decoration::trv);
        int r = mpfi_p1788_isCommonInterval(mx);
        mpfi_clear(mx);
        return r;
    }

    static bool is_singleton(representation const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x)) return false;
        x.get_fi(mx);
        int r = mpfi_p1788_isSingleton(mx);
        mpfi_clear(mx);
        return r;
    }

    static bool is_singleton(representation_dec const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x) || x.second == decoration::decoration::ill) return false;
        x.get_fi(mx, decoration::decoration::trv);
        int r = mpfi_p1788_isSingleton(mx);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static bool is_member(T1 m, representation const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x)) return false;
        mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var mm(m, MPFR_RNDN);
        x.get_fi(mx);
        int r = mpfi_p1788_isMember(mm(), mx);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static bool is_member(T1 m, representation_dec const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x) || x.second == decoration::decoration::ill) return false;
        mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var::setup();
        typename mpfr_bin_ieee754_flavor_m<T1> ::mpfr_var mm(m, MPFR_RNDN);
        x.get_fi(mx, decoration::decoration::trv);
        int r = mpfi_p1788_isMember(mm(), mx);
        mpfi_clear(mx);
        return r;
    }

    template<typename T1>
    static bool equal(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_equal(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool equal(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_equal(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool subset(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_subset(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool subset(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_subset(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool less(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_less(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool less(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_less(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool precedes(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_precedes(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool precedes(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_precedes(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool interior(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_interior(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool interior(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_interior(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool strictly_less(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_strictLess(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool strictly_less(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_strictLess(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool strictly_precedes(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_strictPrecedes(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool strictly_precedes(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_strictPrecedes(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool disjoint(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return false;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_disjoint(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static bool disjoint(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return false;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_disjoint(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return r;
    }

    template<typename T1>
    static overlapping::overlapping_state overlap(representation const& a, REP<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b)) return overlapping::overlapping_state::undefined;
        a.get_fi(ma);
        b.get_fi(mb);
        int r = mpfi_p1788_overlap(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return static_cast<overlapping::overlapping_state>(r);
    }

    template<typename T1>
    static overlapping::overlapping_state overlap(representation_dec const& a, REP_DEC<T1> const& b) {
        mpfi_t ma, mb;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(a) || !mpfr_bin_ieee754_flavor<T1>::is_valid(b) || a.second == decoration::decoration::ill || b.second == decoration::decoration::ill) return overlapping::overlapping_state::undefined;
        a.get_fi(ma, decoration::decoration::trv);
        b.get_fi(mb, decoration::decoration::trv);
        int r = mpfi_p1788_overlap(ma, mb);
        mpfi_clear(ma);
        mpfi_clear(mb);
        return static_cast<overlapping::overlapping_state>(r);
    }

    template<typename T1>
    static representation_dec new_dec(REP<T1> const& x) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_newDec(mr, mx)) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, static_cast<decoration::decoration>(locdec));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    static decoration::decoration decoration_part(representation_dec const& x) {
        if (!is_valid(x)) return decoration::decoration::ill;;
        return x.second;
    }

    template<typename T1>
    static representation interval_part(REP_DEC<T1> const& x) {
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)) return empty();
        if (x.second == decoration::decoration::ill) {
            exception::signal_interval_part_of_nai();
            return empty();
        }
        return convert_type<T1>(x.first);
    }

    template<typename T1>
    static representation_dec set_dec(REP<T1> const& x, decoration::decoration dec) {
        mpfi_t mr, mx;
        if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !decoration::is_valid(dec)) return nai();
        mpfi_init2(mr, mpfr_var::PREC);
        x.get_fi(mx);
        mpfr_var::setup();
        int locdec = mpfi_p1788_subnormalize(mr, mpfi_p1788_setDec(mr, mx, static_cast<int>(dec))) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        representation_dec r(mr, static_cast<decoration::decoration>(locdec));
        mpfi_clear(mr);
        mpfi_clear(mx);
        return r;
    }

    static representation exact_to_interval(std::string const& s) {
        mpfi_t mr;
        mpfi_init2(mr, mpfr_var::PREC);
        mpfr_var::setup();
        int locdec = mpfi_p1788_exactToInterval(mr, s.c_str(), 0);
        if (locdec >= 0) {
            mpfi_p1788_subnormalize(mr, locdec);
        } else {
            signal_exception(locdec);
        }
        representation r(mr);
        mpfi_clear(mr);
        return r;
    }

    static representation_dec exact_to_decorated_interval(std::string const& s) {
        mpfi_t mr;
        mpfi_init2(mr, mpfr_var::PREC);
        mpfr_var::setup();
        int locdec = mpfi_p1788_exactToDecoratedInterval(mr, s.c_str(), 1);
        if (locdec >= 0) {
            locdec = mpfi_p1788_subnormalize(mr, locdec) & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;
        } else {
            locdec = signal_exception(locdec);
        }
        representation_dec r(mr, static_cast<decoration::decoration>(locdec));
        mpfi_clear(mr);
        return r;
    }

    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_interval_to_text(std::basic_ostream<CharT, Traits>& os, representation const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x)) return os << "[]";
        char *r;
        x.get_fi(mx);
        mpfr_var::setup();
        r = mpfi_p1788_intervalToExact(mx, 0);
        mpfi_clear(mx);
        std::string s(r);
        free(r);
        os << s;
        return os;
    }

    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_interval_to_text(std::basic_ostream<CharT, Traits>& os, representation_dec const& x) {
        mpfi_t mx;
        if (!mpfr_bin_ieee754_flavor<T>::is_valid(x) || x.second == decoration::decoration::ill) return os << "[nai]";
        char *r;
        decoration::decoration d = x.get_fi(mx, decoration::decoration::com);
        mpfr_var::setup();
        r = mpfi_p1788_intervalToExact(mx, static_cast<int>(d));
        mpfi_clear(mx);
        std::string s(r);
        free(r);
        os << s;
        return os;
    }

    template< typename CharT, typename Traits >
    static std::basic_istream<CharT, Traits>&
    operator_text_to_interval(std::basic_istream<CharT, Traits>& is,
            representation& x)
    {
        int state = (is.flags() & std::ios_base::skipws) ? 0 : 1;
        std::string input;
        while (is && state != 99 && state != 100)
        {
           char ch;
           try
           {
               ch = is.peek();
           }
           catch (std::ios_base::failure& e)
           {
               if (!is.eof())
               {
                   throw;
               }
               ch = '\0';
           }
           if (is.eof() || ch == '\n')
           {
               state = state == 3 || state == 5 || state == 6 || state == 7 || state == 8 || state == 11 ? 100 : 99;
               break;
           }
           switch (state)
           {
              case 0:
                  if (std::isspace(ch))
                  {
                     is.get();
                     break;
                  }
              case 1:
                  if (ch == '[') state = 2;
                  else if (ch == '+' || ch == '-' || ch == '.' || std::isdigit(ch)) state = 4;
                  else { state = 99; break; }
                  input += ch;
                  is.get();
                  break;
              case 2:
                  if (ch == ']') state = 3;
                  input += ch;
                  is.get();
                  break;
               case 3:
                  if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 4:
                  if (ch == '?') state = 5;
                  input += ch;
                  is.get();
                  break;
               case 5:
                  if (std::isdigit(ch)) state = 6;
                  else if (ch == '?') state = 7;
                  else if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
                  else if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 6:
                  if (std::isdigit(ch)) state = 6;
                  else if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
                  else if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 7:
                  if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
                  else if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 8:
                  if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 9:
                  if (ch == '+' || ch == '-') state = 10;
                  else if (std::isdigit(ch)) state = 11;
                  else { state = 99; break; }
                  input += ch;
                  is.get();
                  break;
               case 10:
                  if (std::isdigit(ch)) state = 11;
                  else { state = 99; break; }
                  input += ch;
                  is.get();
                  break;
               case 11:
                  if (std::isdigit(ch)) state = 11;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 12:
                  state = 13;
                  input += ch;
                  is.get();
                  break;
               case 13:
                  state = 14;
                  input += ch;
                  is.get();
                  break;
               case 14:
                  state = 100;
                  input += ch;
                  is.get();
                  break;
           }
        }
        if (is && state == 100)
        {
            representation r;
            exception::exception_bits saved_cwd = exception::cwd();
            exception::set_throw_exception_cwd(exception::exception_bits::none_bit);
            exception::exception_bits saved_state = exception::state();
            exception::clear();
            r = text_to_interval(input);
            exception::exception_bits new_state = exception::state();
            exception::state() = saved_state;
            exception::set_throw_exception_cwd(saved_cwd);
            if (new_state == exception::exception_bits::none_bit)
            {
                x = r;
            }
            else
            {
                is.setstate(std::ios_base::failbit);
                if (new_state & exception::exception_bits::undefined_operation_bit)
                    exception::signal_undefined_operation();
                if (new_state & exception::exception_bits::possibly_undefined_operation_bit)
                    exception::signal_possibly_undefined_operation();
            }
    /*
            int exc = text_to_interval;
            signal_exception(exc);
            if (exc >= 0)
                x = r;
            else
                is.setstate(std::ios_base::failbit);
     */
        }
        else {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }

    template< typename CharT, typename Traits >
    static std::basic_istream<CharT, Traits>&
    operator_text_to_interval(std::basic_istream<CharT, Traits>& is,
            representation_dec& x)
    {
        int state = (is.flags() & std::ios_base::skipws) ? 0 : 1;
        std::string input;
        while (is && state != 99 && state != 100)
        {
           char ch;
           try
           {
               ch = is.peek();
           }
           catch (std::ios_base::failure& e)
           {
               if (!is.eof())
               {
                   throw;
               }
               ch = '\0';
           }
           if (is.eof() || ch == '\n')
           {
               state = state == 3 || state == 5 || state == 6 || state == 7 || state == 8 || state == 11 ? 100 : 99;
               break;
           }
           switch (state)
           {
              case 0:
                  if (std::isspace(ch))
                  {
                     is.get();
                     break;
                  }
              case 1:
                  if (ch == '[') state = 2;
                  else if (ch == '+' || ch == '-' || ch == '.' || std::isdigit(ch)) state = 4;
                  else { state = 99; break; }
                  input += ch;
                  is.get();
                  break;
              case 2:
                  if (ch == ']') state = 3;
                  input += ch;
                  is.get();
                  break;
               case 3:
                  if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 4:
                  if (ch == '?') state = 5;
                  input += ch;
                  is.get();
                  break;
               case 5:
                  if (std::isdigit(ch)) state = 6;
                  else if (ch == '?') state = 7;
                  else if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
                  else if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 6:
                  if (std::isdigit(ch)) state = 6;
                  else if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
                  else if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 7:
                  if (ch == 'd' || ch == 'D' || ch == 'u' || ch == 'U') state = 8;
                  else if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 8:
                  if (ch == 'e' || ch == 'E') state = 9;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 9:
                  if (ch == '+' || ch == '-') state = 10;
                  else if (std::isdigit(ch)) state = 11;
                  else { state = 99; break; }
                  input += ch;
                  is.get();
                  break;
               case 10:
                  if (std::isdigit(ch)) state = 11;
                  else { state = 99; break; }
                  input += ch;
                  is.get();
                  break;
               case 11:
                  if (std::isdigit(ch)) state = 11;
                  else if (ch == '_') state = 12;
                  else { state = 100; break; }
                  input += ch;
                  is.get();
                  break;
               case 12:
                  state = 13;
                  input += ch;
                  is.get();
                  break;
               case 13:
                  state = 14;
                  input += ch;
                  is.get();
                  break;
               case 14:
                  state = 100;
                  input += ch;
                  is.get();
                  break;
           }
        }
        if (is && state == 100)
        {
            representation_dec r;
            exception::exception_bits saved_cwd = exception::cwd();
            exception::set_throw_exception_cwd(exception::exception_bits::none_bit);
            exception::exception_bits saved_state = exception::state();
            exception::clear();
            r = text_to_decorated_interval(input);
            exception::exception_bits new_state = exception::state();
            exception::state() = saved_state;
            exception::set_throw_exception_cwd(saved_cwd);
            if (new_state == exception::exception_bits::none_bit)
            {
                x = r;
            }
            else
            {
                is.setstate(std::ios_base::failbit);
                if (new_state & exception::exception_bits::undefined_operation_bit)
                    exception::signal_undefined_operation();
                if (new_state & exception::exception_bits::possibly_undefined_operation_bit)
                    exception::signal_possibly_undefined_operation();
            }
    /*
            int exc = text_to_decorated_interval;
            signal_exception(exc);
            if (exc >= 0)
                x = r;
            else
                is.setstate(std::ios_base::failbit);
     */
        }
        else {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }


    static representation copy(representation const& other) {
        return convert_type<T>(other);
    }
    static representation_dec copy(representation_dec const& other) {
        return convert_type<T>(other);
    }
};

}}}}

#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_M_HPP
