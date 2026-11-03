#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "queue.h"

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
    if(root == NULL)
    {
        return;
    }
    Queue *q = queue_create(100);
    q->enqueue(q,root);
    while(!q->is_empty(q))
    {
        TreeNode *current = q->dequeue(q);
        printf("%d ",current->data);
        if(current->left != NULL)
        {
            q->enqueue(q,current->left);
        }
        if(current->right != NULL)
        {
            q->enqueue(q,current->right);
        }
    }
    printf("\n");
    q->destroy(q);
}

void free_tree(TreeNode *root)
{
    if(root == NULL)
    {
        return;
    }
    free(root->left);
    free(root->right);
    free(root);
}