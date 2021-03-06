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
package net.java.jinterval.interval.kaucher;

import net.java.jinterval.interval.Decoration;
import net.java.jinterval.interval.Interval;
import net.java.jinterval.rational.Rational;

/**
 *
 */
public interface KaucherInterval extends Interval {

    /**
     * Level 1 inf
     *
     * @return
     */
    public Rational inf();

    /**
     * Level 1 sup
     *
     * @return
     */
    public Rational sup();

    /**
     * Level 1 mid
     *
     * @return
     */
    public Rational mid();

    /**
     * Level 1 wid
     *
     * @return
     */
    public Rational wid();

    /**
     * Level 1 rad
     *
     * @return
     */
    public Rational rad();

    /**
     * Level 1 mag
     *
     * @return
     */
    public Rational mag();

    /**
     * Level 1 mig
     *
     * @return
     */
    public Rational mig();
    
    public Decoration getDecoration();
}
