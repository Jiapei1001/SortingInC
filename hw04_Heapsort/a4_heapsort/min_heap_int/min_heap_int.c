#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "min_heap_int.h"

Heap* CreateHeap(int* data, int num_elems) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->num_elems = 0;
    int i;
    for (i = 0; i < num_elems; i++) {
        heap->tree[i] = 0;
    }
    for (i = 0; i < num_elems; i++) {
        Insert(heap, data[i]);
    }
    return heap;
}

void Insert(Heap* heap, int val) {
    heap->num_elems++;
    heap->tree[heap->num_elems] = val;

    BubbleUp(heap, heap->num_elems);
}

int ExtractMin(Heap* heap) {
    int val = heap->tree[1];
    heap->tree[1] = heap->tree[heap->num_elems];
    BubbleDown(heap, 1);
    return val;
}

int Delete(Heap* heap, int position) {
    int lastElement = heap->tree[heap->num_elems];
    int returnElement = heap->tree[position];

    heap->tree[position] = lastElement;
    heap->tree[heap->num_elems] = 0;
    heap->num_elems--;

    Heapify(heap, position);

    return returnElement;
}

void BubbleUp(Heap* heap, int index) {
    if (index == 0) return;
    int parent_id = index / TWO_DIVIDE;

    if (heap->tree[parent_id] > heap->tree[index]) {
        Swap(heap, parent_id, index);
        BubbleUp(heap, parent_id);
    }
}

void BubbleDown(Heap* heap, int index) {
    if (index == 0) return;

    int low_pri_index;
    int left_child = index * 2;
    int right_child = left_child + 1;

    if (left_child <= heap->num_elems) {
        if (right_child <= heap->num_elems) {
            if (heap->tree[left_child] < heap->tree[right_child]) {
                low_pri_index = left_child;
            } else {
                low_pri_index = right_child;
            }
        } else {
            low_pri_index = left_child;
        }
    } else {
        return;  // No children
    }

    // compare children with parent
    if (heap->tree[low_pri_index] < heap->tree[index]) {
        Swap(heap, low_pri_index, index);
        BubbleDown(heap, low_pri_index);
    }
}

void Swap(Heap* heap, int first_ind, int second_ind) {
    int temp = heap->tree[first_ind];
    heap->tree[first_ind] = heap->tree[second_ind];
    heap->tree[second_ind] = temp;
}

void DestroyHeap(Heap* heap) {
    free(heap);
}

void Heapify(Heap* heap, int index) {
    int left = index * 2;
    int right = left + 1;
    int smallest;

    if (left <= heap->num_elems && heap->tree[left] < heap->tree[index]) {
        smallest = left;
    } else {
        smallest = index;
    }

    if (right <= heap->num_elems && heap->tree[right] < heap->tree[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        Swap(heap, index, smallest);
        PrintArray(heap->tree, HEAP_SIZE);
        Heapify(heap, smallest);
    }
}

void Heapsort(int* data, int num_elems) {
    Heap* heap = CreateHeap(data, num_elems);
    PrintArray(heap->tree, HEAP_SIZE);

    int i;
    for (i = heap->num_elems; i > 1; i--) {
        Swap(heap, 1, i);
        heap->num_elems--;
//        Heapify(heap, 1);  // Heapify method is similar to BubbleDown, either way works.
        BubbleDown(heap, 1);  // Similar to Heapify method.
    }

    for (i = 1; i <= num_elems; i++) {
        printf("copying %d into index %d\n", heap->tree[i], i-1);
        data[i-1] = heap->tree[i];
    }

    DestroyHeap(heap);
}


void PrintArray(int* array, int num_elems) {
    int i;
    printf("[");
    for (i = 0; i < num_elems; i++) {
        printf("%d ", array[i]);
    }
    printf("]\n");
}
