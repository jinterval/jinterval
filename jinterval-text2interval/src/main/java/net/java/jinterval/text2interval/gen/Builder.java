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
import java.util.List;
import net.java.jinterval.text2interval.Text2interval;

/**
 *
 */
public class Builder {

    private static final String LICENSE_HEADER = "LICENSE_HEADER";
    private static final int digitBlockSize = 19;
    private static final int maxDigitBlock = 324 / 18 + 10;
    private static String[] filesToCopy = {
        "README",
        "COPYING.LIB",
        "longlong.h",
        "jinterval.h"
    };

    private static List<String> readHeaderLines() throws IOException {
        List<String> result = new ArrayList<String>();
        LineNumberReader reader = new LineNumberReader(new InputStreamReader(Builder.class.getResourceAsStream(LICENSE_HEADER), Charset.forName("UTF8")));
        String line;
        while ((line = reader.readLine()) != null) {
            result.add(line);
        }
        reader.close();
        return result;
    }
    
    private static void copyFile(File dir, String filename) throws IOException {
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

    public static void main(String[] args) {
        File dir = new File("../wrk/");
        boolean is64 = true;
        try {
            for (String fileToCopy : filesToCopy) {
                copyFile(dir, fileToCopy);
            }
            List<String> headerLines = readHeaderLines();

            new GenParse().gen(new File(dir, "textToInterval.c"), headerLines, digitBlockSize, maxDigitBlock);
            new GenPow2().gen(new File(dir, "pow2-table.h"), headerLines);
            new GenPow5().gen(new File(dir, "pow5-table.h"), headerLines);
        } catch (IOException e) {
            e.printStackTrace();
        }

        ProcessBuilder pb = new ProcessBuilder();
        pb.directory(dir);
        pb.redirectErrorStream(true);
        pb.redirectOutput(ProcessBuilder.Redirect.INHERIT);

        List<String> command = new ArrayList<String>();
        command.add("gcc");
        command.add("-std=gnu99");
        command.add("--shared");
        command.add(is64 ? "-m64" : "-m32");
        command.add("-frounding-math");
        command.add("-fPIC");
        command.add("-O2");
        command.add("textToInterval.c");
        int test = 1;
        switch (test) {
            case 1:
                command.add("-o");
                command.add("libtest.so");
                break;
        }
        pb.command(command);
        try {
            Process pwdProc = pb.start();
            int exitStatus = pwdProc.waitFor();
            if (exitStatus != 0) {
                System.out.println("exitStatus=" + exitStatus);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        new Text2interval().text2interval("[empty]");
    }
}
