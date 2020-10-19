#include "stdafx.h"
#include "MoneyObject.h"

MoneyObject::MoneyObject(Vector3 pos)
{
	_position = pos;
	_size = Vector3(30, 100, 30);
	_position.y = -_size.y * 1.5f;
	_remainTime = 10.0f;
	_randomSpawn = RANDOM->getInt(5) + 1;

	_state = OBJECT_STATE::IDLE;
	switch (_randomSpawn)
	{
		case 1:
		{
			_gravity = 8.0f;
			_img = IMAGE_MANAGER->findImage("OBJECT_MOVE_COIN_SILVER");
		}
		break;
		case 2:
		{
			_gravity = 8.0f;
			_img = IMAGE_MANAGER->findImage("OBJECT_MOVE_COIN_GOLD");
		}
		break;
		case 3:
		{
			_gravity = 0.8f;
			_img = IMAGE_MANAGER->findImage("OBJECT_MOVE_MONEY_BLUE");
		}
		break;
		case 4:
		{
			_gravity = 0.8f;
			_img = IMAGE_MANAGER->findImage("OBJECT_MOVE_MONEY_PURPLE");
		}
		break;
		case 5:
		{
			_gravity = 0.8f;
			_img = IMAGE_MANAGER->findImage("OBJECT_MOVE_MONEY_GREEN");
		}
		break;
	}
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setPlayFrame(0, 12, 0, 1);
	_ani->setFPS(8);
	_ani->start();
}

void MoneyObject::update()
{
	_position.y += _gravity;
	if (_position.y > 0)
	{
		switch (_randomSpawn)
		{
			case 3:
			case 4:
			case 5:
			{_ani->stop(); }
			break;
		}
		
		_gravity = 0;
	}

	_remainTime -= TIME_MANAGER->getElapsedTime();

	if (_remainTime <= 0)
	{
		_state = OBJECT_STATE::INACTIVE;
	}
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void MoneyObject::release()
{
	_ani->release();
	delete _ani;
}

void MoneyObject::render()
{
	Object::render();

	if (_remainTime <= 4.0f && _remainTime >= 1.5f)
	{
		if (fmod(_remainTime, 0.2f) < 0.1f)
		{
			_img->setAlpha(1);
		}
		if (fmod(_remainTime, 0.2f) > 0.1f)
		{
			_img->setAlpha(0);
		}
	}
	else if (_remainTime < 1.5f)
	{
		if (fmod(_remainTime, 0.1f) < 0.05f)
		{
			_img->setAlpha(1);
		}
		if (fmod(_remainTime, 0.1f) > 0.05f)
		{
			_img->setAlpha(0);
		}
	}
	CAMERA_MANAGER->aniRenderZ(_img, _position, _size, _ani);
}

void MoneyObject::eatEffect(Player * player)
{
	_state = OBJECT_STATE::INACTIVE;

	SOUND_MANAGER->stop("STAGE_getMoney");
	SOUND_MANAGER->play("STAGE_getMoney", 1.0f);
	EFFECT_MANAGER->playZ("effect_eat", _position, 1.0f);

	switch (_randomSpawn)
	{
		case 1:
		{ player->setMoney(player->getMoney() + 5.15f);	}
		break;
		case 2:
		{ player->setMoney(player->getMoney() + 10.25f); }
		break;
		case 3:
		{ player->setMoney(player->getMoney() + 15.00f); }
		break;
		case 4:
		{ player->setMoney(player->getMoney() + 20.15f); }
		break;
		case 5:
		{ player->setMoney(player->getMoney() + 30.25f); }
		break;
	}
}
