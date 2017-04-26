package ru.nsc.interval.globalopt;

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;
import net.java.jinterval.rational.*;

import java.util.Arrays;


public class Gradient {
    /**
     *   Gradient class for interval computing on Java.
     *   With this class you can compute partial derivatives and the range of values for some functions.
     *   Here was used the idea of automatic differentiation.
     *   JInterval library was used for all interval arithmetic and functions.
     */
    private static SetIntervalContext ic; //This field determine accuracy of computing.
    private static int dim; //Represents the number of variables.
    private SetInterval X; //Interval value of expression.
    private SetInterval[] dX; //Interval values of derivative.
    private SetInterval[][] ddX;
    private static final SetInterval ZERO = SetIntervalContexts.getExact().numsToInterval(0,0);
    private static final SetInterval ONE = SetIntervalContexts.getExact().numsToInterval(1, 1);

    public Gradient() {
        X = null;
        dX = null;
        ddX = null;
    }

    public Gradient(SetInterval box, SetIntervalContext ic) {
        dim = 1;
        dX = new SetInterval[1];
        ddX = new SetInterval[1][1];
        dX[0] = ONE;
        for (SetInterval[] row: ddX) {
            Arrays.fill(row, ZERO);
        }
        X = box;
        Gradient.ic = ic;
    }

    private void hessianFill() {
        for (int i = 1; i < dim; i++)
            for (int j = i-1; j >= 0; j--) {
                this.ddX[i][j] = this.ddX[j][i];
            }
    }

    public static Gradient[] init(SetInterval[] box, SetIntervalContext ic) {
        dim = box.length;
        Gradient.ic = ic;
        Gradient[] result = new Gradient[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = new Gradient();
            result[i].dX = new SetInterval[dim];
            result[i].ddX = new SetInterval[dim][dim];
            result[i].X = box[i];
            for (SetInterval[] row: result[i].ddX) {
                Arrays.fill(row, ZERO);
            }
            for (int j = 0; j < i; j++) {
                result[i].dX[j] = ZERO;
            }
            result[i].dX[i] = ONE;
            for (int j = i + 1; j < dim; j++) {
                result[i].dX[j] = ZERO;
            }
        }
        return result;
    }

    public static Gradient num(double number) {
        Gradient result = new Gradient();
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(number,number);
        return result;
    }

    public static Gradient num(Rational number) {
        Gradient result = new Gradient();
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(number,number);
        return result;
    }

    public static Gradient num(ExtendedRational number) {
        Gradient result = new Gradient();
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(number,number);
        return result;
    }

    public static Gradient nums(double lower,double upper) {
        Gradient result = new Gradient();
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(lower,upper);
        return result;
    }

    public static Gradient nums(Rational lower,Rational upper) {
        Gradient result = new Gradient();
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(lower,upper);
        return result;
    }

    public static Gradient nums(ExtendedRational lower,ExtendedRational upper) {
        Gradient result = new Gradient();
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (SetInterval[] row: result.ddX) {
            Arrays.fill(row, ZERO);
        }
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ZERO;
        }
        result.X = SetIntervalContexts.getExact().numsToInterval(lower,upper);
        return result;
    }

    public Gradient neg() {
        Gradient result = new Gradient();
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        result.X = ic.neg(X);
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(dX[i]);
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j]=ic.neg(ddX[i][j]);
            }
        }
        return result;
    }

    public Gradient intersection(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.intersection(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.intersection(this.dX[i],Y.dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j]=ic.intersection(this.ddX[i][j],Y.ddX[i][j]);
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient intersection(GradientMV Y) {
        Gradient result = new Gradient();
        result.X = ic.intersection(this.X, Y.getX());
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.intersection(this.dX[i],Y.getDX()[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j]=ic.intersection(this.ddX[i][j],Y.getDDX()[i][j]);
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient intersectionX(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.intersection(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = this.dX[i];
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        return result;
    }

    public Gradient intersectionX(SetInterval Y) {
        Gradient result = new Gradient();
        result.X = ic.intersection(this.X, Y);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = this.dX[i];
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        return result;
    }

    public Gradient intersectionDX(Gradient Y) {
        Gradient result = new Gradient();
        result.X = this.X;
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.intersection(this.dX[i], Y.dX[i]);
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        return result;
    }

    public Gradient intersectionDX(SetInterval[] Y) {
        Gradient result = new Gradient();
        result.X = this.X;
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.intersection(this.dX[i], Y[i]);
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        return result;
    }

    public Gradient intersectionDXInd(Gradient Y, int ind) {
        Gradient result = new Gradient();
        result.X = this.X;
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = this.dX[i];
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        result.dX[ind] = ic.intersection(this.dX[ind],Y.dX[ind]);
        return result;
    }

    public Gradient intersectionDXInd(SetInterval Y, int ind) {
        Gradient result = new Gradient();
        result.X = this.X;
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = this.dX[i];
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        result.dX[ind] = ic.intersection(this.dX[ind],Y);
        return result;
    }

    public Gradient intersectionDXInd(SetInterval[] Y, int ind) {
        Gradient result = new Gradient();
        result.X = this.X;
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = this.dX[i];
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        result.dX[ind] = ic.intersection(this.dX[ind],Y[ind]);
        return result;
    }

    public Gradient hull(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.convexHull(this.X,Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.convexHull(this.dX[i],Y.dX[i]);
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = ic.convexHull(this.ddX[i][j],Y.ddX[i][j]);
            }
        }
        return result;
    }

    public Gradient add(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.add(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.add(this.dX[i],Y.dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.add(this.ddX[i][j],Y.ddX[i][j]);
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient sub(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.sub(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.sub(this.dX[i],Y.dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.sub(this.ddX[i][j],Y.ddX[i][j]);
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient mul(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.mul(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.add(ic.mul(this.X, Y.dX[i]),ic.mul(this.dX[i],Y.X));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.add(ic.add(ic.mul(this.ddX[i][j],Y.X),ic.add(ic.mul(this.dX[i],Y.dX[j]),ic.mul(this.dX[j],Y.dX[i])))
                        ,ic.mul(this.X,Y.ddX[i][j]));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient div(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.div(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.sub(ic.div(this.dX[i],Y.X),ic.div(ic.mul(this.X,Y.dX[i]),ic.sqr(Y.X)));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] =ic.add(ic.sub(ic.div(this.ddX[i][j],Y.X),
                        ic.div(
                            ic.add(ic.add(ic.mul(this.dX[i],Y.dX[j]),ic.mul(this.dX[j],Y.dX[i])),ic.mul(this.X,Y.ddX[i][j])),ic.sqr(Y.X))),
                                ic.mul(ic.numsToInterval(2,2),ic.div(ic.mul(this.X,ic.mul(Y.dX[i],Y.dX[j])),ic.pown(Y.X,3))));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient recip() {
        Gradient result = new Gradient();
        result.X = ic.recip(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(ic.div(this.dX[i],ic.sqr(this.X)));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] =ic.sub(
                    ic.mul(ic.numsToInterval(2,2),ic.div(ic.mul(this.dX[i],this.dX[j]),ic.pown(this.X,3))),
                    ic.div(this.ddX[i][j],ic.sqr(this.X)));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient pow(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.pow(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.mul(Y.X, ic.pow(X,ic.sub(Y.X, ic.numsToInterval(1,1)))),this.dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.mul(ic.mul(Y.X,ic.pow(this.X,ic.sub(Y.X,ic.numsToInterval(2,2)))),
                        ic.add(ic.mul(ic.mul(ic.sub(Y.X,ic.numsToInterval(1,1)),this.dX[i]),this.dX[j]),
                                ic.mul(this.X,this.ddX[i][j])));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient pow(double P) {
        Gradient result = new Gradient();
        SetInterval Y = ic.numsToInterval(P,P);
        result.X = ic.pow(this.X, Y);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.mul(Y, ic.pow(X,ic.sub(Y, ic.numsToInterval(1,1)))),this.dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.mul(ic.mul(Y,ic.pow(this.X,ic.sub(Y,ic.numsToInterval(2,2)))),
                        ic.add(ic.mul(ic.mul(ic.sub(Y,ic.numsToInterval(1,1)),this.dX[i]),this.dX[j]),
                                ic.mul(this.X,this.ddX[i][j])));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient sqr() {
        Gradient result = new Gradient();
        result.X = ic.sqr(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.mul(ic.numsToInterval(2,2),X),this.dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.mul(ic.numsToInterval(2,2),ic.add(ic.mul(this.dX[j],this.dX[i]),ic.mul(this.X,this.ddX[i][j])));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient sqrt() {
        Gradient result = new Gradient();
        result.X = ic.sqrt(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.div(dX[i], ic.mul(ic.numsToInterval(2,2),ic.sqrt(X)));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.div(ic.sub(ic.mul(ic.mul(this.ddX[i][j],ic.numsToInterval(2,2)),this.X),ic.mul(this.dX[i],this.dX[j])),
                        ic.mul(ic.numsToInterval(4,4),ic.sqrt(ic.pown(this.X,3))));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient abs() {
        Gradient result = new Gradient();
        result.X = ic.intersection(this.X,ic.numsToInterval(1, Double.POSITIVE_INFINITY));
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = /*ic.convexHull(ic.neg(this.dX[i]),this.dX[i]);*/this.dX[i];
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient sin() {
        Gradient result = new Gradient();
        result.X = ic.sin(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.cos(X),dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.add(ic.mul(ic.mul(ic.neg(ic.sin(this.X)),this.dX[i]),this.dX[j]),
                        ic.mul(ic.cos(this.X),this.ddX[i][j]));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient cos() {
        Gradient result = new Gradient();
        result.X = ic.cos(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(ic.mul(ic.sin(X),dX[i]));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.neg(ic.add(ic.mul(ic.mul((ic.cos(this.X)),this.dX[i]),this.dX[j]),
                        ic.mul(ic.sin(this.X),this.ddX[i][j])));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient tan() {
        Gradient result = new Gradient();
        result.X = ic.tan(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.div(ic.numsToInterval(1,1),ic.sqr(ic.cos(X))),dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.div(ic.add(ic.mul(this.ddX[i][j],ic.sqr(ic.cos(this.X))),
                        ic.mul(ic.mul(ic.sin(ic.mul(ic.numsToInterval(2,2),this.X)),this.dX[i]),this.dX[j])),
                        ic.pown(ic.cos(this.X),4));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient acos() {
        Gradient result = new Gradient();
        result.X = ic.acos(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.neg(ic.div(dX[i],ic.sqrt(ic.sub(ic.numsToInterval(1,1),ic.sqr(X)))));
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.neg(ic.div(ic.add(ic.mul(this.ddX[i][j],ic.sub(ic.numsToInterval(1,1),ic.sqr(this.X))),
                        ic.mul(ic.mul(this.X,this.dX[i]),this.dX[j])),
                            ic.pow(ic.sub(ic.numsToInterval(1,1),ic.sqr(this.X)),ic.numsToInterval(1.5,1.5))));
             }
        }
        result.hessianFill();
        return result;
    }

    public Gradient atan() {
        Gradient result = new Gradient();
        result.X = ic.atan(this.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.div(ic.numsToInterval(1,1),ic.add(ic.numsToInterval(1,1),ic.sqr(X))),dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.div(ic.sub(ic.mul(this.ddX[i][j],ic.add(ic.numsToInterval(1,1),ic.sqr(this.X))),
                        ic.mul(ic.mul(ic.mul(ic.numsToInterval(2,2),this.X),this.dX[i]),this.dX[j])),
                        ic.sqr(ic.add(ic.numsToInterval(1,1),ic.sqr(this.X))));
            }
        }
        result.hessianFill();
        return result;
    }

    public Gradient max(Gradient Y) {
        Gradient result = new Gradient();
        result.X = ic.max(this.X, Y.X);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
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
        return result;
    }

    public Gradient rootn(int q) {
        Gradient result = new Gradient();
        SetInterval Y = ic.recip(ic.numsToInterval(q,q));
        result.X = ic.pow(this.X, Y);
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = ic.mul(ic.mul(Y, ic.pow(X,ic.sub(Y, ic.numsToInterval(1,1)))),this.dX[i]);
            for (int j = i; j < dim; j++) {
                result.ddX[i][j] = ic.mul(ic.mul(Y,ic.pow(this.X,ic.sub(Y,ic.numsToInterval(2,2)))),
                        ic.add(ic.mul(ic.mul(ic.sub(Y,ic.numsToInterval(1,1)),this.dX[i]),this.dX[j]),
                                ic.mul(this.X,this.ddX[i][j])));
            }
        }
        result.hessianFill();
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

    public SetInterval[] getDDXInd(int i) {
        SetInterval[] result = new SetInterval[dim];
        for (int j = 0; j < dim; j++) {
            result[j] = ddX[i][j];
        }
        return result;
    }

    public static double getDim() {return dim;}

    public Gradient copy() {
        Gradient result = new Gradient();
        result.X = this.X;
        result.dX = new SetInterval[dim];
        result.ddX = new SetInterval[dim][dim];
        for (int i = 0; i < dim; i++) {
            result.dX[i] = this.dX[i];
            for (int j = 0; j < dim; j++) {
                result.ddX[i][j] = this.ddX[i][j];
            }
        }
        return result;
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
