#pragma once
#include "enemyManager.h"
#include "enemy.h"

enum class BOSS_PHASE
{
	PHASE_1,
	PHASE_2,
	PHASE_3,
	DEFEAT
};

enum class BOSS_STATE
{
	IDLE, // 대기 상태
	WALK, // 플레이어에게 걸어오는 상태, 여러 패턴 사용 가능
	LAUGH, // 웃는 상태, 딜 타이밍
	GROUND, // 앉아있는 상태
	STAND_UP, // 앉아있다 일어나는 상태
	METEOR_ATTACK, // 점프 후 내려찍기 공격
	METEOR_ATTACK_DELAY, // 내려찍기 후 아파하기
	ROAR, // 페이즈 전환할때 울부짖음
	STRONG_PUNCH, // 기모아서 펀치 떄리기
	WEAK_PUNCH_COMBO, // 3대 때리기
	DASH_ATTACK, // 플레이어 호밍하면서 달려옴
	GET_HIT, // 맞는 상태
	GROUND_HIT, // 앉아있다가 맞는 상태
	KNOCKDOWN, // 맞아 날라가는 상태
};

class Boss : public Enemy
{
private:
	BOSS_PHASE _phase;
	BOSS_STATE _bossState;

	float _combo; // 3단 콤보까지는 맞아줌
	float _electricTime;
	int _count; // 여러 방면에서 여러 상태에서 사용되는 카운트

	bool _checkDialog;
	int _maxHp;

public:
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setState(BOSS_STATE state, DIRECTION direction, bool initTime);
	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	void setAttackState(BOSS_PHASE phase, float playerDistance);
};

