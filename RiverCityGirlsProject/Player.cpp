#include "stdafx.h"
#include "Player.h"
#include "AllPlayerState.h"
#include "StageManager.h"


Player::Player()
{
}

Player::~Player()
{
}

void Player::move(Vector3 moveDir)
{
	_stageManager->moveGameObject(this, moveDir);
}

void Player::init()
{
	setPosition(Vector3(330, -105, 600));
	setSize(Vector3(80, 210, 30));

	_state = new IdleState;
	_state->enter(*this);

	_direction = DIRECTION::RIGHT;

	_team = OBJECT_TEAM::PLAYER;
	_jumpPower = 25;
	_gravity = 1.0f;
	_speed = 5;
	_maxHp = 100;
	_hp = _maxHp;
	_money = 0;
	_onObject = false;
	_damageTime = 0;
	_isHit = false;
	_guarding=false;
	_mortalTime = 0;
}

void Player::release()
{
	_state->exit(*this);
	delete _state;

	//_attackState->exit(*this); 
	//delete _attackState;
}

void Player::update()
{
	

	PlayerState* _newState = _state->update(*this);
	if (_newState != nullptr)
	{
		_state->exit(*this);
		delete _state;
		_state = _newState;
		_damageTime = 0;
		_state->enter(*this);
	}

	

	/*AttackState* _newAttackState = _attackState->update(*this);
	if (_newAttackState != nullptr)
	{
		_attackState->exit(*this);
		delete _attackState;
		_attackState = _newAttackState;
		_attackState->enter(*this);
	}*/
}

void Player::render()
{
	_state->render(*this);

	if (DEBUG_MANAGER->isDebugMode(DEBUG_TYPE::PLAYER))
	{
		FloatRect rc = FloatRect(Vector2(_position.x, _position.z + _position.y + (_size.y / 2)), Vector2(_size.x, _size.z), Pivot::Center);
		CAMERA_MANAGER->drawLine(Vector2(_position.x, _position.z), Vector2(_position.x, _position.z + _position.y));
		CAMERA_MANAGER->rectangle(rc, D2D1::ColorF::Enum::Red, 1, 1);
	}
	
}

float Player::getCenterBottom()
{
	return _stageManager->getCenterBottom(_position);
}

bool Player::attack(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	return _stageManager->playerAttack(pos, size, team, attackRc, damage, type);
}

bool Player::getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	if (_isHit) return false;
		

	_getHitType = type;
	_damage = damage;


	Vector3 enemyPos = pos;
	Vector3 enemySize = size;
	float hitterMinZ = enemyPos.z - enemySize.z / 2;
	float hitterMaxZ = enemyPos.z + enemySize.z / 2;
	float playerMinZ = _position.z - _size.z / 2;
	float playerMaxZ = _position.z + _size.z / 2;

	if (playerMaxZ<hitterMinZ || playerMinZ>hitterMaxZ) return false;
	
	FloatRect getHitRc = FloatRect(_position.x - _size.x / 2, _position.y - _size.y / 2, _position.x + _size.x / 2, _position.y + _size.y / 2);
	
	if (FloatRect::intersect(getHitRc, attackRc))
	{

		

		PlayerState* state = new getHitState;
		PlayerState* gdState = new GuardState;
		
		if (_guarding)
		{
			if (pos.x > _position.x && _direction == DIRECTION::LEFT)
			{
				if (pos.x > _position.x)
				{
					_direction == DIRECTION::RIGHT;
				}
				else
				{
					_direction = DIRECTION::LEFT;
				}
				int num = RANDOM->getFromIntTo(1, 5);
				SOUND_MANAGER->stop("KYOKO_GetHit" + to_string(num));
				SOUND_MANAGER->play("KYOKO_GetHit" + to_string(num), 1.0f);
				SOUND_MANAGER->stop("STAGE_HitSound" + to_string(num));
				SOUND_MANAGER->play("STAGE_HitSound" + to_string(num), 1.0f);

				EFFECT_MANAGER->playZ("effect_4", Vector3((attackRc.left + attackRc.right) / 2, (attackRc.top + attackRc.bottom) / 2, _position.z + _size.z / 2), 1);
				_state->exit(*this);
				delete _state;
				_state = state;
				state->enter(*this);
				return true;
			}
			if (pos.x < _position.x && _direction == DIRECTION::RIGHT)
			{
				if (pos.x > _position.x)
				{
					_direction == DIRECTION::RIGHT;
				}
				else
				{
					_direction = DIRECTION::LEFT;
				}
				int num = RANDOM->getFromIntTo(1, 4);
				SOUND_MANAGER->stop("KYOKO_GetHit" + to_string(num));
				SOUND_MANAGER->play("KYOKO_GetHit" + to_string(num), 1.0f);
				SOUND_MANAGER->stop("STAGE_HitSound" + to_string(num));
				SOUND_MANAGER->play("STAGE_HitSound" + to_string(num), 1.0f);
				
				EFFECT_MANAGER->playZ("effect_4", Vector3((attackRc.left + attackRc.right) / 2, (attackRc.top + attackRc.bottom) / 2, _position.z + _size.z / 2), 1);
				_state->exit(*this);
				delete _state;
				_state = state;
				state->enter(*this);
				return true;
			}
			else 
			{
				EFFECT_MANAGER->playZ("effect_guard", Vector3(attackRc.getCenter().x, attackRc.getCenter().y, _position.z + _size.z / 2), 0.2);
				int num = RANDOM->getFromIntTo(1, 4);
				SOUND_MANAGER->stop("STAGE_HitSound" + to_string(num));
				SOUND_MANAGER->play("STAGE_HitSound" + to_string(num), 1.0f);
				_state->exit(*this);
				delete _state;
				_state = gdState;
				gdState->enter(*this);
				return true;
			}
		}
		else
		{
			if (pos.x > _position.x)
			{
				_direction == DIRECTION::RIGHT;
			}
			else
			{
				_direction = DIRECTION::LEFT;
			}

			EFFECT_MANAGER->playZ("effect_4", Vector3(attackRc.getCenter().x, attackRc.getCenter().y, _position.z + _size.z / 2), 1);
			int num = RANDOM->getFromIntTo(1, 4);

			SOUND_MANAGER->stop("KYOKO_GetHit" + to_string(num));
			SOUND_MANAGER->play("KYOKO_GetHit" + to_string(num),1.0f);
			SOUND_MANAGER->stop("STAGE_HitSound" + to_string(num));
			SOUND_MANAGER->play("STAGE_HitSound" + to_string(num), 1.0f);

			_state->exit(*this);
			delete _state;
			_state = state;
			state->enter(*this);
			return true;
		}

	}
	return false;

}

void Player::setIdleState()
{
	PlayerState* state = new IdleState;
	_state->exit(*this);
	delete _state;
	_state = state;
	state->enter(*this);
}

void Player::setStartState()
{
	PlayerState* state = new StartState;
	_state->exit(*this);
	delete _state;
	_state = state;
	state->enter(*this);
}

void Player::gameOver()
{
	_stageManager->gameOver();
}
