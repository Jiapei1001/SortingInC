//
// Created by Jiapei Li on 7/30/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "min_heap_int.h"

#define RAND_NUM 20
#define RAND_MOD 90


int main() {
    int num_elems = HEAP_SIZE;
    int* integers = (int*)malloc(sizeof(int) * num_elems);

    time_t t;
    srand(RAND_NUM);  // (unsigned)time(&t));

    int i;
    for (i = 0; i < num_elems; i++) {
        integers[i] = (rand() % RAND_MOD) + HEAP_SIZE;
    }

    printf("\n\n");
//    printf("Check delete:\n");
    PrintArray(integers, num_elems);
//    Heap* heap = CreateHeap(integers, num_elems);
//    Delete(heap, 1);
//    DestroyHeap(heap);

    Heapsort(integers, num_elems);
    printf("\n\n");
    printf("Check heap sort:\n");
    printf("min_heap for descending order:\n\n");
    PrintArray(integers, num_elems);
    printf("\n");

    free(integers);
}
