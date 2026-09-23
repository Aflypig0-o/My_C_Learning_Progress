#include <stdio.h>
typedef enum {MENU_EXIT = 0,MENU_ADD,MENU_SUB,MENU_MUL} MenuOption;

int main()
{
    int choice;
    double a,b;
    do
    {
        printf("请选择,0退出,1加法,2减法,3乘法\n");
        scanf("%d",&choice);
        if(choice == MENU_EXIT)
        {
            break;
        }
        printf("请输入a和b\n");
        scanf("%lf%lf",&a,&b);
        switch ((MenuOption)choice)
        {
            case MENU_ADD :printf("%lf\n",(a+b));break;
            case MENU_SUB :printf("%lf\n",(a-b));break;
            case MENU_MUL :printf("%lf\n",(a*b));break;
            default : printf("Unexcepted input");break;
        }
    }while(choice != MENU_EXIT);
    printf("再见");
    return 0;
}