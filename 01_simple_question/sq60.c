#include <stdio.h>
typedef enum {IDLE=0,RUNNING,PAUSED,STOPPED} State;
int main()
{
    State current = RUNNING;
    switch (current)
    {
        case IDLE :printf("空闲");break;
        case RUNNING : printf("运行中");break;
        case PAUSED : printf("暂停");break;
        case STOPPED : printf("结束");break;
    }
    return 0;
}