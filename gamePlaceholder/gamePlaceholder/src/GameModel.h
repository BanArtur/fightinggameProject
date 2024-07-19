#pragma once

#include "Player.h"

class GameModel {
private:
	//TODO: put two player object into one vector
	Player* player1;

	Player* player2;

	PlayerData p1Data;
	PlayerData p2Data;

	bool p1Won;
	bool p2Won;
public:
	GameModel();
	~GameModel();

	void Init();

	void PlayerAction(int num, PlayerStateEnum inputAction);
	void GameAdvance(int frames);

	glm::vec2 GetPlayerPosition(int num) const;
	int GetPlayerOrientation(int num) const;
	int GetPlayerFrameNum(int num) const;
	int GetPlayerHealth(int num) const;
	PlayerStateEnum GetPlayerState(int num) const;
	bool P1Won() const;
	bool P2Won() const;
	Rectangle GetPlayerHurtBox(int num) const;
	Rectangle GetPlayerHitBox(int num) const;
};

