#include <stdio.h>

void rotate(int *a,int *b,int *c)
{
    int temp1 = *a;//暂存a
    int temp2 = *b;//暂存b
    *a = *c;//c给a
    *b = temp1;//a给b
    *c = temp2;//b给c

}

int main()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    rotate(&a,&b,&c);
    printf("%d%d%d",a,b,c);
    return 0;
}