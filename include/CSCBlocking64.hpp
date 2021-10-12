/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef CSCBLOCKING64_HPP_
#define CSCBLOCKING64_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include "CSCMatrix.hpp"
#include "COOMatrix.hpp"
#include "Noodle.hpp"
#include "Vector8.hpp"
#include "Vector8Util.hpp"
#include "AUXParameters.hpp"


#define BLOCK64_LINE_SIZE 8 

#define BLOCK64_SIZE 64

#define VECTOR8_SIZE 8

#define BLOCK64_MAX_VALUE 0xFFFFFFFFFFFFFFFF

#ifdef DEBUGGING_CHECKS

    #define DBG_CSCBLOCKING_BOUNDS_CHECK

    #define CSCBLOCKING64_CHECK_COO_VALUES

#endif


using namespace std;

class CSCBlocking64 {

  public:  

    /**
     * Calculates the integer data value of a 
     * block, using a CSC Noodle.
     * @param linBegin Line at Upper left corner of block.
     * @param colBegin Column at Upper left corner of block.
     * @return 64-bit Integer value of block in Column-Major format.
     **/
    static uint64_t GetBlockValue(Noodle* M, int linBegin, int colBegin);

    /**
     * Calculates the integer data value of a 
     * filter block, using a CSC Noodle.
     * The resulting data contains ones in places where
     * the filter doesn't require calculations.
     * @param linBegin Line at Upper left corner of block.
     * @param colBegin Column at Upper left corner of block.
     * @return 64-bit Integer value of block in Column-Major format.
     **/
    static uint64_t GetFilterBlockValue(Noodle* M, int linBegin, int colBegin);

    /**
     * Add COO Values from 
     **/
    static void AddCOOfromBlockValue(COOMatrix* M, uint64_t blockValue, int linBegin, int colBegin);

    /**
     * Multiply two 64x64 block values.
     * Optimized to stop when no further calculations
     * are required.
     * 
     * @param A Value of block A
     * @param B Value of block B (B should be Transposed)
     * @param F Value of filter block
     * @returns Value of final 
     **/
    static uint64_t MultiplyBlocks(uint64_t A, uint64_t B, uint64_t F);

};

#endif