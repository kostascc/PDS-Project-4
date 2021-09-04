/**
 * PDS Project 4
 * 
 * Copyright 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

class Matrix {
  public:    
    int* csci;  // Row Indices
    int* cscp;  // Column Pointers
    int NZ;     // Non-Zeroes
    int W;      // Width
    int H;      // Height
};

#endif