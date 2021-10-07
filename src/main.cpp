/**
 * Parallel & Distributed Systems
 * Project 4
 * 
 * Ⓒ 2021 K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

// #include <stdio.h>
// #include <stdlib.h>
// #include <cstdio>
// #include <mpi.h>
// #include <cuda_runtime.h>
// #include <omp.h>
#include "utils.hpp"
// #include "utils.cuh"
#include "auxlib.hpp"
// #include "mmarket.hpp"
// #include "mmio.hpp"
#include "v1.hpp"
#include "v2.hpp"
// #include "BlockPermutations.hpp"
#include "Block9Permutations.hpp"
#include "CSCBlocking9.hpp"


using namespace std;


int main(int argc, char** argv)
{

    Runtime rt = startup(argc, argv);
    
    if(rt.v1)
        V1::Execute(rt);

    if(rt.v2)
        V2::Execute(rt);

    return 0;

}