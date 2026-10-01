#include <stdio.h>
typedef enum{RED = 0,GREEN,BLUE} Color;

int main()
{
    int input;
    scanf("%d",&input);
    Color c = (Color)input;
    switch(c)
    {
        case RED:printf("RED");break;
        case GREEN:printf("GREEN");break;
        case BLUE:printf("BLUE");break;
        default : printf("Not Found");break;
    }
    return 0;
}