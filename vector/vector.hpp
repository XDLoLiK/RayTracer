#pragma once

#include "maths.hpp"

#include <cmath>

class Vector3 {
private:
	long double x_ = 0.0;
	long double y_ = 0.0;
	long double z_ = 0.0;

	long double length_ = 0.0;

public:
	Vector3(long double x,  long double y,  long double z);
	Vector3(long double x0, long double y0, long double z0,
		   long double x1, long double y1, long double z1);
	Vector3 &operator*=(long double scale);
	Vector3 &operator+=(const Vector3 &vec);
	Vector3 &operator-=(const Vector3 &vec);
	~Vector3();

	void normalize();

	/* Getters */
	long double x()      const;
	long double y()      const;
	long double z()      const;
	long double length() const;
};

Vector3 normalized(const Vector3 &vec);

Vector3 operator*(const Vector3 &vec, long double num);
Vector3 operator*(long double num, const Vector3 &vec);
long double operator*(const Vector3 &vec1, const Vector3 &vec2);
Vector3 operator+(const Vector3 &vec1, const Vector3 &vec2);
Vector3 operator-(const Vector3 &vec1, const Vector3 &vec2);
Vector3 operator-(const Vector3 &vec);

long double cos(const Vector3 &vec1, const Vector3 &vec2);
Vector3 reflect(const Vector3 &vec, const Vector3 &norm);
Vector3 refract(const Vector3 &vec, const Vector3 &norm, long double n1, long double n2);