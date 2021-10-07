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
    // TODO:
}