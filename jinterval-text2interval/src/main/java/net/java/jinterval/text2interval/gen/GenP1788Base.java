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
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.io.OutputStream;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Set;
import net.java.jinterval.interval.Decoration;

/**
 *
 */
public class GenP1788Base extends GenSupport {

    private static final String LICENSE_HEADER = "LICENSE_HEADER";
    private static final String OPERATOR_TEXT_TO_INTERVAL = "operator_text_to_interval.cpp";
    String prefix = "p1788_";
    String mpfi_prefix = "mpfi_p1788_";
    boolean infsupNan = true;
    Set<Operation> skipDumper = Collections.emptySet();

    private final String className;

    public enum Kind {

        INTERVAL, POINT, INT, DEC, OVERLAP, TEXT, STREAM, CS, BOOL, LEN, POINT_ARRAY, RND
    };

    static abstract class Format {

        abstract char cCharLower();

        String tag() {
            return "TAG_" + cCharLower();
        }

        char cCharUpper() {
            return Character.toUpperCase(cCharLower());
        }

        abstract String cFormat(boolean isDecorated);

        abstract String cFormat();

        abstract String rep(boolean isDecorated);

        abstract String fmt();

        abstract String cMath();

        abstract String mpfrGetName();

        abstract String mpfrSetName();
    }

    private static final Format B32 = new Format() {
        @Override
        char cCharLower() {
            return 'f';
        }

        @Override
        String cFormat(boolean isDecorated) {
            return isDecorated ? "DECORATED_INFSUP_B32" : "BARE_INFSUP_B32";
        }

        @Override
        String cFormat() {
            return "float";
        }

        @Override
        String rep(boolean isDecorated) {
            return isDecorated ? "REP_DEC_B32" : "REP_B32";
        }

        @Override
        String fmt() {
            return "%+-16.6a";
        }

        @Override
        String cMath() {
            return "FLT";
        }

        @Override
        String mpfrGetName() {
            return "mpfr_get_flt";
        }

        @Override
        String mpfrSetName() {
            return "mpfr_set_flt";
        }
    };

    private static final Format B64 = new Format() {

        @Override
        char cCharLower() {
            return 'd';
        }

        @Override
        String cFormat(boolean isDecorated) {
            return isDecorated ? "DECORATED_INFSUP_B64" : "BARE_INFSUP_B64";
        }

        @Override
        String cFormat() {
            return "double";
        }

        @Override
        String rep(boolean isDecorated) {
            return isDecorated ? "REP_DEC_B64" : "REP_B64";
        }

        @Override
        String fmt() {
            return "%+-24.13a";
        }

        @Override
        String cMath() {
            return "DBL";
        }

        @Override
        String mpfrGetName() {
            return "mpfr_get_d";
        }

        @Override
        String mpfrSetName() {
            return "mpfr_set_d";
        }
    };
    private static final Format B80 = new Format() {

        @Override
        char cCharLower() {
            return 'l';
        }

        @Override
        String cFormat(boolean isDecorated) {
            return isDecorated ? "DECORATED_INFSUP_B80" : "BARE_INFSUP_B80";
        }

        @Override
        String cFormat() {
            return "long double";
        }

        @Override
        String rep(boolean isDecorated) {
            return isDecorated ? "REP_DEC_B80" : "REP_B80";
        }

        @Override
        String fmt() {
            return "%+-28.16La";
        }

        @Override
        String cMath() {
            return "LDBL";
        }

        @Override
        String mpfrGetName() {
            return "mpfr_get_ld";
        }

        @Override
        String mpfrSetName() {
            return "mpfr_set_ld";
        }
    };
    static final Format[] formats = {B32, B64, B80};

    GenP1788Base(String className) {
        this.className = className;
    }

    String cls() {
        return className;
    }

    static List<String> readHeaderLines() throws IOException {
        List<String> result = new ArrayList<String>();
        LineNumberReader reader = new LineNumberReader(new InputStreamReader(Builder.class.getResourceAsStream(LICENSE_HEADER), Charset.forName("UTF8")));
        String line;
        while ((line = reader.readLine()) != null) {
            result.add(line);
        }
        reader.close();
        return result;
    }

    private void genOperatorTextToInterval(String typ, String goodCall) throws IOException {
        LineNumberReader reader = new LineNumberReader(new InputStreamReader(Builder.class.getResourceAsStream(OPERATOR_TEXT_TO_INTERVAL), Charset.forName("UTF8")));
        String line;
        while ((line = reader.readLine()) != null) {
            s(line.replace("$T$", typ).replace("$G$", goodCall));
        }
        reader.close();
    }

    void genOperatorTextToInterval() throws IOException {
        genOperatorTextToInterval("representation", "text_to_interval");
        genOperatorTextToInterval("representation_dec", "text_to_decorated_interval");
    }

    static void copyFile(File dir, String filename) throws IOException {
        InputStream inp = Builder.class.getResourceAsStream(filename);
        File file = new File(dir, filename);
        OutputStream out = new FileOutputStream(file);
        byte[] buf = new byte[4096];
        int len;
        while ((len = inp.read(buf)) > 0) {
            out.write(buf, 0, len);
        }
        out.close();
        inp.close();
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

    public abstract static class Operation {

        final String opName;
        String incName;
        final String cppName;
        final String cppNameDec;
        final String[] resNames;
        public Kind[] results;
        final String[] argNames;
        public final Kind[] args;
        final int[] argTypenames;
        final int argTypenamesCnt;
        final Decoration constantDecoration;
        final boolean exceptionsPossible;
        final OperationTypes[] opTypes;

        Operation(String opName, String cppName, String cppNameDec,
                Decoration constantDecoration, boolean exceptionsPossible,
                Kind[] results, String[] argNames, Kind... args) {
            this.opName = opName;
            incName = opName;
            this.cppName = cppName;
            this.cppNameDec = cppNameDec;
            this.constantDecoration = constantDecoration;
            this.exceptionsPossible = exceptionsPossible;
            resNames = new String[results.length];
            for (int i = 0; i < resNames.length; i++) {
                resNames[i] = resNames.length > 1 ? "r" + (i + 1) : "r";
            }
            this.results = results;
            assert argNames.length == args.length;
            this.argNames = argNames.clone();
            this.args = args.clone();
            argTypenames = new int[args.length];
            int argCnt = results[0] == Kind.INTERVAL || results[0] == Kind.POINT ? 1 : 0;
            for (int i = 0; i < args.length; i++) {
                if (args[i] == Kind.INTERVAL) {
                    argTypenames[i] = argCnt++;
                }
            }
            for (int i = 0; i < args.length; i++) {
                if (args[i] == Kind.POINT) {
                    argTypenames[i] = argCnt++;
                }
            }
            argTypenamesCnt = argCnt;
            opTypes = makeOperationTypes();
        }

        Operation(String opName, String cppName, Decoration constantDecoration, Kind result, String[] argNames, Kind... args) {
            this(opName, cppName, cppName, constantDecoration, false, new Kind[]{result}, argNames, args);
        }

        Operation(String opName, String cppName, Kind result, String[] argNames, Kind... args) {
            this(opName, cppName, cppName, result == Kind.INTERVAL ? Decoration.TRV : null, false, new Kind[]{result}, argNames, args);
        }

        String getName(GenP1788Base g) {
            return g.prefix + opName;
        }

        String getName(GenP1788Base g, boolean isDecorated) {
            return g.prefix + (isDecorated ? "dec_" : "bar_") + opName;
        }

        public final static int B_B = 1 << 0;
        public final static int B_D = 1 << 1;
        public final static int D_B = 1 << 2;
        public final static int D_D = 1 << 3;

        public int getDecPairs() {
            return B_B | D_D;
        }

        private OperationTypes[] makeOperationTypes() {
            List<OperationTypes> operationTypes = new ArrayList<>();
            OperationTypes ot = new OperationTypes(this);
            int pairs = getDecPairs();
            if (pairs == 0) {
                assert results.length == 1 && results[0] == Kind.POINT;
                for (Format fmt : formats) {
                    ot.results[0] = fmt;
                    for (int i = 0; i < args.length; i++) {
                        if (args[i] == Kind.POINT_ARRAY) {
                            ot.args[i] = fmt;
                        }
                    }
                    operationTypes.add(new OperationTypes(ot));
                }
            } else {
                for (int pair = 0; pair < 4; pair++) {
                    if ((pairs & (1 << pair)) == 0) {
                        continue;
                    }
                    ot.res_dec = (pair & 2) != 0;
                    ot.arg_dec = (pair & 1) != 0;
                    switch (results[0]) {
                        case INTERVAL:
                        case POINT:
                            for (Format fmt : formats) {
                                ot.results[0] = fmt;
                                if (results.length > 1) {
                                    assert results.length == 2 && results[0] == results[1];
                                    ot.results[1] = fmt;
                                }
                                makeOperationTypes(operationTypes, ot, 0);
                            }
                            break;
                        default:
                            makeOperationTypes(operationTypes, ot, 0);
                            break;
                    }
                }
            }
            return operationTypes.toArray(new OperationTypes[operationTypes.size()]);
        }

        private void makeOperationTypes(List<OperationTypes> operationTypes, OperationTypes ot, int iArg) {
            if (iArg == args.length) {
                operationTypes.add(new OperationTypes(ot));
            } else {
                switch (args[iArg]) {
                    case INTERVAL:
                    case POINT:
                        for (Format fmt : formats) {
                            ot.args[iArg] = fmt;
                            makeOperationTypes(operationTypes, ot, iArg + 1);
                        }
                        break;
                    default:
                        makeOperationTypes(operationTypes, ot, iArg + 1);
                        break;
                }
            }
        }

        void genOperH(GenP1788Base g) {
            for (OperationTypes ot : opTypes) {
                ot.genOperH(g);
            }
        }

        void genH(GenP1788Base g) {
            int pairs = getDecPairs();
            if (pairs == 0) {
            }
            for (int pair = 0; pair < 4; pair++) {
                if ((pairs & (1 << pair)) == 0) {
                    continue;
                }
                boolean res_dec = (pair & 2) != 0;
                boolean arg_dec = (pair & 1) != 0;
                genH(g, res_dec, arg_dec);
            }
        }

        void genC(GenP1788Base g) {
            int pairs = getDecPairs();
            if (pairs == 0) {
            }
            for (int pair = 0; pair < 4; pair++) {
                if ((pairs & (1 << pair)) == 0) {
                    continue;
                }
                boolean res_dec = (pair & 2) != 0;
                boolean arg_dec = (pair & 1) != 0;
                genC(g, res_dec, arg_dec);
            }
        }

        void genDumper(GenP1788Base g) {
            int pairs = getDecPairs();
            for (int pair = 0; pair < 4; pair++) {
                if ((pairs & (1 << pair)) == 0) {
                    continue;
                }
                boolean res_dec = (pair & 2) != 0;
                boolean arg_dec = (pair & 1) != 0;
                genDumper(g, res_dec, arg_dec);
            }
        }

        void genMoore(GenP1788Base g) {
            int pairs = getDecPairs();
            for (int pair = 0; pair < 4; pair++) {
                if ((pairs & (1 << pair)) == 0) {
                    continue;
                }
                boolean res_dec = (pair & 2) != 0;
                boolean arg_dec = (pair & 1) != 0;
                genMoore(g, res_dec, arg_dec);
            }
        }

        void genMPFI(GenP1788Base g) {
            int pairs = getDecPairs();
            for (int pair = 0; pair < 4; pair++) {
                if ((pairs & (1 << pair)) == 0) {
                    continue;
                }
                boolean res_dec = (pair & 2) != 0;
                boolean arg_dec = (pair & 1) != 0;
                genMPFI(g, res_dec, arg_dec);
            }
        }

        void genCPP(GenP1788Base g) {
            int pairs = getDecPairs();
            for (int pair = 0; pair < 4; pair++) {
                if ((pairs & (1 << pair)) == 0) {
                    continue;
                }
                boolean res_dec = (pair & 2) != 0;
                boolean arg_dec = (pair & 1) != 0;
                genCPP(g, res_dec, arg_dec);
            }
        }

        void genDumper(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            bCPPFun(g, false, isDecoratedRes, isDecoratedArg);
            {
                genBodyDumper(g, isDecoratedRes, isDecoratedArg);
            }
            g.endFun();
        }

        void genMoore(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            bCPPFun(g, false, isDecoratedRes, isDecoratedArg);
            {
                genBodyMoore(g, isDecoratedRes, isDecoratedArg);
            }
            g.endFun();
        }

        /*
         */
        void genMPFI(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            bCPPFun(g, true, isDecoratedRes, isDecoratedArg);
            {
                genBodyMPFI(g, isDecoratedRes, isDecoratedArg);
            }
            g.endFun();
        }

        void genCPP(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            bCPPFun(g, true, isDecoratedRes, isDecoratedArg);
            {
                genBodyCPP(g, isDecoratedRes, isDecoratedArg);
            }
            g.endFun();
        }

        String genTempFun(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            List<String> argms = new ArrayList<>();
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            switch (results[0]) {
                case INTERVAL:
                case POINT:
                    argms.add("int r_tag");
                    if (results.length == 2) {
                        argms.add("void *" + resNames[0]);
                        argms.add("void *" + resNames[1]);
                    } else {
                        argms.add("void *" + resNames[0]);
                    }
                    break;
                case TEXT:
                case STREAM:
                    assert results.length == 1;
                    argms.add("char **" + resNames[0]);
                    break;
                case BOOL:
                case DEC:
                case OVERLAP:
                    assert results.length == 1;
                    break;
                default:
                    throw new AssertionError();
            }
            for (int i = 0; i < args.length; i++) {
                switch (args[i]) {
                    case INTERVAL:
                        argms.add("int " + argNames[i] + "_tag");
                        argms.add("const void *" + argNames[i]);
                        break;
                    case POINT:
                        argms.add("int " + argNames[i] + "_tag");
                        argms.add("const void *" + argNames[i]);
                        break;
                    case TEXT:
                    case CS:
                        argms.add("const char* " + argNames[i]);
                        break;
                    case INT:
                    case LEN:
                        argms.add("int " + argNames[i]);
                        break;
                    case DEC:
                        argms.add("int " + argNames[i]);
                        break;
                    case POINT_ARRAY:
                        argms.add("const void *" + argNames[i]);
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String fName = g.prefix + (isDecoratedRes ? "dec_" : "bar_") + incName;
            return "int " + f(fName, argms.toArray(new String[argms.size()]));
        }

        void genH(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.s("extern " + genTempFun(g, isDecoratedRes, isDecoratedArg) + ";");
        }

        void genC(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.s();
            g.bFun(genTempFun(g, isDecoratedRes, isDecoratedArg));
            {
                String validExpr = "";
                for (int i = 0; i < args.length; i++) {
                    switch (args[i]) {
                        case INTERVAL:
                            if (!validExpr.isEmpty()) {
                                validExpr += " || ";
                            }
                            validExpr += "!" + f(isDecoratedArg ? "is_valid_d" : "is_valid_b", argNames[i] + "_tag", argNames[i]);
                            break;
                        case DEC:
                            if (!validExpr.isEmpty()) {
                                validExpr += " || ";
                            }
                            validExpr += argNames[i] + " != COM && "
                                    + argNames[i] + " != DAC && "
                                    + argNames[i] + " != DEF && "
                                    + argNames[i] + " != TRV && "
                                    + argNames[i] + " != ILL";
                            break;
                        case TEXT:
                        case CS:
                            if (!validExpr.isEmpty()) {
                                validExpr += " || ";
                            }
                            validExpr += argNames[i] + " == NULL";
                            break;
                        case POINT:
                        case INT:
                            break;
                        default:
                            throw new AssertionError();
                    }
                }
                if (!validExpr.isEmpty()) {
                    assert results.length == 1 || results.length == 2 && results[0] == results[1];
                    switch (results[0]) {
                        case INTERVAL:
                            if (isDecoratedRes) {
                                if (results.length == 2) {
                                    g.retIf(validExpr,
                                            f("p1788_dec_nai", "r_tag", resNames[0]) + ", "
                                            + f("p1788_dec_nai", "r_tag", resNames[1]) + ", EXC_INVALID_OPERAND");
                                } else {
                                    g.retIf(validExpr,
                                            f("p1788_dec_nai", "r_tag", resNames[0]) + ", EXC_INVALID_OPERAND");
                                }
                            } else if (results.length == 2) {
                                g.retIf(validExpr,
                                        f("p1788_bar_empty", "r_tag", resNames[0]) + ", "
                                        + f("p1788_bar_empty", "r_tag", resNames[1]) + ", EXC_INVALID_OPERAND");
                            } else {
                                g.retIf(validExpr,
                                        f("p1788_bar_empty", "r_tag", resNames[0]) + ", EXC_INVALID_OPERAND");
                            }
                            break;
                        case POINT:
                            if (results.length == 2) {
                                g.retIf(validExpr,
                                        f("p1788_set_nan", "r_tag", resNames[0]) + ", "
                                        + f("p1788_set_nan", "r_tag", resNames[1]) + ", EXC_INVALID_OPERAND");
                            } else {
                                g.retIf(validExpr, f("p1788_set_nan", "r_tag", resNames[0]) + ", EXC_INVALID_OPERAND");
                            }
                            break;
                        case TEXT:
                        case STREAM:
                            g.retIf(validExpr,
                                    "*r = " + f("strdup", isDecoratedArg ? "\"[nai]\"" : "\"[]\"") + ", EXC_INVALID_OPERAND");
                            break;
                        case BOOL:
                        case DEC:
                        case OVERLAP:
                            g.retIf(validExpr, "EXC_INVALID_OPERAND");
                            break;
                        default:
                            throw new AssertionError();
                    }
                }

                if (isDecoratedArg) {
                    validExpr = "";
                    for (int i = 0; i < args.length; i++) {
                        switch (args[i]) {
                            case INTERVAL:
                                if (!validExpr.isEmpty()) {
                                    validExpr += " || ";
                                }
                                validExpr += f("is_nai", argNames[i] + "_tag", argNames[i]);
                                break;
                            case DEC:
                            case TEXT:
                            case CS:
                            case POINT:
                            case INT:
                                break;
                            default:
                                throw new AssertionError();
                        }
                    }
                    if (!validExpr.isEmpty()) {
                        assert results.length == 1 || results.length == 2 && results[0] == results[1];
                        switch (results[0]) {
                            case INTERVAL:
                                if (isDecoratedRes) {
                                    if (results.length == 2) {
                                        g.retIf(validExpr,
                                                f("p1788_dec_nai", "r_tag", resNames[0]) + ", "
                                                + f("p1788_dec_nai", "r_tag", resNames[1]));
                                    } else {
                                        g.retIf(validExpr, f("p1788_dec_nai", "r_tag", resNames[0]));
                                    }
                                } else {
                                    assert results.length == 1;
                                    g.retIf(validExpr,
                                            f("p1788_bar_empty", "r_tag", resNames[0]) + ", EXC_INTERVAL_PART_OF_NAI");
                                }
                                break;
                            case POINT:
                                if (results.length == 2) {
                                    g.retIf(validExpr,
                                            f("p1788_set_nan", "r_tag", resNames[0]) + ", "
                                            + f("p1788_set_nan", "r_tag", resNames[1]) + ", 0");
                                } else {
                                    g.retIf(validExpr, f("p1788_set_nan", "r_tag", resNames[0]) + ", 0");
                                }
                                break;
                            case TEXT:
                            case STREAM:
                                g.retIf(validExpr,
                                        "*r = " + f("strdup", isDecoratedArg ? "\"[nai]\"" : "\"[]\"") + ", 0");
                                break;
                            case BOOL:
                            case DEC:
                            case OVERLAP:
                                g.retIf(validExpr, "0");
                                break;
                            default:
                                throw new AssertionError();
                        }
                    }
                }
                genBodyC(g, isDecoratedRes, isDecoratedArg);
            }
            g.endFun();
        }

        private void clearVars(GenP1788Base g, List<String> mpfiVarNames) {
            for (String varName : mpfiVarNames) {
                g.s(f("mpfi_clear", varName) + ";");
            }
        }

        private void clearVars(GenP1788Base g, List<String> mpfiVarNames, List<String> mpfrVarNames) {
            for (String varName : mpfiVarNames) {
                g.s(f("mpfi_clear", varName) + ";");
            }
            for (String varName : mpfrVarNames) {
                g.s(f("mpfr_clear", varName) + ";");
            }
        }

        void genBodyC(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            boolean needDecoration = false;
            switch (results[0]) {
                case INTERVAL:
                case TEXT:
                case STREAM:
                    needDecoration = constantDecoration == null && isDecoratedRes;
                    break;
                case DEC:
                    needDecoration = true;
                    break;
            }
            List<String> mpfiVarNames = new ArrayList<>();
            List<String> mpfrVarNames = new ArrayList<>();
            List<String> stmts = new ArrayList();
            List<String> argsInc = new ArrayList<>();
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            for (int i = 0; i < results.length; i++) {
                switch (results[i]) {
                    case INTERVAL:
                        mpfiVarNames.add("m" + resNames[i]);
                        stmts.add(f("mpfi_init2", "m" + resNames[i], f("p1788_get_prec", "r_tag")));
                        argsInc.add("m" + resNames[i]);
                        break;
                    case POINT:
                        mpfrVarNames.add("m" + resNames[i]);
                        stmts.add(f("mpfr_init2", "m" + resNames[i], f("p1788_get_prec", "r_tag")));
                        argsInc.add("m" + resNames[i]);
                        break;
                    case TEXT:
                    case STREAM:
                    case BOOL:
                    case DEC:
                    case OVERLAP:
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            boolean declaredD = false;
            for (int i = 0; i < args.length; i++) {
                switch (args[i]) {
                    case INTERVAL:
                        mpfiVarNames.add("m" + argNames[i]);
                        if (isDecoratedArg) {
                            stmts.add((!needDecoration ? "" : declaredD ? "d = " : "int d = ")
                                    + f("p1788_d_get_fi",
                                            "m" + argNames[i],
                                            argNames[i] + "_tag",
                                            argNames[i],
                                            !needDecoration ? "TRV" : declaredD ? "d" : "COM"));
                            declaredD = declaredD || needDecoration;
                        } else {
                            stmts.add(f("p1788_b_get_fi",
                                    "m" + argNames[i],
                                    argNames[i] + "_tag",
                                    argNames[i]));
                        }
                        argsInc.add("m" + argNames[i]);
                        if (results[0] == Kind.TEXT || results[0] == Kind.STREAM) {
                            argsInc.add(isDecoratedArg ? "d" : "ILL");
                        }
                        break;
                    case POINT:
                        mpfrVarNames.add("m" + argNames[i]);
                        stmts.add(f("p1788_get_fr",
                                "m" + argNames[i],
                                argNames[i] + "_tag",
                                argNames[i]));
                        argsInc.add("m" + argNames[i]);
                        break;
                    case TEXT:
                    case CS:
                        argsInc.add(argNames[i]);
                        break;
                    case INT:
                        argsInc.add(argNames[i]);
                        break;
                    case DEC:
                        argsInc.add(argNames[i]);
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String fIncName = g.mpfi_prefix + incName;
            if (results.length == 2 || results[0] == Kind.POINT) {
                fIncName += "Subnormal";
            }
            if (!mpfiVarNames.isEmpty()) {
                StringBuilder sb = new StringBuilder().append("mpfi_t");
                for (int i = 0; i < mpfiVarNames.size(); i++) {
                    if (i != 0) {
                        sb.append(',');
                    }
                    sb.append(' ').append(mpfiVarNames.get(i));
                }
                g.s(sb.append(';').toString());
            }
            if (!mpfrVarNames.isEmpty()) {
                StringBuilder sb = new StringBuilder().append("mpfr_t");
                for (int i = 0; i < mpfrVarNames.size(); i++) {
                    if (i != 0) {
                        sb.append(',');
                    }
                    sb.append(' ').append(mpfrVarNames.get(i));
                }
                g.s(sb.append(';').toString());
            }
            for (String stmt : stmts) {
                g.s(stmt + ";");
            }
            String call = f(fIncName, argsInc.toArray(new String[argsInc.size()]));
            switch (results[0]) {
                case INTERVAL:
                    g.s(f("MPFR_SAVE_RANGE_EXP", "r_tag") + ";");
                    if (exceptionsPossible) {
                        assert results.length == 1;
                        g.s("int locdec = " + call + ";");
                        g.shortIf("locdec >= 0",
                                (needDecoration ? "" : "(")
                                + "locdec = "
                                + f(g.mpfi_prefix + "subnormalize", "m" + resNames[0], "locdec")
                                + (needDecoration ? " & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;" : ", 0);"));
                    } else {
                        g.s((needDecoration ? "int locdec = " : "")
                                + (results.length == 2 ? call : f(g.mpfi_prefix + "subnormalize", "m" + resNames[0], call))
                                + (needDecoration ? " & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;" : ";"));
                    }
                    g.s(f("MPFR_RESTORE_RANGE_EXP") + ";");
                    if (isDecoratedRes) {
                        String resultDec;
                        if (constantDecoration != null) {
                            resultDec = constantDecoration.name();
                        } else if (declaredD) {
                            resultDec = "locdec < d ? locdec : d";
                        } else {
                            resultDec = "locdec";
                        }
                        if (results.length == 2) {
                            g.s(f("p1788_d_set_fi", "r_tag", resNames[0], "m" + resNames[0], resultDec) + ";");
                            g.s(f("p1788_d_set_fi", "r_tag", resNames[1], "m" + resNames[1], "TRV") + ";");
                        } else {
                            g.s(f("p1788_d_set_fi", "r_tag", resNames[0], "m" + resNames[0], resultDec) + ";");
                        }
                    } else if (results.length == 2) {
                        g.s(f("p1788_b_set_fi", "r_tag", resNames[0], "m" + resNames[0]) + ";");
                        g.s(f("p1788_b_set_fi", "r_tag", resNames[1], "m" + resNames[1]) + ";");
                    } else {
                        g.s(f("p1788_b_set_fi", "r_tag", resNames[0], "m" + resNames[0]) + ";");
                    }
                    clearVars(g, mpfiVarNames, mpfrVarNames);
                    g.ret(!exceptionsPossible ? "0" : needDecoration ? "locdec >= 0 ? 0 : locdec" : "locdec");
                    break;
                case POINT:
                    g.s(f("MPFR_SAVE_RANGE_EXP", "r_tag") + ";");
                    g.s(call + ";");
                    g.s(f("MPFR_RESTORE_RANGE_EXP") + ";");
                    if (results.length == 2) {
                        g.s(f("p1788_set_fr", "r_tag", resNames[0], "m" + resNames[0]) + ";");
                        g.s(f("p1788_set_fr", "r_tag", resNames[1], "m" + resNames[1]) + ";");
                    } else {
                        g.s(f("p1788_set_fr", "r_tag", resNames[0], "m" + resNames[0]) + ";");
                    }
                    clearVars(g, mpfiVarNames, mpfrVarNames);
                    g.ret("0");
                    break;
                case TEXT:
                case STREAM:
                    assert results.length == 1;
                    g.s(f("MPFR_SAVE_RANGE_EXP", argNames[0] + "_tag") + ";");
                    g.s("*" + resNames[0] + " = " + call + ";");
                    g.s(f("MPFR_RESTORE_RANGE_EXP") + ";");
                    clearVars(g, mpfiVarNames, mpfrVarNames);
                    g.ret("0");
                    break;
                case BOOL:
                case OVERLAP:
                    assert results.length == 1;
                    g.s("int result = " + call + ";");
                    clearVars(g, mpfiVarNames, mpfrVarNames);
                    g.ret("result");
                    break;
                case DEC:
                    clearVars(g, mpfiVarNames, mpfrVarNames);
                    g.ret("d");
                    break;
                default:
                    throw new AssertionError();
            }
        }

        void bCPPFun(GenP1788Base g, boolean hasREP, boolean isDecoratedRes, boolean isDecoratedArg) {
            g.s();
            switch (argTypenamesCnt) {
                case 1:
                    if (results[0] == Kind.STREAM) {
                        g.s("template< typename CharT, typename Traits >");
                    }
                    break;
                case 2:
                    g.s("template<typename T1>");
                    break;
                case 3:
                    g.s("template<typename T1, typename T2>");
                    break;
                case 4:
                    g.s("template<typename T1, typename T2, typename T3>");
                    break;
                default:
                    throw new AssertionError();
            }
            String retType1 = null, retType;
            List<String> cppArgs = new ArrayList<>();
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            switch (results[0]) {
                case INTERVAL:
                    retType1 = isDecoratedRes ? "representation_dec" : "representation";
                    if (results.length == 2) {
                        retType = "std::pair<" + retType1 + "," + retType1 + ">";
                    } else {
                        assert results.length == 1;
                        retType = retType1;
                    }
                    break;
                case POINT:
                    retType1 = "T";
                    if (results.length == 2) {
                        retType = "std::pair<" + retType1 + "," + retType1 + ">";
                    } else {
                        assert results.length == 1;
                        retType = retType1;
                    }
                    break;
                case BOOL:
                    assert results.length == 1;
                    retType = retType1 = "bool";
                    break;
                case DEC:
                    assert results.length == 1;
                    retType = retType1 = "p1788::decoration::decoration";
                    break;
                case OVERLAP:
                    assert results.length == 1;
                    retType = retType1 = "p1788::overlapping::overlapping_state";
                    break;
                case TEXT:
                    assert results.length == 1;
                    retType = retType1 = "std::string";
                    break;
                case STREAM:
                    assert results.length == 1;
                    retType = retType1 = "std::basic_ostream<CharT, Traits>&";
                    cppArgs.add("std::basic_ostream<CharT, Traits>& os");
                    break;
                default:
                    throw new AssertionError();
            }
            for (int i = 0; i < args.length; i++) {
                String argType = null;
                String T = "T";
                switch (args[i]) {
                    case INTERVAL:
                        argType = isDecoratedArg ? "representation_dec" : "representation";
                        if (argTypenames[i] != 0) {
                            T += argTypenames[i];
                            if (hasREP) {
                                argType = isDecoratedArg ? "REP_DEC" : "REP";
                            } else {
                                argType = isDecoratedArg ? "representation_dec_type" : "representation_type";
                            }
                            argType += "<" + T + ">";
                        }
                        cppArgs.add(argType + " const& " + argNames[i]);
                        break;
                    case POINT:
                        if (argTypenames[i] != 0) {
                            T += argTypenames[i];
                        }
                        cppArgs.add(T + " " + argNames[i]);
                        break;
                    case TEXT:
                        cppArgs.add("std::string const& " + argNames[i]);
                        break;
                    case CS:
                        break;
                    case INT:
                        cppArgs.add("int " + argNames[i]);
                        break;
                    case DEC:
                        cppArgs.add("p1788::decoration::decoration " + argNames[i]);
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String shortCallName = isDecoratedRes ? cppNameDec : cppName;
            g.bFun(f("static " + retType + " " + shortCallName, cppArgs.toArray(new String[cppArgs.size()])));
        }

        void genBodyDumper(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            String retType1, retType;
            List<String> argmcs = new ArrayList<>();
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            switch (results[0]) {
                case INTERVAL:
                    retType1 = isDecoratedRes ? "representation_dec" : "representation";
                    if (results.length == 2) {
                        retType = "std::pair<" + retType1 + "," + retType1 + ">";
                    } else {
                        assert results.length == 1;
                        retType = retType1;
                    }
                    break;
                case POINT:
                    retType1 = "T";
                    if (results.length == 2) {
                        retType = "std::pair<" + retType1 + "," + retType1 + ">";
                    } else {
                        assert results.length == 1;
                        retType = retType1;
                    }
                    break;
                case BOOL:
                    assert results.length == 1;
                    retType = retType1 = "bool";
                    break;
                case DEC:
                    assert results.length == 1;
                    retType = retType1 = "p1788::decoration::decoration";
                    break;
                case OVERLAP:
                    assert results.length == 1;
                    retType = retType1 = "p1788::overlapping::overlapping_state";
                    break;
                case TEXT:
                    assert results.length == 1;
                    retType = retType1 = "std::string";
                    break;
                case STREAM:
                    assert results.length == 1;
                    retType = retType1 = "std::basic_ostream<CharT, Traits>&";
                    argmcs.add("os");
                    break;
                default:
                    throw new AssertionError();
            }
            for (int i = 0; i < args.length; i++) {
                switch (args[i]) {
                    case INTERVAL:
                    case POINT:
                    case TEXT:
                    case INT:
                    case DEC:
                        argmcs.add(argNames[i]);
                        break;
                    case CS:
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String shortCallName = isDecoratedRes ? cppNameDec : cppName;
            String callName = "p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::" + shortCallName;
            List<String> validChecks = new ArrayList<>();
            List<String> prints = new ArrayList<>();
            if (!g.skipDumper.contains(this)) {
                for (int i = 0; i < args.length; i++) {
                    switch (args[i]) {
                        case INTERVAL:
                            prints.add(f(isDecoratedArg ? "print_dec" : "print_bare", argNames[i]) + ";");
                            validChecks.add(f("is_valid", argNames[i]));
                            break;
                        case POINT:
                            prints.add(f("print_num", argNames[i]) + ";");
                            break;
                        case TEXT:
                            prints.add(f("printf", "\"\\\"%s\\\"\"", argNames[i] + "." + f("c_str")) + ";");
                            break;
                        case CS:
                            break;
                        case INT:
                            prints.add(f("printf", "\"%d\"", argNames[i]) + ";");
                            break;
                        case DEC:
                            prints.add(f("printf", "\"%s\"", "dec_strings[static_cast<int>(" + argNames[i] + ") >> 2]") + ";");
                            validChecks.add(f("decoration::is_valid", argNames[i]));
                            break;
                        default:
                            throw new AssertionError();
                    }
                }
                String cond = "";
                if (validChecks.isEmpty()) {
                    cond = "true";
                } else {
                    for (int i = 0; i < validChecks.size(); i++) {
                        if (i > 0) {
                            cond += " && ";
                        }
                        cond += validChecks.get(i);
                    }
                }
                g.s("exception::exception_bits saved_cwd = exception::cwd();");
                g.s("exception::cwd() = exception::none_bit;");
                g.s("exception::exception_bits saved_state = exception::state();");
                g.bIf(cond);
                {
                    g.s(f("print_op", "\"" + opName + "\"") + ";");
                    for (int i = 0; i < prints.size(); i++) {
                        if (i > 0) {
                            g.s(f("printf", "\" | \"") + ";");
                        }
                        g.s(prints.get(i));
                    }
                    g.s(f("printf", "\"\\n\"") + ";");
                }
                g.endIf();
                g.s("exception::cwd() = saved_cwd;");
                g.s("exception::state() = saved_state;");
            }
            g.s(retType + " r = " + f(callName, argmcs.toArray(new String[argmcs.size()])) + ";");
            if (false) {
                if (g.skipDumper.contains(this)) {
                    g.s("/*");
                }

                g.s(f("printf", "\"" + shortCallName + "(\"") + ";");
                for (int i = 0; i < args.length; i++) {
                    if (i == 0) {
                        if (results[0] == Kind.TEXT) {
                            g.s(f("printf", "\"os,\"") + ";");
                        }
                    } else {
                        g.s(f("printf", "\",\"") + ";");
                    }
                    switch (args[i]) {
                        case INTERVAL:
                            g.s(f(isDecoratedArg ? "print_dec" : "print_bare", argNames[i]) + ";");
                            break;
                        case POINT:
                            g.s(f("print_num", argNames[i]) + ";");
                            break;
                        case TEXT:
                            break;
                        case INT:
                            g.s(f("printf", "\"%d\"", argNames[i]) + ";");
                            break;
                        case DEC:
                            g.s(f("printf", "\"%s\"", "dec_strings[static_cast<int>(" + argNames[i] + ") >> 2]") + ";");
                            break;
                        default:
                            throw new AssertionError();
                    }
                }
                g.s(f("printf", "\") = \"") + ";");
                switch (results[0]) {
                    case INTERVAL:
                        if (results.length == 2) {
                            g.s(f(isDecoratedRes ? "print_dec" : "print_bare", "r.first") + ";");
                            g.s(f("printf", "\",\"") + ";");
                            g.s(f(isDecoratedRes ? "print_dec" : "print_bare", "r.second") + ";");
                        } else {
                            assert results.length == 1;
                            g.s(f(isDecoratedRes ? "print_dec" : "print_bare", "r") + ";");
                        }
                        break;
                    case POINT:
                        retType1 = "T";
                        if (results.length == 2) {
                            g.s(f("print_num", "r.first") + ";");
                            g.s(f("printf", "\",\"") + ";");
                            g.s(f("print_num", "r.second") + ";");
                        } else {
                            assert results.length == 1;
                            g.s(f("print_num", "r") + ";");
                        }
                        break;
                    case BOOL:
                        assert results.length == 1;
                        g.s(f("printf", "\"%d\"", "r") + ";");
                        break;
                    case DEC:
                        assert results.length == 1;
                        g.s(f("printf", "\"%s\"", "dec_strings[static_cast<int>(r) >> 2]") + ";");
                        break;
                    case OVERLAP:
                        assert results.length == 1;
                        g.s(f("printf", "\"%04x\"", "r") + ";");
//                        s(f("printf", "\"%04x\"", "static_cast<int>(r)") + ";");
                        break;
                    case TEXT:
                        assert results.length == 1;
                        g.s(f("printf", "\"os\"") + ";");
                        break;
                    default:
                        throw new AssertionError();
                }
                g.s(f("printf", "\";\\n\"") + ";");
                if (g.skipDumper.contains(this)) {
                    g.s("*/");
                }
            }
            g.ret("r");
        }

        void genBodyMoore(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            String retError;
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            switch (results[0]) {
                case INTERVAL:
                    String retType = isDecoratedRes ? "representation_dec" : "representation";
                    retError = f(retType);
                    if (results.length == 2) {
                        retType = "std::pair<" + retType + "," + retType + ">";
                        retError = f(retType, retError, retError);
                    }
                    break;
                case POINT:
                    retError = f("std::numeric_limits<float>::quiet_NaN");
                    if (results.length == 2) {
                        retError = f("std::pair<T,T>", retError, retError);
                    }
                    break;
                case BOOL:
                    assert results.length == 1;
                    retError = "false";
                    break;
                case DEC:
                    assert results.length == 1;
                    retError = "p1788::decoration::decoration::ill";
                    break;
                case OVERLAP:
                    assert results.length == 1;
                    retError = "p1788::overlapping::overlapping_state::undefined";
                    break;
                case TEXT:
                    assert results.length == 1;
                    retError = "\"[" + (isDecoratedRes ? "nai" : "empty") + "]\"";
                    break;
                case STREAM:
                    assert results.length == 1;
                    retError = "os";
                    break;
                default:
                    throw new AssertionError();
            }
            List<String> validChecks = new ArrayList<>();
            List<String> naiChecks = new ArrayList<>();
            for (int i = 0; i < args.length; i++) {
                switch (args[i]) {
                    case INTERVAL:
                        validChecks.add(f("check_valid", argNames[i]));
                        naiChecks.add(argNames[i] + ".dec_ != p1788::decoration::decoration::ill");
                        break;
                    case POINT:
                        break;
                    case TEXT:
                        break;
                    case CS:
                        break;
                    case INT:
                        break;
                    case DEC:
                        validChecks.add(f("p1788::decoration::is_valid", argNames[i]));
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            if (isDecoratedArg && results[0] != Kind.INTERVAL) {
                validChecks.addAll(naiChecks);
            }
            if (validChecks.isEmpty()) {
                genBodyMooreValid(g, isDecoratedRes, isDecoratedArg);
            } else {
                String cond = "";
                for (int i = 0; i < validChecks.size(); i++) {
                    if (i > 0) {
                        cond += " && ";
                    }
                    cond += validChecks.get(i);
                }
                g.bIf(cond);
                {
                    genBodyMooreValid(g, isDecoratedRes, isDecoratedArg);
                }
                g.elseIf();
                {
                    g.ret(retError);
                }
                g.endIf();
            }
        }

        void genBodyMooreValid(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            String retType1, retType, mooreRetType;
            String retExpr = resNames[0];
            String callName;
            if (opName.equals("empty") || opName.equals("nai")) {
                callName = "representation";
            } else if (opName.equals("equal")) {
                callName = "operator==";
            } else if (opName.equals("newDec") || opName.equals("setDec") || opName.equals("convertType") || opName.equals("pos")) {
                callName = "representation::convert_type";
            } else if (opName.equals("entire")) {
                callName = "representation::entire";
//            } else if (opName.equals("isEmpty")) {
//                callName = "Moore::is_empty_not_friend";
            } else if (opName.equals("numsDecToInterval")) {
                callName = "Moore::nums_to_interval";
            } else if (opName.equals("textToDecoratedInterval")) {
                callName = "Moore::text_to_dec_interval";
            } else {
                callName = "Moore::" + cppName;
            }
            List<String> argmcs = new ArrayList<>();
            List<String> setObjects = new ArrayList<>();
            List<String[]> setPrefixes = new ArrayList<>();
            List<String> decoratedArgs = new ArrayList<>();
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            switch (results[0]) {
                case INTERVAL:
                    if (isDecoratedRes) {
                        retType1 = "representation_dec";
                        if (results.length == 2) {
                            retType = "std::pair<" + retType1 + "," + retType1 + ">";
                            mooreRetType = "std::pair<representation,representation>";
                            setObjects.add("result.first");
                            setPrefixes.add(new String[]{resNames[0] + ".first", "dec1"});
                            setObjects.add("result.second");
                            setPrefixes.add(new String[]{resNames[0] + ".second", "dec2"});
                        } else {
                            assert results.length == 1;
                            retType = retType1;
                            mooreRetType = "representation";
                            setObjects.add("result");
                            if (constantDecoration == null) {
                                setPrefixes.add(new String[]{resNames[0], "dec"});
                            } else {
                                String dec = constantDecoration.name().toLowerCase();
                                setPrefixes.add(new String[]{resNames[0], "p1788::decoration::decoration::" + dec});
                            }
                        }
                        g.s(retType + " result;");
                        retExpr = "result";
                    } else {
                        retType1 = "representation";
                        if (results.length == 2) {
                            mooreRetType = retType = "std::pair<" + retType1 + "," + retType1 + ">";
                        } else {
                            assert results.length == 1;
                            mooreRetType = retType = retType1;
                        }
                    }
                    if (!callName.startsWith("representation")) {
                        callName += "<T>";
                    }
                    if (exceptionsPossible) {
                        if (opName.equals("textToDecoratedInterval")) {
                            g.s("Moore::Decoration d = Moore::Decoration::Com;");
                            argmcs.add("d");
                        }
                        argmcs.add(resNames[0]);
                    }
                    break;
                case POINT:
                    retType1 = "T";
                    if (results.length == 2) {
                        retType = "std::pair<" + retType1 + "," + retType1 + ">";
                        mooreRetType = retType1;
                        g.s(retType1 + " " + resNames[1] + ";");
                        argmcs.add(resNames[1]);
                        retExpr = f(retType, resNames[0], resNames[1]);
                    } else {
                        assert results.length == 1;
                        mooreRetType = retType = retType1;

                    }
                    callName += "<T>";
                    break;
                case BOOL:
                    assert results.length == 1;
                    mooreRetType = retType = retType1 = "bool";
                    break;
                case DEC:
                    assert results.length == 1;
                    retType = retType1 = "p1788::decoration::decoration";
                    mooreRetType = "p1788::decoration::decoration";
                    break;
                case OVERLAP:
                    assert results.length == 1;
                    retType = retType1 = "p1788::overlapping::overlapping_state";
                    mooreRetType = "Moore::Overlap";
                    retExpr = f("static_cast<" + retType + ">", resNames[0]);
                    break;
                case TEXT:
                    assert results.length == 1;
                    mooreRetType = retType = retType1 = "std::string";
                    break;
                case STREAM:
                    assert results.length == 1;
                    mooreRetType = retType = retType1 = "std::basic_ostream<CharT, Traits>&";
                    argmcs.add("os");
                    retExpr = "os";
                    break;
                default:
                    throw new AssertionError();
            }
            for (int i = 0; i < args.length; i++) {
                switch (args[i]) {
                    case INTERVAL:
                        if (isDecoratedArg) {
                            argmcs.add(f("bare", argNames[i]));
                            decoratedArgs.add(argNames[i]);
                        } else {
                            argmcs.add(argNames[i]);
                        }
                        break;
                    case POINT:
                    case TEXT:
                    case INT:
                        argmcs.add(argNames[i]);
                        break;
                    case DEC:
                    case CS:
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String call = f(callName, argmcs.toArray(new String[argmcs.size()]));
            if (exceptionsPossible) {
                g.s(mooreRetType + " " + resNames[0] + ";");
                genExceptionMoore(g, call);
            } else {
                g.s(mooreRetType + " " + resNames[0] + " = " + call + ";");
            }
            if (isDecoratedRes && results[0] == Kind.INTERVAL && constantDecoration == null) {
                genDecMoore(g);
            }
            assert setObjects.size() == setPrefixes.size();
            for (int i = 0; i < setObjects.size(); i++) {
                String setObject = setObjects.get(i);
                String[] setPrefix = setPrefixes.get(i);
                List<String> setArgs = new ArrayList<>(Arrays.asList(setPrefix));
                setArgs.addAll(decoratedArgs);
                g.s(f(setObject + ".set" + decoratedArgs.size(), setArgs.toArray(new String[setArgs.size()])) + ";");
            }
            g.ret(retExpr);
        }

        void genDecMoore(GenP1788Base g) {
            g.s("p1788::decoration::decoration dec = p1788::decoration::decoration::trv;");
        }

        void genExceptionMoore(GenP1788Base g, String call) {
            throw new UnsupportedOperationException();
        }

        void genBodyMPFI(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            boolean needDecoration = false;
            switch (results[0]) {
                case INTERVAL:
                case TEXT:
                case STREAM:
                    needDecoration = constantDecoration == null && isDecoratedRes;
                    break;
                case DEC:
                    needDecoration = true;
                    break;
            }

            String retType = null;
            List<String> mpfiVarNames = new ArrayList<>();
            List<String> validChecks = new ArrayList<>();
            List<String> naiChecks = new ArrayList<>();
            List<String> stmts = new ArrayList<>();
            List<String> mpfiArgs = new ArrayList<>();
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            switch (results[0]) {
                case INTERVAL:
                    retType = isDecoratedRes ? "representation_dec" : "representation";
                    if (results.length == 2) {
                        mpfiVarNames.add("m" + resNames[0]);
                        mpfiVarNames.add("m" + resNames[1]);
                        stmts.add(f("mpfi_init2", "m" + resNames[0], "mpfr_var::PREC"));
                        stmts.add(f("mpfi_init2", "m" + resNames[1], "mpfr_var::PREC"));
                        mpfiArgs.add("m" + resNames[0]);
                        mpfiArgs.add("m" + resNames[1]);
                    } else {
                        assert results.length == 1;
                        mpfiVarNames.add("m" + resNames[0]);
                        stmts.add(f("mpfi_init2", "m" + resNames[0], "mpfr_var::PREC"));
                        mpfiArgs.add("m" + resNames[0]);
                    }
                    break;
                case POINT:
                    retType = "T";
                    if (results.length == 2) {
                        stmts.add("mpfr_var m" + resNames[0] + ", m" + resNames[1]);
                        mpfiArgs.add(f("m" + resNames[0]));
                        mpfiArgs.add(f("m" + resNames[1]));
                    } else {
                        assert results.length == 1;
                        stmts.add("mpfr_var m" + resNames[0]);
                        mpfiArgs.add(f("m" + resNames[0]));
                    }
                    break;
                case BOOL:
                    assert results.length == 1;
                    retType = "bool";
                    break;
                case DEC:
                    assert results.length == 1;
                    retType = "decoration::decoration";
                    break;
                case OVERLAP:
                    assert results.length == 1;
                    retType = "overlapping::overlapping_state";
                    break;
                case TEXT:
                    assert results.length == 1;
                    retType = "std::string";
                    stmts.add("char *" + resNames[0]);
                    break;
                case STREAM:
                    assert results.length == 1;
                    retType = "std::basic_ostream<CharT, Traits>&";
                    stmts.add("char *" + resNames[0]);
                    break;
                default:
                    throw new AssertionError();
            }
            boolean declaredD = false;
            for (int i = 0; i < args.length; i++) {
                String T = "T";
                if (argTypenames[i] != 0) {
                    T += argTypenames[i];
                }
                switch (args[i]) {
                    case INTERVAL:
                        mpfiVarNames.add("m" + argNames[i]);
                        validChecks.add("!" + f("mpfr_bin_ieee754_flavor<" + T + ">::is_valid", argNames[i]));
                        if (isDecoratedArg) {
                            naiChecks.add(argNames[i] + ".second == decoration::decoration::ill");
                            stmts.add((!needDecoration ? "" : declaredD ? "d = " : "decoration::decoration d = ")
                                    + argNames[i] + f(".get_fi",
                                            "m" + argNames[i],
                                            !needDecoration
                                                    ? "decoration::decoration::trv"
                                                    : declaredD ? "d" : "decoration::decoration::com"));
                            declaredD = declaredD || needDecoration;
                        } else {
                            stmts.add(argNames[i] + f(".get_fi", "m" + argNames[i]));
                        }

                        mpfiArgs.add("m" + argNames[i]);
                        if (results[0] == Kind.TEXT || results[0] == Kind.STREAM) {
                            mpfiArgs.add(isDecoratedArg ? f("static_cast<int>", "d") : "0");
                        }
                        break;
                    case POINT:
                        stmts.add(g.cls() + "<" + T + "> ::mpfr_var::" + f("setup"));
                        stmts.add("typename " + g.cls() + "<" + T + "> ::mpfr_var " + f("m" + argNames[i], argNames[i], "MPFR_RNDN"));
                        mpfiArgs.add(f("m" + argNames[i]));
                        break;
                    case TEXT:
                        mpfiArgs.add(argNames[i] + ".c_str()");
                        if (i == 0) {
                            mpfiArgs.add(isDecoratedRes ? "1" : "0");
                        }
                        break;
                    case CS:
                        mpfiArgs.add("NULL");
                        break;
                    case INT:
                        mpfiArgs.add(argNames[i]);
                        break;
                    case DEC:
                        validChecks.add("!" + f("decoration::is_valid", argNames[i]));
                        mpfiArgs.add("static_cast<int>(" + argNames[i] + ")");
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String fIncName = g.mpfi_prefix + incName;
            if (results.length == 2 || results[0] == Kind.POINT) {
                fIncName += "Subnormal";
            }
            if (!mpfiVarNames.isEmpty()) {
                StringBuilder sb = new StringBuilder().append("mpfi_t");
                for (int i = 0; i < mpfiVarNames.size(); i++) {
                    if (i != 0) {
                        sb.append(',');
                    }
                    sb.append(' ').append(mpfiVarNames.get(i));
                }
                g.s(sb.append(';').toString());
            }
            String validExpr = "";
            validChecks.addAll(naiChecks);
            for (String validCheck : validChecks) {
                if (!validExpr.isEmpty()) {
                    validExpr += " || ";
                }
                validExpr += validCheck;
            }
            if (!validExpr.isEmpty()) {
                assert results.length == 1 || results.length == 2 && results[0] == results[1];
                switch (results[0]) {
                    case INTERVAL:
                        if (isDecoratedRes) {
                            if (results.length == 2) {
                                g.retIf(validExpr,
                                        f("std::pair<representation_dec, representation_dec>", f("nai"), f("nai")));
                            } else {
                                g.retIf(validExpr, f("nai"));
                            }
                        } else if (results.length == 2) {
                            g.retIf(validExpr,
                                    f("std::pair<representation, representation>", f("empty"), f("empty")));
                        } else {
                            g.retIf(validExpr, f("empty"));
                        }
                        break;
                    case POINT:
                        if (results.length == 2) {
                            g.retIf(validExpr,
                                    f("std::pair<T,T>", f("std::numeric_limits<T>::quiet_NaN"), f("std::numeric_limits<T>::quiet_NaN")));
                        } else {
                            g.retIf(validExpr, f("std::numeric_limits<T>::quiet_NaN"));
                        }
                        break;
                    case TEXT:
                        g.retIf(validExpr,
                                "os << " + (isDecoratedArg ? "\"[nai]\"" : "\"[]\""));
                        break;
                    case STREAM:
                        g.retIf(validExpr,
                                "os << " + (isDecoratedArg ? "\"[nai]\"" : "\"[]\""));
                        break;
                    case BOOL:
                        g.retIf(validExpr, "false");
                        break;
                    case DEC:
                        g.retIf(validExpr, "decoration::decoration::ill");
                        break;
                    case OVERLAP:
                        g.retIf(validExpr, "overlapping::overlapping_state::undefined");
                        break;
                    default:
                        throw new AssertionError();
                }

            }
            String call = f(fIncName, mpfiArgs.toArray(new String[mpfiArgs.size()]));
            for (String stmt : stmts) {
                g.s(stmt + ";");
            }
            switch (results[0]) {
                case INTERVAL:
                    g.s(f("mpfr_var::setup") + ";");
                    if (exceptionsPossible) {
                        assert results.length == 1;
                        g.s("int locdec = " + call + ";");
                        g.bIf("locdec >= 0");
                        {
                            if (needDecoration) {
                                g.s("locdec = "
                                        + f(g.mpfi_prefix + "subnormalize", "m" + resNames[0], "locdec")
                                        + " & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;");
                            } else {
                                g.s(f(g.mpfi_prefix + "subnormalize", "m" + resNames[0], "locdec") + ";");
                            }
                        }
                        g.elseIf();
                        {
                            g.s((needDecoration ? "locdec = " : "") + f("signal_exception", "locdec") + ";");
                        }
                        g.endIf();
                    } else {
                        g.s((needDecoration ? "int locdec = " : "")
                                + (results.length == 2 ? call : f(g.mpfi_prefix + "subnormalize", "m" + resNames[0], call))
                                + (needDecoration ? " & ~MPFI_FLAGS_BOTH_ENDPOINTS_INEXACT;" : ";"));
                    }
                    if (isDecoratedRes) {
                        String resultDec;
                        if (constantDecoration != null) {
                            resultDec = "decoration::decoration::" + constantDecoration.name().toLowerCase();
                        } else if (declaredD) {
                            resultDec = f("std::min", f("static_cast<decoration::decoration>", "locdec"), "d");
                        } else {
                            resultDec = f("static_cast<decoration::decoration>", "locdec");
                        }
                        if (results.length == 2) {
                            g.s("representation_dec " + f(resNames[0], "m" + resNames[0], resultDec) + ";");
                            g.s("representation_dec " + f(resNames[1], "m" + resNames[1], "decoration::decoration::trv") + ";");
                        } else {
                            g.s("representation_dec " + f(resNames[0], "m" + resNames[0], resultDec) + ";");
                        }
                    } else if (results.length == 2) {
                        g.s("representation " + f(resNames[0], "m" + resNames[0]) + ";");
                        g.s("representation " + f(resNames[1], "m" + resNames[1]) + ";");
                    } else {
                        g.s("representation " + f(resNames[0], "m" + resNames[0]) + ";");
                    }
                    clearVars(g, mpfiVarNames);
                    if (results.length == 2) {
                        g.ret(f("std::pair<" + retType + "," + retType + ">", resNames[0], resNames[1]));
                    } else {
                        g.ret(resNames[0]);
                    }
                    break;
                case POINT:
                    assert !exceptionsPossible;
                    g.s(f("mpfr_var::setup") + ";");
                    g.s(call + ";");
                    if (results.length == 2) {
                        g.s(retType + " " + resNames[0] + " = m" + resNames[0] + ".template " + f("get<T>", "MPFR_RNDN") + ";");
                        g.s(retType + " " + resNames[1] + " = m" + resNames[1] + ".template " + f("get<T>", "MPFR_RNDN") + ";");
                        clearVars(g, mpfiVarNames);
                        g.ret(f("std::pair<" + retType + "," + retType + ">", resNames[0], resNames[1]) + ";");
                    } else {
                        g.s(retType + " " + resNames[0] + " = m" + resNames[0] + ".template " + f("get<T>", "MPFR_RNDN") + ";");
                        clearVars(g, mpfiVarNames);
                        g.ret(resNames[0]);
                    }
                    break;
                case TEXT:
                    g.s("GENBodyMPFI TEXT 1");
                    assert results.length == 1 && !exceptionsPossible;
                    g.s(f("mpfr_var::setup") + ";");
                    g.s(resNames[0] + " = " + call + ";");
                    clearVars(g, mpfiVarNames);
                    clearVars(g, mpfiVarNames);
                    g.s("std::string " + f("s", resNames[0]) + ";");
                    g.s(f("free", resNames[0]) + ";");
                    g.ret("s");
                    break;
                case STREAM:
                    assert results.length == 1 && !exceptionsPossible;
                    g.s(f("mpfr_var::setup") + ";");
                    g.s(resNames[0] + " = " + call + ";");
                    clearVars(g, mpfiVarNames);
                    g.s("std::string " + f("s", resNames[0]) + ";");
                    g.s(f("free", resNames[0]) + ";");
                    g.s("os << s;");
                    g.ret("os");
                    break;
                case BOOL:
                    assert results.length == 1 && !exceptionsPossible;
                    g.s("int " + resNames[0] + " = " + call + ";");
                    clearVars(g, mpfiVarNames);
                    g.ret(resNames[0]);
                    break;
                case DEC:
                    assert results.length == 1 && !exceptionsPossible;
                    g.s("int " + resNames[0] + " = " + call + ";");
                    clearVars(g, mpfiVarNames);
                    g.ret(f("static_cast<decoration::decoration>", resNames[0]));
                    break;
                case OVERLAP:
                    assert results.length == 1 && !exceptionsPossible;
                    g.s("int " + resNames[0] + " = " + call + ";");
                    clearVars(g, mpfiVarNames);
                    g.ret(f("static_cast<overlapping::overlapping_state>", resNames[0]));
                    break;
                default:
                    throw new AssertionError();
            }
        }

        void genBodyCPP(GenP1788Base g, boolean isDecoratedRes, boolean isDecoratedArg) {
            String retType = null;
            List<String> vars = new ArrayList<>();
            List<String> cArgs = new ArrayList<>();
            assert results.length == 1 || results.length == 2 && results[0] == results[1];
            switch (results[0]) {
                case INTERVAL:
                    retType = isDecoratedRes ? "representation_dec" : "representation";
                    cArgs.add("static_cast<int>(util::type_precision_order<T>::value)");
                    if (results.length == 2) {
                        vars.add(retType + " " + resNames[0]);
                        vars.add(retType + " " + resNames[1]);
                        cArgs.add("&" + resNames[0]);
                        cArgs.add("&" + resNames[1]);
                    } else {
                        assert results.length == 1;
                        vars.add(retType + " " + resNames[0]);
                        cArgs.add("&" + resNames[0]);
                    }
                    break;
                case POINT:
                    retType = "T";
                    cArgs.add("static_cast<int>(util::type_precision_order<T>::value)");
                    if (results.length == 2) {
                        vars.add(retType + " " + resNames[0]);
                        vars.add(retType + " " + resNames[1]);
                        cArgs.add("&" + resNames[0]);
                        cArgs.add("&" + resNames[1]);
                    } else {
                        assert results.length == 1;
                        vars.add(retType + " " + resNames[0]);
                        cArgs.add("&" + resNames[0]);
                    }
                    break;
                case BOOL:
                    assert results.length == 1;
                    retType = "bool";
                    break;
                case DEC:
                    assert results.length == 1;
                    retType = "decoration::decoration";
                    break;
                case OVERLAP:
                    assert results.length == 1;
                    retType = "overlapping::overlapping_state";
                    break;
                case TEXT:
                    assert results.length == 1;
                    retType = "std::string";
                    vars.add("char *" + resNames[0]);
                    cArgs.add("&" + resNames[0]);
                    break;
                case STREAM:
                    assert results.length == 1;
                    retType = "std::basic_ostream<CharT, Traits>&";
                    vars.add("char *" + resNames[0]);
                    cArgs.add("&" + resNames[0]);
                    break;
                default:
                    throw new AssertionError();
            }
            for (int i = 0; i < args.length; i++) {
                String T = "T";
                switch (args[i]) {
                    case INTERVAL:
                        if (argTypenames[i] != 0) {
                            T += argTypenames[i];
                        }
                        cArgs.add("static_cast<int>(util::type_precision_order<" + T + ">::value)");
                        cArgs.add("&" + argNames[i]);
                        break;
                    case POINT:
                        if (argTypenames[i] != 0) {
                            T += argTypenames[i];
                        }
                        cArgs.add("static_cast<int>(util::type_precision_order<" + T + ">::value)");
                        cArgs.add("&" + argNames[i]);
                        break;
                    case TEXT:
                        cArgs.add(argNames[i] + ".c_str()");
                        break;
                    case CS:
                        cArgs.add("NULL");
                        break;
                    case INT:
                        cArgs.add(argNames[i]);
                        break;
                    case DEC:
                        cArgs.add("static_cast<int>(" + argNames[i] + ")");
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String call = f(g.prefix + (isDecoratedRes ? "dec_" : "bar_") + incName, cArgs.toArray(new String[cArgs.size()]));
            for (String v : vars) {
                g.s(v + ";");
            }
            g.s("int exc = " + call + ";");
            switch (results[0]) {
                case INTERVAL:
                case POINT:
                    g.s(f("signal_exception", "exc") + ";");
                    if (results.length == 2) {
                        g.ret(f("std::pair<" + retType + "," + retType + ">", resNames[0], resNames[1]));
                    } else {
                        g.ret(resNames[0]);
                    }
                    break;
                case TEXT:
                    g.s("std::string " + f("s", resNames[0]) + ";");
                    g.s(f("free", resNames[0]) + ";");
                    g.s(f("signal_exception", "exc") + ";");
                    g.ret("s");
                    break;
                case STREAM:
                    g.s("std::string " + f("s", resNames[0]) + ";");
                    g.s(f("free", resNames[0]) + ";");
                    g.s(f("signal_exception", "exc") + ";");
                    g.s("os << s;");
                    g.ret("os");
                    break;
                case BOOL:
                    g.ret(f("signal_exception", "exc"));
                    break;
                case DEC:
                    g.ret(f("static_cast<decoration::decoration>", f("signal_exception", "exc")));
                    break;
                case OVERLAP:
                    g.ret(f("static_cast<overlapping::overlapping_state>", f("signal_exception", "exc")));
                    break;
                default:
                    throw new AssertionError();
            }
        }
    }

    static class OperationTypes {

        final Operation oper;
        final Format[] results;
        final Format[] args;
        boolean arg_dec, res_dec;

        OperationTypes(Operation oper) {
            this.oper = oper;
            results = new Format[oper.results.length];
            args = new Format[oper.args.length];
        }

        OperationTypes(OperationTypes other) {
            this.oper = other.oper;
            this.results = other.results.clone();
            this.args = other.args.clone();
            this.arg_dec = other.arg_dec;
            this.res_dec = other.res_dec;
        }

        void setDec(boolean isDecoration) {
            arg_dec = res_dec = isDecoration;
        }

        private String cName(GenP1788Base g) {
            StringBuilder sb = new StringBuilder();
            if (arg_dec == res_dec && oper.getDecPairs() != 0) {
                sb.append(oper.getName(g, arg_dec && res_dec));
            } else {
                sb.append(g.prefix + oper.opName);
            }
            sb.append('_');
            for (int i = 0; i < oper.results.length; i++) {
                switch (oper.results[i]) {
                    case INTERVAL:
                        sb.append(results[i].cCharUpper());
                        break;
                    case POINT:
                        sb.append(results[i].cCharLower());
                        break;
                    case TEXT:
                    case STREAM:
                        sb.append('c');
                        break;
                    case BOOL:
                    case DEC:
                    case OVERLAP:
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            for (int i = 0; i < oper.args.length; i++) {
                switch (oper.args[i]) {
                    case INTERVAL:
                        sb.append(args[i].cCharUpper());
                        break;
                    case POINT:
                    case POINT_ARRAY:
                        sb.append(args[i].cCharLower());
                        break;
                    case INT:
                    case DEC:
                    case LEN:
                    case RND:
                        sb.append('i');
                        break;
                    case TEXT:
                    case CS:
                        sb.append('c');
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            return sb.toString();
        }

        void genOperH(GenP1788Base g) {
            g.s();
            List<String> funArgs = new ArrayList<>();
            List<String> asserts = new ArrayList<>();
            List<String> args = new ArrayList<>();
            for (int i = 0; i < oper.results.length; i++) {
                switch (oper.results[i]) {
                    case INTERVAL:
                        funArgs.add(oper.resNames[i]);
                        asserts.add("sizeof(*(" + oper.resNames[i] + ")) == sizeof(" + results[i].cFormat(res_dec) + ")");
                        if (i == 0) {
                            args.add(results[0].tag());
                        }
                        args.add("(" + oper.resNames[i] + ")");
                        break;
                    case POINT:
                        funArgs.add(oper.resNames[i]);
                        asserts.add("sizeof(*(" + oper.resNames[i] + ")) == sizeof(" + results[i].cFormat() + ")");
                        if (i == 0) {
                            args.add(results[0].tag());
                        }
                        args.add("(" + oper.resNames[i] + ")");
                        break;
                    case TEXT:
                    case STREAM:
                        funArgs.add(oper.resNames[i]);
                        args.add("(" + oper.resNames[i] + ")");
                        break;
                    case BOOL:
                    case DEC:
                    case OVERLAP:
                        continue;
                    default:
                        throw new AssertionError();
                }
            }
            for (int i = 0; i < oper.args.length; i++) {
                switch (oper.args[i]) {
                    case INTERVAL:
                        funArgs.add(oper.argNames[i]);
                        asserts.add("sizeof(*(" + oper.argNames[i] + ")) == sizeof(" + this.args[i].cFormat(arg_dec) + ")");
                        args.add(this.args[i].tag());
                        args.add("(" + oper.argNames[i] + ")");
                        break;
                    case POINT:
                        funArgs.add(oper.argNames[i]);
                        asserts.add("sizeof(*(" + oper.argNames[i] + ")) == sizeof(" + this.args[i].cFormat() + ")");
                        args.add(this.args[i].tag());
                        args.add("(" + oper.argNames[i] + ")");
                        break;
                    case TEXT:
                    case CS:
                    case DEC:
                    case LEN:
                    case POINT_ARRAY:
                    case RND:
                        funArgs.add(oper.argNames[i]);
                        args.add("(" + oper.argNames[i] + ")");
                        break;
                    case INT:
                        funArgs.add(oper.argNames[i]);
                        args.add("*(" + oper.argNames[i] + ")");
                        break;
                    default:
                        throw new AssertionError();
                }
            }
            String macro = f(cName(g), funArgs.toArray(new String[funArgs.size()]));
            String assertArg = "";
            for (String a : asserts) {
                if (!assertArg.isEmpty()) {
                    assertArg += " && ";
                }
                assertArg += a;
            }
            if (assertArg.isEmpty()) {
                assertArg = "1";
            }
            String call = f(g.prefix + (oper.getDecPairs() == 0 ? "" : res_dec ? "dec_" : "bar_") + oper.incName, args.toArray(new String[args.size()]));
            g.s("#define " + macro + " \\");
            g.s("  (" + f("assert", assertArg) + ", \\");
            g.s("   " + call + ")");
        }
    }
}
