#include "Player.h"

Player::Player(PlayerData& out) : outLoc(out) {

}

Player::~Player() {

}


void Player::Init(glm::vec2 pos, int ori) {
	position = pos;
	orientation = ori;
	health = 100;
	state.Init();
	moveConnected = false;
}

void Player::PlayerAction(PlayerStateEnum inputAction) {
	state.Action(inputAction);
}

void Player::GameAdvance() {
	//TODO: return PlayerData
	if (state.IsNewMove()) {
		moveConnected = false;
	}
	state.GameAdvance();
	glm::vec2 movement = state.GetMove().velocity;
	if ((state.GetState() == PlayerStateEnum::AttackL || state.GetState() == PlayerStateEnum::AttackH)) {
		movement.x *= orientation;
	}
	if (movement.x + position.x < leftPosLimit) {
		position += movement;
		position.x = leftPosLimit;
	}
	else if (movement.x + position.x > rightPosLimit) {
		position += movement;
		position.x = rightPosLimit;
	}
	else {
		position += movement;
	}
	outLoc.pos = position;
	outLoc.state = state.GetState();
	outLoc.hurtBox = state.GetMove().hurtbox;
	outLoc.hitBox = state.GetMove().hitbox;
	if (orientation == -1) {
		outLoc.hurtBox = FlipRectangle(outLoc.hurtBox);
		outLoc.hitBox = FlipRectangle(outLoc.hitBox);
	}
	outLoc.hurtBox.lowerLeft += position;
	outLoc.hurtBox.upperRight += position;
	outLoc.hitBox.lowerLeft += position;
	outLoc.hitBox.upperRight += position;
	outLoc.damage = state.GetDamage();
	outLoc.hitStun = state.GetHitStun();
	outLoc.moveConnected = moveConnected;
}

void Player::moveConnect() {
	moveConnected = true;
}

void Player::ChangePos(glm::vec2 pos) {
	if (pos.x < leftPosLimit) {
		glm::vec2 tmp = pos;
		tmp.x = leftPosLimit;
		position = tmp;
	}
	else if (pos.x > rightPosLimit) {
		glm::vec2 tmp = pos;
		tmp.x = rightPosLimit;
		position = tmp;
	}
	else {
		position = pos;
	}

}

void Player::ChangeOrientation(int newori) {
	orientation = newori;
}

void Player::Damage(int damage, int hitStun) {
	health -= damage;
	state.Stun(hitStun, PlayerStateEnum::HitStun);
}

glm::vec2 Player::GetPosition() const {
	return position;
}

int Player::GetOrientation() const {
	return orientation;
}

int Player::GetFrameNum() const {
	return state.GetFrameNum();
}

int Player::GetHealth() const {
	return health;
}

PlayerStateEnum Player::GetState() const {
	return state.GetState();
}
