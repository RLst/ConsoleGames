#include "CPUGuesser.h"
#include <iostream>

CPUGuesser::CPUGuesser()
{
}
CPUGuesser::~CPUGuesser()
{
}

int CPUGuesser::linearGuess(const Range & range)
{
	//Stupid search; just return the next one up or down
	if (Random(0, 1) == 0) {
		//Guess the next one up
		return range.low;
	}
	else {
		return range.high;
	}
}

int CPUGuesser::randomGuess(const Range & range)
{
	//Ok search; Returns a random number in between the possible range
	return Random(range.low, range.high);
}

int CPUGuesser::binaryGuess(const Range & range)
{
	//Smart search; Returns the middle of the range
	return (range.high + range.low)/2;		
	//NOTE: Could this potentially never be able to guess the final number due to rounding issues???
}


int CPUGuesser::guess(const int & CPUSkillLevel, const Range & range)
{
	//Display what's going on
	std::cout << "The CPU is making a guess..." << std::endl;
	WaitForKey();

	//Return a guess based on difficulty setting
	switch (CPUSkillLevel) {
	case 1:		//Low
		return linearGuess(range);
		break;
	case 2:		//OK
		return randomGuess(range);
		break;
	case 3:		//High
		return binaryGuess(range);
		break;
	default:
		return 0;
		break;
	}
}
