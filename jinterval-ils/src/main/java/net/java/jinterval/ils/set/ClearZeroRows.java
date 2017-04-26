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
import net.java.jinterval.linear.Array2DRowRationalMatrix;
import net.java.jinterval.linear.ArrayRationalVector;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.linear.RationalVector;
import net.java.jinterval.rational.Rational;

/**
 * Обработка нулевых строк матрицы A в системе $Ax\geq b, A\in \mbR^{m\times n},
 * b\in\mbR^m$. Результат - система без нулевых строк-коэффициентов + параметр
 * cnmty = совместность исходной системы % control not empty (true - совместна,
 * false - нет, т.е множество решений пусто).
 *
 * Для cnmty = true учесть далее, что если после исключение нулевых строк
 * size(A,1)=0, то множество решений исходной системы = R^n и его граница пуста.
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 */
public class ClearZeroRows {

    public static class Result {

        public final RationalMatrix A;
        public final RationalVector b;
        boolean cnmty;

        public Result(RationalMatrix A, RationalVector b, boolean cnmty) {
            this.A = A;
            this.b = b;
            this.cnmty = cnmty;
        }
    }

    public static Result apply(RationalMatrix A, RationalVector b) {
        int m = A.getRowDimension();
        int n = A.getColumnDimension();
        boolean cnmty = true;
        BitSet p = new BitSet();

        for (int i = 0; i < m; i++) {
            boolean zeroRow = true;
            for (int j = 0; j < n; j++) {
                zeroRow = zeroRow && A.getEntry(i, j).signum() == 0;
            }
            if (zeroRow) {
                p.set(i);
                if (b.getEntry(i).signum() > 0) {
                    cnmty = false;
                }
            }
        }
        if (!p.isEmpty()) {
            int newM = m - p.cardinality();
            RationalMatrix newA = new Array2DRowRationalMatrix(newM, n);
            RationalVector newB = new ArrayRationalVector(newM);
            int ii = 0;
            for (int i = 0; i < m; i++) {
                if (p.get(i)) {
                    continue;
                }
                for (int j = 0; j < n; j++) {
                    newA.setEntry(ii, j, A.getEntry(i, j));
                }
                newB.setEntry(ii, b.getEntry(i));
                ii++;
            }
            assert ii == newM;
            A = newA;
            b = newB;
        }
        return new Result(A, b, cnmty);
    }
}
