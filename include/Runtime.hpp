/**
 * PDS Project 4
 * 
 * Copyright 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#ifndef RUNTIME_HPP_
#define RUNTIME_HPP_

#define URI_STRING_SIZE 1024

#include "Matrix.hpp"
#include "string.h"

class Runtime {
  public:    
    Matrix* A;       // 
    Matrix* B;       // 
    bool v1;         // Run V1
    bool opt_csr_a;  // Optimization: Use CSR for Matrix A
    char URIa[URI_STRING_SIZE];
    char URIb[URI_STRING_SIZE];

  Runtime(){
    v1 = false;
    opt_csr_a = false;
  }
};

#endif