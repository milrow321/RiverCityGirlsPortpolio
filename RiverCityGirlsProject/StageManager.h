#pragma once
#include "GameObject.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "Player.h"
#include "UIManager.h"
#include "DialogueManager.h"

class StageManager
{
private:
	map<string, Stage*> _stageMap;
	Stage* _currStage;
	Stage* _stageBuffer = nullptr;
	Player* _player;
	UIManager* _uiManager;
	DialogueManager* _dgManager;
	bool _isGameOver;

public:
	void init();

	void release();

	void update();

	void render();

	void moveGameObject(GameObject* gameObject, Vector3 moveDir) { _currStage->moveGameObject(gameObject, moveDir); }
	void setPlayer(Player* player) { _player = player; }
	void setUIManager(UIManager* uiManager) { _uiManager = uiManager; }
	void setDialogueManager(DialogueManager* dgManager) { _dgManager = dgManager; }

	bool playerAttack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type);

	void setBossUiVisible(bool isVisible);
	void setBossUi(float currHp, float maxHp);
	void setLockLevel(int level);

	float getCenterBottom(Vector3 pos) { return _currStage->getCenterBottom(pos); }
	Stage* getStage(string keyName) { return _stageMap[keyName]; }
	void setDoorInfo(vector<tagDoorInfo> doorInfos);
	void openShop();
	void startDialogue(BossChapter chapter);
	bool isDialoging();
	void setHeart(bool isVisible);
	void gameOver();
};

