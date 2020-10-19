#include "stdafx.h"
#include "FoodObject.h"

FoodObject::FoodObject(Vector3 pos)
{
	_position = pos;
	_size = Vector3(30, 30, 30);
	_position.y = -_size.y * 0.5;
	_remainTime = 10.0f;

	_randomSpawn = RANDOM->getInt(3);

	_state = OBJECT_STATE::IDLE;
	switch (_randomSpawn)
	{
		case 0:
		{ 
			_img = IMAGE_MANAGER->findImage("OBJECT_FOOD_APPLE"); 
		}
		break;
		case 1:
		{ 
			_img = IMAGE_MANAGER->findImage("OBJECT_FOOD_CHIKEN"); 
		}
		break;
		case 2:
		{ 
			_img = IMAGE_MANAGER->findImage("OBJECT_FOOD_CHILI"); 
		}
		break;
	}
}

void FoodObject::update()
{
	_remainTime -= TIME_MANAGER->getElapsedTime();

	if (_remainTime <= 0)
	{
		_state = OBJECT_STATE::INACTIVE;
	}
}

void FoodObject::release()
{
}

void FoodObject::render()
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
	CAMERA_MANAGER->renderZ(_img, _position, _size);
}

void FoodObject::eatEffect(Player * player)
{
	
	switch (_randomSpawn)
	{
		case 0:
		{ 
			if (player->getHp() < player->getMaxHp())
			{
				_state = OBJECT_STATE::INACTIVE;
				player->setHp(min(player->getHp() + 10, player->getMaxHp()));
				SOUND_MANAGER->stop("STAGE_getMoney");
				SOUND_MANAGER->play("STAGE_getMoney", 1.0f);
				EFFECT_MANAGER->playZ("effect_eat", _position, 1.0f);
			}
		}
		break;
		case 1:
		{ 
			if (player->getHp() < player->getMaxHp())
			{
				_state = OBJECT_STATE::INACTIVE;
				player->setHp(min(player->getHp() + 30, player->getMaxHp()));
				SOUND_MANAGER->stop("STAGE_getMoney");
				SOUND_MANAGER->play("STAGE_getMoney", 1.0f);
				EFFECT_MANAGER->playZ("effect_eat", _position, 1.0f);
			}
		}
		break;
		case 2:
		{ 
			if (player->getHp() < player->getMaxHp())
			{
				_state = OBJECT_STATE::INACTIVE;
				player->setHp(min(player->getHp() + 20, player->getMaxHp()));
				SOUND_MANAGER->stop("STAGE_getMoney");
				SOUND_MANAGER->play("STAGE_getMoney", 1.0f);
				EFFECT_MANAGER->playZ("effect_eat", _position, 1.0f);
			}
		}
		break;
	}
}
