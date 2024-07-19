#include "Player.h"

Player::Player() {

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

PlayerData Player::GameAdvance() {
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
	PlayerData ret;
	ret.pos = position;
	ret.state = state.GetState();
	ret.hurtBox = state.GetMove().hurtbox;
	ret.hitBox = state.GetMove().hitbox;
	if (orientation == -1) {
		ret.hurtBox = FlipRectangle(ret.hurtBox);
		ret.hitBox = FlipRectangle(ret.hitBox);
	}
	ret.hurtBox.lowerLeft += position;
	ret.hurtBox.upperRight += position;
	ret.hitBox.lowerLeft += position;
	ret.hitBox.upperRight += position;
	ret.damage = state.GetDamage();
	ret.hitStun = state.GetHitStun();
	ret.moveConnected = moveConnected;
	return ret;
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
