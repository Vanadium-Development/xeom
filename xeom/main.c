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
        scene.antialiasing = false;
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

        struct Image output = render_simultaneously(&scene, 10);

        struct Preview prev;
        preview_create(&prev, &output);

        while (preview_tick(&prev) == 0) {
                output = render_simultaneously(&scene, 100);
        }

        scene_free(&scene);
        return 0;
}
