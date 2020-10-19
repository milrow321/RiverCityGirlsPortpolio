#include "stdafx.h"
#include "RestrictMoveLine.h"

void RestrictMoveLine::checkCollision(Vector3 * poses, Vector3 size)
{
	float dir[4][2] = { {-1.0, -1.0}, {-1.0, 1.0}, {1.0, -1.0}, {1.0, 1.0} }; // 각 대각 값
	float width = size.x / 2;
	float height = size.z / 2;

	for (int i = 0; i < 4; i++) // 4 꼭지점에 대한 검사
	{
		Vector3 checkPos = poses[i];
		if (_line.a != LinearFunc::INF_A)
		{
			if (_startX > poses[i].x || _endX < poses[i].x) continue; // 검사하지 않아도 되는 좌표

			LINEAR_VALUE_TYPE posType = _line.getValueType(checkPos.x, checkPos.z);
			if (posType == _type) // 선을 넘어간 경우
			{
				if (_line.a == 0) // 기울기가 0이 아닌 경우
				{
					checkPos.z = _line.getY(checkPos.x); // z 좌표 변경은 x를 기준으로

				}
				else if (_line.a == LinearFunc::INF_A) // x = 100 꼴의 함수인 경우
				{
					checkPos.x = _line.b;
				}
				else
				{
					checkPos.x = _line.getX(checkPos.z); // x 좌표 변경은 z를 기준으로
				}

				// 바뀐 좌표를 기준으로 다시 그린다
				Vector3 newPos = Vector3(checkPos.x - dir[i][0] * width, checkPos.y, checkPos.z - dir[i][1] * height);
				for (int k = 0; k < 4; k++)
				{
					poses[k] = Vector3(newPos.x + dir[k][0] * width, checkPos.y, newPos.z + dir[k][1] * height);
				}
			}
		}
		else
		{
			if (_startX > poses[i].z || _endX < poses[i].z) continue; // 검사하지 않아도 되는 좌표

			LINEAR_VALUE_TYPE posType = _line.getValueType(checkPos.x, checkPos.z);
			if (posType == _type) // 선을 넘어간 경우
			{
				checkPos.x = _line.b;

				// 바뀐 좌표를 기준으로 다시 그린다
				Vector3 newPos = Vector3(checkPos.x - dir[i][0] * width, checkPos.y, checkPos.z - dir[i][1] * height);
				for (int k = 0; k < 4; k++)
				{
					poses[k] = Vector3(newPos.x + dir[k][0] * width, checkPos.y, newPos.z + dir[k][1] * height);
				}
			}
		}
	}
}

void RestrictMoveLine::render()
{
	Vector2 startPoint;
	Vector2 endPoint;
	if (_line.a != LinearFunc::INF_A)
	{
		startPoint = Vector2(_startX, _line.getY(_startX));
		endPoint = Vector2(_endX, _line.getY(_endX));
	}
	else
	{
		startPoint = Vector2(_line.b, _startX);
		endPoint = Vector2(_line.b, _endX);
	}
	
	CAMERA_MANAGER->drawLine(startPoint, endPoint);
}
