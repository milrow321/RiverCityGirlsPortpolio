#include "stdafx.h"
#include "AllPlayerState.h"

PlayerState * WalkState::update(Player& player)
{
	moveDir.x = 0;
	moveDir.y = 0;
	moveDir.z = 0;

	float lastPlayerY = player.getPosition().y;

	if (_initTime <= 0.08 && _state == WALK_STATE::IDLE)
	{
		_initTime += TIME_MANAGER->getElapsedTime();
		if ((player.getDirection() == DIRECTION::RIGHT && KEY_MANAGER->isOnceKeyDown(VK_RIGHT))
			|| (player.getDirection() == DIRECTION::LEFT && KEY_MANAGER->isOnceKeyDown(VK_LEFT)))
		{
			return new RunState;
		}
	}

	if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
	{
		
		moveDir.x += player.getSpeed();
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
	{
		
		moveDir.x -= player.getSpeed();
	}
	if (KEY_MANAGER->isStayKeyDown(VK_UP))
	{
		moveDir.z -= player.getSpeed();
	}
	else if (KEY_MANAGER->isStayKeyDown(VK_DOWN))
	{
		moveDir.z += player.getSpeed();
	}

	if (moveDir.x > 0)
	{
		player.setDirection(DIRECTION::RIGHT);
	}
	else if (moveDir.x < 0)
	{
		player.setDirection(DIRECTION::LEFT);
	}
	


	// TODO :: 움직임 대각석으로 움직일 때 보정하기

	
	if (moveDir.x == 0 && moveDir.z == 0)
	{
		if (_state != WALK_STATE::IDLE)
		{
			_state = WALK_STATE::IDLE;
			_img = IMAGE_MANAGER->findImage("Kyoko_idle");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				_ani->setPlayFrame(0, 12, false, false); // 0 ~ 11

			}
			else
			{
				_ani->setPlayFrame(12, 24, false, false); // 12 ~ 23

			}

			_ani->setFPS(15);
			_ani->start();
		}
		


		// 후처리 이미지으로 바꾸기
		// 후처리 애니메이션 설정하고 스타트
	}
	else
	{
		if (_state != WALK_STATE::MOVE)
		{
			_state = WALK_STATE::MOVE;
			_img = IMAGE_MANAGER->findImage("Kyoko_walk");
			_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
			_ani->setFPS(15);
			_ani->start();
			_initTime = 0;
			
		}
	}

	switch (_state)
	{
	case WALK_STATE::MOVE:
	{
		moveDir.y = 0.01;
		

		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
		}
		else
		{
			_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
		}

		if (KEY_MANAGER->isOnceKeyDown('X'))
		{
			
			JumpState* jumpState = new JumpState;
			jumpState->setJumpType(JUMP_TYPE::DEFAULT_JUMP);
			return jumpState;
		}

		

		if (KEY_MANAGER->isOnceKeyDown('Z'))
		{
			AttackState* attackState = new AttackState;
			attackState->setSkill(ATTACK_SKILL::QC1);
			return attackState;
		}

		if (KEY_MANAGER->isOnceKeyDown('S'))
		{
			AttackState* attackState = new AttackState;
			attackState->setSkill(ATTACK_SKILL::HC);
			return attackState;
		}

		if (KEY_MANAGER->isOnceKeyDown('D'))
		{
			return new GuardState;
		}

		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * player.getSpeed();
		player.move(moveDir);

		float currentPlayerY = player.getPosition().y;
		
		if (_startY != lastPlayerY && moveDir.y != 0)
		{

			JumpState* jumpState = new JumpState;
			jumpState->setJumpType(JUMP_TYPE::DEFAULT_JUMP);
			player.setJumpPower(0);
			return jumpState;
		}

	}
	break;
	case WALK_STATE::IDLE:
	{

		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 12, false, false); // 0 ~ 11
			
		}
		else
		{
			_ani->setPlayFrame(12, 24, false, false); // 12 ~ 23
			
		}

		if (KEY_MANAGER->isOnceKeyDown('X'))
		{
			JumpState* jumpState = new JumpState;
			jumpState->setJumpType(JUMP_TYPE::DEFAULT_JUMP);
			return jumpState;
		}
		if (KEY_MANAGER->isOnceKeyDown('Z'))
		{
			AttackState* attackState = new AttackState;
			attackState->setSkill(ATTACK_SKILL::QC1);
			return attackState;
		}

		if (KEY_MANAGER->isOnceKeyDown('S'))
		{
			AttackState* attackState = new AttackState;
			attackState->setSkill(ATTACK_SKILL::HC);
			return attackState;
		}

		if (KEY_MANAGER->isOnceKeyDown('D'))
		{
			return new GuardState;
		}

		if (!_ani->isPlay())
		{
			return new IdleState;
		}
	}
	break;
	}
	
	

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	return nullptr;
}

void WalkState::render(Player& player)
{
	PlayerState::render(player);
	_img->setScale(3);

	CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani, -(player.getPosition().y + (player.getSize().y / 2)));
	CAMERA_MANAGER->drawShadowZ(player.getPosition(), Vector3(120.0, player.getSize().y, 25.0), -(player.getPosition().y + (player.getSize().y / 2)));
	//CAMERA_MANAGER->aniRenderZ(_img, player.getPosition(), player.getSize(), _ani);

	/*char str[254];
	sprintf_s(str, "state:%d ,direction:%d ", _state, player.getDirection());
	TextOut(_hdc, 0, 100, str, strlen(str));*/
}


void WalkState::enter(Player& player)
{
	_img = IMAGE_MANAGER->findImage("Kyoko_walk");
	_ani = new Animation;
	_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
	_ani->setFPS(15);

	if (player.getDirection() == DIRECTION::RIGHT)
	{
		_ani->setPlayFrame(0, 12, false, true); // 0 ~ 11
	}
	else
	{
		_ani->setPlayFrame(12, 24, false, true); // 12 ~ 23
	}
	_ani->start();

	_initTime = 0;
	
	_startY=player.getPosition().y;

	_state = WALK_STATE::MOVE;
}

void WalkState::exit(Player& player)
{
	
	_ani->release();
	SAFE_DELETE(_ani);
}