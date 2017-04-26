package ru.nsc.interval.globalopt;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.expression.OptimizationProblem;

/**
 * Created by astronaut on 01/04/16.
 */
public class Functions {
    private static CodeList list = CodeList.create("tpac","T","uw", "d");
    private static Expression[] expr;
    private static Expression objectiveFunction;
    private static void initFunctions(){
        expr = new Expression[17];
        expr[0] = (list.num(1.216 / 0.67668).mul(list.getInp(0).pow(list.num(1.0 / 3.0)))); //k
        expr[1] = (list.num(7).mul(expr[0]).sub(list.num(21.5))). //mu
                add((list.num(0.76).sub(list.num(0.04).mul(expr[0]))).mul(list.getInp(0))).
                add((list.num(0.0003).mul(expr[0]).sub(list.num(0.00245))).mul(list.getInp(0).sqr()));
        expr[2] = expr[1].div(list.num(22.413).mul(list.num(1).add(list.num(0.00367).mul(list.getInp(0)))));//ro p
        expr[3] = list.getInp(2).mul( //u*2
                        (expr[2].div(list.num(0.06*9.81).mul(list.getInp(3))).
                                pow(list.num(1.0/3.0)))).abs();
//                                .intersectionX(list.nums(ExtendedRational.valueOf(1), ExtendedRational.POSITIVE_INFINITY));
        expr[4] = list.num(288.15*1.225).div(list.getInp(1)); // ro v
        expr[5] = (//L
                    list.num(55 * Math.pow(0.06, 0.67) / (Math.pow(9.81, 0.335))).
                    mul(list.getInp(3).pow(list.num(0.665))).mul(expr[3].pow(list.num(0.21)))
                  ).div(expr[4].pow(list.num(0.67)));
        expr[6] = (list.num(1).div(expr[3].sqrt())).acos(); //theta
        expr[7] = expr[5].mul(list.num(2)).div(list.getInp(3)); //a
        expr[8] = (list.num(200)).div(list.getInp(3));//b
        expr[9] = (expr[7].sqr().add((expr[8].add(list.num(1))).sqr()).
                sub(list.num(2).mul(expr[7].mul(expr[8].add(list.num(1))).mul(expr[6].sin())))).abs().sqrt(); //A
        expr[10] = (expr[7].sqr().add((expr[8].sub(list.num(1))).sqr()).
                sub(list.num(2).mul(expr[7].mul(expr[8].sub(list.num(1))).mul(expr[6].sin())))).abs().sqrt(); //B
        expr[11] = (list.num(1).add((expr[8].sqr().sub(list.num(1))).mul(expr[6].cos().sqr()))).sqrt(); //C
        expr[12] = ((list.num(200).sub(list.getInp(3))).div(list.num(200).add(list.getInp(3)))).sqrt(); //D
        expr[13] = (expr[5].mul(expr[6].cos())).div(list.num(100).sub(expr[5].mul(expr[6].sin()))); //E
        expr[14] = (expr[8].sqr().sub(list.num(1))).sqrt();//F
        expr[15] = (list.num(1.0/Math.PI). //Fh
                mul(
                        (list.num(1).div(expr[12])).atan().
                                add((expr[6].sin().div(expr[11])).
                                        mul(
                                                ((expr[7].mul(expr[8]).sub(expr[14].sqr().mul(expr[6].sin()))).div(expr[14].mul(expr[11]))).atan().
                                                        add((expr[14].mul(expr[6].sin()).div(expr[11])).atan()
                                                        )
                                        )
                                ).
                                sub(
                                        (expr[7].sqr().add((expr[8].add(list.num(1))).sqr()).add(list.num(-2).
                                                mul(expr[8].add(list.num(1).add(expr[7].mul(expr[8]).mul(expr[6].sin())))))
                                        ).div(expr[9].mul(expr[10])).mul((expr[9].mul(expr[12]).div(expr[10])).atan())
//                                      ).div(expr[9].mul(expr[10])).mul((expr[9].mul(expr[10]).div(expr[10])).atan())
                                )
                )
        );
        expr[16] = (list.num(1.0 / Math.PI). //Fv
                mul(expr[13].neg().mul(expr[12].atan()).
                        add(expr[13].
                                mul(expr[7].sqr().add((expr[8].add(list.num(1))).sqr()).add(list.num(-2).mul(expr[8]).
                                        mul(list.num(1).add(expr[7].mul(expr[6].sin()))))
                                ).div(expr[9].mul(expr[10])).mul((expr[9].mul(expr[12]).div(expr[10])).atan()).
                                add(expr[6].cos().div(expr[11]).
                                        mul(((expr[7].mul(expr[8]).sub(expr[14].sqr().mul(expr[6].sin()))).div(expr[14].mul(expr[11]))).atan().
                                                add((expr[14].mul(expr[6].sin()).div(expr[11])).atan()
                                                )
                                        )
                                )
                        )
                ));
        objectiveFunction = (expr[15].sqr().add(expr[16].sqr())).neg();
    }

    public static OptimizationProblem createOptimizationProblem() {
        initFunctions();
        String[] box = new String[]{
            "[50.0,170.0]", // tpac
            "[254.0,299.0]", // T
            "[2.3,9.0]", // uw
            "[15.2,34.8]" // d
        };
        return new OptimizationProblem(objectiveFunction, box);
    }
}
