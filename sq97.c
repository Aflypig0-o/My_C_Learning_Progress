#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row,col;
    scanf("%d%d",&row,&col);
    int **mat =(int**)malloc(row*sizeof(int*));
    if(mat==NULL)
    {
        return 1;
    }
    for(int i=0;i<col;++i)
    {
        mat[i] = (int*)malloc(col*sizeof(int));
        if(mat[i] == NULL)
        {
            free(mat);
            return 1;
        }
    }
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            scanf("%d",&mat[i][j]);
        }
    }
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            free(mat[j]);
        }
        free(mat);
    }
    return 0;
}   
