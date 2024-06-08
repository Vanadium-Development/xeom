#include <stdio.h>

#include "../image/image.h"

#include "../preview/preview.h"

#include "../core/scene.h"

#include "../math/shape.h"

#include "../core/pr.h"

#include <stdbool.h>

#if !defined (XEOM_RENDER_SAMPLES)
        #error Number of samples is expected to be defined in compile-time macro 'XEOM_RENDER_SAMPLES'
#endif

int main(void)
{
        uint64_t nSamples = XEOM_RENDER_SAMPLES;

#ifdef XEOM_USE_GUI
        printf("The image will be revealed in an SDL preview after rendering.\n");
#else
        printf("The image will be outputted to a file after rendering.\n");
#endif

        struct Scene scene;

        scene_create(&scene);
        scene.camera.width = 1000;
        scene.camera.location.y += 0.25;
        scene.camera.aspect_ratio = 1.0;
        scene.antialiasing = false;
        scene.kern_size = 2;
        scene.ray_fuzz = 0.0;

        double groundRadius = 10000000.0;

        struct Shape goundSphere = {.type = SHAPE_SPHERE};
        goundSphere.sphere.radius = groundRadius;
        goundSphere.sphere.center = vec(0.0, groundRadius + 0.84, 1.0);
        goundSphere.color = rgb(240, 240, 240);
        goundSphere.shader = shader_diffuse;
        goundSphere.shading_hints.diffuse_roughness = 0.1;
        array_push(&scene.shapes, &goundSphere);

//        struct Shape another = {.type = SHAPE_SPHERE};
//        another.sphere.radius = 0.2;
//        another.sphere.center = vec(0.0, 0.3997 + verticalOffset, 1.0);
//        another.color = rgb(255, 0, 0);
//        another.shader = shader_metal;
//        another.shading_hints.diffuse_roughness = 0.1;
//        array_push(&scene.shapes, &another);


        for (int i = 0; i < 100; i++) {
                double radius = ((double) rand() / (double) RAND_MAX) / 4.0 + 0.05;
                struct Shape randomSphere = {.type = SHAPE_SPHERE};
                randomSphere.sphere.radius = radius;
                randomSphere.sphere.center = vec(((double) rand() / (double) RAND_MAX) * 10.0 - 6.0,
                                                 groundRadius + 0.828 - (groundRadius - (1000.0 - 999.98)) - radius,
                                                 ((double) rand() / (double) RAND_MAX) * 15.0 + 1.0);
                rand();
                randomSphere.color = rgb(rand() % 255, rand() % 255, rand() % 255);
//                randomSphere.color = rgb(100, 100, 100);
//                randomSphere.shader = shader_diffuse;
//                randomSphere.shader = shader_diffuse;
                randomSphere.shader = (rand() % 10 > 2) ? shader_diffuse : shader_metal;
                if (randomSphere.shader == shader_metal)
                        randomSphere.shading_hints.metal_fuzz_amount = 0.2;
                else
                        randomSphere.shading_hints.diffuse_roughness = 0.2;
                array_push(&scene.shapes, &randomSphere);
        }

        struct Image output = render_simultaneously(&scene, nSamples);

#ifdef XEOM_USE_GUI
        printf("Rendering done. Revealing in SDL preview.\n");

        struct Preview prev;
        preview_create(&prev, &output);

        while (preview_tick(&prev) == 0);
#else
        image_write(&output, FORMAT_PPM, "render.ppm");
        printf("Written mean of %llu samples to PPM file.\n", nSamples);
#endif

        image_free(&output);
        scene_free(&scene);
        return 0;
}
