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
#include "utils.cuh"
#include "auxlib.hpp"
#include "mmarket.hpp"
#include "mmio.h"
#include "v1.hpp"


using namespace std;


int main(int argc, char** argv)
{

    Runtime rt = startup(argc, argv);

    if(rt.v1){
        v1_execute(rt);
    }

    return 0;
}