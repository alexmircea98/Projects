#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Core/Engine.h>
#include "Transform3D.h"
#include "Object3D.h"


class Fuel
{
public:
	
	std::vector<glm::mat4> fuelLine;
	std::vector<int> hit;
	float angle;
	float fuelHeight;

	

	Fuel(float angle, float fuelHeight);
	~Fuel();

	float getNewRand();
	

};

