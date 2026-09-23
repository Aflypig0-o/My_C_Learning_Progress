#include <stdio.h>
#include <string.h>

#define AVERAGE(sum) ((sum)/(3.0))

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

int main()
{
    Student student[3];
    double sum = 0;
    for(int i=0;i<3;++i)
    {
        char line[100];
        fgets(student[i].name,50,stdin);
        student[i].name[strcspn(student[i].name,"\n")] = '\0';
        fgets(line,100,stdin);
        sscanf(line,"%d%lf",&student[i].age,&student[i].score);
    }
    for(int i=0;i<3;++i)
    {
        sum += student[i].score;
    }

    printf("%g",AVERAGE(sum));
    return 0;
}