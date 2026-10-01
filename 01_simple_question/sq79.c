#include <stdio.h>

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

void print_all(const Student *arr,int len)
{
    const Student *p = arr;
    for(int i=0;i<len;++i)
    {
        printf("%s %d %g\n",p->name,p->age,p->score);
        ++p;
    }
}

int main()
{
    Student student[3] = {
         {"张三", 18, 95.5},
        {"李四", 19, 88.0},
        {"王五", 20, 76.5}
    };
    print_all(student,3);
    return 0;
}