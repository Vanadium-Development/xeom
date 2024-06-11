//
// Created by Piotr Krzysztof Wyrwas on 04.06.24.
//

#include "pr.h"

#include "../error/error.h"

#include <pthread.h>

#include <stdbool.h>

#include <stdio.h>

struct RenderThread {
        uint64_t number;
        const struct Scene *scene;
        struct Image image;
};

void *_render(struct RenderThread *thread)
{
        printf("[Started thread %llu]\n", thread->number);

        struct Image outputImage;

        const struct Scene *scene = thread->scene;

        image_create(&outputImage, (uint64_t) scene->camera.width,
                     (uint64_t) (scene->camera.width / scene->camera.aspect_ratio));

        if (scene_render(scene, &outputImage) < 0) {
                printf("Rendering failed: %s\n", xeom_string_error());
                return NULL;
        }

        printf("[Thread %llu finished]\n", thread->number);

        thread->image = outputImage;

        return NULL;
}

struct Image render_simultaneously(struct Scene *scene, uint64_t samples)
{
        printf("[Multiprocessor-rendering %llu samples ..]\n", samples);

        pthread_t _threads[samples];
        struct RenderThread renderThreads[samples];

        uint64_t remaining_samples = samples;

//        printf("[Starting %llu rendering threads ...]\n", samples);

        for (uint64_t i = 0; i < samples; i++) {
                renderThreads[i].scene = scene;
                renderThreads[i].number = i;

                pthread_create(&_threads[i], NULL, (void *) _render, (void *) &renderThreads[i]);
        }

        for (uint64_t i = 0; i < samples; i++) {
                pthread_join(_threads[i], NULL);
        }

//        printf("[Computing mean from samples ...]\n");

        struct Image intermediate;
        image_create(&intermediate, (uint64_t) scene->camera.width,
                     (uint64_t) (scene->camera.width / scene->camera.aspect_ratio));

        for (uint64_t i = 0; i < samples; i++) {
                image_add(&intermediate, &renderThreads[i].image);
                image_free(&renderThreads[i].image);
        }

        image_compute_mean(&intermediate, samples + 1);

//        printf("[Done rendering %llu samples]\n", samples);

        return intermediate;
}
