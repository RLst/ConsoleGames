#include "Enemy.h"
#include <iostream>
#include "GameDefines.h"


Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}


void Enemy::draw()	//just the enemy
{
	//std::cout << ENEMY_LEFT << this->getValue() << ENEMY_RIGHT;
	int value = this->getValue();
	//One digit
	if (value >= 0 && value < 10)
		std::cout << " (" << value << ") ";
	//Two digits
	else if (value >= 10 && value < 100)
		std::cout << "(" << value << ") ";
	//Three digits
	else if (value >= 100 && value < 1000)
		std::cout << "(" << value << ")";
	//default
	else
		std::cout << "!@#$%";
}

void Enemy::explode()
{
	std::cout << EXPLOSION;
	this->explodedC = true;
}

void Enemy::setValue(int value)
{
	this->valueC = value;
}

bool Enemy::isShot(Bullet &bullet)
{
	//Check bullet is live
	//if (bullet.isAlive()) {
		//Check correct lane
		if (this->getPositionX() == bullet.getPositionX()) {

			//Check if bullet has reached the end ie. hit the enemy
			if (bullet.getPositionY() < 0) {
				return true;
			}
		}
	//}
	return false;
}

bool Enemy::justBeenHit()
{
	//If the enemy has just been hit then it hasn't been exploded
	return (!explodedC);
}

//void Enemy::setAsShot()
//{
//	this->exploded_ = false;
//	this->alive_ = false;
//}

void Enemy::setAsExploded()
{
	this->explodedC = true;
}

void Enemy::spawn()
{
	this->aliveC = true;
	this->explodedC = false;
}

void Enemy::kill()
{
	//This should get called after the explosion animation
	this->aliveC = false;
}