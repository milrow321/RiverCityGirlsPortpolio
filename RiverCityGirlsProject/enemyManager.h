#pragma once
#include "GameObject.h"
#include <vector>
#include "DialogueManager.h"

class SchoolBoy;
class SchoolGirl;
class CheerGirl;
class Boss;
class Enemy;
class Stage;

enum class ENEMY_TYPE : int
{
	SCHOOL_BOY,
	SCHOOL_GIRL,
	CHEER_GIRL,
	BOSS
};


class EnemyManager
{
private:
	Stage* _stage;

	vector<Enemy*> _enemies;

protected:

public:
	EnemyManager() {};
	~EnemyManager() {};

	void init();
	void release();
	void update();
	void render();

	void moveEnemy(GameObject* enemy, Vector3 dir);
	void spawnEnemy(ENEMY_TYPE type, Vector2 pos);
	void clearEnemy();

	void setStage(Stage* stage) { _stage = stage; }
	int getEnemyCount() { return _enemies.size(); }
	Vector3 getPlayerPosition();
	
	float getPlayerHp();
	float getCenterBottom(Vector3 pos);
	
	
	void setBossUiVisible(bool isVisible);
	void setBossUi(float currHp, float maxHp);

	bool getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	bool enemyAttack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	bool enemyAttackObject(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);
	void startDialogue(BossChapter key);
	void spawnMoney(Vector3 pos);
	bool isDialoging();
	void setHeart(bool isVisible);
};

