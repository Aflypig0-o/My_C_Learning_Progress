#include <stdio.h>
#include <string.h>
typedef struct
{
    char name[50];
    double price;
    int page;
}Book;

int main()
{
    Book s1;
    fgets(s1.name,50,stdin);
    s1.name[strcspn(s1.name,"\n")] = '\0';
    scanf("%lf%d",&s1.price,&s1.page);
    printf("%s\n%g\n%d",s1.name,s1.price,s1.page);
    return 0;
}