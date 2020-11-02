#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "gen_heap.h"
#include "gen_heapsort.h"
#include "int_helpers.h"

// swap the first node (the min node)
// with the node at the end of the array
// recursive call to change the swapped first node
// to the correct position in the min heap.
void LoopHeapSort(Heap *heap) {
    int i = 0;
    for (i = heap->num_elems; i > 1; i--) {
        Swap(heap, 1, i);
        heap->num_elems--;
        BubbleDown(heap, 1);  // Similar to Heapify method.
    }
}

// after the nodes on the min heap are sorted,
// assign the correct order to the original array.
void Change(Heap *heap, void** data, int num_elems) {
    int i;
    for (i = 0; i < num_elems; i++) {
        data[i] = heap->data[i + 1];
    }
}

// Heap sort a min heap in a descending order.
void HeapSort(void **data, int num_elems, int (*Compare)(void *, void *)) {
    Heap *heap = CreateHeap(data, num_elems, *Compare);
    LoopHeapSort(heap);
    Change(heap, (void **)data, num_elems);
    DestroyHeap(heap);
}
