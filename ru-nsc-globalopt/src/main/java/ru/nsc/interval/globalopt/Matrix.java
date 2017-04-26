package ru.nsc.interval.globalopt;

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalContext;
import net.java.jinterval.interval.set.SetIntervalContexts;

import java.lang.reflect.Member;

class Matrix {
    private SetInterval[][] matrix;

    private static SetIntervalContext ic = SetIntervalContexts.getPlain();
    private static final SetInterval ZERO = SetIntervalContexts.getExact().numsToInterval(0,0);
    private static final SetInterval ONE = SetIntervalContexts.getExact().numsToInterval(1, 1);

    Matrix() {
        matrix = null;
    }

    Matrix(int rSize, int cSize) {
        matrix = new SetInterval[rSize][cSize];
    }

    Matrix(int rSize) {
        matrix = new SetInterval[rSize][1];
    }

    Matrix(SetInterval[][] A) {
        this.matrix = new SetInterval[A.length][A[0].length];
        for (int i = 0; i < A.length; i++) {
            for (int j = 0; j < A[0].length; j++) {
                this.matrix[i][j] = A[i][j];
            }
        }
    }

    Matrix (SetInterval[] A) {
        matrix = new SetInterval[A.length][1];
        for (int i = 0; i < A.length; i++) {
            matrix[i][0] = A[i];
        }
    }

    static Matrix identity(int size) {
        Matrix result = new Matrix(size,size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j)
                    result.matrix[i][j] = ONE;
                else
                    result.matrix[i][j] = ZERO;
            }
        }
        return result;
    }

    Matrix[] LU() {
        if (this.matrix.length == this.matrix[0].length) {
            Matrix[] result = new Matrix[2];
            result[0] = new Matrix(this.matrix.length, this.matrix.length);
            result[1] = new Matrix(this.matrix.length, this.matrix.length);
            for (int i = 0; i < this.matrix.length; i++) {
                for (int j = 0; j < this.matrix.length; j++) {
                    result[1].matrix[0][i] = this.matrix[0][i];
                    result[0].matrix[i][0] = ic.div(this.matrix[i][0],result[1].matrix[0][0]);
                    SetInterval sum = ZERO;
                    for (int k = 0; k < i; k++) {
                        sum = ic.add(sum, ic.mul(result[0].matrix[i][k],result[1].matrix[k][j]));
                    }
                    result[1].matrix[i][j] = ic.sub(this.matrix[i][j],sum);
                    if (i > j)
                        result[0].matrix[j][i] = ZERO;
                    else {
                        sum = ZERO;
                        for (int k = 0; k < i; k++) {
                            sum = ic.add(sum, ic.mul(result[0].matrix[j][k],result[1].matrix[k][i]));
                        }
                        result[0].matrix[j][i] = ic.div(ic.sub(this.matrix[j][i],sum),result[1].matrix[i][i]);
                    }
                }
            }
            return result;
        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix inverse() {
        if(this.matrix.length == this.matrix[0].length) {
            Matrix[] LU = this.LU();
            Matrix y = new Matrix(this.matrix.length,this.matrix.length);
            Matrix x = new Matrix(this.matrix.length,this.matrix.length);
            Matrix identity = identity(this.matrix.length);
            for (int i = 0; i < this.matrix.length; i++) {
                for (int j = 0; j < this.matrix.length; j++) {
                    y.matrix[i][j] = ZERO;
                    for (int k = 0; k < j; k++) {
                        y.matrix[i][j] = ic.add(y.matrix[i][j],ic.mul(LU[0].matrix[j][k],y.matrix[i][k]));
                    }
                    y.matrix[i][j] = ic.div(ic.sub(identity.matrix[i][j],y.matrix[i][j]),LU[0].matrix[j][j]);
                }
            }
            for (int i = 0; i < this.matrix.length; i++) {
                for (int j = this.matrix.length - 1; j >= 0; j--) {
                    x.matrix[i][j] = ZERO;
                    for (int k = j; k < this.matrix.length; k++) {
                        x.matrix[i][j] = ic.add(x.matrix[i][j],ic.mul(LU[1].matrix[j][k],x.matrix[i][k]));
                    }
                    x.matrix[i][j] = ic.div(ic.sub(y.matrix[i][j],x.matrix[i][j]),LU[1].matrix[j][j]);
                }
            }
            return x.transp();
        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix transp() {
        Matrix result = new Matrix(this.matrix[0].length,this.matrix.length);
        for (int i = 0; i < this.matrix[0].length; i++) {
            for (int j = 0; j < this.matrix.length; j++) {
                result.matrix[i][j] = this.matrix[j][i];
            }
        }
        return result;
    }

    Matrix mul(Matrix A) {
        if (this.matrix[0].length == A.matrix.length) {
            Matrix result;
            if (A.matrix[0].length == 1) {
                result = new Matrix(this.matrix.length);
                for (int i = 0; i < this.matrix.length; i++) {
                    result.matrix[i][0] = ZERO;
                    for (int j = 0; j < A.matrix.length; j++) {
                        result.matrix[i][0] = ic.add(result.matrix[i][0],ic.mul(this.matrix[i][j],A.matrix[j][0]));
                    }
                }
            }
            else {
                result = new Matrix(this.matrix.length,A.matrix[0].length);
                for (int i = 0; i < this.matrix.length; i++) {
                    for (int j = 0; j < A.matrix[0].length; j++) {
                        result.matrix[i][j] = ZERO;
                        for (int k = 0; k < A.matrix[0].length; k++) {
                            result.matrix[i][j] = ic.add(result.matrix[i][j],ic.mul(this.matrix[i][k],A.matrix[k][j]));
                        }
                    }
                }
            }
            return result;
        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix mul(SetInterval[][] A) {
        if (this.matrix[0].length == A.length) {
            Matrix result = new Matrix(this.matrix.length,A[0].length);
            for (int i = 0; i < this.matrix.length; i++) {
                for (int j = 0; j < A[0].length; j++) {
                    result.matrix[i][j] = ZERO;
                    for (int k = 0; k < A[0].length; k++) {
                        result.matrix[i][j] = ic.add(result.matrix[i][j],ic.mul(this.matrix[i][k],A[k][j]));
                    }
                }
            }
            return result;
        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix mul(SetInterval[] A) {
        if (this.matrix[0].length == A.length) {
            Matrix result = new Matrix(this.matrix.length);
            for (int i = 0; i < this.matrix.length; i++) {
                result.matrix[i][0] = ZERO;
                for (int j = 0; j < A.length; j++)
                    result.matrix[i][0] = ic.add(result.matrix[i][0],ic.mul(this.matrix[i][j],A[j]));
            }
            return result;
        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix add(SetInterval[][] A) {
        if ((this.matrix.length == A.length) && (this.matrix[0].length == A[0].length))
        {/*Gradient[] box = Gradient.init(new SetInterval[]{ic.numsToInterval(19.1,55.2), ic.numsToInterval(15.2,34.8), ic.numsToInterval(0,1.18)},ic);
            IAOGO alghoritm = new IAOGO();*/
            Matrix result = new Matrix(this.matrix.length, A[0].length);
            for (int i = 0; i < A.length; i++) {
                for (int j = 0; j < A[0].length; j++) {
                    result.matrix[i][j] = ic.add(A[i][j],this.matrix[i][j]);
                }
            }
            return result;

        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix add(Matrix A) {
        if ((this.matrix.length == A.matrix.length) && (this.matrix[0].length == A.matrix[0].length))
        {
            Matrix result = new Matrix(this.matrix.length, A.matrix[0].length);
            for (int i = 0; i < A.matrix.length; i++) {
                for (int j = 0; j < A.matrix[0].length; j++) {
                    result.matrix[i][j] = ic.add(A.matrix[i][j],this.matrix[i][j]);
                }
            }
            return result;

        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix sub(Matrix A) {
        if ((this.matrix.length == A.matrix.length) && (this.matrix[0].length == A.matrix[0].length))
        {
            Matrix result = new Matrix(this.matrix.length, A.matrix[0].length);
            for (int i = 0; i < A.matrix.length; i++) {
                for (int j = 0; j < A.matrix[0].length; j++) {
                    result.matrix[i][j] = ic.sub(A.matrix[i][j],this.matrix[i][j]);
                }
            }
            return result;

        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix sub(SetInterval[][] A) {
        if ((this.matrix.length == A.length) && (this.matrix[0].length == A[0].length))
        {
            Matrix result = new Matrix(this.matrix.length, A[0].length);
            for (int i = 0; i < A.length; i++) {
                for (int j = 0; j < A[0].length; j++) {
                    result.matrix[i][j] = ic.sub(A[i][j],this.matrix[i][j]);
                }
            }
            return result;

        }
        throw new ArrayIndexOutOfBoundsException();
    }

    Matrix mid() {
        Matrix result = new Matrix(this.matrix.length, this.matrix[0].length);
        for (int i = 0; i < this.matrix.length; i++) {
            for (int j = 0; j < this.matrix[0].length; j++) {
                result.matrix[i][j] = ic.numsToInterval(this.matrix[i][j].mid(),this.matrix[i][j].mid());
            }
        }
        return result;
    }

    SetInterval[] getVector() {
        if (matrix[0].length == 1) {
            SetInterval[] result = new SetInterval[matrix.length];
            for (int i = 0; i < result.length; i++) {
                result[i] = matrix[i][0];
            }
            return result;
        }
        throw new ArrayIndexOutOfBoundsException();
    }

    SetInterval[][] getMatrix() {
        return this.matrix;
    }

    SetInterval[] intersection(Gradient[] box) {
        SetInterval[] result = new SetInterval[box.length];
        for (int i = 0; i < box.length; i++) {
            result[i] = ic.intersection(this.matrix[i][0],box[i].getX());
        }
        return result;
    }

    void show() {
        for (int i = 0; i < this.matrix.length; i++) {
            for (int j = 0; j < this.matrix[0].length; j++) {
                System.out.printf(" [%+10.8f, %+10.8f]\t", this.matrix[i][j].doubleInf(), this.matrix[i][j].doubleSup());
            }
            System.out.println();
        }
    }

}
