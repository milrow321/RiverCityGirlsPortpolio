#pragma once
#include "GameObject.h"
#include "Player.h"

enum class OBJECT_STATE : int
{
	IDLE, // 기본 대기 상태
	REACTION, // 반응중인 상태
	BROKEN, // 이미 깨져서 이제 반응 안하는 상태
	INACTIVE // 아이템을 먹거나 시간이 다되어서 사라지는 상태
};

class ObjectManager;

class Object :  public GameObject
{
protected:
	ObjectManager* _objectManager;
	OBJECT_STATE _state;					// object state
	DIRECTION _direction;

	Image* _img;								//image
	float _imgScale = 3;
	Animation* _ani;

	bool _isCollision = false;

public:
	Object() {};
			//
	Object(Vector3 position, DIRECTION direction, int imageType);

	inline OBJECT_STATE getState() { return _state; }

	void setObjectManager(ObjectManager* objectManager) { _objectManager = objectManager; }

	virtual void update();
	virtual void release();
	virtual void render();
	virtual void collision(Vector3* newPoses, GameObject* gameObject);
	virtual void reaction();

	void isEat(Player* gameObject); // 위치가 겹쳤는지 체크하기 위해 공통으로 사용되는 위치 체크 함수
	virtual void eatEffect(Player* gameObject); // 위치가 겹쳤을 때 호출되는 함수, 각 오브젝트별로 구현하기
	bool getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type); // 맞았는지 체크하기 위해 공통으로 사용되는 충돌 처리 함수
	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type); // 맞았을 때 호출되는 함수, 각 오브젝트별로 구현하기
	float getCenterBottom(Vector2 pos);
};

