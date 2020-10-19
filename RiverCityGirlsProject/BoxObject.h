#pragma once
#include "Object.h"
class BoxObject :
	public Object
{
public:
	BoxObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
};

