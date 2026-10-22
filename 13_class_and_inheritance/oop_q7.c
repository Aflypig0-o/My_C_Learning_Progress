#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Animal
{
    char name[100];
    void (*speak) (struct Animal *self);
}Animal;

typedef struct 
{
    Animal base;
}Dog;

typedef struct
{
    Animal base;
}Cat;

static void dog_speak(struct Animal *self)
{
    if(self == NULL)
    {
        return;
    }
    printf("%s:嗷~~呜\n",self->name);
}

static void cat_speak(struct Animal *self)
{
    if(self == NULL)
    {
        return;
    }
    printf("%s:吼~\n",self->name);
}

Animal *create_dog(const char *name)
{
    if(name == NULL)
    {
        fprintf(stderr,"姓名不能为空\n");
        return NULL;
    }
    Dog *my_dog = (Dog*)malloc(sizeof(Dog));
    if(my_dog == NULL)
    {
        perror("malloc");
        return NULL;
    }
    strcpy(my_dog->base.name,name);
    my_dog->base.speak = dog_speak;
    return (Animal*)my_dog;
}

Animal *create_cat(const char *name)
{
    if(name == NULL)
    {
        fprintf(stderr,"姓名不能为空\n");
        return NULL;
    }
    Cat *my_cat = (Cat*)malloc(sizeof(Cat));
    if(my_cat == NULL)
    {
        perror("malloc");
        return NULL;
    }
    strcpy(my_cat->base.name,name);
    my_cat->base.speak = cat_speak;
    return (Animal*)my_cat;
}

int main()
{
    // 任务 5：创建数组并放入动物
    Animal *zoo[2];
    zoo[0] = create_dog("达里奥");
    zoo[1] = create_cat("奥特曼");

    // 任务 6：统一多态调用
    printf("--- 动物园开会 ---\n");
    for (int i = 0; i < 2; i++) {
        if (zoo[i] != NULL) 
        {
            zoo[i]->speak(zoo[i]);
        }
    }

    // 释放内存
    free(zoo[0]);
    free(zoo[1]);

    return 0;
}