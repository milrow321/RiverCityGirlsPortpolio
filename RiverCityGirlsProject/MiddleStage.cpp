#include "stdafx.h"
#include "MiddleStage.h"
#include "StageManager.h"
#include "EnemyManager.h"

void MiddleStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);

	int linePos[10][4] = { {0, 835, _background->getWidth() * _bgScale, 835}, // 하
							{0, 490, _background->getWidth() * _bgScale, 490}, // 상 첫번째          
						{920, 490, 921, 491}, // 상 두번째
						{0, 545, 1, 545}, // 상 세번째
						{1640, 545, 1641, 544}, // 상 네번째
						{1745, 440, 1741, 440}, // 상 다섯번째
						{_background->getWidth() * _bgScale - 1, 10, _background->getWidth() * _bgScale - 1, 100}, // 오른쪽 수직선
						{1, 10, 1, 100}, // 왼쪽 수직선
						{_background->getWidth() * _bgScale, 795, _background->getWidth() * _bgScale - 795, 0}, // 우
						{0, 750, 750, 0} }; // 좌
	LINEAR_VALUE_TYPE lineTypes[10] = { LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::RIGHT,
										LINEAR_VALUE_TYPE::LEFT,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP };
	float lineRange[10][4] = { {0, _background->getWidth() * _bgScale} , // 하
								{260, 920}, // 상 첫번째
								{920, 975}, // 상 두번째
								{975, 1640}, // 상 세번째
								{1640, 1745}, // 상 네번째
								{1745, 2505}, // 상 다섯번째
								{795, 835}, // 오른쪽 수직선
								{750, 835}, // 왼쪽 수직선
								{2505, _background->getWidth() * _bgScale}, // 우
								{0, 260} }; // 좌
	for (int i = 0; i < 10; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
	}

	//Object 배치
	_objectManager->spawnObject(OBJECT_TYPE::SNACKMACHINE, Vector3(2420, 0, 470), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::TABLE01, Vector3(500, 0, 680), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::TABLE06, Vector3(1120, 0, 750), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::TABLE07, Vector3(1740, 0, 750), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::TABLE03, Vector3(2360, 0, 680), DIRECTION::LEFT);

	_objectManager->spawnObject(OBJECT_TYPE::schoolGirlA_idle01, Vector3(300, 0, 500), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::schoolGirlE_idle01, Vector3(400, 0, 500), DIRECTION::LEFT);

	_objectManager->spawnObject(OBJECT_TYPE::schoolGirlB_idle01, Vector3(400, 0, 750), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::schoolBoyA_idle01, Vector3(550, 0, 750), DIRECTION::LEFT);

	_objectManager->spawnObject(OBJECT_TYPE::schoolBoyE_idle01, Vector3(2100, 0, 470), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::schoolGirlA_idle01, Vector3(2200, 0, 470), DIRECTION::LEFT);

	_objectManager->spawnObject(OBJECT_TYPE::workingFemaleA, Vector3(2500, 0, 900), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::workingMaleD, Vector3(2700, 0, 900), DIRECTION::LEFT);

	_isQuestClear = true;
	_isQuesting = false;
	_maxRestCount = 4;
	_restCount = _maxRestCount;

	DOOR_STATE doorStates[3] = {DOOR_STATE::UNLOCK, DOOR_STATE::SHOP, (_isQuestClear)?DOOR_STATE::UNLOCK:DOOR_STATE::LOCK};
	Vector3 doorPoses[3] = {Vector3(80, 0, 500),
							Vector3(1165, 0, 360) ,
							Vector3(2710, 0, 500) };
	for (int i = 0; i < 3; i++)
	{
		tagDoorInfo door;
		door.doorState = doorStates[i];
		door.pos = doorPoses[i];
		_doorInfos.push_back(door);
	}

	string destNames[3] = {"START_STAGE", "SHOP", "BOSS_STAGE"};
	Vector3 destPoses[3] = {Vector3(1250, -(_player->getSize().y * 0.5), 400),
							Vector3() ,
							Vector3(1150, -(_player->getSize().y * 0.5), 750) };
	for(int i = 0 ; i < 3 ; i++)
	{ 
		tagDoorDestination doorDest;
		doorDest.destName = destNames[i];
		doorDest.destPos = destPoses[i];
		_doorDestination.push_back(doorDest);
	}

	_respawnCool = 2;
	_respawnPos[0] = Vector2(1000, 650);
	_respawnPos[1] = Vector2(1750, 650);
}

void MiddleStage::release()
{
	Stage::release();
}

void MiddleStage::enter()
{
	Stage::enter();
	SOUND_MANAGER->stop("BGM_Hall");
	SOUND_MANAGER->play("BGM_Hall", 0.3f);
}

void MiddleStage::exit()
{
	SOUND_MANAGER->stop("BGM_Hall");
}

Stage * MiddleStage::update()
{
	for (int i = 0; i < _doorInfos.size(); i++)
	{
		if (_isQuesting) continue;
		if (_doorInfos[i].doorState == DOOR_STATE::LOCK) continue;
		if (Vector3::distance(_doorInfos[i].pos, _player->getPosition()) < 250.0f)
		{
			if (KEY_MANAGER->isOnceKeyDown('Z'))
			{
				switch (_doorInfos[i].doorState)
				{
				case DOOR_STATE::SHOP:
				{
					_stageManager->openShop();
					return nullptr;
				}
				break;
				case DOOR_STATE::UNLOCK:
				{
					_enemyManager->clearEnemy();
					_player->setPosition(_doorDestination[i].destPos);
					_player->setIdleState();
					return _stageManager->getStage(_doorDestination[i].destName);
				}
				}
			}
		}
	}

	_lastEnemyNum = _enemyManager->getEnemyCount();
	_objectManager->update();
	_objectManager->isEat(_player);
	_enemyManager->update();

	if (!_isQuestClear && !_isQuesting && _player->getPosition().x >= 1350)
	{
		// 퀘스트 시작
		_isQuesting = true;

		// 좌우로 움직이지 못하는 라인 추가
		float linePos[2][4] = { {1350 - WINSIZEX / 2, 1, 1350 - WINSIZEX / 2, 2}, {1350 + WINSIZEX / 2, 1, 1350 + WINSIZEX / 2, 2}};
		float lineRange[2][2] = { {0, 3000}, {0, 3000} };
		LINEAR_VALUE_TYPE lineTypes[2] = {LINEAR_VALUE_TYPE::LEFT,
											LINEAR_VALUE_TYPE::RIGHT};
		for (int i = 0; i < 2; i++)
		{
			LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
			_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
		}

		// UI 추가
		_stageManager->setLockLevel(4);
		_deadNum = 0;

	}

	_respawnCool -= TIME_MANAGER->getElapsedTime();
	

	if (!_isQuesting)
	{
		CAMERA_MANAGER->setXY(CAMERA_MANAGER->convertV3ToV2(_player->getPosition()));
	}
	else
	{
		CAMERA_MANAGER->setXY(Vector2(1350, 670));
		if (_lastEnemyNum != _enemyManager->getEnemyCount())
		{
			_deadNum++;
			if (_deadNum == 4)
			{
				SOUND_MANAGER->stop("UI_lock");
				SOUND_MANAGER->play("UI_lock", 1);
				_isQuesting = false;
				_isQuestClear = true;
				_stageManager->setLockLevel(0);
				_restrictLines.erase(_restrictLines.end() - 1);
				_restrictLines.erase(_restrictLines.end() - 1);
				_doorInfos[2].doorState = DOOR_STATE::UNLOCK;
				_stageManager->setDoorInfo(_doorInfos);
			}
			else if (_deadNum == 3)
			{
				SOUND_MANAGER->stop("UI_lock");
				SOUND_MANAGER->play("UI_lock", 1);
				_stageManager->setLockLevel(1);
			}
			else if (_deadNum == 2)
			{
				SOUND_MANAGER->stop("UI_lock");
				SOUND_MANAGER->play("UI_lock", 1);
				_stageManager->setLockLevel(2);
			}
			else if (_deadNum == 1)
			{
				SOUND_MANAGER->stop("UI_lock");
				SOUND_MANAGER->play("UI_lock", 1);
				_stageManager->setLockLevel(3);
			}
		}

		if (_enemyManager->getEnemyCount() < 3 && _respawnCool < 0 && _restCount > 0)
		{
			_restCount--;
			_respawnCool = 2;
			int randomType = RANDOM->getInt(3);
			int randomRespawn = RANDOM->getInt(2);
			switch (randomType)
			{
			case 0:
			{
				_enemyManager->spawnEnemy(ENEMY_TYPE::SCHOOL_BOY, _respawnPos[randomRespawn]);
			}
			break;
			case 1:
			{
				_enemyManager->spawnEnemy(ENEMY_TYPE::SCHOOL_GIRL, _respawnPos[randomRespawn]);
			}
			break;
			case 2:
			{
				_enemyManager->spawnEnemy(ENEMY_TYPE::CHEER_GIRL, _respawnPos[randomRespawn]);
			}
			break;
			}
		}
	}

	return nullptr;
}

void MiddleStage::render()
{
	Vector2 bgCenter;
	bgCenter.x = _background->getWidth() * _bgScale * 0.5;
	bgCenter.y = _background->getHeight() * _bgScale * 0.5;
	_background->setScale(_bgScale);
	CAMERA_MANAGER->render(_background, bgCenter);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::STAGE))
	{
		for (int i = 0; i < _restrictLines.size(); i++)
		{
			_restrictLines[i]->render();
		}
	}


	_objectManager->render();
	_enemyManager->render();
}

void MiddleStage::gameOver()
{
	Stage::enter();
	_enemyManager->clearEnemy();
	if (_isQuesting)
	{
		_stageManager->setLockLevel(-1);
		_restrictLines.erase(_restrictLines.end() - 1);
		_restrictLines.erase(_restrictLines.end() - 1);
	}
	_isQuesting = false;
	_restCount = _maxRestCount;
	_player->setPosition(Vector3(200, -(_player->getSize().y * 0.5), 670));
	_player->setHp(_player->getMaxHp());
	_player->setIdleState();
	_respawnCool = 2;
}
