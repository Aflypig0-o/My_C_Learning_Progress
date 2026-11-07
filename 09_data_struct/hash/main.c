#include <stdio.h>
#include "hash.h"

int main() {
    printf("========== 哈希表（拉链法）测试 ==========\n");
    
    // 创建一个容量为 10 的哈希表（桶数组长度为 10）
    hash_table *dict = hash_table_create(10);
    
    // 1. 插入一些数据
    dict->put(dict, "apple", "苹果");
    dict->put(dict, "banana", "香蕉");
    dict->put(dict, "orange", "橘子");
    dict->put(dict, "computer", "电脑");
    dict->put(dict, "c language", "C语言");

    // 2. 测试查找
    printf("查找 apple: %s\n", dict->get(dict, "apple"));
    printf("查找 computer: %s\n", dict->get(dict, "computer"));
    printf("查找 c language: %s\n", dict->get(dict, "c language"));
    
    // 3. 测试查找不存在的 key
    const char *res = dict->get(dict, "watermelon");
    if (res == NULL) {
        printf("查找 watermelon: 未找到 (正确)\n");
    }

    // 4. 测试更新（覆盖原有的 value）
    dict->put(dict, "apple", "红苹果");
    printf("更新后查找 apple: %s\n", dict->get(dict, "apple"));

    // 5. 销毁
    dict->destroy(dict);
    printf("========== 测试结束，内存已销毁 ==========\n");

    return 0;
}