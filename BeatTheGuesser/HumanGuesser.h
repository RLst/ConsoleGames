#pragma once
#include "Guesser.h"
#include "GameDefines.h"

class HumanGuesser : public Guesser
{
public:
	HumanGuesser();
	~HumanGuesser();

	int guess(Range & guess);		//Prompts for a guess
};

