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
        if(scanf("%d",&choice) != 1)
        {
            while(getchar() != '\n');
            printf("请输入数字选项\n");
            continue;
        }
        getchar();
        switch (choice)
        {
            case EXIT:
            {
                free(token_in);
                free(token_out);
                token_in = NULL;
                token_out = NULL;
                printf("退出成功\n");
                return 0;
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
                int sub;
                printf("1.显示精度  2.角度模式  3.保存历史  4.最大Token\n");
                printf("0.返回\n");
                if(scanf("%d", &sub) != 1)
                {
                    while(getchar() != '\n');
                    printf("请输入数字选项\n");
                    break;
                }
                getchar();

                switch (sub)
                {
                    case 1:
                    {
                        printf("当前: %d 位小数，输入新值: ", g_setting.decimal_places);
                        scanf("%d", &g_setting.decimal_places);
                        getchar();
                        break;
                    }
                    case 2:
                    {
                        int tmp;
                        printf("当前: %s,输入 1(弧度) 0(角度): ", g_setting.use_radians ? "弧度" : "角度");
                        if(scanf("%d", &tmp) != 1)
                        {
                            while(getchar() != '\n');
                            printf("输入无效\n");
                            break;
                        }
                        g_setting.use_radians = (tmp != 0);
                        getchar();
                        break;
                    }
                    case 3:
                    {
                        int tmp;
                        printf("当前: %s,输入 1(开) 0(关): ", g_setting.save_history ? "开" : "关");
                        if(scanf("%d", &tmp) != 1)
                        {
                            while(getchar() != '\n');
                            printf("输入无效\n");
                            break;
                        }
                        g_setting.save_history = (tmp != 0);
                        getchar();
                        break;
                    }
                    case 4:
                    {
                        int new_max;
                        printf("当前: %d,输入新值: ", g_setting.max_token);
                        if(scanf("%d", &new_max) != 1)
                        {
                            while(getchar() != '\n');
                            printf("输入无效\n");
                            break;
                        }
                        getchar();
                        if(new_max <= 0)
                        {
                            printf("值必须大于 0\n");
                            break;
                        }
                        Token *new_in = (Token*)realloc(token_in, new_max * sizeof(Token));
                        if(new_in == NULL)
                        {
                            perror("realloc");
                            break;
                        }
                        token_in = new_in;
                        Token *new_out = (Token*)realloc(token_out, new_max * sizeof(Token));
                        if(new_out == NULL)
                        {
                            perror("realloc");
                            break;
                        }
                        token_out = new_out;
                        g_setting.max_token = new_max;
                        break;
                    }
                    case 0:break;
                    default:
                    {
                        printf("无效选项\n");
                        break;
                    }
                }

                setting_save("setting.txt");
                setting_print();
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