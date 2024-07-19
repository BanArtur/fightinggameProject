#include "Moves.h"

Moves::Moves() {

	std::vector<std::pair<int, MoveFrame>> toBeAdded;
	MoveFrame tmp;

	//idle
	{
		idle.allowedTransitions = {
			PlayerStateEnum::MovingLeft,
			PlayerStateEnum::MovingRight,
			PlayerStateEnum::AttackL,
			PlayerStateEnum::AttackH,
			PlayerStateEnum::HitStun
		};

		std::vector<std::pair<int, MoveFrame>> idleFrames = {
			{18,MoveFrame{ glm::vec2(0,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 0 }},
			{12,MoveFrame{ glm::vec2(0,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 1 }},
			{12,MoveFrame{ glm::vec2(0,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 2 }}
		};

		for (std::pair<int, MoveFrame> m : idleFrames) {
			for (int i = 0; i < m.first; i++) {
				idle.frames.push_back(m.second);
			}
		}
		idle.relatedState = PlayerStateEnum::Idle;
		idle.damage = 0;
		idle.hitStun = 0;
	}

	//moveRight
	{
		moveRight.allowedTransitions = {
			PlayerStateEnum::MovingLeft,
			PlayerStateEnum::Idle,
			PlayerStateEnum::AttackL,
			PlayerStateEnum::AttackH,
			PlayerStateEnum::HitStun
		};

		std::vector<std::pair<int, MoveFrame>> moveRightFrames = {
			{6,MoveFrame{ glm::vec2(0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 0 }},
			{6,MoveFrame{ glm::vec2(0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 1 }},
			{6,MoveFrame{ glm::vec2(0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 2 }},
			{6,MoveFrame{ glm::vec2(0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 3 }},
			{6,MoveFrame{ glm::vec2(0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 4 }}
		};

		for (std::pair<int, MoveFrame> m : moveRightFrames) {
			for (int i = 0; i < m.first; i++) {
				moveRight.frames.push_back(m.second);
			}
		}

		moveRight.relatedState = PlayerStateEnum::MovingRight;
		moveRight.damage = 0;
		moveRight.hitStun = 0;
	}

	//moveLeft
	{
		moveLeft.allowedTransitions = {
			PlayerStateEnum::MovingRight,
			PlayerStateEnum::Idle,
			PlayerStateEnum::AttackL,
			PlayerStateEnum::AttackH,
			PlayerStateEnum::HitStun
		};

		std::vector<std::pair<int, MoveFrame>> moveLeftFrames = {
			{6,MoveFrame{ glm::vec2(-0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 0 }},
			{6,MoveFrame{ glm::vec2(-0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 1 }},
			{6,MoveFrame{ glm::vec2(-0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 2 }},
			{6,MoveFrame{ glm::vec2(-0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 3 }},
			{6,MoveFrame{ glm::vec2(-0.5f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 4 }}
		};

		for (std::pair<int, MoveFrame> m : moveLeftFrames) {
			for (int i = 0; i < m.first; i++) {
				moveLeft.frames.push_back(m.second);
			}
		}

		moveLeft.relatedState = PlayerStateEnum::MovingLeft;
		moveLeft.damage = 0;
		moveLeft.hitStun = 0;
	}

	//attackLight
	{
		attackLight.allowedTransitions = {
			PlayerStateEnum::HitStun
		};

		std::vector<std::pair<int, MoveFrame>> attackLightFrames = {
			{1,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 0 }},
			{3,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 1 }},
			{3,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 2 }},
			{5,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(-5,7), glm::vec2(24,41)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 3 }}, //*
			{4,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(-5,7), glm::vec2(24,41)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 4 }},
			{2,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(-5,7), glm::vec2(24,41)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 5 }},
			{2,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(-5,7), glm::vec2(24,41)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 6 }}, //*
			{4,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 7 }}
		};

		for (std::pair<int, MoveFrame> m : attackLightFrames) {
			for (int i = 0; i < m.first; i++) {
				attackLight.frames.push_back(m.second);
			}
		}

		attackLight.relatedState = PlayerStateEnum::AttackL;
		attackLight.damage = 4;
		attackLight.hitStun = 15;
	}

	//attackHeavy
	{
		attackHeavy.allowedTransitions = {
			PlayerStateEnum::HitStun
		};

		std::vector<std::pair<int, MoveFrame>> attackHeavyFrames = {
			{3,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 0 }},
			{2,MoveFrame{ glm::vec2(5.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 1 }},
			{3,MoveFrame{ glm::vec2(5.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-8,0) ,glm::vec2(8,30)}, 2 }},
			{2,MoveFrame{ glm::vec2(2.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-9,0) ,glm::vec2(10,30)}, 3 }},
			{5,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(5,1), glm::vec2(55,25)}, {glm::vec2(-9,0) ,glm::vec2(10,30)}, 4 }}, //*
			{3,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(5,2), glm::vec2(54,25)}, {glm::vec2(-9,0) ,glm::vec2(10,30)}, 5 }}, 
			{3,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(5,5), glm::vec2(53,25)}, {glm::vec2(-9,0) ,glm::vec2(10,30)}, 6 }}, 
			{3,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(5,15), glm::vec2(40,25)}, {glm::vec2(-9,0) ,glm::vec2(10,30)}, 7 }}, 
			{3,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(5,18), glm::vec2(36,25)}, {glm::vec2(-9,0) ,glm::vec2(10,30)}, 8 }}, //*
			{8,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-9,0) ,glm::vec2(10,30)}, 9 }}
		};

		for (std::pair<int, MoveFrame> m : attackHeavyFrames) {
			for (int i = 0; i < m.first; i++) {
				attackHeavy.frames.push_back(m.second);
			}
		}

		attackHeavy.relatedState = PlayerStateEnum::AttackH;
		attackHeavy.damage = 20;
		attackHeavy.hitStun = 40;
	}

	//hitStun
	{
		hitStun.allowedTransitions = {
			PlayerStateEnum::HitStun
		};

		std::vector<std::pair<int, MoveFrame>> hitStunFrames = {
			{1,MoveFrame{ glm::vec2(0.0f,0), {glm::vec2(0,0), glm::vec2(0,0)}, {glm::vec2(-7,0) ,glm::vec2(7,30)}, 0 }}
		};

		for (std::pair<int, MoveFrame> m : hitStunFrames) {
			for (int i = 0; i < m.first; i++) {
				hitStun.frames.push_back(m.second);
			}
		}

		hitStun.relatedState = PlayerStateEnum::HitStun;
		hitStun.damage = 0;
		hitStun.hitStun = 0;
	}
}