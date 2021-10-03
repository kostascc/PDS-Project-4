#include "v2.hpp"

/**
 * Do not change the following three values.
 * Block size is hardcoded!
 **/
#ifndef BLOCK_SIZE
    #define BLOCK_SIZE 9
#endif
#ifndef BLOCK_HEIGHT
    #define BLOCK_HEIGHT 3
#endif
#ifndef BLOCK_WIDTH
    #define BLOCK_WIDTH 3
#endif


void V2::Execute(Runtime rt){   

    // Matrix required to be CSR
    if(!rt.opt_csr_a){
        printf("[Error] Flag '--opt-csr-a' is required for V2.\n");
        exit(EXIT_FAILURE);
    }

    // Start Clock
    utils::Clock clock = utils::Clock();
    clock.startClock();

    // Initialize MPI
    // MPIUtil mpi = MPIUtil();

    CSCMatrix* A = rt.A;    // Matrix A
    CSCMatrix* B = rt.B;    // Matrix B
    CSCMatrix* F = rt.F;    // Filter Matrix
    COOMatrix* C = new COOMatrix(); // Resulting Matrix

    // All possible 3x3 blocks, and every
    // multiplication between them.
    BlockPermutations permute = BlockPermutations();
    permute.Permutate(rt.threads);

    /**
     * TODO: Add padding on the input CSC matrices, for 
     * the case where the matrix is not divisible by 3.
     **/

    // For each block in the initial Matrix
    for(int i=0; i<A->H; i+=BLOCK_HEIGHT){      // For each block-starting line
        for(int j=0; j<A->W; j+=BLOCK_WIDTH){   // For each block-starting column

            // Block with starting point at i, j
            Block block = Block(i, j);



        }
    }

    
    printf("[Info] V2 Took %s\n", clock.stopClock());

    printf("[Info] NZ: %d\n", C->nnz);


}

#undef BLOCK_SIZE
#undef BLOCK_HEIGHT
#undef BLOCK_WIDTH
