/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef BLOCK9_HPP_
#define BLOCK9_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include "utils.hpp"
//#include "utils.cuh"

#ifndef BLOCK_LINE_SIZE
#define BLOCK_LINE_SIZE 3
#endif

// Check for failures in the integer value of the block
#define DBG_BLOCK_CHECK_VALUE_OVERFLOW true

using namespace std;

/**
 * Block9 of the CSC Matrix in 
 * integer value format.
 **/
class Block9 {

  public:  
    int value;      // Integer value of block (column-first/CSC)
    int maxValue;   // Max possible value of block
    int linBegin;   // Line of Upper-Left corner
    int colBegin;   // Column of Upper-Left corner

  public:

    Block9();

    /**
     * Update block position
     * 
     * @param linBegin Upper left line of block
     * @param colBegin Upper left column of block
     **/
    void UpdateBlockPosition(int linBegin, int colBegin);

    /**
     * Executes the OR operation on the block and 
     * it's next state.
     * 
     * @param nextValue calculated block value to be 
     * added to the existent block
     **/
    void BlockOR(int nextValue);

    /**
     * Check if block is All-Ones
     **/
    bool isAllOnes();

    /**
     * Remove the value of the filter
     * 
     * @param filter The value with ones in the positions
     * where a calculation is required, and zeroes in positions
     * to be cleaned.
     **/
    void CleanFilter(int filter);

    /** 
     * Resets block value
     **/
    void Reset();

};

#endif