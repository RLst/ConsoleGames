#pragma once
#include "GameDefines.h"


class Bullet
{
private:
	Point2D posC;
	bool aliveC;

public:
	Bullet();
	~Bullet();

	//Gets and sets
	int getPositionX() { return posC.x; }
	int getPositionY() { return posC.y; }
	Point2D getPosition() { return posC; }
	void setPosition(Point2D pos) { this->posC = pos; }	//should i have this?

	//draws
	void draw();

	//updates
	void start(Point2D position);
	
	void move();
	void move(int dist);

	bool isAlive();
	void kill();

	//operators
	
};

