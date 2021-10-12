/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef mmarket_hpp__
#define mmarket_hpp__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "mat.h"
#include <mmio.hpp>
#include <stdbool.h>
#include <iostream>
#include "utils.hpp"
#include "CSCMatrix.hpp"
#include "msort.hpp"
#include "Runtime.hpp"
#include "sparse.hpp"
#include "Runtime.hpp"
#include "AUXParameters.hpp"



#define V3_DIVISOR V3_BLOCK_SIZE*V3_BLOCKS_PER_NOODLE_BLOCK
#define V2_DIVISOR V2_LINE_SIZE

#define ALLOW_ONLY_RECTANGULAR_MATRICES true


/**
 * Import Matrix-Market file
 **/
void mmarket_import(Runtime rt, char* filename, CSCMatrix* mx, bool transpose, bool three_column_coo);


#endif  // mmarket_h__