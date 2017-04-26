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

import java.util.BitSet;
import net.java.jinterval.ils.MatlabOps;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.linear.RationalVector;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;

/**
 * внесем в список особых точек вершины множества решений системы линейных
 * неравенств A x \geq b (известно заранее, что оно лежит в одном ортанте)
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 */
public class AddV extends MatlabOps {

    private static final ExtendedRationalContext rc = ExtendedRationalContexts.exact();

    public static class Result {

        public final RationalMatrix V;
        public final int cfinite;

        public Result(RationalMatrix V, int cfinite) {
            this.V = V;
            this.cfinite = cfinite;
        }
    }

    public static Result apply(RationalMatrix V, int cfinite, RationalMatrix A, RationalVector b, int m, boolean cnmty) {

        System.out.println("======= AddV ========");
        System.out.println("A=\n" + A);
        System.out.println("b=\n" + b);

        if (!cnmty) {
            // в ортанте нет точек множества АЕ-решений
            return new Result(V, cfinite);
        }

        if (m == 0) {
            // весь ортант в множестве решений
            V = concatVer(V, concatVer(vec(0, 0, 0)));
            return new Result(V, cfinite);
        }

        for (int i = 0; i < m; i++) {
            // найдем точку привязки плоскости i (точнее A(i,:)x=b(i))
            // и перейдем от исходных координат (x) 
            // к внутренним координатам (y) плоскости i
            ChangeVariable.Result cv = ChangeVariable.apply(A, b, i);
            RationalVector xi = cv.xi;
            RationalMatrix At = cv.At;
            RationalVector bt = cv.bt;
            RationalVector y1 = cv.y1;
            RationalVector y2 = cv.y2;

            // удаление нулевых строк из At (их могут дать плоскости, параллельные i) 
            ClearZeroRows.Result cz = ClearZeroRows.apply(At, bt);
            At = cz.A;
            bt = cz.b;
            boolean cnmtyt = cz.cnmty;

            System.out.println("i=" + i);
//            System.out.println("xi=\n" + xi);
//            System.out.println("At=\n" + At);
//            System.out.println("bt=\n" + bt);
//            System.out.println("y1=\n" + y1);
//            System.out.println("y2=\n" + y2);

            if (!cnmtyt) {
                continue; // плоскость i не пересекает границу H
            }

            // найдем пересечения прямых At(k,:)y=bt(k) с границей H в координатах (y)
            // матрица St построчно составлена из таких прямолинейных участков по типу
            // [ beginy1 beginy2 endy1 endy2 k ]
            RationalMatrix St = BoundaryIntervals.apply(At, bt);

            if (St.getRowDimension() == 0) {
                continue; // плоскость i не пересекает границу H
            }

            // cоберем вершины из плоскости i в матрицу Vt
            // Из каждой вершины выходит хоть один участок, поэтому все вершины
            // перечислены в первых двух столбцах матрицы St 
            // (первый - абсцисса, второй - ордината)
            // и имеют значения из R (в координатах вершин нет -Inf, Inf, NaN).
            BitSet binf = new BitSet();
            for (int k = 0; k < St.getRowDimension(); k++) {
                boolean xbf = St.getEntry(k, 0).isFinite();
                boolean ybf = St.getEntry(k, 1).isFinite();
                // неравенства St(binf,5) дают участки границы 
                // с началом в бесконечности
                binf.set(k, !xbf || !ybf);
            }
            
            RationalMatrix Vtt = zeros(St.getRowDimension() - binf.cardinality(), 3);
            int kk = 0;
            for (int k = 0; k < St.getRowDimension(); k++) {
                if (binf.get(k)) {
                    continue;
                }
                RationalVector v = add(rc, add(rc, xi, mul(rc, y1, St.getEntry(k, 0))), mul(rc, y2, St.getEntry(k, 1)));
                Vtt.setRowVector(kk++, v);
            }
            assert kk == Vtt.getRowDimension();
            
            System.out.println("Vtt=\n" + Vtt);
            
            V = concatVer(V, Vtt);
            
            if (!binf.isEmpty()) {
                cfinite =  0;
            }
        }

        return new Result(V, cfinite);
    }
}
