#include <stdio.h>
#include <string.h>

void reverse_str(char *s,int left,int right)
{
    if(left>=right)
    {
        return;
    }
    else
    {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        reverse_str(s,++left,--right);
    }
}

int main()
{
    char str[50];
    fgets(str,50,stdin);
    str[strcspn(str,"\n")] = '\0';
    reverse_str(str,0,strlen(str)-1);
    printf("%s",str);
    return 0;
}