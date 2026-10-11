#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "setting.h"
#include "doublestack.h"
#include "basic_calc.h"
#include "file_io.h"

/* 打开 README.md */
void open_readme(void)
{
#ifdef _WIN32
    system("start README.md");      // Windows: 用默认程序打开
#elif __APPLE__
    system("open README.md");       // macOS
#else
    system("xdg-open README.md");   // Linux
#endif
}

typedef enum
{
    EXIT = 0,
    BASIC_CALC = 1,
    SETTING = 8,
    READ_ME = 9  
}Choice;

int main(void)
{
    if(!setting_load("setting.txt"))
    {
        setting_init();
        setting_save("setting.txt");
    }
    Choice choice;
    char expression[256];
    Token *token_in = (Token*)malloc(g_setting.max_token * sizeof(Token));
    Token *token_out = (Token*)malloc(g_setting.max_token * sizeof(Token));
    if(token_in == NULL || token_out == NULL)
    {
        perror("malloc");
        free(token_in);
        free(token_out);
        return 1;
    }
    while(1)
    {
        printf("==========科学计算器v0.02测试版==========\n");
        printf("请选择:\n1.基础运算\n8.设置\n9.查看README\n0.退出\n");
        scanf("%d",&choice);
        getchar();
        switch (choice)
        {
            case EXIT:
            {
                free(token_in);
                free(token_out);
                token_in = NULL;
                token_out = NULL;
                printf("退出成功\n");return;
            }
            case BASIC_CALC:
            {
                double basic_final_result;
                printf("请输入表达式:\n");
                fgets(expression,256,stdin);
                expression[strcspn(expression,"\n")] = '\0';
                if(!handle_basic_calc(expression,token_in,token_out,&basic_final_result))
                {
                    fprintf(stderr,"计算失败");
                    break;
                }

                printf("%s = %g\n",expression,basic_final_result);
                if(g_setting.save_history)
                {
                    file_to_save(expression,basic_final_result,"history.txt");
                    break;
                }
                else
                {
                    break;
                }
            }
            case SETTING:
            {
                break;
            }
            case READ_ME:
            {
                open_readme();
                break;
            }
            default:printf("意外的输入，请再试一次");break;
        }
    }
    return 0;
}