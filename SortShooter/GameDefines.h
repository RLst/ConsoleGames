#pragma once

//Printing constants; based on blocks of chars 5 wide
const char EMPTY_BLOCK[] = "     ";

const char SHIP_TOP[] = "  A  ";
const char SHIP_BOTTOM[] = " <H> ";

const char BULLET[] = "  *  ";
const char EXPLOSION[] = "#####";

//const char ENEMY_LEFT[] = " (";
//const char ENEMY_RIGHT[] = ") ";
//const char ENEMY_ONEDIGIT - " "

//Messages
const char TAB = '\t';
const char MSG_DEFAULT[] = "Objective: Shoot enemies LOW to HIGH";
const char MSG_WIN[] = "Nice Shot!!";
const char MSG_LOSE[] = "Incorrect enemy shot :(";
//const char MSG_NEXT_LEVEL[] = "Nice sorting! Next level...";

//Enemies
const int MAX_ENEMIES = 5;
const int TOTAL_ENEMY_ROUNDS = 5;

//Bullets
const int MAX_BULLETS = 1;	//NOTE: only one works at the moment
const int BULLET_SPEED = 1;
const int BULLET_ZONE_HEIGHT = 13;

//Core
const int MIN_VALUE = 1;
const int MAX_VALUE = 99;
const int SCREEN_WIDTH = MAX_ENEMIES;
//const int SCREEN_HEIGHT = 5;	//NOTE: required?

struct Point2D {
	int x, y;

	//== OPERATOR OVERLOAD
	bool operator == (Point2D & input) {
		return x == input.x && y == input.y;
	}
};
