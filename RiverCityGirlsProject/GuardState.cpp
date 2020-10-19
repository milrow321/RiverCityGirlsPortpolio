#include "stdafx.h"
#include "GuardState.h"
#include "AllPlayerState.h"

void GuardState::enter(Player& player)
{
	_img = IMAGE_MANAGER->findImage("Kyoko_guard");
	
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(15);
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 2, false, false); // 0 ~ 
	}
	else if (player.getDirection() == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(3, 5, false, false); // 3 ~ 
	}
	_ani->start();

	player.setGuarding(true);
}

void GuardState::exit(Player& player)
{
	player.setGuarding(false);
	_ani->release();
	SAFE_DELETE(_ani)
}

PlayerState* GuardState::update(Player& player)
{
	if (KEY_MANAGER->isOnceKeyUp('D'))
	{
		return new IdleState;
	}
	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

    return nullptr;
}

void GuardState::render(Player& player)
{
	PlayerState::render(player);
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani);
	CAMERA_MANAGER->drawShadowZ(player.getPosition(), Vector3(120.0, player.getSize().y, 25.0), -(player.getPosition().y + (player.getSize().y / 2)));
}
