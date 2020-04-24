#include "Obstacle.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Obstacle::Obstacle(float angle, float cloudHeight) {
	
	this->angle = angle;
	this->obsHeight = cloudHeight;
	obs = glm::mat4(1);
	hit = false;
}

Obstacle::~Obstacle() {}

float Obstacle::getNewRand()
{	
		return (rand() % 15 + 10) / 10.0;
}

