#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

TreeNode *insert(TreeNode *root,int val)
{
    if(root == NULL)
    {
    TreeNode *new_load = (TreeNode*)malloc(sizeof(TreeNode));
    if(new_load == NULL)
    {
        perror("malloc");
        return NULL;
    }
    new_load->data = val;
    new_load->left = NULL;
    new_load->right = NULL;
    return new_load;
    }
    if(val < root->data)
    {
        root->left = insert(root->left,val);
    }
    else if(val > root->data)
    {
        root->right = insert(root->right,val);
    }
    return root;
}

void preorder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

void postorder(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}

void freeTree(TreeNode *root) {
    if (root == NULL) return; // 到底了，直接返回
    
    freeTree(root->left);     // 1. 先去把左子树全释放了
    freeTree(root->right);    // 2. 再去把右子树全释放了
    free(root);               // 3. 最后释放自己（根节点）
}

TreeNode *search(TreeNode *root,int target)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->data == target)
    {
        return root;
    }
    else
    {
        if(target < root->data)
        {
            return search(root->left,target);
        }
        if(target > root->data)
        {
            return search(root->right,target);
        }
    }
    return NULL;
}

TreeNode *delete_node(TreeNode *root,int key)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(key < root->data)
    {
        root->left = delete_node(root->left,key);
    }
    else if (key > root->data)
    {
        root->right = delete_node(root->right,key);
    }
    else
    {
        if(root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        TreeNode *successor = root->right;
        while(successor->left != NULL)
        {
            successor = successor->left;
        }
        root->data = successor->data;
        root->right = delete_node(root->right,successor->data);
    }
    return root;
}

int main() {
    TreeNode *root = NULL;
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        root = insert(root, arr[i]);
    }

    printf("原始中序遍历: ");
    inorder(root);
    printf("\n\n");

    // 1. 测试删除叶子节点 (20)
    printf("删除叶子节点 20...\n");
    root = delete_node(root, 20);
    printf("删除后中序遍历: ");
    inorder(root);
    printf("\n\n");

    // 2. 测试删除单分支节点 (70 只有右儿子 80)
    printf("删除单分支节点 70...\n");
    root = delete_node(root, 70);
    printf("删除后中序遍历: ");
    inorder(root);
    printf("\n\n");

    // 3. 测试删除双分支节点 (50 有两儿子)
    printf("删除双分支节点 50...\n");
    root = delete_node(root, 50);
    printf("删除后中序遍历: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}