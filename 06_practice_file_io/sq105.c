#include <stdio.h>

typedef struct
{
    char name[50];
    char phone[20];
    int age;
}Contact;

int main()
{
    Contact c;
    FILE *fp = fopen("Contact.txt","r");
    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    fscanf(fp,"%s %s %d",c.name,c.phone,&c.age);
    printf("%s\n",c.name);
    printf("%s\n",c.phone);
    printf("%d\n",c.age);
    fclose(fp);
    return 0;
}