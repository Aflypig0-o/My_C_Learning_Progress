#include <stdio.h>
#include <string.h>

int main()
{
    char str_a[200],str_b[100];
    fgets(str_a,200,stdin);
    str_a[strcspn(str_a,"\n")] = '\0';
    fgets(str_b,100,stdin);
    str_b[strcspn(str_b,"\n")] = '\0';
    char *is_substring = strstr(str_a,str_b);
    if(is_substring != NULL)
    {
        printf("yes");
    }
    else
    {
        printf("no");
    }
    return 0;
}