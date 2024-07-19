#pragma once

#include "PlayerStateMachine.h"

struct PlayerData {
	glm::vec2 pos;
	Rectangle hitBox;
	Rectangle hurtBox;
	PlayerStateEnum state;
	int damage;
	int hitStun;
	bool moveConnected;
};

class Player {
private:
	glm::vec2 position = glm::vec2(0,0);
	float leftPosLimit = 0.0f;
	float rightPosLimit = 400.0f;

	int orientation = 1;

	int health = 100;

	bool moveConnected = false;

	PlayerStateMachine state;

	PlayerData& outLoc;

public:
	Player(PlayerData& out);
	~Player();

	void Init(glm::vec2 pos, int ori);

	void PlayerAction(PlayerStateEnum inputAction);
	void GameAdvance();
	void moveConnect();

	void ChangePos(glm::vec2 pos);
	void ChangeOrientation(int newori);
	void Damage(int damage, int hitStun);

	glm::vec2 GetPosition() const;
	int GetOrientation() const;
	int GetFrameNum() const;
	int GetHealth() const;
	PlayerStateEnum GetState() const;
};

