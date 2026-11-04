#include <stdio.h>
#include "heap.h"

int main() {
    // 我们故意初始容量只给 2
    heap *h = heap_create(2); 
    
    // 插入 6 个数字，必定触发多次 realloc
    int arr[] = {3, 10, 5, 8, 1, 9};
    for (int i = 0; i < 6; i++) {
        h->push(h, arr[i]);
    }

    printf("依次弹出最大值: ");
    while (!h->is_empty(h)) {
        printf("%d ", h->pop(h));
    }
    printf("\n");

    h->destroy(h);
    return 0;
}