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

import net.java.jinterval.interval.set.SetInterval;
import net.java.jinterval.interval.set.SetIntervalOps;
import net.java.jinterval.linear.RationalVector;
import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalOps;
import org.apache.commons.math3.exception.DimensionMismatchException;
import org.apache.commons.math3.exception.NullArgumentException;
import org.apache.commons.math3.util.MathUtils;

public class ShaidurovTolBoxDimention {
    
    private ExtendedRational radius;
    private IntervalVector box;
    private boolean debug;
    
    public ExtendedRational getRadius () {
        return ExtendedRationalOps.abs(radius);
    }
    
    public IntervalVector getBrus () {
        return box;
    }
    
    public ShaidurovTolBoxDimention (IntervalMatrix a, IntervalVector b, ExtendedRational[] y, boolean debug) {
        this.debug = debug;
        this.CalculateBoxDimention(a, b, y);
    }
    
    public ShaidurovTolBoxDimention (IntervalMatrix a, IntervalVector b, ExtendedRational[] y) {
        this(a, b, y, false);
    }
      
    private void CalculateBoxDimention (IntervalMatrix a, IntervalVector b, ExtendedRational[] y) {
        int rowCount = a.getRowDimension();
        int columnCount = a.getColumnDimension();
        
        if (this.debug) {
            System.out.println("m: " + rowCount + " n: " + columnCount);
        }
        
        
        IntervalVector r = new IntervalVector(rowCount);
        
        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
            SetInterval numeratorSummInterval = SetIntervalOps.nums2(0, 0);
            ExtendedRational denominator = ExtendedRational.zero();
            
            for (int columnIndex = 0 ; columnIndex < columnCount; columnIndex++) {
                ExtendedRational yComponent = y[columnIndex];
                SetInterval yComponentInterval = SetIntervalOps.nums2(yComponent, yComponent);
                SetInterval numeratorSummIntervalComponent = SetIntervalOps.mul(a.getEntry(rowIndex, columnIndex), yComponentInterval);
                numeratorSummInterval = SetIntervalOps.add(numeratorSummInterval, numeratorSummIntervalComponent);
                
                denominator = ExtendedRationalOps.add(denominator, a.getEntry(rowIndex, columnIndex).mag());
                
                if (this.debug) {
                    System.out.println("i: " + rowIndex + " j: " + columnIndex + " numSumm: " + numeratorSummInterval);
                    System.out.println("i: " + rowIndex + " j: " + columnIndex + " denSumm: " + denominator.floatValue());
                }               
            }
            
            // R(i) = (rad(b(i)) - abs(mid(b(i)) - numeratorSummInterval)) / denominator;
            SetInterval midInterval = SetIntervalOps.nums2(b.getEntry(rowIndex).mid(), b.getEntry(rowIndex).mid());
            SetInterval numerator = SetIntervalOps.sub(midInterval, numeratorSummInterval);
            
            if (this.debug) {
                System.out.println("i: " + rowIndex + " midInterval: " + midInterval);
                System.out.println("i: " + rowIndex + " numeratorStep1: " + numerator);
            }
            
            numerator = SetIntervalOps.abs(numerator);
            SetInterval radInterval = SetIntervalOps.nums2(b.getEntry(rowIndex).rad(), b.getEntry(rowIndex).rad());
            
            if (this.debug) {
                System.out.println("i: " + rowIndex + " radInterval: " + midInterval);
                System.out.println("i: " + rowIndex + " numeratorAbs: " + numerator);
            }
            
            numerator = SetIntervalOps.sub(radInterval, numerator);
             
            SetInterval denominatorInterval = SetIntervalOps.nums2(denominator, denominator);
            SetInterval rComponent = SetIntervalOps.div(numerator, denominatorInterval);
            
            if (this.debug) {
                System.out.println("i: " + rowIndex + " numeratorStep2: " + numerator);
                System.out.println("i: " + rowIndex + " rComponent: " + rComponent);
            }
            
            r.setEntry(rowIndex, rComponent);
        }
        
        RationalVector infRVector = r.getInf();
        this.radius = infRVector.getMinValue();
        
        if (this.debug) {
            System.out.println("radius: " + this.radius);
        }
        
        this.BuildBox(y);
    }
    
    private void BuildBox (ExtendedRational[] y) {
        int rowCount = y.length;
        
        this.box = new IntervalVector(rowCount);
        
        SetInterval e = SetIntervalOps.nums2(-1, 1);
        SetInterval radiusInterval = SetIntervalOps.nums2(this.radius, this.radius);
        
        for (int index = 0; index < rowCount; index++) {
            SetInterval yInterval = SetIntervalOps.nums2(y[index], y[index]);
            SetInterval boxComponent = SetIntervalOps.mul(radiusInterval, e);
            boxComponent = SetIntervalOps.add(yInterval, boxComponent);
            
            if (this.debug) {
                System.out.println("i: " + index + " boxComponent: " + boxComponent);
            }
            
            this.box.setEntry(index, boxComponent);
        }
    }
    
    private static void checkParameters(IntervalMatrix a, IntervalVector b) 
            throws NullArgumentException, DimensionMismatchException {
        MathUtils.checkNotNull(a);
        MathUtils.checkNotNull(b);
        
        if (b.getDimension() != a.getRowDimension()) {
            throw new DimensionMismatchException(b.getDimension(),
                    a.getRowDimension());
        }
    }   
}
