/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

#include "Block.hpp"

Block::Block(){
  this->linBegin = -1;
  this->colBegin = -1;
  this->maxValue = (int)pow(2, POW2(BLOCK_LINE_SIZE)) -1;
  this->value = 0;
}

void Block::UpdateBlockPosition(int linBegin, int colBegin){
  this->linBegin = linBegin;
  this->colBegin = colBegin;
  this->value = 0;
}

void Block::BlockOR(int nextValue){
    this->value |= nextValue;
}

bool Block::isAllOnes(){

  #if DBG_BLOCK_CHECK_VALUE_OVERFLOW == true
    if (value > this->maxValue){
      printf("[Error] Block Value overflow\n");
      exit(EXIT_FAILURE);
    }
  #endif

  return (value == this->maxValue);
}
