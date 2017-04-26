/*
 * Copyright (c) 2012, JInterval Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.text2interval.gen;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.set.OverlapState;

/**
 *
 */
public class GenP1788 extends GenP1788Base {

    private static final String classPrefix = "mpfr_bin_ieee754_flavor";
    private static final String suf_mo = "_mo";
//    private static final String suf_mo = "";
    private static final String suf_j = "_j";
//    private static final String suf_j = "";
    private static final String suf_m = "_m";
//    private static final String suf_m = "";
    private static final String suf_t = "_t";
    private static String[] filesToCopy = {
        "COPYING.LIB"
    };

    GenP1788(String className) {
        super(className);
    }

    private void genIncludes() {
        s("#include <stdio.h>");
        s("#include <malloc.h>");
        s("#include <math.h>");
        s("#include <float.h>");
        s("#include <string.h>");
        s("#include <assert.h>");
        s("#include <mpfr.h>");
        s("#include \"p1788_reduction.inc.c\"");
        s("#include <mpfi.h>");
        s("#include \"mpfi_p1788.h\"");
        s("#include \"p1788.h\"");
        s();
    }

    private static Kind k(String kindName) {
        String[] ss = kindName.split("[ ]+");
        assert ss.length == 2;
        return Kind.valueOf(ss[0]);
    }

    private static Kind[] k(String[] kindName) {
        Kind[] r = new Kind[kindName.length];
        for (int i = 0; i < kindName.length; i++) {
            r[i] = k(kindName[i]);
        }
        return r;
    }

    private static String n(String kindName) {
        String[] ss = kindName.split("[ ]+");
        assert ss.length == 2;
        return ss[1];
    }

    private static String[] n(String[] kindName) {
        String[] r = new String[kindName.length];
        for (int i = 0; i < kindName.length; i++) {
            r[i] = n(kindName[i]);
        }
        return r;
    }

    private static class Op0 extends Operation {

        private final String inf, sup, dec;

        Op0(String opName, String cppName, String cppNameDec, String inf, String sup, String dec) {
            super(opName, cppName, cppNameDec, Decoration.valueOf(dec), false, new Kind[]{Kind.INTERVAL}, new String[0]);
            this.inf = inf;
            this.sup = sup;
            this.dec = dec;
        }

        @Override
        public int getDecPairs() {
            return cppName == null ? D_D : (B_B | D_D);
        }

        @Override
        void genC(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            String infS = inf.equals("+INFINITY") && g.infsupNan ? "NAN" : inf;
            String supS = sup.equals("-INFINITY") && g.infsupNan ? "NAN" : sup;
            g.s();
            g.bFun(genTempFun(g, isDecoratedRes, isDecoratedArg));
            {
                g.bSwitch("r_tag");
                {
                    for (Format fmt : formats) {
                        g.bCase(fmt.tag());
                        g.s("{");
                        g.b();
                        {
                            g.s(fmt.cFormat(isDecoratedRes) + "* p = (" + fmt.cFormat(isDecoratedRes) + "*) r;");
                            g.s("p->inf = " + infS + ";");
                            g.s("p->sup = " + supS + ";");
                            if (isDecoratedRes) {
                                g.s("p->decoration = " + dec + ";");
                            }
                        }
                        g.e();
                        g.s("}");
                        g.endCase();
                    }
                    g.bDefault();
                    g.s(f("assert", "0") + ";");
                    g.endCase();
                }
                g.endSwitch();
            }
            g.ret("0");
            g.endFun();
        }

        @Override
        void genBodyMPFI(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            String infS = inf.equals("+INFINITY") && g.infsupNan ? "NAN" : inf;
            String supS = sup.equals("-INFINITY") && g.infsupNan ? "NAN" : sup;
            infS = infS
                    .replace("NAN", f("std::numeric_limits<T>::quiet_NaN"))
                    .replace("INFINITY", f("std::numeric_limits<T>::infinity"));
            supS = supS
                    .replace("NAN", f("std::numeric_limits<T>::quiet_NaN"))
                    .replace("INFINITY", f("std::numeric_limits<T>::infinity"));
            String decS = "decoration::decoration::" + dec.toLowerCase();
            if (isDecoratedRes) {
                g.ret(f("REP_DEC<T>", f("REP<T>", infS, supS), decS));
            } else {
                g.ret(f("REP<T>", infS, supS));
            }
        }
    }

    private static class Arith extends Operation {

        Arith(String opName, String cppName, String... ops) {
            super(opName, cppName, null, Kind.INTERVAL, n(ops), k(ops));
        }

        @Override
        void genDecMoore(GenP1788Base g) {
            switch (opName) {
                case "div":
                    g.s("p1788::decoration::decoration dec = Moore::is_member(0.0f, bare(y)) ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "recip":
                    g.s("p1788::decoration::decoration dec = Moore::is_member(0.0f, bare(x)) ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "sqrt":
                    g.s("p1788::decoration::decoration dec = Moore::inf(bare(x)) < 0.0f ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "pown":
                    g.s("p1788::decoration::decoration dec = p < 0 && Moore::is_member(0.0f, bare(x)) ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "pow":
                    g.s("p1788::decoration::decoration dec = Moore::inf(bare(x)) < 0.0f || (Moore::is_member(0.0f, bare(x)) && Moore::inf(bare(y)) <= 0.0f)");
                    g.s("  ? p1788::decoration::decoration::trv");
                    g.s("  : p1788::decoration::decoration::com;");
                    break;
                case "log":
                case "log2":
                case "log10":
                    g.s("p1788::decoration::decoration dec = Moore::inf(bare(x)) <= 0.0f ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "tan":
                    g.s("representation_type<T1> cosx = " + f("Moore::cos<T1>", f("bare", "x")) + ";");
                    g.s("bool has_singularities = " + f("Moore::interior", "representation_type<T1>(0.0f, 0.0f)", "cosx") + ";");
                    g.s("p1788::decoration::decoration dec = has_singularities ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "asin":
                case "acos":
                    g.s("p1788::decoration::decoration dec = !Moore::subset(bare(x), representation_type<T1>(-1.0f,1.0f)) ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "atan2":
                    g.s("p1788::decoration::decoration dec = !Moore::is_member(0.0f, bare(y)) || Moore::inf(bare(x)) > 0.0f ? p1788::decoration::decoration::com");
                    g.s("  : Moore::sup(bare(x)) >= 0.0f ? p1788::decoration::decoration::trv");
                    g.s("  : Moore::inf(bare(y)) < 0.0f ? p1788::decoration::decoration::def");
                    g.s("  : p1788::decoration::decoration::dac;");
                    break;
                case "acosh":
                    g.s("p1788::decoration::decoration dec = Moore::inf(bare(x)) < 1.0f ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "atanh":
                    g.s("p1788::decoration::decoration dec = !Moore::interior(bare(x), representation_type<T1>(-1.0f,1.0f)) ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
                    break;
                case "sign":
                    g.s("p1788::decoration::decoration dec = !Moore::is_singleton(r) ? p1788::decoration::decoration::def");
                    g.s("  : Moore::is_member(0.0f, bare(x)) ? p1788::decoration::decoration::dac");
                    g.s("  : p1788::decoration::decoration::com;");
                    break;
                case "ceil":
                    g.s("p1788::decoration::decoration dec = !Moore::is_singleton(r) ? p1788::decoration::decoration::def");
                    g.s(" : Moore::sup(Moore::sub(bare(x),r)) >= 0.0f ? p1788::decoration::decoration::dac");
                    g.s(" : p1788::decoration::decoration::com;");
                    break;
                case "floor":
                    g.s("p1788::decoration::decoration dec = !Moore::is_singleton(r) ? p1788::decoration::decoration::def");
                    g.s("  : Moore::inf(sub(bare(x),r)) <= 0.0f ? p1788::decoration::decoration::dac");
                    g.s("  : p1788::decoration::decoration::com;");
                    break;
                case "trunc":
                    g.s("p1788::decoration::decoration dec = !Moore::is_singleton(r) ? p1788::decoration::decoration::def");
                    g.s("  : (Moore::inf(bare(x)) >= 1.0f && Moore::inf(sub(bare(x),r)) <= 0.0f)");
                    g.s("  || (Moore::sup(bare(x)) <= -1.0f && Moore::sup(sub(bare(x),r)) >= 0.0f) ? p1788::decoration::decoration::dac");
                    g.s("  : p1788::decoration::decoration::com;");
                    break;
                case "roundTiesToEven":
                case "roundTiesToAway":
                    g.s("p1788::decoration::decoration dec = !Moore::is_singleton(r) ? p1788::decoration::decoration::def");
                    g.s(" : !Moore::interior(Moore::sub(bare(x),r), representation_type<T1>(-0.5f,0.5f)) ? p1788::decoration::decoration::dac");
                    g.s(" : p1788::decoration::decoration::com;");
                    break;
                default:
                    g.s("p1788::decoration::decoration dec = p1788::decoration::decoration::com;");
            }
        }
    }

    private static class Op2Trivial extends Operation {

        Op2Trivial(String opName, String cppName) {
            super(opName, cppName, Decoration.TRV, Kind.INTERVAL,
                    new String[]{"x", "y"},
                    Kind.INTERVAL, Kind.INTERVAL);
        }
    }

    private static class OpMulRevToPair extends Operation {

        OpMulRevToPair(String opName, String cppName) {
            super(opName, cppName, cppName, null, false,
                    new Kind[]{Kind.INTERVAL, Kind.INTERVAL},
                    new String[]{"b", "c"},
                    Kind.INTERVAL, Kind.INTERVAL);
        }

        @Override
        void genDecMoore(GenP1788Base g) {
            g.s("p1788::decoration::decoration dec1 = Moore::is_member(0.0f, bare(b)) ? p1788::decoration::decoration::trv : p1788::decoration::decoration::com;");
            g.s("p1788::decoration::decoration dec2 = p1788::decoration::decoration::trv;");
        }
    }

    private static class Op1Rev extends Operation {

        Op1Rev(String opName, String cppName) {
            super(opName, cppName, Kind.INTERVAL,
                    new String[]{"c", "x"},
                    Kind.INTERVAL, Kind.INTERVAL);
        }
    }

    private static class Op1RevEntire extends Operation {

        Op1RevEntire(String opName, String cppName) {
            super(opName, cppName, Kind.INTERVAL,
                    new String[]{"c"},
                    Kind.INTERVAL);
            incName = incName + "Entire";
        }
    }

    private static class Op1pRev extends Operation {

        Op1pRev(String opName, String cppName) {
            super(opName, cppName, Kind.INTERVAL,
                    new String[]{"c", "x", "p"},
                    Kind.INTERVAL, Kind.INTERVAL, Kind.INT);
        }
    }

    private static class Op1pRevEntire extends Operation {

        Op1pRevEntire(String opName, String cppName) {
            super(opName, cppName, Kind.INTERVAL,
                    new String[]{"c", "p"},
                    Kind.INTERVAL, Kind.INT);
            incName = incName + "Entire";
        }
    }

    private static class Op2Rev extends Operation {

        Op2Rev(String opName, String cppName, boolean second) {
            this(opName, cppName, new String[]{second ? "a" : "b", "c", "x"});
        }

        Op2Rev(String opName, String cppName, String[] argNames) {
            super(opName, cppName, Kind.INTERVAL,
                    argNames,
                    Kind.INTERVAL, Kind.INTERVAL, Kind.INTERVAL);
        }
    }

    private static class Op2RevEntire extends Operation {

        Op2RevEntire(String opName, String cppName, boolean second) {
            this(opName, cppName, new String[]{second ? "a" : "b", "c"});
        }

        Op2RevEntire(String opName, String cppName, String[] argNames) {
            super(opName, cppName, Kind.INTERVAL,
                    argNames,
                    Kind.INTERVAL, Kind.INTERVAL);
            incName = incName + "Entire";
        }
    }

    private static class OpNumsToInterval extends Operation {

        OpNumsToInterval(String opName, String cppName, String cppNameDec) {
            super(opName, cppName, cppNameDec, null, true,
                    new Kind[]{Kind.INTERVAL},
                    new String[]{"l", "u"},
                    Kind.POINT, Kind.POINT);
        }

        @Override
        void genExceptionMoore(GenP1788Base g, String call) {
            g.s("Moore::Accuracy exc = " + call + ";");
            g.bIf("exc == Moore::Accuracy::Invalid");
            {
                g.s(f("p1788::exception::signal_undefined_operation") + ";");
            }
            g.elseIf("exc == Moore::Accuracy::Imprecise");
            {
                g.s(f("p1788::exception::signal_possibly_undefined_operation") + ";");
            }
            g.endIf();
        }

        @Override
        void genDecMoore(GenP1788Base g) {
            g.s("p1788::decoration::decoration dec;");
            g.bIf("exc == Moore::Accuracy::Invalid || exc == Moore::Accuracy::Imprecise");
            {
                g.s("dec = p1788::decoration::decoration::ill;");
            }
            g.elseIf();
            {
                g.s("dec = p1788::decoration::decoration::com;");
            }
            g.endIf();
        }
    }

    private static class OpNumsDecToInterval extends Operation {

        OpNumsDecToInterval(String opName, String cppName) {
            super(opName, cppName, cppName, null, true,
                    new Kind[]{Kind.INTERVAL},
                    new String[]{"l", "u", "dec"},
                    Kind.POINT, Kind.POINT, Kind.DEC);
        }

        @Override
        public int getDecPairs() {
            return D_D;
        }

        @Override
        void genExceptionMoore(GenP1788Base g, String call) {
            g.s("Moore::Accuracy exc;");
            g.bIf("dec > p1788::decoration::decoration::dac && !(std::isfinite(l) && std::isfinite(u))");
            {
                g.s("exc = Moore::Accuracy::Invalid;");
            }
            g.elseIf();
            {
                g.s("exc = " + call + ";");
            }
            g.endIf();
            g.bIf("exc == Moore::Accuracy::Invalid");
            {
                g.s(f("p1788::exception::signal_undefined_operation") + ";");
            }
            g.elseIf("exc == Moore::Accuracy::Imprecise");
            {
                g.s(f("p1788::exception::signal_possibly_undefined_operation") + ";");
            }
            g.endIf();
        }

        @Override
        void genDecMoore(GenP1788Base g) {
            g.bIf("exc == Moore::Accuracy::Invalid");
            {
                g.s("dec = p1788::decoration::decoration::ill;");
            }
            g.endIf();
        }
    }

    private static class OpTextToInterval extends Operation {

        OpTextToInterval(String opName, String cppName, boolean isDecorated) {
            super(opName,
                    isDecorated ? null : cppName,
                    isDecorated ? cppName : null,
                    null, true,
                    new Kind[]{Kind.INTERVAL},
                    new String[]{"s"},
                    Kind.TEXT);
        }

        @Override
        public int getDecPairs() {
            return cppNameDec != null ? D_D : B_B;
        }

        @Override
        void genExceptionMoore(GenP1788Base g, String call) {
            g.s("Moore::Accuracy exc = " + call + ";");
            g.bIf("exc == Moore::Accuracy::Invalid");
            {
                g.s(f("p1788::exception::signal_undefined_operation") + ";");
            }
            g.elseIf("exc == Moore::Accuracy::Imprecise");
            {
                g.s(f("p1788::exception::signal_possibly_undefined_operation") + ";");
            }
            g.endIf();
        }

        @Override
        void genDecMoore(GenP1788Base g) {
            g.s("p1788::decoration::decoration dec;");
            g.bIf("exc == Moore::Accuracy::Invalid || exc == Moore::Accuracy::Imprecise");
            {
                g.s("dec = p1788::decoration::decoration::ill;");
            }
            g.elseIf();
            {
                g.s("dec = static_cast<p1788::decoration::decoration>(d);");
            }
            g.endIf();
        }
        /*
        @Override
        void genBodyMooreValid(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.s(isDecoratedRes ? "representation_dec r;" : "representation r;");
            String call = isDecoratedRes
                    ? f("r.text_to_interval_impl", "s.c_str()")
                    : f("Moore::text_to_interval", "r", "s.c_str()");
            g.s("Moore::Accuracy exc = " + call + ";");
            g.bIf("exc == Moore::Accuracy::Invalid");
            {
                g.s(f("p1788::exception::signal_undefined_operation") + ";");
            }
            g.elseIf("exc == Moore::Accuracy::Imprecise");
            {
                g.s(f("p1788::exception::signal_possibly_undefined_operation") + ";");
            }
            g.endIf();
            g.ret("r");
        }
         */
    }

    private static class OpNumber extends Operation {

        OpNumber(String opName, String cppName, String rndMode) {
            super(opName, cppName, Kind.POINT,
                    new String[]{"x"},
                    Kind.INTERVAL);
        }
    }

    private static class OpMidRad extends Operation {

        OpMidRad(String opName, String cppName, String... rndMode) {
            super(opName, cppName, cppName, null, false,
                    new Kind[]{Kind.POINT, Kind.POINT},
                    new String[]{"x"},
                    Kind.INTERVAL);
        }
    }

    private static class Bool extends Operation {

        Bool(String opName, String cppName, String... ops) {
            super(opName, cppName, Kind.BOOL, n(ops), k(ops));
        }
    }

    private static class IsValid extends Operation {

        IsValid(String opName, String cppName) {
            super(opName, cppName, Kind.BOOL,
                    new String[]{"x"},
                    Kind.INTERVAL);
        }

        @Override
        void genC(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.s();
            g.bFun(genTempFun(g, isDecoratedRes, isDecoratedArg));
            {
                g.retIf("!" + f(isDecoratedArg ? "is_valid_d" : "is_valid_b", argNames[0] + "_tag", argNames[0]), "EXC_INVALID_OPERAND");
                g.ret("1");
            }
            g.endFun();
        }

        @Override
        void genMoore(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.s();
            g.s("template<typename T_>");
            g.bFun("static bool " + f("check_valid",
                    "representation" + (isDecoratedRes ? "_dec" : "") + "_type<T_> const & x"));
            if (isDecoratedRes) {
                g.s("p1788::decoration::decoration d = "
                        + f("static_cast<p1788::decoration::decoration>", "x.dec_") + ";");
                g.ret(f("check_valid", f("bare", "x"))
                        + " && " + f("p1788::decoration::is_valid", "d"));
            } else {
                g.bIf(f("is_valid", "x"));
                {
                    g.ret("true");
                }
                g.elseIf();
                {
                    g.s(f("p1788::exception::signal_invalid_operand") + ";");
                    g.ret("false");
                }
                g.endIf();
            }
            g.endFun();
        }

        @Override
        void genBodyMPFI(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            if (isDecoratedRes) {
                g.s("bool r;");
                g.bSwitch("x.second");
                {
                    g.bCase("decoration::decoration::com");
                    g.s("r = x.first.first <= x.first.second && x.first.first != -std::numeric_limits<T>::infinity() && x.first.second != std::numeric_limits<T>::infinity();");
                    g.endCase();
                    g.bCase("decoration::decoration::dac");
                    g.s("r = x.first.first <= x.first.second && x.first.first != std::numeric_limits<T>::infinity() && x.first.second != -std::numeric_limits<T>::infinity();");
                    g.endCase();
                    g.bCase("decoration::decoration::def");
                    g.s("r = x.first.first <= x.first.second && x.first.first != std::numeric_limits<T>::infinity() && x.first.second != -std::numeric_limits<T>::infinity();");
                    g.endCase();
                    g.bCase("decoration::decoration::trv");
                    g.s("r = (x.first.first <= x.first.second && x.first.first != std::numeric_limits<T>::infinity() && x.first.second != -std::numeric_limits<T>::infinity()) || ("
                            + (g.infsupNan ? "std::isnan(x.first.first) && std::isnan(x.first.second));"
                                    : "x.first.first == std::numeric_limits<T>::infinity() && x.first.second == -std::numeric_limits<T>::infinity());"));
                    g.endCase();
                    g.bCase("decoration::decoration::ill");
                    g.s("r = std::isnan(x.first.first) && std::isnan(x.first.second);");
                    g.endCase();
                    g.bDefault();
                    g.s("r = false;");
                    g.endCase();
                }
                g.endSwitch();

            } else {
                g.s("bool r = (x.first <= x.second && x.first != std::numeric_limits<T>::infinity() && x.second != -std::numeric_limits<T>::infinity()) || ("
                        + (g.infsupNan ? "std::isnan(x.first) && std::isnan(x.second));"
                                : "x.first == std::numeric_limits<T>::infinity()&& x.second == -std::numeric_limits<T>::infinity());"));
            }
            g.ret("r || !" + f("exception::signal_invalid_operand"));
        }
    }

    private static class IsNaI extends Operation {

        IsNaI(String opName, String cppName) {
            super(opName, cppName, Kind.BOOL,
                    new String[]{"x"},
                    Kind.INTERVAL);
        }

        @Override
        public int getDecPairs() {
            return D_D;
        }

        @Override
        void genC(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            assert isDecoratedRes && isDecoratedArg;
            g.s();
            g.bFun(genTempFun(g, true, true));
            {
                g.retIf("!" + f("is_valid_d", argNames[0] + "_tag", argNames[0]), "EXC_INVALID_OPERAND");
                g.ret(f("is_nai", argNames[0] + "_tag", argNames[0]));
            }
            g.endFun();
        }

        @Override
        void genBodyMoore(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.ret("!check_valid(x) || x.dec_ == p1788::decoration::decoration::ill");
        }

        @Override
        void genBodyMPFI(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            assert isDecoratedRes;
            g.ret(f("is_valid", "x") + " && x.second == decoration::decoration::ill");
        }
    }

    private static class Overlap extends Operation {

        Overlap(String opName, String cppName) {
            super(opName, cppName, Kind.OVERLAP,
                    new String[]{"a", "b"},
                    Kind.INTERVAL, Kind.INTERVAL);
        }
    }

    private static class NewDec extends Operation {

        NewDec(String opName, String cppName) {
            super(opName, cppName, null, Kind.INTERVAL,
                    new String[]{"x"},
                    Kind.INTERVAL);
        }

        @Override
        public int getDecPairs() {
            return D_B;
        }

        @Override
        void genDecMoore(GenP1788Base g) {
            g.s("p1788::decoration::decoration dec = p1788::decoration::decoration::com;");
        }

    }

    private static class DecorationPart extends Operation {

        DecorationPart(String opName, String cppName) {
            super(opName, cppName, Kind.DEC,
                    new String[]{"x"},
                    Kind.INTERVAL);
        }

        @Override
        public int getDecPairs() {
            return B_D;
        }

        @Override
        void genBodyMooreValid(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.ret(f("static_cast<p1788::decoration::decoration>", "x.dec_"));
        }

        @Override
        void genBodyMPFI(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            assert isDecoratedArg;
            g.retIf("!" + f("is_valid", "x"), "decoration::decoration::ill;");
            g.ret("x.second");
        }
    }

    private static class IntervalPart extends Operation {

        IntervalPart(String opName, String cppName) {
            super(opName, cppName, Kind.INTERVAL,
                    new String[]{"x"},
                    Kind.INTERVAL);
        }

        @Override
        public int getDecPairs() {
            return B_D;
        }

        @Override
        void genBodyMooreValid(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.bIf("x.dec_ == p1788::decoration::decoration::ill");
            {
                g.s(f("p1788::exception::signal_interval_part_of_nai") + ";");
                g.ret(f("representation"));
            }
            g.endIf();
            g.ret(f("representation::convert_type", f("bare", "x")));
        }

        @Override
        void genBodyMPFI(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.retIf("!" + f("mpfr_bin_ieee754_flavor<T1>::is_valid", "x"), f("empty"));
            g.bIf("x.second == decoration::decoration::ill");
            {
                g.s(f("exception::signal_interval_part_of_nai") + ";");
                g.ret(f("empty"));
            }
            g.endIf();
            g.ret(f("convert_type<T1>", "x.first"));
        }
    }

    private static class SetDec extends Operation {

        SetDec(String opName, String cppName) {
            super(opName, cppName, null, Kind.INTERVAL,
                    new String[]{"x", "dec"},
                    Kind.INTERVAL, Kind.DEC);
        }

        @Override
        public int getDecPairs() {
            return D_B;
        }
        
        @Override
        void genDecMoore(GenP1788Base g) {
        }

    }

    private static class Reduction1 extends Operation {

        Reduction1(String opName) {
            super(opName, null, Kind.POINT,
                    new String[]{"n", "a", "rnd"},
                    Kind.LEN, Kind.POINT_ARRAY, Kind.RND);
        }

        @Override
        public int getDecPairs() {
            return 0;
        }

        @Override
        void genH(GenP1788Base g) {
            g.s("extern int " + f(getName(g), "int r_tag", "void *r", "int n", "void *a", "int rnd") + ";");
        }

        @Override
        void genC(GenP1788Base g) {
            g.s();
            g.bFun("int " + f(getName(g), "int r_tag", "void *r", "int n", "void *a", "int rnd"));
            {
                g.bSwitch("r_tag");
                {
                    for (Format pfmt : formats) {
                        g.bCase(pfmt.tag());
                        g.s(f(getName(g) + "_" + pfmt.cCharLower(),
                                "(" + pfmt.cFormat() + "*) r",
                                "n",
                                "(" + pfmt.cFormat() + "*) a",
                                "rnd") + ";");
                        g.endCase();
                    }
                    g.bDefault();
                    g.s(f("assert", "0") + ";");
                    g.endCase();
                }
                g.endSwitch();
            }
            g.endFun();
        }
    }

    private static class Reduction2 extends Operation {

        Reduction2(String opName) {
            super(opName, null, Kind.POINT,
                    new String[]{"n", "a", "b", "rnd"},
                    Kind.LEN, Kind.POINT_ARRAY, Kind.POINT_ARRAY, Kind.RND);
        }

        @Override
        public int getDecPairs() {
            return 0;
        }

        @Override
        void genH(GenP1788Base g) {
            g.s("extern int " + f(getName(g), "int r_tag", "void *r", "int n", "void *a", "void *b", "int rnd") + ";");
        }

        @Override
        void genC(GenP1788Base g) {
            g.s();
            g.bFun("int " + f(getName(g), "int r_tag", "void *r", "int n", "void *a", "void *b", "int rnd"));
            {
                g.bSwitch("r_tag");
                {
                    for (Format fmt : formats) {
                        g.bCase(fmt.tag());
                        g.s(f(getName(g) + "_" + fmt.cCharLower(),
                                "(" + fmt.cFormat() + "*) r",
                                "n",
                                "(" + fmt.cFormat() + "*) a",
                                "(" + fmt.cFormat() + "*) b",
                                "rnd") + ";");
                        g.endCase();
                    }
                    g.bDefault();
                    g.s(f("assert", "0") + ";");
                    g.endCase();
                }
                g.endSwitch();
            }
            g.endFun();
        }
    }

    private static class IntervalToText extends Operation {

        IntervalToText(String opName, String cppName) {
            super(opName, cppName, null, Kind.STREAM,
                    new String[]{"x", "cs"},
                    Kind.INTERVAL, Kind.CS);
        }

        @Override
        void genBodyMooreValid(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            if (isDecoratedArg) {
                g.bIf(f("is_nai", "x"));
                {
                    g.s("os << \"[nai]\";");
                }
                g.elseIf();
                {
                    g.s("os << bare(x);");
                    g.shortIf("!" + f("is_empty", "x"), "os << '_' << " + f("static_cast<p1788::decoration::decoration>", "x.dec_") + ";");
                }
                g.endIf();
            } else {
                g.s("os << x;");
            }
            g.ret("os");
        }
    }

    private static class IntervalToExact extends Operation {

        IntervalToExact(String opName, String cppName) {
            super(opName, cppName, null, Kind.TEXT,
                    new String[]{"x"},
                    Kind.INTERVAL);
        }
    }
    private static Operation opIsValid = new IsValid("isValid", "is_valid");
    public static Operation opEmpty = new Op0("empty", "empty", "empty_dec",
            "+INFINITY", "-INFINITY", "TRV");
    public static Operation opEntire = new Op0("entire", "entire", "entire_dec",
            "-INFINITY", "+INFINITY", "DAC");
    public static Operation opNaI = new Op0("nai", null, "nai",
            "NAN", "NAN", "ILL");
    public static Operation opPos = new Arith("pos", "pos",
            "INTERVAL x");
    public static Operation opNeg = new Arith("neg", "neg",
            "INTERVAL x");
    public static Operation opAdd = new Arith("add", "add",
            "INTERVAL x", "INTERVAL y");
    public static Operation opSub = new Arith("sub", "sub",
            "INTERVAL x", "INTERVAL y");
    public static Operation opMul = new Arith("mul", "mul",
            "INTERVAL x", "INTERVAL y");
    public static Operation opDiv = new Arith("div", "div",
            "INTERVAL x", "INTERVAL y");
    public static Operation opRecip = new Arith("recip", "recip",
            "INTERVAL x");
    public static Operation opSqr = new Arith("sqr", "sqr",
            "INTERVAL x");
    public static Operation opSqrt = new Arith("sqrt", "sqrt",
            "INTERVAL x");
    public static Operation opFma = new Arith("fma", "fma",
            "INTERVAL x", "INTERVAL y", "INTERVAL z");
    public static Operation opPown = new Arith("pown", "pown",
            "INTERVAL x", "INT p");
    public static Operation opPow = new Arith("pow", "pow",
            "INTERVAL x", "INTERVAL y");
    public static Operation opExp = new Arith("exp", "exp",
            "INTERVAL x");
    public static Operation opExp2 = new Arith("exp2", "exp2",
            "INTERVAL x");
    public static Operation opExp10 = new Arith("exp10", "exp10",
            "INTERVAL x");
    public static Operation opLog = new Arith("log", "log",
            "INTERVAL x");
    public static Operation opLog2 = new Arith("log2", "log2",
            "INTERVAL x");
    public static Operation opLog10 = new Arith("log10", "log10",
            "INTERVAL x");
    public static Operation opSin = new Arith("sin", "sin",
            "INTERVAL x");
    public static Operation opCos = new Arith("cos", "cos",
            "INTERVAL x");
    public static Operation opTan = new Arith("tan", "tan",
            "INTERVAL x");
    public static Operation opAsin = new Arith("asin", "asin",
            "INTERVAL x");
    public static Operation opAcos = new Arith("acos", "acos",
            "INTERVAL x");
    public static Operation opAtan = new Arith("atan", "atan",
            "INTERVAL x");
    public static Operation opAtan2 = new Arith("atan2", "atan2",
            "INTERVAL y", "INTERVAL x");
    public static Operation opSinh = new Arith("sinh", "sinh",
            "INTERVAL x");
    public static Operation opCosh = new Arith("cosh", "cosh",
            "INTERVAL x");
    public static Operation opTanh = new Arith("tanh", "tanh",
            "INTERVAL x");
    public static Operation opAsinh = new Arith("asinh", "asinh",
            "INTERVAL x");
    public static Operation opAcosh = new Arith("acosh", "acosh",
            "INTERVAL x");
    public static Operation opAtanh = new Arith("atanh", "atanh",
            "INTERVAL x");
    public static Operation opSign = new Arith("sign", "sign",
            "INTERVAL x");
    public static Operation opCeil = new Arith("ceil", "ceil",
            "INTERVAL x");
    public static Operation opFloor = new Arith("floor", "floor",
            "INTERVAL x");
    public static Operation opTrunc = new Arith("trunc", "trunc",
            "INTERVAL x");
    public static Operation opRoundTiesToEven = new Arith("roundTiesToEven", "round_ties_to_even",
            "INTERVAL x");
    public static Operation opRoundTiesToAway = new Arith("roundTiesToAway", "round_ties_to_away",
            "INTERVAL x");
    public static Operation opAbs = new Arith("abs", "abs",
            "INTERVAL x");
    public static Operation opMin = new Arith("min", "min",
            "INTERVAL x", "INTERVAL y");
    public static Operation opMax = new Arith("max", "max",
            "INTERVAL x", "INTERVAL y");
    public static Operation opMulRevToPair = new OpMulRevToPair("mulRevToPair", "mul_rev_to_pair");
    public static Operation opSqrRev = new Op1Rev("sqrRev", "sqr_rev");
    public static Operation opSqrRevEntire = new Op1RevEntire("sqrRevEntire", "sqr_rev");
    public static Operation opAbsRev = new Op1Rev("absRev", "abs_rev");
    public static Operation opAbsRevEntire = new Op1RevEntire("absRevEntire", "abs_rev");
    public static Operation opPownRev = new Op1pRev("pownRev", "pown_rev");
    public static Operation opPownRevEntire = new Op1pRevEntire("pownRevEntire", "pown_rev");
    public static Operation opSinRev = new Op1Rev("sinRev", "sin_rev");
    public static Operation opSinRevEntire = new Op1RevEntire("sinRevEntire", "sin_rev");
    public static Operation opCosRev = new Op1Rev("cosRev", "cos_rev");
    public static Operation opCosRevEntire = new Op1RevEntire("cosRevEntire", "cos_rev");
    public static Operation opTanRev = new Op1Rev("tanRev", "tan_rev");
    public static Operation opTanRevEntire = new Op1RevEntire("tanRevEntire", "tan_rev");
    public static Operation opCoshRev = new Op1Rev("coshRev", "cosh_rev");
    public static Operation opCoshRevEntire = new Op1RevEntire("coshRevEntire", "cosh_rev");
    public static Operation opMulRev = new Op2Rev("mulRev", "mul_rev", false);
    public static Operation opMulRevEntire = new Op2RevEntire("mulRevEntire", "mul_rev", false);
    public static Operation opPowRev1 = new Op2Rev("powRev1", "pow_rev1", false);
    public static Operation opPowRev1Entire = new Op2RevEntire("powRev1Entire", "pow_rev1", false);
    public static Operation opPowRev2 = new Op2Rev("powRev2", "pow_rev2", true);
    public static Operation opPowRev2Entire = new Op2RevEntire("powRev2Entire", "pow_rev2", true);
    public static Operation opAtan2Rev1 = new Op2Rev("atan2Rev1", "atan2_rev1", false);
    public static Operation opAtan2Rev1Entire = new Op2RevEntire("atan2Rev1Entire", "atan2_rev1", false);
    public static Operation opAtan2Rev2 = new Op2Rev("atan2Rev2", "atan2_rev2", true);
    public static Operation opAtan2Rev2Entire = new Op2RevEntire("atan2Rev2Entire", "atan2_rev2", true);
    public static Operation opCancelMinus = new Op2Trivial("cancelMinus", "cancel_minus");
    public static Operation opCancelPlus = new Op2Trivial("cancelPlus", "cancel_plus");
    public static Operation opIntersection = new Op2Trivial("intersection", "intersection");
    public static Operation opConvexHull = new Op2Trivial("convexHull", "convex_hull");
    public static Operation opNumsToInterval = new OpNumsToInterval("numsToInterval", "nums_to_interval", "nums_to_decorated_interval");
    public static Operation opNumsDecToInterval = new OpNumsDecToInterval("numsDecToInterval", "nums_dec_to_decorated_interval");
    public static Operation opTextToInterval = new OpTextToInterval("textToInterval", "text_to_interval", false);
    public static Operation opTextToDecoratedInterval = new OpTextToInterval("textToDecoratedInterval", "text_to_decorated_interval", true);
    public static Operation opConvertType = new Arith("convertType", "convert_type",
            "INTERVAL x");
    public static Operation opInf = new OpNumber("inf", "inf", "MPFR_RNDD");
    public static Operation opSup = new OpNumber("sup", "sup", "MPFR_RNDU");
    public static Operation opMid = new OpNumber("mid", "mid", "MPFR_RNDN");
    public static Operation opRad = new OpNumber("rad", "rad", "MPFR_RNDU");
    public static Operation opWid = new OpNumber("wid", "wid", "MPFR_RNDU");
    public static Operation opMag = new OpNumber("mag", "mag", "MPFR_RNDU");
    public static Operation opMig = new OpNumber("mig", "mig", "MPFR_RNDD");
    public static Operation opMidRad = new OpMidRad("midRad", "mid_rad", "MPFR_RNDN", "MPFR_RNDU");
    public static Operation opIsEmpty = new Bool("isEmpty", "is_empty",
            "INTERVAL x");
    public static Operation opIsEntire = new Bool("isEntire", "is_entire",
            "INTERVAL x");
    public static Operation opIsNaI = new IsNaI("isNaI", "is_nai");
    public static Operation opIsCommonInterval = new Bool("isCommonInterval", "is_common_interval",
            "INTERVAL x");
    public static Operation opIsSingleton = new Bool("isSingleton", "is_singleton",
            "INTERVAL x");
    public static Operation opIsMember = new Bool("isMember", "is_member",
            "POINT m", "INTERVAL x");
    public static Operation opEqual = new Bool("equal", "equal",
            "INTERVAL a", "INTERVAL b");
    public static Operation opSubset = new Bool("subset", "subset",
            "INTERVAL a", "INTERVAL b");
    public static Operation opLess = new Bool("less", "less",
            "INTERVAL a", "INTERVAL b");
    public static Operation opPrecedes = new Bool("precedes", "precedes",
            "INTERVAL a", "INTERVAL b");
    public static Operation opInterior = new Bool("interior", "interior",
            "INTERVAL a", "INTERVAL b");
    public static Operation opStrictLess = new Bool("strictLess", "strict_less",
            "INTERVAL a", "INTERVAL b");
    public static Operation opStrictPrecedes = new Bool("strictPrecedes", "strict_precedes",
            "INTERVAL a", "INTERVAL b");
    public static Operation opDisjoint = new Bool("disjoint", "disjoint",
            "INTERVAL a", "INTERVAL b");
    public static Operation opOverlap = new Overlap("overlap", "overlap");
    public static Operation opNewDec = new NewDec("newDec", "new_dec");
    public static Operation opDecorationPart = new DecorationPart("decorationPart", "decoration_part");
    public static Operation opIntervalPart = new IntervalPart("intervalPart", "interval_part");
    public static Operation opSetDec = new SetDec("setDec", "set_dec");
    private static Operation opSum = new Reduction1("sum");
    private static Operation opSumAbs = new Reduction1("sumAbs");
    private static Operation opDot = new Reduction2("dot");
    private static Operation opSumSquare = new Reduction1("sumSquare");
    public static Operation opExactToInterval = new OpTextToInterval("exactToInterval", "exact_to_interval", false);
    public static Operation opExactToDecoratedInterval = new OpTextToInterval("exactToDecoratedInterval", "exact_to_decorated_interval", true);
    public static Operation opIntervalToText = new IntervalToText("intervalToText", "operator_interval_to_text");
    public static Operation opIntervalToExact = new IntervalToExact("intervalToExact", "interval_to_exact");
    private Operation[] allOperations = {
        opIsValid,
        opEmpty,
        opEntire,
        opNaI,
        opConvertType,
        opPos,
        opNeg,
        opAdd,
        opSub,
        opMul,
        opDiv,
        opRecip,
        opSqr,
        opSqrt,
        opFma,
        opPown,
        opPow,
        opExp,
        opExp2,
        opExp10,
        opLog,
        opLog2,
        opLog10,
        opSin,
        opCos,
        opTan,
        opAsin,
        opAcos,
        opAtan,
        opAtan2,
        opSinh,
        opCosh,
        opTanh,
        opAsinh,
        opAcosh,
        opAtanh,
        opSign,
        opCeil,
        opFloor,
        opTrunc,
        opRoundTiesToEven,
        opRoundTiesToAway,
        opAbs,
        opMin,
        opMax,
        opMulRevToPair,
        opSqrRev,
        opSqrRevEntire,
        opAbsRev,
        opAbsRevEntire,
        opPownRev,
        opPownRevEntire,
        opSinRev,
        opSinRevEntire,
        opCosRev,
        opCosRevEntire,
        opTanRev,
        opTanRevEntire,
        opCoshRev,
        opCoshRevEntire,
        opMulRev,
        opMulRevEntire,
        opPowRev1,
        opPowRev1Entire,
        opPowRev2,
        opPowRev2Entire,
        opAtan2Rev1,
        opAtan2Rev1Entire,
        opAtan2Rev2,
        opAtan2Rev2Entire,
        opCancelMinus,
        opCancelPlus,
        opIntersection,
        opConvexHull,
        opNumsToInterval,
        opNumsDecToInterval,
        opTextToInterval,
        opTextToDecoratedInterval,
        opInf,
        opSup,
        opMid,
        opRad,
        opWid,
        opMag,
        opMig,
        opMidRad,
        opIsEmpty,
        opIsEntire,
        opIsNaI,
        opIsCommonInterval,
        opIsSingleton,
        opIsMember,
        opEqual,
        opSubset,
        opLess,
        opPrecedes,
        opInterior,
        opStrictLess,
        opStrictPrecedes,
        opDisjoint,
        opOverlap,
        opNewDec,
        opDecorationPart,
        opIntervalPart,
        opSetDec,
        opSum,
        opSumAbs,
        opDot,
        opSumSquare,
        opExactToInterval,
        opExactToDecoratedInterval,
        opIntervalToText,
        opIntervalToExact
    };

    private void genStruct(boolean isDecorated, Format fmt) {
        s();
        s("typedef struct {");
        b();
        {
            s(fmt.cFormat() + " inf;");
            s(fmt.cFormat() + " sup;");
            if (isDecorated) {
                s("char decoration;");
            }
        }
        e();
        s("} " + fmt.cFormat(isDecorated) + ";");

    }

    private void genAllH() {
        s("/* Decorations */");
        s("#define ILL 0");
        s("#define TRV 4");
        s("#define DEF 8");
        s("#define DAC 12");
        s("#define COM 16");
        s();
        s("/* Exceptions */");
        s("#define EXC_UNDEFINED_OPERATION          -1");
        s("#define EXC_POSSIBLY_UNDEFINED_OPERATION -2");
        s("#define EXC_INTERVAL_PART_OF_NAI         -3");
        s("#define EXC_INVALID_OPERAND              -4");
        s();
        s("/* Overlap States */");
        for (OverlapState os : OverlapState.values()) {
            s("#define OVERLAP_" + os.name() + " " + os.ordinal());
        }
        s();
        s("/* Type tags */");
        for (int i = 0; i < formats.length; i++) {
            s("#define " + formats[i].tag() + " " + i);
        }
        s();
        for (Format fmt : formats) {
            genStruct(false, fmt);
            genStruct(true, fmt);
        }
        s();
        for (Operation op : allOperations) {
            s();
            op.genH(this);
        }
        s();
    }

    private void genOperH() {
        s("#include <assert.h>");
        s("#include \"p1788.h\"");
        s();
        for (Operation op : allOperations) {
            s();
            op.genOperH(this);
        }
        s();
    }

    private void genAllC() {
        genIncludes();
        s();
        s("#define MPFR_SAVE_RANGE_EXP(tag) mpfr_exp_t saved_emin, saved_emax; set_range_exp_tag((tag), &saved_emin, &saved_emax);");
        s("#define MPFR_RESTORE_RANGE_EXP() (mpfr_set_emin(saved_emin), mpfr_set_emax(saved_emax))");
        s();
        bFun("static void " + f("set_range_exp_tag", "int tag", "mpfr_exp_t* saved_emin", "mpfr_exp_t* saved_emax"));
        {
            s("*saved_emin = " + f("mpfr_get_emin") + ";");
            s("*saved_emax = " + f("mpfr_get_emax") + ";");
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s(f("mpfr_set_emin", fmt.cMath() + "_MIN_EXP - " + fmt.cMath() + "_MANT_DIG + 1") + ";");
                    s(f("mpfr_set_emax", fmt.cMath() + "_MAX_EXP") + ";");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static mpfr_prec_t " + f("p1788_get_prec", "int tag"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    ret(fmt.cMath() + "_MANT_DIG");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static int " + f("is_valid_b", "int tag", "const void *x"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("{");
                    b();
                    {
                        s(fmt.cFormat(false) + "* p = (" + fmt.cFormat(false) + "*) x;");
                        ret("p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || "
                                + (infsupNan ? "p->inf != p->inf && p->sup != p->sup"
                                        : "p->inf == INFINITY && p->sup == -INFINITY"));
                    }
                    e();
                    s("}");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static int " + f("is_valid_d", "int tag", "const void *x"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("{");
                    b();
                    {
                        s(fmt.cFormat(true) + "* p = (" + fmt.cFormat(true) + "*) x;");
                        bSwitch("p->decoration");
                        {
                            bCase("COM");
                            ret("p->inf <= p->sup && p->inf != -INFINITY && p->sup != INFINITY");
                            endCase();
                            bCase("DAC");
                            ret("p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY");
                            endCase();
                            bCase("DEF");
                            ret("p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY");
                            endCase();
                            bCase("TRV");
                            ret("p->inf <= p->sup && p->inf != INFINITY && p->sup != -INFINITY || "
                                    + (infsupNan ? "p->inf != p->inf && p->sup != p->sup"
                                            : "p->inf == INFINITY && p->sup == -INFINITY"));
                            endCase();
                            bCase("ILL");
                            ret("p->inf != p->inf && p->sup != p->sup");
                            endCase();
                            bDefault();
                            ret("0");
                            endCase();
                        }
                        endSwitch();
                    }
                    e();
                    s("}");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static int " + f("is_nai", "int tag", "const void *x"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    ret("((" + fmt.cFormat(true) + "*) x)->decoration == ILL");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static void " + f("p1788_get_fr", "mpfr_ptr mx", "int tag", "const void *x"));
        {
            s(f("mpfr_init2", "mx", f("p1788_get_prec", "tag")) + ";");
            s("int t;");
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("t = " + f(fmt.mpfrSetName(), "mx", "*((" + fmt.cFormat() + "*) x)", "MPFR_RNDN") + ";");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
            s(f("assert", "t == 0") + ";");
        }
        endFun();
        s();
        bFun("static void " + f("p1788_b_get_fi", "mpfi_ptr mx", "int tag", "const void *x"));
        {
            s(f("mpfi_init2", "mx", f("p1788_get_prec", "tag")) + ";");
            s("int tl, tr;");
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("{");
                    b();
                    {
                        s(fmt.cFormat(false) + "* p = (" + fmt.cFormat(false) + "*) x;");
                        s("tl = " + f(fmt.mpfrSetName(), "&mx->left", "p->inf", "MPFR_RNDD") + ";");
                        s("tr = " + f(fmt.mpfrSetName(), "&mx->right", "p->sup", "MPFR_RNDU") + ";");
                    }
                    e();
                    s("}");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
            s(f("assert", "tl == 0 && tr == 0") + ";");
            shortIf(f("mpfr_zero_p", "&mx->left") + " && " + f("mpfr_signbit", "&mx->left"),
                    f("mpfr_set_zero", "&mx->left", "1") + ";");
            shortIf(f("mpfr_zero_p", "&mx->right") + " && " + f("!mpfr_signbit", "&mx->right"),
                    f("mpfr_set_zero", "&mx->right", "-1") + ";");
            shortIf(f("mpfi_is_empty", "mx"), f("mpfi_p1788_empty", "mx") + ";");
        }
        endFun();
        s();
        bFun("static int " + f("p1788_d_get_fi", "mpfi_ptr mx", "int tag", "const void *x", "int dec"));
        {
            s(f("mpfi_init2", "mx", f("p1788_get_prec", "tag")) + ";");
            s("int tl, tr, mydec;");
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("{");
                    b();
                    {
                        s(fmt.cFormat(true) + "* p = (" + fmt.cFormat(true) + "*) x;");
                        s("tl = " + f(fmt.mpfrSetName(), "&mx->left", "p->inf", "MPFR_RNDD") + ";");
                        s("tr = " + f(fmt.mpfrSetName(), "&mx->right", "p->sup", "MPFR_RNDU") + ";");
                        s("mydec = p->decoration;");
                    }
                    e();
                    s("}");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
            s(f("assert", "tl == 0 && tr == 0") + ";");
            shortIf(f("mpfr_zero_p", "&mx->left") + " && " + f("mpfr_signbit", "&mx->left"),
                    f("mpfr_set_zero", "&mx->left", "1") + ";");
            shortIf(f("mpfr_zero_p", "&mx->right") + " && " + f("!mpfr_signbit", "&mx->right"),
                    f("mpfr_set_zero", "&mx->right", "-1") + ";");
            shortIf(f("mpfi_is_empty", "mx"), f("mpfi_p1788_empty", "mx") + ";");
            ret("mydec < dec ? mydec : dec");
        }
        endFun();
        s();
        bFun("static void " + f("p1788_set_nan", "int tag", "void *x"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("*((" + fmt.cFormat() + "*) x) = NAN;");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static void " + f("p1788_set_fr", "int tag", "void *x", "mpfr_srcptr mx"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("*((" + fmt.cFormat() + "*) x) = " + f(fmt.mpfrGetName(), "mx", "MPFR_RNDN") + ";");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static void " + f("p1788_b_set_fi", "int tag", "void *x", "mpfi_srcptr mx"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("{");
                    b();
                    {
                        s(fmt.cFormat(false) + "* p = (" + fmt.cFormat(false) + "*) x;");
                        bIf(f("mpfi_is_empty", "mx"));
                        {
                            s("p->inf = " + (infsupNan ? "NAN" : "+INFINITY") + ";");
                            s("p->sup = " + (infsupNan ? "NAN" : "-INFINITY") + ";");
                        }
                        elseIf();
                        {
                            s("p->inf = " + f("mpfr_zero_p", "&mx->left") + " ? -0.0 : " + f(fmt.mpfrGetName(), "&mx->left", "MPFR_RNDD") + ";");
                            s("p->sup = " + f("mpfr_zero_p", "&mx->right") + " ? +0.0 : " + f(fmt.mpfrGetName(), "&mx->right", "MPFR_RNDU") + ";");
                        }
                        endIf();
                    }
                    e();
                    s("}");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();
        s();
        bFun("static void " + f("p1788_d_set_fi", "int tag", "void *x", "mpfi_srcptr mx", "int dec"));
        {
            bSwitch("tag");
            {
                for (Format fmt : formats) {
                    bCase(fmt.tag());
                    s("{");
                    b();
                    {
                        s(fmt.cFormat(true) + "* p = (" + fmt.cFormat(true) + "*) x;");
                        bIf("dec <= ILL");
                        {
                            s("p->inf = p->sup = NAN;");
                            s("dec = ILL;");
                        }
                        elseIf(f("mpfi_is_empty", "mx"));
                        {
                            s("p->inf = " + (infsupNan ? "NAN" : "+INFINITY") + ";");
                            s("p->sup = " + (infsupNan ? "NAN" : "-INFINITY") + ";");
                        }
                        elseIf();
                        {
                            s("p->inf = " + f("mpfr_zero_p", "&mx->left") + " ? -0.0 : " + f(fmt.mpfrGetName(), "&mx->left", "MPFR_RNDD") + ";");
                            s("p->sup = " + f("mpfr_zero_p", "&mx->right") + " ? +0.0 : " + f(fmt.mpfrGetName(), "&mx->right", "MPFR_RNDU") + ";");
                        }
                        endIf();
                    }
                    s("p->decoration = dec;");
                    e();
                    s("}");
                    endCase();
                }
                bDefault();
                s(f("assert", "0") + ";");
                endCase();
            }
            endSwitch();
        }
        endFun();

        for (Operation op : allOperations) {
            op.genC(this);
        }
    }

    private void genDumper(boolean withoutNumsToInterval) throws IOException {
        skipDumper = new HashSet<>(Arrays.asList(opIsValid, opEmpty, opEntire, opNaI, opIsEmpty, opIsEntire, opIsNaI));
        if (withoutNumsToInterval) {
            skipDumper.add(opNumsToInterval);
            skipDumper.add(opNumsDecToInterval);
            skipDumper.add(opEqual);
        }

        s("#include \"p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp\"");
        s();
        s("namespace p1788 {");
        s("namespace flavor {");
        s("namespace infsup {");
        s("namespace setbased {");
        s();
        s("static const char* dec_strings[] = { \"ill\", \"trv\", \"def\", \"dac\", \"com\"};");
        s();
        bFun("static void " + f("print_op", "const char* op"));
        {
            s("static const char* old_op = NULL;");
            bIf("old_op == NULL || " + f("strcmp", "op", "old_op"));
            {
                s("old_op = op;");
                s(f("printf", "\"* %s\\n\"", "op") + ";");
            }
            endIf();
        }
        endFun();
        s("template<typename T>");
        s(f("static void print_num", "T x") + ";");
        s();
        s("template<typename T>");
        s(f("static void print_bare", "std::pair<T,T> const& x") + ";");
        s();
        s("template<typename T>");
        s(f("static void print_dec", "std::pair<std::pair<T,T>,p1788::decoration::decoration> const& x") + ";");
        for (Format fmt : formats) {
            String cf = fmt.cFormat();
            s();
            s("template<>");
            bFun(f("void print_num<" + cf + ">",
                    cf + " x"));
            {
                s(f("printf", "\"" + fmt.fmt() + "\"", "x") + ";");
            }
            endFun();
            s();
            s("template<>");
            bFun(f("void print_bare<" + cf + ">",
                    "std::pair<" + cf + "," + cf + "> const& x"));
            {
                bIf("x.first <= x.second && x.first != std::numeric_limits<" + cf + ">::infinity() && x.second != -std::numeric_limits<" + cf + ">::infinity()");
                {
                    s(f("printf", "\"[" + fmt.fmt() + "," + fmt.fmt() + "]\"",
                            "x.first",
                            "x.second") + ";");
                }
                elseIf();
                {
                    s(f("printf", "\"[]\"") + ";");
                }
                endIf();
            }
            endFun();
            s();
            s("template<>");
            bFun(f("void print_dec<" + cf + ">",
                    "std::pair<std::pair<" + cf + "," + cf + ">,p1788::decoration::decoration> const& x"));
            {
//                s(f("print_bare", "x.first") + ";");
                bIf("x.first.first <= x.first.second");
                {
                    s(f("printf", "\"[" + fmt.fmt() + "," + fmt.fmt() + "]_%s\"",
                            "x.first.first",
                            "x.first.second",
                            "dec_strings[static_cast<int>(x.second) >> 2]") + ";");
                }
                elseIf();
                {
                    s(f("printf", "\"[]_%s\"",
                            "dec_strings[static_cast<int>(x.second) >> 2]") + ";");

                }
                endIf();
            }
            endFun();
        }
        s();
        bFun(f("void dummy_init"));
        {
            for (Format fmt : formats) {
                String cf = fmt.cFormat();
                s(f("print_num<" + cf + ">", "0") + ";");
                s("std::pair<" + cf + "," + cf + "> b_" + fmt.cCharLower() + ";");
                s(f("print_bare<" + cf + ">", "b_" + fmt.cCharLower()) + ";");
                s("std::pair<std::pair<" + cf + "," + cf + ">,p1788::decoration::decoration> d_" + fmt.cCharLower() + ";");
                s(f("print_dec<" + cf + ">", "d_" + fmt.cCharLower()) + ";");
            }
        }
        endFun();
        s();
        s("template<typename T>");
        s("class " + cls());
        s("{");
        s();
        s("public:");
        b();
        {
            s("template<typename T_>");
            s("using representation_type = typename p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::template representation_type<T_>;");
            s();
            s("template<typename T_>");
            s("using representation_dec_type = typename p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::template representation_dec_type<T_>;");
            s();
            s("typedef representation_type<T> representation;");
            s("typedef representation_dec_type<T> representation_dec;");
//            opIsValid.genDumper(this);
            for (Operation op : allOperations) {
                op.genDumper(this);
            }
            s();
            bFun(f("static representation copy", "representation const& other"));
            {
                s("representation r = "
                        + f("p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::copy", "other")
                        + ";");
//                s(f("print_op", "\"copy\"") + ";");
//                s(f("printf", "\"copy(\"") + ";");
//                s(f("print_bare", "other") + ";");
//                s(f("printf", "\") = \"") + ";");
//                s(f("print_bare", "r") + ";");
//                s(f("printf", "\";\\n\"") + ";");
                ret("r");
            }
            endFun();
            s();
            bFun(f("static representation_dec copy", "representation_dec const& other"));
            {
                s("representation_dec r = "
                        + f("p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::copy", "other")
                        + ";");
//                s(f("print_op", "\"copy_dec\"") + ";");
//                s(f("printf", "\"copy(\"") + ";");
//                s(f("print_dec", "other") + ";");
//                s(f("printf", "\") = \"") + ";");
//                s(f("print_dec", "r") + ";");
//                s(f("printf", "\";\\n\"") + ";");
                ret("r");
            }
            endFun();
            s();
            s("template< typename CharT, typename Traits >");
            bFun(f("static std::basic_istream<CharT, Traits>& operator_text_to_interval",
                    "std::basic_istream<CharT, Traits>& is",
                    "representation& x"));
            {
                s(f("print_op", "\"operator_text_to_interval\"") + ";");
                s(f("p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::operator_text_to_interval",
                        "is", "x") + ";");
//                s(f("printf", "\"operator_text_to_interval(is,\"") + ";");
//                s(f("print_bare", "x") + ";");
//                s(f("printf", "\") = is;\\n\"") + ";");
                ret("is");
            }
            endFun();
            s();
            s("template< typename CharT, typename Traits >");
            bFun(f("static std::basic_istream<CharT, Traits>& operator_text_to_interval",
                    "std::basic_istream<CharT, Traits>& is",
                    "representation_dec& x"));
            {
                s(f("print_op", "\"operator_text_to_dec_interval\"") + ";");
                s(f("p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::operator_text_to_interval",
                        "is", "x") + ";");
//                s(f("printf", "\"operator_text_to_interval(is,\"") + ";");
//                s(f("print_dec", "x") + ";");
//                s(f("printf", "\") = is;\\n\"") + ";");
                ret("is");
            }
            endFun();
        }
        e();
        s("};");
        s();
        s("}}}}");
    }

    private void genMoore() throws IOException {
        s("#include \"moore_flavor_defs.hpp\"");
        s();
        s("namespace Moore::Flavor {");
//        s("namespace Flavor {");
        s();
        s("template<typename T>");
        s("class " + cls());
        s("{");
        s();
        s("public:");
        b();
        {
//            s("template<typename T_>");
//            s("using representation_type = Moore::Interval<T_>;");
//            s();
//            s("template<typename T_>");
//            s("using representation_dec_type = Moore::TDecInterval<Moore::Interval<T_>>;");
//            s();
            s("typedef representation_type<T> representation;");
            s("typedef representation_dec_type<T> representation_dec;");
            for (Operation op : allOperations) {
                if (op == opExactToInterval || op == opExactToDecoratedInterval) {
                    continue;
                }
                op.genMoore(this);
            }
            s();
            bFun(f("static representation copy", "representation const& other"));
            {
                ret(f("representation", "other"));
            }
            endFun();
            s();
            bFun(f("static representation_dec copy", "representation_dec const& other"));
            {
                ret(f("representation_dec", "other"));
            }
            endFun();
            s();
            genOperatorTextToInterval();
            /*
            s("template< typename CharT, typename Traits >");
            bFun(f("static std::basic_istream<CharT, Traits>& operator_text_to_interval",
                    "std::basic_istream<CharT, Traits>& is",
                    "representation& x"));
            {
                ret("is >> x");
            }
            endFun();
            s();
            s("template< typename CharT, typename Traits >");
            bFun(f("static std::basic_istream<CharT, Traits>& operator_text_to_interval",
                    "std::basic_istream<CharT, Traits>& is",
                    "representation_dec& x"));
            {
                s(f("p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::operator_text_to_interval",
                        "is", "x") + ";");
                ret("is");
            }
            endFun();
             */
        }
        e();
        s("};");
        s();
        s("}");
//        s("}}");
    }

    private void genCPPsignalException() {
        bFun("static int " + f("signal_exception", "int exc"));
        {
            bSwitch("exc");
            {
                bCase("EXC_UNDEFINED_OPERATION");
                s(f("p1788::exception::signal_undefined_operation") + ";");
                endCase();
                bCase("EXC_POSSIBLY_UNDEFINED_OPERATION");
                s(f("p1788::exception::signal_possibly_undefined_operation") + ";");
                endCase();
                bCase("EXC_INTERVAL_PART_OF_NAI");
                s(f("p1788::exception::signal_interval_part_of_nai") + ";");
                endCase();
                bCase("EXC_INVALID_OPERAND");
                s(f("p1788::exception::signal_invalid_operand") + ";");
                endCase();
                bDefault();
                ret("exc");
                endCase();
            }
            endSwitch();
            ret("0");
        }
        endFun();
    }

    private void genAllMPFI() throws IOException {
        s("#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_" + cls().toUpperCase() + "_HPP");
        s("#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_" + cls().toUpperCase() + "_HPP");
        s();
        s("#include <assert.h>");
        s("#include <mpfi.h>");
        s();
        s("extern \"C\" {");
        s("#include \"p1788.h\"");
        s("#include \"mpfi_p1788.h\"");
        s("}");
        s();
        s("#include \"p1788/exception/exception.hpp\"");
        s("#include \"p1788/decoration/decoration.hpp\"");
        s("#include \"p1788/util/mpfr_var.hpp\"");
        s("#include \"p1788/util/mixed_type_traits.hpp\"");
        s("#include \"p1788/infsup/base_interval.hpp\"");
        s();
        s("namespace p1788 {");
        s("namespace flavor {");
        s("namespace infsup {");
        s("namespace setbased {");
        s();
        genCPPsignalException();
        s();
        s("template<typename T>");
        s("class " + cls() + ";");
        s();
        s("template<typename T>");
        s("struct REP");
        s("{");
        b();
        {
            s("T first;");
            s("T second;");
            s();
            bFun(f("REP", "T inf", "T sup"));
            {
                s("first = inf;");
                s("second = sup;");
            }
            endFun();
            s();
            s("// empty");
            bFun(f("REP"));
            {
                s("first = " + f(infsupNan ? "std::numeric_limits<T>::quiet_NaN" : "std::numeric_limits<T>::infinity") + ";");
                s("second = " + f(infsupNan ? "std::numeric_limits<T>::quiet_NaN" : "-std::numeric_limits<T>::infinity") + ";");
            }
            endFun();
            s();
            bFun(f("REP", "mpfi_srcptr m"));
            {
                bIf(f("mpfi_is_empty", "m"));
                {
                    s("first = " + f(infsupNan ? "std::numeric_limits<T>::quiet_NaN" : "std::numeric_limits<T>::infinity") + ";");
                    s("second = " + f(infsupNan ? "std::numeric_limits<T>::quiet_NaN" : "-std::numeric_limits<T>::infinity") + ";");
                }
                elseIf();
                {
                    s(cls() + "<T>::mpfr_var::" + f("setup") + ";");
                    s("typename " + cls() + "<T>::mpfr_var left, right;");
                    s(f("mpfr_subnormalize", f("left"), f("mpfr_set", f("left"), "&m->left", "MPFR_RNDD"), "MPFR_RNDD") + ";");
                    s(f("mpfr_subnormalize", f("right"), f("mpfr_set", f("right"), "&m->right", "MPFR_RNDU"), "MPFR_RNDU") + ";");
                    s("first = " + f("mpfr_zero_p", f("left")) + " ? -0.0 : " + f("left.template get<T>", "MPFR_RNDD") + ";");
                    s("second = " + f("mpfr_zero_p", f("right")) + " ? +0.0 : " + f("right.template get<T>", "MPFR_RNDU") + ";");
                }
                endIf();
            }
            endFun();
            s();
            bFun("bool " + f("is_empty") + " const");
            {
                ret("!(first <= second)");
            }
            endFun();
            s();
            bFun("void " + f("get_fi", "mpfi_ptr m") + " const");
            {
                s(f("mpfi_init2", "m", cls() + "<T>::mpfr_var::PREC") + ";");
                bIf(f("is_empty"));
                {
                    s(f("mpfi_p1788_empty", "m") + ";");
                }
                elseIf();
                {
                    s(cls() + "<T>::mpfr_var::" + f("setup") + ";");
                    s("typename " + cls() + "<T>::mpfr_var "
                            + f("left", "first", "MPFR_RNDD") + ", " + f("right", "second", "MPFR_RNDU") + ";");
                    s(f("mpfi_p1788_numsToInterval", "m", f("left"), f("right")) + ";");
                }
                endIf();
            }
            endFun();
        }
        e();
        s("};");
        s();
        s("template<typename T>");
        bFun("static bool " + f("operator==", "REP<T> const& x", "REP<T> const& y"));
        {
            ret("x.first == y.first && x.second == y.second");
        }
        endFun();
        s();
        s("template<typename T>");
        s("struct REP_DEC");
        s("{");
        b();
        {
            s("REP<T> first;");
            s("decoration::decoration second;");
            s();
            bFun(f("REP_DEC", "REP<T> intvl", "decoration::decoration dec"));
            {
                s("first = intvl;");
                s("second = dec;");
            }
            endFun();
            s();
            s("// nai");
            bFun(f("REP_DEC"));
            {
                s("first = " + f("REP<T>", f("std::numeric_limits<T>::quiet_NaN"), f("std::numeric_limits<T>::quiet_NaN")) + ";");
                s("second = decoration::decoration::ill;");
            }
            endFun();
            s();
            bFun(f("REP_DEC", "mpfi_srcptr m", "decoration::decoration dec"));
            {
                bIf("dec == decoration::decoration::ill");
                {
                    s("first.first = first.second = " + f("std::numeric_limits<T>::quiet_NaN") + ";");
                }
                elseIf();
                {
                    s("first = " + f("REP<T>", "m") + ";");
                }
                endIf();
                s("second = dec;");
            }
            endFun();
            s();
            bFun("bool " + f("is_nai") + " const");
            {
                ret("second == decoration::decoration::ill");
            }
            endFun();
            s();
            bFun("decoration::decoration " + f("get_fi", "mpfi_ptr m", "decoration::decoration dec") + " const");
            {
                s(f("first.get_fi", "m") + ";");
                ret(f("std::min", "dec", "second"));
            }
            endFun();
        }
        e();
        s("};");
        s();
        s("template<typename T>");
        bFun("static bool " + f("operator==", "REP_DEC<T> const& x", "REP_DEC<T> const& y"));
        {
            ret("x.first == y.first && x.second == y.second");
        }
        endFun();
        s();
        s("template<typename T>");
        s("class " + cls());
        s("{");
        s();
        s("public:");
        b();
        {
            s("typedef p1788::util::mpfr_var<");
            s("std::numeric_limits<T>::digits,");
            s("    std::numeric_limits<T>::has_denorm != std::denorm_present ? std::numeric_limits<T>::min_exponent");
            s("    : std::numeric_limits<T>::min_exponent - std::numeric_limits<T>::digits + 1,");
            s("    std::numeric_limits<T>::max_exponent,");
            s("    std::numeric_limits<T>::has_denorm == std::denorm_present");
            s("    >   mpfr_var;");
            s();
            s("typedef REP<T> representation;");
            s("typedef REP_DEC<T> representation_dec;");
//            opIsValid.genMPFI();
            for (Operation op : allOperations) {
                op.genMPFI(this);
            }
            s();
            genOperatorTextToInterval();
            s();
            bFun("static representation " + f("copy", "representation const& other"));
            {
                ret(f("convert_type<T>", "other"));
            }
            endFun();
            bFun("static representation_dec" + f(" copy", "representation_dec const& other"));
            {
                ret(f("convert_type<T>", "other"));
            }
            endFun();
        }
        e();
        s("};");
        s();
        s("}}}}");
        s();
        s("#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_" + cls().toUpperCase() + "_HPP");
    }

    private void genAllCPP() throws IOException {
        s("#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_" + cls().toUpperCase() + "_HPP");
        s("#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_" + cls().toUpperCase() + "_HPP");
        s();
        s("extern \"C\" {");
        s("#include \"p1788.h\"");
        s("}");
        s();
        s("#include \"p1788/exception/exception.hpp\"");
        s("#include \"p1788/decoration/decoration.hpp\"");
        s("#include \"p1788/util/mixed_type_traits.hpp\"");
        s("#include \"p1788/infsup/base_interval.hpp\"");
        s();
        s("namespace p1788 {");
        s("namespace flavor {");
        s("namespace infsup {");
        s("namespace setbased {");
        s();
        genCPPsignalException();
        s();
        s("template<typename T>");
        s("struct REP");
        s("{");
        b();
        {
            s("T first;");
            s("T second;");
            s();
            bFun(f("REP"));
            {
                s(f("p1788_bar_empty", "static_cast<int>(util::type_precision_order<T>::value)", "this") + ";");
            }
            endFun();
            s();
            bFun(f("REP", "T inf", "T sup"));
            {
                s("first = inf;");
                s("second = sup;");
            }
            endFun();
        }
        e();
        s("};");
        s();
        s("template<typename T>");
        bFun("static bool " + f("operator==", "REP<T> const& x", "REP<T> const& y"));
        {
            ret("x.first == y.first && x.second == y.second");
        }
        endFun();
        s();
        s("template<typename T>");
        s("struct REP_DEC");
        s("{");
        b();
        {
            s("REP<T> first;");
            s("decoration::decoration second;");
            s();
            bFun(f("REP_DEC"));
            {
                s(f("p1788_dec_nai", "static_cast<int>(util::type_precision_order<T>::value)", "this") + ";");
            }
            endFun();
            s();
            bFun(f("REP_DEC", "REP<T> intvl", "decoration::decoration dec"));
            {
                s("first = intvl;");
                s("second = dec;");
            }
            endFun();
        }
        e();
        s("};");
        s();
        s("template<typename T>");
        bFun("static bool " + f("operator==", "REP_DEC<T> const& x", "REP_DEC<T> const& y"));
        {
            ret("x.first == y.first && x.second == y.second");
        }
        endFun();
        s();
        s("template<typename T>");
        s("class " + cls());
        s("{");
        s();
        s("public:");
        b();
        {
            s("typedef REP<T> representation;");
            s("typedef REP_DEC<T> representation_dec;");
//            opIsValid.genCPP_k();
            for (Operation op : allOperations) {
                op.genCPP(this);
            }
            s();
            genOperatorTextToInterval();
            s();
            bFun("static representation " + f("copy", "representation const& other"));
            {
                ret(f("convert_type<T>", "other"));
            }
            endFun();
            bFun("static representation_dec" + f(" copy", "representation_dec const& other"));
            {
                ret(f("convert_type<T>", "other"));
            }
            endFun();
        }
        e();
        s("};");
        s();
        s("}}}}");
        s();
        s("#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_" + cls().toUpperCase() + "_HPP");
    }

    public static void main(String[] aggs) throws Exception {
        File dir = new File("../wrk/");
        try {
            for (String fileToCopy : filesToCopy) {
                copyFile(dir, fileToCopy);
            }
            List<String> headerLines = readHeaderLines();

            GenP1788 gen = new GenP1788(null);
            gen.create(new File(dir, "p1788.h"), Collections.<String>emptyList());
            gen.genAllH();
            gen.close();

            gen = new GenP1788(classPrefix + suf_m);
            gen.create(new File(dir, gen.cls() + ".hpp"), Collections.<String>emptyList());
            gen.genAllMPFI();
            gen.close();

            gen = new GenP1788(null);
            gen.create(new File(dir, "p1788.c"), Collections.<String>emptyList());
            gen.genAllC();
            gen.close();

            gen = new GenP1788(classPrefix + suf_t);
            gen.create(new File(dir, gen.cls() + ".hpp"), Collections.<String>emptyList());
            gen.genDumper(false);
            gen.close();

            gen = new GenP1788("moore_flavor");
//            gen = new GenP1788(classPrefix + suf_mo);
            gen.create(new File(dir, gen.cls() + ".hpp"), Collections.<String>emptyList());
            gen.genMoore();
            gen.close();

            gen = new GenP1788(classPrefix + suf_j);
            gen.create(new File(dir, gen.cls() + ".hpp"), Collections.<String>emptyList());
            gen.genAllCPP();
            gen.close();

            gen = new GenP1788(null);
            gen.create(new File(dir, "p1788_oper.h"), Collections.<String>emptyList());
            gen.genOperH();
            gen.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
