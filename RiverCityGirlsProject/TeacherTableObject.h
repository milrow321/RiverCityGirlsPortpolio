#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

class TeacherTableObject :
	public Object
{
private:
	RestrictMoveRect* _restrictRect;
	int _collisionOffsetX = 5;
	int _collisionOffsetZ = 20;
public:
	TeacherTableObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	void collision(Vector3 * newPoses, GameObject * gameObject);
};

