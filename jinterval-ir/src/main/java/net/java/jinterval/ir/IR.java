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
package net.java.jinterval.ir;


/**
 *  @author sz
 */
public class IR 
{
    
    public static void main( String[] args )
    {
		double x[][] = new double[][] {{1,2},{1,3},{1,4}};
		double y[] = new double[] {3,4,5};
		double e[] = new double[] {0.1,0.1,0.1};

        IRPredictor ir = new IRPredictor(x,y,e);
        if (ir.predictAtEveryDataPoint()){
            System.out.println("Predictions:");			
            for(int i=0; i<x.length; i++) {
                    System.out.println(i+": ["+ir.getMin(i)+", "+ir.getMax(i)+"]");
            }

            System.out.println("\nResiduals:");
            double[] r =ir.getResiduals(); 
            for(int i=0; i<r.length; i++) {
                    System.out.print(r[i]+" ");
            }

            System.out.println("\n\nBoundary:");

            int[] b =ir.getBoundary(); 
            for(int i=0; i<b.length; i++) {
                System.out.print(b[i]+" ");
            }		
		}
		else {
            System.out.println("No solution! "+"("+ir.getExitCode()+")");
		}
        
        IREstimator irest = new IREstimator(x,y,e);
        if (irest.estimateAll()){
            System.out.println("\n\nEstimates:");			
            for(int i=0; i<x[0].length; i++) {
                System.out.println(i+": ["+irest.getMin(i)+", "+irest.getMax(i)+"]");
            }
		}
		else {
            System.out.println("No solution! "+"("+irest.getExitCode()+")");
		}

        
    }
}
