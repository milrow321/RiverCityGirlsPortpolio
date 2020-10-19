#include "stdafx.h"
#include "AttackState.h"

void AttackState::enter(Player & player)
{
	num2 = RANDOM->getFromIntTo(1, 3);
	num3 = RANDOM->getFromIntTo(1, 4);
	_isCombo = false;
	_isStep = false;
	_isFirstAttackCheck = true;

	switch (_skill)
	{
	case ATTACK_SKILL:: QC1:
		SOUND_MANAGER->stop("KYOKO_Chop" + to_string(num3));
		SOUND_MANAGER->play("KYOKO_Chop"+ to_string(num3), 1.0f);
		
		_img = IMAGE_MANAGER->findImage("Kyoko_attack1");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 6, false, false);
		}
		else
		{
			_ani->setPlayFrame(6, 12, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	case ATTACK_SKILL::RUN_QC:
		SOUND_MANAGER->stop("KYOKO_BackElbow" + to_string(num2));
		SOUND_MANAGER->play("KYOKO_BackElbow" + to_string(num2), 1.0f);
		
		_img = IMAGE_MANAGER->findImage("Kyoko_backelbow");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 7, false, false);
		}
		else
		{
			_ani->setPlayFrame(7, 14, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	case ATTACK_SKILL::JUMP_QC:
		SOUND_MANAGER->stop("KYOKO_HipAttack" + to_string(num2));
		SOUND_MANAGER->play("KYOKO_HipAttack" + to_string(num2), 1.0f);
		_img = IMAGE_MANAGER->findImage("Kyoko_buttbump");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 10, false, false);
		}
		else
		{
			_ani->setPlayFrame(10, 20, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		
		break;
	case ATTACK_SKILL::HC:
		SOUND_MANAGER->stop("KYOKO_HeavyAtkKick");
		SOUND_MANAGER->play("KYOKO_HeavyAtkKick", 1.0f);
		
		_img = IMAGE_MANAGER->findImage("Kyoko_axekick");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 13, false, false);
		}
		else
		{
			_ani->setPlayFrame(13, 26, false, false);
		}
		CAMERA_MANAGER->pushShakeEvent(-2, 0.06, 0.1);
		_ani->setFPS(15);
		_ani->start();
		
		break;
	case ATTACK_SKILL::RUN_HC:
		SOUND_MANAGER->stop("KYOKO_Dive" + to_string(num2));
		SOUND_MANAGER->play("KYOKO_Dive" + to_string(num2), 1.0f);
		
		_img = IMAGE_MANAGER->findImage("Kyoko_dive");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 21, false, false);
		}
		else
		{
			_ani->setPlayFrame(21, 42, false, false);
		}

		_ani->setFPS(25);
		_ani->start();
		break;
	case ATTACK_SKILL::JUMP_HC:
		SOUND_MANAGER->stop("KYOKO_JumpKick");
		SOUND_MANAGER->play("KYOKO_JumpKick", 1.0f);
		_img = IMAGE_MANAGER->findImage("Kyoko_airstep");
		_ani = new Animation;
		_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			_ani->setPlayFrame(0, 11, false, false);
		}
		else
		{
			_ani->setPlayFrame(11, 22, false, false);
		}

		_ani->setFPS(15);
		_ani->start();
		break;
	}
	

}

PlayerState * AttackState::update(Player & player)
{
	Vector3 moveDir;
	moveDir.x = 0;
	moveDir.y = 0;
	moveDir.z = 0;

	_attackRc = FloatRect(0, 0, 0, 0);
	_viewRc = FloatRect(0, 0, 0, 0);

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

	float lastPlayerY = player.getPosition().y;

	switch (_skill)
	{
	case ATTACK_SKILL::QC1:
	{
		_initTime += TIME_MANAGER->getElapsedTime();
		if (!_ani->isPlay())
		{
			SOUND_MANAGER->stop("KYOKO_Chop" + to_string(num3));
			if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
			else return new IdleState;
		}
				
		if (_ani->getPlayIndex() == 2 && _isFirstAttackCheck)
		{
			_isFirstAttackCheck = false;
			Vector3 position = player.getPosition();
			if (player.getDirection() == DIRECTION::RIGHT)
			{
				_attackRc = FloatRect(position.x + 20, position.y - 45,
					position.x + 130, position.y + 10);
			}
			else
			{
				_attackRc = FloatRect(position.x - 130, position.y - 45,
					position.x - 20, position.y + 10);
			}

			_viewRc = FloatRect(_attackRc.left, position.z + _attackRc.top,
				_attackRc.right, position.z + _attackRc.bottom);
			if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::HIT1))
			{
				EFFECT_MANAGER->playZ("effect_4", Vector3((_attackRc.left + _attackRc.right) / 2, (_attackRc.top + _attackRc.bottom) / 2, position.z + player.getSize().z / 2), 1);
				_isCombo = true;
			}
		}
		if (_isCombo&& _ani->getPlayIndex()>3)
		{
			if (KEY_MANAGER->isOnceKeyDown('Z'))
			{
				_img = IMAGE_MANAGER->findImage("Kyoko_attack2");

				_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					_ani->setPlayFrame(0, 7, false, false);
				}
				else
				{
					_ani->setPlayFrame(7, 14, false, false);
				}
				_ani->setFPS(15);
				_ani->start();
				_isCombo = false;

				_isFirstAttackCheck = true;
				_skill = ATTACK_SKILL::QC2;
				_initTime = 0;
			}
			if (KEY_MANAGER->isOnceKeyDown('S'))
			{

				_img = IMAGE_MANAGER->findImage("Kyoko_axekick");
				_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					_ani->setPlayFrame(0, 13, false, false);
				}
				else
				{
					_ani->setPlayFrame(13, 26, false, false);
				}

				_ani->setFPS(15);
				_ani->start();
				_isCombo = false;
				_isFirstAttackCheck = true;

				_skill = ATTACK_SKILL::HC;

			}

		}
		
	}
			
		

	break;
	case ATTACK_SKILL::QC2:
		//CAMERA_MANAGER->rectangle(FloatRect(300, 300, 800, 800), D2D1::ColorF::Enum::Red, 1, 20);
		if (!_ani->isPlay())
		{
			if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
			else return new IdleState;
		}
		else
		{
			if (_ani->getPlayIndex() == 3 && _isFirstAttackCheck)
			{
				_isFirstAttackCheck = false;
				Vector3 position = player.getPosition();
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					_attackRc = FloatRect(position.x + 30, position.y - 60,
						position.x + 140, position.y + 70);
				}
				else
				{
					_attackRc = FloatRect(position.x - 140, position.y - 60,
						position.x - 30, position.y + 70);
				}

				_viewRc = FloatRect(_attackRc.left, position.z + _attackRc.top,
					_attackRc.right, position.z + _attackRc.bottom);
				
				if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::HIT2))
				{
					EFFECT_MANAGER->playZ("effect_4", Vector3((_attackRc.left + _attackRc.right) / 2, (_attackRc.top + _attackRc.bottom) / 2, position.z + player.getSize().z / 2), 1);
					_isCombo = true;
				}
				
			}
			if (_isCombo&& _ani->getPlayIndex()>4)
			{
				if (KEY_MANAGER->isOnceKeyDown('Z'))
				{
					SOUND_MANAGER->stop("KYOKO_Combo");
					SOUND_MANAGER->play("KYOKO_Combo",1.0f);
					CAMERA_MANAGER->pushShakeEvent(-2, 0.06, 0.1);
					_img = IMAGE_MANAGER->findImage("Kyoko_attack3");

					_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						_ani->setPlayFrame(0, 7, false, false);
					}
					else
					{
						_ani->setPlayFrame(7, 14, false, false);
					}
					_ani->setFPS(15);
					_ani->start();
					_isCombo = false;
					_isFirstAttackCheck = true;

					_initTime = 0;

					_skill = ATTACK_SKILL::QC3;

				}
				if (KEY_MANAGER->isOnceKeyDown('S'))
				{
					_img = IMAGE_MANAGER->findImage("Kyoko_axekick");
					_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						_ani->setPlayFrame(0, 13, false, false);
					}
					else
					{
						_ani->setPlayFrame(13, 26, false, false);
					}

					_ani->setFPS(15);
					_ani->start();
					_isCombo = false;
					_isFirstAttackCheck = true;

					_skill = ATTACK_SKILL::HC;

				}
			}


			_initTime += TIME_MANAGER->getElapsedTime();
					
		}
			break;
		case ATTACK_SKILL::QC3:
			if (!_ani->isPlay())
			{
				SOUND_MANAGER->stop("KYOKO_Combo");
				if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
				else return new IdleState;
					
			}
			else
			{
				if (_ani->getPlayIndex() == 5 && _isFirstAttackCheck)
				{
					_isFirstAttackCheck = false;
					Vector3 position = player.getPosition();
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						_attackRc = FloatRect(position.x + 30, position.y - 100,
							position.x + 160, position.y + 100);
					}
					else
					{
						_attackRc = FloatRect(position.x - 160, position.y - 100,
							position.x - 30, position.y + 100);
					}

					_viewRc = FloatRect(_attackRc.left, position.z + _attackRc.top,
						_attackRc.right, position.z + _attackRc.bottom);
					
					if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::KNOCKDOWN))
					{
						EFFECT_MANAGER->playZ("effect_4",Vector3(_attackRc.getCenter().x,_attackRc.getCenter().y,position.z+player.getSize().z/2),1);
						_isCombo = true;
					}
					
					
				}
				if (_isCombo && _ani->getPlayIndex() > 6)
				{
					if (KEY_MANAGER->isOnceKeyDown('S'))
					{
						_img = IMAGE_MANAGER->findImage("Kyoko_axekick");
						_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							_ani->setPlayFrame(0, 13, false, false);
						}
						else
						{
							_ani->setPlayFrame(13, 26, false, false);
						}

						_ani->setFPS(15);
						_ani->start();
						_isCombo = false;
						_isFirstAttackCheck = true;

						_skill = ATTACK_SKILL::HC;

					}
				}
				
			}
			break;

		case ATTACK_SKILL::RUN_QC:
			if (!_ani->isPlay())
			{
				SOUND_MANAGER->stop("KYOKO_Dive");
				if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
				else return new IdleState;
			}
			else {
				_initTime += TIME_MANAGER->getElapsedTime();
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					moveDir.x += player.getSpeed() / 5;
				}
				else
				{
					moveDir.x -= player.getSpeed() / 5;
				}


				if (_ani->getPlayIndex() == 3 && _isFirstAttackCheck)
				{
					_isFirstAttackCheck = false;

					Vector3 position = player.getPosition();
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						_attackRc = FloatRect(position.x + 20, position.y - 45,
							position.x + 130, position.y + 10);
					}
					else
					{
						_attackRc = FloatRect(position.x - 130, position.y - 45,
							position.x - 20, position.y + 10);
					}


					_viewRc = FloatRect(_attackRc.left, position.z + _attackRc.top,
						_attackRc.right, position.z + _attackRc.bottom);
					
					if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::HIT1))
					{
						EFFECT_MANAGER->playZ("effect_4", Vector3((_attackRc.left + _attackRc.right) / 2, (_attackRc.top + _attackRc.bottom) / 2, position.z + player.getSize().z / 2), 1);
						_isCombo = true;
					}
				}
				if (_isCombo && _ani->getPlayIndex() > 4)
				{
					if (KEY_MANAGER->isOnceKeyDown('Z'))
					{
						_img = IMAGE_MANAGER->findImage("Kyoko_attack2");

						_ani->init(_img->getWidth(), _img->getHeight(), _img->getMaxFrameX(), _img->getMaxFrameY());
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							_ani->setPlayFrame(0, 7, false, false);
						}
						else
						{
							_ani->setPlayFrame(7, 14, false, false);
						}
						_ani->setFPS(15);
						_ani->start();
						_isCombo = false;
						_isFirstAttackCheck = true;


						_skill = ATTACK_SKILL::QC2;
						_initTime = 0;

					}
				}
				
			}
			break;
		case ATTACK_SKILL::JUMP_QC:
				
			if (_ani->getPlayIndex() == 5 && _isFirstAttackCheck)
			{
				_isFirstAttackCheck = false;

				Vector3 position = player.getPosition();
				if (player.getDirection() == DIRECTION::RIGHT)
				{
					_attackRc = FloatRect(player.getPosition().x + 20, player.getPosition().y ,
						player.getPosition().x + 90, player.getPosition().y + 100);
				}
				else
				{
					_attackRc = FloatRect(player.getPosition().x - 90, player.getPosition().y,
						player.getPosition().x - 20, player.getPosition().y + 100);
				}


				_viewRc = FloatRect(_attackRc.left, player.getPosition().z + _attackRc.top,
					_attackRc.right, player.getPosition().z + _attackRc.bottom);
				
				if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::HIT1))
				{
					EFFECT_MANAGER->playZ("effect_1", Vector3((_attackRc.left + _attackRc.right) / 2, (_attackRc.top + _attackRc.bottom) / 2, position.z + player.getSize().z / 2), 1);
				}
			}

			moveDir.y -= _currJumpPower;
			_currJumpPower -= player.getGravity();

			moveDir.x += _currMoveDirX;
				


				break;
			case ATTACK_SKILL::HC:
				if (!_ani->isPlay())
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
					else return new IdleState;
					SOUND_MANAGER->stop("KYOKO_HeavyAtkKick");
				}
				else
				{
					if (_ani->getPlayIndex() == 6 && _isFirstAttackCheck)
					{
						_isFirstAttackCheck = false;
						Vector3 position = player.getPosition();
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							_attackRc = FloatRect(position.x + 10, position.y - 100,
								position.x + 140, position.y + 100);
						}
						else
						{
							_attackRc = FloatRect(position.x - 140, position.y - 100,
								position.x - 10, position.y + 100);
						}

						_viewRc = FloatRect(_attackRc.left, position.z + _attackRc.top,
							_attackRc.right, position.z + _attackRc.bottom);
						
						if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::KNOCKDOWN))
						{
							CAMERA_MANAGER->pushShakeEvent(-2, 0.06, 0.1);
							EFFECT_MANAGER->playZ("effect_4", Vector3((_attackRc.left + _attackRc.right) / 2, (_attackRc.top + _attackRc.bottom) / 2, position.z + player.getSize().z / 2), 1);
						}
					}

				}

				break;
			case ATTACK_SKILL::RUN_HC:
				if (!_ani->isPlay())
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))return new WalkState;
					else return new IdleState;
					SOUND_MANAGER->stop("KYOKO_Dive" + to_string(num2));
				}
				else
				{
					moveDir.x += _currMoveDirX;
					if (_ani->getPlayIndex() == 6 && _isFirstAttackCheck)
					{
						_isFirstAttackCheck = false;
						Vector3 position = player.getPosition();
						if (player.getDirection() == DIRECTION::RIGHT)
						{
							_attackRc = FloatRect(position.x + 10, position.y - 40,
							position.x + 140, position.y + 100);
							
							//_currMoveDirX -= 0.02f;
						}
						else
						{
							_attackRc = FloatRect(position.x - 140, position.y - 40,
								position.x - 10, position.y + 100);
							//moveDir.x += _currMoveDirX;
							//_currMoveDirX += 0.02f;
						}

						_viewRc = FloatRect(_attackRc.left, position.z + _attackRc.top,
							_attackRc.right, position.z + _attackRc.bottom);
						
						if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::KNOCKDOWN))
						{
							CAMERA_MANAGER->pushShakeEvent(-2, 0.06, 0.1);
							EFFECT_MANAGER->playZ("effect_4", Vector3((_attackRc.left + _attackRc.right) / 2, (_attackRc.top + _attackRc.bottom) / 2, position.z + player.getSize().z / 2), 1);
						}
					}
					else if (_ani->getPlayIndex() > 10)
					{
						moveDir.x = 0;
					}
				}
				
				break;
			case ATTACK_SKILL::JUMP_HC:
				
				

				if (_ani->getPlayIndex() == 6 && _isFirstAttackCheck)
				{
					
					Vector3 position = player.getPosition();
					if (player.getDirection() == DIRECTION::RIGHT)
					{
						_attackRc = FloatRect(player.getPosition().x , player.getPosition().y+90,
							player.getPosition().x + 60, player.getPosition().y + 150);
						
					}
					else
					{
						_attackRc = FloatRect(player.getPosition().x - 60, player.getPosition().y+90,
							player.getPosition().x , player.getPosition().y + 150);
						
					}


					_viewRc = FloatRect(_attackRc.left, player.getPosition().z + _attackRc.top,
						_attackRc.right, player.getPosition().z + _attackRc.bottom);
					
					if (player.attack(player.getPosition(), player.getSize(), OBJECT_TEAM::PLAYER, _attackRc, 10, ATTACK_TYPE::KNOCKDOWN))
					{
						_isFirstAttackCheck = false;
						EFFECT_MANAGER->playZ("effect_4", Vector3((_attackRc.left + _attackRc.right) / 2, (_attackRc.top + _attackRc.bottom) / 2, position.z + player.getSize().z / 2), 1);
						_isStep = true;
						_currJumpPower = -_currJumpPower;
					}
				}
				

				moveDir.x += _currMoveDirX;
				moveDir.y -= _currJumpPower;
				_currJumpPower -= player.getGravity();

				if (KEY_MANAGER->isStayKeyDown(VK_RIGHT))
				{
					moveDir.x += player.getSpeed();
				}
				if (KEY_MANAGER->isStayKeyDown(VK_LEFT))
				{
					moveDir.x -= player.getSpeed();
				}
				
				break;

				}
		
			
		

				player.move(moveDir);
			
			float currentPlayerY = player.getPosition().y;

				if (_currJumpPower < -1 && currentPlayerY == lastPlayerY && moveDir.y != 0 
					&& (_skill == ATTACK_SKILL::JUMP_QC|| _skill == ATTACK_SKILL::JUMP_HC))
				{
					if (KEY_MANAGER->isStayKeyDown(VK_RIGHT) || KEY_MANAGER->isStayKeyDown(VK_LEFT))
					{
						return new WalkState;
					}
					else
					{
						return new IdleState;
					}
				}
				
				

			return nullptr;

		}

	

void AttackState::render(Player & player)
{
	PlayerState::render(player);
	_img->setScale(3);
	Vector3 position = player.getPosition();
	
	if (_skill == ATTACK_SKILL::JUMP_HC)
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			position.x += 25;
		}
		else
		{
			position.x -= 25;
		}
	}
	else
	{
		if (player.getDirection() == DIRECTION::RIGHT)
		{
			position.x += 35;
		}
		else
		{
			position.x -= 35;
		}
	}

	

	if (_skill == ATTACK_SKILL::HC)
	{
		
		position.y += 15;
	}
	else if (_skill == ATTACK_SKILL::QC3)
	{
		position.y -= 15;
	}
	else if (_skill == ATTACK_SKILL::RUN_HC)
	{
		position.y += 10;
	}

	//CAMERA_MANAGER->rectangle(FloatRect(300, 300, 800, 800), D2D1::ColorF::Enum::Red, 1, 20);
	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::PLAYER))
	{
		CAMERA_MANAGER->rectangle(_viewRc, D2D1::ColorF::Enum::Red, 1, 1);
	}
	CAMERA_MANAGER->aniRenderZ(_img, position, player.getSize(), _ani);

	if (_skill == ATTACK_SKILL::JUMP_HC || _skill == ATTACK_SKILL::JUMP_QC)
	{
		Vector3 shadowPos = player.getPosition();
		shadowPos.y = player.getCenterBottom();
		CAMERA_MANAGER->drawShadowZ(shadowPos, Vector3(120.0, 0, 25.0), -shadowPos.y);
	}
	else
	{
		CAMERA_MANAGER->drawShadowZ(player.getPosition(), Vector3(120.0, player.getSize().y, 25.0), -(player.getPosition().y + (player.getSize().y / 2)));
	}
}

void AttackState::exit(Player & paleyr)
{
	
	_ani->release();
	SAFE_DELETE(_ani);
}
