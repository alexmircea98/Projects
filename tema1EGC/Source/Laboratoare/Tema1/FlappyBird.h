#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <Core/Engine.h>
#include "Pile.h"

class Bird {
	glm::mat3 body;
	glm::mat3 peak;
};

class FlappyBird : public SimpleScene
{
public:
	FlappyBird();
	~FlappyBird();

	void Init() override;

private:
	void GameReset();
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;


protected:
	glm::mat3 bird;
	std::vector<Pile> column;
	float translateX, translateY;
	float translatePiles;
	float scaleX, scaleY;
	float angularStep;
	int fal, score, multip;
};
