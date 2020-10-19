#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Enemy::init()
{
}

void Enemy::release()
{
}

void Enemy::update()
{
}

void Enemy::render()
{
	
}

bool Enemy::getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	// 1. Z축 검사
	Vector3 hitterPos = pos;
	Vector3 hitterSize = size;
	float hitterMinZ = hitterPos.z - (hitterSize.z / 2);
	float hitterMaxZ = hitterPos.z + (hitterSize.z / 2);
	float victimMinZ = _position.z - (_size.z / 2);
	float victimMaxZ = _position.z + (_size.z / 2);
	if (victimMaxZ < hitterMinZ || hitterMaxZ < victimMinZ) // Z 축 좌표가 공유되지 않는 경우 종료
	{
		return false;
	}

	// 2. X, Y 검사 (IntersectRect)
	FloatRect victimRc = FloatRect(_position.x - (_size.x / 2), _position.y - (_size.y / 2), _position.x + (_size.x / 2), _position.y + (_size.y / 2));
	if (FloatRect::intersect(victimRc, attackRc))
	{
		return hitEffect(pos, size, team, attackRc, damage, type);
	}
	return false;
}

bool Enemy::enemyAttack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	
	return _enemyManager->enemyAttack(pos, size, team, attackRc, damage, type);
	
	
}

bool Enemy::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	return false;
}

void Enemy::setDirectionToPlayer()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition();
	if (playerPos.x <= _position.x - 50)
	{
		_direction = DIRECTION::LEFT;
	}
	else if (playerPos.x >= _position.x + 50)
	{
		_direction = DIRECTION::RIGHT;
	}
}

