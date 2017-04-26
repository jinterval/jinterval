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
import java.io.PrintWriter;
import java.util.List;

/**
 *
 */
public class GenSupport {

    private final String INDENT = "    ";
    private int indent;
    private PrintWriter out;

    protected GenSupport() {
    }

    protected void create(File file, List<String> headerLines) throws IOException {
        out = new PrintWriter(file);
        for (String line : headerLines) {
            s(line);
        }
        s();
    }

    protected void close() {
        out.close();
        out = null;
    }

    protected void b() {
        indent++;
    }

    protected void s(String s) {
        for (int i = 0; i < indent; i++) {
            out.print(INDENT);
        }
        out.println(s);
    }

    protected void s() {
        out.println();
    }

    protected void e() {
        indent--;
    }

    protected void bFun(String synopsis) {
        s(synopsis + " {");
        b();
    }

    protected void endFun() {
        e();
        s("}");
    }

    protected void bWhile(String cond) {
        s("while (" + cond + ") {");
        b();
    }

    protected void endWhile() {
        e();
        s("}");
    }

    protected void doWhile() {
        s("do {");
        b();
    }

    protected void endDoWhile(String cond) {
        e();
        s("} while (" + cond + ");");
    }

    protected void bFor(String init, String cond, String next) {
        s("for (" + init + ";" + cond + ";" + next + ") {");
        b();
    }

    protected void endFor() {
        e();
        s("}");
    }

    protected void bIf(String cond) {
        s("if (" + cond + ") {");
        b();
    }

    protected void elseIf(String cond) {
        e();
        s("} else if (" + cond + ") {");
        b();
    }

    protected void elseIf() {
        e();
        s("} else {");
        b();
    }

    protected void endIf() {
        e();
        s("}");
    }

    protected void bSwitch(String expr) {
        s("switch (" + expr + ") {");
        b();
    }

    protected void endSwitch() {
        e();
        s("}");
    }

    protected void bCase(String label) {
        s("case " + label + ":");
        b();
    }

    protected void bDefault() {
        s("default:");
        b();
    }

    protected void endCase() {
        s("break;");
        e();
    }

    protected void shortIf(String cond, String then) {
        s("if (" + cond + ") " + then);
    }

    protected void retIf(String cond, String val) {
        s("if (" + cond + ") return " + val + ";");
    }

    protected void ret(String val) {
        s("return " + val + ";");
    }

    protected void breakFor() {
        s("break;");
    }

    protected static String f(String fName, String... args) {
        StringBuilder sb = new StringBuilder();
        sb.append(fName);
        sb.append('(');
        for (int i = 0; i < args.length; i++) {
            if (i > 0) {
                sb.append(", ");
            }
            sb.append(args[i]);
        }
        sb.append(')');
        return sb.toString();
    }
}
