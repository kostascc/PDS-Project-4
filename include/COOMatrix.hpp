/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#ifndef COOMATRIX_HPP_
#define COOMATRIX_HPP_

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#define MPI_COO_ADDPOINT 0xC00A

#define COO_DEFAULT_SIZE 1<<14

using namespace std;

class COOMatrix {
  public:    
    vector<pair<int,int>> coo;
    int nnz;

    COOMatrix(){
        coo.resize(COO_DEFAULT_SIZE);
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

};

#endif