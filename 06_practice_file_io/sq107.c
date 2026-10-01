#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[50];
    char phone[20];
    int age;
}Contact;

int main()
{
    Contact *arr = (Contact*)malloc(3*sizeof(Contact));
    if(arr == NULL)
    {
        perror("malloc");
        return 1;
    }
    int count = 0;
    FILE *fp = fopen("Contact.txt","r");
    if(fp == NULL)
    {
        perror("fopen");
        free(arr);
        return 2;
    }
    while(count<3 && fscanf(fp,"%s %s %d",arr[count].name,arr[count].phone,&arr[count].age) == 3)
    {
        ++count;
    }
    fclose(fp);
    printf("共%d个联系人\n",count);
    for(int i=0;i<count;++i)
    {
        printf("%s %s %d\n",arr[i].name,arr[i].phone,arr[i].age);
    }
    free(arr);
    return 0;
}