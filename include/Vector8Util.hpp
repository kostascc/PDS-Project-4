/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef VECTOR8_UTIL_HPP_
#define VECTOR8_UTIL_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include "utils.hpp"

using namespace std;


/**
 * Auxiliary class for Vector-Vector multiplication.
 * The supported vectors are exclusively of length 8.
 **/
class Vector8Util{

    private:

        /**
         * Magic Array
         **/
        const static uint64_t magic [];


    public: 

        /**
         * Lookup of vector b in the magic array.
         * 
         * @param b Vector b from operation "a * f(b)".
         * 
         * @return f(b) operation.
         **/
        static uint64_t Lookup(uint64_t b);

        /**
         * Multiplication of two vectors, of length 8.
         * 
         * @param a Vector a
         * @param b Vector b
         * 
         * @returns Column-Major 8x8 Matrix, encoded in
         * a 64bit unsigned integer.
         **/
        static uint64_t Mult(uint8_t a, uint8_t b); 

};

#endif