#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"


class Pile
{
public:

	glm::mat3 upPile;
	glm::mat3 dwPile;
	float trX;
	const float con = 4.5;
	float ran;
	bool pointTaken;

	

	Pile();
	~Pile();

	void getNewRand();
	
	

};

