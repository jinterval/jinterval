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
import net.java.jinterval.linear.ArrayRationalVector;
import net.java.jinterval.linear.RationalVector;

/**
 * Dummy interval vector in Commons Math style
 *
 * @author sz
 */
public class IntervalVector {

    private final IntervalMatrix m;

    public IntervalVector(int dimension) {
        this.m = new IntervalMatrix(dimension, 1);
    }

    public IntervalVector(int dimension, SetInterval v) {
        this.m = new IntervalMatrix(dimension, 1, v);
    }

    public IntervalVector(SetInterval... v) {
        this.m = new IntervalMatrix(v.length, 1);
        for (int i = 0; i < v.length; i++) {
            m.setEntry(i, 0, v[i]);
        }
    }

    public IntervalVector(RationalVector inf, RationalVector sup) {
        this.m = new IntervalMatrix(inf.getDimension(), 1);
        for (int i = 0; i < inf.getDimension(); i++) {
            m.setEntry(i, 0, SetIntervalOps.nums2(inf.getEntry(i), sup.getEntry(i), Decoration.COM));
        }
    }

    public IntervalVector(RationalVector v) {
        this.m = new IntervalMatrix(v.getDimension(), 1);
        for (int i = 0; i < v.getDimension(); i++) {
            m.setEntry(i, 0, SetIntervalOps.nums2(v.getEntry(i), v.getEntry(i), Decoration.COM));
        }
    }

    IntervalVector copy() {
        IntervalVector v = new IntervalVector(this.m.getRowDimension());
        for (int i = 0; i < v.getDimension(); i++) {
            v.setEntry(i, this.getEntry(i));
        }
        return v;
    }

    public int getDimension() {
        return this.m.getRowDimension();
    }

    public SetInterval getEntry(int i) {
        return this.m.getEntry(i, 0);
    }

    public void setEntry(int i, SetInterval value) {
        this.m.setEntry(i, 0, value);
    }

    public void set(SetInterval value) {
        for (int i = 0; i < getDimension(); i++) {
            this.m.setEntry(i, 0, value);
        }
    }

    public RationalVector getInf() {
        RationalVector r = new ArrayRationalVector(getDimension());
        for (int i = 0; i < getDimension(); i++) {
            r.setEntry(i, getEntry(i).inf());
        }
        return r;
    }

    public RationalVector getSup() {
        RationalVector r = new ArrayRationalVector(getDimension());
        for (int i = 0; i < getDimension(); i++) {
            r.setEntry(i, getEntry(i).sup());
        }
        return r;
    }
    
    public RationalVector getMid() {
        RationalVector r = new ArrayRationalVector(getDimension());
        for (int i = 0; i < getDimension(); i++) {
            r.setEntry(i, getEntry(i).mid());
        }
        return r;
    }
    
    public RationalVector getRad() {
        RationalVector r = new ArrayRationalVector(getDimension());
        for (int i = 0; i < getDimension(); i++) {
            r.setEntry(i, getEntry(i).rad());
        }
        return r;
    }
            
    public RationalVector mag() {
        return this.m.mag().getColumnVector(0);
    }

    public RationalVector mig() {
        return this.m.mig().getColumnVector(0);
    }

    @Override
    public String toString() {
        return m.toString();
    }
}
