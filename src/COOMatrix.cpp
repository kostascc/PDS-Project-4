/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#include "COOMatrix.hpp"


void COOMatrix::addPoint(int i, int j){
  this->coo.emplace_back(i, j);
  this->nnz++;
}


void COOMatrix::CSCsort(){
  
  std::sort(this->coo.begin(), this->coo.end(), [](auto &left, auto &right) {
    if(left.second == right.second)
      return left.first < right.first;
      return left.second < right.second;
  });

}
