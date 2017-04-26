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

import java.awt.Color;
import java.util.ArrayList;
import java.util.List;
import net.java.jinterval.ils.MatlabOps;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.linear.RationalVector;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;

/**
 * для каждой строки i рисуем пересечение границы множества решений с плоскостью
 * A(i,:)x=b(i)) ("грань i")
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 */
public class DrawHedrons extends MatlabOps {

    private static final ExtendedRationalContext rc = ExtendedRationalContexts.exact();

    public static class Hedron {
        public final RationalVector r0;
        public final RationalVector ex;
        public final RationalVector ey;
        public final RationalVector xt;
        public final RationalVector yt;
        public final Color c;
        public final double transp;
        
        Hedron(RationalVector r0, RationalVector ex, RationalVector ey, RationalVector xt, RationalVector yt, Color c, double transp) {
            this.r0 = r0.copy();
            this.ex = ex.copy();
            this.ey = ey.copy();
            this.xt = xt.copy();
            this.yt = yt.copy();
            this.c = c;
            this.transp = transp;
        }
    } 
    
    public static List<Hedron> apply(RationalMatrix A, RationalVector b, int m) {
        List<Hedron> result = new ArrayList<Hedron>();
        int mn = b.getDimension();
        for (int i = 0; i < mn; i++) {
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

            if (!cnmtyt) {
                continue; // плоскость i не пересекает границу H
            }

            // найдем пересечения прямых At(k,:)y=bt(k) с границей H в координатах (y)
            // матрица St построчно составлена из таких прямолинейных участков по типу
            // [ beginy1 beginy2 endy1 endy2 k ]
            RationalMatrix St = BoundaryIntervals.apply(At, bt);

            // по матрице St составим путь Pt обхода i-ой грани
            if (St.getRowDimension() > 0) {
                RationalMatrix Pt = Intervals2Path.apply(St);

                // перепишем матрицу Pt в координатах (x)
                // P=xi+y1*Pt(:,1)+y2*Pt(:,2);
                RationalMatrix P = zeros(Pt.getRowDimension(), 3);
                for (int k = 0; k < Pt.getRowDimension(); k++) {
                    P.setRowVector(k, add(rc, add(rc, xi, mul(rc, y1, Pt.getEntry(k, 0))), mul(rc, y2, Pt.getEntry(k, 1))));
                }

                // выберем для обычных граней зеленый цвет и прозрачность 0.9, 
                // а для граней обрезки - красный цвет и более высокую прозрачность 0.7
                Color c = Color.BLUE;
                double transp = 0.9;
                if (i >= m) {
                    c = Color.RED;
                    transp = 0.7;
                }
                
                // нарисуем "грань i"
                result.add(new Hedron(xi, y1, y2, Pt.getColumnVector(0), Pt.getColumnVector(1), c, transp));
//                fill3(P.getColumnVector(0), P.getColumnVector(1), P.getColumnVector(2), c, 'FaceAlpha', transp);
            }
        }
        return result;
    }
}
