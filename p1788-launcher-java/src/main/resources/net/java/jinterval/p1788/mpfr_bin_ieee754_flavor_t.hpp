
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"

namespace p1788 {
namespace flavor {
namespace infsup {
namespace setbased {

static const char* dec_strings[] = { "ill", "trv", "def", "dac", "com"};

static void print_op(const char* op) {
    static const char* old_op = NULL;
    if (old_op == NULL || strcmp(op, old_op)) {
        old_op = op;
        printf("* %s\n", op);
    }
}
template<typename T>
static void print_num(T x);

template<typename T>
static void print_bare(std::pair<T,T> const& x);

template<typename T>
static void print_dec(std::pair<std::pair<T,T>,p1788::decoration::decoration> const& x);

template<>
void print_num<float>(float x) {
    printf("%+-16.6a", x);
}

template<>
void print_bare<float>(std::pair<float,float> const& x) {
    if (x.first <= x.second && x.first != std::numeric_limits<float>::infinity() && x.second != -std::numeric_limits<float>::infinity()) {
        printf("[%+-16.6a,%+-16.6a]", x.first, x.second);
    } else {
        printf("[]");
    }
}

template<>
void print_dec<float>(std::pair<std::pair<float,float>,p1788::decoration::decoration> const& x) {
    print_bare(x.first);
}

template<>
void print_num<double>(double x) {
    printf("%+-24.13a", x);
}

template<>
void print_bare<double>(std::pair<double,double> const& x) {
    if (x.first <= x.second && x.first != std::numeric_limits<double>::infinity() && x.second != -std::numeric_limits<double>::infinity()) {
        printf("[%+-24.13a,%+-24.13a]", x.first, x.second);
    } else {
        printf("[]");
    }
}

template<>
void print_dec<double>(std::pair<std::pair<double,double>,p1788::decoration::decoration> const& x) {
    print_bare(x.first);
}

template<>
void print_num<long double>(long double x) {
    printf("%+-28.16La", x);
}

template<>
void print_bare<long double>(std::pair<long double,long double> const& x) {
    if (x.first <= x.second && x.first != std::numeric_limits<long double>::infinity() && x.second != -std::numeric_limits<long double>::infinity()) {
        printf("[%+-28.16La,%+-28.16La]", x.first, x.second);
    } else {
        printf("[]");
    }
}

template<>
void print_dec<long double>(std::pair<std::pair<long double,long double>,p1788::decoration::decoration> const& x) {
    print_bare(x.first);
}
template<typename T>
class mpfr_bin_ieee754_flavor_t
{

public:
    template<typename T_>
    using representation_type = typename p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::template representation_type<T_>;

    template<typename T_>
    using representation_dec_type = typename p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::template representation_dec_type<T_>;

    typedef representation_type<T> representation;
    typedef representation_dec_type<T> representation_dec;

    static bool is_valid(representation const& x) {
        print_op("is_valid");
        print_bare(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_valid(x);
        return r;
    }

    static bool is_valid(representation_dec const& x) {
        print_op("is_valid");
        print_dec(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_valid(x);
        return r;
    }

    static representation empty() {
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::empty();
        return r;
    }

    static representation_dec empty_dec() {
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::empty_dec();
        return r;
    }

    static representation entire() {
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::entire();
        return r;
    }

    static representation_dec entire_dec() {
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::entire_dec();
        return r;
    }

    static representation_dec nai() {
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nai();
        return r;
    }

    template<typename T1>
    static representation convert_type(representation_type<T1> const& x) {
        print_op("convert_type");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::convert_type(x);
        return r;
    }

    template<typename T1>
    static representation_dec convert_type(representation_dec_type<T1> const& x) {
        print_op("convert_type");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::convert_type(x);
        return r;
    }

    template<typename T1>
    static representation pos(representation_type<T1> const& x) {
        print_op("pos");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pos(x);
        return r;
    }

    template<typename T1>
    static representation_dec pos(representation_dec_type<T1> const& x) {
        print_op("pos");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pos(x);
        return r;
    }

    template<typename T1>
    static representation neg(representation_type<T1> const& x) {
        print_op("neg");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::neg(x);
        return r;
    }

    template<typename T1>
    static representation_dec neg(representation_dec_type<T1> const& x) {
        print_op("neg");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::neg(x);
        return r;
    }

    template<typename T1, typename T2>
    static representation add(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("add");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::add(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec add(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("add");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::add(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation sub(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("sub");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sub(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sub(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("sub");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sub(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation mul(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("mul");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec mul(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("mul");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation div(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("div");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::div(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec div(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("div");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::div(x, y);
        return r;
    }

    template<typename T1>
    static representation recip(representation_type<T1> const& x) {
        print_op("recip");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::recip(x);
        return r;
    }

    template<typename T1>
    static representation_dec recip(representation_dec_type<T1> const& x) {
        print_op("recip");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::recip(x);
        return r;
    }

    template<typename T1>
    static representation sqr(representation_type<T1> const& x) {
        print_op("sqr");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqr(x);
        return r;
    }

    template<typename T1>
    static representation_dec sqr(representation_dec_type<T1> const& x) {
        print_op("sqr");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqr(x);
        return r;
    }

    template<typename T1>
    static representation sqrt(representation_type<T1> const& x) {
        print_op("sqrt");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqrt(x);
        return r;
    }

    template<typename T1>
    static representation_dec sqrt(representation_dec_type<T1> const& x) {
        print_op("sqrt");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqrt(x);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation fma(representation_type<T1> const& x, representation_type<T2> const& y, representation_type<T3> const& z) {
        print_op("fma");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf(" | ");
        print_bare(z);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::fma(x, y, z);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec fma(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y, representation_dec_type<T3> const& z) {
        print_op("fma");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf(" | ");
        print_dec(z);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::fma(x, y, z);
        return r;
    }

    template<typename T1>
    static representation pown(representation_type<T1> const& x, int p) {
        print_op("pown");
        print_bare(x);
        printf(" | ");
        printf("%d", p);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pown(x, p);
        return r;
    }

    template<typename T1>
    static representation_dec pown(representation_dec_type<T1> const& x, int p) {
        print_op("pown");
        print_dec(x);
        printf(" | ");
        printf("%d", p);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pown(x, p);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("pow");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("pow");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow(x, y);
        return r;
    }

    template<typename T1>
    static representation exp(representation_type<T1> const& x) {
        print_op("exp");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exp(x);
        return r;
    }

    template<typename T1>
    static representation_dec exp(representation_dec_type<T1> const& x) {
        print_op("exp");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exp(x);
        return r;
    }

    template<typename T1>
    static representation exp2(representation_type<T1> const& x) {
        print_op("exp2");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exp2(x);
        return r;
    }

    template<typename T1>
    static representation_dec exp2(representation_dec_type<T1> const& x) {
        print_op("exp2");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exp2(x);
        return r;
    }

    template<typename T1>
    static representation exp10(representation_type<T1> const& x) {
        print_op("exp10");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exp10(x);
        return r;
    }

    template<typename T1>
    static representation_dec exp10(representation_dec_type<T1> const& x) {
        print_op("exp10");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exp10(x);
        return r;
    }

    template<typename T1>
    static representation log(representation_type<T1> const& x) {
        print_op("log");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::log(x);
        return r;
    }

    template<typename T1>
    static representation_dec log(representation_dec_type<T1> const& x) {
        print_op("log");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::log(x);
        return r;
    }

    template<typename T1>
    static representation log2(representation_type<T1> const& x) {
        print_op("log2");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::log2(x);
        return r;
    }

    template<typename T1>
    static representation_dec log2(representation_dec_type<T1> const& x) {
        print_op("log2");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::log2(x);
        return r;
    }

    template<typename T1>
    static representation log10(representation_type<T1> const& x) {
        print_op("log10");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::log10(x);
        return r;
    }

    template<typename T1>
    static representation_dec log10(representation_dec_type<T1> const& x) {
        print_op("log10");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::log10(x);
        return r;
    }

    template<typename T1>
    static representation sin(representation_type<T1> const& x) {
        print_op("sin");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sin(x);
        return r;
    }

    template<typename T1>
    static representation_dec sin(representation_dec_type<T1> const& x) {
        print_op("sin");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sin(x);
        return r;
    }

    template<typename T1>
    static representation cos(representation_type<T1> const& x) {
        print_op("cos");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cos(x);
        return r;
    }

    template<typename T1>
    static representation_dec cos(representation_dec_type<T1> const& x) {
        print_op("cos");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cos(x);
        return r;
    }

    template<typename T1>
    static representation tan(representation_type<T1> const& x) {
        print_op("tan");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tan(x);
        return r;
    }

    template<typename T1>
    static representation_dec tan(representation_dec_type<T1> const& x) {
        print_op("tan");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tan(x);
        return r;
    }

    template<typename T1>
    static representation asin(representation_type<T1> const& x) {
        print_op("asin");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::asin(x);
        return r;
    }

    template<typename T1>
    static representation_dec asin(representation_dec_type<T1> const& x) {
        print_op("asin");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::asin(x);
        return r;
    }

    template<typename T1>
    static representation acos(representation_type<T1> const& x) {
        print_op("acos");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::acos(x);
        return r;
    }

    template<typename T1>
    static representation_dec acos(representation_dec_type<T1> const& x) {
        print_op("acos");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::acos(x);
        return r;
    }

    template<typename T1>
    static representation atan(representation_type<T1> const& x) {
        print_op("atan");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan(x);
        return r;
    }

    template<typename T1>
    static representation_dec atan(representation_dec_type<T1> const& x) {
        print_op("atan");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan(x);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2(representation_type<T1> const& y, representation_type<T2> const& x) {
        print_op("atan2");
        print_bare(y);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2(y, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2(representation_dec_type<T1> const& y, representation_dec_type<T2> const& x) {
        print_op("atan2");
        print_dec(y);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2(y, x);
        return r;
    }

    template<typename T1>
    static representation sinh(representation_type<T1> const& x) {
        print_op("sinh");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sinh(x);
        return r;
    }

    template<typename T1>
    static representation_dec sinh(representation_dec_type<T1> const& x) {
        print_op("sinh");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sinh(x);
        return r;
    }

    template<typename T1>
    static representation cosh(representation_type<T1> const& x) {
        print_op("cosh");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cosh(x);
        return r;
    }

    template<typename T1>
    static representation_dec cosh(representation_dec_type<T1> const& x) {
        print_op("cosh");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cosh(x);
        return r;
    }

    template<typename T1>
    static representation tanh(representation_type<T1> const& x) {
        print_op("tanh");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tanh(x);
        return r;
    }

    template<typename T1>
    static representation_dec tanh(representation_dec_type<T1> const& x) {
        print_op("tanh");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tanh(x);
        return r;
    }

    template<typename T1>
    static representation asinh(representation_type<T1> const& x) {
        print_op("asinh");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::asinh(x);
        return r;
    }

    template<typename T1>
    static representation_dec asinh(representation_dec_type<T1> const& x) {
        print_op("asinh");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::asinh(x);
        return r;
    }

    template<typename T1>
    static representation acosh(representation_type<T1> const& x) {
        print_op("acosh");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::acosh(x);
        return r;
    }

    template<typename T1>
    static representation_dec acosh(representation_dec_type<T1> const& x) {
        print_op("acosh");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::acosh(x);
        return r;
    }

    template<typename T1>
    static representation atanh(representation_type<T1> const& x) {
        print_op("atanh");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atanh(x);
        return r;
    }

    template<typename T1>
    static representation_dec atanh(representation_dec_type<T1> const& x) {
        print_op("atanh");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atanh(x);
        return r;
    }

    template<typename T1>
    static representation sign(representation_type<T1> const& x) {
        print_op("sign");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sign(x);
        return r;
    }

    template<typename T1>
    static representation_dec sign(representation_dec_type<T1> const& x) {
        print_op("sign");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sign(x);
        return r;
    }

    template<typename T1>
    static representation ceil(representation_type<T1> const& x) {
        print_op("ceil");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::ceil(x);
        return r;
    }

    template<typename T1>
    static representation_dec ceil(representation_dec_type<T1> const& x) {
        print_op("ceil");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::ceil(x);
        return r;
    }

    template<typename T1>
    static representation floor(representation_type<T1> const& x) {
        print_op("floor");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::floor(x);
        return r;
    }

    template<typename T1>
    static representation_dec floor(representation_dec_type<T1> const& x) {
        print_op("floor");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::floor(x);
        return r;
    }

    template<typename T1>
    static representation trunc(representation_type<T1> const& x) {
        print_op("trunc");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::trunc(x);
        return r;
    }

    template<typename T1>
    static representation_dec trunc(representation_dec_type<T1> const& x) {
        print_op("trunc");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::trunc(x);
        return r;
    }

    template<typename T1>
    static representation round_ties_to_even(representation_type<T1> const& x) {
        print_op("round_ties_to_even");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::round_ties_to_even(x);
        return r;
    }

    template<typename T1>
    static representation_dec round_ties_to_even(representation_dec_type<T1> const& x) {
        print_op("round_ties_to_even");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::round_ties_to_even(x);
        return r;
    }

    template<typename T1>
    static representation round_ties_to_away(representation_type<T1> const& x) {
        print_op("round_ties_to_away");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::round_ties_to_away(x);
        return r;
    }

    template<typename T1>
    static representation_dec round_ties_to_away(representation_dec_type<T1> const& x) {
        print_op("round_ties_to_away");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::round_ties_to_away(x);
        return r;
    }

    template<typename T1>
    static representation abs(representation_type<T1> const& x) {
        print_op("abs");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::abs(x);
        return r;
    }

    template<typename T1>
    static representation_dec abs(representation_dec_type<T1> const& x) {
        print_op("abs");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::abs(x);
        return r;
    }

    template<typename T1, typename T2>
    static representation min(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("min");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::min(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec min(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("min");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::min(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation max(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("max");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::max(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec max(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("max");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::max(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static std::pair<representation,representation> mul_rev_to_pair(representation_type<T1> const& b, representation_type<T2> const& c) {
        print_op("mul_rev_to_pair");
        print_bare(b);
        printf(" | ");
        print_bare(c);
        printf("\n");
        std::pair<representation,representation> r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(b, c);
        return r;
    }

    template<typename T1, typename T2>
    static std::pair<representation_dec,representation_dec> mul_rev_to_pair(representation_dec_type<T1> const& b, representation_dec_type<T2> const& c) {
        print_op("mul_rev_to_pair");
        print_dec(b);
        printf(" | ");
        print_dec(c);
        printf("\n");
        std::pair<representation_dec,representation_dec> r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(b, c);
        return r;
    }

    template<typename T1, typename T2>
    static representation sqr_rev(representation_type<T1> const& c, representation_type<T2> const& x) {
        print_op("sqr_rev");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqr_rev(c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sqr_rev(representation_dec_type<T1> const& c, representation_dec_type<T2> const& x) {
        print_op("sqr_rev");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqr_rev(c, x);
        return r;
    }

    template<typename T1>
    static representation sqr_rev(representation_type<T1> const& c) {
        print_op("sqr_rev");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqr_rev(c);
        return r;
    }

    template<typename T1>
    static representation_dec sqr_rev(representation_dec_type<T1> const& c) {
        print_op("sqr_rev");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sqr_rev(c);
        return r;
    }

    template<typename T1, typename T2>
    static representation abs_rev(representation_type<T1> const& c, representation_type<T2> const& x) {
        print_op("abs_rev");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::abs_rev(c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec abs_rev(representation_dec_type<T1> const& c, representation_dec_type<T2> const& x) {
        print_op("abs_rev");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::abs_rev(c, x);
        return r;
    }

    template<typename T1>
    static representation abs_rev(representation_type<T1> const& c) {
        print_op("abs_rev");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::abs_rev(c);
        return r;
    }

    template<typename T1>
    static representation_dec abs_rev(representation_dec_type<T1> const& c) {
        print_op("abs_rev");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::abs_rev(c);
        return r;
    }

    template<typename T1, typename T2>
    static representation pown_rev(representation_type<T1> const& c, representation_type<T2> const& x, int p) {
        print_op("pown_rev");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf(" | ");
        printf("%d", p);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pown_rev(c, x, p);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pown_rev(representation_dec_type<T1> const& c, representation_dec_type<T2> const& x, int p) {
        print_op("pown_rev");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf(" | ");
        printf("%d", p);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pown_rev(c, x, p);
        return r;
    }

    template<typename T1>
    static representation pown_rev(representation_type<T1> const& c, int p) {
        print_op("pown_rev");
        print_bare(c);
        printf(" | ");
        printf("%d", p);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pown_rev(c, p);
        return r;
    }

    template<typename T1>
    static representation_dec pown_rev(representation_dec_type<T1> const& c, int p) {
        print_op("pown_rev");
        print_dec(c);
        printf(" | ");
        printf("%d", p);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pown_rev(c, p);
        return r;
    }

    template<typename T1, typename T2>
    static representation sin_rev(representation_type<T1> const& c, representation_type<T2> const& x) {
        print_op("sin_rev");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sin_rev(c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec sin_rev(representation_dec_type<T1> const& c, representation_dec_type<T2> const& x) {
        print_op("sin_rev");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sin_rev(c, x);
        return r;
    }

    template<typename T1>
    static representation sin_rev(representation_type<T1> const& c) {
        print_op("sin_rev");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sin_rev(c);
        return r;
    }

    template<typename T1>
    static representation_dec sin_rev(representation_dec_type<T1> const& c) {
        print_op("sin_rev");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sin_rev(c);
        return r;
    }

    template<typename T1, typename T2>
    static representation cos_rev(representation_type<T1> const& c, representation_type<T2> const& x) {
        print_op("cos_rev");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cos_rev(c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cos_rev(representation_dec_type<T1> const& c, representation_dec_type<T2> const& x) {
        print_op("cos_rev");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cos_rev(c, x);
        return r;
    }

    template<typename T1>
    static representation cos_rev(representation_type<T1> const& c) {
        print_op("cos_rev");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cos_rev(c);
        return r;
    }

    template<typename T1>
    static representation_dec cos_rev(representation_dec_type<T1> const& c) {
        print_op("cos_rev");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cos_rev(c);
        return r;
    }

    template<typename T1, typename T2>
    static representation tan_rev(representation_type<T1> const& c, representation_type<T2> const& x) {
        print_op("tan_rev");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tan_rev(c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec tan_rev(representation_dec_type<T1> const& c, representation_dec_type<T2> const& x) {
        print_op("tan_rev");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tan_rev(c, x);
        return r;
    }

    template<typename T1>
    static representation tan_rev(representation_type<T1> const& c) {
        print_op("tan_rev");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tan_rev(c);
        return r;
    }

    template<typename T1>
    static representation_dec tan_rev(representation_dec_type<T1> const& c) {
        print_op("tan_rev");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::tan_rev(c);
        return r;
    }

    template<typename T1, typename T2>
    static representation cosh_rev(representation_type<T1> const& c, representation_type<T2> const& x) {
        print_op("cosh_rev");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cosh_rev(c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cosh_rev(representation_dec_type<T1> const& c, representation_dec_type<T2> const& x) {
        print_op("cosh_rev");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cosh_rev(c, x);
        return r;
    }

    template<typename T1>
    static representation cosh_rev(representation_type<T1> const& c) {
        print_op("cosh_rev");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cosh_rev(c);
        return r;
    }

    template<typename T1>
    static representation_dec cosh_rev(representation_dec_type<T1> const& c) {
        print_op("cosh_rev");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cosh_rev(c);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation mul_rev(representation_type<T1> const& b, representation_type<T2> const& c, representation_type<T3> const& x) {
        print_op("mul_rev");
        print_bare(b);
        printf(" | ");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul_rev(b, c, x);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec mul_rev(representation_dec_type<T1> const& b, representation_dec_type<T2> const& c, representation_dec_type<T3> const& x) {
        print_op("mul_rev");
        print_dec(b);
        printf(" | ");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul_rev(b, c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation mul_rev(representation_type<T1> const& b, representation_type<T2> const& c) {
        print_op("mul_rev");
        print_bare(b);
        printf(" | ");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul_rev(b, c);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec mul_rev(representation_dec_type<T1> const& b, representation_dec_type<T2> const& c) {
        print_op("mul_rev");
        print_dec(b);
        printf(" | ");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mul_rev(b, c);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation pow_rev1(representation_type<T1> const& b, representation_type<T2> const& c, representation_type<T3> const& x) {
        print_op("pow_rev1");
        print_bare(b);
        printf(" | ");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev1(b, c, x);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec pow_rev1(representation_dec_type<T1> const& b, representation_dec_type<T2> const& c, representation_dec_type<T3> const& x) {
        print_op("pow_rev1");
        print_dec(b);
        printf(" | ");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev1(b, c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow_rev1(representation_type<T1> const& b, representation_type<T2> const& c) {
        print_op("pow_rev1");
        print_bare(b);
        printf(" | ");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev1(b, c);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow_rev1(representation_dec_type<T1> const& b, representation_dec_type<T2> const& c) {
        print_op("pow_rev1");
        print_dec(b);
        printf(" | ");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev1(b, c);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation pow_rev2(representation_type<T1> const& a, representation_type<T2> const& c, representation_type<T3> const& x) {
        print_op("pow_rev2");
        print_bare(a);
        printf(" | ");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev2(a, c, x);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec pow_rev2(representation_dec_type<T1> const& a, representation_dec_type<T2> const& c, representation_dec_type<T3> const& x) {
        print_op("pow_rev2");
        print_dec(a);
        printf(" | ");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev2(a, c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation pow_rev2(representation_type<T1> const& a, representation_type<T2> const& c) {
        print_op("pow_rev2");
        print_bare(a);
        printf(" | ");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev2(a, c);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec pow_rev2(representation_dec_type<T1> const& a, representation_dec_type<T2> const& c) {
        print_op("pow_rev2");
        print_dec(a);
        printf(" | ");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::pow_rev2(a, c);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation atan2_rev1(representation_type<T1> const& b, representation_type<T2> const& c, representation_type<T3> const& x) {
        print_op("atan2_rev1");
        print_bare(b);
        printf(" | ");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev1(b, c, x);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec atan2_rev1(representation_dec_type<T1> const& b, representation_dec_type<T2> const& c, representation_dec_type<T3> const& x) {
        print_op("atan2_rev1");
        print_dec(b);
        printf(" | ");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev1(b, c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2_rev1(representation_type<T1> const& b, representation_type<T2> const& c) {
        print_op("atan2_rev1");
        print_bare(b);
        printf(" | ");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev1(b, c);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2_rev1(representation_dec_type<T1> const& b, representation_dec_type<T2> const& c) {
        print_op("atan2_rev1");
        print_dec(b);
        printf(" | ");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev1(b, c);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation atan2_rev2(representation_type<T1> const& a, representation_type<T2> const& c, representation_type<T3> const& x) {
        print_op("atan2_rev2");
        print_bare(a);
        printf(" | ");
        print_bare(c);
        printf(" | ");
        print_bare(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev2(a, c, x);
        return r;
    }

    template<typename T1, typename T2, typename T3>
    static representation_dec atan2_rev2(representation_dec_type<T1> const& a, representation_dec_type<T2> const& c, representation_dec_type<T3> const& x) {
        print_op("atan2_rev2");
        print_dec(a);
        printf(" | ");
        print_dec(c);
        printf(" | ");
        print_dec(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev2(a, c, x);
        return r;
    }

    template<typename T1, typename T2>
    static representation atan2_rev2(representation_type<T1> const& a, representation_type<T2> const& c) {
        print_op("atan2_rev2");
        print_bare(a);
        printf(" | ");
        print_bare(c);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev2(a, c);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec atan2_rev2(representation_dec_type<T1> const& a, representation_dec_type<T2> const& c) {
        print_op("atan2_rev2");
        print_dec(a);
        printf(" | ");
        print_dec(c);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::atan2_rev2(a, c);
        return r;
    }

    template<typename T1, typename T2>
    static representation cancel_minus(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("cancel_minus");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cancel_minus(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cancel_minus(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("cancel_minus");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cancel_minus(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation cancel_plus(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("cancel_plus");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cancel_plus(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec cancel_plus(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("cancel_plus");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::cancel_plus(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation intersection(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("intersection");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::intersection(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec intersection(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("intersection");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::intersection(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation convex_hull(representation_type<T1> const& x, representation_type<T2> const& y) {
        print_op("convex_hull");
        print_bare(x);
        printf(" | ");
        print_bare(y);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::convex_hull(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec convex_hull(representation_dec_type<T1> const& x, representation_dec_type<T2> const& y) {
        print_op("convex_hull");
        print_dec(x);
        printf(" | ");
        print_dec(y);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::convex_hull(x, y);
        return r;
    }

    template<typename T1, typename T2>
    static representation nums_to_interval(T1 l, T2 u) {
        print_op("nums_to_interval");
        print_num(l);
        printf(" | ");
        print_num(u);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nums_to_interval(l, u);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec nums_to_decorated_interval(T1 l, T2 u) {
        print_op("nums_to_decorated_interval");
        print_num(l);
        printf(" | ");
        print_num(u);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nums_to_decorated_interval(l, u);
        return r;
    }

    template<typename T1, typename T2>
    static representation_dec nums_dec_to_decorated_interval(T1 l, T2 u, decoration::decoration dec) {
        print_op("nums_dec_to_decorated_interval");
        print_num(l);
        printf(" | ");
        print_num(u);
        printf(" | ");
        printf("%s", dec_strings[static_cast<int>(dec) >> 2]);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nums_dec_to_decorated_interval(l, u, dec);
        return r;
    }

    static representation text_to_interval(std::string const& s) {
        print_op("text_to_interval");
        printf("\"%s\"", s.c_str());
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::text_to_interval(s);
        return r;
    }

    static representation_dec text_to_decorated_interval(std::string const& s) {
        print_op("text_to_decorated_interval");
        printf("\"%s\"", s.c_str());
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::text_to_decorated_interval(s);
        return r;
    }

    template<typename T1>
    static T inf(representation_type<T1> const& x) {
        print_op("inf");
        print_bare(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::inf(x);
        return r;
    }

    template<typename T1>
    static T inf(representation_dec_type<T1> const& x) {
        print_op("inf");
        print_dec(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::inf(x);
        return r;
    }

    template<typename T1>
    static T sup(representation_type<T1> const& x) {
        print_op("sup");
        print_bare(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sup(x);
        return r;
    }

    template<typename T1>
    static T sup(representation_dec_type<T1> const& x) {
        print_op("sup");
        print_dec(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::sup(x);
        return r;
    }

    template<typename T1>
    static T mid(representation_type<T1> const& x) {
        print_op("mid");
        print_bare(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mid(x);
        return r;
    }

    template<typename T1>
    static T mid(representation_dec_type<T1> const& x) {
        print_op("mid");
        print_dec(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mid(x);
        return r;
    }

    template<typename T1>
    static T rad(representation_type<T1> const& x) {
        print_op("rad");
        print_bare(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::rad(x);
        return r;
    }

    template<typename T1>
    static T rad(representation_dec_type<T1> const& x) {
        print_op("rad");
        print_dec(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::rad(x);
        return r;
    }

    template<typename T1>
    static T wid(representation_type<T1> const& x) {
        print_op("wid");
        print_bare(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::wid(x);
        return r;
    }

    template<typename T1>
    static T wid(representation_dec_type<T1> const& x) {
        print_op("wid");
        print_dec(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::wid(x);
        return r;
    }

    template<typename T1>
    static T mag(representation_type<T1> const& x) {
        print_op("mag");
        print_bare(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mag(x);
        return r;
    }

    template<typename T1>
    static T mag(representation_dec_type<T1> const& x) {
        print_op("mag");
        print_dec(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mag(x);
        return r;
    }

    template<typename T1>
    static T mig(representation_type<T1> const& x) {
        print_op("mig");
        print_bare(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mig(x);
        return r;
    }

    template<typename T1>
    static T mig(representation_dec_type<T1> const& x) {
        print_op("mig");
        print_dec(x);
        printf("\n");
        T r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mig(x);
        return r;
    }

    template<typename T1>
    static std::pair<T,T> mid_rad(representation_type<T1> const& x) {
        print_op("mid_rad");
        print_bare(x);
        printf("\n");
        std::pair<T,T> r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mid_rad(x);
        return r;
    }

    template<typename T1>
    static std::pair<T,T> mid_rad(representation_dec_type<T1> const& x) {
        print_op("mid_rad");
        print_dec(x);
        printf("\n");
        std::pair<T,T> r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::mid_rad(x);
        return r;
    }

    static bool is_empty(representation const& x) {
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_empty(x);
        return r;
    }

    static bool is_empty(representation_dec const& x) {
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_empty(x);
        return r;
    }

    static bool is_entire(representation const& x) {
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_entire(x);
        return r;
    }

    static bool is_entire(representation_dec const& x) {
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_entire(x);
        return r;
    }

    static bool is_nai(representation_dec const& x) {
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_nai(x);
        return r;
    }

    static bool is_common_interval(representation const& x) {
        print_op("is_common_interval");
        print_bare(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_common_interval(x);
        return r;
    }

    static bool is_common_interval(representation_dec const& x) {
        print_op("is_common_interval");
        print_dec(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_common_interval(x);
        return r;
    }

    static bool is_singleton(representation const& x) {
        print_op("is_singleton");
        print_bare(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_singleton(x);
        return r;
    }

    static bool is_singleton(representation_dec const& x) {
        print_op("is_singleton");
        print_dec(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_singleton(x);
        return r;
    }

    template<typename T1>
    static bool is_member(T1 m, representation const& x) {
        print_op("is_member");
        print_num(m);
        printf(" | ");
        print_bare(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_member(m, x);
        return r;
    }

    template<typename T1>
    static bool is_member(T1 m, representation_dec const& x) {
        print_op("is_member");
        print_num(m);
        printf(" | ");
        print_dec(x);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::is_member(m, x);
        return r;
    }

    template<typename T1>
    static bool equal(representation const& a, representation_type<T1> const& b) {
        print_op("equal");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::equal(a, b);
        return r;
    }

    template<typename T1>
    static bool equal(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("equal");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::equal(a, b);
        return r;
    }

    template<typename T1>
    static bool subset(representation const& a, representation_type<T1> const& b) {
        print_op("subset");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::subset(a, b);
        return r;
    }

    template<typename T1>
    static bool subset(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("subset");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::subset(a, b);
        return r;
    }

    template<typename T1>
    static bool less(representation const& a, representation_type<T1> const& b) {
        print_op("less");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::less(a, b);
        return r;
    }

    template<typename T1>
    static bool less(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("less");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::less(a, b);
        return r;
    }

    template<typename T1>
    static bool precedes(representation const& a, representation_type<T1> const& b) {
        print_op("precedes");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::precedes(a, b);
        return r;
    }

    template<typename T1>
    static bool precedes(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("precedes");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::precedes(a, b);
        return r;
    }

    template<typename T1>
    static bool interior(representation const& a, representation_type<T1> const& b) {
        print_op("interior");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::interior(a, b);
        return r;
    }

    template<typename T1>
    static bool interior(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("interior");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::interior(a, b);
        return r;
    }

    template<typename T1>
    static bool strictly_less(representation const& a, representation_type<T1> const& b) {
        print_op("strictly_less");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::strictly_less(a, b);
        return r;
    }

    template<typename T1>
    static bool strictly_less(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("strictly_less");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::strictly_less(a, b);
        return r;
    }

    template<typename T1>
    static bool strictly_precedes(representation const& a, representation_type<T1> const& b) {
        print_op("strictly_precedes");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::strictly_precedes(a, b);
        return r;
    }

    template<typename T1>
    static bool strictly_precedes(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("strictly_precedes");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::strictly_precedes(a, b);
        return r;
    }

    template<typename T1>
    static bool disjoint(representation const& a, representation_type<T1> const& b) {
        print_op("disjoint");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::disjoint(a, b);
        return r;
    }

    template<typename T1>
    static bool disjoint(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("disjoint");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        bool r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::disjoint(a, b);
        return r;
    }

    template<typename T1>
    static overlapping::overlapping_state overlap(representation const& a, representation_type<T1> const& b) {
        print_op("overlap");
        print_bare(a);
        printf(" | ");
        print_bare(b);
        printf("\n");
        p1788::overlapping::overlapping_state r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::overlap(a, b);
        return r;
    }

    template<typename T1>
    static overlapping::overlapping_state overlap(representation_dec const& a, representation_dec_type<T1> const& b) {
        print_op("overlap");
        print_dec(a);
        printf(" | ");
        print_dec(b);
        printf("\n");
        p1788::overlapping::overlapping_state r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::overlap(a, b);
        return r;
    }

    template<typename T1>
    static representation_dec new_dec(representation_type<T1> const& x) {
        print_op("new_dec");
        print_bare(x);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::new_dec(x);
        return r;
    }

    static decoration::decoration decoration_part(representation_dec const& x) {
        print_op("decoration_part");
        print_dec(x);
        printf("\n");
        p1788::decoration::decoration r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::decoration_part(x);
        return r;
    }

    template<typename T1>
    static representation interval_part(representation_dec_type<T1> const& x) {
        print_op("interval_part");
        print_dec(x);
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::interval_part(x);
        return r;
    }

    template<typename T1>
    static representation_dec set_dec(representation_type<T1> const& x, decoration::decoration dec) {
        print_op("set_dec");
        print_bare(x);
        printf(" | ");
        printf("%s", dec_strings[static_cast<int>(dec) >> 2]);
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::set_dec(x, dec);
        return r;
    }

    static representation exact_to_interval(std::string const& s) {
        print_op("exact_to_interval");
        printf("\"%s\"", s.c_str());
        printf("\n");
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exact_to_interval(s);
        return r;
    }

    static representation_dec exact_to_decorated_interval(std::string const& s) {
        print_op("exact_to_decorated_interval");
        printf("\"%s\"", s.c_str());
        printf("\n");
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::exact_to_decorated_interval(s);
        return r;
    }

    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_interval_to_text(std::basic_ostream<CharT, Traits>& os, representation const& x) {
        print_op("operator_interval_to_text");
        print_bare(x);
        printf("\n");
        std::basic_ostream<CharT, Traits>& r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::operator_interval_to_text(os, x);
        return r;
    }

    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_interval_to_text(std::basic_ostream<CharT, Traits>& os, representation_dec const& x) {
        print_op("operator_interval_to_text");
        print_dec(x);
        printf("\n");
        std::basic_ostream<CharT, Traits>& r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::operator_interval_to_text(os, x);
        return r;
    }

    static representation copy(representation const& other) {
        representation r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::copy(other);
        printf("copy(");
        print_bare(other);
        printf(") = ");
        print_bare(r);
        printf(";\n");
        return r;
    }

    static representation_dec copy(representation_dec const& other) {
        representation_dec r = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::copy(other);
        printf("copy(");
        print_dec(other);
        printf(") = ");
        print_dec(r);
        printf(";\n");
        return r;
    }

    template< typename CharT, typename Traits >
    static std::basic_istream<CharT, Traits>& operator_text_to_interval(std::basic_istream<CharT, Traits>& is, representation& x) {
        p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::operator_text_to_interval(is, x);
        printf("operator_text_to_interval(is,");
        print_bare(x);
        printf(") = is;\n");
        return is;
    }

    template< typename CharT, typename Traits >
    static std::basic_istream<CharT, Traits>& operator_text_to_interval(std::basic_istream<CharT, Traits>& is, representation_dec& x) {
        p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::operator_text_to_interval(is, x);
        printf("operator_text_to_interval(is,");
        print_dec(x);
        printf(") = is;\n");
        return is;
    }
};

}}}}
