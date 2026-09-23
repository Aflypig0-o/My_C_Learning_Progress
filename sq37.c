#include <stdio.h>
#include <stdbool.h>

int main()
{
    int arr[8] = {0};
    for(int i=0;i<8;++i)
    {
        scanf("%d",&arr[i]);
    }

    int *p = arr;
    int *q = arr + 7;
    bool is_palindrome = true;
    for(int i=0;i<4;++i)
    {
        if(*p != *q)
        {
            is_palindrome = false;
            break;
        }
        ++p;
        --q;
    }
    if(is_palindrome)
    {
        printf("yes");
    }
    else
    {
        printf("no");
    }
    return 0;
}