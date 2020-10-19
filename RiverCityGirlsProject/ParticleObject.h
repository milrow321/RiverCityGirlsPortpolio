#pragma once
#include "Object.h"
class ParticleObject :  public Object
{
private:
	Vector2 _moveAngle;				// 이동 각도
	float _speed;					// 이동 속도
	float _rotateAngle;			// 회전각도
	float _gravity;					// 중력
	float _remainTime;				// 보이는 시간
	bool _isLand; // 착지하였음
	PARTICLE_TYPE _type;			// 생성할 타입

public:
	ParticleObject(PARTICLE_TYPE type, Vector3 pos, Vector2 angle, float speed, float time);
	virtual void update();
	virtual void release();
	virtual void render();
};

