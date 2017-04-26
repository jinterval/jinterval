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
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;
import net.java.jinterval.rational.RationalOps;

/**
 * для плоскости i (точнее A(i,:)x=b(i)) вычисляем точку привязки xi и переходим
 * от исходных координат (x) к внутренним координатам (y) плоскости i
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 */
public class ChangeVariable extends MatlabOps {

    private static final ExtendedRationalContext rc = ExtendedRationalContexts.exact();

    public static class Result {

        public final RationalVector xi;
        public final RationalMatrix At;
        public final RationalVector bt;
        public final RationalVector y1;
        public final RationalVector y2;

        public Result(RationalVector xi, RationalMatrix At, RationalVector bt, RationalVector y1, RationalVector y2) {
            this.xi = xi;
            this.At = At;
            this.bt = bt;
            this.y1 = y1;
            this.y2 = y2;
        }
    }

    public static Result apply(RationalMatrix A, RationalVector b, int i) {
        // xi - точка привязки плоскости i
        RationalVector Ai = A.getRowVector(i);
        RationalVector xi = mul(rc, Ai, (Rational) rc.div(b.getEntry(i), dot(rc, Ai, Ai)));

        // выбор внутренних ортов y1 и y2

        // y1 - наиболее длинную проекция вектора A(i,:) на коорд плоскость
        // повернем в этой плоскости на 90 градусов (направление не важно)
        int l = 0;
        for (int j = 1; j < Ai.getDimension(); j++) {
            if (ExtendedRationalOps.abs(Ai.getEntry(j)).lt(ExtendedRationalOps.abs(Ai.getEntry(l)))) {
                l = j;
            }
        }
        // в координатной плоскости ~l проекция вектора A(i,:)
        // наиболее длинная

        int l1 = (l + 1) % 3;
        int l2 = (l + 2) % 3;
        RationalVector y1 = zeros(3);
        y1.setEntry(l1, Ai.getEntry(l2));
        y1.setEntry(l2, ExtendedRationalOps.neg(Ai.getEntry(l1)));

        // y2 - векторное произведение A(i,:) на y1
        RationalVector y2 = cross(rc, Ai, y1);
        A = deleteRow(A, i);
        b = deleteElem(b, i);
        RationalMatrix At = concatHor(mul(rc, A, y1), mul(rc, A, y2));
        RationalVector bt = sub(rc, b, mul(rc, A, xi));

        // пересчет матрицы и правой части 
        // -  переход от (A,b) к (At,bt)
        return new Result(xi, At, bt, y1, y2);
    }
}
