//
// Created by Jiapei Li on 7/24/20.
//
#include <stdbool.h>

#include "quicksort.h"

// Insertion Sort
// When size of array is < 10
void Insertion_Sort(int *array, int low, int n) {
  int i;
    for (i = low + 1; i < n + 1; i++) {
        int val = array[i];
        int j = i;
        while (j > low && array[j - 1] > val) {
            array[j] = array[j - 1];
            j -= 1;
        }
        array[j] = val;
    }
}

// Hybrid function -> Quick + Insertion sort
// Recursive QuickSort for implementing hybrid QuickSort and Insertion Sort
// Calling Insertion Sort when the size of the array is < 10
// Otherwise utilize typical QuickSort method
void Quicksort_Hybrid(int *data, int low, int high) {
    if (low < high) {
        if (high - low + 1 < HYBRID_CUTOFF) {
            Insertion_Sort(data, low, high);
        } else {
            int pivot_location = Partition_Median(data, low, high);
            Quicksort_Hybrid(data, low, pivot_location);
            Quicksort_Hybrid(data, pivot_location + 1, high);
        }
    }
}
