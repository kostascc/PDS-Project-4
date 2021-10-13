/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef V4_HPP__
#define V4_HPP__

#include "Runtime.hpp"
#include "CSCMatrix.hpp"
#include "COOMatrix.hpp"
#include "auxlib.hpp"
#include <time.h>
#include "Block64.hpp"
#include "Noodle.hpp"
#include "CSCBlocking64.hpp"
#include "MPIUtil.hpp"


#define MPI_TAG_SEND_COO 0xC00
#define MPI_TAG_SEND_NNZ 0x110


using namespace std;

class V4{

    public:

        static void Execute(Runtime rt);

};

#endif