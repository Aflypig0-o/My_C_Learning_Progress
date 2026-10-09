#include <stdio.h>
#include <string.h>

int main()
{
    const char *expr = "3 4 2 * +";
    const char *start = expr;

    while (*start)
    {
        // 跳过前导空格
        while (*start == ' ')
            start++;
        if (*start == '\0')
            break;

        // 找到 token 结尾
        const char *end = start;
        while (*end && *end != ' ')
            end++;

        // 打印（用 %.*s 按长度打印，不需要拷贝）
        printf("token: %.*s\n", (int)(end - start), start);

        start = end;
    }
    return 0;
}