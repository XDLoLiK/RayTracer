#include "scene.hpp"
#include "sphere.hpp"
#include "plane.hpp"

/*
 * TODO:
 * -Custom background for scene
 * -Custom frame position for scene
 * -Objects, frame and camera rotation
 */

int main()
{
	Canvas canvas(600, 600);
	Scene  scene(&canvas, Scene::Camera(0.0, 0.0, 1.0));

	scene.addLightSource(Scene::LightSource(-20.0, 20.0,  20.0));
	scene.addLightSource(Scene::LightSource( 30.0, 50.0, -25.0));
	scene.addLightSource(Scene::LightSource( 30.0, 20.0,  30.0));
	scene.addLightSource(Scene::LightSource(-2.0,  2.0,  -8.0));

	Sphere sphere1(-3.0, -1.5, -8.0, 1.0, ivory(Color(0.4, 0.4, 0.3, 1.0)));
	scene.addObject(&sphere1);

	Sphere sphere2(-1.0, -1.5, -6.0, 1.0, glass(Color(0.6, 0.7, 0.8, 1.0)));
	scene.addObject(&sphere2);

	Sphere sphere3(1.5, -1.5, -9.0, 2.0, rubber(red));
	scene.addObject(&sphere3);

	Sphere sphere4(0.0, 5.0, -12.0, 3.0, mirror(white));
	scene.addObject(&sphere4);

	Sphere sphere5(-2.0, 2.0, -5.0, 1.0, rubber(green));
	scene.addObject(&sphere5);

	Sphere sphere6(3.0, -1.5, -6.0, 1.0, mirror(white));
	scene.addObject(&sphere6);

	while (canvas.isOpen()) {
		canvas.clearRender();
		Event event{};
		event.poll();
		canvas.processEvent(event);
		scene.render();
		canvas.presentRender();
	}

	return 0;
}
