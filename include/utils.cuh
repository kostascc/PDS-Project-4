/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef _UTILS_CUH
#define _UTILS_CUH


#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <parameters.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <math.h>


#ifndef POW2
#define POW2(a) (a)*(a)
#endif
#ifndef MAX
#define MAX(a,b) ((a < b) ? b : a)
#endif
#ifndef MIN
#define MIN(a,b) ((a < b) ? a : b)
#endif


#ifdef __INTELLISENSE__ // Intellisense
#define __KERNEL2(grid, block)
#define __KERNEL3(grid, block, sh_mem)
#define __KERNEL4(grid, block, sh_mem, stream)
#define __syncthreads() ;
#define atomicAdd(a,b) *a+=b
#define __expf(a) exp(a)
#define __fsub_rn(a,b) a-b
#define __fadd_rn(a,b) a+b
#define __fmul_rn(a,b) a*b
#define __fdiv_rn(a,b) a/b
#else   // CUDA
#define __KERNEL2(grid, block) <<< grid, block >>>
#define __KERNEL3(grid, block, sh_mem) <<< grid, block, sh_mem >>>
#define __KERNEL4(grid, block, sh_mem, stream) <<< grid, block, sh_mem, stream >>>
#endif


#endif