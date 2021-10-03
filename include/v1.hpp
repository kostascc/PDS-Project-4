#ifndef V1_HPP__
#define V1_HPP__

#include "Runtime.hpp"
#include "CSCMatrix.hpp"
#include "auxlib.hpp"
#include <windows.h>
#include <algorithm>

using namespace std;

static class V1{
    public:

        static void Execute(Runtime rt);

        static bool binarySearch(int* arr, int l, int r, int x);

};

#endif