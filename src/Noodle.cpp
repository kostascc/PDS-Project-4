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


Noodle::Noodle(){
    // csci = 0;
    // cscp = 0;

    // cscb = (int *) malloc(sizeof(int) *( (H/NOODLE_BLOCK_LENGTH)*NOODLE_BLOCK_COLS+1 ));
    // this->H = H;
}


void Noodle::LoadNoodleFromCSC(CSCMatrix* csc, int col){

    cols = NOODLE_BLOCK_COLS <= 0? csc->W : NOODLE_BLOCK_COLS;

    #ifdef NOODLE_CHECK_COL_OVERFLOW
        if( csc->W <= col)
        {
            printf("[Error] Noodle Column Overflow (LoadNoodleFromCSC): %d\n", col);
            exit(EXIT_FAILURE);
        }
    #endif

    // int _col = NOODLE_BLOCK_COLS <= 0? csc->W : col;

    csci = csc->csci;
    cscp = &csc->cscp[0] + col;

    // if(csc->H != this->H){
        // printf("[Info] Noodle Matrix default height changed (%d->%d)\n", 
            // this->H, csc->H);
        this->H = csc->H;
        cscb = (int *) malloc(sizeof(int) *( (H/NOODLE_BLOCK_LENGTH)*cols+1 ));
    // }

    

    // printf("cscb size: %d\n", ( (H/NOODLE_BLOCK_LENGTH)*cols+1 ));

    Noodle::CreateBlocks(csc);

}


// void Noodle::Reset(){
//     csci = 0;
//     cscp = 0;
//     cscb = new int[(H/NOODLE_BLOCK_LENGTH)*NOODLE_BLOCK_COLS+1];
// }


void Noodle::CreateBlocks(CSCMatrix* csc){
    
    // TODO: Remove debugging info
    // TODO: Optimize
    
    const int columns = cols;               // Columns from the CSC Matrix to include
    const int length = NOODLE_BLOCK_LENGTH; // Length of a block 
    const int height = H;                   // Height of the CSC Matrix
    const int blocks = columns * height/length; // Number of blocks to create
    int cscbidx = 0;                        // Index of cscb for the next cscb insertion
    int i, b;

    // for(int kk=0; kk<10; kk++)
    //     printf("%d, ", cscp[kk]);

    // // printf("cols: %d\n", columns);

    // printf("\n\n");

    // for(int kk=0; kk<10; kk++)
    //     printf("%d, ", csc->cscp[kk]);

    // // printf("cols: %d\n", columns);

    // printf("\n\n");

    // TODO: For some reason, not all overflows are caught in the next part.

    // For each CSC Column
    for(int j=0; j<columns; j++){
        
        b = 0;

        // Insert pointer to the column's first element
        cscb[cscbidx] = cscp[j];
        // printf("%d: %d [colstart: %d (%d)]\n", cscbidx, cscb[cscbidx], csci[cscp[j]], cscp[j]);
        cscbidx++;

        // For each row in the j column
        for (i=cscp[j]; i<cscp[j+1]; i++){

            #ifdef NOODLE_CHECK_CSCI_CONTEXT
                if(csci[i]<0 || csci[i]>=height){
                    printf("[Error] Noodle CSCI context check failed (CreateBlocks): csci:%d@%d cscp[%d,%d]@[%d,%d]\n", csci[i], i, cscp[j], cscp[j+1], j, j+1);
                    exit(EXIT_FAILURE);
                }
            #endif

            // While there are empty blocks before
            // the one this pointer refers to,
            // plus the next one
            while( csci[i] >= (b+1) * length ){
                
                cscb[cscbidx] = i;
                
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

        // printf("[%d]\n", cscbidx);
        // printf("\n");

    }

    cscb[cscbidx] = cscp[columns];
    // printf("%d: %d\n", cscbidx, cscb[cscbidx]);
    cscbidx++;

    // printf("\nIdx: %d\n", cscbidx);

    // #ifdef NOODLE_CHECK_CSCB_CONTEXT
    //     int c = cscb[0];
    //     for(int i=1; i<columns * height/length +1; i++){

    //         if(c > cscb[i]){
    //             printf("[Error] Noodle CSCB context check failed (CreateBlocks)\n");
    //             exit(EXIT_FAILURE);
    //         }
    //         c = cscb[i];

    //     }
    // #endif

}
