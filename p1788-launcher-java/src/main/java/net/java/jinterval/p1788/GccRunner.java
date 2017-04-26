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

import com.sun.jna.Platform;
import java.io.*;

/**
 *
 */
public class GccRunner {

    private final boolean is64 = Platform.is64Bit();
    private final File dir;
    String testName = "testDemo.dat";
//    String testName = "testAdd.dat";
//    String testName = "testFilibArith.dat";
//    String testName = "testFilibElemFun.dat";
//    String testName = "testUnaryRev.dat";
//    String testName = "testPownRev.dat";
//    String testName = "testBinaryRev.dat";
//    String testName = "testTextToIntervalBadSyntax.dat";
//    String testName = "testTextToIntervalSloppy.dat";
//    String testName = "testTextToInterval.dat";
//    String testName = "testIntervalToText.dat";
//    String testName = "testIntegerFuns.dat";
//    String testName = "libieeep1788_integration_bool.dat";
//    String testName = "libieeep1788_integration_cancel.dat";
//    String testName = "libieeep1788_integration_class.dat";
//    String testName = "libieeep1788_integration_elem.dat";
//    String testName = "libieeep1788_integration_io.dat";
//    String testName = "libieeep1788_integration_num.dat";
//    String testName = "libieeep1788_integration_mul_rev_to_pair.dat";
//    String testName = "libieeep1788_integration_rec_bool.dat";
//    String testName = "libieeep1788_integration_rec_overlap.dat";
//    String testName = "libieeep1788_integration_rev.dat";
//    String testName = "libieeep1788_integration_set_op.dat";
//    String testName = "libieeep1788_unit_bool_func.dat";
//    String testName = "libieeep1788_unit_cancel_func.dat";
//    String testName = "libieeep1788_unit_class.dat";
//    String testName = "libieeep1788_unit_elem_func.dat";
//    String testName = "libieeep1788_unit_io.dat";
//    String testName = "libieeep1788_unit_mul_rev_to_pair_func.dat";
//    String testName = "libieeep1788_unit_num_func.dat";
//    String testName = "libieeep1788_unit_rec_bool_func.dat";
//    String testName = "libieeep1788_unit_rec_overlap.dat";
//    String testName = "libieeep1788_unit_rev_func.dat";
//    String testName = "libieeep1788_unit_set_op.dat";
//    String testName = "mascarenhas/testPowRev1Walter.dat";
//    String testName = "mascarenhas/testAtan2Rev1Walter.dat";
//    String testName = "mascarenhas/testAtan2Rev2Walter.dat";
    private final static String[] testNames = {
        "testDemo.dat",
        "testAdd.dat",
        "testFilibArith.dat",
        "testFilibElemFun.dat",
        "testUnaryRev.dat",
        "testPownRev.dat",
        "testBinaryRev.dat",
        "testTextToIntervalBadSyntax.dat",
        "testTextToIntervalSloppy.dat",
        "testTextToInterval.dat",
        "testIntervalToText.dat",
        "testIntegerFuns.dat",
        "libieeep1788_integration_bool.dat",
        "libieeep1788_integration_cancel.dat",
        "libieeep1788_integration_class.dat",
        "libieeep1788_integration_elem.dat",
        "libieeep1788_integration_io.dat",
        "libieeep1788_integration_num.dat",
        "libieeep1788_integration_mul_rev_to_pair.dat",
        "libieeep1788_integration_rec_bool.dat",
        "libieeep1788_integration_rec_overlap.dat",
        "libieeep1788_integration_rev.dat",
        "libieeep1788_integration_set_op.dat",
        "libieeep1788_unit_bool_func.dat",
        "libieeep1788_unit_cancel_func.dat",
        "libieeep1788_unit_class.dat",
        "libieeep1788_unit_elem_func.dat",
        "libieeep1788_unit_io.dat",
        "libieeep1788_unit_mul_rev_to_pair_func.dat",
        "libieeep1788_unit_num_func.dat",
        "libieeep1788_unit_rec_bool_func.dat",
        "libieeep1788_unit_rec_overlap.dat",
        "libieeep1788_unit_rev_func.dat",
        "libieeep1788_unit_set_op.dat",
        "mascarenhas/testPowRev1Walter.dat",
        "mascarenhas/testAtan2Rev1Walter.dat",
        "mascarenhas/testAtan2Rev2Walter.dat"
    };

    public static void main(String[] args) {
        File dir = new File(System.getProperty("user.dir"));
        new File(dir, "mascarenhas").mkdir();
        GccRunner runner = new GccRunner(dir);
        try {
            for (String testName : testNames) {
                runner.copyFile("dat/" + testName, testName);
            }
            // testName
//            runner.compileFilib(runner.testName);
//            runner.compileProfil(runner.testName);
//            runner.compileCXSC(runner.testName);
//            runner.compileBoost(runner.testName);
//            runner.compileMPFI(runner.testName);
//            runner.compileJInterval(runner.testName);
//            runner.compileJIntervalGmp(runner.testName);
//            runner.compileP1788(runner.testName);
//            runner.compileMPFIP1788(runner.testName);
//            runner.compileLibIEEI1788(runner.testName);
//            runner.compileLibMoore(runner.testName);
//            runner.compileLibMooreDec(runner.testName);
//            runner.compileLibDecMoore(runner.testName);
            // testNames
//            runner.compileFilib(testNames);
//            runner.compileProfil(testNames);
//            runner.compileCXSC(testNames);
//            runner.compileBoost(testNames);
//            runner.compileMPFI(testNames);
//            runner.compileJInterval(testNames);
//            runner.compileJIntervalGmp(testNames);
//            runner.compileP1788(testNames);
//            runner.compileMPFIP1788(testNames);
//            runner.compileLibIEEI1788(testNames);
//           runner.compileLibMoore(testNames);
//            runner.compileLibMooreDec(testNames);
            runner.compileLibDecMoore(testNames);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            return;
        }
    }

    private GccRunner(File dir) {
        this.dir = dir;
    }

    private void copyFile(String filename) throws IOException {
        copyFile(filename, filename);
    }

    private void copyFile(String inpFilename, String outFilename) throws IOException {
        InputStream inp = getClass().getResourceAsStream(inpFilename);
        File file = new File(dir, outFilename);
        OutputStream out = new FileOutputStream(file);
        byte[] buf = new byte[4096];
        int len = 0;
        while ((len = inp.read(buf)) > 0) {
            out.write(buf, 0, len);
        }
        out.close();
        inp.close();
    }

    private void compileFilib(String... testNames) throws IOException, InterruptedException {
        File filibDir = new File(System.getProperty("user.home") + "/local/filib-3.0.2");
        copyFile("testFilib.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "g++",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-I" + filibDir + "/include",
                "-L" + filibDir + "/lib",
                "-lprim",
                "-o", "libtestFilib.so",
                "testFilib.cpp"
        );
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-l" + filibDir + "/lib/libprim.so",
                "-l" + dir + "/libtestFilib.so",
                "-ptest_filib_",
                "-rnan",
                "-b",
                //                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileProfil(String... testNames) throws IOException, InterruptedException {
        File profilDir = new File(System.getProperty("user.home") + "/dist/interval/Profil-2.0.8");
        copyFile("testProfil.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "g++",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-I" + profilDir + "/include",
                "-o", "libtestProfil.so",
                "testProfil.cpp",
                profilDir + "/lib/libBias.a");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-l" + dir + "/libtestProfil.so",
                "-ptest_profil_",
                "-rnan",
                "-b",
                new File(dir, testName).toString()});
        }
    }

    private void compileCXSC(String... testNames) throws IOException, InterruptedException {
        File cxscDir = new File(System.getProperty("user.home") + "/local/cxsc-2-5-4");
        copyFile("testCXSC.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "g++",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-I" + cxscDir + "/include",
                "-o", "libtestCXSC.so",
                "testCXSC.cpp");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-l" + cxscDir + "/lib/libcxsc.so",
                "-l" + dir + "/libtestCXSC.so",
                "-ptest_cxsc_",
                "-rnan",
                "-b",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileBoost(String... testNames) throws IOException, InterruptedException {
        copyFile("testBoost.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "g++",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-fpermissive",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "libtestBoost.so",
                "testBoost.cpp");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-l" + dir + "/libtestBoost.so",
                "-ptest_boost_",
                "-rnan",
                "-b",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileMPFI(String... testNames) throws IOException, InterruptedException {
        copyFile("testMPFI.c");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "gcc",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "libtestMPFI.so",
                "testMPFI.c");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-lmpfi",
                "-l" + dir + "/libtestMPFI.so",
                "-ptest_mpfi_",
                "-rnan",
                "-b",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileJInterval(String... testNames) throws IOException, InterruptedException {
        if (!is64) {
            System.out.println("Only 64-bit");
            return;
        }
        copyFile("COPYING.LIB");
        copyFile("longlong.h");
        copyFile("pow2-table.h");
        copyFile("pow5-table.h");
        copyFile("jinterval.h");
        copyFile("textToInterval.c");
        copyFile("integerFuns.c");
        copyFile("testJInterval.c");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);

        pb.command(
                "gcc",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "libtextToInterval.so",
                "textToInterval.c");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }

        pb.command(
                "gcc",
                is64 ? "-m64" : "-m32",
                "-c",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "integerFuns.o",
                "integerFuns.c");
        System.out.println(pb.command());
        pwdProc = pb.start();
        exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }

        pb.command(
                "gcc",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "libtestJInterval.so",
                "integerFuns.o",
                "testJInterval.c");
        System.out.println(pb.command());
        pwdProc = pb.start();
        exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-l" + dir + "/libtextToInterval.so",
                "-l" + dir + "/libtestJInterval.so",
                "-ptest_jinterval_",
                "-rnan",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileJIntervalGmp(String... testNames) throws IOException, InterruptedException {
        copyFile("COPYING.LIB");
        copyFile("jinterval.h");
        copyFile("p1788_textToInterval.inc.c");
        copyFile("textToIntervalGmp.c");
        copyFile("testJIntervalGmp.c");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "gcc",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "libtextToIntervalGmp.so",
                "textToIntervalGmp.c");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        pb.command(
                "gcc",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "libtestJIntervalGmp.so",
                "testJIntervalGmp.c");
        System.out.println(pb.command());
        pwdProc = pb.start();
        exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-lgmp",
                "-l" + dir + "/libtextToIntervalGmp.so",
                "-l" + dir + "/libtestJIntervalGmp.so",
                "-ptest_jintervalgmp_",
                "-rstd",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileP1788(String... testNames) throws IOException, InterruptedException {
        File mpfiDir = new File(System.getProperty("user.home") + "/local/mpfi-1.5.1");
        copyFile("COPYING.LIB");
        copyFile("p1788_textToInterval.inc.c");
        copyFile("p1788_reduction.inc.c");
        copyFile("mpfr_ext.inc.c");
        copyFile("mpfi_p1788.h");
        copyFile("mpfi_p1788.c");
        copyFile("p1788.h");
        copyFile("p1788.c");
        copyFile("p1788_oper.h");
        copyFile("testP1788.c");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "gcc",
                is64 ? "-m64" : "-m32",
                "-c",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-I" + mpfiDir + "/include",
                "-o", "mpfi_p1788.o",
                "mpfi_p1788.c");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        pb.command(
                "gcc",
                is64 ? "-m64" : "-m32",
                "-c",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "p1788.o",
                "p1788.c");
        System.out.println(pb.command());
        pwdProc = pb.start();
        exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        pb.command(
                "gcc",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-o", "libtestP1788.so",
                "-L", mpfiDir + "/lib",
                "-lmpfi",
                "mpfi_p1788.o",
                "p1788.o",
                "testP1788.c");
        System.out.println(pb.command());
        pwdProc = pb.start();
        exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-l" + mpfiDir + "/lib/libmpfi.so",
                "-ltestP1788",
                "-ptest_p1788_",
                "-rnan",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileMPFIP1788(String... testNames) throws IOException, InterruptedException {
        File mpfiDir = new File(System.getProperty("user.home") + "/local/mpfi-1.5.1");
        copyFile("p1788_textToInterval.inc.c");
        copyFile("mpfr_ext.inc.c");
        copyFile("mpfi_p1788.h");
        copyFile("mpfi_p1788.c");
        copyFile("testMPFIP1788.c");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "gcc",
                is64 ? "-m64" : "-m32",
                "-c",
                "-frounding-math",
                "-fPIC",
                "-O2",
                "-I" + mpfiDir + "/include",
                "-o", "mpfi_p1788.o",
                "mpfi_p1788.c");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        pb.command(
                "gcc",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-frounding-math",
                "-fPIC",
                "-I" + mpfiDir + "/include",
                "-o", "libtestMPFIP1788.so",
                "mpfi_p1788.o",
                "testMPFIP1788.c");
        System.out.println(pb.command());
        pwdProc = pb.start();
        exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-l" + mpfiDir + "/lib/libmpfi.so",
                "-ltestMPFIP1788",
                "-ptest_mpfi_p1788_",
                "-rnan",
                "-b",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileLibIEEI1788(String... testNames) throws IOException, InterruptedException {
        File libieee1788Dir = new File(System.getProperty("user.home") + "/local");
        copyFile("testLibIEEE1788.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "g++",
                "-shared",
                is64 ? "-m64" : "-m32",
                "--std=c++11",
                "-fPIC",
                //                "-O2",
                "-I" + libieee1788Dir + "/include",
                "-o", "libtestieee1788.so",
                "testLibIEEE1788.cpp");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                "-lgmp",
                "-lmpfr",
                "-ltestieee1788",
                "-ptest_libieee1788_",
                "-rnan",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileLibMoore(String... testNames) throws IOException, InterruptedException {
        File mooreDir = new File(System.getProperty("user.home") + "/dist/interval/libmoore");
        copyFile("testLibMoore.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "g++-6",
                "-std=c++1z",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-pipe",
                "-fconcepts",
                "-frounding-math",
                "-mfpmath=sse",
                "-msse2",
                "-fsignaling-nans",
                "-Wall",
                "-W",
                "-fPIC",
                "-I" + mooreDir + "/include",
                "-o", "libtestmoore.so",
                "testLibMoore.cpp",
                "-Wl,--whole-archive",
                mooreDir + "/lib/libmoore.a",
                "-Wl,--no-whole-archive");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                //                "-lgmp",
                "-lmpfr",
                "-ltestmoore",
                "-ptest_moore_",
                "-rneg",
                "-b",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileLibMooreDec(String... testNames) throws IOException, InterruptedException {
        File mooreDir = new File(System.getProperty("user.home") + "/dist/interval/libmoore");
        copyFile("testLibMooreDec.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
        pb.command(
                "g++-6",
                "-std=c++1z",
                "-shared",
                is64 ? "-m64" : "-m32",
                "-pipe",
                "-fconcepts",
                "-frounding-math",
                "-mfpmath=sse",
                "-msse2",
                "-fsignaling-nans",
                "-Wall",
                "-W",
                "-fPIC",
                "-I" + mooreDir + "/include",
                "-o", "libtestmooredec.so",
                "testLibMooreDec.cpp",
                "-Wl,--whole-archive",
                mooreDir + "/lib/libmoore.a",
                "-Wl,--no-whole-archive");
        System.out.println(pb.command());
        Process pwdProc = pb.start();
        int exitStatus = pwdProc.waitFor();
        if (exitStatus != 0) {
            System.out.println("exitStatus=" + exitStatus);
        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                //                "-lgmp",
                "-lmpfr",
                "-ltestmooredec",
                "-ptest_moore_",
                "-rneg",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }

    private void compileLibDecMoore(String... testNames) throws IOException, InterruptedException {
        File mooreDir = new File(System.getProperty("user.home") + "/dist/interval/libmoore");
        copyFile("testLibMooreDec.cpp");
        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);
//        pb.command(
//                "g++-6",
//                "-std=c++1z",
//                "-shared",
//                is64 ? "-m64" : "-m32",
//                "-pipe",
//                "-fconcepts",
//                "-frounding-math",
//                "-mfpmath=sse",
//                "-msse2",
//                "-fsignaling-nans",
//                "-Wall",
//                "-W",
//                "-fPIC",
//                "-I" + mooreDir + "/include",
//                "-o", "libtestmooredec.so",
//                "testLibMooreDec.cpp",
//                "-Wl,--whole-archive",
//                mooreDir + "/lib/libmoore.a",
//                "-Wl,--no-whole-archive");
//        System.out.println(pb.command());
//        Process pwdProc = pb.start();
//        int exitStatus = pwdProc.waitFor();
//        if (exitStatus != 0) {
//            System.out.println("exitStatus=" + exitStatus);
//        }
        for (String testName : testNames) {
            Launcher.main(new String[]{
                //                "-lgmp",
                "-lmpfr",
                "-ldecmoore",
                "-ptest_moore_",
                "-rneg",
                "-t",
                new File(dir, testName).toString()
            });
        }
    }
}
