#pragma once

#include "color.hpp"

class Material {
private:
	Color color_ = red;
	long double refractiveIndex_  = 0.0;
	long double specularExponent_ = 0.0;

	long double  diffuseCoeff_ = 0.0;
	long double specularCoeff_ = 0.0;
	long double  reflectCoeff_ = 0.0;
	long double  refractCoeff_ = 0.0;	

public:
	Material(const Color &color = red,
		     long double refractiveIndex = 1.0, long double specularExponent = 1.0,
             long double diffuseCoeff    = 1.0, long double specularCoeff    = 1.0,
             long double reflectCoeff    = 1.0, long double refractCoeff     = 1.0);
	~Material();

	const Color &color           () const;
	long double refractiveIndex  () const;
	long double specularExponent () const;
	long double diffuseCoeff     () const;
	long double specularCoeff    () const;
	long double reflectCoeff     () const;
	long double refractCoeff     () const;
};

const Material   redRubber = Material(red,   1.0, 10.0, 1.4, 0.3, 0.0, 0.0);
const Material greenRubber = Material(green, 1.0, 10.0, 1.4, 0.3, 0.0, 0.0);
const Material  blueRubber = Material(blue,  1.0, 10.0, 1.4, 0.3, 0.0, 0.0);
