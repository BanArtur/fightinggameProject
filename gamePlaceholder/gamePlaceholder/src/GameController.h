#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"
#include "Shader.h"

#include "GameModel.h"
#include "InputHandler.h"
#include "AppEnums.h"
#include "Texture.h"
#include "RenderableObject.h"
#include "TextureHandler.h"

class GameController {
private:
	const float AnimationStripHeight = 128.0f;
	const float AnimationStripLength = 1280.0f;

	GLFWwindow* window;
	Renderer& renderer;
	Shader& shader;
	Shader& shaderAnimation;
	ApplicationState& state;
	bool& showHitboxes;

	GameModel gameModel;
	InputHandler inputHandler;

	double currentFrame;
	double lastFrame;
	double elapsedTimeBuffer;
	int physicsFrames;
	float frameLength;

	float player1pos;
	float player2pos;

	float playermidpoint;
	float cameraPos;

	int gameEndFrames;

	glm::mat4 gameProj;
	glm::mat4 gameView;

	RenderableObject* GameBackground;
	RenderableObject* Box;
	RenderableObject* Player;

	Texture textureHitbox;
	Texture textureHurtbox;
	Texture textureGameBackground;

public:
	GameController(Shader& sh, Shader& ansh, Renderer& rend, GLFWwindow* wind, ApplicationState& st, bool& hitb);
	~GameController();

	void Init();
	void Render();
	void RenderGameEnd();
};
