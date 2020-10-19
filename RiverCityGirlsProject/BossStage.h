#pragma once
#include "Stage.h"
class BossStage : public Stage
{
private:
	
public:
	virtual void init(Image* background, float bgScale);
	virtual void release();
	virtual void enter();
	virtual void exit();
	virtual Stage* update();
	virtual void render();

	virtual void gameOver();
};

