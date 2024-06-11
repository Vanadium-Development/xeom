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
        scene.antialiasing = false;
        scene.kern_size = 2;

        struct Shape firstSphere = {.type = SHAPE_SPHERE};
        firstSphere.sphere.radius = 0.2;
        firstSphere.sphere.center = vec(0.0, -0.15, 1.0);
        firstSphere.color = rgb(255, 0, 0);
        firstSphere.shader = shader_diffuse;
        firstSphere.shading_hints.diffuse_roughness = 0.1;
        array_push(&scene.shapes, &firstSphere);

        struct Shape secondSphere = {.type = SHAPE_SPHERE};
        secondSphere.sphere.radius = 0.2;
        secondSphere.sphere.center = vec(0.0, 0.247, 1.0);
        secondSphere.color = rgb(255, 0, 0);
        secondSphere.shader = shader_diffuse;
        secondSphere.shading_hints.diffuse_roughness = 0.1;
        array_push(&scene.shapes, &secondSphere);

        struct Image output = render_simultaneously(&scene, nSamples);

#ifdef XEOM_USE_GUI
        printf("Rendering done. Revealing in SDL preview.\n");

        struct Preview prev;
        preview_create(&prev, &output);

        while (preview_tick(&prev) == 0); // {
//                image_free(&output);
//                scene.camera.location.y += 0.1;
//                output = render_simultaneously(&scene, nSamples);
//        }
#else
        image_write(&output, FORMAT_PPM, "render.ppm");
        printf("Written mean of %llu samples to PPM file.\n", nSamples);
#endif

        image_free(&output);
        scene_free(&scene);
        return 0;
}
