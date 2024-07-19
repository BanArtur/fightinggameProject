#include "GameModel.h"

GameModel::GameModel() {
	player1 = new Player(p1Data);
	player2 = new Player(p2Data);
	p1Won = false;
	p2Won = false;
}

GameModel::~GameModel() {
	delete player1;
	delete player2;
}

void GameModel::Init() {
	player1->Init({100.0f,0.0f},1);
	player2->Init({300.0f,0.0f},-1);
	p1Won = false;
	p2Won = false;
}

void GameModel::PlayerAction(int num, PlayerStateEnum inputAction) {
	if (num == 1) {
		player1->PlayerAction(inputAction);
	}
	else {
		player2->PlayerAction(inputAction);
	}
}

void GameModel::GameAdvance(int frames) {
	for (int i = 0; i < frames; i++) {
		//TODO: return PlayerData
		player1->GameAdvance();
		player2->GameAdvance();
		if (player1->GetPosition().x < player2->GetPosition().x) {
			if (player1->GetState() == PlayerStateEnum::Idle || player1->GetState() == PlayerStateEnum::MovingLeft || player1->GetState() == PlayerStateEnum::MovingRight) {
				player1->ChangeOrientation(1);
			}
			if (player2->GetState() == PlayerStateEnum::Idle || player2->GetState() == PlayerStateEnum::MovingLeft || player2->GetState() == PlayerStateEnum::MovingRight) {
				player2->ChangeOrientation(-1);
			}
		}
		else {
			if (player1->GetState() == PlayerStateEnum::Idle || player1->GetState() == PlayerStateEnum::MovingLeft || player1->GetState() == PlayerStateEnum::MovingRight) {
				player1->ChangeOrientation(-1);
			}
			if (player2->GetState() == PlayerStateEnum::Idle || player2->GetState() == PlayerStateEnum::MovingLeft || player2->GetState() == PlayerStateEnum::MovingRight) {
				player2->ChangeOrientation(1);
			}
		}
		bool p1hits = IsOverlapping(p1Data.hitBox, p2Data.hurtBox);
		bool p2hits = IsOverlapping(p2Data.hitBox, p1Data.hurtBox);
		bool clash = IsOverlapping(p1Data.hitBox, p2Data.hitBox);
		if (clash) {
			//TODO: implement clash
		}
		else if ((p1hits && !p1Data.moveConnected) && (p2hits && !p2Data.moveConnected)) {
			player1->Damage(p2Data.damage,p2Data.hitStun);
			player2->Damage(p1Data.damage,p1Data.hitStun);
			player1->moveConnect();
			player2->moveConnect();
		}
		else if ((p1hits && !p1Data.moveConnected) && (!p2hits)){
			player2->Damage(p1Data.damage,p1Data.hitStun);
			player1->moveConnect();
		}
		else if ((!p1hits) && (p2hits && !p2Data.moveConnected)) {
			player1->Damage(p2Data.damage,p2Data.hitStun);
			player2->moveConnect();
		}
		if (player1->GetHealth() <= 0) {
			p2Won = true;
		}
		if (player2->GetHealth() <= 0) {
			p1Won = true;
		}
	}
}

glm::vec2 GameModel::GetPlayerPosition(int num) const {
	if (num == 1) {
		return player1->GetPosition();
	}
	else {
		return player2->GetPosition();
	}
}

int GameModel::GetPlayerOrientation(int num) const {
	if (num == 1) {
		return player1->GetOrientation();
	}
	else {
		return player2->GetOrientation();
	}
}

int GameModel::GetPlayerFrameNum(int num) const {
	if (num == 1) {
		return player1->GetFrameNum();
	}
	else {
		return player2->GetFrameNum();
	}
}

int GameModel::GetPlayerHealth(int num) const {
	if (num == 1) {
		return player1->GetHealth();
	}
	else {
		return player2->GetHealth();
	}
}

PlayerStateEnum GameModel::GetPlayerState(int num) const {
	if (num == 1) {
		return player1->GetState();
	}
	else {
		return player2->GetState();
	}
}

bool GameModel::P1Won() const {
	return p1Won;
}

bool GameModel::P2Won() const {
	return p2Won;
}

Rectangle GameModel::GetPlayerHurtBox(int num) const {
	if (num == 1) {
		return p1Data.hurtBox;
	}
	else {
		return p2Data.hurtBox;
	}
}

Rectangle GameModel::GetPlayerHitBox(int num) const {
	if (num == 1) {
		return p1Data.hitBox;
	}
	else {
		return p2Data.hitBox;
	}
}
