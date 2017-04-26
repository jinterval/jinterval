/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package net.java.jinterval.ir;

import com.cflex.util.lpSolve.LpConstant;
import com.cflex.util.lpSolve.LpModel;
import com.cflex.util.lpSolve.LpSolver;

/**
 *
 * @author sz
 */
public class IREstimator {
    private double[][] X;
    private double[]   Y;
    private double[]   E;
    private boolean dataAreGiven;
    
    // Number of observations
    private int ObsNumber;

    // Number of variables
    private int VarNumber;
    
    // Storage for parameters
    private double ParameterMin;
    private double ParameterMax;
    private double[] ParametersMins;
    private double[] ParametersMaxs;
    
    // Last error
    int ExitCode;
    
    public IREstimator(){
        ObsNumber = 0;
        VarNumber = 0;
        dataAreGiven = false;
    }

    public IREstimator(double[][] X, double[] Y, double[] E){
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
    
    private boolean solveLpp(int ParamNum)
       // throws IllegalDimensionException 
    {
        ParamNum++;
        if (ParamNum < 1 || ParamNum > VarNumber){
           // throw IllegalDimensionException;
            ExitCode = -1;
            return false;
        }
        
      try {
        // Init LP Solver
        LpModel Lpp = new LpModel(0, VarNumber);
        
        // Define LPP
        double[] zObjective = new double[VarNumber+1];
        for(int i=0; i<=VarNumber; i++) {
            zObjective[i]=0;
        }
        zObjective[ParamNum]=1;

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
                ParameterMin = Lpp.getBestSolution(0);
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
                ParameterMax = Lpp.getBestSolution(0);
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
        return solveLpp(0);
    }
    
    

    public boolean estimate(int ParamNum){
        return solveLpp(ParamNum);
    }
    
    public boolean estimateAll(){ 
        ParametersMins = new double[VarNumber];
        ParametersMaxs = new double[VarNumber];

        boolean Solved = true;
        for (int i=0; i<VarNumber; i++){
            Solved = Solved && estimate(i);
            if(!Solved) {
                break;
            }
            ParametersMins[i] = getMin();
            ParametersMaxs[i] = getMax();
        }
        return Solved;
    }
    
    public double getMin(){
        return ParameterMin;
    }

    public double getMax(){
        return ParameterMax;
    }

    public double getMin(int i) {
        return ParametersMins[i];
    }

    public double getMax(int i) {
        return ParametersMaxs[i];
    }

    public double[] getMins() {
        return ParametersMins;
    }

    public double[] getMaxs() {
        return ParametersMaxs;
    }
        
}
