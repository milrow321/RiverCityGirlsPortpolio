#include "stdafx.h"
#include "StageManager.h"
#include "StartStage.h"
#include "MiddleStage.h"
#include "BossStage.h"


void StageManager::init()
{
	Stage* stage_1 = new StartStage;
	stage_1->setStageManager(this);
	stage_1->setPlayer(_player);
	stage_1->init(IMAGE_MANAGER->findImage("STAGE_1"), 3);

	_stageMap["START_STAGE"] = stage_1;

	Stage* stage_2 = new MiddleStage;
	stage_2->setStageManager(this);
	stage_2->setPlayer(_player);
	stage_2->init(IMAGE_MANAGER->findImage("STAGE_2"), 3);
	_stageMap["MIDDLE_STAGE"] = stage_2;

	Stage* stage_3 = new BossStage;
	stage_3->setStageManager(this);
	stage_3->setPlayer(_player);
	stage_3->init(IMAGE_MANAGER->findImage("STAGE_BOSS_BEFORE"), 3);
	_stageMap["BOSS_STAGE"] = stage_3;

	_currStage = _stageMap["START_STAGE"];
	//_currStage = _stageMap["MIDDLE_STAGE"];
	//_currStage = _stageMap["BOSS_STAGE"];
	_currStage->enter();
	_player->setStartState();
	
	_isGameOver = false;

	TIME_MANAGER->update(60);
}

void StageManager::release()
{
	for (auto iter = _stageMap.begin(); iter != _stageMap.end(); iter++)
	{
		iter->second->release();
		delete iter->second;
	}
	_stageMap.clear();
}
 
void StageManager::update()
{
	if (_isGameOver && !_uiManager->getHeart())
	{
		_currStage->gameOver();
		_isGameOver = false;
	}
	if (!_dgManager->getIsPlay() && !_uiManager->getShopUI())
	{
		if (_stageBuffer != nullptr)
		{
			_currStage->exit();
			_currStage = _stageBuffer;
			_currStage->enter();
		}

		_stageBuffer = _currStage->update();
		_player->update();
	}
}

void StageManager::render()
{
	_currStage->render();
	_player->render();
}

bool StageManager::playerAttack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	vector<OBJECT_TEAM> getAttack;
	getAttack.push_back(OBJECT_TEAM::ENEMY);
	getAttack.push_back(OBJECT_TEAM::OBJECT);
	return _currStage->attack(pos, size, team, attackRc, damage, type, getAttack);
}

void StageManager::setBossUiVisible(bool isVisible)
{
	_uiManager->setBossHpActive(isVisible);
}

void StageManager::setBossUi(float currHp, float maxHp)
{
	_uiManager->setBossHp(currHp, maxHp);
}

void StageManager::setLockLevel(int level)
{
	switch (level)
	{
	case 4:
	{
		_uiManager->setLock(LOCK_STATE::LOCK_4);
	}
	break;
	case 3:
	{
		_uiManager->setLock(LOCK_STATE::LOCK_3);
	}
	break;
	case 2:
	{
		_uiManager->setLock(LOCK_STATE::LOCK_2);
	}
	break;
	case 1:
	{
		_uiManager->setLock(LOCK_STATE::LOCK_1);
	}
	break;
	case 0:
	{
		_uiManager->setLock(LOCK_STATE::LOCK_0);
	}
	break;
	case -1:
	{
		_uiManager->setLock(LOCK_STATE::NORMAL);
	}
	break;
	}
}



void StageManager::setDoorInfo(vector<tagDoorInfo> doorInfos)
{
	_uiManager->setDoor(doorInfos);
}

void StageManager::openShop()
{
	_uiManager->setShopUI(true);
}

void StageManager::startDialogue(BossChapter keyname)
{
	_dgManager->startChapter(keyname);
}

bool StageManager::isDialoging()
{
	return _dgManager->getIsPlay();
}

void StageManager::setHeart(bool isVisible)
{
	_uiManager->setHeart(isVisible);
}

void StageManager::gameOver()
{
	_isGameOver = true;
	SOUND_MANAGER->stop("GameOver");
	SOUND_MANAGER->play("GameOver", 1);
	_uiManager->setHeart(true);
}
