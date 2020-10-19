#pragma once
#include "LinearFunc.h"
#include "GameObject.h"

enum class RECT_TYPE : int
{
	LEFT,
	MIDDLE, // Á÷»ç°¢Çü
	RIGHT
};

class RestrictMoveRect
{
private:
	Vector2 _point[4]; // LT, RT, RB, LB
	LinearFunc _lines[4]; // L T R B
	float _height;
	RECT_TYPE _type;

public:
	RestrictMoveRect(Vector2 LT, Vector2 RT, Vector2 RB, Vector2 LB, float height)
	{
		_point[0] = LT;
		_point[1] = RT;
		_point[2] = RB;
		_point[3] = LB;

		_lines[0] = LinearFunc::getLinearFuncFromPoints(LB, LT); // LEFT
		_lines[1] = LinearFunc::getLinearFuncFromPoints(LT, RT); // TOP
		_lines[2] = LinearFunc::getLinearFuncFromPoints(RB, RT); // RIGHT
		_lines[3] = LinearFunc::getLinearFuncFromPoints(LB, RB); // BOTTOM

		if (_lines[0].a == LinearFunc::INF_A)
		{
			_type = RECT_TYPE::MIDDLE;
		}
		else if (_lines[0].a < 0)
		{
			_type = RECT_TYPE::RIGHT;
		}
		else
		{
			_type = RECT_TYPE::LEFT;
		}

		_height = -height;
	}

	RestrictMoveRect(Vector3 position, Vector3 size)
	{
		int linePos[2][4] = { {position.x - (size.x / 2) + (size.z / 2) , position.z - (size.z / 2), position.x + (size.x / 2) + (size.z / 2), position.z - (size.z / 2)}, // À­ ÁÙ 
						{position.x - (size.x / 2) - (size.z / 2), position.z + (size.z / 2), position.x + (size.x / 2) - (size.z / 2), position.z + (size.z / 2)}, }; // ¾Æ·§ ÁÙ

		RestrictMoveRect(Vector2(linePos[0][0], linePos[0][1]),		// LT
			Vector2(linePos[0][2], linePos[0][3]),		// RT
			Vector2(linePos[1][2], linePos[1][3]),		// RB
			Vector2(linePos[1][0], linePos[1][1]),
			-size.y);		// LB
	}

	~RestrictMoveRect()
	{
	}

	void checkCollision(Vector3* poses, GameObject* gameObject);

	// FOR DEBUG
	void render();
};

