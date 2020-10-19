#pragma once
#include "PlayerState.h"
class GuardState : public PlayerState
{
	
public:

	virtual void enter(Player& player);
	virtual void exit(Player& player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	
};

