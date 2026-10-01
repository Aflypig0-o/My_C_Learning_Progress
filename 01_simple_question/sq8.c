#include <stdio.h>

int main()
{
    int sum = 0;
    int a,d,n,current;
    int i=1;
    scanf("%d%d%d",&a,&d,&n);
    current = a;
    for(i;i<n;i++)
    {
        current += d;
        sum += current;
    }
    if (n != 0)
    {
        sum += a;
    }
    printf("%d",sum);
    return 0;
}

/*可能存在的另一个解
#include <stdio.h>
int main()
{
    int sum=0;
    int a,d,n;
    sum = n*a + n*(n-1)/2*d;
    printf("%d",sum);
    return 0;
}
*/