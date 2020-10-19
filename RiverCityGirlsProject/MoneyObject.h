#pragma once
#include "Object.h"
class MoneyObject :	public Object
{
private:
	Animation* _ani;
	float _remainTime;
	int _randomSpawn;
	float _gravity;
public:
	MoneyObject(Vector3 pos);
	void update();
	void release();
	void render();
	void eatEffect(Player * player);
};

