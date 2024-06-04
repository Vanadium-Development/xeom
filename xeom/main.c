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
        scene.camera.width = 900;
        scene.camera.aspect_ratio = 1.0;
        scene.antialiasing = true;
        scene.kern_size = 3;

        struct Shape ball1 = {.type = SHAPE_SPHERE};
        ball1.sphere.radius = 0.25;
        ball1.sphere.center = vec(0.0, 0.0, 1.0);
        ball1.color = rgb(255, 0, 0);
        ball1.shader = shader_diffuse;
        ball1.shading_hints.diffuse_roughness = 0.25;

        array_push(&scene.shapes, &ball1);

        uint64_t image_width = (uint64_t) scene.camera.width;
        uint64_t image_height = (uint64_t) (scene.camera.width / scene.camera.aspect_ratio);

        struct Image outputImage;
        image_create(&outputImage, image_width, image_height);

        struct Image temporaryImage;
        image_create(&temporaryImage, image_width, image_height);

        struct Image renderedImage;
        image_create(&renderedImage, image_width, image_height);

        struct Preview prev;
        preview_create(&prev, &renderedImage);

        uint64_t render_pass = 0;

        while (preview_tick(&prev) == 0) {
                printf("Rendering pass %llu ...\n", render_pass);

                if (scene_render(&scene, ((render_pass++) == 0) ? &outputImage : &temporaryImage) < 0) {
                        printf("Rendering failed: %s\n", xeom_string_error());
                        goto error;
                }

                if (render_pass > 1) {
                        image_output_average(&renderedImage, &outputImage, render_pass);
                }

                if (image_add(&outputImage, &temporaryImage) < 0) {
                        printf("Progressive refine failed: %s\n", xeom_string_error());
                        goto error;
                }
        }

        error:
        image_free(&outputImage);
        image_free(&temporaryImage);
        image_free(&renderedImage);
        scene_free(&scene);
        return 0;
}
