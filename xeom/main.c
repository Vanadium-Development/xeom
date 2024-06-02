#include <stdio.h>

#include "../image/image.h"

#include "../error/error.h"

#include "../preview/preview.h"

#include "../core/scene.h"

#include "../math/shape.h"

int main(void)
{
        struct Scene scene;
        scene_create(&scene);

        struct Shape ball = {.type = SHAPE_SPHERE};
        ball.sphere.radius = 10.0;
        ball.sphere.center = (struct Vec3d) {
                .x = 0.0,
                .y = 0.0,
                .z = 300.0
        };

        array_push(&scene.shapes, &ball);

        struct Image img;
        image_create(&img, scene.camera.frame_width, scene.camera.frame_height);

        if (scene_render(&scene, &img) < 0) {
                printf("Rendering failed: %s\n", xeom_string_error());
                goto error;
        }

        struct Preview prev;
        preview_create(&prev, &img);

        while (preview_tick(&prev) == 0);

        error:
        image_free(&img);
        scene_free(&scene);
        return 0;
}
