#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

Student *find_max(Student *arr,int len)
{
    if(len <= 0)
    return NULL;
    int max_index= 0;
    for(int i=1;i<len;++i)
    {
        if(arr[i].score > arr[max_index].score)   
        {
            max_index= i;
        }
    }
    return &arr[max_index];
}

int main()
{
    Student student[3] = { 
        {"张三", 18, 95.5},
        {"李四", 19, 88.0},
        {"王五", 20, 76.5}
    };
    Student *best = find_max(student,3);
    printf("%s %d %g",best->name,best->age,best->score);
    return 0;
}