#include "stdafx.h"
#include "Effect.h"

Effect::Effect()
	: _effectImage(nullptr),
	_effectAnimation(nullptr),
	_isRunning(false)
{
	_position = Vector2(0, 0);
	_size = Vector2(0, 0);
}

Effect::~Effect()
{
}

void Effect::init(Image * effectImage, int fps)
{
	if (!effectImage) return;

	_effectImage = effectImage;
	_isRunning = false;

	//����Ʈ �ִϸ��̼��� ������ �����ض�
	if (!_effectAnimation) _effectAnimation = new Animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(),
		_effectImage->getMaxFrameX(), _effectImage->getMaxFrameY());
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();
}

void Effect::release()
{
	_effectImage = nullptr;
	SAFE_DELETE(_effectAnimation);
}

void Effect::update()
{
	//����Ʈ �ִϸ��̼� ���� ������ false�� �������� ����
	if (!_isRunning) return;

	_effectAnimation->frameUpdate(TIME_MANAGER->getElapsedTime());

	if (!_effectAnimation->isPlay()) killEffect();
}

void Effect::render()
{
	if (!_isRunning) return;

	_effectImage->setScale(_scale);
	CAMERA_MANAGER->aniRenderZ(_effectImage, _position, Vector3(10, 10, 30), _effectAnimation);
}

//void Effect::startEffect(int x, int y)
//{
//	if (!_effectImage || !_effectAnimation) return;
//
//	_position = Vector2(x - (_effectAnimation->getFrameWidth() / 2), 
//		y - (_effectAnimation->getFrameHeight() / 2));
//	_size = Vector2(_effectAnimation->getFrameWidth(), 
//		_effectAnimation->getFrameHeight());
//
//	_isRunning = true;
//
//	_effectAnimation->start();
//}
//
//void Effect::startEffect(int x, int y, int width, int height)
//{
//	//����Ʈ �̹��� �Ǵ� ����Ʈ �ִϸ��̼��� ������ ������������
//	if (!_effectImage || !_effectAnimation) return;
//
//	_position = Vector2(x - (_effectAnimation->getFrameWidth() / 2),
//		y - (_effectAnimation->getFrameHeight() / 2));
//	_size = Vector2(width,
//		height);
//
//	_isRunning = true;
//
//	_effectAnimation->start();
//}

void Effect::startEffectZ(Vector3 pos, float scale)
{
	if (!_effectImage || !_effectAnimation) return;

	_position = pos;
	_scale = scale;
	_isRunning = true;
	_effectAnimation->start();
}

void Effect::killEffect()
{
	_isRunning = false;
}