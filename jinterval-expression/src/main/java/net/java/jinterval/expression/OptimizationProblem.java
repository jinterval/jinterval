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
package net.java.jinterval.expression;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.Serializable;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * A problem for (global) optimization on a box
 */
public class OptimizationProblem implements Serializable {

    private final Expression objective;
    private final String[] box;

    /**
     * Create an Optimization problem. It searches minimum of objective function
     * on a box domain
     *
     * @param objective objective function
     * @param box box domain
     */
    public OptimizationProblem(Expression objective, String[] box) {
        this.objective = objective;
        this.box = box.clone();
        if (box.length != objective.getCodeList().getNumInps()) {
            throw new IllegalArgumentException();
        }
        for (String b : box) {
            if (b == null) {
                throw new NullPointerException();
            }
        }
    }

    /**
     * Return objective function
     *
     * @return objective function
     */
    public Expression getObjective() {
        return objective;
    }

    /**
     * Return CodeList
     *
     * @return objective function
     */
    public CodeList getCodeList() {
        return objective.getCodeList();
    }

    /**
     * Return number of inputs in the problem
     *
     * @return number of inputs in the problem
     */
    public int getNumInps() {
        return getCodeList().getNumInps();
    }

    /**
     * Returns interval literal which specifies range of input variable
     *
     * @param i an index of input variable
     * @return interval literal with the range
     */
    public String getInpRange(int i) {
        return box[i];
    }

    /**
     * Save this optimization problem to a File
     *
     * @param file File to save
     * @throws IOException
     */
    public void save(File file) throws IOException {
        save(file.toPath());
    }

    /**
     * Save this optimization problem to a Path
     *
     * @param path Path to save
     * @throws IOException
     */
    public void save(Path path) throws IOException {
        try (OutputStream os = new BufferedOutputStream(Files.newOutputStream(path))) {
            save(os);
        }
    }

    /**
     * Save this optimization problem to OutputStream
     *
     * @param out OutputStream to save
     * @throws IOException
     */
    public void save(OutputStream out) throws IOException {
        try (ObjectOutputStream os = new ObjectOutputStream(out)) {
            os.writeObject(this);
        }
    }

    /**
     * load an optimization problem from a File
     *
     * @param file file to load from
     * @return OptimizationProblem read from file
     * @throws IOException
     */
    public static OptimizationProblem load(File file) throws IOException {
        return load(file.toPath());
    }

    /**
     * load an optimization problem from a Path
     *
     * @param path oath to load from
     * @return OptimizationProblem read from path
     * @throws IOException
     */
    public static OptimizationProblem load(Path path) throws IOException {
        try (InputStream in = new BufferedInputStream(Files.newInputStream(path))) {
            return load(in);
        }
    }

    /**
     * load an optimization problem from an InputStream
     *
     * @param in InputStream to load from
     * @return OptimizationProblem read from InputStream
     * @throws IOException
     */
    public static OptimizationProblem load(InputStream in) throws IOException {
        try (ObjectInputStream is = new ObjectInputStream(in)) {
            return (OptimizationProblem) is.readObject();
        } catch (ClassNotFoundException e) {
            throw new IOException(e);
        }
    }
}
