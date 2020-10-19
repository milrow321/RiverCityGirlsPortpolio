#include "stdafx.h"
#include "SnackMachineObject.h"
#include "ObjectManager.h"

SnackMachineObject::SnackMachineObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(190, 190, 55);
	_position = Vector3(position.x, -(_size.y / 2), position.z);
	_isCollision = true;
	if (_direction == DIRECTION::LEFT)
	{
		_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_LEFT");
	}
	if (_direction == DIRECTION::RIGHT)
	{
		_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_RIGHT");
	}

	int linePos[4][4] = { {_position.x - (_size.x / 2) + (_size.z / 2) , _position.z - (_size.z / 2), _position.x + (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)}, // 상
						{_position.x - (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2), _position.x + (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)}, }; // 하
	linePos[2][0] = linePos[1][0]; // 좌
	linePos[2][1] = linePos[1][1];
	linePos[2][2] = linePos[0][0];
	linePos[2][3] = linePos[0][1];
	linePos[3][0] = linePos[1][2]; // 우
	linePos[3][1] = linePos[1][3];
	linePos[3][2] = linePos[0][2];

	if (_direction == DIRECTION::LEFT)
	{
		_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
			Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
			Vector2(_position.x + _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		// RB
			Vector2(_position.x + _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	}
	else if (_direction == DIRECTION::RIGHT)
	{
		_restrictRect = new RestrictMoveRect(Vector2(_position.x - _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
			Vector2(_position.x - _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
			Vector2(_position.x - _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		//RB
			Vector2(_position.x - _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	}
}

void SnackMachineObject::update()
{
}

void SnackMachineObject::release()
{
	delete _restrictRect;
}

void SnackMachineObject::render()
{
	Object::render();

	CAMERA_MANAGER->renderZ(_img, _position, _size);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_restrictRect->render();
	}
}

void SnackMachineObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}

bool SnackMachineObject::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (team != OBJECT_TEAM::PLAYER) return false; // 플레이어가 때린 게 아니라면 패스

	if (_state != OBJECT_STATE::BROKEN)
	{
		_state = OBJECT_STATE::BROKEN;
		EFFECT_MANAGER->playZ("effect_explosion", Vector3(_position.x, _position.y, _position.z + (_size.z / 2)), 3);
		CAMERA_MANAGER->pushShakeEvent(-20, 0.06, 0.24);

		if (_direction == DIRECTION::LEFT)
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_LEFT_BROKEN");
			_objectManager->makeParticle(PARTICLE_TYPE::PIECE_SNACKMACHINE, 10, 
				Vector3(_position.x - (_size.x / 2), _position.y, _position.z),
				Vector3(_position.x + (_size.x / 2), _position.y + (_size.y / 2), _position.z + (_size.z / 2)),
				Vector2(0, 0), 
				Vector2(PI2, PI), 
				5, 6, 3, 5);
			_objectManager->spawnFood(Vector3(_position.x, 25.0, _position.z + 60));
			//_objectManager->spawnMoney(Vector3(_position.x, 50.0, _position.z + 60));
		}
		if (_direction == DIRECTION::RIGHT)
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_SNACKMACHINE_RIGHT_BROKEN");
			_objectManager->makeParticle(PARTICLE_TYPE::PIECE_SNACKMACHINE, 10,
				Vector3(_position.x - (_size.x / 2), _position.y, _position.z),
				Vector3(_position.x + (_size.x / 2), _position.y + (_size.y / 2), _position.z + (_size.z / 2)),
				Vector2(0, 0),
				Vector2(PI2, PI),
				5, 6, 3, 5);
			_objectManager->spawnFood(Vector3(_position.x, 25.0, _position.z + 60));
			//_objectManager->spawnMoney(Vector3(_position.x, 50.0, _position.z + 60));
		}

		return true;
	}

	return false;
}