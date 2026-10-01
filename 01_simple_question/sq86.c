#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

typedef enum {
    exit = 0,
    add,
    show,
    find,
    delete,
}Choice;

typedef struct
{
    char name[50];
    char phone[20];
    int age;
}Contact;

void add_contact(Contact *list,int *count)
{
    char line[100];
    printf("姓名:");
    fgets(list[*count].name,50,stdin);
    list[*count].name[strcspn(list[*count].name,"\n")] = '\0';
    printf("\n电话:");
    fgets(list[*count].phone,20,stdin);
    list[*count].phone[strcspn(list[*count].phone,"\n")] = '\0';
    printf("\n年龄:");
    fgets(line,100,stdin);
    sscanf(line,"%d",&list[*count].age);
    ++(*count);
}

void show_all(const Contact *list,int count)
{
    for(int i=0;i<count;++i)
    {
        printf("姓名:%s\n电话:%s\n年龄:%d\n",list[i].name,list[i].phone,list[i].age);
    }
}

Contact *find_contact(Contact *list,int count,const char *name)
{
    for(int i=0;i<count;++i)
    {
        if(strcmp(list[i].name,name) == 0)
        {
            return &list[i];
        }
    }
        return NULL;
}

void delete_contact(Contact *list,int *count,const char *name)
{
    for(int i=0;i<*count;++i)
    {
        if(strcmp(list[i].name,name) ==0 )
        {
            for(int j = i;j<*count-1;++j)
            {
                list[j] = list [j+1];
            }
            --(*count);
            printf("删除成功\n");
            return;
        }
    }
    printf("未找到%s\n",name);
}
int main()
{
    int c = 0;
    Contact contact[MAX];  
    bool is_continue = true;
    Choice choice;
    do
    {
        printf("==========通讯录==========");
        printf("请输入:\n1.添加联系人\n2.显示所有联系人\n3.查找联系人\n4.删除联系人\n0.退出\n");
        scanf("%d",&choice);
        getchar();
        switch(choice)
        {
            case exit :
            {
                printf("谢谢,再见");
                is_continue = false;
                break;
            }
            case add :
            {
                add_contact(contact,&c);
                printf("添加完成,请重新选择\n");
                break;
            }

            case show :
            {
                show_all(contact,c);
                break;
            }
            case find :
            {
                char find_name[50];
                printf("请输入姓名:");
                fgets(find_name,50,stdin);
                find_name[strcspn(find_name,"\n")] = '\0';
                Contact *found = find_contact(contact,c,find_name);
                if(found != NULL)
                {
                    printf("找到 %s %s %d\n",found->name,found->phone,found->age);
                    break;
                }
                else
                {
                    printf("not found\n");
                    break;
                }
            }
            case delete :
            {
                char find_name[50];
                printf("请输入姓名:");
                fgets(find_name,50,stdin);
                find_name[strcspn(find_name,"\n")] = '\0';
                delete_contact(contact,&c,find_name);
                break;
            }
            default : printf("意外的输入,请重新选择\n");break;
        }
    }while(is_continue);
    return 0;
}