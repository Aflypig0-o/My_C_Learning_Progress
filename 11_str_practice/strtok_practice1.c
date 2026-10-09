#include <stdio.h>
#include <string.h>

int main()
{
    char expr[] = {"3 4 2 * +"};
    char *token = strtok(expr," ");
    while(token != NULL)
    {
        printf("token: %s\n",token);
        token =  strtok(NULL," ");
    }
    return 0;
}