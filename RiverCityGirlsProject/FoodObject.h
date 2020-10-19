#pragma once
#include "Object.h"
class FoodObject :
	public Object
{
private:
	float _remainTime;
	int _randomSpawn;
public:
	FoodObject(Vector3 pos);
	virtual void update();
	virtual void release();
	virtual void render();

	//void isEat(Player* gameObject); // 위치가 겹쳤는지 체크하기 위해 공통으로 사용되는 위치 체크 함수
	virtual void eatEffect(Player* gameObject); // 위치가 겹쳤을 때 호출되는 함수, 각 오브젝트별로 구현하기
};

