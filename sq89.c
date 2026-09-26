#include <stdio.h>
#include <stdbool.h>
#define MAX 100

bool is_palindrome(int arr[],int left,int right)
{
    if(left>=right)
    {
        return true;
    }
    if(arr[left]!=arr[right])
    {
        return false;
    }
    else
    {
        return is_palindrome(arr,++left,--right);
    }
}
int main()
{
    bool palindrome = false;
    int arr[MAX] = {0};
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
    palindrome = is_palindrome(arr,0,n-1);
    if(!palindrome)
    {
        printf("不是");
    }
    else
    {
        printf("是");
    }
    return 0;
}