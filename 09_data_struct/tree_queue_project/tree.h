#ifndef TREE_H
#define TREE_H

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

TreeNode *insert(TreeNode *root,int val);
void level_order(TreeNode *root);
void free_tree(TreeNode *root);

#endif