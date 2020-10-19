#include "stdafx.h"
#include "TableObject.h"


TableObject::TableObject(Vector3 position, DIRECTION direction, int type)
{
	_direction = direction;
	_size = Vector3(300, 75, 50);
	_position = Vector3(position.x, -(_size.y / 2), position.z);
	_isCollision = true;

	switch (type)
	{
		case 1:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE01"); }
		break;

		case 2:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE02"); }
		break;

		case 3:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE03"); }
		break;

		case 4:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE04"); }
		break;

		case 5:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE05"); }
		break;

		case 6:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE06"); }
		break;

		case 7:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE07"); }
		break;

		case 8:
		{_img = IMAGE_MANAGER->findImage("OBJECT_TABLE08"); }
		break;
	}

	_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
		Vector2(_position.x + _collisionOffsetX + (_size.x / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
		Vector2(_position.x + _collisionOffsetX + (_size.x / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		// RB
		Vector2(_position.x + _collisionOffsetX - (_size.x / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB

	//if (_direction == DIRECTION::LEFT)
	//{
	//	_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
	//		Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
	//		Vector2(_position.x + _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		// RB
	//		Vector2(_position.x + _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	//}
	//else if (_direction == DIRECTION::RIGHT)
	//{
	//	_restrictRect = new RestrictMoveRect(Vector2(_position.x - _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
	//		Vector2(_position.x - _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
	//		Vector2(_position.x - _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		//RB
	//		Vector2(_position.x - _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)), _size.y);		// LB
	//}
}

void TableObject::update()
{
}

void TableObject::release()
{
	delete _restrictRect;
}

void TableObject::render()
{
	Object::render();

	_img->setScale(3);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_restrictRect->render();
	}
}

void TableObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}
