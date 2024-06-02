//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#include "rt.h"

#include "scene.h"

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
        struct Vec3d direction = {.x = x - (int) scene->camera.frame_width / 2.0, .y = y - (double) scene->camera.frame_height / 2.0, .z = scene->camera.focal_length};
        vec3d_normalize(&direction);

        return (struct Ray) {
                .origin = (struct Vec3d) {
                        .x = 0.0,
                        .y = 0.0,
                        .z = 0.0
                },
                .direction = direction
        };
}

struct Pixel scene_trace_single(double x, double y, struct Scene *scene)
{
        struct Pixel color = pixel_black();

        struct Ray ray = scene_ray(x, y, scene);
        struct Intersection inter = trace_ray(&ray, scene);

        if (inter.exists)
                color = (struct Pixel) {255, 255, 255};

        return color;
}