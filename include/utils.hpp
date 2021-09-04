/**
 * Parallel & Distributed Systems
 * Project 4
 * 
 * Ⓒ 2021 K. Chatzis
 * kachatzis <at> ece.auth.gr
 **/

#ifndef _UTILS_HPP
#define _UTILS_HPP


#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <parameters.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "vector_functions.h"
#include <math.h>


#ifndef POW2
#define POW2(a) (a)*(a)
#endif
#ifndef MAX
#define MAX(a,b) ((a < b) ? b : a)
#endif
#ifndef MIN
#define MIN(a,b) ((a < b) ? a : b)
#endif


using namespace std;

namespace utils
{

    /**************************
	 *      Program Timer
	 **************************/
	class Clock
	{
	private:

		clock_t clockT;		// Timer

	public:
		Clock();

		/**
		 * Record starting time
		 **/
		void startClock();

		/**
		 * Record Stop time and return the value in seconds
		 **/
		string stopClock();

		/**
		 * Pause Thread for milliseconds
		 **/
		void sleep(int ms);
	};

}


#endif