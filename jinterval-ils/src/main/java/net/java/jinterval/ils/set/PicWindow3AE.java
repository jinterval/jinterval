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
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.Rational;

/**
 * выбор окна отрисовки, содержащего точки - строки матрицы V (во всех матрицах
 * первый столбец - абсцисса, второй - ордината, третий - аппликата) (в ihV и W
 * первая строка - нижний конец, вторая - верхний)
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 */
public class PicWindow3AE extends MatlabOps {

    private static final ExtendedRationalContext rc = ExtendedRationalContexts.exact();

    public static RationalMatrix apply(RationalMatrix V) {
        // интервальная оболочка точек из V
        RationalVector minV = vec(
                min(V.getColumnVector(0)),
                min(V.getColumnVector(1)),
                min(V.getColumnVector(2)));
        RationalVector maxV = vec(
                max(V.getColumnVector(0)),
                max(V.getColumnVector(1)),
                max(V.getColumnVector(2)));
        RationalVector center = mul(rc, add(rc, minV, maxV), Rational.valueOf(0.5));
        RationalVector radius = mul(rc, sub(rc, maxV, minV), Rational.valueOf(0.5));
        ExtendedRational rm = max(radius);
        RationalMatrix W;
        // выбор окна отрисовки чуть шире интервальной оболочки
        // он зависит от наличия у интервальной оболочки вырожденных компонент 
        if (minV.equals(maxV)) {
            W = concatVer(
                    sub(rc, center, ones(3)),
                    add(rc, center, ones(3)));
        } else {
            W = concatVer(
                    sub(rc, center, mul(rc, ones(3), rc.mul(rm, Rational.valueOf(2)))),
                    add(rc, center, mul(rc, ones(3), rc.mul(rm, Rational.valueOf(2)))));
        }
        return W;
    }
}
