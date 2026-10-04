#include <stdio.h>
#include "postfix.h"

int main()
{
    const char *tests[] = {
        "3 4 2 * +",      // 11
        "5 1 2 + 4 * + 3 -",  // 14
        "1 2 +",          // 3
        "6 2 /",          // 3
        "5 3 -",          // 2
        "2 3 *",          // 6
    };
    
    int n = sizeof(tests) / sizeof(tests[0]);
    for(int i = 0; i < n; ++i)
    {
        int result;
        if (eval_postfix(tests[i], &result))
        {
            printf("Postfix expression: %s = %d\n", tests[i], result);
        }
        else
        {
            printf("Error evaluating postfix expression: %s\n", tests[i]);
        }
    }
    return 0;
}