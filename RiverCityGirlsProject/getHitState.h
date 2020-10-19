#pragma once
#include "PlayerState.h"

enum class GET_HIT_STATE
{
	HIT,//맞아서 경직되는 상태
	HIT2,//맞아서 경직되는 상태2
	KNOCK_DOWN,//맞아서 누운 상태
	STAND_UP,//DOWN에서 일어나는 상태
	STUN,
	GAME_OVER //체력이 0이 되었을 때 상태
};

class getHitState : public PlayerState
{
private: 
	float _getHitTerm;
	float lastPlayerY;
	float currentPlayerY;
	float _downTime;
	float _airBorne;
	float _hitDelay;
	float _stunTime;

	bool _isDead;

	ATTACK_TYPE _getHitType;
	Synthesize(GET_HIT_STATE, _getHitState,GetHitState)

	Vector3 moveDir;
	//int _hitAniArr[10];

public:
	virtual void enter(Player& player);
	virtual void exit(Player& player);
	virtual PlayerState* update(Player& player);
	virtual void render(Player& player);
	void setGetHitAni(Player& player);
	void setMotalTime(Player& player);
};

