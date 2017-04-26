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

import net.java.jinterval.expression.CodeList;
import net.java.jinterval.expression.Expression;
import net.java.jinterval.expression.OptimizationProblem;

/**
 * Формулы из Количественная оценка неопределённости пожарного риска. Сценарий
 * аварии "Пожар пролива ЛВЖ" Проблемы анализа риска, том 11, 2014Б ном. 4
 */
public class FireRisk {

    /**
     * Enum to choose input variable
     */
    public enum From {
        tpac_T_uw_d, L_d_theta, a_b_theta
    };

    /**
     * Enum to choose objective function.
     */
    public enum To {
        F, Fv, Fh, Fsqr
    }

    /**
     * Create optimization problem minimizing Fv on (l,d,theta) inputs.
     *
     * @return OptimizationProblem
     */
    public static OptimizationProblem createOptimizationProblemLdMinFv() {
        return createOptimizationProblem(From.L_d_theta, To.Fv, false);
    }

    /**
     * Create optimization problem maximizing Fv on (tpac,T,uw,d) inputs.
     *
     * @return OptimizationProblem
     */
    public static OptimizationProblem createOptimizationProblemTempMaxFv() {
        return createOptimizationProblem(From.tpac_T_uw_d, To.Fv, true);
    }

    /**
     * Create optimization problem
     *
     * @param from choose input variables
     * @param to choose objective function
     * @param neg true to negate objective function
     * @return OptimizationProblem
     */
    public static OptimizationProblem createOptimizationProblem(From from, To to, boolean neg) {
        String[] box;
        switch (from) {
            case tpac_T_uw_d:
                box = new String[]{
                    "[50.0,170.0]", // tpac
                    "[254.0,299.0]", // T
                    "[2.3,9.0]", // uw
                    "[15.2,34.8]" // d
                };
                break;
            case L_d_theta:
                box = new String[]{
                    "[19.1,55.2]", // L
                    "[15.2,34.8]", // d
                    "[0,1.18]" // theta
                };
                break;
            case a_b_theta:
                box = new String[]{
                    "[382/348,1104/152]", // a = 2*L/d
                    "[2000/348,2000/152]", // b = 2*X/d
                    "[0,1.18]" // theta
                };
                break;
            default:
                throw new AssertionError();
        }
        return new OptimizationProblem(createObjective(from, to, neg), box);
    }

    /**
     * Create objective function
     *
     * @param from choose input variables
     * @param to choose objective function
     * @param neg true to negate objective function
     * @return objective function
     */
    public static Expression createObjective(From from, To to, boolean neg) {
        Subclass fr = new Subclass(from);
        Expression objective;
        switch (to) {
            case F:
                objective = fr.F;
                break;
            case Fv:
                objective = fr.Fv();
                break;
            case Fh:
                objective = fr.Fh();
                break;
            case Fsqr:
                objective = fr.Fsqr();
                break;
            default:
                throw new AssertionError();
        }
        return neg ? objective.neg().name("neg_" + objective.name()) : objective;
    }

    final CodeList cl;
    final From from;

    FireRisk(From from) {
        this.from = from;
        switch (from) {
            case tpac_T_uw_d:
                cl = CodeList.create("tpac", "T", "uw", "d");
                break;
            case L_d_theta:
                cl = CodeList.create("L", "d", "theta");
                break;
            case a_b_theta:
                cl = CodeList.create("a", "b", "theta");
                break;
            default:
                throw new AssertionError();
        }
    }

    boolean from(From from) {
        return this.from.ordinal() <= from.ordinal();
    }

    Expression n(String literal) {
        return cl.lit(literal);
    }

    public static class Subclass extends FireRisk {

        Subclass(From from) {
            super(from);
        }

        // Constants
        public Expression m_prime = n("0.06").name("m_prime");
        public Expression g = n("9.81").name("g");
        public Expression Tnom = n("288.15").name("Tnom");
        public Expression ro_v_nom = n("1.225").name("ro_v_nom");
        public Expression X = n("100").name("X");
        public Expression V_mu = n("22.413").name("V_mu");
        public Expression k_factor = n("1.216").div(n("0.67668")).name("k_factor");
        public Expression c1Pi = cl.pi().recip().name("c1Pi");

        public Expression tpac = from(From.tpac_T_uw_d) ? cl.getInp(0) : null;
        public Expression T = from(From.tpac_T_uw_d) ? cl.getInp(1) : null;
        public Expression uw = from(From.tpac_T_uw_d) ? cl.getInp(2) : null;
        public Expression d = from(From.tpac_T_uw_d)
                ? cl.getInp(3)
                : from(From.L_d_theta)
                ? cl.getInp(1)
                : null;

        /*0*/
        public Expression k = from(From.tpac_T_uw_d)
                ? k_factor.mul(tpac.rootn(3)).name("k")
                : null;

        public Expression mu0 = from(From.tpac_T_uw_d)
                ? n("7").mul(k).sub(n("21.5")).name("mu0")
                : null;
        public Expression mu1 = from(From.tpac_T_uw_d)
                ? n("0.76").sub(n("0.04").mul(k)).name("mu1")
                : null;
        public Expression mu2 = from(From.tpac_T_uw_d)
                ? n("0.0003").mul(k).sub(n("0.00245")).name("mu2")
                : null;
        /*1*/
        public Expression mu = from(From.tpac_T_uw_d)
                ? mu0.add(mu1.mul(tpac)).add(mu2.mul(tpac.sqr())).name("mu")
                : null;

        /*2*/
        public Expression ro_p = from(From.tpac_T_uw_d)
                ? mu.div(V_mu.mul(n("1").add(n("0.00367").mul(tpac)))).name("ro_p")
                : null;

        public Expression u_star_arg = from(From.tpac_T_uw_d)
                ? ro_p.div(m_prime.mul(g).mul(d))
                : null;
        /*3*/
        public Expression u_star = from(From.tpac_T_uw_d)
                ? uw.mul(u_star_arg.rootn(3)).max(n("1")).name("u_star")
                : null;

        /*4*/
        public Expression ro_v = from(From.tpac_T_uw_d)
                ? Tnom.mul(ro_v_nom).div(T).name("ro_v")
                : null;

        /*5*/
        public Expression L = from(From.tpac_T_uw_d)
                ? n("55")
                .mul(m_prime.pow(n("0.67")))
                .div(g.pow(n("0.335")))
                .mul(d.pow(n("0.665")))
                .mul(u_star.pow(n("0.21")))
                .div(ro_v.pow(n("0.67")))
                .name("L")
                : from(From.L_d_theta)
                ? cl.getInp(0)
                : null;

        /*6*/
        public Expression theta = from(From.tpac_T_uw_d)
                ? u_star.sqrt().recip().acos().name("theta")
                : from(From.L_d_theta)
                ? cl.getInp(2)
                : from(From.a_b_theta)
                ? cl.getInp(2)
                : null;

        /*7*/
        public Expression a = from(From.L_d_theta)
                ? L.mul(n("2")).div(d).name("a")
                : from(From.a_b_theta)
                ? cl.getInp(0)
                : null;

        /*8*/
        public Expression b = from(From.L_d_theta)
                ? n("2").mul(X).div(d).name("b")
                : from(From.a_b_theta)
                ? cl.getInp(1)
                : null;

        public Expression bp1 = b.add(n("1")).name("bp1");
        public Expression bm1 = b.sub(n("1")).name("bm1");

        public Expression sinth = theta.sin().name("sinth");
        public Expression costh = theta.cos().name("costh");

        public Expression A_arg = a.sqr()
                .add(bp1.sqr())
                .sub(n("2").mul(a.mul(bp1).mul(sinth)))
                .name("A_arg");
        /*9*/
        public Expression A = A_arg.sqrt().name("A");

        public Expression B_arg = a.sqr()
                .add(bm1.sqr())
                .sub(n("2").mul(a.mul(bm1).mul(sinth)))
                .name("B_arg");
        /*10*/
        public Expression B = B_arg.sqrt().name("B");

        public Expression C_arg = n("1").add((b.sqr().sub(n("1"))).mul(costh.sqr())).name("C_arg");
        /*11*/
        public Expression C = C_arg.sqrt().name("C");

        public Expression D_arg = from(From.L_d_theta)
                ? n("2").mul(X).sub(d)
                .div(n("2").mul(X).add(d))
                .name("D_arg")
                : from(From.a_b_theta)
                ? bm1.div(bp1).sqrt()
                : null;
        /*12*/
        public Expression D = D_arg.sqrt().name("D");

        /*13*/
        public Expression E = from(From.L_d_theta)
                ? L.mul(costh)
                .div(X.sub(L.mul(sinth)))
                .name("E")
                : from(From.a_b_theta)
                ? a.mul(costh).div(b.sub(a.mul(sinth)))
                : null;

        /*14*/
        public Expression F_arg = b.sqr().sub(n("1")).name("F_arg");
        public Expression F = F_arg.sqrt().name("F");

        public Expression ab = a.mul(b).name("ab");
        public Expression AB = A.mul(B).name("AB");

        public Expression S1arg = ab.sub(F.sqr().mul(sinth))
                .div(F.mul(C)).name("S1arg");
        public Expression S1 = S1arg.atan().name("S1");
        public Expression S2arg = F.mul(sinth).div(C).name("S2arg");
        public Expression S2 = S2arg.atan().name("S2");
        public Expression S = S1.add(S2).name("S");

        public Expression ADB = A.mul(D).div(B).name("ADB");
        public Expression atanADB = ADB.atan().name("atanADB");

        public Expression Fv() {
            Expression abFv = a.sqr()
                    .add(b.add(n("1")).sqr())
                    .sub(n("2").mul(b).mul(n("1").add(a.mul(sinth))))
                    .name("abFv");
            Expression Fv1 = E.neg().mul(D.atan()).name("Fv1");
            Expression Fv2 = E.mul(abFv).div(AB).mul(atanADB).name("Fv2");
            Expression Fv3 = costh.div(C).mul(S).name("Fv3");
            Expression Fv = cl.pi().recip().mul(Fv1.add(Fv2.add(Fv3))).name("Fv");
            return Fv;
        }

        public Expression Fh() {
            Expression abFh = a.sqr()
                    .add(b.add(n("1")).sqr())
                    .sub(n("2").mul(b.add(n("1")).add(ab.mul(sinth))))
                    .name("abFh");
            Expression Fh1 = D.recip().atan().name("Fh1");
            Expression Fh2 = sinth.div(C).mul(S).name("Fh2");
            Expression Fh3 = abFh.div(AB).mul(atanADB).name("Fh3");
            Expression Fh = c1Pi.mul(Fh1.add(Fh2).sub(Fh3)).name("Fh");
            return Fh;
        }

        public Expression Fsqr() {
            return Fv().sqr()
                    .add(Fh().sqr())
                    .name("Fsqr");
        }

    }
}
