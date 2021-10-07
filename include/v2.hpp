/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef V2_HPP__
#define V2_HPP__

#include "Runtime.hpp"
#include "CSCMatrix.hpp"
#include "COOMatrix.hpp"
#include "auxlib.hpp"
// #include <windows.h>
// #include <algorithm>
#include <time.h>
#include "Block9Permutations.hpp"
#include "Block9.hpp"
#include "CSCBlocking9.hpp"

using namespace std;

class V2{

    public:

        static void Execute(Runtime rt);

};

#endif