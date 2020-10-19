#include "stdafx.h"
#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(const float & x, const float & y, const float & z)
	: x(x), y(y), z(z)
{
}

Vector3::Vector3(const int & x, const int & y, const int & z)
	: x(static_cast<int> (x)), y(static_cast<int> (y)), z(static_cast<int> (z))
{
}

const int Vector3::getIntX()
{
	return static_cast<int>(x);
}

const int Vector3::getIntY()
{
	return static_cast<int>(y);
}

const int Vector3::getIntZ()
{
	return static_cast<int>(z);
}

Vector3 Vector3::operator+(const Vector3 & v)
{
	Vector3 result;
	result.x = x + v.x;
	result.y = y + v.y;
	result.z = z + v.z;
	return result;
}

Vector3 Vector3::operator-(const Vector3 & v)
{
	Vector3 result;
	result.x = x - v.x;
	result.y = y - v.y;
	result.z = z - v.z;
	return result;
}

void Vector3::operator+=(const Vector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3::operator-=(const Vector3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vector3::operator=(const Vector2 & v2)
{
	x = v2.x;
	y = v2.y;
	z = 0;
}

Vector3 Vector3::operator*(const float & scalar)
{
	Vector3 result;
	result.x = x * scalar;
	result.y = y * scalar;
	result.z = z * scalar;
	return result;
}

Vector3 Vector3::operator/(const float & scalar)
{
	Vector3 result;
	result.x = x / scalar;
	result.y = y / scalar;
	result.z = z / scalar;
	return result;
}

const bool Vector3::operator==(const Vector3 & v)
{
	if (x == v.x && y == v.y && z == v.z)
	{
		return true;
	}
	return false;
}

const bool Vector3::operator!=(const Vector3 & v)
{
	return !((*this) == v);
}

Vector3 Vector3::normalize(const Vector3 * const pVector3)
{
	Vector3 result = *pVector3;

	float length = Vector3::length(pVector3);
	result.x /= length;
	result.y /= length;
	result.z /= length;

	return result;
}

float Vector3::toRadian(const Vector3 * const pVector2)
{
	// TO DO
	return 0.0f;
}

float Vector3::length(const Vector3 * const pVector3)
{
	Vector3 vec = *pVector3;
	float length = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return length;
}

float Vector3::distance(Vector3 a, Vector3 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

float Vector3::dot(const Vector3 * const pVector2A, const Vector3 * const pVector2B)
{
	// TO DO
	return 0.0f;
}

float Vector3::cross(const Vector3 * const pvector2A, const Vector3 * const pVector2B)
{
	// TO DO
	return 0.0f;
}
