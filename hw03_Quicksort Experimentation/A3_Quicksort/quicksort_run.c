//
// Created by Jiapei Li on 7/23/20.
//
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>
#include "quicksort.h"

struct timeval stop, start;

// Algorithm A: QuickSort partition, with pivot location as the leftmost element
void RunAlgoA(int sort_cycle, int *integers, int num_elems,
              int64_t *runningTimes_a) {
    gettimeofday(&start, NULL);
    // Algorithm A: QuickSort call
    Quicksort(integers, 0, num_elems - 1);
    gettimeofday(&stop, NULL);
    runningTimes_a[sort_cycle] =
            (stop.tv_sec - start.tv_sec) * 1000000
            + stop.tv_usec - start.tv_usec;
//    CheckArray(integers, num_elems);
}

// Algorithm B: QuickSort partition, with pivot location as the median element
void RunAlgoB(int sort_cycle, int *integers,
        int num_elems, int64_t *runningTimes_b) {
    gettimeofday(&start, NULL);
    // Algorithm B: QuickSort call
    Quicksort_Median(integers, 0, num_elems - 1);
    gettimeofday(&stop, NULL);
    runningTimes_b[sort_cycle] =
            (stop.tv_sec - start.tv_sec) * 1000000
            + stop.tv_usec - start.tv_usec;
//    CheckArray(integers, num_elems);
}

// Algorithm C: QuickSort partition,
// with the hybrid of both QuickSort and Insertion Sort
void RunAlgoC(int sort_cycle, int *integers,
        int num_elems, int64_t *runningTimes_c) {
    gettimeofday(&start, NULL);
    // Algorithm C: Hybrid of QuickSort and Insertion Sort call
    Quicksort_Hybrid(integers, 0, num_elems - 1);
    gettimeofday(&stop, NULL);
    runningTimes_c[sort_cycle] =
            (stop.tv_sec - start.tv_sec) * 1000000
            + stop.tv_usec - start.tv_usec;
//    CheckArray(integers, num_elems);
}


// Sorting Controller to check which specific
// or combined sorting algorithms to be proceeded with
// Getting different sizes of random numbers in the arrays for sorting
// Copying array with random numbers to other arrays for sorting comparisons
// Calling specific sorting algorithm
// Free the declared pointer memories
void SortController(int sort_cycle,
        bool alg_a, bool alg_b, bool alg_c, bool alg_d,
        int64_t *runningTimes_a,
        int64_t *runningTimes_b,
        int64_t *runningTimes_c) {
    int num_elems = (int) pow(NUM_GENERATING_BASE,
            (sort_cycle + NUM_GENERATING_ADDITION));
    int *integers_a;
    int *integers_b;
    int *integers_c;

    integers_a = (int *) malloc(sizeof(integers_a) * num_elems);
    integers_b = (int *) malloc(sizeof(integers_b) * num_elems);
    integers_c = (int *) malloc(sizeof(integers_c) * num_elems);

    time_t t;
    srand(SHUFFLE_SEED);

    int i;
    for (i = 0; i < num_elems; i++) {
        integers_a[i] = (rand() % (num_elems * 4));
    }

    Shuffle(integers_a, num_elems);

    integers_b = CopyArray(integers_a, integers_b, num_elems);
    integers_c = CopyArray(integers_a, integers_c, num_elems);

    if (alg_a == true) {
        RunAlgoA(sort_cycle, integers_a, num_elems, runningTimes_a);
    } else if (alg_b == true) {
        RunAlgoB(sort_cycle, integers_b, num_elems, runningTimes_b);
    } else if (alg_c == true) {
        RunAlgoC(sort_cycle, integers_c, num_elems, runningTimes_c);
    } else if (alg_d == true) {
        RunAlgoA(sort_cycle, integers_a, num_elems, runningTimes_a);
        RunAlgoB(sort_cycle, integers_b, num_elems, runningTimes_b);
        RunAlgoC(sort_cycle, integers_c, num_elems, runningTimes_c);
    }

    free(integers_a);
    free(integers_b);
    free(integers_c);
}

// Main function for running the program
// Getting the input from command line argument
int main(int argc, char *argv[]) {
    int64_t *runningTimes_a = (int64_t *) malloc(sizeof(int64_t) * SORT_CYCLES);
    int64_t *runningTimes_b = (int64_t *) malloc(sizeof(int64_t) * SORT_CYCLES);
    int64_t *runningTimes_c = (int64_t *) malloc(sizeof(int64_t) * SORT_CYCLES);

    bool alg_a = false;
    bool alg_b = false;
    bool alg_c = false;
    bool alg_d = false;

    // Check which sorting algorithm to be proceeded with
    if (strcmp(argv[1], "-a") == 0) {
        alg_a = true;
    } else if (strcmp(argv[1], "-b") == 0) {
        alg_b = true;
    } else if (strcmp(argv[1], "-c") == 0) {
        alg_c = true;
    } else if (strcmp(argv[1], "-all") == 0) {
        alg_d = true;
    } else {
        printf("Please enter '-a', '-b', '-c', or '-all'.\n");
    }

    // Calling Sorting Controller
    int i;
    for (i = 0; i < SORT_CYCLES; i++) {
        SortController(i, alg_a, alg_b, alg_c, alg_d,
                runningTimes_a, runningTimes_b, runningTimes_c);
    }

    // Print out the results
    PrintResults(alg_a, alg_b, alg_c, alg_d,
            runningTimes_a, runningTimes_b, runningTimes_c);

    // Free pointers' memories
    free(runningTimes_a);
    free(runningTimes_b);
    free(runningTimes_c);
}
