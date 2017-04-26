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
package net.java.jinterval.ils;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.rational.ExtendedRational;

/**
 *
 */
public abstract class Sample {

    private final int rows, cols;
    private final double AInf[][];
    private final double ASup[][];
    private final double bInf[];
    private final double bSup[];
    private final IntervalVector x0;
    private final double xInf[];
    private final double xSup[];

    Sample(int rows, int cols,
            double[][] AInf, double[][] ASup,
            double[] bInf, double[] bSup,
            IntervalVector x0,
            double[] xInf, double[] xSup) {
        this.rows = rows;
        this.cols = cols;
        this.AInf = AInf;
        this.ASup = ASup;
        this.bInf = bInf;
        this.bSup = bSup;
        this.x0 = x0;
        this.xInf = xInf;
        this.xSup = xSup;
    }

    protected static SetInterval n2i(double inf, double sup) {
        return SetIntervalOps.nums2(inf, sup);
    }

    public IntervalMatrix getA() {
        SetInterval AData[][] = new SetInterval[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                AData[i][j] = SetIntervalOps.nums2(AInf[i][j], ASup[i][j], Decoration.COM);
            }
        }
        return new IntervalMatrix(AData);
    }

    public IntervalVector getb() {
        SetInterval bData[] = new SetInterval[rows];
        for (int i = 0; i < rows; i++) {
            bData[i] = SetIntervalOps.nums2(bInf[i], bSup[i], Decoration.COM);
        }
        return new IntervalVector(bData);
    }

    public IntervalVector getx0() {
        return x0;
    }

    public IntervalVector getx() {
        SetInterval xData[] = new SetInterval[rows];
        for (int i = 0; i < rows; i++) {
            xData[i] = SetIntervalOps.nums2(xInf[i], xSup[i], Decoration.COM);
        }
        return new IntervalVector(xData);
    }
}
