#include "Bullet.h"
#include <iostream>


Bullet::Bullet()
{
	posC = { 10, 10 };
	aliveC = false;
}
Bullet::~Bullet()
{
}


void Bullet::draw()
{
	//Only draw the bullet
	//NOTE: this can be done easily since it's on the one line
	std::cout << BULLET;
}

void Bullet::start(Point2D position)
{
	//Set bullet position...
	this->posC.x = position.x;
	this->posC.y = BULLET_ZONE_HEIGHT;

	//and make alive
	this->aliveC = true;
}

void Bullet::move()
{
	this->posC.y--;
}

void Bullet::move(int dist)		//Overload
{
	this->posC.y -= dist;
}

bool Bullet::isAlive()
{
	return aliveC;
}

void Bullet::kill()
{
	aliveC = false;
}
