#include <stdio.h>

typedef struct
{
    char name[50];
    char phone[20];
    int age;
}Contact;

int main()
{
    Contact arr[3] = {
        {"ZhangSan", "13800138000", 20},
        {"LiSi", "13900139000", 21},
        {"WangWu", "13700137000", 19}
    };

    FILE *fp = fopen("Contact.txt","w");
    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    for(int i=0;i<3;++i)
    {
        fprintf(fp,"%s %s %d\n",arr[i].name,arr[i].phone,arr[i].age);
    }
    fclose(fp);
    return 0;
}