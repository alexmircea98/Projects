#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Core/Engine.h>
#include "Transform3D.h"
#include "Object3D.h"


class Cloud
{
public:

	std::vector<glm::mat4> cloud;
	float angle;
	float cloudHeight;
	float ran[3];


	

	Cloud(float angle, float cloudHeight);
	~Cloud();

	float getNewRand();
	void  getNewSize();
	

};

