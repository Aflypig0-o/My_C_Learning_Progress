#ifndef RECTANGLE_H
#define RECTANGLE_H

typedef struct
{
    int width;
    int height;
}Rectangle;

void Rect_init(Rectangle *this, int w, int h);
int Rect_area(Rectangle *this);
int Rect_perimeter(Rectangle *this);

#endif 