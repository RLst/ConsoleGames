#include "GameDefines.h"
#include "Engine.h"
#include "Guesser.h"
#include "HumanGuesser.h"
#include "CPUGuesser.h"

int main() {

	RandomizeSeed();
	//Initialise game engine
	Engine Game(RANGE_MAX, RANGE_MIN);

	while (Game.isRunning()) {		//Main game loop
		Game.draw();
		Game.update();
	}

	return 0;
}