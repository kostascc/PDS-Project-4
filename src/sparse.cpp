/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/
#include "sparse.hpp"

void sparseSortMtx(CSCMatrix* mx){

    // For each set of pointers
    #pragma omp parallel for
    for(int i=0; i<mx->W; i++){
        // Sort the indices specified between them
        quicksort(mx->csci, mx->cscp[i], mx->cscp[i+1]-1);
    }

}


void quicksort(int* arr,int first,int last){
    int i, j, pivot, temp;

    if(first<last){
        pivot = first;
        i = first;
        j = last;

        while(i<j){
            while(arr[i]<=arr[pivot]&&i<last)
                i++;
            while(arr[j]>arr[pivot])
                j--;
            if(i<j){
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        #pragma omp parallel
        #pragma omp single
        {
            #pragma omp task
            quicksort(arr,first,j-1);

            #pragma omp task
            quicksort(arr,j+1,last);
        }
    }
}


// void addcsci(Matrix* mx, int idx, int ptr){

//     if (mx->csci[mx->cscp[ptr+1]]!=0) {
//         printf("[Error] addcsci: Tried adding row to a non-zero index. [%d]\n", mx->csci[mx->cscp[ptr+1]]);
//         exit(EXIT_FAILURE);
//     } else if (ptr > mx->W) {
//         printf("[Error] addcsci: Pointer out of bounds.\n");
//         exit(EXIT_FAILURE);
//     } else if ( ptr > (mx->W) *2 ) {
//         printf("[Error] addcsci: Pointer out Non-Zero of bounds.\n");
//         exit(EXIT_FAILURE);
//     } else {
//         mx->csci[mx->cscp[ptr+1]] = idx;
//         mx->NZ ++;
//     }

//     for(int i=ptr; i<mx->W; i++){
//         mx->cscp[i]++;
//     }

// }
