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
#include "Block9Permutations.hpp"
#include "CSCBlocking9.hpp"
#include "COOMatrix.hpp"
#include "Noodle.hpp"
#include "Vector8.hpp"
#include "CSCBlocking64.hpp"


using namespace std;


int main(int argc, char** argv)
{

    uint64_t a = 0xF43723F41F08B39E;
    uint64_t b = 0xFF1502FD9B4CE3CE;
    uint64_t f = 0;

    uint64_t c = CSCBlocking64::MultiplyBlocks(a, b, f);

    printf("mult: %lx\n", c);
    return 0;

}