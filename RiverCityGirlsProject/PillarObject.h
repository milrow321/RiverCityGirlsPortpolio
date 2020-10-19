#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

class PillarObject :
	public Object
{
private:
	RestrictMoveRect* _restrictRect;
	int _collisionOffsetX = 0;
	int _collisionOffsetZ = 30;
public:
	PillarObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	void collision(Vector3 * newPoses, GameObject * gameObject);
	bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
};

