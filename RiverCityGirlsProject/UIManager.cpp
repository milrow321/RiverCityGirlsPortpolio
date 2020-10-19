#include "stdafx.h"
#include "UIManager.h"
#include "Player.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init(Player* player)
{
	HRESULT result;

	_player = player;	

	ZeroMemory(&_playerInfo,	sizeof(_playerInfo));
	ZeroMemory(&_bossInfo,		sizeof(_bossInfo));
	ZeroMemory(&_heart,			sizeof(_heart));
	ZeroMemory(&_levelInfo,		sizeof(_levelInfo));
	ZeroMemory(&_cellPhone,		sizeof(_cellPhone));

	result = _playerInfo.init();
	result = _bossInfo.init();
	result = _levelInfo.init();
	result = _heart.init(3);
	result = _shop.init();
	
	
	return result;
}

void UIManager::release()
{
}

void UIManager::update()
{
	// 플레이어 컨트롤
	_playerInfo.update(_player);
	
	// 보스 체력
	_bossInfo.update();

	//레벨업!!	
	_levelInfo.update(_player->getPosition());

	if (!_vDoor.empty())
	{
		for (int i = 0; i < _vDoor.size(); i++)
		{			
			_vDoor[i].update(_player->getPosition());
		}
	}

	_heart.update(_player);

	_lock.update();	

	_shop.update(_player);

}

void UIManager::render()
{
	_lock.render();

	if (!_vDoor.empty())
	{
		for (int i = 0; i < _vDoor.size(); i++)
		{
			_vDoor[i].render();
		}
	}

	CAMERA_MANAGER->fillOutline();
	
	_bossInfo.render();

	_levelInfo.render();	

	_shop.render();	

	_playerInfo.render();

	_heart.render();
}

void UIManager::setLevelUp(bool active)
{
	_levelInfo.active = active;

	_levelInfo.pos = _player->getPosition();

	_levelInfo.playerAni->start();
}

void UIManager::setDoor(vector<tagDoorInfo> doors)
{
	_vDoor.clear();

	for (int i = 0; i < doors.size(); i++)
	{
		tagDoorInfo door;
		door.init(doors[i].doorState, doors[i].pos);

		_vDoor.push_back(door);
	}
}

void UIManager::setLock(LOCK_STATE state)
{	
	_lock.init(state);
}
