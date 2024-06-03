#include <stdio.h>

#include "../image/image.h"

#include "../error/error.h"

#include "../preview/preview.h"

#include "../core/scene.h"

#include "../math/shape.h"

#include <stdbool.h>

int main(void)
{
        struct Scene scene;
        scene_create(&scene);
        scene.antialiasing = true;

        struct Shape ball1 = {.type = SHAPE_SPHERE};
        ball1.sphere.radius = 0.5;
        ball1.sphere.center = vec(0.0, 0.0, 1.5);
        ball1.shader = shader_normal;

        array_push(&scene.shapes, &ball1);

        struct Shape ball2 = {.type = SHAPE_SPHERE};
        ball2.sphere.radius = 0.25;
        ball2.sphere.center = vec(0.5, 0.0, 1.2);
        ball2.shader = shader_normal;

        array_push(&scene.shapes, &ball2);

        struct Image img;
        image_create(&img, scene.camera.frame_width, scene.camera.frame_height);

        if (scene_render(&scene, &img) < 0) {
                printf("Rendering failed: %s\n", xeom_string_error());
                goto error;
        }

        image_write(&img, FORMAT_PPM, "frame.ppm");

        struct Preview prev;
        preview_create(&prev, &img);

        while (preview_tick(&prev) == 0);

        error:
        image_free(&img);
        scene_free(&scene);
        return 0;
}
