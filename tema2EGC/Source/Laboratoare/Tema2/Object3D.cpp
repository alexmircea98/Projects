#include "Object3D.h"

#include <Core/Engine.h>
#include <math.h>



Mesh* Object3D::CreateBody(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	glm::vec3 white = glm::vec3(.8, .8, .8);
	glm::vec3 black = glm::vec3(0, 0, 0);
	glm::vec3  norm = glm::vec3(0, 0, .5);
	

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0 * d, -1 * d, -1 * d),  glm::vec3(0, 0, 0), color + norm),
		VertexFormat(glm::vec3(0 * d, -1 * d, 1 * d),  glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0 * d, 1 * d, 1 * d),  glm::vec3(0, 0, 0), color + norm),
		VertexFormat(glm::vec3(0 * d, 1 * d, -1 * d),  glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(5 * d, -2 * d, -2 * d),  glm::vec3(0, 0, 0), color + norm),
		VertexFormat(glm::vec3(5 * d, -2 * d, 2 * d),  glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(5 * d, 2 * d, 2 * d),  glm::vec3(0, 0, 0), color + norm),
		VertexFormat(glm::vec3(5 * d, 2 * d, -2 * d),  glm::vec3(0, 0, 0), color),

		VertexFormat(glm::vec3(5 * d, -2 * d, -2 * d),glm::vec3(0, 0, 0), white),
		VertexFormat(glm::vec3(5 * d, -2 * d, 2 * d),glm::vec3(0, 0, 0), white),
		VertexFormat(glm::vec3(5 * d, 2 * d, 2 * d), glm::vec3(0, 0, 0), white),
		VertexFormat(glm::vec3(5 * d, 2 * d, -2 * d), glm::vec3(0, 0, 0), white),
		VertexFormat(glm::vec3(8 * d, -2 * d, -2 * d), glm::vec3(0, 0, 0), white),
		VertexFormat(glm::vec3(8 * d, -2 * d, 2 * d), glm::vec3(0, 0, 0), white),
		VertexFormat(glm::vec3(8 * d, 2 * d, 2 * d), glm::vec3(0, 0, 0), white),
		VertexFormat(glm::vec3(8 * d, 2 * d, -2 * d), glm::vec3(0, 0, 0), white),

		VertexFormat(glm::vec3(-1 * d, 1 * d, -0.3 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1 * d, 1 * d, 0.3 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1 * d, 2 * d, 0.3 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1 * d, 2 * d, -0.3 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0.3 * d, 1 * d, -0.3 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0.3 * d, 1 * d, 0.3 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0.3 * d, 2 * d, 0.3 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0.3 * d, 2 * d, -0.3 * d), glm::vec3(0, 0, 0), color),

		VertexFormat(glm::vec3(2.5 * d, 1 * d, -5 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(2.5 * d, 1 * d, 5 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(2.5 * d, 1.5 * d, 5 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(2.5 * d, 1.5 * d, -5 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(5 * d, 1 * d, -5 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(5 * d, 1 * d, 5 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(5 * d, 1.5 * d, 5 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(5 * d, 1.5 * d, -5 * d), glm::vec3(0, 0, 0), color),

		VertexFormat(glm::vec3(8 * d, -.5 * d, -.5 * d),glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8 * d, -.5 * d, .5 * d),glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8 * d, .5 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8 * d, .5 * d, -.5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, -.5 * d, -.5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, -.5 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, .5 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, .5 * d, -.5 * d), glm::vec3(0, 0, 0), black),

		VertexFormat(glm::vec3(8.5 * d, -2 * d, -.5 * d),glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, -2 * d, .5 * d),glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, 2 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, 2 * d, -.5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, -2 * d, -.5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, -2 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, 2 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, 2 * d, -.5 * d), glm::vec3(0, 0, 0), black),

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 
		//body
		0, 4, 3,
		4, 7, 3,
		3, 7, 6,
		3, 6, 2,
		4, 6, 7,
		4, 5, 6,
		2, 6, 1,
		6, 5, 1,
		0, 1, 4,
		4, 1, 5,
		3, 2, 1,
		0, 3, 1,
		//white head
		8, 12, 11, 12, 15, 11, 11, 15, 14, 11, 14, 10, 12, 14, 15, 12, 13, 14, 10, 14, 9, 14, 13, 9, 8, 9, 12, 12, 9, 13, 11, 10, 9, 8, 11, 9,
		//tail
		16, 20, 19, 20, 23, 19, 19, 23, 22, 19, 22, 18, 20, 22, 23, 20, 21, 22, 18, 22, 17, 22, 21, 17, 16, 17, 20, 20, 17, 21, 19, 18, 17, 16, 19, 17,
		//wings
		24, 28, 27, 28, 31, 27, 27, 31, 30, 27, 30, 26, 28, 30, 31, 28, 29, 30, 26, 30, 25, 30, 29, 25, 24, 25, 28, 28, 25, 29, 27, 26, 25, 24, 27, 25,
		//rotor
		32, 36, 35, 36, 39, 35, 35, 39, 38, 35, 38, 34, 36, 38, 39, 36, 37, 38, 34, 38, 33, 38, 37, 33, 32, 33, 36, 36, 33, 37, 35, 34, 33, 32, 35, 33,
		//blade
		//40, 44, 43, 44, 47, 43, 43, 47, 46, 43, 46, 42, 44, 46, 47, 44, 45, 46, 42, 46, 41, 46, 45, 41, 40, 41, 44, 44, 41, 45, 43, 42, 41, 40, 43, 41
	
	
	
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

Mesh* Object3D::CreateBlade(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{
	
	glm::vec3 black = glm::vec3(0, 0, 0);


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(8.5 * d, -2 * d, -.5 * d),glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, -2 * d, .5 * d),glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, 2 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.5 * d, 2 * d, -.5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, -2 * d, -.5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, -2 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, 2 * d, .5 * d), glm::vec3(0, 0, 0), black),
		VertexFormat(glm::vec3(8.6 * d, 2 * d, -.5 * d), glm::vec3(0, 0, 0), black),

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = {
		
		//blade
		0, 4, 3,
		4, 7, 3,
		3, 7, 6,
		3, 6, 2,
		4, 6, 7,
		4, 5, 6,
		2, 6, 1,
		6, 5, 1,
		0, 1, 4,
		4, 1, 5,
		3, 2, 1,
		0, 3, 1,

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

Mesh* Object3D::CreateCloud(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{

	glm::vec3 whitey = glm::vec3(0.98, 0.819, 0.643);


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-1 * d, -1 * d, -1 * d),glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(-1 * d, -1 * d, 1 * d),glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(-1 * d, 1 * d, 1 * d), glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(-1 * d, 1 * d, -1 * d), glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(1 * d, -1 * d, -1 * d), glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(1 * d, -1 * d, 1 * d), glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(1 * d, 1 * d, 1 * d), glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(1 * d, 1 * d, -1 * d), glm::vec3(0, 0, 0), whitey),

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = {

		//cloud
		0, 4, 3, 4, 7, 3, 3, 7, 6, 3, 6, 2, 4, 6, 7, 4, 5, 6, 2, 6, 1, 6, 5, 1, 0, 1, 4, 4, 1, 5, 3, 2, 1, 0, 3, 1
	
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


Mesh* Object3D::CreateFuel(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{

	glm::vec3 whitey = glm::vec3(0, 0.5, 0.776);
	glm::vec3 whiteyy = glm::vec3(0, 0.262, 0.4);


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.5 * d, -0.27 * d, -0.3 * d),glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(0.5 * d, -0.27 * d, -0.3 * d),glm::vec3(0, 0, 0), whiteyy),
		VertexFormat(glm::vec3(0 * d, -0.27 * d, 0.6 * d), glm::vec3(0, 0, 0), whitey),
		VertexFormat(glm::vec3(0 * d, .54 * d, 0 * d), glm::vec3(0, 0, 0), whiteyy),
		

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = {

		//fuel
		0,1,2, 0,1,3, 1,2,3, 2,0,3

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

Mesh* Object3D::CreateObstacle(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{

	glm::vec3 whitey = glm::vec3(1, 0, 0);

	std::vector<VertexFormat> vertices;

	int numLat = 16, numLong = 16;
	float gr = 1.0 / 57.0;
	float r = 1.0;
	int totalVerts = 2 + (numLat * numLong);
	//vertices.push_back(VertexFormat(glm::vec3(0,0,0), glm::vec3(0, 0, 0), whitey));
	float dy = (2 * r) / (float)(numLong); 
	float dTheta = gr * 360.0f / (float)numLat;
	float angleLong = gr * 180.0f / (float)(numLong);//for sphere
  
	for (int longi = 0; longi <= numLong; longi++) {
		float sr = r * sin(angleLong * (float)longi);
		for (int lati = 1; lati <= numLat; lati++) {			
			vertices.push_back(VertexFormat(glm::vec3(cos(dTheta * lati) * sr,  dy * longi, sin(dTheta * lati) * sr), glm::vec3(0, 0, 0), whitey));
		}
	}
	//vertices.push_back(VertexFormat(glm::vec3(0, 2 * r, 0), glm::vec3(0, 0, 0), whitey));
	

	
	std::vector<unsigned short> indices = {
		0,  16,  1, 17,  2, 18,  3, 19,  4, 20,  5, 21,  6, 22,  7, 23,  8, 24,  9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31,  0, 16,
		16, 32, 17, 33, 18, 34, 19, 35, 20, 36, 21, 37, 22, 38, 23, 39, 24, 40, 25, 41, 26, 42, 27, 43, 28, 44, 29, 45, 30, 46, 31, 47, 16, 32,
		32, 48, 33, 49, 34, 50, 35, 51, 36, 52, 37, 53, 38, 54, 39, 55, 40, 56, 41, 57, 42, 58, 43, 59, 44, 60, 45, 61, 46, 62, 47, 63, 32, 48,
		48, 64, 49, 65, 50, 66, 51, 67, 52, 68, 53, 69, 54, 70, 55, 71, 56, 72, 57, 73, 58, 74, 59, 75, 60,	76, 61, 77, 62, 78, 63, 79, 48, 64,
		64, 80, 65, 81, 66, 82, 67, 83, 68, 84, 69, 85, 70, 86, 71, 87, 72, 88, 73, 89, 74, 90, 75, 91, 76,	92, 77, 93, 78, 94, 79, 95, 64, 80,
		80, 96, 81, 97, 82, 98, 83, 99, 84, 100, 85, 101, 86, 102, 87, 103, 88, 104, 89, 105, 90, 106, 91, 107, 92, 108, 93, 109, 94, 110, 95, 111, 80, 96,
		96, 112, 97, 113, 98, 114, 99, 115, 100, 116, 101, 117, 102, 118, 103, 119, 104, 120, 105, 121, 106, 122, 107, 123, 108, 124, 109, 125, 110, 126, 111, 127, 96, 112,
		112, 128, 113, 129, 114, 130, 115, 131, 116, 132, 117, 133, 118, 134, 119, 135, 120, 136, 121, 137,	122, 138, 123, 139, 124, 140, 125, 141, 126, 142, 127, 143, 112, 128,
		128, 144, 129, 145, 130, 146, 131, 147, 132, 148, 133, 149, 134, 150, 135, 151, 136, 152, 137, 153,	138, 154, 139, 155, 140, 156, 141, 157, 142, 158, 143, 159, 128, 144,
		144, 160, 145, 161, 146, 162, 147, 163, 148, 164, 149, 165, 150, 166, 151, 167, 152, 168, 153, 169,	154, 170, 155, 171, 156, 172, 157, 173, 158, 174, 159, 175, 144, 160,
		160, 176, 161, 177, 162, 178, 163, 179, 164, 180, 165, 181, 166, 182, 167, 183, 168, 184, 169, 185,	170, 186, 171, 187, 172, 188, 173, 189, 174, 190, 175, 191, 160, 176,
		176, 192, 177, 193, 178, 194, 179, 195, 180, 196, 181, 197, 182, 198, 183, 199, 184, 200, 185, 201,	186, 202, 187, 203, 188, 204, 189, 205, 190, 206, 191, 207, 176, 192,
		192, 208, 193, 209, 194, 210, 195, 211, 196, 212, 197, 213, 198, 214, 199, 215, 200, 216, 201, 217,	202, 218, 203, 219, 204, 220, 205, 221, 206, 222, 207, 223, 192, 208,
		208, 224, 209, 225, 210, 226, 211, 227, 212, 228, 213, 229, 214, 230, 215, 231, 216, 232, 217, 233,	218, 234, 219, 235, 220, 236, 221, 237, 222, 238, 223, 239, 208, 224,
		224, 240, 225, 241, 226, 242, 227, 243, 228, 244, 229, 245, 230, 246, 231, 247, 232, 248, 233, 249,	234, 250, 235, 251, 236, 252, 237, 253, 238, 254, 239, 255, 224, 240,
		240, 256, 241, 257, 242, 258, 243, 259, 244, 260, 245, 261, 246, 262, 247, 263, 248, 264, 249, 265,	250, 266, 251, 267, 252, 268, 253, 269, 254, 270, 255, 271, 240, 256,
		256, 272, 257, 273, 258, 274, 259, 275, 260, 276, 261, 277, 262, 278, 263, 279, 264, 280, 265, 281, 266, 282, 267, 283, 268, 284, 269, 285, 270, 286, 271, 287, 256, 272
	
	};

	Mesh* square = new Mesh(name);
	square->SetDrawMode(GL_TRIANGLE_STRIP);
	square->InitFromData(vertices, indices);

	
	return square;
}


Mesh* Object3D::CreateSea(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{

	glm::vec3 whitey = glm::vec3(0.54, 0.80, 0.95);
	glm::vec3 bluey = glm::vec3(0, 0.262, 0.4);

	std::vector<VertexFormat> vertices;

	int numLat = 16, numLong = 8;
	float gr = 1.0 / 57.0;
	float r = 1.0;
	int totalVerts = 2 + (numLat * numLong);
	//vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), whitey));
	float dy = (2 * r) / (float)(numLong); //+ 2 is for the top and bottom points.
	float dTheta = gr * 360.0f / (float)numLat;
	float angleLong = 180.0f / (float)(numLong + 2);//for sphere
	float sr = r * cos(angleLong);			 //for sphere - del this for cilinder
	for (int longi = 1; longi < numLong; longi++) {
		for (int lati = 0; lati < numLat; lati++) {
			vertices.push_back(VertexFormat(glm::vec3(cos(dTheta * lati) * sr, sin(dTheta * lati) * sr, dy * longi*2), glm::vec3(0, 0, 0), whitey));
		}
	}


	std::vector<unsigned short> indices = {

		
		0,  16,  1, 17,  2, 18,  3, 19,  4, 20,  5, 21,  6, 22,  7, 23,  8, 24,  9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31,  0, 16,
		16, 32, 17, 33, 18, 34, 19, 35, 20, 36, 21, 37, 22, 38, 23, 39, 24, 40, 25, 41, 26, 42, 27, 43, 28, 44, 29, 45, 30, 46, 31, 47, 16, 32,
		32, 48, 33, 49, 34, 50, 35, 51, 36, 52, 37, 53, 38, 54, 39, 55, 40, 56, 41, 57, 42, 58, 43, 59, 44, 60, 45, 61, 46, 62, 47, 63, 32, 48,
		48, 64, 49, 65, 50, 66, 51, 67, 52, 68, 53, 69, 54, 70, 55, 71, 56, 72, 57, 73, 58, 74, 59, 75, 60,	76, 61, 77, 62, 78, 63, 79, 48, 64,
		64, 80, 65, 81, 66, 82, 67, 83, 68, 84, 69, 85, 70, 86, 71, 87, 72, 88, 73, 89, 74, 90, 75, 91, 76,	92, 77, 93, 78, 94, 79, 95, 64, 80,
		80, 96, 81, 97, 82, 98, 83, 99, 84, 100, 85, 101, 86, 102, 87, 103, 88, 104, 89, 105, 90, 106, 91, 107, 92, 108, 93, 109, 94, 110, 95, 111, 80, 96,
		96, 112, 97, 113, 98, 114, 99, 115, 100, 116, 101, 117, 102, 118, 103, 119, 104, 120, 105, 121, 106, 122, 107, 123, 108, 124, 109, 125, 110, 126, 111, 127, 96, 112,
		112, 128, 113, 129, 114, 130, 115, 131, 116, 132, 117, 133, 118, 134, 119, 135, 120, 136, 121, 137,	122, 138, 123, 139, 124, 140, 125, 141, 126, 142, 127, 143, 112, 128

	};

	Mesh* square = new Mesh(name);
	square->SetDrawMode(GL_TRIANGLE_STRIP);
	square->InitFromData(vertices, indices);


	return square;
}

Mesh* Object3D::CreateCap(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{

	glm::vec3 whitey = glm::vec3(0.98, 0.819, 0.643);


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0 * d, 0 * d, 0 * d),glm::vec3(0, 0, 0), whitey), //0
		VertexFormat(glm::vec3(0 * d, 0 * d, -1 * d),glm::vec3(0, 0, 0), whitey), //1
		VertexFormat(glm::vec3(-.7 * d, 0 * d, -.7 * d), glm::vec3(0, 0, 0), whitey), //2
		VertexFormat(glm::vec3(-1 * d, 0 * d, 0 * d), glm::vec3(0, 0, 0), whitey), //3
		VertexFormat(glm::vec3(-.7 * d, 0 * d, .7 * d), glm::vec3(0, 0, 0), whitey), //4
		VertexFormat(glm::vec3(0 * d, 0 * d, 1 * d), glm::vec3(0, 0, 0), whitey), //5
		VertexFormat(glm::vec3(.7 * d, 0 * d, .7 * d), glm::vec3(0, 0, 0), whitey), //6
		VertexFormat(glm::vec3(1 * d, 0 * d, 0 * d), glm::vec3(0, 0, 0), whitey), //7
		VertexFormat(glm::vec3(.7 * d, 0 * d, -.7 * d), glm::vec3(0, 0, 0), whitey), //8

		VertexFormat(glm::vec3(0 * d, -1 * d, 0 * d),glm::vec3(0, 0, 0), whitey), //0
		VertexFormat(glm::vec3(0 * d, -1 * d, -1 * d),glm::vec3(0, 0, 0), whitey), //1
		VertexFormat(glm::vec3(-.7 * d, -1 * d, -.7 * d), glm::vec3(0, 0, 0), whitey), //2
		VertexFormat(glm::vec3(-1 * d, -1 * d, 0 * d), glm::vec3(0, 0, 0), whitey), //3
		VertexFormat(glm::vec3(-.7 * d, -1 * d, .7 * d), glm::vec3(0, 0, 0), whitey), //4
		VertexFormat(glm::vec3(0 * d, -1 * d, 1 * d), glm::vec3(0, 0, 0), whitey), //5
		VertexFormat(glm::vec3(.7 * d, -1 * d, .7 * d), glm::vec3(0, 0, 0), whitey), //6
		VertexFormat(glm::vec3(1 * d, -1 * d, 0 * d), glm::vec3(0, 0, 0), whitey), //7
		VertexFormat(glm::vec3(.7 * d, -1 * d, -.7 * d), glm::vec3(0, 0, 0), whitey), //8

	};


	std::vector<unsigned short> indices = {

		//cloud
		0, 1, 2, 3, 4, 5, 6, 7, 8, 1,
		9,10,11,12,13,14,15,16,17,10

	};

	Mesh* square = new Mesh(name);
	square->SetDrawMode(GL_TRIANGLE_FAN);
	square->InitFromData(vertices, indices);


	return square;
}

Mesh* Object3D::CreateHeart(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{

	glm::vec3 whitey = glm::vec3(1, 0, 0);


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0 * d, 1 * d, 0),glm::vec3(0, 0, 0), whitey), //0
		VertexFormat(glm::vec3(1 * d, 3 * d, 0),glm::vec3(0, 0, 0), whitey), //1
		VertexFormat(glm::vec3(2 * d, 3 * d, 0), glm::vec3(0, 0, 0), whitey), //2
		VertexFormat(glm::vec3(3 * d, 2 * d, 0), glm::vec3(0, 0, 0), whitey), //3
		VertexFormat(glm::vec3(3 * d, 0.5 * d, 0), glm::vec3(0, 0, 0), whitey), //4
		VertexFormat(glm::vec3(0 * d, -3 * d, 0), glm::vec3(0, 0, 0), whitey), //5
		VertexFormat(glm::vec3(-3 * d, 0.5 * d, 0), glm::vec3(0, 0, 0), whitey), //6
		VertexFormat(glm::vec3(-3 * d, 2 * d, 0), glm::vec3(0, 0, 0), whitey), //7
		VertexFormat(glm::vec3(-2 * d, 3 * d, 0), glm::vec3(0, 0, 0), whitey), //8
		VertexFormat(glm::vec3(-1 * d, 3 * d, 0), glm::vec3(0, 0, 0), whitey), //7
		

	};


	std::vector<unsigned short> indices = {

		0, 1, 2, 3, 4, 5, 6, 7, 8, 9

	};

	Mesh* square = new Mesh(name);
	square->SetDrawMode(GL_TRIANGLE_FAN);
	square->InitFromData(vertices, indices);


	return square;
}

Mesh* Object3D::CreateBox(std::string name, glm::vec3 leftBottomCorner, float d, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-1 * d, -1 * d, -1 * d),glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1 * d, -1 * d, 1 * d),glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1 * d, 1 * d, 1 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1 * d, 1 * d, -1 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(1 * d, -1 * d, -1 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(1 * d, -1 * d, 1 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(1 * d, 1 * d, 1 * d), glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(1 * d, 1 * d, -1 * d), glm::vec3(0, 0, 0), color),

	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = {

		//cloud
		0, 4, 3, 4, 7, 3, 3, 7, 6, 3, 6, 2, 4, 6, 7, 4, 5, 6, 2, 6, 1, 6, 5, 1, 0, 1, 4, 4, 1, 5, 3, 2, 1, 0, 3, 1

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