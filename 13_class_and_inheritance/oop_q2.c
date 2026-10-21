#include <stdio.h>
#include <stdlib.h>

typedef struct Account
{
    int balance;
    void (*deposit)(struct Account *self, int amount);
    void (*withdraw)(struct Account *self, int amount);
    int (*get_balance)(struct Account *self);
}Account;

static void deposit_impl(struct Account *self,int amount)
{
    self->balance += amount;
}

static void withdraw_impl(struct Account *self,int amount)
{
    if(amount > self->balance)
    {
        printf("余额不足\n");
        return;
    }
    else
    {
        self->balance -= amount;
    }
}

static int get_balance_impl(struct Account *self)
{
    return self->balance;
}
Account *account_create(int initial)
{
    if(initial < 0 )
    {
        fprintf(stderr,"不合理的初始值，请重试\n");
        return NULL;
    }
    Account *acc = (Account*)malloc(sizeof(Account));
    if(acc == NULL)
    {
        perror("malloc");
        return NULL;
    }
    acc->balance = initial;
    acc->deposit = deposit_impl;
    acc->withdraw = withdraw_impl;
    acc->get_balance = get_balance_impl;
    return acc;
}

int main()
{
    Account *acc = account_create(100);
    acc->deposit(acc, 50);
    printf("存款后余额: %d\n", acc->get_balance(acc)); // 预期 150

    acc->withdraw(acc, 200); // 预期：触发“余额不足”
    printf("取款失败后余额: %d\n", acc->get_balance(acc)); // 预期 150

    acc->withdraw(acc, 80);
    printf("取款后余额: %d\n", acc->get_balance(acc)); // 预期 70

    free(acc);
    return 0;
}