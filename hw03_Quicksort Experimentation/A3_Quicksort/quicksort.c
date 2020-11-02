//
// Created by Jiapei Li on 7/23/20.
//

#include "quicksort.h"

// Creat QuickSort partition, with pivot location as the leftmost element
// Return the location of the pivot,
// after its left side elements are <= pivot value,
// and its right side elements are >= pivot value
int Partition(int *data, int low, int high) {
    int pivot = data[low];
    int leftwall = low;
    int i;
    for (i = low + 1; i <= high; i++) {
        if (data[i] < pivot) {
            leftwall++;
            Swap(data, i, leftwall);
        }
    }
    Swap(data, low, leftwall);
    return leftwall;
}

// Recursive QuickSort
void Quicksort(int *data, int low, int high) {
    if (low < high) {
        int pivot_location = Partition(data, low, high);
        Quicksort(data, low, pivot_location);
        Quicksort(data, pivot_location + 1, high);
    }
}
