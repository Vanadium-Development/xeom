#include <stdio.h>

#include "../image/image.h"

#include "../error/error.h"

#include "../preview/preview.h"

#include "../core/scene.h"

#include "../math/shape.h"

#include "../core/pr.h"

#include <stdbool.h>

int main(void)
{
        struct Scene scene;

        scene_create(&scene);
        scene.camera.width = 1000;
        scene.camera.location.y += 0.25;
        scene.camera.aspect_ratio = 10.0 / 9.0;
        scene.antialiasing = true;
        scene.kern_size = 3;

        double groundRadius = 4000.0;

        struct Shape goundSphere = {.type = SHAPE_SPHERE};
        goundSphere.sphere.radius = groundRadius;
        goundSphere.sphere.center = vec(0.0, groundRadius + 0.828, 0.0);
        goundSphere.color = rgb(240, 240, 240);
        goundSphere.shader = shader_diffuse;
        goundSphere.shading_hints.diffuse_roughness = 0.1;

        array_push(&scene.shapes, &goundSphere);

        for (int i = 0; i < 70; i++) {
                double radius = ((double) rand() / (double) RAND_MAX) / 4.0 + 0.05;
                struct Shape randomSphere = {.type = SHAPE_SPHERE};
                randomSphere.sphere.radius = radius;
                randomSphere.sphere.center = vec(((double) rand() / (double) RAND_MAX) * 10.0 - 6.0,
                                                 groundRadius + 0.828 - (groundRadius - (1000.0 - 999.98)) - radius,
                                                 ((double) rand() / (double) RAND_MAX) * 15.0 + 1.0);
                rand();
                randomSphere.color = rgb(rand() % 255, rand() % 255, rand() % 255);
                randomSphere.shader = (rand() % 10 > 2) ? shader_diffuse : shader_metal;
                if (randomSphere.shader == shader_metal)
                        randomSphere.shading_hints.metal_fuzz_amount = 0.2;
                randomSphere.shading_hints.diffuse_roughness = 0.25;
                array_push(&scene.shapes, &randomSphere);
        }

        render_simultaneously(&scene, 100);

//        uint64_t image_width = (uint64_t) scene.camera.width;
//        uint64_t image_height = (uint64_t) (scene.camera.width / scene.camera.aspect_ratio);
//
//        struct Image outputImage;
//        image_create(&outputImage, image_width, image_height);
//
//        struct Image temporaryImage;
//        image_create(&temporaryImage, image_width, image_height);
//
//        struct Image renderedImage;
//        image_create(&renderedImage, image_width, image_height);
//
//        struct Preview prev;
//        preview_create(&prev, &renderedImage);

//        uint64_t render_pass = 0;

//        while (preview_tick(&prev) == 0) {
//        while (true) {
//                printf("Rendering pass %llu ...\n", render_pass);
//
//                if (scene_render(&scene, ((render_pass++) == 0) ? &outputImage : &temporaryImage) < 0) {
//                        printf("Rendering failed: %s\n", xeom_string_error());
//                        goto error;
//                }
//
//                if (render_pass > 1) {
//                        image_output_average(&renderedImage, &outputImage, render_pass);
//                }
//
//                if (image_add(&outputImage, &temporaryImage) < 0) {
//                        printf("Progressive refine failed: %s\n", xeom_string_error());
//                        goto error;
//                }
//
//                if (render_pass == 200) {
//                        printf("-- PPM image of pass %llu written to file --\n", render_pass);
//                        image_write(&renderedImage, FORMAT_PPM, "cumulative_result.ppm");
//                        break;
//                }
//        }
//
//        }

//        error:
//        image_free(&outputImage);
//        image_free(&temporaryImage);
//        image_free(&renderedImage);
        scene_free(&scene);
        return 0;
}
