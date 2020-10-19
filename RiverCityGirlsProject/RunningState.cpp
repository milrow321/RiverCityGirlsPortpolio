#include "stdafx.h"
#include "KyokoState.h"






KyokoState * RunningState::update(Kyoko & Kyoko)
{
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{

		return new IdleState;
	}


	if (Kyoko.getDirection() == RIGHT)
	{
		Kyoko.setX(Kyoko.getX() + 15);
	}
	if (Kyoko.getDirection() == LEFT)
	{
		Kyoko.setX(Kyoko.getX() - 15);
	}

	return nullptr;
}

void RunningState::render(Kyoko & Kyoko)
{
}

void RunningState::ImageEnter(Kyoko & Kyoko)
{
	Kyoko.setImage(ImageManager::GetInstance()->FindImage("쿄코달리기"));
}
