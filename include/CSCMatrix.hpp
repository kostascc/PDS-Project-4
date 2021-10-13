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


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <sstream>

class CSCMatrix {
  public:    
    int* csci;  // Row Indices
    int* cscp;  // Column Pointers
    int NZ;     // Non-Zeroes
    int W;      // Width
    int H;      // Height

    CSCMatrix(){};

    ~CSCMatrix(){
        
        delete csci;
        delete cscp;
        // if(csci!=NULL){
        //     free(csci);
        //     csci = NULL;
        // }

        // if(cscp!=NULL){
        //     free(cscp);
        //     cscp = NULL;
        // }
    };
};

#endif