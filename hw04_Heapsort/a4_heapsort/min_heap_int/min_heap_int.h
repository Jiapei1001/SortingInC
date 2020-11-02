//
// Created by Jiapei Li on 7/30/20.
//

#ifndef HW04_HEAPSORT_MIN_HEAP_INT_H
#define HW04_HEAPSORT_MIN_HEAP_INT_H

#define HEAP_SIZE 40
#define TWO_DIVIDE 2


typedef struct {
    int tree[HEAP_SIZE + 1];
    int num_elems;
} Heap;

Heap* CreateHeap(int* data, int num_elems);

void Insert(Heap* heap, int val);

int ExtractMin(Heap* heap);

int Delete(Heap* heap, int position);

void BubbleUp(Heap* heap, int index);

void BubbleDown(Heap* heap, int index);

void Swap(Heap* heap, int first_ind, int second_ind);

void DestroyHeap(Heap* heap);

void PrintArray(int* array, int num_elems);

void Heapify(Heap* heap, int index);

void Heapsort(int* data, int num_elems);


#endif  // HW04_HEAPSORT_MIN_HEAP_INT_H
