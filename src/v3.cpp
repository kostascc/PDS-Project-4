/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "v3.hpp"

/**
 * Do not change the following three values.
 * Block size is hardcoded!
 **/

#define BLOCK_SIZE 64
#define BLOCK_HEIGHT 8
#define BLOCK_WIDTH 8

using namespace std;


void V3::Execute(Runtime rt){   

    // Matrix B required to be in CSR format
    if(!rt.opt_csr_b || rt.opt_csr_a || rt.opt_csr_f){
        printf("[Error] Flag '--opt-csr-b' is required for V3.\n");
        exit(EXIT_FAILURE);
    }

    // Start Timer
    time_t tim;
    srand((unsigned) time(&tim));
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    CSCMatrix* A = rt.A;    // Matrix A
    CSCMatrix* B = rt.B;    // Matrix B
    CSCMatrix* F = rt.F;    // Filter Matrix
    COOMatrix* C = new COOMatrix(); // Resulting Matrix

    // Check that matrix sizes match
    if(A->W != B->H || A->H != B->W || F->H != B->W){
        printf("[Error] Matrix Sizes do not match\n");
        exit(EXIT_FAILURE);
    }

    // Full width Noodle of the A matrix
    Noodle noodleA = Noodle();
    noodleA.LoadNoodleFromCSC(A, 0);

    // Full width Noodle of the B matrix
    Noodle noodleB = Noodle();
    noodleB.LoadNoodleFromCSC(B, 0);

    // Full width Noodle of the F matrix
    Noodle noodleF = Noodle();
    noodleF.LoadNoodleFromCSC(F, 0);

    Block64 block;
    COOMatrix coo;

    // For each block in the initial Matrix
    #pragma omp parallel for \
    shared(noodleA,noodleB,noodleF,C) \
    private(block,coo) 
    for(int i=0; i<A->H; i+=BLOCK_HEIGHT){      // For each block-starting line
    
        coo.Reset();
        
        for(int j=0; j<A->W; j+=BLOCK_WIDTH){   // For each block-starting column

            // Block with starting point at i, j
            block.UpdateBlockPosition(i, j);
            block.Reset();

            // Initiate the block using the filter
            // uint64_t tmpFilter = CSCBlocking64::GetBlockValue(&noodleF, i, j);
            //tmpFilter = (uint64_t)0xFFFFFFFFFFFFFFFF;
            //block.BlockOR( (uint64_t)tmpFilter );

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
                    CSCBlocking64::MultiplyBlocks(
                        CSCBlocking64::GetBlockValue(&noodleA, i, k),
                        CSCBlocking64::GetBlockValue(&noodleB, j, k),
                        (uint64_t)0 /*tmpFilter ^*/ /*0xFFFFFFFFFFFFFFFF*/
                    )
                );

            }

            //block.value &= (tmpFilter /*^ 0xFFFFFFFFFFFFFFFF*/);
            // Block value has been calculated
            // block.CleanFilter( tmpFilter );

            // Add block to COO values
            CSCBlocking64::AddCOOfromBlockValue(&coo, block.value, i, j);

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
    printf("[Info] V3 took %f s\n", delta_us);

    printf("[Info] NNZ: %d\n", C->nnz);

}

#undef BLOCK_SIZE
#undef BLOCK_HEIGHT
#undef BLOCK_WIDTH
