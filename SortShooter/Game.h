#pragma once
#include "GameDefines.h"
#include "Ship.h"
#include "Enemy.h"
#include "Bullet.h"

//Core functions
int Random(int min, int max);
void ClearBuffer();
void WaitForKey();
void NewLine();
void RandomizeSeed();

class Game
{

private:
	Ship m_player;
	Enemy *m_enemy;		//Potential for many enemies; default = 5
	int *m_checklist;	//Holds sorted list
	Bullet *m_bullet;		//Potential for many bullets; default = 1

	bool gameOver_;

	int score_;
	int hiScore_;

	int currentLevel_;
	bool levelState_;	//true = currently running, false = not running

	unsigned int enemyKilled_;	//Once it reaches max

	char m_infoMessage[50];		//Holds the string to be displayed up top

	///NOTE: Should these functions be private?; they are called by core funcs draw & update
	//draws
	void drawInfo();
	void drawEnemies();
	void drawBullets();

	void drawMessage();	
	void setMessage(const char message[]);
	void resetMessage();

	//updates
	void executeCommand();
	void updateBullets();
	void updateKills();
	void updateLevels();

	//Levels
	void startNewLevel();
	void endLevel();

	//Enemy
	int enemyKillCount();
	bool isCorrectKill(Enemy &enemyJustKilled);

	//Sort functions
	void sortChecklist(int *checkList/*, bool ascending = true*/);
	void merge(int sortArr[], int left, int mid, int right);
	void mergeSort(int sortingArray[], int start, int end);
	void swap(int &a, int &b);
	void bubbleSort(int sortingArray[], int arraySize);

	//debug
	void dbgPrintChecklist();

	//Gets and sets
	int getCurrentLevel() { return currentLevel_; }		//redundant
	bool getLevelState() { return levelState_; }	//NOTE: maybe redundant
	inline void setLevelState(bool isLevelRunning) { levelState_ = isLevelRunning; }	//NOTE: may be redundant

	inline int getScore() { return score_; }
	inline void scoreUp() { score_++; }
	inline void scoreUp(int increase) { score_ += increase; }
	inline void scoreDown() { score_--; }
	inline void scoreDown(int decrease) { score_ -= decrease; }

public:
	Game(int numberOfEnemies = MAX_ENEMIES, int numberOfBullets = MAX_BULLETS);
	~Game();

	//Core
	bool isRunning() { return (!gameOver_); }
	void draw();
	void update();
	void endGame();

};

