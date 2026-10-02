#include <stdio.h>
#include "sq110_calc.h"

int main()
{
    int a = 10;
    int b = 3;
    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, sub(a, b));
    printf("%d * %d = %d\n", a, b, mul(a, b));
    printf("%d / %d = %d\n", a, b, my_div(a, b));
    return 0;
}