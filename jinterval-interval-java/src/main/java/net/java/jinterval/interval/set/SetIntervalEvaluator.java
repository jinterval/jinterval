/*
 * Copyright (c) 2016, JInterval Project.
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
package net.java.jinterval.interval.set;

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.expression.ExpressionVisitor;
import net.java.jinterval.rational.BinaryValueSet;

/**
 * An abstract evaluator over SetIntervals. It has registers that can store bare
 * or decorated interval values. Names of registers are natural numbers. There
 * are method to get and set register values as {
 *
 * @codew SetInterval}, though internal representation of intervals is
 * implementation-dependent.
 *
 * Evaluator provides operations on registers that are declared in the
 * {@link net.java.jinterval.expression.ExpressionVisitor} interface. For
 * example {@code add(int r, int x, int y)} gets it arguments from x-th and y-th
 * registers and stores result of addition into r-th register.
 *
 */
public abstract class SetIntervalEvaluator implements ExpressionVisitor {

    /**
     * Create SetIntervalEvaluator for evaluation of specified Expressions from
     * a CodeList. Use interval context for evaluation
     *
     * @param ic SetIntervlaContext
     * @param codeList CodeList
     * @param results Expressions to return
     * @return Evaluator for expressions
     */
    public static SetIntervalEvaluator create(SetIntervalContext ic, CodeList codeList, Expression... results) {
        return new SetIntervalEvaluatorGeneric(ic, codeList, results);
    }

    /**
     * Create SetIntervalEvaluator for evaluation of specified Expressions from
     * a CodeList. Use accurate evaluations in given BinaryValueSet
     *
     * @param valueSet BinaryValueSet of evaluations
     * @param codeList CodeList
     * @param results Expressions to return
     * @return Evaluator for expressions
     */
    public static SetIntervalEvaluator createAccurate(BinaryValueSet valueSet, CodeList codeList, Expression... results) {
        if (valueSet == BinaryValueSet.BINARY64) {
            return new SetIntervalEvaluatorBareAccur64(codeList, results);
        } else {
            return create(SetIntervalContexts.getTightest(valueSet), codeList, results);
        }
    }

    /**
     * Create SetIntervalEvaluator for evaluation of specified Expressions from
     * a CodeList. Use tightest evaluations of given BinaryValueSet
     *
     * @param valueSet BinaryValueSet of evaluations
     * @param codeList CodeList
     * @param results Expressions to return
     * @return Evaluator for expressions
     */
    public static SetIntervalEvaluator createTightest(BinaryValueSet valueSet, CodeList codeList, Expression... results) {
        if (valueSet == BinaryValueSet.BINARY64) {
            return new SetIntervalEvaluatorBareTightest64(codeList, results);
        } else {
            return create(SetIntervalContexts.getTightest(valueSet), codeList, results);
        }
    }

    /**
     * Create SetIntervalEvaluator for arbitrary computations. Use interval
     * context for evaluation
     *
     * @param ic SetIntervlaContext
     * @param size number of registers
     * @return Evaluator for expressions
     */
    public static SetIntervalEvaluator create(SetIntervalContext ic, int size) {
        return new SetIntervalEvaluatorGeneric(ic, size);
    }

    /**
     * Create SetIntervalEvaluator for arbitrary computations. Use accurate
     * evaluations in given BinaryValueSet
     *
     * @param valueSet BinaryValueSet of evaluations
     * @param size number of registers
     * @return Evaluator for expressions
     */
    public static SetIntervalEvaluator createAccurate(BinaryValueSet valueSet, int size) {
        if (valueSet == BinaryValueSet.BINARY64) {
            return new SetIntervalEvaluatorBareAccur64(size);
        } else {
            return createTightest(valueSet, size);
        }
    }

    /**
     * Create SetIntervalEvaluator for arbitrary computations. Use tightest
     * evaluations in given BinaryValueSet
     *
     * @param valueSet BinaryValueSet of evaluations
     * @param size number of registers
     * @return Evaluator for expressions
     */
    public static SetIntervalEvaluator createTightest(BinaryValueSet valueSet, int size) {
        if (valueSet == BinaryValueSet.BINARY64) {
            return new SetIntervalEvaluatorBareTightest64(size);
        } else {
            return create(SetIntervalContexts.getTightest(valueSet), size);
        }
    }

    final CodeList codeList;
    final Expression[] results;

    /**
     * Construct SetIntervalEvaluator
     *
     * @param codeList CodeList to evaluate
     * @param results Expressions from the CodeList which client of the class
     * wants to evaluate
     */
    SetIntervalEvaluator(CodeList codeList, Expression[] results) {
        this.codeList = codeList;
        this.results = results.clone();
        for (Expression result : this.results) {
            if (result.getCodeList() != codeList) {
                throw new IllegalArgumentException();
            }
        }
    }

    SetIntervalEvaluator() {
        codeList = null;
        results = null;
    }

    /**
     * Return CodeList which will be evaluated
     *
     * @return CodeList
     */
    public CodeList getCodeList() {
        return codeList;
    }

    /**
     * Return Expressions from the CodeList which client of the class wants to
     * evaluate
     *
     * @return array of Expressions
     */
    public Expression[] getResults() {
        return results.clone();
    }

    /**
     * Evaluate CodeList and return interval values specified Expressions
     *
     * @param args array with interval values of inputs
     * @return array with interval results
     */
    public SetInterval[] evaluate(SetInterval[] args) {
        if (args.length != codeList.getNumInps()) {
            throw new IllegalArgumentException();
        }
        SetInterval[] ret = new SetInterval[results.length];
        evaluate(ret, 0, args, 0);
        return ret;
    }

    /**
     * Evaluate CodeList and return interval values specified Expressions
     *
     * @param results array where to put results
     * @param resultsOffset put results at array elements from this offset
     * @param args array with interval values of inputs
     * @param argsOffset get args at array elements from this offset
     */
    public void evaluate(SetInterval[] results, int resultsOffset,
            SetInterval[] args, int argsOffset) {
        for (int i = 0; i < codeList.getNumInps(); i++) {
            set(i, args[i + argsOffset]);
        }
        codeList.acceptForward(this);
        for (int i = 0; i < results.length; i++) {
            results[i + resultsOffset] = get(this.results[i].getIndex());
        }
    }

    /**
     * Get value stored in a register as SetInterval
     *
     * @param i register number
     * @return a value of the register
     */
    public abstract SetInterval get(int i);

    /**
     * Change value in a register
     *
     * @param i register number
     * @param v new value
     */
    public abstract void set(int i, SetInterval v);

}
