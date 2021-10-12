/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef V3_HPP__
#define V3_HPP__

#include "Runtime.hpp"
#include "CSCMatrix.hpp"
#include "COOMatrix.hpp"
#include "auxlib.hpp"
#include <time.h>
#include "Block64.hpp"
#include "Noodle.hpp"
#include "CSCBlocking64.hpp"

using namespace std;

class V3{

    public:

        static void Execute(Runtime rt);

};

#endif