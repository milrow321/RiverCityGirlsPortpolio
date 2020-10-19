#include "stdafx.h"
#include "AllPlayerState.h"

void StartState::enter(Player& player)
{

	SOUND_MANAGER->stop("KYOKO_StageUp");
	SOUND_MANAGER->play("KYOKO_StageUp", 1.0f);

	_img = IMAGE_MANAGER->findImage("Kyoko_battle_start");
	_img->setScale(3);
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(20);

	_ani->setPlayFrame(0, 26, false, false);
	
	//스폰 장소가 스테이지기준 좌측인지 우측인지에 따라 나눌수 있지만
	//굳이 하기 귀찮다면 왼쪽에서 나타나는 걸로

	//if (player.getDirection() == DIRECTION::RIGHT)
	//{
	//	_ani->setPlayFrame(0, 26, false, true); // 
	//}
	//else if (player.getDirection() == DIRECTION::LEFT)
	//{
	//	_ani->setPlayFrame(26, 52, false, true); // 
	//}

	_ani->start();
}

void StartState::exit(Player& player)
{
	SOUND_MANAGER->stop("KYOKO_StageUp");
	_ani->release();
	SAFE_DELETE(_ani)
}

PlayerState* StartState::update(Player& player)
{
	if (!_ani->isPlay())
	{
		return new IdleState;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
	return nullptr;
}

void StartState::render(Player& player)
{
	PlayerState::render(player);

	_img->setScale(3);
	Vector3 position = player.getPosition();
	CAMERA_MANAGER->aniRenderZ(_img, position, player.getSize(), _ani);
	CAMERA_MANAGER->drawShadowZ(player.getPosition(), Vector3(120.0, player.getSize().y, 25.0), -(player.getPosition().y + (player.getSize().y / 2)));
}
