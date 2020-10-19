#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

class TableObject :	public Object
{
private:
	RestrictMoveRect* _restrictRect;
	int _collisionOffsetX = 5;
	int _collisionOffsetZ = 0;
public:
	TableObject(Vector3 position, DIRECTION direction, int type);

	virtual void update();
	virtual void release();
	virtual void render();
	void collision(Vector3 * newPoses, GameObject * gameObject);
};

