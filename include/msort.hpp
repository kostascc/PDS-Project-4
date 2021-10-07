/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef msort_hpp__
#define msort_hpp__

#include <stdlib.h>
#include "omp.h"
#include <stdio.h>

/** Make a copy of an array from start to end - 1.
Equivalent to Python's arr[start:end] */
int* slice(int *arr, int start, int end);

/** Merge left and right into result, overwriting everything in result. */
void merge(
    int *I, int *J, /*int *V,*/                     // Result
    int *left_I, int *left_J, /*int *left_V,*/      // Left
    int *right_I, int *right_J, /*int *right_V,*/   // Right
    int leftLen, int rightLen)                      // Length
;

// in-place merge sort
void mergeSort(int *I, int *J, /*int *V,*/ int len);

void switcharoo_to_lower_triangle(int *I, int *J, int nz);

#endif