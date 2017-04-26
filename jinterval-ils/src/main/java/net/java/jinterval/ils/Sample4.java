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

/**
 * Sample data for small interval linear system (TODO: convert to test)
 *
 * @author sz
 */
public class Sample4 extends Sample {

    public Sample4() {
        super(2, 2,
                // A
                new double[][]{{1, 0}, {0, -4}},
                new double[][]{{10, 1}, {1, -1}},
                // b
                new double[]{0, 0},
                new double[]{2, 2},
                // x0
                new IntervalVector(n2i(-1000, 1000), n2i(-1000, 1000)),
                // x
                new double[]{-7.61868e-8, -2.00000},
                new double[]{2.41421, 1.00000});

    }
    // HBR +  modified GS (PPS) 
    //[-7.61868e-8,2.41421]
    //[-2.00000,1.00000]
    //
    //After HBR:
    //[-14.93333, 23.7333]
    //[-44.6667, 38.0000]
}
