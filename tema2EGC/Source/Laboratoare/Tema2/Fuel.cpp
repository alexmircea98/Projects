#include "Fuel.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Fuel::Fuel(float angle, float FuelHeight) {
	
	this->angle = angle;
	this->fuelHeight = FuelHeight;
	fuelLine = std::vector<glm::mat4>(5);
	for (int i = 0; i < 5; i++) {
		fuelLine.push_back(glm::mat4(1));
	}
	hit = std::vector<int>(10, 0);
	
	

}

Fuel::~Fuel() {}

float Fuel::getNewRand()
{	
		return (rand() % 15 + 10) / 10.0;
}

