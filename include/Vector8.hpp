/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef VECTOR8_HPP_
#define VECTOR8_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include "utils.hpp"
#include "Noodle.hpp"
#include "AUXParameters.hpp"


using namespace std;

#ifdef DEBUGGING_CHECKS
    // Check for pointer overflows while loading a vector
    #define VECTOR8_CHECK_LOADING_OVERFLOW

    // Check the csci array for erroneous contents
    #define VECTOR8_CHECK_CSCI_CONTEXT
#endif

// Length of 8-digit blocks (8 of course)
#define VECTOR8_BLOCK_LENGTH V3_BLOCK_SIZE

// 8-digit blocks per Noodle Block
#define VECTOR8_BLOCKS_PER_NOODLE_BLOCK V3_BLOCKS_PER_NOODLE_BLOCK



/**
 * A class to store and use vectors of length 8.
 * For a quicker execution, two Vector8 instances should
 * be created and used throughout the algorithm,
 * without them being destroyed.
 **/
class Vector8{

    // private:
    public: 

        uint8_t vec;    // Vector, with LSB at the end (down)

    public:

        /**
         * Constructor without initial vector value.
         **/
        Vector8();

        /**
         * Constructor of a vector with a size of 8.
         * 
         * @param vec Vector
         **/
        Vector8(uint8_t vec);

        /**
         * Loads a vector of length 8 from a Noodle.
         * 
         * @param noodle A Noodle object with the respective columns loaded.
         * @param col Column of vector (0 .. 7, or 0 .. Width-1).
         * @param block Index of block from the top of the column (0 .. H/8-1 ).
         **/
        void LoadVectorFromNoodle(Noodle* noodle, int col, int block);

        /**
         * Loads a vector of length 8 from a Noodle.
         * 
         * @param noodle A Noodle object with the respective columns loaded.
         * @param col Column of vector (0 .. 7, or 0 .. Width-1).
         * @param block Index of block from the top of the column (0 .. H/8-1 ).
         **/
        static uint8_t GetVectorFromNoodle(Noodle* noodle, int col, int block);

        /**
         * Resets Vector
         **/
        void Reset();

};

#endif