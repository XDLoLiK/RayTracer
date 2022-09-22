#pragma once

#include "color.hpp"

class Material {
private:
	Color color_ = red;

public:
	Material(const Color &color = red);
	~Material();

	Color color();
};

