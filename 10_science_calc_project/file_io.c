#include <stdio.h>
#include "file_io.h"

bool file_to_save(const char *expression,double result,const char *filename)
{
    FILE *fp = fopen(filename,"w");
    if(fp == NULL)
    {
        perror("fopen");
        return false;
    }
    fprintf(fp,"%s %g\n",expression,result);
    fclose(fp);
    printf("已保存成功\n");
    return true;
}