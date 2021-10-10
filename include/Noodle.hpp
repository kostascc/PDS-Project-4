/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef NOODLE_HPP_
#define NOODLE_HPP_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mat.h"
#include <string>
#include <vector>
#include <sstream>
#include "CSCMatrix.hpp"

using namespace std;

// Check for column overflows
#define NOODLE_CHECK_COL_OVERFLOW

// Check overflow while building cscb matrix
#define NOODLE_CHECK_BLOCKMAKING_OVERFLOW

#define NOODLE_CHECK_CSCB_CONTEXT

#define NOODLE_BLOCK_LENGTH 2
#define NOODLE_BLOCK_COLS 3

/**
 * Noodle is an auxiliary class assisting to the
 * handling of blocks. 
 * 8 of the columns that are being used for block multiplication
 * are converted into 8-by-8 blocks.
 * The noodle contains which rows belong to every block and column,
 * thus improving block calculations. 
 **/
class Noodle {

    public:

        /* Pointer to csci, of the start of each column.  *
         * This is a pointer to the actual cscp array,    *
         * with an offset to the selected starting column.*/
        int* cscp;  

        /* Pointer to csci, of the start of each block.   *
         * Blocks are continuous, thus blocks of a column *
         * start at the end of the previous one.          */
        int* cscb;  

        /* Non-Zero rows. This is a pointer to the actual *
         * csci array, with an ofset to the selected      *
         * column.                                        */
        int* csci;  

        // Default height of Matrix
        int  H;   

        // Starting Column (leftmost)
        // int startCol;

        /**
         * Noodle Constructor.
         * 
         * @param H Default Matrix height
         **/
        Noodle(int H);

        /**
         * Loads 8 full columns of the CSC Matrix,
         * devided into blocks of length 8.
         * 
         * @param csc CSCMatrix object.
         * @param col The leftmost column of the Noodle.
         **/
        void LoadNoodleFromCSC(CSCMatrix* csc, int col);

        /**
         * Resets Noodle.
         * (Not Required between Noodle Loads, as it 
         * instantiates new arrays)
         **/
        void Reset();

    private:

        /**
         * Divide the CSC Matrix into blocks.
         * This is used internally after successful 
         * column initializations, to build the
         * cscb array.
         **/
        void CreateBlocks();
    
};

#endif