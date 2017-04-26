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
package net.java.jinterval.ucbtest;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.math.BigInteger;
import java.math.RoundingMode;
import java.nio.charset.Charset;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import net.java.jinterval.rational.*;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.compressors.gzip.GzipCompressorInputStream;
import org.gnu.mpfr.ExtendedRationalContextMPFR;

/**
 *
 */
public class UcbTest {

    private static final String path = "ucb/ucblib/";
    private static final Charset utf8 = Charset.forName("UTF-8");

    private static Map<String, byte[]> readTgz(File file, Set<String> entryNames) throws IOException {
        System.out.println(System.getProperty("user.dir"));
        InputStream input = new FileInputStream(file); // can only read the compressed bytes  
        input = new GzipCompressorInputStream(input); // can read the uncompressed bytes  
        TarArchiveInputStream tar = new TarArchiveInputStream(input); // can now read the TAR contents
        Map<String, byte[]> result = new HashMap<String, byte[]>();
        TarArchiveEntry entry;
        while ((entry = (TarArchiveEntry) tar.getNextEntry()) != null) {
            String entryName = entry.getName();
            if (entryNames.contains(entryName)) {
                byte[] bytes = new byte[(int) entry.getSize()];
                int len = tar.read(bytes);
                assert len == entry.getSize();
                result.put(entryName, bytes);
            }
        }
        tar.close();
        return result;
    }

    private static ExtendedRational eval(ExtendedRationalContext rc, String name, ExtendedRational x, ExtendedRational y) {
        try {
            ExtendedRational r;
            if (name.startsWith("sqrt")) {
                r = rc.sqrt(x);
            } else if (name.startsWith("hypot")) {
                r = rc.hypot(x, y);
            } else if (name.startsWith("pow")) {
                r = rc.pow(x, y);
            } else if (name.startsWith("exp")) {
                r = rc.exp(x);
            } else if (name.startsWith("log10")) {
                r = rc.log10(x);
            } else if (name.startsWith("log")) {
                r = rc.log(x);
            } else if (name.startsWith("sinh")) {
                r = rc.sinh(x);
            } else if (name.startsWith("cosh")) {
                r = rc.cosh(x);
            } else if (name.startsWith("tanh")) {
                r = rc.tanh(x);
            } else if (name.startsWith("asinh")) {
                r = rc.asinh(x);
            } else if (name.startsWith("acosh")) {
                r = rc.acosh(x);
            } else if (name.startsWith("atanh")) {
                r = rc.atanh(x);
            } else if (name.startsWith("sin")) {
                r = rc.sin(x);
            } else if (name.startsWith("cos")) {
                r = rc.cos(x);
            } else if (name.startsWith("tan")) {
                r = rc.tan(x);
            } else if (name.startsWith("asin")) {
                r = rc.asin(x);
            } else if (name.startsWith("acos")) {
                r = rc.acos(x);
            } else if (name.startsWith("atan2")) {
                r = rc.atan2(x, y);
            } else if (name.startsWith("atan")) {
                r = rc.atan(x);
            } else {
                throw new AssertionError();
            }
            return r;
        } catch (DomainException e) {
            return null;
        }

    }

    private static void showTest(String name, byte[] bytes) {
        char fmt = name.charAt(name.length() - 1);
        boolean binary = name.startsWith("hypot") || name.startsWith("pow") || name.startsWith("atan2");
        BinaryValueSet valueSet;
        switch (fmt) {
            case 's':
                valueSet = BinaryValueSet.BINARY32;
                break;
            case 'd':
                valueSet = BinaryValueSet.BINARY64;
                break;
            case 'q':
                valueSet = BinaryValueSet.BINARY128;
                break;
            default:
                throw new AssertionError();
        }
        for (String s : new String(bytes, utf8).split("\\n")) {
            if (s.startsWith(name)) {
                System.out.println("  " + s);
                String[] ss = s.split(" +");
                assert ss[0].equals(name);
                assert ss[1].length() == 1;
                char rndC = ss[1].charAt(0);
                ExtendedRational x;
                ExtendedRational y;
                switch (fmt) {
                    case 's':
                        assert ss.length == (binary ? 7 : 6);
                        x = parseFloat(ss[4]);
                        y = binary ? parseFloat(ss[5]) : null;
                        break;
                    case 'd':
                        assert ss.length == (binary ? 10 : 8);
                        x = parseDouble(ss[4], ss[5]);
                        y = binary ? parseDouble(ss[6], ss[7]) : null;
                        break;
                    case 'q':
                        assert ss.length == (binary ? 16 : 12);
                        x = parseQuad(ss[4], ss[5], ss[6], ss[7]);
                        y = binary ? parseQuad(ss[8], ss[9], ss[10], ss[11]) : null;
                        break;
                    default:
                        throw new AssertionError();
                }
                if (x == null) {
                    continue;
                }
                if (binary && y == null) {
                    continue;
                }
                RoundingMode rm;
                switch (rndC) {
                    case 'n':
                        rm = RoundingMode.HALF_EVEN;
                        break;
                    case 'z':
                        rm = RoundingMode.DOWN;
                        break;
                    case 'p':
                        rm = RoundingMode.CEILING;
                        break;
                    case 'm':
                        rm = RoundingMode.FLOOR;
                        break;
                    default:
                        throw new AssertionError();
                }
                RationalContextBinary rc0 = new RationalContextBinary(valueSet.getMathContext(rm));
                ExtendedRationalContextMPFR rc = new ExtendedRationalContextMPFR(valueSet, rm);
                ExtendedRational r = eval(rc0, name, x, y);
                ExtendedRational mr = eval(rc, name, x, y);
                if (r == null) {
                    if (mr != null) {
                        System.out.println("mr="+mr);
                        throw new AssertionError();
                    }
                    continue;
                }
                System.out.println(name + " " + x.doubleValue() + " " + (mr != null ? mr.doubleValue() : "NaN"));
                if (r.ne(mr)) {
                    System.out.println(name + " x=" + x + " " + x.doubleValue() + " rnd=" + rndC + " r=" + r + " " + r.doubleValue() + " r2=" + mr + " " + mr.doubleValue());
                    rc0.tanh(x);
                    rc.tanh(x);
                }
            }
        }

    }

    private static void showTests(String[] testNames) {
        File file = new File("ucbtest.tgz");
        Set<String> entryNames = new HashSet<String>();
        for (String test : testNames) {
            entryNames.add(path + test + ".input");
        }
        Map<String, byte[]> entries = null;
        try {
            entries = readTgz(file, entryNames);
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        showTest("sqrts", entries.get(path + "sqrts" + ".input"));
        showTest("sqrtd", entries.get(path + "sqrtd" + ".input"));
        showTest("sqrtq", entries.get(path + "sqrtq" + ".input"));
        showTest("hypots", entries.get(path + "hypots" + ".input"));
        showTest("hypotd", entries.get(path + "hypotd" + ".input"));
        showTest("hypotq", entries.get(path + "hypotq" + ".input"));
        showTest("pows", entries.get(path + "pows" + ".input"));
        showTest("powd", entries.get(path + "powd" + ".input"));
        showTest("powq", entries.get(path + "powq" + ".input"));
        showTest("exps", entries.get(path + "exps" + ".input"));
        showTest("expd", entries.get(path + "expd" + ".input"));
        showTest("expq", entries.get(path + "expq" + ".input"));
        showTest("logs", entries.get(path + "logs" + ".input"));
        showTest("logd", entries.get(path + "logd" + ".input"));
        showTest("logq", entries.get(path + "logq" + ".input"));
        showTest("log10s", entries.get(path + "log10s" + ".input"));
        showTest("log10d", entries.get(path + "log10d" + ".input"));
        showTest("log10q", entries.get(path + "log10q" + ".input"));
        showTest("sins", entries.get(path + "sins" + ".input"));
        showTest("sind", entries.get(path + "sind" + ".input"));
        showTest("sinq", entries.get(path + "sinq" + ".input"));
        showTest("coss", entries.get(path + "coss" + ".input"));
        showTest("cosd", entries.get(path + "cosd" + ".input"));
        showTest("cosq", entries.get(path + "cosq" + ".input"));
        showTest("tans", entries.get(path + "tans" + ".input"));
        showTest("tand", entries.get(path + "tand" + ".input"));
        showTest("tanq", entries.get(path + "tanq" + ".input"));
        showTest("asins", entries.get(path + "asins" + ".input"));
        showTest("asind", entries.get(path + "asind" + ".input"));
        showTest("asinq", entries.get(path + "asinq" + ".input"));
        showTest("acoss", entries.get(path + "acoss" + ".input"));
        showTest("acosd", entries.get(path + "acosd" + ".input"));
        showTest("acosq", entries.get(path + "acosq" + ".input"));
        showTest("atans", entries.get(path + "atans" + ".input"));
        showTest("atand", entries.get(path + "atand" + ".input"));
        showTest("atanq", entries.get(path + "atanq" + ".input"));
        showTest("atan2s", entries.get(path + "atan2s" + ".input"));
        showTest("atan2d", entries.get(path + "atan2d" + ".input"));
        showTest("atan2q", entries.get(path + "atan2q" + ".input"));
        showTest("sinhs", entries.get(path + "sinhs" + ".input"));
        showTest("sinhd", entries.get(path + "sinhd" + ".input"));
        showTest("sinhq", entries.get(path + "sinhq" + ".input"));
        showTest("coshs", entries.get(path + "coshs" + ".input"));
        showTest("coshd", entries.get(path + "coshd" + ".input"));
        showTest("coshq", entries.get(path + "coshq" + ".input"));
        showTest("tanhs", entries.get(path + "tanhs" + ".input"));
        showTest("tanhd", entries.get(path + "tanhd" + ".input"));
        showTest("tanhq", entries.get(path + "tanhq" + ".input"));
    }

    private static ExtendedRational parseFloat(String s1) {
        long bits = Long.valueOf(s1, 16);
        BigInteger bibits = BigInteger.valueOf(bits);
        ExtendedRational r = BinaryValueSet.fromBinary(32, bibits);
        float f = Float.intBitsToFloat((int) bits);
        if (Float.isNaN(f)) {
            assert r == null;
        } else {
            assert ExtendedRational.valueOf(f).eq(r);
        }
        return r;
    }

    private static ExtendedRational parseDouble(String s1, String s2) {
        long bits1 = Long.valueOf(s1, 16);
        long bits2 = Long.valueOf(s2, 16);
        BigInteger bibits = BigInteger.valueOf(bits1);
        bibits = bibits.shiftLeft(32).or(BigInteger.valueOf(bits2));
        ExtendedRational r = BinaryValueSet.fromBinary(64, bibits);
        double d = Double.longBitsToDouble((bits1 << 32) | bits2);
        if (Double.isNaN(d)) {
            assert r == null;
        } else {
            assert ExtendedRational.valueOf(d).eq(r);
        }
        return r;
    }

    private static ExtendedRational parseQuad(String s1, String s2, String s3, String s4) {
        BigInteger bits = BigInteger.valueOf(Long.valueOf(s1, 16));
        bits = bits.shiftLeft(32).or(BigInteger.valueOf(Long.valueOf(s2, 16)));
        bits = bits.shiftLeft(32).or(BigInteger.valueOf(Long.valueOf(s3, 16)));
        bits = bits.shiftLeft(32).or(BigInteger.valueOf(Long.valueOf(s4, 16)));
        return BinaryValueSet.fromBinary(128, bits);
    }

    /**
     * wget www.netlib.org/fp/ucbtest.tgz
     */
    public static void main(String[] args) {
//        testMPFR();
        String[] tests = {
            "sqrts", "sqrtd", "sqrtq",
            "hypots", "hypotd", "hypotq",
            "pows", "powd", "powq",
            "exps", "expd", "expq",
            "logs", "logd", "logq",
            "log10s", "log10d", "log10q",
            "sins", "sind", "sinq",
            "coss", "cosd", "cosq",
            "tans", "tand", "tanq",
            "asins", "asind", "asinq",
            "acoss", "acosd", "acosq",
            "atans", "atand", "atanq",
            "atan2s", "atan2d", "atan2q",
            "sinhs", "sinhd", "sinhq",
            "coshs", "coshd", "coshq",
            "tanhs", "tanhd", "tanhq",};
        showTests(tests);
    }
}
