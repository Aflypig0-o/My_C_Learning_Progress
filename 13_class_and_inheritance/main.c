#include <stdio.h>
#include "rectangle.h"

int main()
{
    Rectangle rec;
    int width,height;
    printf("请输入长和宽\n");
    int ret = scanf("%d %d", &width, &height);
    if(ret < 2)
    {
        fprintf(stderr,"读取错误，请重新输入\n");
        return 1;
    }
    rect_init(&rec,width,height);
    printf("area: %d\n",rect_area(&rec));
    printf("perimeter: %d\n",rect_perimeter(&rec));
    return 0;
}