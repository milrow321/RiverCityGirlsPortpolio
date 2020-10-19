#pragma once
#include "LinearFunc.h"


class RestrictMoveLine
{
private:
	LinearFunc _line; // 선분
	LINEAR_VALUE_TYPE _type; // 이 선분 어디를 못지나가게 할 것인가?
	float _startX; // 감지를 할 X의 시작 좌표
	float _endX; // 감지를 할 X의 마지막 좌표 range : [_startX, _endX]

public:
	RestrictMoveLine(LinearFunc line, LINEAR_VALUE_TYPE type, float startX, float endX)
		: _line(line), _type(type), _startX(startX), _endX(endX)
	{
	}

	void checkCollision(Vector3* poses, Vector3 size);

	// FOR DEBUG
	void render(); 
};

