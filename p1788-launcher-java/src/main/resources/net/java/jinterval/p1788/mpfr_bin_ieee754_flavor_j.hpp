
#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_J_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_J_HPP

extern "C" {
#include "p1788.h"
}

#include "p1788/exception/exception.hpp"
#include "p1788/decoration/decoration.hpp"
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
struct REP
{
    T first;
    T second;

    REP() {
        p1788_bar_empty(static_cast<int>(util::type_precision_order<T>::value), this);
    }

    REP(T inf, T sup) {
        first = inf;
        second = sup;
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

    REP_DEC() {
        p1788_dec_nai(static_cast<int>(util::type_precision_order<T>::value), this);
    }

    REP_DEC(REP<T> intvl, decoration::decoration dec) {
        first = intvl;
        second = dec;
    }
};

template<typename T>
static bool operator==(REP_DEC<T> const& x, REP_DEC<T> const& y) {
    return x.first == y.first && x.second == y.second;
}

template<typename T>
class mpfr_bin_ieee754_flavor_j
{

public:
    typedef REP<T> representation;
    typedef REP_DEC<T> representation_dec;

    static bool is_valid(representation const& x) {
        int exc = p1788_bar_isValid(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_valid(representation_dec const& x) {
        int exc = p1788_dec_isValid(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static representation empty() {
        representation r;
        int exc = p1788_bar_empty(static_cast<int>(util::type_precision_order<T>::value), &r);
        signal_exception(exc);
        return r;
    }

    static representation_dec empty_dec() {
        representation_dec r;
        int exc = p1788_dec_empty(static_cast<int>(util::type_precision_order<T>::value), &r);
        signal_exception(exc);
        return r;
    }

    static representation entire() {
        representation r;
        int exc = p1788_bar_entire(static_cast<int>(util::type_precision_order<T>::value), &r);
        signal_exception(exc);
        return r;
    }

    static representation_dec entire_dec() {
        representation_dec r;
        int exc = p1788_dec_entire(static_cast<int>(util::type_precision_order<T>::value), &r);
        signal_exception(exc);
        return r;
    }

    static representation_dec nai() {
        representation_dec r;
        int exc = p1788_dec_nai(static_cast<int>(util::type_precision_order<T>::value), &r);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation convert_type(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_convertType(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec convert_type(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_convertType(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation pos(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_pos(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec pos(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_pos(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation neg(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_neg(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec neg(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_neg(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation add(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_add(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec add(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_add(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation sub(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_sub(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sub(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_sub(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation mul(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_mul(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec mul(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_mul(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation div(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_div(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec div(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_div(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation recip(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_recip(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec recip(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_recip(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation sqr(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_sqr(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec sqr(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_sqr(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation sqrt(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_sqrt(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec sqrt(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_sqrt(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation fma(REP<T1> const& x, REP<T2> const& y, REP<T3> const& z) {
        representation r;
        int exc = p1788_bar_fma(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y, static_cast<int>(util::type_precision_order<T3>::value), &z);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec fma(REP_DEC<T1> const& x, REP_DEC<T2> const& y, REP_DEC<T3> const& z) {
        representation_dec r;
        int exc = p1788_dec_fma(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y, static_cast<int>(util::type_precision_order<T3>::value), &z);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation pown(REP<T1> const& x, int p) {
        representation r;
        int exc = p1788_bar_pown(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, p);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec pown(REP_DEC<T1> const& x, int p) {
        representation_dec r;
        int exc = p1788_dec_pown(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, p);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_pow(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_pow(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation exp(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_exp(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec exp(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_exp(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation exp2(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_exp2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec exp2(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_exp2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation exp10(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_exp10(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec exp10(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_exp10(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation log(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_log(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec log(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_log(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation log2(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_log2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec log2(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_log2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation log10(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_log10(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec log10(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_log10(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation sin(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_sin(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec sin(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_sin(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation cos(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_cos(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec cos(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_cos(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation tan(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_tan(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec tan(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_tan(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation asin(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_asin(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec asin(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_asin(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation acos(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_acos(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec acos(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_acos(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation atan(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_atan(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec atan(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_atan(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2(REP<T1> const& y, REP<T2> const& x) {
        representation r;
        int exc = p1788_bar_atan2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &y, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2(REP_DEC<T1> const& y, REP_DEC<T2> const& x) {
        representation_dec r;
        int exc = p1788_dec_atan2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &y, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation sinh(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_sinh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec sinh(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_sinh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation cosh(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_cosh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec cosh(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_cosh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation tanh(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_tanh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec tanh(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_tanh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation asinh(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_asinh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec asinh(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_asinh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation acosh(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_acosh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec acosh(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_acosh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation atanh(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_atanh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec atanh(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_atanh(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation sign(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_sign(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec sign(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_sign(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation ceil(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_ceil(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec ceil(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_ceil(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation floor(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_floor(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec floor(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_floor(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation trunc(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_trunc(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec trunc(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_trunc(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation round_ties_to_even(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_roundTiesToEven(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec round_ties_to_even(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_roundTiesToEven(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation round_ties_to_away(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_roundTiesToAway(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec round_ties_to_away(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_roundTiesToAway(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation abs(REP<T1> const& x) {
        representation r;
        int exc = p1788_bar_abs(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec abs(REP_DEC<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_abs(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation min(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_min(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec min(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_min(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation max(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_max(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec max(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_max(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static std::pair<representation,representation> mul_rev_to_pair(REP<T1> const& b, REP<T2> const& c) {
        representation r1;
        representation r2;
        int exc = p1788_bar_mulRevToPair(static_cast<int>(util::type_precision_order<T>::value), &r1, &r2, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return std::pair<representation,representation>(r1, r2);
    }

    template<typename T1, typename T2>
    static std::pair<representation_dec,representation_dec> mul_rev_to_pair(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        representation_dec r1;
        representation_dec r2;
        int exc = p1788_dec_mulRevToPair(static_cast<int>(util::type_precision_order<T>::value), &r1, &r2, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return std::pair<representation_dec,representation_dec>(r1, r2);
    }

    template<typename T1, typename T2>
    static representation sqr_rev(REP<T1> const& c, REP<T2> const& x) {
        representation r;
        int exc = p1788_bar_sqrRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sqr_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        representation_dec r;
        int exc = p1788_dec_sqrRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation sqr_rev(REP<T1> const& c) {
        representation r;
        int exc = p1788_bar_sqrRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec sqr_rev(REP_DEC<T1> const& c) {
        representation_dec r;
        int exc = p1788_dec_sqrRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation abs_rev(REP<T1> const& c, REP<T2> const& x) {
        representation r;
        int exc = p1788_bar_absRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec abs_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        representation_dec r;
        int exc = p1788_dec_absRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation abs_rev(REP<T1> const& c) {
        representation r;
        int exc = p1788_bar_absRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec abs_rev(REP_DEC<T1> const& c) {
        representation_dec r;
        int exc = p1788_dec_absRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation pown_rev(REP<T1> const& c, REP<T2> const& x, int p) {
        representation r;
        int exc = p1788_bar_pownRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x, p);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pown_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x, int p) {
        representation_dec r;
        int exc = p1788_dec_pownRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x, p);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation pown_rev(REP<T1> const& c, int p) {
        representation r;
        int exc = p1788_bar_pownRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, p);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec pown_rev(REP_DEC<T1> const& c, int p) {
        representation_dec r;
        int exc = p1788_dec_pownRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, p);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation sin_rev(REP<T1> const& c, REP<T2> const& x) {
        representation r;
        int exc = p1788_bar_sinRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sin_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        representation_dec r;
        int exc = p1788_dec_sinRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation sin_rev(REP<T1> const& c) {
        representation r;
        int exc = p1788_bar_sinRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec sin_rev(REP_DEC<T1> const& c) {
        representation_dec r;
        int exc = p1788_dec_sinRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation cos_rev(REP<T1> const& c, REP<T2> const& x) {
        representation r;
        int exc = p1788_bar_cosRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cos_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        representation_dec r;
        int exc = p1788_dec_cosRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation cos_rev(REP<T1> const& c) {
        representation r;
        int exc = p1788_bar_cosRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec cos_rev(REP_DEC<T1> const& c) {
        representation_dec r;
        int exc = p1788_dec_cosRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation tan_rev(REP<T1> const& c, REP<T2> const& x) {
        representation r;
        int exc = p1788_bar_tanRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec tan_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        representation_dec r;
        int exc = p1788_dec_tanRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation tan_rev(REP<T1> const& c) {
        representation r;
        int exc = p1788_bar_tanRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec tan_rev(REP_DEC<T1> const& c) {
        representation_dec r;
        int exc = p1788_dec_tanRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation cosh_rev(REP<T1> const& c, REP<T2> const& x) {
        representation r;
        int exc = p1788_bar_coshRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cosh_rev(REP_DEC<T1> const& c, REP_DEC<T2> const& x) {
        representation_dec r;
        int exc = p1788_dec_coshRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c, static_cast<int>(util::type_precision_order<T2>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation cosh_rev(REP<T1> const& c) {
        representation r;
        int exc = p1788_bar_coshRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec cosh_rev(REP_DEC<T1> const& c) {
        representation_dec r;
        int exc = p1788_dec_coshRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation mul_rev(REP<T1> const& b, REP<T2> const& c, REP<T3> const& x) {
        representation r;
        int exc = p1788_bar_mulRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec mul_rev(REP_DEC<T1> const& b, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        representation_dec r;
        int exc = p1788_dec_mulRev(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation mul_rev(REP<T1> const& b, REP<T2> const& c) {
        representation r;
        int exc = p1788_bar_mulRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec mul_rev(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        representation_dec r;
        int exc = p1788_dec_mulRevEntire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation pow_rev1(REP<T1> const& b, REP<T2> const& c, REP<T3> const& x) {
        representation r;
        int exc = p1788_bar_powRev1(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec pow_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        representation_dec r;
        int exc = p1788_dec_powRev1(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow_rev1(REP<T1> const& b, REP<T2> const& c) {
        representation r;
        int exc = p1788_bar_powRev1Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        representation_dec r;
        int exc = p1788_dec_powRev1Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation pow_rev2(REP<T1> const& a, REP<T2> const& c, REP<T3> const& x) {
        representation r;
        int exc = p1788_bar_powRev2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec pow_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        representation_dec r;
        int exc = p1788_dec_powRev2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow_rev2(REP<T1> const& a, REP<T2> const& c) {
        representation r;
        int exc = p1788_bar_powRev2Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c) {
        representation_dec r;
        int exc = p1788_dec_powRev2Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation atan2_rev1(REP<T1> const& b, REP<T2> const& c, REP<T3> const& x) {
        representation r;
        int exc = p1788_bar_atan2Rev1(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec atan2_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        representation_dec r;
        int exc = p1788_dec_atan2Rev1(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2_rev1(REP<T1> const& b, REP<T2> const& c) {
        representation r;
        int exc = p1788_bar_atan2Rev1Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2_rev1(REP_DEC<T1> const& b, REP_DEC<T2> const& c) {
        representation_dec r;
        int exc = p1788_dec_atan2Rev1Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &b, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation atan2_rev2(REP<T1> const& a, REP<T2> const& c, REP<T3> const& x) {
        representation r;
        int exc = p1788_bar_atan2Rev2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec atan2_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c, REP_DEC<T3> const& x) {
        representation_dec r;
        int exc = p1788_dec_atan2Rev2(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c, static_cast<int>(util::type_precision_order<T3>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2_rev2(REP<T1> const& a, REP<T2> const& c) {
        representation r;
        int exc = p1788_bar_atan2Rev2Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2_rev2(REP_DEC<T1> const& a, REP_DEC<T2> const& c) {
        representation_dec r;
        int exc = p1788_dec_atan2Rev2Entire(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &a, static_cast<int>(util::type_precision_order<T2>::value), &c);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation cancel_minus(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_cancelMinus(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cancel_minus(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_cancelMinus(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation cancel_plus(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_cancelPlus(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cancel_plus(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_cancelPlus(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation intersection(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_intersection(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec intersection(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_intersection(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation convex_hull(REP<T1> const& x, REP<T2> const& y) {
        representation r;
        int exc = p1788_bar_convexHull(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec convex_hull(REP_DEC<T1> const& x, REP_DEC<T2> const& y) {
        representation_dec r;
        int exc = p1788_dec_convexHull(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(util::type_precision_order<T2>::value), &y);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation nums_to_interval(T1 l, T2 u) {
        representation r;
        int exc = p1788_bar_numsToInterval(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &l, static_cast<int>(util::type_precision_order<T2>::value), &u);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec nums_to_decorated_interval(T1 l, T2 u) {
        representation_dec r;
        int exc = p1788_dec_numsToInterval(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &l, static_cast<int>(util::type_precision_order<T2>::value), &u);
        signal_exception(exc);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec nums_dec_to_decorated_interval(T1 l, T2 u, decoration::decoration dec) {
        representation_dec r;
        int exc = p1788_dec_numsDecToInterval(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &l, static_cast<int>(util::type_precision_order<T2>::value), &u, static_cast<int>(dec));
        signal_exception(exc);
        return r;
    }

    static representation text_to_interval(std::string const& s) {
        representation r;
        int exc = p1788_bar_textToInterval(static_cast<int>(util::type_precision_order<T>::value), &r, s.c_str());
        signal_exception(exc);
        return r;
    }

    static representation_dec text_to_decorated_interval(std::string const& s) {
        representation_dec r;
        int exc = p1788_dec_textToDecoratedInterval(static_cast<int>(util::type_precision_order<T>::value), &r, s.c_str());
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T inf(REP<T1> const& x) {
        T r;
        int exc = p1788_bar_inf(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T inf(REP_DEC<T1> const& x) {
        T r;
        int exc = p1788_dec_inf(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T sup(REP<T1> const& x) {
        T r;
        int exc = p1788_bar_sup(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T sup(REP_DEC<T1> const& x) {
        T r;
        int exc = p1788_dec_sup(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T mid(REP<T1> const& x) {
        T r;
        int exc = p1788_bar_mid(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T mid(REP_DEC<T1> const& x) {
        T r;
        int exc = p1788_dec_mid(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T rad(REP<T1> const& x) {
        T r;
        int exc = p1788_bar_rad(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T rad(REP_DEC<T1> const& x) {
        T r;
        int exc = p1788_dec_rad(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T wid(REP<T1> const& x) {
        T r;
        int exc = p1788_bar_wid(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T wid(REP_DEC<T1> const& x) {
        T r;
        int exc = p1788_dec_wid(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T mag(REP<T1> const& x) {
        T r;
        int exc = p1788_bar_mag(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T mag(REP_DEC<T1> const& x) {
        T r;
        int exc = p1788_dec_mag(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T mig(REP<T1> const& x) {
        T r;
        int exc = p1788_bar_mig(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static T mig(REP_DEC<T1> const& x) {
        T r;
        int exc = p1788_dec_mig(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static std::pair<T,T> mid_rad(REP<T1> const& x) {
        T r1;
        T r2;
        int exc = p1788_bar_midRad(static_cast<int>(util::type_precision_order<T>::value), &r1, &r2, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return std::pair<T,T>(r1, r2);
    }

    template<typename T1>
    static std::pair<T,T> mid_rad(REP_DEC<T1> const& x) {
        T r1;
        T r2;
        int exc = p1788_dec_midRad(static_cast<int>(util::type_precision_order<T>::value), &r1, &r2, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return std::pair<T,T>(r1, r2);
    }

    static bool is_empty(representation const& x) {
        int exc = p1788_bar_isEmpty(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_empty(representation_dec const& x) {
        int exc = p1788_dec_isEmpty(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_entire(representation const& x) {
        int exc = p1788_bar_isEntire(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_entire(representation_dec const& x) {
        int exc = p1788_dec_isEntire(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_nai(representation_dec const& x) {
        int exc = p1788_dec_isNaI(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_common_interval(representation const& x) {
        int exc = p1788_bar_isCommonInterval(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_common_interval(representation_dec const& x) {
        int exc = p1788_dec_isCommonInterval(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_singleton(representation const& x) {
        int exc = p1788_bar_isSingleton(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    static bool is_singleton(representation_dec const& x) {
        int exc = p1788_dec_isSingleton(static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool is_member(T1 m, representation const& x) {
        int exc = p1788_bar_isMember(static_cast<int>(util::type_precision_order<T1>::value), &m, static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool is_member(T1 m, representation_dec const& x) {
        int exc = p1788_dec_isMember(static_cast<int>(util::type_precision_order<T1>::value), &m, static_cast<int>(util::type_precision_order<T>::value), &x);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool equal(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_equal(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool equal(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_equal(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool subset(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_subset(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool subset(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_subset(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool less(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_less(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool less(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_less(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool precedes(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_precedes(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool precedes(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_precedes(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool interior(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_interior(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool interior(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_interior(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool strictly_less(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_strictLess(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool strictly_less(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_strictLess(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool strictly_precedes(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_strictPrecedes(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool strictly_precedes(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_strictPrecedes(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool disjoint(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_disjoint(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static bool disjoint(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_disjoint(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return signal_exception(exc);
    }

    template<typename T1>
    static overlapping::overlapping_state overlap(representation const& a, REP<T1> const& b) {
        int exc = p1788_bar_overlap(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return static_cast<overlapping::overlapping_state>(signal_exception(exc));
    }

    template<typename T1>
    static overlapping::overlapping_state overlap(representation_dec const& a, REP_DEC<T1> const& b) {
        int exc = p1788_dec_overlap(static_cast<int>(util::type_precision_order<T>::value), &a, static_cast<int>(util::type_precision_order<T1>::value), &b);
        return static_cast<overlapping::overlapping_state>(signal_exception(exc));
    }

    template<typename T1>
    static representation_dec new_dec(REP<T1> const& x) {
        representation_dec r;
        int exc = p1788_dec_newDec(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    static decoration::decoration decoration_part(representation_dec const& x) {
        int exc = p1788_bar_decorationPart(static_cast<int>(util::type_precision_order<T>::value), &x);
        return static_cast<decoration::decoration>(signal_exception(exc));
    }

    template<typename T1>
    static representation interval_part(REP_DEC<T1> const& x) {
        representation r;
        int exc = p1788_bar_intervalPart(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x);
        signal_exception(exc);
        return r;
    }

    template<typename T1>
    static representation_dec set_dec(REP<T1> const& x, decoration::decoration dec) {
        representation_dec r;
        int exc = p1788_dec_setDec(static_cast<int>(util::type_precision_order<T>::value), &r, static_cast<int>(util::type_precision_order<T1>::value), &x, static_cast<int>(dec));
        signal_exception(exc);
        return r;
    }

    static representation exact_to_interval(std::string const& s) {
        representation r;
        int exc = p1788_bar_exactToInterval(static_cast<int>(util::type_precision_order<T>::value), &r, s.c_str());
        signal_exception(exc);
        return r;
    }

    static representation_dec exact_to_decorated_interval(std::string const& s) {
        representation_dec r;
        int exc = p1788_dec_exactToDecoratedInterval(static_cast<int>(util::type_precision_order<T>::value), &r, s.c_str());
        signal_exception(exc);
        return r;
    }

    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_interval_to_text(std::basic_ostream<CharT, Traits>& os, representation const& x) {
        char *r;
        int exc = p1788_bar_intervalToExact(&r, static_cast<int>(util::type_precision_order<T>::value), &x);
        std::string s(r);
        free(r);
        signal_exception(exc);
        os << s;
        return os;
    }

    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_interval_to_text(std::basic_ostream<CharT, Traits>& os, representation_dec const& x) {
        char *r;
        int exc = p1788_dec_intervalToExact(&r, static_cast<int>(util::type_precision_order<T>::value), &x);
        std::string s(r);
        free(r);
        signal_exception(exc);
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

#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_J_HPP
