#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *token = "3.14";
    char *end;
    double value = strtod(token, &end);

    if (end == token) {
        // 没有数字被转换，说明 token 不是数字
        printf("不是数字\n");
    } else if (*end != '\0') {
        // 有部分字符没被转换，比如 "3.14abc"
        printf("部分转换\n");
    } else {
        printf("完全转换：%f\n", value);   // 3.140000
    }
    return 0;
}