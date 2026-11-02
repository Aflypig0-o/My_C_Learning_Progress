#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

TreeNode *insert(TreeNode *root,int val)
{
    if(root == NULL)
    {
        TreeNode *new_node = (TreeNode*)malloc(sizeof(TreeNode));
        if(new_node == NULL)
        {
            perror("malloc");
            return NULL;
        }
        new_node->data = val;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
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

void level_order(TreeNode *root)
{
    
}