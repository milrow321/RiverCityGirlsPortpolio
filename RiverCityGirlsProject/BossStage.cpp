#include "stdafx.h"
#include "BossStage.h"
#include "StageManager.h"
#include "EnemyManager.h"
#include "ObjectManager.h"

void BossStage::init(Image * background, float bgScale)
{
	Stage::init(background, bgScale);

	int linePos[6][4] = { {0, 1080, _background->getWidth() * _bgScale, 1080}, // ж
							{0, 475, _background->getWidth() * _bgScale, 475}, // 鼻       
						{_background->getWidth() * _bgScale - 1, 475, _background->getWidth() * _bgScale - 1, 476}, // 辦 熱霜
						{1, 475, 1, 476}, // 謝 熱霜
						{2205, 475, 2206, 476}, // 辦
						{0, 1050, 1050, 0} }; // 謝
	LINEAR_VALUE_TYPE lineTypes[6] = { LINEAR_VALUE_TYPE::DOWN,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::RIGHT,
										LINEAR_VALUE_TYPE::LEFT,
										LINEAR_VALUE_TYPE::UP,
										LINEAR_VALUE_TYPE::UP };
	float lineRange[6][4] = { {0, _background->getWidth() * _bgScale} , // ж
								{575, 2205}, // 鼻
								{1040, 1080}, // 辦 熱霜
								{1050, 1080}, // 謝 熱霜
								{2205, _background->getWidth() * _bgScale}, // 辦
								{0, 575} }; // 謝
	for (int i = 0; i < 6; i++)
	{
		LinearFunc line = LinearFunc::getLinearFuncFromPoints(Vector2(linePos[i][0], linePos[i][1]), Vector2(linePos[i][2], linePos[i][3]));
		_restrictLines.push_back(new RestrictMoveLine(line, lineTypes[i], lineRange[i][0], lineRange[i][1]));
	}

	//Object 寡纂
	_objectManager->spawnObject(OBJECT_TYPE::PILLAR, Vector3(900, 150, 650), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::PILLAR, Vector3(700, 150, 900), DIRECTION::LEFT);
	_objectManager->spawnObject(OBJECT_TYPE::PILLAR, Vector3(1900, 150, 650), DIRECTION::RIGHT);
	_objectManager->spawnObject(OBJECT_TYPE::PILLAR, Vector3(2100, 150, 900), DIRECTION::RIGHT);


	DOOR_STATE doorStates[2] = { DOOR_STATE::LOCK, DOOR_STATE::LOCK };
	Vector3 doorPoses[2] = { Vector3(280, 0, 620),
							Vector3(1390, 0, 290)};
	for (int i = 0; i < 2; i++)
	{
		tagDoorInfo door;
		door.doorState = doorStates[i];
		door.pos = doorPoses[i];
		_doorInfos.push_back(door);
	}

	string destNames[2] = { "MIDDLE_STAGE", "NEXT_STAGE"};
	Vector3 destPoses[2] = { Vector3(2560, -(_player->getSize().y * 0.5), 650),
							Vector3()};

	for (int i = 0; i < 2; i++)
	{
		tagDoorDestination doorDest;
		doorDest.destName = destNames[i];
		doorDest.destPos = destPoses[i];
		_doorDestination.push_back(doorDest);
	}
}

void BossStage::release()
{
	Stage::release();
}

void BossStage::enter()
{
	Stage::enter();
	
	SOUND_MANAGER->stop("Boss_StageBGM");
	SOUND_MANAGER->play("Boss_StageBGM", 0.3);

	if (_enemyManager->getEnemyCount() < 1)
	{
		_stageManager->startDialogue(BossChapter::BATTLE_BEFORE);
	}
}

void BossStage::exit()
{

}

Stage * BossStage::update()
{
	for (int i = 0; i < _doorInfos.size(); i++)
	{
		if (_doorInfos[i].doorState == DOOR_STATE::LOCK) continue;
		if (Vector3::distance(_doorInfos[i].pos, _player->getPosition()) < 250.0f)
		{
			if (KEY_MANAGER->isOnceKeyDown('Z'))
			{
				switch (_doorInfos[i].doorState)
				{
				case DOOR_STATE::SHOP:
				{

				}
				break;
				case DOOR_STATE::UNLOCK:
				{
					_player->setPosition(_doorDestination[i].destPos);
					_player->setIdleState();
					return _stageManager->getStage(_doorDestination[i].destName);
				}
				}
			}
		}
	}

	if (_enemyManager->getEnemyCount() < 1)
	{
		_enemyManager->spawnEnemy(ENEMY_TYPE::BOSS, Vector2(1600, 750));
	}

	_objectManager->update();
	_objectManager->isEat(_player);
	_enemyManager->update();

	CAMERA_MANAGER->setXY(CAMERA_MANAGER->convertV3ToV2(_player->getPosition()));

	return nullptr;
}

void BossStage::render()
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

void BossStage::gameOver()
{
	Stage::enter();
	_enemyManager->clearEnemy();
	_player->setPosition(Vector3(1150, -(_player->getSize().y * 0.5), 750));
	_player->setIdleState();
	_player->setHp(_player->getMaxHp());
}

