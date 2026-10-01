#include <stdio.h>
#include <string.h>

int main()
{
    char str_a[100],str_b[100];
    fgets(str_a,100,stdin);
    str_a[strcspn(str_a,"\n")] = '\0';
    fgets(str_b,100,stdin);
    str_b[strcspn(str_b,"\n")] = '\0';
    strcat(str_a,str_b);
    printf("%s",str_a);
    return 0;
}