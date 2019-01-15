#pragma once
#include "Guesser.h"
#include "GameDefines.h"

class CPUGuesser : public Guesser
{
	int linearGuess(const Range & range);
	int randomGuess(const Range & range);
	int binaryGuess(const Range & range);
	//int interpSearch(Range range);	//maybe some other time

public:
	CPUGuesser();
	~CPUGuesser();

	int guess(const int & CPUSkillLevel, const Range & range);		//The CPU will guess based on difficulty level
																	//1 = linear, 2 = random, 3 = binary

};