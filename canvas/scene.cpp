#include "scene.hpp"

Scene::Scene(const Canvas *canvas, const LightSource &lightSource, 
             const Camera &camera):
    canvas_(canvas),
    camera_(camera)
{
    this->addLightSource(lightSource);
}

Scene::~Scene()
{
    lightSourcesList_.clear();
    objectsList_.clear();
}

void Scene::processEvent(const Event &event)
{
    switch (event.type()) {
        case SDL_KEYDOWN:
            switch (event.key().keysym.sym) {
                case SDLK_LEFT:
                    camera_.position(camera_.position() - Vector3(0.01, 0.0, 0.0));
                    break;

                case SDLK_RIGHT:
                    camera_.position(camera_.position() + Vector3(0.01, 0.0, 0.0));
                    break;

                case SDLK_DOWN:
                    camera_.position(camera_.position() - Vector3(0.0, 0.01, 0.0));
                    break;

                case SDLK_UP:
                    camera_.position(camera_.position() + Vector3(0.0, 0.01, 0.0));
                    break;

                default:
                    break;
            }

        default:
            break;
    }
}

void Scene::render()
{
    const Canvas *canvas   = canvas_;
    SDL_Renderer *renderer = canvas->renderer();
    SDL_Window   *window   = canvas->window();

    int width  = 0;
    int height = 0;
    SDL_GetWindowSize(window, &width, &height);

    for (int pixel = 0; pixel < height * width; pixel++) {
        int w = pixel % width;
        int h = pixel / width;

        long double curX = canvas->xToCU(w);
        long double curY = canvas->yToCU(h);
        long double curZ = 0.0; /* frame pos is 0.0 on z axis */

        Vector3 origin    = camera_.position();
        Vector3 point     = Vector3(curX, curY, curZ);
        Vector3 direction = normalized(point - origin);

        Color color = traceRay(origin, direction);
        SDL_SetRenderDrawColor(renderer, color.red(),  color.green(), color.blue(), color.alpha());
        SDL_RenderDrawPoint(renderer, w, h);
    }
}

Color Scene::traceRay(const Vector3 &origin, const Vector3 &direction, int depth) const
{
    auto [intersects, point, normal, material] = intersect(origin, direction);
    if (depth > 5 || !intersects)
        return grey; /* background color */

    Vector3 reflectedDir = normalized(reflect(direction, normal));
    Vector3 refractedDir = normalized(refract(direction, normal, 1.0, 0.5));

    Color reflectedColor = traceRay(point, reflectedDir, depth + 1);
    Color refractedColor = traceRay(point, refractedDir, depth + 1);

    return material.color();
}

std::tuple<bool, Vector3, Vector3, Material> Scene::intersect(const Vector3 &origin, const Vector3 &direction) const
{
    long double minDistance = INFINITY;
    Object *closestObject   = nullptr;

    for (unsigned long n = 0; n < objectsList_.size(); n++) {
        auto [intersects, t] = objectsList_.at(n)->intersect(origin, direction);

        if (intersects && std::abs(t) < std::abs(minDistance)) {
            minDistance = t;
            closestObject = objectsList_.at(n);
        }
    }
    
    if (!isfinite(minDistance) || closestObject == nullptr)
        return {false, Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), Material()};

    Vector3 point  = origin + direction * minDistance;
    Vector3 normal = closestObject->normal(point);
    return {true, point, normal, closestObject->material()};
}

void Scene::addLightSource(const LightSource &lightSource)
{
    lightSourcesList_.push_back(lightSource);
}

void Scene::addObject(Object *obj)
{
    objectsList_.push_back(obj);
}

const std::vector<Object *> &Scene::objectsList() const
{
    return objectsList_;
}

const std::vector<Scene::LightSource> &Scene::lightSourcesList() const
{
    return lightSourcesList_;
}

const Scene::Camera &Scene::camera() const
{
    return camera_;
}

const Canvas *Scene::canvas() const
{
    return canvas_;
}
