#include <stdio.h>
#include <string.h>
typedef struct
{
    char name[50];
    int age;
    double score;
} Student;

int main()
{
    Student student[3];
    printf("请输入学生信息,注意姓名请单独一行输入\n");
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
        printf("%s%d%g",student[i].name,student[i].age,student[i].score);
    }
    return 0;
}