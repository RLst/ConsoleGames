#pragma once
#include "GameDefines.h"
#include "HumanGuesser.h"
#include "CPUGuesser.h"
#include <cstdlib>

class Engine
{
	bool m_runningState;
	int m_CPUDifficulty;				//1 = linear, 2 = random, 3 = binary
	int m_numberToGuess;					//The number the player's are trying to guess
	
	int m_latestGuess;						//The latest guess
	//int m_guessLog[RANGE_MAX];
	bool m_winnerExists;			//DEFAULT = false;					
	char m_infoMessage[50];

	Range m_guessRange;				//The current range of the guesses
	ePLAYER m_currentPlayer;				//0 = CPU, 1 = Player

	HumanGuesser m_human;
	CPUGuesser m_CPU;

	//Gets and Sets
	int getLowRange();
	void setLowRange(int lowRange);
	int getHighRange();
	void setHighRange(int highRange);
	int getGuessNumber();
	void setGuessNumber(int number);
	ePLAYER getCurrentPlayer();

	//Messages
	void resetMessage();
	void setMessage(const char* message);
	void drawMessage();

	//Inits
	void newGame(int highestGuess, int lowestGuess);
	int askDifficulty();
	void endGame();

	//Guessing game
	int getNextGuess();
	void declareWinner(ePLAYER player);
	bool winnerExists();
	void askPlayAgain();
	
	//Updates
	void processGuess();		//Adjusts guess range accordingly or declare winner
	void endPlayerTurn(ePLAYER & currentPlayer);

	//Draw
	void displayTitle();
	void displayInfo();
	void displayGuessingMatrix();
	void displayHUD();

public:
	Engine(int highestGuess, int lowestGuess);
	~Engine();

	bool isRunning();
	void update();
	void draw();
};