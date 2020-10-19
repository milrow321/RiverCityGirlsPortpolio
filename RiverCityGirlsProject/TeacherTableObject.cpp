#include "stdafx.h"
#include "TeacherTableObject.h"

TeacherTableObject::TeacherTableObject(Vector3 position, DIRECTION direction)
{
	_direction = direction;
	_size = Vector3(130, 120, 180);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_img = IMAGE_MANAGER->findImage("OBJECT_TEACHER_TABLE");

	//높이 라인
	int linePos[4][4] = { {_position.x - (_size.x / 2) + (_size.z / 2) , _position.z - (_size.z / 2), _position.x + (_size.x / 2) + (_size.z / 2), _position.z - (_size.z / 2)}, // 상
						{_position.x - (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2), _position.x + (_size.x / 2) - (_size.z / 2), _position.z + (_size.z / 2)}, }; // 하
	linePos[2][0] = linePos[1][0]; // 좌
	linePos[2][1] = linePos[1][1];
	linePos[2][2] = linePos[0][0];
	linePos[2][3] = linePos[0][1];
	linePos[3][0] = linePos[1][2]; // 우
	linePos[3][1] = linePos[1][3];
	linePos[3][2] = linePos[0][2];

	//오브젝트 충돌 평행사변형
	_restrictRect = new RestrictMoveRect(Vector2(_position.x - _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
		Vector2(_position.x - _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
		Vector2(_position.x - _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		//RB
		Vector2(_position.x - _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
}

void TeacherTableObject::update()
{
}

void TeacherTableObject::release()
{
	delete _restrictRect;
}

void TeacherTableObject::render()
{
	Object::render();

	_img->setScale(4);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_restrictRect->render();
	}
}

void TeacherTableObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}