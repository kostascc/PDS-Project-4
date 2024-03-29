/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include <stdio.h>
#include <stdlib.h>
#include "utils.hpp"
#include "auxlib.hpp"
#include "v1.hpp"
#include "v2.hpp"
#include "v3.hpp"
#include "v4.hpp"
#include "Block9Permutations.hpp"
#include "CSCBlocking9.hpp"
#include "COOMatrix.hpp"
#include "Noodle.hpp"
#include "Vector8.hpp"
#include "CSCBlocking64.hpp"


using namespace std;


int main(int argc, char** argv)
{

    Runtime rt = startup(argc, argv);

    if(rt.v1)
        V1::Execute(rt);

    if(rt.v2)
        V2::Execute(rt);

    if(rt.v3)
        V3::Execute(rt);

    if(rt.v4)
        V4::Execute(rt);

    return 0;

}