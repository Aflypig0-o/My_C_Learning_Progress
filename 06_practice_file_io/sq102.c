#include <stdio.h>

int main()
{
    FILE *fp = fopen("data.txt","r");
    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    char line[100];
    while(fgets(line,100,fp) !=NULL)
    {
        printf("%s",line);
    }
    fclose(fp);
    return 0;
}