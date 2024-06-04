//
// Created by Piotr Krzysztof Wyrwas on 04.06.24.
//

#include "pr.h"

#include "../error/error.h"

#include <pthread.h>

#include <stdio.h>

struct RenderThread {
        uint64_t number;
        const struct Scene *scene;
        struct Image image;
};

void *render(struct RenderThread *thread)
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

void render_simultaneously(const struct Scene *scene, uint64_t threads)
{
        pthread_t _threads[threads];
        struct RenderThread renderThreads[threads];

        printf("[Starting %llu rendering threads ...]\n", threads);

        for (uint64_t i = 0; i < threads; i++) {
                renderThreads[i].scene = scene;
                renderThreads[i].number = i;

                pthread_create(&_threads[i], NULL, (void *) render, (void *) &renderThreads[i]);
        }

        for (uint64_t i = 0; i < threads; i++)
                pthread_join(_threads[i], NULL);

        printf("[Dumping samples to files]\n");

        char *filename = malloc(100);

        for (uint64_t i = 0; i < threads; i++) {
                sprintf(filename, "sample_%llu.ppm", renderThreads[i].number);
                image_write(&renderThreads[i].image, FORMAT_PPM, filename);
                image_free(&renderThreads[i].image);
        }

        free(filename);

        printf("[All done]\n");
}
