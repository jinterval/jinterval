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
package net.java.jinterval.rational;

import java.math.BigInteger;

/**
 *
 */
public class ExtendedRationalOps {

    private ExtendedRationalOps() {
    }

    private static ExtendedRational domainException() {
        throw new DomainException();
    }

    public static ExtendedRational neg(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.neg((Rational) x);
        } else {
            return negExt(x);
        }
    }

    public static ExtendedRational negExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        }
        if (x.isPositiveInfinity()) {
            return ExtendedRational.NEGATIVE_INFINITY;
        } else if (x.isNegativeInfinity()) {
            return ExtendedRational.POSITIVE_INFINITY;
        } else {
            assert x.isNaN();
            return x;
        }
    }

    public static ExtendedRational add(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return RationalOps.add((Rational) x, (Rational) y);
        } else {
            return addExt(x, y);
        }
    }

    public static ExtendedRational addExt(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational) {
            if (y instanceof Rational) {
                throw new IllegalArgumentException();
            } else {
                return y;
            }
        } else if (x.isPositiveInfinity()) {
            if (y.isNaN()) {
                return y;
            } else if (y.isNegativeInfinity()) {
                return domainException();
            }
        } else if (x.isNegativeInfinity()) {
            if (y.isNaN()) {
                return y;
            } else if (y.isPositiveInfinity()) {
                return domainException();
            }
        }
        return x;
    }

    public static ExtendedRational sub(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return RationalOps.sub((Rational) x, (Rational) y);
        } else {
            return subExt(x, y);
        }
    }

    public static ExtendedRational subExt(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational) {
            if (y instanceof Rational) {
                throw new IllegalArgumentException();
            } else if (y.isPositiveInfinity()) {
                return ExtendedRational.NEGATIVE_INFINITY;
            } else if (y.isNegativeInfinity()) {
                return ExtendedRational.POSITIVE_INFINITY;
            } else {
                return y;
            }
        } else if (x.isPositiveInfinity()) {
            if (y.isNaN()) {
                return y;
            } else if (y.isPositiveInfinity()) {
                return domainException();
            }
        } else if (x.isNegativeInfinity()) {
            if (y.isNaN()) {
                return y;
            } else if (y.isNegativeInfinity()) {
                return domainException();
            }
        }
        return x;
    }

    public static ExtendedRational mul(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return RationalOps.mul((Rational) x, (Rational) y);
        } else {
            return mulExt(x, y);
        }
    }

    public static ExtendedRational mulExt(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational) {
            if (y instanceof Rational) {
                throw new IllegalArgumentException();
            } else if (y.isPositiveInfinity()) {
                int xsign = x.signum();
                if (xsign > 0) {
                    return y;
                } else if (xsign < 0) {
                    return ExtendedRational.NEGATIVE_INFINITY;
                } else {
                    return domainException();
                }
            } else if (y.isNegativeInfinity()) {
                int xsign = x.signum();
                if (xsign > 0) {
                    return y;
                } else if (xsign < 0) {
                    return ExtendedRational.POSITIVE_INFINITY;
                } else {
                    return domainException();
                }
            } else {
                return y;
            }
        } else if (x.isPositiveInfinity()) {
            if (y.isNaN()) {
                return y;
            }
            int ysign = y.signum();
            if (ysign > 0) {
                return x;
            } else if (ysign < 0) {
                return ExtendedRational.NEGATIVE_INFINITY;
            } else {
                return domainException();
            }
        } else if (x.isNegativeInfinity()) {
            if (y.isNaN()) {
                return y;
            }
            int ysign = y.signum();
            if (ysign > 0) {
                return x;
            } else if (ysign < 0) {
                return ExtendedRational.POSITIVE_INFINITY;
            } else {
                return domainException();
            }
        } else {
            return x;
        }
    }

    public static ExtendedRational div(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return RationalOps.div((Rational) x, (Rational) y);
        } else {
            return divExt(x, y);
        }
    }

    public static ExtendedRational divExt(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational) {
            if (y instanceof Rational) {
                throw new IllegalArgumentException();
            } else if (y.isPositiveInfinity() || y.isNegativeInfinity()) {
                return Rational.zero();
            } else {
                return y;
            }
        } else if (x.isPositiveInfinity()) {
            if (y instanceof Rational) {
                int ysign = y.signum();
                if (ysign > 0) {
                    return x;
                } else if (ysign < 0) {
                    return ExtendedRational.NEGATIVE_INFINITY;
                } else {
                    return domainException();
                }
            } else if (y.isPositiveInfinity() || y.isNegativeInfinity()) {
                return domainException();
            } else {
                return y;
            }
        } else if (x.isNegativeInfinity()) {
            if (y instanceof Rational) {
                int ysign = y.signum();
                if (ysign > 0) {
                    return x;
                } else if (ysign < 0) {
                    return ExtendedRational.POSITIVE_INFINITY;
                } else {
                    return domainException();
                }
            } else if (y.isPositiveInfinity() || y.isNegativeInfinity()) {
                return domainException();
            } else {
                return y;
            }
        } else {
            return x;
        }
    }

    public static ExtendedRational recip(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.recip((Rational) x);
        } else {
            return recipExt(x);
        }
    }

    public static ExtendedRational recipExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return Rational.zero();
        } else {
            return x;
        }
    }

    public static ExtendedRational sqr(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.sqr((Rational) x);
        } else {
            return sqrExt(x);
        }
    }

    public static ExtendedRational sqrExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return ExtendedRational.POSITIVE_INFINITY;
        } else {
            return x;
        }
    }

    public static ExtendedRational sqrt(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.sqrt((Rational) x);
        } else {
            return sqrtExt(x);
        }
    }

    public static ExtendedRational sqrtExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational fma(ExtendedRational x, ExtendedRational y, ExtendedRational z) {
        if (x instanceof Rational && y instanceof Rational && z instanceof Rational) {
            return RationalOps.fma((Rational) x, (Rational) y, (Rational) z);
        } else {
            return fmaExt(x, y, z);
        }
    }

    public static ExtendedRational fmaExt(ExtendedRational x, ExtendedRational y, ExtendedRational z) {
        return ExtendedRationalOps.addExt(ExtendedRationalOps.mul(x, y), z);
    }

    public static ExtendedRational pown(ExtendedRational x, BigInteger p) {
        if (x instanceof Rational) {
            return RationalOps.pown((Rational) x, p);
        } else {
            return pownExt(x, p);
        }
    }

    public static ExtendedRational pownExt(ExtendedRational x, BigInteger p) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            if (p.signum() > 0) {
                return x;
            } else if (p.signum() < 0) {
                return Rational.zero();
            } else {
                return Rational.one();
            }
        } else if (x.isNegativeInfinity()) {
            if (p.signum() > 0) {
                return p.testBit(0) ? x : ExtendedRational.POSITIVE_INFINITY;
            } else if (p.signum() < 0) {
                return Rational.zero();
            } else {
                return Rational.one();
            }
        } else {
            return x;
        }
    }

    public static ExtendedRational pown(ExtendedRational x, long p) {
        if (x instanceof Rational) {
            return RationalOps.pown((Rational) x, p);
        } else {
            return pownExt(x, p);
        }
    }

    public static ExtendedRational pownExt(ExtendedRational x, long p) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            if (p > 0) {
                return x;
            } else if (p < 0) {
                return Rational.zero();
            } else {
                return Rational.one();
            }
        } else if (x.isNegativeInfinity()) {
            if (p > 0) {
                return (p & 1) != 0 ? x : ExtendedRational.POSITIVE_INFINITY;
            } else if (p < 0) {
                return Rational.zero();
            } else {
                return Rational.one();
            }
        } else {
            return x;
        }
    }

    public static ExtendedRational pown(ExtendedRational x, int p) {
        if (x instanceof Rational) {
            return RationalOps.pown((Rational) x, p);
        } else {
            return pownExt(x, p);
        }
    }

    public static ExtendedRational pownExt(ExtendedRational x, int p) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            if (p > 0) {
                return x;
            } else if (p < 0) {
                return Rational.zero();
            } else {
                return Rational.one();
            }
        } else if (x.isNegativeInfinity()) {
            if (p > 0) {
                return (p & 1) != 0 ? x : ExtendedRational.POSITIVE_INFINITY;
            } else if (p < 0) {
                return Rational.zero();
            } else {
                return Rational.one();
            }
        } else {
            return x;
        }
    }

    public static ExtendedRational pow(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return RationalOps.pow((Rational) x, (Rational) y);
        } else {
            return powExt(x, y);
        }
    }

    public static ExtendedRational powExt(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational) {
            if (y instanceof Rational) {
                throw new IllegalArgumentException();
            } else if (y.isPositiveInfinity()) {
                if (x.signum() < 0) {
                    return domainException();
                } else {
                    int cmpX = x.compareTo(Rational.one());
                    if (cmpX > 0) {
                        return y;
                    } else if (cmpX < 0) {
                        return Rational.zero();
                    } else {
                        return domainException();
                    }
                }
            } else if (y.isNegativeInfinity()) {
                if (x.signum() <= 0) {
                    return domainException();
                } else {
                    int cmpX = x.compareTo(Rational.one());
                    if (cmpX > 0) {
                        return Rational.zero();
                    } else if (cmpX < 0) {
                        return ExtendedRational.POSITIVE_INFINITY;
                    } else {
                        return domainException();
                    }
                }
            } else {
                return y;
            }
        } else if (x.isPositiveInfinity()) {
            if (y.isNaN()) {
                return y;
            }
            int ysign = y.signum();
            if (ysign > 0) {
                return x;
            } else if (ysign < 0) {
                return Rational.zero();
            } else {
                return domainException();
            }
        } else if (x.isNegativeInfinity()) {
            if (y.isNaN()) {
                return y;
            }
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational exp(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.exp((Rational) x);
        } else {
            return expExt(x);
        }
    }

    public static ExtendedRational expExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return Rational.zero();
        } else {
            return x;
        }
    }

    public static ExtendedRational exp2(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.exp2((Rational) x);
        } else {
            return exp2Ext(x);
        }
    }

    public static ExtendedRational exp2Ext(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return Rational.zero();
        } else {
            return x;
        }
    }

    public static ExtendedRational exp10(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.exp10((Rational) x);
        } else {
            return exp10Ext(x);
        }
    }

    public static ExtendedRational exp10Ext(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return Rational.zero();
        } else {
            return x;
        }
    }

    public static ExtendedRational log(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.log((Rational) x);
        } else {
            return logExt(x);
        }
    }

    public static ExtendedRational logExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational log2(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.log2((Rational) x);
        } else {
            return log2Ext(x);
        }
    }

    public static ExtendedRational log2Ext(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational log10(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.log10((Rational) x);
        } else {
            return log10Ext(x);
        }
    }

    public static ExtendedRational log10Ext(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational sin(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.sin((Rational) x);
        } else {
            return sinExt(x);
        }
    }

    public static ExtendedRational sinExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational cos(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.cos((Rational) x);
        } else {
            return cosExt(x);
        }
    }

    public static ExtendedRational cosExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational tan(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.tan((Rational) x);
        } else {
            return tanExt(x);
        }
    }

    public static ExtendedRational tanExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational asin(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.asin((Rational) x);
        } else {
            return asinExt(x);
        }
    }

    public static ExtendedRational asinExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational acos(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.asin((Rational) x);
        } else {
            return acosExt(x);
        }
    }

    public static ExtendedRational acosExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational atan(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.atan((Rational) x);
        } else {
            return atanExt(x);
        }
    }

    public static ExtendedRational atanExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            throw new IrrationalException();
        } else {
            return x;
        }
    }

    public static ExtendedRational atan2(ExtendedRational y, ExtendedRational x) {
        if (x instanceof Rational && y instanceof Rational) {
            return RationalOps.atan2((Rational) x, (Rational) y);
        } else if (x.isPositiveInfinity() && y.signum() == 0) {
            return Rational.zero();
        } else {
            throw new IrrationalException();
        }
    }

    public static ExtendedRational atan2Ext(ExtendedRational y, ExtendedRational x) {
        if (x instanceof Rational && y instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isNaN()) {
            return x;
        } else if (y.isNaN()) {
            return y;
        } else if (x.isPositiveInfinity() && y.signum() == 0) {
            return Rational.zero();
        } else {
            throw new IrrationalException();
        }
    }

    public static ExtendedRational sinh(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.sinh((Rational) x);
        } else {
            return sinhExt(x);
        }
    }

    public static ExtendedRational sinhExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return x;
        } else {
            return x;
        }
    }

    public static ExtendedRational cosh(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.cosh((Rational) x);
        } else {
            return coshExt(x);
        }
    }

    public static ExtendedRational coshExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return ExtendedRational.POSITIVE_INFINITY;
        } else {
            return x;
        }
    }

    public static ExtendedRational tanh(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.tanh((Rational) x);
        } else {
            return tanhExt(x);
        }
    }

    public static ExtendedRational tanhExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return Rational.one();
        } else if (x.isNegativeInfinity()) {
            return Rational.valueOf(-1);
        } else {
            return x;
        }
    }

    public static ExtendedRational asinh(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.asinh((Rational) x);
        } else {
            return asinhExt(x);
        }
    }

    public static ExtendedRational asinhExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return x;
        } else {
            return x;
        }
    }

    public static ExtendedRational acosh(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.acosh((Rational) x);
        } else {
            return acoshExt(x);
        }
    }

    public static ExtendedRational acoshExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return x;
        } else if (x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational atanh(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.atanh((Rational) x);
        } else {
            return atanhExt(x);
        }
    }

    public static ExtendedRational atanhExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity() || x.isNegativeInfinity()) {
            return domainException();
        } else {
            return x;
        }
    }

    public static ExtendedRational sign(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.sign((Rational) x);
        } else {
            return signExt(x);
        }
    }

    public static ExtendedRational signExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return Rational.one();
        } else if (x.isNegativeInfinity()) {
            return Rational.valueOf(-1);
        } else {
            return x;
        }
    }

    public static ExtendedRational ceil(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.ceil((Rational) x);
        } else {
            return x;
        }
    }

    public static ExtendedRational floor(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.floor((Rational) x);
        } else {
            return x;
        }
    }

    public static ExtendedRational trunc(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.trunc((Rational) x);
        } else {
            return x;
        }
    }

    public static ExtendedRational roundTiesToEven(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.roundTiesToEven((Rational) x);
        } else {
            return x;
        }
    }

    public static ExtendedRational roundTiesToAway(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.roundTiesToAway((Rational) x);
        } else {
            return x;
        }
    }

    public static ExtendedRational abs(ExtendedRational x) {
        if (x instanceof Rational) {
            return RationalOps.abs((Rational) x);
        } else {
            return absExt(x);
        }
    }

    public static ExtendedRational absExt(ExtendedRational x) {
        if (x instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isNegativeInfinity() || x.isPositiveInfinity()) {
            return ExtendedRational.POSITIVE_INFINITY;
        } else {
            return x;
        }
    }

    public static ExtendedRational min(ExtendedRational x1, ExtendedRational x2) {
        return x1.isNaN() ? x1 : x2.isNaN() ? x2 : x1.le(x2) ? x1 : x2;
    }

    public static ExtendedRational min(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn) {
        ExtendedRational r = min(x1, x2);
        for (ExtendedRational x : xn) {
            r = min(r, x);
        }
        return r;
    }

    public static ExtendedRational max(ExtendedRational x1, ExtendedRational x2) {
        return x1.isNaN() ? x1 : x2.isNaN() ? x2 : x1.ge(x2) ? x1 : x2;
    }

    public static ExtendedRational max(ExtendedRational x1, ExtendedRational x2, ExtendedRational... xn) {
        ExtendedRational r = max(x1, x2);
        for (ExtendedRational x : xn) {
            r = max(r, x);
        }
        return r;
    }

    public static ExtendedRational hypot(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            return RationalOps.hypot((Rational) x, (Rational) y);
        } else {
            return hypotExt(x, y);
        }
    }

    public static ExtendedRational rootn(ExtendedRational x, BigInteger q) {
        if (x instanceof Rational) {
            return RationalOps.rootn((Rational) x, q);
        } else {
            return rootnExt(x, q);
        }
    }

    public static ExtendedRational rootnExt(ExtendedRational x, BigInteger q) {
        if (x instanceof Rational || q.signum() == 0) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return q.signum() > 0 ? x : Rational.zero();
        } else if (x.isNegativeInfinity()) {
            if (!q.testBit(0)) {
                throw new DomainException();
            }
            return q.signum() > 0 ? x : Rational.zero();
        } else {
            return x;
        }
    }

    public static ExtendedRational rootn(ExtendedRational x, long q) {
        if (x instanceof Rational) {
            return RationalOps.rootn((Rational) x, q);
        } else {
            return rootnExt(x, q);
        }
    }

    public static ExtendedRational rootnExt(ExtendedRational x, long q) {
        if (x instanceof Rational || q == 0) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return q > 0 ? x : Rational.zero();
        } else if (x.isNegativeInfinity()) {
            if ((q & 1) == 0) {
                throw new DomainException();
            }
            return q > 0 ? x : Rational.zero();
        } else {
            return x;
        }
    }

    public static ExtendedRational rootn(ExtendedRational x, int q) {
        if (x instanceof Rational) {
            return RationalOps.rootn((Rational) x, q);
        } else {
            return rootnExt(x, q);
        }
    }

    public static ExtendedRational rootnExt(ExtendedRational x, int q) {
        if (x instanceof Rational || q == 0) {
            throw new IllegalArgumentException();
        } else if (x.isPositiveInfinity()) {
            return q > 0 ? x : Rational.zero();
        } else if (x.isNegativeInfinity()) {
            if ((q & 1) == 0) {
                throw new DomainException();
            }
            return q > 0 ? x : Rational.zero();
        } else {
            return x;
        }
    }

    public static ExtendedRational hypotExt(ExtendedRational x, ExtendedRational y) {
        if (x instanceof Rational && y instanceof Rational) {
            throw new IllegalArgumentException();
        } else if (x.isNaN()) {
            return x;
        } else if (y.isNaN()) {
            return y;
        } else {
            return ExtendedRational.POSITIVE_INFINITY;
        }
    }
}
