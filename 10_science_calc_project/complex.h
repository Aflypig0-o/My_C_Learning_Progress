#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct
{
    double re;//实数部分
    double im;//虚数部分
}Complex;

Complex complex_add(Complex a,Complex b);//复数加法
Complex complex_sub(Complex a,Complex b);//复数减法
Complex complex_mul(Complex a,Complex b);//复数乘法
Complex complex_div(Complex a,Complex b);//复数除法
Complex complex_conjugate(Complex a);//求共轭复数
double complex_modulus(Complex a);//求复数的模

#endif