#pragma once
#include "Stage.h"
class MiddleStage : public Stage
{
private:
	float _respawnCool;
	bool _isQuestClear;
	bool _isQuesting;
	int _maxRestCount;
	int _lastEnemyNum;
	int _deadNum;
	int _restCount;
	Vector2 _respawnPos[2];

public:
	virtual void init(Image* background, float bgScale);
	virtual void release();
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();

	virtual void gameOver();
};

