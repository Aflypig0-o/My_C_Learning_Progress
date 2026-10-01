#include <stdio.h>

int main()
{
    FILE *fp = fopen("data.txt","a");
    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    fprintf(fp,"Hello,GitHub\n");
    fprintf(fp,"How can I learn the way to create a Minecraft mod?\n");
    fclose(fp);
    return 0;
}