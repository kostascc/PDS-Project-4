/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

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


using namespace std;


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

        int* cscp;  // Pointer to cscb, of the start of each column
        int* cscb;  // Pointer to csco, of the start of each block
        int* csci;  // Non-Zero rows

    Noodle();

};

#endif