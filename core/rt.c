//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#include "rt.h"

#include "scene.h"

#include "../math/utility.h"

#include <math.h>

struct Intersection trace_ray(struct Ray *ray, struct Scene *scene)
{
        struct Intersection inter = no_intersection();

        // Look through the array and find the closest intersection
        for (uint64_t i = 0; i < scene->shapes.length; i++) {
                struct Shape *shape = array_get(&scene->shapes, i);
                struct Intersection tmpInter = ray_shape(ray, shape);

                if (!tmpInter.exists)
                        continue;

                if (!inter.exists) {
                        inter = tmpInter;
                        continue;
                }

                if (inter.distance > tmpInter.distance)
                        inter = tmpInter;
        }

        return inter;
}

struct Ray scene_ray(double x, double y, struct Scene *scene)
{
        double x00 = 1.0 / scene->camera.width - 0.5;
        double y00 = 1.0 / (scene->camera.width / scene->camera.aspect_ratio) - 0.5;

        double dx = 1.0 / scene->camera.width;
        double dy = 1.0 / scene->camera.width / scene->camera.aspect_ratio;

        struct Vec3d direction = {.x = x00 + x * dx, .y = y00 + y * dy, scene->camera.focal_length};

        vec3d_normalize(&direction);

        return (struct Ray) {
                .origin = scene->camera.location,
                .direction = direction
        };
}

struct Pixel _scene_trace(double x, double y, struct Scene *scene)
{
        struct Ray ray = scene_ray(x, y, scene);
        return _scene_trace_raw(&ray, scene, 0);
}

struct Pixel _scene_trace_raw(struct Ray *ray, struct Scene *scene, uint64_t bounces)
{
        if (bounces > scene->bounces_limit) {
                return pixel_black();
        }

        struct Pixel color = render_sky(2, ray->direction.y + 1);

        struct Intersection inter = trace_ray(ray, scene);

        if (inter.exists) {
                if (!inter.shape->shader) {
                        color = rgb(224, 86, 253);
                } else
                        color = inter.shape->shader(&inter, scene, bounces);
        }

        return color;
}

struct Pixel scene_trace_single(double x, double y, struct Scene *scene)
{
        if (!scene->antialiasing)
                return _scene_trace(x, y, scene);

        uint64_t r = 0;
        uint64_t g = 0;
        uint64_t b = 0;

        // The kernel is a square region
        uint64_t count = scene->kern_size * scene->kern_size;

        for (uint64_t ky = 0; ky < scene->kern_size; ky++)
                for (uint64_t kx = 0; kx < scene->kern_size; kx++) {
                        struct Pixel px = _scene_trace(x + (double) kx, y + (double) ky, scene);
                        r += px.r;
                        g += px.g;
                        b += px.b;
                }

        r /= count;
        g /= count;
        b /= count;

        return (struct Pixel) {r, g, b};
}