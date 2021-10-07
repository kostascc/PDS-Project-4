/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
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