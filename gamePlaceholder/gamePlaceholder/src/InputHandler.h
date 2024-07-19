#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include <vector>

#include "PlayerStateEnum.h"

class InputHandler {
private:
	const int moveCount = 4;

	std::vector<int> KeyPresses;
public:
	InputHandler();
	~InputHandler();

	void Init();
	void CheckButtons();
	std::pair<PlayerStateEnum, PlayerStateEnum> GetPlayerActions();
};