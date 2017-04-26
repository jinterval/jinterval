package ru.nsc.interval.globalopt;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.BinaryValueSet;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;
import net.java.jinterval.rational.ExtendedRationalContexts;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.PriorityQueue;


public class IAOGO {
    static PriorityQueue<ListElem> wList = new PriorityQueue<ListElem>(new AssessmentComp());
    static ExtendedRational supMin;
    private static SetIntervalContext ic;
    private static ExtendedRationalContext rc;
    private static ExtendedRational tolerance;
    private static SetInterval[] initBox;
    static ExtendedRational FIVE = ExtendedRational.valueOf(5);
    static CodeList list;
    static Expression objectiveFun;
    static IntervalEvaluator.GradientEvaluator ev;
    static IntervalEvaluator.GradientMVEvaluator evmv;

    public IAOGO(Expression objectiveFunction) {
        supMin = ExtendedRational.POSITIVE_INFINITY;
        rc =  ExtendedRationalContexts.mkNearest(BinaryValueSet.BINARY64);
        list = objectiveFunction.getCodeList();
        objectiveFun = objectiveFunction;
    }

    static SetInterval scMul(SetInterval[] X, SetInterval[] Y) {
        SetInterval result = ic.numsToInterval(0, 0);
        for (int i = 0; i < X.length; i++) {
            result = ic.add(result, ic.mul(X[i], Y[i]));
        }
        return result;
    }

    public void rmUseless(ExtendedRational supMin) {
        Iterator<ListElem> iterator = wList.iterator();
        while (iterator.hasNext()) {
            if (iterator.next().getAssessment().ge(supMin))
                iterator.remove();
        }
    }

    void initElem(SetInterval[] box, ExtendedRational normBox) {
        boolean isPropSubBox = true;
        for (int i = 0; i < box.length; i++) {
            if (box[i].inf().eq(initBox[i].inf()) || (box[i].sup().eq(initBox[i].sup()))) {
                isPropSubBox = false;
                break;
            }
        }
        Gradient[] boxGradient = Gradient.init(box,ic);
//        Gradient objectiveFunction = IntervalEvaluator.evaluateGradient(ic,list,boxGradient,objectiveFun)[0];
        System.arraycopy(boxGradient, 0, ev.values, 0, list.getNumInps());
        list.acceptForward(ev);
        Gradient objectiveFunction = ev.values[objectiveFun.getIndex()];

        SetInterval[] centralPoint = new SetInterval[box.length];
        for (int i = 0; i < box.length; i++) {
            centralPoint[i] = ic.numsToInterval(box[i].mid(), box[i].mid());
        }
//        Gradient objFuncCentralPointVal = IntervalEvaluator.evaluateGradient(ic,list,Gradient.init(centralPoint,ic),objectiveFun)[0];
        Gradient[] centerGradient = Gradient.init(centralPoint,ic);
        System.arraycopy(centerGradient, 0, ev.values, 0, list.getNumInps());
        list.acceptForward(ev);
        Gradient objFuncCentralPointVal = ev.values[objectiveFun.getIndex()];

        if(rc.sub(supMin,objFuncCentralPointVal.getX().sup()).ge(tolerance)){
            rmUseless(objFuncCentralPointVal.getX().sup());
            supMin = objFuncCentralPointVal.getX().sup();
        }
        SetInterval[] xBiasCentral = new SetInterval[box.length];
        for (int i = 0; i < xBiasCentral.length; i++) {
            xBiasCentral[i] = ic.sub(box[i],centralPoint[i]);
        }
        //improving partial derivatives
        if (normBox.le(FIVE)) {
            GradientMV[] boxGradientMV = GradientMV.init(box, ic);
//            GradientMV objectiveFunctionMV = IntervalEvaluator.evaluateGradientMV(ic, list, boxGradientMV, objectiveFun)[0];
            System.arraycopy(boxGradientMV, 0, evmv.values, 0, list.getNumInps());
            list.acceptForward(evmv);
            GradientMV objectiveFunctionMV = evmv.values[objectiveFun.getIndex()];

            objectiveFunction = objectiveFunction.intersection(objectiveFunctionMV);
        }
        SetInterval fMeanValue = ic.add(objFuncCentralPointVal.getX(),scMul(xBiasCentral,objectiveFunction.getDX()));
        SetInterval fRes = ic.intersection(objectiveFunction.getX(),fMeanValue);
        if (isPropSubBox) {
            for (int i = 0; i < box.length; i++) {
                if (ic.intersection(objectiveFunction.getDX()[i],ic.numsToInterval(0,0)).isEmpty())
                    return;
            }
            Matrix jacoby = new Matrix(objectiveFunction.getDDX());
            Matrix lambda = jacoby.mid().inverse();
            Matrix mXBiasCentral = new Matrix(xBiasCentral);
            Matrix mObjFuncCentrPointVal = new Matrix(objFuncCentralPointVal.getDX());
            SetInterval[] krawczyk = ((mXBiasCentral.sub(lambda.mul(mObjFuncCentrPointVal))).
                    add((Matrix.identity(box.length).sub(lambda.mul(jacoby))).mul(mXBiasCentral))).getVector();
            for (int i = 0; i < box.length; i++) {
                box[i] = ic.intersection(box[i],krawczyk[i]);
                if (box[i].isEmpty())
                    return;
            }
        }
        for (int i = 0; i < box.length; i++) {
            if (objectiveFunction.getDX()[i].inf().ge(ExtendedRational.zero())) {
                box[i] = SetIntervalContexts.getExact().numsToInterval(box[i].inf(),box[i].inf());
            }
            else
                if (objectiveFunction.getDX()[i].sup().le(ExtendedRational.zero())) {
                    box[i] = SetIntervalContexts.getExact().numsToInterval(box[i].sup(),box[i].sup());
                }
        }
        wList.add(new ListElem(box,fRes.inf(),fRes.wid(),objectiveFunction.getDX()));
    }

    ExtendedRational start(SetInterval[] box, ExtendedRational tolerance, SetIntervalContext ic) {
        IAOGO.tolerance = tolerance;
        IAOGO.ic = ic;
        IAOGO.initBox = box;
        Gradient.init(box, ic);
        ev = new IntervalEvaluator.GradientEvaluator(objectiveFun.getCodeList(), ic);
        GradientMV.init(box, ic);
        evmv = new IntervalEvaluator.GradientMVEvaluator(objectiveFun.getCodeList(), ic);
        initElem(box, ExtendedRational.POSITIVE_INFINITY);
        int count = 1;
        while (wList.peek().getWid().ge(tolerance)) {
            int max = 0;
            int pMax = 0;
            SetInterval[] partials = wList.peek().getPartials();
            box = wList.poll().getData();
            for (int i = 1; i < box.length; i++) {
                if (box[max].wid().lt(box[i].wid())) {
                    pMax = max;
                    max = i;
                }
            }
            if (box[max].wid().lt(FIVE))
                for (int i = 0; i < box.length; i++) {
                    if ((rc.mul(ic.abs(partials[i]).sup(),box[i].wid())).gt(rc.mul(ic.abs(partials[max]).sup(),box[max].wid()))) {
                        max = i;
                    }
                }
            SetInterval[] first = box.clone();
            SetInterval[] second = box.clone();
            first[max] = (ic.numsToInterval(first[max].inf(),first[max].mid()));
            second[max] = (ic.numsToInterval(second[max].mid(),second[max].sup()));
            initElem(first, first[pMax].wid());
            initElem(second, second[pMax].wid());
//            System.out.println(wList.peek().getAssessment().doubleValue());
            count++;
        }
        System.out.println(count);
        //return wList.peek().getAssessment();

        //System out.....
        ExtendedRationalContext erc = ExtendedRationalContexts.exact();
        ExtendedRational min = wList.peek().getAssessment();
        System.out.printf("%.18f\t",min.doubleValue());
        SetInterval[] wrkBox = wList.poll().getData();
        for (int i = 0; i < wrkBox.length; i++) {
            System.out.printf("[%.18f, %.18f]\t",wrkBox[i].doubleInf(), wrkBox[i].doubleSup());
        }
        System.out.println();
        if (wList.isEmpty())
            return min;
        else {
            ExtendedRational wrkMin= wList.peek().getAssessment();
//            while (erc.sub(wrkMin,min).le(tolerance)) {
            for (int i = 0; i < 1; i++) {
                System.out.printf("%.18f\t",wrkMin.doubleValue());
                wrkBox = wList.poll().getData();
                for (int j = 0; j < wrkBox.length; j++) {
                    System.out.printf("[%.18f, %.18f]\t",wrkBox[j].doubleInf(), wrkBox[j].doubleSup());
                }
                System.out.println();
                if (wList.isEmpty())
                    return min;
                else
                    wrkMin= wList.peek().getAssessment();
            }
            return min;
        }
    }
}

class AssessmentComp implements Comparator<ListElem> {
    public int compare(ListElem el1, ListElem el2) {
        return ExtendedRational.valueOf(el1.getAssessment()).compareTo(el2.getAssessment());
    }
}

class ListElem implements Comparable<ListElem> {

    private SetInterval[] data;
    private ExtendedRational assessment;
    private ExtendedRational wid;
    private SetInterval[] partials;

    ListElem() {
        data = null;
        assessment = ExtendedRational.valueOf(0.0);
        wid = ExtendedRational.valueOf(0.0);
        Arrays.fill(partials, SetIntervalContexts.getExact().nai());
    }

    ListElem(SetInterval[] data, ExtendedRational assessment, ExtendedRational wid, SetInterval[] partials) {
        this.data = data;
        this.assessment = assessment;
        this.wid = wid;
        this.partials = partials;
    }

    public ExtendedRational getAssessment() {
        return assessment;
    }

    public void setAssessment(ExtendedRational assessment) {
        this.assessment = assessment;
    }

    public ExtendedRational getWid() {
        return wid;
    }

    public SetInterval[] getData() {
        return data;
    }

    public SetInterval[] getPartials() {
        return partials;
    }

    public void setData(SetInterval[] data) {
        this.data = data;
    }

    public int compareTo(ListElem el) {
        return ExtendedRational.valueOf(this.assessment).compareTo(ExtendedRational.valueOf(el.assessment));
    }
}
