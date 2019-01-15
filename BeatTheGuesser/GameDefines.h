#pragma once

//Function declarations
int Random(int min, int max);
void ClearBuffer();
void WaitForKey();
void RandomizeSeed();
void ClearScreen();
void NewLine();

const int RANGE_MIN = 1;
const int RANGE_MAX = 250;
const int RANGE_AMOUNT = RANGE_MAX - RANGE_MIN;

const int DRAW_COLUMNS = 17;
//const int DRAW_HEIGHT = ;

//Messages
const char* const MSG_DEFAULT = "GUESS THE NUMBER!";
const char* const MSG_HIGH = "PREVIOUS GUESS WAS TOO HIGH";
const char* const MSG_LOW = "PREVIOUS GUESS WAS TOO LOW";

//Enums
enum ePLAYER {
	CPU,
	PLAYER
};

//Range struct
class Range {
public:
	int low;
	int high;
};

