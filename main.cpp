#include "scene.hpp"

/*
 * TODO:
 * -Custom background for scene
 * -Custom frame position for scene
 * -Objects, frame and camera rotation
 * -Fix specular lighting
 * -Refactor class Color
 * -Add refraction (best way to implement - ???)
 */

int main()
{
	Canvas canvas(600, 600);
	Scene  scene(&canvas, 
		         Scene::LightSource(0.5, 0.5, -0.25),
		         Scene::Camera(0.0, 0.0, 1.0));
	scene.addLightSource(Scene::LightSource(-0.5, -0.5, -0.5));

	Sphere sphere1(0.0, 0.0, -1.0, 0.5, redRubber);
	scene.addObject(&sphere1);

	Sphere sphere2(-1.0, 0.0, -1.5, 0.4, greenRubber);
	scene.addObject(&sphere2);

	Sphere sphere3(0.85, -0.25, -0.5, 0.4, blueRubber);
	scene.addObject(&sphere3);

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
