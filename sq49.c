#include <stdio.h>
#include <string.h>

int main()
{
    char str_a[100],str_b[100];
    fgets(str_a,100,stdin);
    str_a[strcspn(str_a,"\n")] = '\0';
    fgets(str_b,100,stdin);
    str_b[strcspn(str_b,"\n")] = '\0';
    int test = strcmp(str_a,str_b);
    if(test == 0)
    {
        printf("相等");
    }
    else
    {
        printf("不相等");
    }
    return 0;
}