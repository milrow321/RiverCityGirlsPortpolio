#pragma once
#include "Enemy.h"
#include "EnemyManager.h"

class SchoolBoy : public Enemy
{
private:
	

public:
	SchoolBoy() {};
	~SchoolBoy() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);

	void setState(ENEMY_STATE state, DIRECTION direction);
	void setDirectionToPlayer();
};

