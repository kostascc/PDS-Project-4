/**
 * PDS Project 4
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 */

#ifndef BLOCKPERMUTATIONS_HPP_
#define BLOCKPERMUTATIONS_HPP_

#include <iostream>
#include <vector>
#include <math.h>

#define MPI_BLOCKPERMUTATIONS 0xB9

#define PERM_BLOCK_SIZE 9  // Do NOT change! Hard-coded size!

using namespace std;

class BlockPermutations {
  public:    
    vector<int> permutations;
    int lSideIdxBegin, lSideIdxEnd; // Permutation bounds

    /**
     * Initializes Block Permutations.
     * Call Permutate(...) to develop calculate thhe permutations.
     **/
    BlockPermutations();

    /**
     * Creates possible permutations out of
     * a bxb boolean matrix-matrix multiplication,
     * using a set of threads.
     * @param threads threads to work on the permutations
     **/ 
    void Permutate(int threads);

    /**
     * Calculates the permutation index of two 
     * integer states.
     **/
    int PermutationIdx(int leftState, int rightState);
    
    
    private:
      
      /**
       * Creates possible permutations out of
       * a bxb boolean matrix-matrix multiplication,
       * using a set of threads.
       **/
      void permutate_thread(int LSideBegin, int LSideEnd);

      /** 
       * Multiplies two matrices in the format
       * of integer bit data (Column-first array (CSC)).
       **/
      int block_data_matrix_mult(int L, int R);



    // /**
    //  * Combines BlockPermutation differend BlockPermutations
    //  * objects.
    //  * @param A First BlockPermutations object
    //  * @param B Second BlockPermutations object
    //  * @param C The combination of A and B
    //  **/
    // static void Combine(BlockPermutations** C, BlockPermutations** A, BlockPermutations** B);

    // /**
    //  * Sends BlockPermutations Object over MPI to a node
    //  **/
    // static void MPISend(BlockPermutations** C, int node);

    // /** 
    //  * Receives BlockPermutations Object over MPI from a node
    //  **/
    // static void MPIReceive(BlockPermutations** C, int node);
};

#endif