//
// Created by Jiapei Li on 7/24/20.
//

#include "quicksort.h"

// Creat QuickSort partition, with pivot location as the middle index element
// Return the location of the pivot,
// after its left side elements are <= pivot value,
// and its right side elements are >= pivot value
int Partition_Median(int *data, int low, int high) {
    int midpoint = low + (high - low) / HALF;
    int pivot = data[midpoint];

    int l = low;
    int h = high;

    int done = false;

    while (!done) {
        while (data[l] < pivot) {
            ++l;
        }
        while (pivot < data[h]) {
            --h;
        }

        if (l >= h) {
            done = true;
        } else {
            // Swap
            int temp = data[l];
            data[l] = data[h];
            data[h] = temp;
            ++l;
            --h;
        }
    }
    return h;
}

// Recursive QuickSort for implementing middle index partition
void Quicksort_Median(int *data, int low, int high) {
    if (low < high) {
        int pivot_location = Partition_Median(data, low, high);
        Quicksort_Median(data, low, pivot_location);
        Quicksort_Median(data, pivot_location + 1, high);
    }
}
