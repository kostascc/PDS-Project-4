/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "v4.hpp"

/**
 * Do not change the following three values.
 * Block size is hardcoded!
 **/

#define BLOCK_SIZE 64
#define BLOCK_HEIGHT 8
#define BLOCK_WIDTH 8

using namespace std;


void V4::Execute(Runtime rt){   

    // Matrix B required to be in CSR format
    if(!rt.opt_csr_b || rt.opt_csr_a || rt.opt_csr_f){
        printf("[Error] Flag '--opt-csr-b' is required for V4.\n");
        exit(EXIT_FAILURE);
    }

    // Start Timer
    time_t tim;
    srand((unsigned) time(&tim));
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    // Initialize MPI
    MPIUtil mpi = MPIUtil();

    // MPI_Request* mpiReceive = new MPI_Request();
    // uint32_t* arr;
    // mpi.Receive_t(1, arr, 1, 0, MPI_UNSIGNED, mpiReceive);
    // mpi.ReceiveWait(mpiReceive);
    // printf("     Go on\n");
    
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

    // Starting row for each node
    int pStart = mpi.NodeIdx() * BLOCK_HEIGHT * (int)((A->H / BLOCK_HEIGHT) / mpi.ClusterSize());

    // Ending row for each node
    int pEnd = pStart + BLOCK_HEIGHT * (int)((A->H / BLOCK_HEIGHT ) / mpi.ClusterSize()) - 1;

    // Give more work to the last node
    if(mpi.NodeIdx()==mpi.ClusterSize()-1)
        pEnd = A->H -1;

    #ifdef DEBUGGING_CHECKS
        printf("[Info] Batch for MPI node %d: %d..%d\n", mpi.NodeIdx(), pStart, pEnd);
    #endif
    

    // For each block in the initial Matrix
    #pragma omp parallel for \
    shared(noodleA,noodleB,noodleF,C) \
    private(block,coo) 
    for(int i=pStart; i<=pEnd; i+=BLOCK_HEIGHT){      // For each block-starting line
        
        // COOMatrix coo = COOMatrix();
        coo.Reset();
        
        for(int j=0; j<A->W; j+=BLOCK_WIDTH){   // For each block-starting column
            // break;
            // Block with starting point at i, j
            // Block64 block = Block64();
            block.UpdateBlockPosition(i, j);
            block.Reset();
            // block.value = (uint64_t)0;

            // Initiate the block using the filter
            // uint64_t tmpFilter = CSCBlocking64::GetBlockValue(&noodleF, i, j);
            // tmpFilter = (uint64_t)0xFFFFFFFFFFFFFFFF;
            // block.BlockOR( (uint64_t)tmpFilter );
            
            // For each intermediate block other than the middle one
            for(int k=0; k<A->H; k+=BLOCK_HEIGHT){
                
                if (block.isAllOnes())
                    break;

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

            // block.value &= (tmpFilter /*^ 0xFFFFFFFFFFFFFFFF*/);
            // Block value has been calculated
            // block.CleanFilter( tmpFilter );

            // Add block to COO values
            CSCBlocking64::AddCOOfromBlockValue(&coo, block.value, i, j);
            // delete &block;

        }

        #pragma omp critical
        {
            C->coo.insert( C->coo.end(), coo.coo.begin(), coo.coo.end() );
            C->nnz += coo.nnz;
        }

        // delete &coo;
    }
    

    delete A;
    delete B;
    delete F;

    // Collect data from mpi nodes
    if(mpi.IsMaster()){ // Master Node receives

        // For every node in the cluster
        // #pragma omp parallel for \
        // shared(mpi,C)
        for(int i=1; i<mpi.ClusterSize(); i++){
            
            MPI_Request* mpiReq = new MPI_Request();

            uint32_t* buffNNZ;

            // Receive non-zeroes from any node
            mpi.Receive_t(
                MPI_TAG_SEND_NNZ,
                buffNNZ,
                2,
                MPI_ANY_SOURCE,
                MPI_UNSIGNED,
                mpiReq
            );
            mpi.ReceiveWait(mpiReq);

            uint32_t nnz  = buffNNZ[0];
            uint32_t node = buffNNZ[1];

            if(nnz < 0 || node < 1 || node >= mpi.ClusterSize()){
                printf("[Error] NNZ or Node received by naster was wrong (node: %d)\n", node);
                mpi.Abort();
                exit(EXIT_FAILURE);
            }

            if(nnz<=0)
                continue;

            // Construct COO Matrix buffer
            uint32_t * buffCOO = (uint32_t*) malloc(sizeof(uint32_t) * nnz * 2);
            uint32_t end = nnz;

            // Receive COO Matrix from the same node
            mpi.Receive_t(
                MPI_TAG_SEND_COO,
                buffCOO,
                nnz * 2,
                node,
                MPI_UNSIGNED,
                mpiReq
            );
            mpi.ReceiveWait(mpiReq);
            
            // Add COO values to the overall result
            C->coo.reserve(C->nnz + nnz);
            for(int i=0; i<nnz; i++){
                C->coo.emplace_back(buffCOO[i], buffCOO[i+end]);
            }
            C->nnz += nnz;

            free(buffCOO);
            free(mpiReq);
            
        }

    }else{  // Worker nodes send

        // TODO: Free-Up memory before constructing the buffer

        MPI_Request* mpiReq = new MPI_Request();

        // Send non-zeroes to master
        uint32_t buffNNZ[] = {(uint32_t)C->nnz, (uint32_t)mpi.NodeIdx()};
        mpi.Send_t(
            MPI_TAG_SEND_NNZ,
            buffNNZ,
            2,
            MPI_MASTER_NODE_IDX,
            MPI_UNSIGNED,
            mpiReq
        );

        if(C->nnz<=0){
            // Wait for the last transaction to finish
            mpi.SendWait(mpiReq);
        }else{
            
            // Construct the COO Matrix buffer
            uint32_t * buffCOO = (uint32_t*) malloc(sizeof(uint32_t) * C->nnz * 2);
            uint32_t end = C->nnz;
            for(int i=0; i<C->nnz; i++){
                buffCOO[    i] = C->coo[i].first;
                buffCOO[end+i] = C->coo[i].second;
            }
            
            // Wait for the last transaction to finish
            mpi.SendWait(mpiReq);

            // Send COO matrix to master
            mpi.Send_t(
                MPI_TAG_SEND_COO,
                buffCOO,
                C->nnz * 2,
                MPI_MASTER_NODE_IDX,
                MPI_UNSIGNED,
                mpiReq
            );
            mpi.SendWait(mpiReq);

            free(buffCOO);
            // buffCOO == NULL;

        }

    }

    MPI_Barrier(MPI_COMM_WORLD);

    if(mpi.IsMaster()){
        // Stop Timer
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        float delta_us = (float) ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000)/ (1000000);
        printf("[Info] V4 took %f s\n", delta_us);

        printf("[Info] NNZ: %d\n", C->nnz);

        mpi.Finalize();
    }
    

    delete C;

    return;

}

#undef BLOCK_SIZE
#undef BLOCK_HEIGHT
#undef BLOCK_WIDTH
