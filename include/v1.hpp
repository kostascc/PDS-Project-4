/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef V1_HPP__
#define V1_HPP__

#include "Runtime.hpp"
#include "CSCMatrix.hpp"
#include "auxlib.hpp"
// #include <windows.h>
// #include <algorithm>
#include "COOMatrix.hpp"

using namespace std;

class V1{
    public:

        static void Execute(Runtime rt);

        static bool binarySearch(int* arr, int l, int r, int x);

};

#endif