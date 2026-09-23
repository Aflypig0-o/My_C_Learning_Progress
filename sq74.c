#include <stdio.h>

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

void birthday(Student *s1)
{
    s1->age++;
}

int main()
{
    Student s1 = {"张三", 18, 95.5};
    birthday(&s1);
    printf("%s %d %g",s1.name,s1.age,s1.score);
    return 0;
}