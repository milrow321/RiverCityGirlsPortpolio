#include "stdafx.h"
#include "DeskObject.h"

DeskObject::DeskObject(Vector3 position, DIRECTION direction, int imageType)
{
	_imageType = imageType;
	_direction = direction;
	_size = Vector3(80, 80, 60);
	_position = Vector3(position.x, -(_size.y / 2), position.z);
	_isCollision = true;

	if (imageType > 7) {imageType = 7;}
	if (imageType <= 0)	{imageType = 1;}

	switch (imageType)
	{
		case 1:
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_DESK01");
		}
		break;

		case 2:
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_DESK02");
		}
		break;

		case 3:
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_DESK03");
		}
		break;

		//sit boy
		case 4:
		{
			_position = Vector3(position.x, -_size.y - 25, position.z);
			_img = IMAGE_MANAGER->findImage("OBJECT_DESK_boy_idle01");
			_frameAni = new Animation;
			_frameAni->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_frameAni->setPlayFrame(0, 4, 0, 1);
			_frameAni->setFPS(1);
			_frameAni->start();
		}
		break;

		case 5:
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_DESK_boy_idle02");
		}
		break;

		//sit girl
		case 6:
		{
			_position = Vector3(position.x, -_size.y - 25, position.z);
			_img = IMAGE_MANAGER->findImage("OBJECT_DESK_girl_idle01");
			_frameAni = new Animation;
			_frameAni->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_frameAni->setPlayFrame(0, 2, 0, 1);
			_frameAni->setFPS(1);
			_frameAni->start();
		}
		break;

		case 7:
		{
			_img = IMAGE_MANAGER->findImage("OBJECT_DESK_girl_idle02");
		}
		break;
	}	

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
	_restrictRect = new RestrictMoveRect(Vector2(_position.x + _collisionOffsetX - (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// LT
										Vector2(_position.x + _collisionOffsetX + (_size.x / 2) + (_size.z / 2), _position.z + _collisionOffsetZ - (_size.z / 2)),		// RT
										Vector2(_position.x + _collisionOffsetX + (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),		// RB
									Vector2(_position.x + _collisionOffsetX - (_size.x / 2) - (_size.z / 2), _position.z + _collisionOffsetZ + (_size.z / 2)),
									_size.y);		// LB
}


void DeskObject::update()
{
	if (_imageType == 4 || _imageType == 6)
	{
		_frameAni->frameUpdate(TIME_MANAGER->getElapsedTime() * 2);
	}
}

void DeskObject::release()
{
	delete _restrictRect;
}

void DeskObject::render()
{
	Object::render();
	
	if (_imageType == 4 || _imageType == 6)
	{
		CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _frameAni);
	}
	if (_imageType != 4 && _imageType != 6)
	{
		CAMERA_MANAGER->renderZ(_img, _position, _size);
	}
	
	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::OBJECT))
	{
		_restrictRect->render();
	}
}

void DeskObject::collision(Vector3 * newPoses, GameObject* gameObject)
{
	_restrictRect->checkCollision(newPoses, gameObject);
}


