#include <stdio.h>

void set_to_null(int **pp)
{
    *pp = NULL;
}

int main()
{
    int a = 0;
    int *p = &a;
    printf("修改前:%d\n",*p);
    set_to_null(&p);
    if(p == NULL)
    {
        printf("已经是NULL");
    }
    else
    {
        printf("p还指向%d",*p);
    }
    return 0;
}