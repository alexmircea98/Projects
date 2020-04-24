#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <iostream>
#include <math.h>

namespace Object3D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateBody(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateBlade(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateCloud(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateFuel(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateObstacle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	std::vector<glm::vec3> genSPH(float r, int numLat, int numLong);
	Mesh* CreateSea(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateCap(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateHeart(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateBox(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
}

