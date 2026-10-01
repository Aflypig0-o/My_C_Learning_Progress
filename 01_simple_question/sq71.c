#include <stdio.h>
typedef struct 
{
    char name[50];
    int age;
    double score;
}Student;

int main()
{
    Student student[3] = {
    {"张三", 18, 95.5},
    {"李四", 19, 88.0},
    {"王五", 20, 76.5}
    };
    Student *p = student;
    for(int i=0;i<3;++i)
    {
        printf("%s %d %g\n",p->name,p->age,p->score);
        ++p;
    }
    return 0;
}