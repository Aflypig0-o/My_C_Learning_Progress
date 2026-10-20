#include "rectangle.h"

void rect_init(Rectangle *this,int w,int h)
{
    this->width = w;
    this->height = h;
}

int rect_area(Rectangle *this)
{
    int area = this->width * this->height;
    return area;
}

int rect_perimeter(Rectangle *this)
{
    int perimeter = (this->width + this->height) * 2;
    return perimeter;
}