#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

int main()
{
    int count = 0;
    int index_max[3] = {0};
    Student student[3];
    for(int i=0;i<3;++i)
    {
        char line[100];
        fgets(student[i].name,50,stdin);
        student[i].name[strcspn(student[i].name,"\n")] = '\0';
        fgets(line,100,stdin);
        sscanf(line,"%d%lf",&student[i].age,&student[i].score);
    }
    double max = student[0].score;
    for(int i=1;i<3;++i)
    {
        if(student[i].score > max)
        {
            max = student[i].score;
        }
    }
    for(int i=0;i<3;++i)
    {
        if(student[i].score == max)
        {
            index_max[count] = i;
            ++count;
        }
    }
    printf("最高分:%g\n",max);
    printf("学生是:");
    for(int j=0;j<count;++j)
    {
        printf("%s ",student[index_max[j]].name);
    }
    return 0;
}