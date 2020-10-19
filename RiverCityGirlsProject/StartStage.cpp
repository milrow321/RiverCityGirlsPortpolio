#include "stdafx.h"
#include "StartStage.h"
#include "MiddleStage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "StageManager.h"

void StartStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);

	int linePos[4][4] = { {0, 670, _background->getWidth() * _bgScale, 670}, // 하
							{0, 380, _background->getWidth() * _bgScale, 380}, // 상
						{_background->getWidth() * _bgScale, 770, _background->getWidth() * _bgScale - 770, 0}, // 우
						{0, 740, 740, 0} }; // 좌
	LINEAR_VALUE_TYPE lineTypes[4] = { LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP };
	float lineRange[4][4] = { {70, _background->getWidth() * _bgScale - 100} , // 하
								{360, 1625}, // 상
								{1625, _background->getWidth() * _bgScale - 100}, // 좌
								{70, 360} }; // 우
	for (int i = 0; i < 4; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
	}
	
	//Object 배치
	_objectManager->spawnObject(OBJECT_TYPE::DESK01, Vector3(460, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK02, Vector3(710, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK01, Vector3(970, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK03, Vector3(1230, 0, 510), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK04, Vector3(310, 0, 710), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK01, Vector3(560, 0, 710), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK02, Vector3(820, 0, 710), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::DESK05, Vector3(1080, 0, 710), DIRECTION::LEFT);

	_objectManager->spawnObject(OBJECT_TYPE::TEACHER_TABLE, Vector3(1650, 0, 800), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::FALL_CHAIR02, Vector3(1600, 0, 480), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::FALL_CHAIR01, Vector3(1800, 0, 620), DIRECTION::LEFT);

	_objectManager->spawnObject(OBJECT_TYPE::mrRudis, Vector3(1670, 0, 560), DIRECTION::LEFT);


	tagDoorInfo door;
	door.doorState = DOOR_STATE::UNLOCK;
	door.pos = Vector3(1430, 0, 220);
	_doorInfos.push_back(door);

	tagDoorDestination doorDest;
	doorDest.destName = "MIDDLE_STAGE";
	doorDest.destPos = Vector3(200, -(_player->getSize().y * 0.5), 670);
	_doorDestination.push_back(doorDest);
	
	_respawnPos[0] = Vector2(400, 600);
	_respawnPos[1] = Vector2(600, 600);
	_respawnPos[2] = Vector2(800, 600);
	_respawnPos[3] = Vector2(1000, 600);
	_respawnCool = 2;
}

void StartStage::release()
{
	Stage::release();
}

void StartStage::enter()
{
	Stage::enter();
	SOUND_MANAGER->stop("BGM_Classroom");
	SOUND_MANAGER->play("BGM_Classroom", 0.3f);
}

void StartStage::exit()
{
	Stage::exit();
	SOUND_MANAGER->stop("BGM_Classroom");
}

Stage * StartStage::update()
{
	for (int i = 0; i < _doorInfos.size(); i++)
	{
		if (_doorInfos[i].doorState == DOOR_STATE::LOCK) continue;
		if (Vector3::distance(_doorInfos[i].pos, _player->getPosition()) < 250.0f)
		{
			if (KEY_MANAGER->isOnceKeyDown('Z'))
			{
				_enemyManager->clearEnemy();
				_player->setPosition(_doorDestination[i].destPos);
				_player->setIdleState();
				return _stageManager->getStage(_doorDestination[i].destName);
			}
		}
	}

	_respawnCool -= TIME_MANAGER->getElapsedTime();

	if (_enemyManager->getEnemyCount() < 3 && _respawnCool <= 0) // 적 수가 3 이하라면 소환
	{
		_respawnCool = 1;
		int randomType = RANDOM->getInt(3);
		//int randomType = 0;
		int randomRespawn = RANDOM->getInt(4);
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

	_objectManager->update();
	_objectManager->isEat(_player);
	_enemyManager->update();

	CAMERA_MANAGER->setXY(CAMERA_MANAGER->convertV3ToV2(_player->getPosition()));

	return nullptr;
}

void StartStage::render()
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

void StartStage::gameOver()
{
	Stage::enter();
	_enemyManager->clearEnemy();
	_player->setPosition(Vector3(330, -105, 600));
	_player->setHp(_player->getMaxHp());
	_player->setStartState();
	_respawnCool = 2;
}
