#pragma once
#include "PlayerState.h"

class IdleState : public PlayerState
{
private:

public:
	IdleState();

	virtual void exit(Player& player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	virtual void enter(Player& player);
};
