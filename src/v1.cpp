#include "v1.hpp"


void V1::Execute(Runtime rt){

    // Matrix required to be CSR
    if(!rt.opt_csr_a){
        printf("[Error] Flag '--opt-csr-a' is required for V1.\n");
        exit(EXIT_FAILURE);
    }


    // // debug input Matrix
    // FILE *f = fopen("debug.txt", "wb");
    // if (f == NULL)
    // {
    //     printf("[Error] Couldn't open file!\n");
    //     exit(EXIT_FAILURE);
    // }
    // for(int i=0; i<rt.B->W; i++){
    //     for(int j=rt.B->cscp[i]; j<rt.B->cscp[i+1]; j++){
    //         fprintf(f, "%d,%d\n", rt.B->csci[j]+1, i+1);
    //     }
    // }
    // fclose(f);


    // Start Timer
    time_t tim;
    srand((unsigned) time(&tim));
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
 
    // Resulting COO pairs
    std::vector<std::pair<int,int>> coo;
    int NZ = 0;

    // Vector Reduction

    // For Each Column of Matrix B
    for(int j=0; j<rt.B->W; j++){

        // Caution:
        // Matrix A is Transposed, thus rows are meant
        // to be searched as columns in the CSC format.

        // Foreach Row of Matrix A
        // (or column of A transposed)
        #pragma omp parallel for num_threads(rt.threads)
        for(int i=0; i<rt.A->W; i++){
            
            // Foreach Non-Zero on i-th row of Matrix A
            for(int k=rt.A->cscp[i]; k<rt.A->cscp[i+1]; k++){
                
                if(binarySearch(rt.B->csci, rt.B->cscp[j], rt.B->cscp[j+1]-1, rt.A->csci[k])){
                    
                    // #pragma omp critical
                    // {
                        coo.emplace_back(i, j);
                        NZ ++;
                    // }
                    
                    break;
                }

            }

        }

    }

    // Stop Timer
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    float delta_us = (float) ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000)/ (1000000);
    printf("[Info] V1 took %f s\n", delta_us);

    // TODO: Was Removed when porting to linux. Must fix
    // std::sort(coo.begin(), coo.end(), [](auto &left, auto &right) {
    //     if(left.second == right.second)
    //         return left.first  < right.first ;
    //         return left.second < right.second;
    // });

    exportCOOVectorP(&coo, rt, "v1");

    printf("[Info] NNZ: %d\n", NZ);

}


// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
bool V1::binarySearch(int* arr, int l, int r, int x)
{

    if (r >= l) {
        int mid = l + (r - l) / 2;
  
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return true;
  
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
  
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
  
    // We reach here when element is not
    // present in array
    return false;
    
}
