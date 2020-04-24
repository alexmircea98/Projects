#include "Flight.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"
#include "Object3D.h"
#include "Cloud.h"
#include "Fuel.h"
#include "Obstacle.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

Flight::Flight()
{
}

Flight::~Flight()
{
}

void Flight::Init()
{	
	
	polygonMode = GL_FILL;

	dist = -5.0;
	height = 0;
	bladeAngle = 0.0;
	planeHeight = 1.0;
	planeAngle = 0.0;
	cloudHeight = 5;
	fuelHeight = 4;
	obstacleHeight = 3;
	timer = 0;
	timer2 = 0;
	hearts = std::vector<glm::mat4>(3, glm::mat4(1));
	fuelBar1 = glm::mat4(1);
	fuelBar2 = glm::mat4(1);

	gameOver = false;

	lives = 3;
	ftank = 10;
	
	for (int i = 0; i < 8; i++) {
		float angle = (1.0/57.0)* 45.0 * i;
		clouds.push_back(Cloud(angle, cloudHeight));
	}
	for (int i = 0; i < 2; i++) {
		float angle = (1.0 / 57.0) * 180 * i;
		fuelChunks.push_back(Fuel(angle, fuelHeight));
	}

	for (int i = 0; i < 3; i++) {
		float angle = (1.0 / 57.0) * 120 * i;
		obstacles.push_back(Obstacle(angle, obstacleHeight));
	}

	Mesh* body = Object3D::CreateBody("body", glm::vec3(0,0,0), 0.1, glm::vec3(1, 0, 0), true);
	AddMeshToList(body);

	Mesh* blade = Object3D::CreateBlade("blade", glm::vec3(0, 0, 0), 0.1, glm::vec3(1, 0, 0), true);
	AddMeshToList(blade);

	Mesh* cloud = Object3D::CreateCloud("cloud", glm::vec3(0, 0, 0), 0.1, glm::vec3(0, 0, 0), true);
	AddMeshToList(cloud);

	Mesh* fuel = Object3D::CreateFuel("fuel", glm::vec3(0, 0, 0), 0.3, glm::vec3(0, 0, 0), true);
	AddMeshToList(fuel);

	Mesh* obstacle = Object3D::CreateObstacle("obstacle", glm::vec3(0, 0, 0), 0.1, glm::vec3(0, 0, 0), true);
	AddMeshToList(obstacle);

	Mesh* sea2 = Object3D::CreateSea("sea2", glm::vec3(0, 0, 0), 0.1, glm::vec3(0, 0, 0), true);
	AddMeshToList(sea2);

	Mesh* heart = Object3D::CreateHeart("heart", glm::vec3(0, 0, 0), 0.1, glm::vec3(0, 0, 0), true);
	AddMeshToList(heart);

	Mesh* fuelBoxL = Object3D::CreateBox("fuelBoxL", glm::vec3(0, 0, 0), 0.1, glm::vec3(1, 1, 1), true);
	AddMeshToList(fuelBoxL);

	Mesh* fuelBoxLs = Object3D::CreateBox("fuelBoxS", glm::vec3(0, 0, 0), 0.1, glm::vec3(0, 0, 0), true);
	AddMeshToList(fuelBoxLs);

	{
		glm::vec3 whitey = glm::vec3(0.54, 0.80, 0.95);
		glm::vec3 bluey = glm::vec3(0, 0.262, 0.4);

		std::vector<VertexFormat> vertices;

		int numLat = 16, numLong = 8;
		float gr = 1.0 / 57.0;
		float r = 1.0;
		//vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), whitey));
		float dy = (2 * r) / (float)(numLong); //+ 2 is for the top and bottom points.
		float dTheta = gr * 360.0f / (float)numLat;
		float angleLong = 180.0f / (float)(numLong + 2);//for sphere
		float sr = r * cos(angleLong);			 //for sphere - del this for cilinder
		for (int longi = 1; longi <= numLong; longi++) {
			for (int lati = 0; lati < numLat; lati++) {
				float ran = (rand() % 10 + 1) / 100.0;
				if (rand() % 2) {
					ran *= -1.0;
				}
				vertices.push_back(VertexFormat(glm::vec3(cos(dTheta * lati) * (sr + ran), sin(dTheta * lati) * (sr + ran), dy * longi * 2), glm::vec3(0, 0, 0), whitey));
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


		CreateMesh("sea", vertices, indices);
	}

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		CreateMesh("cube", vertices, indices);
	}



	{
		Shader* shader = new Shader("SeaShader");
		shader->AddShader("Source/Laboratoare/Tema2/ShaderSea/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/ShaderSea/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

Mesh* Flight::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	//meshes[name]->SetDrawMode(GL_TRIANGLE_STRIP);
	meshes[name] = new Mesh(name);
	meshes[name]->SetDrawMode(GL_TRIANGLE_STRIP);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}

void Flight::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.98, 0.64, 0.31, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Flight::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
	
	bladeAngle += deltaTimeSeconds * 15;
	worldAngle += deltaTimeSeconds * 0.5;
	timer2 += deltaTimeSeconds;
	if (timer2>=2 && !gameOver) {
		timer2 = 0;
		ftank--;
	}


	{
		body = glm::mat4(1);
		body *= Transform3D::Translate(0, height, 0);
		body *= Transform3D::Translate( 0, planeHeight, dist);
		body *= Transform3D::RotateOZ(planeAngle);

		RenderMesh(meshes["body"], shaders["VertexNormal"], body);

		blade = glm::mat4(1);
		blade *= Transform3D::Translate(0, height, 0);
		blade *= Transform3D::Translate(0, planeHeight, dist);
		blade *= Transform3D::RotateOZ(planeAngle);
		blade *= Transform3D::RotateOX(bladeAngle);
		
		RenderMesh(meshes["blade"], shaders["VertexNormal"], blade);

		for (int f = 0; f < clouds.size(); f++) {
			int x = 0;
			if ((int)((worldAngle + clouds[f].angle) * 57) % 360 == 270 ) {
				clouds[f].getNewSize();
			}
			for (glm::mat4 cl : clouds[f].cloud) {
				float angle = worldAngle + clouds[f].angle + (3.0 / 57.0) * x;
				cl = glm::mat4(1);
				cl *= Transform3D::RotateOZ(angle);
				cl *= Transform3D::Translate(cloudHeight, height, dist);
				cl *= Transform3D::RotateOX(angle*3);
				cl *= Transform3D::Scale(clouds[f].ran[x], clouds[f].ran[x], clouds[f].ran[x]);
				x++;
				RenderMesh(meshes["cloud"], shaders["VertexNormal"], cl);
			}
		}
		
		for (int f = 0; f<fuelChunks.size(); f++){
			int x = 0;
			for (glm::mat4 fuelPoint : fuelChunks[f].fuelLine) {
				if ((int)((worldAngle + fuelChunks[f].angle) * 57) % 360 == 270) {
					fuelChunks[f].hit[x] = false;
				}
				float angle = worldAngle + fuelChunks[f].angle + (3.0 / 57.0) * x;
				if (!fuelChunks[f].hit[x]) {
					if ((int)(angle * 57) % 360 > 75.0 && (int)(angle * 57) % 360 < 90.0) {
						if (planeHeight < 4.2 && planeHeight > 3.8) {
							if (ftank < 10)	ftank++;
							fuelChunks[f].hit[x] = true;
						}
					}
				}
				
				fuelPoint = glm::mat4(1);
				fuelPoint *= Transform3D::RotateOZ(angle);
				fuelPoint *= Transform3D::Translate(fuelHeight, height, dist);
				fuelPoint *= Transform3D::RotateOX(angle*2);
				
				if (!fuelChunks[f].hit[x]) {
					RenderMesh(meshes["fuel"], shaders["VertexNormal"], fuelPoint);
				}
				x++;
			}
		}
		for (int f = 0; f < obstacles.size(); f++) {
			if ((int)((worldAngle + obstacles[f].angle) * 57) % 360 == 270) {
				obstacles[f].hit = false;
			}
			if (!obstacles[f].hit) {
				if ((int)((worldAngle + obstacles[f].angle) * 57) % 360 > 65.0 && (int)((worldAngle + obstacles[f].angle) * 57) % 360 < 90.0) {
					if (planeHeight < 3.3 && planeHeight > 2.7) {
						lives--;
						obstacles[f].hit = true;
					}
				}
			}
			float angle = worldAngle + obstacles[f].angle;
			obstacles[f].obs = glm::mat4(1);
			obstacles[f].obs *= Transform3D::RotateOZ(angle);
			obstacles[f].obs *= Transform3D::Translate(obstacleHeight, height, dist);
			obstacles[f].obs *= Transform3D::Scale(0.3, 0.3, 0.3);
			obstacles[f].obs *= Transform3D::RotateOX(angle*2);
			obstacles[f].obs *= Transform3D::Translate(0, -1, 0);
			if (!obstacles[f].hit) {
				RenderMesh(meshes["obstacle"], shaders["VertexNormal"], obstacles[f].obs);
			}
		}

		sea = glm::mat4(1);
		sea *= Transform3D::Translate(0, -6, 8);
		sea *= Transform3D::Scale(10, 10, -10);
		RenderMesh(meshes["sea2"], shaders["VertexNormal"], sea);
		sea *= Transform3D::RotateOZ(worldAngle);

		RenderSimpleMesh(meshes["sea"], shaders["SeaShader"], sea);

		timer = Engine::GetElapsedTime();

		
		
		for (int i = 0; i < lives; i++) {
			h = glm::mat4(1);
			h *= Transform3D::Translate(-6 + 0.5 * i, 6, -4.5);
			h *= Transform3D::Scale(0.7, 0.7, 0);
			RenderMesh(meshes["heart"], shaders["VertexNormal"], h);
		}
		
		fuelBar1 = glm::mat4(1);
		fuelBar1 *= Transform3D::Translate(6 , 6, -4.5);
		fuelBar1 *= Transform3D::Scale(0.95, 0.6, 0.6);
		fuelBar1 *= Transform3D::Scale(10, 1, 1);
		
		RenderMesh(meshes["fuelBoxS"], shaders["VertexNormal"], fuelBar1);

		fuelBar2 = glm::mat4(1);
		fuelBar2 *= Transform3D::Translate(6, 6, -4.5);
		fuelBar2 *= Transform3D::Scale(ftank, 1, 1);
		RenderMesh(meshes["fuelBoxL"], shaders["VertexNormal"], fuelBar2);

		if (lives == 0 || ftank <= 0) gameOver = true;

		if (gameOver) {
			planeHeight -= deltaTimeSeconds * 3;
			planeAngle -= deltaTimeSeconds * 3;
		}


		////TODO: obstacle mseh - DONE
		//		obstacle / fuel / cloud chunks and generation -Done
		//		camera position - 
		//		object / fuel colosions -Done
		//		dinamyc sea - Done
		//		UI - Done 
		//      animatie final - Done

	}
}

void Flight::FrameEnd()
{
}
void Flight::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location_m = glGetUniformLocation(shader->program, "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location_m, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	// TODO : get shader location for uniform mat4 "View"
	int location_v = glGetUniformLocation(shader->program, "View");

	// TODO : set shader uniform "View" to viewMatrix

	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(location_v, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	int location_p = glGetUniformLocation(shader->program, "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location_p, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int location_t = glGetUniformLocation(shader->program, "Time");
	glUniform1f(location_t, abs(sinf(timer)) + abs(sinf(timer)));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Flight::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_1)) {
		
	}
	
}

void Flight::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Flight::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Flight::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (!gameOver) {
		planeHeight = 1.0 + (720.0 - mouseY) / 720.0 * 3.0;
		//cout << planeHeight << "\n";
		planeAngle = 1.0 / 57.0 * (-deltaY) / 2.0;
		//cout << mouseY << "   " << deltaY << "\n";
	}
	
}

void Flight::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Flight::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Flight::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Flight::OnWindowResize(int width, int height)
{
}
