/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include "Block9.hpp"

Block9::Block9(){
  this->linBegin = -1;
  this->colBegin = -1;
  this->maxValue = (int)pow(2, POW2(BLOCK_LINE_SIZE)) -1;
  this->value = 0;
}

void Block9::UpdateBlockPosition(int linBegin, int colBegin){
  this->linBegin = linBegin;
  this->colBegin = colBegin;
  this->value = 0;
}

void Block9::BlockOR(int nextValue){
    this->value |= nextValue;
}

bool Block9::isAllOnes(){

  #if DBG_BLOCK_CHECK_VALUE_OVERFLOW == true
    if (value > this->maxValue || value < 0){
      printf("[Error] Block Value overflow\n");
      exit(EXIT_FAILURE);
    }
  #endif

  return (value == this->maxValue);
}

void Block9::CleanFilter(int filter){
    // Ones in the positions where a
    // calculation is required.
    // Zeroes in places to be cleaned.
    this->value &= filter;
}

void Block9::Reset(){
    this->value = 0;
}
