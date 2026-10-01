#include <stdio.h>

typedef struct
{
    char name[50];
    char phone[20];
    int age;
}Contact;

int main()
{
    Contact c = {"Aflypig0_o", "13812345678", 18};
    FILE *fp = fopen("Contact.txt","w");
    if(fp == NULL)
    {
        perror("fopen");
        return 1;
    }
    fprintf(fp,"%s %s %d\n",c.name,c.phone,c.age);
    fclose(fp);
    return 0;
}