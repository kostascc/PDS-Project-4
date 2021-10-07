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

void Vector8::LoadVectorFromNoodle(Noodle* noodle, int col, int block){
    // TODO:
}

void Vector8::Reset(){
    this->vec = (uint8_t)0;
}