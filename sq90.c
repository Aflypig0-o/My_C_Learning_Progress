#include <stdio.h>

void hanoi(int n,char from,char to,char via)
{
    if(n==1)
    {
        printf("%c -> %c\n",from,to);
        return;
    }
    else
    {
        hanoi(n-1,from,via,to);
        printf("%c -> %c\n",from,to);
        hanoi(n-1,via,to,from);
    }
}

int main()
{
    char A,B,C;
    int number;
    scanf("%d",&number);
    hanoi(number,'A','C','B');
    return 0;
}