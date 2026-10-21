#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159

// 1. 定义父类：Shape（图形）
typedef struct Shape Shape;

struct Shape{
    char name[20];
    // 父类定义了一个函数指针“槽位”，所有继承它的子类，必须把这个槽位填上自己的实现
    double (*area)(Shape *self); 
} ;

// 2. 定义子类：Rectangle（长方形），继承自 Shape
typedef struct {
    Shape base; // 把父类放第一位
    double width;
    double height;
} Rectangle;

// 3. 定义子类：Circle（圆），继承自 Shape
typedef struct {
    Shape base; 
    double radius;
} Circle;

// ==========================================
// 你的任务从这里开始：

// 任务 1：实现长方形的面积计算
static double rect_area(Shape *self) {
    // 魔法第二步：把父类指针强转回真正的子类指针
    Rectangle *r = (Rectangle *)self;

    // 写代码：返回长方形的面积 (宽 * 高)

    return r->width * r->height;
}

// 任务 2：实现圆形的面积计算
static double circle_area(Shape *self) {
    Circle *c = (Circle *)self;
    
    // 写代码：返回圆的面积 (3.14159 * r * r)
    return PI * c->radius * c->radius;
}

// 任务 3：实现创建长方形的工厂函数
Shape* create_rect(double w, double h) {
    Rectangle *r = (Rectangle *)malloc(sizeof(Rectangle));
    if (r == NULL) return NULL;
    
    // 1. 设置父类属性
    strcpy(r->base.name, "Rectangle");
    // 2. 绑定函数指针
    r->base.area = rect_area; 
    
    // 3. 设置子类属性
    r->width = w;
    r->height = h;
    
    // 4. 向上转型：把 Rectangle* 当成 Shape* 返回
    return (Shape *)r; 
}

// 任务 4：实现创建圆形的工厂函数
Shape* create_circle(double radius) {
    // 参考任务 3，自己写
    Circle *c = (Circle*)malloc(sizeof(Circle));
    if(c == NULL)
    {
        perror("malloc");
        return NULL;
    }
    strcpy(c->base.name,"Circle");
    c->base.area = circle_area;
    c->radius = radius;
    return (Shape*)c;
}

// ==========================================

int main() {
    // 核心演示：一个存放“图形”的通用数组
    Shape *shapes[2];
    
    // 创建时，各自伪装成 Shape
    shapes[0] = create_rect(4.0, 5.0);
    shapes[1] = create_circle(3.0);

    // 遍历数组，统一调用！
    for(int i = 0; i < 2; i++) {
        // 这就是多态！我们不需要知道 shapes[i] 到底是圆还是长方形，
        // 只需要知道它是一个 Shape，直接调 area 即可。
        printf("%s 的面积是: %.2f\n", shapes[i]->name, shapes[i]->area(shapes[i]));
    }

    // 释放内存
    free(shapes[0]);
    free(shapes[1]);
    return 0;
}