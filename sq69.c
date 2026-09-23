#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define AVERAGE(sum) ((sum)/(5.0))//定义宏

typedef struct//定义Student结构体
{
    char name[50];
    int age;
    double score;
}Student;

void find_max()
{
    
}

void sort(Student *student[5],double *student[].score)
{
    bool is_swapped = false;//判定是否发生交换，初始为否，如果循环后仍为否表示已经有序无须进行后续循环
}

int main()
{
    double sum = 0;
    char line[100];
    Student student[5];//定义五个学生
    for(int i=0;i<5;++i)//输入学生数据
    {
        fgets(student[i].name,50,stdin);
        student[i].name[strcspn(student[i].name,"\n")] = '\0';
        fgets(line,100,stdin);
        sscanf(line,"%d%lf",&student[i].age,&student[i].score);//sscanf从字符串中读取数据
    }

    for(int i=0;i<5;++i)
    {
        sum += student[i].score;
    }

    printf("%g",AVERAGE(sum));


    return 0;
}