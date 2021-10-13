/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "v2.hpp"

/**
 * Do not change the following three values.
 * Block size is hardcoded!
 **/

#define BLOCK_SIZE 9
#define BLOCK_HEIGHT 3
#define BLOCK_WIDTH 3

using namespace std;


void V2::Execute(Runtime rt){   

    // Matrices A and F required to be in CSR format
    if(!rt.opt_csr_a || rt.opt_csr_b || !rt.opt_csr_f){
        printf("[Error] Flags '--opt-csr-a' and '--opt-csr-f' are required for V2.\n");
        // exit(EXIT_FAILURE);
    }

    // Start Timer
    time_t tim;
    srand((unsigned) time(&tim));
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    // Initialize MPI
    // MPIUtil mpi = MPIUtil();

    CSCMatrix* A = rt.A;    // Matrix A
    CSCMatrix* B = rt.B;    // Matrix B
    CSCMatrix* F = rt.F;    // Filter Matrix
    COOMatrix* C = new COOMatrix(); // Resulting Matrix

    // Check that matrix sizes match
    if(A->W != B->H || A->H != B->W || F->H != B->W){
        printf("[Error] Matrix Sizes do not match\n");
        exit(EXIT_FAILURE);
    }

    // All possible 3x3 blocks, and every
    // multiplication between them.
    Block9Permutations permute = Block9Permutations();
    permute.Permutate(rt.threads);

    // Block block = Block9();

    // uint64_t blocksAvoided = 0;     // Count of blocks that were skipped
    // uint64_t blocksCalculated = 0;  // Count of blocks that were calculated

    Block9 block;
    COOMatrix coo;

    int tmpnnz = 0;

    // For each block in the initial Matrix

    #pragma omp parallel for \
    shared(A,B,F,C,tmpnnz) \
    private(block,coo)
    for(int i=0; i<A->H; i+=BLOCK_HEIGHT){      // For each block-starting line
        
        coo.Reset();
        
        for(int j=0; j<A->W; j+=BLOCK_WIDTH){   // For each block-starting column

            // Block with starting point at i, j
            block.UpdateBlockPosition(i, j);
            block.Reset();
            block.value = 0;

            // int tmpFilter = CSCBlocking9::GetBlockValue(F, i, j);
            // Initiate the block using the filter
            // block.BlockOR( tmpFilter ^ 0x1FF );
            
            // For each intermediate block other than the middle one
            for(int k=0; k<A->H; k+=BLOCK_HEIGHT){
                
                if (block.isAllOnes() ){
                    // #pragma omp atomic
                    // blocksAvoided += (int)((A->H-k) / 3);
                    break;
                }

                // OR the previous block value with the  
                // current intermediate block multiplication
                block.BlockOR( 
                    permute.GetPermutation(
                        CSCBlocking9::GetBlockValue(A, k, i),
                        CSCBlocking9::GetBlockValue(B, k, j)
                    )
                );

            }


            // Block value has been calculated
            // block.value &= tmpFilter;
            // block.CleanFilter( tmpFilter ^ 0x1FF );

            // Add block to COO values
            CSCBlocking9::AddCOOfromBlockValue(&coo, block.value, i, j);

        }

        #pragma omp critical
        {
            C->coo.insert( C->coo.end(), coo.coo.begin(), coo.coo.end() );
            C->nnz += coo.nnz;
        }
    }


    // Stop Timer
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    float delta_us = (float) ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000)/ (1000000);
    printf("[Info] V2 took %f s\n", delta_us);

    printf("[Info] NNZ: %d\n", C->nnz);

}

#undef BLOCK_SIZE
#undef BLOCK_HEIGHT
#undef BLOCK_WIDTH
