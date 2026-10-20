#ifndef RECTANGLE_H
#define RECTANGLE_H

typedef struct
{
    int width;
    int height;
}Rectangle;

void rect_init(Rectangle *this, int w, int h);
int rect_area(Rectangle *this);
int rect_perimeter(Rectangle *this);

#endif 