#include "stdafx.h"
#include "AllPlayerState.h"


PlayerState * RunState::update(Player & player)
{
	Vector3 moveDir;
	moveDir.x = 0;
	moveDir.y = 0;
	moveDir.z = 0;

	float lastPlayerY = player.getPosition().y;

	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		moveDir.y = 0.01;
		moveDir.x += player.getSpeed() * 2;
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		moveDir.y = 0.01;
		moveDir.x -= player.getSpeed() * 2;
	}

	if (KEY_MANAGER->isStayKeyDown(VK_UP))
	{
		moveDir.y = 0.01;
		moveDir.z -= player.getSpeed();
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_DOWN))
	{
		moveDir.y = 0.01;
		moveDir.z += player.getSpeed();
	}

	if (KEY_MANAGER->isOnceKeyDown('X'))
	{
		JumpState* jumpState = new JumpState;
		jumpState->setJumpType(JUMP_TYPE::RUN_JUMP);
		return jumpState;
	}

	if (KEY_MANAGER->isOnceKeyDown('Z'))
	{
		AttackState* attackState = new AttackState;
		attackState->setSkill(ATTACK_SKILL::RUN_QC);
		return attackState;
	}

	if (KEY_MANAGER->isOnceKeyDown('S'))
	{
		AttackState* attackState = new AttackState;
		attackState->setSkill(ATTACK_SKILL::RUN_HC);
		attackState->setCurrMoveDirX(moveDir.x);
		return attackState;
	}

	if (KEY_MANAGER->isOnceKeyDown('D'))
	{
		return new GuardState;
	}

	if (moveDir.x > 0)
	{
		_ani->setPlayFrame(0, 16, false, true);
		player.setDirection(DIRECTION::RIGHT);
	}
	else if(moveDir.x<0)
	{
		_ani->setPlayFrame(16, 32, false, true);
		player.setDirection(DIRECTION::LEFT);
	}
	else return new IdleState;

	moveDir = Vector3::normalize(&moveDir);
	moveDir = moveDir * player.getSpeed()*2;
	player.move(moveDir);

	float currentPlayerY = player.getPosition().y;

	if (_startY != lastPlayerY && moveDir.y != 0)
	{

		JumpState* jumpState = new JumpState;
		jumpState->setJumpType(JUMP_TYPE::DEFAULT_JUMP);
		player.setJumpPower(0);
		return jumpState;
	}


	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void RunState::render(Player & player)
{
	PlayerState::render(player);
	_img->setScale(3);
	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani, -(player.getPosition().y + (player.getSize().y / 2)));
	CAMERA_MANAGER->drawShadowZ(player.getPosition(), Vector3(120.0, player.getSize().y, 25.0), -(player.getPosition().y + (player.getSize().y / 2)));
}


void RunState::enter(Player & player)
{
	SOUND_MANAGER->stop("KYOKO_Run");
	SOUND_MANAGER->play("KYOKO_Run", 1.0f);

	_img = IMAGE_MANAGER->findImage("Kyoko_run");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(15);

	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 16, false, true); // 0 ~ 15
	}
	else
	{
		_ani->setPlayFrame(16, 32, false, true); // 16 ~ 31
	}
	_ani->start();
	_startY = player.getPosition().y;
}

void RunState::exit(Player & player)
{
	_ani->release();
	SAFE_DELETE(_ani);
	SOUND_MANAGER->stop("KYOKO_Run");
}
