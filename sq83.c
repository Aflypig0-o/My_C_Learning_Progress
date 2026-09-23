#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

void input_students(Student *arr,int n)
{
    for(int i=0;i<n;++i)
    {
        char line[100];
        fgets(arr[i].name,50,stdin);
        arr[i].name[strcspn(arr[i].name,"\n")] = '\0';
        fgets(line,100,stdin);
        sscanf(line,"%d%lf",&arr[i].age,&arr[i].score);
    }
}

void print_students(const Student *arr,int n)
{
    for(int i=0;i<n;++i)
    {
        printf("%s %d %g\n",arr[i].name,arr[i].age,arr[i].score);
    }
}

double calc_average(Student *arr,int n)
{
    double sum = 0;
    double aver;
    for(int i=0;i<n;++i)
    {
        sum += arr[i].score;
    }
    aver = sum / (double)n;
    return aver;
}

void find_max(Student *arr,int n,int *best_max)
{
    int count = 0;
    int max_index = 0;
    for(int i=1;i<n;++i)
    {
        if(arr[i].score > arr[max_index].score)
        {
            max_index = i;
        }
    }
    for(int i=0;i<n;++i)
    {
        if(arr[i].score == arr[max_index].score)
        {
            best_max[count] = i;
            ++count;
        }
    }

    printf("成绩最好的学生信息:\n");

    for(int j=0;j<count;++j)
    {
        printf("%s %d %g\n",arr[best_max[j]].name,arr[best_max[j]].age,arr[best_max[j]].score);
    }
}

int main()
{
    int c = 0;
    Student student[MAX];
    int best_index[3] = {0};
    int n =3;
    input_students(student,n);
    print_students(student,n);
    double average = calc_average(student,n);
    printf("%g\n",average);
    find_max(student,3,best_index);
    return 0;
}