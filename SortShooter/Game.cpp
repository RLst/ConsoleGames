#include "Game.h"
#include "GameDefines.h"
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
//#include "ScreenBuffer.h"

//Core functions
int Random(int min, int max) {
	return (min + rand() % (max - min));
}
void ClearBuffer() {
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}
void WaitForKey() {
	ClearBuffer();
	std::cout << std::endl;
	std::cout << "Press enter..." << std::endl;
	std::cin.get();
}
void NewLine() {
	std::cout << std::endl;
}
void RandomizeSeed()
{
	srand((unsigned int)time(nullptr));
}

Game::Game(int numberOfEnemies, int numberOfBullets)
{
	//Create enemy arrays :)
	m_enemy = new Enemy[numberOfEnemies];

	//Create and clear checklist
	m_checklist = new int[numberOfEnemies];
	for (int i = 0; i < numberOfEnemies; i++) {
		m_checklist[i] = 0;
	}

	//Create bullet arrays
	m_bullet = new Bullet[numberOfBullets];

	//Resets
	levelState_ = false;	//No levels are running
	currentLevel_ = 0;		//Level 1
	//enemyKilledValueToCheck = NULL;
	this->endLevel();

	gameOver_ = false;

	score_ = 0;
	hiScore_ = 0;
}

Game::~Game()
{
	//Important to deallocate memory!!
	delete[] m_enemy;
	delete[] m_checklist;
	delete[] m_bullet;
}


void Game::drawInfo()
{
	std::cout << "\tSORT SHOOTER" << std::endl;
	std::cout << "SCORE: " << getScore() << "\t" << "LEVEL: " << getCurrentLevel() << std::endl;
	//std::cout << "   [Shoot LOW to HIGH]" << std::endl;		//"Nice shot!", "Incorrect order!"
	std::cout << this->m_infoMessage << std::endl;
	std::cout << std::endl;
}

void Game::drawEnemies()	
{
	//Draw enemies...
	for (int i = 0; i < MAX_ENEMIES; i++) {

		//Draw normally if alive
		if (m_enemy[i].isAlive() == true) {
			m_enemy[i].draw();
		}
		//Draw exploding if just hit
		else if (m_enemy[i].justBeenHit()) {
			m_enemy[i].explode();	//blow up enemy
		}
		else if (m_enemy[i].isAlive() == false) {	//Don't draw if enemy dead/non-exist
			std::cout << EMPTY_BLOCK;
		}
	}
	std::cout << std::endl;
}

void Game::drawBullets()
{
	//This draws the entire bullet zone in between the enemies and player
	for (int y = 0; y < BULLET_ZONE_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			for (int i = 0; i < MAX_BULLETS; i++) {
				//If bullet is alive...
				if (m_bullet[i].isAlive()) {
					Point2D drawPosition = { x, y };	//NOTE: need to learn operator overloading
					//and is in the correct position
					if (m_bullet[i].getPosition() == drawPosition) {
						m_bullet[i].draw();
					}
				}
			}
			//Otherwise draw a blank
			std::cout << EMPTY_BLOCK;
		}
		std::cout << std::endl;
	}

}

void Game::drawMessage()
{
	std::cout << this->m_infoMessage;
}

void Game::setMessage(const char message[])
{
	strcpy_s(this->m_infoMessage, message);
}

void Game::resetMessage()
{
	strcpy_s(this->m_infoMessage, MSG_DEFAULT);
}


/////////////////// UPDATES //////////////////

void Game::updateBullets()
{
	//Move bullets
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (m_bullet[i].isAlive()) {
			m_bullet[i].move(BULLET_SPEED);
		}
	}
}

int Game::enemyKillCount()
{
	//If all enemies are killed means you won the level
	int killCount = 0;
	for (int e = 0; e < MAX_ENEMIES; e++) {
		if (m_enemy[e].isAlive() == false) {
			killCount++;
		}
	}
	return killCount;
}

void Game::updateKills()
{
	//Kill enemy if bullet hits
	for (int e = 0; e < MAX_ENEMIES; e++) {
		for (int b = 0; b < MAX_BULLETS; b++) {
			if (m_bullet[b].isAlive() && m_enemy[e].isAlive()) {	//Both have to be alive!
				if (m_enemy[e].isShot(m_bullet[b])) {
					//kill enemy...
					m_enemy[e].kill();
					//and the bullet too
					m_bullet[b].kill();
					//Record the sorted value and compare with the checklist etc.
					//enemyKilledValueToCheck = m_enemy[e].getValue();

					//NOTE: Maybe try checking for correct kill right after the being shot
					if (isCorrectKill(m_enemy[e])) {	//The kill is correct
						this->scoreUp(5);		//Score up and continue as usual
						this->setMessage(MSG_WIN);
					}
					else {	//Wrong kill...
						this->scoreDown(20);		//Penalise
						this->endLevel();			//and end the level
						this->setMessage(MSG_LOSE);
					}
				}
			}
		}
	}
}


bool Game::isCorrectKill(Enemy &enemyJustKilled)
{
	if (enemyJustKilled.getValue() == this->m_checklist[enemyKillCount()-1]) {
		return true;	//Correct enemy hit
	}
	else {
		return false;	//Incorrect enemy killed
	}
}

////////////////// SORTING FUNCTIONS ////////////////
void Game::sortChecklist(int *checkList/*, bool ascending = true*/)	//NIL second parameter passed defaults to ascending sort
{
	for (int i = 0; i < MAX_ENEMIES; i++) {
		m_checklist[i] = m_enemy[i].getValue();			//put enemy values into checklist...
	}
	//this->mergeSort(m_checklist, 0, MAX_ENEMIES);		//NOTE: Merge sort algo is a bit buggy for some reason
	this->bubbleSort(m_checklist, MAX_ENEMIES);			//and sort
}

void Game::dbgPrintChecklist()
{
	for (int i = 0; i < MAX_ENEMIES; i++) {
		std::cout << m_checklist[i] << ", ";
	}
	std::cout << std::endl;
}

//////////////// MERGE SORT /////////////////////
void Game::merge(int sortArr[], int left, int mid, int right)
{	//NOTE: Buggy
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	//Create temp dynamic arrays
	int *L = new int[n1];
	int *R = new int[n2];

	//Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = sortArr[left + i];
	for (j = 0; j < n2; j++)
		R[j] = sortArr[mid + 1 + j];

	//Merge the temp arrays back into sortArr[left...right]
	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			sortArr[k] = L[i];
			i++;
		}
		else {
			sortArr[k] = R[j];
			j++;
		}
		k++;
	}

	//Copy the remaining elements of L[], if there are any
	while (i < n1) {
		sortArr[k] = L[i];
		i++; k++;
	}

	//Copy the remaining elements of R[], if there are any
	while (j < n2) {
		sortArr[k] = R[j];
		j++; k++;
	}

	//Delete the dynamic arrays after use
	delete[] L;
	delete[] R;

}
void Game::mergeSort(int sortingArray[], int start, int end)
{	//NOTE: Buggy
	if (start < end) {
		int mid = (start + end) / 2;
		mergeSort(sortingArray, start, mid);
		mergeSort(sortingArray, mid+1, end);
		merge(sortingArray, start, mid, end);
	}
}

//////////////// BUBBLE SORT /////////////////
void Game::swap(int & a, int & b)
{
	int temp = b;
	b = a;
	a = temp;
}
void Game::bubbleSort(int sortingArray[], int arraySize)
{
	for (int i = 0; i < arraySize; i++) {
		for (int j = 0; j < arraySize - 1; j++) {
			//if number is higher then swap (ascending sort)
			if (sortingArray[j] > sortingArray[j + 1]) {
				this->swap(sortingArray[j], sortingArray[j + 1]);
			}
		}
	}
}
//////////////////////////////////////////////////

void Game::executeCommand()
{
	if (_kbhit()) {

		char command = 0;
		command = _getch();

		switch (command) {
		case 'a':
			m_player.moveLeft();
			break;
		case 'd':
			m_player.moveRight();
			break;
		case 'j':	
		case 32:	//or space bar
			m_player.shoot(*m_bullet);
			break;

		case '/':
			this->endGame();
			break;
		default:
			break;
		}
	}
}

void Game::startNewLevel()
{
	levelState_ = true;
	//Spawn enemies and...
	for (int x = 0; x < MAX_ENEMIES; x++) {
		m_enemy[x].spawn();
		m_enemy[x].setValue(Random(MIN_VALUE, MAX_VALUE));
		m_enemy[x].setPositionX(x);
		this->setMessage(MSG_DEFAULT);
	}
}


void Game::updateLevels()
{

	//if no level is currently running...
	if (this->getLevelState() == false) {
		this->currentLevel_++;

		//if max level reached...
		if (this->getCurrentLevel() > TOTAL_ENEMY_ROUNDS) {
			this->endGame();
		}
		else {	//otherwise start a new level
			this->startNewLevel();
			//Sort values and put into checklist HERE
			this->sortChecklist(m_checklist);
		}
	}

	//if you sucessfully shot down all the enemies...
	if (enemyKillCount() == MAX_ENEMIES) {
		endLevel();		//Shut down current level
		scoreUp(10);		//and get points
	}
}


void Game::endLevel()		//Shuts down the level so that it's ready for the next level
{
	//Reset
	this->levelState_ = false;
	//Enemies
	for (int e = 0; e < MAX_ENEMIES; ++e) {
		m_enemy[e].kill();
	}
	//Bullets
	for (int b = 0; b < MAX_BULLETS; b++) {
		m_bullet[b].kill();
	}
}


///////////////////////////////////// CORE

void Game::update()
{
	//Control enemy rounds
	updateLevels();

	//Player; move player, shoot bullets
	executeCommand();

	//Bullets; move bullets
	updateBullets();

	//Check for hits, kills enemy and check correct kill
	updateKills();
}

void Game::draw()
{
	system("cls");
	//cls();

	//Draw info; scores, instructions, etc
	drawInfo();

	//Draw enemies
	drawEnemies();

	//Draw bullets
	drawBullets();

	//Draw ship
	m_player.drawShip();

	//Debugs
	//for (int i = 0; i < MAX_ENEMIES; i++) {
	//	std::cout << m_enemy[i].isAlive() << ", ";
	//}
	//std::cout << std::endl;
	//for (int i = 0; i < MAX_ENEMIES; i++) {
	//	std::cout << m_enemy[i].getValue() << ", ";
	//}
	//std::cout << std::endl;
	//dbgPrintChecklist();
	//std::cout << std::endl;

}

void Game::endGame()
{
	this->gameOver_ = true;
	std::cout << std::endl;
	std::cout << "\tGAME OVER" << std::endl;
	std::cout << "Your final score is " << this->score_ << std::endl;
	WaitForKey();
}
