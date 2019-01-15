#include "Engine.h"
#include "GameDefines.h"

#include <iostream>
#include <iomanip>


Engine::Engine(int highestGuess, int lowestGuess)
{
	m_runningState = true;					//App is running
	newGame(highestGuess, lowestGuess);		//Starts a new game
}

Engine::~Engine()
{
}



void Engine::resetMessage()		//Resets info message to default
{
	strcpy_s(m_infoMessage, MSG_DEFAULT);
}

void Engine::setMessage(const char * message)		//Update info message
{
	strcpy_s(m_infoMessage, message);
}

void Engine::drawMessage()
{
	std::cout << m_infoMessage << std::endl;
}



void Engine::newGame(int highestGuess, int lowestGuess)
{
	///Reset everything
	RandomizeSeed();

	displayTitle();

	m_CPUDifficulty = askDifficulty();			//Ask for difficulty

	m_numberToGuess = Random(lowestGuess, highestGuess);	//Set the number to guess

	m_winnerExists = false;						//Reset winner flag

	setMessage(MSG_DEFAULT);					//Set default message
	
	m_guessRange.low = lowestGuess;				//Set ranges
	m_guessRange.high = highestGuess;
	setLowRange(lowestGuess);					//CHECK
	setHighRange(highestGuess);		

	m_currentPlayer = (ePLAYER)Random(0, 1);	//Set a random player to start

	m_human.resetGuessAttempts();
	m_CPU.resetGuessAttempts();

	m_latestGuess = highestGuess + 1;			//Set it to be just out of range so 
						//that it doesn't show up the last result of the previous game
}

int Engine::askDifficulty()
{
	bool validInput = false;
	int input = 0;

	while (!validInput) {
		std::cout << "Enter CPU difficulty level" << std::endl;
		std::cout << "1. Beginner" << std::endl;
		std::cout << "2. Intermediate" << std::endl;
		std::cout << "3. Pro" << std::endl;
		std::cin >> input;

		//Check if the value is valid
		if (input >= 1 && input <= 3) {
			validInput = true;
		}
		else {
			std::cout << "Invalid input! Try again..." << std::endl;
			WaitForKey();
			ClearScreen();
		}
	}
	return input;
}

void Engine::endGame()		//Shutdown everything
{
	m_winnerExists = true;		//CHECK!
	m_runningState = false;
}



//Gets and Sets
int Engine::getLowRange()
{
	return m_guessRange.low;
}
void Engine::setLowRange(int lowRange)
{
	m_guessRange.low = lowRange;
}
int Engine::getHighRange()
{
	return m_guessRange.high;
}
void Engine::setHighRange(int highRange)
{
	m_guessRange.high = highRange;
}
int Engine::getGuessNumber()
{
	return m_latestGuess;
}
void Engine::setGuessNumber(int number)
{
	m_latestGuess = number;
}

ePLAYER Engine::getCurrentPlayer()
{
	return m_currentPlayer;
}



//Guesses
int Engine::getNextGuess()
{
	if (m_currentPlayer == CPU) {			//CPU guess
		m_CPU.incrementGuessAttempts();
		return m_CPU.guess(m_CPUDifficulty, m_guessRange);
	}
	else if (m_currentPlayer == PLAYER) {	//Human guess
		m_human.incrementGuessAttempts();
		return m_human.guess(m_guessRange);
	}
	return 0;
}

void Engine::processGuess()
{
	if (m_latestGuess > m_numberToGuess) {		//Guess was too high
		setHighRange(m_latestGuess - 1);		//Set new high range (minus 1
		setMessage(MSG_HIGH);					//Set too high message
		endPlayerTurn(m_currentPlayer);			//Swap players
	}
	else if (m_latestGuess < m_numberToGuess) {	//Guess was too low
		setLowRange(m_latestGuess + 1);
		setMessage(MSG_LOW);
		endPlayerTurn(m_currentPlayer);
	}
	else {										//Correct guess!
		declareWinner(m_currentPlayer);
	}
}

void Engine::declareWinner(ePLAYER winner)
{
	m_winnerExists = true;
	if (winner == CPU) {
		std::cout << "The computer guessed correctly with " << getGuessNumber() << " has beaten you," << std::endl;
		std::cout << "thus proving human's are inferior" << std::endl;
		std::cout << "Better luck next time buddy :P" << std::endl;
		WaitForKey();
	}
	else if (winner == PLAYER) {
		std::cout << "You guessed correctly with " << getGuessNumber() << " and have won!" << std::endl;
		std::cout << "Humans still have a chance... For now..." << std::endl;
		WaitForKey();
	}
}

bool Engine::winnerExists()
{
	return m_winnerExists;
}

void Engine::askPlayAgain()
{
	ClearScreen();
	NewLine();
	std::cout << "Your guess attempts: " << m_human.getGuessAttempts() << std::endl;
	std::cout << "CPU guess attempts: " << m_CPU.getGuessAttempts() << std::endl;
	std::cout << std::endl;
	std::cout << "Would you like to play again (Y/N)?";
	char input;
	std::cin >> input;
	switch (input) {
	case 'y':
	case 'Y':
		newGame(RANGE_MAX, RANGE_MIN);
		break;
	case 'n':
	case 'N':
		endGame();
		break;
	default:
		endGame();
		break;
	}
}

void Engine::endPlayerTurn(ePLAYER & currentPlayer)
{
	switch (currentPlayer) {
	case CPU:
		currentPlayer = PLAYER;
		break;
	case PLAYER:
		currentPlayer = CPU;
		break;
	default:
		break;
	}

	//*****   THIS LOGIC SEQUENCE DIDN'T WORK FOR SOME REASON
	//if (currentPlayer = CPU) {
	//	currentPlayer = PLAYER;
	//}
	//else if (currentPlayer = PLAYER) {
	//	currentPlayer = CPU;
	//}
	//currentPlayer = ((m_currentPlayer == CPU) ? PLAYER : CPU);
}

void Engine::displayTitle()
{
	ClearScreen();
	std::cout << "Guess the Number!" << std::endl;
	std::cout << "================" << std::endl << std::endl;
}

void Engine::displayInfo()
{
	std::cout << "Guess the number between " << RANGE_MIN << " and " << RANGE_MAX << std::endl;
	std::cout << std::endl;
	drawMessage();
}

void Engine::displayGuessingMatrix()
{
	//Draw the ranges as a grid
	int counter = RANGE_MIN;
	do {
		std::cout << "    ";
		for (int i = 0; i < DRAW_COLUMNS; ++i) {
			//If counter is not within the current guess range then print normally
			if (counter >= m_guessRange.low && counter <= m_guessRange.high) {
				std::cout << counter << std::setw(4);
			}
			else {
				std::cout << "X" << std::setw(4);
			}
			++counter;
			if (counter > RANGE_MAX)
				break;
		}
		std::cout << std::endl;
	} while (counter <= RANGE_MAX);
	std::cout << std::endl;
}

void Engine::displayHUD()
{
	//Display the previous guesses
	if (m_latestGuess > RANGE_MIN && m_latestGuess < RANGE_MAX) {	//Display if guess within bounds
		if (getCurrentPlayer() == CPU) {
			std::cout << "You guessed " << m_latestGuess << "..." << std::endl;
		}
		else if (getCurrentPlayer() == PLAYER) {
			std::cout << "The CPU guessed " << m_latestGuess << "..." << std::endl;
		}
	}

	//Display each player's guess attempts
	std::cout << "Human guesses: " << m_human.getGuessAttempts();
	std::cout << "\tCPU guesses: " << m_CPU.getGuessAttempts() << std::endl;
}


bool Engine::isRunning()
{
	return m_runningState;
}

void Engine::update()
{
	m_latestGuess = getNextGuess();

	processGuess();

	if (winnerExists()) {
		askPlayAgain();
	}
}

void Engine::draw()
{
	ClearScreen();

	displayInfo();
	
	displayGuessingMatrix();

	displayHUD();
}

