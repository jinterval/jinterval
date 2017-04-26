/*
 * Copyright (c) 2016, JInterval Project.
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
package net.java.jinterval.globalopt;

import java.util.ArrayList;
import java.util.List;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;

import java.util.PriorityQueue;
import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.expression.OptimizationProblem;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.interval.set.SetIntervalEvaluatorDecoratedGrad;
import net.java.jinterval.interval.set.SetIntervalEvaluatorGrad;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalOps;
import net.java.jinterval.rational.Rational;

/**
 * @author astronautr
 * @author declow
 */
public class IAOGO {

    private final OptimizationProblem problem;
    private final CodeList cl;
    private final Expression objFun;
    private final SetInterval[] outerBox;
    private final SetInterval[] innerBox;
    private final Rational[] argC;
    private final SetInterval[] recordPoint;
    private final SetInterval[] evResults = new SetInterval[1];
    PriorityQueue<ListElem> wList = new PriorityQueue<>(); //is used for storage objects of ListElem
    List<ListElem> tinyList = new ArrayList<>();
    private SetIntervalContext ic;
    private SetIntervalEvaluatorGrad ev;
    private SetIntervalEvaluatorDecoratedGrad ev2;
    private ExtendedRational record = ExtendedRational.POSITIVE_INFINITY;
    private long numSteps;

    public IAOGO(OptimizationProblem problem) {
        this.problem = problem;
        objFun = problem.getObjective();
        cl = objFun.getCodeList();
        outerBox = new SetInterval[problem.getNumInps()];
        innerBox = new SetInterval[problem.getNumInps()];
        argC = new Rational[problem.getNumInps()];
        recordPoint = new SetInterval[problem.getNumInps()];
    }

    private static String p(SetInterval x) {
        return "[" + x.doubleInf() + "," + x.doubleSup() + "]_" + x.getDecoration();
    }

    private Rational mid(int i, SetInterval v) {
        Rational midR = v.mid();
        SetInterval midI = ic.numsToInterval(midR, midR);
        if (!midI.subset(innerBox[i])) {
            midI = SetIntervalOps.intersection(midI, innerBox[i]);
            assert !midI.isEmpty();
            assert midI.isSingleton();
            return (Rational) midI.inf();
        }
        if (!midI.isSingleton()) {
            if (midI.inf().signum() >= 0) {
                midR = (Rational) midI.inf();
            } else if (midI.sup().signum() <= 0) {
                midR = (Rational) midI.sup();
            } else {
                midR = Rational.zero();
            }
        }
        return midR;

    }

    private void initElem(SetInterval[] box) {
        for (int i = 0; i < box.length; i++) {
            argC[i] = mid(i, box[i]);
            assert innerBox[i].isMember(argC[i]);
        }
        ev.evaluate(evResults, 0, box, argC, 0);
        SetInterval val = evResults[0];
        SetInterval valC = ev.getCenter(objFun.getIndex());
        SetInterval valR = ev.getRefined(objFun.getIndex());
        if (valR.inf().ge(record)) {
//            System.out.println("ignore");
            return;
        }
        if (valC.sup().lt(record)) {
            record = valC.sup();
//            System.out.print("record=" + record.doubleValue() + " at");
            for (int i = 0; i < recordPoint.length; i++) {
                recordPoint[i] = ev.getCenter(i);
//                System.out.print(" " + recordPoint[i].doubleMid());
            }
//            System.out.println();
        }
        boolean collapsed = false;
        for (int i = 0; i < box.length; i++) {
            SetInterval grad = ev.getD(objFun.getIndex(), i);
//            System.out.println(" grad" + i + "=" + p(grad));
            if (grad.inf().signum() > 0) {
                if (box[i].inf().gt(outerBox[i].inf())) {
                    return;
                }
                assert box[i].inf().eq(outerBox[i].inf());
                if (box[i].sup().gt(innerBox[i].inf())) {
                    box[i] = SetIntervalOps.nums2(outerBox[i].inf(), innerBox[i].inf());
                    collapsed = true;
                }
            } else if (grad.sup().signum() < 0) {
                if (box[i].sup().lt(outerBox[i].sup())) {
                    return;
                }
                assert box[i].sup().eq(outerBox[i].sup());
                if (box[i].inf().lt(innerBox[i].sup())) {
                    box[i] = SetIntervalOps.nums2(innerBox[i].sup(), outerBox[i].sup());
                    collapsed = true;
                }
            }
        }
        if (collapsed) {
            initElem(box);
            return;
        }
        int split = -1;
        ExtendedRational splitW = Rational.zero();
        for (int i = 0; i < box.length; i++) {
            if (splitW.lt(box[i].wid())) {
                SetInterval ci = ev.getCenter(i);
                assert ci.isSingleton();
                if (ci.interior(box[i])) {
                    split = i;
                    splitW = box[i].wid();
                }
            }
        }
        Rational splitMid = split >= 0 ? argC[split] : null;
        wList.add(new ListElem(box, valR, valC, split, splitMid));
        numSteps++;
    }

    private void initElem1(SetInterval[] box) {
        for (int i = 0; i < box.length; i++) {
            argC[i] = mid(i, box[i]);
            assert innerBox[i].isMember(argC[i]);
        }
        ev2.evaluate(evResults, 0, box, argC, 0);
        SetInterval val = evResults[0];
        SetInterval valC = ev2.getCenter(objFun.getIndex());
        SetInterval valR = ev2.getRefined(objFun.getIndex());
        if (valR.inf().ge(record)) {
//            System.out.println("ignore");
            return;
        }
        if (valC.sup().lt(record)) {
            record = valC.sup();
//            System.out.print("record=" + record.doubleValue() + " at");
            for (int i = 0; i < recordPoint.length; i++) {
                recordPoint[i] = ev2.getCenter(i);
//                System.out.print(" " + recordPoint[i].doubleMid());
            }
//            System.out.println();
        }
        boolean collapsed = false;
        for (int i = 0; i < box.length; i++) {
            SetInterval grad = ev2.getD(objFun.getIndex(), i);
//            System.out.println(" grad" + i + "=" + p(grad));
            if (grad.inf().signum() > 0) {
                if (box[i].inf().gt(outerBox[i].inf())) {
                    return;
                }
                assert box[i].inf().eq(outerBox[i].inf());
                if (box[i].sup().gt(innerBox[i].inf())) {
                    box[i] = SetIntervalOps.nums2(outerBox[i].inf(), innerBox[i].inf());
                    collapsed = true;
                }
            } else if (grad.sup().signum() < 0) {
                if (box[i].sup().lt(outerBox[i].sup())) {
                    return;
                }
                assert box[i].sup().eq(outerBox[i].sup());
                if (box[i].inf().lt(innerBox[i].sup())) {
                    box[i] = SetIntervalOps.nums2(innerBox[i].sup(), outerBox[i].sup());
                    collapsed = true;
                }
            }
        }
        if (collapsed) {
            initElem(box);
            return;
        }
        int split = -1;
        ExtendedRational splitW = Rational.zero();
        for (int i = 0; i < box.length; i++) {
            if (splitW.lt(box[i].wid())) {
                SetInterval ci = ev2.getCenter(i);
                assert ci.isSingleton();
                if (ci.interior(box[i])) {
                    split = i;
                    splitW = box[i].wid();
                }
            }
        }
        Rational splitMid = split >= 0 ? argC[split] : null;
        wList.add(new ListElem(box, valR, valC, split, splitMid));
        numSteps++;
    }

    private void initElem2(SetInterval[] box) {
        for (int i = 0; i < box.length; i++) {
            argC[i] = mid(i, box[i]);
            assert innerBox[i].isMember(argC[i]);
        }
        ev.evaluate(evResults, 0, box, argC, 0);
        SetInterval val1 = evResults[0];
        SetInterval val1C = ev.getCenter(objFun.getIndex());
        SetInterval val1R = ev.getRefined(objFun.getIndex());
        ev2.evaluate(evResults, 0, box, argC, 0);
        SetInterval val2 = evResults[0];
        SetInterval val2C = ev2.getCenter(objFun.getIndex());
        SetInterval val2R = ev2.getRefined(objFun.getIndex());
//        if (!val1.equal(val2) || !val1C.equal(val2C) || !val1R.equal(val2R)) {
//            System.out.println("val1=" + p(val1) + " val1C=" + p(val1C) + " val1R=" + p(val1R));
//            System.out.println("val2=" + p(val2) + " val2C=" + p(val2C) + " val2R=" + p(val2R));
            for (int i = 0; i < cl.getNumExprs(); i++) {
                Expression e = cl.getExpr(i);
                assert e.getIndex() == i;
                SetInterval v1 = ev.get(i);
                SetInterval v2 = ev2.get(i);
//                System.out.println("  " + 0 + " " + p(ev.get(0)) + " " + p(ev2.get(0)));
//                System.out.println("  " + i + " " + p(v1) + " " + p(v2));
                if (!v1.equal(v2)) {
                    System.out.println("  " + i + " " + p(v1) + " " + p(v2));
                    System.out.print(" ^^^^ ");
                    e.accept(ev);
                    e.accept(ev2);
                }
                v1 = ev.getCenter(i);
                v2 = ev2.getCenter(i);
                if (!v1.equal(v2)) {
                    System.out.println("  " + i + " " + p(v1) + " " + p(v2));
                }
                for (int j = 0; j < cl.getNumInps(); j++) {
                    SetInterval g1 = ev.getD(i, j);
                    SetInterval g2 = ev2.getD(i, j);
                    if (!v1.equal(v2)) {
                        System.out.println("  " + i + " " + j + " " + p(g1) + " " + p(g2));
                    }
                }
            }
//        }
        if (val1R.inf().ge(record)) {
//            System.out.println("ignore");
            return;
        }
        if (val1C.sup().lt(record)) {
            record = val1C.sup();
//            System.out.print("record=" + record.doubleValue() + " at");
            for (int i = 0; i < recordPoint.length; i++) {
                recordPoint[i] = ev.getCenter(i);
//                System.out.print(" " + recordPoint[i].doubleMid());
            }
//            System.out.println();
        }
        boolean collapsed = false;
        for (int i = 0; i < box.length; i++) {
            SetInterval grad = ev.getD(objFun.getIndex(), i);
//            System.out.println(" grad" + i + "=" + p(grad));
            if (grad.inf().signum() > 0) {
                if (box[i].inf().gt(outerBox[i].inf())) {
                    return;
                }
                assert box[i].inf().eq(outerBox[i].inf());
                if (box[i].sup().gt(innerBox[i].inf())) {
                    box[i] = SetIntervalOps.nums2(outerBox[i].inf(), innerBox[i].inf());
                    collapsed = true;
                }
            } else if (grad.sup().signum() < 0) {
                if (box[i].sup().lt(outerBox[i].sup())) {
                    return;
                }
                assert box[i].sup().eq(outerBox[i].sup());
                if (box[i].inf().lt(innerBox[i].sup())) {
                    box[i] = SetIntervalOps.nums2(innerBox[i].sup(), outerBox[i].sup());
                    collapsed = true;
                }
            }
        }
        if (collapsed) {
            initElem(box);
            return;
        }
        int split = -1;
        ExtendedRational splitW = Rational.zero();
        for (int i = 0; i < box.length; i++) {
            if (splitW.lt(box[i].wid())) {
                SetInterval ci = ev.getCenter(i);
                assert ci.isSingleton();
                if (ci.interior(box[i])) {
                    split = i;
                    splitW = box[i].wid();
                }
            }
        }
        Rational splitMid = split >= 0 ? argC[split] : null;
        wList.add(new ListElem(box, val1R, val1C, split, splitMid));
        numSteps++;
    }

    public SetInterval start(Rational tolerance, SetIntervalContext ic) {

        if (ic == null) {
            this.ic = SetIntervalContexts.getDefault();
            ev = new SetIntervalEvaluatorGrad(cl, new Expression[]{objFun});
            ev2 = new SetIntervalEvaluatorDecoratedGrad(cl, new Expression[]{objFun});
        } else {
            this.ic = ic;
            ev = new SetIntervalEvaluatorGrad(ic, cl, new Expression[]{objFun});
            ev2 = new SetIntervalEvaluatorDecoratedGrad(ic, cl, new Expression[]{objFun});
        }
        for (int i = 0; i < problem.getNumInps(); i++) {
            String inpRange = problem.getInpRange(i).trim();
            assert inpRange.startsWith("[") && inpRange.endsWith("]");
            inpRange = inpRange.substring(1, inpRange.length() - 1).trim();
            int indComma = inpRange.indexOf(',');
            String lS = inpRange.substring(0, indComma).trim();
            String uS = inpRange.substring(indComma + 1).trim();
            SetInterval lI = this.ic.textToInterval("[" + lS + "]");
            SetInterval uI = this.ic.textToInterval("[" + uS + "]");
            outerBox[i] = this.ic.textToInterval(problem.getInpRange(i));
            assert lI.inf().eq(outerBox[i].inf());
            assert uI.sup().eq(outerBox[i].sup());
            innerBox[i] = SetIntervalOps.nums2(lI.sup(), uI.inf());
//            System.out.println("  outerBox" + i + "=" + p(outerBox[i]) + " innerBox" + i + "=" + p(innerBox[i]));
        }
        initElem(outerBox);
        while (!wList.isEmpty() && ExtendedRationalOps.sub(record, wList.peek().getAssessment()).ge(tolerance)) {
            ListElem elem = wList.poll();
            SetInterval[] box = elem.getData();
            int split = elem.getSplit();
            Rational splitMid = elem.getSplitMid();
//            System.out.print("Split " + split);
//            for (int i = 0; i < box.length; i++) {
//                System.out.print(" " + box[i].doubleWid());
//            }
//            System.out.println();
            if (split < 0 || elem.getValC().wid().ge(tolerance)) {
                tinyList.add(elem);
                continue;
            }
            SetInterval[] first = box.clone();
            SetInterval[] second = box.clone();
            first[split] = this.ic.numsToInterval(box[split].inf(), splitMid);
            second[split] = this.ic.numsToInterval(splitMid, box[split].sup());
            initElem(first);
            initElem(second);
        }
        ExtendedRational lowerBound = ExtendedRational.POSITIVE_INFINITY;
        if (!tinyList.isEmpty()) {
            System.out.println(tinyList.size() + " tiny elements");
            for (ListElem elem : tinyList) {
                lowerBound = ExtendedRationalOps.min(lowerBound, elem.getAssessment());
            }
        }
        if (!wList.isEmpty()) {
            lowerBound = ExtendedRationalOps.min(lowerBound, wList.peek().getAssessment());
        }
        int interesting = 0;
        for (ListElem elem : wList) {
            if (elem.getAssessment().lt(record)) {
                interesting++;
            }
        }
        System.out.println("numSteps=" + numSteps
                + " tinyList.size=" + tinyList.size()
                + " wList.size=" + wList.size()
                + " interesting=" + interesting);
        return SetIntervalOps.nums2(lowerBound, record);
    }
}

class ListElem implements Comparable<ListElem> {

    private SetInterval[] data; //here we store domain of objective function
    private ExtendedRational assessment; //this field represents infumum of range of objective function for ListElem
    private SetInterval val;
    private SetInterval valC;
    private int split;
    private Rational splitMid;

    ListElem(SetInterval[] data, SetInterval val, SetInterval valC, int split, Rational splitMid) {
        this.data = data;
        this.val = val;
        this.valC = valC;
        this.split = split;
        this.splitMid = splitMid;
        assessment = val.inf();
    }

    public ExtendedRational getAssessment() {
        return assessment;
    }

    public SetInterval[] getData() {
        return this.data;
    }

    public void setData(SetInterval[] data) {
        this.data = data;
    }

    public SetInterval getVal() {
        return val;
    }

    public SetInterval getValC() {
        return valC;
    }

    public int getSplit() {
        return split;
    }

    public Rational getSplitMid() {
        return splitMid;
    }

    @Override
    public int compareTo(ListElem el) { //at this place and at strings 58-62 we redefined comparator for comparison ListElem objects by "assessment" field
        return this.assessment.compareTo(el.assessment);
    }
}
