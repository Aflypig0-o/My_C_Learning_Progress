#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "wordlist.h"
#include "tokenizer.h"
#include "detector.h"

int main(void)
{
    // 切换控制台输出编码为 UTF-8，确保中文不乱码
    SetConsoleOutputCP(65001);

    // ========== 1. 加载两个词表 ==========
    static WordList big;       // 大表（四级）
    static WordList small;     // 小表（高考）
    static WordList target;    // 目标表（剔除后）

    if (!wordlist_load(&big, "data/cet4.txt")) {
        fprintf(stderr, "加载 cet4.txt 失败\n");
        return 1;
    }
    if (!wordlist_load(&small, "data/gaokao3500.txt")) {
        fprintf(stderr, "加载 gaokao3500.txt 失败\n");
        return 1;
    }

    printf("大表：%d 个词\n", big.count);
    printf("小表：%d 个词\n", small.count);

    // ========== 2. 剔除 ==========
    target = big;                       // 结构体整体赋值
    wordlist_remove_all(&target, &small);
    printf("目标词表：%d 个词\n", target.count);

    wordlist_save(&target, "output/cet4_only.txt");

    // ========== 3. 切分试卷 ==========
    static TokenList tokens;
    if (!tokenize_file("data/exam.txt", &tokens)) {
        fprintf(stderr, "加载 exam.txt 失败\n");
        return 1;
    }
    printf("试卷：%d 个单词\n", tokens.count);

    // ========== 4. 匹配 ==========
    static DetectionResult result;
    detector_find(&tokens, &target, &result);
    printf("找到 %d 个生词\n", result.count);

    // ========== 5. 输出 ==========
    detector_print(&result);
    detector_save(&result, "output/result.txt");
    printf("\n按任意键退出...");
    _getch();
    return 0;
}