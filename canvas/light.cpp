#include "scene.hpp"

Scene::LightSource::LightSource(long double x, long double y,
	                            long double z, long double r,
                                const Color &color, long double intensity):
	body_(Sphere(x, y, z, r, Material(color))),
	intensity_((intensity > 1.0) ? 1.0 : intensity)
{

}

Scene::LightSource::LightSource(const Sphere &sphere, long double intensity):
	body_(sphere),
	intensity_((intensity > 1.0) ? 1.0 : intensity)

{

}

Scene::LightSource::~LightSource()
{
	intensity_ = 0.0;
}

const Sphere &Scene::LightSource::body() const
{
	return body_;
}

long double Scene::LightSource::intensity() const
{
	return intensity_;
}	

void Scene::LightSource::intensity(long double intensity)
{
	intensity_ = intensity;
}
