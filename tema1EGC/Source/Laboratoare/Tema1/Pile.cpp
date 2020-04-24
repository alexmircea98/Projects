#include "Pile.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Pile::Pile() {
	
	upPile = glm::mat3(1) * Transform2D::Translate(1260, 360);
	dwPile = glm::mat3(1) * Transform2D::Translate(1280, 0);
	trX = 0;
	ran = 1;
	getNewRand();
	

}

Pile::~Pile() {}

void Pile::getNewRand()
{	
	
	ran = (float)(rand() % 35 + 1)/10.0;
	pointTaken = 0;
	
}
