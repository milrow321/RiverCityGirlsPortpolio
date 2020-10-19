#include "stdafx.h"
#include "AllPlayerState.h"

IdleState::IdleState()
{
    
}

PlayerState * IdleState::update(Player & player)
{
	//if (player.getDirection() == DIRECTION::RIGHT)
	//{
	//	_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
	//}
	//else if (player.getDirection() == DIRECTION::LEFT)
	//{
	//	_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
	//}

	
	//약공격
	if (KEY_MANAGER->isOnceKeyDown('Z'))
	{
		AttackState* attackState = new AttackState;
		attackState->setSkill(ATTACK_SKILL::QC1);
		return attackState;
	}
	//강공격
	if (KEY_MANAGER->isOnceKeyDown('S'))
	{
		AttackState* attackState = new AttackState;
		attackState->setSkill(ATTACK_SKILL::HC);
		return attackState;
	}
	//점프
	if (KEY_MANAGER->isOnceKeyDown('X'))
	{
		JumpState* jumpState = new JumpState;
		jumpState->setJumpType(JUMP_TYPE::DEFAULT_JUMP);
		return jumpState;
	}
	//가드
	if (KEY_MANAGER->isOnceKeyDown('D'))
	{
		return new GuardState;
	}

	if (KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
	{
		player.setDirection(DIRECTION::RIGHT);
		return new WalkState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_LEFT))
	{
		player.setDirection(DIRECTION::LEFT);
		return new WalkState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_UP))
	{
		return new WalkState;
	}
	if (KEY_MANAGER->isOnceKeyDown(VK_DOWN))
	{
		return new WalkState;
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void IdleState::render(Player & player)
{
	PlayerState::render(player);
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani, -(player.getPosition().y + (player.getSize().y / 2)));
	CAMERA_MANAGER->drawShadowZ(player.getPosition(), Vector3(120.0, player.getSize().y, 25.0), -(player.getPosition().y + (player.getSize().y / 2)));
}

void IdleState::enter(Player & player)
{
	_img = IMAGE_MANAGER->findImage("Kyoko_idle");
	_img->setScale(3);
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(15);
	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
	}
	else if (player.getDirection() == DIRECTION::LEFT)
	{
		_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
	}
	_ani->start();
}

void IdleState::exit(Player& player)
{
	_ani->release();
	SAFE_DELETE(_ani);
}
