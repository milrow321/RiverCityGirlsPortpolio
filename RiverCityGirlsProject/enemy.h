#pragma once
#include "GameObject.h"
#include "Player.h"

class EnemyManager;

enum class ENEMY_STATE
{
	IDLE,
	WALK,
	RETURN,
	RUN,	 //RUN상태에서 ATTACK -> DASH_ATTACK
	JUMP,	 //JUMP상태에서 ATTACK -> JUMP_PUNCH
	ATTACK,	 //콤보처리 ATTACK 1 ~ 3
	DASHATTACK,
	JUMPATTACK,
	GUARD,	 
	HIT,
	KNOCKDOWN,	 //DOWN상태에서 피격 -> GROUND_HIT
	STANDUP,
	STUN,
	SKILL,	 //BOY(SANDTOSS), GIRL(), CHEER_GIRL()
	HELD//HELD상태에서 피격 -> HELD_HIT / 일정 시간 지나면 HELD_RELEASE
};

//좌우 디렉션은 플레이어 기준 setFrameY로 조정

class Enemy : public GameObject
{
protected:
	EnemyManager* _enemyManager;
	
	
	FloatRect _attackRc;	// 공격 판정 렉트
	FloatRect _viewRc;		
	int _attackS;	// 공격 판정할 프레임 저장용

	ENEMY_STATE _state;		// 상태

	Image* _enemyImg;
	Animation* _ani;		// 애니메이션
	DIRECTION _direction;	// 애니메이션 좌우 재생
	DIRECTION _moveTo;		// 현재 이동 방향
	ATTACK_TYPE _hitType;	//플레이어에게 받은 피격 타입

	int _hp;				//체력
	float _hitCount;        //피격 카운트
	int _attackCount;		//공격 카운트(카운트 처리로 플레이어 넉다운 시키기)
	float _jumpPower;       //점프파워
	float _gravity;         //중력값
	float _elapsedTime;		// 상태 전환 계산 타이머

	bool _isActive;			//적 개체 생존 여부
	bool _isAttack;			//공격 처리

	float _drawYFix;		//이미지 렌더 Y축 조정용

	
public:
	Enemy() {};
	~Enemy() {};

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setEnemyManager(EnemyManager* enemyManager) { _enemyManager = enemyManager; }
	bool getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	bool enemyAttack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	virtual bool hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	//Vector3 playerPos = _enemyManager->getPlayerPosition(); // 플레이어의 위치
	void setDirectionToPlayer();
	
	bool isActive() { return _isActive; }


};

