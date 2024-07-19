#include "PlayerStateMachine.h"

PlayerStateMachine::PlayerStateMachine() : currentMove(nullmove) {
	state = PlayerStateEnum::Idle;
	ChangeState(PlayerStateEnum::Idle);
}

PlayerStateMachine::~PlayerStateMachine() {
}

void PlayerStateMachine::Init() {
	state = PlayerStateEnum::Idle;
}

void PlayerStateMachine::Action(PlayerStateEnum newAction) {
	bool valid = false;
	for (PlayerStateEnum move : currentMove.allowedTransitions) {
		if (move == newAction) {
			valid = true;
		}
	}
	if (valid) {
		ChangeState(newAction);
	}
}

void PlayerStateMachine::GameAdvance() {
	if (state == PlayerStateEnum::HitStun || state == PlayerStateEnum::BlockStun) {
		if (stunFrames == 1) {
			stunFrames = 0;
			ChangeState(PlayerStateEnum::Idle);
		}
		else {
			stunFrames--;
		}
	}
	else {
		if (frameNum == currentMove.frames.size() - 1) {
			ChangeState(PlayerStateEnum::Idle);
		}
		else {
			frameNum++;
		}
	}
}

void PlayerStateMachine::ChangeState(PlayerStateEnum changeTo) {
	state = changeTo;
	currentMove = Moves::GetMovesInstance().GetMove(changeTo);
	frameNum = 0;
}

void PlayerStateMachine::Stun(int hitStun, PlayerStateEnum type) {
	ChangeState(type);
	stunFrames = hitStun;
}

int PlayerStateMachine::GetFrameNum() const {
	return currentMove.frames[frameNum].realFrame;
}

PlayerStateEnum PlayerStateMachine::GetState() const {
	return state;
}

int PlayerStateMachine::GetDamage() const
{
	return currentMove.damage;
}

int PlayerStateMachine::GetHitStun() const {
	return currentMove.hitStun;
}

MoveFrame PlayerStateMachine::GetMove() const {
	return currentMove.frames[frameNum];
}

bool PlayerStateMachine::IsNewMove() const
{
	return frameNum == 0;
}
