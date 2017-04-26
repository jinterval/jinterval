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

import com.cflex.util.lpSolve.LpConstant;
import com.cflex.util.lpSolve.LpModel;
import com.cflex.util.lpSolve.LpSolver;
import java.util.ArrayList;


//import org.apache.commons.math3.exception.MathIllegalArgumentException;

//TODO: Add exceptions and throws
public class IRPredictor {
    private double[][] X;
    private double[]   Y;
    private double[]   E;
    private boolean dataAreGiven;
    
    // Number of observations
    private int ObsNumber;

    // Number of variables
    private int VarNumber;
    
    // Storage for predictions
    private double PredictionMin;
    private double PredictionMax;
    private double[] PredictionMins;
    private double[] PredictionMaxs;
    
    // Last error
    int ExitCode;
    
    public IRPredictor(){
        ObsNumber = 0;
        VarNumber = 0;
        dataAreGiven = false;
    }

    public IRPredictor(double[][] X, double[] Y, double[] E){
        setData(X,Y,E);
    }
    
    public final void setData(double[][] X, double[] Y, double[] E) 
    //        throws IllegalDimensionException 
    {
//        if(X.length != Y.length || X.length != E.length) 
//            throw IllegalDimensionException;
        
        this.X=X;
        this.Y=Y;
        this.E=E;

        ObsNumber = X.length;
        VarNumber = X[0].length;
        
        dataAreGiven = true;
    }
    
    public int getExitCode() {
        return ExitCode;
    }    
    
    private boolean solveLpp(double[] Objective)
       // throws IllegalDimensionException 
    {
        if (Objective.length != VarNumber){
           // throw IllegalDimensionException;
            ExitCode = -1;
            return false;
        }
        
      try {
        // Init LP Solver
        LpModel Lpp = new LpModel(0, VarNumber);
        
        // Define LPP
        double[] zObjective = new double[VarNumber+1];
        System.arraycopy(Objective, 0, zObjective, 1, VarNumber);
        Lpp.setObjFn(zObjective);

        double[] zX=new double[VarNumber+1];
        for (int i=0; i<ObsNumber; i++) {				
            System.arraycopy(X[i], 0, zX, 1, VarNumber);
            Lpp.addConstraint(zX, LpConstant.LE, Y[i]+E[i]);
            Lpp.addConstraint(zX, LpConstant.GE, Y[i]-E[i]);
//            Solver.add_constraint(Lpp, zX, constant.LE, Y[i]+E[i]);
//            Solver.add_constraint(Lpp, zX, constant.GE, Y[i]-E[i]);
	}
              
        //Solver.set_minim(Lpp);
        //Lpp.setMinimum();
        
        LpSolver Solver = new LpSolver(Lpp);

        ExitCode = Solver.solve();
//        ExitCode = Solver.solve(Lpp);
        switch ( ExitCode ) {
            case LpConstant.OPTIMAL:
                PredictionMin = Lpp.getBestSolution(0);
                break;
            case LpConstant.INFEASIBLE:
                //throw InfeasibleException
            case LpConstant.UNBOUNDED:            
                //throw UnboundedException
        }
        
//        Solver.set_maxim(Lpp);
        Lpp.setMaximum();
        ExitCode = Solver.solve();
        switch ( ExitCode ) {
            case LpConstant.OPTIMAL:
                PredictionMax = Lpp.getBestSolution(0);
                break;
            case LpConstant.INFEASIBLE:
                //throw InfeasibleException
            case LpConstant.UNBOUNDED:            
                //throw UnboundedException
        }
      } catch (Exception e){
          //e.printStackTrace();
      }
      return ExitCode == LpConstant.OPTIMAL;
    }

           
    public boolean isDataConsistent(){
        return solveLpp(X[0]);
    }
    
    public void compressData(){
    }

    public boolean predictAt(double[] x){
        return solveLpp(x);
    }
    
    public boolean predictAtEveryDataPoint(){ 
        PredictionMins = new double[ObsNumber];
        PredictionMaxs = new double[ObsNumber];

        boolean Solved = true;
        for (int i=0; i<ObsNumber; i++){
            Solved = Solved && predictAt(X[i]);
            if(!Solved) {
                break;
            }
            PredictionMins[i] = getMin();
            PredictionMaxs[i] = getMax();
        }
        return Solved;
    }
    
    public double getMin(){
        return PredictionMin;
    }

    public double getMax(){
        return PredictionMax;
    }

    public double getMin(int i) {
        return PredictionMins[i];
    }

    public double getMax(int i) {
        return PredictionMaxs[i];
    }

    public double[] getMins() {
        return PredictionMins;
    }

    public double[] getMaxs() {
        return PredictionMaxs;
    }
    
    public double[] getResiduals(){
       //Residuals=(y-(vmax+vmin)/2)/beta
        double v;
        double[] residuals = new double[ObsNumber];

        for(int i=0; i<ObsNumber; i++) {
            v = (PredictionMins[i]+PredictionMaxs[i])/2;
            residuals[i] = (Y[i]-v)/E[i];
        }
        
        return residuals;	    
    }
    
    public double[] getLeverages(){
       //Leverage=((vmax-vmin)/2)/beta
        double v;
        double[] leverages = new double[ObsNumber];

        for(int i=0; i<ObsNumber; i++) {
            v = (PredictionMaxs[i]-PredictionMins[i])/2;
            leverages[i] = v/E[i];
        }

        return leverages;        
    }

  
    public int[] getBoundary(){
        final double EPSILON = 1.0e-6;
        ArrayList<Integer> boundary = new ArrayList<Integer>();

        double yp, ym, vp, vm;				

        for (int i=0; i<ObsNumber; i++){
            yp = Y[i]+E[i];
            vp = PredictionMaxs[i];
            ym = Y[i]-E[i];
            vm = PredictionMins[i];

            if ( Math.abs(yp - vp) < EPSILON || Math.abs(ym - vm) < EPSILON ) {  
                boundary.add(1);
            }
            else {
                boundary.add(0);
            }
        }		

        int[] a_boundary = new int[boundary.size()];
        for (int i=0; i<a_boundary.length; i++){
            a_boundary[i] = boundary.get(i).intValue();
        }

        return a_boundary;        
    }
    
    public int[] getBoundaryNumbers(){
        int Count = 0;
        int[] boundary = getBoundary();
        for (int i=0; i<boundary.length; i++){
            if(boundary[i] == 1) {
                Count++;
            }
        }
        
        int j = 0;
        int[] numbers = new int[Count];
        for (int i=0; i<boundary.length; i++){
            if(boundary[i] == 1) {
                numbers[j++] = i;
            }
        }
        
        return numbers;
    }

//TODO: Implement getOutliers()
//    public int[] getOutliers(){
//    
//    }

//TODO: Implement getOutliersNumbers()
//    public int[] getOutliersNumbers(){
//    
//    }

    public double[] getOutliersWeights(){

        double[] outliers = new double[ObsNumber];
        for(int i=0; i<ObsNumber; i++) {
            outliers[i]=0;
        }

        try {
            LpModel Lpp = new LpModel(0, ObsNumber+VarNumber);

            // Build and set objective of LPP
            double[] zObjective = new double[ObsNumber+VarNumber+1];
            for(int i=1;i<=VarNumber; i++) {
                zObjective[i] = 0;
            }
            for(int i=1;i<=ObsNumber; i++) {
                zObjective[VarNumber+i] = 1;
            }
            Lpp.setObjFn(zObjective);
            //Solver.set_minim(Lpp);

            // Build and set constraints of LPP
            double[] Row = new double[ObsNumber+VarNumber+1];
            for (int i=0; i<ObsNumber; i++) {
                for (int j=1; j<=VarNumber; j++) {
                    Row[j]=X[i][j-1];
                }
                for(int j=1; j<=ObsNumber; j++) {
                    Row[VarNumber+j] = 0;
                }
                Row[VarNumber+i+1] = -E[i];
    //            Solver.add_constraint(Lpp, Row, constant.LE, Y[i]);
                Lpp.addConstraint(Row, LpConstant.LE, Y[i]);

                Row[VarNumber+i+1] = E[i];
    //            Solver.add_constraint(Lpp, Row, constant.GE, Y[i]);
                Lpp.addConstraint(Row, LpConstant.GE, Y[i]);

                for (int j=1; j<=ObsNumber+VarNumber; j++) {
                    Row[j] = 0;
                }            
                Row[VarNumber+i+1] = 1;
    //            Solver.add_constraint(Lpp, Row, constant.GE, 1);
                Lpp.addConstraint(Row, LpConstant.GE, 1);

            }

            // Solve LPP and get outliers' weights
            LpSolver Solver = new LpSolver(Lpp);
            ExitCode = Solver.solve();        

            for(int i = 0; i < ObsNumber; i++) {
                outliers[i] = Lpp.getBestSolution(Lpp.getRows()+VarNumber+i+1);
            }
        } catch(Exception e){
            //e.printStackTrace();
        }
    
        return outliers;
    }
    
}

