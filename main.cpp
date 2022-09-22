#include "scene.hpp"

/*
 * TODO:
 * -Custom background for scene
 * -Custom frame position for scene
 * -Objects, frame and camera rotation
 */

int main()
{
	Canvas canvas(600, 600);
	Scene  scene(&canvas, 
		         Scene::LightSource(1.0, 1.0, -1.0, 1.0), 
		         Scene::Camera(0.0, 0.0, 1.0));

	Sphere sphere(0.0, 0.0, -1.0, 0.5);
	scene.addObject(&sphere);

	Sphere testSphere(-0.5, 0.0, -2.0, 0.5, blue);
	scene.addObject(&testSphere);

	while (canvas.isOpen()) {
		canvas.clearRender();
		Event event{};
		event.poll();
		canvas.processEvent(event);
		scene.processEvent(event);
		scene.render();
		canvas.presentRender();
	}

	return 0;
}
