#include <stdio.h>
#include <string.h>

int main()
{
    int space = 0;
    char str[100];
    fgets(str,100,stdin);
    str[strcspn(str,"\n")] = '\0';
    for(int i=0;str[i] != '\0';++i)
    {
        if(str[i] == ' ')
        {
            ++space;
        }
    }
    printf("一共有%d个单词",(space+1));
    return 0;
}