#include <stdio.h>
#include <string.h>

int main()
{
    char alpha;
    char str[100];
    fgets(str,100,stdin);
    str[strcspn(str,"\n")] = '\0';
    scanf("%c",&alpha);
    char *p = strchr(str,alpha);
    if(p != NULL)
    {
        printf("%d",(int)(p-str+1));
    }
    else
    {
        printf("Not found");
    }
    return 0;
}