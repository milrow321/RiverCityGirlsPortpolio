#pragma once
#include "Object.h"
class ChairObject :
	public Object
{
public:
	ChairObject(Vector3 position, DIRECTION direction, int imageType);

	virtual void update();
	virtual void release();
	virtual void render();
};

