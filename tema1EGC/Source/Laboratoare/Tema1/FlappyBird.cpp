#include "FlappyBird.h"

#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"



using namespace std;

 
FlappyBird::FlappyBird()
{
}

FlappyBird::~FlappyBird()
{
}

void FlappyBird::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 upcorner = glm::vec3(0, 1, 0);
	float squareSide = 100;

	
	for (int i = 0; i < 6; i++) {
		column.push_back(Pile());
		column.at(i).trX = i * 230; /*230 este distanta la care am ajuns 
									impartind lungimea rezolutiei la 6 piloni 
									si 6, pentru ca latimea unui pilon e de 
									100 si asa ar fi distanta optima de spatiu intre*/
	}
	

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;
	translatePiles = 0;
	fal = 11;
	multip = 0;
	score = 0;

	srand(time(NULL));

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;


	Mesh* dwPile = Object2D::CreateSquare("dwPile", corner, squareSide, glm::vec3(0.44, .5, .56), true);
	AddMeshToList(dwPile);

	Mesh* upPile = Object2D::CreateSquareDown("upPile", upcorner, squareSide, glm::vec3(0.44, .5, .56), true);
	AddMeshToList(upPile);

	Mesh* bird = Object2D::Createbird("bird", corner, 50, glm::vec3(.54, .27, .07), true);
	AddMeshToList(bird);

	Mesh* birdfal = Object2D::Createbirdfal("birdfal", corner, 50, glm::vec3(.54, .27, .07), true);
	AddMeshToList(birdfal);

	Mesh* backg = Object2D::CreateBack("backg", corner, 50, glm::vec3(0, 0, 0), true);
	AddMeshToList(backg);

}

void FlappyBird::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void FlappyBird::Update(float deltaTimeSeconds)
{
	
	
	
	if (translateY > -998) {
		translateY -= deltaTimeSeconds * 400;
		angularStep += deltaTimeSeconds * 3.0f;
	}

	bird =
		glm::mat3(1)
		* Transform2D::Translate(200, 500)
		* Transform2D::Scale(0.5, 0.5)
		* Transform2D::Translate(0, translateY)
		* Transform2D::Translate(50, 50)
	    * Transform2D::Rotate(-angularStep*0.1)
		* Transform2D::Translate(-50, -50);

		if (fal <= 10) 
		{
		RenderMesh2D(meshes["birdfal"], shaders["VertexColor"], bird);
		}
		else 
		{
		RenderMesh2D(meshes["bird"], shaders["VertexColor"], bird);
		}
	    
		fal++;
	

	for (int i = 0; i < 6; i++) {
		int bonusDist = i * 100;
		column.at(i).trX -= deltaTimeSeconds * (130 + multip);
		column.at(i).upPile = glm::mat3(1) * Transform2D::Translate(1280, 720) * Transform2D::Translate(column.at(i).trX, 0) * Transform2D::Scale(1, column.at(i).ran);
		column.at(i).dwPile = glm::mat3(1) * Transform2D::Scale(1, column.at(i).con - column.at(i).ran)	* Transform2D::Translate(1280, 0) * Transform2D::Translate(column.at(i).trX, 0);

		RenderMesh2D(meshes["upPile"], shaders["VertexColor"], column.at(i).upPile);
		RenderMesh2D(meshes["dwPile"], shaders["VertexColor"], column.at(i).dwPile);
		if (column.at(i).trX < -1380) {
			column.at(i).trX = 0;
			column.at(i).getNewRand();
		}


		//Coliisions
		if (column.at(i).trX + 1280 < 265  && column.at(i).trX + 1280 > 100) {
			if (500 + (translateY / 2) < 100 * (column.at(i).con - column.at(i).ran)
				||
				500 + (translateY / 2) + 60 > 720 - 100 * column.at(i).ran) 
			{
				cout << "collision detection at: " << column.at(i).trX + 1280 << " " << 500 + (translateY / 2) << "\n";
				cout << "Game Over.\nFinal score : " << score << "\n";
				GameReset();
			}
				
		}

		//Fell out of map
		if (500 + (translateY / 2) < 10) {
			cout << "You fell out of map at: " << column.at(i).trX + 1280 << " " << 500 + (translateY / 2) << "\n";
			cout << "Game Over.\nFinal score : " << score << "\n";
			GameReset();
		}

		//Score
		if (column.at(i).trX + 1280 < 100 && column.at(i).pointTaken == 0) {
			column.at(i).pointTaken = 1;
			score++;
			cout << "Great ! Score : " << score << "\n";
			multip = score * 5; 
		}
			


	}
	
	RenderMesh2D(meshes["backg"], shaders["VertexColor"], glm::mat3(1));
}

void FlappyBird::GameReset()
{
	score = 0;
	for (int i = 0; i < 6; i++) {
		column.at(i).trX = i * 230;
		column.at(i).getNewRand();
	}
	translateY = 0;
	angularStep = 0;
	multip = 0;

}

void FlappyBird::FrameEnd()
{

}

void FlappyBird::OnInputUpdate(float deltaTime, int mods)
{

}

void FlappyBird::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE)
	{
		if (500 + 60 + (translateY + 200)/2  > 720) {
			translateY = 400;
		}
		else {
			translateY += 200;
		}
		
		angularStep = 0;
		fal = 0;
	}
}

void FlappyBird::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void FlappyBird::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void FlappyBird::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void FlappyBird::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void FlappyBird::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void FlappyBird::OnWindowResize(int width, int height)
{
}
