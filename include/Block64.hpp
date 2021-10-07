/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

#ifndef BLOCK64_HPP_
#define BLOCK64_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include "utils.hpp"


#define BLOCK64_LINE_SIZE 8

// Check for failures in the integer value of the block
// #define DBG_BLOCK64_CHECK_VALUE_OVERFLOW

#define BLOCK64_MAX_VALUE 0xFFFFFFFFFFFFFFFF

using namespace std;

/**
 * Block64 of the CSC Matrix in 
 * integer value format.
 **/
class Block64 {

  public:  

    uint64_t value; // Integer value of block (Column-Major)
    int linBegin;   // Line of Upper-Left corner
    int colBegin;   // Column of Upper-Left corner


    Block64();

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
    void BlockOR(uint64_t nextValue);

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
    void CleanFilter(uint64_t filter);

    /** 
     * Resets block value
     **/
    void Reset();

};

#endif