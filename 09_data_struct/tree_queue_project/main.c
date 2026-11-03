#include <stdio.h>
#include "tree.h"

int main() {
    // 1. 初始化根节点为空
    TreeNode *root = NULL;
    
    // 2. 准备一组测试数据
    // 树的形状：
    //         50
    //       /    \ 
    //     30      70
    //    /  \    /  \ 
    //  20   40  60  80
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("开始建树...\n");
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
    }

    // 3. 层序遍历大显神威
    printf("\n层序遍历（一层一层剥洋葱）结果: \n");
    level_order(root); // 确保 tree.h 和 tree.c 里用的是这个名字
    printf("\n");

    // 4. 安全释放所有内存
    printf("\n正在销毁整棵树...\n");
    free_tree(root);   // 确保 tree.h 和 tree.c 里用的是这个名字
    printf("销毁完成，内存已释放。\n");

    return 0;
}