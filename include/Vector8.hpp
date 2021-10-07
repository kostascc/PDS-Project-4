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


using namespace std;


/**
 * A class to store and use vectors of length 8.
 * For a quicker execution, two Vector8 instances should
 * be created and used throughout the algorithm,
 * without them being destroyed.
 **/
class Vector8{

    private: 

        uint8_t vec;    // Vector

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
         * @param col Column of vector in Noodle (not global).
         * @param block Index of block from the top of the column.
         **/
        void LoadVectorFromNoodle(Noodle* noodle, int col, int block);

        /**
         * Resets Vector
         **/
        void Reset();

};

#endif