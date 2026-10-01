#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows,cols;
    scanf("%d%d",&rows,&cols);
    if(rows<1 || cols<1)
    {
        printf("unexpected input");
        return 0;
    }
    int **mat =(int**)malloc(rows*sizeof(int*));
    if(mat == NULL)
    {
        return 1;
    }
    for(int i=0;i<rows;++i)
    {
        mat[i] = (int*)malloc(cols*sizeof(int));
        if(mat[i] == NULL)
        {
            for(int j=0;j<i;++j)
            {
                free(mat[j]);
            }
            free(mat);
            return 1;
        }
    }
    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<cols;++j)
        {
            scanf("%d",&mat[i][j]);
        }
    }

    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<cols;++j)
        {
            printf("%d",mat[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<rows;++i)
    {
        free(mat[i]);
    }
    free(mat);
    return 0;
}