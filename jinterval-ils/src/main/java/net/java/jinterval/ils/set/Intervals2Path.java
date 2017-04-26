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

/**
 * по матрице S участков границы строим путь P - обход многогранника
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 */
public class Intervals2Path extends MatlabOps {

    public static RationalMatrix apply(RationalMatrix S) {
        RationalVector bp = vec(S.getEntry(0, 0), S.getEntry(0, 1)); // начало обхода
        RationalMatrix P = concatVer(bp);
        RationalVector bs = bp; // начало прямолинейного участка

        while (S.getRowDimension() > 0) {
            int i = -1;
            for (int k = 0; k < S.getRowDimension(); k++) { // ищем строку i, для которой сегмент S(i,:) начинается в bs
                if (bs.getEntry(0).eq(S.getEntry(k, 0)) && bs.getEntry(1).eq(S.getEntry(k, 1))) {
                    i = k;
                    break;
                }
            }

            RationalVector es = vec(S.getEntry(i, 2), S.getEntry(i, 3)); // конец прямолинейного участка
            if (!es.equals(bs)) {
                P = concatVer(P, concatVer(es));
                if (es.equals(bp)) {
                    return P; // построен замкнутый путь
                }
                bs = es; // начинаем новый прямолинейный участок из конца предыдущего
            }
            S = deleteRow(S, i);
        }

        return P;
    }
}
