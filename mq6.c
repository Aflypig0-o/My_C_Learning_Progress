/**
 * mq5.c - 用递归计算 n 阶行列式
 * 
 * 数学原理：按第一行展开
 *   D = Σ(j=0 to n-1) (-1)^j * a[0][j] * M[0][j]
 * 
 * 其中 M[0][j] 是去掉第0行第j列后的余子式
 * 
 * 递归思路：
 *   - 1阶：直接返回 a[0][0]
 *   - 2阶：用对角线法则直接算
 *   - n阶：拆成n个(n-1)阶，递归调用
 */

#include <stdio.h>
#define MAX 10   // 最大支持10阶

/**
 * 计算n阶行列式
 * @param d  二维数组，存储矩阵
 * @param n  当前矩阵的阶数
 * @return   行列式的值
 */
double calc_det(double d[MAX][MAX], int n)
{
    double sum = 0;

    // ========== 递归终止条件 ==========
    // 1阶行列式就是它本身
    if (n == 1)
    {
        return d[0][0];
    }
    // 2阶行列式用对角线法则直接算，避免不必要的递归
    if (n == 2)
    {
        return d[0][0] * d[1][1] - d[0][1] * d[1][0];
    }

    // ========== 递归：按第一行展开 ==========
    // 遍历第一行的每个元素
    for (int j = 0; j < n; ++j)
    {
        // ----- 第1步：构建余子式 d_m -----
        // 去掉第0行和第j列后，剩下的(n-1)x(n-1)矩阵
        double d_m[MAX][MAX] = {0};
        int row = 0;   // d_m的行下标，独立于原矩阵的行
        for (int i = 1; i < n; ++i)   // 从第1行开始（跳过第0行）
        {
            int col = 0;   // d_m的列下标，独立于原矩阵的列
            for (int k = 0; k < n; ++k)   // 遍历原矩阵的所有列
            {
                if (j == k)   // 跳过第j列
                {
                    continue;
                }
                d_m[row][col] = d[i][k];   // 把元素复制到余子式矩阵
                ++col;
            }
            ++row;
        }

        // ----- 第2步：计算符号 -----
        // 符号是 (-1)^(0+j)，因为C语言下标从0开始
        // j为偶数时为正，j为奇数时为负
        double sign;
        if (j % 2 == 0)
        {
            sign = 1;
        }
        else
        {
            sign = -1;
        }

        // ----- 第3步：递归累加 -----
        // 当前项 = 符号 * 第一行第j列元素 * 余子式的行列式值
        sum += sign * d[0][j] * calc_det(d_m, n - 1);
    }

    return sum;
}

int main()
{
    double det[MAX][MAX] = {0};
    int n;

    printf("请输入行列式的阶数n (n<=10): ");
    scanf("%d", &n);

    printf("请输入 %d x %d 矩阵：\n", n, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%lf", &det[i][j]);
        }
    }

    double result = calc_det(det, n);
    printf("行列式的值为：%g\n", result);

    return 0;
}