/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

#ifndef CSCBLOCKING_HPP_
#define CSCBLOCKING_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include "CSCMatrix.hpp"
#include "COOMatrix.hpp"

#define BLOCK_LINE_SIZE 3  // Do NOT change! Hard-coded size!

#define DBG_CSCBLOCKING_BOUNDS_CHECK


#define B001 1
#define B010 2
#define B011 3
#define B100 4
#define B101 5
#define B110 6
#define B111 7


using namespace std;

class CSCBlocking {

  public:  

    /**
     * Calculates the integer data value of a 
     * block, using a Matrix in CSC format.
     * @param linBegin Line at Upper left corner of block.
     * @param colBegin Column at Upper left corner of block.
     * @return Integer value of block in column-first format (CSC).
     **/
    static int GetBlockValue(CSCMatrix* M, int linBegin, int colBegin);

    /**
     * Calculates the integer data value of a 
     * filter block, using a Matrix in CSC format.
     * The resulting data contains ones in places where
     * the filter doesn't require calculations.
     * @param linBegin Line at Upper left corner of block.
     * @param colBegin Column at Upper left corner of block.
     * @return Integer value of block in column-first format (CSC).
     **/
    static int GetFilterBlockValue(CSCMatrix* M, int linBegin, int colBegin);

    /**
     * Add COO Values from 
     **/
    static void AddCOOfromBlockValue(COOMatrix* M, int blockValue, int linBegin, int colBegin);

    // private:

    /**
     * Binary Search algorithm for 
     **/
    static int BinarySearch(int* arr, int l, int r, int x);

};

#endif