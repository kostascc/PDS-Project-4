#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include "utils.cuh"

#ifndef BLOCK_LINE_SIZE
#define BLOCK_LINE_SIZE 3
#endif

// Check for failures in the integer value of the block
#define DBG_BLOCK_CHECK_VALUE_OVERFLOW true

using namespace std;

/**
 * Block of the CSC Matrix in 
 * integer value format.
 **/
static class Block {

  public:  
    int linBegin;   // Line of Upper-Left corner
    int colBegin;   // Column of Upper-Left corner
    int value;      // Integer value of block (column-first/CSC)
  private:  
    int maxValue;

  public:

    Block(int linBegin, int colBegin);

    /**
     * Check if block is All-Ones
     **/
    bool isAllOnes();

};

#endif