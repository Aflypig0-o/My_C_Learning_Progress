#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[100];
    int legs;
}Animal;

typedef struct 
{
    Animal base;
    char bread[20];
}Dog;


void print_animal(Animal *a)
{
    if(a == NULL)
    {
        return;
    }
    printf("名字: %s, 腿数: %d\n", a->name, a->legs);
}

int main()
{
    Dog my_dog;
    strcpy(my_dog.base.name,"达里奥");
    my_dog.base.legs = 32767;//嘻嘻
    print_animal((Animal*)(&my_dog));
    return 0;
}