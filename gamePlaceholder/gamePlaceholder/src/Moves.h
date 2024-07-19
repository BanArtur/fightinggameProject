#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "PlayerStateEnum.h"
#include "Geo.h"

#include <vector>
#include <utility>
#include <memory>

struct MoveFrame {
	glm::vec2 velocity;

	Rectangle hitbox;
	Rectangle hurtbox;

	int realFrame = 0;
};

struct Move
{
	std::vector<MoveFrame> frames;
	std::vector<PlayerStateEnum> allowedTransitions;
	PlayerStateEnum relatedState;
	int damage;
	int hitStun;
};


class Moves {
private:
	Move idle;
	Move moveRight;
	Move moveLeft;
	Move attackLight;
	Move attackHeavy;
	Move hitStun;
	Move blockStun;

	Moves();
public:
	static Moves& GetMovesInstance() {
		static Moves INSTANCE;
		return INSTANCE;
	}
	Move& GetIdle() {
		return idle;
	}
	Move& GetMoveRight() {
		return moveRight;
	}
	Move& GetMoveLeft() {
		return moveLeft;
	}
	Move& GetAttackLight() {
		return attackLight;
	}
	Move& GetAttackHeavy() {
		return attackHeavy;
	}
	Move& GetMove(PlayerStateEnum state) {
		switch (state)
		{
		case Idle:
			return idle;
			break;
		case MovingLeft:
			return moveLeft;
			break;
		case MovingRight:
			return moveRight;
			break;
		case AttackL:
			return attackLight;
			break;
		case AttackH:
			return attackHeavy;
			break;
		case HitStun:
			return hitStun;
			break;
		default:
			break;
		}
	}
};