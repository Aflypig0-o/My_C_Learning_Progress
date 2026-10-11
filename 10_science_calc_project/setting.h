/*
 * ============================================================
 *  setting.h —— 全局设置
 * ============================================================
 *  管理计算器的运行时配置：
 *      - 显示精度
 *      - 角度/弧度模式
 *      - 是否保存历史记录
 *      - 历史记录文件路径
 *      - 最大 Token 数
 *
 *  使用方式：
 *      任何模块通过 extern 声明访问 g_setting，
 *      修改后调用 setting_save 持久化到文件。
 */

#ifndef SETTING_H
#define SETTING_H
#include <stdbool.h>

/*
 * Setting —— 设置结构体
 *
 * decimal_places - 显示精度（小数位数），默认 6
 * use_radians    - 是否使用弧度制，默认 true
 * save_history   - 是否自动保存历史记录，默认 true
 * history_file   - 历史记录文件路径，默认 "history.txt"
 * max_token      - 最大 Token 数，默认 256
 */
typedef struct
{
    int decimal_places;
    bool use_radians;
    bool save_history;
    char history_file[256];
    int max_token;
} Setting;

/* 全局设置，任何模块都可以直接访问和修改 */
extern Setting g_setting;

/* 初始化（填默认值），再次调用会重置 */
void setting_init(void);

/* 打印当前设置到 stdout */
void setting_print(void);

/* 把设置写入文件（key=value 格式） */
bool setting_save(const char *path);

/* 从文件读取设置（覆盖当前值），文件不存在返回 false */
bool setting_load(const char *path);

#endif