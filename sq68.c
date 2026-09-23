#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct 
{
    char name[50];
    int age;
    double score;
}Student;

int main()
{
    Student student[3];
    char line[100];
    for(int i=0;i<3;++i)
    {
        fgets(student[i].name,50,stdin);
        student[i].name[strcspn(student[i].name,"\n")] = '\0';
        fgets(line,100,stdin);
        sscanf(line,"%d%lf",&student[i].age,&student[i].score);
    }

    for(int i=0;i<2;++i)
    {
        bool is_swapped = false;
        for(int j=0;j<2-i;++j)
        {
            if(student[j].score < student[j+1].score)
            {
                Student temp = student[j];
                student[j] = student[j+1];
                student[j+1] = temp;
                is_swapped = true;
            }
        }
        if(!is_swapped)
        {
            break;
        }
    }

    for(int i=0;i<3;++i)
    {
        printf("%s\n%d\n%g",student[i].name,student[i].age,student[i].score);
    }
    return 0;
}