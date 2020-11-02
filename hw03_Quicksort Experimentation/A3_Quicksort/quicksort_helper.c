//
// Created by Jiapei Li on 7/24/20.
//

#include "quicksort.h"

// Shuffle the elements in the array
// after generating the random elements in the array
void Shuffle(int *array, int num_elems) {
    srand(SHUFFLE_SEED);
    int i;
    for (i = 0; i < num_elems; i++) {
        int randIndex = rand() % num_elems;
        Swap(array, i, randIndex);
    }
}

// Swap the values of two different indexes in the array
void Swap(int *array, int ind1, int ind2) {
    int tmp = array[ind1];
    array[ind1] = array[ind2];
    array[ind2] = tmp;
}

// Copy all elements in the array to the same index in another array
// The two arrays' sizes are the same.
int *CopyArray(int *old_array, int *new_array, int num_elems) {
    int i;
    for (i = 0; i < num_elems; i++) {
        new_array[i] = old_array[i];
    }
    return new_array;
}

// Check if the array is sorted or not
int CheckArray(int *array, int num_elems) {
    int i;
    for (i = 1; i < num_elems; i++) {
        if (array[i] < array[i - 1]) {
            printf("NOT SORTED!!!\n");
            return 0;
        }
    }
    printf("SORTED!!\n");
    return 1;
}

// Check if the array is copied correctly or not
bool CheckCopyArray(int *old_array, int *new_array, int num_elems) {
    int i;
    bool check = true;
    for (i = 0; i < num_elems; i++) {
        if (old_array[i] != new_array[i]) {
            check = false;
        }
    }
    return check;
}

// Print elements in the array
void PrintArray(int *array, int num_elems) {
    int i;
    printf("[");
    for (i = 0; i < num_elems; i++) {
        printf("%d ", array[i]);
    }
    printf("]\n");
}

// Generate reports of the result of the comparisons
// between different sorting methods
void PrintResults(bool alg_a, bool alg_b,
        bool alg_c, bool alg_d,
        int64_t *runningTimes_a,
        int64_t *runningTimes_b,
        int64_t *runningTimes_c) {
    int i;
    int num_elems;
    // print header
    printf("\nNote: sorting time periods are counted in milliseconds.\n\n");

    printf("Sort size:");
    for (i = 0; i < SORT_CYCLES; i++) {
        num_elems = (int) pow(2, (i + 4));
        printf("%7d;", num_elems);
    }
    printf("\n");
    for (i = 0; i < SORT_CYCLES * 2; i++) {
        printf("----");
    }
    printf("----------");
    printf("\n");

    // Algo A condition
    if (alg_a) {
        printf("Algo A:   ");
        for (i = 0; i < SORT_CYCLES; i++) {
            printf("%7llu;", runningTimes_a[i]);
        }
        printf("\n");
    }
    // Algo B condition
    if (alg_b) {
        printf("Algo B:   ");
        for (i = 0; i < SORT_CYCLES; i++) {
            printf("%7llu;\t", runningTimes_b[i]);
        }
        printf("\n");
    }
    // Algo C condition
    if (alg_c) {
        printf("Algo C:   ");
        for (i = 0; i < SORT_CYCLES; i++) {
            printf("%7llu;\t", runningTimes_c[i]);
        }
        printf("\n");
    }
    // Combined conditions
    if (alg_d) {
        printf("Algo A:   ");
        for (i = 0; i < SORT_CYCLES; i++) {
            printf("%7llu;", runningTimes_a[i]);
        }
        printf("\n");

        printf("Algo B:   ");
        for (i = 0; i < SORT_CYCLES; i++) {
            printf("%7llu;", runningTimes_b[i]);
        }
        printf("\n");

        printf("Algo C:   ");
        for (i = 0; i < SORT_CYCLES; i++) {
            printf("%7llu;", runningTimes_c[i]);
        }
        printf("\n");
    }
    printf("\n");
}
