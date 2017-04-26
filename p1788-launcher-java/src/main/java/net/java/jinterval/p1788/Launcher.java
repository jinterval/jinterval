/*
 * Copyright (c) 2012, JInterval Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. * Redistributions in
 * binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
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
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
package net.java.jinterval.p1788;

import java.io.IOException;
import java.math.BigInteger;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.set.IntvlPartOfNaI;
import net.java.jinterval.interval.set.InvalidOperandException;
import net.java.jinterval.interval.set.OverlapState;
import net.java.jinterval.interval.set.P1788Exception;
import net.java.jinterval.interval.set.PossiblyUndefinedOperationException;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.interval.set.UndefinedOperationException;
import net.java.jinterval.p1788.bridj.DECORATED_INFSUP_B64;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.text2interval.gen.GenP1788Base;
import org.bridj.BridJ;
import org.bridj.DynamicFunction;
import org.bridj.NativeLibrary;
import org.bridj.Platform;
import org.bridj.Pointer;
import org.bridj.ann.Convention;

/**
 *
 */
public class Launcher {

    enum Representation {
        INFSUP, INFSUPNAN, NEGINFSUPNAN;
    }
    private final Representation rep;
    private final boolean bare;
    private final boolean tightest;
    private final BinaryValueSet valueSet = BinaryValueSet.BINARY64;
    private final ExtendedRationalContext rc = ExtendedRationalContexts.mkNearest(valueSet);
    private final SetIntervalContext ic = SetIntervalContexts.getTightestSlow(valueSet);
    private final SetIntervalContext ic2 = SetIntervalContexts.decorate(SetIntervalContexts.getTightest(valueSet));
    private static final int DEC_RESULT_MASK = GenP1788Base.Operation.D_B | GenP1788Base.Operation.D_D;
    private static final String[] excNames = {
        "NONE",
        "UNDEFINED_OPERATION",
        "POSSIBLY_UNDEFINED_OPERATION",
        "INTERVAL_PART_OF_NAI",
        "EXC_INVALID_OPERAND"
    };

    private static void help() {
        System.err.println("Usage: -l<LibraryPath> ... -l<libraryPath> -p<prefix> <testFile> ... <testFile>  [-rRep] [-b]");
        System.err.println("       -rstd empty interval is represented as [+INF,-INF]");
        System.err.println("       -rnan empty interval is represented as [NAN,NAN]");
        System.err.println("       -rneg inf is negated; empty interval is represented as [NAN,NAN]");
        System.err.println("       -b bare interval library");
        System.err.println("       -t accuracy=tightest");
        System.err.println("       -h  print help message");
    }

    public static void main(String[] args) throws IOException {
        List<String> libs = new ArrayList<String>();
        List<String> testFiles = new ArrayList<String>();
        String prefix = null;
        Representation rep = Representation.INFSUP;
        boolean bare = false;
        boolean tightest = false;
        int i = 0;
        while (i < args.length) {
            String s = args[i];
            if (s.startsWith("-h")) {
                help();
                return;
            } else if (s.startsWith("-l")) {
                if (s.length() > 2) {
                    libs.add(s.substring(2));
                } else if (i + 1 < args.length) {
                    i += 1;
                    libs.add(args[i]);
                } else {
                    help();
                    return;
                }
            } else if (s.startsWith("-p")) {
                if (prefix != null) {
                    help();
                    return;
                } else if (s.length() > 2) {
                    prefix = s.substring(2);
                } else if (i + 1 < args.length) {
                    i += 1;
                    prefix = args[i];
                } else {
                    help();
                    return;
                }
            } else if (s.equals("-rstd")) {
                rep = Representation.INFSUP;
            } else if (s.equals("-rnan")) {
                rep = Representation.INFSUPNAN;
            } else if (s.equals("-rneg")) {
                rep = Representation.NEGINFSUPNAN;
            } else if (s.equals("-b")) {
                bare = true;
            } else if (s.equals("-t")) {
                tightest = true;
            } else if (s.startsWith("-")) {
                help();
                return;
            } else {
                testFiles.add(s);
            }
            i += 1;
        }

        if (libs.isEmpty()) {
            System.err.println("No library files");
            help();
            return;
        }
        if (prefix == null) {
            prefix = "";
        }
        List<NativeLibrary> allNativeLibraries = new ArrayList<>();
        BridJ.addLibraryPath(System.getProperty("user.dir"));
        for (String libName : libs) {
            NativeLibrary lib = BridJ.getNativeLibrary(libName);
            allNativeLibraries.add(lib);
        }
        NativeLibrary mainLibrary = allNativeLibraries.get(allNativeLibraries.size() - 1);

        Launcher launcher = new Launcher(rep, bare, tightest);
        for (String testFile : testFiles) {
            List<String> lines;
            try {
                lines = Files.readAllLines(Paths.get(testFile), Charset.forName("UTF-8"));
            } catch (IOException ex) {
                System.err.println("I/O error in test file " + testFile);
                continue;
            }
            System.out.println("# " + testFile);
            launcher.run(mainLibrary, prefix, lines);
        }
        return;
    }

    private Launcher(Representation rep, boolean bare, boolean tightest) {
        this.rep = rep;
        this.bare = bare;
        this.tightest = tightest;
    }

    private void run(NativeLibrary lib, String funPrefix, List<String> lines) {
        DynamicFunction<Void> setup = lib.getSymbolPointer(funPrefix + "setup")
                .asDynamicFunction(Convention.Style.CDecl, void.class);
        setup.apply();

        boolean wasWarn = false;
        int lineNo = 0;
        Operation op = null;
        DynamicFunction<Integer> function = null;
        for (String line : lines) {
//            System.out.println(line);
            lineNo += 1;
//            System.out.print(lineNo + " ");
            String s = line.trim();
            if (s.isEmpty()) {
            } else if (s.charAt(0) == '#') {
            } else if (s.charAt(0) == '*') {
                System.out.println(s);
                String name = s.substring(1).trim();
                try {
                    op = Operation.valueOf(name);
                } catch (IllegalArgumentException e) {
                    op = null;
                    function = null;
                    System.out.println("Unknown Operation \"" + name + "\" in line " + lineNo + " : " + s);
                    wasWarn = true;
                }
                if (op != null) {
                    Pointer<?> symbolPointer = lib.getSymbolPointer(funPrefix + name);
                    if (symbolPointer != null) {
                        function = lib.getSymbolPointer(funPrefix + name)
                                .asDynamicFunction(Convention.Style.CDecl, int.class, op.getParameters());
                    } else {
                        System.out.println("Library has no Operation \"" + name + "\" in line " + lineNo + " : " + s);
                        op = null;
                        function = null;
                        wasWarn = true;
                    }
                }
            } else if (op == null) {
                if (!wasWarn) {
                    System.out.println("Operation was not specified before the line " + lineNo + " : " + s);
                    wasWarn = true;
                }
            } else {
                try {
                    Object[] argsJ = parseLine(s.split("[|]"), op);
                    testLine(line, argsJ, op, function);
                } catch (NumberFormatException e) {
                    System.out.println(" Bad number format in line " + lineNo + ": " + s);
                } catch (Exception e) {
                    System.out.println(" Checker FAILURE in line " + lineNo);
                    e.printStackTrace();
                }
            }
        }
    }

    private Object[] parseLine(String[] ss, Operation op) {
        GenP1788Base.Operation oper = op.getBaseOperation();
        int nArg = oper.args.length;
        if (ss.length != nArg) {
            throw new NumberFormatException();
        }
        Object[] argsJ = new Object[nArg];
        for (int i = 0; i < nArg; i++) {
            String s = ss[i].trim();
            switch (oper.args[i]) {
                case INTERVAL:
                    argsJ[i] = parseInterval(s);
                    break;
                case POINT:
                    if (!s.toUpperCase().contains("NAN")) {
                        argsJ[i] = ExtendedRational.valueOf(s);
                    }
                    break;
                case INT:
                    argsJ[i] = new BigInteger(s);
                    break;
                case DEC:
                    if (!s.equals("(null)")) {
                        argsJ[i] = Decoration.valueOf(s.toUpperCase());
                    } else {
                        argsJ[i] = Decoration.ILL;
                    }
                    break;
                case TEXT:
                    if (s.length() < 2 || s.charAt(0) != '"' || s.charAt(s.length() - 1) != '"') {
                        throw new NumberFormatException();
                    }
                    argsJ[i] = s.substring(1, s.length() - 1);
                    break;
                default:
                    throw new AssertionError(oper.args[i].name());
            }
        }
        return argsJ;
    }

    private void testLine(String line, Object[] argsJ, Operation op, DynamicFunction<Integer> function) {
        GenP1788Base.Operation oper = op.getBaseOperation();
        int nArg = oper.args.length;
        int nRes = oper.results.length;
        argsJ = argsJ.clone();
        Object[] bloatedArgsJ = argsJ.clone();
        for (int i = 0; i < nArg; i++) {
            switch (oper.args[i]) {
                case INTERVAL:
                    SetInterval iArg = (SetInterval) argsJ[i];
                    if (bare) {
                        iArg = ic.newDec(iArg);
                    }
                    argsJ[i] = ic.hull(iArg);
                    bloatedArgsJ[i] = nextOut(iArg);
                    break;
                case POINT:
                    ExtendedRational pArg = (ExtendedRational) argsJ[i];
                    if (pArg != null) {
                        // not NaN
                        bloatedArgsJ[i] = argsJ[i] = rc.rnd(pArg);
                    }
                    break;
                case POINT_ARRAY:
                    throw new UnsupportedOperationException();
            }
        }
        Object[] tightestResults = new Object[nRes];
        Object[] accurateResults = new Object[nRes];
        P1788Exception tightestException = evalJava(op, argsJ, tightestResults);
        P1788Exception accurateException = evalJava(op, bloatedArgsJ, accurateResults);
        for (int i = 0; i < nRes; i++) {
            if (accurateResults[i] instanceof SetInterval) {
                accurateResults[i] = nextOut((SetInterval) accurateResults[i]);
            }
        }
//        TestPrinter.printLine(argsJ, op, tightestResults, accurateResults);
        evalCAndCompare(line, op, argsJ, function,
                tightestResults, tightestException,
                accurateResults, accurateException);
    }

    private P1788Exception evalJava(Operation op, Object[] argsJ, Object[] resJ) {
        GenP1788Base.Operation oper = op.getBaseOperation();
        int nRes = oper.results.length;
        int nArg = oper.args.length;
        Object[] contexts = new Object[nRes];
        Object[] contexts2 = new Object[nRes];
        for (int i = 0; i < nRes; i++) {
            switch (oper.results[i]) {
                case INTERVAL: {
                    Arrays.fill(contexts, ic);
                    Arrays.fill(contexts2, ic2);
                }
                break;
                case POINT:
                case TEXT: {
                    Arrays.fill(contexts, valueSet);
                    Arrays.fill(contexts2, valueSet);
                }
                break;
                case BOOL:
                case DEC:
                case OVERLAP:
                    break;
                default:
                    throw new AssertionError(oper.results[i].name());
            }
        }
        assert resJ.length == oper.results.length;
        P1788Exception e1 = null;
        try {
            op.eval(contexts, resJ, argsJ);
        } catch (P1788Exception e) {
            resJ[0] = e.getValue();
            e1 = e;
        }
        Object[] r1a = new Object[oper.results.length];
        P1788Exception e1a = null;
        try {
            op.eval(contexts2, r1a, argsJ);
        } catch (P1788Exception e) {
            r1a[0] = e.getValue();
            e1a = e;
        }
        for (int i = 0; i < nRes; i++) {
            switch (oper.results[i]) {
                case INTERVAL: {
                    SetInterval i1 = (SetInterval) resJ[i];
                    SetInterval i2 = (SetInterval) r1a[i];
                    assert i1.equals(i2);
                }
                break;
                case POINT: {
                    ExtendedRational er1 = (ExtendedRational) resJ[i];
                    ExtendedRational er2 = (ExtendedRational) r1a[i];
                    assert er1 == null && er2 == null || er1.eq(er2);
                }
                break;
                case DEC: {
                    Decoration d1 = (Decoration) resJ[i];
                    Decoration d2 = (Decoration) r1a[i];
                    assert d1 == d2;
                }
                break;
                case OVERLAP: {
                    OverlapState over1 = (OverlapState) resJ[i];
                    OverlapState over2 = (OverlapState) r1a[i];
                    assert over1 == over2;
                }
                break;
                case TEXT: {
                    String s1 = (String) resJ[i];
                    String s2 = (String) r1a[i];
                    assert s1.equals(s2);
                }
                break;
                case BOOL: {
                    boolean b1 = (Boolean) resJ[i];
                    boolean b2 = (Boolean) r1a[i];
                    assert b1 == b2;
                }
                break;
                default:
                    throw new AssertionError(oper.results[i].name());
            }
        }
        assert e1 == null && e1a == null || e1.getClass() == e1a.getClass();
        return e1;
    }

    private void evalCAndCompare(String line, Operation op, Object[] argsJ, DynamicFunction<Integer> function,
            Object[] tightestResults, P1788Exception tightestException,
            Object[] accurateResults, P1788Exception accurateException) {
        GenP1788Base.Operation oper = op.getBaseOperation();
        int nRes = oper.results.length;
        int nArg = oper.args.length;
        Pointer<?>[] argsC = new Pointer<?>[nRes + nArg];
        Object[] argsCP = new Object[nRes + nArg];
        for (int i = 0; i < nRes; i++) {
            switch (oper.results[i]) {
                case INTERVAL: {
                    Pointer<DECORATED_INFSUP_B64> p = Pointer.getPointer(new DECORATED_INFSUP_B64());
                    argsC[nArg + i] = p;
                }
                break;
                case POINT: {
                    Pointer<Double> p = Pointer.allocateDouble();
                    argsC[nArg + i] = p;
                }
                break;
                case DEC:
                case OVERLAP: {
                    Pointer<Integer> p = Pointer.allocateInt();
                    argsC[nArg + i] = p;
                }
                break;
                case TEXT: {
                    Pointer<Pointer<Byte>> p = Pointer.allocatePointer(Byte.TYPE);
                    argsC[nArg + i] = p;
                }
                break;
                case BOOL: {
                    Pointer<Integer> p = Pointer.allocateInt();
                    argsC[nArg + i] = p;
                }
                break;
                default:
                    throw new AssertionError(oper.results[i].name());
            }
        }
        for (int i = 0; i < nArg; i++) {
            switch (oper.args[i]) {
                case INTERVAL: {
                    SetInterval a = (SetInterval) argsJ[i];
                    Pointer<DECORATED_INFSUP_B64> p = Pointer.getPointer(toIntervalDouble(a, rep));
                    argsC[i] = p;
                }
                break;
                case POINT: {
                    ExtendedRational a = (ExtendedRational) argsJ[i];
                    Pointer<Double> p = Pointer.allocateDouble();
                    p.set(a != null ? a.doubleValue() : Double.NaN);
                    argsC[i] = p;
                }
                break;
                case INT: {
                    BigInteger a = (BigInteger) argsJ[i];
                    Pointer<Integer> p = Pointer.allocateInt();
                    p.set(a.intValue());
                    argsC[i] = p;
                }
                break;
                case DEC: {
                    Decoration a = (Decoration) argsJ[i];
                    Pointer<Integer> p = Pointer.allocateInt();
                    p.set(a != null ? a.ordinal() << 2 : -1);
                    argsC[i] = p;
                }
                break;
                case TEXT: {
                    String a = (String) argsJ[i];
                    Pointer<Byte> p = Pointer.pointerToCString(a);
                    argsC[i] = p;
                }
                break;
                default:
                    throw new AssertionError(oper.args[i].name());
            }
        }
        for (int i = 0; i < nRes + nArg; i++) {
            long peer = argsC[i].getPeer();
            argsCP[i] = Platform.is64Bits() ? Long.valueOf(peer) : Integer.valueOf((int) peer);
        }
        int jException;
        if (tightestException == null) {
            jException = 0;
        } else if (tightestException instanceof UndefinedOperationException) {
            jException = -1;
        } else if (tightestException instanceof PossiblyUndefinedOperationException) {
            jException = -2;
        } else if (tightestException instanceof IntvlPartOfNaI) {
            jException = -3;
        } else if (tightestException instanceof InvalidOperandException) {
            jException = -4;
        } else {
            throw new AssertionError();
        }
        int exception = function.apply(argsCP);
        if (exception != jException) {
            System.out.println(line);
            System.out.println(" Exceptions e=" + excNames[-exception] + " te=" + excNames[-jException]);
        }
        for (int i = 0; i < nRes; i++) {
            switch (oper.results[i]) {
                case INTERVAL:
                    SetInterval ti = (SetInterval) tightestResults[i];
                    SetInterval ai = (SetInterval) accurateResults[i];
                    boolean thisBare = bare || (oper.getDecPairs() & DEC_RESULT_MASK) == 0;
                    SetInterval i2 = toInterval(((Pointer<DECORATED_INFSUP_B64>) argsC[nArg + i]).get(), thisBare);
                    String msg = null;
                    if (!ti.subset(i2)) {
                        msg = " CONTAINMENT FAILURE !!! i= " + i2.toStringDecorated()
                                + " ti=" + ti.toStringDecorated();
                    } else if (!i2.subset(tightest ? ti : ai)) {
                        msg = " NOT " + (tightest ? "TIGHT" : "ACCURATE") + " ! i= " + i2 + " ti=" + ti + " ai=" + ai;
                    } else if (!thisBare && ti.getDecoration() != i2.getDecoration()) {
                        msg = " Decoration mismatch i= " + i2.toStringDecorated()
                                + " ti=" + ti.toStringDecorated();
                    }
                    if (msg != null) {
                        System.out.println(line);
                        System.out.println("!!" + i + " " + msg);
                    }
                    break;
                case POINT:
                    ExtendedRational er1 = (ExtendedRational) tightestResults[i];
                    double v2 = ((Pointer<Double>) argsC[nArg + i]).getDouble();
                    ExtendedRational er2 = Double.isNaN(v2) ? null : ExtendedRational.valueOf(v2);
                    if (er1 == null || er2 == null ? er1 != er2 : !er1.eq(er2)) {
                        System.out.println(line);
                        System.out.println(" Number mismatch v=" + er2 + " tv=" + er1);
                    }
                    break;
                case DEC:
                    Decoration dec1 = (Decoration) tightestResults[i];
                    Decoration dec2 = Decoration.values()[((Pointer<Integer>) argsC[nArg + i]).getInt() >> 2];
                    if (dec1 != dec2) {
                        System.out.println(line);
                        System.out.println(" Decoration mismatch d=" + dec2 + " td=" + dec1);
                    }
                    break;
                case OVERLAP:
                    OverlapState over1 = (OverlapState) tightestResults[i];
                    int over1mask = over1 != null ? 1 << over1.ordinal() : 0;
                    int over2mask = ((Pointer<Integer>) argsC[nArg + i]).getInt();
                    if (over1mask != over2mask) {
                        System.out.println(line);
                        System.out.println(" OverlapState mismatch = " 
                                + Integer.toHexString(over2mask) + 
                                " " + Integer.toHexString(over1mask) + " " + over1);
                    }
                    break;
                case TEXT:
                    String s1 = (String) tightestResults[i];
                    String s1p = s1.replace("[-inf,inf]", "[entire]").replace("[]", "[empty]");
                    String s2 = (String) ((Pointer<Pointer<Byte>>) argsC[nArg + i]).get().getCString();
                    String s2p = s2.replace("p+", "p").replace(".0p", "p").replace("-0x0p0", "0x0p0").replace(" ", "").replace("[]", "[empty]");
                    if (!s1p.equals(s2p)) {
                        System.out.println(line);
                        System.out.println(" Text mismatch s=\"" + s2 + "\" ts=\"" + s1 + "\"");
                    }
                    break;
                case BOOL:
                    boolean b1 = (Boolean) tightestResults[i];
                    boolean b2 = ((Pointer<Integer>) argsC[nArg + i]).getInt() != 0;
                    if (b1 != b2) {
                        System.out.println(line);
                        System.out.println(" Boolean mismatch = " + b2 + " " + b1);
                    }
                    break;
                default:
                    throw new AssertionError(oper.args[i].name());
            }
        }
    }

    private SetInterval nextOut(SetInterval x) {
        SetInterval hull = ic.hull(x);
        if (x.isEmpty()) {
            return hull;
        }
        ExtendedRational inf = valueSet.next(hull.inf(), -1);
        ExtendedRational sup = valueSet.next(hull.sup(), +1);
        Decoration dec = x.getDecoration();
        if (dec == Decoration.COM && !(inf.isFinite() && sup.isFinite())) {
            dec = Decoration.DAC;
        }
        return ic.numsDecToInterval(inf, sup, dec);
    }

    private static SetInterval parseInterval(String s) {
        Decoration dec = Decoration.COM;
        int indexOfUnder = s.indexOf('_');
        if (indexOfUnder >= 0) {
            dec = Decoration.valueOf(s.substring(indexOfUnder + 1).toUpperCase());
            s = s.substring(0, indexOfUnder);
        }
        if (s.isEmpty() || s.charAt(0) != '[' || s.charAt(s.length() - 1) != ']') {
            throw new NumberFormatException();
        }
        s = s.substring(1, s.length() - 1).trim();
        if (s.isEmpty()) {
            return SetIntervalOps.empty(dec);
        }
        int commaInd = s.indexOf(',');
        ExtendedRational inf = ExtendedRational.valueOf(s.substring(0, commaInd).trim());
        ExtendedRational sup = ExtendedRational.valueOf(s.substring(commaInd + 1).trim());
        return SetIntervalOps.nums2(inf, sup, dec);
    }

    private static DECORATED_INFSUP_B64 toIntervalDouble(SetInterval x, Representation rep) {
        DECORATED_INFSUP_B64 xd = new DECORATED_INFSUP_B64();
        if (x.isNaI()) {
            xd.inf(Double.NaN).sup(Double.NaN);
        } else if (x.isEmpty()) {
            if (rep == Representation.INFSUP) {
                xd.inf(Double.POSITIVE_INFINITY).sup(Double.NEGATIVE_INFINITY);
            } else {
                xd.inf(Double.NaN).sup(Double.NaN);
            }
        } else if (rep == Representation.NEGINFSUPNAN) {
            xd.inf(-x.doubleInf()).sup(x.doubleSup());
        } else {
            xd.inf(x.doubleInf()).sup(x.doubleSup());
        }
        xd.decoration((byte) (x.getDecoration().ordinal() << 2));
        return xd;
    }

    private SetInterval toInterval(DECORATED_INFSUP_B64 xd, boolean bare) {
        Decoration d = bare ? Decoration.COM : Decoration.values()[xd.decoration() >> 2];
        double inf = rep == Representation.NEGINFSUPNAN ? -xd.inf() : xd.inf();
        double sup = xd.sup();
        if (inf <= sup) {
            return SetIntervalOps.nums2(inf, sup, d);
        } else {
            return SetIntervalOps.empty(d);
        }
    }
}
