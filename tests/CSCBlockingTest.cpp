/**
 * Parallel & Distributed Systems
 * Project 4
 * 
 * Ⓒ 2021 K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <mpi.h>
#include <cuda_runtime.h>
#include <omp.h>
#include "utils.hpp"
// #include "utils.cuh"
#include "auxlib.hpp"
#include "mmarket.hpp"
#include "mmio.hpp"
#include "v1.hpp"
#include "BlockPermutations.hpp"
#include "CSCBlocking.hpp"


using namespace std;


int main(int argc, char** argv)
{
    CSCMatrix csc = CSCMatrix();
    csc.csci = new int[]{0, 1, 3, 5, 0, 4, 5, 0, 2, 3, 0, 3, 1, 3, 4};
    csc.cscp = new int[]{0,          4,       7,      10, 10,   12,      15};
    csc.H  = 6;
    csc.W  = 6;
    csc.NZ = 15; 

    int linBegin = 3;
    int colBegin = 2;

    int val = CSCBlocking::GetBlockValue(&csc, linBegin, colBegin);

    for (int i = 9; 0 <= i; i--) {
        printf("%c ", (val & (1 << i)) ? '1' : '0');
        if(i%3==0){
            printf(" ");
        }
    }

    printf("\n");


    COOMatrix coo = COOMatrix();

    CSCBlocking::AddCOOfromBlockValue(&coo, val, linBegin, colBegin);

    printf("\nCOO:\n");

    for(int i=0; i<coo.nnz; i++){
        printf("[ %d , %d ]\n", coo.coo.at(i).first, coo.coo.at(i).second);
    }

    return 0;

}