#pragma once

#include <math.h>

class Vector2D
{

public:
	Vector2D(float x = 0, float y = 0);
	~Vector2D() {};

	void Rotate(const float angle);
	float Magnitude() const;
	float Normalize();
	float DotProduct(const Vector2D& v2) const;
	float CrossProduct(const Vector2D& v2) const;

	static Vector2D Reflect(Vector2D vec,Vector2D normal);
	static Vector2D Down();
	static Vector2D Up();
	static Vector2D Left();
	static Vector2D Right();
	static Vector2D Zero();
	static float Distance(const Vector2D& v1, const Vector2D& v2);

	Vector2D& operator= (const Vector2D& v2);

	Vector2D& operator+= (const Vector2D& v2);
	Vector2D& operator-= (const Vector2D& v2);
	Vector2D& operator*= (const float scalar);
	Vector2D& operator/= (const float scalar);

	const Vector2D operator+(const Vector2D &v2) const;
	const Vector2D operator-(const Vector2D &v2) const;
	const Vector2D operator*(const float scalar) const;
	const Vector2D operator/(const float scalar) const;

	bool operator== (const Vector2D& v2) const;
	bool operator!= (const Vector2D& v2) const;

public:
	float x, y;
};
