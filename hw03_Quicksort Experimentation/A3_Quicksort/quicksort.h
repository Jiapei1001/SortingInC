//
// Created by Jiapei Li on 7/24/20.
//

#ifndef A3_QUICKSORT_EXPERIMENTATION_QUICKSORT_H
#define A3_QUICKSORT_EXPERIMENTATION_QUICKSORT_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define SORT_CYCLES 18 // number of sizes for comparing different sorting methods
#define HYBRID_CUTOFF 10 // cutoff size of number of elements to be sorted by selection sort
#define SHUFFLE_SEED 84 // shuffle seed
#define HALF 2
#define NUM_GENERATING_BASE 2 // for auto-generating different sizes of the array
#define NUM_GENERATING_ADDITION 4 // for linking sizes of the array with the iteration of the cycles


//----------------------------------------
// QuickSort leftmost functions
//----------------------------------------

// Creat QuickSort partition, with pivot location as the leftmost element
// Return the location of the pivot,
// after its left side elements are <= pivot value,
// and its right side elements are >= pivot value
int Partition(int *data, int low, int high);

// Recursive QuickSort
void Quicksort(int *data, int low, int high);

//----------------------------------------
// QuickSort midpoint functions
//----------------------------------------

// Creat QuickSort partition, with pivot location as the middle index element
// Return the location of the pivot,
// after its left side elements are <= pivot value,
// and its right side elements are >= pivot value
int Partition_Median(int *data, int low, int high);

// Recursive QuickSort for implementing middle index partition
void Quicksort_Median(int *data, int low, int high);

//----------------------------------------
// QuickSort hybrid functions
//----------------------------------------

// Create Insertion Sort
// When size of array is < 10
void Insertion_Sort(int *array, int low, int n);

// Recursive QuickSort for implementing hybrid QuickSort and Insertion Sort
// Calling Insertion Sort when the size of the array is < 10
// Otherwise utilize typical QuickSort method
void Quicksort_Hybrid(int *data, int low, int high);

//----------------------------------------
// QuickSort helper functions
//----------------------------------------

// Shuffle the elements in the array after generating the random elements in the array
void Shuffle(int *array, int num_elems);

// Swap the values of two different indexes in the array
void Swap(int *array, int ind1, int ind2);

// Copy all elements in the array to the same index in another array
// The two arrays' sizes are the same.
int *CopyArray(int *old_array, int *new_array, int num_elems);

// Check if the array is sorted or not
int CheckArray(int *array, int num_elems);

// Check if the array is copied correctly or not
bool CheckCopyArray(int *old_array, int *new_array, int num_elems);

// Print elements in the array
void PrintArray(int *array, int num_elems);

// Generate reports of the result of the comparisons between different sorting methods
void PrintResults(bool alg_a, bool alg_b, bool alg_c, bool alg_d, int64_t *runningTimes_a,
                  int64_t *runningTimes_b, int64_t *runningTimes_c);

#endif //A3_QUICKSORT_EXPERIMENTATION_QUICKSORT_H
