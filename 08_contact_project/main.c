#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "file_io.h"

#define FILENAME "contact.txt"

void open_readme(void)
{
#ifdef _WIN32
    system("start README.md");
#elif __APPLE__
    system("open README.md");
#else
    system("xdg-open README.md");
#endif
}

void show_menu()
{
    printf("\n========== 通讯录 ==========\n");
    printf("1. 添加联系人\n");
    printf("2. 显示所有联系人\n");
    printf("3. 按姓名查找\n");
    printf("4. 按电话号码查找\n");
    printf("5. 按姓名删除\n");
    printf("6. 按电话号码删除\n");
    printf("7. 按姓名修改\n");
    printf("8. 按电话号码修改\n");
    printf("9. 关于本程序及其作者(查看README)\n"); 
    printf("0. 保存并退出\n");
    printf("============================\n");
    printf("请选择: ");
}

void add_contact(LinkedList *list)
{
    Contact c;
    char line[100];
    printf("请输入姓名: ");
    fgets(c.name,NAME_LEN,stdin);
    c.name[strcspn(c.name,"\n")] = '\0';
    printf("请输入电话: ");
    fgets(c.phone,PHONE_LEN,stdin);
    c.phone[strcspn(c.phone,"\n")] = '\0';
    printf("请输入年龄: ");
    fgets(line,100,stdin);
    sscanf(line,"%d",&c.age);
    if(list_push_back(list,c))
    {
        printf("添加成功\n");
    }
    else
    {
        printf("添加失败\n");
    }
}

void find_contact_by_name(LinkedList *list)
{
    char name[NAME_LEN];
    printf("请输入需要查找的姓名: ");
    fgets(name,NAME_LEN,stdin);
    name[strcspn(name,"\n")] = '\0';
    Node *p = list_find_by_name(list,name);
    if(p != NULL)
    {
        printf("找到: 姓名=%s  电话=%s  年龄=%d\n",p->data.name, p->data.phone, p->data.age);
    }
    else
    {
        printf("未找到%s\n",name);
    }
}

void find_contact_by_phone(LinkedList *list)
{
    char phone[PHONE_LEN];
    printf("请输入需要查找的电话号码: ");
    fgets(phone,PHONE_LEN,stdin);
    phone[strcspn(phone,"\n")] = '\0';
    Node *p = list_find_by_phone(list,phone);
    if(p != NULL)
    {
        printf("找到: 姓名=%s  电话=%s  年龄=%d\n",p->data.name, p->data.phone, p->data.age);
    }
    else
    {
        printf("未找到%s\n",phone);
    }
}

void remove_contact_by_name(LinkedList *list)
{
    char name[NAME_LEN];
    printf("请输入需要删除的姓名: ");
    fgets(name,NAME_LEN,stdin);
    name[strcspn(name,"\n")] = '\0';
    if(list_remove_by_name(list,name))
    {
        printf("已删除%s\n",name);
    }
    else
    {
        printf("未找到%s\n",name);
    }
}

void remove_contact_by_phone(LinkedList *list)
{
    char phone[PHONE_LEN];
    printf("请输入需要删除的电话号码: ");
    fgets(phone,PHONE_LEN,stdin);
    phone[strcspn(phone,"\n")] = '\0';
    if(list_remove_by_phone(list,phone))
    {
        printf("已删除%s\n",phone);
    }
    else
    {
        printf("未找到%s\n",phone);
    }
}

void modify_by_name(LinkedList *list)
{
    char name[NAME_LEN];
    printf("请输入需要修改的姓名: ");
    fgets(name,NAME_LEN,stdin);
    name[strcspn(name,"\n")] = '\0';
    Node *p = list_find_by_name(list,name);
    if(p == NULL)
    {
        printf("未找到%s\n",name);
        return;
    }
    printf("当前信息: 电话=%s  年龄=%d\n", p->data.phone, p->data.age);
    
    printf("请输入新电话: ");
    fgets(p->data.phone, PHONE_LEN, stdin);
    p->data.phone[strcspn(p->data.phone, "\n")] = '\0';

    char line[100];
    printf("请输入新年龄: ");
    fgets(line,100,stdin);
    sscanf(line,"%d",&p->data.age);
    printf("修改成功");
}

void modify_by_phone(LinkedList *list)//不会吧,不会真有人用这个功能吧,只记得号码不记得名字的来了,哈哈哈
{
    char phone[PHONE_LEN];
    printf("请输入需要修改的的电话号码: ");
    fgets(phone,PHONE_LEN,stdin);
    phone[strcspn(phone,"\n")] = '\0';    
    Node *p = list_find_by_phone(list,phone);
    if(p == NULL)
    {
        printf("未找到%s\n",phone);
        return;
    }
    printf("当前信息: 电话=%s  年龄=%d\n", p->data.phone, p->data.age);
    printf("请输入新的姓名: ");
    fgets(p->data.name,NAME_LEN,stdin);
    p->data.name[strcspn(p->data.name,"\n")] = '\0';

    printf("请输入新电话: ");
    fgets(p->data.phone, PHONE_LEN, stdin);
    p->data.phone[strcspn(p->data.phone, "\n")] = '\0';

    char line[100];
    printf("请输入新年龄: ");
    fgets(line,100,stdin);
    sscanf(line,"%d",&p->data.age);
    printf("修改成功");
}

int main()
{
    LinkedList list;
    if(!list_init(&list))
    {
        fprintf(stderr,"初始化失败");
        return EXIT_FAILURE;
    }
    list_load_from_file(&list,FILENAME);
    int choice;
    while(1)
    {
        show_menu();
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
            case 1:add_contact(&list);break;
            case 2:list_print(&list);break;
            case 3:find_contact_by_name(&list);break;
            case 4:find_contact_by_phone(&list);break;
            case 5:remove_contact_by_name(&list);break;
            case 6:remove_contact_by_phone(&list);break;
            case 7:modify_by_name(&list);break;
            case 8:modify_by_phone(&list);break;
            case 9:open_readme();break;
            case 0:
            {
                list_save_to_file(&list, FILENAME);
                list_destroy(&list);
                printf("再见!\n");
                return 0;
            }
            default:printf("无效结果,请重试\n");
        }
    }
    return 0;
}