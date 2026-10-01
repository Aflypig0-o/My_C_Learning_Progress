#include <stdio.h>

int main()
{
    FILE *fp = fopen("data.txt","w");
    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    fprintf(fp,"name:Aflypig0_o\n");
    fprintf(fp,"age:18\n");
    fprintf(fp,"How to create a Minecraft mod?\n");
    fclose(fp);
    printf("finish\n");
    return 0;
}