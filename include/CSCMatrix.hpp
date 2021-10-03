/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

#ifndef CSCMATRIX_HPP_
#define CSCMATRIX_HPP_

class CSCMatrix {
  public:    
    int* csci;  // Row Indices
    int* cscp;  // Column Pointers
    int NZ;     // Non-Zeroes
    int W;      // Width
    int H;      // Height
};

#endif