/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef AUXPARAMETERS_H_
#define AUXPARAMETERS_H_

    // Debugging Flag. 
    // Comment out to disable debugging checks and information.
    // #define DEBUGGING_CHECKS

    // 9x9 Matrix height
    #define V2_LINE_SIZE 3

    // 8-digit Vector size
    #define V3_BLOCK_SIZE 8

    // 8-digit blocks to contain in each Noodle block
    #define V3_BLOCKS_PER_NOODLE_BLOCK 1

    // Columns to contain in each Noodle.
    // Use 0 to contain the whole Matrix.
    #define V3_NOODLE_COLUMNS 0

#endif