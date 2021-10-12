/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "Vector8.hpp"


Vector8::Vector8(){
    this->vec = (uint8_t)0;
}


Vector8::Vector8(uint8_t vec){
    this->vec = vec;
}

void Vector8::LoadVectorFromNoodle(Noodle* noodle, int colIdx, int blockIdx){
    
    this->vec = Vector8::GetVectorFromNoodle(noodle, colIdx, blockIdx);

}


uint8_t Vector8::GetVectorFromNoodle(Noodle* noodle, int colIdx, int blockIdx){
    
    // Check input for errors
    #ifdef VECTOR8_CHECK_LOADING_OVERFLOW

        if(colIdx < 0 || colIdx > noodle->cols-1){
            printf("[Error] Column out of bounds (LoadVectorFromNoodle): %d\n", colIdx);
            exit(EXIT_FAILURE);
        }

        if(blockIdx >= noodle->H / 8){
            printf("[Error] Block out of bounds (LoadVectorFromNoodle): %d\n", blockIdx);
            exit(EXIT_FAILURE);
        }

        if((noodle->H/VECTOR8_BLOCK_LENGTH)%1 > 0){
            printf("[Error] Block count is not an integer (LoadVectorFromNoodle): %f\n", noodle->H/VECTOR8_BLOCK_LENGTH);
            exit(EXIT_FAILURE);
        }

    #endif

    // Block that this corresponds to in the Noodle
    int noodleBlockIdx = blockIdx / VECTOR8_BLOCKS_PER_NOODLE_BLOCK;


    // TODO: ready?
    int pStart = noodle->cscb[ (noodle->H / (VECTOR8_BLOCK_LENGTH*VECTOR8_BLOCKS_PER_NOODLE_BLOCK))
                                *colIdx + noodleBlockIdx    ]   ;
    int pEnd   = noodle->cscb[ (noodle->H / (VECTOR8_BLOCK_LENGTH*VECTOR8_BLOCKS_PER_NOODLE_BLOCK))
                                *colIdx + noodleBlockIdx +1 ] -1;
    
    /**
     * Note:
     * Between pStart and pEnd there are 
     * VECTOR8_BLOCKS_PER_NOODLE_BLOCK blocks.
     * We have to construct a Vector by filtering
     * out the rows that don't belong to
     * this column.
     * The correct rows have values in the
     * region: {blockIdx*8 .. (blockIdx+1)*8-1}
     **/

    int digitCount = 0;

    uint8_t vec = (uint8_t)0;

    // TODO: For some reason, not all overflows are caught in the next part.
    // TODO: Optimize

    // For each digit in the block
    for(int i=pStart; i<=pEnd; i++){
        int c = noodle->csci[i];

        #ifdef VECTOR8_CHECK_CSCI_CONTEXT
            if( c <  VECTOR8_BLOCKS_PER_NOODLE_BLOCK * VECTOR8_BLOCK_LENGTH * noodleBlockIdx ||
                c >= VECTOR8_BLOCKS_PER_NOODLE_BLOCK * VECTOR8_BLOCK_LENGTH * (noodleBlockIdx+1) ){
                printf("[Error] Noodle Block context out of bounds (LoadVectorFromNoodle): %d", c - blockIdx*VECTOR8_BLOCK_LENGTH);
                exit(EXIT_FAILURE);
            }
            
        #endif

        // Check if the csci element is within the correct 8-digit block
        if(c < blockIdx*VECTOR8_BLOCK_LENGTH || c >= (blockIdx+1)*VECTOR8_BLOCK_LENGTH)
            continue;

        #ifdef VECTOR8_CHECK_CSCI_CONTEXT
            if( c - blockIdx*VECTOR8_BLOCK_LENGTH > VECTOR8_BLOCK_LENGTH-1 || 
                c - blockIdx*VECTOR8_BLOCK_LENGTH < 0){
                printf("[Error] Block context out of bounds (LoadVectorFromNoodle): %d", c - blockIdx*VECTOR8_BLOCK_LENGTH);
                exit(EXIT_FAILURE);
            }
        #endif

        vec |= (uint8_t)128 >> (c - blockIdx*VECTOR8_BLOCK_LENGTH); 

    }

    return vec;

}


void Vector8::Reset(){
    this->vec = (uint8_t)0;
}