#pragma once

#include "canvas.hpp"
#include "sphere.hpp"
#include "vector.hpp"

#include <vector>
#include <tuple>

class Scene {
public:
    /* Camera exists only inside of a scene */
    class Camera {
    private:
        Vector3 position_ = Vector3(0.0, 0.0, -1.0);

    public:
        Camera(long double x, long double y,
               long double z);
        Camera(const Vector3 &vec);
        ~Camera();

        const Vector3 &position() const;
        void position(const Vector3 &newpos);
    };
    
    /* Light Sources exists only inside of a scene */
    class LightSource {
    private:
        Sphere body_ = Sphere(0.0, 0.0, 0.0, 0.0);
        long double intensity_ = 1.0;

    public:
        LightSource(long double x, long double y, 
                    long double z, long double r,
                    const Color &color = Color(255, 255, 255, 255), long double intensity = 1.0);
        LightSource(const Sphere &sphere, long double intensity = 1.0);
        ~LightSource();

        /* Getters */
        const Sphere &body()    const;
        long double intensity() const;

        /* Setters */
        void intensity(long double);
    };

private:
    /* Parent canvas, may be NULL */
    const Canvas *canvas_ = nullptr;
    Camera camera_ = Camera(0.0, 0.0, 0.0);

    std::vector<LightSource> lightSourcesList_ = std::vector<LightSource> (0, LightSource(0.0, 0.0, 0.0, 1.0));
    std::vector<Object *>    objectsList_      = std::vector<Object *>    (0);

    Color traceRay(const Vector3 &origin, const Vector3 &direction, int depth = 1) const;
    std::tuple<bool, Vector3, Vector3, Material> intersect(const Vector3 &origin, const Vector3 &direction) const;

public:
    Scene(const Canvas *canvas, const LightSource &lightSource = LightSource(0.0, 0.0, 0.0, 1.0), 
          const Camera &viewpoint = Camera(0.0, 0.0, 0.0));
    Scene(const Scene &scene) = delete;
    Scene operator=(const Scene &scene) = delete;
    ~Scene();

    void processEvent(const Event &event);
    void render();
    void addObject(Object *obj);
    void addLightSource(const LightSource &lightSource);

    /* Getters */
    const std::vector<Object *>    &objectsList()      const;
    const std::vector<LightSource> &lightSourcesList() const;
    const Camera                   &camera()           const;
    const Canvas                   *canvas()           const;
};
