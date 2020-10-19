#pragma once
#include "Object.h"
class MrRudis :
	public Object
{
private:
	Animation* _ani;

public:
	MrRudis(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3** pos);
	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type); // 맞았을 때 호출되는 함수, 각 오브젝트별로 구현하기
};

