/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef COOMATRIX_HPP_
#define COOMATRIX_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#define MPI_COO_ADDPOINT 0xC00A

#define COO_DEFAULT_RESERVE_SIZE 1<<19

using namespace std;

class COOMatrix {
  public:    
    vector<pair<int,int>> coo;  // <Line,Column> pairs 
    int nnz;

    COOMatrix(){
        coo.reserve(COO_DEFAULT_RESERVE_SIZE);
        nnz = 0;
    }

    /**
     * Adds Point in COO Matrix
     * @param i Line
     * @param j Column
     **/
    void addPoint(int i, int j);

    /**
     * Sorts COO Matrix for export
     * in CSC Format.
     **/ 
    void CSCsort();

    /**
     * Reset COO Matrix
     **/
    void Reset();

};

#endif