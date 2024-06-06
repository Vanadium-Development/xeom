//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#include "scene.h"
#include "rt.h"

#include "../error/error.h"

#include <stdio.h>

#include <stdbool.h>

void scene_create(struct Scene *scene)
{
        array_init(&scene->shapes, sizeof(struct Shape));
        scene->kern_size = 4;
        scene->antialiasing = true;
        scene->camera = (struct Camera) {
                .width = 1000,
                .aspect_ratio = 16.0 / 9.0,
                .focal_length = 1.0,
                .location = vec(0.0, 0.0, 0.0),
        };
        scene->ray_fuzz = 0.1;
        scene->bounces_limit = 10;
}

void scene_free(struct Scene *scene)
{
        array_free(&scene->shapes, NULL);
}

int scene_render(struct Scene *scene, struct Image *output)
{
        for (uint64_t y = 0; y < scene->camera.width / scene->camera.aspect_ratio; y ++) {
                for (uint64_t x = 0; x < scene->camera.width; x ++) {
                        struct Pixel px = scene_trace_single((double) x, (double) y, scene);
                        image_set(output, (uint64_t) x, (uint64_t) y, px);
                }
        }

        return 0;
}
