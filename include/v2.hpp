#ifndef V2_HPP__
#define V2_HPP__

#include "Runtime.hpp"
#include "CSCMatrix.hpp"
#include "COOMatrix.hpp"
#include "auxlib.hpp"
// #include <windows.h>
// #include <algorithm>
#include <time.h>
#include "BlockPermutations.hpp"
#include "Block.hpp"
#include "CSCBlocking.hpp"

using namespace std;

class V2{

    public:

        static void Execute(Runtime rt);

};

#endif