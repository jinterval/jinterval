package ru.nsc.interval.globalopt;

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.ExtendedRational;

import java.util.Arrays;

public class GradientMV {
    static SetInterval[] box;
    static SetInterval[] boxBiasCentral;
    static SetIntervalContext ic;
    static int dim;
    private SetInterval xCentral;
    private SetInterval[] dxCentral;
    private SetInterval X;
    private SetInterval[] dX;
    private SetInterval[][] ddX;

    private static final SetInterval ZERO = SetIntervalContexts.getExact().numsToInterval(0,0);
    private static final SetInterval ONE = SetIntervalContexts.getExact().numsToInterval(1, 1);

    private void hessianFill() {
        for (int i = 1; i < dim; i++)
            for (int j = i-1; j >= 0; j--) {
                this.ddX[i][j] = this.ddX[j][i];
            }
    }

    static SetInterval scMul(SetInterval[] X, SetInterval[] Y) {
        SetInterval result = ic.numsToInterval(0, 0);
        for (int i = 0; i < X.length; i++) {
            result = ic.add(result, ic.mul(X[i], Y[i]));
        }
        return result;
    }

    private void improving() {
        for (int i = 0; i < dim; i++) {
            SetInterval dxiMV = ic.add(this.dxCentral[i],scMul(this.ddX[i],boxBiasCentral));
            this.dX[i] = ic.intersection(this.dX[i], dxiMV);
        }
        SetInterval xMV = ic.add(this.xCentral,scMul(this.dX,boxBiasCentral));
        this.X = ic.intersection(X,xMV);
    }

    public static GradientMV[] init(SetInterval[] box, SetIntervalContext ic) {
        dim = box.length;
        GradientMV.ic = ic;
        GradientMV.box = box;
        GradientMV[] result = new GradientMV[dim];
        GradientMV.boxBiasCentral = new SetInterval[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = new GradientMV();
            result[i].xCentral = SetIntervalContexts.getExact().numsToInterval(box[i].mid(), box[i].mid());
            result[i].dxCentral = new SetInterval[dim];
            GradientMV.boxBiasCentral[i] = ic.sub(box[i],result[i].xCentral);
            result[i].dX = new SetInterval[dim];
            result[i].ddX = new SetInterval[dim][dim];
            result[i].X = box[i];
            for (SetInterval[] row: result[i].ddX) {
                Arrays.fill(row, ZERO);
            }
            for (int j = 0; j < i; j++) {
                result[i].dX[j] = ZERO;
                result[i].dxCentral[j] = ZERO;
            }
            result[i].dX[i] = ONE;
            result[i].dxCentral[i] = ONE;
            for (int j = i + 1; j < dim; j++) {
                result[i].dX[j] = ZERO;
                result[i].dxCentral[j] = ZERO;
            }
        }
        return result;
    }

    public static GradientMV num(double number) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.numsToInterval(number,number);
        result.dxCentral = new SetInterval[dim];
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
            result.dxCentral[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(number,number);
        return result;
    }

    public static GradientMV num(ExtendedRational number) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.numsToInterval(number,number);
        result.dxCentral = new SetInterval[dim];
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
            result.dxCentral[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(number,number);
        return result;
    }

    public static GradientMV nums(ExtendedRational inf, ExtendedRational sup) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.numsToInterval(inf,sup);
        result.dxCentral = new SetInterval[dim];
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
            result.dxCentral[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(inf,sup);
        return result;
    }

    public GradientMV neg() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.neg(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        result.X = ic.neg(X);
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(dX[i]);
            result.dxCentral[i] = ic.neg(dxCentral[i]);
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j]=ic.neg(ddX[i][j]);
            }
        }
        return result;
    }

    public GradientMV add(GradientMV Y) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.add(this.xCentral,Y.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.add(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.add(this.dX[i],Y.dX[i]);
            result.dxCentral[i] = ic.add(this.dxCentral[i],Y.dxCentral[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.add(this.ddX[i][j],Y.ddX[i][j]);
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV sub(GradientMV Y) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.sub(this.xCentral,Y.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.sub(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.sub(this.dX[i],Y.dX[i]);
            result.dxCentral[i] = ic.sub(this.dxCentral[i],Y.dxCentral[i]);

            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.sub(this.ddX[i][j],Y.ddX[i][j]);
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV mul(GradientMV Y) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.mul(this.xCentral,Y.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.mul(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.add(ic.mul(this.X, Y.dX[i]),ic.mul(this.dX[i],Y.X));
            result.dxCentral[i] = ic.add(ic.mul(this.xCentral, Y.dxCentral[i]),ic.mul(this.dxCentral[i],Y.xCentral));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.add(ic.add(ic.mul(this.ddX[i][j],Y.X),ic.add(ic.mul(this.dX[i],Y.dX[j]),ic.mul(this.dX[j],Y.dX[i])))
                        ,ic.mul(this.X,Y.ddX[i][j]));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV div(GradientMV Y) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.div(this.xCentral,Y.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.div(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.sub(ic.div(this.dX[i],Y.X),ic.div(ic.mul(this.X,Y.dX[i]),ic.sqr(Y.X)));
            result.dxCentral[i] = ic.sub(ic.div(this.dxCentral[i],Y.xCentral),ic.div(ic.mul(this.xCentral,Y.dxCentral[i]),ic.sqr(Y.xCentral)));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] =ic.add(ic.sub(ic.div(this.ddX[i][j],Y.X),
                        ic.div(
                                ic.add(ic.add(ic.mul(this.dX[i],Y.dX[j]),ic.mul(this.dX[j],Y.dX[i])),ic.mul(this.X,Y.ddX[i][j])),ic.sqr(Y.X))),
                        ic.mul(ic.numsToInterval(2,2),ic.div(ic.mul(this.X,ic.mul(Y.dX[i],Y.dX[j])),ic.pown(Y.X,3))));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV recip() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.recip(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.recip(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(ic.div(this.dX[i],ic.sqr(this.X)));
            result.dxCentral[i] = ic.neg(ic.div(this.dxCentral[i],ic.sqr(xCentral)));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] =ic.sub(
                    ic.mul(ic.numsToInterval(2,2),ic.div(ic.mul(this.dX[i],this.dX[j]),ic.pown(this.X,3))),
                    ic.div(this.ddX[i][j],ic.sqr(this.X)));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV sqr() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.sqr(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.sqr(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.mul(ic.numsToInterval(2,2),X),this.dX[i]);
            result.dxCentral[i] = ic.mul(ic.mul(ic.numsToInterval(2,2),xCentral),this.dxCentral[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.mul(ic.numsToInterval(2,2),ic.add(ic.mul(this.dX[j],this.dX[i]),ic.mul(this.X,this.ddX[i][j])));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV sqrt() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.sqrt(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.sqrt(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.div(dX[i], ic.mul(ic.numsToInterval(2,2),ic.sqrt(X)));
            result.dxCentral[i] = ic.div(dxCentral[i], ic.mul(ic.numsToInterval(2,2),ic.sqrt(xCentral)));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.div(ic.sub(ic.mul(ic.mul(this.ddX[i][j],ic.numsToInterval(2,2)),this.X),ic.mul(this.dX[i],this.dX[j])),
                        ic.mul(ic.numsToInterval(4,4),ic.sqrt(ic.pown(this.X,3))));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    //NotIsRealAbs
    public GradientMV abs() {
        GradientMV result = new GradientMV();
        result.xCentral = this.xCentral;
        result.dxCentral = new SetInterval[dim];
        result.X = ic.intersection(this.X,ic.numsToInterval(1, Double.POSITIVE_INFINITY));
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = /*ic.convexHull(ic.neg(this.dX[i]),this.dX[i]);*/this.dX[i];
            result.dxCentral[i] = /*ic.convexHull(ic.neg(this.dX[i]),this.dX[i]);*/this.dxCentral[i];
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        result.hessianFill();
        return result;
    }

    public GradientMV acos() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.acos(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.acos(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(ic.div(dX[i],ic.sqrt(ic.sub(ic.numsToInterval(1,1),ic.sqr(X)))));
            result.dxCentral[i] = ic.neg(ic.div(dxCentral[i],ic.sqrt(ic.sub(ic.numsToInterval(1,1),ic.sqr(xCentral)))));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.neg(ic.div(ic.add(ic.mul(this.ddX[i][j],ic.sub(ic.numsToInterval(1,1),ic.sqr(this.X))),
                        ic.mul(ic.mul(this.X,this.dX[i]),this.dX[j])),
                        ic.pow(ic.sub(ic.numsToInterval(1,1),ic.sqr(this.X)),ic.numsToInterval(1.5,1.5))));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV pow(GradientMV Y) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.pow(this.xCentral,Y.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.pow(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.mul(Y.X, ic.pow(X,ic.sub(Y.X, ic.numsToInterval(1,1)))),this.dX[i]);
            result.dxCentral[i] = ic.mul(ic.mul(Y.xCentral, ic.pow(xCentral,ic.sub(Y.xCentral, ic.numsToInterval(1,1)))),this.dxCentral[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.mul(ic.mul(Y.X,ic.pow(this.X,ic.sub(Y.X,ic.numsToInterval(2,2)))),
                        ic.add(ic.mul(ic.mul(ic.sub(Y.X,ic.numsToInterval(1,1)),this.dX[i]),this.dX[j]),
                                ic.mul(this.X,this.ddX[i][j])));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV sin() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.sin(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.sin(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.cos(X),dX[i]);
            result.dxCentral[i] = ic.mul(ic.cos(xCentral),dxCentral[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.add(ic.mul(ic.mul(ic.neg(ic.sin(this.X)),this.dX[i]),this.dX[j]),
                        ic.mul(ic.cos(this.X),this.ddX[i][j]));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV cos() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.cos(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.cos(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(ic.mul(ic.sin(X),dX[i]));
            result.dxCentral[i] = ic.neg(ic.mul(ic.sin(xCentral),dxCentral[i]));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.neg(ic.add(ic.mul(ic.mul((ic.cos(this.X)),this.dX[i]),this.dX[j]),
                        ic.mul(ic.sin(this.X),this.ddX[i][j])));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV atan() {
        GradientMV result = new GradientMV();
        result.xCentral = ic.atan(this.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.atan(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.div(ic.numsToInterval(1,1),ic.add(ic.numsToInterval(1,1),ic.sqr(X))),dX[i]);
            result.dxCentral[i] = ic.mul(ic.div(ic.numsToInterval(1,1),ic.add(ic.numsToInterval(1,1),ic.sqr(xCentral))),dxCentral[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.div(ic.sub(ic.mul(this.ddX[i][j],ic.add(ic.numsToInterval(1,1),ic.sqr(this.X))),
                        ic.mul(ic.mul(ic.mul(ic.numsToInterval(2,2),this.X),this.dX[i]),this.dX[j])),
                        ic.sqr(ic.add(ic.numsToInterval(1,1),ic.sqr(this.X))));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV max(GradientMV Y) {
        GradientMV result = new GradientMV();
        result.xCentral = ic.max(this.xCentral, Y.xCentral);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.max(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        if (this.xCentral.strictPrecedes(Y.xCentral)) {
            for (int i = 0; i < dim; i++) {
                result.dxCentral[i] = Y.dxCentral[i];
            }
        } else if (Y.xCentral.strictPrecedes(this.xCentral)) {
            for (int i = 0; i < dim; i++) {
                result.dxCentral[i] = this.dxCentral[i];
            }
        } else {
            for (int i = 0; i < dim; i++) {
                result.dxCentral[i] = ic.convexHull(this.dxCentral[i], Y.dxCentral[i]);
            }
        }
        if (this.X.strictPrecedes(Y.X)) {
            for (int i = 0; i < dim; i++) {
                result.dX[i] = Y.dX[i];
                for (int j = i; j < dim; j++) {
                    result.ddX[i][j] = Y.ddX[i][j];
                }
            }
        } else if (Y.X.strictPrecedes(this.X)) {
            for (int i = 0; i < dim; i++) {
                result.dX[i] = this.dX[i];
                for (int j = i; j < dim; j++) {
                    result.ddX[i][j] = this.ddX[i][j];
                }
            }
        } else {
            for (int i = 0; i < dim; i++) {
                result.dX[i] = ic.convexHull(this.dX[i], Y.dX[i]);
                for (int j = i; j < dim; j++) {
                    result.ddX[i][j] = ic.entire();
                }
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public GradientMV rootn(int q) {
        GradientMV result = new GradientMV();
        SetInterval Y = ic.recip(ic.numsToInterval(q,q));
        result.xCentral = ic.pow(this.xCentral, Y);
        result.dxCentral = new SetInterval[dim];
        result.X = ic.pow(this.X, Y);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.mul(Y, ic.pow(X,ic.sub(Y, ic.numsToInterval(1,1)))),this.dX[i]);
            result.dxCentral[i] = ic.mul(ic.mul(Y, ic.pow(xCentral,ic.sub(Y, ic.numsToInterval(1,1)))),dxCentral[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.mul(ic.mul(Y,ic.pow(this.X,ic.sub(Y,ic.numsToInterval(2,2)))),
                        ic.add(ic.mul(ic.mul(ic.sub(Y,ic.numsToInterval(1,1)),this.dX[i]),this.dX[j]),
                                ic.mul(this.X,this.ddX[i][j])));
            }
        }
        result.hessianFill();
        result.improving();
        return result;
    }

    public SetInterval getX() {
        return X;
    }

    public SetInterval[] getDX() {
        return dX;
    }

    public SetInterval[][] getDDX() {
        return this.ddX;
    }

    public void show() {
        System.out.println("[" + this.X.doubleInf() + ", " + this.X.doubleSup() + "]");
        System.out.print("(");
        for (int i = 0; i < dim; i++) {
            System.out.print(" [" + this.dX[i].doubleInf() + ", " + this.dX[i].doubleSup() + "]");
            //another formatting style
            // System.out.printf(" [%+10.4f, %+10.4f]\t", this.dX[i].doubleInf(), this.dX[i].doubleSup());
        }
        System.out.println(" )");
        for (int i = 0; i < dim; i++) {
            System.out.print("|");
            for (int j = 0; j < dim; j++) {
                System.out.printf(" [%+10.8f, %+10.8f]\t", this.ddX[i][j].doubleInf(), this.ddX[i][j].doubleSup());
            }
            System.out.println(" |");
        }
    }

}

