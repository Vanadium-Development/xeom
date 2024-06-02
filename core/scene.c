//
// Created by Piotr Krzysztof Wyrwas on 02.06.24.
//

#include "scene.h"
#include "rt.h"

#include "../error/error.h"

#include <stdio.h>

void scene_create(struct Scene *scene)
{
        array_init(&scene->shapes, sizeof(struct Shape));
        scene->camera = (struct Camera) {
                .frame_width = 900,
                .frame_height = 900,
                .focal_length = 10000.0,
                .location = (struct Vec3d) {
                        .x = 0.0,
                        .y = 0.0,
                        .z = 0.0
                }
        };
}

void scene_free(struct Scene *scene)
{
        array_free(&scene->shapes, NULL);
}

int scene_render(struct Scene *scene, struct Image *output)
{
        if (output->width != scene->camera.frame_width || output->height != scene->camera.frame_height) {
                raise_error(XEOM_UNMATCHED_SIZES);
                return -1;
        }

        for (uint64_t y = 0; y < scene->camera.frame_height; y++) {
                for (uint64_t x = 0; x < scene->camera.frame_width; x++) {
                        struct Pixel px = scene_trace_single((double) x, (double) y, scene);
                        image_set(output, x, y, px);
                }
        }

        return 0;
}
