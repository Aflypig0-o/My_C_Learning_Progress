#include <stdio.h>
#include <string.h>

int main()
{
    char str[20];
    fgets(str,20,stdin);
    str[strcspn(str,"\n")] = '\0';
    printf("%s",str);
    return 0;
} 