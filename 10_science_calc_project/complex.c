#include <stdio.h>
#include <math.h>
#include "complex.h"

Complex complex_add(Complex a, Complex b)
{
    Complex sum;
    sum.re = a.re + b.re;
    sum.im = a.im + b.im;
    return sum;
}

Complex complex_sub(Complex a, Complex b)
{
    Complex diff;
    diff.re = a.re - b.re;
    diff.im = a.im - b.im;
    return diff;
}

Complex complex_mul(Complex a, Complex b)
{
    Complex product;
    product.re = a.re * b.re - a.im * b.im;
    product.im = a.re * b.im + a.im * b.re;
    return product;
}

Complex complex_div(Complex a, Complex b)
{
    Complex quotient;
    double denom = b.re * b.re + b.im * b.im;
    if (denom == 0.0)
    {
        fprintf(stderr, "Division by zero complex number\n");
        quotient.re = 0.0;
        quotient.im = 0.0;
        return quotient;
    }
    quotient.re = (a.re * b.re + a.im * b.im) / denom;
    quotient.im = (a.im * b.re - a.re * b.im) / denom;
    return quotient;
}

Complex complex_conjugate(Complex a)
{
    Complex conj;
    conj.re = a.re;
    conj.im = -a.im;
    return conj;
}

double complex_modulus(Complex a)
{
    return sqrt(a.re * a.re + a.im * a.im);
}
