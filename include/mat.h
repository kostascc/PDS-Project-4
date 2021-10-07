/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#ifndef mat_h__
#define mat_h__


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "msort.hpp"


/**
 * double** X, double val, int i, int j, int n
 **/
void mat_set_ij(double** X, double val, int i, int j, int n);


/**
 * double** X, int i, int j, int n
 **/
double mat_read_ij(double** X, int i, int j, int n);



void mat_transpose(double** X, double** T, int M, int N);

#endif  // mat_h__