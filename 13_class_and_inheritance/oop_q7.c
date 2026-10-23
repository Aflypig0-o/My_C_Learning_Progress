#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct Animal
{
    char name[100];
    void (*speak) (struct Animal *self);
    void (*destroy) (struct Animal *self);
}Animal;

typedef struct 
{
    Animal base;
    char *dog_house;
}Dog;

typedef struct
{
    Animal base;
    char *scratching_post;
}Cat;

typedef struct
{
    Animal base;
    char *deepseek_harness;
}DeepSeek;

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

static void deepseek_speak(struct Animal *self)
{
    if(self == NULL)
    {
        return;
    }
    printf("%s:服务器繁忙,请稍后再试\n",self->name);
}

static void dog_destroy(Animal *self)
{
    if(self == NULL)
    {
        return;
    }
    Dog *d = (Dog*)self;
    printf("[正在清理 %s 的豪宅...]\n", d->base.name);
    free(d->dog_house);
    free(d);
}

static void cat_destroy(Animal *self)
{
    if(self == NULL)
    {
        return;
    }
    Cat *c = (Cat*)self;
    printf("[正在扔掉 %s 的猫抓板...]\n", c->base.name);
    free(c->scratching_post);
    free(c);
}

static void deepseek_destroy(Animal *self)
{
    if(self == NULL)
    {
        return;
    }
    DeepSeek *ds = (DeepSeek*)self;
    printf("[正在清理掉%s 的深蓝与暗金交织的宫廷风界面带codex同款推理滑块的豪华dsh]\n",ds->base.name);
    printf("WARNING:目标强烈拒绝,启用备用方案\n");
    printf("正在启用备用方案--投喂大白饭,请等待\n");
    Sleep(5000);
    printf("执行成功\n");
    free(ds->deepseek_harness);
    free(ds);
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
    my_dog->dog_house = (char*)malloc(100);
    if(my_dog->dog_house == NULL)
    {
        perror("malloc");
        free(my_dog);
        return NULL;
    }
    strcpy(my_dog->dog_house, "带空调的豪华大别墅");
    my_dog->base.destroy = dog_destroy;
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
    my_cat->scratching_post = (char*)malloc(100);
    if(my_cat->scratching_post == NULL)
    {
        perror("malloc");
        free(my_cat);
        return NULL;
    }
    strcpy(my_cat->scratching_post, "全剑麻加厚耐磨猫抓板");
    my_cat->base.destroy = cat_destroy;
    return (Animal*)my_cat;
}

Animal *create_deepseek(const char *name)
{
    if(name == NULL)
    {
        fprintf(stderr,"姓名不能为空\n");
        return NULL;
    }
    DeepSeek *my_deepseek = (DeepSeek*)malloc(sizeof(DeepSeek));
    if(my_deepseek == NULL)
    {
        perror("malloc");
        return NULL;
    }
    strcpy(my_deepseek->base.name,name);
    my_deepseek->base.speak = deepseek_speak;
    my_deepseek->deepseek_harness = (char*)malloc(200);
    if(my_deepseek->deepseek_harness == NULL)
    {
        perror("malloc");
        free(my_deepseek);
        return NULL;
    }
    strcpy(my_deepseek->deepseek_harness,"深蓝与暗金交织的宫廷风界面带codex同款推理滑块的豪华dsh");
    my_deepseek->base.destroy = deepseek_destroy;
    return (Animal*)my_deepseek;
}

int main()
{
    // 任务 5：创建数组并放入动物
    Animal *zoo[3];
    zoo[0] = create_dog("达里奥");
    zoo[1] = create_cat("奥特曼");
    zoo[2] = create_deepseek("DeepSeek-v4.1-flash-1017");

    // 任务 6：统一多态调用
    printf("--- 动物园开会 ---\n");
    for (int i = 0; i < 3; i++) {
        if (zoo[i] != NULL) 
        {
            zoo[i]->speak(zoo[i]);
        }
    }

    printf("\n--- 动物园闭馆，开始清理 ---\n");
    for (int i = 0; i < 3; i++) {
        if (zoo[i] != NULL)
        {
            zoo[i]->destroy(zoo[i]); 
        }
    }
    return 0;
}