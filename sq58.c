#include <stdio.h>

typedef enum {MON=1,TUE,WED,THU,FRI,SAT,SUN} Weekday;

int main()
{
    Weekday today = WED;
    printf("%d",today);
    return 0;
}