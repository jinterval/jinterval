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
import net.java.jinterval.rational.ExtendedRationalOps;

/**
 * В системе $Ax\geq b, A\in \mbR^{m\times 2}, b\in\mbR^m$, матрица которой не
 * содержит нулевых строк и m >= 1, для каждого неравенства вносим в S участок
 * активности (= пересечение прямой A_{i:}x = b(i) с множеством решений).
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 */
public class BoundaryIntervals extends MatlabOps {

    private static final ExtendedRationalContext rc = ExtendedRationalContexts.exact();

    public static RationalMatrix apply(RationalMatrix A, RationalVector b) {
        int m = A.getRowDimension();
        RationalMatrix S = zeros(0, 5);

        for (int i = 0; i < m; i++) {
            // заготовка под участок активности i-го неравенства
            ExtendedRational qMin = ExtendedRational.NEGATIVE_INFINITY;
            ExtendedRational qMax = ExtendedRational.POSITIVE_INFINITY;
            // предположим, что i-е неравество имеет участок активности
            boolean si = true;
            RationalVector Ai = A.getRowVector(i);
            // \dot{x}
            RationalVector dotx = mul(rc, Ai, rc.div(b.getEntry(i), dot(rc, Ai, Ai)));
            // направление обхода границы i-й полуплоскости
            // так, что сама полуплоскость справа 
            // (соответствует обходу множества решений 
            //  по часовой стрелке)
            RationalVector p = vec(ExtendedRationalOps.neg(Ai.getEntry(1)), Ai.getEntry(0));

            for (int k = 0; k < m; k++) {
                // по хорошему i-ое неравенство не надо считать - 
                // оно не влияет на участок активности
                RationalVector Ak = A.getRowVector(k);
                // скалярное произведение A_{k:} на \dot{x}
                ExtendedRational Akx = dot(rc, Ak, dotx);
                // скалярное произведение A_{k:} на вектор p
                ExtendedRational c = dot(rc, Ak, p);
                switch (c.signum()) {
                    case -1:
                        qMax = rc.min(qMax, rc.div(rc.sub(b.getEntry(k), Akx), c));
                        break;
                    case +1:
                        qMin = rc.max(qMin, rc.div(rc.sub(b.getEntry(k), Akx), c));
                        break;
                    // case 0:
                    default:
                        if (Akx.lt(b.getEntry(k))) {
                            if (dot(rc, Ak, Ai).signum() > 0) {
                                si = false; // i-е неравенство не имеет участка активности
                                break; // выход из цикла for k
                            } else { // т.е. <0 и при этом нер-ва i и k несовместны
//                       disp('Есть пара противоречивых неравенств') 
                                return S; // выход из функции 
                            }
                        }
                }
            }

            if (qMin.gt(qMax)) {
                si = false;
            }

            if (si) {
                S = concatVer(S, concatVer(concat(add(rc, dotx, mul(rc, p, qMin)), add(rc, dotx, mul(rc, p, qMax)), vec(i))));
            }
        }
        return S;
    }
}
