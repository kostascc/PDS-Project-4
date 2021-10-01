#include "Block.hpp"

Block::Block(int linBegin, int colBegin){
  this->linBegin = linBegin;
  this->colBegin = colBegin;

  this->maxValue = (int)pow(2, POW2(BLOCK_LINE_SIZE)) -1;
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
