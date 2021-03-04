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
#include <utils.hpp>


using namespace std;

__device__ void ker(){;}

int main(int argc, char** argv)
{
    printf("This Runs!!\n");

    // ker <<<1,1>>> ();

    return 0;
}
