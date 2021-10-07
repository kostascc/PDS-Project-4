/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef SPARSE_HPP__
#define SPARSE_HPP__

#include "CSCMatrix.hpp"
#include "auxlib.hpp"

// Convert between CSC and CSR formats.
void CSCtoCSR(CSCMatrix* A, CSCMatrix* B);

// Sort Sparse Matrix (CSC/CSR) indices.
void sparseSortMtx(CSCMatrix* mx);

// Quicksort of an array between two indiices
void quicksort(int* arr, int first, int last);

//void CSCtoBlock9(Matrix* M, int** b, Runtime runtime);



// Adds a row to the specified column
// void addcsci(Matrix* mx, int idx, int ptr);

#endif