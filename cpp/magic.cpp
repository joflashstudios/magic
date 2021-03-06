// magic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <chrono>
#include <random>
typedef std::chrono::high_resolution_clock Clock;
#include <string>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int billion = 1000 * 1000 * 1000;

bool tryReadInt(int& output) {
	std::string input;
	std::getline(cin, input);
	try {
		output = std::stoi(input);
	}
	catch (std::invalid_argument) {
		return false;
	}
	return true;
}

uint64_t state0 = 1;
uint64_t state1 = 2;
uint64_t xorshift128plus() {
	uint64_t s1 = state0;
	uint64_t s0 = state1;
	state0 = s0;
	s1 ^= s1 << 23;
	s1 ^= s1 >> 17;
	s1 ^= s0;
	s1 ^= s0 >> 26;
	state1 = s1;
	return state0 + state1;
}


int main()
{
	cout << "Enter a max greater than 0: ";
	int maxValue = -1;
	while (!tryReadInt(maxValue) || maxValue < 1)
		cout << "Not a number" << endl;
	maxValue++;

	cout << "Enter a magic number in range: ";
	int magicNumber = -1;
	while (!tryReadInt(magicNumber) || magicNumber < 0 || magicNumber >= maxValue)
		cout << "Not a number" << endl;
	
	auto start = Clock::now();

	int guessCount = 0;
	while (xorshift128plus() % maxValue != magicNumber)
		guessCount++;
	
	auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start).count();
	cout << "Took " << guessCount << " guesses over " << (double)nanoseconds / billion << " seconds" << endl;
	cout << "That's " << (guessCount / ((double)nanoseconds / billion)) / 1000000 << "m/sec" << endl;

	return 0;
}

