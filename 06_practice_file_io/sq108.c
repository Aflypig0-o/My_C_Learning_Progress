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
    int capacity = 4;
    int count = 0;
    Contact *arr = (Contact*)malloc(capacity*sizeof(Contact));
    if(arr == NULL)
    {
        perror("malloc");
        return 1;
    }
    FILE *fp = fopen("Contact.txt","r");
    if(fp == NULL)
    {
        perror("fopen");
        free(arr);
        return 2;
    }
    while(fscanf(fp,"%s %s %d",arr[count].name,arr[count].phone,&arr[count].age) == 3)
    {
        ++count;
        if(count == capacity)
        {
            capacity *= 2;
            Contact *temp = (Contact*)realloc(arr,capacity*sizeof(Contact));
            if(temp == NULL)
            {
                perror("realloc");
                free(arr);
                return 3;
            }
            arr = temp;
        }
    }
    printf("共有%d个联系人\n",count);
    for(int i=0;i<count;++i)
    {
        printf("%s %s %d\n",arr[i].name,arr[i].phone,arr[i].age);
    }
    free(arr);
    return 0;
}