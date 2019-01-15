#pragma once
#include "Bullet.h"
#include "GameDefines.h"

class Enemy
{
private:
	Point2D posC;
	int valueC;
	bool aliveC = false;
	bool explodedC = false;

public:
	Enemy();
	~Enemy();

	//Gets and sets
	inline int getPositionX() { return posC.x; }
	inline int getPositionY() { return posC.y; }
	inline Point2D getPosition() { return posC; }

	void setPositionX(int posx) { posC.x = posx; }
	//void setPosition
	
	//draws
	void draw();
	void explode();

	//updates
	int getValue() { return valueC; }
	void setValue(int value);

	bool justBeenHit();
	//void setAsShot();
	void setAsExploded();
	bool isShot(Bullet & bullet);		//const because bullet should be read only; NOTE: const doesn't work!!

	void spawn();
	void kill();
	bool isAlive() { return aliveC; }
	
};

