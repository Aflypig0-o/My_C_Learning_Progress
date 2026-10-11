#ifndef FILE_IO_H
#define FILE_IO_H
#include <stdbool.h>

/*
 * file_to_save —— 保存一条计算记录到文件
 *
 * 参数：
 *     expression - 用户输入的表达式字符串
 *     result     - 计算结果
 *     filename   - 目标文件路径（如 "history.txt"）
 *
 * 返回：
 *     true  - 保存成功
 *     false - 文件打开失败
 */
bool file_to_save(const char *expression, double result, const char *filename);

#endif