#include <stdio.h>
#include <string.h>
#include "setting.h"

/* 全局设置变量，定义在这里 */
Setting g_setting;

void setting_init(void)
{
    g_setting.decimal_places = 6;
    g_setting.use_radians = true;
    g_setting.save_history = true;
    strcpy(g_setting.history_file, "history.txt");
    g_setting.max_token = 256;
}

void setting_print(void)
{
    printf("=== 当前设置 ===\n");
    printf("显示精度:   %d 位小数\n", g_setting.decimal_places);
    printf("角度模式:   %s\n", g_setting.use_radians ? "弧度制" : "角度制");
    printf("保存历史:   %s\n", g_setting.save_history ? "是" : "否");
    printf("历史文件:   %s\n", g_setting.history_file);
    printf("最大Token:  %d\n", g_setting.max_token);
}

bool setting_save(const char *path)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        perror("fopen");
        return false;
    }
    fprintf(fp, "decimal_places=%d\n", g_setting.decimal_places);
    fprintf(fp, "use_radians=%d\n", g_setting.use_radians);
    fprintf(fp, "save_history=%d\n", g_setting.save_history);
    fprintf(fp, "history_file=%s\n", g_setting.history_file);
    fprintf(fp, "max_token=%d\n", g_setting.max_token);
    fclose(fp);
    return true;
}

bool setting_load(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        return false;
    }

    fscanf(fp, "decimal_places=%d", &g_setting.decimal_places);
    fscanf(fp, "use_radians=%d", (int *)&g_setting.use_radians);
    fscanf(fp, "save_history=%d", (int *)&g_setting.save_history);
    fscanf(fp, "history_file=%255s", g_setting.history_file);
    fscanf(fp, "max_token=%d", &g_setting.max_token);

    fclose(fp);
    return true;
}