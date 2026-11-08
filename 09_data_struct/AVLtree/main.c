#include <stdio.h>
#include "AVLtree.h"

int main()
{
    AVLNode *root = build_demo();
    root->dump(root);
    root->destroy(root);
    return 0;
}