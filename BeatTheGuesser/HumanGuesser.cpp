#include "HumanGuesser.h"

#include <iostream>

HumanGuesser::HumanGuesser()
{
}
HumanGuesser::~HumanGuesser()
{
}

int HumanGuesser::guess(Range & guessRange)	//Gets a guess from the human player
{
	int input = 0;
	bool validGuess = false;

	while (!validGuess) {
		std::cout << "Enter your guess: ";
		std::cin >> input;

		//Deny if out of range
		if (input < guessRange.low || input > guessRange.high) {
			std::cout << "Out of range! Try again...";
			std::cout << std::endl;
		}
		else
			validGuess = true;
	}
	return input;
}
