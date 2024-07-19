#include "InputHandler.h"

InputHandler::InputHandler() {
	Init();
}

InputHandler::~InputHandler() {
}

void InputHandler::Init() {
	KeyPresses.assign(moveCount*2, 0);
}

void InputHandler::CheckButtons() {
	if (ImGui::IsKeyDown(ImGuiKey_A)) {
		KeyPresses[0]++;
	}
	else {
		KeyPresses[0] = 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_D)) {
		KeyPresses[1]++;
	}
	else {
		KeyPresses[1] = 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_F)) {
		KeyPresses[2]++;
	}
	else {
		KeyPresses[2] = 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_G)) {
		KeyPresses[3]++;
	}
	else {
		KeyPresses[3] = 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_LeftArrow)) {
		KeyPresses[4]++;
	}
	else {
		KeyPresses[4] = 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_RightArrow)) {
		KeyPresses[5]++;
	}
	else {
		KeyPresses[5] = 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_K)) {
		KeyPresses[6]++;
	}
	else {
		KeyPresses[6] = 0;
	}
	if (ImGui::IsKeyDown(ImGuiKey_L)) {
		KeyPresses[7]++;
	}
	else {
		KeyPresses[7] = 0;
	}
}

std::pair<PlayerStateEnum, PlayerStateEnum> InputHandler::GetPlayerActions() {
	PlayerStateEnum p1action = PlayerStateEnum::Idle;
	PlayerStateEnum p2action = PlayerStateEnum::Idle;
	if (KeyPresses[0] != 0) {
		p1action = PlayerStateEnum::MovingLeft;
	}
	if (KeyPresses[1] != 0) {
		p1action = PlayerStateEnum::MovingRight;
	}
	if (KeyPresses[2] == 1) {
		p1action = PlayerStateEnum::AttackL;
	}
	if (KeyPresses[3] == 1) {
		p1action = PlayerStateEnum::AttackH;
	}
	if (KeyPresses[4] != 0) {
		p2action = PlayerStateEnum::MovingLeft;
	}
	if (KeyPresses[5] != 0) {
		p2action = PlayerStateEnum::MovingRight;
	}
	if (KeyPresses[6] == 1) {
		p2action = PlayerStateEnum::AttackL;
	}
	if (KeyPresses[7] == 1) {
		p2action = PlayerStateEnum::AttackH;
	}
	return std::make_pair(p1action,p2action);
}
