#include <stdio.h>
#include "file_io.h"

bool list_save_to_file(LinkedList *list,const char *filename)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    FILE *fp = fopen(filename,"w");
    if(fp == NULL)
    {
        perror("fopen");
        return false;
    }
    Node *p = list->head->next;
    while(p != NULL)
    {
        fprintf(fp,"%s %s %d\n",p->data.name,p->data.phone,p->data.age);
        p = p->next;
    }
    fclose(fp);
    printf("已经保存%zu个联系人到%s\n",list->size,filename);
    return true;
}

bool list_load_from_file(LinkedList *list,const char *filename)
{
    if(list == NULL || list->head == NULL)
    {
        return false;
    }
    FILE *fp = fopen(filename,"r");
    if(fp == NULL)
    {
        perror("fopen");
        return false;
    }
    Contact c;
    int count = 0;
    while(fscanf(fp,"%s %s %d",c.name,c.phone,&c.age) == 3)
    {
        list_push_back(list,c);
        ++count;
    }
    fclose(fp);
    printf("已从%s中读取%d个联系人\n",filename,count);
    return true;
}