#include <stdio.h>
#include <string.h>

int main()
{
    char str_a[100],str_b[100];
    fgets(str_a,100,stdin);
    str_a[strcspn(str_a,"\n")] = '\0';
    strcpy(str_b,str_a);
    printf("%s\n%s",str_a,str_b);
    return 0;
}