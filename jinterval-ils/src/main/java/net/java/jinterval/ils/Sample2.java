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
public class Sample2 extends Sample {

    public Sample2() {
        super(3, 3,
                // A
                new double[][]{{4, -1, 1.5}, {-0.5, -7, 1}, {-1.5, -0.7, 2}},
                new double[][]{{5, 1, 2.5}, {.5, -5, 2}, {-.5, -.5, 3}},
                // b
                new double[]{3, 0, 3},
                new double[]{4, 2, 4},
                // x0
                new IntervalVector(n2i(-100, 100), n2i(-100, 100), n2i(-100, 100)),
                // x
                new double[]{-1.0604173, -0.3543717, 0.7583502},
                new double[]{1.048619, 1.2996759, 2.9840853});
    }
    //Answers from Int4Sci's linearsolve
    //
    //Hansen-Bliek precontioning only
    //phb = I4Slinearsolve(A,b,"PHB")
    //!|-1.0604173,1.3836696|  !
    //!                        !
    //!|-0.7446036,1.3320011|  !
    //!                        !
    //!|0.7583502,2.9840853|   !
    //Gauss-Seidel only
    //gs = I4Slinearsolve(A,b,x0,"GS")
    //!|-2.2562425,1.8084532|  !
    //!                        !
    //!|-0.8418408,1.8484259|  !
    //!                        !
    //!|-0.4868261,4.003289|   !
    // Hansen-Bliek + Gauss-Seidel
    //!|-1.0604173,1.048619|   !
    //!                        !
    //!|-0.3543717,1.2996759|  !
    //!                        !
    //!|0.7583502,2.9840853|   !
}
