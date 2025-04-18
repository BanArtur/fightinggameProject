#pragma once
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "Texture.h"
#include "LoginChecker.h"

#include "AppEnums.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include <firebase/app.h>
#include <firebase/database.h>
#include <firebase/auth.h>
#include <firebase/firestore.h>

class MenuController {
private:
	ApplicationState& state;
	MenuState menuState;
	Shader& shader;
	Renderer& renderer;

	GLFWwindow* window;

	glm::mat4 menuProj;
	glm::mat4 menuView;

	RenderableObject* MenuBackground;
	Texture textureMenuBackground;

	bool& showHitboxes;
	char emailAddress[256], username[256], password[256], passwordAgain[256];

	firebase::App* application;
	firebase::auth::Auth* authentication;

	std::string errorMessage;
public:
	MenuController(Shader& sh, Renderer& rend, GLFWwindow* wind, ApplicationState& app, bool& hitb, firebase::App* app_p);
	~MenuController();

	void Init();

	void Render();
};