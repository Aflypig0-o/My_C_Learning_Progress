#include <stdio.h>

typedef struct
{
    double real,imag;
}Complex;

Complex add(Complex a,Complex b)
{
    Complex sum_result;
    sum_result.real = a.real + b.real;
    sum_result.imag = a.imag + b.imag;
    return sum_result;
}

Complex mult(Complex a,Complex b)
{
    Complex mult_result;
    mult_result.real = (a.real * b.real) - (a.imag * b.imag);
    mult_result.imag = (a.real * b.imag) + (a.imag * b.real);
    return mult_result;
}

void print_complex(Complex *c)
{
    printf("%g+%gi\n",c->real,c->imag);
}

int main()
{
    Complex c1,c2;
    scanf("%lf%lf%lf%lf",&c1.real,&c1.imag,&c2.real,&c2.imag);
    Complex sum = add(c1,c2);
    print_complex(&sum);
    Complex mul = mult(c1,c2);
    print_complex(&mul);
    return 0;
}