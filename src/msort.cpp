/**
 * PDS Project 2
 * 
 * Copyright 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#include "msort.hpp"

/** Make a copy of an array from start to end - 1.
Equivalent to Python's arr[start:end] */
int* slice(int *arr, int start, int end)
{
    try{
        int *result = (int *) malloc((end - start) * sizeof(int));
        int i;
        for (i = start; i < end; i++)
        {
            result[i - start] = arr[i];
        }
        return result;
    } catch (int e) {
        printf("[Info] msort_slice Exception (%d).\n", e);
        exit(EXIT_FAILURE);
    }
}

/** Merge left and right into result, overwriting everything in result. */
void merge(
    int *I, int *J,             // Result
    int *left_I, int *left_J,   // Left
    int *right_I, int *right_J, // Right
    int leftLen, int rightLen)  // Length
{

    try{
        int i, j;

        // I
        i = 0;
        j = 0;
        while(i < leftLen && j < rightLen)
        {
            if (left_I[i] < right_I[j] ||
                (left_I[i] == right_I[j] && left_J[i] < right_J[j]) 
            )
            {
                I[i + j] = left_I[i];
                J[i + j] = left_J[i];

                i++;
            }
            else
            {
                I[i + j] = right_I[j];
                J[i + j] = right_J[j];

                j++;
            }

        }

        for(; i < leftLen; i++)
        {
            I[i + j] = left_I[i];
            J[i + j] = left_J[i];
        }
        for(; j < rightLen; j++)
        {
            I[i + j] = right_I[j];
            J[i + j] = right_J[j];
        }

        free(left_I);
        free(right_I);
        free(left_J);
        free(right_J);

    } catch (int e) {
        printf("[Info] msort_merge Exception (%d).\n", e);
        exit(EXIT_FAILURE);
    }
}

// in-place merge sort
void mergeSort(int *I, int *J, int len)
{
    try{
        if (len <= 1)
        {
            return;
        }
        
        int *left_I = slice(I, 0, len / 2 + 1);
        int *right_I = slice(I, len / 2, len);

        int *left_J = slice(J, 0, len / 2 + 1);
        int *right_J = slice(J, len / 2, len);

        #pragma omp parallel
        #pragma omp single
        {
            #pragma omp task
            mergeSort(left_I, left_J, /*left_V,*/ len / 2);

            #pragma omp task
            mergeSort(right_I, right_J, /*right_V,*/ len - (len / 2));
        }

        merge(I, J, /*V,*/ left_I, left_J, /*left_V,*/ right_I, right_J, /*right_V,*/ len / 2, len - (len / 2));
    } catch (int e) {
        printf("[Info] msort_mergeSort Exception (%d).\n", e);
        exit(EXIT_FAILURE);
    }
}



void switcharoo_to_lower_triangle(int *I, int *J, int nz){

    int t;

    for(int i=0; i<nz; i++){
        if(J[i] > I[i])
        {
            t = I[i];
            I[i] = J[i];
            J[i] = t;
        }
    }

}
