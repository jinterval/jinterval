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
package net.java.jinterval.linear;

import net.java.jinterval.rational.ExtendedRational;
import net.java.jinterval.rational.ExtendedRationalContext;

/**
 *
 */
public interface RationalMatrix {
    public int getRowDimension();
    public int getColumnDimension();
    public ExtendedRational getEntry(int i, int j);
    public void setEntry(int i, int j, ExtendedRational v);
    public RationalVector diag();
    public RationalVector getRowVector(int i);
    public void setRowVector(int i, RationalVector v);
    public RationalVector getColumnVector(int j);
    public RationalMatrix getSubMatrix(int startRow, int endRow, int startColumn, int endColumn);
    public RationalMatrix copy();
    public ExtendedRational getMinValue();
    public ExtendedRational getMaxValue();
    public RationalMatrix add(ExtendedRationalContext ctx, RationalMatrix that);
    public RationalMatrix subtract(ExtendedRationalContext ctx, RationalMatrix that);
    public RationalMatrix multiply(ExtendedRationalContext ctx, RationalMatrix that);
    public RationalVector multiply(ExtendedRationalContext ctx, RationalVector that);
    public RationalMatrix scalarMultiply(ExtendedRationalContext ctx, ExtendedRational v);
}
