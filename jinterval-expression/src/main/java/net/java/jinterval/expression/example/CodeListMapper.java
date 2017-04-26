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
package net.java.jinterval.expression.example;

import java.util.Arrays;
import net.java.jinterval.expression.AbstractExpressionVisitor;
import net.java.jinterval.expression.CodeList;

/**
 * Class tries to map Expression of one CodeList to another
 */
public class CodeListMapper extends AbstractExpressionVisitor {

    /**
     * Maps expressions of "from" CodeList to expressions of "to" CodeList
     *
     * @param myList "from" CodeList
     * @param thatList "to" CodeList
     * @param reportSubexpressions true to report about common subexpressions in
     * the "to" CodeList
     * @return
     * @trhows RuntimeException if can't map
     */
    public static int[] mapCodeList(CodeList myList, CodeList thatList, boolean reportSubexpressions) {
        return new CodeListMapper(myList, thatList, reportSubexpressions).thatIndex;
    }

    private final Lookup lookup;
    private final int[] thatIndex;

    private CodeListMapper(CodeList myList, CodeList thatList, boolean reportSubexpression) {
        lookup = new Lookup(thatList, reportSubexpression);
        thatIndex = new int[myList.getNumExprs()];
        Arrays.fill(thatIndex, -1);
        myList.acceptForward(this);
    }

    private void setIndex(int myIndex, int thatIndex) {
        if (thatIndex < 0) {
            throw new RuntimeException("Can't map expression " + myIndex);
        }
        this.thatIndex[myIndex] = thatIndex;
//        System.out.println(myIndex + " --> " + thatIndex);
    }

    @Override
    public void visitInp(int r, String name) {
        setIndex(r, lookup.lookupInp(name));
    }

    @Override
    public void visitLit(int r, String numerator, String denominator) {
        setIndex(r, lookup.lookupLiteral(numerator, denominator));
    }

    @Override
    public void visitLit(int r, String literal) {
        setIndex(r, lookup.lookupLiteral(literal));
    }

    @Override
    public void visitInterval(int r, String inf, String sup) {
        setIndex(r, lookup.lookupInterval(inf, sup));
    }

    @Override
    public void visitNum(int r, Number num) {
        setIndex(r, lookup.lookupNum(num));
    }

    @Override
    public void visitNeg(int r, int x) {
        setIndex(r, lookup.lookupUnary(Kind.Neg, thatIndex[x]));
    }

    @Override
    public void visitAdd(int r, int x, int y) {
        setIndex(r, lookup.lookupBinary(Kind.Add, thatIndex[x], thatIndex[y]));
    }

    @Override
    public void visitSub(int r, int x, int y) {
        setIndex(r, lookup.lookupBinary(Kind.Sub, thatIndex[x], thatIndex[y]));
    }

    @Override
    public void visitMul(int r, int x, int y) {
        if (thatIndex[x] == thatIndex[y]) {
            setIndex(r, lookup.lookupUnary(Kind.Sqr, thatIndex[x]));
        } else {
            setIndex(r, lookup.lookupBinary(Kind.Mul, thatIndex[x], thatIndex[y]));
        }
    }

    @Override
    public void visitDiv(int r, int x, int y) {
        setIndex(r, lookup.lookupBinary(Kind.Div, thatIndex[x], thatIndex[y]));
    }

    @Override
    public void visitSqr(int r, int x) {
        setIndex(r, lookup.lookupUnary(Kind.Sqr, thatIndex[x]));
    }

    @Override
    public void visitSqrt(int r, int x) {
        setIndex(r, lookup.lookupUnary(Kind.Sqrt, thatIndex[x]));
    }

    @Override
    public void visitSin(int r, int x) {
        setIndex(r, lookup.lookupUnary(Kind.Sin, thatIndex[x]));
    }

    @Override
    public void visitCos(int r, int x) {
        setIndex(r, lookup.lookupUnary(Kind.Cos, thatIndex[x]));
    }

    @Override
    public void visitAtan(int r, int x) {
        setIndex(r, lookup.lookupUnary(Kind.Atan, thatIndex[x]));
    }

    private enum Kind {
        Inp, Lit, Interval, Fraction, Num, Neg, Add, Sub, Mul, Div, Sqr, Sqrt, Sin, Cos, Atan;
    }

    private static class Lookup extends AbstractExpressionVisitor {

        private final CodeList codeList;
        private boolean reportSubexpression;
        private Kind kind;
        private int ax, ay;
        private Number num;
        private String numerator, denominator;
        private String name;
        int found;

        Lookup(CodeList codeList, boolean reportSubexpressions) {
            this.codeList = codeList;
            this.reportSubexpression = reportSubexpressions;
        }

        private int lookupInp(String name) {
            kind = Kind.Inp;
            this.name = name;
            return lookup();
        }

        private int lookupLiteral(String literal) {
            kind = Kind.Lit;
            numerator = literal;
            denominator = null;
            return lookup();
        }

        private int lookupLiteral(String numerator, String denominator) {
            kind = Kind.Lit;
            this.numerator = numerator;
            this.denominator = denominator;
            return lookup();
        }

        private int lookupInterval(String inf, String sup) {
            kind = Kind.Interval;
            this.numerator = inf;
            this.denominator = sup;
            return lookup();
        }

        private int lookupNum(Number num) {
            kind = Kind.Num;
            this.num = num;
            return lookup();
        }

        @Override
        public void visitInterval(int r, String inf, String sup) {
            kind = Kind.Interval;
            numerator = inf;
            denominator = sup;
        }

        private int lookupUnary(Kind kind, int x) {
            this.kind = kind;
            ax = x;
            return lookup();
        }

        private int lookupBinary(Kind kind, int x, int y) {
            this.kind = kind;
            ax = x;
            ay = y;
            return lookup();
        }

        private int lookup() {
            found = -1;
            codeList.acceptForward(this);
            return found;
        }

        private void setFound(int r) {
            if (found != -1 && reportSubexpression) {
                System.out.println("Common subexpressions " + found + " and " + r);
            }
            found = r;
        }

        @Override
        public void visitInp(int r, String name) {
            if (kind == Kind.Inp && this.name.equals(name)) {
                setFound(r);
            }
        }

        @Override
        public void visitLit(int r, String numerator, String denominator) {
            if (kind == Kind.Fraction
                    && this.numerator.equals(numerator)
                    && this.denominator.equals(denominator)) {
                setFound(r);
            }
        }

        @Override
        public void visitLit(int r, String literal) {
            if (kind == Kind.Fraction && this.numerator.equals(literal)) {
                setFound(r);
            }
        }

        @Override
        public void visitNum(int r, Number num) {
            if (kind == Kind.Num && this.num.equals(num)) {
                setFound(r);
            }
        }

        @Override
        public void visitPi(int r) {
        }

        @Override
        public void visitNeg(int r, int x) {
            if (kind == Kind.Neg && x == ax) {
                setFound(r);
            }
        }

        @Override
        public void visitAdd(int r, int x, int y) {
            if (kind == Kind.Add && x == ax && y == ay) {
                setFound(r);
            }
        }

        @Override
        public void visitSub(int r, int x, int y) {
            if (kind == Kind.Sub && x == ax && y == ay) {
                setFound(r);
            }
        }

        @Override
        public void visitMul(int r, int x, int y) {
            if (kind == Kind.Mul && x == ax && y == ay) {
                setFound(r);
            }
        }

        @Override
        public void visitDiv(int r, int x, int y) {
            if (kind == Kind.Div && x == ax && y == ay) {
                setFound(r);
            }
        }

        @Override
        public void visitSqr(int r, int x) {
            if (kind == Kind.Sqr && x == ax) {
                setFound(r);
            }
        }

        @Override
        public void visitSqrt(int r, int x) {
            if (kind == Kind.Sqrt && x == ax) {
                setFound(r);
            }
        }

        @Override
        public void visitSin(int r, int x) {
            if (kind == Kind.Sin && x == ax) {
                setFound(r);
            }
        }

        @Override
        public void visitCos(int r, int x) {
            if (kind == Kind.Cos && x == ax) {
                setFound(r);
            }
        }

        @Override
        public void visitAtan(int r, int x) {
            if (kind == Kind.Atan && x == ax) {
                setFound(r);
            }
        }
    }
}
