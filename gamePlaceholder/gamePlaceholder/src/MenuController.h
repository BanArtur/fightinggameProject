#pragma once
#include <iostream>

#include "Shader.h"
#include "Renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

enum MenuState { Main, Settings };

class MenuController {
private:
	MenuState menuState;
	Shader& shader;
	Renderer& renderer;

public:
	MenuController(Shader& sh, Renderer& rend);
	~MenuController();

	void Render(int windowWidth, int windowHeight);
};