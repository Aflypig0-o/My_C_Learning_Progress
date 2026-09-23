#include <stdio.h>
typedef struct 
{
    char name[50];
    int age;
    double score;
}Student;

void print_student(const Student *s)
{
    printf("%s %d %g",s->name,s->age,s->score);
}

int main()
{
    Student student = {"张三",18,90.0};
    print_student(&student);
    return 0;
}