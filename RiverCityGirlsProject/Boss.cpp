#include "stdafx.h"
#include "Boss.h"

void Boss::init()
{
	_position = Vector3(1000, -135, 500);
	_size = Vector3(180, 260, 40);
	_ani = new Animation;
	_direction = DIRECTION::LEFT;
	setState(BOSS_STATE::IDLE, _direction, true);

	_team = OBJECT_TEAM::BOSS;
	_gravity = 0;
	_jumpPower = 0;
	_maxHp = 300;
	_hp = _maxHp;
	_isActive = true;
	_checkDialog = false;
}

void Boss::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void Boss::update()
{	

	if (_phase == BOSS_PHASE::DEFEAT)
	{
		if (!_ani->isPlay())
		{
			if (_direction == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(_enemyImg->getMaxFrameX() + 10, _enemyImg->getMaxFrameX() + 13, false, true);
			}
			else
			{
				_ani->setPlayFrame(10, 13, false, true);
			}
			_ani->start();
			_enemyManager->setBossUiVisible(false);
			_enemyManager->startDialogue(BossChapter::BATTLE_AFTER);
			_checkDialog = true;
		}

		if (!_enemyManager->isDialoging() && _checkDialog)
		{
			_enemyManager->setHeart(true);
		}
	}
	else
	{
		if (!_enemyManager->isDialoging())
		{
			_enemyManager->setBossUiVisible(true);
			_enemyManager->setBossUi(_hp, _maxHp);
		}
		
		_attackRc = FloatRect(0, 0, 0, 0);
		_viewRc = FloatRect(0, 0, 0, 0);

		Vector3 playerPos = _enemyManager->getPlayerPosition(); // 플레이어의 위치
		float distanceFromPlayer = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.z - _position.z, 2)); // 플레이어와 xz 거리
		Vector3 moveDir = Vector3(0, 0, 0);
		_elapsedTime += TIME_MANAGER->getElapsedTime();
		_electricTime -= TIME_MANAGER->getElapsedTime();


		// 상태에 따른 행동 및 상태 전이
		switch (_bossState)
		{
		case BOSS_STATE::IDLE:
		{
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::WALK, _direction, true);
			}
		}
		break;
		case BOSS_STATE::WALK: // 걷기 상태
		{
			setDirectionToPlayer(); // 플레이어 바라보기

			moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
			moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
			moveDir = Vector3::normalize(&moveDir);

			float speed = (_phase == BOSS_PHASE::PHASE_3) ? 5 : 3;

			moveDir = moveDir * speed;

			_enemyManager->moveEnemy(this, moveDir);

			setAttackState(_phase, distanceFromPlayer);
		}
		break;
		case BOSS_STATE::LAUGH:
		{
			
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::IDLE, _direction, true);
			}
		}
		break;
		case BOSS_STATE::GET_HIT:
		{
			setDirectionToPlayer(); // 플레이어 바라보기

			moveDir.x += (_direction == DIRECTION::RIGHT) ? -0.5 : 0.5;
			moveDir = moveDir * 3;

			_enemyManager->moveEnemy(this, moveDir);

			if (!_ani->isPlay())
			{
				_combo++;
				setState(BOSS_STATE::IDLE, _direction, true);
			}
		}
		break;
		case BOSS_STATE::GROUND_HIT:
		{
			setDirectionToPlayer(); // 플레이어 바라보기

			_gravity += 0.5;
			_jumpPower += _gravity;
			moveDir.y += _jumpPower;

			float lastY = _position.y;
			_enemyManager->moveEnemy(this, moveDir);
			float currY = _position.y;


			if (!_ani->isPlay())
			{
				_gravity = 0;
				setState(BOSS_STATE::GROUND, _direction, false);
			}
		}
		break;
		case BOSS_STATE::KNOCKDOWN:
		{
			_gravity += 0.5;
			_jumpPower += _gravity;
			if (_gravity != 0.5)
			{
				moveDir.x += (_direction == DIRECTION::RIGHT) ? -3 : 3;
			}
			moveDir.y += _jumpPower;

			float lastY = _position.y;
			_enemyManager->moveEnemy(this, moveDir);
			float currY = _position.y;

			if (!_ani->isPlay())
			{
				if (_hp == 0)
				{
					_phase = BOSS_PHASE::DEFEAT;
					_enemyImg = IMAGE_MANAGER->findImage("boss_defeat");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(), _enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(15);
					if (_direction == DIRECTION::LEFT)
					{
						_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, false);
					}
					else
					{
						_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, false);
					}
					_ani->start();
				}
				else
				{
					setState(BOSS_STATE::GROUND, _direction, true);
				}
			}
			else if (moveDir.y >= 1 && lastY == currY) // 땅에 부딪힘
			{
				_gravity = 0;
				if (_count == 0)
				{
					_count++;
					_jumpPower = -20;
				}
				else if (_count == 1)
				{
					_count++;
					_jumpPower = -10;
				}
			}
		}
		break;

		case BOSS_STATE::GROUND:
		{
			if (_elapsedTime > 2)
			{
				setState(BOSS_STATE::STAND_UP, _direction, true);
			}
		}
		break;

		case BOSS_STATE::METEOR_ATTACK_DELAY:
		{
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::IDLE, _direction, false);
			}
		}
		break;

		// 공격 상태
		case BOSS_STATE::WEAK_PUNCH_COMBO:
		{
			if (!_ani->isPlay())
			{
				_count++;
				if (_count == 2)
				{
					SOUND_MANAGER->stop("BOSS_Voice_Elbow2");
					SOUND_MANAGER->play("BOSS_Voice_Elbow2", 1.f);
					_attackS = 8;
					_enemyImg = IMAGE_MANAGER->findImage("boss_attack2");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
						_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(30);
					_ani->start();
					
				}
				else if (_count > 2)
				{
					//attack2 공격 렉트
					if (_ani->isPlay())
					{
						if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
						{
							_attackRc = FloatRect(_position.x - 150, _position.y - 45,
								_position.x - 20, _position.y + 30);
						}
						else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
						{
							_attackRc = FloatRect(_position.x + 20, _position.y - 45,
								_position.x + 120, _position.y + 30);
						}
						else
						{
							_attackRc = FloatRect(0, 0, 0, 0);
							_viewRc = FloatRect(0, 0, 0, 0);
						}
						_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
							_attackRc.right, _position.z + _attackRc.bottom);
						enemyAttack(_position, _size, _team, _attackRc, 5, ATTACK_TYPE::STUN);
					}
					else setState(BOSS_STATE::LAUGH, _direction, true);
				}
				else
				{
					SOUND_MANAGER->stop("BOSS_Voice_Elbow");
					SOUND_MANAGER->play("BOSS_Voice_Elbow", 1.f);
					_enemyImg = IMAGE_MANAGER->findImage("boss_attack1");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
						_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(30);
					_ani->start();
				}
			}
			else
			{
				//attack1 공격 렉트
				if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
				{
					_attackRc = FloatRect(_position.x - 150, _position.y - 45,
						_position.x - 20, _position.y + 30);
				}
				else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
				{
					_attackRc = FloatRect(_position.x + 20, _position.y - 45,
						_position.x + 120, _position.y + 30);
				}
				else
				{
					_attackRc = FloatRect(0, 0, 0, 0);
					_viewRc = FloatRect(0, 0, 0, 0);
				}
				_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
					_attackRc.right, _position.z + _attackRc.bottom);
				enemyAttack(_position, _size, _team, _attackRc, 5, ATTACK_TYPE::STUN);
			}
		}
		break;

		case BOSS_STATE::STRONG_PUNCH:
		{
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::LAUGH, _direction, true);
			}
			else
			{
				//이펙트
				if (_ani->isPlay() && _ani->getPlayIndex() >= _attackS && _ani->getPlayIndex() <= _enemyImg->getMaxFrameX())
				{
					float dir = (_direction == DIRECTION::RIGHT) ? 100 : -100;
					EFFECT_MANAGER->playZ("effect_strongPunch", Vector3(_position.x + dir, _position.y - 20, _position.z + 10), 2.f);
				}
				//powerPunch 공격 렉트
				if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
				{
					_attackRc = FloatRect(_position.x - 150, _position.y - 45,
						_position.x - 20, _position.y + 30);
				}
				else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
				{
					_attackRc = FloatRect(_position.x + 20, _position.y - 45,
						_position.x + 120, _position.y + 30);
				}
				else
				{
					_attackRc = FloatRect(0, 0, 0, 0);
					_viewRc = FloatRect(0, 0, 0, 0);
				}
				_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
					_attackRc.right, _position.z + _attackRc.bottom);
				enemyAttack(_position, _size, _team, _attackRc, 5, ATTACK_TYPE::STUN);
			}
		}
		break;

		case BOSS_STATE::STAND_UP:
		{
			if (!_ani->isPlay())
			{
				if (_phase == BOSS_PHASE::PHASE_1 && _hp == 200)
				{
					setState(BOSS_STATE::ROAR, _direction, true);
					_phase = BOSS_PHASE::PHASE_2;
				}
				else if (_phase == BOSS_PHASE::PHASE_2 && _hp == 100)
				{
					setState(BOSS_STATE::ROAR, _direction, true);
					_phase = BOSS_PHASE::PHASE_3;
				}
				else
				{
					setState(BOSS_STATE::IDLE, _direction, true);
				}
			}
			else
			{
				//standup 이펙트
				if (_ani->getPlayIndex() >= _attackS)
				{
					EFFECT_MANAGER->playZ("effect_standUpEffect", Vector3(_position.x, _position.y + 50, _position.z + 30), 5.0f);
				}
				//standup 공격 렉트
				if (_ani->getPlayIndex() == _attackS)
				{
					_size.z = _position.x -1150;
					_attackRc = FloatRect(_position.x - 250, _position.y ,
						_position.x + 250, _position.y + 200);					
				}
				else
				{
					_size.z = 30;
					_attackRc = FloatRect(0, 0, 0, 0);
					_viewRc = FloatRect(0, 0, 0, 0);
				}
				_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
					_attackRc.right, _position.z + _attackRc.bottom);
				enemyAttack(_position, _size, _team, _attackRc, 5, ATTACK_TYPE::STUN);
			}
		}
		break;

		case BOSS_STATE::ROAR:
		{
			if (!_ani->isPlay())
			{
				setState(BOSS_STATE::IDLE, _direction, true);
			}
			else
			{
				//roar 공격 렉트
				if (_ani->getPlayIndex() == _attackS)
				{
					_size.z = _position.x - 1050;
					_attackRc = FloatRect(_position.x - 250, _position.y-200,
						_position.x + 250, _position.y + 200);
				}
				else
				{
					_size.z = 30;
					_attackRc = FloatRect(0, 0, 0, 0);
					_viewRc = FloatRect(0, 0, 0, 0);
				}
				_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
					_attackRc.right, _position.z + _attackRc.bottom);
				enemyAttack(_position, _size, _team, _attackRc, 5, ATTACK_TYPE::STUN);
			}
		}
		break;

		case BOSS_STATE::METEOR_ATTACK:
		{
			if (_count == 0)
			{
				if (_ani->getPlayIndex() >= 6)
				{
					moveDir.y += _jumpPower;

					_enemyManager->moveEnemy(this, moveDir);

					if (_position.y <= -2000)
					{
						_count++;
						_elapsedTime = 0;
					}
				}
			}
			else if (_count == 1) // 플레이어와 근접한 방향으로 이동
			{
				setDirectionToPlayer();
				int speed = (_phase == BOSS_PHASE::PHASE_2) ? 8 : 16;

				moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
				moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
				moveDir = Vector3::normalize(&moveDir);
				moveDir = moveDir * speed;

				_enemyManager->moveEnemy(this, moveDir);

				if (_elapsedTime > 2)
				{
					_count++;
					_enemyImg = IMAGE_MANAGER->findImage("boss_falling");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
						_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(15);
					_ani->start();
				}
				
			}
			else // 떨어지기 
			{
				moveDir.y -= _jumpPower;

				float lastY = _position.y;
				_enemyManager->moveEnemy(this, moveDir);
				float currY = _position.y;

				if (moveDir.y >= 1 && lastY == currY) // 땅에 부딪힘
				{
					_gravity = 0;
					_jumpPower = 0;
					//지면에 떨어졌을 때의 이펙트 재생
					

					if (_phase == BOSS_PHASE::PHASE_2)
					{
						setState(BOSS_STATE::METEOR_ATTACK_DELAY, _direction, true);
					}
					else
					{
						int randomCount = RANDOM->getInt(100);
						if (randomCount < 50)
						{
							_jumpPower = -70;
							setState(BOSS_STATE::METEOR_ATTACK, _direction, true);
						}
						else
						{
							setState(BOSS_STATE::METEOR_ATTACK_DELAY, _direction, true);
						}
					}

					Vector3 attackSize = _size;
					attackSize.z = 150;

					_enemyManager->enemyAttackObject(_position, attackSize, OBJECT_TEAM::BOSS, FloatRect(_position.x - 150, _position.y - 100, _position.x + 150, _position.y + 100), 10, ATTACK_TYPE::KNOCKDOWN);
					enemyAttack(_position, attackSize, OBJECT_TEAM::BOSS, FloatRect(_position.x - 150, _position.y - 100, _position.x + 150, _position.y + 100), 10, ATTACK_TYPE::KNOCKDOWN);
					CAMERA_MANAGER->pushShakeEvent(-20, 0.06, 0.24);
				}
			}
		}
		break;

		case BOSS_STATE::DASH_ATTACK:
		{
			if (_count == 0)
			{
				if (!_ani->isPlay())
				{
					_enemyImg = IMAGE_MANAGER->findImage("boss_tackle_loop");
					_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
						_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
					_ani->setFPS(10);
					_ani->start();
					_count++;
				}
			}
			else if (_count == 1)
			{
				DIRECTION lastDir = _direction;
				setDirectionToPlayer();
				DIRECTION currDir = _direction;

				if (lastDir != currDir) // 방향 전환
				{
					_count++;
					_ani->start();
				}
				else
				{
					int speedX = (_phase == BOSS_PHASE::PHASE_2)? 6: 10;
					int speedZ = (_phase == BOSS_PHASE::PHASE_2) ? 2 : 3;
					moveDir.x += (_direction == DIRECTION::RIGHT) ? speedX : -speedX;
					moveDir.z += (playerPos.z >= _position.z + 90) ? speedZ : ((playerPos.z <= _position.z - 90) ? -speedZ : 0);

					_enemyManager->moveEnemy(this, moveDir);

					Vector3 attackSize = _size;
					attackSize.z = 70;

					FloatRect attackRc;
					if (_direction == DIRECTION::LEFT)
					{
						attackRc = FloatRect(_position.x - 130, _position.y - 100, _position.x, _position.y);
					}
					else
					{
						attackRc = FloatRect(_position.x, _position.y - 100, _position.x + 130, _position.y);
					}
					_viewRc = FloatRect(attackRc.left, _position.z + attackRc.top,
						attackRc.right, _position.z + attackRc.bottom);

					if (_enemyManager->enemyAttack(_position, attackSize, OBJECT_TEAM::BOSS, attackRc, 10, ATTACK_TYPE::KNOCKDOWN) ||
						_enemyManager->enemyAttackObject(_position, attackSize, OBJECT_TEAM::BOSS, attackRc, 10, ATTACK_TYPE::KNOCKDOWN)) // 사물이나 플레이어에게 부딪힘
					{
						setState(BOSS_STATE::LAUGH, _direction, true);
						CAMERA_MANAGER->pushShakeEvent(-20, 0.06, 0.24);
					}
				}
			}
			else if (_count == 2)
			{
				int speedX = (_phase == BOSS_PHASE::PHASE_2) ? 1 : 4;
				int speedZ = (_phase == BOSS_PHASE::PHASE_2) ? 1 : 2;
				moveDir.x += (_direction == DIRECTION::RIGHT) ? -speedX : +speedX;
				moveDir.z += (playerPos.z >= _position.z + 10) ? speedZ : ((playerPos.z <= _position.z - 10) ? -speedZ : 0);

				_enemyManager->moveEnemy(this, moveDir);

				if (!_ani->isPlay())
				{
					_count--;
					_ani->start();
				}
			}
		}
		break;
		}
	}

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());
}

void Boss::render()
{


	//좌우에 따른 애니메이션 프레임 및 루프 조정
	if (_phase != BOSS_PHASE::DEFEAT)
	{
		switch (_bossState)
		{
		case BOSS_STATE::WALK:
		case BOSS_STATE::GROUND:
		{
			if (_direction == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, true);
			}
			else
			{
				_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, true);
			}
		}
		break;
		case BOSS_STATE::GET_HIT:
		{
			if (_direction == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(_enemyImg->getMaxFrameX() + 3 * (_combo - 1), _enemyImg->getMaxFrameX() + 3 * _combo, false, false);
			}
			else
			{
				_ani->setPlayFrame(3 * (_combo - 1), 3 * _combo, false, false);
			}
		}
		break;
		case BOSS_STATE::METEOR_ATTACK:
		{


			if (_count == 0)
			{
				if (_direction == DIRECTION::LEFT)
				{
					_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, false);
				}
				else
				{
					_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, false);
				}
			}
			else if (_count == 2)
			{
				if (_direction == DIRECTION::LEFT)
				{
					_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, true);
				}
				else
				{
					_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, true);
				}
			}
		}
		break;
		case BOSS_STATE::DASH_ATTACK:
		{
			if (_count == 0)
			{
				if (_direction == DIRECTION::LEFT)
				{
					_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, false);
				}
				else
				{
					_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, false);
				}
			}
			else if (_count == 1)
			{
				_ani->setFPS(20);
				if (_direction == DIRECTION::LEFT)
				{
					_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() + 8, false, true);
				}
				else
				{
					_ani->setPlayFrame(0, 8, false, true);
				}
			}
			else if (_count == 2)
			{
				_ani->setFPS(10);

				if (_direction == DIRECTION::RIGHT)
				{
					_ani->setPlayFrame(_enemyImg->getMaxFrameX() + 8, _enemyImg->getMaxFrameX() * 2, false, false);
				}
				else
				{
					_ani->setPlayFrame(8, _enemyImg->getMaxFrameX(), false, false);
				}
			}
		}
		break;
		default:
		{
			if (_direction == DIRECTION::LEFT)
			{
				_ani->setPlayFrame(_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameX() * 2, false, false);
			}
			else
			{
				_ani->setPlayFrame(0, _enemyImg->getMaxFrameX(), false, false);
			}
		}
		break;
		}
	}


	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::ENEMY))
	{
		_enemyImg->setAlpha(0.5);
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z + _position.y + (_size.y / 2)), Vector2(_size.x, _size.z), Pivot::Center);
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
		CAMERA_MANAGER->rectangle(_viewRc, D2D1::ColorF::Enum::Magenta, 1, 1);
	}

	_enemyImg->setScale(3);

	if (_phase == BOSS_PHASE::DEFEAT)
	{
		Vector3 drawPos = _position;
		drawPos.y -= 20;
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani, -(_position.y + (_size.y / 2)));
	}
	else
	{
		switch (_bossState) // 이미지 그리기
		{
		case BOSS_STATE::LAUGH:
		{
			Vector3 drawPos = _position;
			drawPos.y -= 35;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani);
		}
		break;
		case BOSS_STATE::IDLE:
		{
			Vector3 drawPos = _position;
			drawPos.y -= 20;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani);
		}
		break;
		case BOSS_STATE::STRONG_PUNCH:
		{
			Vector3 drawPos = _position;
			drawPos.y += 10;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani);
		}
		break;
		case BOSS_STATE::WEAK_PUNCH_COMBO:
		{
			if (_count == 2)
			{
				Vector3 drawPos = _position;
				drawPos.y -= 15;
				CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani);
			}
			else
			{
				Vector3 drawPos = _position;
				drawPos.y -= 20;
				CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani);
			}
		}
		break;
		case BOSS_STATE::GROUND:
		case BOSS_STATE::GROUND_HIT:
		case BOSS_STATE::STAND_UP:
		case BOSS_STATE::ROAR:
		case BOSS_STATE::GET_HIT:
		case BOSS_STATE::METEOR_ATTACK:
		case BOSS_STATE::METEOR_ATTACK_DELAY:
		{
			Vector3 drawPos = _position;
			drawPos.y -= 20;
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drawPos, _size, _ani);
		}
		break;
		default:
		{
			CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);
		}
		break;
		}
	}	
	if (_phase == BOSS_PHASE::PHASE_3)
	{

		if (_electricTime < 0 && _bossState != BOSS_STATE::METEOR_ATTACK &&  _bossState != BOSS_STATE::ROAR)
		{
			EFFECT_MANAGER->playZ("effect_electric", Vector3(_position.x, -310.0, _position.z - 20), 1);
			_electricTime = 0.5;
		}
	}
	
	if (_bossState == BOSS_STATE::DASH_ATTACK)
	{
		if(_direction == DIRECTION::LEFT)
		{
		   EFFECT_MANAGER->playZ("effect_dashAttackEffect", Vector3(_position.x +50, -10.0, _position.z - 20), 1);
		}
		else
		{
			EFFECT_MANAGER->playZ("effect_dashAttackEffect", Vector3(_position.x - 50, -10.0, _position.z - 20), 1);
		}
		
	}

	switch (_bossState) // 그림자 그리기
	{
	default:
	{
		Vector3 shadowPos = _position;
		shadowPos.y = 0;
		CAMERA_MANAGER->drawShadowZ(shadowPos, Vector3(200.0, 0, 40.0));
	}
	break;
	}
}

void Boss::setState(BOSS_STATE state, DIRECTION direction, bool initTime)
{
	_bossState = state;
	if (initTime)
	{
		_elapsedTime = 0;
	}

	//상태에 따른 애니메이션
	switch (state)
	{
	case BOSS_STATE::IDLE:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_idle");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::WALK:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_walk");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;
	case BOSS_STATE::LAUGH:
	{
		int playRate = RANDOM->getInt(2);
		char str[128];
		sprintf_s(str, "BOSS_Voice_Laugh%d", playRate);
		SOUND_MANAGER->stop(str);
		SOUND_MANAGER->play(str, 1.f);
		_enemyImg = IMAGE_MANAGER->findImage("boss_laugh");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;
	case BOSS_STATE::STRONG_PUNCH:
	{
		SOUND_MANAGER->stop("Boss_Effect_WUPunch");
		SOUND_MANAGER->play("Boss_Effect_WUPunch", 1.f);
		_attackS = 17;
		_enemyImg = IMAGE_MANAGER->findImage("boss_powerAttack");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;
	case BOSS_STATE::WEAK_PUNCH_COMBO:
	{
		SOUND_MANAGER->stop("BOSS_Voice_Elbow");
		SOUND_MANAGER->play("BOSS_Voice_Elbow", 1.f);
		_count = 0;
		_attackS = 5;
		_enemyImg = IMAGE_MANAGER->findImage("boss_attack1");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(30);
		_ani->start();
	}
	break;
	case BOSS_STATE::GET_HIT:
	{
		SOUND_MANAGER->stop("BOSS_Voice_GetHit");
		SOUND_MANAGER->play("BOSS_Voice_GetHit", 1.f);
		_enemyImg = IMAGE_MANAGER->findImage("boss_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case BOSS_STATE::GROUND_HIT:
	{

		_enemyImg = IMAGE_MANAGER->findImage("boss_groundHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case BOSS_STATE::KNOCKDOWN:
	{
		_count = 0;
		_enemyImg = IMAGE_MANAGER->findImage("boss_blownBack");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::GROUND:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_dizzy");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case BOSS_STATE::STAND_UP:
	{
		_attackS = 5;
		_enemyImg = IMAGE_MANAGER->findImage("boss_getup");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::ROAR:
	{
		//SOUND_MANAGER->stop("BOSS_Voice_Scream");
		//SOUND_MANAGER->play("BOSS_Voice_Scream", 1.f);
		_attackS = 5;
		_enemyImg = IMAGE_MANAGER->findImage("boss_roar");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
	}
	break;
	case BOSS_STATE::METEOR_ATTACK:
	{
		SOUND_MANAGER->stop("Boss_Effect_Jump");
		SOUND_MANAGER->play("Boss_Effect_Jump", 1.f);
		_count = 0;
		_enemyImg = IMAGE_MANAGER->findImage("boss_jump");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
		
	}
	break;
	case BOSS_STATE::METEOR_ATTACK_DELAY:
	{
		_enemyImg = IMAGE_MANAGER->findImage("boss_fallingmiss");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case BOSS_STATE::DASH_ATTACK:
	{
		_count = 0;
		_enemyImg = IMAGE_MANAGER->findImage("boss_tackle_init");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(20);
		_ani->start();
	}
	break;
	}
}

bool Boss::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_bossState == BOSS_STATE::GET_HIT || _bossState == BOSS_STATE::GROUND_HIT) return false;

	if (_phase == BOSS_PHASE::PHASE_1)
	{
		_hp = max(200, _hp - damage);
	}
	else if (_phase == BOSS_PHASE::PHASE_2)
	{
		_hp = max(100, _hp - damage);
	}
	else if (_phase == BOSS_PHASE::PHASE_3)
	{
		_hp = max(0, _hp - damage);
	}

	_combo++;

	if (_bossState == BOSS_STATE::IDLE || _bossState == BOSS_STATE::WALK || _bossState == BOSS_STATE::LAUGH) // 빈틈
	{
		if (_combo > 3 || type == ATTACK_TYPE::KNOCKDOWN)
		{
			_combo = 0;
			setState(BOSS_STATE::KNOCKDOWN, _direction, true);
		}
		else
		{
			_jumpPower = -30;
			_gravity = 0;
			setState(BOSS_STATE::GET_HIT, _direction, true);
		}
	}
	else if (_bossState == BOSS_STATE::GROUND)
	{
		_jumpPower = -10;
		_gravity = 0;
		setState(BOSS_STATE::GROUND_HIT, _direction, false);
	}

	return true;

}

void Boss::setAttackState(BOSS_PHASE phase, float playerDistance)
{
	switch (phase)
	{
	case BOSS_PHASE::PHASE_1:
	{
		if (playerDistance < 140)
		{
			int randomCount = RANDOM->getInt(100);
			if (randomCount < 50)
			{
				setState(BOSS_STATE::STRONG_PUNCH, _direction, true);
			}
			else
			{
				setState(BOSS_STATE::WEAK_PUNCH_COMBO, _direction, true);
			}
		}
	}
	break;
	case BOSS_PHASE::PHASE_2:
	{
		int randomCount = RANDOM->getInt(100);
		if (playerDistance < 140)
		{
			if (randomCount < 20) // 10%
			{
				setState(BOSS_STATE::STRONG_PUNCH, _direction, true);
			}
			else if (randomCount < 40) // 10%
			{
				setState(BOSS_STATE::WEAK_PUNCH_COMBO, _direction, true);
			}
			else  // 40%
			{
				_jumpPower = -50;
				setState(BOSS_STATE::METEOR_ATTACK, _direction, true);
			}
		}
		else
		{
			if (randomCount < 2)
			{
				setState(BOSS_STATE::DASH_ATTACK, _direction, true);
			}
			else if (randomCount < 4)
			{
				_jumpPower = -50;
				setState(BOSS_STATE::METEOR_ATTACK, _direction, true);
			}
		}
	}
	break;
	case BOSS_PHASE::PHASE_3:
	{
		int randomCount = RANDOM->getInt(100);
		if (playerDistance < 140)
		{
			if (randomCount < 20) // 10%
			{
				setState(BOSS_STATE::STRONG_PUNCH, _direction, true);
			}
			else if (randomCount < 40) // 10%
			{
				setState(BOSS_STATE::WEAK_PUNCH_COMBO, _direction, true);
			}
			else  // 40%
			{
				_jumpPower = -70;
				setState(BOSS_STATE::METEOR_ATTACK, _direction, true);
			}
		}
		else
		{
			if (randomCount < 2)
			{
				setState(BOSS_STATE::DASH_ATTACK, _direction, true);
			}
			else if (randomCount < 4)
			{
				_jumpPower = -70;
				setState(BOSS_STATE::METEOR_ATTACK, _direction, true);
			}
		}
	}
	break;
	}
}