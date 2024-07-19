#pragma once

#include "Renderer.h"

#include "Moves.h"

#include <string>

class PlayerStateMachine {
private:
	Move nullmove;

	PlayerStateEnum state;

	Move& currentMove;

	int frameNum;

	int stunFrames;
public:
	PlayerStateMachine();
	~PlayerStateMachine();

	void Init();

	void Action(PlayerStateEnum newAction);
	void GameAdvance();

	void ChangeState(PlayerStateEnum changeTo);
	void Stun(int hitStun, PlayerStateEnum type);

	int GetFrameNum() const;
	PlayerStateEnum GetState() const;
	int GetDamage() const;
	int GetHitStun() const;
	MoveFrame GetMove() const;
	bool IsNewMove() const;
};


