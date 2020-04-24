#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateSquareDown(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, -length, 0), color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}


Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, length/2, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::Createbird(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	glm::vec3 head = glm::vec3(1, 1, 1);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(glm::vec3(40, 20, 0), color),
		VertexFormat(glm::vec3(80, 10, 0), color),
		VertexFormat(glm::vec3(110, 40, 0), color),
		VertexFormat(glm::vec3(130, 30, 0), color),
		VertexFormat(glm::vec3(110, 60, 0), color),
		VertexFormat(glm::vec3(80, 60, 0), color),
		VertexFormat(glm::vec3(60, 100, 0), color),
		VertexFormat(glm::vec3(0, 120, 0), color),
		VertexFormat(glm::vec3(40, 50, 0), color),
		VertexFormat(glm::vec3(10, 30, 0), color),

		VertexFormat(glm::vec3(110, 40, 0), head),
		VertexFormat(glm::vec3(130, 30, 0), head),
		VertexFormat(glm::vec3(110, 60, 0), head)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 
											11, 12,13,
											0, 1, 10,
											1, 9, 10,
											1, 2, 9,
											9, 2, 3,
											3, 4, 5,
											6, 3, 5,
											9, 3, 6,
											9, 6, 7,
											8, 9, 7,
											9, 10, 0
	};

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
		

	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::Createbirdfal(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	glm::vec3 head = glm::vec3(1, 1, 1);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(glm::vec3(40, 20, 0), color),
		VertexFormat(glm::vec3(80, 10, 0), color),
		VertexFormat(glm::vec3(110, 40, 0), color),
		VertexFormat(glm::vec3(130, 30, 0), color),
		VertexFormat(glm::vec3(110, 60, 0), color),
		VertexFormat(glm::vec3(80, 60, 0), color),
		VertexFormat(glm::vec3(40, 50, 0), color),
		VertexFormat(glm::vec3(10, 30, 0), color),
		VertexFormat(glm::vec3(30, -50, 0), color),
		VertexFormat(glm::vec3(80, -10, 0), color),

		VertexFormat(glm::vec3(110, 40, 0), head),
		VertexFormat(glm::vec3(130, 30, 0), head),
		VertexFormat(glm::vec3(110, 60, 0), head)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 11, 12, 13,
		                                    0, 1, 8,
											1, 7, 8,
											1, 2, 7,
											7, 2, 3,
											3, 4, 5,
											6, 3, 5,
											7, 3, 6,
											7, 8, 1,
											1, 9, 10,
		                                    1, 10, 2
											
	};

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);


	}

	square->InitFromData(vertices, indices);
	return square;
}
Mesh* Object2D::CreateBack(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	glm::vec3 grass = glm::vec3(.5, .5, 0);
	glm::vec3 sky = glm::vec3(.5, 1, 1);
	glm::vec3 mountin = glm::vec3(.75, .75, .75);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, grass),                   //0
		VertexFormat(glm::vec3(1280, 0, 0), grass),    //1
		VertexFormat(glm::vec3(1280, 200, 0), grass),  //2
		VertexFormat(glm::vec3(0, 200, 0), grass),     //3
		//=================pamant==================//
		VertexFormat(glm::vec3(1280, 200, 0), sky),  //4
		VertexFormat(glm::vec3(0, 200, 0), sky),     //5
		VertexFormat(glm::vec3(1280, 720, 0), sky),  //6
		VertexFormat(glm::vec3(0, 720, 0), sky),    //7
		//=================cer=====================//
		VertexFormat(glm::vec3(1280, 200, 0), mountin),  //8
		VertexFormat(glm::vec3(0, 200, 0), mountin),     //9
		VertexFormat(glm::vec3(0, 400, 0), mountin),     //10
		VertexFormat(glm::vec3(200, 500, 0), mountin),   //11
		VertexFormat(glm::vec3(300, 300, 0), mountin),   //12
		VertexFormat(glm::vec3(400, 550, 0), mountin),   //13
		VertexFormat(glm::vec3(580, 480, 0), mountin),   //14
		VertexFormat(glm::vec3(700, 560, 0), mountin),   //15
		VertexFormat(glm::vec3(1050, 400, 0), mountin),  //16
		VertexFormat(glm::vec3(1200, 500, 0), mountin),  //17
		VertexFormat(glm::vec3(1280, 300, 0), mountin)   //18
		//=================munte=====================//
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2,
											0, 2, 3,

											

											9, 8, 12,
											9, 12, 10,
											10, 12, 11,
											12, 14, 13,
											12, 16, 15,
											12, 8, 16,
											16, 8, 18,
		                                    16, 18, 17,

											5, 4, 6,
											5, 6, 7
	};

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);


	}

	square->InitFromData(vertices, indices);
	return square;
}