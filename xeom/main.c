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
        scene.camera.frame_width = 1000;
        scene.camera.frame_height = 1000;
        scene.antialiasing = true;
        scene.kern_size = 2;

        struct Shape ball1 = {.type = SHAPE_SPHERE};
        ball1.sphere.radius = 0.2;
        ball1.sphere.center = vec(0.0, 0.31 - 0.1, 1.0);
        ball1.shader = shader_diffuse;
        ball1.shading_hints.diffuse_roughness = 0.25;

        array_push(&scene.shapes, &ball1);

        struct Shape ball2 = {.type = SHAPE_SPHERE};
        ball2.sphere.radius = 0.2;
        ball2.sphere.center = vec(0.0, -0.088 - 0.1, 1.0);
        ball2.shader = shader_diffuse;
        ball2.shading_hints.diffuse_roughness = 0.25;

        array_push(&scene.shapes, &ball2);

        uint64_t render_pass = 0;

        struct Image outputImage;
        image_create(&outputImage, scene.camera.frame_width, scene.camera.frame_height);

        struct Image temporaryImage;
        image_create(&temporaryImage, scene.camera.frame_width, scene.camera.frame_height);

//        struct Preview prev;
//        preview_create(&prev, &outputImage);

//        while (preview_tick(&prev) == 0) {
        while (render_pass < 100) {
                printf("Rendering pass %llu ...\n", render_pass);

                if (scene_render(&scene, ((render_pass++) == 0) ? &outputImage : &temporaryImage) < 0) {
                        printf("Rendering failed: %s\n", xeom_string_error());
                        goto error;
                }

                if (render_pass <= 1)
                        continue;

                if (image_average(&outputImage, &temporaryImage) < 0) {
                        printf("Progressive refine failed: %s\n", xeom_string_error());
                        goto error;
                }
        }
//        }

        image_write(&outputImage, FORMAT_PPM, "prog_ref.ppm");

        error:
        image_free(&outputImage);
        image_free(&temporaryImage);
        scene_free(&scene);
        return 0;
}
