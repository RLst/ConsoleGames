#pragma once
#include "GameDefines.h"
#include "Bullet.h"

class Ship
{
	///int x, y;	//Don't need y because the ship can't move forward or back?
	Point2D posC;

public:
	Ship();
	~Ship();

	//Gets and sets
	int getPositionX();
	int getPositionY();
	Point2D getPosition();

	//Draws
	void drawShip();

	//Updates
	void moveLeft();
	void moveRight();

	void shoot(Bullet &bullet);

};

