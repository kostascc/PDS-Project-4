/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "Block64.hpp"

Block64::Block64(){
  this->linBegin = -1;
  this->colBegin = -1;
  this->value = (uint64_t)0;
}

void Block64::UpdateBlockPosition(int linBegin, int colBegin){
  this->linBegin = linBegin;
  this->colBegin = colBegin;
  this->value = (uint64_t)0;
}

void Block64::BlockOR(uint64_t nextValue){
    this->value |= nextValue;
}

bool Block64::isAllOnes(){

    // No overflow check possible in uint64_t
    // #ifdef DBG_BLOCK64_CHECK_VALUE_OVERFLOW
    // if (value > BLOCK64_MAX_VALUE || value < 0){
    //     printf("[Error] Block Value overflow\n");
    //     exit(EXIT_FAILURE);
    // }
    // #endif

    return (value == (uint64_t)BLOCK64_MAX_VALUE);
}

void Block64::CleanFilter(uint64_t filter){
    // Ones in the positions where a
    // calculation is required.
    // Zeroes in places to be cleaned.
    this->value &= filter;
}

void Block64::Reset(){
    this->value = (uint64_t)0;
}
