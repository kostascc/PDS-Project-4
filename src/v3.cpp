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
    if(!rt.opt_csr_b){
        printf("[Error] Flags '--opt-csr-b' is required for V3.\n");
        // exit(EXIT_FAILURE);
    }

    // Start Timer
    time_t tim;
    srand((unsigned) time(&tim));
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

//     // Initialize MPI
//     // MPIUtil mpi = MPIUtil();

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

    
//     rt.threads = 1;

//     // All possible 3x3 blocks, and every
//     // multiplication between them.
//     Block9Permutations permute = Block9Permutations();
//     permute.Permutate(rt.threads);

//     // printf("[Info] Permutations Took %s\n", clock.stopClock());


//     uint64_t blocksAvoided = 0;     // Count of blocks that were skipped
//     uint64_t blocksCalculated = 0;  // Count of blocks that were calculated

//     vector<Block> tblock;
//     vector<COOMatrix> tcoo;
//     tblock.reserve(rt.threads+1);
//     tcoo.reserve(rt.threads+1);
//     for(int i=0; i<rt.threads+1; i++){
//         tblock.emplace_back(Block9());
//         tcoo.emplace_back(COOMatrix());
//     }

    Block64 block;
    COOMatrix coo;

    // for(int i=0; i<1000000; i++)
    //     i += (int)(i%2);

    // return;

//     // For each block in the initial Matrix

    #pragma omp parallel for \
    shared(noodleA,noodleB,noodleF,C) \
    private(block,coo) /*num_threads(rt.threads)*/
    for(int i=0; i<A->H; i+=BLOCK_HEIGHT){      // For each block-starting line
    
//         //int t = omp_get_thread_num();

//         // if(t > rt.threads)
//         //     printf("Thread Id out of bounds\n");

//         // if(t>omp_get_thread_num())
//         //     printf("Thread count out of bounds\n");
//         // if(tmpp==0){
//         //     tmpp++;
//         //     #pragma omp critical
//         //         printf("\nthread: %d\n", t);
//         // }
        coo.Reset();
        
        for(int j=0; j<A->W; j+=BLOCK_WIDTH){   // For each block-starting column

            // Block with starting point at i, j
            block.UpdateBlockPosition(i, j);
            block.Reset();

            // Initiate the block using the filter
            uint64_t tmpFilter = CSCBlocking64::GetFilterBlockValue(&noodleF, i, j);
            block.BlockOR( tmpFilter );
            
            
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
                        CSCBlocking64::GetBlockValue(&noodleA, k, j),
                        CSCBlocking64::GetBlockValue(&noodleB, j, k),
                        tmpFilter
                    )
                );

            }

            // Block value has been calculated
            //block.CleanFilter( tmpFilter ^ 0xFFFFFFFFFFFFFFFF );

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

//     printf("[Info] Blocks Calculated: %d, Blocks Avoided: %d\n", blocksCalculated, blocksAvoided);

}

#undef BLOCK_SIZE
#undef BLOCK_HEIGHT
#undef BLOCK_WIDTH
