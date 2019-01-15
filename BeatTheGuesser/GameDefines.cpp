#include "GameDefines.h"
#include <iostream>
#include <ctime>

//Core functions
int Random(int min, int max)
{
	return min + rand() % (max - min + 1);	//Need the extra "+ 1" at the end ot make it more accurate
}

void ClearBuffer() {
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

void WaitForKey() {
	ClearBuffer();
	std::cout << "Press ENTER" << std::endl;
	std::cin.get();
}

void RandomizeSeed()
{
	srand((unsigned int)time(nullptr));
}

void ClearScreen()
{
	system("cls");		//worse function ever
}

void NewLine() {
	std::cout << std::endl;
}
