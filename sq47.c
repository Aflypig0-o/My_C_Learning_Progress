#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    fgets(str,100,stdin);
    str[strcspn(str,"\n")] = '\0';
    printf("%zu",strlen(str));
    return 0; 
}