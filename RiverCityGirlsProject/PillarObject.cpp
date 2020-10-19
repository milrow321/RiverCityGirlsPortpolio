#include "stdafx.h"
#include "PillarObject.h"
#include "ObjectManager.h"

PillarObject::PillarObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(110, 5000, 55);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	switch (_direction)
	{
		case DIRECTION::RIGHT:
		{_img = IMAGE_MANAGER->findImage("OBJECT_PILLAR_RIGHT"); }
		break;
		case DIRECTION::LEFT:
		{_img = IMAGE_MANAGER->findImage("OBJECT_PILLAR_LEFT"); }
		break;
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

void PillarObject::update()
{
}

void PillarObject::release()
{
	delete _restrictRect;
}

void PillarObject::render()
{
	Object::render();

	_img->setScale(3);
	Vector3 drawPos = _position;
	drawPos.y += 2100;
	CAMERA_MANAGER->renderZ(_img, drawPos, _size);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_restrictRect->render();
	}
}

void PillarObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}

bool PillarObject::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (team != OBJECT_TEAM::BOSS) return false; // 보스가 때린 게 아니라면 패스

	if (_state != OBJECT_STATE::INACTIVE)
	{
		_objectManager->makeParticle(PARTICLE_TYPE::PIECE_PILLAR, 35,
			Vector3(_position.x - (_size.x / 2), 400.0, _position.z),
			Vector3(_position.x + (_size.x / 2), 800.0, _position.z + (_size.z / 2)),
			Vector2(0, 0),
			Vector2(PI2, PI),
			5, 6, 3, 5);
		_state = OBJECT_STATE::INACTIVE;
		return true;
	}

	return false;
}
