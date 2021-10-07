/**
 * Parallel & Distributed Systems:
 * Boolean Matrix-Matrix Multiplication
 * 
 * 2021 Ⓒ K. Chatzis
 * kachatzis <at> ece.auth.gr
 * Dept. of Electrical & Computer Engineering
 * Aristotle University of Thessaloniki
 **/

#include <utils.hpp>

utils::Clock::Clock() {
	clockT = clock_t();
}


void utils::Clock::startClock()
{
	clockT = clock();
	return;
}


string utils::Clock::stopClock()
{
	char buf[100];
	snprintf(buf, sizeof(buf), "%.4fs", (double)(clock() - clockT) / CLOCKS_PER_SEC);
	string bufStr = buf;
	return bufStr;
}

void utils::Clock::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	return;
}