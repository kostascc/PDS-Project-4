/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "CSCBlocking64.hpp"


uint64_t CSCBlocking64::GetBlockValue(Noodle* M, int linBegin, int colBegin){

    int block = linBegin / VECTOR8_SIZE;

    uint64_t value = (uint64_t)0;

    // For each column
    for(int i=0; i<BLOCK64_LINE_SIZE; i++){

        // Get the corresponding Vector8, and shift it to the correct column
        value |= ((uint64_t)Vector8::GetVectorFromNoodle(M, colBegin+i, block)) << i*VECTOR8_SIZE;

    }

    return value;

}

uint64_t CSCBlocking64::GetFilterBlockValue(Noodle* M, int linBegin, int colBegin){

    return ((uint64_t) CSCBlocking64::GetBlockValue(M, linBegin, colBegin)) ^ (uint64_t)BLOCK64_MAX_VALUE;

}

void CSCBlocking64::AddCOOfromBlockValue(COOMatrix* M, uint64_t blockValue, int linBegin, int colBegin){

    // For each bit of the value,
    // starting from the LSB
    for(int i=0; i<64; i++){

        if( blockValue & (1 << i) ){
            // Note: The value is in Column-Major format, thus
            //   column = i / 8
            //   row    = i % 8
            M->addPoint(
                linBegin + BLOCK64_LINE_SIZE-1 - i%VECTOR8_SIZE,  // Line
                colBegin + BLOCK64_LINE_SIZE-1 - i/VECTOR8_SIZE   // Column
            );

            #ifdef CSCBLOCKING64_CHECK_COO_VALUES
                int tmplin = linBegin + BLOCK64_LINE_SIZE-1 - i%VECTOR8_SIZE;
                int tmpcol = colBegin + BLOCK64_LINE_SIZE-1 - i/VECTOR8_SIZE;

                if(tmplin < 0 || tmplin - linBegin > BLOCK64_LINE_SIZE){
                    printf("[Error] COO Row out of bounds (AddCOOfromBlockValue): %d\n", tmplin);
                    exit(EXIT_FAILURE);
                }

                if(tmpcol < 0 || tmpcol - colBegin > BLOCK64_LINE_SIZE){
                    printf("[Error] COO Column out of bounds (AddCOOfromBlockValue): %d\n", tmpcol);
                    exit(EXIT_FAILURE);
                }
            #endif
        }

    }

}

uint64_t CSCBlocking64::MultiplyBlocks(uint64_t A, uint64_t B, uint64_t F){
    // Initialize with the filter
    uint64_t val = F;   // F contains ones in places that don't need calculation
    int i=0;
    // val = (uint64_t)0;
    // TODO: Add counter to measure multiplication savings
    
    // For each Column of A and Row of B
    while(i<BLOCK64_LINE_SIZE && val != BLOCK64_MAX_VALUE)
    {
        val |= Vector8Util::Mult( 
            (uint8_t) ((A>>(56-i*VECTOR8_SIZE)) & 0xFF) ,
            (uint8_t) ((B>>(56-i*VECTOR8_SIZE)) & 0xFF));
        i++;
    }

    // TODO: Maybe optimize time by removing the filter-cleaning afterwards

    // Clean Filter
    return val & (F ^ BLOCK64_MAX_VALUE) ;

}
