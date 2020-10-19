#pragma once
#include "PlayerState.h"

class WalkState :public PlayerState
{
private:
	enum class WALK_STATE
	{
		MOVE,
		IDLE
	};

	float _initTime;
	float _gravityTime;

	WALK_STATE _state;

	Vector3 moveDir;
	float _startY;
public:
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
	virtual void exit(Player& player);
};