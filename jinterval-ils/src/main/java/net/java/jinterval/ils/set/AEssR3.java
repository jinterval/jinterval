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

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import net.java.jinterval.ils.MatlabOps;
import net.java.jinterval.linear.RationalMatrix;
import net.java.jinterval.linear.RationalVector;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;
import net.java.jinterval.rational.Rational;

/**
 * множество решений интервального включения [uC,oC] x \subseteq [ud,od] в
 * арифметике Каухера
 *
 * @author Шарая Ирина Александровна
 * @version 30/04/2012
 *
 * Пример обращения: uC=[18 -16 -8; -9 -15 16; -8 8 -11] oC=[14 -20 -14; -13 -19
 * 12; -12 4 -15] ud=[-7; 10; -1] od=[-7; 10; -1] cnmty=AEssR3(uC,oC,ud,od)
 *
 */
public class AEssR3 extends MatlabOps {

    private static final ExtendedRationalContext rc = ExtendedRationalContexts.exact();

    public static class Result {
        public final List<DrawHedrons.Hedron> hedrons;
        public final RationalMatrix W;
        
        Result(List<DrawHedrons.Hedron> hedrons, RationalMatrix W) {
            this.hedrons = hedrons;
            this.W = W.copy();
        }
    }
    
    public static Result apply(RationalMatrix uC, RationalMatrix oC, RationalVector ud, RationalVector od) {
        boolean cnmty = true;

        // (аналогично критерию Рона или Оетли-Прагера) множество решений 
        // включения[uC,oC] x \subseteq [ud,od] в ортанте k описывается 
        // системой неравенств Ak(:,:)x>=bk при следующем выборе Ak и bk
        RationalMatrix Appp = concatVer(
                uC,
                neg(oC),
                eye(3));
        RationalMatrix Appm = concatVer(
                concatHor(uC.getSubMatrix(0, 2, 0, 0), uC.getSubMatrix(0, 2, 1, 1), oC.getSubMatrix(0, 2, 2, 2)),
                concatHor(neg(oC.getSubMatrix(0, 2, 0, 0)), neg(oC.getSubMatrix(0, 2, 1, 1)), neg(uC.getSubMatrix(0, 2, 2, 2))),
                concatVer(
                vec(1, 0, 0),
                vec(0, 1, 0),
                vec(0, 0, -1)));
        RationalMatrix Apmp = concatVer(
                concatHor(uC.getSubMatrix(0, 2, 0, 0), oC.getSubMatrix(0, 2, 1, 1), uC.getSubMatrix(0, 2, 2, 2)),
                concatHor(neg(oC.getSubMatrix(0, 2, 0, 0)), neg(uC.getSubMatrix(0, 2, 1, 1)), neg(oC.getSubMatrix(0, 2, 2, 2))),
                concatVer(
                vec(1, 0, 0),
                vec(0, -1, 0),
                vec(0, 0, 1)));
        RationalMatrix Ampp = concatVer(
                concatHor(oC.getSubMatrix(0, 2, 0, 0), uC.getSubMatrix(0, 2, 1, 1), uC.getSubMatrix(0, 2, 2, 2)),
                concatHor(neg(uC.getSubMatrix(0, 2, 0, 0)), neg(oC.getSubMatrix(0, 2, 1, 1)), neg(oC.getSubMatrix(0, 2, 2, 2))),
                concatVer(
                vec(-1, 0, 0),
                vec(0, 1, 0),
                vec(0, 0, 1)));
        RationalMatrix Apmm = concatVer(
                concatHor(uC.getSubMatrix(0, 2, 0, 0), oC.getSubMatrix(0, 2, 1, 1), oC.getSubMatrix(0, 2, 2, 2)),
                concatHor(neg(oC.getSubMatrix(0, 2, 0, 0)), neg(uC.getSubMatrix(0, 2, 1, 1)), neg(uC.getSubMatrix(0, 2, 2, 2))),
                concatVer(
                vec(1, 0, 0),
                vec(0, -1, 0),
                vec(0, 0, -1)));
        RationalMatrix Ampm = concatVer(
                concatHor(oC.getSubMatrix(0, 2, 0, 0), uC.getSubMatrix(0, 2, 1, 1), oC.getSubMatrix(0, 2, 2, 2)),
                concatHor(neg(uC.getSubMatrix(0, 2, 0, 0)), neg(oC.getSubMatrix(0, 2, 1, 1)), neg(uC.getSubMatrix(0, 2, 2, 2))),
                concatVer(
                vec(-1, 0, 0),
                vec(0, 1, 0),
                vec(0, 0, -1)));
        RationalMatrix Ammp = concatVer(
                concatHor(oC.getSubMatrix(0, 2, 0, 0), oC.getSubMatrix(0, 2, 1, 1), uC.getSubMatrix(0, 2, 2, 2)),
                concatHor(neg(uC.getSubMatrix(0, 2, 0, 0)), neg(uC.getSubMatrix(0, 2, 1, 1)), neg(oC.getSubMatrix(0, 2, 2, 2))),
                concatVer(
                vec(-1, 0, 0),
                vec(0, -1, 0),
                vec(0, 0, 1)));
        RationalMatrix Ammm = concatVer(
                oC,
                neg(uC),
                neg(eye(3)));
        RationalVector bppp = concat(ud, neg(od), vec(0, 0, 0));
        RationalVector bppm = bppp.copy();
        RationalVector bpmp = bppp.copy();
        RationalVector bmpp = bppp.copy();
        RationalVector bpmm = bppp.copy();
        RationalVector bmpm = bppp.copy();
        RationalVector bmmp = bppp.copy();
        RationalVector bmmm = bppp.copy();

        // заготовка для набора особых точек множества АЕ-решений 
        // (вершин пересечения его с каждым из ортантов) 
        // и показателя ограниченности множества решений
        RationalMatrix V = zeros(0, 3);
        int cfinite = 1; // считаем, что множество решений ограничено (м.б. пустым)

        // удалим из системы неравенств каждого ортанта строки, 
        // соответствующее нулевым строкам матрицы Ak
        ClearZeroRows.Result rppp = ClearZeroRows.apply(Appp, bppp);
        Appp = rppp.A;
        bppp = rppp.b;
        boolean cnmtyppp = rppp.cnmty;
        int mppp = bppp.getDimension();

        ClearZeroRows.Result rppm = ClearZeroRows.apply(Appm, bppm);
        Appm = rppm.A;
        bppm = rppm.b;
        boolean cnmtyppm = rppm.cnmty;
        int mppm = bppm.getDimension();

        ClearZeroRows.Result rpmp = ClearZeroRows.apply(Apmp, bpmp);
        Apmp = rpmp.A;
        bpmp = rpmp.b;
        boolean cnmtypmp = rpmp.cnmty;
        int mpmp = bpmp.getDimension();

        ClearZeroRows.Result rmpp = ClearZeroRows.apply(Ampp, bmpp);
        Ampp = rmpp.A;
        bmpp = rmpp.b;
        boolean cnmtympp = rmpp.cnmty;
        int mmpp = bmpp.getDimension();

        ClearZeroRows.Result rpmm = ClearZeroRows.apply(Apmm, bpmm);
        Apmm = rpmm.A;
        bpmm = rpmm.b;
        boolean cnmtypmm = rpmm.cnmty;
        int mpmm = bpmm.getDimension();

        ClearZeroRows.Result rmpm = ClearZeroRows.apply(Ampm, bmpm);
        Ampm = rmpm.A;
        bmpm = rmpm.b;
        boolean cnmtympm = rmpm.cnmty;
        int mmpm = bmpm.getDimension();

        ClearZeroRows.Result rmmp = ClearZeroRows.apply(Ammp, bmmp);
        Ammp = rmmp.A;
        bmmp = rmmp.b;
        boolean cnmtymmp = rmmp.cnmty;
        int mmmp = bmmp.getDimension();

        ClearZeroRows.Result rmmm = ClearZeroRows.apply(Ammm, bmmm);
        Ammm = rmmm.A;
        bmmm = rmmm.b;
        boolean cnmtymmm = rmmm.cnmty;
        int mmmm = bmmm.getDimension();

        // если множество решений в ортанте непусто, добавим его вершины
        // в список особых точек всего множества АЕ-решений,
        // при этом если множество решений в ортанте неограничено,
        // запомним это как cfinite=0
        AddV.Result appp = AddV.apply(V, cfinite, Appp, bppp, mppp, cnmtyppp);
        V = appp.V;
        cfinite = appp.cfinite;

        AddV.Result appm = AddV.apply(V, cfinite, Appm, bppm, mppm, cnmtyppm);
        V = appm.V;
        cfinite = appm.cfinite;

        AddV.Result apmp = AddV.apply(V, cfinite, Apmp, bpmp, mpmp, cnmtypmp);
        V = apmp.V;
        cfinite = apmp.cfinite;

        AddV.Result ampp = AddV.apply(V, cfinite, Ampp, bmpp, mmpp, cnmtympp);
        V = ampp.V;
        cfinite = ampp.cfinite;

        AddV.Result apmm = AddV.apply(V, cfinite, Apmm, bpmm, mpmm, cnmtypmm);
        V = apmm.V;
        cfinite = apmm.cfinite;

        AddV.Result ampm = AddV.apply(V, cfinite, Ampm, bmpm, mmpm, cnmtympm);
        V = ampm.V;
        cfinite = ampm.cfinite;

        AddV.Result ammp = AddV.apply(V, cfinite, Ammp, bmmp, mmmp, cnmtymmp);
        V = ammp.V;
        cfinite = ammp.cfinite;

        AddV.Result ammm = AddV.apply(V, cfinite, Ammm, bmmm, mmmm, cnmtymmm);
        V = ammm.V;
        cfinite = ammm.cfinite;

        if (V.getRowDimension() == 0) {
            System.out.println("Множество АЕ-решений пусто");
            cnmty = false;
            return new Result(Collections.<DrawHedrons.Hedron>emptyList(), null);
        }

        // по набору вершин (=особых точек) выберем окно отрисовки
        RationalMatrix W = PicWindow3AE.apply(V);

        // если множество решений неограничено,
        // увеличим окно отрисовки W и 
        // внесем в каждом ортанте шесть неравенств обрезки в систему Ak(:,:)x>=bk 
        if (cfinite == 0) {
            RationalVector radius = mul(rc, sub(rc, W.getRowVector(1), W.getRowVector(0)), Rational.valueOf(0.5));
            W = add(rc, W, mul(rc, concatVer(neg(radius), radius), Rational.valueOf(11, 10)));
            Appp = concatVer(Appp, eye(3), neg(eye(3)));
            bppp = concat(bppp, W.getRowVector(0), neg(W.getRowVector(1)));
            Appm = concatVer(Appm, eye(3), neg(eye(3)));
            bppm = concat(bppm, W.getRowVector(0), neg(W.getRowVector(1)));
            Apmp = concatVer(Apmp, eye(3), neg(eye(3)));
            bpmp = concat(bpmp, W.getRowVector(0), neg(W.getRowVector(1)));
            Ampp = concatVer(Ampp, eye(3), neg(eye(3)));
            bmpp = concat(bmpp, W.getRowVector(0), neg(W.getRowVector(1)));
            Apmm = concatVer(Apmm, eye(3), neg(eye(3)));
            bpmm = concat(bpmm, W.getRowVector(0), neg(W.getRowVector(1)));
            Ampm = concatVer(Ampm, eye(3), neg(eye(3)));
            bmpm = concat(bmpm, W.getRowVector(0), neg(W.getRowVector(1)));
            Ammp = concatVer(Ammp, eye(3), neg(eye(3)));
            bmmp = concat(bmmp, W.getRowVector(0), neg(W.getRowVector(1)));
            Ammm = concatVer(Ammm, eye(3), neg(eye(3)));
            bmmm = concat(bmmm, W.getRowVector(0), neg(W.getRowVector(1)));
        }

        // нарисуем по ортантам 
        // грани множества решений в ортанте - зеленым,
        // а грани обрезки - красным
//   figure(1);
//   clf(1);
//   hold on
//   axis vis3d; % auto on normal fill image tight equal
//   axis([W(1,1),W(2,1),W(1,2),W(2,2),W(1,3),W(2,3)]);
//   view(3);
        List<DrawHedrons.Hedron> hedrons = new ArrayList<DrawHedrons.Hedron>();
        hedrons.addAll(DrawHedrons.apply(Appp, bppp, mppp));
        hedrons.addAll(DrawHedrons.apply(Appm, bppm, mppm));
        hedrons.addAll(DrawHedrons.apply(Apmp, bpmp, mpmp));
        hedrons.addAll(DrawHedrons.apply(Ampp, bmpp, mmpp));
        hedrons.addAll(DrawHedrons.apply(Apmm, bpmm, mpmm));
        hedrons.addAll(DrawHedrons.apply(Ampm, bmpm, mmpm));
        hedrons.addAll(DrawHedrons.apply(Ammp, bmmp, mmmp));
        hedrons.addAll(DrawHedrons.apply(Ammm, bmmm, mmmm));
//   camlight left % включить свет слева
//   hidden on % скрыть невидимые линии - аналог отключения прозрачности 'FaceAlpha',1
//   hold off

        return new Result(hedrons, W);
    }
}
