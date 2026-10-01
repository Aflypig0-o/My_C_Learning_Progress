#include <stdio.h>

void update_score(int *current_score)
{
    
    static int score = 0;
    if (*current_score > score )
    {
        score = *current_score;
    }
    printf("最大得分为%d",score);
}

int main()
{   
    int current_score = 85;
    update_score(&current_score);
    current_score = 120;
    update_score(&current_score);
    current_score = 95;
    update_score(&current_score);
    return 0;
}