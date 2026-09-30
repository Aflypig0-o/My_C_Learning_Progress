#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

int main()
{
    Node *A =(Node*)malloc(sizeof(Node));
    Node *B =(Node*)malloc(sizeof(Node));
    Node *C =(Node*)malloc(sizeof(Node));
    A->next = B;
    B->next = C;
    C->next = NULL;
    A->data = 100;
    B->data = 200;
    C->data = 300;
    Node *p = A;
    while(p != NULL)
    {
        printf("%d -> ",p->data);
        p = p->next;
    }
    printf("NULL");
    free(A);
    free(B);
    free(C);
    A = NULL;
    B = NULL;
    C = NULL;
    return 0;
}