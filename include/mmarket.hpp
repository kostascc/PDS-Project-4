// PDS Project 4
// 
// Copyright 2021 Ⓒ K. Chatzis
// kachatzis <at> ece.auth.gr

#ifndef mmarket_hpp__
#define mmarket_hpp__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "mat.h"
#include <mmio.h>
#include <stdbool.h>
#include <iostream>
#include "utils.hpp"
#include "CSCMatrix.hpp"
#include "msort.hpp"
#include "Runtime.hpp"
#include "sparse.hpp"


/**
 * Import Matrix-Market file
 **/
void mmarket_import(char* filename, CSCMatrix* mx, bool transpose, bool three_column_coo);


#endif  // mmarket_h__