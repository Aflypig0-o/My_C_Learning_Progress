#include <stdio.h>
#include <stdlib.h>

typedef struct Rectangle
{
    int width;
    int height;
    int (*rect_area) (struct Rectangle *self);
    void(*rect_scale) (struct Rectangle *self,int factor);
}Rectangle;

static int rect_area_impl(struct Rectangle *self)
{
    if(self == NULL)
    {
        fprintf(stderr,"error\n");
        return -1;
    }  
    return self->width * self->height;
}

static void rect_scale_impl(struct Rectangle *self,int factor)
{
    if(factor <= 0)
    {
        fprintf(stderr,"无意义取值，请重新输入\n");
        return;
    }
    self->width *= factor;
    self->height *= factor;
}

void rect_init(Rectangle *self,int w,int h)
{
    self->width = w;
    self->height = h;
    self->rect_area = rect_area_impl;
    self->rect_scale = rect_scale_impl;
}

int main()
{
    Rectangle r;
    rect_init(&r, 5, 3);
    printf("原始面积: %d\n", r.rect_area(&r));
    
    r.rect_scale(&r, 2); // 放大2倍
    printf("放大后面积: %d\n", r.rect_area(&r));
    
    return 0;
}
