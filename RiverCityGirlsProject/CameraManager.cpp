#include "stdafx.h"
#include "CameraManager.h"
#include "CameraShakeEvent.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::merge(int s, int e) // merge sort
{
	if (s == e) return;
	int mid = (s + e) / 2;
	merge(s, mid);
	merge(mid + 1, e);

	sort(s, e);
}

void CameraManager::sort(int s, int e) // z 를 기준으로 오름차순,(먼저 그려야 되는게 앞으로)
{
	int mid = (s + e) / 2;
	int sIndex = s;
	int eIndex = mid + 1;
	vector<tagZImage> tempVector;

	while (sIndex <= mid && eIndex <= e)
	{
		if ((_renderList[sIndex].pos.z + (_renderList[sIndex].size.z / 2) + _renderList[sIndex].offsetZ) < (_renderList[eIndex].pos.z + (_renderList[eIndex].size.z / 2) + _renderList[eIndex].offsetZ))
		{
			tempVector.push_back(_renderList[sIndex]);
			sIndex++;
		}
		else if ((_renderList[sIndex].pos.z + (_renderList[sIndex].size.z / 2) + _renderList[sIndex].offsetZ) == (_renderList[eIndex].pos.z + (_renderList[eIndex].size.z / 2) + _renderList[eIndex].offsetZ))
		{
			if (_renderList[sIndex].renderType == IMAGE_RENDER_TYPE::SHADOW)
			{
				tempVector.push_back(_renderList[sIndex]);
				sIndex++;
			}
			else
			{
				tempVector.push_back(_renderList[eIndex]);
				eIndex++;
			}
		}
		else
		{
			tempVector.push_back(_renderList[eIndex]);
			eIndex++;
		}
	}
	while (sIndex <= mid)
	{
		tempVector.push_back(_renderList[sIndex]);
		sIndex++;
	}
	while (eIndex <= e)
	{
		tempVector.push_back(_renderList[eIndex]);
		eIndex++;
	}

	for (int i = 0; i <= (e - s); i++) // 정렬
	{
		_renderList[s + i] = tempVector[i];
	}
}

void CameraManager::render(tagZImage imageInfo)
{
	if (imageInfo.renderType == IMAGE_RENDER_TYPE::SHADOW)
	{
		drawShadow(imageInfo.pos, imageInfo.size);
	}
	else
	{
		imageInfo.img->setScale(imageInfo.scale);
		imageInfo.img->setAngle(imageInfo.angle);
		imageInfo.img->setAlpha(imageInfo.alpha);
		// 타입에 맞게 이미지 그리기
		switch (imageInfo.renderType)
		{
		case IMAGE_RENDER_TYPE::RENDER:
		{
			render(imageInfo.img, convertV3ToV2(imageInfo.pos));
		}
		break;
		case IMAGE_RENDER_TYPE::RENDER_WITH_SOURCE_POS:
		{
			render(imageInfo.img, convertV3ToV2(imageInfo.pos), imageInfo.sourPos, imageInfo.sourSize);
		}
		break;
		case IMAGE_RENDER_TYPE::FRAME_RENDER:
		{
			frameRender(imageInfo.img, convertV3ToV2(imageInfo.pos), imageInfo.frameX, imageInfo.frameY);
		}
		break;
		case IMAGE_RENDER_TYPE::ANIMATION_RENDER:
		{
			aniRender(imageInfo.img, convertV3ToV2(imageInfo.pos), imageInfo.ani);
		}
		break;
		}
	}
}

Vector2 CameraManager::convertV3ToV2(Vector3 v3)
{
	return Vector2(v3.x, (v3.y + v3.z));
}

HRESULT CameraManager::init()
{
	return S_OK;
}

void CameraManager::release()
{
}

void CameraManager::processEvent()
{
	if (_eventQueue.empty()) return;

	_eventQueue.front()->processEvent();
	if (_eventQueue.front()->getRemainTime() <= 0)
	{
		delete _eventQueue.front();
		_eventQueue.pop();
	}
}

void CameraManager::pushShakeEvent(float power, float shakePerTime, float remainTime)
{
	CameraShakeEvent* event = new CameraShakeEvent(power, shakePerTime, remainTime);
	_eventQueue.push(event);
}

void CameraManager::setConfig(float offsetL, float offsetT, float width, float height, float minL, float minT, float maxL, float maxT)
{
	_offsetL = offsetL;
	_offsetT = offsetT;
	_L = minL;
	_T = minT;
	_width = width;
	_height = height;
	_originMinL = _minL = minL;
	_originMinT = _minT = minT;
	_originMaxL = _maxL = maxL;
	_originMaxT = _maxT = maxT;

	_x = _L + (_width / 2);
	_y = _T + (_height / 2);
	_originMinX = _minX = _minL + (_width / 2);
	_originMinY = _minY = _minT + (_height / 2);
	_originMaxX = _maxX = _maxL + (_width / 2);
	_originMaxY = _maxY = _maxT + (_height / 2);
}

void CameraManager::setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_originMinX = _minX = minX;
	_originMinY = _minY = minY;
	_originMaxX = _maxX = maxX;
	_originMaxY = _maxY = maxY;

	_L = _x - (width / 2);
	_T = _y - (height / 2);
	_originMinL = _minL = _minX - (width / 2);
	_originMinT = _minT = _minY - (height / 2);
	_originMaxL = _maxL = _maxX - (width / 2);
	_originMaxT = _maxT = _minY - (height / 2);
}

float CameraManager::getL()
{
	return _L;
}

float CameraManager::getT()
{
	return _T;
}

Vector2 CameraManager::getLT()
{
	return Vector2(_L, _T);
}

float CameraManager::getX()
{
	return _x;
}

float CameraManager::getY()
{
	return _y;
}

Vector2 CameraManager::getXY()
{
	return Vector2(_x, _y);
}

void CameraManager::setL(float newL)
{
	newL = min(_maxL, newL);
	newL = max(_minL, newL);
	_L = floor(newL);
	_x = _L + (_width / 2);
}

void CameraManager::setT(float newT)
{
	newT = min(_maxT, newT);
	newT = max(_minT, newT);
	_T = floor(newT);
	_y = _T + (_height / 2);
}

void CameraManager::setLT(Vector2 newLT)
{
	setL(newLT.x);
	setT(newLT.y);
}

void CameraManager::setX(float newX)
{
	newX = min(_maxX, newX);
	newX = max(_minX, newX);
	_x = floor(newX);
	_L = _x - (_width / 2);
}

void CameraManager::setY(float newY)
{
	newY = min(_maxY, newY);
	newY = max(_minY, newY);
	_y = floor(newY);
	_T = _y - (_height / 2);
}

void CameraManager::setXY(Vector2 newXY)
{
	setX(newXY.x);
	setY(newXY.y);
}

void CameraManager::movePivot(float offsetX, float offsetY)
{
	setL(_L + offsetX);
	setT(_T + offsetY);
}

void CameraManager::movePivot(Vector2 offsetXY)
{
	setL(_L + offsetXY.x);
	setT(_T + offsetXY.y);
}

float CameraManager::getRelativeX(float left)
{
	float newL = _offsetL + left - _L;
	return newL;
}

LONG CameraManager::getRelativeX(LONG left)
{
	LONG newL = _offsetL + left - _L;
	return newL;
}

float CameraManager::getRelativeY(float top)
{
	float newT = _offsetT + top - _T;
	return  newT;
}

LONG CameraManager::getRelativeY(LONG top)
{
	LONG newT = _offsetT + top - _T;
	return  newT;
}

Vector2 CameraManager::getRelativeV2(Vector2 vec2)
{
	return Vector2(getRelativeX(vec2.x), getRelativeY(vec2.y));
}

FloatRect CameraManager::getRelativeFR(FloatRect rc)
{
	float left = getRelativeX(rc.left);
	float top = getRelativeY(rc.top);
	float right = getRelativeX(rc.right);
	float bottom = getRelativeY(rc.bottom);

	return FloatRect(left, top,
		right, bottom);
}

float CameraManager::getAbsoluteX(float left)
{
	float newL = -_offsetL + _L + left;
	return newL;
}

LONG CameraManager::getAbsoluteX(LONG left)
{
	LONG newL = -_offsetL + _L + left;
	return newL;
}

float CameraManager::getAbsoluteY(float top)
{
	float newT = -_offsetT + _T + top;
	return newT;
}

LONG CameraManager::getAbsoluteY(LONG top)
{
	LONG newT = -_offsetT + _T + top;
	return newT;
}

Vector2 CameraManager::getAbsoluteV2(Vector2 vec2)
{
	return Vector2(getAbsoluteX(vec2.x), getAbsoluteY(vec2.y));
}

FloatRect CameraManager::getAbsoluteFR(FloatRect rc)
{
	return FloatRect(getAbsoluteX(rc.left), getAbsoluteY(rc.top),
		getAbsoluteX(rc.right), getAbsoluteY(rc.bottom));
}

void CameraManager::drawLine(Vector2 start, Vector2 end)
{
	D2D_RENDERER->drawLine(getRelativeV2(start), getRelativeV2(end));
}

void CameraManager::rectangle(FloatRect rect, D2D1::ColorF::Enum color, float alpha, float strokeWidth)
{
	FloatRect relativeRc = getRelativeFR(rect);
	D2D_RENDERER->drawRectangle(relativeRc, color, alpha, strokeWidth);
}

void CameraManager::drawShadow(Vector3 pos, Vector3 size)
{
	Vector2 drawPos = getRelativeV2(Vector2(pos.x, pos.z + pos.y + (size.y / 2)));
	Vector2 drawSize = Vector2(size.x / 2, size.z / 2);
	// D2D_RENDERER->drawEllipse(drawPos, drawSize, D2D1::ColorF::Enum::Black, 0.2);
	D2D_RENDERER->fillEllipse(drawPos, drawSize, D2D1::ColorF::Enum::Black, 0.3);
}

void CameraManager::render(Image * img, Vector2 center)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos);
}

void CameraManager::render(Image * img, Vector2 center, Vector2 sourLT, Vector2 sourSize)
{
	Vector2 drawPos = getRelativeV2(center);
	img->render(drawPos, sourLT, sourSize);
}


void CameraManager::aniRender(Image * img, Vector3 center, Animation * ani)
{
	aniRender(img, convertV3ToV2(center), ani);
}

void CameraManager::frameRender(Image * img, Vector2 center, int frameX, int frameY)
{
	Vector2 drawPos = getRelativeV2(center);
	img->frameRender(drawPos, frameX, frameY);
}

void CameraManager::aniRender(Image * img, Vector2 center, Animation * ani)
{
	Vector2 drawPos = getRelativeV2(center);
	img->aniRender(drawPos, ani);
}

void CameraManager::drawShadowZ(Vector3 pos, Vector3 size, float offsetZ)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::SHADOW;
	zImage.offsetZ = offsetZ;
	zImage.pos = pos;
	zImage.size = size;

	_renderList.push_back(zImage);
}

void CameraManager::renderZ(Image * img, Vector3 center, Vector3 size, float offsetZ)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::RENDER;
	zImage.img = img;
	zImage.scale = img->getScale();
	zImage.alpha = img->getAlpha();
	zImage.angle = img->getAngle();
	zImage.offsetZ = offsetZ;
	zImage.pos = center;
	zImage.size = size;

	_renderList.push_back(zImage);
}

void CameraManager::renderZ(Image * img, Vector3 center, Vector3 size, Vector2 sourLT, Vector2 sourSize, float offsetZ)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::RENDER_WITH_SOURCE_POS;
	zImage.img = img;
	zImage.scale = img->getScale();
	zImage.alpha = img->getAlpha();
	zImage.angle = img->getAngle(); 
	zImage.offsetZ = offsetZ;
	zImage.pos = center;
	zImage.size = size;
	zImage.sourPos = sourLT;
	zImage.sourSize = sourSize;
	
	_renderList.push_back(zImage);
}

void CameraManager::frameRenderZ(Image * img, Vector3 center, Vector3 size, int frameX, int frameY, float offsetZ)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::FRAME_RENDER;
	zImage.img = img;
	zImage.scale = img->getScale();
	zImage.alpha = img->getAlpha();
	zImage.angle = img->getAngle(); 
	zImage.offsetZ = offsetZ;
	zImage.pos = center;
	zImage.size = size;
	zImage.frameX = frameX;
	zImage.frameY = frameY;

	_renderList.push_back(zImage);
}

void CameraManager::aniRenderZ(Image * img, Vector3 center, Vector3 size, Animation * ani, float offsetZ)
{
	tagZImage zImage;
	zImage.renderType = IMAGE_RENDER_TYPE::ANIMATION_RENDER;
	zImage.img = img;
	zImage.scale = img->getScale();
	zImage.alpha = img->getAlpha();
	zImage.angle = img->getAngle(); 
	zImage.offsetZ = offsetZ;
	zImage.pos = center;
	zImage.size = size;
	zImage.ani = ani;

	_renderList.push_back(zImage);
}

void CameraManager::renderZList()
{
	if (_renderList.size() == 0) return;
	merge(0, _renderList.size() - 1);

	for (int i = 0; i < _renderList.size(); i++)
	{
		render(_renderList[i]);
	}

	_renderList.clear();

	
}

void CameraManager::fillOutline()
{
	D2D_RENDERER->fillRectangle(FloatRect(0.0, 0.0, (float)WINSIZEX, _offsetT), D2D1::ColorF::Enum::Black, 1);
	D2D_RENDERER->fillRectangle(FloatRect(0.0, _offsetT + _height, (float)WINSIZEX, (float)WINSIZEY), D2D1::ColorF::Enum::Black, 1);
}
