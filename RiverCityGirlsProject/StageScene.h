#pragma once
#include "GameNode.h"
#include "StageManager.h"'
#include "UIManager.h"
#include "DialogueManager.h"
#include "Player.h"

class StageScene : public GameNode
{
private:
	StageManager* _stageManager;
	UIManager* _uiManager;
	Player* _player;
	DialogueManager* _dgManager;

public:
	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 전용
	virtual void update();			//연산 전용
	virtual void render();			//그리기 전용
};

