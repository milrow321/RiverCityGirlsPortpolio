#pragma once

class Vector3 final
{
public:
	float x;
	float y;
	float z;

public:
	explicit Vector3();
	explicit Vector3(const float& x, const float& y, const float& z);
	explicit Vector3(const int& x, const int& y, const int& z);

	const int getIntX();
	const int getIntY();
	const int getIntZ();

	Vector3 operator+ (const Vector3& v);
	Vector3 operator- (const Vector3& v);
	void operator+= (const Vector3& v);
	void operator-= (const Vector3& v);
	void operator= (const Vector2& v2);
	Vector3 operator* (const float& scalar);
	Vector3 operator/ (const float& scalar);
	const bool operator==(const Vector3& v);
	const bool operator!=(const Vector3& v);
public:
	static Vector3 normalize(const Vector3* const  pVector2);
	static float toRadian(const Vector3* const pVector2);
	static float length(const Vector3* const pVector2);
	static float distance(Vector3 a, Vector3 b);
	static float dot(const Vector3* const pVector2A, const Vector3* const pVector2B);
	static float cross(const Vector3* const pvector2A, const Vector3* const pVector2B);
};


