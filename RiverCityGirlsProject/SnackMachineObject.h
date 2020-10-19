#pragma once
#include "Object.h"
#include "RestrictMoveRect.h"

class SnackMachineObject :
	public Object
{
private:
	RestrictMoveRect* _restrictRect;
	int _collisionOffsetX = 5;
	int _collisionOffsetZ = 0;
	Image* _pieceImg01;
	Image* _pieceImg02;
	Image* _pieceImg03;
	Image* _pieceImg04;
public:
	SnackMachineObject(Vector3 position, DIRECTION direction);

	virtual void update();
	virtual void release();
	virtual void render();
	void collision(Vector3 * newPoses, GameObject * gameObject);
	bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	//virtual void collision(Vector3** pos);
};

