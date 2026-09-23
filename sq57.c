#include <stdio.h>
#define PRINT_VAR(x) printf(#x " = %d\n",x)

int main()
{
    int score = 95;
    int age = 18;
    PRINT_VAR(score);
    PRINT_VAR(age);
    return 0;
}