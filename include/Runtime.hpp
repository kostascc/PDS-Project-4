/**
 * PDS Project 4
 * 
 * Copyright 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#ifndef RUNTIME_HPP_
#define RUNTIME_HPP_

#include "Matrix.hpp"

class Runtime {
  public:    
    Matrix* A;       // 
    Matrix* B;       // 
    bool v1;         // Run V1
    bool opt_csr_a;  // Optimization: Use CSR for Matrix A

  Runtime(){
    v1 = false;
    opt_csr_a = false;
  }
};

#endif