#include "material.hpp"

Material::Material(const Color &color):
	color_(color)
{

}

Material::~Material()
{

}

Color Material::color()
{
	return color_;
}
