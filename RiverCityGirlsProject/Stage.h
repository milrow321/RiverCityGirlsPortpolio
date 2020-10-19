#pragma once
#include "linearFunc.h"
#include "GameObject.h"
#include "RestrictMoveLine.h"
#include "UIManager.h"
#include "DialogueManager.h"

class StageManager;
class ObjectManager;
class EnemyManager;
class Player;

struct tagDontMove // 이동 영역을 제한하기 위한 구조체
{
	LinearFunc line; // 선분
	LINEAR_VALUE_TYPE type; // 이 선분 어디를 못지나가게 할 것인가?
};

struct tagDoorDestination
{
	string destName;
	Vector3 destPos;
};

class Stage
{
protected:
	StageManager* _stageManager; 
	ObjectManager* _objectManager; 
	EnemyManager* _enemyManager;
	Player* _player;
	
	Image* _background; // 배경 이미지
	float _bgScale; // 배경이미지 배율
	vector<RestrictMoveLine*> _restrictLines; // 스테이지의 이동 영역을 제한
	vector<tagDoorInfo> _doorInfos; // 스테이지의 문
	vector<tagDoorDestination> _doorDestination; // 스테이지의 문 목적지

public:
	virtual void init(Image* background, float bgScale);
	virtual void release();
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();

	void setStageManager(StageManager* stageManager) { _stageManager = stageManager; }
	void setPlayer(Player* player) { _player = player; }

	// 게임 오브젝트를 가능한만큼 이동시킴
	void moveGameObject(GameObject* gameObject, Vector3 move);
	bool attack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect rc, float damage, ATTACK_TYPE type, vector<OBJECT_TEAM> getAttack);

	void setBossUiVisible(bool isVisible);
	void setBossUi(float currHp, float maxHp);
	void startDialogue(BossChapter chapter);
	bool isDialoging();
	void setHeart(bool isVisible);
	void spawnMoney(Vector3 pos);

	virtual void gameOver();

	float getCenterBottom(Vector3 pos);
	Vector3 getPlayerPosition();
	float getPlayerHp();
};