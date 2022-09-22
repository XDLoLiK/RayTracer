#include "vector.hpp"

Vector3::Vector3(long double x, long double y, long double z):
	x_(x),
	y_(y),
	z_(z),
	length_(sqrtl(powl(x, 2) + powl(y, 2) + powl(z, 2)))
{

}

Vector3::Vector3(long double x0, long double y0, long double z0,
	           long double x1, long double y1, long double z1):
	x_(x1 - x0),
	y_(y1 - y0),
	z_(z1 - z0)
{

}

Vector3::~Vector3()
{
	x_ = y_ = z_ = length_ = 0.0;
}

Vector3 &Vector3::operator*=(long double scale)
{
	x_ *= scale;
	y_ *= scale;
	z_ *= scale;
	return *this;
}

Vector3 operator*(const Vector3 &vec, long double num)
{
	Vector3 newVec = vec;
	newVec *= num;
	return newVec;
}

Vector3 operator*(long double num, const Vector3 &vec)
{
	return vec * num;
}

long double operator*(const Vector3 &vec1, const Vector3 &vec2)
{
	return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

Vector3 &Vector3::operator+=(const Vector3 &vec)
{
	x_ += vec.x();
	y_ += vec.y();
	z_ += vec.z();
	return *this;
}

Vector3 operator+(const Vector3 &vec1, const Vector3 &vec2)
{
	Vector3 newVec = vec1;
	newVec += vec2;
	return newVec;
}

Vector3 &Vector3::operator-=(const Vector3 &vec)
{
	x_ -= vec.x();
	y_ -= vec.y();
	z_ -= vec.z();
	return *this;	
}

Vector3 operator-(const Vector3 &vec1, const Vector3 &vec2)
{
	Vector3 newVec = vec1;
	newVec -= vec2;
	return newVec;	
}

Vector3 operator-(const Vector3 &vec)
{
	return -1 * vec;
}

Vector3 normalized(const Vector3 &vec)
{
	return Vector3(vec.x() / vec.length(),
		           vec.y() / vec.length(),
		           vec.z() / vec.length());
}

long double Vector3::x() const
{
	return x_;
}

long double Vector3::y() const
{
	return y_;
}

long double Vector3::z() const
{
	return z_;
}

long double Vector3::length() const
{
	return length_;
}

void Vector3::normalize()
{
	x_ /= length_;
	y_ /= length_;
	z_ /= length_;
	length_ = 1;
}

long double cos(const Vector3 &vec1, const Vector3 &vec2)
{
	long double numerator   = vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
	long double denominator = vec1.length() * vec2.length();
	return compare(denominator, 0.0) ? INFINITY : numerator / denominator;
}

Vector3 reflect(const Vector3 &vec, const Vector3 &norm)
{
	return normalized(vec) + normalized(norm) * 2.0 * cos(vec, norm);
}

Vector3 refract(const Vector3 &vec, const Vector3 &norm, long double n1, long double n2)
{
	if (cos(norm, vec) < 0)
		return refract(vec, -norm, n1, n2);

	long double cosAlpha = cos(norm, vec);
	long double cosBeta  = cosAlpha * n1 / n2;

	if (cosAlpha < cosBeta) {
		long double temp = cosAlpha;
		cosAlpha = cosBeta;
		cosBeta  = temp;
	}

	long double sinAlpha = sqrtl(1 - cosAlpha * cosAlpha);
	long double sinBeta  = sqrtl(1 - cosBeta  * cosBeta);
	long double coeff    = sinBeta / (sinAlpha * cosBeta - cosAlpha * sinBeta);

	return normalized(vec) * coeff + normalized(norm);
}
