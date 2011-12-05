// PlayerObject implementation.

#include "PlayerObject.h"

#include <iostream>

using namespace std;


void PlayerObject :: bounceSphere(Sphere* otherSphere)
{
	//Make it explode here, update lives
	lives--;
	cout << "You died. Well done, nubcake." << endl;
	cout << "Freezing the game. Resuming in 3 seconds." << endl;
}