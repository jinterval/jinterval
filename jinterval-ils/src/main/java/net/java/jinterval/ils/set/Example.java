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
package net.java.jinterval.ils.set;

import net.java.jinterval.ils.MatlabOps;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.linear.RationalVector;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 *
 */
public class Example extends MatlabOps {

    private static final ExtendedRationalContext rc = ExtendedRationalContexts.exact();
    String name;
    RationalMatrix oC;
    RationalMatrix uC;
    RationalVector ud;
    RationalVector od;

    private Example() {
        initNstar();
    }

    private void initNstar() {
        name = "Nstar";
        Rational t = Rational.valueOf(4);
//        Rational t = Rational.valueOf(3.5);
        Rational t2 = RationalOps.sub(t, Rational.valueOf(2));
        uC = add(rc, mul(rc, ones(3, 3), Rational.valueOf(2)), mul(rc, eye(3), t2));
        oC = mul(rc, eye(3), t);
        ud = mul(rc, ones(3), Rational.valueOf(-1));
        od = ones(3);
    }

    public static void main(String[] args) {
        Example example = new Example();
        System.out.println("uC=\n" + example.uC);
        System.out.println("oC=\n" + example.oC);
        System.out.println("ud=\n" + example.ud);
        System.out.println("od=\n" + example.od);

        AEssR3.Result r = AEssR3.apply(example.uC, example.oC, example.ud, example.od);
    }
}
