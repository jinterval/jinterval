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
package net.java.jinterval.interval.set;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Utils;

/**
 * An exception that indicates that Decoration of the result is below threshold
 */
public class CompressedException extends P1788Exception {

    private final Decoration decoration;
    private final boolean isEmpty;

    public CompressedException() {
        this.decoration = Decoration.TRV;
        this.isEmpty = true;
    }

    public CompressedException(Decoration decoration, boolean isEmpty) {
        this.decoration = isEmpty ? decoration.min(Decoration.TRV) : decoration;
        this.isEmpty = isEmpty;
    }

    public CompressedException(String msg, Decoration decoration, boolean isEmpty) {
        super(msg);
        this.decoration = isEmpty ? decoration.min(Decoration.TRV) : decoration;
        this.isEmpty = isEmpty || decoration == Decoration.ILL;
    }

    @Override
    public SetInterval getValue() {
        return isEmpty ? EmptyInterval.empty(decoration) : Utils.entire(decoration);
    }
}
