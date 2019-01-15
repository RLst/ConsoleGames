#include <iostream>
#include "Game.h"
#include "Ship.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameDefines.h"
#include <time.h>


int main() {
	RandomizeSeed();
	Game game(MAX_ENEMIES, MAX_BULLETS);	//default bullets = 1

	while (game.isRunning()) {
		game.update();
		game.draw();
	}
	return 0;
}



