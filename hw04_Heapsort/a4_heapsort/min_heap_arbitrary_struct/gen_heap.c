#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "gen_heap.h"
#include "int_helpers.h"

// returns an empty heap H that is set up to store at most n elements.
Heap *CreateHeap(void **data, int num_elems, int (*compare)(void *, void *)) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->num_elems = 0;
    heap->compare = (*compare);

    int i;

    for (i = 0; i < PQ_SIZE + 1; i++) {
      void *a;
      a = NULL;
      heap->data[i] = a;
    }

    for (i = 0; i < num_elems; i++) {
        Insert(heap, data[i]);
    }

    return heap;
}

// frees all resources associated with heap heap.
void DestroyHeap(Heap *heap) {
    free(heap);
}

// get the parent index of a node
int ParentIndex(int child_index) {
    if (child_index == 1)
        return (-1);
    else
        return ((int) child_index / 2);
}

// get the left side child index of a node
int YoungChildIndex(int parent_index) {
    return (2 * parent_index);
}

// inserts the int val into heap heap.
void Insert(Heap *heap, void *new_data_val) {
    heap->num_elems++;
    heap->data[heap->num_elems] = new_data_val;
    BubbleUp(heap, heap->num_elems);
}

// swap two nodes at two indexes.
void Swap(Heap *heap, int child_index, int parent_index) {
    void *temp = heap->data[child_index];
    heap->data[child_index] = heap->data[parent_index];
    heap->data[parent_index] = temp;
}

// bubbles the element at location index up to its correct position.
void BubbleUp(Heap *heap, int index) {
    if (index == 0) return;
    int parent_id = ParentIndex(index);

    if (parent_id == -1) {
        return;
    }
    if (heap->compare(heap->data[parent_id], heap->data[index]) > 0) {
        Swap(heap, parent_id, index);
        BubbleUp(heap, parent_id);
    }
}

// identifies and deletes an element with minimum value from a heap.
void *ExtractMin(Heap *heap) {
    void *lastElement = heap->data[heap->num_elems];
    void *returnElement = heap->data[1];

    heap->data[1] = lastElement;
    int *a;
    *a = DEFAULT_OBJ;
    heap->data[heap->num_elems] = a;
    heap->num_elems--;

    BubbleDown(heap, 1);
    return returnElement;
}

// bubbles the element at location index down to its correct position.
void BubbleDown(Heap *heap, int index) {
    if (index == 0) return;

    int low_pri_index;
    int left_child = YoungChildIndex(index);
    int right_child = left_child + 1;

    if (left_child <= heap->num_elems) {
        if (right_child <= heap->num_elems) {
            if (heap->compare(heap->data[left_child],
                              heap->data[right_child]) < 0) {
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
    if (heap->compare(heap->data[low_pri_index], heap->data[index]) < 0) {
        Swap(heap, low_pri_index, index);
        BubbleDown(heap, low_pri_index);
    }
}
