/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "Noodle.hpp"


Noodle::Noodle(int H){
    csci = 0;
    cscp = 0;
    cscb = new int[(H/8)+1];
}


void Noodle::LoadNoodleFromCSC(CSCMatrix* csc, int col){
    csci = csc->csci;
    cscp = &csc->cscp[0];
    
    if(csc->H != this->H){
        printf("[Info] Noodle Matrix default height changed (%d->%d)\n", 
            this->H, csc->H);
        this->H = csc->H;
        cscb = new int[(H/8)+1];
    }


    Noodle::CreateBlocks();

}


void Noodle::Reset(){
    csci = 0;
    cscp = 0;
    cscb = new int[(H/8)+1];
}


void Noodle::CreateBlocks(){
    // TODO: ready?
    // TODO: Remove debugging info

    const int columns = NOODLE_BLOCK_COLS;    // Columns from the CSC Matrix to include
    const int length = NOODLE_BLOCK_LENGTH;     // Length of a block 
    const int height = H;     // Height of the CSC Matrix
    const int blocks = columns * height/length; // Number of blocks to create
    int cscbidx = 0;    // Index of cscb for the next cscb insertion
    int i, b;

    // printf("\n\n");

    // For each CSC Column
    for(int j=0; j<columns; j++){

        b = 0;

        // Insert pointer to the column's first element
        cscb[cscbidx] = cscp[j];
        // printf("%d: %d [colstart: %d (%d)]\n", cscbidx, cscb[cscbidx], csci[cscp[j]], cscp[j]);
        cscbidx++;

        // For each row in the j column
        for (i=cscp[j]; i<cscp[j+1]; i++){

            // While there are empty blocks before
            // the one this pointer refers to,
            // plus the next one
            while( csci[i] >= (b+1) * length ){

                cscb[cscbidx] = i;
                // printf("%d: %d [row: %d (%d)]\n", cscbidx, cscb[cscbidx], csci[i], i);
                cscbidx++;

                b++;

            }

        }

        // i ++;

        // Fill it the rest of blocks below,
        // that don't contain any indices
        for(int k=0; k<height/length-b-1; k++){
            cscb[cscbidx] = i;
            // printf("%d: %d  [fill]\n", cscbidx, cscb[cscbidx]);
            cscbidx++;
        }
        printf("\n");

    }

    cscb[cscbidx] = cscp[columns];
    // printf("%d: %d\n", cscbidx, cscb[cscbidx]);
    cscbidx++;

    // printf("\nIdx: %d\n", cscbidx);

    #ifdef NOODLE_CHECK_CSCB_CONTEXT
        int c = cscb[0];
        for(int i=1; i<columns * height/length +1; i++){

            if(c > cscb[i]){
                printf("[Error] Noodle CSCB context check failed (CreateBlocks)\n");
                exit(EXIT_FAILURE);
            }
            c = cscb[i];

        }
    #endif

}
