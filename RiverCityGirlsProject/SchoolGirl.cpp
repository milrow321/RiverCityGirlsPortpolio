#include "stdafx.h"
#include "SchoolGirl.h"

void SchoolGirl::init()
{
	
	_position = Vector3(1000, -105, 500);
	_size = Vector3(80, 210, 30);
	_state = ENEMY_STATE::IDLE;
	_direction = DIRECTION::RIGHT;
	setState(_state, _direction);
	_isActive = true;
	_gravity = 0;
	_jumpPower = 0;
	_hp = 100;
}

void SchoolGirl::release()
{
	_ani->release();
	SAFE_DELETE(_ani);
}

void SchoolGirl::update()
{


	_attackRc = FloatRect(0, 0, 0, 0);
	_viewRc = FloatRect(0, 0, 0, 0);
	
	
	Vector3 playerPos = _enemyManager->getPlayerPosition(); // 플레이어의 위치
	float distanceFromPlayer = sqrt(pow(playerPos.x - _position.x, 2) + pow(playerPos.z - _position.z, 2)); // 플레이어와 xz 거리
	Vector3 moveDir = Vector3(0, 0, 0);
	_elapsedTime += TIME_MANAGER->getElapsedTime();
	float playerHp = _enemyManager->getPlayerHp();
	if (playerHp <= 0)
	{
		setState(ENEMY_STATE::IDLE, _direction);
	}
	if (_elapsedTime >1)
	{
		_hitCount = 0;
	}

	// 상태에 따른 행동 및 상태 전이
	switch (_state)
	{
	case ENEMY_STATE::IDLE: // 대기 상태
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		if (_elapsedTime > 1)
		{
			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // 플레이어에게 달려가기
			}
			else
			{
				setState(ENEMY_STATE::WALK, _direction); // 플레이어에게 걸어가기
			}
		}
	}
	break;

	case ENEMY_STATE::WALK: // 걷기 상태
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		_gravity += 1;

		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 2;
		moveDir.y += _gravity;
		
		float lastY = _position.y;
		float lastX = _position.x;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;	
		float currX = _position.x;

		if (lastY != currY) // 떨어짐
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			_gravity = 0;
			if (distanceFromPlayer <= 100) // 근접 시 공격
			{
				setState(ENEMY_STATE::ATTACK, _direction);
				if (_state != ENEMY_STATE::ATTACK && _hitType == ATTACK_TYPE::HIT1)
				{
					setState(ENEMY_STATE::GUARD, _direction);
				}
			}
			else if (_elapsedTime >= 5) 
			{
				setState(ENEMY_STATE::SKILL, _direction);
				_gravity = -22;
			}			
		}
		if (_state == ENEMY_STATE::WALK && lastX == currX )
		{
			
			setState(ENEMY_STATE::RETURN, _direction);
		}
		
		
	}
	break;
	case ENEMY_STATE::RUN:
	{
		setDirectionToPlayer(); // 플레이어 바라보기

		_gravity += 1;

		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;		
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 4;
		moveDir.y += _gravity;

		float lastY = _position.y;
		float lastX = _position.x;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;
		float currX = _position.x;
		
		
	
		if (lastY != currY) // 떨어짐
		{
			setState(ENEMY_STATE::JUMP, _direction);
		}
		else
		{
			_gravity = 0;
			if (distanceFromPlayer <= 100) // 근접 시 공격
			{
				setState(ENEMY_STATE::DASHATTACK, _direction);
			}
			else if (_elapsedTime >= 5) // 오랜 쫓음으로 인해 한번 점프해본다
			{
				setState(ENEMY_STATE::JUMP, _direction);
				_gravity = -26;
			}
		}
		if (_state == ENEMY_STATE::RUN && lastX == currX)
		{

			setState(ENEMY_STATE::RETURN, _direction);
		}
	
	}
	break;
	case ENEMY_STATE::RETURN:
	{
		moveDir.z += (playerPos.z < _position.z ) ? 1 : ((playerPos.z > _position.z ) ? -1 : 0);
		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 1;
		_enemyManager->moveEnemy(this, moveDir);

		if (_elapsedTime > 1.5)
		{
			_elapsedTime = 0;
			setState(ENEMY_STATE::WALK, _direction);

			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // 플레이어에게 달려가기
			}
		}
	}
	break;
	case ENEMY_STATE::JUMP:
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 2;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (_gravity > 1 && lastY == currY) // 착지한 경우
		{
			_gravity = 0;
			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // 플레이어에게 달려가기
			}
			else
			{
				setState(ENEMY_STATE::WALK, _direction); // 플레이어에게 걸어가기
			}
		}
	}
	break;

	case ENEMY_STATE::ATTACK:
	{
		if (!_ani->isPlay()) // 공격 모션이 끝났다면
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
		else
		{
			if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x - 130, _position.y - 35,
					_position.x - 20, _position.y + 20);

			}
			else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x + 20, _position.y - 35,
					_position.x + 100, _position.y + 20);
			}
			else
			{
				_attackRc = FloatRect(0, 0, 0, 0);
				_viewRc = FloatRect(0, 0, 0, 0);
			}
			_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
				_attackRc.right, _position.z + _attackRc.bottom);
			enemyAttack(_position, _size, OBJECT_TEAM::ENEMY, _attackRc, 5, ATTACK_TYPE::HIT1);
		}
	
	}
	break;

	case ENEMY_STATE::DASHATTACK:
	{
		if (!_ani->isPlay()) // 공격 모션이 끝났다면
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
		else
		{
			if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x - 130, _position.y - 35,
					_position.x - 20, _position.y + 20);
			}
			else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x + 20, _position.y - 35,
					_position.x + 100, _position.y + 20);
			}
			else
			{
				_attackRc = FloatRect(0, 0, 0, 0);
				_viewRc = FloatRect(0, 0, 0, 0);
			}
			_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
				_attackRc.right, _position.z + _attackRc.bottom);
			 enemyAttack(_position, _size, OBJECT_TEAM::ENEMY, _attackRc, 5, ATTACK_TYPE::HIT2);
		}
		
	}
	break;
	case ENEMY_STATE::SKILL:
	{
		_gravity += 1;
		moveDir.x += (_direction == DIRECTION::RIGHT) ? 1 : -1;
		moveDir.z += (playerPos.z >= _position.z + 10) ? 1 : ((playerPos.z <= _position.z - 10) ? -1 : 0);
		moveDir = Vector3::normalize(&moveDir);
		moveDir = moveDir * 2;
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (_gravity > 1 && lastY == currY) // 착지한 경우
		{
			_gravity = 0;
			if (distanceFromPlayer > 400)
			{
				setState(ENEMY_STATE::RUN, _direction); // 플레이어에게 달려가기
			}
			else
			{
				setState(ENEMY_STATE::WALK, _direction); // 플레이어에게 걸어가기
			}
		}

		if (!_ani->isPlay()) // 공격 모션이 끝났다면
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
		else
		{
			if (_direction == DIRECTION::LEFT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x - 130, _position.y - 35,
					_position.x - 20, _position.y + 20);
			}
			else if (_direction == DIRECTION::RIGHT && _ani->getPlayIndex() == _attackS)
			{
				_attackRc = FloatRect(_position.x + 20, _position.y - 35,
					_position.x + 100, _position.y + 20);
			}
			else
			{
				_attackRc = FloatRect(0, 0, 0, 0);
				_viewRc = FloatRect(0, 0, 0, 0);
			}
			_viewRc = FloatRect(_attackRc.left, _position.z + _attackRc.top,
				_attackRc.right, _position.z + _attackRc.bottom);
			enemyAttack(_position, _size, OBJECT_TEAM::ENEMY, _attackRc, 5, ATTACK_TYPE::KNOCKDOWN);
		}
	}
	break;

	case ENEMY_STATE::HIT: // 작은 경직
	{
		
			_gravity += 1;
			moveDir.x += (_direction == DIRECTION::RIGHT) ? -1 : 1;
			moveDir.y += _gravity;

			float lastY = _position.y;
			_enemyManager->moveEnemy(this, moveDir);
			float currY = _position.y;
			
			_hitCount += 1;
			if (lastY != currY) // 떨어짐
			{
				setState(ENEMY_STATE::JUMP, _direction);
			}
			else
			{
				if (!_ani->isPlay() && _hp > 0)
				{
					setState(ENEMY_STATE::IDLE, _direction);
				}
				else if (_hp <= 0)
				{
					_gravity = -16.0f;
					setState(ENEMY_STATE::KNOCKDOWN, _direction);
				}
				else if (_hitCount > 60)
				{
					
					_gravity = -16.0f;
					setState(ENEMY_STATE::KNOCKDOWN, _direction);
					
				}
				
				
			}
			
			
		
	}
	break;

	case ENEMY_STATE::KNOCKDOWN: // 쓰러지는 경직
	{
	
		_gravity += 1;
		if (_hp > 0 && _ani->isPlay() && _elapsedTime < 1) {
			moveDir.x += (_direction == DIRECTION::RIGHT) ? -1 : 1;
		}
		moveDir.y += _gravity;

		float lastY = _position.y;
		_enemyManager->moveEnemy(this, moveDir);
		float currY = _position.y;

		if (moveDir.y > 1 && lastY == currY) // 땅에 부딪힘
		{
			_gravity = 0;

			if (_elapsedTime > 3 && _hp > 0)
			{
				setState(ENEMY_STATE::STANDUP, _direction);
			}
			else if (_hp <= 0 && !_ani->isPlay())
			{
				_isActive = false;
			}
		}
	}
	break;

	case ENEMY_STATE::STANDUP: // 쓰러지고 일어서는 상태
	{
		
		int randomCount = RANDOM->getInt(10);
		if (randomCount < 3 && !_ani->isPlay() && _hp <50)
		{
			setState(ENEMY_STATE::STUN, _direction);
		}
		else if (!_ani->isPlay() && randomCount > 2)
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	
	
	}
	break;

	case ENEMY_STATE::STUN: // 스턴 걸린 상태
	{
		if (_elapsedTime > 3.0f)
		{
			setState(ENEMY_STATE::IDLE, _direction);
		}
	}
	break;
	}

	

	_ani->frameUpdate(TIME_MANAGER->getElapsedTime());

}

void SchoolGirl::render()
{	

	

	//좌우에 따른 애니메이션 프레임 및 루프 조정
	switch (_state)
	{
	case ENEMY_STATE::IDLE:
	case ENEMY_STATE::WALK:
	case ENEMY_STATE::RETURN:
	case ENEMY_STATE::RUN:
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
	case ENEMY_STATE::HIT:
	{
		
		if (_direction == DIRECTION::LEFT)
		{
			if (_hitType == ATTACK_TYPE::HIT1)
			{
				_ani->setPlayFrame(9, 12, false, false);
			}
			else if (_hitType == ATTACK_TYPE::HIT2)
			{
				_ani->setPlayFrame(12, 15, false, false);
			}
		}
		else
		{
			if (_hitType == ATTACK_TYPE::HIT1)
			{
				_ani->setPlayFrame(0, 3, false, false);
			}
			else if (_hitType == ATTACK_TYPE::HIT2)
			{
				_ani->setPlayFrame(3, 6, false, false);
			}
		}
		
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
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
	case ENEMY_STATE::STUN:
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

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::ENEMY))
	{
	
		
		_enemyImg->setAlpha(0.5);
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z + _position.y + (_size.y / 2)), Vector2(_size.x, _size.z), Pivot::Center);		
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
		CAMERA_MANAGER->rectangle(_viewRc, D2D1::ColorF::Enum::Red, 1, 1);
	}

	switch (_state) // 그림자 그리기
	{
	case ENEMY_STATE::JUMP:
	case ENEMY_STATE::KNOCKDOWN:
	{
		Vector3 shadowPos = _position;
		shadowPos.y = _enemyManager->getCenterBottom(_position);
		CAMERA_MANAGER->drawShadowZ(shadowPos, Vector3(120.0, 0, 25.0), -shadowPos.y);
	}
	break;
	default:
	{
		CAMERA_MANAGER->drawShadowZ(_position, Vector3(120.0, _size.y, 25.0), -(_position.y + (_size.y / 2)));
	}
	break;
	}
	if (_state == ENEMY_STATE::KNOCKDOWN  )
	{ 
		

		if (_hp <= 0 && !_ani->isPlay())
		{
			if (fmod(_elapsedTime, 0.2f) < 0.1f)
			{
				_enemyImg->setAlpha(1);
			}
			if (fmod(_elapsedTime, 0.2f) > 0.1f)
			{
				_enemyImg->setAlpha(0);
			}
			if (_elapsedTime > 5)
			{
				_elapsedTime = 0;
				_isActive = false;
			}

			Vector3 drowPos = _position;
			drowPos.y = _position.y + 30;
			_enemyImg->setScale(3);
			CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani);
		}
		else
		{
		Vector3 drowPos = _position;
		drowPos.y = _position.y + 30;
		_enemyImg->setScale(3);
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani);
		}
	}
	else if (_state == ENEMY_STATE::HIT)
	{
		Vector3 drowPos = _position;
		drowPos.y = _position.y + 10;
		_enemyImg->setScale(3);
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani);
	}
	else if (_state == ENEMY_STATE::GUARD)
	{
		Vector3 drowPos = _position;
		drowPos.y = _position.y + 15;
		_enemyImg->setScale(3);
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani);
	}
	else if (_state == ENEMY_STATE::IDLE)
	{
		Vector3 drowPos = _position;
		drowPos.y = _position.y + 10;
		_enemyImg->setScale(3);
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani);
	}
	else if (_state == ENEMY_STATE::STUN)
	{
		Vector3 drowPos = _position;
		drowPos.y = _position.y + 30;
		_enemyImg->setScale(3);
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani);
	}
	else if (_state == ENEMY_STATE::STANDUP)
	{
		Vector3 drowPos = _position;
		drowPos.y = _position.y + 30;
		_enemyImg->setScale(3);
		CAMERA_MANAGER->aniRenderZ(_enemyImg, drowPos, _size, _ani);
	}
	else{
	 _enemyImg->setScale(3);
	 CAMERA_MANAGER->aniRenderZ(_enemyImg, _position, _size, _ani);
	}

}


bool SchoolGirl::hitEffect(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{


	if (_state == ENEMY_STATE::KNOCKDOWN || _state == ENEMY_STATE::STANDUP) {
		return false;
	}
	if (_state != ENEMY_STATE::KNOCKDOWN || _state != ENEMY_STATE::STANDUP ) {
		_hitType = type;
		if (_state != ENEMY_STATE::HIT && _state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP)
		{
			if (_hitType == ATTACK_TYPE::HIT1 || _hitType == ATTACK_TYPE::HIT2)
			{

				_hp = _hp - damage;
				setState(ENEMY_STATE::HIT, _direction);

			}
			else if (_hitType == ATTACK_TYPE::KNOCKDOWN)
			{
				_hp = _hp - damage;
				_gravity = -16.0f;
				setState(ENEMY_STATE::KNOCKDOWN, _direction);


			}
			else if (_hitType == ATTACK_TYPE::STUN)
			{
				setState(ENEMY_STATE::STUN, _direction);
			}
		}
		return true;
	}
	
}

void SchoolGirl::setState(ENEMY_STATE state, DIRECTION direction)
{
	_state = state;
	_elapsedTime = 0;

	//상태에 따른 애니메이션
	switch (state)
	{
	case ENEMY_STATE::IDLE:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_idle");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::WALK:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_walk");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::RETURN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_walk");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());

		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::RUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_run");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::JUMP:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_jump");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(2);
		_ani->start();
	}
	break;
	case ENEMY_STATE::ATTACK:
	{
		_ani = new Animation;
		int i = RANDOM->getFromIntTo(1, 3);		
		if (i == 2)
		{
			_attackS = 3;
		}
		else
		{
			_attackS = 3;
		}	
		char imgNameNum[128];
		sprintf_s(imgNameNum, "schoolgirl_attack%d", i);
		_enemyImg = IMAGE_MANAGER->findImage(imgNameNum);
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();	

		char soundNameNum[128];
		sprintf_s(soundNameNum, "SchoolGirl_Attack%d", i);
		SOUND_MANAGER->stop("SchoolGirl_Attack1");
		SOUND_MANAGER->stop("SchoolGirl_Attack2");
		SOUND_MANAGER->stop("SchoolGirl_Attack3");
		SOUND_MANAGER->play(soundNameNum, 0.7f);
	}
	break;
	case ENEMY_STATE::DASHATTACK:
	{
		_attackS = 3;
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_attack3");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::JUMPATTACK:
	{
		_attackS = 3;
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_jumpAttack2");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
	}
	break;
	case ENEMY_STATE::HIT:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_getHit");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();

		SOUND_MANAGER->stop("SchoolGirl_GetHit3");
		SOUND_MANAGER->play("SchoolGirl_GetHit3", 0.7f);
	}
	break;
	case ENEMY_STATE::STUN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_stun");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(7);
		_ani->start();
	}
	break;
	case ENEMY_STATE::GUARD:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_block");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(7);
		_ani->start();
	}
	break;
	case ENEMY_STATE::KNOCKDOWN:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_knockDown");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(15);
		_ani->start();
		SOUND_MANAGER->stop("SchoolGirl_GetHit2");
		SOUND_MANAGER->play("SchoolGirl_GetHit2", 0.7f);
	}
	break;
	case ENEMY_STATE::STANDUP:
	{
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_standUp");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(8);
		_ani->start();
	}
	break;
	case ENEMY_STATE::SKILL:
	{
		_attackS = 1;
		_ani = new Animation;
		_enemyImg = IMAGE_MANAGER->findImage("schoolgirl_skill");
		_ani->init(_enemyImg->getWidth(), _enemyImg->getHeight(),
			_enemyImg->getMaxFrameX(), _enemyImg->getMaxFrameY());
		_ani->setFPS(10);
		_ani->start();
		SOUND_MANAGER->stop("SchoolGirl_tornado");
		SOUND_MANAGER->play("SchoolGirl_tornado", 0.7f);
	}
	break;
	}
}

void SchoolGirl::setDirectionToPlayer()
{
	Vector3 playerPos = _enemyManager->getPlayerPosition();
	if (_state != ENEMY_STATE::KNOCKDOWN && _state != ENEMY_STATE::STANDUP
		&& _state != ENEMY_STATE::HIT && _state != ENEMY_STATE::STUN)
	{
		if (playerPos.x <= _position.x - 50)
		{
			_direction = DIRECTION::LEFT;
		}
		else if (playerPos.x >= _position.x + 50)
		{
			_direction = DIRECTION::RIGHT;
		}
	}
}



