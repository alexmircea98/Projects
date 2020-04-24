#include "Cloud.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Cloud::Cloud(float angle, float cloudHeight) {
	
	this->angle = angle;
	this->cloudHeight = cloudHeight;
	cloud = std::vector<glm::mat4>(3);
	for (int i = 0; i < 3; i++) {
		cloud.push_back(glm::mat4(1));
	}
	this->ran[0] = getNewRand();
	this->ran[1] = getNewRand();
	this->ran[2] = getNewRand();
	

}

Cloud::~Cloud() {}

float Cloud::getNewRand()
{	
		return (rand() % 15 + 10) / 10.0;
}

void Cloud::getNewSize()
{
	this->ran[0] = getNewRand();
	this->ran[1] = getNewRand();
	this->ran[2] = getNewRand();
}
