/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef RUNTIME_HPP_
#define RUNTIME_HPP_

#define URI_STRING_SIZE 1024

#include "CSCMatrix.hpp"
#include "string.h"

class Runtime {
  public:    
    CSCMatrix* A;   // First Input Matrix (CSC Format)
    CSCMatrix* B;   // Second Input Matrix (CSC Format)
    CSCMatrix* F;   // Input Filter Matrix (CSC Format)
    bool v1;        // Run V1
    bool v2;        // Run V2
    bool v3;        // Run V3
    bool v4;        // Run V4
    bool opt_csr_a; // Optimization: Use CSR for Matrix A
    bool opt_csr_b; // Optimization: Use CSR for Matrix B
    bool opt_csr_f; // Optimization: Use CSR for Matrix F
    char URIa[URI_STRING_SIZE];
    char URIb[URI_STRING_SIZE];
    char URIf[URI_STRING_SIZE];
    int threads;


  Runtime(){
    v1 = false;
    v2 = false;
    v3 = false;
    v4 = false;
    opt_csr_a = false;
    threads = 1;
  }
};

#endif