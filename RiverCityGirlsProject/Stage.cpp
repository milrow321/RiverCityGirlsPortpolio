#include "stdafx.h"
#include "Stage.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "Player.h"


void Stage::init(Image * background, float bgScale)
{
	_background = background;
	_bgScale = bgScale;
	
	_objectManager = new ObjectManager;
	_objectManager->init();
	_objectManager->setStageManager(_stageManager);

	_enemyManager = new EnemyManager;
	_enemyManager->setStage(this);
	_enemyManager->init();
}

void Stage::release()
{
	_objectManager->release();
	_enemyManager->release();
	for (int i = 0; i < _restrictLines.size(); i++)
	{
		delete _restrictLines[i];
	}
	_restrictLines.clear();
}

void Stage::enter()
{
	float maxWidth = _background->getWidth() * _bgScale;
	float maxHeight = _background->getHeight() * _bgScale;
	// 아래 위로 100만큼의 UI 공간 두기
	CAMERA_MANAGER->setConfig(0, 100, WINSIZEX, (WINSIZEY - 200), 0, 0, maxWidth - WINSIZEX, maxHeight - (WINSIZEY - 200));
	_stageManager->setDoorInfo(_doorInfos);
}

void Stage::exit()
{
	
}

Stage * Stage::update()
{
	return nullptr;
}

void Stage::render()
{	
}

// 게임 오브젝트가 이동가능한 영역까지 이동할 수 있도록 하는 함수
void Stage::moveGameObject(GameObject* gameObject, Vector3 move)
{
	if (move.x == 0 && move.y == 0 && move.z == 0) return;

	float dir[4][2] = { {-1.0, -1.0}, {-1.0, 1.0}, {1.0, -1.0}, {1.0, 1.0} }; // 각 대각 값
	float width = gameObject->getSize().x * 0.5; // 충돌 가로 길이
	float height = gameObject->getSize().z * 0.5; // 충돌 세로 길이

	Vector3 newPos = gameObject->getPosition() + move;
	Vector3 size = gameObject->getSize();
	if (newPos.y + (size.y / 2) > 0)
	{
		newPos.y = -(size.y / 2);
	}

	Vector3 newPoses[4]; // 새로운 좌표를 기준으로 하는 대각 위치
	for (int i = 0; i < 4; i++)
	{
		newPoses[i] = Vector3(newPos.x + dir[i][0] * width, newPos.y, newPos.z + dir[i][1] * height);
	}

	_objectManager->collision(newPoses, gameObject);

	// 선분과의 이동가능 비교는 x, z 비교
	for (int i = 0; i < _restrictLines.size(); i++)
	{
		_restrictLines[i]->checkCollision(newPoses, size);
	}

	// 물체와의 이동가능 비교는 x, y, z 비교, 물체를 올라탈 수도 있음
	
	newPos = Vector3(0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		newPos.x += newPoses[i].x;
		newPos.y += newPoses[i].y;
		newPos.z += newPoses[i].z;
	}
	newPos.x /= 4;
	newPos.y /= 4;
	newPos.z /= 4;

	gameObject->setPosition(newPos);
}

bool Stage::attack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect rc, float damage, ATTACK_TYPE type, vector<OBJECT_TEAM> getAttack)
{
	bool result = false;
	for (int i = 0; i < getAttack.size(); i++)
	{
		switch (getAttack[i])
		{
		case OBJECT_TEAM::PLAYER:
		{
			if (_player->getHit(pos, size, team, rc, damage, type))
			{
				result = true;
			}
		}
		break;
		case OBJECT_TEAM::ENEMY:
		{
			if (_enemyManager->getHit(pos, size, team, rc, damage, type))
			{
				result = true;
			}
		}
		break;
		case OBJECT_TEAM::OBJECT:
		{
			if (_objectManager->getHit(pos, size, team, rc, damage, type))
			{
				result = true;
			}
		}
		break;
		}
	}
	return result;
}

void Stage::setBossUiVisible(bool isVisible)
{
	_stageManager->setBossUiVisible(isVisible);
}

void Stage::setBossUi(float currHp, float maxHp)
{
	_stageManager->setBossUi(currHp, maxHp);
}

void Stage::startDialogue(BossChapter chapter)
{
	_stageManager->startDialogue(chapter);
}

bool Stage::isDialoging()
{
	return _stageManager->isDialoging();
}

void Stage::setHeart(bool isVisible)
{
	_stageManager->setHeart(isVisible);
}

void Stage::gameOver()
{
}

void Stage::spawnMoney(Vector3 pos)
{
	_objectManager->spawnMoney(pos);
}

float Stage::getCenterBottom(Vector3 pos)
{
	Vector2 centerPos = Vector2(pos.x, pos.z);
	return _objectManager->getCenterBottom(centerPos);
}

Vector3 Stage::getPlayerPosition()
{
	return _player->getPosition();
	

}

float Stage::getPlayerHp()
{
	return _player->getHp();
}

