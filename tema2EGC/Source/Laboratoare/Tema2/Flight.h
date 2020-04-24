#pragma once
#include <Component/SimpleScene.h>
#include "Cloud.h"
#include "Fuel.h"
#include "Obstacle.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Flight : public SimpleScene
{
	public:
		Flight();
		~Flight();

		void Init() override;
		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat4 modelMatrix;
		glm::mat4 body;
		glm::mat4 blade;
		glm::mat4 fuelBar1;
		glm::mat4 fuelBar2;
		glm::mat4 h;
		std::vector<Cloud> clouds;
		std::vector<Fuel> fuelChunks;
		std::vector<Obstacle> obstacles;
		std::vector<glm::mat4> hearts;

		glm::mat4 sea;
		float dist;
		float height;
		float bladeAngle;
		float planeHeight;
		float planeAngle;
		float cloudHeight;
		float worldAngle;
		float fuelHeight;
		float obstacleHeight;
		float timer;
		float timer2;
		int lives;
		int ftank;
		bool gameOver;
		
		GLenum polygonMode;
};
