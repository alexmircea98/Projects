#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Core/Engine.h>
#include "Transform3D.h"
#include "Object3D.h"


class Obstacle
{
public:

	glm::mat4 obs;
	float angle;
	float obsHeight;
	bool hit;

	

	Obstacle(float angle, float cloudHeight);
	~Obstacle();

	float getNewRand();
	

};

