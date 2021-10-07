/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef BLOCK9PERMUTATIONS_HPP_
#define BLOCK9PERMUTATIONS_HPP_

#include <iostream>
#include <vector>
#include <math.h>

#define MPI_BLOCKPERMUTATIONS 0xB9

#define PERM_BLOCK_SIZE 9  // Do NOT change! Hard-coded size!

using namespace std;

class Block9Permutations {
  public:    
    vector<int> permutations;
    int lSideIdxBegin, lSideIdxEnd; // Permutation bounds

    /**
     * Initializes Block Permutations.
     * Call Permutate(...) to develop calculate thhe permutations.
     **/
    Block9Permutations();

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
    
    /**
     * Retrieve a specific permutation.
     * 
     * @param permutationIdx Index of permutation to receive
     **/
    int GetPermutationAt(int permutationIdx);

    /**
     * Retrieve the permutation of two block values.
     * 
     * @param leftState value of first block
     * @param rightState value of second block
     **/
    int GetPermutation(int leftState, int rightState);
    
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
    //  * Combines BlockPermutation differend Block9Permutations
    //  * objects.
    //  * @param A First Block9Permutations object
    //  * @param B Second Block9Permutations object
    //  * @param C The combination of A and B
    //  **/
    // static void Combine(Block9Permutations** C, Block9Permutations** A, Block9Permutations** B);

    // /**
    //  * Sends Block9Permutations Object over MPI to a node
    //  **/
    // static void MPISend(Block9Permutations** C, int node);

    // /** 
    //  * Receives Block9Permutations Object over MPI from a node
    //  **/
    // static void MPIReceive(Block9Permutations** C, int node);
};

#endif