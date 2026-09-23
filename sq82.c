#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    char name[50];
    int age;
    double score;
}Student;

void sort_by_score(Student *arr,int len)
{
    for(int i=0;i<len-1;++i)
    {
        bool is_swapped = false;
        for(int j=0;j<len-i-1;++j)
        {
            if(arr[j].score < arr[j+1].score)
            {
                Student temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                is_swapped = true;
            }
        }
        if(!is_swapped)
        {
            break;
        }
    }

}

int main()
{
    Student student[3] = {
        {"张三", 18, 76.5},
        {"李四", 19, 95.5},
        {"王五", 20, 88.0}
    };
    sort_by_score(student,3);
    for(int i=0;i<3;++i)
    {
        printf("%s %d %g\n",student[i].name,student[i].age,student[i].score);
    }
    return 0;
}