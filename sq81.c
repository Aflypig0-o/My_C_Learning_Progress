#include <stdio.h>

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

double average(Student *arr,int len)
{
    if(len <=0)
    {
        printf("unexpected input");
        return 0;
    }
    double sum = 0;
    double aver;
    Student *p = arr;
    for(int i=0;i<len;++i)
    {
        sum += p->score;
        ++p;
    }
    aver = sum / (double)len;
    return aver;
}

int main()
{
    Student student[3] = {
        {"张三", 18, 95.5},
        {"李四", 19, 88.0},
        {"王五", 20, 76.5}
    };
    printf("%g",average(student,3));
    return 0;
}