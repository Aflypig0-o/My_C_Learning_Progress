#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "World";
    printf("%zu\n",sizeof(str));
    printf("%zu",strlen(str));
    return 0;
}