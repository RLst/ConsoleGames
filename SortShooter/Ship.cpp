#include "Ship.h"
#include "GameDefines.h"
#include <iostream>
#include <iomanip>

Ship::Ship()
{
	this->posC.x = SCREEN_WIDTH / 2;		//Ship starts off in the middle
}
Ship::~Ship()
{
}


void Ship::drawShip()
{
	//Draw top of ship
	for (int i = 0; i < SCREEN_WIDTH; i++) {

		//Point2D pos = this->getPosition(); NOTE: Don't need to do this when I can access the privates directly

		if (posC.x == i) {
			std::cout << SHIP_TOP << std::endl;
			break;
		}
		else {
			std::cout << EMPTY_BLOCK;
		}
	}

	//Draw bottom
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		if (posC.x == i) {
			std::cout << SHIP_BOTTOM << std::endl;
			break;
		}
		else {
			std::cout << EMPTY_BLOCK;
		}
	}
}

void Ship::moveLeft()
{
	posC.x--;
	//Limit movement
	if (posC.x < 0)
		posC.x = 0;
}

void Ship::moveRight()
{
	posC.x++;
	//Limit movement
	if (posC.x >= SCREEN_WIDTH)
		posC.x = SCREEN_WIDTH-1;
}

void Ship::shoot(Bullet &bullet)
{
	//Send position of the ship to start the bullet
	bullet.start(this->getPosition());
}

int Ship::getPositionX()
{
	return posC.x;
}

int Ship::getPositionY()
{
	return posC.y;
}

Point2D Ship::getPosition()
{
	return posC;
}