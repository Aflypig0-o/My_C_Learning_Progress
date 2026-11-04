#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"

int main(void) {
    srand((unsigned)time(NULL));
    int trials = 2000;
    for (int t = 0; t < trials; t++) {
        heap *h = heap_create(1 + rand() % 5);
        int n = 1 + rand() % 100;
        int *in = malloc(sizeof(int) * n);
        int *out = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) { in[i] = rand() % 1000 - 500; h->push(h, in[i]); }
        for (int i = 0; i < n; i++) out[i] = h->pop(h);
        h->destroy(h);

        // brute-force sort descending
        for (int a = 0; a < n; a++)
            for (int b = a + 1; b < n; b++)
                if (in[b] > in[a]) { int tmp = in[a]; in[a] = in[b]; in[b] = tmp; }
        for (int i = 0; i < n; i++) {
            if (in[i] != out[i]) {
                printf("MISMATCH trial %d at %d: expected %d got %d\n", t, i, in[i], out[i]);
                return 1;
            }
        }
        free(in); free(out);
    }
    printf("all %d random trials match descending order\n", trials);
    return 0;
}
