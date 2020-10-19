#include "stdafx.h"
#include "SchoolStudent.h"

SchoolStudent::SchoolStudent(Vector3 position, DIRECTION direction, int imageType)
{
	_imageType = imageType;
	_direction = direction;
	_size = Vector3(100, 230, 30);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	_ani = new Animation;
	/*if (imageType > 2) { imageType = 2; }
	if (imageType < 1) { imageType = 1; }*/

	switch (_imageType)
	{
		case 1:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle01"); }
		break;

		case 2:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle02"); }
		break;

		case 3:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyB_idle01"); }
		break;

		case 4:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyB_idle02"); }
		break;

		case 5:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyE_idle01"); }
		break;

		case 6:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyE_idle02"); }
		break;

		case 7:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlA_idle01"); }
		break;

		case 8:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlA_idle02"); }
		break;

		case 9:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlB_idle01"); }
		break;

		case 10:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlB_idle02"); }
		break;

		case 11:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlE_idle01"); }
		break;

		case 12:
		{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlE_idle02"); }
		break;
	}
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	if (_direction == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 4, 0, 1);
	}
	if (_direction == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(4, 8, 0, 1);
	}
	_ani->setFPS(3);
	_ani->start();
}

void SchoolStudent::update()
{

	switch (_state)
	{
		case OBJECT_STATE::IDLE:
		{
		}
		break;
		case OBJECT_STATE::REACTION:
		{
			if (!_ani->isPlay())
			{
				switch (_imageType)
				{
					case 1:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle01"); }
					break;

					case 2:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_idle02"); }
					break;

					case 3:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyB_idle01"); }
					break;

					case 4:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyB_idle02"); }
					break;

					case 5:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyE_idle01"); }
					break;

					case 6:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyE_idle02"); }
					break;
						
					case 7:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlA_idle01"); }
					break;

					case 8:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlA_idle02"); }
					break;

					case 9:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlB_idle01"); }
					break;

					case 10:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlB_idle02"); }
					break;

					case 11:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlE_idle01"); }
					break;

					case 12:
					{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlE_idle02"); }
					break;
				}

				_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
				if (_direction == DIRECTION::RIGHT)
				{
					_ani->setPlayFrame(0, 4, false, true);
				}
				if (_direction == DIRECTION::LEFT)
				{
					_ani->setPlayFrame(4, 8, false, true);
				}
				_ani->setFPS(3);
				_ani->start();
				_state = OBJECT_STATE::IDLE;
			}
		}
		break;
	}
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void SchoolStudent::release()
{
	_ani->release();
	delete _ani;
}

void SchoolStudent::render()
{
	Object::render();
	//_img->setSize(Vector2(100, 100));
	Vector3 renderPos = _position;
	renderPos.y -= 50;
	CAMERA_MANAGER->aniRenderZ(_img, renderPos, _size, _ani);
	CAMERA_MANAGER->drawShadowZ(_position, Vector3(100.0, _size.y, 25.0));
}

void SchoolStudent::collision(Vector3 ** pos)
{
}

bool SchoolStudent::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_state != OBJECT_STATE::REACTION)
	{
		switch (_imageType)
		{
			case 1:
			case 2:
			{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyA_reaction"); }
			break;

			case 3:
			case 4:
			{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyB_reaction"); }
			break;

			case 5:
			case 6:
			{_img = IMAGE_MANAGER->findImage("OBJECT_schoolBoyE_reaction"); }
			break;

			case 7:
			case 8:
			{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlA_reaction"); }
			break;

			case 9:
			case 10:
			{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlB_reaction"); }
			break;

			case 11:
			case 12:
			{_img = IMAGE_MANAGER->findImage("OBJECT_schoolGirlE_reaction"); }
			break;


		}
		_state = OBJECT_STATE::REACTION;
		
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (_direction == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 3, false, false);
		}
		if (_direction == DIRECTION::LEFT)
		{
			_ani->setPlayFrame(4, 6, false, false);
		}
		_ani->setFPS(5);
		_ani->start();
	}

	return false;
}