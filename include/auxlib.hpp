// PDS Project 2
// 
// Copyright 2021 Ⓒ K. Chatzis
// kachatzis <at> ece.auth.gr

#ifndef auxlib_hpp__
#define auxlib_hpp__


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "mat.h"
#include "mpi_wrapper.h"
#include <mpi.h>
#include "omp.h"
#include "mmarket.hpp"
#include "Runtime.hpp"
#include <string>
#include <vector>
#include <sstream>



/**********************************************
 *          MPI Communication Tags
 **********************************************/
#define MPI_INITIALIZING           10
/**********************************************/


/**
 * Environment variable name for
 * timing info.
 **/
#define _TIMER_PRINT_VAR "TIMER_PRINT"

#ifndef min
#define min(x,y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef max
#define max(x,y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef pow2
#define pow2(x)  x*x
#endif

/**
 * Startup Script Options
 **/
#define MATRIX_PRINT  false  // Print Resulting Matrices


/**
 * Each external variable should
 * be defined both in .c and .h file.
 **/

/**
 * @brief Print timing information.
 * Default: true.
 **/
extern bool _TIMER_PRINT ;


/**
 * Sorts and selects neighbors
 * for a specific m.
 **/
int aux_sort_idx(double** C, int** nidx, double** ndist, int N, int M, int m, int k);


/** 
 * Makes a copy of an array from 
 * start to end - 1. Equivalent to Python's 
 * arr[start:end] 
 **/
// Double Array
double * aux_slice_d(double ** arr, int start, int end);
// Integer Array
int * aux_slice_i(int ** arr, int start, int end);


/** 
 * Merge left and right into result, 
 * overwriting the array in result. 
 **/
void aux_merge ( double** _I, int ** _J, double ** left_I, int ** left_J, double ** right_I, int ** right_J, int leftLen, int rightLen); 


/**
 * In-Place Merge-Sort, with
 * CilkPlus parallelization.
 **/
void aux_mergeSort( double ** _I, int ** _J, int len );


/**
 * Startup Script
 **/
Runtime startup(int argc, char** argv);

// TODO: For Debugging, Remove later
extern int tmp_node_id;


int n_per_node(int node_id, int cluster_size, int n);


/**
 * Export Vector Pair of COO
 **/
void exportCOOVectorP(vector<pair<int,int>>* v, Runtime rt, string title);

#endif