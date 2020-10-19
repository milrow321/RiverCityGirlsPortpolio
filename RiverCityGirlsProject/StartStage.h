#pragma once
#include "Stage.h"

class StartStage : public Stage
{
private:
	Vector2 _respawnPos[4];
	float _respawnCool;

public:
	virtual void init(Image* background, float bgScale);
	virtual void release();
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();

	virtual void gameOver();
};

