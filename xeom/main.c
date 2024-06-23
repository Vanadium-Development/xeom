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
        scene.camera.aspect_ratio = 1.0;
//        scene.camera.focal_length = 1.5;
        scene.antialiasing = false;
        scene.kern_size = 3;

        struct Shape ball1 = {.type = SHAPE_SPHERE};
        ball1.sphere.radius = 0.5;
        ball1.sphere.center = vec(0.0, -0.5, 3.0);
        ball1.color = rgb(255, 0, 0);
        ball1.shader = shader_diffuse;
        ball1.shading_hints.diffuse_roughness = 0.2;
        array_push(&scene.shapes, &ball1);

        struct Shape ball2 = {.type = SHAPE_SPHERE};
        ball2.sphere.radius = 0.5;
        ball2.sphere.center = vec(0.0, 0.49, 3.0);
        ball2.color = rgb(0, 0, 255);
        ball2.shader = shader_diffuse;
        ball2.shading_hints.diffuse_roughness = 0.2;
        array_push(&scene.shapes, &ball2);

        struct Shape ball3 = {.type = SHAPE_SPHERE};
        ball3.sphere.radius = 0.25;
        ball3.sphere.center = vec(0.55, 0.0, 3.0);
        ball3.color = rgb(255, 255, 255);
        ball3.shader = shader_metal;
        ball3.shading_hints.metal_fuzz_amount = 1.5;
//        ball3.shading_hints.diffuse_roughness = 0.0;
        array_push(&scene.shapes, &ball3);

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
