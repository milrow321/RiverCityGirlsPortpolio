#pragma once
#include "Player.h"

class PlayerState 
{
protected:
	Image* _img;
	Animation* _ani;

public:
	virtual void enter(Player& player);
	virtual void exit(Player& player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
};




////
//class JumpState :public PlayerState
//{
//private:
//
//
//public:
//	JumpState();
//
//	virtual PlayerState* update(Player& player);
//	virtual void render(Player& player);
//	virtual void enter(Player& player);
//};
